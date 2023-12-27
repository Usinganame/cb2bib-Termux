/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bWebBrowser.h"

#include "c2bUtils.h"

#include <QApplication>
#include <QClipboard>
#include <QContextMenuEvent>
#include <QShortcut>
#include <QTimer>

#include <QWebFrame>


c2bWebBrowser::c2bWebBrowser(QWidget* parentw) : QWebView(parentw)
{
    // Avoid flickering (Qt 4.3)
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_OpaquePaintEvent, true);

    // Set default background to application
    page()->setPalette(qApp->palette());

    // Actions
    setContextMenuPolicy(Qt::ActionsContextMenu);
    viewBackwardAction = new QAction(QIcon(QString::fromUtf8(":/icons/icons/viewBackward.png")), tr("Backward"), this);
    viewBackwardAction->setShortcut(QKeySequence("Left"));
    viewBackwardAction->setStatusTip(tr("Backward"));
    addAction(viewBackwardAction);
    viewForwardAction = new QAction(QIcon(QString::fromUtf8(":/icons/icons/viewForward.png")), tr("Forward"), this);
    viewForwardAction->setShortcut(QKeySequence("Right"));
    viewForwardAction->setStatusTip(tr("Forward"));
    addAction(viewForwardAction);
    c2bUtils::addSeparator(this);
    viewHomeAction = new QAction(QIcon(QString::fromUtf8(":/icons/icons/viewHome.png")), tr("Home"), this);
    viewHomeAction->setShortcut(QKeySequence("Esc"));
    viewHomeAction->setStatusTip(tr("Home page"));
    addAction(viewHomeAction);
    c2bUtils::addSeparator(this);
    viewReloadAction = new QAction(QIcon(QString::fromUtf8(":/icons/icons/viewReload.png")), tr("Reload"), this);
    viewReloadAction->setShortcut(QKeySequence("R"));
    viewReloadAction->setStatusTip(tr("Reload current page"));
    addAction(viewReloadAction);
    c2bUtils::addSeparator(this);
    viewZoomInAction = new QAction(QIcon(QString::fromUtf8(":/icons/icons/viewZoomIn.png")), tr("Zoom In"), this);
    viewZoomInAction->setShortcut(QKeySequence(QKeySequence::ZoomIn));
    viewZoomInAction->setStatusTip(tr("Zoom in"));
    addAction(viewZoomInAction);
    viewZoomOutAction = new QAction(QIcon(QString::fromUtf8(":/icons/icons/viewZoomOut.png")), tr("Zoom Out"), this);
    viewZoomOutAction->setShortcut(QKeySequence(QKeySequence::ZoomOut));
    viewZoomOutAction->setStatusTip(tr("Zoom out"));
    addAction(viewZoomOutAction);

    connect(viewForwardAction, SIGNAL(triggered()), this, SLOT(forward()));
    connect(viewBackwardAction, SIGNAL(triggered()), this, SLOT(back()));
    connect(viewHomeAction, SIGNAL(triggered()), this, SLOT(home()));
    connect(viewReloadAction, SIGNAL(triggered()), this, SLOT(reload()));
    connect(viewZoomInAction, SIGNAL(triggered()), this, SLOT(zoomIn()));
    connect(viewZoomOutAction, SIGNAL(triggered()), this, SLOT(zoomOut()));

    QShortcut* copy_shortcut = new QShortcut(QKeySequence(QKeySequence::Copy), this);
    connect(copy_shortcut, SIGNAL(activated()), this, SLOT(copy()));
    connect(page(), SIGNAL(linkHovered(QString,QString,QString)), this, SLOT(linkHovered(QString)));
    connect(page(), SIGNAL(statusBarMessage(QString)), this, SIGNAL(statusMessage(QString)));

    connect(this, SIGNAL(titleChanged(QString)), this, SLOT(_set_window_title(QString)));
}

c2bWebBrowser::~c2bWebBrowser() {}


void c2bWebBrowser::setHomePage(const QString& hp_url)
{
    _home_page = hp_url;
    home();
}

void c2bWebBrowser::setFont(const QFont& qfont)
{
    QWebSettings* wsettings = settings();
    wsettings->setFontFamily(QWebSettings::StandardFont, qfont.family());
    wsettings->setFontSize(QWebSettings::DefaultFontSize, qfont.pointSize());
}

void c2bWebBrowser::setFixedFont(const QFont& qfont)
{
    QWebSettings* wsettings = settings();
    wsettings->setFontFamily(QWebSettings::FixedFont, qfont.family());
    wsettings->setFontSize(QWebSettings::DefaultFixedFontSize, qfont.pointSize());
}

void c2bWebBrowser::copy()
{
    page()->triggerAction(QWebPage::Copy);
}

void c2bWebBrowser::home()
{
    if (!_home_page.isEmpty())
        load(c2bUtils::stringToUrl(_home_page));
}

void c2bWebBrowser::loadPage(const QString& p_url)
{
    if (!p_url.isEmpty())
        load(c2bUtils::stringToUrl(p_url));
}

void c2bWebBrowser::zoomIn()
{
    setTextSizeMultiplier(textSizeMultiplier() + 0.1);
}

void c2bWebBrowser::zoomOut()
{
    setTextSizeMultiplier(textSizeMultiplier() - 0.1);
}

QWebView* c2bWebBrowser::createWindow(QWebPage::WebWindowType /* type */)
{
    if (!_hovered_link.isEmpty())
        c2bUtils::openFile(_hovered_link, this);
    return 0;
}

void c2bWebBrowser::mousePressEvent(QMouseEvent* qevent)
{
    if (qevent->button() == Qt::BackButton)
    {
        back();
        qevent->accept();
    }
    QWebView::mousePressEvent(qevent);
}

void c2bWebBrowser::_set_window_title(const QString& pagetitle)
{
    // This fixes anchor clicked cases where titleChanged signal emits an empty document title
    if (!pagetitle.isEmpty())
        setWindowTitle(pagetitle);
}

void c2bWebBrowser::linkHovered(const QString& link)
{
    _hovered_link = link;
    if (_hovered_link.isEmpty())
        emit statusMessage(QString());
    else if (_hovered_link.contains(".tex.html#"))
    {
        const QString q(QFileInfo(link).fileName().split('#').last());
        const QVariant v(
            page()->mainFrame()->evaluateJavaScript("document.querySelector('a[id*=\"" + q + "\"]').text"));
        if (!v.isValid())
            emit statusMessage(QString());
        else
            emit statusMessage(v.toString());
    }
    else
    {
        QString vlink(link);
        emit statusMessage(vlink.remove("file://"));
    }
}
