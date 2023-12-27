/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bPdfImport.h"

#include "c2b.h"
#include "c2bFileDialog.h"
#include "c2bSettings.h"
#include "c2bUtils.h"

#include <document.h>

#include <QDropEvent>
#include <QMimeData>
#include <QPushButton>
#include <QTimer>
#include <QUrl>


/** \page pdfimport PDF Reference Import

<p>GET_TABLE_OF_CONTENTS</p>


  \section intro_automatic_extraction Introduction

  Articles in PDF or other formats that can be converted to plain text can be
  processed and indexed by cb2Bib. Files can be selected using the Select Files
  button, or dragging them from the desktop or the file manager to the
  PDFImport dialog panel. Files are converted to plain text by using any
  external translation tool or script. This tool, and optionally its
  parameters, are set in the cb2Bib configure dialog. See the \ref
  c2bconf_utilities section for details.

  Once the file is converted, the text, and optionally, the preparsed metadata,
  is sent to cb2Bib for reference recognition. This is the usual, two step
  process. First, text is optionally preprocessed, using a simple set of rules
  and/or any external script.or tool. See \ref c2bconf_clipboard. Second, text
  is processed for reference extraction. cb2Bib so far uses two methods. One
  considers the text as a full pattern, which is checked against the user's set
  of regular expressions. The better designed are these rules, the best and
  most reliable will be the extraction. The second method, used when no regular
  expression matches the text, considers instead a set of predefined
  subpatterns. See \ref heuristics.

  At this point users can interact and supervise their references, right before
  saving them. Allowing user intervention is and has been a design goal in
  cb2Bib. Therefore, at this point, cb2Bib helps users to check their
  references. Poorly translated characters, accented letters, 'forgotten'
  words, or some minor formatting in the titles might be worth considering. See
    \htmlonly
    <a href="https://www.glyphandcog.com/textext.html" target="_blank">Glyph & Cog's Text Extraction</a>
    \endhtmlonly
  for a description on the intricacies of PDF to text conversions. In addition,
  if too few fields were extracted, one might perform a network query. Say,
  only the DOI was catch, then there are chances that such a query will fill
  the remaining fields.

  The references are saved from the cb2Bib main panel. Once Save is pressed,
  and depending on the configuration, see \ref c2bconf_documents, the document
  file will be either renamed, copied, moved or simply linked onto the
  <tt>file</tt> field of the reference. If <b>Insert BibTeX metadata to
  document files</b> is checked, the current reference will also be inserted
  into the document itself.


  When several files are going to be indexed, the sequence can be as follows:

  - <b>Process next after saving</b>\n Once files are load and Process is
  pressed, the PDFImport dialog can be minimized (but not closed) for
  convenience. All required operations to completely fill the desired fields
  (e.g. dynamic bookmarks, open DOI, etc, which might be required if the data
  in document is not complete) are at this point accessible from the main
  panel. The link in the <tt>file</tt> field <b>will be permanent</b>, without
  regard to which operations (e.g. clipboard copying) are needed, until the
  reference is saved. The source file can be open at any time by right clicking
  the <tt>file</tt> line edit. Once the reference is saved, the next file will
  be automatically processed. To skip a given document file from saving its
  reference, press the Process button.


  - <b>Unsupervised processing</b>\n In this operation mode, all files will be
  sequentially processed, following the chosen steps and rules. <b>If the
  processes is successful</b>, the reference is automatically saved, and the
  next file is processed. <b>If it is not</b>, the file is skipped and no
  reference is saved. While processing, the clipboard is disabled for safety.
  Once finished, this box is unchecked, to avoid a possible accidental saving
  of a void reference. Network queries that require intervention, i.e., whose
  result is launching a given page, are skipped. The processes follows until
  all files are processed. However, it will stop to avoid a file being
  overwritten, as a result of a repeated key. In this case, it will resume
  after manual renaming and saving. See also \ref commandline, commands
  <tt>--txt2bib</tt> and <tt>--doc2bib</tt>.


  <p>&nbsp;</p>
  \section faq_automatic_extraction Automatic Extraction: Questions and Answers

  - <b>When does cb2Bib do automatic extractions?</b>\n
    cb2Bib is conceived as a lightweight tool to extract references and manage
    bibliographies in a simple, fast, and accurate way. Accuracy is better
    achieved in semi-automatic extractions. Such extractions are handy, and
    allow user intervention and verification. However, in cases where one has
    accumulated a large number of unindexed documents, automatic processing can
    be convenient. cb2Bib does automatic extraction when, in PDFImport mode,
    'Unsupervised processing' is checked, or, in command line mode, when typing
    <tt>cb2bib --doc2bib *.pdf tmp_references.bib</tt>, or, on Windows,
    <tt>c2bconsole.exe</tt> instead of <tt>cb2bib</tt>.

  - <b>Are PDFImport and command line modes equivalent?</b>\n
    Yes. There are, however, two minor differences. First, PDFImport adds each
    reference to the current BibTeX file, as this behavior is the normal one in
    cb2Bib. On the other hand, command line mode will, instead, overwrite
    <tt>tmp_references.bib</tt> if it exists, as this is the expected behavior
    for almost all command line tools. Second, as for now, command line mode
    does not follow the configuration option 'Check Repeated On Save'.

  - <b>How do I do automatic extraction?</b>\n
    To test and learn about automatic extractions, the cb2Bib distribution
    includes a set of four PDF files that mimic a paper title page. For these
    files, distribution also includes a regular expression, in file
    <tt>regexps.txt</tt>, capable of extracting the reference fields, provided
    the <tt>pdftotex</tt> flags are set to their default values. Processing
    these files, should, therefore, be automatic, and four messages stating
    <tt>Processed as 'PDF Import Example'</tt> should be seen in the logs. Note
    that extractions are configurable. A reading of \ref configuration will
    provide additional, useful information.

  - <b>Why some entries are not saved and files not renamed?</b>\n
    Once you move from the fabricated examples to real cases, you will realize
    that some of the files, while being processed, are not renamed and their
    corresponding BibTeX data is not written. For each document file, cb2Bib
    converts its first page to text, and from this text it attempts to extract
    the bibliographic reference. By design, when extraction fails, cb2Bib does
    nothing: no file is moved, no BibTeX is written. This way, you know that
    the remaining files in the origin directory need special, manual attention.
    <b>Extractions are seen as failed, unless reliable data is found in the
    text</b>.

  - <b>What is <em>reliable data</em>?</b>\n
    Note that computer processing of natural texts, as extracting the
    bibliographic data from a title page, is nowadays an approximated
    procedure. cb2Bib tries several strategies: <b>1)</b> allow for including
    user regular expressions very specific to the extraction at hand, <b>2)</b>
    use metadata if available, <b>3)</b> guess what is reasonable, and, based
    on this, make customized queries. Then, cb2Bib considers extracted <b>data
    is reliable if i)</b> data comes from a match to an user supplied regular
    expression <b>ii)</b> document contains BibTeX metadata, or <b>iii)</b> a
    guess is transformed through a query to formatted bibliographic data. As
    formatted bibliographic data, cb2Bib understands BibTeX, PubMed XML, arXiv
    XML, and CR JSON data. In addition, it allows external processing if
    needed. Other data, metadata, guesses, and guesses on query results are
    considered unreliable data.

  - <b>Is metadata reliable data?</b>\n
    No. Only author, title, and keywords in standard PDF metadata can be mapped
    to their corresponding bibliographic fields. Furthermore, publishers most
    often misuse these three keys, placing, for instance, DOI in title, or
    setting author to, perhaps, the document typesetter. Only BibTeX XMP
    metadata is considered reliable. If you consider that a set of PDF files
    does contain reliable data, you may force to accept it using the command
    line switch <tt>--sloppy</tt> together with <tt>--doc2bib</tt>.

  - <b>How successful is automatic extraction?</b>\n
    As it follows from the given definition of reliable data, running automatic
    extractions without adhoc <tt>regexps.txt</tt> and <tt>netqinf.txt</tt>
    files will certainly give a zero success ratio. In practice, scenario 3)
    often applies: cb2Bib guesses several fields, and, based on the
    out-of-the-box <tt>netqinf.txt</tt> file, it obtains from the web either
    BibTeX, PubMed XML, arXiv XML, or CR JSON data.

  - <b>What can I do to increase success ratio?</b>\n
    First, set your favorite journals in file <tt>abbreviations.txt</tt>.
    Besides increasing the chances of journal name recognition, it will provide
    consistency across your BibTeX database. In general, do not write regular
    expressions to extract directly from the PDF text. Conversion is often
    poor. Special characters often break lines, thus breaking your regular
    expressions too. Write customized queries instead. For instance, if your
    PDFs have DOI in title page, set the simple query
\verbatim
journal=The Journal of Everything|
query=https://dx.doi.org/<<doi>>
capture_from_query=
referenceurl_prefix=
referenceurl_sufix=
pdfurl_prefix=
pdfurl_sufix=
action=htm2txt_query
\endverbatim
    then, if it is feasible to extract the reference from the document's web
    page using a regular expression, include it in file <tt>regexps.txt</tt>.
    Note that querying in cb2Bib had been designed having in mind minority
    fields of research, for which, established databases might not be
    available. If cb2Bib failed to make reasonable guesses, then, you might
    consider writing very simple regular expressions to extract directly from
    the PDF text. For instance, obtain title only. Then, the posterior query
    step can provide the remaining information. Note also, especially for old
    documents, journal name is often missing from the paper title page. If in
    need of processing a series of those papers, consider using a simple
    script, that, in the cb2Bib preprocessing step, adds this missing
    information.

  - <b>Does successful extraction mean accurate extraction?</b>\n
    No. An extraction is successful if reliable data, as defined above, is
    found in the text, in the metadata, or in the text returned by a query.
    Reference accuracy relies on whether or not user regular expressions are
    robust, BibTeX metadata is correct, a guess is appropriate, a set of
    queries can correct a partially incorrect guess, and the text returned by a
    query is accurate. In general, well designed sets of regular expressions
    are accurate. Publisher's abstract pages and PubMed are accurate. But, some
    publishers are still using images for non-ASCII characters, and PubMed
    algorithms may drop author middle names if a given author has 'too many
    names'. Expect convenience over accuracy on other sources.


  - <b>Can I use cb2Bib to extract comma separated value CSV references?</b>\n
    Yes. To automatically import multiple CSV references you will need one
    regular expression. If you can control CSV export, choose | as separator,
    since comma might be used, for instance, in titles. The regular expression
    for
\verbatim
AuthName1, AuthName2 | Title | 2010
\endverbatim
    will simply be
\verbatim
author title year
^([^|]*)\|([^|]*)\|([^|]*)$
\endverbatim
    The reference file <tt>references.csv</tt> can then be split to single-line
    files typing
\verbatim
split -l 1 references.csv slineref
\endverbatim
    and the command
\verbatim
cb2bib --txt2bib slineref* references.bib
rm -f slineref*
\endverbatim
  will convert <tt>references.csv</tt> to BibTeX file <tt>references.bib</tt>

*/
c2bPdfImport::c2bPdfImport(QWidget* parentw) : QDialog(parentw)
{
    ui.setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    settings = c2bSettingsP;
    loadSettings();

    buttonSelectFiles = new QPushButton(tr("&Select Files"));
    buttonSelectFiles->setStatusTip(tr("Select PDF files. Hint: Files can be dragged and dropped to this window"));
    buttonSelectFiles->setMouseTracking(true);
    ui.buttonBox->addButton(buttonSelectFiles, QDialogButtonBox::ActionRole);
    buttonProcess = new QPushButton(tr("&Process"));
    ui.buttonBox->addButton(buttonProcess, QDialogButtonBox::ActionRole);
    ui.buttonBox->button(QDialogButtonBox::Help)->setAutoDefault(false);
    buttonProcess->setAutoDefault(true);
    buttonProcess->setDefault(true);
    buttonProcess->setEnabled(false);
    buttonSelectFiles->setAutoDefault(true);
    buttonSelectFiles->setDefault(true);
    buttonSelectFiles->setFocus();
    ui.buttonBox->button(QDialogButtonBox::Abort)->setAutoDefault(false);
    ui.buttonBox->button(QDialogButtonBox::Abort)->setEnabled(false);
    m_aborted = false;

    connect(ui.buttonBox->button(QDialogButtonBox::Abort), SIGNAL(clicked()), this, SLOT(abort()));
    connect(ui.buttonBox, SIGNAL(helpRequested()), this, SLOT(help()));
    connect(buttonSelectFiles, SIGNAL(clicked()), this, SLOT(selectFiles()));
    connect(buttonProcess, SIGNAL(clicked()), this, SLOT(processOneFile()));
    connect(ui.DoAll, SIGNAL(toggled(bool)), this, SIGNAL(setClipboardDisabled(bool)));
    connect(c2b::instance(), SIGNAL(statusMessage(QString)), this, SLOT(showMessage(QString)));

    ui.Log->appendPlainText(
        tr("PDF to Text converter: %1\nArguments: %2\n")
        .arg(settings->fileName("c2bPdfImport/Pdf2TextBin"), settings->value("c2bPdfImport/Pdf2TextArg").toString()));
    showMessage(tr("See cb2Bib install directory for demo c2bPdfImport files."));
}

