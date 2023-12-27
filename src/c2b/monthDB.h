/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef MONTHDB_H
#define MONTHDB_H

#include <QRegExp>
#include <QStringList>


/**
    Post processing of tag 'month'

    @author Pere Constans
*/
class monthDB
{

public:
    monthDB();
    inline ~monthDB() {}

    QString retrieve(const QString& month_query);


private:
    QRegExp _day_rx;
    QRegExp _month_rx;
    QString abbreviated(const QString& month) const;
    QString full(const QString& month) const;
    const QStringList _month_abbreviated;
    const QStringList _month_full;
};

#endif
