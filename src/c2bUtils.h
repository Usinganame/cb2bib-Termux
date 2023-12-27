/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BUTILS_H
#define C2BUTILS_H

#include <cb2bib_utilities.h>

#include "dialog.h"

#include <QAction>
#include <QTextDocument>
#include <QUrl>

/**
    General cb2Bib Utils: GUI related utilities
*/
namespace c2bUtils
{

extern bool openFile(const QString& fn, QWidget* w = 0);

inline void displayHelp(const QString& url)
{
    openFile(url);
}

inline QUrl stringToUrl(const QString& fn)
{
    // Avoid cross-platform pitfalls regarding string to url conversions
    // Avoid possible issues regarding QUrl and local files not starting with 'file://'
    if (QFileInfo::exists(fn))
        return QUrl::fromLocalFile(fn);
    else
        return QUrl(fn, QUrl::TolerantMode);
}

inline QString fromHtmlString(const QString& str, const bool addMetadata = false)
{
    QTextDocument converter;
    converter.setHtml(str);
    if (addMetadata)
    {
        const QString md(converter.metaInformation(QTextDocument::DocumentTitle).trimmed());
        if (md.isEmpty())
            return converter.toPlainText();
        else
            return "Document Title: " + md + "\n\n" + converter.toPlainText();
    }
    else
        return converter.toPlainText();
}

inline void addSeparator(QWidget* w)
{
    // Adds separator to widget w
    QAction* action = new QAction(w);
    action->setSeparator(true);
    w->addAction(action);
}

inline void setWidgetOnTop(QWidget* w)
{
    if (w)
    {
        if (w->isHidden())
            w->show();
        if (w->isMinimized())
            w->showNormal();
        w->raise();
        w->activateWindow();
    }
}

} // namespace c2bUtils

#endif
