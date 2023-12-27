/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef PUBMEDXML_H
#define PUBMEDXML_H

#include "bibReference.h"

#include <QXmlStreamReader>


class pubmedXml : public QXmlStreamReader
{

public:
    explicit pubmedXml(const QString& xml);
    inline ~pubmedXml() {}

    inline const bibReference& reference() const
    {
        return _reference;
    }


private:
    bibReference _reference;
    bool reading(const QString& tag);
    void readAuthors();
    void readField(const QString& field);
    void readJournal();
    void readKeywords();
    void readReference();
};

#endif
