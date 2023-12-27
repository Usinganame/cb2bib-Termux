/********************************************************************************
** Form generated from reading UI file 'c2bCiterWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C2BCITERWIDGET_H
#define UI_C2BCITERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "c2bCiterView.h"

QT_BEGIN_NAMESPACE

class Ui_c2bCiterWidget
{
public:
    QGridLayout *gridLayout;
    QFrame *line1;
    c2bCiterView *citationsView;
    QFrame *line2;
    QHBoxLayout *horizontalLayout;
    QStatusBar *statusBar;
    QLabel *filterIcon;
    QLabel *clipboardIcon;
    QFrame *line3;

    void setupUi(QWidget *c2bCiterWidget)
    {
        if (c2bCiterWidget->objectName().isEmpty())
            c2bCiterWidget->setObjectName(QString::fromUtf8("c2bCiterWidget"));
        c2bCiterWidget->resize(901, 400);
        gridLayout = new QGridLayout(c2bCiterWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(3, 6, 3, 6);
        line1 = new QFrame(c2bCiterWidget);
        line1->setObjectName(QString::fromUtf8("line1"));
        line1->setFrameShape(QFrame::HLine);
        line1->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line1, 0, 0, 1, 1);

        citationsView = new c2bCiterView(c2bCiterWidget);
        citationsView->setObjectName(QString::fromUtf8("citationsView"));
        citationsView->setFrameShape(QFrame::NoFrame);
        citationsView->setFrameShadow(QFrame::Plain);
        citationsView->setProperty("showDropIndicator", QVariant(false));
        citationsView->setSelectionMode(QAbstractItemView::SingleSelection);
        citationsView->setSelectionBehavior(QAbstractItemView::SelectRows);
        citationsView->setShowGrid(false);
        citationsView->setGridStyle(Qt::NoPen);
        citationsView->setWordWrap(false);
        citationsView->setCornerButtonEnabled(false);

        gridLayout->addWidget(citationsView, 1, 0, 1, 1);

        line2 = new QFrame(c2bCiterWidget);
        line2->setObjectName(QString::fromUtf8("line2"));
        line2->setFrameShape(QFrame::HLine);
        line2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line2, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, 7, -1);
        statusBar = new QStatusBar(c2bCiterWidget);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(statusBar->sizePolicy().hasHeightForWidth());
        statusBar->setSizePolicy(sizePolicy);
        statusBar->setSizeGripEnabled(false);

        horizontalLayout->addWidget(statusBar);

        filterIcon = new QLabel(c2bCiterWidget);
        filterIcon->setObjectName(QString::fromUtf8("filterIcon"));
        filterIcon->setPixmap(QPixmap(QString::fromUtf8(":/icons/icons/filter.png")));

        horizontalLayout->addWidget(filterIcon);

        clipboardIcon = new QLabel(c2bCiterWidget);
        clipboardIcon->setObjectName(QString::fromUtf8("clipboardIcon"));
        clipboardIcon->setPixmap(QPixmap(QString::fromUtf8(":/icons/icons/clipboard.png")));

        horizontalLayout->addWidget(clipboardIcon);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 1);

        line3 = new QFrame(c2bCiterWidget);
        line3->setObjectName(QString::fromUtf8("line3"));
        line3->setFrameShape(QFrame::HLine);
        line3->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line3, 4, 0, 1, 1);


        retranslateUi(c2bCiterWidget);

        QMetaObject::connectSlotsByName(c2bCiterWidget);
    } // setupUi

    void retranslateUi(QWidget *c2bCiterWidget)
    {
        c2bCiterWidget->setWindowTitle(QCoreApplication::translate("c2bCiterWidget", "c2bCiter - cb2Bib", nullptr));
        filterIcon->setText(QString());
        clipboardIcon->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class c2bCiterWidget: public Ui_c2bCiterWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C2BCITERWIDGET_H
