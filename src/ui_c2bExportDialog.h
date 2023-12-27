/********************************************************************************
** Form generated from reading UI file 'c2bExportDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C2BEXPORTDIALOG_H
#define UI_C2BEXPORTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include "c2bLineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_c2bExportDialog
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox2;
    QGridLayout *gridLayout1;
    QLabel *label;
    QHBoxLayout *hboxLayout;
    c2bLineEdit *ExportFile;
    QToolButton *ExportFileDir;
    QFrame *line_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout2;
    QCheckBox *CopyDocuments;
    QGroupBox *DocumentsDirectoryBox;
    QGridLayout *gridLayout3;
    QHBoxLayout *hboxLayout1;
    c2bLineEdit *DocumentsDirectory;
    QToolButton *DocumentsDirectoryDir;
    QCheckBox *RelativeDocumentDirectory;
    QSpacerItem *spacerItem;
    QFrame *line;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *c2bExportDialog)
    {
        if (c2bExportDialog->objectName().isEmpty())
            c2bExportDialog->setObjectName(QString::fromUtf8("c2bExportDialog"));
        c2bExportDialog->resize(563, 308);
        gridLayout = new QGridLayout(c2bExportDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox2 = new QGroupBox(c2bExportDialog);
        groupBox2->setObjectName(QString::fromUtf8("groupBox2"));
        gridLayout1 = new QGridLayout(groupBox2);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        label = new QLabel(groupBox2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout1->addWidget(label, 0, 0, 1, 1);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        ExportFile = new c2bLineEdit(groupBox2);
        ExportFile->setObjectName(QString::fromUtf8("ExportFile"));

        hboxLayout->addWidget(ExportFile);

        ExportFileDir = new QToolButton(groupBox2);
        ExportFileDir->setObjectName(QString::fromUtf8("ExportFileDir"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/mimeFolder.png"), QSize(), QIcon::Normal, QIcon::Off);
        ExportFileDir->setIcon(icon);

        hboxLayout->addWidget(ExportFileDir);


        gridLayout1->addLayout(hboxLayout, 0, 1, 1, 1);


        gridLayout->addWidget(groupBox2, 0, 0, 1, 1);

        line_2 = new QFrame(c2bExportDialog);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 1, 0, 1, 1);

        groupBox = new QGroupBox(c2bExportDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout2 = new QGridLayout(groupBox);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        CopyDocuments = new QCheckBox(groupBox);
        CopyDocuments->setObjectName(QString::fromUtf8("CopyDocuments"));

        gridLayout2->addWidget(CopyDocuments, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox, 2, 0, 1, 1);

        DocumentsDirectoryBox = new QGroupBox(c2bExportDialog);
        DocumentsDirectoryBox->setObjectName(QString::fromUtf8("DocumentsDirectoryBox"));
        gridLayout3 = new QGridLayout(DocumentsDirectoryBox);
        gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
        hboxLayout1 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
#endif
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        DocumentsDirectory = new c2bLineEdit(DocumentsDirectoryBox);
        DocumentsDirectory->setObjectName(QString::fromUtf8("DocumentsDirectory"));

        hboxLayout1->addWidget(DocumentsDirectory);

        DocumentsDirectoryDir = new QToolButton(DocumentsDirectoryBox);
        DocumentsDirectoryDir->setObjectName(QString::fromUtf8("DocumentsDirectoryDir"));
        DocumentsDirectoryDir->setIcon(icon);

        hboxLayout1->addWidget(DocumentsDirectoryDir);


        gridLayout3->addLayout(hboxLayout1, 0, 0, 1, 1);

        RelativeDocumentDirectory = new QCheckBox(DocumentsDirectoryBox);
        RelativeDocumentDirectory->setObjectName(QString::fromUtf8("RelativeDocumentDirectory"));

        gridLayout3->addWidget(RelativeDocumentDirectory, 1, 0, 1, 1);


        gridLayout->addWidget(DocumentsDirectoryBox, 3, 0, 1, 1);

        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacerItem, 4, 0, 1, 1);

        line = new QFrame(c2bExportDialog);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 5, 0, 1, 1);

        buttonBox = new QDialogButtonBox(c2bExportDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Help);

        gridLayout->addWidget(buttonBox, 6, 0, 1, 1);


        retranslateUi(c2bExportDialog);
        QObject::connect(buttonBox, SIGNAL(rejected()), c2bExportDialog, SLOT(reject()));
        QObject::connect(CopyDocuments, SIGNAL(clicked(bool)), DocumentsDirectoryBox, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(c2bExportDialog);
    } // setupUi

    void retranslateUi(QDialog *c2bExportDialog)
    {
        c2bExportDialog->setWindowTitle(QCoreApplication::translate("c2bExportDialog", "Dialog", nullptr));
        groupBox2->setTitle(QString());
        label->setText(QCoreApplication::translate("c2bExportDialog", "BibTeX File:", nullptr));
        ExportFile->setText(QString());
#if QT_CONFIG(statustip)
        ExportFileDir->setStatusTip(QCoreApplication::translate("c2bExportDialog", "Select BibTeX directory", nullptr));
#endif // QT_CONFIG(statustip)
        groupBox->setTitle(QString());
        CopyDocuments->setText(QCoreApplication::translate("c2bExportDialog", "Copy Documents", nullptr));
#if QT_CONFIG(shortcut)
        CopyDocuments->setShortcut(QString());
#endif // QT_CONFIG(shortcut)
        DocumentsDirectoryBox->setTitle(QCoreApplication::translate("c2bExportDialog", "Documents Directory", nullptr));
        DocumentsDirectory->setText(QString());
#if QT_CONFIG(statustip)
        DocumentsDirectoryDir->setStatusTip(QCoreApplication::translate("c2bExportDialog", "Select PDF directory", nullptr));
#endif // QT_CONFIG(statustip)
        RelativeDocumentDirectory->setText(QCoreApplication::translate("c2bExportDialog", "Set directory relative to the BibTeX File Directory", nullptr));
    } // retranslateUi

};

namespace Ui {
    class c2bExportDialog: public Ui_c2bExportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C2BEXPORTDIALOG_H
