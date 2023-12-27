/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "bookmarkPlugin.h"

#include "c2b.h"
#include "c2bFileSystemWatcher.h"
#include "c2bSettings.h"
#include "c2bUtils.h"

#include <QtGui>


bookmarkPlugin::bookmarkPlugin(QWidget* parentw) : QMenu(parentw)
{
    setObjectName(QString::fromUtf8("menuBookmarks"));
    setTitle(QApplication::translate("c2bEditor", "&Bookmarks", 0));
    connect(c2bSettingsP, SIGNAL(newSettings()), this, SLOT(init()));
    _fsw = new c2bFileSystemWatcher(this);
    connect(_fsw, SIGNAL(fileChanged(QString)), this, SLOT(parseBookmarks()));
    init();
}

bookmarkPlugin::~bookmarkPlugin() {}


void bookmarkPlugin::init()
{
    const QString nfn(c2bSettingsP->fileName("cb2Bib/NetworkFile"));
    if (nfn == _bookmark_file)
        return;
    if (QFileInfo::exists(nfn))
    {
        if (!_bookmark_file.isEmpty())
            _fsw->removePath(_bookmark_file);
        _bookmark_file = nfn;
        _fsw->addPath(_bookmark_file);
    }
    parseBookmarks();
}

void bookmarkPlugin::parseBookmarks()
{
    clear();
    const QString bmf(c2bUtils::fileToString(_bookmark_file));
    QStringList bookmarks(bmf.split(QRegExp("[\\r\\n]"), QString::KeepEmptyParts));
    const QRegExp _bookmark("^editorbookmark=");
    const QRegExp _separator("^editorbookmark=\\s*$");
    for (int i = 0; i < bookmarks.count(); ++i)
    {
        if (bookmarks.at(i).contains(_separator))
        {
            addSeparator();
            continue;
        }
        if (bookmarks.at(i).contains(_bookmark))
        {
            bookmarks[i].remove(_bookmark);
            const QStringList bm_parts(bookmarks.at(i).split('|', QString::KeepEmptyParts));
            if (bm_parts.count() != 4)
            {
                c2bUtils::warn(tr("bookmarkPlugin::parseBookmarks: Syntax error at '%1'").arg(bookmarks.at(i)));
                continue;
            }
            QAction* act = addAction(bm_parts.at(0), this, SLOT(openBookmark()));
            act->setData(bm_parts.at(1));
            act->setStatusTip(QString("%1  [%2]").arg(bm_parts.at(0), bm_parts.at(1)));
            act->setShortcut(bm_parts.at(2));
            act->setIcon(QIcon(iconProvider(bm_parts.at(1), bm_parts.at(3))));
        }
    }
    addSeparator();
    QAction* edit_bookmarks = addAction(tr("Edit Bookmarks"), this, SIGNAL(editBookmarks()));
    edit_bookmarks->setStatusTip(tr("Edit bookmarks"));
    edit_bookmarks->setIcon(QIcon(":/icons/icons/edit.png"));
}

QString bookmarkPlugin::iconProvider(const QString& fn, const QString& iconFile)
{
    if (!iconFile.isEmpty())
        return iconFile;
    if (fn.contains(QRegExp("\\.(tex|dvi)\\b", Qt::CaseInsensitive)))
        return ":/icons/icons/application-x-tex.png";
    if (fn.contains(QRegExp("\\.(chm|djvu|pdf|ps)\\b", Qt::CaseInsensitive)))
        return ":/icons/icons/application-x-pdf.png";
    if (fn.contains(QRegExp("\\.(htm|html|php)\\b", Qt::CaseInsensitive)))
        return ":/icons/icons/application-x-html.png";
    if (fn.contains(QRegExp("\\.txt\\b", Qt::CaseInsensitive)))
        return ":/icons/icons/application-x-tex.png";
    if (fn.contains(QRegExp("\\.bib\\b", Qt::CaseInsensitive)))
        return ":/icons/icons/cb2bib.png";
    return ":/icons/icons/application-x-none.png";
}

void bookmarkPlugin::openBookmark()
{
    QAction* act = static_cast<QAction*>(sender());
    if (act)
    {
        const QString fn(act->data().toString());
        if (fn.endsWith(".bib")) // Open BiBTeX files internally
            emit openFile(fn);
        else
            c2bUtils::openFile(fn, parentWidget());
    }
}
