/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bNetworkQuery.h"

#include "c2b.h"

#include <QMessageBox>


c2bNetworkQuery::c2bNetworkQuery(bibParser* bp, QObject* parento) : networkQuery(bp, parento) {}

c2bNetworkQuery::c2bNetworkQuery(bibParser* bp, network* net, QObject* parento) : networkQuery(bp, net, parento) {}

c2bNetworkQuery::~c2bNetworkQuery() {}


bool c2bNetworkQuery::checkQueryFile(const QString& fn) const
{
    if (fn.isEmpty())
    {
        QMessageBox::information(c2b::mainWidget(), tr("Information - cb2Bib"),
                                 tr("No Network Query file has been specified.\n\n"
                                    "Note: Network Query files are specified through the cb2Bib Configure dialog."),
                                 QMessageBox::Ok);
        return false;
    }
    QFile file(fn);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(c2b::mainWidget(), tr("Warning - cb2Bib"),
                             tr("Unable to open the Network Query file %1 for reading.\nError: '%2'.\n\n"
                                "Note: Network Query files are specified through the cb2Bib Configure dialog.")
                             .arg(fn, file.errorString()),
                             QMessageBox::Ok);
        return false;
    }
    return true;
}
