/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef METADATAPARSER_H
#define METADATAPARSER_H

#include <bibReference.h>

#include <QObject>

class coreBibParser;
class settings;


class metadataParser : public QObject
{

    Q_OBJECT

public:
    explicit metadataParser(QObject* parento = 0);
    explicit metadataParser(coreBibParser* cbp, QObject* parento = 0);
    inline ~metadataParser() {}

    bool insertMetadata(const bibReference& ref, const QString& fn, QString* error = 0,
                        const bool has_reference = false);
    bool metadata(const QString& fn, bibReference* ref);
    const QString metadata(const QString& fn);


signals:
    void showMessage(const QString& title, const QString& ms);


private:
    QHash<QString, QString> _bibtex_key;
    QRegExp _bibtex_fields;
    QRegExp _fields;
    bibReference _ref;
    bool _has_bibtex;
    bool _has_cb2bib;
    bool _has_prism;
    bool _metadata(const QString& fn);
    const QString _pdfDictionary(const QByteArray& rawpdf);
    coreBibParser* _cbpP;
    settings* _settingsP;
    void _fuzzyParser(const QString& data);
    void _metadataXmp(const QString& fn, const QByteArray& raw_contents, QStringList* xmls);
    void _metadataXmpExifTool(const QString& fn, QStringList* xmls);
    void _miscellaneousData(const QString& fn, const QByteArray& raw_contents);
    void init();

    inline QString formattedAuthor(const QString& author) const
    {
        const QStringList alist(author.split(" and ", QString::SkipEmptyParts));
        int na(alist.count());
        if (na <= 2)
            return author;
        QString formatted(alist.first());
        for (int i = 1; i < na - 1; ++i)
            formatted += ", " + alist.at(i);
        formatted += ", and " + alist.last();
        return formatted;
    }
};

#endif
