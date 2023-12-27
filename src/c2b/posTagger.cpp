/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "posTagger.h"

#include "cb2bib_utilities.h"
#include "settings.h"


posTagger::posTagger()
    : _period('.'),
      _space(' '),
      _pos_a("A"),
      _pos_g("G"),
      _pos_n("N"),
      _pos_o("O"),
      _pos_r("R"),
      _pos_s("S"),
      _suffix_able("able"),
      _suffix_ae("ae"),
      _suffix_al("al"),
      _suffix_apostrophes("'s"),
      _suffix_ar("ar"),
      _suffix_ed("ed"),
      _suffix_ful("ful"),
      _suffix_ic("ic"),
      _suffix_ics("ics"),
      _suffix_ing("ing"),
      _suffix_is("is"),
      _suffix_ive("ive"),
      _suffix_lent("lent"),
      _suffix_less("less"),
      _suffix_like("like"),
      _suffix_ly("ly"),
      _suffix_ous("ous"),
      _suffix_s("s"),
      _suffix_ss("ss"),
      _suffix_us("us") {}


bool posTagger::loadLexicon()
{
    const QString lexfn(settings::instance()->fileName("cb2Bib/PosLexiconFile"));
    QFile lexf(lexfn);
    if (!lexf.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        c2bUtils::warn(QObject::tr("Could not open POS lexicon file %1 for reading").arg(lexfn));
        return false;
    }
    QTextStream lex(&lexf);
    lex.setCodec("UTF-8");
    lex.setAutoDetectUnicode(true);
    const QChar comment('#');
    QString line;

    while (!lex.atEnd())
    {
        line = lex.readLine();
        if (line.isEmpty() || line.startsWith(comment))
            continue;
        const int n(line.toInt());
        for (int i = 0; i < n; ++i)
            _sentence_patterns.insert(lex.readLine(), QString());
        break;
    }
    while (!lex.atEnd())
    {
        line = lex.readLine();
        if (line.isEmpty() || line.startsWith(comment))
            continue;
        const int n(line.toInt());
        const QString tag(lex.readLine());
        for (int i = 0; i < n; ++i)
            _lexicon.insert(lex.readLine(), tag);
    }
    lexf.close();
    return _sentence_patterns.size() > 0 && _lexicon.size() > 0;
}

QString posTagger::tagged(const QString& text) const
{
    const QStringList words(text.split(_space, QString::SkipEmptyParts));
    const int nw(words.count());
    QString t(_period);
    for (int i = 0; i < nw; ++i)
    {
        const QString& w(words.at(i));
        if (_lexicon.contains(w))
            t += _lexicon.value(w) + _period;
        else
            t += ruletag(w) + _period;
    }
    return t;
}

QString posTagger::ruletag(const QString& word) const
{
    if (word.length() < 3)
        return _pos_s;
    if (word.endsWith(_suffix_ed) || word.endsWith(_suffix_ar) || word.endsWith(_suffix_ive) ||
        word.endsWith(_suffix_able) || word.endsWith(_suffix_ic) || word.endsWith(_suffix_al) ||
        word.endsWith(_suffix_ous) || word.endsWith(_suffix_lent) || word.endsWith(_suffix_like) ||
        word.endsWith(_suffix_ful) || word.endsWith(_suffix_less))
        return _pos_a;
    if (word.endsWith(_suffix_ing))
        return _pos_g;
    if (word.endsWith(_suffix_ly))
        return _pos_r;
    if (word.endsWith(_suffix_ss) || word.endsWith(_suffix_is) || word.endsWith(_suffix_ics) ||
        word.endsWith(_suffix_apostrophes) || word.endsWith(_suffix_us))
        return _pos_n;
    if (word.endsWith(_suffix_ae))
        return _pos_o;
    if (word.endsWith(_suffix_s))
        return _pos_o;
    return _pos_n;
}