c2bPdfImport::~c2bPdfImport()
{
    emit setClipboardDisabled(false);
    saveSettings();
}


void c2bPdfImport::processOneFile()
{
    // Converting PDF to Text
    buttonProcess->setEnabled(false);
    m_aborted = false;
    ui.buttonBox->button(QDialogButtonBox::Abort)->setEnabled(ui.DoAll->isChecked());
    settings->setValue("networkQuery/isSupervised", !ui.DoAll->isChecked());
    settings->setValue("cb2Bib/AutomaticQuery", ui.AutomaticQuery->isChecked());

    if (ui.PDFlist->currentItem() == 0)
        return;
    processedFile = ui.PDFlist->currentItem()->text();
    if (ui.OpenFiles->isChecked())
        c2bUtils::openFile(processedFile, this);

    QCoreApplication::processEvents();
    processDocument();
}

void c2bPdfImport::processNext()
{
    processedFile.clear();
    if (m_aborted)
    {
        m_aborted = false;
        return;
    }
    if (ui.PDFlist->currentItem() == 0)
        return;
    if (ui.DoNextAfterSaving->isChecked() || ui.DoAll->isChecked())
        processOneFile();
}

void c2bPdfImport::processDocument()
{
    document doc(processedFile, document::FirstPage);
    QString text(doc.toString());
    const QString log(doc.logString());
    if (!log.isEmpty())
        ui.Log->appendPlainText(log);
    const QString error(doc.errorString());
    if (!error.isEmpty())
        ui.Log->appendPlainText(tr("[cb2bib] %1.").arg(error));

    QListWidgetItem* item = ui.PDFlist->currentItem();
    delete item;
    if (ui.PDFlist->currentItem() == 0)
    {
        buttonProcess->setEnabled(false);
        ui.buttonBox->button(QDialogButtonBox::Close)->setFocus();
    }
    else
    {
        buttonProcess->setEnabled(true);
        buttonProcess->setFocus();
    }

    QString metadata;
    if (settings->value("cb2Bib/AddMetadata").toBool())
        metadata = c2b::documentMetadata(processedFile);
    if (text.isEmpty() && metadata.isEmpty())
    {
        if (ui.DoAll->isChecked())
            QTimer::singleShot(500, this, SLOT(processNext()));
    }
    else
    {
        if (settings->value("cb2Bib/PreAppendMetadata").toString() == "prepend")
            text = metadata + text;
        else
            text = text + '\n' + metadata;
        ui.Log->appendPlainText(tr("[cb2bib] Conversion completed for file %1.").arg(processedFile));
        emit textProcessed(text);
        emit fileProcessed(processedFile);
    }
}

