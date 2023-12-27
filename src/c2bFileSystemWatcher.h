/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BFILESYSTEMWATCHER_H
#define C2BFILESYSTEMWATCHER_H

#include <QFileSystemWatcher>


class c2bFileSystemWatcher : public QObject
{

    Q_OBJECT

public:
    explicit c2bFileSystemWatcher(QObject* parento = 0);
    inline ~c2bFileSystemWatcher() {}


    inline void addPath(const QString& path)
    {
        _filewatcher.addPath(path);
    }
    inline void removePath(const QString& path)
    {
        _filewatcher.removePath(path);
    }


signals:
    void fileChanged(const QString& path);


private slots:
    void fileSaved();
    void waitForSaved(const QString& path);


private:
    QFileSystemWatcher _filewatcher;
    QString _path;
};

#endif
