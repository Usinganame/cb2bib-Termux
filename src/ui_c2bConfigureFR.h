/********************************************************************************
** Form generated from reading UI file 'c2bConfigureFR.ui'
**
** Created by: Qt User Interface Compiler version 5.15.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C2BCONFIGUREFR_H
#define UI_C2BCONFIGUREFR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include "c2bLineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_c2bConfigureFR
{
public:
    QGridLayout *gridLayout;
    QDialogButtonBox *buttonBox;
    QSpacerItem *spacerItem;
    QFrame *line2;
    QGridLayout *gridLayout1;
    QLabel *textLabel3;
    QLabel *textLabel1;
    QLabel *textLabel2;
    c2bLineEdit *lineEditFind;
    c2bLineEdit *lineEditReplace;
    c2bLineEdit *lineEditDescription;

    void setupUi(QDialog *c2bConfigureFR)
    {
        if (c2bConfigureFR->objectName().isEmpty())
            c2bConfigureFR->setObjectName(QString::fromUtf8("c2bConfigureFR"));
        c2bConfigureFR->resize(666, 151);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(c2bConfigureFR->sizePolicy().hasHeightForWidth());
        c2bConfigureFR->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(c2bConfigureFR);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(6, 6, 6, 6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        buttonBox = new QDialogButtonBox(c2bConfigureFR);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setLayoutDirection(Qt::LeftToRight);
        buttonBox->setAutoFillBackground(true);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);

        gridLayout->addWidget(buttonBox, 2, 1, 1, 1);

        spacerItem = new QSpacerItem(271, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem, 2, 0, 1, 1);

        line2 = new QFrame(c2bConfigureFR);
        line2->setObjectName(QString::fromUtf8("line2"));
        line2->setFrameShape(QFrame::HLine);
        line2->setFrameShadow(QFrame::Sunken);
        line2->setFrameShape(QFrame::HLine);

        gridLayout->addWidget(line2, 1, 0, 1, 2);

        gridLayout1 = new QGridLayout();
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(0, 0, 0, 0);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        textLabel3 = new QLabel(c2bConfigureFR);
        textLabel3->setObjectName(QString::fromUtf8("textLabel3"));

        gridLayout1->addWidget(textLabel3, 2, 0, 1, 1);

        textLabel1 = new QLabel(c2bConfigureFR);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));

        gridLayout1->addWidget(textLabel1, 0, 0, 1, 1);

        textLabel2 = new QLabel(c2bConfigureFR);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));

        gridLayout1->addWidget(textLabel2, 1, 0, 1, 1);

        lineEditFind = new c2bLineEdit(c2bConfigureFR);
        lineEditFind->setObjectName(QString::fromUtf8("lineEditFind"));

        gridLayout1->addWidget(lineEditFind, 0, 1, 1, 1);

        lineEditReplace = new c2bLineEdit(c2bConfigureFR);
        lineEditReplace->setObjectName(QString::fromUtf8("lineEditReplace"));

        gridLayout1->addWidget(lineEditReplace, 1, 1, 1, 1);

        lineEditDescription = new c2bLineEdit(c2bConfigureFR);
        lineEditDescription->setObjectName(QString::fromUtf8("lineEditDescription"));

        gridLayout1->addWidget(lineEditDescription, 2, 1, 1, 1);


        gridLayout->addLayout(gridLayout1, 0, 0, 1, 2);

        QWidget::setTabOrder(lineEditFind, lineEditReplace);
        QWidget::setTabOrder(lineEditReplace, lineEditDescription);

        retranslateUi(c2bConfigureFR);
        QObject::connect(buttonBox, SIGNAL(rejected()), c2bConfigureFR, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), c2bConfigureFR, SLOT(accept()));

        QMetaObject::connectSlotsByName(c2bConfigureFR);
    } // setupUi

    void retranslateUi(QDialog *c2bConfigureFR)
    {
        c2bConfigureFR->setWindowTitle(QCoreApplication::translate("c2bConfigureFR", "Edit Find-Replace - cb2Bib", nullptr));
        textLabel3->setText(QCoreApplication::translate("c2bConfigureFR", "Description:", nullptr));
        textLabel1->setText(QCoreApplication::translate("c2bConfigureFR", "Find:", nullptr));
        textLabel2->setText(QCoreApplication::translate("c2bConfigureFR", "Replace:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class c2bConfigureFR: public Ui_c2bConfigureFR {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C2BCONFIGUREFR_H
