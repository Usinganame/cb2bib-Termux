/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "substringMatcher.h"

#include "cb2bib_utilities.h"
#include "triads.h"


substringMatcher::substringMatcher() : _hook(-1), _substring_count(0), _matched_length(-1), _p0(0), _pn(0) {}

substringMatcher::substringMatcher(const QString& pattern, const Qt::CaseSensitivity cs)
    : _hook(-1), _matched_length(-1), _p0(0), _pn(0)
{
    QRegExp sep("\\.\\{(\\d+),(\\d+)\\}");
    QStringList substrings(pattern.split(sep, QString::SkipEmptyParts));
    Q_ASSERT_X(substrings.count() >= 2, "substringMatcher", "Expected at least two substrings in pattern");
    int s(0);
    QList<int> stretches;
    while ((s = sep.indexIn(pattern, s)) != -1)
    {
        Q_ASSERT_X(sep.captureCount() == 2, "substringMatcher", "Expected two digits in repetition");
        Q_ASSERT_X(sep.cap(1).toInt() == 0, "substringMatcher", "Expected zero in first repetition digit");
        stretches.append(sep.cap(2).toInt());
        s += sep.matchedLength();
    }
    Q_ASSERT_X(substrings.count() == stretches.count() + 1, "substringMatcher", "Mismatch in pattern");

    _substring_count = substrings.count();
    _substrings.resize(_substring_count);
    _lengths.resize(_substring_count);
    for (int i = 0; i < _substring_count; ++i)
    {
        _substrings[i] = txtmatcher(substrings.at(i), cs);
        _lengths[i] = substrings.at(i).length();
    }
    _stretches.resize(_substring_count);
    _stretches[0] = 0;
    for (int i = 1; i < _substring_count; ++i)
        _stretches[i] = stretches.at(i - 1);
    _acc_lengths.fill(0, _substring_count);
    for (int i = 1; i < _substring_count; ++i)
        _acc_lengths[i] = _acc_lengths[i - 1] + _lengths.at(i - 1);

    int lf(10000);
    for (int i = 0; i < _substring_count; ++i)
    {
        const int f(triads::textFrequency(substrings.at(i)));
        if (f < lf)
        {
            lf = f;
            _hook = i;
        }
    }
#if C2B_DEBUG_SUBSTRINGMATCHER
    qDebug() << "substringMatcher: Pattern: " << pattern;
    qDebug() << "substringMatcher: Hook:    " << substrings.at(_hook);
#endif
}


int substringMatcher::indexIn(const QString& str, const int from) const
{
    _matched_length = -1;
    if (_hook == -1) // Uninitialized
        return -1;
    _p0 = from;
    if (_p0 < 0)
        _p0 = 0;
    _pn = str.length();
    if (_pn == 0)
        return -1;

    int hp(_p0);
    int p(-1);
    while (p == -1)
    {
        hp = _index_in(_hook, str, hp + _acc_lengths.at(_hook));
#if C2B_DEBUG_SUBSTRINGMATCHER
        qDebug() << "substringMatcher: Hook at  " << hp;
#endif
        if (hp == -1)
            return -1;
        p = _index_around(str, hp);
        hp += _lengths.at(_hook);
    }
    return p;
}
