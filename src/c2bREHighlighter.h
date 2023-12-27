/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BREHIGHLIGHTER_H
#define C2BREHIGHLIGHTER_H

#include <QSyntaxHighlighter>


/**
    RegExp SyntaxHighLighter

    @author Pere Constans
*/

class c2bColors;

class c2bREHighlighter : public QSyntaxHighlighter
{

public:
    explicit c2bREHighlighter(QTextDocument* doc);
    ~c2bREHighlighter();


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
    c2bColors* c;
};

#endif
