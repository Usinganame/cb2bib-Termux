/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef BOOKMARKPLUGIN_H
#define BOOKMARKPLUGIN_H

#include <QMenu>

class c2bFileSystemWatcher;


class bookmarkPlugin : public QMenu
{

    Q_OBJECT

public:
    explicit bookmarkPlugin(QWidget* parentw = 0);
    ~bookmarkPlugin();


signals:
    void editBookmarks();
    void openFile(const QString& fn);


private:
    c2bFileSystemWatcher* _fsw;
    QString _bookmark_file;
    QString iconProvider(const QString& fn, const QString& iconFile);


private slots:
    void init();
    void openBookmark();
    void parseBookmarks();
};

#endif
