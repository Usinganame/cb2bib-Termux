/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BSEARCHINFILESPATTERN_H
#define C2BSEARCHINFILESPATTERN_H

#include "ui_c2bSearchInFilesPattern.h"

#include <QWidget>


const int ITEMS_IN_SEARCH_PATTERN(6);

class QTreeWidgetItem;

class c2bSearchInFilesPattern : public QWidget
{

    Q_OBJECT

public:
    explicit c2bSearchInFilesPattern(QWidget* parentw = 0);
    ~c2bSearchInFilesPattern();

    const QStringList patterns();
    void clear();
    void setPattern(QTreeWidgetItem* pattern);
    void setText(const QString& text);

    inline bool isAvailable() const
    {
        return !ui.inputPattern->text().isEmpty();
    }


signals:
    void patternAvailable(bool available);


public slots:
    void setFocus();


private slots:
    void patternChanged();
    void showYearScope(const QString& scope);


private:
    Ui::c2bSearchInFilesPattern ui;
};

#endif
