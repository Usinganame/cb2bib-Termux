/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BREFERENCELIST_H
#define C2BREFERENCELIST_H

#include "ui_c2bReferenceList.h"

#include <QWidget>


class bibSearcher;
class c2bCoreCiter;
class c2bRLWebSearchSettings;
class c2bSettings;
class c2bTextBrowser;
class c2bTextEdit;


class c2bReferenceList : public QWidget
{
    Q_OBJECT

public:
    c2bReferenceList(c2bTextEdit* ed, c2bTextBrowser* br, QWidget* parentw = 0);
    ~c2bReferenceList();

    QAction* citeEntryAction;
    QAction* clearSelectionsAction;
    QAction* openAuthorsWebSearchAction;
    QAction* openDOIAction;
    QAction* openFileAction;
    QAction* openTextLocalSearchAction;
    QAction* openTextWebSearchAction;
    QAction* openTitleWebSearchAction;
    QAction* openUrlAction;
    QAction* refreshListAction;
    QAction* webSearchSettingsAction;
    QStringList selectedKeys() const;
    void goToReference(const QString& id);
    void goToReference(const int position);


public slots:
    void loadList(const QString& txt, bibSearcher* searcher = 0);
    void refreshList();
    void setLyXPipe();


signals:
    void hasSelectedItems(bool);
    void openFile(const QString& fn);


protected slots:
    void citeEntry();
    void clearSelections();
    void goToReference(QTreeWidgetItem* ref);
    void itemSelectionChanged();
    void openAuthorWebSearch();
    void openDOI();
    void openFile();
    void openLink(const QUrl& ln);
    void openTextLocalSearch();
    void openTextWebSearch();
    void openTitleWebSearch();
    void openUrl();
    void scrollToReference(const QString& id);
    void webSearchSettings();


private:
    QList<int> _positionList;
    QString _bib_item_html;
    QString _filter_mode;
    QString _references_html;
    QStringList _doiList;
    QStringList _fileList;
    QStringList _urlList;
    Ui::c2bReferenceList ui;
    c2bCoreCiter* _citerP;
    c2bSettings* _settingsP;
    c2bTextBrowser* _browserP;
    c2bTextEdit* _editorP;
    int _author_index;
    int _id_index;
    int _journal_index;
    int _key_index;
    int _title_index;
    int _year_index;
    void setupFilterBar();


private slots:
    void blockFilterSignals();
    void filterList();
    void keepFilterPattern();
    void setFilterMode(QAction* mode);
};

#endif
