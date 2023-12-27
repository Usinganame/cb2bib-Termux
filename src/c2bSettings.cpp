/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bSettings.h"
#include "c2bUtils.h"

#include <QApplication>
#include <QClipboard>
#include <QMessageBox>
#include <QProgressBar>
#include <QShortcut>
#include <QTimer>


/**
    Global settings for cb2Bib
*/
c2bSettings::c2bSettings(const QString& organization, const QString& application, QObject* parento)
    : settings(organization, application, parento), _progress_bar(0) {}

c2bSettings::c2bSettings(const QString& fn, QObject* parento) : settings(fn, parento), _progress_bar(0) {}

c2bSettings::~c2bSettings()
{
    delete _progress_bar;
}


c2bSettings* c2bSettings::initSettings()
{
    c2bSettings* s;
    if (c2bSettings::isConfiguredMode())
        s = new c2bSettings(c2bSettings::configuredFilename());
    else
        s = new c2bSettings(qApp->organizationName(), qApp->applicationName());
    s->init();
    return s;
}

void c2bSettings::init()
{
    settings::init();
    _progress_bar = 0;
    if (cl_console_mode)
        return;
    setDefaults();
    if (cl_import)
        // Process cl_import_filename and update cl_cb2bib_import_mode
        processReferenceFile();
    if (cl_cb2bib_mode && !cl_cb2bib_import_mode)
    {
        setValue("cb2Bib/isRunning", true);
        sync();
        connect(qApp, SIGNAL(lastWindowClosed()), this, SLOT(guiExits()));
    }
}

void c2bSettings::notify()
{
    update();
    emit newSettings();
}

void c2bSettings::update()
{
    // Values for very general GUI settings
    c2bMonoFont = value("cb2Bib/MonoFont").value<QFont>();
    colors.loadColors(this);
}

