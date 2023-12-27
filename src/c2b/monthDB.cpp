/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "monthDB.h"

#include "settings.h"


monthDB::monthDB()
    : _day_rx(QRegExp("(\\d+)")),
      _month_rx(QRegExp("([A-Za-z]+)")),
      _month_abbreviated(QString("jan|feb|mar|apr|may|jun|jul|aug|sep|oct|nov|dec").split('|')),
      _month_full(
          QString("January|February|March|April|May|June|July|August|September|October|November|December").split('|')) {}


QString monthDB::retrieve(const QString& month_query)
{
    bool has_month(_month_rx.indexIn(month_query) > -1);
    if (!has_month)
        return month_query;
    const QString month(_month_rx.cap(1));
    const QString month_abbreviated(abbreviated(month));
    const QString month_full(full(month));
    // Early return if month is not recognized
    if (month_abbreviated == month_full)
        return month_query;
    const bool has_day(_day_rx.indexIn(month_query) > -1);
    if (settings::instance()->value("cb2Bib/PostprocessMonth").toBool())
    {
        // Do '1 April' -> '"1~" # apr'
        if (has_day)
            return QString("\"%1~\" # %2").arg(_day_rx.cap(1), month_abbreviated);
        else
            return month_abbreviated;
    }
    else
    {
        // Capitalize
        if (has_day)
            return QString("%1 %2").arg(_day_rx.cap(1), month_full);
        else
            return month_full;
    }
}

QString monthDB::abbreviated(const QString& month) const
{
    for (int i = 0; i < 12; i++)
        if (QString::compare(month, _month_abbreviated.at(i), Qt::CaseInsensitive) == 0 ||
            QString::compare(month, _month_full.at(i), Qt::CaseInsensitive) == 0)
            return _month_abbreviated.at(i);
    return month;
}

QString monthDB::full(const QString& month) const
{
    for (int i = 0; i < 12; i++)
        if (QString::compare(month, _month_abbreviated.at(i), Qt::CaseInsensitive) == 0 ||
            QString::compare(month, _month_full.at(i), Qt::CaseInsensitive) == 0)
            return _month_full.at(i);
    return month;
}
