/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BNETWORKQUERYINFO_H
#define C2BNETWORKQUERYINFO_H

#include <QObject>
#include <QStringList>

class QAction;
class c2bBibParser;
class c2bFileSystemWatcher;


/**
    Manage Network Query Information
*/
class c2bNetworkQueryInfo : public QObject
{

    Q_OBJECT

public:
    explicit c2bNetworkQueryInfo(QObject* parento = 0);
    ~c2bNetworkQueryInfo();

    QList<QAction*> bookmarkActions(const QString& selection);
    const QString bookmarksToHtml() const;
    const QString encodeLink(const QString& ln) const;


private:
    QList<QAction*> BookmarkActionList;
    QString NetworkFile;
    QString _current_selection;
    QStringList BookmarkList;
    c2bFileSystemWatcher* _fsw;
    const c2bBibParser* _bpP;


private slots:
    void loadSettings();
    void openBookmark();
    void parseBookmarks();
};

#endif
