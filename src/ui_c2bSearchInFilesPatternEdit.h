/********************************************************************************
** Form generated from reading UI file 'c2bSearchInFilesPatternEdit.ui'
**
** Created by: Qt User Interface Compiler version 5.15.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C2BSEARCHINFILESPATTERNEDIT_H
#define UI_C2BSEARCHINFILESPATTERNEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include "c2bSearchInFilesPattern.h"

QT_BEGIN_NAMESPACE

class Ui_c2bSearchInFilesPatternEdit
{
public:
    QGridLayout *gridLayout;
    c2bSearchInFilesPattern *pattern;
    QFrame *line;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *c2bSearchInFilesPatternEdit)
    {
        if (c2bSearchInFilesPatternEdit->objectName().isEmpty())
            c2bSearchInFilesPatternEdit->setObjectName(QString::fromUtf8("c2bSearchInFilesPatternEdit"));
        c2bSearchInFilesPatternEdit->resize(594, 85);
        gridLayout = new QGridLayout(c2bSearchInFilesPatternEdit);
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(6, 6, 6, 6);
        pattern = new c2bSearchInFilesPattern(c2bSearchInFilesPatternEdit);
        pattern->setObjectName(QString::fromUtf8("pattern"));

        gridLayout->addWidget(pattern, 0, 0, 1, 1);

        line = new QFrame(c2bSearchInFilesPatternEdit);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(c2bSearchInFilesPatternEdit);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 1);


        retranslateUi(c2bSearchInFilesPatternEdit);
        QObject::connect(buttonBox, SIGNAL(accepted()), c2bSearchInFilesPatternEdit, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), c2bSearchInFilesPatternEdit, SLOT(reject()));

        QMetaObject::connectSlotsByName(c2bSearchInFilesPatternEdit);
    } // setupUi

    void retranslateUi(QDialog *c2bSearchInFilesPatternEdit)
    {
        c2bSearchInFilesPatternEdit->setWindowTitle(QCoreApplication::translate("c2bSearchInFilesPatternEdit", "Edit Pattern - cb2Bib", nullptr));
    } // retranslateUi

};

namespace Ui {
    class c2bSearchInFilesPatternEdit: public Ui_c2bSearchInFilesPatternEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C2BSEARCHINFILESPATTERNEDIT_H
