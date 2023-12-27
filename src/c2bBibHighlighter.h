/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BBIBHIGHLIGHTER_H
#define C2BBIBHIGHLIGHTER_H

#include <QSyntaxHighlighter>


/**
    BibTeX SyntaxHighLighter

    @author Pere Constans
*/

class c2bColors;

class c2bBibHighlighter : public QSyntaxHighlighter
{

public:
    explicit c2bBibHighlighter(QTextDocument* doc);
    ~c2bBibHighlighter();


protected:
    virtual void highlightBlock(const QString& text);


private:
    QColor text_color;
    QRegExp rx0;
    QRegExp rx1;
    QRegExp rx2;
    QRegExp rx3;
    c2bColors* c;
};

#endif
