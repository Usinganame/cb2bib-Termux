/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2b.h"

#include "c2bClipboard.h"
#include "c2bConfigure.h"
#include "dialog.h"
#include "ui_proxyDialog.h"

#include <QAuthenticator>
#include <QMessageBox>
#include <QNetworkProxy>
#include <QProgressDialog>


/**
    Global resources for cb2Bib
*/
c2b::c2b(QWidget* main, QObject* parento) : QObject(parento)
{
    Q_ASSERT_X(!_c2b_single_instance, "c2b", "cb2Bib resources already instantiated");
    c2b::_c2b_single_instance = this;
    _c2b_main = main;

    if (_c2b_main->inherits("cb2Bib"))
    {
        // Create bibliographic parser
        _c2b_bibparser = new c2bBibParser(this);

        // Create cb2Bib network
        _c2b_network = new network(this);
        connect(_c2b_network, SIGNAL(proxyAuthenticationRequired(QNetworkProxy,QAuthenticator*)), this,
                SLOT(proxyAuthenticationRequired(QNetworkProxy,QAuthenticator*)));
        connect(_c2b_network, SIGNAL(downloadProgress(qint64,qint64)), this,
                SLOT(updateDownloadProgress(qint64,qint64)));
        _download_progress = new QProgressDialog(_c2b_main, dialog::flags);
        _download_progress->setWindowTitle("Downloading...");
        _download_progress->reset();
        connect(_download_progress, SIGNAL(canceled()), _c2b_network, SLOT(cancelDownload()));

        // Create cb2Bib network query info
        _c2b_netqinf = new c2bNetworkQueryInfo(this);

        // Create cb2Bib metadata parser
        _c2b_metadataparser = new metadataParser(_c2b_bibparser, this);
        connect(_c2b_metadataparser, SIGNAL(showMessage(QString,QString)), this, SLOT(showMessage(QString,QString)));

        // Create cb2Bib clipboard
        _c2b_clipboard = new c2bClipboard(this);
        _c2b_clipboard->setConnected(true);
    }
    else if (_c2b_main->inherits("c2bAnnote"))
    {
        // Nothing is needed at present for the c2bAnnote
    }
    else
        Q_ASSERT_X(false, "c2b", "unknown required resources for main");
}

c2b::~c2b()
{
    _c2b_single_instance = 0;
}


c2b* c2b::_c2b_single_instance = 0;


void c2b::showMessage(const QString& title, const QString& ms)
{
    QMessageBox::warning(_c2b_main, title, ms, QMessageBox::Ok);
}

void c2b::configure(int index)
{
    c2bConfigure* c = new c2bConfigure();
    if (index > -1)
        c->setPage(index);
    if (c->exec() == QDialog::Accepted)
        showMessage(tr("Configuration was saved."));
    else
        showMessage(tr("Configuration was cancelled."));
    delete c;
}

void c2b::exitRequested()
{
    foreach (QWidget* w, QApplication::topLevelWidgets())
    {
        // So far only editors grant user exit cancellation
        // Avoid closing other visible widgets until exit is granted
        if (w->isVisible())
            if (w->inherits("c2bEditor"))
                w->close();
    }
    qApp->processEvents();
    foreach (QWidget* widget, QApplication::topLevelWidgets())
    {
        if (widget->isVisible())
            if (widget->inherits("c2bEditor"))
                return;
    }
    qApp->closeAllWindows();
    qApp->processEvents();
    if (!qApp->quitOnLastWindowClosed())
        qApp->quit();
}

void c2b::updateDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    if (bytesTotal < 50000)
        return;
    if (bytesReceived == bytesTotal)
    {
        _download_progress->reset();
        return;
    }
    _download_progress->setLabelText(tr("Retrieving from %1...").arg(QUrl(_c2b_network->sourceFilename()).host()));
    _download_progress->setMaximum((int)bytesTotal);
    _download_progress->setValue((int)bytesReceived);
}

void c2b::proxyAuthenticationRequired(const QNetworkProxy& proxy, QAuthenticator* auth)
{
    QDialog dialog(_c2b_main, dialog::flags);
    Ui::proxyDialog proxyDialog;
    proxyDialog.setupUi(&dialog);
    dialog.setWindowTitle(tr("Proxy %1 Authentication - cb2Bib").arg(proxy.hostName()));
    if (dialog.exec() == QDialog::Accepted)
    {
        auth->setUser(proxyDialog.userNameLineEdit->text());
        auth->setPassword(proxyDialog.passwordLineEdit->text());
    }
    else
        _c2b_network->cancelDownload();
}
