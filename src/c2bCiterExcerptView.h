/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BCITEREXCERPTVIEW_H
#define C2BCITEREXCERPTVIEW_H


#include <QDialog>


class c2bTextBrowser;


class c2bCiterExcerptView : public QDialog
{

    Q_OBJECT

public:
    explicit c2bCiterExcerptView(const QString& html, QWidget* parentw = 0);
    ~c2bCiterExcerptView();


private:
    c2bTextBrowser* _browserP;
};

#endif
