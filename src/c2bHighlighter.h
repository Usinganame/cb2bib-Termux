/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BHIGHLIGHTER_H
#define C2BHIGHLIGHTER_H

#include <QSyntaxHighlighter>


/**
    clipboard SyntaxHighLighter

    @author Pere Constans
*/

class c2bColors;

class c2bHighlighter : public QSyntaxHighlighter
{

public:
    explicit c2bHighlighter(QTextDocument* doc);
    ~c2bHighlighter();


protected:
    virtual void highlightBlock(const QString& text);


private:
    QColor text_color;
    QRegExp rx0;
    QRegExp rx1;
    QRegExp rx2;
    QRegExp rx3;
    QRegExp rx4;
    QRegExp rx5;
    QRegExp rx6;
    QRegExp rx_extracted_ends;
    QRegExp rx_extracted_starts;
    QRegExp rx_metadata_ends;
    QRegExp rx_metadata_starts;
    c2bColors* c;
};

#endif
