/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bEditor.h"

#include "bookmarkPlugin.h"
#include "c2b.h"
#include "c2bBibHighlighter.h"
#include "c2bBibParser.h"
#include "c2bExportDialog.h"
#include "c2bFileDialog.h"
#include "c2bPostprocess.h"
#include "c2bREHighlighter.h"
#include "c2bReferenceList.h"
#include "c2bSettings.h"
#include "c2bTextBrowser.h"
#include "c2bTextEdit.h"
#include "c2bUpdateMetadata.h"
#include "c2bUtils.h"
#include "findDialog.h"

#include <bibSearcher.h>
#include <texToHtml.h>

#include <QCloseEvent>
#include <QDir>
#include <QDockWidget>
#include <QLabel>
#include <QMessageBox>
#include <QStackedWidget>
#include <QTextCursor>
#include <QTextStream>


/** \page bibeditor Embedded File Editor

<p>GET_TABLE_OF_CONTENTS</p>


  cb2Bib contains a practical editor suitable to manipulate the files
  related to a cb2Bib session. Abbreviations, bookmarks, regular expressions,
  and BibTeX are readily available. On BibTeX mode, the editor contains a
  Reference List to ease file navigation, and to extend the editor
  functionality. The BibTeX editor can optionally be turned to a reference
  browser.


  \section bookmarks Bookmarks

  Bookmarks pointing to local or network files are available at the editor menu
  bar. They provide a fast access to external resources. Concretely, they are
  suitable for retrieving working documents, writing notes, or for accessing
  internet databases.

  The editor bookmark functionality had been introduced in the cb2Bib version
  0.9.3. Currently, bookmarks are set manually in the <tt>netqinf.txt</tt>
  file, see \ref c2bconf_files. Each bookmark is an entry line with the form
\verbatim
editorbookmark=Description|Target file name|Shortcut|Icon file name
\endverbatim
    having four fields, description, target file name, shortcut, and icon
    file name, separated with three (required) vertical bars |.
\verbatim
# Bookmark Examples:
# - A URL:
editorbookmark=URL Description|https://www.molspaces.com/cb2bib/doc/bibeditor/||
# - A separator, which is a blank line:
editorbookmark=
# - A TeX document, which will be opened with its default application:
editorbookmark=Document Description|/home/doc/chapter1.tex||
\endverbatim


  \section update_metadata Update Documents Metadata

  The Update Documents Metadata functionality is available at the Edit and
  context menus on the BibTeX editor mode. Documents referred in the BibTeX
  file tags are scanned for metadata. If the BibTeX reference does not coincide
  with the bibliographic metadata, the document metadata is updated. In this
  way, metadata is synchronized with the BibTeX file contents. A log window
  appears, and possible errors are reported. Reported errors are, non-existence
  of a document file, read-only files, mismatches between BibTeX references and
  the actual metadata (often due to HTML tags or other illegal characters in
  BibTeX), or that the writing to the document format is not implemented. Note
  that this process will update all documents referenced in the BibTeX file.
  <b>While this process is safe, it implies writing into the documents.</b>
  Therefore take the usual measures and backup your data. See also \ref
  metadata_write.


  \section export_entries Export Selected Entries

  Selected entries can be exported to a separate BibTeX document. Click on
  <tt>File->Export Entries</tt> menu option, and provide an export filename at
  the Export Dialog. Optionally, export will copy the document files attached
  to the citation. The copy of documents is similar to the cb2Bib
  'rename/copy/move' general procedure. See \ref c2bconf_documents, on <b>Set
  directory relative to the BibTeX File Directory</b>, for copying options.
  Documents will not be overwritten: copying of existing documents is skipped.
  Possible issues are reported in the new document, as LaTeX comments.


  \section c2beditor_menu Right-Click Menu Functionality

\htmlonly
<center><table cellpadding="4" cellspacing="2" border="1"
summary="Summary table of Right-Click Menu Functionality">
<tr> <th valign="top">Default Key</th> <th valign="top">Action</th></tr>
<tr> <td valign="top">Ctrl+F</td> <td valign="top">Find in text</td></tr>
<tr> <td valign="top"></td> <td valign="top">Toggle word wrapping</td></tr>
<tr> <td valign="top"></td> <td valign="top">Selection to LaTeX</td></tr>
<tr> <td valign="top"></td> <td valign="top">Selection to Unicode</td></tr>
<tr> <td valign="top"></td> <td valign="top">Journals to full name</td></tr>
<tr> <td valign="top"></td> <td valign="top">Journals to alternate full name</td></tr>
<tr> <td valign="top"></td> <td valign="top">Journals to abbreviated name</td></tr>
<tr> <td valign="top"></td> <td valign="top">Journals to alternate abbreviated name</td></tr>
<tr> <td valign="top"></td> <td valign="top">Update documents metadata</td></tr>
<tr> <td valign="top">Shift+Ins</td> <td valign="top">Paste current BibTeX</td></tr>
<tr> <td valign="top">Alt+P</td> <td valign="top">Save and postprocess BibTeX file</td></tr>
</table></center>
\endhtmlonly

  \section references_menu Reference List Right-Click Menu Functionality

\htmlonly
<center><table cellpadding="4" cellspacing="2" border="1"
summary="Summary table of References Right-Click Menu Functionality">
<tr> <th valign="top">Default Key</th> <th valign="top">Action</th></tr>
<tr> <td valign="top">Alt+C</td> <td valign="top">Cite selected entries</td></tr>
<tr> <td valign="top"></td> <td valign="top">Open document file</td></tr>
<tr> <td valign="top"></td> <td valign="top">Browse by DOI</td></tr>
<tr> <td valign="top"></td> <td valign="top">Web search by Author</td></tr>
<tr> <td valign="top"></td> <td valign="top">Web search by Title</td></tr>
<tr> <td valign="top"></td> <td valign="top">Web search settings</td></tr>
<tr> <td valign="top"></td> <td valign="top">Clear entry selection</td></tr>
<tr> <td valign="top"></td> <td valign="top">Refresh list and browser</td></tr>
</table></center>
\endhtmlonly

  \section browser_menu BibTeX Browser Right-Click Menu Functionality

\htmlonly
<center><table cellpadding="4" cellspacing="2" border="1"
summary="Summary table of Browser Right-Click Menu Functionality">
<tr> <th valign="top">Default Key</th> <th valign="top">Action</th></tr>
<tr> <td valign="top">Alt+C</td> <td valign="top">Cite selected entries</td></tr>
<tr> <td valign="top"></td> <td valign="top">Local search for selected text</td></tr>
<tr> <td valign="top"></td> <td valign="top">Web search for selected text</td></tr>
<tr> <td valign="top"></td> <td valign="top">Web search settings</td></tr>
<tr> <td valign="top"></td> <td valign="top">Clear entry selection</td></tr>
<tr> <td valign="top"></td> <td valign="top">Refresh list and browser</td></tr>
</table></center>
\endhtmlonly

  \section c2beditor_qt Additional Functionality

\htmlonly
<center><table cellpadding="4" cellspacing="2" border="1"
summary="Summary table of Additional Functionality">
<tr> <td valign="top">Backspace</td> <td valign="top">Deletes the character to the left of the cursor</td></tr>
<tr> <td valign="top">Delete</td> <td valign="top">Deletes the character to the right of the cursor</td></tr>
<tr> <td valign="top">Ctrl+A</td> <td valign="top">Selects all text</td></tr>
<tr> <td valign="top">Ctrl+C</td> <td valign="top">Copy the selected text to the clipboard</td></tr>
<tr> <td valign="top">Ctrl+Insert</td> <td valign="top">Copy the selected text to the clipboard</td></tr>
<tr> <td valign="top">Ctrl+K</td> <td valign="top">Deletes to the end of the line</td></tr>
<tr> <td valign="top">Ctrl+V</td> <td valign="top">Pastes the clipboard text into text edit</td></tr>
<tr> <td valign="top">Shift+Insert</td> <td valign="top">Pastes the clipboard text into text edit</td></tr>
<tr> <td valign="top">Ctrl+X</td> <td valign="top">Deletes the selected text and copies it to the clipboard</td></tr>
<tr> <td valign="top">Shift+Delete</td> <td valign="top">Deletes the selected text and copies it to the
clipboard</td></tr>
<tr> <td valign="top">Ctrl+Z</td> <td valign="top">Undoes the last operation</td></tr>
<tr> <td valign="top">Ctrl+Y</td> <td valign="top">Redoes the last operation</td></tr>
<tr> <td valign="top">LeftArrow</td> <td valign="top">Moves the cursor one character to the left</td></tr>
<tr> <td valign="top">Ctrl+LeftArrow</td> <td valign="top">Moves the cursor one word to the left</td></tr>
<tr> <td valign="top">RightArrow</td> <td valign="top">Moves the cursor one character to the right</td></tr>
<tr> <td valign="top">Ctrl+RightArrow</td> <td valign="top">Moves the cursor one word to the right</td></tr>
<tr> <td valign="top">UpArrow</td> <td valign="top">Moves the cursor one line up</td></tr>
<tr> <td valign="top">Ctrl+UpArrow</td> <td valign="top">Moves the cursor one word up</td></tr>
<tr> <td valign="top">DownArrow</td> <td valign="top">Moves the cursor one line down</td></tr>
<tr> <td valign="top">Ctrl+Down Arrow</td> <td valign="top">Moves the cursor one word down</td></tr>
<tr> <td valign="top">PageUp</td> <td valign="top">Moves the cursor one page up</td></tr>
<tr> <td valign="top">PageDown</td> <td valign="top">Moves the cursor one page down</td></tr>
<tr> <td valign="top">Home</td> <td valign="top">Moves the cursor to the beginning of the line</td></tr>
<tr> <td valign="top">Ctrl+Home</td> <td valign="top">Moves the cursor to the beginning of the text</td></tr>
<tr> <td valign="top">End</td> <td valign="top">Moves the cursor to the end of the line</td></tr>
<tr> <td valign="top">Ctrl+End</td> <td valign="top">Moves the cursor to the end of the text</td></tr>
<tr> <td valign="top">Alt+Wheel</td> <td valign="top">Scrolls the page horizontally</td></tr>
<tr> <td valign="top">Ctrl+Wheel</td> <td valign="top">Zooms the text</td></tr>
</table></center>
\endhtmlonly

*/


