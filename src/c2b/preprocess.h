/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef PREPROCESS_H
#define PREPROCESS_H

#include <QObject>
#include <QStringList>


/**
    @author Pere Constans
*/
class preprocess : public QObject
{

    Q_OBJECT

public:
    explicit preprocess(QObject* parento = 0);
    inline ~preprocess() {}


public:
    void preprocessText(QString* text);


public slots:
    void loadSettings();


private:
    bool FindReplaceInput;
    QStringList FindReplaceInputList;
};

#endif
