/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 *
 *   Class implementation of the approximate search algorithm
 *   P. Constans. Approximate textual retrieval. arXiv:0705.0751, 2007.
 ***************************************************************************/
#include "approximatePattern.h"

#include "cb2bib_utilities.h"
#include "triads.h"

namespace
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 4, 0)) && (QT_VERSION < QT_VERSION_CHECK(5, 12, 0))
static const QRegularExpression::PatternOptions _qre_pattern_options(QRegularExpression::DontCaptureOption |
        QRegularExpression::UseUnicodePropertiesOption |
        QRegularExpression::OptimizeOnFirstUsageOption);
#else
static const QRegularExpression::PatternOptions _qre_pattern_options(QRegularExpression::DontCaptureOption |
        QRegularExpression::UseUnicodePropertiesOption);
#endif
} // namespace


approximatePattern::approximatePattern() : compositePattern() {}

approximatePattern::approximatePattern(const QString& pattern, const Qt::CaseSensitivity cs)
    : compositePattern(pattern, cs)
{
    setPattern(pattern, cs);
}


void approximatePattern::setPattern(const QString& pattern, const Qt::CaseSensitivity cs)
{
    _string = pattern;
    _subpatterns = pattern.split(c2bUtils::nonLetter, QString::SkipEmptyParts);
    _case_sensitivity = cs;
    _is_multipattern = false;
    _matched_length = -1;
    _subpattern_count = 0;
    // Exact match
    if (_string.length() < 5)
    {
        _regexp.setPattern(escape(_string, _case_sensitivity));
        _regexp.setPatternOptions(_qre_pattern_options);
        return;
    }
    // Single word: Allow 1 error (1 missing / 3 excess), anywhere
    if (wordCount(_string) == 1)
    {
        _regexp.setPattern(wordPattern(_string, _case_sensitivity));
        _regexp.setPatternOptions(_qre_pattern_options);
        return;
    }
    // Multiple words
    _prefixes = c2bUtils::fileToString(":/txt/txt/prefixes.txt").split(c2bUtils::nonLetter, QString::SkipEmptyParts);
    _suffixes = c2bUtils::fileToString(":/txt/txt/suffixes.txt").split(c2bUtils::nonLetter, QString::SkipEmptyParts);
    splitPattern();
    if (_string_pieces.count() < 3) // Cases: "qq pp", "qqq pp", etc
    {
        _regexp.setPattern(wordPattern(_string, _case_sensitivity));
        _regexp.setPatternOptions(_qre_pattern_options);
        // Avoid rare cases triggering 'too large regular expression' by just composing prefix and suffix
        if (!_regexp.isValid())
        {
            _regexp.setPattern("(?:" + _string_pieces.join('|') + ')');
            _regexp.setPatternOptions(_qre_pattern_options);
        }
        return;
    }
    _is_multipattern = true;

    // Set parameters
    const double percent_scan(50.);
    const double scan_factor(100. / percent_scan);
    const int max_blocks(_string_pieces.count() / 2);
    const int requested_blocks(c2bUtils::nearInteger(scan_factor));
    const int blocks(std::min(max_blocks, 1 + requested_blocks));
    int pieces_per_block(_string_pieces.count() / blocks); // Ceiling
    if ((_string_pieces.count() % blocks) > 0)
        ++pieces_per_block;

#if C2B_DEBUG_APPROXIMATEPATTERN
    qDebug() << _string_pieces << max_blocks << scan_factor << requested_blocks << pieces_per_block
             << _string_pieces.count() % blocks;
    for (int b = 0; b < blocks; ++b)
        for (int i = 0; i < pieces_per_block; ++i)
            if (b + (i * blocks) < _string_pieces.count())
                qDebug() << "block#   " << b << "pick item " << b + (i * blocks) << _string_pieces.at(b + (i * blocks));
#endif

    _ranks.clear();
    QStringList submatcher;
    QStringList subpattern;
    QStringList substring;
    const QString sp_stretch(".{0,%1}%2");
    for (int b = 0; b < blocks; ++b)
    {
        int ii(b);
        QString sm(_string_pieces.at(ii));
        QString sp(escape(_string_pieces.at(ii), _case_sensitivity));
        QString ss(_string_pieces.at(ii));
        double stretch_product(1.);
        for (int j = 1; j < pieces_per_block; ++j)
        {
            int jj(b + (j * blocks));
            if (jj < _string_pieces.count())
            {
                const int st(stretch(ii, jj));
                sm += sp_stretch.arg(st).arg(_string_pieces.at(jj));
                sp += sp_stretch.arg(st).arg(escape(_string_pieces.at(jj), _case_sensitivity));
                ss += ' ' + _string_pieces.at(jj);
                stretch_product *= st;
                ii = jj;
            }
        }
        submatcher.append(sm);
        subpattern.append(sp);
        substring.append(ss);
        // Rank according expectation (arXiv:0705.0751, Eq. 6)
        _ranks.append(stretch_product * triads::textFrequency(ss));
        ++_subpattern_count;
    }
    set_sort_index();
    _regexp.setPattern(QString("(?:%1)").arg(subpattern.join("|")));
    _submatchers.resize(_subpattern_count);
    _subregexps.resize(_subpattern_count);
    _substrings.clear();
    for (int i = 0; i < _subpattern_count; ++i)
    {
        const int ii(_index.at(i));
        _submatchers[i] = substringMatcher(submatcher.at(ii), _case_sensitivity);
        _subregexps[i].setPattern(subpattern.at(ii));
        _substrings.append(substring.at(ii));
    }
    _p0.resize(_subpattern_count);
    _pn.resize(_subpattern_count);
}

