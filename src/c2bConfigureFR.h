/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BCONFIGUREFR_H
#define C2BCONFIGUREFR_H

#include "ui_c2bConfigureFR.h"

#include <QDialog>


class QTreeWidgetItem;


class c2bConfigureFR : public QDialog
{
    Q_OBJECT

public:
    explicit c2bConfigureFR(QTreeWidgetItem* item, QWidget* parentw = 0);
    ~c2bConfigureFR();


private:
    QTreeWidgetItem* itemFindReplace;
    Ui::c2bConfigureFR ui;


protected slots:
    void accept();
    void reject();
};

#endif
