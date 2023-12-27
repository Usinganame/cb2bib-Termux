/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 *   findDialog is adapted from Qt Designer
 *   Copyright (C) 2001 Trolltech AS.  All rights reserved.
 ***************************************************************************/
#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include "ui_findDialog.h"

#include <QDialog>
#include <QPointer>


class QAction;
class QPlainTextEdit;
class QTextEdit;


class findDialog : public QDialog
{

    Q_OBJECT

public:
    explicit findDialog(QWidget* parentw = 0);
    ~findDialog();

    QAction* findAction;
    QAction* findNextAction;
    QAction* findPreviousAction;


public slots:
    int exec();
    void findNext();
    void findPrevious();
    void findText();
    void setEditor(QPlainTextEdit* editor);
    void setEditor(QTextEdit* editor);
    void show();


private slots:
    void accept();


private:
    QPointer<QWidget> _editor;
    QString m_find_pattern;
    Ui::findDialog ui;
    bool findText(const QString& pattern, bool do_forward = true, bool do_case_sensitive = false,
                  bool do_whole_words = false);
    bool m_find_case;
    bool m_find_words;
    void init();
};

#endif
