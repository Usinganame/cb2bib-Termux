/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef AUTHORSTRING_H
#define AUTHORSTRING_H

#include "cb2bib_utilities.h"

#include <QRegExp>
#include <QString>
#include <QStringList>


namespace author
{

struct unifier
{
    unifier();

    QString& unifyNames(QString& author) const;

    QString& simplifyString(QString& author, const bool full = false) const;
    QString fromMedline(const QString& author) const;

    const QString name;
    const QString initials;

    const QString double_initials;
    const QString prefixes;

    const QString reversed_romance_name;

    const QRegExp reversed_name_rx;
    const QRegExp reversed_romance_name_rx;

    const QRegExp unifier_rx1;
    const QRegExp unifier_rx2;
    const QRegExp unifier_rx3;
    const QRegExp unifier_rx4;
    const QRegExp unifier_rx5;
    const QRegExp unifier_rx6;
    const QRegExp unifier_rx7;

    const QRegExp simplify_string_rx1;
    const QRegExp simplify_string_rx2;
    const QRegExp simplify_string_rx3;
    const QRegExp simplify_string_rx4;
    const QRegExp simplify_string_rx5;
    const QRegExp simplify_string_rx6;
    const QRegExp simplify_string_rx7;
};

/**
    Implementation of author field extraction
    P. Constans. A Simple Extraction Procedure for Bibliographical Author Field.
    arXiv:0902.0755, 2009.
*/
struct encoder
{
    encoder() {}
    explicit encoder(const QString& str)
    {
        encode(str);
    }
    QString code;
    QString decoded(const int position, const int length) const;
    QStringList fragments;
    unifier aunifier;
    void clear()
    {
        code.clear();
        fragments.clear();
    }
    void encode(const QString& raw);
    void scape(const int pos, const int length, const QChar c = QChar(' '))
    {
        const int pos0(std::max(pos, 0));
        const int posn(std::min(pos0 + length, code.length()));
        for (int i = pos0; i < posn; ++i)
            if (code.at(i) != 'L')
                code[i] = c;
    }
    void scapePattern(const QString& pattern, const QChar c = QChar(' '))
    {
        QRegExp rx(pattern, Qt::CaseSensitive);
        rx.setMinimal(true);
        rx.setPatternSyntax(QRegExp::RegExp2);
        if (!rx.isValid())
            exit(6);
        int pos(0);
        while (pos > -1)
        {
            pos = rx.indexIn(code, pos);
            if (pos > -1)
            {
                scape(pos, rx.matchedLength(), c);
                pos += rx.matchedLength();
            }
        }
    }
    static inline bool hasUpper(const QString& str)
    {
        for (int i = 0; i < str.length(); i++)
            if (str.at(i).isLetter())
                if (str.at(i).category() == QChar::Letter_Uppercase)
                    return true;
        return false;
    }
    static inline bool isCapitalName(const QString& w)
    {
        return c2bUtils::isUpperCaseString(w, std::max(0, w.lastIndexOf('_', -5))); // Skip prefixes and suffixes
    }
    static inline bool isSeparator(const QString& w)
    {
        return (w == "and") || (w == "&");
    }
    static bool isAdparticle(const QString& w);
    static bool isInitial(const QString& w);
    static bool isName(const QString& w);
    static bool isPlainWord(const QString& w);
};

} // namespace author


class authorString
{

public:
    authorString();
    inline ~authorString() {}

    QString toBibTeX(const QString& author, bool full_form = false);
    inline QString fromMedline(const QString& author) const
    {
        return au.fromMedline(author);
    }
    inline const QString& prefixes() const
    {
        return au.prefixes;
    }


private:
    QString capitalize(const QString& name) const;
    QString processFirstMiddle(const QString& first_middle) const;
    bool containLowerCaseLetter(const QString& author) const;
    bool isReverseOrder(const QString& author) const;
    static bool containUpperCaseLetter(const QString& author);

    QString _author_string;
    author::unifier au;
    bool _full_form;
};

#endif
