/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bTextBrowser.h"

#include <QAction>
#include <QContextMenuEvent>
#include <QMenu>
#include <QScrollBar>


c2bTextBrowser::c2bTextBrowser(QWidget* parentw) : QTextBrowser(parentw)
{
    setFrameShape(QTextBrowser::StyledPanel);
    setFrameShadow(QTextBrowser::Raised);
}

c2bTextBrowser::~c2bTextBrowser() {}


void c2bTextBrowser::setSource(const QUrl& /* dummy_name */) {}

void c2bTextBrowser::contextMenuEvent(QContextMenuEvent* qevent)
{
    QMenu* edit_menu = createStandardContextMenu();
    edit_menu->setTitle(tr("Edit..."));
    QMenu* menu = new QMenu(this);
    menu->addMenu(edit_menu);
    QList<QAction*> acts = actions();
    for (int i = 0; i < acts.count(); ++i)
        menu->addAction(acts.at(i));
    menu->exec(qevent->globalPos());
    delete edit_menu;
    delete menu;
}

void c2bTextBrowser::updateHtml(const QString& newHtml)
{
    const int scrollPosition(verticalScrollBar()->value());
    setHtml(newHtml);
    verticalScrollBar()->setValue(scrollPosition);
}
