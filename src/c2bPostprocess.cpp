/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bPostprocess.h"

#include "c2b.h"
#include "c2bSettings.h"
#include "c2bUtils.h"

#include <QDir>
#include <QMessageBox>
#include <QProcess>
#include <QPushButton>


c2bPostprocess::c2bPostprocess(const QString& fn, QWidget* parentw) : QDialog(parentw)
{
    ui.setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle(tr("BibTeX Postprocessing Log - cb2Bib"));
    setAttribute(Qt::WA_DeleteOnClose);
    _buttonOpenFile = new QPushButton(tr("&Open File"));
    ui.buttonBox->addButton(_buttonOpenFile, QDialogButtonBox::ActionRole);
    _buttonOpenFile->setAutoDefault(true);
    _buttonOpenFile->setDefault(true);
    _buttonOpenFile->setEnabled(false);
    ui.buttonBox->button(QDialogButtonBox::Close)->setEnabled(false);
    connect(ui.buttonBox, SIGNAL(helpRequested()), this, SLOT(help()));
    connect(_buttonOpenFile, SIGNAL(clicked()), this, SLOT(openFile()));
    c2bSettings* settings(c2bSettingsP);
    resize(settings->value("c2bLogWidget/size", size()).toSize());
    PPBIBTEX_BIN = settings->fileName("cb2Bib/PostprocessBibTeXBin");
    PPBIBTEX_ARG = settings->value("cb2Bib/PostprocessBibTeXArg").toString();
    PPBIBTEX_EXT = settings->value("cb2Bib/PostprocessBibTeXExt").toString();

    QFile f(fn);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(parentw, tr("Warning - cb2Bib"),
                             tr("Unable to open the file %1 for reading.\nError: '%2'.").arg(fn, f.errorString()),
                             QMessageBox::Ok);
        ui.buttonBox->button(QDialogButtonBox::Close)->setEnabled(true);
        ui.buttonBox->button(QDialogButtonBox::Close)->setFocus();
        ui.Log->appendPlainText(tr("BibTeX Post Processing: Erroneous termination.\n"));
    }
    else
    {
        f.close();
        _bib = fn;
        QFileInfo fi(fn);
        _out = QDir::toNativeSeparators(fi.absolutePath() + '/' + fi.baseName() + '.' + PPBIBTEX_EXT);
        QString cargs(PPBIBTEX_ARG);
        cargs.replace("%finput", _bib);
        cargs.replace("%foutput", _out);
        ui.Log->appendPlainText(tr("BibTeX Post Processing Command:\n%1 %2\n").arg(PPBIBTEX_BIN, cargs));
        PProcessFile();
    }
}

c2bPostprocess::~c2bPostprocess()
{
    c2bSettingsP->setValue("c2bLogWidget/size", size());
}


void c2bPostprocess::PProcessFile()
{
    // Postprocessing BibTeX
    const QStringList arglist(PPBIBTEX_ARG.split(' ', QString::SkipEmptyParts));
    QStringList args;
    for (int i = 0; i < arglist.count(); i++)
    {
        if (arglist.at(i) == "%finput")
            args.append(_bib);
        else if (arglist.at(i) == "%foutput")
            args.append(_out);
        else
            args.append(arglist.at(i));
    }
    _ppBibTeX = new QProcess(this);
    connect(_ppBibTeX, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(conversionEnded()));
    _ppBibTeX->start(PPBIBTEX_BIN, args);
    if (!_ppBibTeX->waitForStarted())
    {
        ui.Log->appendPlainText(tr("Failed to call %1.").arg(PPBIBTEX_BIN));
        ui.buttonBox->button(QDialogButtonBox::Close)->setEnabled(true);
        ui.buttonBox->button(QDialogButtonBox::Close)->setFocus();
        delete _ppBibTeX;
    }
}

void c2bPostprocess::conversionEnded()
{
    addToLog();
    ui.buttonBox->button(QDialogButtonBox::Close)->setEnabled(true);
    if (QFileInfo(_out).isReadable())
    {
        _buttonOpenFile->setEnabled(true);
        _buttonOpenFile->setFocus();
    }
    else
    {
        ui.buttonBox->button(QDialogButtonBox::Close)->setAutoDefault(true);
        ui.buttonBox->button(QDialogButtonBox::Close)->setDefault(true);
        ui.buttonBox->button(QDialogButtonBox::Close)->setFocus();
    }
    ui.Log->appendPlainText(tr("\n\nBibTeX Post Processing Command Ended."));
    delete _ppBibTeX;
}

void c2bPostprocess::addToLog()
{
    QString log(QString::fromUtf8(_ppBibTeX->readAllStandardOutput().trimmed()));
    if (!log.isEmpty())
        ui.Log->appendPlainText(log);
    log = QString::fromUtf8(_ppBibTeX->readAllStandardError().trimmed());
    if (!log.isEmpty())
        ui.Log->appendPlainText(log);
}

void c2bPostprocess::openFile()
{
    c2bUtils::openFile(_out, this);
    close();
}

void c2bPostprocess::help()
{
    c2bUtils::displayHelp("https://www.molspaces.com/cb2bib/doc/overview/#additional-keyboard-functionality");
}
