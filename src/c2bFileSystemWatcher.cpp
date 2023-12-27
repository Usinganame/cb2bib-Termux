/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bFileSystemWatcher.h"

#include <QTimer>


/**
    Workaround to avoid reading a file when external writing has not yet finished
*/
c2bFileSystemWatcher::c2bFileSystemWatcher(QObject* parento) : QObject(parento)
{
    connect(&_filewatcher, SIGNAL(fileChanged(QString)), this, SLOT(waitForSaved(QString)));
}

void c2bFileSystemWatcher::waitForSaved(const QString& path)
{
    _path = path;
    QTimer::singleShot(500, this, SLOT(fileSaved()));
}

void c2bFileSystemWatcher::fileSaved()
{
    emit fileChanged(_path);
}