c2bEditor::c2bEditor(const QString& file, const Mode mode, QWidget* main, QWidget* parentw) : QMainWindow(parentw)
{
    _editor_fn = QDir::toNativeSeparators(file);
    _editor_mode = mode;
    _c2b_mainP = main;
    _searcherP = 0;
    initEditor();
}

c2bEditor::c2bEditor(const QString& file, bibSearcher* searcher, QWidget* main, QWidget* parentw) : QMainWindow(parentw)
{
    _editor_fn = QDir::toNativeSeparators(file);
    _editor_mode = BibTeX;
    _c2b_mainP = main;
    _searcherP = searcher;
    initEditor();
}

c2bEditor::~c2bEditor()
{
    if (_browserP)
        _settingsP->setValue("c2bEditor/BrowserFontPointSize", _browserP->font().pointSize());
}


void c2bEditor::initEditor()
{
    ui.setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    _settingsP = c2bSettingsP;
    if (_editor_mode == BibTeX)
        _bpP = c2b::bibParser();
    else
        _bpP = 0;
    _browserP = 0;
    _editorP = new c2bTextEdit(this);
    _referencesP = 0;
    _stackedWidgetP = new QStackedWidget(this);
    setCentralWidget(_stackedWidgetP);
    _stackedWidgetP->addWidget(_editorP);
    _textFinderP = new findDialog(this);
    _lineLabelP = new QLabel();
    _lineLabelP->setText(tr(" Line: 1  Col: 1 "));
    _lineLabelP->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    _lineLabelP->setFrameStyle(QFrame::NoFrame);
    _lineLabelP->setLineWidth(1);
    _lineLabelP->setFixedHeight(_lineLabelP->fontMetrics().height());
    statusBar()->addWidget(_lineLabelP, 1);
    connect(_editorP, SIGNAL(cursorPositionChanged()), this, SLOT(cursorPositionChanged()));
    _overwriteLabelP = new QLabel();
    _overwriteLabelP->setText(tr(" INS "));
    _overwriteLabelP->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    _overwriteLabelP->setFrameStyle(QFrame::NoFrame);
    _overwriteLabelP->setLineWidth(1);
    _overwriteLabelP->setFixedHeight(_overwriteLabelP->fontMetrics().height());
    statusBar()->addWidget(_overwriteLabelP);
    _editorP->setOverwriteMode(false);
    connect(_editorP, SIGNAL(overwriteModeChanged()), this, SLOT(overwriteModeChanged()));
    connect(ui.fileCloseAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui.fileExecAction, SIGNAL(triggered()), this, SLOT(saveAndExecute()));
    connect(ui.fileExitAction, SIGNAL(triggered()), c2b::instance(), SLOT(exitRequested()));
    connect(ui.fileSaveAction, SIGNAL(triggered()), this, SLOT(fileSave()));
    connect(ui.fileSaveAsAction, SIGNAL(triggered()), this, SLOT(fileSaveAs()));
    connect(ui.helpEditorAction, SIGNAL(triggered()), this, SLOT(helpEditor()));
    connect(ui.helpCb2BibAction, SIGNAL(triggered()), this, SLOT(helpCb2Bib()));
    connect(ui.viewCb2BibAction, SIGNAL(triggered()), this, SLOT(viewCb2Bib()));

    // Standard shortcuts
    ui.fileCloseAction->setShortcut(QKeySequence(QKeySequence::Close));
    ui.fileOpenAction->setShortcut(QKeySequence(QKeySequence::Open));
    ui.fileSaveAction->setShortcut(QKeySequence(QKeySequence::Save));
    ui.helpEditorAction->setShortcut(QKeySequence(QKeySequence::HelpContents));
    ui.viewZoomInAction->setShortcut(QKeySequence(QKeySequence::ZoomIn));
    ui.viewZoomOutAction->setShortcut(QKeySequence(QKeySequence::ZoomOut));
    ui.fileExitAction->setShortcut(QKeySequence(QKeySequence::Quit));
    ui.fileSaveAsAction->setShortcut(QKeySequence(QKeySequence::SaveAs));

    // Editor Settings
    resize(_settingsP->value("c2bEditor/size", size()).toSize());
    ui.menuView->addAction(ui.toolBar->toggleViewAction());
    ui.setLyXPipeAction->setVisible(false);
    _editorP->setFont(_settingsP->c2bMonoFont);
    connect(ui.settingsCb2BibAction, SIGNAL(triggered()), c2b::instance(), SLOT(configure()));

    // Bookmarks
    bookmarkPlugin* bookmarks = new bookmarkPlugin(this);
    menuBar()->insertMenu(ui.menuSettings->menuAction(), bookmarks);
    connect(bookmarks, SIGNAL(openFile(QString)), this, SIGNAL(openFile(QString)));
    connect(bookmarks, SIGNAL(editBookmarks()), this, SIGNAL(openBookmarks()));

    load();
    setEditorMode();
    importActions();
    QApplication::processEvents(); // Qt 4.7.0 emits contentsChange with position inconsistently defined, make sure it
    // is not captured
    connect(_editorP->document(), SIGNAL(contentsChange(int,int,int)), this, SLOT(isModified(int,int,int)));
    connect(c2b::instance(), SIGNAL(statusMessage(QString)), this, SLOT(showMessage(QString)));
}

