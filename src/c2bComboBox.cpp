/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bComboBox.h"

#include <QAction>
#include <QContextMenuEvent>
#include <QLineEdit>
#include <QMenu>


c2bComboBox::c2bComboBox(QWidget* parentw) : QComboBox(parentw) {}

c2bComboBox::~c2bComboBox() {}


void c2bComboBox::contextMenuEvent(QContextMenuEvent* e)
{
    QMenu* menu = QComboBox::lineEdit()->createStandardContextMenu();
    QList<QAction*> acts = menu->actions();
    QAction* act;
    act = new QAction("Clear", menu);
    act->setEnabled(!QComboBox::lineEdit()->text().isEmpty());
    connect(act, SIGNAL(triggered()), this, SLOT(clearEditText()));
    menu->insertAction(acts.at(7), act);
    acts = actions();
    for (int i = 0; i < acts.count(); ++i)
        menu->addAction(acts.at(i));
    menu->exec(e->globalPos());
    delete menu;
}
