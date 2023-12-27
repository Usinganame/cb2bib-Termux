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
#ifndef CLIPBOARDPOLL_H
#define CLIPBOARDPOLL_H


#include <QApplication>
#include <QTimer>
#include <QWidget>
#include <X11/Xlib.h>
#undef Bool // Workaround for unqualified-id before 'int' for bool signal and slot


/**
    @author Lubos Lunak
*/
class clipboardPoll : public QWidget
{

    Q_OBJECT

public:
    explicit clipboardPoll(QWidget* parentw = 0);
    ~clipboardPoll();

    inline void startT(uint interval)
    {
        timer->start(interval);
    }

    inline void stopT()
    {
        timer->stop();
    }


signals:
    void clipboardChanged(bool selectionMode);


protected:
    virtual bool x11Event(XEvent*);


private slots:
    void timeout();


private:
    struct SelectionData
    {
        Atom atom;
        Atom sentinel_atom;
        Atom timestamp_atom;
        Window last_owner;
        bool owner_is_qt;
        Time last_change;
        bool waiting_for_timestamp;
        Time waiting_x_time;
    };
    Atom xa_clipboard;
    Atom xa_timestamp;
    bool changedTimestamp(SelectionData& sData, const XEvent& ev);
    bool checkTimestamp(SelectionData& sData);
    QTimer* timer;
    SelectionData clipboard;
    SelectionData selection;
    void updateQtOwnership(SelectionData& sData);
};

#endif
