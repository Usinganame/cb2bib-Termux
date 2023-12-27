/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "wordMatcher.h"

#include "cb2bib_utilities.h"
#include "triads.h"

#include <limits>


wordMatcher::wordMatcher() : _hook(-1), _stretch(0), _substring_count(0), _matched_length(-1), _p0(0), _pn(0) {}

wordMatcher::wordMatcher(const QString& pattern, const Qt::CaseSensitivity cs) : _p0(0), _pn(0)
{
    setPattern(pattern, cs);
}


void wordMatcher::setPattern(const QString& pattern, const Qt::CaseSensitivity cs)
{
    _hook = -1;
    _matched_length = -1;
    _stretch = 0;

    _subpatterns = pattern.split(c2bUtils::nonLetter, QString::SkipEmptyParts);
    if (_subpatterns.count() == 0)
        return;
    _substring_count = _subpatterns.count();
    for (int i = 0; i < _substring_count; ++i)
        _subpatterns[i].replace('_', ' ');
    _substrings.resize(_substring_count);
    _lengths.resize(_substring_count);
    _sp0.resize(_substring_count);
    for (int i = 0; i < _substring_count; ++i)
    {
        _substrings[i] = txtmatcher(_subpatterns.at(i), cs);
        _lengths[i] = _subpatterns.at(i).length();
        if (_lengths.at(i) > 4)
            _stretch += 50;
        else
            _stretch += 10;
    }
    for (int i = 0, lf = std::numeric_limits<int>::max(); i < _substring_count; ++i)
    {
        const int f(_substrings.at(i).frequency() * triads::textFrequency(_substrings.at(i).pattern()));
        if (f < lf)
        {
            lf = f;
            _hook = i;
        }
    }
#ifdef C2B_DEBUG_SEARCHING
    for (int i = 0; i < _substring_count; ++i)
        qDebug() << "subpattern         " << _substrings.at(i).pattern();
    qDebug() << "hook               " << _substrings.at(_hook).pattern() << _hook;
    qDebug() << "_stretch           " << _stretch;
    qDebug() << "subpatternstrings  " << subpatternStrings();
#endif
}

int wordMatcher::indexIn(const QString& text, const int from) const
{
    _matched_length = -1;
    if (_hook == -1) // Uninitialized
        return -1;
    _p0 = from;
    if (_p0 < 0)
        _p0 = 0;
    _pn = text.length();
    if (_pn == 0)
        return -1;

    int hp(_p0);
    int p(-1);
    while (p == -1)
    {
        hp = _index_in(_hook, text, hp);
        if (hp == -1)
            return -1;
        p = _index_around(text, hp);
        hp += _lengths.at(_hook);
    }
    return p;
}
