/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "wordPattern.h"

#include "cb2bib_utilities.h"
#include "triads.h"


wordPattern::wordPattern() : compositePattern(), _type(AllWords) {}

wordPattern::wordPattern(const QString& pattern, const Type type, const Qt::CaseSensitivity cs)
    : compositePattern(pattern, cs), _type(type)
{
    setPattern(pattern, type, cs);
}


void wordPattern::setPattern(const QString& pattern, const Type type, const Qt::CaseSensitivity cs)
{
    _string = pattern;
    _type = type;
    _case_sensitivity = cs;
    _is_multipattern = false;
    _matched_length = -1;

    const QStringList words(_string.split(c2bUtils::nonLetter, QString::SkipEmptyParts));
    _subpattern_count = words.count();
    if (_subpattern_count == 0)
        return;

    _ranks.clear();
    QStringList subpattern;
    QStringList substring;
    for (int i = 0; i < words.count(); ++i)
    {
        const QString& wi = words.at(i);
        const QString sp(escape(wi, _case_sensitivity));
        subpattern.append(sp);
        substring.append(wi);
        _ranks.append(triads::textFrequency(wi)); // Rank according expectation (arXiv:0705.0751, Eq. 6)
    }
    set_sort_index();
    if (_subpattern_count == 1)
        _regexp.setPattern(escape(_string, _case_sensitivity));
    else
        _regexp.setPattern(QString("(?:%1)").arg(subpattern.join("|")));
    _submatchers.resize(_subpattern_count);
    _subregexps.resize(_subpattern_count);
    _substrings.clear();
    for (int i = 0; i < _subpattern_count; ++i)
    {
        const int ii(_index.at(i));
        _submatchers[i] = txtmatcher(substring.at(ii), _case_sensitivity);
        _subregexps[i].setPattern(subpattern.at(ii));
        _substrings.append(substring.at(ii));
    }
    _is_multipattern = _subpattern_count > 1;
}
