/********************************************************************************
** Form generated from reading UI file 'c2bLogWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C2BLOGWIDGET_H
#define UI_C2BLOGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPlainTextEdit>

QT_BEGIN_NAMESPACE

class Ui_c2bLogWidget
{
public:
    QGridLayout *gridLayout;
    QPlainTextEdit *Log;
    QFrame *line;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *c2bLogWidget)
    {
        if (c2bLogWidget->objectName().isEmpty())
            c2bLogWidget->setObjectName(QString::fromUtf8("c2bLogWidget"));
        c2bLogWidget->resize(827, 347);
        gridLayout = new QGridLayout(c2bLogWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(6, 6, 6, 6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        Log = new QPlainTextEdit(c2bLogWidget);
        Log->setObjectName(QString::fromUtf8("Log"));
        Log->setFrameShape(QFrame::StyledPanel);
        Log->setFrameShadow(QFrame::Raised);
        Log->setReadOnly(true);

        gridLayout->addWidget(Log, 0, 0, 1, 1);

        line = new QFrame(c2bLogWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line->setFrameShape(QFrame::HLine);

        gridLayout->addWidget(line, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(c2bLogWidget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close|QDialogButtonBox::Help);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 1);


        retranslateUi(c2bLogWidget);
        QObject::connect(buttonBox, SIGNAL(rejected()), c2bLogWidget, SLOT(reject()));

        QMetaObject::connectSlotsByName(c2bLogWidget);
    } // setupUi

    void retranslateUi(QDialog *c2bLogWidget)
    {
        c2bLogWidget->setWindowTitle(QCoreApplication::translate("c2bLogWidget", "Process Log - cb2Bib", nullptr));
    } // retranslateUi

};

namespace Ui {
    class c2bLogWidget: public Ui_c2bLogWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C2BLOGWIDGET_H
