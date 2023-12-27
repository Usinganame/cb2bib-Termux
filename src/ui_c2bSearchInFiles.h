/********************************************************************************
** Form generated from reading UI file 'c2bSearchInFiles.ui'
**
** Created by: Qt User Interface Compiler version 5.15.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C2BSEARCHINFILES_H
#define UI_C2BSEARCHINFILES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeWidget>
#include "c2bSearchInFilesPattern.h"

QT_BEGIN_NAMESPACE

class Ui_c2bSearchInFiles
{
public:
    QGridLayout *gridLayout;
    QGroupBox *Modifiers;
    QGridLayout *gridLayout1;
    QCheckBox *simplifySource;
    QSpacerItem *spacerItem;
    QGroupBox *Scope;
    QGridLayout *gridLayout2;
    QCheckBox *documentFiles;
    QCheckBox *allBibFiles;
    QSpacerItem *spacerItem1;
    QLabel *searchLog;
    QFrame *line;
    QFrame *line_4;
    QFrame *line_2;
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QGridLayout *gridLayout3;
    c2bSearchInFilesPattern *pattern;
    QFrame *line_3;
    QGroupBox *Composite;
    QGridLayout *gridLayout4;
    QPushButton *editPatternB;
    QPushButton *deletePatternB;
    QPushButton *addPatternB;
    QTreeWidget *patternList;
    QSpacerItem *spacerItem2;
    QComboBox *Boolean;

    void setupUi(QDialog *c2bSearchInFiles)
    {
        if (c2bSearchInFiles->objectName().isEmpty())
            c2bSearchInFiles->setObjectName(QString::fromUtf8("c2bSearchInFiles"));
        c2bSearchInFiles->resize(824, 494);
        gridLayout = new QGridLayout(c2bSearchInFiles);
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(6, 6, 6, 6);
        Modifiers = new QGroupBox(c2bSearchInFiles);
        Modifiers->setObjectName(QString::fromUtf8("Modifiers"));
        gridLayout1 = new QGridLayout(Modifiers);
        gridLayout1->setSpacing(6);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        gridLayout1->setContentsMargins(9, 9, 9, 9);
        simplifySource = new QCheckBox(Modifiers);
        simplifySource->setObjectName(QString::fromUtf8("simplifySource"));

        gridLayout1->addWidget(simplifySource, 0, 0, 1, 1);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout1->addItem(spacerItem, 0, 1, 1, 1);


        gridLayout->addWidget(Modifiers, 4, 1, 1, 1);

        Scope = new QGroupBox(c2bSearchInFiles);
        Scope->setObjectName(QString::fromUtf8("Scope"));
        gridLayout2 = new QGridLayout(Scope);
        gridLayout2->setSpacing(6);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        gridLayout2->setContentsMargins(9, 9, 9, 9);
        documentFiles = new QCheckBox(Scope);
        documentFiles->setObjectName(QString::fromUtf8("documentFiles"));

        gridLayout2->addWidget(documentFiles, 0, 1, 1, 1);

        allBibFiles = new QCheckBox(Scope);
        allBibFiles->setObjectName(QString::fromUtf8("allBibFiles"));

        gridLayout2->addWidget(allBibFiles, 0, 0, 1, 1);

        spacerItem1 = new QSpacerItem(16, 22, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout2->addItem(spacerItem1, 0, 2, 1, 1);


        gridLayout->addWidget(Scope, 4, 0, 1, 1);

        searchLog = new QLabel(c2bSearchInFiles);
        searchLog->setObjectName(QString::fromUtf8("searchLog"));

        gridLayout->addWidget(searchLog, 6, 0, 1, 2);

        line = new QFrame(c2bSearchInFiles);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 7, 0, 1, 2);

        line_4 = new QFrame(c2bSearchInFiles);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_4, 5, 0, 1, 2);

        line_2 = new QFrame(c2bSearchInFiles);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 3, 0, 1, 2);

        buttonBox = new QDialogButtonBox(c2bSearchInFiles);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setFocusPolicy(Qt::NoFocus);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Abort|QDialogButtonBox::Close|QDialogButtonBox::Help);

        gridLayout->addWidget(buttonBox, 8, 0, 1, 2);

        groupBox = new QGroupBox(c2bSearchInFiles);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout3 = new QGridLayout(groupBox);
        gridLayout3->setSpacing(6);
        gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
        gridLayout3->setContentsMargins(9, 9, 9, 9);
        pattern = new c2bSearchInFilesPattern(groupBox);
        pattern->setObjectName(QString::fromUtf8("pattern"));

        gridLayout3->addWidget(pattern, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 2);

        line_3 = new QFrame(c2bSearchInFiles);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_3, 1, 0, 1, 2);

        Composite = new QGroupBox(c2bSearchInFiles);
        Composite->setObjectName(QString::fromUtf8("Composite"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Composite->sizePolicy().hasHeightForWidth());
        Composite->setSizePolicy(sizePolicy);
        gridLayout4 = new QGridLayout(Composite);
        gridLayout4->setSpacing(6);
        gridLayout4->setObjectName(QString::fromUtf8("gridLayout4"));
        gridLayout4->setContentsMargins(9, 9, 9, 9);
        editPatternB = new QPushButton(Composite);
        editPatternB->setObjectName(QString::fromUtf8("editPatternB"));
        editPatternB->setEnabled(false);

        gridLayout4->addWidget(editPatternB, 3, 1, 1, 1);

        deletePatternB = new QPushButton(Composite);
        deletePatternB->setObjectName(QString::fromUtf8("deletePatternB"));
        deletePatternB->setEnabled(false);

        gridLayout4->addWidget(deletePatternB, 4, 1, 1, 1);

        addPatternB = new QPushButton(Composite);
        addPatternB->setObjectName(QString::fromUtf8("addPatternB"));
        addPatternB->setEnabled(false);
        addPatternB->setContextMenuPolicy(Qt::PreventContextMenu);

        gridLayout4->addWidget(addPatternB, 2, 1, 1, 1);

        patternList = new QTreeWidget(Composite);
        patternList->headerItem()->setText(0, QString());
        patternList->headerItem()->setText(4, QString());
        patternList->setObjectName(QString::fromUtf8("patternList"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(patternList->sizePolicy().hasHeightForWidth());
        patternList->setSizePolicy(sizePolicy1);
        patternList->setTabKeyNavigation(true);
        patternList->setRootIsDecorated(false);
        patternList->setAnimated(true);

        gridLayout4->addWidget(patternList, 0, 0, 5, 1);

        spacerItem2 = new QSpacerItem(75, 91, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout4->addItem(spacerItem2, 1, 1, 1, 1);

        Boolean = new QComboBox(Composite);
        Boolean->addItem(QString());
        Boolean->addItem(QString());
        Boolean->setObjectName(QString::fromUtf8("Boolean"));
        Boolean->setEnabled(false);

        gridLayout4->addWidget(Boolean, 0, 1, 1, 1);


        gridLayout->addWidget(Composite, 2, 0, 1, 2);

        QWidget::setTabOrder(patternList, addPatternB);
        QWidget::setTabOrder(addPatternB, deletePatternB);
        QWidget::setTabOrder(deletePatternB, allBibFiles);
        QWidget::setTabOrder(allBibFiles, documentFiles);
        QWidget::setTabOrder(documentFiles, buttonBox);

        retranslateUi(c2bSearchInFiles);
        QObject::connect(buttonBox, SIGNAL(rejected()), c2bSearchInFiles, SLOT(reject()));

        QMetaObject::connectSlotsByName(c2bSearchInFiles);
    } // setupUi

    void retranslateUi(QDialog *c2bSearchInFiles)
    {
        c2bSearchInFiles->setWindowTitle(QCoreApplication::translate("c2bSearchInFiles", "Search in files - cb2Bib", nullptr));
        Modifiers->setTitle(QCoreApplication::translate("c2bSearchInFiles", "Modifier", nullptr));
        simplifySource->setText(QCoreApplication::translate("c2bSearchInFiles", "&Simplify source", nullptr));
        Scope->setTitle(QCoreApplication::translate("c2bSearchInFiles", "Search scope", nullptr));
        documentFiles->setText(QCoreApplication::translate("c2bSearchInFiles", "Scan &linked documents", nullptr));
        allBibFiles->setText(QCoreApplication::translate("c2bSearchInFiles", "Scan all &BibTeX files", nullptr));
        searchLog->setText(QCoreApplication::translate("c2bSearchInFiles", "Search for ...", nullptr));
        groupBox->setTitle(QCoreApplication::translate("c2bSearchInFiles", "Pattern", nullptr));
        Composite->setTitle(QCoreApplication::translate("c2bSearchInFiles", "Composite pattern", nullptr));
        editPatternB->setText(QCoreApplication::translate("c2bSearchInFiles", "&Edit", nullptr));
        deletePatternB->setText(QCoreApplication::translate("c2bSearchInFiles", "&Delete", nullptr));
        addPatternB->setText(QCoreApplication::translate("c2bSearchInFiles", "&Add", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = patternList->headerItem();
        ___qtreewidgetitem->setText(5, QCoreApplication::translate("c2bSearchInFiles", "Pattern", nullptr));
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("c2bSearchInFiles", "Scope", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("c2bSearchInFiles", "Type", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("c2bSearchInFiles", "Case", nullptr));
        Boolean->setItemText(0, QCoreApplication::translate("c2bSearchInFiles", "All", nullptr));
        Boolean->setItemText(1, QCoreApplication::translate("c2bSearchInFiles", "Any", nullptr));

    } // retranslateUi

};

namespace Ui {
    class c2bSearchInFiles: public Ui_c2bSearchInFiles {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C2BSEARCHINFILES_H
