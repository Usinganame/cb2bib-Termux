/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 *
 *   Improvements and modifications:
 *   July 2009 - Added <<author_all_abbreviated>>, (C) 2009 by Dayu Huang
 ***************************************************************************/
#include "c2bIdPatternLineEdit.h"

#include "c2bUtils.h"

#include <cb2bib_parameters.h>

#include <QAction>


c2bIdPatternLineEdit::c2bIdPatternLineEdit(QWidget* parentw) : c2bLineEdit(parentw)
{
    a_author_all_abbreviated = new QAction(this);
    a_author_all_initials = new QAction(this);
    a_author_first = new QAction(this);
    a_author_first_lowercase = new QAction(this);
    a_citeid = new QAction(this);
    a_journal_initials = new QAction(this);
    a_pages_first = new QAction(this);
    a_ppages_first = new QAction(this);
    a_title = new QAction(this);
    a_title_first_word = new QAction(this);
    a_title_underscored = new QAction(this);
    a_volume = new QAction(this);
    a_year_abbreviated = new QAction(this);
    a_year_full = new QAction(this);

    a_reset = new QAction(this);

    c2bUtils::addSeparator(this);
    addAction(a_author_all_abbreviated);
    addAction(a_author_all_initials);
    addAction(a_author_first);
    addAction(a_author_first_lowercase);
    c2bUtils::addSeparator(this);
    addAction(a_citeid);
    c2bUtils::addSeparator(this);
    addAction(a_journal_initials);
    c2bUtils::addSeparator(this);
    addAction(a_pages_first);
    addAction(a_ppages_first);
    c2bUtils::addSeparator(this);
    addAction(a_title);
    addAction(a_title_underscored);
    addAction(a_title_first_word);
    c2bUtils::addSeparator(this);
    addAction(a_volume);
    c2bUtils::addSeparator(this);
    addAction(a_year_abbreviated);
    addAction(a_year_full);
    c2bUtils::addSeparator(this);
    addAction(a_reset);

    a_author_all_abbreviated->setText(tr("Insert <<author_all_abbreviated>>"));
    a_author_all_initials->setText(tr("Insert <<author_all_initials>>"));
    a_author_first->setText(tr("Insert <<author_first>>"));
    a_author_first_lowercase->setText(tr("Insert <<author_first_lowercase>>"));
    a_citeid->setText(tr("Insert <<citeid>>"));
    a_journal_initials->setText(tr("Insert <<journal_initials>>"));
    a_pages_first->setText(tr("Insert <<pages_first>>"));
    a_ppages_first->setText(tr("Insert <<ppages_first>>"));
    a_title->setText(tr("Insert <<title>>"));
    a_title_first_word->setText(tr("Insert <<title_first_word>>"));
    a_title_underscored->setText(tr("Insert <<title_underscored>>"));
    a_volume->setText(tr("Insert <<volume>>"));
    a_year_abbreviated->setText(tr("Insert <<year_abbreviated>>"));
    a_year_full->setText(tr("Insert <<year_full>>"));

    a_reset->setText(tr("Reset ID Pattern"));

    connect(a_author_all_abbreviated, SIGNAL(triggered()), this, SLOT(author_all_abbreviated()));
    connect(a_author_all_initials, SIGNAL(triggered()), this, SLOT(author_all_initials()));
    connect(a_author_first, SIGNAL(triggered()), this, SLOT(author_first()));
    connect(a_author_first_lowercase, SIGNAL(triggered()), this, SLOT(author_first_lowercase()));
    connect(a_citeid, SIGNAL(triggered()), this, SLOT(citeid()));
    connect(a_journal_initials, SIGNAL(triggered()), this, SLOT(journal_initials()));
    connect(a_pages_first, SIGNAL(triggered()), this, SLOT(pages_first()));
    connect(a_ppages_first, SIGNAL(triggered()), this, SLOT(ppages_first()));
    connect(a_title, SIGNAL(triggered()), this, SLOT(title()));
    connect(a_title_first_word, SIGNAL(triggered()), this, SLOT(title_first_word()));
    connect(a_title_underscored, SIGNAL(triggered()), this, SLOT(title_underscored()));
    connect(a_volume, SIGNAL(triggered()), this, SLOT(volume()));
    connect(a_year_abbreviated, SIGNAL(triggered()), this, SLOT(year_abbreviated()));
    connect(a_year_full, SIGNAL(triggered()), this, SLOT(year_full()));

    connect(a_reset, SIGNAL(triggered()), this, SLOT(reset()));

    // Hide citeid as default: CiteID line edit
    a_citeid->setVisible(false);
    setPlaceholderText(C2B_CITE_ID_PATTERN);
}

c2bIdPatternLineEdit::~c2bIdPatternLineEdit() {}


void c2bIdPatternLineEdit::setDocumentIDEdit()
{
    a_citeid->setVisible(true);
    setPlaceholderText(C2B_DOCUMENT_ID_PATTERN);
}

void c2bIdPatternLineEdit::author_all_abbreviated()
{
    insert(QLatin1String("<<author_all_abbreviated>>"));
}

void c2bIdPatternLineEdit::author_all_initials()
{
    insert(QLatin1String("<<author_all_initials>>"));
}

void c2bIdPatternLineEdit::author_first()
{
    insert(QLatin1String("<<author_first>>"));
}

void c2bIdPatternLineEdit::author_first_lowercase()
{
    insert(QLatin1String("<<author_first_lowercase>>"));
}

void c2bIdPatternLineEdit::citeid()
{
    insert(QLatin1String("<<citeid>>"));
}

void c2bIdPatternLineEdit::journal_initials()
{
    insert(QLatin1String("<<journal_initials>>"));
}

void c2bIdPatternLineEdit::pages_first()
{
    insert(QLatin1String("<<pages_first>>"));
}

void c2bIdPatternLineEdit::ppages_first()
{
    insert(QLatin1String("<<ppages_first>>"));
}

void c2bIdPatternLineEdit::title()
{
    insert(QLatin1String("<<title_25>>"));
}

void c2bIdPatternLineEdit::title_underscored()
{
    insert(QLatin1String("<<title_underscored_25>>"));
}

void c2bIdPatternLineEdit::title_first_word()
{
    insert(QLatin1String("<<title_first_word>>"));
}

void c2bIdPatternLineEdit::volume()
{
    insert(QLatin1String("<<volume>>"));
}

void c2bIdPatternLineEdit::year_abbreviated()
{
    insert(QLatin1String("<<year_abbreviated>>"));
}

void c2bIdPatternLineEdit::year_full()
{
    insert(QLatin1String("<<year_full>>"));
}

void c2bIdPatternLineEdit::reset()
{
    if (a_citeid->isVisible())
        setText(C2B_DOCUMENT_ID_PATTERN);
    else
        setText(C2B_CITE_ID_PATTERN);
}
