/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BTEXTBROWSER_H
#define C2BTEXTBROWSER_H

#include <QTextBrowser>


class QAction;


/**
    @author Pere Constans
*/
class c2bTextBrowser : public QTextBrowser
{
    Q_OBJECT

public:
    explicit c2bTextBrowser(QWidget* parentw = 0);
    ~c2bTextBrowser();

    void updateHtml(const QString& newHtml);


public slots:
    virtual void setSource(const QUrl& name);


protected:
    virtual void contextMenuEvent(QContextMenuEvent* qevent);
};

#endif