void c2bEditor::setEditorMode()
{
    if (_editor_mode == RegExp)
    {
        _shP = new c2bREHighlighter(_editorP->document());
        ui.fileExecAction->setText(tr("Restart Recognition"));
        ui.fileExecAction->setStatusTip(tr("Restart recognition"));
        _settingsP->setKeysequence("Shortcuts/Editor/", ui.fileExecAction);
        connect(this, SIGNAL(execute()), this, SIGNAL(restartEngine()));
        ui.toolBar->setVisible(_settingsP->value("c2bEditor/ToolBar", true).toBool());
        setViewMode(true);
    }
    else if (_editor_mode == NetQInfo)
    {
        _shP = new c2bREHighlighter(_editorP->document());
        ui.fileExecAction->setText(tr("Restart Network Query"));
        ui.fileExecAction->setStatusTip(tr("Restart network query"));
        _settingsP->setKeysequence("Shortcuts/Editor/", ui.fileExecAction);
        connect(this, SIGNAL(execute()), this, SIGNAL(restartQuery()));
        ui.toolBar->setVisible(_settingsP->value("c2bEditor/ToolBar", true).toBool());
        setViewMode(true);
    }
    else if (_editor_mode == JAbbrev)
    {
        ui.fileExecAction->setVisible(false);
        ui.toolBar->setVisible(_settingsP->value("c2bEditor/ToolBar", true).toBool());
        setViewMode(true);
    }
    else if (_editor_mode == Annote)
    {
        _shP = new c2bBibHighlighter(_editorP->document());
        ui.fileExecAction->setText(tr("View Note in External Browser"));
        ui.fileExecAction->setStatusTip(tr("View Note in External Browser"));
        _settingsP->setKeysequence("Shortcuts/Editor/", ui.fileExecAction);
        _editorP->setLaTeXActions();
        connect(this, SIGNAL(execute()), this, SLOT(htmlView()));
        ui.toolBar->setVisible(_settingsP->value("c2bEditor/ToolBar", true).toBool());
        setViewMode(true);
    }
    else if (_editor_mode == BibTeX)
    {
        // Editor
        _shP = new c2bBibHighlighter(_editorP->document());
        ui.fileOpenAction->setVisible(true);
        connect(ui.fileOpenAction, SIGNAL(triggered()), this, SLOT(fileOpen()));
        _editorP->setBibTeXActions();
        connect(_editorP->pasteCurrentBibTeXAction, SIGNAL(triggered()), this, SLOT(pasteCurrentBibTeX()));
        connect(_editorP->journalsToAbbreviatedAction, SIGNAL(triggered()), this, SLOT(journalsToAbbreviated()));
        connect(_editorP->journalsToAlternateAbbreviatedAction, SIGNAL(triggered()), this,
                SLOT(journalsToAlternateAbbreviated()));
        connect(_editorP->journalsToFullAction, SIGNAL(triggered()), this, SLOT(journalsToFull()));
        connect(_editorP->journalsToAlternateFullAction, SIGNAL(triggered()), this, SLOT(journalsToAlternateFull()));
        connect(_editorP->updateMetadataAction, SIGNAL(triggered()), this, SLOT(updateMetadata()));
        connect(_c2b_mainP, SIGNAL(addedBibToFile(QString)), this, SLOT(reload(QString)));
        ui.fileExecAction->setText(tr("Save and Postprocess"));
        ui.fileExecAction->setStatusTip(tr("Save and postprocess"));
        _settingsP->setKeysequence("Shortcuts/Editor/", ui.fileExecAction);
        connect(this, SIGNAL(execute()), this, SLOT(postProcess()));

        // Browser
        _browserP = new c2bTextBrowser(this);
        _browserP->setFont(
            QFont(QFont().family(), _settingsP->value("c2bEditor/BrowserFontPointSize", QFont().pointSize()).toInt()));
        _stackedWidgetP->addWidget(_browserP);
        ui.viewEditorModeAction->setVisible(true);
        _settingsP->setKeysequence("Shortcuts/Editor/", ui.viewEditorModeAction);
        connect(ui.viewEditorModeAction, SIGNAL(triggered(bool)), this, SLOT(setViewMode(bool)));
        connect(ui.viewZoomInAction, SIGNAL(triggered()), _browserP, SLOT(zoomIn()));
        connect(ui.viewZoomOutAction, SIGNAL(triggered()), _browserP, SLOT(zoomOut()));

        // Reference List
        createReferenceList();
        _referencesP->loadList(_editorP->toPlainText(), _searcherP);
        bool edit_mode(false);
        if (_searcherP)
        {
            edit_mode = (_searcherP->hitsCount() == 0 && _searcherP->errorsCount() > 0);
            connect(_referencesP, SIGNAL(openFile(QString)), this, SIGNAL(openFile(QString)));
        }
        if (!_edit_reference_at_position.isEmpty())
        {
            edit_mode = true;
            _referencesP->goToReference(_edit_reference_at_position.toInt());
        }
        ui.viewEditorModeAction->setChecked(edit_mode);
        setViewMode(edit_mode);
        ui.setLyXPipeAction->setVisible(true);
        _settingsP->setKeysequence("Shortcuts/Editor/", ui.setLyXPipeAction);

        // Export entries
        ui.fileExportEntriesAction->setVisible(true);
        _settingsP->setKeysequence("Shortcuts/Editor/", ui.fileExportEntriesAction);
        connect(ui.fileExportEntriesAction, SIGNAL(triggered()), this, SLOT(exportEntries()));
        connect(_referencesP, SIGNAL(hasSelectedItems(bool)), ui.fileExportEntriesAction, SLOT(setEnabled(bool)));
    }
    else
        c2bUtils::debug(tr("c2bEditor::setEditorMode: '%1' invalid Editor Mode.").arg(_editor_mode));
}

