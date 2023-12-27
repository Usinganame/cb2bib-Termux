/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef ARXIVXML_H
#define ARXIVXML_H

#include "bibReference.h"

#include <QXmlStreamReader>


class arxivXml : public QXmlStreamReader
{

public:
    explicit arxivXml(const QString& xml);
    inline ~arxivXml() {}

    inline const bibReference& reference() const
    {
        return _reference;
    }


private:
    void readReference();

    bool reading(const QString& tag);
    void appendAuthor(QStringList* authors);
    void processDate();
    void processId();
    void readField(const QString& field);

    bibReference _reference;
};

#endif
