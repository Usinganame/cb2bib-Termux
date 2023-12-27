/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef DOCUMENTCACHE_H
#define DOCUMENTCACHE_H

#include "documentContents.h"

#include <QHash>


class settings;

class documentCache
{

public:
    documentCache();
    ~documentCache();

    bool setCurrent(const QString& fn);
    bool setCurrent(const QString& fn, int* pdfCounter, QString* logString, int* errorCounter);
    void load(const QString& fn, const documentContents::Type type);
    void unload();

    inline const documentContents& current() const
    {
        return _current;
    }

    inline const QHash<QString, QByteArray>& cacheData() const
    {
        return _cache;
    }


private:
    QHash<QString, QByteArray> _cache;
    QString _cache_filename;
    QString _load_filename;
    documentContents _current;
    documentContents::Type _content_type;
    int _cache_load_size;
    settings* _settingsP;
    void save();
};

#endif
