/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BSAVEREHIGHLIGHTER_H
#define C2BSAVEREHIGHLIGHTER_H

#include <QSyntaxHighlighter>


/**
    Save RegExp SyntaxHighLighter

    @author Pere Constans
*/

class c2bColors;

class c2bSaveREHighlighter : public QSyntaxHighlighter
{

public:
    c2bSaveREHighlighter(QRegExp& rx, QTextDocument* doc);
    ~c2bSaveREHighlighter();


protected:
    virtual void highlightBlock(const QString& text);


private:
    QColor text_color;
    QRegExp& _current_rx;
    c2bColors* c;
};

#endif
