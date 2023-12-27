/********************************************************************************
** Form generated from reading UI file 'findDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDDIALOG_H
#define UI_FINDDIALOG_H

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
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include "c2bComboBox.h"

QT_BEGIN_NAMESPACE

class Ui_findDialog
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout1;
    QCheckBox *checkCase;
    QSpacerItem *spacerItem;
    QCheckBox *checkWords;
    QHBoxLayout *hboxLayout;
    QLabel *TextLabel1;
    c2bComboBox *comboFind;
    QToolButton *clearB;
    QLabel *notFound;
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout2;
    QSpacerItem *spacerItem1;
    QRadioButton *radioBackward;
    QRadioButton *radioForward;
    QFrame *line5;

    void setupUi(QDialog *findDialog)
    {
        if (findDialog->objectName().isEmpty())
            findDialog->setObjectName(QString::fromUtf8("findDialog"));
        findDialog->resize(459, 196);
        gridLayout = new QGridLayout(findDialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(6, 6, 6, 6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(findDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        gridLayout1 = new QGridLayout(groupBox);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(9, 9, 9, 9);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        checkCase = new QCheckBox(groupBox);
        checkCase->setObjectName(QString::fromUtf8("checkCase"));

        gridLayout1->addWidget(checkCase, 1, 0, 1, 1);

        spacerItem = new QSpacerItem(180, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout1->addItem(spacerItem, 2, 0, 1, 1);

        checkWords = new QCheckBox(groupBox);
        checkWords->setObjectName(QString::fromUtf8("checkWords"));

        gridLayout1->addWidget(checkWords, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox, 1, 0, 1, 1);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        TextLabel1 = new QLabel(findDialog);
        TextLabel1->setObjectName(QString::fromUtf8("TextLabel1"));

        hboxLayout->addWidget(TextLabel1);

        comboFind = new c2bComboBox(findDialog);
        comboFind->setObjectName(QString::fromUtf8("comboFind"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboFind->sizePolicy().hasHeightForWidth());
        comboFind->setSizePolicy(sizePolicy1);
        comboFind->setEditable(true);
        comboFind->setDuplicatesEnabled(false);

        hboxLayout->addWidget(comboFind);

        clearB = new QToolButton(findDialog);
        clearB->setObjectName(QString::fromUtf8("clearB"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/clear_left.png"), QSize(), QIcon::Normal, QIcon::Off);
        clearB->setIcon(icon);

        hboxLayout->addWidget(clearB);


        gridLayout->addLayout(hboxLayout, 0, 0, 1, 2);

        notFound = new QLabel(findDialog);
        notFound->setObjectName(QString::fromUtf8("notFound"));

        gridLayout->addWidget(notFound, 3, 0, 1, 1);

        buttonBox = new QDialogButtonBox(findDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 3, 1, 1, 1);

        groupBox_2 = new QGroupBox(findDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        gridLayout2 = new QGridLayout(groupBox_2);
        gridLayout2->setSpacing(6);
        gridLayout2->setContentsMargins(9, 9, 9, 9);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        spacerItem1 = new QSpacerItem(147, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout2->addItem(spacerItem1, 2, 0, 1, 1);

        radioBackward = new QRadioButton(groupBox_2);
        radioBackward->setObjectName(QString::fromUtf8("radioBackward"));

        gridLayout2->addWidget(radioBackward, 1, 0, 1, 1);

        radioForward = new QRadioButton(groupBox_2);
        radioForward->setObjectName(QString::fromUtf8("radioForward"));
        radioForward->setChecked(true);

        gridLayout2->addWidget(radioForward, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_2, 1, 1, 1, 1);

        line5 = new QFrame(findDialog);
        line5->setObjectName(QString::fromUtf8("line5"));
        line5->setFrameShape(QFrame::HLine);
        line5->setFrameShadow(QFrame::Sunken);
        line5->setFrameShape(QFrame::HLine);

        gridLayout->addWidget(line5, 2, 0, 1, 2);

#if QT_CONFIG(shortcut)
        TextLabel1->setBuddy(comboFind);
#endif // QT_CONFIG(shortcut)
        QWidget::setTabOrder(comboFind, clearB);
        QWidget::setTabOrder(clearB, checkWords);
        QWidget::setTabOrder(checkWords, checkCase);
        QWidget::setTabOrder(checkCase, radioForward);
        QWidget::setTabOrder(radioForward, radioBackward);

        retranslateUi(findDialog);
        QObject::connect(clearB, SIGNAL(clicked()), comboFind, SLOT(clearEditText()));
        QObject::connect(buttonBox, SIGNAL(rejected()), findDialog, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), findDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(findDialog);
    } // setupUi

    void retranslateUi(QDialog *findDialog)
    {
        findDialog->setWindowTitle(QCoreApplication::translate("findDialog", "Find in text - cb2Bib", nullptr));
        groupBox->setTitle(QCoreApplication::translate("findDialog", "Options", nullptr));
        checkCase->setText(QCoreApplication::translate("findDialog", "&Case sensitive", nullptr));
        checkWords->setText(QCoreApplication::translate("findDialog", "&Whole words only", nullptr));
        TextLabel1->setText(QCoreApplication::translate("findDialog", "Find:", nullptr));
#if QT_CONFIG(tooltip)
        clearB->setToolTip(QCoreApplication::translate("findDialog", "Clear Text", nullptr));
#endif // QT_CONFIG(tooltip)
        clearB->setText(QString());
        notFound->setText(QCoreApplication::translate("findDialog", "Pattern not found", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("findDialog", "Direction", nullptr));
        radioBackward->setText(QCoreApplication::translate("findDialog", "&Backward", nullptr));
        radioForward->setText(QCoreApplication::translate("findDialog", "&Forward", nullptr));
    } // retranslateUi

};

namespace Ui {
    class findDialog: public Ui_findDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDDIALOG_H
