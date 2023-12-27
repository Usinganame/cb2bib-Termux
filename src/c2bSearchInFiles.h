/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BSEARCHINFILES_H
#define C2BSEARCHINFILES_H

#include "ui_c2bSearchInFiles.h"
#include "ui_c2bSearchInFilesPatternEdit.h"

#include <QDialog>


class bibSearcher;

class c2bSearchInFiles : public QDialog
{

    Q_OBJECT

public:
    explicit c2bSearchInFiles(const QString& file, QWidget* parentw = 0);
    ~c2bSearchInFiles();

    void setCurrentText(const QString& text);


public slots:
    void setBibTeXFile(const QString& file = QString());
    void show();


signals:
    void searchDone(const QString& filename, bibSearcher* searcher);


private slots:
    void help();
    void on_addPatternB_clicked();
    void on_deletePatternB_clicked();
    void on_editPatternB_clicked();
    void searchB_clicked();
    void updateForm();


private:
    QPushButton* _searchB;
    QString _bibtex_dir;
    QString _bibtex_file;
    QString _search_log;
    Ui::c2bSearchInFiles ui;
    Ui::c2bSearchInFilesPatternEdit ui_editor;
};

#endif
