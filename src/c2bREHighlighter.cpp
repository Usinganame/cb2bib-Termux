/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bREHighlighter.h"
#include "c2bSettings.h"

#include <QPalette>
#include <QTextDocument>


c2bREHighlighter::c2bREHighlighter(QTextDocument* doc) : QSyntaxHighlighter(doc)
{
    QPalette p;
    text_color = p.text().color();
    c2bSettings* settings(c2bSettingsP);
    c = &settings->colors;
    connect(settings, SIGNAL(newSettings()), this, SLOT(rehighlight()));

    rx0 = QRegExp("\\b(?:abstract|address|annote|author|booktitle|chapter|"
                  "doi|edition|editor|eprint|file|institution|isbn|issn|journal|"
                  "keywords|month|note|number|organization|pages|publisher|"
                  "school|series|title|url|volume|year)\\b");
    rx0.setMinimal(true);
    rx1 = QRegExp("\\b(?:article|book|booklet|conference|inbook|incollection|"
                  "inproceedings|manual|mastersthesis|misc|periodical|phdthesis|"
                  "proceedings|techreport|unpublished)\\b");
    rx2 = QRegExp("^[a-z_]+=\\S.+$");
    rx3 = QRegExp("^[a-z_]+=");
    rx4 = QRegExp("<<[a-z]+>>");
    rx5 = QRegExp("^#.*$");
}

c2bREHighlighter::~c2bREHighlighter() {}


void c2bREHighlighter::highlightBlock(const QString& text)
{
    const int len(text.length());
    setFormat(0, len - 1, text_color);

    int pos(0);
    while (pos >= 0)
    {
        pos = rx0.indexIn(text, pos);
        if (pos > -1)
        {
            setFormat(pos, rx0.matchedLength(), c->bib_reference_field_color);
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
            setFormat(pos, rx2.matchedLength(), c->netqinf_command_content_color);
            pos += rx2.matchedLength();
        }
    }
    pos = 0;
    while (pos >= 0)
    {
        pos = rx3.indexIn(text, pos);
        if (pos > -1)
        {
            setFormat(pos, rx3.matchedLength(), c->netqinf_command_key_color);
            pos += rx3.matchedLength();
        }
    }
    pos = 0;
    while (pos >= 0)
    {
        pos = rx4.indexIn(text, pos);
        if (pos > -1)
        {
            setFormat(pos, rx4.matchedLength(), c->cb2bib_tag_color);
            pos += rx4.matchedLength();
        }
    }
    pos = 0;
    while (pos >= 0)
    {
        pos = rx5.indexIn(text, pos);
        if (pos > -1)
        {
            setFormat(pos, rx5.matchedLength(), c->comment_color);
            pos += rx5.matchedLength();
        }
    }
}
