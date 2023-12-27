/********************************************************************************
** Form generated from reading UI file 'c2bRLWebSearchSettings.ui'
**
** Created by: Qt User Interface Compiler version 5.15.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C2BRLWEBSEARCHSETTINGS_H
#define UI_C2BRLWEBSEARCHSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include "c2bComboBox.h"

QT_BEGIN_NAMESPACE

class Ui_c2bRLWebSearchSettings
{
public:
    QGridLayout *gridLayout;
    QCheckBox *addQuotes;
    QSpacerItem *spacerItem;
    QFrame *line;
    QDialogButtonBox *buttonBox;
    QSpacerItem *spacerItem1;
    QLabel *label;
    c2bComboBox *searchEngine;
    QFrame *line_2;

    void setupUi(QDialog *c2bRLWebSearchSettings)
    {
        if (c2bRLWebSearchSettings->objectName().isEmpty())
            c2bRLWebSearchSettings->setObjectName(QString::fromUtf8("c2bRLWebSearchSettings"));
        c2bRLWebSearchSettings->resize(466, 152);
        c2bRLWebSearchSettings->setSizeGripEnabled(false);
        gridLayout = new QGridLayout(c2bRLWebSearchSettings);
        gridLayout->setSpacing(3);
        gridLayout->setContentsMargins(6, 6, 6, 6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        addQuotes = new QCheckBox(c2bRLWebSearchSettings);
        addQuotes->setObjectName(QString::fromUtf8("addQuotes"));

        gridLayout->addWidget(addQuotes, 3, 0, 1, 3);

        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacerItem, 4, 1, 1, 1);

        line = new QFrame(c2bRLWebSearchSettings);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 5, 0, 1, 3);

        buttonBox = new QDialogButtonBox(c2bRLWebSearchSettings);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setLayoutDirection(Qt::LeftToRight);
        buttonBox->setAutoFillBackground(true);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);

        gridLayout->addWidget(buttonBox, 6, 2, 1, 1);

        spacerItem1 = new QSpacerItem(121, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem1, 6, 0, 1, 1);

        label = new QLabel(c2bRLWebSearchSettings);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 3);

        searchEngine = new c2bComboBox(c2bRLWebSearchSettings);
        searchEngine->setObjectName(QString::fromUtf8("searchEngine"));
        searchEngine->setEditable(true);
        searchEngine->setInsertPolicy(QComboBox::NoInsert);

        gridLayout->addWidget(searchEngine, 1, 0, 1, 3);

        line_2 = new QFrame(c2bRLWebSearchSettings);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 2, 0, 1, 3);

        QWidget::setTabOrder(addQuotes, buttonBox);

        retranslateUi(c2bRLWebSearchSettings);
        QObject::connect(buttonBox, SIGNAL(accepted()), c2bRLWebSearchSettings, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), c2bRLWebSearchSettings, SLOT(reject()));

        QMetaObject::connectSlotsByName(c2bRLWebSearchSettings);
    } // setupUi

    void retranslateUi(QDialog *c2bRLWebSearchSettings)
    {
        c2bRLWebSearchSettings->setWindowTitle(QCoreApplication::translate("c2bRLWebSearchSettings", "Web Search Settings - cb2Bib", nullptr));
        addQuotes->setText(QCoreApplication::translate("c2bRLWebSearchSettings", "&Add quotes to query", nullptr));
        label->setText(QCoreApplication::translate("c2bRLWebSearchSettings", "Search Engine:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class c2bRLWebSearchSettings: public Ui_c2bRLWebSearchSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C2BRLWEBSEARCHSETTINGS_H
