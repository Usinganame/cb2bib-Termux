/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bHighlighter.h"
#include "c2bSettings.h"

#include <QPalette>
#include <QTextDocument>


c2bHighlighter::c2bHighlighter(QTextDocument* doc) : QSyntaxHighlighter(doc)
{
    QPalette p;
    text_color = p.text().color();
    c2bSettings* settings(c2bSettingsP);
    c = &settings->colors;
    connect(settings, SIGNAL(newSettings()), this, SLOT(rehighlight()));

    rx0 = QRegExp("\\d+");
    rx0.setMinimal(true);
    rx1 = QRegExp("[^\\w\\d]+");
    rx1.setMinimal(true);
    rx2 = QRegExp("<(?:NewLine|Tab)\\d+>");
    rx2.setMinimal(true);
    rx3 = QRegExp("\\b(?:19|20)\\d\\d\\b");
    rx3.setMinimal(true);
    rx4 = QRegExp("\\b(?:abstract|authors{0,1}|introduction|issue|keywords|key words|title|volume|vol)\\b",
                  Qt::CaseInsensitive);
    rx4.setMinimal(true);
    rx5 = QRegExp("<<(?:abstract|address|annote|author|booktitle|chapter|"
                  "doi|edition|editor|eprint|file|institution|isbn|issn|journal|"
                  "keywords|month|note|number|organization|pages|publisher|"
                  "school|series|title|url|volume|year)>>");
    rx5.setMinimal(true);
    rx6 = QRegExp("<AnyPattern>");
    rx6.setMinimal(true);
    rx_extracted_starts = QRegExp("\\[\\[");
    rx_extracted_ends = QRegExp("\\]\\]");
    rx_metadata_starts = QRegExp("\\[(Bibliographic|Raw) Metadata");
    rx_metadata_ends = QRegExp("/(Bibliographic|Raw) Metadata\\]");
}

c2bHighlighter::~c2bHighlighter() {}


void c2bHighlighter::highlightBlock(const QString& text)
{
    const int len(text.length());
    setFormat(0, len - 1, text_color);

    int pos(0);
    while (pos >= 0)
    {
        pos = rx0.indexIn(text, pos);
        if (pos > -1)
        {
            setFormat(pos, rx0.matchedLength(), c->cb2bib_digit_color);
            pos += rx0.matchedLength();
        }
    }
    pos = 0;
    while (pos >= 0)
    {
        pos = rx1.indexIn(text, pos);
        if (pos > -1)
        {
            setFormat(pos, rx1.matchedLength(), c->cb2bib_unrelevant_color);
            pos += rx1.matchedLength();
        }
    }
    pos = 0;
    while (pos >= 0)
    {
        pos = rx2.indexIn(text, pos);
        if (pos > -1)
        {
            setFormat(pos, rx2.matchedLength(), c->cb2bib_unrelevant_color);
            pos += rx2.matchedLength();
        }
    }
    pos = 0;
    while (pos >= 0)
    {
        pos = rx3.indexIn(text, pos);
        if (pos > -1)
        {
            setFormat(pos, rx3.matchedLength(), c->cb2bib_relevant_color);
            pos += rx3.matchedLength();
        }
    }
    pos = 0;
    while (pos >= 0)
    {
        pos = rx4.indexIn(text, pos);
        if (pos > -1)
        {
            setFormat(pos, rx4.matchedLength(), c->cb2bib_highly_relevant_color);
            pos += rx4.matchedLength();
        }
    }
    pos = 0;
    while (pos >= 0)
    {
        pos = rx5.indexIn(text, pos);
        if (pos > -1)
        {
            setFormat(pos, rx5.matchedLength(), c->cb2bib_tag_color);
            pos += rx5.matchedLength();
        }
    }
    pos = 0;
    while (pos >= 0)
    {
        pos = rx6.indexIn(text, pos);
        if (pos > -1)
        {
            setFormat(pos, rx6.matchedLength(), c->cb2bib_unrelevant_color);
            pos += rx6.matchedLength();
        }
    }

    setCurrentBlockState(0);
    int startIndexMD(0);
    if (previousBlockState() != 1)
        startIndexMD = rx_metadata_starts.indexIn(text);
    while (startIndexMD >= 0)
    {
        const int endIndex(rx_metadata_ends.indexIn(text, startIndexMD));
        int extractedLength;
        if (endIndex == -1)
        {
            setCurrentBlockState(1);
            extractedLength = text.length() - startIndexMD;
        }
        else
            extractedLength = endIndex - startIndexMD + rx_metadata_ends.matchedLength();
        setFormat(startIndexMD, extractedLength, c->cb2bib_metadata_color);
        startIndexMD = rx_metadata_starts.indexIn(text, startIndexMD + extractedLength);
    }

    int startIndexEx(0);
    if (previousBlockState() != 2)
        startIndexEx = rx_extracted_starts.indexIn(text);
    while (startIndexEx >= 0)
    {
        const int endIndex(rx_extracted_ends.indexIn(text, startIndexEx));
        int extractedLength;
        if (endIndex == -1)
        {
            setCurrentBlockState(2);
            extractedLength = text.length() - startIndexEx;
        }
        else
            extractedLength = endIndex - startIndexEx + rx_extracted_ends.matchedLength();
        setFormat(startIndexEx, extractedLength, c->cb2bib_unrelevant_color);
        startIndexEx = rx_extracted_starts.indexIn(text, startIndexEx + extractedLength);
    }
}
