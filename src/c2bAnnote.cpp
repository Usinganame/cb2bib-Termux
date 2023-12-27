/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bAnnote.h"

#include "c2b.h"
#include "c2bFileSystemWatcher.h"
#include "c2bSettings.h"
#include "c2bUtils.h"
#include "c2bWebBrowser.h"

#include <texToHtml.h>

#include <QLabel>
#include <QMessageBox>
#include <QShortcut>
#include <QStatusBar>


/** \page c2bannote cb2Bib Annote

  The cb2Bib Annote module is named after the BibTeX key <tt>annote</tt>.
  Annote is not for a 'one reference annotation' though. Instead, Annote is for
  short notes that interrelate several references. Annote takes a plain text
  note, with minimal or no markup, inserts the bibliographic citations, and
  converts it to a HTML page with links to the referenced documents.


  From within cb2Bib, to write a note, type <tt>Alt+A</tt>, enter a filename,
  either new or existing, and once in Annote, type <tt>E</tt> to start the
  editor. Each time you save the document the viewer will be updated. For help
  on Annote's syntax type <tt>F1</tt>. If cb2Bib was compiled without Annote's
  Viewer, typing <tt>Alt+A</tt> will start the editor and HTML viewing will be
  committed to the default web browser.


  From the command line, typing
\verbatim
cb2bib --html-annote annote.tex
\endverbatim
  will produce the HTML file <tt>annote.tex.html</tt>.


  See also \ref c2bconf_annote and \ref commandline.



\section c2bannote_syntax Annote Syntax

  The resulting HTML file <tt>annote.tex.html</tt> can be seen at
\htmlonly
<a href="https://www.molspaces.com/cb2bib/doc/c2bannote/annote.tex.html" target="_blank">cb2Bib Annote</a>.
\endhtmlonly

\htmlonly
<pre style="font-size: xx-small;">
% annote.tex

GET_C2BANNOTE_TEX_DOC
\endhtmlonly

*/
c2bAnnote::c2bAnnote(QWidget* parentw) : QMainWindow(parentw)
{
    _view_port = new c2bWebBrowser(this);
    setCentralWidget(_view_port);
    QLabel* informationLabel = new QLabel(this);
    statusBar()->addWidget(informationLabel, 1);
    connect(_view_port, SIGNAL(windowTitleChanged(QString)), this, SLOT(setWindowTitle(QString)));
    connect(_view_port, SIGNAL(statusMessage(QString)), this, SLOT(showMessage(QString)));

    // Creating cb2Bib global resources
    c2b* c2b_resources = new c2b(this, this);
    connect(c2b_resources, SIGNAL(statusMessage(QString)), this, SLOT(showMessage(QString)));

    QAction* act = new QAction(QIcon(QString::fromUtf8(":/icons/icons/edit.png")), tr("Edit Note"), this);
    act->setShortcut(QKeySequence(Qt::Key_E));
    act->setStatusTip(tr("Edit TeX note"));
    c2bUtils::addSeparator(_view_port);
    _view_port->addAction(act);
    connect(act, SIGNAL(triggered()), this, SLOT(edit()));

    act = new QAction(QIcon(QString::fromUtf8(":/icons/icons/configure.png")), tr("Configure"), this);
    act->setShortcut(QKeySequence(Qt::Key_C));
    act->setStatusTip(tr("Configure cb2Bib Annote"));
    c2bUtils::addSeparator(_view_port);
    _view_port->addAction(act);
    connect(act, SIGNAL(triggered()), this, SLOT(configure()));

    _settingsP = c2bSettingsP;
    resize(_settingsP->value("c2bAnnote/size", size()).toSize());
    move(_settingsP->value("c2bAnnote/position", pos()).toPoint());
    loadSettings();
    connect(_settingsP, SIGNAL(newSettings()), this, SLOT(loadSettings()));

    _t2h = new texToHtml;
    _fsw = new c2bFileSystemWatcher(this);
    connect(_fsw, SIGNAL(fileChanged(QString)), this, SLOT(annote()));
    disconnect(_view_port->viewReloadAction, 0, 0, 0);
    connect(_view_port->viewReloadAction, SIGNAL(triggered()), this, SLOT(update()));

    QShortcut* help_shortcut = new QShortcut(QKeySequence(QKeySequence::HelpContents), this);
    connect(help_shortcut, SIGNAL(activated()), this, SLOT(help()));
}

c2bAnnote::~c2bAnnote()
{
    delete _t2h;
    _settingsP->setValue("c2bAnnote/position", pos());
    _settingsP->setValue("c2bAnnote/size", size());
}


bool c2bAnnote::show()
{
    _annote_filename = QDir::cleanPath(_settingsP->cl_annote_filename);
    const bool is_html = _annote_filename.endsWith(".html");
    if (is_html)
        _annote_filename.remove(QRegExp("\\.html$"));
    if (!QFileInfo::exists(_annote_filename))
    {
        QMessageBox::warning(this, tr("Warning - cb2Bib"),
                             tr("Unable to open the file %1 for reading.\nError: '%2'.")
                             .arg(QDir::toNativeSeparators(_annote_filename), "File does not exist"),
                             QMessageBox::Ok);
        return false;
    }
    _html_filename = _annote_filename + ".html";
    if (!is_html || !QFileInfo::exists(_html_filename))
        _t2h->toHtml(c2bUtils::fileToString(_annote_filename), _html_filename);
    _view_port->setHomePage(_html_filename);
    _fsw->addPath(_annote_filename);
    QMainWindow::show();
    return true;
}

void c2bAnnote::annote()
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    _t2h->toHtml(c2bUtils::fileToString(_annote_filename), _html_filename);
    if (_html_filename == QDir::cleanPath(_view_port->url().toLocalFile()))
        _view_port->reload();
    QApplication::restoreOverrideCursor();
}

void c2bAnnote::update()
{
    if (_html_filename == QDir::cleanPath(_view_port->url().toLocalFile()))
        annote();
    else
        _view_port->reload();
}

void c2bAnnote::edit()
{
    c2bUtils::openFile(_annote_filename, this);
}

void c2bAnnote::configure()
{
    // Attention: Currently c2bAnnote is page 0. Update here if c2bConfigure changes page ordering.
    c2b::configure(0);
}

void c2bAnnote::setWindowTitle(const QString& title)
{
    if (title.isEmpty())
        QMainWindow::setWindowTitle("Annote - cb2Bib");
    else
        QMainWindow::setWindowTitle(title + " - cb2Bib");
    if (title == "New Note")
        showMessage(tr("Press E to Edit and %1 for Help.").arg(QKeySequence(QKeySequence::HelpContents).toString()));
}

void c2bAnnote::showMessage(const QString& ms)
{
    statusBar()->showMessage(ms, C2B_MESSAGE_TIME);
}

void c2bAnnote::loadSettings()
{
    _view_port->setFont(_settingsP->value("c2bAnnote/Font").value<QFont>());
    _view_port->setFixedFont(_settingsP->value("c2bAnnote/FixedFont").value<QFont>());
}

void c2bAnnote::help()
{
    c2bUtils::displayHelp("https://www.molspaces.com/cb2bib/doc/c2bannote/");
}
