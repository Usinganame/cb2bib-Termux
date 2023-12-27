/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BEDITOR_H
#define C2BEDITOR_H

#include "ui_c2bEditor.h"

#include <QMainWindow>
#include <QPointer>


class QDockWidget;
class QLabel;
class QStackedWidget;
class QSyntaxHighlighter;
class bibSearcher;
class c2bBibParser;
class c2bReferenceList;
class c2bSettings;
class c2bTextBrowser;
class c2bTextEdit;
class findDialog;


class c2bEditor : public QMainWindow
{

    Q_OBJECT

public:
    enum Mode
    {
        Annote,
        BibTeX,
        JAbbrev,
        NetQInfo,
        RegExp
    };

    c2bEditor(const QString& file, const Mode mode, QWidget* main, QWidget* parentw = 0);
    c2bEditor(const QString& file, bibSearcher* searcher, QWidget* main, QWidget* parentw = 0);

    ~c2bEditor();

    inline QString editorFilename() const
    {
        return _editor_fn;
    }
    bool closeEditor();


signals:
    void editFileRenamed(const QString& old_name, const QString& new_name);
    void execute();
    void openBookmarks();
    void openFile(const QString& fn);
    void restartEngine();
    void restartQuery();


protected:
    virtual void closeEvent(QCloseEvent* qevent);


protected slots:
    bool fileSave();
    bool fileSaveAs();
    void cursorPositionChanged();
    void exportEntries();
    void fileOpen();
    void helpCb2Bib();
    void helpEditor();
    void htmlView();
    void isModified(int position, int charsRemoved, int charsAdded);
    void journalsToAbbreviated();
    void journalsToAlternateAbbreviated();
    void journalsToAlternateFull();
    void journalsToFull();
    void load();
    void overwriteModeChanged();
    void pasteCurrentBibTeX();
    void postProcess();
    void reload(const QString& fn);
    void saveAndExecute();
    void setViewMode(bool edit_mode);
    void showMessage(const QString& ms);
    void updateMetadata();
    void viewCb2Bib();


private:
    Mode _editor_mode;
    QDockWidget* _dockWidgetP;
    QLabel* _lineLabelP;
    QLabel* _overwriteLabelP;
    QPointer<bibSearcher> _searcherP;
    QStackedWidget* _stackedWidgetP;
    QString _edit_reference_at_position;
    QString _editor_fn;
    QSyntaxHighlighter* _shP;
    QWidget* _c2b_mainP;
    Ui::c2bEditor ui;
    bool _is_modified_by_user;
    c2bBibParser* _bpP;
    c2bReferenceList* _referencesP;
    c2bSettings* _settingsP;
    c2bTextBrowser* _browserP;
    c2bTextEdit* _editorP;
    findDialog* _textFinderP;
    void createReferenceList();
    void importActions();
    void initEditor();
    void setEditorMode();

    QMenu* createPopupMenu() // to avoid default context menu
    {
        return 0;
    }
};

#endif
