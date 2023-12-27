/***************************************************************************
 *   clipboardPoll, modified by Pere Constans for cb2Bib, 2005
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *
 *
 *   Author and Copyright (C) 2003 by Lubos Lunak <l.lunak@kde.org>
 *   Distributed under the GNU General Public License
 *
 *
 *   This file is part of the KDE project
 *   Copyright (C) 2003 by Lubos Lunak <l.lunak@kde.org>
 *
 *   This program is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU General Public
 *   License as published by the Free Software Foundation; either
 *   version 2 of the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; see the file COPYING.  If not, write to
 *   the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 *   Boston, MA 02111-1307, USA.
 ***************************************************************************/
#include "clipboardPoll.h"


#include <QClipboard>
#include <QX11Info>
#include <X11/Xatom.h>


/*

 The polling magic:

 There's no way with X11 how to find out if the selection has changed (unless
its ownership is taken away from the current client). In the future, there will
be hopefully such notification, which will make this whole file more or less
obsolete. But for now, Klipper has to poll. In order to avoid transferring all
the data on every time pulse, this file implements two optimizations: The first
one is checking whether the selection owner is Qt application (using the
_QT_SELECTION/CLIPBOARD_SENTINEL atoms on the root window of screen 0), and if
yes, Klipper can rely on QClipboard's signals. If the owner is not Qt app, and
the ownership has changed, it means the selection has changed as well.
Otherwise, first only the timestamp of the last selection change is requested
using the TIMESTAMP selection target, and if it's the same, it's assumed the
contents haven't changed. Note that some applications (like XEmacs) does not
provide this information, so Klipper has to assume that the clipboard might have
changed in this case --- this is what is meant by REFUSED below.

*/

clipboardPoll::clipboardPoll(QWidget* parentw) : QWidget(parentw)
{
    //     kapp->installX11EventFilter( this );
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));

    const char* names[6] = { "_QT_SELECTION_SENTINEL",      "_QT_CLIPBOARD_SENTINEL",     "CLIPBOARD", "TIMESTAMP",
                             "KLIPPER_SELECTION_TIMESTAMP", "KLIPPER_CLIPBOARD_TIMESTAMP"
                           };
    Atom atoms[6];
    XInternAtoms(QX11Info::display(), const_cast<char**>(names), 6, False, atoms);
    selection.sentinel_atom = atoms[0];
    clipboard.sentinel_atom = atoms[1];
    xa_clipboard = atoms[2];
    xa_timestamp = atoms[3];
    selection.timestamp_atom = atoms[4];
    clipboard.timestamp_atom = atoms[5];
    selection.atom = XA_PRIMARY;
    clipboard.atom = xa_clipboard;
    selection.last_change = clipboard.last_change = QX11Info::appTime(); // don't trigger right after startup
    selection.last_owner = XGetSelectionOwner(QX11Info::display(), XA_PRIMARY);
    clipboard.last_owner = XGetSelectionOwner(QX11Info::display(), xa_clipboard);
    selection.waiting_for_timestamp = false;
    clipboard.waiting_for_timestamp = false;
    updateQtOwnership(selection);
    updateQtOwnership(clipboard);
}

clipboardPoll::~clipboardPoll()
{
    delete timer;
}


bool clipboardPoll::x11Event(XEvent* e)
{
    // note that this is also installed as app-wide filter
    if (e->type == SelectionNotify && e->xselection.requestor == winId())
    {
        if (changedTimestamp(selection, *e))
        {
            emit clipboardChanged(true);
        }

        if (changedTimestamp(clipboard, *e))
        {
            emit clipboardChanged(false);
        }
        return true; // filter out
    }
    return false;
}

void clipboardPoll::updateQtOwnership(SelectionData& sData)
{
    Atom type;
    int format;
    unsigned long nitems;
    unsigned long after;
    unsigned char* prop = NULL;
    if (XGetWindowProperty(QX11Info::display(), QX11Info::appRootWindow(0), sData.sentinel_atom, 0, 2, False, XA_WINDOW,
                           &type, &format, &nitems, &after, &prop) != Success ||
        type != XA_WINDOW || format != 32 || nitems != 2 || prop == NULL)
    {
        sData.owner_is_qt = false;
        if (prop != NULL)
            XFree(prop);
        return;
    }
    Window owner = reinterpret_cast<long*>(prop)[0]; // [0] is new owner, [1] is previous
    XFree(prop);
    Window current_owner = XGetSelectionOwner(QX11Info::display(), sData.atom);
    sData.owner_is_qt = (owner == current_owner);
}

void clipboardPoll::timeout()
{
    //     KlipperWidget::updateTimestamp();
    if (!qApp->clipboard()->ownsSelection() && checkTimestamp(selection))
    {
        emit clipboardChanged(true);
    }
    if (!qApp->clipboard()->ownsClipboard() && checkTimestamp(clipboard))
    {
        emit clipboardChanged(false);
    }
}

bool clipboardPoll::checkTimestamp(SelectionData& sData)
{
    Window current_owner = XGetSelectionOwner(QX11Info::display(), sData.atom);
    updateQtOwnership(sData);
    if (sData.owner_is_qt)
    {
        sData.last_change = CurrentTime;
        sData.last_owner = current_owner;
        sData.waiting_for_timestamp = false;
        return false;
    }
    if (current_owner != sData.last_owner) // owner has changed
    {
        sData.last_owner = current_owner;
        sData.waiting_for_timestamp = false;
        sData.last_change = CurrentTime;
        return true;
    }
    if (current_owner == None)
    {
        return false; // None also last_owner...
    }
    if (sData.waiting_for_timestamp)
    {
        // We're already waiting for the timestamp of the last check
        return false;
    }
    XDeleteProperty(QX11Info::display(), winId(), sData.timestamp_atom);
    XConvertSelection(QX11Info::display(), sData.atom, xa_timestamp, sData.timestamp_atom, winId(),
                      QX11Info::appTime());
    sData.waiting_for_timestamp = true;
    sData.waiting_x_time = QX11Info::appTime();
    return false;
}

bool clipboardPoll::changedTimestamp(SelectionData& sData, const XEvent& ev)
{
    if (ev.xselection.requestor != winId() || ev.xselection.selection != sData.atom ||
        ev.xselection.time != sData.waiting_x_time)
    {
        return false;
    }
    sData.waiting_for_timestamp = false;
    if (ev.xselection.property == None)
    {
        return true;
    }
    Atom type;
    int format;
    unsigned long nitems;
    unsigned long after;
    unsigned char* prop = NULL;
    if (XGetWindowProperty(QX11Info::display(), winId(), ev.xselection.property, 0, 1, False, AnyPropertyType, &type,
                           &format, &nitems, &after, &prop) != Success ||
        format != 32 || nitems != 1 || prop == NULL)
    {
        if (prop != NULL)
            XFree(prop);
        return true;
    }
    Time timestamp = reinterpret_cast<long*>(prop)[0];
    XFree(prop);
    if (timestamp != sData.last_change || timestamp == CurrentTime)
    {
        sData.last_change = timestamp;
        return true;
    }
    return false; // ok, same timestamp
}
