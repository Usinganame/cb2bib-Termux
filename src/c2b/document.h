/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QString>

/**
    This class converts documents to unicode strings
*/
class document
{

public:
    enum Conversion
    {
        FirstPage,
        Complete
    };

    document(const QString& fn, const Conversion mode);
    inline ~document() {}

    QString fileToString(const QString& fn);
    QString toString();
    void setConverter(const Conversion mode);

    inline QString errorString() const
    {
        return _error_string.trimmed();
    }
    inline QString logString() const
    {
        return _log_string.trimmed();
    }

    static QString& normalize(QString& doc, const Conversion mode);

private:
    Conversion _conversion_mode;
    QString _converter_arg;
    QString _converter_bin;
    QString _converter_output;
    QString _document_fn;
    QString _error_string;
    QString _log_string;
    void setConverter(const QString& bin, const QString& args);
};

#endif
