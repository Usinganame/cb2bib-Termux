/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bClipEdit.h"

#include "c2b.h"
#include "c2bBibHighlighter.h"
#include "c2bHighlighter.h"

#include <QAction>
#include <QContextMenuEvent>
#include <QMenu>
#include <QScrollBar>
#include <QTextCursor>


c2bClipEdit::c2bClipEdit(const Mode mode, QWidget* parentw) : QPlainTextEdit(parentw)
{
    setFrameShape(QPlainTextEdit::StyledPanel);
    setFrameShadow(QPlainTextEdit::Raised);
    viewport()->setAcceptDrops(false);
    _has_selecting_ended = false;
    _is_tagged_view = false;
    if (mode == Editor)
    {
        new c2bHighlighter(document());
        setReadOnly(false);
        connect(this, SIGNAL(selectionChanged()), this, SLOT(selectionHasChanged()));
    }
    else if (mode == Browser)
    {
        new c2bBibHighlighter(document());
        setReadOnly(true);
    }
}

c2bClipEdit::~c2bClipEdit() {}


void c2bClipEdit::setText(const QString& text, const QString& tagged_text)
{
    _text = text;
    if (tagged_text.isEmpty())
        _tagged_text = text;
    else
        _tagged_text = tagged_text;
    if (_is_tagged_view)
        setPlainText(_tagged_text);
    else
        setPlainText(_text);
}

void c2bClipEdit::insertTag(const QString& tag)
{
    if (_is_tagged_view)
        insertPlainText(tag);
    else
        insertPlainText("[[" + textCursor().selectedText() + "]]");
}

void c2bClipEdit::setTaggedViewMode(bool tagged_view)
{
    _is_tagged_view = tagged_view;
    if (_is_tagged_view)
    {
        _text = toPlainText();
        setPlainText(_tagged_text);
    }
    else
    {
        _tagged_text = toPlainText();
        setPlainText(_text);
    }
}

void c2bClipEdit::updatePlainText(const QString& text)
{
    const int scrollPosition(verticalScrollBar()->value());
    setPlainText(text);
    verticalScrollBar()->setValue(scrollPosition);
}

void c2bClipEdit::keyPressEvent(QKeyEvent* qevent)
{
    _has_selecting_ended = false;
    QPlainTextEdit::keyPressEvent(qevent);
}

void c2bClipEdit::keyReleaseEvent(QKeyEvent* qevent)
{
    QPlainTextEdit::keyReleaseEvent(qevent);
    if (_has_selecting_ended && qevent->key() == Qt::Key_Shift)
        if (textCursor().hasSelection())
        {
            _has_selecting_ended = false;
            emit userEndedSelection(mapToGlobal(cursorRect().topLeft()));
        }
}

void c2bClipEdit::mouseReleaseEvent(QMouseEvent* qevent)
{
    QPlainTextEdit::mouseReleaseEvent(qevent);
    if (qevent->button() == Qt::LeftButton)
        if (textCursor().hasSelection())
            emit userEndedSelection(QCursor::pos());
    _has_selecting_ended = false;
}

void c2bClipEdit::selectionHasChanged()
{
    _has_selecting_ended = textCursor().hasSelection();
}

void c2bClipEdit::contextMenuEvent(QContextMenuEvent* qevent)
{
    QMenu* edit_menu = createStandardContextMenu();
    edit_menu->setTitle(tr("Edit..."));
    QList<QAction*> acts = edit_menu->actions();
    if (!isReadOnly())
    {
        QAction* act;
        act = new QAction(tr("Clear"), edit_menu);
        act->setEnabled(acts.last()->isEnabled()); // As is Select All
        connect(act, SIGNAL(triggered()), this, SLOT(clear()));
        edit_menu->insertAction(acts.at(7), act);
    }
    QMenu* menu = new QMenu(this);
    menu->addMenu(edit_menu);
    menu->addSeparator();
    acts = c2b::netqinf()->bookmarkActions(textCursor().selectedText());
    for (int i = 0; i < acts.count(); ++i)
        menu->addAction(acts.at(i));
    acts = actions();
    for (int i = 0; i < acts.count(); ++i)
        menu->addAction(acts.at(i));
    menu->exec(qevent->globalPos());
    delete edit_menu;
    delete menu;
}
