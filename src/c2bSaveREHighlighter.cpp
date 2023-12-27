/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bSaveREHighlighter.h"
#include "c2bSettings.h"

#include <QPalette>
#include <QTextDocument>


c2bSaveREHighlighter::c2bSaveREHighlighter(QRegExp& rx, QTextDocument* doc) : QSyntaxHighlighter(doc), _current_rx(rx)
{
    QPalette p;
    text_color = p.text().color();
    c2bSettings* settings(c2bSettingsP);
    c = &settings->colors;
    connect(settings, SIGNAL(newSettings()), this, SLOT(rehighlight()));
}

c2bSaveREHighlighter::~c2bSaveREHighlighter() {}


void c2bSaveREHighlighter::highlightBlock(const QString& text)
{
    const int len(text.length());
    const int ind(_current_rx.indexIn(text));
    const int caps(_current_rx.capturedTexts().count());
    if (ind == -1 || caps <= 1)
        setFormat(0, len, text_color);
    else
    {
        setFormat(0, len, c->cb2bib_unrelevant_color);
        for (int i = 1; i < caps; i = i + 2)
            setFormat(_current_rx.pos(i), _current_rx.cap(i).length(), c->cb2bib_highly_relevant_color);
        for (int i = 2; i < caps; i = i + 2)
            setFormat(_current_rx.pos(i), _current_rx.cap(i).length(), c->cb2bib_relevant_color);
    }
}
