/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef TRIADS_H
#define TRIADS_H


#include <QStringList>


class triads
{

public:
    static const QString asciiTextSignature(const QString& str);
    static const QString textSignature(const QString& str);
    static const QVector<QString> textSignature(const QStringList& strs);

    static const QVector<int> textFrequency(const QStringList& strs);
    static int textFrequency(const QString& str);


private:
    inline triads() {}
    inline ~triads() {}


    static int _rank(const QString& str, const QString& sign, const QString& ranks);
};

#endif
