/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef WORDMATCHER_H
#define WORDMATCHER_H

#include "txtmatcher.h"

#include <QStringList>
#include <QVector>


class wordMatcher
{

public:
    wordMatcher();
    explicit wordMatcher(const QString& pattern, const Qt::CaseSensitivity cs = Qt::CaseSensitive);
    inline ~wordMatcher() {}


    int indexIn(const QString& text, const int from = 0) const;
    void setPattern(const QString& pattern, const Qt::CaseSensitivity cs);
    inline int matchedLength() const
    {
        return _matched_length;
    }
    inline const QStringList& subpatternStrings() const
    {
        return _subpatterns;
    }


private:
    inline int _index_in(const int s, const QString& text, const int p0) const
    {
        return _substrings.at(s).indexIn(text, p0);
    }
    inline int _index_in(const int s, const QString& text, const int p0, const int pn) const
    {
        return _substrings.at(s).indexIn(text.unicode(), std::min(_pn, pn), p0);
    }
    inline int _index_around(const QString& text, const int phook) const
    {
        for (int i = 0; i < _substring_count; ++i)
            _sp0[i] = -1;
        _sp0[_hook] = phook;

        const int bp0 = std::max(_p0, phook - _stretch);
        const int bpn = std::min(_pn, phook + _stretch);
        for (int i = 0; i < _substring_count; ++i)
            if (_sp0.at(i) == -1)
            {
                const int p0(_index_in(i, text, bp0, bpn));
                if (p0 == -1)
                    return -1;
                _sp0[i] = p0;
            }

        int bp(_pn);
        int fp(_p0);
        for (int i = 0; i < _substring_count; ++i)
        {
            const int p0(_sp0.at(i));
            if (bp > p0)
                bp = p0;
            const int pn(p0 + _lengths.at(i));
            if (fp < pn)
                fp = pn;
        }
        _matched_length = fp - bp;
        return bp;
    }

    QStringList _subpatterns;
    QVector<int> _lengths;
    QVector<txtmatcher> _substrings;
    int _hook;
    int _stretch;
    int _substring_count;
    mutable QVector<int> _sp0;
    mutable int _matched_length;
    mutable int _p0;
    mutable int _pn;
};

#endif
