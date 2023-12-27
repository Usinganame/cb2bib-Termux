/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef STEMMER_H
#define STEMMER_H

#include <QRegExp>
#include <QString>


struct stemmer
{
    stemmer()
        : digits("\\d"),
          suffix_1_letter("(:?a|e|f|i|o|r|s|t|x|y)$", Qt::CaseInsensitive),
          suffix_2_letter("(:?as|ce|er|es|fs|ic|id|ie|is|on|os|se|sm|st|um|us|ys)$", Qt::CaseInsensitive),
          suffix_2_letter_inflected("(:?ed|en|er)$", Qt::CaseInsensitive),
          suffix_2_letter_length_5("(:?ed|er)$", Qt::CaseInsensitive),
          suffix_3_letter("(:?ers|ics|ies|ion|ish|ism|ist|ium|oes|ons|ora|sms|sts|ums|ves|xes)$", Qt::CaseInsensitive),
          suffix_3_letter_length_7("(:?ers|ies|ish|ora|sms|ums|ves|xes)$", Qt::CaseInsensitive),
          suffix_4_letter("(:?ical|ions|isms|ists)$", Qt::CaseInsensitive),
          suffix_double_esses("(:?sses|ssis|ssus)$", Qt::CaseInsensitive),
          suffix_isz("(:?ise|ised|iser|isers|ises|ising|isis|ize|ized|izer|izers|izes|izing)$", Qt::CaseInsensitive),
          suffix_man("(:?man|men)$", Qt::CaseInsensitive),
          suffix_misc("(:?mme|mmes|lty|lties|lity|lities)$", Qt::CaseInsensitive),
          suffix_ogues("(:?ogue|ogues)$", Qt::CaseInsensitive),
          suffix_ours("(:?or|ors|our|ours)$", Qt::CaseInsensitive),
          suffix_reer("(:?tre|tres|bre|bres)$", Qt::CaseInsensitive),
          suffix_sz("(:?isation|ization|ysation|yzation|isations|izations|ysations|yzations)$", Qt::CaseInsensitive),
          suffix_ysz("(:?yse|ysed|yser|ysers|yses|ysing|ysis|yze|yzed|yzer|yzers|yzes|yzing)$", Qt::CaseInsensitive)
    {
        dictionary.insert("alpha", QChar(913));
        dictionary.insert("beta", QChar(914));
        dictionary.insert("gamma", QChar(915));
        dictionary.insert("delta", QChar(916));
        dictionary.insert("epsilon", QChar(917));
        dictionary.insert("zeta", QChar(918));
        dictionary.insert("eta", QChar(919));
        dictionary.insert("theta", QChar(920));
        dictionary.insert("iota", QChar(921));
        dictionary.insert("kappa", QChar(922));
        dictionary.insert("lambda", QChar(923));
        dictionary.insert("mu", QChar(924));
        dictionary.insert("nu", QChar(925));
        dictionary.insert("xi", QChar(926));
        dictionary.insert("omicron", QChar(927));
        dictionary.insert("pi", QChar(928));
        dictionary.insert("rho", QChar(929));
        dictionary.insert("sigma", QChar(931));
        dictionary.insert("tau", QChar(932));
        dictionary.insert("upsilon", QChar(933));
        dictionary.insert("phi", QChar(934));
        dictionary.insert("chi", QChar(935));
        dictionary.insert("psi", QChar(936));
        dictionary.insert("omega", QChar(937));

        dictionary.insert("axes", "axis");
        dictionary.insert("axis", "axes");
        dictionary.insert("bases", "basis");
        dictionary.insert("basis", "bases");
        dictionary.insert("data", "datum");
        dictionary.insert("datum", "data");
        dictionary.insert("liked", "like");

        dictionary.insert("infinity", QChar(8734));
    }

