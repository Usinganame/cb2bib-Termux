/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef SEARCHPATTERN_H
#define SEARCHPATTERN_H

#include "approximatePattern.h"
#include "documentContents.h"
#include "scorer.h"
#include "stemMatcher.h"
#include "wordMatcher.h"
#include "wordPattern.h"

#include <QRegularExpression>


class searchPattern
{

public:
    searchPattern(const QString& pattern, const QString& patternType);
    searchPattern(const bool NOT, const bool caseSensitive, const QString& patternType, const QString& scope,
                  const QChar& yearScope, const QString& pattern);
    inline ~searchPattern() {}

    enum Type
    {
        ApproximateString = 1,
        Context = 2,
        FixedStringAllWords = 3,
        FixedStringAnyWord = 4,
        FixedStringContext = 5,
        FixedString = 6,
        RegularExpression = 7,
        Wildcard = 8
    };
    static const QString type(const Type t);
    static const QStringList types();

    struct modifiers
    {
        QChar yearScope;
        QString scope;
        QString string;
        bool NOT;
    };

    inline const modifiers& modifier() const
    {
        return _modifier;
    }
    inline bool matches(const QString& contents) const
    {
        return _matcher.match(contents);
    }
    inline bool matches(const documentContents& contents) const
    {
        return _matcher.match(contents);
    }
    inline int indexIn(const QString& contents, const int from) const
    {
        return _matcher.index(contents, from);
    }
    inline int indexIn(const documentContents& contents, const int from) const
    {
        return _matcher.index(contents.text(), from);
    }
    inline int matchedLength() const
    {
        return _matcher.length;
    }
    inline void initializeScores() const
    {
        _scorer.initialize();
    }
    inline void updateScore() const
    {
        _scorer.update(_matcher.plength, _matcher.length);
    }
    inline int matchedCounter() const
    {
        return _scorer.nscores;
    }
    inline double matchedScore() const
    {
        return _scorer.score();
    }
    inline const QString toString() const
    {
        return _formatted_string;
    }
    inline bool operator<(const searchPattern& p) const
    {
        return (_rank < p._rank);
    }


private:
    struct matcher
    {
        matcher(const QString& pattern, const Type t, const Qt::CaseSensitivity cs);

        QRegularExpression regexp;
        QString signature;
        QString typedpattern;
        QStringMatcher strexp;
        QVector<QString> subsignatures;
        Qt::CaseSensitivity csensitivity;
        Type type;
        approximatePattern appexp;
        int plength;
        mutable QRegularExpressionMatch regexp_match;
        mutable int length;
        stemMatcher cstemexp;
        wordMatcher cwordexp;
        wordPattern wordexp;

        bool match(const QString& contents) const;
        bool match(const documentContents& contents) const;
        int index(const QString& contents, const int from) const;

        static QString _wildcard_escaped(const QString& pattern);
        void _set_typed_pattern(const QString& pattern);

        static inline bool _match_signature(const QString& ps, const QString& cs)
        {
            const int pl(ps.length()); // Always pl > 0
            const int cl(cs.length());
            const ushort* ups(reinterpret_cast<const ushort*>(ps.unicode()));
            const ushort* p(ups);
            const ushort* pn(ups + pl);
            const ushort* ucs(reinterpret_cast<const ushort*>(cs.unicode()));
            const ushort* c(ucs - 1);
            const ushort* cn(ucs + cl);
            while (++c != cn)
                if (*c == *p)
                    if (++p == pn)
                        return true;
            return false;
        }
        static inline bool _match(const QRegularExpression& submatcher, const QString& psignature,
                                  const documentContents& contents)
        {
#ifdef C2B_DEBUG_SEARCHING_SKIP_SIGNATURE
            return submatcher.match(contents.text()).hasMatch();
#else
            // Skip signature check for patterns that do not define it
            if (psignature.length() == 0 || _match_signature(psignature, contents.signature()))
                return submatcher.match(contents.text()).hasMatch();
            else
                return false;
#endif
        }
        template <typename T>
        static inline bool _match(const T& submatcher, const QString& psignature, const documentContents& contents)
        {
#ifdef C2B_DEBUG_SEARCHING_SKIP_SIGNATURE
            return submatcher.indexIn(contents.text()) != -1;
#else
            // Skip signature check for patterns that do not define it
            if (psignature.length() == 0 || _match_signature(psignature, contents.signature()))
                return submatcher.indexIn(contents.text()) != -1;
            else
                return false;
#endif
        }
        template <typename T>
        inline bool _match_all(const int n, const T& submatchers, const documentContents& contents) const
        {
            for (int i = n - 1; i >= 0; --i)
                if (!_match(submatchers.at(i), subsignatures.at(i), contents))
                    return false;
            return true;
        }
        template <typename T>
        inline bool _match_any(const int n, const T& submatchers, const documentContents& contents) const
        {
            for (int i = 0; i < n; ++i)
                if (_match(submatchers.at(i), subsignatures.at(i), contents))
                    return true;
            return false;
        }
    };

    static const QMap<QString, searchPattern::Type> typemap();
    static inline Qt::CaseSensitivity qtcase(bool caseSensitive)
    {
        return caseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive;
    }

    QString _formatted_string;
    int _rank;
    matcher _matcher;
    modifiers _modifier;
    mutable scorer _scorer;
};

#endif
