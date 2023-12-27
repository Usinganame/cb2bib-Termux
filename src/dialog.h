/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef DIALOG_H
#define DIALOG_H

#include <Qt>


/**
    Remove What's This button from c2b dialogues
*/
namespace dialog
{

static const Qt::WindowFlags flags(Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

} // namespace dialog

#endif
