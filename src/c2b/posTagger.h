/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef POSTAGGER_H
#define POSTAGGER_H

#include <QHash>
#include <QString>

class posTagger
{

public:
    posTagger();
    inline ~posTagger() {}

    QString ruletag(const QString& word) const;
    QString tagged(const QString& text) const;
    bool loadLexicon();
    inline bool contains(const QString& sentence) const
    {
        return _sentence_patterns.contains(sentence);
    }


private:
    const QChar _period;
    const QChar _space;
    const QString _pos_a;
    const QString _pos_g;
    const QString _pos_n;
    const QString _pos_o;
    const QString _pos_r;
    const QString _pos_s;
    const QString _suffix_able;
    const QString _suffix_ae;
    const QString _suffix_al;
    const QString _suffix_apostrophes;
    const QString _suffix_ar;
    const QString _suffix_ed;
    const QString _suffix_ful;
    const QString _suffix_ic;
    const QString _suffix_ics;
    const QString _suffix_ing;
    const QString _suffix_is;
    const QString _suffix_ive;
    const QString _suffix_lent;
    const QString _suffix_less;
    const QString _suffix_like;
    const QString _suffix_ly;
    const QString _suffix_ous;
    const QString _suffix_s;
    const QString _suffix_ss;
    const QString _suffix_us;

    QHash<QString, QString> _lexicon;
    QHash<QString, QString> _sentence_patterns;
};

#endif
