/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BCOLLECTIONINDEX_H
#define C2BCOLLECTIONINDEX_H

#include "ui_c2bLogWidget.h"

#include <QDialog>
#include <QProcess>


class c2bCollectionIndex : public QDialog
{

    Q_OBJECT

public:
    explicit c2bCollectionIndex(QWidget* parentw = 0);
    ~c2bCollectionIndex();

    void index();


private slots:
    void aborted();
    void addToLog();
    void help();
    void indexingEnded(int exit_code, QProcess::ExitStatus exit_status);
    void reject();


private:
    QProcess* _indexerP;
    QPushButton* _buttonAbort;
    Ui::c2bLogWidget ui;
    void closeEvent(QCloseEvent* qevent);
};

#endif