void c2bSettings::setDefaults()
{
    QHash<QString, QVariant> defaults;
    defaults["cb2Bib/MonoFont"] = QFont("Courier");

    const QStringList keys(defaults.keys());
    for (int i = 0; i < keys.count(); ++i)
        setValue(keys.at(i), value(keys.at(i), defaults.value(keys.at(i))));

    // Shortcuts
    _default_keysequences.clear();
    _default_keysequences["Shortcuts/cb2Bib/Button About and Bookmarks"] = QKeySequence(Qt::CTRL + Qt::Key_Tab);
    _default_keysequences["Shortcuts/cb2Bib/Button Configure"] = QKeySequence();
    _default_keysequences["Shortcuts/cb2Bib/Button Network Query"] = QKeySequence(Qt::ALT + Qt::Key_N);
    _default_keysequences["Shortcuts/cb2Bib/Button Start PDFImport"] = QKeySequence();
    _default_keysequences["Shortcuts/cb2Bib/Button Toggle Connection"] = QKeySequence();
    _default_keysequences["Shortcuts/cb2Bib/Button View BibTeX"] = QKeySequence(Qt::ALT + Qt::Key_V);
    _default_keysequences["Shortcuts/cb2Bib/Check Repeated"] = QKeySequence(Qt::ALT + Qt::Key_X);
    _default_keysequences["Shortcuts/cb2Bib/Clear All Fields"] = QKeySequence();
    _default_keysequences["Shortcuts/cb2Bib/Delete Temporary BibTeX File"] = QKeySequence(Qt::ALT + Qt::Key_D);
    _default_keysequences["Shortcuts/cb2Bib/Edit Bookmarks"] = QKeySequence(Qt::ALT + Qt::Key_B);
    _default_keysequences["Shortcuts/cb2Bib/Edit Journal Abbreviations"] = QKeySequence(Qt::ALT + Qt::Key_J);
    _default_keysequences["Shortcuts/cb2Bib/Edit Regular Expressions"] = QKeySequence(Qt::ALT + Qt::Key_E);
    _default_keysequences["Shortcuts/cb2Bib/Guess Bibliographic Fields"] = QKeySequence(Qt::ALT + Qt::Key_G);
    _default_keysequences["Shortcuts/cb2Bib/Insert Regular Expression"] = QKeySequence(Qt::ALT + Qt::Key_I);
    _default_keysequences["Shortcuts/cb2Bib/Open Document"] = QKeySequence(Qt::ALT + Qt::Key_O);
    _default_keysequences["Shortcuts/cb2Bib/Postprocess BibTeX"] = QKeySequence(Qt::ALT + Qt::Key_P);
    _default_keysequences["Shortcuts/cb2Bib/Preparse Clipboard"] = QKeySequence(Qt::ALT + Qt::Key_C);
    _default_keysequences["Shortcuts/cb2Bib/Restart Recognition"] = QKeySequence(Qt::ALT + Qt::Key_R);
    _default_keysequences["Shortcuts/cb2Bib/Select BibTeX File"] = QKeySequence(Qt::ALT + Qt::Key_S);
    _default_keysequences["Shortcuts/cb2Bib/Select Document File"] = QKeySequence(Qt::ALT + Qt::Key_F);
    _default_keysequences["Shortcuts/cb2Bib/Annote Editor"] = QKeySequence(Qt::ALT + Qt::Key_A);
    _default_keysequences["Shortcuts/cb2Bib/Toggle Reference Tabs"] = QKeySequence(Qt::Key_F4);
    _default_keysequences["Shortcuts/cb2Bib/View Tagged Clipboard Data"] = QKeySequence();
    _default_keysequences["Shortcuts/cb2Bib/Write Metadata to Document"] = QKeySequence(Qt::ALT + Qt::Key_W);

    _default_keysequences["Shortcuts/Editor/Browse Reference by DOI"] = QKeySequence();
    _default_keysequences["Shortcuts/Editor/Cite Selected Entries"] = QKeySequence(Qt::ALT + Qt::Key_C);
    _default_keysequences["Shortcuts/Editor/Clear Entry Selection"] = QKeySequence(Qt::Key_Delete);
    _default_keysequences["Shortcuts/Editor/Export Entries"] = QKeySequence();
    _default_keysequences["Shortcuts/Editor/Local Search for Selected Text"] = QKeySequence();
    _default_keysequences["Shortcuts/Editor/Open Document File"] = QKeySequence();
    _default_keysequences["Shortcuts/Editor/Open Document URL"] = QKeySequence();
    _default_keysequences["Shortcuts/Editor/Paste Current BibTeX"] = QKeySequence(Qt::SHIFT + Qt::Key_Insert);
    _default_keysequences["Shortcuts/Editor/Restart Network Query"] = QKeySequence(Qt::ALT + Qt::Key_N);
    _default_keysequences["Shortcuts/Editor/Restart Recognition"] = QKeySequence(Qt::ALT + Qt::Key_R);
    _default_keysequences["Shortcuts/Editor/Save and Postprocess"] = QKeySequence(Qt::ALT + Qt::Key_P);
    _default_keysequences["Shortcuts/Editor/Selection to LaTeX"] = QKeySequence();
    _default_keysequences["Shortcuts/Editor/Selection to Unicode"] = QKeySequence();
    _default_keysequences["Shortcuts/Editor/Set Journals to Abbreviated Name"] = QKeySequence();
    _default_keysequences["Shortcuts/Editor/Set Journals to Full Name"] = QKeySequence();
    _default_keysequences["Shortcuts/Editor/Set LyX Pipe"] = QKeySequence(Qt::ALT + Qt::Key_L);
    _default_keysequences["Shortcuts/Editor/Toggle Editing and Browsing"] = QKeySequence(Qt::CTRL + Qt::Key_Tab);
    _default_keysequences["Shortcuts/Editor/Toggle Word Wrapping"] = QKeySequence();
    _default_keysequences["Shortcuts/Editor/Update Documents Metadata"] = QKeySequence();
    _default_keysequences["Shortcuts/Editor/View Note in External Browser"] = QKeySequence();
    _default_keysequences["Shortcuts/Editor/Web Search Settings"] = QKeySequence();
    _default_keysequences["Shortcuts/Editor/Web Search by Author"] = QKeySequence();
    _default_keysequences["Shortcuts/Editor/Web Search by Title"] = QKeySequence();
    _default_keysequences["Shortcuts/Editor/Web Search for Selected Text"] = QKeySequence();

    const QStringList sc(_default_keysequences.keys());
    for (int i = 0; i < sc.count(); ++i)
        setValue(sc.at(i), value(sc.at(i), _default_keysequences.value(sc.at(i))));

    update();
}

