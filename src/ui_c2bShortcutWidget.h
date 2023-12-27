/********************************************************************************
** Form generated from reading UI file 'c2bShortcutWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C2BSHORTCUTWIDGET_H
#define UI_C2BSHORTCUTWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "c2bShortcutPushButton.h"

QT_BEGIN_NAMESPACE

class Ui_c2bShortcutWidget
{
public:
    QGridLayout *gridLayout;
    QComboBox *Description;
    c2bShortcutPushButton *Shortcut;
    QToolButton *Clear;
    QToolButton *Reset;

    void setupUi(QWidget *c2bShortcutWidget)
    {
        if (c2bShortcutWidget->objectName().isEmpty())
            c2bShortcutWidget->setObjectName(QString::fromUtf8("c2bShortcutWidget"));
        c2bShortcutWidget->resize(551, 29);
        gridLayout = new QGridLayout(c2bShortcutWidget);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(-1);
        gridLayout->setVerticalSpacing(0);
        Description = new QComboBox(c2bShortcutWidget);
        Description->setObjectName(QString::fromUtf8("Description"));

        gridLayout->addWidget(Description, 0, 0, 1, 1);

        Shortcut = new c2bShortcutPushButton(c2bShortcutWidget);
        Shortcut->setObjectName(QString::fromUtf8("Shortcut"));
        Shortcut->setCheckable(true);
        Shortcut->setFlat(false);

        gridLayout->addWidget(Shortcut, 0, 1, 1, 1);

        Clear = new QToolButton(c2bShortcutWidget);
        Clear->setObjectName(QString::fromUtf8("Clear"));
        Clear->setFocusPolicy(Qt::NoFocus);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/clear_left.png"), QSize(), QIcon::Normal, QIcon::Off);
        Clear->setIcon(icon);

        gridLayout->addWidget(Clear, 0, 2, 1, 1);

        Reset = new QToolButton(c2bShortcutWidget);
        Reset->setObjectName(QString::fromUtf8("Reset"));
        Reset->setFocusPolicy(Qt::NoFocus);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/edit-undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        Reset->setIcon(icon1);

        gridLayout->addWidget(Reset, 0, 3, 1, 1);


        retranslateUi(c2bShortcutWidget);

        QMetaObject::connectSlotsByName(c2bShortcutWidget);
    } // setupUi

    void retranslateUi(QWidget *c2bShortcutWidget)
    {
        c2bShortcutWidget->setWindowTitle(QCoreApplication::translate("c2bShortcutWidget", "Form", nullptr));
        Shortcut->setText(QString());
#if QT_CONFIG(statustip)
        Clear->setStatusTip(QCoreApplication::translate("c2bShortcutWidget", "Clear key sequence", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(statustip)
        Reset->setStatusTip(QCoreApplication::translate("c2bShortcutWidget", "Reset key sequence to default value", nullptr));
#endif // QT_CONFIG(statustip)
    } // retranslateUi

};

namespace Ui {
    class c2bShortcutWidget: public Ui_c2bShortcutWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C2BSHORTCUTWIDGET_H
