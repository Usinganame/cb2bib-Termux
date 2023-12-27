/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BBIBMENU_H
#define C2BBIBMENU_H

#include <QMenu>


class c2bBibMenu : public QMenu
{

    Q_OBJECT

public:
    explicit c2bBibMenu(QWidget* parentw = 0);
    inline ~c2bBibMenu() {}

    inline QAction* addAuthorAction() const
    {
        return _add_author_action;
    }
    inline QAction* addEditorAction() const
    {
        return _add_editor_action;
    }
    inline QAction* anyPatternAction() const
    {
        return _any_pattern_action;
    }
    inline void setAnyPatternText(const QString& text)
    {
        _any_pattern_action->setText(text);
    }

    QAction* exec(const QPoint& p);


protected:
    void keyPressEvent(QKeyEvent* qevent);


private:
    QAction* _abstract_action;
    QAction* _add_author_action;
    QAction* _add_editor_action;
    QAction* _address_action;
    QAction* _annote_action;
    QAction* _any_pattern_action;
    QAction* _author_action;
    QAction* _booktitle_action;
    QAction* _chapter_action;
    QAction* _doi_action;
    QAction* _edition_action;
    QAction* _editor_action;
    QAction* _eprint_action;
    QAction* _file_action;
    QAction* _institution_action;
    QAction* _isbn_action;
    QAction* _issn_action;
    QAction* _journal_action;
    QAction* _keyboard_selection;
    QAction* _keywords_action;
    QAction* _month_action;
    QAction* _note_action;
    QAction* _number_action;
    QAction* _organization_action;
    QAction* _pages_action;
    QAction* _publisher_action;
    QAction* _school_action;
    QAction* _series_action;
    QAction* _title_action;
    QAction* _url_action;
    QAction* _volume_action;
    QAction* _year_action;
    bool _was_plus_pressed;
};

#endif