void c2bPdfImport::referenceExtacted(bool status)
{
    if (!ui.DoAll->isChecked())
        return;
    if (ui.PDFlist->currentItem() == 0)
    {
        ui.DoAll->setChecked(false);
        ui.buttonBox->button(QDialogButtonBox::Abort)->setEnabled(false);
    }

    // Delay request to make sure fileProcessed has finished
    if (status)
        QTimer::singleShot(500, this, SIGNAL(saveReferenceRequest()));
    else
        QTimer::singleShot(500, this, SLOT(processNext()));
}

void c2bPdfImport::dropEvent(QDropEvent* qevent)
{
    const QList<QUrl> fns(qevent->mimeData()->urls());
    for (int i = 0; i < fns.count(); ++i)
    {
        QString scheme(fns.at(i).scheme());
        QString fn;
        if (scheme == "file")
            fn = fns.at(i).toLocalFile();
        if (!fn.isEmpty())
        {
            QListWidgetItem* item(new QListWidgetItem(fn, ui.PDFlist));
            if (ui.PDFlist->currentItem() == 0)
                ui.PDFlist->setCurrentItem(item);
        }
    }
    qevent->acceptProposedAction();
    c2bUtils::setWidgetOnTop(this);
    buttonProcess->setEnabled(true);
    buttonProcess->setFocus();
    showMessage(tr("%1 files selected.").arg(ui.PDFlist->count()));
}