void c2bSettings::setKeysequences(const QHash<QString, QKeySequence>& keysequences)
{
    if (keysequences.size() == 0)
        return;
    QHash<QString, QKeySequence>::const_iterator it(keysequences.constBegin());
    while (it != keysequences.constEnd())
    {
        setValue(it.key(), it.value());
        ++it;
    }

    // Set keysequences to created objects
    const QString sctag("Shortcuts/");
    foreach (QWidget* w, QApplication::topLevelWidgets())
    {
        const QList<QAction*> alist(w->findChildren<QAction*>());
        for (int i = 0; i < alist.count(); ++i)
        {
            const QString fullname(alist.at(i)->data().toString());
            if (fullname.startsWith(sctag))
                alist.at(i)->setShortcut(keysequence(fullname));
        }
        const QList<QShortcut*> sclist(w->findChildren<QShortcut*>());
        for (int i = 0; i < sclist.count(); ++i)
        {
            const QString fullname(sclist.at(i)->objectName());
            if (fullname.startsWith(sctag))
                sclist.at(i)->setKey(keysequence(fullname));
        }
    }
}

void c2bSettings::setKeysequence(const QString& path, QAction* action)
{
    if (!action)
        return;
    const QString fullname(path + action->text());
    if (_default_keysequences.contains(fullname))
    {
        action->setShortcut(keysequence(fullname));
        action->setData(fullname);
    }
    else
        c2bUtils::warn(tr("Action '%1' is not registered in default keysequence list").arg(fullname));
}

void c2bSettings::setKeysequence(const QString& fullname, QShortcut* shortcut)
{
    if (!shortcut)
        return;
    if (_default_keysequences.contains(fullname))
    {
        shortcut->setObjectName(fullname);
        shortcut->setKey(keysequence(fullname));
    }
    else
        c2bUtils::warn(tr("Shortcut '%1' is not registered in default keysequence list").arg(fullname));
}

#ifdef Q_OS_WIN
#include <QFileDialog>
QString c2bSettings::decodeFilename(const QString& fn) const
{
    // This function is meant for fn given by the command shell and that will end up being visible
    const QString dfn(settings::decodeFilename(fn));
    QFileDialog fd(0, QString(), dfn);
    const QStringList fns(fd.selectedFiles());
    if (fns.count() == 0)
        return dfn;
    const QString wdfn(fns.first());
    if (QFileInfo(wdfn).exists())
        return QDir::toNativeSeparators(wdfn);
    else
        return dfn;
}
#endif

/***************************************************************************
 *  Downloaded reference extraction
 ***************************************************************************/

void c2bSettings::processReferenceFile()
{
    // The "Download reference to reference manager" functionality to cb2Bib is implemented as follows:
    // - Put downloaded reference into the clipboard
    // - If no cb2Bib instance is running, launch cb2Bib GUI, otherwise exit
    // This is simple, enough, and consistent with a 'clipboard to BibTeX' program.
    // The 'single instance' implementation is naive, but it is sufficient for cb2Bib, and does not prevent
    // from having multiple cb2Bib instances in its usual deployment, if so desired.
    // Aware of QClipboard X11 note: "You should not store or retrieve the clipboard contents in response
    // to timer or non-user-input events". Functions processReferenceFile() and processprocessReferenceFileEvent()
    // do not follow it. It seems to work smooth, for all platforms, and, overall, it is a feasible solution
    // in this particular case.

    QFile file(cl_import_filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cl_cb2bib_import_mode = true;
        QMessageBox::warning(0, tr("Warning - cb2Bib"),
                             tr("Unable to open the reference file %1 for reading.\nError: '%2'.")
                             .arg(cl_import_filename, file.errorString()),
                             QMessageBox::Ok);
        QTimer::singleShot(500, qApp, SLOT(quit()));
    }
    else
    {
        if (value("cb2Bib/isRunning", false).toBool())
        {
            cl_cb2bib_import_mode = true;
            if (!_progress_bar)
                _progress_bar = new QProgressBar;
            _progress_bar->setRange(0, 100);
            _progress_bar->setWindowTitle(QObject::tr("Importing..."));
            _progress_bar->show();
            _progress_bar->setValue(50);
        }
        QTimer::singleShot(500, this, SLOT(processReferenceFileEvent()));
    }
}

void c2bSettings::processReferenceFileEvent()
{
    const QString reference(c2bUtils::fileToString(cl_import_filename).trimmed());
    QClipboard* cb = qApp->clipboard();
    cb->setText(reference, QClipboard::Clipboard);
    if (cl_cb2bib_import_mode)
    {
        if (_progress_bar)
            _progress_bar->setValue(100);
        QTimer::singleShot(500, qApp, SLOT(quit()));
    }
}

void c2bSettings::guiExits()
{
    setValue("cb2Bib/isRunning", false);
    sync();
}