void c2bEditor::importActions()
{
    QList<QAction*> acts = _textFinderP->actions();
    for (int i = 0; i < acts.count(); ++i)
        ui.menuEdit->addAction(acts.at(i));
    acts = _editorP->actions();
    for (int i = 0; i < acts.count(); ++i)
        ui.menuEdit->addAction(acts.at(i));
    if (_browserP)
    {
        ui.menuEdit->addSeparator();
        acts = _browserP->actions();
        for (int i = 0; i < acts.count(); ++i)
            ui.menuEdit->addAction(acts.at(i));
    }
}

void c2bEditor::createReferenceList()
{
    _dockWidgetP = new QDockWidget(this);
    _dockWidgetP->setObjectName("dwRList");
    _referencesP = new c2bReferenceList(_editorP, _browserP, _dockWidgetP);
    addDockWidget(Qt::BottomDockWidgetArea, _dockWidgetP);
    _dockWidgetP->setWidget(_referencesP);
    _dockWidgetP->setWindowTitle("Reference List");
    QByteArray state = _settingsP->value("c2bEditor/state").toByteArray();
    restoreState(state);
    ui.menuView->addAction(_dockWidgetP->toggleViewAction());
    // State contains toolBar info, too, but it can be changed from non BibTeX editors
    // State can not be used for non BibTeX editors. They don't have referenceList.
    ui.toolBar->setVisible(_settingsP->value("c2bEditor/ToolBar", true).toBool());
    connect(ui.setLyXPipeAction, SIGNAL(triggered()), _referencesP, SLOT(setLyXPipe()));
}

