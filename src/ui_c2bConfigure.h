/********************************************************************************
** Form generated from reading UI file 'c2bConfigure.ui'
**
** Created by: Qt User Interface Compiler version 5.15.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C2BCONFIGURE_H
#define UI_C2BCONFIGURE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>
#include "c2bCitePatternLineEedit.h"
#include "c2bIdPatternLineEdit.h"
#include "c2bLineEdit.h"
#include "c2bShortcutWidget.h"

QT_BEGIN_NAMESPACE

class Ui_c2bConfigure
{
public:
    QGridLayout *gridLayout_4;
    QFrame *line_4;
    QListWidget *contentsWidget;
    QFrame *line_3;
    QStackedWidget *pagesWidget;
    QWidget *Annote;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_21;
    QGridLayout *gridLayout1;
    c2bLineEdit *AnnoteCssFile;
    QToolButton *AnnoteCssDir;
    QGroupBox *groupBox_22;
    QGridLayout *gridLayout2;
    c2bLineEdit *MathJaxHeaderFile;
    QToolButton *MathJaxDir;
    QGroupBox *groupBox_23;
    QGridLayout *gridLayout3;
    QCheckBox *IncludeCSS;
    QCheckBox *UseRelativeLinks;
    QSpacerItem *spacerItem;
    QGroupBox *AnnoteViewerFont;
    QGridLayout *gridLayout4;
    QLabel *textLabel3_9;
    QFontComboBox *af_familycombo;
    QLabel *textLabel3_10;
    QComboBox *af_psizecombo;
    QGroupBox *AnnoteViewerFixedFont;
    QGridLayout *gridLayout5;
    QLabel *textLabel3_6;
    QFontComboBox *aff_familycombo;
    QLabel *textLabel3_5;
    QComboBox *aff_psizecombo;
    QSpacerItem *spacer;
    QWidget *BibTeX;
    QGridLayout *gridLayout_0;
    QGroupBox *groupBox_11;
    QGridLayout *gridLayout6;
    c2bIdPatternLineEdit *CiteIdPattern;
    QGroupBox *groupBox_9;
    QGridLayout *gridLayout7;
    QSpacerItem *spacerItem1;
    QRadioButton *UseFullNames;
    QRadioButton *UseAbbreviatedNames;
    QGroupBox *groupBox_10;
    QGridLayout *gridLayout8;
    QRadioButton *SetJournalsToFullname;
    QRadioButton *SetJournalsToAbbreviated;
    QSpacerItem *spacerItem2;
    QGroupBox *PageNumberSeparatorBox;
    QGridLayout *gridLayout9;
    c2bLineEdit *PageNumberSeparator;
    QGroupBox *groupBox_24;
    QGridLayout *_5;
    c2bCitePatternLineEedit *CiteCommandPattern;
    QGroupBox *groupBox_12;
    QGridLayout *gridLayout10;
    QSpacerItem *spacerItem3;
    QCheckBox *PostprocessMonth;
    QCheckBox *UseDoubleBraces;
    QCheckBox *ConvertReferenceToLaTeX;
    QGroupBox *groupBox_13;
    QGridLayout *gridLayout11;
    QCheckBox *DoHeuristicGuess;
    QGroupBox *groupBox_19;
    QGridLayout *_3;
    QCheckBox *CheckRepeatedOnSave;
    QGroupBox *groupBox_14;
    QGridLayout *gridLayout12;
    QLabel *textLabel2_2_5;
    QToolButton *PostprocessBibTeXDir;
    QLabel *textLabel1_2_4;
    QLabel *textLabel2_2_3_2;
    c2bLineEdit *PostprocessBibTeXBin;
    c2bLineEdit *PostprocessBibTeXArg;
    c2bLineEdit *PostprocessBibTeXExt;
    QSpacerItem *spacerItem4;
    QWidget *Clipboard;
    QGridLayout *gridLayout13;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout14;
    QCheckBox *FindReplaceInput;
    QGridLayout *gridLayout15;
    QPushButton *FREdit;
    QSpacerItem *spacerItem5;
    QPushButton *FRDelete;
    QTreeWidget *FindReplaceList;
    QPushButton *FRNew;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout16;
    QHBoxLayout *hboxLayout;
    c2bLineEdit *PreparserBin;
    QToolButton *PreparserDir;
    QCheckBox *PreparserAutomatic;
    QCheckBox *PreparserShowLog;
    QSpacerItem *spacerItem6;
    QCheckBox *AddMetadata;
    QGroupBox *PreAppendMetadata;
    QGridLayout *gridLayout17;
    QSpacerItem *spacerItem7;
    QRadioButton *Append;
    QRadioButton *Prepend;
    QWidget *Documents;
    QGridLayout *gridLayout18;
    QCheckBox *MovePdf;
    QGroupBox *RenameCopyMovePdf;
    QGridLayout *gridLayout19;
    QLabel *label;
    QCheckBox *InsertMetadata;
    QCheckBox *RelativePdfDirectory;
    QHBoxLayout *hboxLayout1;
    c2bLineEdit *PdfDirectory;
    QToolButton *PdfDir;
    QGroupBox *CopyMovePdf;
    QGridLayout *gridLayout20;
    QSpacerItem *spacerItem8;
    QRadioButton *Move;
    QRadioButton *Copy;
    QGroupBox *DocumentIdPatternBox;
    QGridLayout *_2;
    c2bIdPatternLineEdit *DocumentIdPattern;
    QGroupBox *groupBox_18;
    QGridLayout *gridLayout21;
    c2bLineEdit *ExifToolBin;
    QToolButton *ExifToolDir;
    QLabel *textLabel1_6;
    QSpacerItem *spacerItem9;
    QWidget *Files;
    QGridLayout *gridLayout22;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout23;
    c2bLineEdit *JournalFile;
    QToolButton *JournalDir;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout24;
    c2bLineEdit *RegularExpressionFile;
    QToolButton *RegularExpressionDir;
    QGroupBox *groupBox_16;
    QGridLayout *gridLayout25;
    c2bLineEdit *NetworkFile;
    QToolButton *NetworkDir;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout26;
    c2bLineEdit *BrowserCssFile;
    QToolButton *BrowserCssDir;
    QSpacerItem *spacerItem10;
    QGroupBox *groupBox_20;
    QGridLayout *_4;
    c2bLineEdit *PosLexiconFile;
    QToolButton *PosLexiconDir;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout27;
    c2bLineEdit *CacheDirectory;
    QToolButton *CacheDir;
    QWidget *Fonts;
    QGridLayout *gridLayout28;
    QGroupBox *groupBox;
    QGridLayout *gridLayout29;
    QLabel *textLabel3;
    QFontComboBox *familycombo;
    QLabel *textLabel3_2;
    QComboBox *psizecombo;
    QLineEdit *samplelineedit;
    QTreeWidget *ColorList;
    QWidget *Network;
    QGridLayout *gridLayout_2;
    QCheckBox *FmClient;
    QGroupBox *clientGroupBox;
    QGridLayout *gridLayout30;
    QLabel *textLabel1_2_3;
    c2bLineEdit *FmClientCopyBin;
    QToolButton *FmClientCopyDir;
    QLabel *textLabel2_2_3;
    c2bLineEdit *FmClientCopyArg;
    QLabel *textLabel1_2_2_4;
    c2bLineEdit *FmClientMoveBin;
    QToolButton *FmClientMoveDir;
    QLabel *textLabel2_2_2_3;
    c2bLineEdit *FmClientMoveArg;
    QCheckBox *UseProxy;
    QGroupBox *proxyGroupBox;
    QGridLayout *gridLayout_3;
    QLabel *textLabel1_2_5;
    c2bLineEdit *ProxyHostName;
    QLabel *textLabel1_2_2_5;
    c2bLineEdit *ProxyPort;
    QLabel *textLabel1_2_2_6;
    QComboBox *ProxyType;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout31;
    QCheckBox *AutomaticPdfDownload;
    QCheckBox *KeepTmpNQFiles;
    QCheckBox *AutomaticQuery;
    QSpacerItem *spacerItem11;
    QWidget *Shortcuts;
    QGridLayout *gridLayout_6;
    QGroupBox *cb2BibScGroupBox;
    QGridLayout *gridLayout_1;
    c2bShortcutWidget *cb2BibShortcuts;
    QGroupBox *EditorScGroupBox;
    QGridLayout *gridLayout_5;
    c2bShortcutWidget *EditorShortcuts;
    QSpacerItem *verticalSpacer;
    QWidget *Utilities;
    QGridLayout *gridLayout32;
    QGroupBox *groupBox_15;
    QGridLayout *gridLayout33;
    QToolButton *PdfImportPdf2TextDir;
    QLabel *textLabel2_6;
    QLabel *textLabel1_4;
    c2bLineEdit *PdfImportPdf2TextBin;
    c2bLineEdit *PdfImportPdf2TextArg;
    QGroupBox *groupBox_17;
    QGridLayout *gridLayout34;
    QToolButton *BibSearcherPdf2TextDir;
    QLabel *textLabel2_7;
    QLabel *textLabel1_5;
    c2bLineEdit *BibSearcherPdf2TextBin;
    c2bLineEdit *BibSearcherPdf2TextArg;
    QSpacerItem *spacerItem12;
    QFrame *line_2;
    QStatusBar *statusBar;
    QFrame *line;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *c2bConfigure)
    {
        if (c2bConfigure->objectName().isEmpty())
            c2bConfigure->setObjectName(QString::fromUtf8("c2bConfigure"));
        c2bConfigure->resize(1184, 775);
        gridLayout_4 = new QGridLayout(c2bConfigure);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        line_4 = new QFrame(c2bConfigure);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout_4->addWidget(line_4, 0, 0, 1, 3);

        contentsWidget = new QListWidget(c2bConfigure);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/annote.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(contentsWidget);
        __qlistwidgetitem->setIcon(icon);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/configure_bibtex.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(contentsWidget);
        __qlistwidgetitem1->setIcon(icon1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/icons/configure_clipboard.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(contentsWidget);
        __qlistwidgetitem2->setIcon(icon2);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/icons/configure_documents.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem3 = new QListWidgetItem(contentsWidget);
        __qlistwidgetitem3->setIcon(icon3);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/icons/configure_files.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem4 = new QListWidgetItem(contentsWidget);
        __qlistwidgetitem4->setIcon(icon4);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/icons/configure_fonts.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem5 = new QListWidgetItem(contentsWidget);
        __qlistwidgetitem5->setIcon(icon5);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/icons/configure_network.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem6 = new QListWidgetItem(contentsWidget);
        __qlistwidgetitem6->setIcon(icon6);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/icons/configure_shortcuts.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem7 = new QListWidgetItem(contentsWidget);
        __qlistwidgetitem7->setIcon(icon7);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/icons/configure_utilities.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem8 = new QListWidgetItem(contentsWidget);
        __qlistwidgetitem8->setIcon(icon8);
        contentsWidget->setObjectName(QString::fromUtf8("contentsWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(contentsWidget->sizePolicy().hasHeightForWidth());
        contentsWidget->setSizePolicy(sizePolicy);
        contentsWidget->setMaximumSize(QSize(200, 16777215));
        contentsWidget->viewport()->setProperty("cursor", QVariant(QCursor(Qt::PointingHandCursor)));
        contentsWidget->setMouseTracking(true);
        contentsWidget->setFrameShadow(QFrame::Raised);
        contentsWidget->setSelectionMode(QAbstractItemView::NoSelection);
        contentsWidget->setSelectionBehavior(QAbstractItemView::SelectColumns);
        contentsWidget->setIconSize(QSize(32, 32));
        contentsWidget->setMovement(QListView::Static);
        contentsWidget->setSpacing(5);
        contentsWidget->setViewMode(QListView::ListMode);
        contentsWidget->setModelColumn(0);
        contentsWidget->setUniformItemSizes(true);

        gridLayout_4->addWidget(contentsWidget, 1, 0, 1, 1);

        line_3 = new QFrame(c2bConfigure);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout_4->addWidget(line_3, 1, 1, 1, 1);

        pagesWidget = new QStackedWidget(c2bConfigure);
        pagesWidget->setObjectName(QString::fromUtf8("pagesWidget"));
        Annote = new QWidget();
        Annote->setObjectName(QString::fromUtf8("Annote"));
        gridLayout = new QGridLayout(Annote);
        gridLayout->setContentsMargins(1, 1, 1, 1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_21 = new QGroupBox(Annote);
        groupBox_21->setObjectName(QString::fromUtf8("groupBox_21"));
        gridLayout1 = new QGridLayout(groupBox_21);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        AnnoteCssFile = new c2bLineEdit(groupBox_21);
        AnnoteCssFile->setObjectName(QString::fromUtf8("AnnoteCssFile"));

        gridLayout1->addWidget(AnnoteCssFile, 0, 0, 1, 1);

        AnnoteCssDir = new QToolButton(groupBox_21);
        AnnoteCssDir->setObjectName(QString::fromUtf8("AnnoteCssDir"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icons/icons/mimeFolder.png"), QSize(), QIcon::Normal, QIcon::Off);
        AnnoteCssDir->setIcon(icon9);

        gridLayout1->addWidget(AnnoteCssDir, 0, 1, 1, 1);


        gridLayout->addWidget(groupBox_21, 0, 0, 1, 1);

        groupBox_22 = new QGroupBox(Annote);
        groupBox_22->setObjectName(QString::fromUtf8("groupBox_22"));
        gridLayout2 = new QGridLayout(groupBox_22);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        MathJaxHeaderFile = new c2bLineEdit(groupBox_22);
        MathJaxHeaderFile->setObjectName(QString::fromUtf8("MathJaxHeaderFile"));

        gridLayout2->addWidget(MathJaxHeaderFile, 0, 0, 1, 1);

        MathJaxDir = new QToolButton(groupBox_22);
        MathJaxDir->setObjectName(QString::fromUtf8("MathJaxDir"));
        MathJaxDir->setIcon(icon9);

        gridLayout2->addWidget(MathJaxDir, 0, 1, 1, 1);


        gridLayout->addWidget(groupBox_22, 1, 0, 1, 1);

        groupBox_23 = new QGroupBox(Annote);
        groupBox_23->setObjectName(QString::fromUtf8("groupBox_23"));
        gridLayout3 = new QGridLayout(groupBox_23);
        gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
        IncludeCSS = new QCheckBox(groupBox_23);
        IncludeCSS->setObjectName(QString::fromUtf8("IncludeCSS"));

        gridLayout3->addWidget(IncludeCSS, 0, 0, 1, 1);

        UseRelativeLinks = new QCheckBox(groupBox_23);
        UseRelativeLinks->setObjectName(QString::fromUtf8("UseRelativeLinks"));

        gridLayout3->addWidget(UseRelativeLinks, 0, 1, 1, 1);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout3->addItem(spacerItem, 0, 2, 1, 1);


        gridLayout->addWidget(groupBox_23, 2, 0, 1, 1);

        AnnoteViewerFont = new QGroupBox(Annote);
        AnnoteViewerFont->setObjectName(QString::fromUtf8("AnnoteViewerFont"));
        gridLayout4 = new QGridLayout(AnnoteViewerFont);
        gridLayout4->setObjectName(QString::fromUtf8("gridLayout4"));
        textLabel3_9 = new QLabel(AnnoteViewerFont);
        textLabel3_9->setObjectName(QString::fromUtf8("textLabel3_9"));

        gridLayout4->addWidget(textLabel3_9, 0, 0, 1, 1);

        af_familycombo = new QFontComboBox(AnnoteViewerFont);
        af_familycombo->setObjectName(QString::fromUtf8("af_familycombo"));
        af_familycombo->setDuplicatesEnabled(false);

        gridLayout4->addWidget(af_familycombo, 0, 1, 1, 1);

        textLabel3_10 = new QLabel(AnnoteViewerFont);
        textLabel3_10->setObjectName(QString::fromUtf8("textLabel3_10"));

        gridLayout4->addWidget(textLabel3_10, 1, 0, 1, 1);

        af_psizecombo = new QComboBox(AnnoteViewerFont);
        af_psizecombo->setObjectName(QString::fromUtf8("af_psizecombo"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(af_psizecombo->sizePolicy().hasHeightForWidth());
        af_psizecombo->setSizePolicy(sizePolicy1);
        af_psizecombo->setEditable(true);
        af_psizecombo->setDuplicatesEnabled(false);

        gridLayout4->addWidget(af_psizecombo, 1, 1, 1, 1);


        gridLayout->addWidget(AnnoteViewerFont, 3, 0, 1, 1);

        AnnoteViewerFixedFont = new QGroupBox(Annote);
        AnnoteViewerFixedFont->setObjectName(QString::fromUtf8("AnnoteViewerFixedFont"));
        gridLayout5 = new QGridLayout(AnnoteViewerFixedFont);
        gridLayout5->setObjectName(QString::fromUtf8("gridLayout5"));
        textLabel3_6 = new QLabel(AnnoteViewerFixedFont);
        textLabel3_6->setObjectName(QString::fromUtf8("textLabel3_6"));

        gridLayout5->addWidget(textLabel3_6, 0, 0, 1, 1);

        aff_familycombo = new QFontComboBox(AnnoteViewerFixedFont);
        aff_familycombo->setObjectName(QString::fromUtf8("aff_familycombo"));
        aff_familycombo->setDuplicatesEnabled(false);
        aff_familycombo->setFontFilters(QFontComboBox::MonospacedFonts);

        gridLayout5->addWidget(aff_familycombo, 0, 1, 1, 1);

        textLabel3_5 = new QLabel(AnnoteViewerFixedFont);
        textLabel3_5->setObjectName(QString::fromUtf8("textLabel3_5"));

        gridLayout5->addWidget(textLabel3_5, 1, 0, 1, 1);

        aff_psizecombo = new QComboBox(AnnoteViewerFixedFont);
        aff_psizecombo->setObjectName(QString::fromUtf8("aff_psizecombo"));
        sizePolicy1.setHeightForWidth(aff_psizecombo->sizePolicy().hasHeightForWidth());
        aff_psizecombo->setSizePolicy(sizePolicy1);
        aff_psizecombo->setEditable(true);
        aff_psizecombo->setDuplicatesEnabled(false);

        gridLayout5->addWidget(aff_psizecombo, 1, 1, 1, 1);


        gridLayout->addWidget(AnnoteViewerFixedFont, 4, 0, 1, 1);

        spacer = new QSpacerItem(20, 41, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacer, 5, 0, 1, 1);

        pagesWidget->addWidget(Annote);
        BibTeX = new QWidget();
        BibTeX->setObjectName(QString::fromUtf8("BibTeX"));
        gridLayout_0 = new QGridLayout(BibTeX);
        gridLayout_0->setContentsMargins(1, 1, 1, 1);
        gridLayout_0->setObjectName(QString::fromUtf8("gridLayout_0"));
        groupBox_11 = new QGroupBox(BibTeX);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        gridLayout6 = new QGridLayout(groupBox_11);
#ifndef Q_OS_MAC
        gridLayout6->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout6->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout6->setObjectName(QString::fromUtf8("gridLayout6"));
        CiteIdPattern = new c2bIdPatternLineEdit(groupBox_11);
        CiteIdPattern->setObjectName(QString::fromUtf8("CiteIdPattern"));

        gridLayout6->addWidget(CiteIdPattern, 0, 0, 1, 1);


        gridLayout_0->addWidget(groupBox_11, 0, 0, 1, 4);

        groupBox_9 = new QGroupBox(BibTeX);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        gridLayout7 = new QGridLayout(groupBox_9);
#ifndef Q_OS_MAC
        gridLayout7->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout7->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout7->setObjectName(QString::fromUtf8("gridLayout7"));
        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout7->addItem(spacerItem1, 0, 2, 1, 1);

        UseFullNames = new QRadioButton(groupBox_9);
        UseFullNames->setObjectName(QString::fromUtf8("UseFullNames"));

        gridLayout7->addWidget(UseFullNames, 0, 1, 1, 1);

        UseAbbreviatedNames = new QRadioButton(groupBox_9);
        UseAbbreviatedNames->setObjectName(QString::fromUtf8("UseAbbreviatedNames"));

        gridLayout7->addWidget(UseAbbreviatedNames, 0, 0, 1, 1);


        gridLayout_0->addWidget(groupBox_9, 1, 0, 1, 1);

        groupBox_10 = new QGroupBox(BibTeX);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        gridLayout8 = new QGridLayout(groupBox_10);
#ifndef Q_OS_MAC
        gridLayout8->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout8->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout8->setObjectName(QString::fromUtf8("gridLayout8"));
        SetJournalsToFullname = new QRadioButton(groupBox_10);
        SetJournalsToFullname->setObjectName(QString::fromUtf8("SetJournalsToFullname"));

        gridLayout8->addWidget(SetJournalsToFullname, 0, 1, 1, 1);

        SetJournalsToAbbreviated = new QRadioButton(groupBox_10);
        SetJournalsToAbbreviated->setObjectName(QString::fromUtf8("SetJournalsToAbbreviated"));

        gridLayout8->addWidget(SetJournalsToAbbreviated, 0, 0, 1, 1);

        spacerItem2 = new QSpacerItem(95, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout8->addItem(spacerItem2, 0, 2, 1, 1);


        gridLayout_0->addWidget(groupBox_10, 1, 1, 1, 2);

        PageNumberSeparatorBox = new QGroupBox(BibTeX);
        PageNumberSeparatorBox->setObjectName(QString::fromUtf8("PageNumberSeparatorBox"));
        gridLayout9 = new QGridLayout(PageNumberSeparatorBox);
#ifndef Q_OS_MAC
        gridLayout9->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout9->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout9->setObjectName(QString::fromUtf8("gridLayout9"));
        PageNumberSeparator = new c2bLineEdit(PageNumberSeparatorBox);
        PageNumberSeparator->setObjectName(QString::fromUtf8("PageNumberSeparator"));

        gridLayout9->addWidget(PageNumberSeparator, 0, 0, 1, 1);


        gridLayout_0->addWidget(PageNumberSeparatorBox, 1, 3, 1, 1);

        groupBox_24 = new QGroupBox(BibTeX);
        groupBox_24->setObjectName(QString::fromUtf8("groupBox_24"));
        _5 = new QGridLayout(groupBox_24);
#ifndef Q_OS_MAC
        _5->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        _5->setContentsMargins(9, 9, 9, 9);
#endif
        _5->setObjectName(QString::fromUtf8("_5"));
        CiteCommandPattern = new c2bCitePatternLineEedit(groupBox_24);
        CiteCommandPattern->setObjectName(QString::fromUtf8("CiteCommandPattern"));

        _5->addWidget(CiteCommandPattern, 0, 0, 1, 1);


        gridLayout_0->addWidget(groupBox_24, 2, 0, 1, 4);

        groupBox_12 = new QGroupBox(BibTeX);
        groupBox_12->setObjectName(QString::fromUtf8("groupBox_12"));
        gridLayout10 = new QGridLayout(groupBox_12);
#ifndef Q_OS_MAC
        gridLayout10->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout10->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout10->setObjectName(QString::fromUtf8("gridLayout10"));
        spacerItem3 = new QSpacerItem(182, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout10->addItem(spacerItem3, 0, 3, 1, 1);

        PostprocessMonth = new QCheckBox(groupBox_12);
        PostprocessMonth->setObjectName(QString::fromUtf8("PostprocessMonth"));

        gridLayout10->addWidget(PostprocessMonth, 0, 2, 1, 1);

        UseDoubleBraces = new QCheckBox(groupBox_12);
        UseDoubleBraces->setObjectName(QString::fromUtf8("UseDoubleBraces"));

        gridLayout10->addWidget(UseDoubleBraces, 0, 1, 1, 1);

        ConvertReferenceToLaTeX = new QCheckBox(groupBox_12);
        ConvertReferenceToLaTeX->setObjectName(QString::fromUtf8("ConvertReferenceToLaTeX"));

        gridLayout10->addWidget(ConvertReferenceToLaTeX, 0, 0, 1, 1);


        gridLayout_0->addWidget(groupBox_12, 3, 0, 1, 4);

        groupBox_13 = new QGroupBox(BibTeX);
        groupBox_13->setObjectName(QString::fromUtf8("groupBox_13"));
        gridLayout11 = new QGridLayout(groupBox_13);
#ifndef Q_OS_MAC
        gridLayout11->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout11->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout11->setObjectName(QString::fromUtf8("gridLayout11"));
        DoHeuristicGuess = new QCheckBox(groupBox_13);
        DoHeuristicGuess->setObjectName(QString::fromUtf8("DoHeuristicGuess"));

        gridLayout11->addWidget(DoHeuristicGuess, 0, 0, 1, 1);


        gridLayout_0->addWidget(groupBox_13, 4, 0, 1, 2);

        groupBox_19 = new QGroupBox(BibTeX);
        groupBox_19->setObjectName(QString::fromUtf8("groupBox_19"));
        _3 = new QGridLayout(groupBox_19);
#ifndef Q_OS_MAC
        _3->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        _3->setContentsMargins(9, 9, 9, 9);
#endif
        _3->setObjectName(QString::fromUtf8("_3"));
        CheckRepeatedOnSave = new QCheckBox(groupBox_19);
        CheckRepeatedOnSave->setObjectName(QString::fromUtf8("CheckRepeatedOnSave"));

        _3->addWidget(CheckRepeatedOnSave, 0, 0, 1, 1);


        gridLayout_0->addWidget(groupBox_19, 4, 2, 1, 2);

        groupBox_14 = new QGroupBox(BibTeX);
        groupBox_14->setObjectName(QString::fromUtf8("groupBox_14"));
        gridLayout12 = new QGridLayout(groupBox_14);
#ifndef Q_OS_MAC
        gridLayout12->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout12->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout12->setObjectName(QString::fromUtf8("gridLayout12"));
        textLabel2_2_5 = new QLabel(groupBox_14);
        textLabel2_2_5->setObjectName(QString::fromUtf8("textLabel2_2_5"));

        gridLayout12->addWidget(textLabel2_2_5, 1, 0, 1, 1);

        PostprocessBibTeXDir = new QToolButton(groupBox_14);
        PostprocessBibTeXDir->setObjectName(QString::fromUtf8("PostprocessBibTeXDir"));
        PostprocessBibTeXDir->setIcon(icon9);

        gridLayout12->addWidget(PostprocessBibTeXDir, 0, 2, 1, 1);

        textLabel1_2_4 = new QLabel(groupBox_14);
        textLabel1_2_4->setObjectName(QString::fromUtf8("textLabel1_2_4"));

        gridLayout12->addWidget(textLabel1_2_4, 0, 0, 1, 1);

        textLabel2_2_3_2 = new QLabel(groupBox_14);
        textLabel2_2_3_2->setObjectName(QString::fromUtf8("textLabel2_2_3_2"));

        gridLayout12->addWidget(textLabel2_2_3_2, 2, 0, 1, 1);

        PostprocessBibTeXBin = new c2bLineEdit(groupBox_14);
        PostprocessBibTeXBin->setObjectName(QString::fromUtf8("PostprocessBibTeXBin"));

        gridLayout12->addWidget(PostprocessBibTeXBin, 0, 1, 1, 1);

        PostprocessBibTeXArg = new c2bLineEdit(groupBox_14);
        PostprocessBibTeXArg->setObjectName(QString::fromUtf8("PostprocessBibTeXArg"));

        gridLayout12->addWidget(PostprocessBibTeXArg, 1, 1, 1, 2);

        PostprocessBibTeXExt = new c2bLineEdit(groupBox_14);
        PostprocessBibTeXExt->setObjectName(QString::fromUtf8("PostprocessBibTeXExt"));

        gridLayout12->addWidget(PostprocessBibTeXExt, 2, 1, 1, 2);


        gridLayout_0->addWidget(groupBox_14, 5, 0, 1, 4);

        spacerItem4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_0->addItem(spacerItem4, 6, 1, 1, 1);

        pagesWidget->addWidget(BibTeX);
        Clipboard = new QWidget();
        Clipboard->setObjectName(QString::fromUtf8("Clipboard"));
        gridLayout13 = new QGridLayout(Clipboard);
        gridLayout13->setContentsMargins(1, 1, 1, 1);
        gridLayout13->setObjectName(QString::fromUtf8("gridLayout13"));
        groupBox_4 = new QGroupBox(Clipboard);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout14 = new QGridLayout(groupBox_4);
#ifndef Q_OS_MAC
        gridLayout14->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout14->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout14->setObjectName(QString::fromUtf8("gridLayout14"));
        FindReplaceInput = new QCheckBox(groupBox_4);
        FindReplaceInput->setObjectName(QString::fromUtf8("FindReplaceInput"));

        gridLayout14->addWidget(FindReplaceInput, 0, 0, 1, 1);

        gridLayout15 = new QGridLayout();
#ifndef Q_OS_MAC
        gridLayout15->setSpacing(6);
#endif
        gridLayout15->setContentsMargins(0, 0, 0, 0);
        gridLayout15->setObjectName(QString::fromUtf8("gridLayout15"));
        FREdit = new QPushButton(groupBox_4);
        FREdit->setObjectName(QString::fromUtf8("FREdit"));

        gridLayout15->addWidget(FREdit, 2, 1, 1, 1);

        spacerItem5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout15->addItem(spacerItem5, 0, 1, 1, 1);

        FRDelete = new QPushButton(groupBox_4);
        FRDelete->setObjectName(QString::fromUtf8("FRDelete"));

        gridLayout15->addWidget(FRDelete, 3, 1, 1, 1);

        FindReplaceList = new QTreeWidget(groupBox_4);
        FindReplaceList->setObjectName(QString::fromUtf8("FindReplaceList"));
        FindReplaceList->setFrameShadow(QFrame::Raised);
        FindReplaceList->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed|QAbstractItemView::SelectedClicked);
        FindReplaceList->setTabKeyNavigation(true);
        FindReplaceList->setSelectionMode(QAbstractItemView::SingleSelection);
        FindReplaceList->setRootIsDecorated(false);
        FindReplaceList->setUniformRowHeights(true);
        FindReplaceList->setSortingEnabled(true);
        FindReplaceList->setColumnCount(3);

        gridLayout15->addWidget(FindReplaceList, 0, 0, 4, 1);

        FRNew = new QPushButton(groupBox_4);
        FRNew->setObjectName(QString::fromUtf8("FRNew"));

        gridLayout15->addWidget(FRNew, 1, 1, 1, 1);


        gridLayout14->addLayout(gridLayout15, 1, 0, 1, 1);


        gridLayout13->addWidget(groupBox_4, 0, 0, 1, 1);

        groupBox_5 = new QGroupBox(Clipboard);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        gridLayout16 = new QGridLayout(groupBox_5);
#ifndef Q_OS_MAC
        gridLayout16->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout16->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout16->setObjectName(QString::fromUtf8("gridLayout16"));
        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        hboxLayout->setContentsMargins(0, 0, 0, 0);
#endif
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        PreparserBin = new c2bLineEdit(groupBox_5);
        PreparserBin->setObjectName(QString::fromUtf8("PreparserBin"));

        hboxLayout->addWidget(PreparserBin);

        PreparserDir = new QToolButton(groupBox_5);
        PreparserDir->setObjectName(QString::fromUtf8("PreparserDir"));
        PreparserDir->setIcon(icon9);

        hboxLayout->addWidget(PreparserDir);


        gridLayout16->addLayout(hboxLayout, 1, 0, 1, 3);

        PreparserAutomatic = new QCheckBox(groupBox_5);
        PreparserAutomatic->setObjectName(QString::fromUtf8("PreparserAutomatic"));

        gridLayout16->addWidget(PreparserAutomatic, 0, 0, 1, 1);

        PreparserShowLog = new QCheckBox(groupBox_5);
        PreparserShowLog->setObjectName(QString::fromUtf8("PreparserShowLog"));

        gridLayout16->addWidget(PreparserShowLog, 0, 1, 1, 1);

        spacerItem6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout16->addItem(spacerItem6, 0, 2, 1, 1);


        gridLayout13->addWidget(groupBox_5, 1, 0, 1, 1);

        AddMetadata = new QCheckBox(Clipboard);
        AddMetadata->setObjectName(QString::fromUtf8("AddMetadata"));

        gridLayout13->addWidget(AddMetadata, 2, 0, 1, 1);

        PreAppendMetadata = new QGroupBox(Clipboard);
        PreAppendMetadata->setObjectName(QString::fromUtf8("PreAppendMetadata"));
        gridLayout17 = new QGridLayout(PreAppendMetadata);
#ifndef Q_OS_MAC
        gridLayout17->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout17->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout17->setObjectName(QString::fromUtf8("gridLayout17"));
        spacerItem7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout17->addItem(spacerItem7, 0, 2, 1, 1);

        Append = new QRadioButton(PreAppendMetadata);
        Append->setObjectName(QString::fromUtf8("Append"));

        gridLayout17->addWidget(Append, 0, 1, 1, 1);

        Prepend = new QRadioButton(PreAppendMetadata);
        Prepend->setObjectName(QString::fromUtf8("Prepend"));

        gridLayout17->addWidget(Prepend, 0, 0, 1, 1);


        gridLayout13->addWidget(PreAppendMetadata, 3, 0, 1, 1);

        pagesWidget->addWidget(Clipboard);
        Documents = new QWidget();
        Documents->setObjectName(QString::fromUtf8("Documents"));
        gridLayout18 = new QGridLayout(Documents);
        gridLayout18->setContentsMargins(1, 1, 1, 1);
        gridLayout18->setObjectName(QString::fromUtf8("gridLayout18"));
        MovePdf = new QCheckBox(Documents);
        MovePdf->setObjectName(QString::fromUtf8("MovePdf"));

        gridLayout18->addWidget(MovePdf, 0, 0, 1, 1);

        RenameCopyMovePdf = new QGroupBox(Documents);
        RenameCopyMovePdf->setObjectName(QString::fromUtf8("RenameCopyMovePdf"));
        gridLayout19 = new QGridLayout(RenameCopyMovePdf);
#ifndef Q_OS_MAC
        gridLayout19->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout19->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout19->setObjectName(QString::fromUtf8("gridLayout19"));
        label = new QLabel(RenameCopyMovePdf);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout19->addWidget(label, 1, 0, 1, 1);

        InsertMetadata = new QCheckBox(RenameCopyMovePdf);
        InsertMetadata->setObjectName(QString::fromUtf8("InsertMetadata"));

        gridLayout19->addWidget(InsertMetadata, 4, 0, 1, 1);

        RelativePdfDirectory = new QCheckBox(RenameCopyMovePdf);
        RelativePdfDirectory->setObjectName(QString::fromUtf8("RelativePdfDirectory"));

        gridLayout19->addWidget(RelativePdfDirectory, 3, 0, 1, 1);

        hboxLayout1 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout1->setSpacing(6);
#endif
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        PdfDirectory = new c2bLineEdit(RenameCopyMovePdf);
        PdfDirectory->setObjectName(QString::fromUtf8("PdfDirectory"));

        hboxLayout1->addWidget(PdfDirectory);

        PdfDir = new QToolButton(RenameCopyMovePdf);
        PdfDir->setObjectName(QString::fromUtf8("PdfDir"));
        PdfDir->setIcon(icon9);

        hboxLayout1->addWidget(PdfDir);


        gridLayout19->addLayout(hboxLayout1, 2, 0, 1, 1);

        CopyMovePdf = new QGroupBox(RenameCopyMovePdf);
        CopyMovePdf->setObjectName(QString::fromUtf8("CopyMovePdf"));
        gridLayout20 = new QGridLayout(CopyMovePdf);
#ifndef Q_OS_MAC
        gridLayout20->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout20->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout20->setObjectName(QString::fromUtf8("gridLayout20"));
        spacerItem8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout20->addItem(spacerItem8, 0, 2, 1, 1);

        Move = new QRadioButton(CopyMovePdf);
        Move->setObjectName(QString::fromUtf8("Move"));

        gridLayout20->addWidget(Move, 0, 1, 1, 1);

        Copy = new QRadioButton(CopyMovePdf);
        Copy->setObjectName(QString::fromUtf8("Copy"));

        gridLayout20->addWidget(Copy, 0, 0, 1, 1);


        gridLayout19->addWidget(CopyMovePdf, 0, 0, 1, 1);


        gridLayout18->addWidget(RenameCopyMovePdf, 1, 0, 1, 1);

        DocumentIdPatternBox = new QGroupBox(Documents);
        DocumentIdPatternBox->setObjectName(QString::fromUtf8("DocumentIdPatternBox"));
        _2 = new QGridLayout(DocumentIdPatternBox);
#ifndef Q_OS_MAC
        _2->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        _2->setContentsMargins(9, 9, 9, 9);
#endif
        _2->setObjectName(QString::fromUtf8("_2"));
        DocumentIdPattern = new c2bIdPatternLineEdit(DocumentIdPatternBox);
        DocumentIdPattern->setObjectName(QString::fromUtf8("DocumentIdPattern"));

        _2->addWidget(DocumentIdPattern, 0, 0, 1, 1);


        gridLayout18->addWidget(DocumentIdPatternBox, 2, 0, 1, 1);

        groupBox_18 = new QGroupBox(Documents);
        groupBox_18->setObjectName(QString::fromUtf8("groupBox_18"));
        gridLayout21 = new QGridLayout(groupBox_18);
#ifndef Q_OS_MAC
        gridLayout21->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout21->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout21->setObjectName(QString::fromUtf8("gridLayout21"));
        ExifToolBin = new c2bLineEdit(groupBox_18);
        ExifToolBin->setObjectName(QString::fromUtf8("ExifToolBin"));

        gridLayout21->addWidget(ExifToolBin, 0, 1, 1, 1);

        ExifToolDir = new QToolButton(groupBox_18);
        ExifToolDir->setObjectName(QString::fromUtf8("ExifToolDir"));
        ExifToolDir->setIcon(icon9);

        gridLayout21->addWidget(ExifToolDir, 0, 2, 1, 1);

        textLabel1_6 = new QLabel(groupBox_18);
        textLabel1_6->setObjectName(QString::fromUtf8("textLabel1_6"));

        gridLayout21->addWidget(textLabel1_6, 0, 0, 1, 1);


        gridLayout18->addWidget(groupBox_18, 3, 0, 1, 1);

        spacerItem9 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout18->addItem(spacerItem9, 4, 0, 1, 1);

        pagesWidget->addWidget(Documents);
        Files = new QWidget();
        Files->setObjectName(QString::fromUtf8("Files"));
        gridLayout22 = new QGridLayout(Files);
        gridLayout22->setContentsMargins(1, 1, 1, 1);
        gridLayout22->setObjectName(QString::fromUtf8("gridLayout22"));
        groupBox_3 = new QGroupBox(Files);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout23 = new QGridLayout(groupBox_3);
        gridLayout23->setObjectName(QString::fromUtf8("gridLayout23"));
        JournalFile = new c2bLineEdit(groupBox_3);
        JournalFile->setObjectName(QString::fromUtf8("JournalFile"));

        gridLayout23->addWidget(JournalFile, 0, 0, 1, 1);

        JournalDir = new QToolButton(groupBox_3);
        JournalDir->setObjectName(QString::fromUtf8("JournalDir"));
        JournalDir->setIcon(icon9);

        gridLayout23->addWidget(JournalDir, 0, 1, 1, 1);


        gridLayout22->addWidget(groupBox_3, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(Files);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout24 = new QGridLayout(groupBox_2);
        gridLayout24->setObjectName(QString::fromUtf8("gridLayout24"));
        RegularExpressionFile = new c2bLineEdit(groupBox_2);
        RegularExpressionFile->setObjectName(QString::fromUtf8("RegularExpressionFile"));

        gridLayout24->addWidget(RegularExpressionFile, 0, 0, 1, 1);

        RegularExpressionDir = new QToolButton(groupBox_2);
        RegularExpressionDir->setObjectName(QString::fromUtf8("RegularExpressionDir"));
        RegularExpressionDir->setIcon(icon9);

        gridLayout24->addWidget(RegularExpressionDir, 0, 1, 1, 1);


        gridLayout22->addWidget(groupBox_2, 1, 0, 1, 1);

        groupBox_16 = new QGroupBox(Files);
        groupBox_16->setObjectName(QString::fromUtf8("groupBox_16"));
        gridLayout25 = new QGridLayout(groupBox_16);
        gridLayout25->setObjectName(QString::fromUtf8("gridLayout25"));
        NetworkFile = new c2bLineEdit(groupBox_16);
        NetworkFile->setObjectName(QString::fromUtf8("NetworkFile"));

        gridLayout25->addWidget(NetworkFile, 0, 0, 1, 1);

        NetworkDir = new QToolButton(groupBox_16);
        NetworkDir->setObjectName(QString::fromUtf8("NetworkDir"));
        NetworkDir->setIcon(icon9);

        gridLayout25->addWidget(NetworkDir, 0, 1, 1, 1);


        gridLayout22->addWidget(groupBox_16, 2, 0, 1, 1);

        groupBox_6 = new QGroupBox(Files);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        gridLayout26 = new QGridLayout(groupBox_6);
        gridLayout26->setObjectName(QString::fromUtf8("gridLayout26"));
        BrowserCssFile = new c2bLineEdit(groupBox_6);
        BrowserCssFile->setObjectName(QString::fromUtf8("BrowserCssFile"));

        gridLayout26->addWidget(BrowserCssFile, 0, 0, 1, 1);

        BrowserCssDir = new QToolButton(groupBox_6);
        BrowserCssDir->setObjectName(QString::fromUtf8("BrowserCssDir"));
        BrowserCssDir->setIcon(icon9);

        gridLayout26->addWidget(BrowserCssDir, 0, 1, 1, 1);


        gridLayout22->addWidget(groupBox_6, 3, 0, 1, 1);

        spacerItem10 = new QSpacerItem(31, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout22->addItem(spacerItem10, 7, 0, 1, 1);

        groupBox_20 = new QGroupBox(Files);
        groupBox_20->setObjectName(QString::fromUtf8("groupBox_20"));
        _4 = new QGridLayout(groupBox_20);
        _4->setObjectName(QString::fromUtf8("_4"));
        PosLexiconFile = new c2bLineEdit(groupBox_20);
        PosLexiconFile->setObjectName(QString::fromUtf8("PosLexiconFile"));

        _4->addWidget(PosLexiconFile, 0, 0, 1, 1);

        PosLexiconDir = new QToolButton(groupBox_20);
        PosLexiconDir->setObjectName(QString::fromUtf8("PosLexiconDir"));
        PosLexiconDir->setIcon(icon9);

        _4->addWidget(PosLexiconDir, 0, 1, 1, 1);


        gridLayout22->addWidget(groupBox_20, 4, 0, 1, 1);

        groupBox_7 = new QGroupBox(Files);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        gridLayout27 = new QGridLayout(groupBox_7);
        gridLayout27->setObjectName(QString::fromUtf8("gridLayout27"));
        CacheDirectory = new c2bLineEdit(groupBox_7);
        CacheDirectory->setObjectName(QString::fromUtf8("CacheDirectory"));

        gridLayout27->addWidget(CacheDirectory, 0, 0, 1, 1);

        CacheDir = new QToolButton(groupBox_7);
        CacheDir->setObjectName(QString::fromUtf8("CacheDir"));
        CacheDir->setIcon(icon9);

        gridLayout27->addWidget(CacheDir, 0, 1, 1, 1);


        gridLayout22->addWidget(groupBox_7, 6, 0, 1, 1);

        pagesWidget->addWidget(Files);
        Fonts = new QWidget();
        Fonts->setObjectName(QString::fromUtf8("Fonts"));
        gridLayout28 = new QGridLayout(Fonts);
        gridLayout28->setContentsMargins(1, 1, 1, 1);
        gridLayout28->setObjectName(QString::fromUtf8("gridLayout28"));
        groupBox = new QGroupBox(Fonts);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout29 = new QGridLayout(groupBox);
        gridLayout29->setObjectName(QString::fromUtf8("gridLayout29"));
        textLabel3 = new QLabel(groupBox);
        textLabel3->setObjectName(QString::fromUtf8("textLabel3"));

        gridLayout29->addWidget(textLabel3, 0, 0, 1, 1);

        familycombo = new QFontComboBox(groupBox);
        familycombo->setObjectName(QString::fromUtf8("familycombo"));
        familycombo->setDuplicatesEnabled(false);

        gridLayout29->addWidget(familycombo, 0, 1, 1, 1);

        textLabel3_2 = new QLabel(groupBox);
        textLabel3_2->setObjectName(QString::fromUtf8("textLabel3_2"));

        gridLayout29->addWidget(textLabel3_2, 1, 0, 1, 1);

        psizecombo = new QComboBox(groupBox);
        psizecombo->setObjectName(QString::fromUtf8("psizecombo"));
        sizePolicy1.setHeightForWidth(psizecombo->sizePolicy().hasHeightForWidth());
        psizecombo->setSizePolicy(sizePolicy1);
        psizecombo->setEditable(true);
        psizecombo->setDuplicatesEnabled(false);

        gridLayout29->addWidget(psizecombo, 1, 1, 1, 1);

        samplelineedit = new QLineEdit(groupBox);
        samplelineedit->setObjectName(QString::fromUtf8("samplelineedit"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(samplelineedit->sizePolicy().hasHeightForWidth());
        samplelineedit->setSizePolicy(sizePolicy2);
        samplelineedit->setAlignment(Qt::AlignHCenter);

        gridLayout29->addWidget(samplelineedit, 2, 0, 1, 2);

        ColorList = new QTreeWidget(groupBox);
        ColorList->setObjectName(QString::fromUtf8("ColorList"));
        ColorList->setFrameShadow(QFrame::Raised);
        ColorList->setTabKeyNavigation(true);
        ColorList->setRootIsDecorated(false);
        ColorList->setUniformRowHeights(true);
        ColorList->setSortingEnabled(true);
        ColorList->setColumnCount(1);

        gridLayout29->addWidget(ColorList, 3, 0, 1, 2);


        gridLayout28->addWidget(groupBox, 0, 0, 1, 1);

        pagesWidget->addWidget(Fonts);
        Network = new QWidget();
        Network->setObjectName(QString::fromUtf8("Network"));
        gridLayout_2 = new QGridLayout(Network);
        gridLayout_2->setContentsMargins(1, 1, 1, 1);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        FmClient = new QCheckBox(Network);
        FmClient->setObjectName(QString::fromUtf8("FmClient"));

        gridLayout_2->addWidget(FmClient, 0, 0, 1, 1);

        clientGroupBox = new QGroupBox(Network);
        clientGroupBox->setObjectName(QString::fromUtf8("clientGroupBox"));
        gridLayout30 = new QGridLayout(clientGroupBox);
        gridLayout30->setObjectName(QString::fromUtf8("gridLayout30"));
        textLabel1_2_3 = new QLabel(clientGroupBox);
        textLabel1_2_3->setObjectName(QString::fromUtf8("textLabel1_2_3"));

        gridLayout30->addWidget(textLabel1_2_3, 0, 0, 1, 1);

        FmClientCopyBin = new c2bLineEdit(clientGroupBox);
        FmClientCopyBin->setObjectName(QString::fromUtf8("FmClientCopyBin"));

        gridLayout30->addWidget(FmClientCopyBin, 0, 1, 1, 1);

        FmClientCopyDir = new QToolButton(clientGroupBox);
        FmClientCopyDir->setObjectName(QString::fromUtf8("FmClientCopyDir"));
        FmClientCopyDir->setIcon(icon9);

        gridLayout30->addWidget(FmClientCopyDir, 0, 2, 1, 1);

        textLabel2_2_3 = new QLabel(clientGroupBox);
        textLabel2_2_3->setObjectName(QString::fromUtf8("textLabel2_2_3"));

        gridLayout30->addWidget(textLabel2_2_3, 0, 3, 1, 1);

        FmClientCopyArg = new c2bLineEdit(clientGroupBox);
        FmClientCopyArg->setObjectName(QString::fromUtf8("FmClientCopyArg"));

        gridLayout30->addWidget(FmClientCopyArg, 0, 4, 1, 1);

        textLabel1_2_2_4 = new QLabel(clientGroupBox);
        textLabel1_2_2_4->setObjectName(QString::fromUtf8("textLabel1_2_2_4"));

        gridLayout30->addWidget(textLabel1_2_2_4, 1, 0, 1, 1);

        FmClientMoveBin = new c2bLineEdit(clientGroupBox);
        FmClientMoveBin->setObjectName(QString::fromUtf8("FmClientMoveBin"));

        gridLayout30->addWidget(FmClientMoveBin, 1, 1, 1, 1);

        FmClientMoveDir = new QToolButton(clientGroupBox);
        FmClientMoveDir->setObjectName(QString::fromUtf8("FmClientMoveDir"));
        FmClientMoveDir->setIcon(icon9);

        gridLayout30->addWidget(FmClientMoveDir, 1, 2, 1, 1);

        textLabel2_2_2_3 = new QLabel(clientGroupBox);
        textLabel2_2_2_3->setObjectName(QString::fromUtf8("textLabel2_2_2_3"));

        gridLayout30->addWidget(textLabel2_2_2_3, 1, 3, 1, 1);

        FmClientMoveArg = new c2bLineEdit(clientGroupBox);
        FmClientMoveArg->setObjectName(QString::fromUtf8("FmClientMoveArg"));

        gridLayout30->addWidget(FmClientMoveArg, 1, 4, 1, 1);


        gridLayout_2->addWidget(clientGroupBox, 1, 0, 1, 1);

        UseProxy = new QCheckBox(Network);
        UseProxy->setObjectName(QString::fromUtf8("UseProxy"));

        gridLayout_2->addWidget(UseProxy, 2, 0, 1, 1);

        proxyGroupBox = new QGroupBox(Network);
        proxyGroupBox->setObjectName(QString::fromUtf8("proxyGroupBox"));
        proxyGroupBox->setCheckable(false);
        proxyGroupBox->setChecked(false);
        gridLayout_3 = new QGridLayout(proxyGroupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        textLabel1_2_5 = new QLabel(proxyGroupBox);
        textLabel1_2_5->setObjectName(QString::fromUtf8("textLabel1_2_5"));

        gridLayout_3->addWidget(textLabel1_2_5, 0, 0, 1, 1);

        ProxyHostName = new c2bLineEdit(proxyGroupBox);
        ProxyHostName->setObjectName(QString::fromUtf8("ProxyHostName"));

        gridLayout_3->addWidget(ProxyHostName, 0, 1, 1, 1);

        textLabel1_2_2_5 = new QLabel(proxyGroupBox);
        textLabel1_2_2_5->setObjectName(QString::fromUtf8("textLabel1_2_2_5"));

        gridLayout_3->addWidget(textLabel1_2_2_5, 0, 2, 1, 1);

        ProxyPort = new c2bLineEdit(proxyGroupBox);
        ProxyPort->setObjectName(QString::fromUtf8("ProxyPort"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(ProxyPort->sizePolicy().hasHeightForWidth());
        ProxyPort->setSizePolicy(sizePolicy3);
        ProxyPort->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(ProxyPort, 0, 3, 1, 1);

        textLabel1_2_2_6 = new QLabel(proxyGroupBox);
        textLabel1_2_2_6->setObjectName(QString::fromUtf8("textLabel1_2_2_6"));

        gridLayout_3->addWidget(textLabel1_2_2_6, 0, 4, 1, 1);

        ProxyType = new QComboBox(proxyGroupBox);
        ProxyType->addItem(QString());
        ProxyType->addItem(QString());
        ProxyType->setObjectName(QString::fromUtf8("ProxyType"));

        gridLayout_3->addWidget(ProxyType, 0, 5, 1, 1);


        gridLayout_2->addWidget(proxyGroupBox, 3, 0, 1, 1);

        groupBox_8 = new QGroupBox(Network);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        gridLayout31 = new QGridLayout(groupBox_8);
#ifndef Q_OS_MAC
        gridLayout31->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout31->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout31->setObjectName(QString::fromUtf8("gridLayout31"));
        AutomaticPdfDownload = new QCheckBox(groupBox_8);
        AutomaticPdfDownload->setObjectName(QString::fromUtf8("AutomaticPdfDownload"));

        gridLayout31->addWidget(AutomaticPdfDownload, 1, 0, 1, 1);

        KeepTmpNQFiles = new QCheckBox(groupBox_8);
        KeepTmpNQFiles->setObjectName(QString::fromUtf8("KeepTmpNQFiles"));

        gridLayout31->addWidget(KeepTmpNQFiles, 2, 0, 1, 1);

        AutomaticQuery = new QCheckBox(groupBox_8);
        AutomaticQuery->setObjectName(QString::fromUtf8("AutomaticQuery"));

        gridLayout31->addWidget(AutomaticQuery, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_8, 4, 0, 1, 1);

        spacerItem11 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(spacerItem11, 5, 0, 1, 1);

        pagesWidget->addWidget(Network);
        Shortcuts = new QWidget();
        Shortcuts->setObjectName(QString::fromUtf8("Shortcuts"));
        gridLayout_6 = new QGridLayout(Shortcuts);
        gridLayout_6->setContentsMargins(1, 1, 1, 1);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        cb2BibScGroupBox = new QGroupBox(Shortcuts);
        cb2BibScGroupBox->setObjectName(QString::fromUtf8("cb2BibScGroupBox"));
        gridLayout_1 = new QGridLayout(cb2BibScGroupBox);
        gridLayout_1->setObjectName(QString::fromUtf8("gridLayout_1"));
        cb2BibShortcuts = new c2bShortcutWidget(cb2BibScGroupBox);
        cb2BibShortcuts->setObjectName(QString::fromUtf8("cb2BibShortcuts"));

        gridLayout_1->addWidget(cb2BibShortcuts, 0, 0, 1, 1);


        gridLayout_6->addWidget(cb2BibScGroupBox, 0, 0, 1, 1);

        EditorScGroupBox = new QGroupBox(Shortcuts);
        EditorScGroupBox->setObjectName(QString::fromUtf8("EditorScGroupBox"));
        gridLayout_5 = new QGridLayout(EditorScGroupBox);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        EditorShortcuts = new c2bShortcutWidget(EditorScGroupBox);
        EditorShortcuts->setObjectName(QString::fromUtf8("EditorShortcuts"));

        gridLayout_5->addWidget(EditorShortcuts, 0, 0, 1, 1);


        gridLayout_6->addWidget(EditorScGroupBox, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 398, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer, 2, 0, 1, 1);

        pagesWidget->addWidget(Shortcuts);
        Utilities = new QWidget();
        Utilities->setObjectName(QString::fromUtf8("Utilities"));
        gridLayout32 = new QGridLayout(Utilities);
        gridLayout32->setContentsMargins(1, 1, 1, 1);
        gridLayout32->setObjectName(QString::fromUtf8("gridLayout32"));
        groupBox_15 = new QGroupBox(Utilities);
        groupBox_15->setObjectName(QString::fromUtf8("groupBox_15"));
        gridLayout33 = new QGridLayout(groupBox_15);
#ifndef Q_OS_MAC
        gridLayout33->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout33->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout33->setObjectName(QString::fromUtf8("gridLayout33"));
        PdfImportPdf2TextDir = new QToolButton(groupBox_15);
        PdfImportPdf2TextDir->setObjectName(QString::fromUtf8("PdfImportPdf2TextDir"));
        PdfImportPdf2TextDir->setIcon(icon9);

        gridLayout33->addWidget(PdfImportPdf2TextDir, 0, 2, 1, 1);

        textLabel2_6 = new QLabel(groupBox_15);
        textLabel2_6->setObjectName(QString::fromUtf8("textLabel2_6"));

        gridLayout33->addWidget(textLabel2_6, 1, 0, 1, 1);

        textLabel1_4 = new QLabel(groupBox_15);
        textLabel1_4->setObjectName(QString::fromUtf8("textLabel1_4"));

        gridLayout33->addWidget(textLabel1_4, 0, 0, 1, 1);

        PdfImportPdf2TextBin = new c2bLineEdit(groupBox_15);
        PdfImportPdf2TextBin->setObjectName(QString::fromUtf8("PdfImportPdf2TextBin"));

        gridLayout33->addWidget(PdfImportPdf2TextBin, 0, 1, 1, 1);

        PdfImportPdf2TextArg = new c2bLineEdit(groupBox_15);
        PdfImportPdf2TextArg->setObjectName(QString::fromUtf8("PdfImportPdf2TextArg"));

        gridLayout33->addWidget(PdfImportPdf2TextArg, 1, 1, 1, 2);


        gridLayout32->addWidget(groupBox_15, 0, 0, 1, 1);

        groupBox_17 = new QGroupBox(Utilities);
        groupBox_17->setObjectName(QString::fromUtf8("groupBox_17"));
        gridLayout34 = new QGridLayout(groupBox_17);
#ifndef Q_OS_MAC
        gridLayout34->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout34->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout34->setObjectName(QString::fromUtf8("gridLayout34"));
        BibSearcherPdf2TextDir = new QToolButton(groupBox_17);
        BibSearcherPdf2TextDir->setObjectName(QString::fromUtf8("BibSearcherPdf2TextDir"));
        BibSearcherPdf2TextDir->setIcon(icon9);

        gridLayout34->addWidget(BibSearcherPdf2TextDir, 0, 2, 1, 1);

        textLabel2_7 = new QLabel(groupBox_17);
        textLabel2_7->setObjectName(QString::fromUtf8("textLabel2_7"));

        gridLayout34->addWidget(textLabel2_7, 1, 0, 1, 1);

        textLabel1_5 = new QLabel(groupBox_17);
        textLabel1_5->setObjectName(QString::fromUtf8("textLabel1_5"));

        gridLayout34->addWidget(textLabel1_5, 0, 0, 1, 1);

        BibSearcherPdf2TextBin = new c2bLineEdit(groupBox_17);
        BibSearcherPdf2TextBin->setObjectName(QString::fromUtf8("BibSearcherPdf2TextBin"));

        gridLayout34->addWidget(BibSearcherPdf2TextBin, 0, 1, 1, 1);

        BibSearcherPdf2TextArg = new c2bLineEdit(groupBox_17);
        BibSearcherPdf2TextArg->setObjectName(QString::fromUtf8("BibSearcherPdf2TextArg"));

        gridLayout34->addWidget(BibSearcherPdf2TextArg, 1, 1, 1, 2);


        gridLayout32->addWidget(groupBox_17, 1, 0, 1, 1);

        spacerItem12 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout32->addItem(spacerItem12, 2, 0, 1, 1);

        pagesWidget->addWidget(Utilities);

        gridLayout_4->addWidget(pagesWidget, 1, 2, 1, 1);

        line_2 = new QFrame(c2bConfigure);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout_4->addWidget(line_2, 2, 0, 1, 3);

        statusBar = new QStatusBar(c2bConfigure);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(statusBar->sizePolicy().hasHeightForWidth());
        statusBar->setSizePolicy(sizePolicy4);
        statusBar->setSizeGripEnabled(false);

        gridLayout_4->addWidget(statusBar, 3, 0, 1, 3);

        line = new QFrame(c2bConfigure);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_4->addWidget(line, 4, 0, 1, 3);

        buttonBox = new QDialogButtonBox(c2bConfigure);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Cancel|QDialogButtonBox::Help|QDialogButtonBox::Save);

        gridLayout_4->addWidget(buttonBox, 5, 0, 1, 3);


        retranslateUi(c2bConfigure);
        QObject::connect(buttonBox, SIGNAL(accepted()), c2bConfigure, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), c2bConfigure, SLOT(reject()));
        QObject::connect(FmClient, SIGNAL(toggled(bool)), clientGroupBox, SLOT(setEnabled(bool)));
        QObject::connect(UseProxy, SIGNAL(toggled(bool)), proxyGroupBox, SLOT(setEnabled(bool)));

        pagesWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(c2bConfigure);
    } // setupUi

    void retranslateUi(QDialog *c2bConfigure)
    {
        c2bConfigure->setWindowTitle(QCoreApplication::translate("c2bConfigure", "Configure - cb2Bib", nullptr));

        const bool __sortingEnabled = contentsWidget->isSortingEnabled();
        contentsWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = contentsWidget->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("c2bConfigure", "Annote", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = contentsWidget->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("c2bConfigure", "BibTeX", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = contentsWidget->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("c2bConfigure", "Clipboard", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = contentsWidget->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("c2bConfigure", "Documents", nullptr));
        QListWidgetItem *___qlistwidgetitem4 = contentsWidget->item(4);
        ___qlistwidgetitem4->setText(QCoreApplication::translate("c2bConfigure", "Files", nullptr));
        QListWidgetItem *___qlistwidgetitem5 = contentsWidget->item(5);
        ___qlistwidgetitem5->setText(QCoreApplication::translate("c2bConfigure", "Fonts", nullptr));
        QListWidgetItem *___qlistwidgetitem6 = contentsWidget->item(6);
        ___qlistwidgetitem6->setText(QCoreApplication::translate("c2bConfigure", "Network", nullptr));
        QListWidgetItem *___qlistwidgetitem7 = contentsWidget->item(7);
        ___qlistwidgetitem7->setText(QCoreApplication::translate("c2bConfigure", "Shortcuts", nullptr));
        QListWidgetItem *___qlistwidgetitem8 = contentsWidget->item(8);
        ___qlistwidgetitem8->setText(QCoreApplication::translate("c2bConfigure", "Utilities", nullptr));
        contentsWidget->setSortingEnabled(__sortingEnabled);

        groupBox_21->setTitle(QCoreApplication::translate("c2bConfigure", "Annote Cascading Style Sheet (CSS)", nullptr));
        AnnoteCssFile->setText(QString());
#if QT_CONFIG(statustip)
        AnnoteCssDir->setStatusTip(QCoreApplication::translate("c2bConfigure", "Select Annote CSS file", nullptr));
#endif // QT_CONFIG(statustip)
        groupBox_22->setTitle(QCoreApplication::translate("c2bConfigure", "MathJax Header", nullptr));
        MathJaxHeaderFile->setText(QString());
#if QT_CONFIG(statustip)
        MathJaxDir->setStatusTip(QCoreApplication::translate("c2bConfigure", "Select MathJax header file", nullptr));
#endif // QT_CONFIG(statustip)
        groupBox_23->setTitle(QCoreApplication::translate("c2bConfigure", "HTML Output", nullptr));
        IncludeCSS->setText(QCoreApplication::translate("c2bConfigure", "Include CSS in HTML", nullptr));
        UseRelativeLinks->setText(QCoreApplication::translate("c2bConfigure", "Use relative links", nullptr));
        AnnoteViewerFont->setTitle(QCoreApplication::translate("c2bConfigure", "Annote Viewer Font", nullptr));
        textLabel3_9->setText(QCoreApplication::translate("c2bConfigure", "Family", nullptr));
        textLabel3_10->setText(QCoreApplication::translate("c2bConfigure", "Size", nullptr));
        AnnoteViewerFixedFont->setTitle(QCoreApplication::translate("c2bConfigure", "Annote Viewer Fixed Font", nullptr));
        textLabel3_6->setText(QCoreApplication::translate("c2bConfigure", "Family", nullptr));
        textLabel3_5->setText(QCoreApplication::translate("c2bConfigure", "Size", nullptr));
        groupBox_11->setTitle(QCoreApplication::translate("c2bConfigure", "Cite ID Pattern", nullptr));
#if QT_CONFIG(statustip)
        CiteIdPattern->setStatusTip(QCoreApplication::translate("c2bConfigure", "Right click to edit pattern placeholders", nullptr));
#endif // QT_CONFIG(statustip)
        groupBox_9->setTitle(QCoreApplication::translate("c2bConfigure", "Author and Editor Format", nullptr));
        UseFullNames->setText(QCoreApplication::translate("c2bConfigure", "F&ull Name", nullptr));
        UseAbbreviatedNames->setText(QCoreApplication::translate("c2bConfigure", "Abbrevia&ted", nullptr));
        groupBox_10->setTitle(QCoreApplication::translate("c2bConfigure", "Journal Format", nullptr));
        SetJournalsToFullname->setText(QCoreApplication::translate("c2bConfigure", "Full Name", nullptr));
        SetJournalsToAbbreviated->setText(QCoreApplication::translate("c2bConfigure", "Abbreviated", nullptr));
        PageNumberSeparatorBox->setTitle(QCoreApplication::translate("c2bConfigure", "Number Separator", nullptr));
#if QT_CONFIG(statustip)
        PageNumberSeparator->setStatusTip(QCoreApplication::translate("c2bConfigure", "Keep empty for default dash. Blank spaces count", nullptr));
#endif // QT_CONFIG(statustip)
        groupBox_24->setTitle(QCoreApplication::translate("c2bConfigure", "Cite Command Pattern", nullptr));
        groupBox_12->setTitle(QCoreApplication::translate("c2bConfigure", "LaTeX Conversions", nullptr));
        PostprocessMonth->setText(QCoreApplication::translate("c2bConfigure", "Postprocess 'month'", nullptr));
        UseDoubleBraces->setText(QCoreApplication::translate("c2bConfigure", "Set 'title' in double braces", nullptr));
        ConvertReferenceToLaTeX->setText(QCoreApplication::translate("c2bConfigure", "Convert entry strings to LaTe&X", nullptr));
        groupBox_13->setTitle(QCoreApplication::translate("c2bConfigure", "Reference Extraction", nullptr));
        DoHeuristicGuess->setText(QCoreApplication::translate("c2bConfigure", "Tr&y Heuristic Guess if recognition fails", nullptr));
        groupBox_19->setTitle(QCoreApplication::translate("c2bConfigure", "Reference Check", nullptr));
        CheckRepeatedOnSave->setText(QCoreApplication::translate("c2bConfigure", "Check Repeated On Save", nullptr));
        groupBox_14->setTitle(QCoreApplication::translate("c2bConfigure", "External BibTeX Postprocessing", nullptr));
        textLabel2_2_5->setText(QCoreApplication::translate("c2bConfigure", "Aguments:", nullptr));
#if QT_CONFIG(statustip)
        PostprocessBibTeXDir->setStatusTip(QCoreApplication::translate("c2bConfigure", "Select external postprocess tool", nullptr));
#endif // QT_CONFIG(statustip)
        textLabel1_2_4->setText(QCoreApplication::translate("c2bConfigure", "Command:", nullptr));
        textLabel2_2_3_2->setText(QCoreApplication::translate("c2bConfigure", "Output Extension:", nullptr));
        PostprocessBibTeXBin->setText(QString());
        PostprocessBibTeXArg->setText(QString());
        PostprocessBibTeXExt->setText(QString());
        groupBox_4->setTitle(QCoreApplication::translate("c2bConfigure", "Clipboard Preprocessing", nullptr));
        FindReplaceInput->setText(QCoreApplication::translate("c2bConfigure", "Replace/Remove from Input Stream", nullptr));
        FREdit->setText(QCoreApplication::translate("c2bConfigure", "&Edit", nullptr));
#if QT_CONFIG(shortcut)
        FREdit->setShortcut(QCoreApplication::translate("c2bConfigure", "Alt+E", nullptr));
#endif // QT_CONFIG(shortcut)
        FRDelete->setText(QCoreApplication::translate("c2bConfigure", "&Delete", nullptr));
#if QT_CONFIG(shortcut)
        FRDelete->setShortcut(QCoreApplication::translate("c2bConfigure", "Alt+D", nullptr));
#endif // QT_CONFIG(shortcut)
        QTreeWidgetItem *___qtreewidgetitem = FindReplaceList->headerItem();
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("c2bConfigure", "Description", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("c2bConfigure", "Replace", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("c2bConfigure", "Find", nullptr));
        FRNew->setText(QCoreApplication::translate("c2bConfigure", "&New", nullptr));
#if QT_CONFIG(shortcut)
        FRNew->setShortcut(QCoreApplication::translate("c2bConfigure", "Alt+N", nullptr));
#endif // QT_CONFIG(shortcut)
        groupBox_5->setTitle(QCoreApplication::translate("c2bConfigure", "External Clipboard Preparsing Command", nullptr));
        PreparserBin->setText(QString());
#if QT_CONFIG(statustip)
        PreparserDir->setStatusTip(QCoreApplication::translate("c2bConfigure", "Select external parser tool", nullptr));
#endif // QT_CONFIG(statustip)
        PreparserAutomatic->setText(QCoreApplication::translate("c2bConfigure", "Perform always, as part of an automatic extraction", nullptr));
        PreparserShowLog->setText(QCoreApplication::translate("c2bConfigure", "Do not show log", nullptr));
        AddMetadata->setText(QCoreApplication::translate("c2bConfigure", "Add document metadata to Input Stream", nullptr));
        PreAppendMetadata->setTitle(QString());
        Append->setText(QCoreApplication::translate("c2bConfigure", "Append", nullptr));
        Prepend->setText(QCoreApplication::translate("c2bConfigure", "Prepend", nullptr));
#if QT_CONFIG(shortcut)
        Prepend->setShortcut(QString());
#endif // QT_CONFIG(shortcut)
        MovePdf->setText(QCoreApplication::translate("c2bConfigure", "Rename and Copy/Move document files", nullptr));
#if QT_CONFIG(shortcut)
        MovePdf->setShortcut(QString());
#endif // QT_CONFIG(shortcut)
        RenameCopyMovePdf->setTitle(QCoreApplication::translate("c2bConfigure", "Document Options", nullptr));
        label->setText(QCoreApplication::translate("c2bConfigure", "Documents Directory:", nullptr));
        InsertMetadata->setText(QCoreApplication::translate("c2bConfigure", "Insert BibTeX metadata to document files", nullptr));
        RelativePdfDirectory->setText(QCoreApplication::translate("c2bConfigure", "Set directory relative to the BibTeX File Directory", nullptr));
        PdfDirectory->setText(QString());
#if QT_CONFIG(statustip)
        PdfDir->setStatusTip(QCoreApplication::translate("c2bConfigure", "Select PDF directory", nullptr));
#endif // QT_CONFIG(statustip)
        CopyMovePdf->setTitle(QString());
        Move->setText(QCoreApplication::translate("c2bConfigure", "Move (local so&urce files)", nullptr));
        Copy->setText(QCoreApplication::translate("c2bConfigure", "Copy", nullptr));
#if QT_CONFIG(shortcut)
        Copy->setShortcut(QString());
#endif // QT_CONFIG(shortcut)
        DocumentIdPatternBox->setTitle(QCoreApplication::translate("c2bConfigure", "Document ID Pattern", nullptr));
#if QT_CONFIG(statustip)
        DocumentIdPattern->setStatusTip(QCoreApplication::translate("c2bConfigure", "Right click to edit pattern placeholders", nullptr));
#endif // QT_CONFIG(statustip)
        groupBox_18->setTitle(QCoreApplication::translate("c2bConfigure", "ExifTool Metadata writer", nullptr));
        ExifToolBin->setText(QString());
#if QT_CONFIG(statustip)
        ExifToolDir->setStatusTip(QCoreApplication::translate("c2bConfigure", "Select ExifTool executable", nullptr));
#endif // QT_CONFIG(statustip)
        textLabel1_6->setText(QCoreApplication::translate("c2bConfigure", "Command:", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("c2bConfigure", "Journal Abbreviation List File", nullptr));
        JournalFile->setText(QString());
#if QT_CONFIG(statustip)
        JournalDir->setStatusTip(QCoreApplication::translate("c2bConfigure", "Select journal abbreviation file", nullptr));
#endif // QT_CONFIG(statustip)
        groupBox_2->setTitle(QCoreApplication::translate("c2bConfigure", "Regular Expression List File", nullptr));
        RegularExpressionFile->setText(QString());
#if QT_CONFIG(statustip)
        RegularExpressionDir->setStatusTip(QCoreApplication::translate("c2bConfigure", "Select regular expression file", nullptr));
#endif // QT_CONFIG(statustip)
        groupBox_16->setTitle(QCoreApplication::translate("c2bConfigure", "Bookmarks and Network Query Info File", nullptr));
        NetworkFile->setText(QString());
#if QT_CONFIG(statustip)
        NetworkDir->setStatusTip(QCoreApplication::translate("c2bConfigure", "Select network informantion file", nullptr));
#endif // QT_CONFIG(statustip)
        groupBox_6->setTitle(QCoreApplication::translate("c2bConfigure", "Browser Cascading Style Sheet (CSS)", nullptr));
        BrowserCssFile->setText(QString());
#if QT_CONFIG(statustip)
        BrowserCssDir->setStatusTip(QCoreApplication::translate("c2bConfigure", "Select CSS file", nullptr));
#endif // QT_CONFIG(statustip)
        groupBox_20->setTitle(QCoreApplication::translate("c2bConfigure", "Part Of Speech (POS) Lexicon", nullptr));
        PosLexiconFile->setText(QString());
#if QT_CONFIG(statustip)
        PosLexiconDir->setStatusTip(QCoreApplication::translate("c2bConfigure", "Select POS lexicon file", nullptr));
#endif // QT_CONFIG(statustip)
        groupBox_7->setTitle(QCoreApplication::translate("c2bConfigure", "Search In Files Cache Directory", nullptr));
        CacheDirectory->setText(QString());
#if QT_CONFIG(statustip)
        CacheDir->setStatusTip(QCoreApplication::translate("c2bConfigure", "Select cache directory", nullptr));
#endif // QT_CONFIG(statustip)
        groupBox->setTitle(QString());
        textLabel3->setText(QCoreApplication::translate("c2bConfigure", "Family", nullptr));
        textLabel3_2->setText(QCoreApplication::translate("c2bConfigure", "Size", nullptr));
        samplelineedit->setText(QCoreApplication::translate("c2bConfigure", "Sample Text", nullptr));
        QTreeWidgetItem *___qtreewidgetitem1 = ColorList->headerItem();
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("c2bConfigure", "Context Colors", nullptr));
        FmClient->setText(QCoreApplication::translate("c2bConfigure", "Use E&xternal Network Client", nullptr));
        clientGroupBox->setTitle(QString());
        textLabel1_2_3->setText(QCoreApplication::translate("c2bConfigure", "Copy:", nullptr));
        FmClientCopyBin->setText(QCoreApplication::translate("c2bConfigure", "kfmclient", nullptr));
#if QT_CONFIG(statustip)
        FmClientCopyDir->setStatusTip(QCoreApplication::translate("c2bConfigure", "Select external copy executable", nullptr));
#endif // QT_CONFIG(statustip)
        textLabel2_2_3->setText(QCoreApplication::translate("c2bConfigure", "Copy Aguments:", nullptr));
        FmClientCopyArg->setText(QString());
        textLabel1_2_2_4->setText(QCoreApplication::translate("c2bConfigure", "Move:", nullptr));
        FmClientMoveBin->setText(QCoreApplication::translate("c2bConfigure", "kfmclient", nullptr));
#if QT_CONFIG(statustip)
        FmClientMoveDir->setStatusTip(QCoreApplication::translate("c2bConfigure", "Select external move executable", nullptr));
#endif // QT_CONFIG(statustip)
        textLabel2_2_2_3->setText(QCoreApplication::translate("c2bConfigure", "Move Aguments:", nullptr));
        FmClientMoveArg->setText(QString());
        UseProxy->setText(QCoreApplication::translate("c2bConfigure", "Use Proxy", nullptr));
        proxyGroupBox->setTitle(QString());
        textLabel1_2_5->setText(QCoreApplication::translate("c2bConfigure", "Host:", nullptr));
        ProxyHostName->setText(QString());
        textLabel1_2_2_5->setText(QCoreApplication::translate("c2bConfigure", "Port:", nullptr));
        ProxyPort->setText(QString());
        textLabel1_2_2_6->setText(QCoreApplication::translate("c2bConfigure", "Type:", nullptr));
        ProxyType->setItemText(0, QCoreApplication::translate("c2bConfigure", "Http", nullptr));
        ProxyType->setItemText(1, QCoreApplication::translate("c2bConfigure", "Socks5", nullptr));

        groupBox_8->setTitle(QCoreApplication::translate("c2bConfigure", "Queries", nullptr));
        AutomaticPdfDownload->setText(QCoreApplication::translate("c2bConfigure", "Download document if available", nullptr));
        KeepTmpNQFiles->setText(QCoreApplication::translate("c2bConfigure", "&Keep Query temporary files (Debug Only)", nullptr));
        AutomaticQuery->setText(QCoreApplication::translate("c2bConfigure", "Perform Network Queries after automatic reference extractions", nullptr));
#if QT_CONFIG(shortcut)
        AutomaticQuery->setShortcut(QCoreApplication::translate("c2bConfigure", "Alt+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        cb2BibScGroupBox->setTitle(QCoreApplication::translate("c2bConfigure", "Main panel", nullptr));
        EditorScGroupBox->setTitle(QCoreApplication::translate("c2bConfigure", "Editor and reference list", nullptr));
        groupBox_15->setTitle(QCoreApplication::translate("c2bConfigure", "PDF Import: To plain text converter", nullptr));
#if QT_CONFIG(statustip)
        PdfImportPdf2TextDir->setStatusTip(QCoreApplication::translate("c2bConfigure", "Select external convert tool", nullptr));
#endif // QT_CONFIG(statustip)
        textLabel2_6->setText(QCoreApplication::translate("c2bConfigure", "Aguments:", nullptr));
        textLabel1_4->setText(QCoreApplication::translate("c2bConfigure", "Command:", nullptr));
        PdfImportPdf2TextBin->setText(QString());
        PdfImportPdf2TextArg->setText(QString());
        groupBox_17->setTitle(QCoreApplication::translate("c2bConfigure", "BibTeX search: To plain text converter", nullptr));
#if QT_CONFIG(statustip)
        BibSearcherPdf2TextDir->setStatusTip(QCoreApplication::translate("c2bConfigure", "Select external convert tool", nullptr));
#endif // QT_CONFIG(statustip)
        textLabel2_7->setText(QCoreApplication::translate("c2bConfigure", "Aguments:", nullptr));
        textLabel1_5->setText(QCoreApplication::translate("c2bConfigure", "Command:", nullptr));
        BibSearcherPdf2TextBin->setText(QString());
        BibSearcherPdf2TextArg->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class c2bConfigure: public Ui_c2bConfigure {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C2BCONFIGURE_H
