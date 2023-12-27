/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BLINEEDIT_H
#define C2BLINEEDIT_H

#include <QLineEdit>


class c2bLineEdit : public QLineEdit
{

    Q_OBJECT

public:
    explicit c2bLineEdit(QWidget* parentw = 0);
    ~c2bLineEdit();

protected:
    virtual void contextMenuEvent(QContextMenuEvent* e);
};

#endif
