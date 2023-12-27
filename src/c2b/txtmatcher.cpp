/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "txtmatcher.h"

#ifdef C2B_USE_TXTMATCHER_AVX2
#include <immintrin.h>
#endif
#ifdef C2B_USE_TXTMATCHER_SSE2
#include <emmintrin.h>
#endif

static const double _upper_case_letter_frequency[] =
{
    //  A          B          C          D          E          F          G          H          I
    0.0461215, 0.0219791, 0.0542205, 0.0247118, 0.0243137, 0.0249272, 0.0155418, 0.0318637, 0.0319445,
    //  J          K          L          M          N          O          P          Q          R
    0.0185178, 0.0110203, 0.0211695, 0.0345829, 0.0251332, 0.0222969, 0.0335058, 0.0034723, 0.0278396,
    //  S          T          U          V          W          X          Y          Z
    0.0433791, 0.0483445, 0.0070459, 0.0108463, 0.0114125, 0.0053894, 0.0057301, 0.0039877
};
static const double _lower_case_letter_frequency[] =
{
    //  a          b          c          d          e          f          g          h          i
    0.6139480, 0.1124940, 0.3052070, 0.2845240, 0.9756860, 0.1816290, 0.1361380, 0.3223960, 0.6192860,
    //  j          k          l          m          n          o          p          q          r
    0.0084664, 0.0315632, 0.3386540, 0.2145900, 0.5768830, 0.5937770, 0.1803630, 0.0162243, 0.5046140,
    //  s          t          u          v          w          x          y          z
    0.4905200, 0.6968060, 0.2104950, 0.0785456, 0.0858753, 0.0380061, 0.1229070, 0.0193867
};


/**
   Specialized substring search for English texts

*/
txtmatcher::txtmatcher() : _case_sensitive(true), _chook(-1), _frequency(10000) {}

txtmatcher::txtmatcher(const QString& spattern, const Qt::CaseSensitivity cs, const int chook)
{
    setPattern(spattern, cs, chook);
}


void txtmatcher::setPattern(const QString& spattern, const Qt::CaseSensitivity cs, const int chook)
{
    _pattern = spattern;
    _case_sensitive = cs == Qt::CaseSensitive;
    const int m(_pattern.size());
#ifdef C2B_USE_TXTMATCHER_SCALAR
    _padded_pattern = _pattern;
#else
#ifdef C2B_USE_TXTMATCHER_SSE2
    _padded_pattern.fill(QChar(65535), std::max(m, 8));
#endif
#ifdef C2B_USE_TXTMATCHER_AVX2
    _padded_pattern.fill(QChar(65535), std::max(m, 16));
#endif
    for (int i = 0; i < m; ++i)
        _padded_pattern[i] = _pattern.at(i);
#endif
    if (_case_sensitive)
    {
        _lcp.clear();
        _ucp.clear();
    }
    else
    {
        // Safe character case folding
        _lcp = _padded_pattern;
        for (int i = 0; i < m; ++i)
            _lcp[i] = _padded_pattern.at(i).toLower();
        _ucp = _padded_pattern;
        for (int i = 0; i < m; ++i)
            _ucp[i] = _padded_pattern.at(i).toUpper();
    }
    if (chook < 0 || chook >= m)
        _set_lowest_frequency_character(_pattern, _case_sensitive);
    else
    {
        _chook = chook;
        _frequency = 0;
    }
}

