/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bCollectionIndex.h"

#include "c2bSettings.h"
#include "c2bUtils.h"

#include <QPushButton>


c2bCollectionIndex::c2bCollectionIndex(QWidget* parentw) : QDialog(parentw), _indexerP(0)
{
    ui.setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle(tr("Documents Indexing Log - cb2Bib"));
    ui.Log->setFont(c2bSettingsP->c2bMonoFont);
    ui.Log->setLineWrapMode(QPlainTextEdit::NoWrap);
    _buttonAbort = new QPushButton(tr("Abort"));
    ui.buttonBox->addButton(_buttonAbort, QDialogButtonBox::ActionRole);
    connect(_buttonAbort, SIGNAL(clicked()), this, SLOT(aborted()));
    connect(ui.buttonBox, SIGNAL(helpRequested()), this, SLOT(help()));
    resize(c2bSettingsP->value("c2bLogWidget/size", size()).toSize());
}

c2bCollectionIndex::~c2bCollectionIndex()
{
    c2bSettingsP->setValue("c2bLogWidget/size", size());
}


void c2bCollectionIndex::index()
{
    ui.Log->clear();
    ui.buttonBox->button(QDialogButtonBox::Close)->setEnabled(false);
    _indexerP = new QProcess(this);
    _indexerP->setProcessChannelMode(QProcess::MergedChannels);
    connect(_indexerP, SIGNAL(finished(int,QProcess::ExitStatus)), this,
            SLOT(indexingEnded(int,QProcess::ExitStatus)));
    connect(_indexerP, SIGNAL(readyReadStandardOutput()), this, SLOT(addToLog()));
    const QStringList flags(QStringList() << "--index" << c2bSettingsP->confCommandFlags());
    _indexerP->start(QCoreApplication::applicationFilePath(), flags);
    if (!_indexerP->waitForStarted())
    {
        ui.Log->appendPlainText(tr("Failed to call %1.").arg(QCoreApplication::applicationFilePath()));
        _buttonAbort->setEnabled(false);
        ui.buttonBox->button(QDialogButtonBox::Close)->setEnabled(true);
        ui.buttonBox->button(QDialogButtonBox::Close)->setFocus();
        delete _indexerP;
        _indexerP = 0;
    }
}

void c2bCollectionIndex::addToLog()
{
    const QString log(QString::fromUtf8(_indexerP->readAllStandardOutput().trimmed()));
    if (log.isEmpty())
        return;
    ui.Log->appendPlainText(log);
}

void c2bCollectionIndex::indexingEnded(int exit_code, QProcess::ExitStatus exit_status)
{
    _buttonAbort->setEnabled(false);
    ui.buttonBox->button(QDialogButtonBox::Close)->setEnabled(true);
    ui.buttonBox->button(QDialogButtonBox::Close)->setFocus();
    if (exit_code == 0 && exit_status == QProcess::NormalExit)
        ui.Log->appendPlainText(tr("\nIndexing ended\nRefresh cb2Bib Citer"));
    else
        ui.Log->appendPlainText(tr("\nAbnormal termination"));
    delete _indexerP;
    _indexerP = 0;
}

void c2bCollectionIndex::aborted()
{
    if (_indexerP)
        _indexerP->kill();
    ui.Log->appendPlainText(tr("Aborting..."));
}

void c2bCollectionIndex::closeEvent(QCloseEvent* qevent)
{
    if (!_indexerP || _indexerP->state() == QProcess::NotRunning)
        QDialog::closeEvent(qevent);
    else
        qevent->ignore();
}

void c2bCollectionIndex::reject()
{
    if (!_indexerP || _indexerP->state() == QProcess::NotRunning)
        QDialog::reject();
}

void c2bCollectionIndex::help()
{
    c2bUtils::displayHelp("https://www.molspaces.com/cb2bib/doc/c2bciter/");
}
