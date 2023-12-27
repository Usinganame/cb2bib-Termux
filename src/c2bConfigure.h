/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BCONFIGURE_H
#define C2BCONFIGURE_H

#include "c2bColors.h"
#include "ui_c2bConfigure.h"

#include <QDialog>
#include <QFontDatabase>


class c2bSettings;

class c2bConfigure : public QDialog
{

    Q_OBJECT

public:
    explicit c2bConfigure(QWidget* parentw = 0);
    ~c2bConfigure();

    void setPage(int index);


protected slots:
    void FindReplaceDialog_Delete();
    void FindReplaceDialog_Edit();
    void FindReplaceDialog_New();
    void accept();
    void apply();
    void changeContextColor(QTreeWidgetItem* item);
    void changePage(QListWidgetItem* current, QListWidgetItem* previous);
    void comboFamilyChanged(const QString& family);
    void comboSizeChanged(const QString& pt);
    void getAnnoteCssFile();
    void getBibSearcherPdf2TextBin();
    void getBrowserCssFile();
    void getCacheDirectory();
    void getExifToolBin();
    void getFmClientCopyBin();
    void getFmClientMoveBin();
    void getJournalFile();
    void getMathJaxHeaderFile();
    void getNetworkFile();
    void getPdfDirectory();
    void getPdfImportPdf2TextBin();
    void getPosLexiconFile();
    void getPostprocessBibTeXBin();
    void getPreparserBin();
    void getRegularExpressionFile();
    void help();
    void showMessage(const QString& ms);
    void updateFindReplaceInputButtons();


private:
    QFont c2bMonoFont;
    QFont selectedFont(QFontComboBox* fc, QComboBox* sc) const;
    Ui::c2bConfigure ui;
    bool event(QEvent* qevent);
    c2bColors colors;
    c2bSettings* settings;
    void fontSelection(const QFont& f, QFontComboBox* fc, QComboBox* sc);
    void populateFontCombos();
};

#endif