int txtmatcher::indexIn(const QChar* const text, const int length, const int from) const
{
    if (from + _pattern.size() > length)
        return -1;
    if (_pattern.size() == 0) // Convention
        return from;
#ifdef C2B_USE_TXTMATCHER_SCALAR
    if (_case_sensitive)
        return _find_case_sensitive(reinterpret_cast<const ushort*>(text), length, from);
    else
        return _find_case_insensitive(reinterpret_cast<const ushort*>(text), length, from);
#endif
#ifdef C2B_USE_TXTMATCHER_SSE2
    if (_pattern.size() > 8 || length - from < 5 * 8)
    {
        if (_case_sensitive)
            return _find_case_sensitive(reinterpret_cast<const ushort*>(text), length, from);
        else
            return _find_case_insensitive(reinterpret_cast<const ushort*>(text), length, from);
    }
    else
    {
        if (_case_sensitive)
            return _find_case_sensitive_sse2(reinterpret_cast<const ushort*>(text), length, from);
        else
            return _find_case_insensitive_sse2(reinterpret_cast<const ushort*>(text), length, from);
    }
#endif
#ifdef C2B_USE_TXTMATCHER_AVX2
    if (_pattern.size() > 16 || length - from < 5 * 16)
    {
        if (_case_sensitive)
            return _find_case_sensitive(reinterpret_cast<const ushort*>(text), length, from);
        else
            return _find_case_insensitive(reinterpret_cast<const ushort*>(text), length, from);
    }
    else
    {
        if (_case_sensitive)
            return _find_case_sensitive_avx2(reinterpret_cast<const ushort*>(text), length, from);
        else
            return _find_case_insensitive_avx2(reinterpret_cast<const ushort*>(text), length, from);
    }
#endif
}

void txtmatcher::_set_lowest_frequency_character(const QString& spattern, const bool cs)
{
    const int n(spattern.length());
    int lfc(-1);
    double lf(2);
    if (cs)
        for (int l = 0; l < n; ++l)
        {
            const ushort lcs(spattern.at(l).unicode());
            double cf(0);
            if (lcs > 96 && lcs < 123)
                cf = _lower_case_letter_frequency[lcs - 97];
            else if (lcs > 64 && lcs < 91)
                cf = _upper_case_letter_frequency[lcs - 65];
            if (cf < lf)
            {
                lf = cf;
                lfc = l;
            }
        }
    else
        for (int l = 0; l < n; ++l)
        {
            const ushort lcu(spattern.at(l).toLower().unicode());
            double cf(0);
            if (lcu > 96 && lcu < 123)
                cf = _lower_case_letter_frequency[lcu - 97] + _upper_case_letter_frequency[lcu - 97];
            if (cf < lf)
            {
                lf = cf;
                lfc = l;
            }
        }
    _chook = lfc;
    _frequency = 1 + int(1000 * lf);
}

int txtmatcher::_find_case_sensitive(const ushort* const t, const int length, const int from) const
{
    const int sp(_pattern.size());
    const int ch(_chook);
    const ushort* const p(reinterpret_cast<const ushort*>(_pattern.unicode()));
    const ushort pch(p[ch]);
    const int a(from + ch), b(length - sp + ch + 1);

    for (int i = a; i < b; ++i)
        if (t[i] == pch)
        {
            for (int j = 0; j < sp; ++j)
                if (t[i - ch + j] != p[j])
                    goto next;
            return i - ch;
next:
            continue;
        }
    return -1;
}

int txtmatcher::_find_case_insensitive(const ushort* const t, const int length, const int from) const
{
    const int sp(_pattern.size());
    const int ch(_chook);
    const ushort* const lp(reinterpret_cast<const ushort*>(_lcp.unicode()));
    const ushort* const up(reinterpret_cast<const ushort*>(_ucp.unicode()));
    const ushort lpch(lp[ch]);
    const ushort upch(up[ch]);
    const int a(from + ch), b(length - sp + ch + 1);

    for (int i = a; i < b; ++i)
        if (t[i] == lpch || t[i] == upch)
        {
            for (int j = 0; j < sp; ++j)
                if (t[i - ch + j] != lp[j] && t[i - ch + j] != up[j])
                    goto next;
            return i - ch;
next:
            continue;
        }
    return -1;
}

/*
   SIMD implementations for _find_case_sensitive and _find_case_insensitive

   Optimizes short substring pattern matching (words and stemmed words) required
   in context and approximate searches

   The _find_case_sensitive and _find_case_insensitive routines use effective
   skipping provided by lowest frequency letters



   See B Smyth, Computing Patterns in Strings (2003), chapter 8, for a review on
   search techniques and letter frequency specialization

   See W Muła, SIMD-friendly algorithms for substring searching (2016), for
   generic SIMD implementations

*/
#ifdef C2B_USE_TXTMATCHER_SSE2
static const uint16_t _zpattern_sse2[] = { 0x0, 0x3, 0xf, 0x3f, 0xff, 0x3ff, 0xfff, 0x3fff, 0xffff };

