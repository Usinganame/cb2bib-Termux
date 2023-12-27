/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BCOMBOBOX_H
#define C2BCOMBOBOX_H

#include <QComboBox>


class c2bComboBox : public QComboBox
{

    Q_OBJECT

public:
    explicit c2bComboBox(QWidget* parentw = 0);
    ~c2bComboBox();


protected:
    virtual void contextMenuEvent(QContextMenuEvent* e);
};

#endif