void c2bEditor::closeEvent(QCloseEvent* qevent)
{
    if (closeEditor())
        qevent->accept();
    else
        qevent->ignore();
}

bool c2bEditor::closeEditor()
{
    // Use _is_modified_by_user to check if closing is possible. This way,
    // no question is asked to exit browsing of search results. Do not use
    // here ui.fileSaveAction->isEnabled().
    if (_is_modified_by_user)
    {
        const int button(QMessageBox::information(
                             this, tr("Information - cb2Bib"), tr("The document has been modified.\nDo you want to save the changes?"),
                             QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Save));
        if (button == QMessageBox::Save)
        {
            if (!fileSave())
                return false;
        }
        else if (button == QMessageBox::Cancel)
            return false;
    }
    _settingsP->setValue("c2bEditor/size", size());
    if (_editor_mode == BibTeX)
        _settingsP->setValue("c2bEditor/state", saveState());
    _settingsP->setValue("c2bEditor/ToolBar", !ui.toolBar->isHidden());
    return true;
}

void c2bEditor::isModified(int position, int charsRemoved, int charsAdded)
{
    if (position == 0 && charsAdded == charsRemoved)
        return;
    ui.fileSaveAction->setEnabled(true);
    setWindowModified(true);
    _is_modified_by_user = true;
}

