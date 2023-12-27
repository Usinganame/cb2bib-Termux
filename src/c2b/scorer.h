/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef SCORER_H
#define SCORER_H

#include <QList>

#ifdef C2B_DEBUG_SEARCHING
#include <QtDebug>
#endif

struct scorer
{
    scorer() : tscore(0), nscores(0) {}

    void initialize()
    {
        tscore = double(0);
        nscores = 0;
    }
    void update(const int plength, const int length)
    {
        const double s(plength == 0 ? double(1) : double(1) / (double(1) + std::abs(length - plength)));
        tscore += s;
        ++nscores;
    }
    double score() const
    {
#ifdef C2B_DEBUG_SEARCHING
        qDebug() << "scorer: n score" << nscores << tscore;
#endif
        return tscore;
    }

    double tscore;
    int nscores;
};

#endif
