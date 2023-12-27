/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bExportDialog.h"

#include "c2b.h"
#include "c2bFileDialog.h"
#include "c2bSettings.h"
#include "c2bUtils.h"

#include <QMessageBox>
#include <QPushButton>


c2bExportDialog::c2bExportDialog(const QString& fn, const QString& contents, const QStringList& keys, QWidget* parentw)
    : QDialog(parentw)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    _ed.bibtex_fn = fn;
    if (contents.isEmpty())
        _ed.bibtex_contents = c2bUtils::fileToString(fn);
    else
        _ed.bibtex_contents = contents;
    _ed.bibtex_keys = keys;
    ui.setupUi(this);
    setWindowTitle(tr("Export Entries - cb2Bib"));
    QPushButton* buttonExport = new QPushButton(tr("Export"));
    ui.buttonBox->addButton(buttonExport, QDialogButtonBox::ActionRole);
    buttonExport->setAutoDefault(true);
    buttonExport->setDefault(true);
    connect(buttonExport, SIGNAL(clicked()), this, SLOT(_export()));

    settings = c2bSettingsP;
    ui.ExportFile->setText(settings->value("c2bExportDialog/ExportFile", QString()).toString());
    ui.DocumentsDirectory->setText(settings->value("c2bExportDialog/DocumentsDirectory", QString()).toString());
    ui.CopyDocuments->setChecked(settings->value("c2bExportDialog/CopyDocuments").toBool());
    ui.RelativeDocumentDirectory->setChecked(settings->value("c2bExportDialog/RelativeDocumentDirectory").toBool());
    ui.DocumentsDirectoryBox->setEnabled(ui.CopyDocuments->isChecked());

    connect(ui.ExportFileDir, SIGNAL(clicked()), this, SLOT(getExportFile()));
    connect(ui.DocumentsDirectoryDir, SIGNAL(clicked()), this, SLOT(getDocumentsDirectory()));
    connect(ui.buttonBox, SIGNAL(helpRequested()), this, SLOT(help()));
}

c2bExportDialog::~c2bExportDialog()
{
    if (result() == QDialog::Accepted)
    {
        settings->setValue("c2bExportDialog/CopyDocuments", ui.CopyDocuments->isChecked());
        settings->setValue("c2bExportDialog/DocumentsDirectory", ui.DocumentsDirectory->text());
        settings->setValue("c2bExportDialog/ExportFile", ui.ExportFile->text());
        settings->setValue("c2bExportDialog/RelativeDocumentDirectory", ui.RelativeDocumentDirectory->isChecked());
    }
}


void c2bExportDialog::_export()
{
    _ed.copy_documents = ui.CopyDocuments->isChecked();
    _ed.documents_dir = ui.DocumentsDirectory->text();
    _ed.export_fn = ui.ExportFile->text();
    _ed.relative_dir = ui.RelativeDocumentDirectory->isChecked();

    // Check files
    if (QFileInfo::exists(_ed.export_fn))
    {
        const int button(QMessageBox::warning(
                             this, tr("Warning - cb2Bib"), tr("File %1 already exists.\nDo you want to replace it?").arg(_ed.export_fn),
                             QMessageBox::Yes | QMessageBox::No));
        if (button == QMessageBox::No)
            return;
    }
    if (_ed.copy_documents)
    {
        const QString ddname(
            c2bUtils::documentAbsoluteName(_ed.relative_dir, _ed.export_fn, _ed.documents_dir, QString()) +
            QDir::separator());
        QDir doc_dir(ddname);
        if (!doc_dir.exists())
            if (!doc_dir.mkpath(ddname))
            {
                QMessageBox::warning(this, tr("Warning - cb2Bib"), tr("Unable to create directory %1.").arg(ddname),
                                     QMessageBox::Ok);
                return;
            }
    }
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    c2bExport e(this);
    e.exportEntries(_ed);
    QApplication::restoreOverrideCursor();
    accept();
}

void c2bExportDialog::getExportFile()
{
    const QString fn(ui.ExportFile->text());
    const QString new_fn(c2bFileDialog::getFilename(this, tr("Select export filename"), fn, "BibTeX (*.bib)"));
    if (!new_fn.isEmpty())
        ui.ExportFile->setText(new_fn);
}

void c2bExportDialog::getDocumentsDirectory()
{
    const QString dir(c2bUtils::documentAbsoluteName(ui.RelativeDocumentDirectory->isChecked(), ui.ExportFile->text(),
                      ui.DocumentsDirectory->text(), QString()));
    QString new_dir(c2bFileDialog::getExistingDirectory(this, tr("Select documents directory"), dir));
    if (!new_dir.isEmpty())
    {
        new_dir = c2bUtils::documentDirName(ui.RelativeDocumentDirectory->isChecked(), ui.ExportFile->text(), new_dir);
        ui.DocumentsDirectory->setText(new_dir);
    }
}

void c2bExportDialog::help()
{
    c2bUtils::displayHelp("https://www.molspaces.com/cb2bib/doc/bibeditor/#export-selected-entries");
}