int txtmatcher::_find_case_sensitive_sse2(const ushort* const t, const int length, const int from) const
{
    const int sp(_pattern.size());
    const int ch(_chook);
    const ushort* const p(reinterpret_cast<const ushort*>(_padded_pattern.unicode()));
    const ushort pch(p[ch]);
    const uint16_t zpattern(_zpattern_sse2[sp]);

    const __m128i ppattern(_mm_loadu_si128(reinterpret_cast<const __m128i*>(p)));
    const __m128i spattern(_mm_set1_epi16(pch));

    const int tposition(length - 8 - 7 + 1);
    int cposition(from + ch);

    while (cposition < tposition)
    {
        __m128i text(_mm_loadu_si128(reinterpret_cast<const __m128i*>(t + cposition)));
        const uint16_t zsp(_mm_movemask_epi8(_mm_cmpeq_epi16(text, spattern)));
        if (zsp == uint16_t(0))
            cposition += 8;
        else
        {
            const int ctz(__builtin_ctz(zsp) / 2);
            cposition += ctz;
            text = _mm_loadu_si128(reinterpret_cast<const __m128i*>(t + cposition - ch));
            const uint16_t zp(_mm_movemask_epi8(_mm_cmpeq_epi16(text, ppattern)));
            if (zp == zpattern)
                return cposition - ch;
            ++cposition;
        }
    }
    for (int i = cposition; i < length - sp + ch + 1; ++i)
        if (t[i] == pch)
        {
            for (int j = 0; j < sp; ++j)
                if (t[i - ch + j] != p[j])
                    goto next;
            return i - ch;
next:
            continue;
        }
    return -1;
}

int txtmatcher::_find_case_insensitive_sse2(const ushort* const t, const int length, const int from) const
{
    const int sp(_pattern.size());
    const int ch(_chook);
    const ushort* const lp(reinterpret_cast<const ushort*>(_lcp.unicode()));
    const ushort* const up(reinterpret_cast<const ushort*>(_ucp.unicode()));
    const ushort lpch(lp[ch]);
    const ushort upch(up[ch]);
    const uint16_t zpattern(_zpattern_sse2[sp]);

    const __m128i lcpattern(_mm_loadu_si128(reinterpret_cast<const __m128i*>(lp)));
    const __m128i ucpattern(_mm_loadu_si128(reinterpret_cast<const __m128i*>(up)));
    const __m128i lspattern(_mm_set1_epi16(lpch));
    const __m128i uspattern(_mm_set1_epi16(upch));

    const int tposition(length - 8 - 7 + 1);
    int cposition(from + ch);

    while (cposition < tposition)
    {
        __m128i text(_mm_loadu_si128(reinterpret_cast<const __m128i*>(t + cposition)));
        const uint16_t zlsp(_mm_movemask_epi8(_mm_cmpeq_epi16(text, lspattern)));
        const uint16_t zusp(_mm_movemask_epi8(_mm_cmpeq_epi16(text, uspattern)));
        const uint16_t zsp(zlsp | zusp);
        if (zsp == uint16_t(0))
            cposition += 8;
        else
        {
            const int ctz(__builtin_ctz(zsp) / 2);
            cposition += ctz;
            text = _mm_loadu_si128(reinterpret_cast<const __m128i*>(t + cposition - ch));
            const uint16_t zlp(_mm_movemask_epi8(_mm_cmpeq_epi16(text, lcpattern)));
            const uint16_t zup(_mm_movemask_epi8(_mm_cmpeq_epi16(text, ucpattern)));
            const uint16_t zp(zlp | zup);
            if (zp == zpattern)
                return cposition - ch;
            ++cposition;
        }
    }
    for (int i = cposition; i < length - sp + ch + 1; ++i)
        if (t[i] == lpch || t[i] == upch)
        {
            for (int j = 0; j < sp; ++j)
                if (t[i - ch + j] != lp[j] && t[i - ch + j] != up[j])
                    goto next;
            return i - ch;
next:
            continue;
        }
    return -1;
}
#endif

