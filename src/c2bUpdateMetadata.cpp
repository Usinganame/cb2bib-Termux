/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bUpdateMetadata.h"

#include "c2b.h"
#include "c2bSettings.h"
#include "c2bUtils.h"

#include <QPushButton>
#include <QTimer>


c2bUpdateMetadata::c2bUpdateMetadata(QWidget* parentw) : QDialog(parentw)
{
    ui.setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle(tr("Documents Updating Log - cb2Bib"));
    ui.Log->setFont(c2bSettingsP->c2bMonoFont);
    ui.Log->setLineWrapMode(QPlainTextEdit::NoWrap);
    _buttonAbort = new QPushButton(tr("Abort"));
    ui.buttonBox->addButton(_buttonAbort, QDialogButtonBox::ActionRole);
    connect(_buttonAbort, SIGNAL(clicked()), this, SLOT(aborted()));
    connect(ui.buttonBox, SIGNAL(helpRequested()), this, SLOT(help()));
    resize(c2bSettingsP->value("c2bLogWidget/size", size()).toSize());
    _bpP = c2b::bibParser();
}

c2bUpdateMetadata::~c2bUpdateMetadata()
{
    c2bSettingsP->setValue("c2bLogWidget/size", size());
}


void c2bUpdateMetadata::update(const QString& fn, const QString& bibtex)
{
    ui.Log->clear();
    _fn = fn;
    _bibtex = bibtex;
    QTimer::singleShot(500, this, SLOT(update()));
    QDialog::exec();
}

void c2bUpdateMetadata::update()
{
    ui.Log->appendPlainText(tr("[cb2bib] Updating documents metadata...\n"));
    const QString exiftool_bin(c2bSettingsP->fileName("cb2Bib/ExifToolBin"));
    if (exiftool_bin.isEmpty())
    {
        ui.Log->appendPlainText(tr("[cb2bib] ExifTool location has not been specified."));
        return;
    }
    const QFileInfo exiftool_bin_fi(exiftool_bin);
    if (exiftool_bin_fi.isAbsolute())
        if (!exiftool_bin_fi.exists())
        {
            ui.Log->appendPlainText(tr("[cb2bib] ExifTool file %1 does not exist.").arg(exiftool_bin));
            return;
        }
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    ui.buttonBox->button(QDialogButtonBox::Close)->setEnabled(false);
    _buttonAbort->setEnabled(true);
    _buttonAbort->setFocus();
    _aborted = false;
    ui.Log->appendPlainText(tr("[cb2bib] Processing file %1...\n").arg(_fn));

    int doc_counter(0);
    int error_counter(0);
    int updated_counter(0);
    metadataParser* mp = c2b::metaParser();
    bibReference ref;
    _bpP->initReferenceParsing(_fn, _bpP->bibliographicFields(), &ref);
    while (_bpP->referencesIn(_bibtex, &ref) && !_aborted)
    {
        QCoreApplication::processEvents();
        const QString file(ref.value("file"));
        if (file.isEmpty())
        {
            ui.Log->appendPlainText(tr("[cb2bib] %1: No file in reference.").arg(ref.citeidName));
            continue;
        }
        QFileInfo fi(file);
        if (!fi.exists())
        {
            ui.Log->appendPlainText(tr("[cb2bib] %1: Warning: File %2 does not exist.").arg(ref.citeidName, file));
            continue;
        }
        ++doc_counter;
        bibReference mref;
        const bool has_reference(mp->metadata(file, &mref));
        if (has_reference)
            if (!needsUpdating(ref, mref))
                continue;
        if (!fi.isWritable())
        {
            ++error_counter;
            ui.Log->appendPlainText(tr("[cb2bib] %1: Error: File %2 is not writable.").arg(ref.citeidName, file));
            continue;
        }
        QString error_str;
        if (mp->insertMetadata(ref, file, &error_str, has_reference))
        {
            if (mp->metadata(file, &mref))
                if (!needsUpdating(ref, mref))
                {
                    ++updated_counter;
                    ui.Log->appendPlainText(tr("[cb2bib] %1: File %2 successfully updated.").arg(ref.citeidName, file));
                    continue;
                }
            ++error_counter;
            ui.Log->appendPlainText(
                tr("[cb2bib] %1: Warning: File %2 was not properly updated.").arg(ref.citeidName, file));
            writeDifferences(ref, mref);
        }
        else
        {
            ++error_counter;
            ui.Log->appendPlainText(tr("[cb2bib] %1: Error: File %2 could not be updated.").arg(ref.citeidName, file));
            ui.Log->appendPlainText(tr("[exiftool] '%1'.").arg(error_str));
        }
        QCoreApplication::processEvents();
    }

    QApplication::restoreOverrideCursor();
    ui.buttonBox->button(QDialogButtonBox::Close)->setEnabled(true);
    ui.buttonBox->button(QDialogButtonBox::Close)->setFocus();
    _buttonAbort->setEnabled(false);

    ui.Log->appendPlainText(tr("\n[cb2bib] Checked %1 documents.").arg(doc_counter));
    if (doc_counter > 0 && updated_counter == 0 && error_counter == 0)
        ui.Log->appendPlainText(tr("[cb2bib] Documents Metadata was up to date."));
    else
        ui.Log->appendPlainText(tr("[cb2bib] Updated %1 documents.").arg(updated_counter));
    if (error_counter > 0)
        ui.Log->appendPlainText(tr("[cb2bib] Found %1 errors.").arg(error_counter));
    c2b::showMessage(tr("Updated %1 documents.").arg(updated_counter));
}

bool c2bUpdateMetadata::needsUpdating(const bibReference& ref, const bibReference& mref)
{
    if (ref.typeName != mref.typeName)
        return true;
    const QStringList& bibliographicFields = _bpP->bibliographicFields();
    for (int i = 0; i < bibliographicFields.count(); ++i)
    {
        const QString key(bibliographicFields.at(i));
        if (key == "file")
            continue;
        else if (key == "id")
            continue;
        QString value(ref.value(key));
        c2bUtils::fullBibToC2b(value);
        if (key == "title" || key == "booktitle")
            c2bUtils::cleanTitle(value);
        if (value != mref.value(key))
            return true;
    }
    return false;
}

void c2bUpdateMetadata::writeDifferences(const bibReference& ref, const bibReference& mref)
{
    const QString diff("  [Key] '%1'\n  [In Reference] '%2'\n  [In Document]  '%3'");
    if (ref.typeName != mref.typeName)
        ui.Log->appendPlainText(diff.arg("type", ref.typeName, mref.typeName));
    const QStringList& bibliographicFields = _bpP->bibliographicFields();
    for (int i = 0; i < bibliographicFields.count(); ++i)
    {
        const QString key(bibliographicFields.at(i));
        if (key == "file")
            continue;
        else if (key == "id")
            continue;
        QString value(ref.value(key));
        c2bUtils::fullBibToC2b(value);
        if (key == "title" || key == "booktitle")
            c2bUtils::cleanTitle(value);
        if (value != mref.value(key))
            ui.Log->appendPlainText(diff.arg(key, value, mref.value(key)));
    }
}

void c2bUpdateMetadata::aborted()
{
    _aborted = true;
    _buttonAbort->setEnabled(false);
    ui.Log->appendPlainText(tr("\n\n[cb2bib] Aborted.\n"));
}

void c2bUpdateMetadata::help()
{
    c2bUtils::displayHelp("https://www.molspaces.com/cb2bib/doc/bibeditor/#update-documents-metadata");
}
