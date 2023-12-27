/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bBibHighlighter.h"
#include "c2bSettings.h"

#include <QPalette>
#include <QTextDocument>


c2bBibHighlighter::c2bBibHighlighter(QTextDocument* doc) : QSyntaxHighlighter(doc)
{
    QPalette p;
    text_color = p.text().color();
    c2bSettings* settings(c2bSettingsP);
    c = &settings->colors;
    connect(settings, SIGNAL(newSettings()), this, SLOT(rehighlight()));

    rx0 = QRegExp("[\\{\\}]+");
    rx0.setMinimal(true);
    rx1 = QRegExp("@\\w+");
    rx2 = QRegExp("^\\w+");
    rx3 = QRegExp("^%.+$");
}

c2bBibHighlighter::~c2bBibHighlighter() {}


void c2bBibHighlighter::highlightBlock(const QString& text)
{
    const int len(text.length());
    setFormat(0, len - 1, text_color);

    int pos(0);
    while (pos >= 0)
    {
        pos = rx0.indexIn(text, pos);
        if (pos > -1)
        {
            setFormat(pos, rx0.matchedLength(), c->bib_delimiter_color);
            pos += rx0.matchedLength();
        }
    }
    pos = 0;
    while (pos >= 0)
    {
        pos = rx1.indexIn(text, pos);
        if (pos > -1)
        {
            setFormat(pos, rx1.matchedLength(), c->bib_reference_type_color);
            pos += rx1.matchedLength();
        }
    }
    pos = 0;
    while (pos >= 0)
    {
        pos = rx2.indexIn(text, pos);
        if (pos > -1)
        {
            setFormat(pos, rx2.matchedLength(), c->bib_reference_field_color);
            pos += rx2.matchedLength();
        }
    }
    pos = 0;
    while (pos >= 0)
    {
        pos = rx3.indexIn(text, pos);
        if (pos > -1)
        {
            setFormat(pos, rx3.matchedLength(), c->comment_color);
            pos += rx3.matchedLength();
        }
    }
}
