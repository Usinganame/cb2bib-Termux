/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 *   findDialog was originally adapted from Qt Designer
 *   Copyright (C) 2001 Trolltech AS.  All rights reserved.
 ***************************************************************************/
#include "findDialog.h"

#include <QAction>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QScrollBar>
#include <QTextEdit>


findDialog::findDialog(QWidget* parentw) : QDialog(parentw)
{
    ui.setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    resize(size().width(), 1);
    ui.buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Find"));
    _editor = 0;

    QAction* act = new QAction(this);
    act->setSeparator(true);
    addAction(act);
    findAction = new QAction(this);
    addAction(findAction);
    findAction->setShortcut(QKeySequence::Find);
    findAction->setText(tr("Find"));
    findAction->setStatusTip(tr("Find in text"));
    connect(findAction, SIGNAL(triggered()), this, SLOT(findText()));

    findNextAction = new QAction(this);
    addAction(findNextAction);
    findNextAction->setShortcut(QKeySequence::FindNext);
    findNextAction->setText(tr("Find Next"));
    findNextAction->setStatusTip(tr("Find next occurrence"));
    connect(findNextAction, SIGNAL(triggered()), this, SLOT(findNext()));

    findPreviousAction = new QAction(this);
    addAction(findPreviousAction);
    findPreviousAction->setShortcut(QKeySequence::FindPrevious);
    findPreviousAction->setText(tr("Find Previous"));
    findPreviousAction->setStatusTip(tr("Find previous occurrence"));
    connect(findPreviousAction, SIGNAL(triggered()), this, SLOT(findPrevious()));
}

findDialog::~findDialog() {}


void findDialog::init()
{
    ui.notFound->hide();
    raise();
    if (_editor->inherits("QPlainTextEdit"))
        ui.comboFind->setEditText(qobject_cast<QPlainTextEdit*>(_editor)->textCursor().selectedText().trimmed());
    else if (_editor->inherits("QTextEdit"))
        ui.comboFind->setEditText(qobject_cast<QTextEdit*>(_editor)->textCursor().selectedText().trimmed());
    ui.comboFind->setFocus();
}

void findDialog::setEditor(QPlainTextEdit* editor)
{
    _editor = editor;
}

void findDialog::setEditor(QTextEdit* editor)
{
    _editor = editor;
}

int findDialog::exec()
{
    if (!_editor)
        return (-1);
    init();
    return QDialog::exec();
}

void findDialog::show()
{
    if (!_editor)
        return;
    init();
    QDialog::show();
}

void findDialog::accept()
{
    if (ui.comboFind->currentText().isEmpty())
        return;
    if (_editor)
    {
        if (findText(ui.comboFind->currentText(), ui.radioForward->isChecked(), ui.checkCase->isChecked(),
                     ui.checkWords->isChecked()))
            QDialog::accept();
        else
            ui.notFound->show();
    }
}

void findDialog::findText()
{
    show();
}

bool findDialog::findText(const QString& pattern, bool do_forward, bool do_case_sensitive, bool do_whole_words)
{
    if (pattern.isEmpty())
        return false;
    m_find_pattern = pattern;
    m_find_case = do_case_sensitive;
    m_find_words = do_whole_words;

    QTextDocument* doc;
    QTextCursor c;
    if (_editor->inherits("QPlainTextEdit"))
    {
        QPlainTextEdit* ed = qobject_cast<QPlainTextEdit*>(_editor);
        doc = ed->document();
        c = ed->textCursor();
    }
    else if (_editor->inherits("QTextEdit"))
    {
        QTextEdit* ed = qobject_cast<QTextEdit*>(_editor);
        doc = ed->document();
        c = ed->textCursor();
    }
    else
        return false;
    QTextDocument::FindFlags options;

    if (c.hasSelection())
        c.setPosition(do_forward ? c.position() : c.anchor(), QTextCursor::MoveAnchor);
    if (!do_forward)
        options |= QTextDocument::FindBackward;
    if (m_find_case)
        options |= QTextDocument::FindCaseSensitively;
    if (m_find_words)
        options |= QTextDocument::FindWholeWords;
    QTextCursor newCursor(doc->find(m_find_pattern, c, options));
    bool found(true);
    if (newCursor.isNull())
    {
        QTextCursor ac(doc);
        ac.movePosition((options & QTextDocument::FindBackward) ? QTextCursor::End : QTextCursor::Start);
        newCursor = doc->find(m_find_pattern, ac, options);
        if (newCursor.isNull())
        {
            newCursor = c;
            found = false;
        }
    }
    if (!found)
        return false;
    if (_editor->inherits("QPlainTextEdit"))
    {
        QPlainTextEdit* ed = qobject_cast<QPlainTextEdit*>(_editor);
        ed->setTextCursor(newCursor);
        ed->verticalScrollBar()->setValue(ed->verticalScrollBar()->maximum());
        ed->centerCursor();
    }
    else if (_editor->inherits("QTextEdit"))
    {
        QTextEdit* ed = qobject_cast<QTextEdit*>(_editor);
        ed->setTextCursor(newCursor);
        ed->verticalScrollBar()->setValue(ed->verticalScrollBar()->maximum());
        ed->ensureCursorVisible();
        ed->verticalScrollBar()->setValue(ed->verticalScrollBar()->value() - ed->viewport()->height() / 3);
        ed->ensureCursorVisible();
    }
    return found;
}

void findDialog::findNext()
{
    if (m_find_pattern.isEmpty())
        findText();
    else
        findText(m_find_pattern, true, m_find_case, m_find_words);
}

void findDialog::findPrevious()
{
    if (m_find_pattern.isEmpty())
        findText();
    else
        findText(m_find_pattern, false, m_find_case, m_find_words);
}
