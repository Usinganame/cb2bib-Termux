/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "stemMatcher.h"

#include "cb2bib_utilities.h"
#include "stemmer.h"
#include "triads.h"

#include <limits>


stemMatcher::stemMatcher()
    : _hook(-1),
      _stretch(0),
      _substring_count(0),
      _substring_rex_count(0),
      _substring_txt_count(0),
      _matched_length(-1),
      _p0(0),
      _pn(0) {}

stemMatcher::stemMatcher(const QString& pattern, const Qt::CaseSensitivity cs) : _p0(0), _pn(0)
{
    setPattern(pattern, cs);
}


void stemMatcher::setPattern(const QString& pattern, const Qt::CaseSensitivity cs)
{
    _hook = -1;
    _matched_length = -1;
    _stretch = 0;

    QStringList substrings;
    {
        const QRegExp rmnww("[\\W_]");
        const QString boundedt("\\b%1\\b");
        const QString ort("(:?%1)");
        const QString stretcht(".{0,%1}");
        const int minimum_word_length(4);
        stemmer ls;

        const QStringList segments(pattern.split(' ', QString::SkipEmptyParts));
        for (int s = 0; s < segments.count(); ++s)
        {
            const QStringList qors(segments.at(s).split('|', QString::SkipEmptyParts));
            QStringList so;
            int slength(0);
            for (int o = 0; o < qors.count(); ++o)
            {
                slength = std::max(slength, qors.at(o).length());
                const QStringList words(qors.at(o).split('_', QString::SkipEmptyParts));
                QStringList sw;
                for (int w = 0; w < words.count(); ++w)
                    if (words.at(w).startsWith('+'))
                    {
                        QString bw(words.at(w).right(words.at(w).length() - 1));
                        bw.replace(c2bUtils::nonLetter, stretcht.arg(1));
                        sw.append(boundedt.arg(bw));
                    }
                    else
                    {
                        QStringList wl(ls.stems(words.at(w)));
                        for (int l = 0; l < wl.count(); ++l)
                        {
                            const int nnl(wl.at(l).count(c2bUtils::nonLetter));
                            if (nnl > 0 && nnl < wl.at(l).length())
                                wl[l].replace(c2bUtils::nonLetter, stretcht.arg(1));
                        }
                        sw.append(wl.count() == 1 ? wl.at(0) : ort.arg(wl.join('|')));
                    }
                so.append(sw.join(stretcht.arg(25)));
            }
            substrings.append(so.count() == 1 ? so.at(0) : ort.arg(so.join('|')));
            _stretch += slength > minimum_word_length ? 35 : 10;
        }

        _subpatterns = pattern.split(rmnww, QString::SkipEmptyParts);
    }

    _substring_count = substrings.count();
    _substring_rex_count = 0;
    for (int i = 0; i < _substring_count; ++i)
        if (substrings.at(i).contains(c2bUtils::nonLetter))
            ++_substring_rex_count;
    _substring_txt_count = _substring_count - _substring_rex_count;
    _substrings_rex.resize(_substring_rex_count);
    _substrings_txt.resize(_substring_txt_count);
    _matched_lengths.fill(0, _substring_count);
    _sp0.resize(_substring_count);
    _signature_string.clear();

    for (int i = 0, ir = 0, it = 0; i < _substring_count; ++i)
        if (substrings.at(i).contains(c2bUtils::nonLetter))
        {
            QRegularExpression& re(_substrings_rex[ir++]);
#if (QT_VERSION >= QT_VERSION_CHECK(5, 4, 0)) && (QT_VERSION < QT_VERSION_CHECK(5, 12, 0))
            const QRegularExpression::PatternOptions po(QRegularExpression::DontCaptureOption |
                    QRegularExpression::UseUnicodePropertiesOption |
                    QRegularExpression::OptimizeOnFirstUsageOption);
#else
            const QRegularExpression::PatternOptions po(QRegularExpression::DontCaptureOption |
                    QRegularExpression::UseUnicodePropertiesOption);
#endif
            re.setPattern(substrings.at(i));
            re.setPatternOptions(cs == Qt::CaseSensitive ? po : po | QRegularExpression::CaseInsensitiveOption);
        }
        else
        {
            txtmatcher& tm(_substrings_txt[it++]);
            tm.setPattern(substrings.at(i), cs);
            _signature_string += substrings.at(i) + ' ';
        }
    _signature_string.chop(1);

    for (int i = 0, lf = std::numeric_limits<int>::max(); i < _substring_txt_count; ++i)
    {
        const int f(_substrings_txt.at(i).frequency() * triads::textFrequency(_substrings_txt.at(i).pattern()));
        if (f < lf)
        {
            lf = f;
            _hook = i;
        }
    }
    if (_hook == -1)
        for (int i = 0, lf = std::numeric_limits<int>::max(); i < _substring_rex_count; ++i)
        {
            const int f(triads::textFrequency(_substrings_rex.at(i).pattern()));
            if (f < lf)
            {
                lf = f;
                _hook = _substring_txt_count + i;
            }
        }
#ifdef C2B_DEBUG_SEARCHING
    for (int i = 0; i < _substring_txt_count; ++i)
        qDebug() << "subpattern txt     " << _substrings_txt.at(i).pattern();
    for (int i = 0; i < _substring_rex_count; ++i)
        qDebug() << "subpattern rex     " << _substrings_rex.at(i).pattern();
    if (_hook < _substring_txt_count)
        qDebug() << "hook               " << _substrings_txt.at(_hook).pattern() << _hook;
    else
        qDebug() << "hook               " << _substrings_rex.at(_hook - _substring_txt_count).pattern() << _hook;
    qDebug() << "_stretch           " << _stretch;
    qDebug() << "subpatternstrings  " << subpatternStrings();
    qDebug() << "signaturestring    " << signatureString();
#endif
}

int stemMatcher::indexIn(const QString& text, const int from) const
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
        hp += _matched_lengths.at(_hook);
    }
    return p;
}
