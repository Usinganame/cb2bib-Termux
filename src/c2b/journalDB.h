/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef JOURNALDB_H
#define JOURNALDB_H

#include <QString>
#include <QStringList>
#include <QVarLengthArray>


/**
    Database of Journal Names

    @author Pere Constans
*/
class journalDB
{

public:
    explicit journalDB(const QString& dbfile);
    inline ~journalDB() {}

    QString retrieve(const QString& JQuery) const;
    QString retrieveAlternate(const QString& JQuery) const;
    QString retrieveAlternateFull(const QString& JQuery) const;
    QString retrieveFull(const QString& JQuery) const;

    inline int count() const
    {
        return _nitems;
    }
    inline const QString& retrieve(const int index) const
    {
        return JAbbrev.at(index);
    }
    inline const QString& retrieveFull(const int index) const
    {
        return JExtended.at(index);
    }
    inline const QString& fullsimplified(const int index) const
    {
        return JAbbrev_simp.at(index);
    }
    inline const QString& fullsimplifiedFull(const int index) const
    {
        return JExtended_simp.at(index);
    }
    inline const QStringList& abbreviatedList() const
    {
        return JAbbrev;
    }


private:
    QStringList JAbbrev;
    QStringList JCode;
    QStringList JExtended;
    QVarLengthArray<QString> JAbbrev_simp;
    QVarLengthArray<QString> JExtended_simp;
    int _nitems;
};

#endif
