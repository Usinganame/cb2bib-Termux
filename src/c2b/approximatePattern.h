/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 *
 *   Class implementation of the approximate search algorithm
 *   P. Constans. Approximate textual retrieval. arXiv:0705.0751, 2007.
 ***************************************************************************/
#ifndef APPROXIMATEPATTERN_H
#define APPROXIMATEPATTERN_H

#include "compositePattern.h"

#include "substringMatcher.h"

#define C2B_DEBUG_APPROXIMATEPATTERN 0


class approximatePattern : public compositePattern
{

public:
    approximatePattern();
    approximatePattern(const QString& pattern, const Qt::CaseSensitivity cs);
    inline ~approximatePattern() {}

    void setPattern(const QString& pattern, const Qt::CaseSensitivity cs = Qt::CaseSensitive);

    inline bool matches(const QString& str) const override
    {
        _matched_length = -1;
        if (str.length() == 0)
            return false;
        if (_is_multipattern)
        {
            for (int i = 0; i < _subpattern_count; ++i)
                if (_submatchers.at(i).indexIn(str) != -1)
                    return true;
            return false;
        }
        else
            return _regexp.match(str).hasMatch();
    }
    inline int indexIn(const QString& str, const int from = 0) const override
    {
        _matched_length = -1;
        if (str.length() == 0)
            return -1;
        int index;
        if (_is_multipattern)
        {
            for (int i = 0; i < _subpattern_count; ++i)
            {
                _p0[i] = _submatchers.at(i).indexIn(str, from);
                _pn[i] = _p0.at(i) + _submatchers.at(i).matchedLength();
            }
            mergeIndices(&index, str);
        }
        else
        {
            _regexp_match = _regexp.match(str, from);
            _matched_length = _regexp_match.capturedLength();
            index = _regexp_match.capturedStart();
        }
        return index;
    }
    inline const QVector<substringMatcher>& submatchers() const
    {
        return _submatchers;
    }
    inline const QStringList& subpatternStrings() const
    {
        return _subpatterns;
    }


private:
    const QStringList splitWord(const QString& word) const;
    int stretch(int piece_i, int piece_j) const;
    static QString wordPattern(const QString& word, Qt::CaseSensitivity cs);
    static int wordCount(const QString& str);
    static void splitPattern(const QString& p, QStringList* w, QList<int>* ws, QList<int>* we);
    void mergeIndices(int* index_in, const QString& str) const;
    void splitPattern();

    QList<int> _piece_ends;
    QList<int> _piece_starts;
    QStringList _prefixes;
    QStringList _string_pieces;
    QStringList _subpatterns;
    QStringList _suffixes;
    QVector<substringMatcher> _submatchers;
    mutable QRegularExpressionMatch _regexp_match;
};

#endif
