/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "triads.h"

#include "cb2bib_utilities.h"

#include <QHash>


const QString triads::textSignature(const QString& str)
{
    if (str.isEmpty())
        return QString();
    else
        return asciiTextSignature(c2bUtils::toAscii(str, c2bUtils::KeepWords));
}

const QVector<QString> triads::textSignature(const QStringList& strs)
{
    QVector<QString> s(strs.count());
    for (int i = 0; i < strs.count(); ++i)
        s[i] = textSignature(strs.at(i));
    return s;
}

const QString triads::asciiTextSignature(const QString& str)
{
    QString s(str);
    s.replace(c2bUtils::nonAsciiLetter, " ");
    s = s.toLower();

    const int nletters(26);
    const int ngram(5);
    const int slength(s.length());
    const int code0(QChar('a').unicode());
    const QChar space(' ');

    QSet<int> triads;
    for (int i = 0; i <= slength - ngram; ++i)
    {
        if (s.midRef(i, ngram).contains(space))
            continue;
        const int t1(s.at(i).unicode() - code0);
        const int t2(s.at(i + 2).unicode() - code0);
        const int t3(s.at(i + 4).unicode() - code0);
        const int code(code0 + t1 * nletters * nletters + t2 * nletters + t3);
        if (!triads.contains(code))
            triads.insert(code);
    }
    QList<int> codes(triads.toList());
    std::sort(codes.begin(), codes.end());
    s.resize(codes.count());
    for (int i = 0; i < codes.count(); ++i)
        s[i] = QChar(codes.at(i));
    return s;
}

int triads::textFrequency(const QString& str)
{
    const QString sign(textSignature(str));
    if (sign.length() == 0)
        return 1000 - str.length();
    else
        return _rank(str, sign, c2bUtils::fileToString(":txt/txt/triads.txt"));
}

const QVector<int> triads::textFrequency(const QStringList& strs)
{
    if (strs.count() == 0)
        return QVector<int>();
    const QString ranks(c2bUtils::fileToString(":txt/txt/triads.txt"));
    QVector<int> fr(strs.count());
    for (int i = 0; i < strs.count(); ++i)
    {
        const QString sign(textSignature(strs.at(i)));
        if (sign.length() == 0)
            fr[i] = 1000 - strs.at(i).length();
        else
            fr[i] = _rank(strs.at(i), sign, ranks);
    }
    return fr;
}

int triads::_rank(const QString& str, const QString& sign, const QString& ranks)
{
    const int m(sign.length());
    const int n(ranks.length());
    int counter(0);
    int j0(0);
    for (int i = 0; i < m; ++i)
        for (int j = j0; j < n; ++j)
            if (sign.at(i) == ranks.at(j))
            {
                ++counter;
                j0 = j + 1;
                break;
            }
    counter = 100 * (m - counter) + str.length();
    return 1000 - counter;
}
