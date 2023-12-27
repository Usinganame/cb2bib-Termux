/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bCiterWidget.h"

#include "c2b.h"
#include "c2bCiterModel.h"
#include "c2bClipboard.h"
#include "c2bCollectionIndex.h"
#include "c2bCoreCiter.h"
#include "c2bFileDialog.h"
#include "c2bSettings.h"
#include "c2bUtils.h"

#include <QKeyEvent>
#include <QLabel>
#include <QMenu>


c2bCiterWidget::c2bCiterWidget(QWidget* parentw) : QWidget(parentw)
{
    ui.setupUi(this);
    ui.clipboardIcon->setVisible(true);
    ui.filterIcon->setVisible(false);
    _citerP = new c2bCoreCiter(this);
    _tray_icon = 0;
    setActions();

    _settingsP = c2bSettingsP;
    resize(_settingsP->value("c2bCiter/size", size()).toSize());
    move(_settingsP->value("c2bCiter/position", pos()).toPoint());

    _clipboard_connected = true;
    _citations = new c2bCiterModel(this);

    connect(_citations, SIGNAL(statusLabel(QString)), this, SLOT(showLabel(QString)));
    connect(_citations, SIGNAL(statusMessage(QString)), this, SLOT(showMessage(QString)));
    connect(c2b::clipboard(), SIGNAL(cbDataChanged(QString)), this, SLOT(filterDataChanged(QString)));
    connect(ui.citationsView, SIGNAL(activated(QModelIndex)), _citations, SLOT(selectCitation(QModelIndex)));
    connect(ui.citationsView, SIGNAL(citeReferences()), this, SLOT(citeReferences()));
    connect(ui.citationsView, SIGNAL(editReference()), this, SLOT(editReference()));
    connect(ui.citationsView, SIGNAL(hideCiter()), this, SLOT(hide()));
    connect(ui.citationsView, SIGNAL(openAnnote()), this, SIGNAL(openAnnote()));
    connect(ui.citationsView, SIGNAL(openFile()), this, SLOT(openFile()));
    connect(ui.citationsView, SIGNAL(openUrl()), this, SLOT(openUrl()));
    connect(ui.citationsView, SIGNAL(patternFilterChanged(bool,QString)), this,
            SLOT(updatePatternFilter(bool,QString)));
    connect(ui.citationsView, SIGNAL(statusMessage(QString)), this, SLOT(showMessage(QString)));
}

c2bCiterWidget::~c2bCiterWidget()
{
    if (!isFullScreen())
    {
        _settingsP->setValue("c2bCiter/position", pos());
        _settingsP->setValue("c2bCiter/size", size());
    }
    _settingsP->setValue("c2bCiter/format", static_cast<int>(_citations->lastCitationFormat()));
}


void c2bCiterWidget::load()
{
    _bibtex_files.clear();
    if (_settingsP->cl_citer_filenames.count() == 0)
        _bibtex_files = c2bUtils::filesInDir(QFileInfo(_settingsP->fileName("cb2Bib/BibTeXFile")).absolutePath(),
                                             QStringList() << "*.bib");
    else
        for (int i = 0; i < _settingsP->cl_citer_filenames.count(); ++i)
            _bibtex_files += c2bUtils::filesInDir(_settingsP->cl_citer_filenames.at(i), QStringList() << "*.bib");
    c2bCiter::State state;
    state.format = static_cast<c2bCiter::Format>(_settingsP->value("c2bCiter/format", state.format).toInt());
    reload(state);
}

void c2bCiterWidget::reload()
{
    const c2bCiter::State state(ui.citationsView->currentState());
    reload(state);
}

void c2bCiterWidget::reload(const c2bCiter::State& state)
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    updatePatternFilter(false, QString());
    if (_bibtex_files.count() == 1)
        setWindowTitle(
            tr("%1 - cb2Bib").arg(QDir::toNativeSeparators(QFileInfo(_bibtex_files.at(0)).absoluteFilePath())));
    else if (_bibtex_files.count() > 1)
        setWindowTitle(tr("%1 - cb2Bib").arg(QDir::toNativeSeparators(QFileInfo(_bibtex_files.at(0)).absolutePath())));
    else
        setWindowTitle(tr("Citer - cb2Bib"));
    ui.citationsView->reloadModel(_citations, _bibtex_files, state);
    QApplication::restoreOverrideCursor();
}

void c2bCiterWidget::toggleVisible()
{
    if (isVisible())
        hide();
    else
        show();
}

