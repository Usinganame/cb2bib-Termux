/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "compositePattern.h"

#include "cb2bib_utilities.h"

namespace
{

template <typename T>
class descending
{
public:
    explicit descending(const T& data) : _data(data) {}
    inline bool operator()(const int i, const int j)
    {
        return _data.at(i) > _data.at(j);
    }

private:
    const T& _data;
};

} // namespace


compositePattern::compositePattern()
    : _case_sensitivity(Qt::CaseSensitive), _is_multipattern(false), _subpattern_count(0), _matched_length(-1) {}

compositePattern::compositePattern(const QString& pattern, const Qt::CaseSensitivity cs)
    : _string(pattern), _case_sensitivity(cs), _is_multipattern(false), _subpattern_count(0), _matched_length(-1) {}


QString compositePattern::escape(const QString& str, const Qt::CaseSensitivity cs)
{
    if (cs == Qt::CaseSensitive)
        return QRegularExpression::escape(str);
    QString scaped;
    for (int i = 0; i < str.length(); ++i)
        if (str.at(i).isLetter())
            scaped += QString("[%1%2]").arg(str.at(i).toUpper()).arg(str.at(i).toLower());
        else
            scaped += QRegularExpression::escape(str.at(i));
    return scaped;
}

void compositePattern::set_sort_index()
{
    Q_ASSERT_X(_ranks.count() == _subpattern_count, "compositePattern", "Mismatch in subexpression initialization");
    _index.resize(_subpattern_count);
    for (int i = 0; i < _subpattern_count; ++i)
        _index[i] = i;
    descending<QList<double>> sort(_ranks);
    std::sort(_index.begin(), _index.end(), sort);
}
