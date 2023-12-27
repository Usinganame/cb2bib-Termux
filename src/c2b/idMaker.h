/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 *
 *   Improvements and modifications:
 *   July 2009 - Added <<author_all_abbreviated>>, (C) 2009 by Dayu Huang
 ***************************************************************************/
#ifndef IDMAKER_H
#define IDMAKER_H

#include "bibReference.h"

#include <QObject>


/**
    @author Pere Constans
*/
class idMaker : public QObject
{

    Q_OBJECT

public:
    explicit idMaker(const QString& patternKey, QObject* parento = 0);
    inline ~idMaker() {}

    QString makeID(const bibReference& reference);


private:
    QString _author;
    QString _id_pattern;
    QString _journal;
    QString _pages;
    QString _title;
    QString _title_pattern;
    QString _volume;
    QString _year;
    bool _is_title_underscored;
    const QString _pattern_key;
    int _title_max_length;
    void make_author_all_abbreviated(QString* id);
    void make_author_all_initials(QString* id);
    void make_author_first(QString* id);
    void make_author_first_lowercase(QString* id);
    void make_journal_initials(QString* id);
    void make_pages_first(QString* id);
    void make_ppages_first(QString* id);
    void make_title(QString* id);
    void make_title_first_word(QString* id);
    void make_volume(QString* id);
    void make_year_abbreviated(QString* id);
    void make_year_full(QString* id);


private slots:
    void loadSettings();
};

#endif
