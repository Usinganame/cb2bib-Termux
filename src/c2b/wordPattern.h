/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef WORDPATTERN_H
#define WORDPATTERN_H

#include "compositePattern.h"

#include "txtmatcher.h"


class wordPattern : public compositePattern
{

public:
    enum Type
    {
        AllWords,
        AnyWord
    };

    wordPattern();
    wordPattern(const QString& pattern, const Type type, const Qt::CaseSensitivity cs);
    inline ~wordPattern() {}


    void setPattern(const QString& pattern, const Type type, const Qt::CaseSensitivity cs = Qt::CaseSensitive);

    inline bool matches(const QString& str) const override
    {
        _matched_length = -1;
        if (str.length() == 0)
            return false;
        if (_type == AllWords)
        {
            for (int i = _subpattern_count - 1; i >= 0; --i)
                if (_submatchers.at(i).indexIn(str) == -1)
                    return false;
            return true;
        }
        else
        {
            for (int i = 0; i < _subpattern_count; ++i)
                if (_submatchers.at(i).indexIn(str) != -1)
                    return true;
            return false;
        }
    }
    inline int indexIn(const QString& str, const int from = 0) const override
    {
        const QRegularExpressionMatch rem(_regexp.match(str, from));
        _matched_length = rem.capturedLength();
        return rem.capturedStart();
    }
    inline const QVector<txtmatcher>& submatchers() const
    {
        return _submatchers;
    }


private:
    QVector<txtmatcher> _submatchers;
    Type _type;
};

#endif
