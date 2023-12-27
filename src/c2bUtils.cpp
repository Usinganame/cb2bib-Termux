/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bUtils.h"

#include <QDesktopServices>
#include <QMessageBox>


namespace c2bUtils
{

bool openFile(const QString& fn, QWidget* w)
{
    // URL fn is decoded always, in the hope of making openFile encoding agnostic
    const QString decoded(QUrl::fromPercentEncoding(fn.toUtf8()));
    const QUrl url(stringToUrl(decoded));
    if (!url.isValid())
    {
        if (w)
            QMessageBox::warning(w, QObject::tr("Warning - cb2Bib"),
                                 QObject::tr("Unable to open file.\nError: URL '%1' is not valid.").arg(url.toString()),
                                 QMessageBox::Ok);
        return false;
    }
    if (!QDesktopServices::openUrl(url))
    {
        if (w)
            QMessageBox::warning(w, QObject::tr("Warning - cb2Bib"), QObject::tr("Unable to open file '%1'.").arg(fn),
                                 QMessageBox::Ok);
        return false;
    }
    return true;
}

} // namespace c2bUtils
