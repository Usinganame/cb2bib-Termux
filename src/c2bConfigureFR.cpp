/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bConfigureFR.h"

#include <QTreeWidgetItem>


c2bConfigureFR::c2bConfigureFR(QTreeWidgetItem* item, QWidget* parentw) : QDialog(parentw)
{
    ui.setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    itemFindReplace = item;
    ui.lineEditFind->setText(itemFindReplace->text(0));
    ui.lineEditReplace->setText(itemFindReplace->text(1));
    ui.lineEditDescription->setText(itemFindReplace->text(2));
    ui.lineEditFind->setFocus();
}

c2bConfigureFR::~c2bConfigureFR() {}


void c2bConfigureFR::reject()
{
    QDialog::reject();
}

void c2bConfigureFR::accept()
{
    itemFindReplace->setText(0, ui.lineEditFind->text());
    itemFindReplace->setText(1, ui.lineEditReplace->text());
    itemFindReplace->setText(2, ui.lineEditDescription->text());
    QDialog::accept();
}
