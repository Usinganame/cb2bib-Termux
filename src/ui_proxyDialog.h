/********************************************************************************
** Form generated from reading UI file 'proxyDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROXYDIALOG_H
#define UI_PROXYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_proxyDialog
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *usernameLabel;
    QLineEdit *userNameLineEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QSpacerItem *verticalSpacer;
    QFrame *line;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *proxyDialog)
    {
        if (proxyDialog->objectName().isEmpty())
            proxyDialog->setObjectName(QString::fromUtf8("proxyDialog"));
        proxyDialog->resize(454, 127);
        gridLayout_2 = new QGridLayout(proxyDialog);
        gridLayout_2->setContentsMargins(6, 6, 6, 6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        usernameLabel = new QLabel(proxyDialog);
        usernameLabel->setObjectName(QString::fromUtf8("usernameLabel"));

        gridLayout->addWidget(usernameLabel, 0, 0, 1, 1);

        userNameLineEdit = new QLineEdit(proxyDialog);
        userNameLineEdit->setObjectName(QString::fromUtf8("userNameLineEdit"));

        gridLayout->addWidget(userNameLineEdit, 0, 1, 1, 1);

        passwordLabel = new QLabel(proxyDialog);
        passwordLabel->setObjectName(QString::fromUtf8("passwordLabel"));

        gridLayout->addWidget(passwordLabel, 1, 0, 1, 1);

        passwordLineEdit = new QLineEdit(proxyDialog);
        passwordLineEdit->setObjectName(QString::fromUtf8("passwordLineEdit"));
        passwordLineEdit->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(passwordLineEdit, 1, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 2);

        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 1, 1, 1, 1);

        line = new QFrame(proxyDialog);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line, 2, 0, 1, 2);

        buttonBox = new QDialogButtonBox(proxyDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 3, 1, 1, 1);


        retranslateUi(proxyDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), proxyDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), proxyDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(proxyDialog);
    } // setupUi

    void retranslateUi(QDialog *proxyDialog)
    {
        proxyDialog->setWindowTitle(QCoreApplication::translate("proxyDialog", "Proxy Authentication - cb2Bib", nullptr));
        usernameLabel->setText(QCoreApplication::translate("proxyDialog", "Username:", nullptr));
        passwordLabel->setText(QCoreApplication::translate("proxyDialog", "Password:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class proxyDialog: public Ui_proxyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROXYDIALOG_H