void c2bPdfImport::dragEnterEvent(QDragEnterEvent* qevent)
{
    if (qevent->mimeData()->hasUrls())
        qevent->acceptProposedAction();
}

bool c2bPdfImport::event(QEvent* qevent)
{
    if (qevent->type() == QEvent::StatusTip)
    {
        ui.statusBar->showMessage(static_cast<QStatusTipEvent*>(qevent)->tip());
        return true;
    }
    else
        return QWidget::event(qevent);
}

void c2bPdfImport::selectFiles()
{
    const QStringList fns(c2bFileDialog::getOpenFilenames(this, QString(), settings->fileName("c2bPdfImport/LastFile"),
                          tr("Portable Document Format (*.pdf);;All (*)")));
    if (fns.isEmpty())
        return;
    settings->setFilename("c2bPdfImport/LastFile", fns.last());

    for (QStringList::const_iterator i = fns.constBegin(); i != fns.constEnd(); ++i)
    {
        QListWidgetItem* item(new QListWidgetItem(*i, ui.PDFlist));
        if (ui.PDFlist->currentItem() == 0)
            ui.PDFlist->setCurrentItem(item);
    }
    buttonProcess->setEnabled(true);
    buttonProcess->setFocus();
    showMessage(tr("%1 files selected.").arg(ui.PDFlist->count()));
}

