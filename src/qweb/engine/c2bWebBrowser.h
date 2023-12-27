/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BWEBBROWSER_H
#define C2BWEBBROWSER_H

#include <QMenu>
#include <QWebEngineView>


class c2bWebBrowser : public QWebEngineView
{

    Q_OBJECT

public:
    explicit c2bWebBrowser(QWidget* parentw = 0);
    virtual ~c2bWebBrowser();

    QAction* viewBackwardAction;
    QAction* viewForwardAction;
    QAction* viewHomeAction;
    QAction* viewReloadAction;
    QAction* viewZoomInAction;
    QAction* viewZoomOutAction;


signals:
    void statusMessage(const QString ms);


public slots:
    void loadPage(const QString& p_url);
    void setFixedFont(const QFont& qfont);
    void setFont(const QFont& qfont);
    void setHomePage(const QString& hp_url);


protected:
    virtual QWebEngineView* createWindow(QWebEnginePage::WebWindowType type);


protected slots:
    void copy();
    void home();
    void zoomIn();
    void zoomOut();


private:
    QString _home_page;
    QString _hovered_link;
    void showTitle(const QVariant& v);


private slots:
    void linkHovered(const QString& link);
};

#endif
