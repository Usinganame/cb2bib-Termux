/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bTextEdit.h"

#include "c2bSettings.h"
#include "c2bUtils.h"

#include <QMenu>
#include <QPainter>
#include <QScrollBar>
#include <QTextBlock>


c2bTextEdit::c2bTextEdit(QWidget* parentw) : QPlainTextEdit(parentw)
{
    setFrameShape(QPlainTextEdit::StyledPanel);
    setFrameShadow(QPlainTextEdit::Raised);
    _settingsP = c2bSettingsP;
    connect(_settingsP, SIGNAL(newSettings()), this, SLOT(loadSettings()));

    _line_number_area = new LineNumberArea(this);
    _line_number_area_color = palette().color(QPalette::Active, QPalette::Base).darker(110);
    _line_number_color_p = &_settingsP->colors.comment_color;
    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth()));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    updateLineNumberAreaWidth();

    c2bUtils::addSeparator(this);
    toggleWordWrappingAction = new QAction(this);
    addAction(toggleWordWrappingAction);
    toggleWordWrappingAction->setText(tr("Toggle Word Wrapping"));
    toggleWordWrappingAction->setStatusTip(tr("Toggle word wrapping"));
    _settingsP->setKeysequence("Shortcuts/Editor/", toggleWordWrappingAction);
    connect(toggleWordWrappingAction, SIGNAL(triggered()), this, SLOT(toggleWordWrapping()));
    if (_settingsP->value("c2bTextEdit/WrapMode", false).toBool())
        setLineWrapMode(QPlainTextEdit::WidgetWidth);
    else
        setLineWrapMode(QPlainTextEdit::NoWrap);
}

c2bTextEdit::~c2bTextEdit()
{
    _settingsP->setValue("c2bTextEdit/WrapMode", lineWrapMode() == QPlainTextEdit::WidgetWidth);
}


void c2bTextEdit::setBibTeXActions()
{
    c2bUtils::addSeparator(this);
    pasteCurrentBibTeXAction = new QAction(this);
    addAction(pasteCurrentBibTeXAction);
    pasteCurrentBibTeXAction->setText(tr("Paste Current BibTeX"));
    pasteCurrentBibTeXAction->setStatusTip(tr("Paste current BibTeX"));
    _settingsP->setKeysequence("Shortcuts/Editor/", pasteCurrentBibTeXAction);

    setLaTeXActions();

    c2bUtils::addSeparator(this);
    journalsToFullAction = new QAction(this);
    addAction(journalsToFullAction);
    journalsToFullAction->setText(tr("Set Journals to Full Name"));
    journalsToFullAction->setStatusTip(tr("Set journals to full name"));
    _settingsP->setKeysequence("Shortcuts/Editor/", journalsToFullAction);
    journalsToAlternateFullAction = new QAction(this);
    addAction(journalsToAlternateFullAction);
    journalsToAlternateFullAction->setText(tr("Set Journals to Alternate Full Name"));
    journalsToAlternateFullAction->setStatusTip(tr("Set journals to alternate full name"));
    journalsToAbbreviatedAction = new QAction(this);
    addAction(journalsToAbbreviatedAction);
    journalsToAbbreviatedAction->setText(tr("Set Journals to Abbreviated Name"));
    journalsToAbbreviatedAction->setStatusTip(tr("Set journals to abbreviated name"));
    _settingsP->setKeysequence("Shortcuts/Editor/", journalsToAbbreviatedAction);
    journalsToAlternateAbbreviatedAction = new QAction(this);
    addAction(journalsToAlternateAbbreviatedAction);
    journalsToAlternateAbbreviatedAction->setText(tr("Set Journals to Alternate Abbreviated Name"));
    journalsToAlternateAbbreviatedAction->setStatusTip(tr("Set journals to alternate abbreviated name"));

    c2bUtils::addSeparator(this);
    updateMetadataAction = new QAction(this);
    addAction(updateMetadataAction);
    updateMetadataAction->setText(tr("Update Documents Metadata"));
    updateMetadataAction->setStatusTip(tr("Update document files metadata"));
    _settingsP->setKeysequence("Shortcuts/Editor/", updateMetadataAction);
}

void c2bTextEdit::setLaTeXActions()
{
    c2bUtils::addSeparator(this);
    convertSelection2LaTeXAction = new QAction(this);
    addAction(convertSelection2LaTeXAction);
    convertSelection2LaTeXAction->setText(tr("Selection to LaTeX"));
    convertSelection2LaTeXAction->setStatusTip(tr("Convert selection to LaTeX"));
    _settingsP->setKeysequence("Shortcuts/Editor/", convertSelection2LaTeXAction);
    connect(convertSelection2LaTeXAction, SIGNAL(triggered()), this, SLOT(convert2LaTeX()));
    convertSelection2LaTeXAction->setEnabled(false);
    connect(this, SIGNAL(copyAvailable(bool)), convertSelection2LaTeXAction, SLOT(setEnabled(bool)));
    convertSelection2UnicodeAction = new QAction(this);
    addAction(convertSelection2UnicodeAction);
    convertSelection2UnicodeAction->setText(tr("Selection to Unicode"));
    convertSelection2UnicodeAction->setStatusTip(tr("Convert selection to Unicode"));
    _settingsP->setKeysequence("Shortcuts/Editor/", convertSelection2UnicodeAction);
    connect(convertSelection2UnicodeAction, SIGNAL(triggered()), this, SLOT(convert2Unicode()));
    convertSelection2UnicodeAction->setEnabled(false);
    connect(this, SIGNAL(copyAvailable(bool)), convertSelection2UnicodeAction, SLOT(setEnabled(bool)));
}