void c2bPdfImport::show()
{
    c2bUtils::setWidgetOnTop(this);
    if (buttonProcess->isEnabled())
        buttonProcess->setFocus();
    else
        buttonSelectFiles->setFocus();
    QDialog::show();
}

void c2bPdfImport::showMessage(const QString& ms)
{
    ui.statusBar->showMessage(ms, C2B_MESSAGE_TIME);
    if (ms.startsWith(tr("Processed as")) || ms.startsWith(tr("Unable")))
        ui.Log->appendPlainText("[cb2bib] " + ms);
}

void c2bPdfImport::loadSettings()
{
    c2bAutomaticQuery = settings->value("cb2Bib/AutomaticQuery").toBool();
    ui.AutomaticQuery->setChecked(settings->value("c2bPdfImport/AutomaticQuery").toBool());
    ui.DoNextAfterSaving->setChecked(settings->value("c2bPdfImport/DoNextAfterSaving", true).toBool());
    ui.OpenFiles->setChecked(settings->value("c2bPdfImport/OpenFiles", false).toBool());
}

void c2bPdfImport::saveSettings()
{
    settings->setValue("c2bPdfImport/AutomaticQuery", ui.AutomaticQuery->isChecked());
    settings->setValue("c2bPdfImport/DoNextAfterSaving", ui.DoNextAfterSaving->isChecked());
    settings->setValue("c2bPdfImport/OpenFiles", ui.OpenFiles->isChecked());
    settings->setValue("cb2Bib/AutomaticQuery", c2bAutomaticQuery);
    settings->setValue("networkQuery/isSupervised", true);
}

void c2bPdfImport::abort()
{
    m_aborted = true;
    ui.DoAll->setChecked(false);
    ui.buttonBox->button(QDialogButtonBox::Abort)->setEnabled(false);
}

void c2bPdfImport::help()
{
    c2bUtils::displayHelp("https://www.molspaces.com/cb2bib/doc/pdfimport/");
}
