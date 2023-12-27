/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef CRJSON_H
#define CRJSON_H

#include "bibReference.h"


class crJson
{

public:
    explicit crJson(const QString& json);
    inline ~crJson() {}

    inline const bibReference& reference() const
    {
        return _reference;
    }
    inline bool hasError() const
    {
        return _has_error;
    }
    inline QString errorString() const
    {
        return _error_string;
    }


private:
    void readReference(const QString& json);

    static QString _bibtex_booktitle(const QStringList& titles);
    static QString _bibtex_series(const QStringList& titles);
    static QString _bibtex_title(const QStringList& titles, const QStringList& subtitles);
    static QString _normalize_jabstract(const QString& abstract);
    static int _words(const QString& s);
    static void _normalize_jtitles(QStringList* titles);

    QString _error_string;
    bibReference _reference;
    bool _has_error;
};

#endif
