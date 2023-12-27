/********************************************************************************
** Form generated from reading UI file 'c2bSearchInFilesPattern.ui'
**
** Created by: Qt User Interface Compiler version 5.15.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C2BSEARCHINFILESPATTERN_H
#define UI_C2BSEARCHINFILESPATTERN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "c2bLineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_c2bSearchInFilesPattern
{
public:
    QGridLayout *gridLayout;
    QFrame *line;
    QHBoxLayout *hboxLayout;
    c2bLineEdit *inputPattern;
    QToolButton *clearB;
    QSpacerItem *spacerItem;
    QLabel *label;
    QCheckBox *NOT;
    QLabel *label_2;
    QComboBox *patternType;
    QCheckBox *caseSensitive;
    QComboBox *yearScope;
    QComboBox *patternScope;

    void setupUi(QWidget *c2bSearchInFilesPattern)
    {
        if (c2bSearchInFilesPattern->objectName().isEmpty())
            c2bSearchInFilesPattern->setObjectName(QString::fromUtf8("c2bSearchInFilesPattern"));
        c2bSearchInFilesPattern->resize(687, 83);
        gridLayout = new QGridLayout(c2bSearchInFilesPattern);
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        line = new QFrame(c2bSearchInFilesPattern);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 1, 0, 1, 8);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        inputPattern = new c2bLineEdit(c2bSearchInFilesPattern);
        inputPattern->setObjectName(QString::fromUtf8("inputPattern"));

        hboxLayout->addWidget(inputPattern);

        clearB = new QToolButton(c2bSearchInFilesPattern);
        clearB->setObjectName(QString::fromUtf8("clearB"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/clear_left.png"), QSize(), QIcon::Normal, QIcon::Off);
        clearB->setIcon(icon);

        hboxLayout->addWidget(clearB);


        gridLayout->addLayout(hboxLayout, 0, 0, 1, 8);

        spacerItem = new QSpacerItem(16, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem, 2, 7, 1, 1);

        label = new QLabel(c2bSearchInFilesPattern);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 2, 2, 1, 1);

        NOT = new QCheckBox(c2bSearchInFilesPattern);
        NOT->setObjectName(QString::fromUtf8("NOT"));

        gridLayout->addWidget(NOT, 2, 0, 1, 1);

        label_2 = new QLabel(c2bSearchInFilesPattern);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 4, 1, 1);

        patternType = new QComboBox(c2bSearchInFilesPattern);
        patternType->setObjectName(QString::fromUtf8("patternType"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(patternType->sizePolicy().hasHeightForWidth());
        patternType->setSizePolicy(sizePolicy);

        gridLayout->addWidget(patternType, 2, 3, 1, 1);

        caseSensitive = new QCheckBox(c2bSearchInFilesPattern);
        caseSensitive->setObjectName(QString::fromUtf8("caseSensitive"));

        gridLayout->addWidget(caseSensitive, 2, 1, 1, 1);

        yearScope = new QComboBox(c2bSearchInFilesPattern);
        yearScope->addItem(QString());
        yearScope->addItem(QString());
        yearScope->addItem(QString());
        yearScope->setObjectName(QString::fromUtf8("yearScope"));

        gridLayout->addWidget(yearScope, 2, 6, 1, 1);

        patternScope = new QComboBox(c2bSearchInFilesPattern);
        patternScope->addItem(QString());
        patternScope->setObjectName(QString::fromUtf8("patternScope"));

        gridLayout->addWidget(patternScope, 2, 5, 1, 1);


        retranslateUi(c2bSearchInFilesPattern);
        QObject::connect(clearB, SIGNAL(clicked()), inputPattern, SLOT(clear()));
        QObject::connect(clearB, SIGNAL(clicked()), inputPattern, SLOT(setFocus()));

        QMetaObject::connectSlotsByName(c2bSearchInFilesPattern);
    } // setupUi

    void retranslateUi(QWidget *c2bSearchInFilesPattern)
    {
        c2bSearchInFilesPattern->setWindowTitle(QCoreApplication::translate("c2bSearchInFilesPattern", "Pattern", nullptr));
        label->setText(QCoreApplication::translate("c2bSearchInFilesPattern", "Type:", nullptr));
        NOT->setText(QCoreApplication::translate("c2bSearchInFilesPattern", "&NOT", nullptr));
        label_2->setText(QCoreApplication::translate("c2bSearchInFilesPattern", "Scope:", nullptr));
        caseSensitive->setText(QCoreApplication::translate("c2bSearchInFilesPattern", "&Case sensitive", nullptr));
        yearScope->setItemText(0, QCoreApplication::translate("c2bSearchInFilesPattern", "Exact", nullptr));
        yearScope->setItemText(1, QCoreApplication::translate("c2bSearchInFilesPattern", "Newer", nullptr));
        yearScope->setItemText(2, QCoreApplication::translate("c2bSearchInFilesPattern", "Older", nullptr));

        patternScope->setItemText(0, QCoreApplication::translate("c2bSearchInFilesPattern", "all", nullptr));

    } // retranslateUi

};

namespace Ui {
    class c2bSearchInFilesPattern: public Ui_c2bSearchInFilesPattern {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C2BSEARCHINFILESPATTERN_H
