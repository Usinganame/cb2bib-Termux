/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef CB2BIB_H
#define CB2BIB_H

#include "ui_cb2Bib.h"

#include <QHash>
#include <QMainWindow>
#include <QPointer>

class bibSearcher;
class c2bBibMenu;
class c2bBibParser;
class c2bCiterWidget;
class c2bClipEdit;
class c2bEditor;
class c2bNetworkQuery;
class c2bPdfImport;
class c2bSearchInFiles;
class c2bSettings;
class c2bTextBrowser;


class cb2Bib : public QMainWindow
{

    Q_OBJECT

public:
    explicit cb2Bib(QWidget* parentw = 0);
    ~cb2Bib();


public slots:
    void show();


signals:
    void addedBibToFile(const QString&);
    void endedProcessing(bool status);


private:
    QHash<QString, c2bEditor*> _openDocuments;
    QPointer<c2bPdfImport> _pdfImportP;
    QPointer<c2bSearchInFiles> _searchInFilesP;
    QString _dropped_document_file;
    QString _raw_input_data;
    QString _target_document_file;
    QString buttonStatusTip(const QString& ms, const QKeySequence& ks) const;
    Ui::cb2Bib ui;
    bool _connected;
    bool _is_check_repeated_done;
    bool _modified;
    bool _tagged_view_mode;
    bool isReferenceRepeated();
    c2bBibMenu* _bib_menu;
    c2bBibParser* _bpP;
    c2bCiterWidget* _citerP;
    c2bClipEdit* BibBrowser;
    c2bClipEdit* ClipEdit;
    c2bNetworkQuery* _netQP;
    c2bSettings* _settingsP;
    c2bTextBrowser* AboutBrowser;
    void annoteEditor(const QString& annotefile);
    void c2bParse(const QString& text);
    void c2bPreparse(const QString& text);
    void closeEvent(QCloseEvent* qevent);
    void dragEnterEvent(QDragEnterEvent* qevent);
    void dropEvent(QDropEvent* qevent);
    void fileDroppedByUser(const QString& fn);
    void initAsBibTeXEditor();
    void processingEnded();
    void setBibMenu();
    void setWidgetMapping();
    void updateBibfile(const QString& fn);
    void updateViewButtons();


private slots:
    void abbreviationsEditor();
    void addAuthors();
    void addEditors();
    void addMetadata();
    void addToFile(bool ready);
    void anyPattern();
    void bibEditor(const QString& bibtexfile, bibSearcher* searcher = 0);
    void bibModified(bool modified);
    void bookmarksEditor();
    void c2bInit();
    void checkRepeated();
    void dataChanged(const QString& str);
    void deleteTmpBib();
    void doSearchInFiles(const QString& string = QString(), const QString& fn = QString());
    void fileDropped(const QString& fn);
    void forceDataChange(const QString& str);
    void guessFields();
    void insertRegExp();
    void linkClicked(const QUrl& ln);
    void loadSettings();
    void makeNetQuery();
    void netQueryEnded(bool succeeded, const QString& targetPDF, const QString& targetBib);
    void on_AddBibB_clicked();
    void on_BibTeXDir_clicked();
    void on_ConfigureB_clicked();
    void on_ConnectB_clicked();
    void on_EditBibTeXB_clicked();
    void on_ExitB_clicked();
    void on_MakeNetworkQueryB_clicked();
    void on_PdfImportB_clicked();
    void on_SearchInFilesB_clicked();
    void on_ViewAboutB_clicked();
    void on_ViewBibB_clicked();
    void openAnnote();
    void openFileDocument();
    void postprocessBibTeX();
    void preparseClipboard();
    void readField(const QPoint& position);
    void regExpsEditor();
    void restartEngine();
    void savePattern(const QString& rx, const QString& rxname);
    void selectFile();
    void setDocumentFilename();
    void setTaggedClipEditMode(bool tagged);
    void setWindowTitle(const QString& title = QString());
    void showLink(const QString& ln);
    void showMessage(const QString& ms);
    void toggleReferenceTabs();
    void updateCheckRepeatedAction();
    void updateOpenDocuments(QObject* obj);
    void updateOpenDocuments(const QString& old_name, const QString& new_name);
};

#endif
