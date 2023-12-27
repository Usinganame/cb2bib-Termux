/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BCORECITER_H
#define C2BCORECITER_H

#include <QObject>
#include <QWidget>


class settings;


class c2bCoreCiter : public QObject
{

    Q_OBJECT

public:
    explicit c2bCoreCiter(QWidget* parentw = 0);
    ~c2bCoreCiter();

    void cite(const QStringList& keys);


public slots:
    void setLyXPipe();


private:
    void _cite_to_clipboard(const QStringList& keys) const;
    void _cite_to_lyx_pipe(const QStringList& keys) const;

    QRegExp _citeids;
    QString _command;
    QString _lyxpipe;
    QWidget* _parentWP;
    settings* _settingsP;
};

#endif
