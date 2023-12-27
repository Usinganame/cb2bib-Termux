/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BCITEPATTERNLINEEEDIT_H
#define C2BCITEPATTERNLINEEEDIT_H

#include "c2bLineEdit.h"

class QAction;


class c2bCitePatternLineEedit : public c2bLineEdit
{

    Q_OBJECT

public:
    explicit c2bCitePatternLineEedit(QWidget* parentw = 0);
    ~c2bCitePatternLineEedit();


signals:
    void statusMessage(const QString& ms);


protected:
    QAction* a_citeid;
    QAction* a_citeids_comma;
    QAction* a_citeids_semicolon;
    QAction* a_latex;
    QAction* a_markdown;


protected slots:
    void check(const QString& pattern);
    void citeid();
    void citeids_comma();
    void citeids_semicolon();
    void latex();
    void markdown();


private:
    QRegExp _citeids;
};

#endif
