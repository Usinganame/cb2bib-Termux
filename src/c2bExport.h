/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BEXPORT_H
#define C2BEXPORT_H

#include <QObject>
#include <QStringList>


class c2bExport : public QObject
{

    Q_OBJECT

public:
    explicit c2bExport(QObject* parento = 0);
    ~c2bExport();

    struct export_data
    {
        QString bibtex_contents;
        QString bibtex_fn;
        QString documents_dir;
        QString export_fn;
        QStringList bibtex_keys;
        bool copy_documents;
        bool relative_dir;
    };
    void exportEntries(const export_data& ed);
};

#endif