void c2bTextEdit::contextMenuEvent(QContextMenuEvent* qevent)
{
    QMenu* menu = createStandardContextMenu();
    QList<QAction*> acts = actions();
    for (int i = 0; i < acts.count(); ++i)
        menu->addAction(acts.at(i));
    menu->exec(qevent->globalPos());
    delete menu;
}

void c2bTextEdit::keyPressEvent(QKeyEvent* qevent)
{
    QPlainTextEdit::keyPressEvent(qevent);
    if (qevent->key() == Qt::Key_Insert)
    {
        setOverwriteMode(!overwriteMode());
        emit overwriteModeChanged();
    }
}

void c2bTextEdit::toggleWordWrapping()
{
    if (lineWrapMode() == QPlainTextEdit::WidgetWidth)
        setLineWrapMode(QPlainTextEdit::NoWrap);
    else
        setLineWrapMode(QPlainTextEdit::WidgetWidth);
}

void c2bTextEdit::updatePlainText(const QString& text)
{
    const int scrollPosition(verticalScrollBar()->value());
    const int cursorBlock(textCursor().blockNumber());
    const int cursorColumn(textCursor().columnNumber());
    setPlainText(text);

    const int lposition(document()->findBlockByNumber(cursorBlock).position());
    QTextCursor tcursor(textCursor());
    tcursor.setPosition(lposition + cursorColumn, QTextCursor::MoveAnchor);
    setTextCursor(tcursor);
    verticalScrollBar()->setValue(scrollPosition);
}

void c2bTextEdit::cursorPosition(int* line_number, int* line_position) const
{
    *line_number = textCursor().blockNumber() + 1;
    *line_position = textCursor().positionInBlock() + 1;
}

void c2bTextEdit::convert2LaTeX()
{
    QString txt(textCursor().selectedText());
    // Better do the long way: Convert anything to c2b, and then
    // translate to TeX
    c2bUtils::fullBibToC2b(txt);
    insertPlainText(c2bUtils::c2bToBib(txt));
}

void c2bTextEdit::convert2Unicode()
{
    QString txt(textCursor().selectedText());
    // Strictly, this should be bibToC2b; but convert also
    // possible PNAS like, and, for consistency, HTML sub
    // and superscripts to TeX
    insertPlainText(c2bUtils::fullBibToC2b(txt));
}

void c2bTextEdit::loadSettings()
{
    if (font() != _settingsP->c2bMonoFont)
    {
        setFont(_settingsP->c2bMonoFont);
        updateLineNumberAreaWidth();
    }
    _line_number_area->update(); // Update, otherwise number colors might not follow apply button
}


/***************************************************************************
 *  Line number area (From CodeEditor Qt's example)
 ***************************************************************************/

int c2bTextEdit::lineNumberAreaWidth()
{
    int digits(1);
    int dmax(std::max(1, blockCount()));
    while (dmax >= 10)
    {
        dmax /= 10;
        ++digits;
    }
#if QT_VERSION >= QT_VERSION_CHECK(5, 11, 0)
    const int space(5 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits);
#else
    const int space(5 + fontMetrics().width(QLatin1Char('9')) * digits);
#endif
    return space;
}

void c2bTextEdit::updateLineNumberAreaWidth()
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void c2bTextEdit::updateLineNumberArea(const QRect& qrect, int dy)
{
    if (dy)
        _line_number_area->scroll(0, dy);
    else
        _line_number_area->update(0, qrect.y(), _line_number_area->width(), qrect.height());
    if (qrect.contains(viewport()->rect()))
        updateLineNumberAreaWidth();
}

void c2bTextEdit::resizeEvent(QResizeEvent* qevent)
{
    QPlainTextEdit::resizeEvent(qevent);
    QRect cr = contentsRect();
    _line_number_area->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void c2bTextEdit::lineNumberAreaPaintEvent(QPaintEvent* qevent)
{
    QPainter painter(_line_number_area);
    painter.fillRect(qevent->rect(), _line_number_area_color);
    painter.setPen(*_line_number_color_p);
    QFont f = font();
    f.setPointSize(std::max(0, f.pointSize() - 3));
    painter.setFont(f);

    QTextBlock block = firstVisibleBlock();
    int blockNumber(block.blockNumber());
    int top(int(blockBoundingGeometry(block).translated(contentOffset()).top()));
    int bottom(top + int(blockBoundingRect(block).height()));

    while (block.isValid() && top <= qevent->rect().bottom())
    {
        if (block.isVisible() && bottom >= qevent->rect().top())
        {
            const QString number(QString::number(blockNumber + 1));
            painter.drawText(5, top + 2, _line_number_area->width(), fontMetrics().height(), Qt::AlignLeft, number);
        }
        block = block.next();
        top = bottom;
        bottom = top + (int)blockBoundingRect(block).height();
        ++blockNumber;
    }
}
