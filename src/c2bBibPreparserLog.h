/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BBIBPREPARSERLOG_H
#define C2BBIBPREPARSERLOG_H

#include "ui_c2bLogWidget.h"

#include <QDialog>


class QCheckBox;


class c2bBibPreparserLog : public QDialog
{

    Q_OBJECT

public:
    explicit c2bBibPreparserLog(QWidget* parentw = 0);
    ~c2bBibPreparserLog();

    void append(const QString& ms);


public slots:
    void show();


protected slots:
    void help();


private:
    QCheckBox* PreparserShowLog;
    Ui::c2bLogWidget ui;
    void closeEvent(QCloseEvent* qevent);
};

#endif