void approximatePattern::splitPattern()
{
    if (_string.isEmpty())
        return;
    QStringList wordList;
    QList<int> wordStarts;
    QList<int> wordEnds;
    splitPattern(_string, &wordList, &wordStarts, &wordEnds);
    for (int i = 0; i < wordList.count(); ++i)
    {
        const QStringList pieces(splitWord(wordList.at(i)));
        const QString prefix(pieces.at(0));
        if (prefix.length() > 2)
        {
            _string_pieces.append(prefix);
            _piece_starts.append(wordStarts.at(i));
            _piece_ends.append(wordStarts.at(i) + prefix.length());
        }
        const QString suffix(pieces.at(1));
        if (suffix.length() > 2)
        {
            _string_pieces.append(suffix);
            _piece_starts.append(wordEnds.at(i) - suffix.length());
            _piece_ends.append(wordEnds.at(i));
        }
    }
}

void approximatePattern::splitPattern(const QString& p, QStringList* w, QList<int>* ws, QList<int>* we)
{
    w->clear();
    ws->clear();
    we->clear();
    QString str(p);
    str.replace(c2bUtils::nonLetter, " ");
    str.append(' ');
    int w_starts(0);
    int w_ends(0);
    bool in_word(false);
    for (int i = 0; i < str.length(); ++i)
        if (str.at(i) == ' ')
        {
            if (in_word)
            {
                // Word actually ends at i - 1. However, this convention simplifies things.
                w_ends = i;
                w->append(str.mid(w_starts, w_ends - w_starts));
                ws->append(w_starts);
                we->append(w_ends);
            }
            in_word = false;
        }
        else
        {
            if (!in_word)
                w_starts = i;
            in_word = true;
        }
}

