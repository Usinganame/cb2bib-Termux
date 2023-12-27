/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef HEURISTICBIBPARSER_H
#define HEURISTICBIBPARSER_H

#include "authorString.h"
#include "bibReference.h"


class bibParser;
class journalDB;


/**
    bibParser helper class for heuristic recognition

    @author Pere Constans
*/
class heuristicBibParser
{

public:
    explicit heuristicBibParser(bibParser* bp);
    ~heuristicBibParser();

    void guessFields(const QString& clean_text, const QString& tagged_text);
    void heuristicFields(const QString& text);


private:
    QRegExp* _author_b2_lc_rx;
    QRegExp* _author_b2_uc_rx;
    QRegExp* _author_b3_lc_rx;
    QRegExp* _author_b3_uc_rx;
    QRegExp* _author_b4_lc_rx;
    QRegExp* _author_b4_uc_rx;
    QRegExp* _author_b5_lc_rx;
    QRegExp* _author_b5_uc_rx;
    QRegExp _author_sb;
    QRegExp _author_sb_lc;
    QRegExp _author_sb_uc;
    QRegExp _hyphens;
    QRegExp _leading_non_letters;
    QString _hyphen_nums;
    QString _hyphen_pages;
    QString guessAuthor_multi_block();
    QString guessAuthor_single_block();
    QStringList _word_prefix_lexicon;
    author::encoder _aencoder;
    bibParser* _bpP;
    bibReference& _current_reference;
    bool _reliable_number;
    bool _reliable_pages;
    bool _reliable_volume;
    const QString _abstract;
    const QString _addauthors;
    const QString _author;
    const QString _isbn;
    const QString _keywords;
    const QString _number;
    const QString _pages;
    const QString _title;
    const QString _volume;
    const QString _year;
    const QStringList& _bibliographic_fields;
    const journalDB& _journal_db;
    int _max_year;
    static int authorCount(const QString& authors);
    void guessAbstract(const QString& text);
    void guessAuthor(const QString& tagged_text);
    void guessFromMetadata(const QString& text);
    void guessISBN(const QString& text);
    void guessJournal(const QString& text);
    void guessKeywords(const QString& text);
    void guessNumber(const QString& text);
    void guessPages(const QString& text);
    void guessTitle(const QString& text);
    void guessVolume(const QString& text);
    void guessVolumePagesYear(const QString& text);
    void guessVolumeYearPages(const QString& text);
    void guessYear(const QString& text);
    void guessYearVolumePages(const QString& text);

    inline void _debug_guess(const QString&
#ifdef C2B_DEBUG_HEURISTICBIBPARSER
                             procedure
#endif
                            ) const
    {
#ifdef C2B_DEBUG_HEURISTICBIBPARSER
        qDebug() << "[cb2bib] " << procedure;
        for (int i = 0; i < _bibliographic_fields.count(); ++i)
        {
            if (!_current_reference.value(_bibliographic_fields.at(i)).isEmpty())
                qDebug() << QString("    %1:  '%2'")
                         .arg(_bibliographic_fields.at(i))
                         .arg(_current_reference.value(_bibliographic_fields.at(i)));
        }
#endif
    }
};

#endif
