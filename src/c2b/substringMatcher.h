/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef SUBSTRINGMATCHER_H
#define SUBSTRINGMATCHER_H

#include "txtmatcher.h"

#include <QVector>

#define C2B_DEBUG_SUBSTRINGMATCHER 0


class substringMatcher
{

public:
    substringMatcher();
    explicit substringMatcher(const QString& pattern, const Qt::CaseSensitivity cs = Qt::CaseSensitive);
    inline ~substringMatcher() {}


    int indexIn(const QString& str, const int from = 0) const;
    inline int matchedLength() const
    {
        return _matched_length;
    }


private:
    inline int _index_in(const int s, const QString& str, const int p0) const
    {
        return _substrings.at(s).indexIn(str, p0);
    }
    inline int _index_in(const int s, const QString& str, const int p0, const int pn) const
    {
#if C2B_DEBUG_SUBSTRINGMATCHER
        qDebug() << "Search for substring:" << _substrings.at(s).pattern() << "in interval" << p0 << pn;
        int i;
        if (p0 >= pn)
            i = -1;
        else
            i = _substrings.at(s).indexIn(str.unicode(), std::min(_pn, pn), p0);
        qDebug() << "substringMatcher: returned index:" << i;
        return i;
#else
        return _substrings.at(s).indexIn(str.unicode(), std::min(_pn, pn), p0);
#endif
    }
    inline int _p_back(const int s, const int p0) const
    {
        return std::max(_p0 + _acc_lengths.at(s), p0 - _stretches.at(s + 1) - _lengths.at(s));
    }
    inline int _p_forth(const int s, const int p0) const
    {
        return std::min(_pn, p0 + _stretches.at(s) + _lengths.at(s));
    }
    inline int _index_back(const int s, const QString& str, int p0, const int pn) const
    {
        while ((p0 = _index_in(s, str, p0, pn)) != -1)
        {
            if (s == 0)
                return p0;
            const int i(_index_back(s - 1, str, _p_back(s - 1, p0), p0));
            if (i != -1)
                return i;
            p0 += _lengths.at(s);
        }
        return -1;
    }
    inline int _index_forth(const int s, const QString& str, int p0, const int pn) const
    {
        while ((p0 = _index_in(s, str, p0, pn)) != -1)
        {
            p0 += _lengths.at(s);
            if (s + 1 == _substring_count)
                return p0;
            const int i(_index_forth(s + 1, str, p0, _p_forth(s + 1, p0)));
            if (i != -1)
                return i;
        }
        return -1;
    }
    inline int _index_around(const QString& str, const int phook) const
    {
        int bp(phook);
        if (_hook > 0)
        {
            bp = _index_back(_hook - 1, str, _p_back(_hook - 1, bp), bp);
            if (bp == -1)
                return -1;
        }
        int fp(phook + _lengths.at(_hook));
        if (_hook + 1 < _substring_count)
        {

            fp = _index_forth(_hook + 1, str, fp, _p_forth(_hook + 1, fp));
            if (fp == -1)
                return -1;
        }
        _matched_length = fp - bp;
        return bp;
    }

    QVector<txtmatcher> _substrings;
    QVector<int> _acc_lengths;
    QVector<int> _lengths;
    QVector<int> _stretches;
    int _hook;
    int _substring_count;
    mutable int _matched_length;
    mutable int _p0;
    mutable int _pn;
};

#endif
