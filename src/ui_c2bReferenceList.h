/********************************************************************************
** Form generated from reading UI file 'c2bReferenceList.ui'
**
** Created by: Qt User Interface Compiler version 5.15.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C2BREFERENCELIST_H
#define UI_C2BREFERENCELIST_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>
#include "c2bComboBox.h"

QT_BEGIN_NAMESPACE

class Ui_c2bReferenceList
{
public:
    QGridLayout *gridLayout;
    QToolButton *clearB;
    QToolButton *filterB;
    QFrame *line;
    QTreeWidget *listView;
    c2bComboBox *comboFilter;

    void setupUi(QWidget *c2bReferenceList)
    {
        if (c2bReferenceList->objectName().isEmpty())
            c2bReferenceList->setObjectName(QString::fromUtf8("c2bReferenceList"));
        c2bReferenceList->resize(738, 153);
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(c2bReferenceList->sizePolicy().hasHeightForWidth());
        c2bReferenceList->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(c2bReferenceList);
        gridLayout->setSpacing(2);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        clearB = new QToolButton(c2bReferenceList);
        clearB->setObjectName(QString::fromUtf8("clearB"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/clear_left.png"), QSize(), QIcon::Normal, QIcon::Off);
        clearB->setIcon(icon);

        gridLayout->addWidget(clearB, 2, 2, 1, 1);

        filterB = new QToolButton(c2bReferenceList);
        filterB->setObjectName(QString::fromUtf8("filterB"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/filter.png"), QSize(), QIcon::Normal, QIcon::Off);
        filterB->setIcon(icon1);
        filterB->setPopupMode(QToolButton::InstantPopup);

        gridLayout->addWidget(filterB, 2, 0, 1, 1);

        line = new QFrame(c2bReferenceList);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line->setFrameShape(QFrame::HLine);

        gridLayout->addWidget(line, 1, 0, 1, 3);

        listView = new QTreeWidget(c2bReferenceList);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setMouseTracking(true);
        listView->setFrameShadow(QFrame::Raised);
        listView->setTabKeyNavigation(true);
        listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
        listView->setRootIsDecorated(false);
        listView->setSortingEnabled(true);
        listView->setColumnCount(6);

        gridLayout->addWidget(listView, 0, 0, 1, 3);

        comboFilter = new c2bComboBox(c2bReferenceList);
        comboFilter->setObjectName(QString::fromUtf8("comboFilter"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboFilter->sizePolicy().hasHeightForWidth());
        comboFilter->setSizePolicy(sizePolicy1);
        comboFilter->setEditable(true);
        comboFilter->setDuplicatesEnabled(false);

        gridLayout->addWidget(comboFilter, 2, 1, 1, 1);


        retranslateUi(c2bReferenceList);
        QObject::connect(clearB, SIGNAL(clicked()), comboFilter, SLOT(clearEditText()));

        QMetaObject::connectSlotsByName(c2bReferenceList);
    } // setupUi

    void retranslateUi(QWidget *c2bReferenceList)
    {
        c2bReferenceList->setWindowTitle(QCoreApplication::translate("c2bReferenceList", "References", nullptr));
#if QT_CONFIG(tooltip)
        clearB->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        clearB->setStatusTip(QCoreApplication::translate("c2bReferenceList", "Clear filter", nullptr));
#endif // QT_CONFIG(statustip)
        clearB->setText(QString());
#if QT_CONFIG(statustip)
        filterB->setStatusTip(QCoreApplication::translate("c2bReferenceList", "Filter Author and Title", nullptr));
#endif // QT_CONFIG(statustip)
        filterB->setText(QCoreApplication::translate("c2bReferenceList", "...", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = listView->headerItem();
        ___qtreewidgetitem->setText(5, QCoreApplication::translate("c2bReferenceList", "5", nullptr));
        ___qtreewidgetitem->setText(4, QCoreApplication::translate("c2bReferenceList", "4", nullptr));
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("c2bReferenceList", "3", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("c2bReferenceList", "2", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("c2bReferenceList", "1", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("c2bReferenceList", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class c2bReferenceList: public Ui_c2bReferenceList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C2BREFERENCELIST_H