#ifdef C2B_USE_TXTMATCHER_AVX2
static const uint32_t _zpattern_avx2[] = { 0x0,      0x3,       0xf,       0x3f,       0xff,      0x3ff,
                                           0xfff,    0x3fff,    0xffff,    0x3ffff,    0xfffff,   0x3fffff,
                                           0xffffff, 0x3ffffff, 0xfffffff, 0x3fffffff, 0xffffffff
                                         };

int txtmatcher::_find_case_sensitive_avx2(const ushort* const t, const int length, const int from) const
{
    const int sp(_pattern.size());
    const int ch(_chook);
    const ushort* const p(reinterpret_cast<const ushort*>(_padded_pattern.unicode()));
    const ushort pch(p[ch]);
    const uint32_t zpattern(_zpattern_avx2[sp]);

    const __m256i ppattern(_mm256_loadu_si256(reinterpret_cast<const __m256i*>(p)));
    const __m256i spattern(_mm256_set1_epi16(pch));

    const int tposition(length - 16 - 15 + 1);
    int cposition(from + ch);

    while (cposition < tposition)
    {
        __m256i text(_mm256_loadu_si256(reinterpret_cast<const __m256i*>(t + cposition)));
        const uint32_t zsp(_mm256_movemask_epi8(_mm256_cmpeq_epi16(text, spattern)));
        if (zsp == uint32_t(0))
            cposition += 16;
        else
        {
            const int ctz(__builtin_ctz(zsp) / 2);
            cposition += ctz;
            text = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(t + cposition - ch));
            const uint32_t zp(_mm256_movemask_epi8(_mm256_cmpeq_epi16(text, ppattern)));
            if (zp == zpattern)
                return cposition - ch;
            ++cposition;
        }
    }
    for (int i = cposition; i < length - sp + ch + 1; ++i)
        if (t[i] == pch)
        {
            for (int j = 0; j < sp; ++j)
                if (t[i - ch + j] != p[j])
                    goto next;
            return i - ch;
next:
            continue;
        }
    return -1;
}

int txtmatcher::_find_case_insensitive_avx2(const ushort* const t, const int length, const int from) const
{
    const int sp(_pattern.size());
    const int ch(_chook);
    const ushort* const lp(reinterpret_cast<const ushort*>(_lcp.unicode()));
    const ushort* const up(reinterpret_cast<const ushort*>(_ucp.unicode()));
    const ushort lpch(lp[ch]);
    const ushort upch(up[ch]);
    const uint32_t zpattern(_zpattern_avx2[sp]);

    const __m256i lcpattern(_mm256_loadu_si256(reinterpret_cast<const __m256i*>(lp)));
    const __m256i ucpattern(_mm256_loadu_si256(reinterpret_cast<const __m256i*>(up)));
    const __m256i lspattern(_mm256_set1_epi16(lpch));
    const __m256i uspattern(_mm256_set1_epi16(upch));

    const int tposition(length - 16 - 15 + 1);
    int cposition(from + ch);

    while (cposition < tposition)
    {
        __m256i text(_mm256_loadu_si256(reinterpret_cast<const __m256i*>(t + cposition)));
        const uint32_t zlsp(_mm256_movemask_epi8(_mm256_cmpeq_epi16(text, lspattern)));
        const uint32_t zusp(_mm256_movemask_epi8(_mm256_cmpeq_epi16(text, uspattern)));
        const uint32_t zsp(zlsp | zusp);
        if (zsp == uint32_t(0))
            cposition += 16;
        else
        {
            const int ctz(__builtin_ctz(zsp) / 2);
            cposition += ctz;
            text = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(t + cposition - ch));
            const uint32_t zlp(_mm256_movemask_epi8(_mm256_cmpeq_epi16(text, lcpattern)));
            const uint32_t zup(_mm256_movemask_epi8(_mm256_cmpeq_epi16(text, ucpattern)));
            const uint32_t zp(zlp | zup);
            if (zp == zpattern)
                return cposition - ch;
            ++cposition;
        }
    }
    for (int i = cposition; i < length - sp + ch + 1; ++i)
        if (t[i] == lpch || t[i] == upch)
        {
            for (int j = 0; j < sp; ++j)
                if (t[i - ch + j] != lp[j] && t[i - ch + j] != up[j])
                    goto next;
            return i - ch;
next:
            continue;
        }
    return -1;
}
#endif
