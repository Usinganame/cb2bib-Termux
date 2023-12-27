/********************************************************************************
** Form generated from reading UI file 'c2bEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.15.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C2BEDITOR_H
#define UI_C2BEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_c2bEditor
{
public:
    QAction *fileSaveAction;
    QAction *fileSaveAsAction;
    QAction *fileExecAction;
    QAction *fileCloseAction;
    QAction *fileExitAction;
    QAction *helpEditorAction;
    QAction *viewCb2BibAction;
    QAction *setLyXPipeAction;
    QAction *viewEditorModeAction;
    QAction *viewZoomInAction;
    QAction *viewZoomOutAction;
    QAction *helpCb2BibAction;
    QAction *settingsCb2BibAction;
    QAction *fileOpenAction;
    QAction *fileExportEntriesAction;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuHelp;
    QMenu *menuEdit;
    QMenu *menuView;
    QMenu *menuSettings;
    QMenu *menuFile;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *c2bEditor)
    {
        if (c2bEditor->objectName().isEmpty())
            c2bEditor->setObjectName(QString::fromUtf8("c2bEditor"));
        c2bEditor->resize(801, 600);
        fileSaveAction = new QAction(c2bEditor);
        fileSaveAction->setObjectName(QString::fromUtf8("fileSaveAction"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/filesave22.png"), QSize(), QIcon::Normal, QIcon::Off);
        fileSaveAction->setIcon(icon);
        fileSaveAsAction = new QAction(c2bEditor);
        fileSaveAsAction->setObjectName(QString::fromUtf8("fileSaveAsAction"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/filesaveas22.png"), QSize(), QIcon::Normal, QIcon::Off);
        fileSaveAsAction->setIcon(icon1);
        fileExecAction = new QAction(c2bEditor);
        fileExecAction->setObjectName(QString::fromUtf8("fileExecAction"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/icons/exec22.png"), QSize(), QIcon::Normal, QIcon::Off);
        fileExecAction->setIcon(icon2);
        fileCloseAction = new QAction(c2bEditor);
        fileCloseAction->setObjectName(QString::fromUtf8("fileCloseAction"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/icons/fileclose22.png"), QSize(), QIcon::Normal, QIcon::Off);
        fileCloseAction->setIcon(icon3);
        fileExitAction = new QAction(c2bEditor);
        fileExitAction->setObjectName(QString::fromUtf8("fileExitAction"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/icons/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        fileExitAction->setIcon(icon4);
        helpEditorAction = new QAction(c2bEditor);
        helpEditorAction->setObjectName(QString::fromUtf8("helpEditorAction"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/icons/help16.png"), QSize(), QIcon::Normal, QIcon::Off);
        helpEditorAction->setIcon(icon5);
        viewCb2BibAction = new QAction(c2bEditor);
        viewCb2BibAction->setObjectName(QString::fromUtf8("viewCb2BibAction"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/icons/cb2bib22.png"), QSize(), QIcon::Normal, QIcon::Off);
        viewCb2BibAction->setIcon(icon6);
        setLyXPipeAction = new QAction(c2bEditor);
        setLyXPipeAction->setObjectName(QString::fromUtf8("setLyXPipeAction"));
        viewEditorModeAction = new QAction(c2bEditor);
        viewEditorModeAction->setObjectName(QString::fromUtf8("viewEditorModeAction"));
        viewEditorModeAction->setCheckable(true);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/icons/edit22.png"), QSize(), QIcon::Normal, QIcon::Off);
        viewEditorModeAction->setIcon(icon7);
        viewEditorModeAction->setVisible(false);
        viewZoomInAction = new QAction(c2bEditor);
        viewZoomInAction->setObjectName(QString::fromUtf8("viewZoomInAction"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/icons/viewZoomIn.png"), QSize(), QIcon::Normal, QIcon::Off);
        viewZoomInAction->setIcon(icon8);
        viewZoomInAction->setVisible(false);
        viewZoomOutAction = new QAction(c2bEditor);
        viewZoomOutAction->setObjectName(QString::fromUtf8("viewZoomOutAction"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icons/icons/viewZoomOut.png"), QSize(), QIcon::Normal, QIcon::Off);
        viewZoomOutAction->setIcon(icon9);
        viewZoomOutAction->setVisible(false);
        helpCb2BibAction = new QAction(c2bEditor);
        helpCb2BibAction->setObjectName(QString::fromUtf8("helpCb2BibAction"));
        helpCb2BibAction->setIcon(icon6);
        settingsCb2BibAction = new QAction(c2bEditor);
        settingsCb2BibAction->setObjectName(QString::fromUtf8("settingsCb2BibAction"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/icons/icons/configure.png"), QSize(), QIcon::Normal, QIcon::Off);
        settingsCb2BibAction->setIcon(icon10);
        fileOpenAction = new QAction(c2bEditor);
        fileOpenAction->setObjectName(QString::fromUtf8("fileOpenAction"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/icons/icons/fileopen22.png"), QSize(), QIcon::Normal, QIcon::Off);
        fileOpenAction->setIcon(icon11);
        fileOpenAction->setVisible(false);
        fileExportEntriesAction = new QAction(c2bEditor);
        fileExportEntriesAction->setObjectName(QString::fromUtf8("fileExportEntriesAction"));
        fileExportEntriesAction->setEnabled(false);
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/icons/icons/configure_bibtex.png"), QSize(), QIcon::Normal, QIcon::Off);
        fileExportEntriesAction->setIcon(icon12);
        fileExportEntriesAction->setVisible(false);
        centralwidget = new QWidget(c2bEditor);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        c2bEditor->setCentralWidget(centralwidget);
        menubar = new QMenuBar(c2bEditor);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 801, 30));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        c2bEditor->setMenuBar(menubar);
        statusbar = new QStatusBar(c2bEditor);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        c2bEditor->setStatusBar(statusbar);
        toolBar = new QToolBar(c2bEditor);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setOrientation(Qt::Horizontal);
        c2bEditor->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuSettings->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuHelp->addAction(helpEditorAction);
        menuHelp->addSeparator();
        menuHelp->addAction(helpCb2BibAction);
        menuEdit->addAction(setLyXPipeAction);
        menuView->addAction(viewEditorModeAction);
        menuView->addSeparator();
        menuView->addAction(viewCb2BibAction);
        menuView->addSeparator();
        menuView->addAction(viewZoomInAction);
        menuView->addAction(viewZoomOutAction);
        menuView->addSeparator();
        menuSettings->addAction(settingsCb2BibAction);
        menuFile->addAction(fileOpenAction);
        menuFile->addSeparator();
        menuFile->addAction(fileSaveAction);
        menuFile->addAction(fileSaveAsAction);
        menuFile->addAction(fileExecAction);
        menuFile->addSeparator();
        menuFile->addAction(fileExportEntriesAction);
        menuFile->addSeparator();
        menuFile->addAction(fileCloseAction);
        menuFile->addSeparator();
        menuFile->addAction(fileExitAction);
        toolBar->addAction(fileSaveAction);
        toolBar->addAction(fileExecAction);
        toolBar->addAction(viewEditorModeAction);
        toolBar->addAction(viewCb2BibAction);

        retranslateUi(c2bEditor);

        QMetaObject::connectSlotsByName(c2bEditor);
    } // setupUi

    void retranslateUi(QMainWindow *c2bEditor)
    {
        c2bEditor->setWindowTitle(QCoreApplication::translate("c2bEditor", "Editor - cb2Bib", nullptr));
        fileSaveAction->setText(QCoreApplication::translate("c2bEditor", "Save", nullptr));
#if QT_CONFIG(statustip)
        fileSaveAction->setStatusTip(QCoreApplication::translate("c2bEditor", "Save", nullptr));
#endif // QT_CONFIG(statustip)
        fileSaveAsAction->setText(QCoreApplication::translate("c2bEditor", "Save As...", nullptr));
        fileSaveAsAction->setIconText(QCoreApplication::translate("c2bEditor", "Save As", nullptr));
#if QT_CONFIG(tooltip)
        fileSaveAsAction->setToolTip(QCoreApplication::translate("c2bEditor", "Save As", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        fileSaveAsAction->setStatusTip(QCoreApplication::translate("c2bEditor", "Save as...", nullptr));
#endif // QT_CONFIG(statustip)
        fileExecAction->setText(QCoreApplication::translate("c2bEditor", "Exec", nullptr));
        fileCloseAction->setText(QCoreApplication::translate("c2bEditor", "Close Document", nullptr));
        fileCloseAction->setIconText(QCoreApplication::translate("c2bEditor", "Close Document", nullptr));
#if QT_CONFIG(tooltip)
        fileCloseAction->setToolTip(QCoreApplication::translate("c2bEditor", "Close Document", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        fileCloseAction->setStatusTip(QCoreApplication::translate("c2bEditor", "Close document", nullptr));
#endif // QT_CONFIG(statustip)
        fileExitAction->setText(QCoreApplication::translate("c2bEditor", "Exit", nullptr));
        fileExitAction->setIconText(QCoreApplication::translate("c2bEditor", "Exit cb2Bib", nullptr));
#if QT_CONFIG(tooltip)
        fileExitAction->setToolTip(QCoreApplication::translate("c2bEditor", "Exit cb2Bib", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        fileExitAction->setStatusTip(QCoreApplication::translate("c2bEditor", "Exit cb2Bib", nullptr));
#endif // QT_CONFIG(statustip)
        helpEditorAction->setText(QCoreApplication::translate("c2bEditor", "Editor Help", nullptr));
        helpEditorAction->setIconText(QCoreApplication::translate("c2bEditor", "Editor Help", nullptr));
#if QT_CONFIG(tooltip)
        helpEditorAction->setToolTip(QCoreApplication::translate("c2bEditor", "Editor Help", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        helpEditorAction->setStatusTip(QCoreApplication::translate("c2bEditor", "Editor context help", nullptr));
#endif // QT_CONFIG(statustip)
        viewCb2BibAction->setText(QCoreApplication::translate("c2bEditor", "Toggle cb2Bib", nullptr));
        viewCb2BibAction->setIconText(QCoreApplication::translate("c2bEditor", "Toggle cb2Bib", nullptr));
#if QT_CONFIG(statustip)
        viewCb2BibAction->setStatusTip(QCoreApplication::translate("c2bEditor", "Toggle cb2Bib", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        viewCb2BibAction->setShortcut(QCoreApplication::translate("c2bEditor", "F2", nullptr));
#endif // QT_CONFIG(shortcut)
        setLyXPipeAction->setText(QCoreApplication::translate("c2bEditor", "Set LyX Pipe", nullptr));
        setLyXPipeAction->setIconText(QCoreApplication::translate("c2bEditor", "Set active LyX pipe", nullptr));
#if QT_CONFIG(tooltip)
        setLyXPipeAction->setToolTip(QCoreApplication::translate("c2bEditor", "Set LyX pipe", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        setLyXPipeAction->setStatusTip(QCoreApplication::translate("c2bEditor", "Set active LyX pipe", nullptr));
#endif // QT_CONFIG(statustip)
        viewEditorModeAction->setText(QCoreApplication::translate("c2bEditor", "Toggle Editing and Browsing", nullptr));
        viewEditorModeAction->setIconText(QCoreApplication::translate("c2bEditor", "Toggle Editing and Browsing", nullptr));
#if QT_CONFIG(tooltip)
        viewEditorModeAction->setToolTip(QCoreApplication::translate("c2bEditor", "Toggle Editing and Browsing", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        viewEditorModeAction->setStatusTip(QCoreApplication::translate("c2bEditor", "Toggle editing and browsing modes", nullptr));
#endif // QT_CONFIG(statustip)
        viewZoomInAction->setText(QCoreApplication::translate("c2bEditor", "Zoom In", nullptr));
#if QT_CONFIG(statustip)
        viewZoomInAction->setStatusTip(QCoreApplication::translate("c2bEditor", "Zoom in", nullptr));
#endif // QT_CONFIG(statustip)
        viewZoomOutAction->setText(QCoreApplication::translate("c2bEditor", "Zoom Out", nullptr));
#if QT_CONFIG(statustip)
        viewZoomOutAction->setStatusTip(QCoreApplication::translate("c2bEditor", "Zoom out", nullptr));
#endif // QT_CONFIG(statustip)
        helpCb2BibAction->setText(QCoreApplication::translate("c2bEditor", "cb2Bib Help", nullptr));
        helpCb2BibAction->setIconText(QCoreApplication::translate("c2bEditor", "cb2Bib Help", nullptr));
#if QT_CONFIG(tooltip)
        helpCb2BibAction->setToolTip(QCoreApplication::translate("c2bEditor", "cb2Bib Help", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        helpCb2BibAction->setStatusTip(QCoreApplication::translate("c2bEditor", "cb2Bib context help", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        helpCb2BibAction->setShortcut(QCoreApplication::translate("c2bEditor", "Shift+F1", nullptr));
#endif // QT_CONFIG(shortcut)
        settingsCb2BibAction->setText(QCoreApplication::translate("c2bEditor", "cb2Bib Settings", nullptr));
        settingsCb2BibAction->setIconText(QCoreApplication::translate("c2bEditor", "cb2Bib Settings", nullptr));
#if QT_CONFIG(tooltip)
        settingsCb2BibAction->setToolTip(QCoreApplication::translate("c2bEditor", "cb2Bib Settings", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        settingsCb2BibAction->setStatusTip(QCoreApplication::translate("c2bEditor", "cb2Bib settings", nullptr));
#endif // QT_CONFIG(statustip)
        fileOpenAction->setText(QCoreApplication::translate("c2bEditor", "Open", nullptr));
        fileOpenAction->setIconText(QCoreApplication::translate("c2bEditor", "Open", nullptr));
#if QT_CONFIG(statustip)
        fileOpenAction->setStatusTip(QCoreApplication::translate("c2bEditor", "Open document", nullptr));
#endif // QT_CONFIG(statustip)
        fileExportEntriesAction->setText(QCoreApplication::translate("c2bEditor", "Export Entries", nullptr));
        fileExportEntriesAction->setIconText(QCoreApplication::translate("c2bEditor", "Export Entries", nullptr));
#if QT_CONFIG(tooltip)
        fileExportEntriesAction->setToolTip(QCoreApplication::translate("c2bEditor", "Export Entries", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        fileExportEntriesAction->setStatusTip(QCoreApplication::translate("c2bEditor", "Export selected entries", nullptr));
#endif // QT_CONFIG(statustip)
        menuHelp->setTitle(QCoreApplication::translate("c2bEditor", "&Help", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("c2bEditor", "&Edit", nullptr));
        menuView->setTitle(QCoreApplication::translate("c2bEditor", "&View", nullptr));
        menuSettings->setTitle(QCoreApplication::translate("c2bEditor", "&Settings", nullptr));
        menuFile->setTitle(QCoreApplication::translate("c2bEditor", "&File", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("c2bEditor", "Tools", nullptr));
    } // retranslateUi

};

namespace Ui {
    class c2bEditor: public Ui_c2bEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C2BEDITOR_H
