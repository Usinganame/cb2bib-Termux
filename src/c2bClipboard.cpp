/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bClipboard.h"
#ifdef C2B_USE_CBPOLL
#include "clipboardPoll.h"
#endif

#include <QApplication>


c2bClipboard::c2bClipboard(QObject* parento) : QObject(parento)
{
    // Connecting clipboard
    _cb = QApplication::clipboard();
    _supports_selection = _cb->supportsSelection();
    _is_connected = false;
    _cb_text = _cb->text(QClipboard::Clipboard);
    if (_supports_selection)
        _cbs_text = _cb->text(QClipboard::Selection);

    // Set polling
    _interval = 1000;
#ifdef C2B_USE_CBPOLL
    _poll = new clipboardPoll();
    connect(_poll, SIGNAL(clipboardChanged(bool)), this, SLOT(newClipboardData(bool)));
#else
    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(checkData()));
#endif
}

c2bClipboard::~c2bClipboard()
{
#ifdef C2B_USE_CBPOLL
    delete _poll;
#endif
}


void c2bClipboard::checkData()
{
    if (_cb_text != _cb->text(QClipboard::Clipboard))
    {
        _cb_text = _cb->text(QClipboard::Clipboard);
        emit cbDataChanged(_cb_text);
    }
    if (_supports_selection && _cbs_text != _cb->text(QClipboard::Selection))
    {
        _cbs_text = _cb->text(QClipboard::Selection);
        emit cbDataChanged(_cbs_text);
    }
}

void c2bClipboard::dataChanged()
{
    if (_cb_text != _cb->text(QClipboard::Clipboard))
    {
        _cb_text = _cb->text(QClipboard::Clipboard);
        emit cbDataChanged(_cb_text);
    }
}

void c2bClipboard::selectionChanged()
{
    if (_supports_selection && _cbs_text != _cb->text(QClipboard::Selection))
    {
        _cbs_text = _cb->text(QClipboard::Selection);
        emit cbDataChanged(_cbs_text);
    }
}

void c2bClipboard::setConnected(bool zconn)
{
    _is_connected = zconn;
    if (_is_connected)
    {
        _cb_text = _cb->text(QClipboard::Clipboard);
        connect(_cb, SIGNAL(dataChanged()), this, SLOT(dataChanged()));
        if (_supports_selection)
        {
            _cbs_text = _cb->text(QClipboard::Selection);
            connect(_cb, SIGNAL(selectionChanged()), this, SLOT(selectionChanged()));
        }
#ifdef C2B_USE_CBPOLL
        _poll->startT(_interval);
#else
        _timer->start(_interval);
#endif
    }
    else
    {
#ifdef C2B_USE_CBPOLL
        _poll->stopT();
#else
        _timer->stop();
#endif
        disconnect(_cb, SIGNAL(dataChanged()), this, SLOT(dataChanged()));
        if (_supports_selection)
            disconnect(_cb, SIGNAL(selectionChanged()), this, SLOT(selectionChanged()));
    }
}

void c2bClipboard::newClipboardData(bool selectionMode)
{
    if (selectionMode)
        selectionChanged();
    else
        dataChanged();
}