const QStringList approximatePattern::splitWord(const QString& word) const
{
    // Returns the pair "prefix+root root+suffix"
    const int minimum_length(5);
    const int wlen(word.length());
    if (wlen < minimum_length)
        return QStringList() << word << word;

    QString w(word.toLower());
    int plen_min(wlen);
    int slen_min(wlen);
    int plen_max(0);
    int slen_max(0);
    for (int i = 0; i < _prefixes.count(); ++i)
        if (w.startsWith(_prefixes.at(i)))
        {
            const int plen(_prefixes.at(i).length());
            if (plen < plen_min)
                plen_min = plen;
            if (plen > plen_max)
                plen_max = plen;
        }
    for (int i = 0; i < _suffixes.count(); ++i)
        if (w.endsWith(_suffixes.at(i)))
        {
            const int slen(_suffixes.at(i).length());
            if (slen < slen_min)
                slen_min = slen;
            if (slen > slen_max)
                slen_max = slen;
        }
    if (plen_min == wlen)
        plen_min = 0;
    if (slen_min == wlen)
        slen_min = 0;

    w = word;
    const int wlenMp_min(std::max(plen_min, wlen - slen_min));
    const int wlenMs_min(std::max(slen_min, wlen - plen_min));
    const int wlenMp_max(std::max(plen_max, wlen - slen_max));
    const int wlenMs_max(std::max(slen_max, wlen - plen_max));
#if C2B_DEBUG_APPROXIMATEPATTERN
    qDebug() << wlenMp_min << wlenMs_min << w.left(wlenMp_min) << w.right(wlenMs_min);
    qDebug() << wlenMp_max << wlenMs_max << w.left(wlenMp_max) << w.right(wlenMs_max);
#endif
    if (wlenMp_max >= minimum_length && wlenMs_max >= minimum_length)
        return QStringList() << w.left(wlenMp_max) << w.right(wlenMs_max);
    else if (wlenMp_min >= minimum_length && wlenMs_min >= minimum_length)
        return QStringList() << w.left(wlenMp_min) << w.right(wlenMs_min);
    else
        return QStringList() << word << word;
}

QString approximatePattern::wordPattern(const QString& word, Qt::CaseSensitivity cs)
{
    const int len(word.length());
    const QString ord(word.right(len - 1));
    QStringList possible;
    possible.append(escape(ord.left(len - 2), cs));
    for (int i = 1; i < len - 2; ++i)
        possible.append(QString("%1.{0,2}%2").arg(escape(ord.left(len - i - 3), cs), escape(ord.right(i), cs)));
#if C2B_DEBUG_APPROXIMATEPATTERN
    qDebug() << "WordPattern: "
             << QString("(?:%1(?:%2)|%3)").arg(escape(word.at(0), cs), possible.join("|"), escape(ord, cs));
#endif
    return QString("(?:%1(?:%2)|%3)").arg(escape(word.at(0), cs), possible.join("|"), escape(ord, cs));
}

int approximatePattern::wordCount(const QString& str)
{
    const QString tstr(QString(str).replace(c2bUtils::nonLetter, " ").simplified());
    return 1 + tstr.count(' ');
}

int approximatePattern::stretch(int piece_i, int piece_j) const
{
    const int minStretch(3);
    const int maxStretch(20);
    if (_string_pieces.at(piece_j).length() > 4)
        return std::max((maxStretch * (piece_j - piece_i)),
                        minStretch * (_piece_starts.at(piece_j) - _piece_ends.at(piece_i)));
    else
        return minStretch * (_piece_starts.at(piece_j) - _piece_ends.at(piece_i)); // Estimated error ratio only
}

void approximatePattern::mergeIndices(int* index_in, const QString& str) const
{
    int index = str.length();
    for (int i = 0; i < _subpattern_count; ++i)
        if (_p0.at(i) != -1 && _p0.at(i) < index)
            index = _p0.at(i);
    if (index == str.length())
        index = -1;
    else
    {
        int pn(0);
        for (int i = 0; i < _subpattern_count; ++i)
            if (_pn.at(i) > pn && _p0.at(i) == index)
                pn = _pn.at(i);
        for (int m = 0; m < _subpattern_count; ++m)
            for (int i = 0; i < _subpattern_count; ++i)
                if (_pn.at(i) > pn && _p0.at(i) < pn)
                    pn = _pn.at(i);
        // Beautify match by including whole words
        for (int w = index - 1; w > std::max(0, index - 13); --w)
            if (!str.at(w).isLetter())
            {
                index = w + 1;
                break;
            }
        for (int w = pn; w < std::min(pn + 13, str.length()); ++w)
            if (!str.at(w).isLetter())
            {
                pn = w;
                break;
            }
        _matched_length = pn - index;
    }
    *index_in = index;
}
