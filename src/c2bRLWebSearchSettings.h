/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BRLWEBSEARCHSETTINGS_H
#define C2BRLWEBSEARCHSETTINGS_H

#include "ui_c2bRLWebSearchSettings.h"

#include <QDialog>


class c2bRLWebSearchSettings : public QDialog
{
    Q_OBJECT

public:
    explicit c2bRLWebSearchSettings(QWidget* parentw = 0);
    ~c2bRLWebSearchSettings();


private:
    Ui::c2bRLWebSearchSettings ui;


protected slots:
    void accept();
};

#endif
