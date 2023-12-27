/********************************************************************************
** Form generated from reading UI file 'c2bSaveRegExp.ui'
**
** Created by: Qt User Interface Compiler version 5.15.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C2BSAVEREGEXP_H
#define UI_C2BSAVEREGEXP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include "c2bLineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_c2bSaveRegExp
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *labeln;
    c2bLineEdit *Name;
    QLabel *labelt;
    c2bLineEdit *Type;
    QLabel *labelf;
    c2bLineEdit *Fields;
    QLabel *labelr;
    c2bLineEdit *RegExp;
    QLabel *label1;
    QPlainTextEdit *Input;
    QFrame *line1;
    QLabel *label2;
    QPlainTextEdit *Information;
    QFrame *line2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *c2bSaveRegExp)
    {
        if (c2bSaveRegExp->objectName().isEmpty())
            c2bSaveRegExp->setObjectName(QString::fromUtf8("c2bSaveRegExp"));
        c2bSaveRegExp->resize(845, 584);
        gridLayout_2 = new QGridLayout(c2bSaveRegExp);
        gridLayout_2->setContentsMargins(6, 6, 6, 6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox = new QGroupBox(c2bSaveRegExp);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labeln = new QLabel(groupBox);
        labeln->setObjectName(QString::fromUtf8("labeln"));

        gridLayout->addWidget(labeln, 0, 0, 1, 1);

        Name = new c2bLineEdit(groupBox);
        Name->setObjectName(QString::fromUtf8("Name"));

        gridLayout->addWidget(Name, 0, 1, 1, 1);

        labelt = new QLabel(groupBox);
        labelt->setObjectName(QString::fromUtf8("labelt"));

        gridLayout->addWidget(labelt, 1, 0, 1, 1);

        Type = new c2bLineEdit(groupBox);
        Type->setObjectName(QString::fromUtf8("Type"));

        gridLayout->addWidget(Type, 1, 1, 1, 1);

        labelf = new QLabel(groupBox);
        labelf->setObjectName(QString::fromUtf8("labelf"));

        gridLayout->addWidget(labelf, 2, 0, 1, 1);

        Fields = new c2bLineEdit(groupBox);
        Fields->setObjectName(QString::fromUtf8("Fields"));

        gridLayout->addWidget(Fields, 2, 1, 1, 1);

        labelr = new QLabel(groupBox);
        labelr->setObjectName(QString::fromUtf8("labelr"));

        gridLayout->addWidget(labelr, 3, 0, 1, 1);

        RegExp = new c2bLineEdit(groupBox);
        RegExp->setObjectName(QString::fromUtf8("RegExp"));

        gridLayout->addWidget(RegExp, 3, 1, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);

        label1 = new QLabel(c2bSaveRegExp);
        label1->setObjectName(QString::fromUtf8("label1"));

        gridLayout_2->addWidget(label1, 1, 0, 1, 1);

        Input = new QPlainTextEdit(c2bSaveRegExp);
        Input->setObjectName(QString::fromUtf8("Input"));
        Input->setFrameShadow(QFrame::Raised);

        gridLayout_2->addWidget(Input, 2, 0, 1, 1);

        line1 = new QFrame(c2bSaveRegExp);
        line1->setObjectName(QString::fromUtf8("line1"));
        line1->setFrameShape(QFrame::HLine);
        line1->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line1, 3, 0, 1, 1);

        label2 = new QLabel(c2bSaveRegExp);
        label2->setObjectName(QString::fromUtf8("label2"));

        gridLayout_2->addWidget(label2, 4, 0, 1, 1);

        Information = new QPlainTextEdit(c2bSaveRegExp);
        Information->setObjectName(QString::fromUtf8("Information"));
        Information->setFrameShadow(QFrame::Raised);
        Information->setUndoRedoEnabled(false);
        Information->setReadOnly(true);

        gridLayout_2->addWidget(Information, 5, 0, 1, 1);

        line2 = new QFrame(c2bSaveRegExp);
        line2->setObjectName(QString::fromUtf8("line2"));
        line2->setFrameShape(QFrame::HLine);
        line2->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line2, 6, 0, 1, 1);

        buttonBox = new QDialogButtonBox(c2bSaveRegExp);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Help|QDialogButtonBox::Save);

        gridLayout_2->addWidget(buttonBox, 7, 0, 1, 1);


        retranslateUi(c2bSaveRegExp);
        QObject::connect(buttonBox, SIGNAL(accepted()), c2bSaveRegExp, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), c2bSaveRegExp, SLOT(reject()));

        QMetaObject::connectSlotsByName(c2bSaveRegExp);
    } // setupUi

    void retranslateUi(QDialog *c2bSaveRegExp)
    {
        c2bSaveRegExp->setWindowTitle(QCoreApplication::translate("c2bSaveRegExp", "Edit and Save Pattern - cb2Bib", nullptr));
        groupBox->setTitle(QString());
        labeln->setText(QCoreApplication::translate("c2bSaveRegExp", "Name:", nullptr));
        Name->setText(QCoreApplication::translate("c2bSaveRegExp", "Choose a name to identify your reference recognition pattern", nullptr));
        labelt->setText(QCoreApplication::translate("c2bSaveRegExp", "Type:", nullptr));
        labelf->setText(QCoreApplication::translate("c2bSaveRegExp", "Fields:", nullptr));
        Fields->setText(QString());
        labelr->setText(QCoreApplication::translate("c2bSaveRegExp", "RegExp:", nullptr));
        label1->setText(QCoreApplication::translate("c2bSaveRegExp", "Input Text:", nullptr));
        label2->setText(QCoreApplication::translate("c2bSaveRegExp", "Pattern Information:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class c2bSaveRegExp: public Ui_c2bSaveRegExp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C2BSAVEREGEXP_H