void c2bEditor::fileOpen()
{
    if (_editor_mode == BibTeX)
    {
        const QString filename(
            c2bFileDialog::getOpenFilename(this, "Select a BibTeX filename", _editor_fn, "BibTeX (*.bib)"));
        if (!filename.isEmpty())
            emit openFile(filename);
    }
}

bool c2bEditor::fileSave()
{
    if (_editor_fn.contains("unnamed_"))
        return fileSaveAs();
    QFile file(_editor_fn);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(
            this, tr("Warning - cb2Bib"),
            tr("Unable to open the file %1 for writing.\nError: '%2'.").arg(_editor_fn, file.errorString()),
            QMessageBox::Ok);
        return false;
    }
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    stream.setAutoDetectUnicode(true);
    stream << _editorP->toPlainText();
    ui.fileSaveAction->setEnabled(false);
    _editorP->document()->setModified(false);
    setWindowModified(false);
    _is_modified_by_user = false;
    return true;
}

bool c2bEditor::fileSaveAs()
{
    QString filename;
    if (_editor_mode == BibTeX)
        filename = c2bFileDialog::getSaveFilename(this, QString(), _editor_fn, "BibTeX (*.bib);;All (*)");
    else if (_editor_mode == Annote)
        filename = c2bFileDialog::getSaveFilename(this, QString(), _editor_fn, "LaTeX (*.tex);;All (*)");
    else
        filename = c2bFileDialog::getSaveFilename(this, QString(), _editor_fn, "Text (*.txt);;All (*)");
    if (filename.isEmpty() || filename.contains("unnamed_"))
        return false;
    const QString old_name(_editor_fn);
    _editor_fn = filename;
    setWindowTitle(tr("%1[*] - cb2Bib").arg(_editor_fn));
    _editorP->setEditorFilename(_editor_fn);
    emit editFileRenamed(old_name, _editor_fn);
    return fileSave();
}

