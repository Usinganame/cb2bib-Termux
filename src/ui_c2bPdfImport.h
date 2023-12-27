/********************************************************************************
** Form generated from reading UI file 'c2bPdfImport.ui'
**
** Created by: Qt User Interface Compiler version 5.15.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C2BPDFIMPORT_H
#define UI_C2BPDFIMPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>

QT_BEGIN_NAMESPACE

class Ui_c2bPdfImport
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QListWidget *PDFlist;
    QPlainTextEdit *Log;
    QStatusBar *statusBar;
    QDialogButtonBox *buttonBox;
    QFrame *line;
    QFrame *line1;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout1;
    QSpacerItem *spacerItem;
    QCheckBox *AutomaticQuery;
    QCheckBox *OpenFiles;
    QGroupBox *groupBox;
    QGridLayout *gridLayout2;
    QSpacerItem *spacerItem1;
    QCheckBox *DoNextAfterSaving;
    QCheckBox *DoAll;

    void setupUi(QDialog *c2bPdfImport)
    {
        if (c2bPdfImport->objectName().isEmpty())
            c2bPdfImport->setObjectName(QString::fromUtf8("c2bPdfImport"));
        c2bPdfImport->resize(869, 414);
        c2bPdfImport->setAcceptDrops(true);
        gridLayout = new QGridLayout(c2bPdfImport);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(6, 6, 6, 6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter = new QSplitter(c2bPdfImport);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        PDFlist = new QListWidget(splitter);
        PDFlist->setObjectName(QString::fromUtf8("PDFlist"));
        PDFlist->setFrameShadow(QFrame::Raised);
        splitter->addWidget(PDFlist);
        Log = new QPlainTextEdit(splitter);
        Log->setObjectName(QString::fromUtf8("Log"));
        Log->setFrameShape(QFrame::StyledPanel);
        Log->setFrameShadow(QFrame::Raised);
        Log->setReadOnly(true);
        splitter->addWidget(Log);

        gridLayout->addWidget(splitter, 0, 0, 1, 2);

        statusBar = new QStatusBar(c2bPdfImport);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(statusBar->sizePolicy().hasHeightForWidth());
        statusBar->setSizePolicy(sizePolicy);
        statusBar->setSizeGripEnabled(false);

        gridLayout->addWidget(statusBar, 3, 0, 1, 2);

        buttonBox = new QDialogButtonBox(c2bPdfImport);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Abort|QDialogButtonBox::Close|QDialogButtonBox::Help);

        gridLayout->addWidget(buttonBox, 5, 0, 1, 2);

        line = new QFrame(c2bPdfImport);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 4, 0, 1, 2);

        line1 = new QFrame(c2bPdfImport);
        line1->setObjectName(QString::fromUtf8("line1"));
        line1->setFrameShape(QFrame::HLine);
        line1->setFrameShadow(QFrame::Sunken);
        line1->setFrameShape(QFrame::HLine);

        gridLayout->addWidget(line1, 2, 0, 1, 2);

        groupBox_2 = new QGroupBox(c2bPdfImport);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout1 = new QGridLayout(groupBox_2);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(9, 9, 9, 9);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout1->addItem(spacerItem, 0, 2, 1, 1);

        AutomaticQuery = new QCheckBox(groupBox_2);
        AutomaticQuery->setObjectName(QString::fromUtf8("AutomaticQuery"));

        gridLayout1->addWidget(AutomaticQuery, 0, 1, 1, 1);

        OpenFiles = new QCheckBox(groupBox_2);
        OpenFiles->setObjectName(QString::fromUtf8("OpenFiles"));

        gridLayout1->addWidget(OpenFiles, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_2, 1, 1, 1, 1);

        groupBox = new QGroupBox(c2bPdfImport);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout2 = new QGridLayout(groupBox);
        gridLayout2->setSpacing(6);
        gridLayout2->setContentsMargins(9, 9, 9, 9);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout2->addItem(spacerItem1, 0, 2, 1, 1);

        DoNextAfterSaving = new QCheckBox(groupBox);
        DoNextAfterSaving->setObjectName(QString::fromUtf8("DoNextAfterSaving"));

        gridLayout2->addWidget(DoNextAfterSaving, 0, 0, 1, 1);

        DoAll = new QCheckBox(groupBox);
        DoAll->setObjectName(QString::fromUtf8("DoAll"));

        gridLayout2->addWidget(DoAll, 0, 1, 1, 1);


        gridLayout->addWidget(groupBox, 1, 0, 1, 1);

        QWidget::setTabOrder(PDFlist, Log);
        QWidget::setTabOrder(Log, OpenFiles);
        QWidget::setTabOrder(OpenFiles, DoNextAfterSaving);
        QWidget::setTabOrder(DoNextAfterSaving, buttonBox);

        retranslateUi(c2bPdfImport);
        QObject::connect(buttonBox, SIGNAL(rejected()), c2bPdfImport, SLOT(reject()));

        QMetaObject::connectSlotsByName(c2bPdfImport);
    } // setupUi

    void retranslateUi(QDialog *c2bPdfImport)
    {
        c2bPdfImport->setWindowTitle(QCoreApplication::translate("c2bPdfImport", "PDFImport - cb2Bib", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("c2bPdfImport", "Miscellaneous", nullptr));
#if QT_CONFIG(statustip)
        AutomaticQuery->setStatusTip(QCoreApplication::translate("c2bPdfImport", "Perform network queries after automatic reference extractions", nullptr));
#endif // QT_CONFIG(statustip)
        AutomaticQuery->setText(QCoreApplication::translate("c2bPdfImport", "Perform network queries", nullptr));
#if QT_CONFIG(tooltip)
        OpenFiles->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        OpenFiles->setStatusTip(QCoreApplication::translate("c2bPdfImport", "Open document files", nullptr));
#endif // QT_CONFIG(statustip)
        OpenFiles->setText(QCoreApplication::translate("c2bPdfImport", "Open document files", nullptr));
        groupBox->setTitle(QCoreApplication::translate("c2bPdfImport", "Sequence", nullptr));
#if QT_CONFIG(statustip)
        DoNextAfterSaving->setStatusTip(QCoreApplication::translate("c2bPdfImport", "Process next after saving", nullptr));
#endif // QT_CONFIG(statustip)
        DoNextAfterSaving->setText(QCoreApplication::translate("c2bPdfImport", "Process next after saving", nullptr));
#if QT_CONFIG(statustip)
        DoAll->setStatusTip(QCoreApplication::translate("c2bPdfImport", "Unsupervised processing", nullptr));
#endif // QT_CONFIG(statustip)
        DoAll->setText(QCoreApplication::translate("c2bPdfImport", "Unsupervised processing", nullptr));
    } // retranslateUi

};

namespace Ui {
    class c2bPdfImport: public Ui_c2bPdfImport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C2BPDFIMPORT_H
