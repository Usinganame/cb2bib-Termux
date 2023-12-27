/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BNETWORKQUERY_H
#define C2BNETWORKQUERY_H

#include "c2bUtils.h"

#include <networkQuery.h>


class c2bNetworkQuery : public networkQuery
{

    Q_OBJECT

public:
    explicit c2bNetworkQuery(bibParser* bp, QObject* parento = 0);
    c2bNetworkQuery(bibParser* bp, network* net, QObject* parento = 0);
    ~c2bNetworkQuery();


protected:
    bool checkQueryFile(const QString& fn) const override;
    inline QString fromHtmlString(const QString& str, const bool addMetadata = false) const override
    {
        return c2bUtils::fromHtmlString(str, addMetadata);
    }
    bool openFile(const QString& fn) const override
    {
        return c2bUtils::openFile(fn);
    }
};

#endif
