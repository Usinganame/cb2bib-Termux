/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 *
 *   Improvements and modifications:
 *   July 2009 - Added <<author_all_abbreviated>>, (C) 2009 by Dayu Huang
 ***************************************************************************/
#ifndef C2BIDPATTERNLINEEDIT_H
#define C2BIDPATTERNLINEEDIT_H

#include "c2bLineEdit.h"

class QAction;


class c2bIdPatternLineEdit : public c2bLineEdit
{

    Q_OBJECT

public:
    explicit c2bIdPatternLineEdit(QWidget* parentw = 0);
    ~c2bIdPatternLineEdit();

    void setDocumentIDEdit();


protected:
    QAction* a_author_all_abbreviated;
    QAction* a_author_all_initials;
    QAction* a_author_first;
    QAction* a_author_first_lowercase;
    QAction* a_citeid;
    QAction* a_journal_initials;
    QAction* a_pages_first;
    QAction* a_ppages_first;
    QAction* a_reset;
    QAction* a_title;
    QAction* a_title_first_word;
    QAction* a_title_underscored;
    QAction* a_volume;
    QAction* a_year_abbreviated;
    QAction* a_year_full;


protected slots:
    void author_all_abbreviated();
    void author_all_initials();
    void author_first();
    void author_first_lowercase();
    void citeid();
    void journal_initials();
    void pages_first();
    void ppages_first();
    void reset();
    void title();
    void title_first_word();
    void title_underscored();
    void volume();
    void year_abbreviated();
    void year_full();
};

#endif
