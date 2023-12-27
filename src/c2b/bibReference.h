/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef BIBREFERENCE_H
#define BIBREFERENCE_H

#include "cb2bib_utilities.h"

#include <QHash>

typedef QHash<QString, QString>::const_iterator bibReferenceIterator;


/**
    Basic class for a bibliographic reference

    @author Pere Constans
*/
class bibReference : public QHash<QString, QString>
{

public:
    inline bibReference() : positionValue(0), pos(0) {}

    void clearFields()
    {
        pos = 0;
    }
    void clearReference()
    {
        positionValue = 0;
        citeidName.clear();
        typeName.clear();
        rawReference.clear();
        unicodeReference.clear();
        QHash<QString, QString>::clear();
    }
    /**
        Fallback for authors
    */
    inline const QString anyAuthor() const
    {
        const QString v(value("author"));
        if (v.isEmpty())
            return value("editor");
        return v;
    }
    /**
        Fallback for titles
    */
    inline const QString anyTitle() const
    {
        const QString v(value("title"));
        if (v.isEmpty())
        {
            const QString v1(value("booktitle"));
            if (v1.isEmpty())
                return QFileInfo(value("file")).fileName();
            return v1;
        }
        return v;
    }
    /**
        Fallback for journal
    */
    inline const QString anyJournal() const
    {
        QString v(value("journal"));
        if (v.isEmpty())
            if (typeName == "inproceedings")
            {
                v = value("booktitle");
                c2bUtils::cleanTitle(v, true);
            }
        return v;
    }
    QString citeidName;
    QString rawReference;
    QString typeName;
    QString unicodeReference;
    int positionValue;


private:
    int pos;

    friend class coreBibParser;
};

#endif
