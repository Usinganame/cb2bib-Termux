/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bSaveRegExp.h"

#include "c2b.h"
#include "c2bSaveREHighlighter.h"
#include "c2bSettings.h"
#include "c2bUtils.h"

#include <QPushButton>


/** \page regexpeditor Regular Expression Editor

  Once a manual processing is done, cb2Bib clipboard area contains the
  extraction tags, plus, possibly, some other cb2Bib tags introduced during the
  preprocessing (see \ref clipboard). The <b>RegExp Editor</b> will generate a
  guess regular expression or matching pattern usable for automated
  extractions.

  The cb2Bib matching patterns consist of four lines: a brief description, the
  reference type, an ordered list of captured fields, and the regular
  expression itself.

\htmlonly
<pre>
# cb2Bib GET_VERSION Pattern:
American Chemical Society Publications
article
journal volume pages year title author abstract
^(.+), (\d+) \(.+\), ([\d|\-|\s]+),(\d\d\d\d)\..+&#060;NewLine3&#062;(.+)&#060;NewLine4&#062;
(.+)&#060;NewLine5&#062;.+Abstract:&#060;NewLine\d+&#062;(.+)$
</pre>
\endhtmlonly

  The Regular Expression Editor provides the basic skeleton and a set of
  predefined suggestions. The regular expressions follow a Perl-like sintax.
  There are, however, some slight differences and minor limitations.
  Information about the basics on the editing and working with Regular
  Expressions as used by cb2Bib can be found at the Qt document file
\htmlonly
<a href="https://doc.qt.io/archives/qt-5.6/QRegExp.html#introduction"
target="_blank">Qt Documentation's QRegExp Class</a>.
\endhtmlonly


  <b>Remember when creating and editing regular expressions:</b>

  - Switch the clipboard mode to 'Tagged Clipboard Data', using the clipboard
  panel context menu.

  - Extract the bibliographic reference manually. On the clipboard panel will
  appear some cb2Bib tags that indicate which fields are being extracted. Once
  done, type Alt+I to enter to the regular expression editor. In the editor,
  there are the four line edits that define a cb2Bib pattern, one copy of the
  clipboard panel, and an information panel. The information panel displays
  possible issues, and, once everything is correct, the actual extracted
  fields. The clipboard panel highlights the captures for the current regular
  expression and current input text.

  - Patterns can be modified at any time by typing Alt+E to edit the regular
  expression file. Patterns are reloaded each time the automatic pattern
  recognition is started. This permits editing and testing.

  - cb2Bib processes sequentially the list of regular expressions as found
  in the regular expression file. It stops and picks the first match for the
  current input. <b>Therefore, the order of the regular expressions is
  important</b>. Consequently, to avoid possible clashing among similar
  patterns, consider sorting them from the most restrictive pattern to the less
  one. As a rule of thumb, the more captions it has the most restrictive a
  pattern is.

  - <b>The cb2Bib proposed patterns are general, and not necessarily the most
  appropriate for a particular capture</b>. E.g. tag <tt>pages</tt> becomes
  <tt>([\\d|\\-|\\s]+)</tt>, which considers digits, hyphens, and spaces. It
  must be modified accordingly for reference sources with, e.g., <tt>pages</tt>
  written as Roman ordinals.

  - <b>Avoid whenever possible general patterns <tt>(.+)</tt></b>. There is a
  risk that such a caption could include text intended for a posterior caption.
  This is why, sometimes, the cb2Bib proposed pattern is not hit by the input
  stream that originated it. <b>Use, whenever possible, cb2Bib anchors like
  <tt>\<NewLine1\></tt> instead of <tt>\<NewLine\\d+\></tt>. They prevent
  <tt>(.+)</tt> captions to overextend</b>.

  - To debug a large regular expression it might be useful to break it to the
  first capturing parenthesis. For instance, the above pattern will be

\verbatim
# cb2Bib GET_VERSION Pattern:
American Chemical Society Publications
article
journal
^(.+),
\endverbatim

  - Then, check if anything is captured and if this corresponds to
  <tt>journal</tt>.

  - Add on successive steps your set of captions and BibTeX fields.

*/
c2bSaveRegExp::c2bSaveRegExp(const QStringList& pattern, const QString& input, QWidget* parentw) : QDialog(parentw)
{
    Q_ASSERT_X(pattern.count() == 3, "c2bSaveRegExp", "Expected exactly three strings for pattern");
    ui.setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    connect(ui.buttonBox, SIGNAL(helpRequested()), this, SLOT(help()));
    c2bSettings* settings(c2bSettingsP);
    ui.Input->setFont(settings->c2bMonoFont);
    ui.Type->setText(pattern.at(0));
    ui.Fields->setText(pattern.at(1));
    ui.RegExp->setText(pattern.at(2));
    ui.Name->setFocus();
    updateInput(input);
    _pattern_rx.setMinimal(true);
    _sreS = new c2bSaveREHighlighter(_pattern_rx, ui.Input->document());
    setInformation();
    connect(ui.Type, SIGNAL(textChanged(QString)), this, SLOT(setInformation()));
    connect(ui.Fields, SIGNAL(textChanged(QString)), this, SLOT(setInformation()));
    connect(ui.RegExp, SIGNAL(textChanged(QString)), this, SLOT(setInformation()));
    connect(ui.Input, SIGNAL(textChanged()), this, SLOT(inputMightHaveChanged()));
}

