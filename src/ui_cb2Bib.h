/********************************************************************************
** Form generated from reading UI file 'cb2Bib.ui'
**
** Created by: Qt User Interface Compiler version 5.15.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CB2BIB_H
#define UI_CB2BIB_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "c2bComboBox.h"
#include "c2bLineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_cb2Bib
{
public:
    QAction *clearFieldsAction;
    QAction *insertRegExpAction;
    QAction *editBookmarksAction;
    QAction *editRegExpsAction;
    QAction *guessFieldsAction;
    QAction *postprocessBibTeXAction;
    QAction *preparseClipboardAction;
    QAction *startEngineAction;
    QAction *viewTaggedClipEditAction;
    QAction *openFileDocumentAction;
    QAction *editAbbreviationsAction;
    QAction *selectFileAction;
    QAction *openAnnoteAction;
    QAction *checkRepeatedAction;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QPushButton *ViewAboutB;
    QPushButton *ConfigureB;
    QPushButton *SearchInFilesB;
    QPushButton *PdfImportB;
    QSpacerItem *spacerItem;
    QPushButton *ExitB;
    QSpacerItem *spacerItem1;
    QPushButton *ConnectB;
    QPushButton *MakeNetworkQueryB;
    QPushButton *ViewBibB;
    QPushButton *AddBibB;
    QPushButton *EditBibTeXB;
    QStackedWidget *stackedWidget;
    QWidget *widget;
    QToolButton *BibTeXDir;
    c2bComboBox *bibtexfile;
    QLabel *TextLabel31;
    QFrame *line_2;
    QFrame *line;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout1;
    QLabel *textLabel1;
    QLabel *textLabel2;
    c2bComboBox *typecombo;
    QLabel *textLabel3;
    QLabel *textLabel4;
    QLabel *textLabel5;
    QLabel *textLabel6;
    QLabel *textLabel7;
    QLabel *textLabel8;
    QLabel *textLabel9;
    QLabel *textLabel10;
    QLabel *textLabel11;
    QLabel *textLabel12;
    c2bLineEdit *id;
    c2bLineEdit *title;
    c2bLineEdit *author;
    c2bLineEdit *journal;
    c2bLineEdit *pages;
    c2bLineEdit *volume;
    c2bLineEdit *number;
    c2bLineEdit *year;
    c2bLineEdit *abstract;
    c2bLineEdit *keywords;
    c2bLineEdit *file;
    QWidget *tab_2;
    QGridLayout *gridLayout2;
    QLabel *textLabel13;
    QLabel *textLabel14;
    QLabel *textLabel15;
    QLabel *textLabel16;
    QLabel *textLabel17;
    QLabel *textLabel18;
    QLabel *textLabel19;
    QLabel *textLabel20;
    QLabel *textLabel21;
    QLabel *textLabel22;
    QLabel *textLabel23;
    QLabel *textLabel24;
    QLabel *textLabel25;
    QLabel *textLabel26;
    QLabel *textLabel27;
    QLabel *textLabel28;
    QLabel *textLabel29;
    QLabel *textLabel30;
    c2bLineEdit *booktitle;
    c2bLineEdit *annote;
    c2bLineEdit *address;
    c2bLineEdit *edition;
    c2bLineEdit *institution;
    c2bLineEdit *month;
    c2bLineEdit *publisher;
    c2bLineEdit *chapter;
    c2bLineEdit *editor;
    c2bLineEdit *isbn;
    c2bLineEdit *note;
    c2bLineEdit *school;
    c2bLineEdit *doi;
    c2bLineEdit *eprint;
    c2bLineEdit *issn;
    c2bLineEdit *organization;
    c2bLineEdit *series;
    c2bLineEdit *url;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *cb2Bib)
    {
        if (cb2Bib->objectName().isEmpty())
            cb2Bib->setObjectName(QString::fromUtf8("cb2Bib"));
        cb2Bib->resize(1432, 820);
        clearFieldsAction = new QAction(cb2Bib);
        clearFieldsAction->setObjectName(QString::fromUtf8("clearFieldsAction"));
        insertRegExpAction = new QAction(cb2Bib);
        insertRegExpAction->setObjectName(QString::fromUtf8("insertRegExpAction"));
        editBookmarksAction = new QAction(cb2Bib);
        editBookmarksAction->setObjectName(QString::fromUtf8("editBookmarksAction"));
        editRegExpsAction = new QAction(cb2Bib);
        editRegExpsAction->setObjectName(QString::fromUtf8("editRegExpsAction"));
        guessFieldsAction = new QAction(cb2Bib);
        guessFieldsAction->setObjectName(QString::fromUtf8("guessFieldsAction"));
        postprocessBibTeXAction = new QAction(cb2Bib);
        postprocessBibTeXAction->setObjectName(QString::fromUtf8("postprocessBibTeXAction"));
        preparseClipboardAction = new QAction(cb2Bib);
        preparseClipboardAction->setObjectName(QString::fromUtf8("preparseClipboardAction"));
        startEngineAction = new QAction(cb2Bib);
        startEngineAction->setObjectName(QString::fromUtf8("startEngineAction"));
        viewTaggedClipEditAction = new QAction(cb2Bib);
        viewTaggedClipEditAction->setObjectName(QString::fromUtf8("viewTaggedClipEditAction"));
        viewTaggedClipEditAction->setCheckable(true);
        openFileDocumentAction = new QAction(cb2Bib);
        openFileDocumentAction->setObjectName(QString::fromUtf8("openFileDocumentAction"));
        editAbbreviationsAction = new QAction(cb2Bib);
        editAbbreviationsAction->setObjectName(QString::fromUtf8("editAbbreviationsAction"));
        selectFileAction = new QAction(cb2Bib);
        selectFileAction->setObjectName(QString::fromUtf8("selectFileAction"));
        openAnnoteAction = new QAction(cb2Bib);
        openAnnoteAction->setObjectName(QString::fromUtf8("openAnnoteAction"));
        checkRepeatedAction = new QAction(cb2Bib);
        checkRepeatedAction->setObjectName(QString::fromUtf8("checkRepeatedAction"));
        centralwidget = new QWidget(cb2Bib);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
#ifndef Q_OS_MAC
        gridLayout->setSpacing(6);
#endif
        gridLayout->setContentsMargins(6, 6, 6, 6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        hboxLayout->setContentsMargins(0, 0, 0, 0);
#endif
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        ViewAboutB = new QPushButton(centralwidget);
        ViewAboutB->setObjectName(QString::fromUtf8("ViewAboutB"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/cb2bib.png"), QSize(), QIcon::Normal, QIcon::Off);
        ViewAboutB->setIcon(icon);
        ViewAboutB->setIconSize(QSize(32, 32));

        hboxLayout->addWidget(ViewAboutB);

        ConfigureB = new QPushButton(centralwidget);
        ConfigureB->setObjectName(QString::fromUtf8("ConfigureB"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/configure.png"), QSize(), QIcon::Normal, QIcon::Off);
        ConfigureB->setIcon(icon1);
        ConfigureB->setIconSize(QSize(32, 32));

        hboxLayout->addWidget(ConfigureB);

        SearchInFilesB = new QPushButton(centralwidget);
        SearchInFilesB->setObjectName(QString::fromUtf8("SearchInFilesB"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/icons/tex.png"), QSize(), QIcon::Normal, QIcon::Off);
        SearchInFilesB->setIcon(icon2);
        SearchInFilesB->setIconSize(QSize(32, 32));

        hboxLayout->addWidget(SearchInFilesB);

        PdfImportB = new QPushButton(centralwidget);
        PdfImportB->setObjectName(QString::fromUtf8("PdfImportB"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/icons/pdf.png"), QSize(), QIcon::Normal, QIcon::Off);
        PdfImportB->setIcon(icon3);
        PdfImportB->setIconSize(QSize(32, 32));

        hboxLayout->addWidget(PdfImportB);

        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        ExitB = new QPushButton(centralwidget);
        ExitB->setObjectName(QString::fromUtf8("ExitB"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/icons/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        ExitB->setIcon(icon4);
        ExitB->setIconSize(QSize(32, 32));

        hboxLayout->addWidget(ExitB);

        spacerItem1 = new QSpacerItem(205, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem1);

        ConnectB = new QPushButton(centralwidget);
        ConnectB->setObjectName(QString::fromUtf8("ConnectB"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/icons/connect_established.png"), QSize(), QIcon::Normal, QIcon::Off);
        ConnectB->setIcon(icon5);
        ConnectB->setIconSize(QSize(32, 32));

        hboxLayout->addWidget(ConnectB);

        MakeNetworkQueryB = new QPushButton(centralwidget);
        MakeNetworkQueryB->setObjectName(QString::fromUtf8("MakeNetworkQueryB"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/icons/package_network.png"), QSize(), QIcon::Normal, QIcon::Off);
        MakeNetworkQueryB->setIcon(icon6);
        MakeNetworkQueryB->setIconSize(QSize(32, 32));

        hboxLayout->addWidget(MakeNetworkQueryB);

        ViewBibB = new QPushButton(centralwidget);
        ViewBibB->setObjectName(QString::fromUtf8("ViewBibB"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/icons/viewbib.png"), QSize(), QIcon::Normal, QIcon::Off);
        ViewBibB->setIcon(icon7);
        ViewBibB->setIconSize(QSize(32, 32));

        hboxLayout->addWidget(ViewBibB);

        AddBibB = new QPushButton(centralwidget);
        AddBibB->setObjectName(QString::fromUtf8("AddBibB"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/icons/filesaveas.png"), QSize(), QIcon::Normal, QIcon::Off);
        AddBibB->setIcon(icon8);
        AddBibB->setIconSize(QSize(32, 32));

        hboxLayout->addWidget(AddBibB);

        EditBibTeXB = new QPushButton(centralwidget);
        EditBibTeXB->setObjectName(QString::fromUtf8("EditBibTeXB"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icons/icons/edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        EditBibTeXB->setIcon(icon9);
        EditBibTeXB->setIconSize(QSize(32, 32));

        hboxLayout->addWidget(EditBibTeXB);


        gridLayout->addLayout(hboxLayout, 5, 0, 1, 3);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        widget = new QWidget();
        widget->setObjectName(QString::fromUtf8("widget"));
        stackedWidget->addWidget(widget);

        gridLayout->addWidget(stackedWidget, 1, 0, 1, 3);

        BibTeXDir = new QToolButton(centralwidget);
        BibTeXDir->setObjectName(QString::fromUtf8("BibTeXDir"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/icons/icons/mimeFolder.png"), QSize(), QIcon::Normal, QIcon::Off);
        BibTeXDir->setIcon(icon10);

        gridLayout->addWidget(BibTeXDir, 3, 2, 1, 1);

        bibtexfile = new c2bComboBox(centralwidget);
        bibtexfile->setObjectName(QString::fromUtf8("bibtexfile"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(bibtexfile->sizePolicy().hasHeightForWidth());
        bibtexfile->setSizePolicy(sizePolicy1);
        bibtexfile->setEditable(true);
        bibtexfile->setFrame(true);

        gridLayout->addWidget(bibtexfile, 3, 1, 1, 1);

        TextLabel31 = new QLabel(centralwidget);
        TextLabel31->setObjectName(QString::fromUtf8("TextLabel31"));

        gridLayout->addWidget(TextLabel31, 3, 0, 1, 1);

        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 2, 0, 1, 3);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 4, 0, 1, 3);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy2);
        tabWidget->setTabPosition(QTabWidget::South);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout1 = new QGridLayout(tab);
#ifndef Q_OS_MAC
        gridLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout1->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        textLabel1 = new QLabel(tab);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));

        gridLayout1->addWidget(textLabel1, 6, 0, 1, 1);

        textLabel2 = new QLabel(tab);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));

        gridLayout1->addWidget(textLabel2, 7, 0, 1, 1);

        typecombo = new c2bComboBox(tab);
        typecombo->setObjectName(QString::fromUtf8("typecombo"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(typecombo->sizePolicy().hasHeightForWidth());
        typecombo->setSizePolicy(sizePolicy3);
        typecombo->setEditable(true);
        typecombo->setDuplicatesEnabled(false);

        gridLayout1->addWidget(typecombo, 0, 5, 1, 3);

        textLabel3 = new QLabel(tab);
        textLabel3->setObjectName(QString::fromUtf8("textLabel3"));

        gridLayout1->addWidget(textLabel3, 0, 4, 1, 1);

        textLabel4 = new QLabel(tab);
        textLabel4->setObjectName(QString::fromUtf8("textLabel4"));

        gridLayout1->addWidget(textLabel4, 4, 6, 1, 1);

        textLabel5 = new QLabel(tab);
        textLabel5->setObjectName(QString::fromUtf8("textLabel5"));

        gridLayout1->addWidget(textLabel5, 4, 4, 1, 1);

        textLabel6 = new QLabel(tab);
        textLabel6->setObjectName(QString::fromUtf8("textLabel6"));

        gridLayout1->addWidget(textLabel6, 4, 2, 1, 1);

        textLabel7 = new QLabel(tab);
        textLabel7->setObjectName(QString::fromUtf8("textLabel7"));

        gridLayout1->addWidget(textLabel7, 5, 0, 1, 1);

        textLabel8 = new QLabel(tab);
        textLabel8->setObjectName(QString::fromUtf8("textLabel8"));

        gridLayout1->addWidget(textLabel8, 4, 0, 1, 1);

        textLabel9 = new QLabel(tab);
        textLabel9->setObjectName(QString::fromUtf8("textLabel9"));

        gridLayout1->addWidget(textLabel9, 3, 0, 1, 1);

        textLabel10 = new QLabel(tab);
        textLabel10->setObjectName(QString::fromUtf8("textLabel10"));

        gridLayout1->addWidget(textLabel10, 2, 0, 1, 1);

        textLabel11 = new QLabel(tab);
        textLabel11->setObjectName(QString::fromUtf8("textLabel11"));

        gridLayout1->addWidget(textLabel11, 1, 0, 1, 1);

        textLabel12 = new QLabel(tab);
        textLabel12->setObjectName(QString::fromUtf8("textLabel12"));

        gridLayout1->addWidget(textLabel12, 0, 0, 1, 1);

        id = new c2bLineEdit(tab);
        id->setObjectName(QString::fromUtf8("id"));
        QSizePolicy sizePolicy4(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(id->sizePolicy().hasHeightForWidth());
        id->setSizePolicy(sizePolicy4);
        id->setAcceptDrops(false);

        gridLayout1->addWidget(id, 0, 1, 1, 3);

        title = new c2bLineEdit(tab);
        title->setObjectName(QString::fromUtf8("title"));
        title->setAcceptDrops(false);

        gridLayout1->addWidget(title, 1, 1, 1, 7);

        author = new c2bLineEdit(tab);
        author->setObjectName(QString::fromUtf8("author"));
        author->setAcceptDrops(false);

        gridLayout1->addWidget(author, 2, 1, 1, 7);

        journal = new c2bLineEdit(tab);
        journal->setObjectName(QString::fromUtf8("journal"));
        journal->setAcceptDrops(false);

        gridLayout1->addWidget(journal, 3, 1, 1, 7);

        pages = new c2bLineEdit(tab);
        pages->setObjectName(QString::fromUtf8("pages"));
        pages->setAcceptDrops(false);

        gridLayout1->addWidget(pages, 4, 1, 1, 1);

        volume = new c2bLineEdit(tab);
        volume->setObjectName(QString::fromUtf8("volume"));
        volume->setAcceptDrops(false);

        gridLayout1->addWidget(volume, 4, 3, 1, 1);

        number = new c2bLineEdit(tab);
        number->setObjectName(QString::fromUtf8("number"));
        number->setAcceptDrops(false);

        gridLayout1->addWidget(number, 4, 5, 1, 1);

        year = new c2bLineEdit(tab);
        year->setObjectName(QString::fromUtf8("year"));
        year->setAcceptDrops(false);

        gridLayout1->addWidget(year, 4, 7, 1, 1);

        abstract = new c2bLineEdit(tab);
        abstract->setObjectName(QString::fromUtf8("abstract"));
        abstract->setAcceptDrops(false);

        gridLayout1->addWidget(abstract, 5, 1, 1, 7);

        keywords = new c2bLineEdit(tab);
        keywords->setObjectName(QString::fromUtf8("keywords"));
        keywords->setAcceptDrops(false);

        gridLayout1->addWidget(keywords, 6, 1, 1, 7);

        file = new c2bLineEdit(tab);
        file->setObjectName(QString::fromUtf8("file"));
        file->setAcceptDrops(false);

        gridLayout1->addWidget(file, 7, 1, 1, 7);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout2 = new QGridLayout(tab_2);
#ifndef Q_OS_MAC
        gridLayout2->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout2->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        textLabel13 = new QLabel(tab_2);
        textLabel13->setObjectName(QString::fromUtf8("textLabel13"));

        gridLayout2->addWidget(textLabel13, 0, 0, 1, 1);

        textLabel14 = new QLabel(tab_2);
        textLabel14->setObjectName(QString::fromUtf8("textLabel14"));

        gridLayout2->addWidget(textLabel14, 1, 0, 1, 1);

        textLabel15 = new QLabel(tab_2);
        textLabel15->setObjectName(QString::fromUtf8("textLabel15"));

        gridLayout2->addWidget(textLabel15, 2, 4, 1, 1);

        textLabel16 = new QLabel(tab_2);
        textLabel16->setObjectName(QString::fromUtf8("textLabel16"));

        gridLayout2->addWidget(textLabel16, 2, 2, 1, 1);

        textLabel17 = new QLabel(tab_2);
        textLabel17->setObjectName(QString::fromUtf8("textLabel17"));

        gridLayout2->addWidget(textLabel17, 2, 0, 1, 1);

        textLabel18 = new QLabel(tab_2);
        textLabel18->setObjectName(QString::fromUtf8("textLabel18"));

        gridLayout2->addWidget(textLabel18, 3, 4, 1, 1);

        textLabel19 = new QLabel(tab_2);
        textLabel19->setObjectName(QString::fromUtf8("textLabel19"));

        gridLayout2->addWidget(textLabel19, 3, 2, 1, 1);

        textLabel20 = new QLabel(tab_2);
        textLabel20->setObjectName(QString::fromUtf8("textLabel20"));

        gridLayout2->addWidget(textLabel20, 3, 0, 1, 1);

        textLabel21 = new QLabel(tab_2);
        textLabel21->setObjectName(QString::fromUtf8("textLabel21"));

        gridLayout2->addWidget(textLabel21, 4, 4, 1, 1);

        textLabel22 = new QLabel(tab_2);
        textLabel22->setObjectName(QString::fromUtf8("textLabel22"));

        gridLayout2->addWidget(textLabel22, 4, 2, 1, 1);

        textLabel23 = new QLabel(tab_2);
        textLabel23->setObjectName(QString::fromUtf8("textLabel23"));

        gridLayout2->addWidget(textLabel23, 4, 0, 1, 1);

        textLabel24 = new QLabel(tab_2);
        textLabel24->setObjectName(QString::fromUtf8("textLabel24"));

        gridLayout2->addWidget(textLabel24, 5, 4, 1, 1);

        textLabel25 = new QLabel(tab_2);
        textLabel25->setObjectName(QString::fromUtf8("textLabel25"));

        gridLayout2->addWidget(textLabel25, 5, 2, 1, 1);

        textLabel26 = new QLabel(tab_2);
        textLabel26->setObjectName(QString::fromUtf8("textLabel26"));

        gridLayout2->addWidget(textLabel26, 5, 0, 1, 1);

        textLabel27 = new QLabel(tab_2);
        textLabel27->setObjectName(QString::fromUtf8("textLabel27"));

        gridLayout2->addWidget(textLabel27, 6, 4, 1, 1);

        textLabel28 = new QLabel(tab_2);
        textLabel28->setObjectName(QString::fromUtf8("textLabel28"));

        gridLayout2->addWidget(textLabel28, 6, 2, 1, 1);

        textLabel29 = new QLabel(tab_2);
        textLabel29->setObjectName(QString::fromUtf8("textLabel29"));

        gridLayout2->addWidget(textLabel29, 6, 0, 1, 1);

        textLabel30 = new QLabel(tab_2);
        textLabel30->setObjectName(QString::fromUtf8("textLabel30"));

        gridLayout2->addWidget(textLabel30, 7, 0, 1, 1);

        booktitle = new c2bLineEdit(tab_2);
        booktitle->setObjectName(QString::fromUtf8("booktitle"));
        booktitle->setAcceptDrops(false);

        gridLayout2->addWidget(booktitle, 0, 1, 1, 5);

        annote = new c2bLineEdit(tab_2);
        annote->setObjectName(QString::fromUtf8("annote"));
        annote->setAcceptDrops(false);

        gridLayout2->addWidget(annote, 1, 1, 1, 5);

        address = new c2bLineEdit(tab_2);
        address->setObjectName(QString::fromUtf8("address"));
        address->setAcceptDrops(false);

        gridLayout2->addWidget(address, 2, 1, 1, 1);

        edition = new c2bLineEdit(tab_2);
        edition->setObjectName(QString::fromUtf8("edition"));
        edition->setAcceptDrops(false);

        gridLayout2->addWidget(edition, 3, 1, 1, 1);

        institution = new c2bLineEdit(tab_2);
        institution->setObjectName(QString::fromUtf8("institution"));
        institution->setAcceptDrops(false);

        gridLayout2->addWidget(institution, 4, 1, 1, 1);

        month = new c2bLineEdit(tab_2);
        month->setObjectName(QString::fromUtf8("month"));
        month->setAcceptDrops(false);

        gridLayout2->addWidget(month, 5, 1, 1, 1);

        publisher = new c2bLineEdit(tab_2);
        publisher->setObjectName(QString::fromUtf8("publisher"));
        publisher->setAcceptDrops(false);

        gridLayout2->addWidget(publisher, 6, 1, 1, 1);

        chapter = new c2bLineEdit(tab_2);
        chapter->setObjectName(QString::fromUtf8("chapter"));
        chapter->setAcceptDrops(false);

        gridLayout2->addWidget(chapter, 2, 3, 1, 1);

        editor = new c2bLineEdit(tab_2);
        editor->setObjectName(QString::fromUtf8("editor"));
        editor->setAcceptDrops(false);

        gridLayout2->addWidget(editor, 3, 3, 1, 1);

        isbn = new c2bLineEdit(tab_2);
        isbn->setObjectName(QString::fromUtf8("isbn"));
        isbn->setAcceptDrops(false);

        gridLayout2->addWidget(isbn, 4, 3, 1, 1);

        note = new c2bLineEdit(tab_2);
        note->setObjectName(QString::fromUtf8("note"));
        note->setAcceptDrops(false);

        gridLayout2->addWidget(note, 5, 3, 1, 1);

        school = new c2bLineEdit(tab_2);
        school->setObjectName(QString::fromUtf8("school"));
        school->setAcceptDrops(false);

        gridLayout2->addWidget(school, 6, 3, 1, 1);

        doi = new c2bLineEdit(tab_2);
        doi->setObjectName(QString::fromUtf8("doi"));
        doi->setAcceptDrops(false);

        gridLayout2->addWidget(doi, 2, 5, 1, 1);

        eprint = new c2bLineEdit(tab_2);
        eprint->setObjectName(QString::fromUtf8("eprint"));
        eprint->setAcceptDrops(false);

        gridLayout2->addWidget(eprint, 3, 5, 1, 1);

        issn = new c2bLineEdit(tab_2);
        issn->setObjectName(QString::fromUtf8("issn"));
        issn->setAcceptDrops(false);

        gridLayout2->addWidget(issn, 4, 5, 1, 1);

        organization = new c2bLineEdit(tab_2);
        organization->setObjectName(QString::fromUtf8("organization"));
        organization->setAcceptDrops(false);

        gridLayout2->addWidget(organization, 5, 5, 1, 1);

        series = new c2bLineEdit(tab_2);
        series->setObjectName(QString::fromUtf8("series"));
        series->setAcceptDrops(false);

        gridLayout2->addWidget(series, 6, 5, 1, 1);

        url = new c2bLineEdit(tab_2);
        url->setObjectName(QString::fromUtf8("url"));
        url->setAcceptDrops(false);

        gridLayout2->addWidget(url, 7, 1, 1, 5);

        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 3);

        cb2Bib->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(cb2Bib);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        cb2Bib->setStatusBar(statusbar);
        QWidget::setTabOrder(tabWidget, id);
        QWidget::setTabOrder(id, typecombo);
        QWidget::setTabOrder(typecombo, title);
        QWidget::setTabOrder(title, author);
        QWidget::setTabOrder(author, journal);
        QWidget::setTabOrder(journal, pages);
        QWidget::setTabOrder(pages, volume);
        QWidget::setTabOrder(volume, number);
        QWidget::setTabOrder(number, year);
        QWidget::setTabOrder(year, abstract);
        QWidget::setTabOrder(abstract, keywords);
        QWidget::setTabOrder(keywords, file);
        QWidget::setTabOrder(file, bibtexfile);
        QWidget::setTabOrder(bibtexfile, BibTeXDir);
        QWidget::setTabOrder(BibTeXDir, ViewAboutB);
        QWidget::setTabOrder(ViewAboutB, ConfigureB);
        QWidget::setTabOrder(ConfigureB, SearchInFilesB);
        QWidget::setTabOrder(SearchInFilesB, PdfImportB);
        QWidget::setTabOrder(PdfImportB, ExitB);
        QWidget::setTabOrder(ExitB, ConnectB);
        QWidget::setTabOrder(ConnectB, MakeNetworkQueryB);
        QWidget::setTabOrder(MakeNetworkQueryB, ViewBibB);
        QWidget::setTabOrder(ViewBibB, AddBibB);
        QWidget::setTabOrder(AddBibB, EditBibTeXB);
        QWidget::setTabOrder(EditBibTeXB, booktitle);
        QWidget::setTabOrder(booktitle, annote);
        QWidget::setTabOrder(annote, address);
        QWidget::setTabOrder(address, edition);
        QWidget::setTabOrder(edition, institution);
        QWidget::setTabOrder(institution, month);
        QWidget::setTabOrder(month, publisher);
        QWidget::setTabOrder(publisher, url);
        QWidget::setTabOrder(url, chapter);
        QWidget::setTabOrder(chapter, editor);
        QWidget::setTabOrder(editor, isbn);
        QWidget::setTabOrder(isbn, note);
        QWidget::setTabOrder(note, school);
        QWidget::setTabOrder(school, doi);
        QWidget::setTabOrder(doi, eprint);
        QWidget::setTabOrder(eprint, issn);
        QWidget::setTabOrder(issn, organization);
        QWidget::setTabOrder(organization, series);

        retranslateUi(cb2Bib);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(cb2Bib);
    } // setupUi

    void retranslateUi(QMainWindow *cb2Bib)
    {
        cb2Bib->setWindowTitle(QCoreApplication::translate("cb2Bib", "cb2Bib", nullptr));
        clearFieldsAction->setText(QCoreApplication::translate("cb2Bib", "Clear All Fields", nullptr));
        insertRegExpAction->setText(QCoreApplication::translate("cb2Bib", "Insert Regular Expression", nullptr));
#if QT_CONFIG(tooltip)
        insertRegExpAction->setToolTip(QCoreApplication::translate("cb2Bib", "Insert regular expression", nullptr));
#endif // QT_CONFIG(tooltip)
        editBookmarksAction->setText(QCoreApplication::translate("cb2Bib", "Edit Bookmarks", nullptr));
#if QT_CONFIG(tooltip)
        editBookmarksAction->setToolTip(QCoreApplication::translate("cb2Bib", "Edit bookmarks", nullptr));
#endif // QT_CONFIG(tooltip)
        editRegExpsAction->setText(QCoreApplication::translate("cb2Bib", "Edit Regular Expressions", nullptr));
#if QT_CONFIG(tooltip)
        editRegExpsAction->setToolTip(QCoreApplication::translate("cb2Bib", "Edit regular expressions", nullptr));
#endif // QT_CONFIG(tooltip)
        guessFieldsAction->setText(QCoreApplication::translate("cb2Bib", "Guess Bibliographic Fields", nullptr));
#if QT_CONFIG(tooltip)
        guessFieldsAction->setToolTip(QCoreApplication::translate("cb2Bib", "Guess bibliographic fields", nullptr));
#endif // QT_CONFIG(tooltip)
        postprocessBibTeXAction->setText(QCoreApplication::translate("cb2Bib", "Postprocess BibTeX", nullptr));
        preparseClipboardAction->setText(QCoreApplication::translate("cb2Bib", "Preparse Clipboard", nullptr));
#if QT_CONFIG(tooltip)
        preparseClipboardAction->setToolTip(QCoreApplication::translate("cb2Bib", "Preparse clipboard", nullptr));
#endif // QT_CONFIG(tooltip)
        startEngineAction->setText(QCoreApplication::translate("cb2Bib", "Restart Recognition", nullptr));
        viewTaggedClipEditAction->setText(QCoreApplication::translate("cb2Bib", "View Tagged Clipboard Data", nullptr));
        viewTaggedClipEditAction->setIconText(QCoreApplication::translate("cb2Bib", "View Tagged Clipboard Data", nullptr));
#if QT_CONFIG(tooltip)
        viewTaggedClipEditAction->setToolTip(QCoreApplication::translate("cb2Bib", "View tagged clipboard data", nullptr));
#endif // QT_CONFIG(tooltip)
        openFileDocumentAction->setText(QCoreApplication::translate("cb2Bib", "Open Document", nullptr));
#if QT_CONFIG(tooltip)
        openFileDocumentAction->setToolTip(QCoreApplication::translate("cb2Bib", "Open document", nullptr));
#endif // QT_CONFIG(tooltip)
        editAbbreviationsAction->setText(QCoreApplication::translate("cb2Bib", "Edit Journal Abbreviations", nullptr));
#if QT_CONFIG(tooltip)
        editAbbreviationsAction->setToolTip(QCoreApplication::translate("cb2Bib", "Edit journal abbreviations", nullptr));
#endif // QT_CONFIG(tooltip)
        selectFileAction->setText(QCoreApplication::translate("cb2Bib", "Select Document File", nullptr));
#if QT_CONFIG(tooltip)
        selectFileAction->setToolTip(QCoreApplication::translate("cb2Bib", "Select document file", nullptr));
#endif // QT_CONFIG(tooltip)
        openAnnoteAction->setText(QCoreApplication::translate("cb2Bib", "Annote Editor", nullptr));
#if QT_CONFIG(tooltip)
        openAnnoteAction->setToolTip(QCoreApplication::translate("cb2Bib", "Annote Editor", nullptr));
#endif // QT_CONFIG(tooltip)
        checkRepeatedAction->setText(QCoreApplication::translate("cb2Bib", "Check Repeated", nullptr));
#if QT_CONFIG(tooltip)
        checkRepeatedAction->setToolTip(QCoreApplication::translate("cb2Bib", "Check repeated", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        ViewAboutB->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        ViewAboutB->setText(QString());
#if QT_CONFIG(tooltip)
        ConfigureB->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        ConfigureB->setText(QString());
#if QT_CONFIG(tooltip)
        SearchInFilesB->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        SearchInFilesB->setText(QString());
#if QT_CONFIG(tooltip)
        PdfImportB->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        PdfImportB->setText(QString());
#if QT_CONFIG(tooltip)
        ExitB->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        ExitB->setText(QString());
        ConnectB->setText(QString());
#if QT_CONFIG(tooltip)
        MakeNetworkQueryB->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        MakeNetworkQueryB->setText(QString());
#if QT_CONFIG(tooltip)
        ViewBibB->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        ViewBibB->setText(QString());
#if QT_CONFIG(tooltip)
        AddBibB->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        AddBibB->setText(QString());
#if QT_CONFIG(tooltip)
        EditBibTeXB->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        EditBibTeXB->setText(QString());
#if QT_CONFIG(tooltip)
        BibTeXDir->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        TextLabel31->setText(QCoreApplication::translate("cb2Bib", "Add to:", nullptr));
        textLabel1->setText(QCoreApplication::translate("cb2Bib", "Keywords", nullptr));
        textLabel2->setText(QCoreApplication::translate("cb2Bib", "File", nullptr));
        textLabel3->setText(QCoreApplication::translate("cb2Bib", "Type", nullptr));
        textLabel4->setText(QCoreApplication::translate("cb2Bib", "Year", nullptr));
        textLabel5->setText(QCoreApplication::translate("cb2Bib", "Number", nullptr));
        textLabel6->setText(QCoreApplication::translate("cb2Bib", "Volume", nullptr));
        textLabel7->setText(QCoreApplication::translate("cb2Bib", "Abstract", nullptr));
        textLabel8->setText(QCoreApplication::translate("cb2Bib", "Pages", nullptr));
        textLabel9->setText(QCoreApplication::translate("cb2Bib", "Journal", nullptr));
        textLabel10->setText(QCoreApplication::translate("cb2Bib", "Author", nullptr));
        textLabel11->setText(QCoreApplication::translate("cb2Bib", "Title", nullptr));
        textLabel12->setText(QCoreApplication::translate("cb2Bib", "CITEID", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("cb2Bib", "Main", nullptr));
        textLabel13->setText(QCoreApplication::translate("cb2Bib", "Book Title", nullptr));
        textLabel14->setText(QCoreApplication::translate("cb2Bib", "Annote", nullptr));
        textLabel15->setText(QCoreApplication::translate("cb2Bib", "DOI", nullptr));
        textLabel16->setText(QCoreApplication::translate("cb2Bib", "Chapter", nullptr));
        textLabel17->setText(QCoreApplication::translate("cb2Bib", "Address", nullptr));
        textLabel18->setText(QCoreApplication::translate("cb2Bib", "Eprint", nullptr));
        textLabel19->setText(QCoreApplication::translate("cb2Bib", "Editor", nullptr));
        textLabel20->setText(QCoreApplication::translate("cb2Bib", "Edition", nullptr));
        textLabel21->setText(QCoreApplication::translate("cb2Bib", "ISSN", nullptr));
        textLabel22->setText(QCoreApplication::translate("cb2Bib", "ISBN", nullptr));
        textLabel23->setText(QCoreApplication::translate("cb2Bib", "Institution", nullptr));
        textLabel24->setText(QCoreApplication::translate("cb2Bib", "Organization", nullptr));
        textLabel25->setText(QCoreApplication::translate("cb2Bib", "Note", nullptr));
        textLabel26->setText(QCoreApplication::translate("cb2Bib", "Month", nullptr));
        textLabel27->setText(QCoreApplication::translate("cb2Bib", "Series", nullptr));
        textLabel28->setText(QCoreApplication::translate("cb2Bib", "School", nullptr));
        textLabel29->setText(QCoreApplication::translate("cb2Bib", "Publisher", nullptr));
        textLabel30->setText(QCoreApplication::translate("cb2Bib", "URL", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("cb2Bib", "Other Fields", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cb2Bib: public Ui_cb2Bib {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CB2BIB_H
