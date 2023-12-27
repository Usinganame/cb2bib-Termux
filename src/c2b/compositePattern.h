/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef COMPOSITEPATTERN_H
#define COMPOSITEPATTERN_H

#include <QRegularExpression>
#include <QStringList>
#include <QVector>


class compositePattern
{

public:
    compositePattern();
    compositePattern(const QString& pattern, const Qt::CaseSensitivity cs);
    inline virtual ~compositePattern() {}


    inline const QString strings() const
    {
        return _string;
    }
    inline const QStringList substrings() const
    {
        return _substrings;
    }
    inline const QRegularExpression& regexp() const
    {
        return _regexp;
    }
    inline const QVector<QRegularExpression>& subregexps() const
    {
        return _subregexps;
    }
    inline Qt::CaseSensitivity caseSensitivity() const
    {
        return _case_sensitivity;
    }
    inline int subpatternCount() const
    {
        return _subpattern_count;
    }
    inline int matchedLength() const
    {
        return _matched_length;
    }
    inline bool isMultipattern() const
    {
        return _is_multipattern;
    }

    virtual bool matches(const QString& str) const = 0;
    virtual int indexIn(const QString& str, const int from) const = 0;


protected:
    static QString escape(const QString& str, const Qt::CaseSensitivity cs);
    void set_sort_index();

    QList<double> _ranks;
    QRegularExpression _regexp;
    QString _string;
    QStringList _substrings;
    QVector<QRegularExpression> _subregexps;
    QVector<int> _index;
    Qt::CaseSensitivity _case_sensitivity;
    bool _is_multipattern;
    int _subpattern_count;
    mutable QVector<int> _p0;
    mutable QVector<int> _pn;
    mutable int _matched_length;
};

#endif