c2bSaveRegExp::~c2bSaveRegExp() {}


void c2bSaveRegExp::setInformation()
{
    QString info;
    bool can_save(false);
    const QStringList field_list(ui.Fields->text().split(' ', QString::SkipEmptyParts));
    const int fields(field_list.count());
    _pattern_rx.setPattern(ui.RegExp->text());
    const int captures(_pattern_rx.captureCount());
    if (_pattern_rx.isValid() && fields > 0 && fields == captures && !ui.Type->text().isEmpty())
    {
        info += tr("Reference type: %1\n").arg(ui.Type->text());
        info += tr("Number of fields: %1\n").arg(fields);
        can_save = true;
    }
    else
    {
        if (ui.Type->text().isEmpty())
            info += tr("[Error] Invalid pattern: empty reference type\n");
        if (fields == 0)
            info += tr("[Error] Invalid pattern: no fields declared\n");
        if (_pattern_rx.isValid())
        {
            if (captures == 0)
            {
                if (_pattern_rx.pattern().isEmpty())
                    info += tr("[Error] Invalid pattern: empty regular expression\n");
                else
                    info += tr("[Error] Invalid pattern: no captures defined in the regular expression\n");
            }
            else if (fields != captures)
                info += tr("[Error] Invalid pattern: declared %1 fields while the regular expression has %2 captures\n")
                        .arg(fields)
                        .arg(captures);
        }
        else
            info += tr("[Error] Invalid regular expression: %1\n").arg(_pattern_rx.errorString());
    }
    if (can_save)
    {
        if (_pattern_rx.indexIn(ui.Input->toPlainText()) == -1 || _pattern_rx.matchedLength() < 1)
            info += tr("[Info] Regular expression does not match input text\n");
        else
        {
            bibParser* bp = c2b::bibParser();
            for (int i = 0; i < fields; ++i)
            {
                const QString& f = field_list.at(i);
                const QString v(bp->parse(f, _pattern_rx.cap(i + 1)));
                info += QString("[%1]: '%2'\n").arg(f, v);
            }
        }
    }
    ui.Information->setPlainText(info);
    ui.buttonBox->button(QDialogButtonBox::Save)->setEnabled(can_save);
    _sreS->rehighlight();
}

void c2bSaveRegExp::updateInput(const QString& text)
{
    if (!ui.Input->textCursor().hasSelection())
        ui.Input->setPlainText(c2b::bibParser()->setTags(text));
}

void c2bSaveRegExp::inputMightHaveChanged()
{
    // Avoid recursively calling setInformation due to syntax highlighting
    if (_input_text == ui.Input->toPlainText())
        return;
    _input_text = ui.Input->toPlainText();
    setInformation();
}

void c2bSaveRegExp::accept()
{
    const QString rx(ui.Type->text() + '\n' + ui.Fields->text() + '\n' + ui.RegExp->text());
    emit savePatternInfo(rx, ui.Name->text());
    QDialog::accept();
}

void c2bSaveRegExp::help()
{
    c2bUtils::displayHelp("https://www.molspaces.com/cb2bib/doc/regexpeditor/");
}