void c2bCiterWidget::show()
{
    if (isHidden())
        QWidget::show();
    raise();
    activateWindow();
    ui.citationsView->setFocus();
}

void c2bCiterWidget::setTrayIcon()
{
    _tray_icon = new QSystemTrayIcon(this);
    _tray_icon->setIcon(QIcon(":/icons/icons/cb2bib.ico"));
    _tray_icon->setToolTip("c2bBib Citer");
    QMenu* tray_icon_menu = new QMenu(this);
    foreach (QAction* a, actions())
    {
        tray_icon_menu->addAction(a);
    }
    _tray_icon->setContextMenu(tray_icon_menu);
    _tray_icon->show();
    connect(_tray_icon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this,
            SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
}

void c2bCiterWidget::trayIconActivated(QSystemTrayIcon::ActivationReason r)
{
    if (r == QSystemTrayIcon::Context)
        return;
    show();
}

void c2bCiterWidget::setActions()
{
    QAction* a;
    a = new QAction(this);
    a->setText(tr("Citer Help"));
    a->setShortcut(QKeySequence(QKeySequence::HelpContents));
    addAction(a);
    connect(a, SIGNAL(triggered()), this, SLOT(help()));
    c2bUtils::addSeparator(this);

    a = new QAction(this);
    a->setText(tr("Open Directory"));
    a->setShortcut(QKeySequence(QKeySequence::Open));
    addAction(a);
    connect(a, SIGNAL(triggered()), this, SLOT(openDirectory()));
    a = new QAction(this);
    a->setText(tr("Open Files"));
    a->setShortcut(QKeySequence(Qt::ALT + Qt::Key_O));
    addAction(a);
    connect(a, SIGNAL(triggered()), this, SLOT(openFiles()));
    c2bUtils::addSeparator(this);

    a = new QAction(this);
    a->setText(tr("Refresh"));
    a->setShortcut(QKeySequence(QKeySequence::Refresh));
    addAction(a);
    connect(a, SIGNAL(triggered()), this, SLOT(reload()));
    c2bUtils::addSeparator(this);

    a = new QAction(this);
    a->setText(tr("Search In Files"));
    a->setShortcut(QKeySequence(QKeySequence::Find));
    addAction(a);
    connect(a, SIGNAL(triggered()), this, SLOT(doSearchInFiles()));
    c2bUtils::addSeparator(this);

    a = new QAction(this);
    a->setText(tr("Set LyX Pipe"));
    a->setShortcut(QKeySequence(Qt::ALT + Qt::Key_L));
    addAction(a);
    connect(a, SIGNAL(triggered()), _citerP, SLOT(setLyXPipe()));
    c2bUtils::addSeparator(this);

    a = new QAction(this);
    a->setText(tr("Toggle cb2Bib"));
    a->setShortcut(QKeySequence(Qt::Key_F2));
    addAction(a);
    connect(a, SIGNAL(triggered()), this, SLOT(toggleCb2Bib()));
    a = new QAction(this);
    a->setText(tr("Toggle Clipboard"));
    a->setShortcut(QKeySequence(Qt::ALT + Qt::Key_C));
    addAction(a);
    connect(a, SIGNAL(triggered()), this, SLOT(toggleClipboard()));
    a = new QAction(this);
    a->setText(tr("Toggle Full Screen"));
    a->setShortcut(QKeySequence(Qt::ALT + Qt::Key_F));
    addAction(a);
    connect(a, SIGNAL(triggered()), this, SLOT(toggleFullScreen()));
    c2bUtils::addSeparator(this);

    a = new QAction(this);
    a->setText(tr("Index Documents"));
    addAction(a);
    connect(a, SIGNAL(triggered()), this, SLOT(indexDocuments()));
    c2bUtils::addSeparator(this);

    a = new QAction(this);
    a->setText(tr("Exit"));
    a->setShortcut(QKeySequence(QKeySequence::Quit));
    addAction(a);
    connect(a, SIGNAL(triggered()), c2b::instance(), SLOT(exitRequested()));
}

void c2bCiterWidget::openDirectory()
{
    QString dir;
    if (_bibtex_files.count() > 0)
        dir = _bibtex_files.at(0);
    dir = c2bFileDialog::getExistingDirectory(this, tr("Select BibTeX directory"), dir);
    if (dir.isEmpty())
        return;
    _bibtex_files = c2bUtils::filesInDir(dir, QStringList() << "*.bib");
    reload();
}

void c2bCiterWidget::openFiles()
{
    QString dir;
    if (_bibtex_files.count() > 0)
        dir = _bibtex_files.at(0);
    const QStringList fns(
        c2bFileDialog::getOpenFilenames(this, "Select BibTeX filenames", dir, "BibTeX (*.bib);;All (*)"));
    if (fns.count() > 0)
    {
        _bibtex_files = fns;
        reload();
    }
}

void c2bCiterWidget::doSearchInFiles()
{
    const QString fn(_citations->isKeywordView() ? QString()
                     : _citations->dataBibTeXFile(ui.citationsView->currentIndex()));
    if (fn.isEmpty())
        showMessage(tr("No active reference."));
    else
        c2b::doSearchInFiles(QString(), fn);
}

void c2bCiterWidget::toggleCb2Bib()
{
    if (c2b::mainWidget()->isVisible())
        c2b::mainWidget()->hide();
    else
        c2bUtils::setWidgetOnTop(c2b::mainWidget());
}

void c2bCiterWidget::toggleClipboard()
{
    _clipboard_connected = !_clipboard_connected;
    ui.clipboardIcon->setVisible(_clipboard_connected);
    if (_clipboard_connected)
        showMessage(tr("Filter set to clipboard contents."));
}

void c2bCiterWidget::toggleFullScreen()
{
    if (isFullScreen())
        showNormal();
    else
        showFullScreen();
}

void c2bCiterWidget::indexDocuments()
{
    c2bCollectionIndex* ci(new c2bCollectionIndex(0));
    ci->setAttribute(Qt::WA_DeleteOnClose);
    ci->show();
    ci->index();
}

void c2bCiterWidget::filterDataChanged(const QString& filter)
{
    if (_clipboard_connected && isVisible())
    {
        const QString p(c2bUtils::toAscii(filter, c2bUtils::Collation).simplified());
        updatePatternFilter(false, p);
        ui.citationsView->setPatternFilter(p);
    }
}

void c2bCiterWidget::updatePatternFilter(const bool mode, const QString& pattern)
{
    ui.filterIcon->setVisible(mode);
    if (mode)
        showLabel(tr("Filter: %1_").arg(pattern));
    else
    {
        if (pattern.isEmpty())
            showLabel(_citations->isKeywordView() ? tr("Glossary of terms") : pattern);
        else
            showLabel(tr("Filter: %1").arg(pattern));
    }
}

void c2bCiterWidget::citeReferences()
{
    const QStringList k(_citations->dataSelectedCiteIds());
    if (k.count() > 0)
    {
        hide();
        _citerP->cite(k);
    }
    else
        showMessage(tr("No selected references."));
}

void c2bCiterWidget::editReference()
{
    if (_citations->isKeywordView())
    {
        showMessage(tr("No active reference."));
        return;
    }
    const QString r(_citations->dataBibTeXPosition(ui.citationsView->currentIndex()));
    if (r.isEmpty())
        showMessage(tr("No active reference."));
    else
        emit openFile(r);
}

void c2bCiterWidget::openFile()
{
    if (_citations->count() == 0)
        return;
    if (_citations->isKeywordView())
    {
        showMessage(tr("No active reference."));
        return;
    }
    const QString f(_citations->dataFile(ui.citationsView->currentIndex()));
    if (f.isEmpty())
        showMessage(tr("No File entry in this reference."));
    else
    {
        showMessage(tr("Opening %1").arg(f));
        c2bUtils::openFile(f, parentWidget());
    }
}

void c2bCiterWidget::openUrl()
{
    if (_citations->count() == 0)
        return;
    if (_citations->isKeywordView())
    {
        showMessage(tr("No active reference."));
        return;
    }
    const QString u(_citations->dataUrl(ui.citationsView->currentIndex()));
    if (u.isEmpty())
        showMessage(tr("No URL entry in this reference."));
    else
    {
        showMessage(tr("Opening %1").arg(QUrl::fromPercentEncoding(u.toUtf8())));
        c2bUtils::openFile(u, parentWidget());
    }
}

void c2bCiterWidget::showLabel()
{
    ui.statusBar->showMessage(_status_label, 0);
}

void c2bCiterWidget::showLabel(const QString& label)
{
    _status_label = label;
    ui.statusBar->showMessage(_status_label, 0);
}

void c2bCiterWidget::showMessage(const QString& message)
{
    QTimer::singleShot(C2B_MESSAGE_TIME, this, SLOT(showLabel()));
    ui.statusBar->showMessage(message, 0);
}

void c2bCiterWidget::help()
{
    c2bUtils::displayHelp("https://www.molspaces.com/cb2bib/doc/c2bciter/");
}
