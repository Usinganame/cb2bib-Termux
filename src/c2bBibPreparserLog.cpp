/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bBibPreparserLog.h"

#include "c2b.h"
#include "c2bSettings.h"
#include "c2bUtils.h"

#include <QCheckBox>
#include <QPushButton>


c2bBibPreparserLog::c2bBibPreparserLog(QWidget* parentw) : QDialog(parentw)
{
    ui.setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle(tr("Clipboard Preparsing Log - cb2Bib"));
    PreparserShowLog = new QCheckBox();
    PreparserShowLog->setObjectName(QString::fromUtf8("PreparserShowLog"));
    PreparserShowLog->setLayoutDirection(Qt::RightToLeft);
    PreparserShowLog->setText(QApplication::translate("c2bBibPreparserLog", "Do not show log", 0));
    ui.buttonBox->addButton(PreparserShowLog, QDialogButtonBox::ActionRole);
    connect(ui.buttonBox, SIGNAL(helpRequested()), this, SLOT(help()));
    connect(this, SIGNAL(finished(int)), this, SLOT(close()));
}

c2bBibPreparserLog::~c2bBibPreparserLog() {}


void c2bBibPreparserLog::append(const QString& ms)
{
    ui.Log->appendPlainText(ms);
}

void c2bBibPreparserLog::show()
{
    resize(c2bSettingsP->value("c2bLogWidget/size", size()).toSize());
    ui.buttonBox->button(QDialogButtonBox::Close)->setFocus();
    QDialog::show();
}

void c2bBibPreparserLog::closeEvent(QCloseEvent* qevent)
{
    ui.Log->clear();
    if (PreparserShowLog->isChecked())
        c2bSettingsP->setValue("cb2Bib/PreparserShowLog", false);
    PreparserShowLog->setChecked(false);
    c2bSettingsP->setValue("c2bLogWidget/size", size());
    qevent->accept();
}

void c2bBibPreparserLog::help()
{
    c2bUtils::displayHelp("https://www.molspaces.com/cb2bib/doc/overview/#additional-keyboard-functionality");
}
