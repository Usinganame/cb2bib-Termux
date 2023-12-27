/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bFileDialog.h"
#include "c2bSettings.h"

#include <QLineEdit>
#include <QTimer>


c2bFileDialog::c2bFileDialog(QWidget* parentw, const QString& caption, const QString& fpath, const QString& ffilter)
    : QFileDialog(parentw, caption, fpath, ffilter)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowFlags(windowFlags() | Qt::WindowMinMaxButtonsHint);
    setOptions(QFileDialog::DontUseNativeDialog);
    setModal(true);
    settings = c2bSettingsP;
}

c2bFileDialog::~c2bFileDialog() {}


QString c2bFileDialog::getFilename(QWidget* parentw, const QString& caption, const QString& path, const QString& filter)
{
    c2bFileDialog* dlg(new c2bFileDialog(parentw, _caption(tr("Select a filename"), caption), _path(path), filter));
    dlg->setFileMode(AnyFile);
    dlg->setOption(QFileDialog::DontConfirmOverwrite, true);
    dlg->setAcceptMode(AcceptSave);
    dlg->setLabelText(QFileDialog::Accept, "Select");
    const QString fn(dlg->fileName(path));
    delete dlg;
    return fn;
}

QString c2bFileDialog::getOpenFilename(QWidget* parentw, const QString& caption, const QString& path,
                                       const QString& filter)
{
    c2bFileDialog* dlg(new c2bFileDialog(parentw, _caption(tr("Select a filename"), caption), _path(path), filter));
    dlg->setFileMode(ExistingFile);
    dlg->setLabelText(QFileDialog::Accept, "Select");
    const QString fn(dlg->fileName(path));
    delete dlg;
    return fn;
}

QStringList c2bFileDialog::getOpenFilenames(QWidget* parentw, const QString& caption, const QString& path,
        const QString& filter)
{
    c2bFileDialog* dlg(new c2bFileDialog(parentw, _caption(tr("Select filenames"), caption), _path(path), filter));
    dlg->setFileMode(ExistingFiles);
    dlg->setLabelText(QFileDialog::Accept, "Select");
    const QString fn(dlg->fileName(path));
    QStringList fns;
    if (!fn.isEmpty())
        fns = dlg->selectedFiles();
    delete dlg;
    return fns;
}

QString c2bFileDialog::getSaveFilename(QWidget* parentw, const QString& caption, const QString& path,
                                       const QString& filter)
{
    c2bFileDialog* dlg(new c2bFileDialog(parentw, _caption(tr("Save As"), caption), _path(path), filter));
    dlg->setFileMode(AnyFile);
    dlg->setAcceptMode(AcceptSave);
    const QString fn(dlg->fileName(path));
    delete dlg;
    return fn;
}

QString c2bFileDialog::getExistingDirectory(QWidget* parentw, const QString& caption, const QString& path)
{
    c2bFileDialog* dlg(new c2bFileDialog(parentw, _caption("Select directory", caption), _dirpath(path), QString()));
    dlg->setFileMode(Directory);
    dlg->setOption(QFileDialog::ShowDirsOnly, true);
    dlg->setLabelText(QFileDialog::Accept, "Select");
    const QString fn(dlg->fileName(QString()));
    delete dlg;
    return fn;
}

QString c2bFileDialog::getSystemFilename(QWidget* parentw, const QString& caption, const QString& path,
        const QString& filter)
{
    c2bFileDialog* dlg(new c2bFileDialog(parentw, _caption(tr("Select a filename"), caption), _path(path), filter));
    dlg->setFileMode(AnyFile);
    dlg->setLabelText(QFileDialog::Accept, "Select");
    dlg->setFilter(QDir::Drives | QDir::AllDirs | QDir::NoDotAndDotDot | QDir::System);
    dlg->setOption(QFileDialog::HideNameFilterDetails, true);
    const QString fn(dlg->fileName(path));
    delete dlg;
    return fn;
}

QString c2bFileDialog::fileName(const QString& path)
{
    readSettings();
    _current_file = path;
    const QStringList fnf(nameFilters().filter(QFileInfo(path).completeSuffix() + ')', Qt::CaseInsensitive));
    if (fnf.count() > 0)
        selectNameFilter(fnf.at(0));
    QTimer::singleShot(250, this, SLOT(selectCurrentFile()));
    QString sfn;
    if (QFileDialog::exec() == QDialog::Accepted)
    {
        const QStringList selected(selectedFiles());
        if (selected.count() > 0)
            sfn = selected.first();
    }
    writeSettings();
    return QDir::toNativeSeparators(QDir::cleanPath(sfn));
}

void c2bFileDialog::accept()
{
    // Set suffix for getSaveFilename dialog
    if (acceptMode() == AcceptSave)
    {
        QString suffix(selectedNameFilter());
        QRegExp sre("\\*\\.([\\w\\.]+)");
        if (sre.indexIn(suffix) != -1)
        {
            suffix = sre.cap(1);
            setDefaultSuffix(suffix);
        }
    }
    QFileDialog::accept();
}

void c2bFileDialog::selectCurrentFile()
{
    // Bug fix for Qt 4.4 not giving correct selection
    const QString fn(_filename(_current_file));
    QLineEdit* le = findChild<QLineEdit*>();
    if (le)
    {
        le->setText(fn);
        le->selectAll();
    }
}

void c2bFileDialog::readSettings()
{
    // Size
    resize(settings->value("c2bFileDialog/size", sizeHint()).toSize());

    // History
    QStringList dhistory(settings->value("c2bFileDialog/history").toStringList());
    dhistory.removeAll(directory().absolutePath());
    std::sort(dhistory.begin(), dhistory.end());
    setHistory(dhistory);
}

void c2bFileDialog::writeSettings()
{
    // Size
    settings->setValue("c2bFileDialog/size", size());

    // History
    if (result() == QDialog::Accepted)
    {
        // Unique paths, keeping the newest history entries
        QStringList dhistory(history());
        dhistory.append(directory().absolutePath());
        dhistory.removeAll(QDir::homePath());
        dhistory.removeAll(QDir::rootPath());
        QStringList chronological(settings->value("c2bFileDialog/history").toStringList());
        chronological.append(dhistory.last());
        // Discard repeated
        dhistory.clear();
        for (int i = chronological.count() - 1; i > -1; --i)
            if (!dhistory.contains(chronological.at(i)))
            {
                dhistory.prepend(chronological.at(i));
                if (dhistory.count() > 10)
                    break;
            }
        settings->setValue("c2bFileDialog/history", dhistory);
    }
}

QString c2bFileDialog::_caption(const QString& generic, const QString& caption)
{
    if (caption.isEmpty())
        return generic + " - cb2Bib";
    else
        return caption + " - cb2Bib";
}

QString c2bFileDialog::_filename(const QString& path)
{
    if (path.isEmpty())
        return path;
    else
        return QFileInfo(path).fileName();
}

QString c2bFileDialog::_path(const QString& path)
{
    if (path.isEmpty())
        return QDir::homePath();
    else
        return QFileInfo(path).absolutePath();
}

QString c2bFileDialog::_dirpath(const QString& path)
{
    if (path.isEmpty())
        return QDir::homePath();
    else
        return QFileInfo(path + '/').absolutePath();
}