void c2bEditor::saveAndExecute()
{
    // Use ui.fileSaveAction->isEnabled() instead of _is_modified_by_user.
    // If browsing search results there is no file on disk.
    if (ui.fileSaveAction->isEnabled())
    {
        if (fileSave())
            emit execute();
    }
    else
        emit execute();
}

void c2bEditor::load()
{
    bool modified_flag(false);
    QFileInfo fi(_editor_fn);
    if (_editor_fn.isEmpty() || fi.isDir()) // Set an appropriate working name
    {
        QStringList unamedList;
        foreach (QWidget* widget, QApplication::topLevelWidgets())
        {
            if (widget->inherits("c2bEditor"))
                unamedList.append(widget->objectName());
        }
        int i(1);
        while (unamedList.indexOf(QRegExp(QString(".*unnamed_%1.bib").arg(i))) > -1)
            ++i;
        _editor_fn =
            QDir::toNativeSeparators(QDir::cleanPath(_editor_fn + QDir::separator() + QString("unnamed_%1.bib").arg(i)));
        if (_searcherP)
        {
            _editorP->setPlainText(_searcherP->logString() + _searcherP->hitsString());
            modified_flag = true;
        }
    }
    else
    {
        QRegExp edit_ref_id(":(\\d+)$");
        if (edit_ref_id.indexIn(_editor_fn) > -1)
        {
            _edit_reference_at_position = edit_ref_id.cap(1);
            _editor_fn.remove(edit_ref_id);
        }
        QFile file(_editor_fn);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(
                _c2b_mainP, tr("Warning - cb2Bib"),
                tr("Unable to open the file %1 for reading.\nError: '%2'.").arg(_editor_fn, file.errorString()),
                QMessageBox::Ok);
        }
        else
        {
            QTextStream stream(&file);
            stream.setCodec("UTF-8");
            stream.setAutoDetectUnicode(true);
            _editorP->setPlainText(stream.readAll());
        }
    }
    setWindowTitle(tr("%1[*] - cb2Bib").arg(_editor_fn));
    _editorP->setEditorFilename(_editor_fn);
    ui.fileSaveAction->setEnabled(modified_flag);
    _editorP->document()->setModified(modified_flag);
    setWindowModified(modified_flag);
    _is_modified_by_user = false;
}

void c2bEditor::reload(const QString& fn)
{
    // This function must be called ONLY in BibTeX mode
    // Pointers are undefined otherwise
    if (_editor_mode != BibTeX || _editor_fn != fn)
        return;

    if (ui.fileSaveAction->isEnabled())
    {
        QMessageBox msgBox(this);
        msgBox.addButton(tr("Discard and Reload"), QMessageBox::AcceptRole);
        msgBox.addButton(QMessageBox::Cancel);
        msgBox.setDefaultButton(msgBox.addButton(QMessageBox::Save));
        msgBox.setWindowTitle(tr("Information - cb2Bib"));
        msgBox.setText(tr("The document has been modified on disk when the reference was inserted. "
                          "No automatic reloading is done because it also has local changes. "
                          "To preserve local changes press Save and insert again the last reference.\n\n"
                          "Do you want to save the changes?"));
        msgBox.setIcon(QMessageBox::Information);
        const int button(msgBox.exec());
        if (button == QMessageBox::Save)
        {
            fileSave();
            _referencesP->refreshList();
            return;
        }
        else if (button == QMessageBox::Cancel)
            return;
    }
    load();
    _referencesP->refreshList();
    QTextCursor cur = _editorP->textCursor();
    cur.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
    _editorP->setTextCursor(cur);
    _editorP->ensureCursorVisible();
}

void c2bEditor::exportEntries()
{
    const QStringList keys(_referencesP->selectedKeys());
    if (keys.count() == 0)
        return;
    c2bExportDialog ed(_editor_fn, _editorP->toPlainText(), keys, this);
    if (ed.exec())
        emit openFile(ed.exportFilename());
}

