/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bLineEdit.h"

#include <QAction>
#include <QContextMenuEvent>
#include <QMenu>


c2bLineEdit::c2bLineEdit(QWidget* parentw) : QLineEdit(parentw) {}

c2bLineEdit::~c2bLineEdit() {}


void c2bLineEdit::contextMenuEvent(QContextMenuEvent* e)
{
    QMenu* menu = QLineEdit::createStandardContextMenu();
    QList<QAction*> acts = menu->actions();
    QAction* act;
    act = new QAction("Clear", menu);
    act->setEnabled(!text().isEmpty());
    connect(act, SIGNAL(triggered()), this, SLOT(clear()));
    menu->insertAction(acts.at(7), act);
    acts = actions();
    for (int i = 0; i < acts.count(); ++i)
        menu->addAction(acts.at(i));
    menu->exec(e->globalPos());
    delete menu;
}
