/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef TXTMATCHER_H
#define TXTMATCHER_H

#if defined(__AVX2__)
#define C2B_USE_TXTMATCHER_AVX2 1
#elif defined(__SSE2__)
#define C2B_USE_TXTMATCHER_SSE2 1
#else
#define C2B_USE_TXTMATCHER_SCALAR 1
#endif

#include <QString>


class txtmatcher
{

public:
    txtmatcher();
    explicit txtmatcher(const QString& spattern, const Qt::CaseSensitivity cs = Qt::CaseSensitive,
                        const int chook = -1);
    inline ~txtmatcher() {}


    void setPattern(const QString& spattern, const Qt::CaseSensitivity cs = Qt::CaseSensitive, const int chook = -1);
    inline const QString& pattern() const
    {
        return _pattern;
    }
    inline int frequency() const
    {
        return _frequency;
    }
    inline int indexIn(const QString& text, const int from = 0) const
    {
        return indexIn(text.unicode(), text.size(), from);
    }
    int indexIn(const QChar* const text, const int length, const int from) const;


private:
    int _find_case_insensitive(const ushort* const t, const int length, const int from) const;
    int _find_case_sensitive(const ushort* const t, const int length, const int from) const;
#ifdef C2B_USE_TXTMATCHER_SSE2
    int _find_case_insensitive_sse2(const ushort* const t, const int length, const int from) const;
    int _find_case_sensitive_sse2(const ushort* const t, const int length, const int from) const;
#endif
#ifdef C2B_USE_TXTMATCHER_AVX2
    int _find_case_insensitive_avx2(const ushort* const t, const int length, const int from) const;
    int _find_case_sensitive_avx2(const ushort* const t, const int length, const int from) const;
#endif
    void _set_lowest_frequency_character(const QString& spattern, const bool cs);

    QString _padded_pattern;
    QString _pattern;

    QString _lcp;
    QString _ucp;

    bool _case_sensitive;
    int _chook;
    int _frequency;
};

#endif