void c2bEditor::pasteCurrentBibTeX()
{
    _editorP->insertPlainText(_bpP->toBibTeX(false));
}

void c2bEditor::journalsToFull()
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    const QString text(_bpP->setJournalsToFull(_editorP->toPlainText(), false));
    _editorP->updatePlainText(text);
    QApplication::restoreOverrideCursor();
}

void c2bEditor::journalsToAlternateFull()
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    const QString text(_bpP->setJournalsToFull(_editorP->toPlainText(), true));
    _editorP->updatePlainText(text);
    QApplication::restoreOverrideCursor();
}

void c2bEditor::journalsToAbbreviated()
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    const QString text(_bpP->setJournalsToAbbreviated(_editorP->toPlainText(), false));
    _editorP->updatePlainText(text);
    QApplication::restoreOverrideCursor();
}

void c2bEditor::journalsToAlternateAbbreviated()
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    const QString text(_bpP->setJournalsToAbbreviated(_editorP->toPlainText(), true));
    _editorP->updatePlainText(text);
    QApplication::restoreOverrideCursor();
}

void c2bEditor::updateMetadata()
{
    c2bUpdateMetadata um(this);
    um.update(_editor_fn, _editorP->toPlainText());
}

void c2bEditor::htmlView()
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    const QString html_filename(_editor_fn + ".html");
    texToHtml t2h;
    t2h.toHtml(c2bUtils::fileToString(_editor_fn), html_filename);
    c2bUtils::openFile(html_filename);
    QApplication::restoreOverrideCursor();
}

void c2bEditor::postProcess()
{
    c2bPostprocess* ppBib = new c2bPostprocess(_editor_fn, this);
    ppBib->show();
}

void c2bEditor::helpEditor()
{
    c2bUtils::displayHelp("https://www.molspaces.com/cb2bib/doc/bibeditor/");
}

void c2bEditor::helpCb2Bib()
{
    const QString umanual(QDir::cleanPath(_settingsP->applicationDataDir() + "/doc/cb2bib_user_manual.pdf"));
    if (QFileInfo::exists(umanual))
        c2bUtils::displayHelp(umanual);
    else
        c2bUtils::displayHelp("https://www.molspaces.com/cb2bib/doc/contents/");
}

void c2bEditor::viewCb2Bib()
{
    c2bUtils::setWidgetOnTop(_c2b_mainP);
}

void c2bEditor::setViewMode(bool edit_mode)
{
    QList<QAction*> acts;
    if (edit_mode)
    {
        _textFinderP->setEditor(_editorP);
        if (_browserP)
        {
            acts = _browserP->actions();
            for (int i = 0; i < acts.count(); ++i)
                acts.at(i)->setVisible(false);
            ui.viewZoomInAction->setVisible(false);
            ui.viewZoomOutAction->setVisible(false);
        }
        acts = _editorP->actions();
        for (int i = 0; i < acts.count(); ++i)
            acts.at(i)->setVisible(true);
        _overwriteLabelP->setVisible(true);
        _lineLabelP->setVisible(true);
        _stackedWidgetP->setCurrentWidget(_editorP);
    }
    else
    {
        // Browser defined
        _textFinderP->setEditor(_browserP);
        acts = _editorP->actions();
        for (int i = 0; i < acts.count(); ++i)
            acts.at(i)->setVisible(false);
        acts = _browserP->actions();
        for (int i = 0; i < acts.count(); ++i)
            acts.at(i)->setVisible(true);
        ui.viewZoomInAction->setVisible(true);
        ui.viewZoomOutAction->setVisible(true);
        _overwriteLabelP->setVisible(false);
        _lineLabelP->setVisible(false);
        _stackedWidgetP->setCurrentWidget(_browserP);
    }
}

void c2bEditor::showMessage(const QString& ms)
{
    statusBar()->showMessage(ms, C2B_MESSAGE_TIME);
}

void c2bEditor::cursorPositionChanged()
{
    int ln, lp;
    _editorP->cursorPosition(&ln, &lp);
    _lineLabelP->setText(tr(" Line: %1  Col: %2 ").arg(ln).arg(lp));
}

void c2bEditor::overwriteModeChanged()
{
    if (_editorP->overwriteMode())
        _overwriteLabelP->setText(tr(" OVR "));
    else
        _overwriteLabelP->setText(tr(" INS "));
}
