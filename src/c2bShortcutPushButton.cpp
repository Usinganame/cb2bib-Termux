/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bShortcutPushButton.h"

#include <QKeyEvent>


void c2bShortcutPushButton::setKeysequence(const QKeySequence& ks)
{
    _keysequence = ks;
    const QString bt(_keysequence.toString(QKeySequence::NativeText));
    setText(bt.isEmpty() ? tr("None") : bt);
    setChecked(false);
}

void c2bShortcutPushButton::clear()
{
    _set_keysequence(QKeySequence());
}

void c2bShortcutPushButton::reset()
{
    _set_keysequence(_default_keysequence);
}

void c2bShortcutPushButton::keyPressEvent(QKeyEvent* qevent)
{
    const int k(qevent->key());
    // This function is based on GPL configdialog.cpp
    // Copyright (C) 2003-2007 by Pascal Brachet, http://www.xm1math.net/texmaker/
    if ((qevent->modifiers() != 0 && k != Qt::Key_Enter && k != Qt::Key_Alt && k != Qt::Key_Shift &&
         k != Qt::Key_Control && k != Qt::Key_AltGr && k != Qt::Key_Meta && k != 0 && k != Qt::Key_Super_L &&
         k != Qt::Key_Super_R) ||
        (k >= Qt::Key_F1 && k <= Qt::Key_F35))
    {
        _set_keysequence(QKeySequence(qevent->modifiers() | k));
        return;
    }
    QPushButton::keyPressEvent(qevent);
}