    QString stem(const QString& word) const
    {
        const Qt::CaseSensitivity ci(Qt::CaseInsensitive);
        const int nl(word.length());
        if (nl < 4)
            return word;

        if (digits.indexIn(word) >= 0)
            return word;

        if (nl == 4)
        {
            if (word.endsWith(QLatin1Char('s'), ci))
                return word.left(3);
            return word;
        }

        if (suffix_man.indexIn(word) >= 0)
            return word.left(nl - 2);
        if (suffix_reer.indexIn(word) >= 0)
            return word.left(nl - suffix_reer.matchedLength() + 1);

        if (nl == 5)
        {
            if (suffix_2_letter_length_5.indexIn(word) >= 0)
                return word.left(3);
            if (suffix_1_letter.indexIn(word) >= 0)
                return word.left(4);
            return word;
        }

        if (suffix_isz.indexIn(word) >= 0)
            return word.left(nl - suffix_isz.matchedLength() + 1);
        if (suffix_ysz.indexIn(word) >= 0)
            return word.left(nl - suffix_ysz.matchedLength() + 1);
        if (suffix_2_letter_inflected.indexIn(word) >= 0)
            return word.at(nl - 3) == word.at(nl - 4) || word.at(nl - 3).toLower() == QLatin1Char('i')
                   ? word.left(nl - 3)
                   : word.left(nl - 2);
        if (suffix_ours.indexIn(word) >= 0)
            return word.left(nl - suffix_ours.matchedLength() + 1);
        if (suffix_misc.indexIn(word) >= 0)
            return word.left(nl - suffix_misc.matchedLength() + 1);

        if (nl == 6)
        {
            if (word.endsWith(QLatin1String("ing"), ci))
                return word.left(3);
            if (suffix_2_letter.indexIn(word) >= 0)
                return word.left(4);
            if (suffix_1_letter.indexIn(word) >= 0)
                return word.left(5);
            return word;
        }

        if (word.endsWith(QLatin1String("est"), ci))
            return word.at(nl - 4) == word.at(nl - 5) || word.at(nl - 4).toLower() == QLatin1Char('i')
                   ? word.left(nl - 4)
                   : word.left(nl - 3);
        if (word.endsWith(QLatin1String("ing"), ci))
            return word.at(nl - 4) == word.at(nl - 5) || word.at(nl - 4).toLower() == QLatin1Char('y')
                   ? word.left(nl - 4)
                   : word.left(nl - 3);
        if (word.endsWith(QLatin1String("ices"), ci))
            return word.left(nl - 3);
        if (word.endsWith(QLatin1String("uses"), ci))
            return word.at(nl - 5).toLower() == QLatin1Char('f') ? word.left(nl - 2) : word.left(nl - 4);
        if (suffix_ogues.indexIn(word) >= 0)
            return word.left(nl - suffix_ogues.matchedLength() + 2);

        if (nl == 7)
        {
            if (suffix_3_letter_length_7.indexIn(word) >= 0)
                return word.left(4);
            if (suffix_2_letter.indexIn(word) >= 0)
                return word.left(5);
            if (suffix_1_letter.indexIn(word) >= 0)
                return word.left(6);
            return word;
        }

        if (word.endsWith(QLatin1String("ings"), ci))
            return word.at(nl - 5) == word.at(nl - 6) || word.at(nl - 5).toLower() == QLatin1Char('y')
                   ? word.left(nl - 5)
                   : word.left(nl - 4);

        if (nl > 9 && suffix_sz.indexIn(word) >= 0)
            return word.left(nl - suffix_sz.matchedLength() + 1);
        if (nl > 8 && suffix_4_letter.indexIn(word) >= 0)
            return word.left(nl - 4);

        if (suffix_3_letter.indexIn(word) >= 0)
            return word.left(nl - 3);
        if (suffix_double_esses.indexIn(word) >= 0)
            return word.left(nl - 3);
        if (suffix_2_letter.indexIn(word) >= 0)
            return word.left(nl - 2);
        if (suffix_1_letter.indexIn(word) >= 0)
            return word.left(nl - 1);

        return word;
    }
    QStringList stems(const QString& word) const
    {
        QStringList sts;
        {
            QString stripped(word);
            c2bUtils::stripDiacritics(stripped);
            if (stripped != word)
            {
                sts.append(word);
                sts.append(stripped);
                return sts;
            }
        }
        {
            const QString lower(word.toLower());
            if (dictionary.contains(lower))
            {
                sts.append(word);
                sts.append(cased(word, dictionary.value(lower)));
                return sts;
            }
        }
        sts.append(stem(word));
        return sts;
    }
    static QString cased(const QString& word, const QString& other)
    {
        const int n(std::min(word.length(), other.length()));
        QString wc(other);
        for (int i = 0; i < n; ++i)
            wc[i] = word.at(i).isUpper() ? wc.at(i).toUpper() : wc.at(i).toLower();
        return wc;
    }

    QHash<QString, QString> dictionary;
    QRegExp digits;
    QRegExp suffix_1_letter;
    QRegExp suffix_2_letter;
    QRegExp suffix_2_letter_inflected;
    QRegExp suffix_2_letter_length_5;
    QRegExp suffix_3_letter;
    QRegExp suffix_3_letter_length_7;
    QRegExp suffix_4_letter;
    QRegExp suffix_double_esses;
    QRegExp suffix_isz;
    QRegExp suffix_man;
    QRegExp suffix_misc;
    QRegExp suffix_ogues;
    QRegExp suffix_ours;
    QRegExp suffix_reer;
    QRegExp suffix_sz;
    QRegExp suffix_ysz;
};

#endif
