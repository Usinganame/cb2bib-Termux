/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "preprocess.h"
#include "settings.h"


preprocess::preprocess(QObject* parento) : QObject(parento)
{
    loadSettings();
    connect(settings::instance(), SIGNAL(newSettings()), this, SLOT(loadSettings()));
}


void preprocess::loadSettings()
{
    FindReplaceInput = settings::instance()->value("cb2Bib/FindReplaceInput").toBool();
    FindReplaceInputList = settings::instance()->value("cb2Bib/FindReplaceInputList").toStringList();
}

void preprocess::preprocessText(QString* text)
{
    if (!FindReplaceInput)
        return;
    QStringList::Iterator i = FindReplaceInputList.begin();
    while (i != FindReplaceInputList.end())
    {
        const QStringList spLine((*i).split('|'));
        if (spLine.count() > 1)
            text->replace(spLine.at(0), spLine.at(1));
        ++i;
    }
}
