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

#include <QWebEngineSettings>


c2bWebBrowser::c2bWebBrowser(QWidget* parentw) : QWebEngineView(parentw)
{
// Set default background to application
#if QT_VERSION >= QT_VERSION_CHECK(5, 6, 0)
    page()->setBackgroundColor(qApp->palette().color(QPalette::Window));
#endif

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
    connect(page(), SIGNAL(linkHovered(QString)), this, SLOT(linkHovered(QString)));

    connect(this, SIGNAL(titleChanged(QString)), this, SLOT(setWindowTitle(QString)));
}

c2bWebBrowser::~c2bWebBrowser() {}


void c2bWebBrowser::setHomePage(const QString& hp_url)
{
    _home_page = hp_url;
    home();
}

void c2bWebBrowser::setFont(const QFont& qfont)
{
    QWebEngineSettings* wsettings = settings();
    wsettings->setFontFamily(QWebEngineSettings::StandardFont, qfont.family());
    wsettings->setFontSize(QWebEngineSettings::DefaultFontSize, qfont.pointSize());
}

void c2bWebBrowser::setFixedFont(const QFont& qfont)
{
    QWebEngineSettings* wsettings = settings();
    wsettings->setFontFamily(QWebEngineSettings::FixedFont, qfont.family());
    wsettings->setFontSize(QWebEngineSettings::DefaultFixedFontSize, qfont.pointSize());
}

void c2bWebBrowser::copy()
{
    page()->triggerAction(QWebEnginePage::Copy);
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
    setZoomFactor(zoomFactor() + 0.1);
}

void c2bWebBrowser::zoomOut()
{
    setZoomFactor(zoomFactor() - 0.1);
}

QWebEngineView* c2bWebBrowser::createWindow(QWebEnginePage::WebWindowType /* type */)
{
    if (!_hovered_link.isEmpty())
        c2bUtils::openFile(_hovered_link, this);
    return 0;
}

template <typename Arg, typename R, typename C>
struct InvokeWrapper
{
    R* receiver;
    void (C::*memberFun)(Arg);
    void operator()(Arg result)
    {
        (receiver->*memberFun)(result);
    }
};

template <typename Arg, typename R, typename C>
InvokeWrapper<Arg, R, C> invoke(R* receiver, void (C::*memberFun)(Arg))
{
    InvokeWrapper<Arg, R, C> wrapper = { receiver, memberFun };
    return wrapper;
}

void c2bWebBrowser::showTitle(const QVariant& v)
{
    if (!v.isValid())
        emit statusMessage(QString());
    else
        emit statusMessage(v.toString());
}

void c2bWebBrowser::linkHovered(const QString& link)
{
    _hovered_link = link;
    if (_hovered_link.isEmpty())
        emit statusMessage(QString());
    else if (_hovered_link.contains(".tex.html#"))
    {
        const QString q(QFileInfo(link).fileName().split('#').last());
        page()->runJavaScript("document.querySelector('a[id*=\"" + q + "\"]').text",
                              invoke(this, &c2bWebBrowser::showTitle));
    }
    else
    {
        QString vlink(link);
        emit statusMessage(vlink.remove("file://"));
    }
}
