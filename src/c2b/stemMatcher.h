/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef STEMMATCHER_H
#define STEMMATCHER_H

#include "txtmatcher.h"

#include <QRegularExpression>
#include <QVector>


class stemMatcher
{

public:
    stemMatcher();
    explicit stemMatcher(const QString& pattern, const Qt::CaseSensitivity cs = Qt::CaseSensitive);
    inline ~stemMatcher() {}


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
    inline QString signatureString() const
    {
        return _signature_string;
    }


private:
    inline int _index_in(const int s, const QString& text, const int p0) const
    {
        if (s < _substring_txt_count)
        {
            const int i(_substrings_txt.at(s).indexIn(text, p0));
            _matched_lengths[s] = i == -1 ? 0 : _substrings_txt.at(s).pattern().length();
            return i;
        }
        else
        {
            _match = _substrings_rex.at(s - _substring_txt_count).match(text, p0);
            _matched_lengths[s] = _match.capturedLength();
            return _match.capturedStart();
        }
    }
    inline int _index_in(const int s, const QString& text, const int p0, const int pn) const
    {
        if (s < _substring_txt_count)
        {
            const int i(_substrings_txt.at(s).indexIn(text.unicode(), std::min(_pn, pn), p0));
            _matched_lengths[s] = i == -1 ? 0 : _substrings_txt.at(s).pattern().length();
            return i;
        }
        else
        {
            const int npn(std::min(_pn, pn));
            if (p0 >= npn)
            {
                _matched_lengths[s] = 0;
                return -1;
            }
            const QStringRef context(&text, p0, npn - p0);
            _match = _substrings_rex.at(s - _substring_txt_count).match(context);
            _matched_lengths[s] = _match.capturedLength();
#if QT_VERSION >= QT_VERSION_CHECK(5, 6, 0)
            return _match.hasMatch() ? _match.capturedStart() + p0 : -1;
#else
#warning[cb2Bib] Linking against older than Qt 5.6 might effect some Context searches
            return _match.hasMatch() ? _match.capturedStart() : -1;
#endif
        }
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
            const int pn(p0 + _matched_lengths.at(i));
            if (fp < pn)
                fp = pn;
        }
        // Beautify match by including word endings
        for (int l = fp; l < _pn; ++l)
            if (text.at(l).isLetter())
                ++fp;
            else
                break;
        _matched_length = fp - bp;
        return bp;
    }

    QString _signature_string;
    QStringList _subpatterns;
    QVector<QRegularExpression> _substrings_rex;
    QVector<txtmatcher> _substrings_txt;
    int _hook;
    int _stretch;
    int _substring_count;
    int _substring_rex_count;
    int _substring_txt_count;
    mutable QRegularExpressionMatch _match;
    mutable QVector<int> _matched_lengths;
    mutable QVector<int> _sp0;
    mutable int _matched_length;
    mutable int _p0;
    mutable int _pn;
};

#endif
