/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BCLIPBOARD_H
#define C2BCLIPBOARD_H

#include <QObject>

#include <QClipboard>
#include <QTimer>


/**
    cb2Bib Clipboard

    Implements clipboard functionality as required by cb2Bib This should fix
    acrobat, mozilla, qt 3.3.3 issues Using clipboardPoll

    STATUS: DEPRECATED
*/

#ifdef C2B_USE_CBPOLL
class clipboardPoll;
#endif

class c2bClipboard : public QObject
{
    Q_OBJECT
public:
    explicit c2bClipboard(QObject* parento = 0);
    ~c2bClipboard();


    void setConnected(bool);


signals:
    void cbDataChanged(const QString&);


private:
    QClipboard* _cb;
    QString _cb_text;
    QString _cbs_text;
    bool _is_connected;
    bool _supports_selection;
    uint _interval;
#ifdef C2B_USE_CBPOLL
    clipboardPoll* _poll;
#else
    QTimer* _timer;
#endif


private slots:
    void checkData();
    void dataChanged();
    void newClipboardData(bool selectionMode);
    void selectionChanged();
};

#endif
