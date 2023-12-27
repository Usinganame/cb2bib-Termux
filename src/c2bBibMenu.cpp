/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bBibMenu.h"

#include <cb2bib_parameters.h>

#include <QKeyEvent>


c2bBibMenu::c2bBibMenu(QWidget* parentw) : QMenu(parentw), _keyboard_selection(0), _was_plus_pressed(false)
{
    _title_action = addAction("Title");
    _title_action->setData("title");
    _author_action = addAction("Author");
    _author_action->setData("author");
    _add_author_action = addAction("Add authors");
    _add_author_action->setIcon(QIcon(C2B_ICON_DIR + "add.png"));
    _journal_action = addAction("Journal");
    _journal_action->setData("journal");
    addSeparator();

    _pages_action = addAction("Pages");
    _pages_action->setData("pages");
    _volume_action = addAction("Volume");
    _volume_action->setData("volume");
    _number_action = addAction("Number");
    _number_action->setData("number");
    _year_action = addAction("Year");
    _year_action->setData("year");
    addSeparator();

    _abstract_action = addAction("Abstract");
    _abstract_action->setData("abstract");
    _keywords_action = addAction("Keywords");
    _keywords_action->setData("keywords");
    _file_action = addAction("File");
    _file_action->setData("file");

    QMenu* submenu = new QMenu("Other fields...", this);
    _address_action = submenu->addAction("Address");
    _address_action->setData("address");
    _annote_action = submenu->addAction("Annote");
    _annote_action->setData("annote");
    _booktitle_action = submenu->addAction("Booktitle");
    _booktitle_action->setData("booktitle");
    _chapter_action = submenu->addAction("Chapter");
    _chapter_action->setData("chapter");
    _doi_action = submenu->addAction("DOI");
    _doi_action->setData("doi");
    _edition_action = submenu->addAction("Edition");
    _edition_action->setData("edition");
    _editor_action = submenu->addAction("Editor");
    _editor_action->setData("editor");
    _add_editor_action = submenu->addAction("Add editors");
    _add_editor_action->setIcon(QIcon(C2B_ICON_DIR + "add.png"));
    _eprint_action = submenu->addAction("Eprint");
    _eprint_action->setData("eprint");
    _institution_action = submenu->addAction("Institution");
    _institution_action->setData("institution");
    _isbn_action = submenu->addAction("ISBN");
    _isbn_action->setData("isbn");
    _issn_action = submenu->addAction("ISSN");
    _issn_action->setData("issn");
    _month_action = submenu->addAction("Month");
    _month_action->setData("month");
    _note_action = submenu->addAction("Note");
    _note_action->setData("note");
    _organization_action = submenu->addAction("Organization");
    _organization_action->setData("organization");
    _publisher_action = submenu->addAction("Publisher");
    _publisher_action->setData("publisher");
    _school_action = submenu->addAction("School");
    _school_action->setData("school");
    _series_action = submenu->addAction("Series");
    _series_action->setData("series");
    _url_action = submenu->addAction("URL");
    _url_action->setData("url");

    addSeparator();
    addMenu(submenu);
    addSeparator();
    _any_pattern_action = addAction(QString());
}

QAction* c2bBibMenu::exec(const QPoint& p)
{
    _keyboard_selection = 0;
    _was_plus_pressed = false;
    QAction* a = QMenu::exec(p);
    if (a)
        return a;
    else
        return _keyboard_selection;
}

void c2bBibMenu::keyPressEvent(QKeyEvent* qevent)
{
    switch (qevent->key())
    {
    case Qt::Key_A:
        if (_was_plus_pressed)
            _keyboard_selection = _add_author_action;
        else
            _keyboard_selection = _author_action;
        break;
    case Qt::Key_B:
        _keyboard_selection = _booktitle_action;
        break;
    case Qt::Key_C:
        _keyboard_selection = _chapter_action;
        break;
    case Qt::Key_D:
        _keyboard_selection = _doi_action;
        break;
    case Qt::Key_E:
        if (_was_plus_pressed)
            _keyboard_selection = _add_editor_action;
        else
            _keyboard_selection = _editor_action;
        break;
    case Qt::Key_F:
        _keyboard_selection = _file_action;
        break;
    case Qt::Key_I:
        _keyboard_selection = _isbn_action;
        break;
    case Qt::Key_J:
        _keyboard_selection = _journal_action;
        break;
    case Qt::Key_K:
        _keyboard_selection = _keywords_action;
        break;
    case Qt::Key_M:
        _keyboard_selection = _month_action;
        break;
    case Qt::Key_N:
        _keyboard_selection = _number_action;
        break;
    case Qt::Key_O:
        _keyboard_selection = _organization_action;
        break;
    case Qt::Key_P:
        _keyboard_selection = _pages_action;
        break;
    case Qt::Key_S:
        _keyboard_selection = _series_action;
        break;
    case Qt::Key_T:
        _keyboard_selection = _title_action;
        break;
    case Qt::Key_U:
        _keyboard_selection = _url_action;
        break;
    case Qt::Key_V:
        _keyboard_selection = _volume_action;
        break;
    case Qt::Key_Y:
        _keyboard_selection = _year_action;
        break;
    case Qt::Key_Plus:
        _was_plus_pressed = true;
        break;
    default:
        _keyboard_selection = 0;
        _was_plus_pressed = false;
    }
    if (_keyboard_selection)
    {
        qevent->accept();
        hide();
        _keyboard_selection->trigger();
    }
    else
        QMenu::keyPressEvent(qevent);
}
