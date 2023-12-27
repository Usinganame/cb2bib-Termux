/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "network.h"

#include "cb2bib_utilities.h"
#include "settings.h"

#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QNetworkProxy>
#include <QNetworkReply>
#include <QTimer>


network::network(QObject* parento) : QObject(parento), _max_redirections(15)
{
    _is_fetching = false;
    _fetcher = new QNetworkAccessManager(this);
    connect(_fetcher, SIGNAL(proxyAuthenticationRequired(QNetworkProxy,QAuthenticator*)), this,
            SIGNAL(proxyAuthenticationRequired(QNetworkProxy,QAuthenticator*)));
    loadSettings();
    connect(settings::instance(), SIGNAL(newSettings()), this, SLOT(loadSettings()));
    // Set predefined cookies
    QNetworkCookieJar* ncj = _fetcher->cookieJar();
    QNetworkCookie nc("GSP", "ID=d093ce1ea042ad2b:IN=54afcd58e3b38df9:HIN=ff7e3a3ab3fbae0a+7e6cc990821af63:CF=4");
    ncj->setCookiesFromUrl(QList<QNetworkCookie>() << nc, QUrl("https://scholar.google.com"));
}


/****************************************************************************

  PUBLIC PART

*****************************************************************************/

void network::getFile(const QString& source, const QString& destination, const Action action, QObject* receiver,
                      const char* callback, const bool overwrite)
{
    if (_is_fetching)
    {
        c2bUtils::warn(tr("network::getFile: Requesting network while still fetching previous request. Returned"));
        return;
    }
    setup(source, destination);
    disconnect(this, SIGNAL(requestFinished(bool)), 0, 0);
    if (receiver)
        connect(this, SIGNAL(requestFinished(bool)), receiver, callback);
    if (overwrite)
        if (QFileInfo::exists(destination))
            QFile::remove(destination);
    getFilePrivate(action);
}

void network::headFile(const QString& source, QObject* receiver, const char* callback)
{
    if (_is_fetching)
    {
        c2bUtils::warn(tr("network::headFile: Requesting network while still fetching previous request. Returned"));
        return;
    }
    setup(source);
    disconnect(this, SIGNAL(requestFinished(bool)), 0, 0);
    if (receiver)
        connect(this, SIGNAL(requestFinished(bool)), receiver, callback);
    headFilePrivate();
}

void network::cancelDownload()
{
    if (_is_fetching)
        _current_reply->abort();
}


/****************************************************************************

  PRIVATE PART

*****************************************************************************/

void network::getFilePrivate(const Action action)
{
    if (!checkDestination())
    {
        _emit_request_finished(false);
        return;
    }
    if (_source_filename.startsWith("<<post>>")) // cb2Bib keyword to use post http method
    {
        _source_filename.remove(QRegExp("^<<post>>"));
        _fetch_c2b(action, QNetworkAccessManager::PostOperation);
        return;
    }
    if (FmClient)
        if ((action == Copy && !FmClientCopyBin.isEmpty()) || (action == Move && !FmClientMoveBin.isEmpty()))
        {
            _fetch_client(action);
            return;
        }
    _fetch_c2b(action);
}

void network::headFilePrivate()
{
    const QUrl u(_source_filename, QUrl::TolerantMode);
    if (u.scheme() == "file" || QFileInfo::exists(_source_filename))
    {
        // Local File
        const QString fn(u.scheme() == "file" ? u.toLocalFile() : _source_filename);
        const bool succeeded(QFileInfo::exists(fn));
        if (!succeeded)
            _request_error_string = tr("File does not exist.");
        _emit_request_finished(succeeded);
    }
    else
    {
        // Network File
        _head(u);
    }
}

void network::_emit_request_finished(bool succeeded)
{
    _request_succeeded = succeeded;
    // Give some time to cleanup events and to return all network functions
    // before passing the control to the callback routine
    QTimer::singleShot(50, this, SLOT(_emit_request_finished()));
}

void network::_emit_request_finished()
{
    _is_fetching = false;
    // Assumed events are clean, all functions returned, then make the callback
    emit requestFinished(_request_succeeded);
}

bool network::checkDestination()
{
    // Checks whether or not writing to destination is safe
    // Returns false if file exists
    if (QFileInfo::exists(_destination_filename))
    {
        _request_error_string = tr("Destination file '%1' already exists.").arg(_destination_filename);
        return false;
    }
    else
        return true;
}

void network::loadSettings()
{
    settings* s(settings::instance());
    FmClient = s->value("cb2Bib/FmClient").toBool();
    FmClientCopyBin = s->fileName("cb2Bib/FmClientCopyBin");
    FmClientMoveBin = s->fileName("cb2Bib/FmClientMoveBin");
    FmClientCopyArg = s->value("cb2Bib/FmClientCopyArg").toString();
    FmClientMoveArg = s->value("cb2Bib/FmClientMoveArg").toString();
    QNetworkProxy proxy;
    if (s->value("cb2Bib/UseProxy").toBool())
    {
        const QString hn(s->value("cb2Bib/ProxyHostName", QString()).toString());
        if (!hn.isEmpty())
        {
            if (s->value("cb2Bib/ProxyType").toInt() == 0)
                proxy = QNetworkProxy::HttpProxy;
            else
                proxy = QNetworkProxy::Socks5Proxy;
            proxy.setHostName(hn);
            proxy.setPort(quint16(s->value("cb2Bib/ProxyPort").toInt()));
        }
    }
    _fetcher->setProxy(proxy);
}


/****************************************************************************

  PRIVATE PART: FILEMANAGER CLIENT

*****************************************************************************/

void network::_fetch_client(const Action action)
{
    // Getting NetworkFile through kfmclient
    Action act(action);
    // Only move local files
    QUrl u(_source_filename);
    if (!(u.scheme() == "file" || QFileInfo::exists(_source_filename)))
        if (action == Move)
            act = Copy; // Copy network files

    QStringList arglist;
    QString fmclient_bin;
    if (act == Copy)
    {
        fmclient_bin = FmClientCopyBin;
        arglist = FmClientCopyArg.split(' ', QString::SkipEmptyParts);
    }
    else if (act == Move)
    {
        fmclient_bin = FmClientMoveBin;
        arglist = FmClientMoveArg.split(' ', QString::SkipEmptyParts);
    }
    arglist.append(_source_filename);
    arglist.append(_destination_filename);
    _fetcher_client = new QProcess(this);
    connect(_fetcher_client, SIGNAL(finished(int,QProcess::ExitStatus)), this,
            SLOT(_client_finished(int,QProcess::ExitStatus)));
    _fetcher_client->start(fmclient_bin, arglist);
    if (!_fetcher_client->waitForStarted())
    {
        delete _fetcher_client;
        _request_error_string = tr("FM Client '%1' could not be launched.").arg(fmclient_bin);
        _emit_request_finished(false);
    }
}

void network::_client_finished(int exitCode, QProcess::ExitStatus exitStatus)
{
    bool succeeded(false);
    if (exitStatus == QProcess::CrashExit)
        _request_error_string = tr("FM Client crashed.");
    else
    {
        if (QFileInfo::exists(_destination_filename))
            succeeded = true;
        else
            _request_error_string =
                tr("File '%1' has not been written. Exit code '%2'.").arg(_source_filename).arg(exitCode);
    }
    delete _fetcher_client;
    _emit_request_finished(succeeded);
}


/****************************************************************************

  PRIVATE PART: C2B FETCHER

*****************************************************************************/

void network::_head(const QUrl& url)
{
    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader(
        "User-Agent",
        QString("cb2Bib/" + C2B_VERSION +
                " (https://www.molspaces.com/cb2bib/; mailto:cb2bib@molspaces.com; Bibliographic Browser Tool)")
        .toLatin1());
    _current_reply = _fetcher->head(request);
    connect(_current_reply, SIGNAL(finished()), SLOT(_head_finished()));
}

void network::_head_finished()
{
    if (_redirection_count++ < _max_redirections)
    {
        const QUrl redirection(_current_reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl());
        if (redirection.isValid())
        {
            const QUrl ru(_current_reply->url().resolved(redirection));
            _source_filename = ru.toString();
            _current_reply->deleteLater();
            _head(ru);
            return;
        }
    }
    const bool succeeded(_current_reply->error() == QNetworkReply::NoError);
    if (succeeded)
        _file_mimetype_string = _current_reply->header(QNetworkRequest::ContentTypeHeader).toString();
    else
        _request_error_string = _current_reply->errorString() + '.';
    _current_reply->deleteLater();
    _emit_request_finished(succeeded);
}

void network::_fetch_c2b(const Action action, const QNetworkAccessManager::Operation operation)
{
    _fetch_operation = operation;
    _fetch_url_query.clear();
    QString url_str;
    if (_fetch_operation == QNetworkAccessManager::PostOperation)
    {
        const int qmark(_source_filename.indexOf('?'));
        url_str = _source_filename.mid(0, qmark);
        if (qmark > -1)
        {
            url_str += '/';
            _fetch_url_query = _source_filename.mid(qmark + 1).toUtf8();
        }
    }
    else
        url_str = _source_filename;

    QUrl u(url_str, QUrl::TolerantMode);
    if (u.scheme() == "file" || QFileInfo::exists(_source_filename))
    {
        // Local File
        QFile source(u.scheme() == "file" ? u.toLocalFile() : _source_filename);
        bool succeeded(false);
        if (action == Copy)
            succeeded = source.copy(_destination_filename);
        else if (action == Move)
            succeeded = source.rename(_destination_filename);
        if (!succeeded)
            _request_error_string = source.errorString();
        _emit_request_finished(succeeded);
    }
    else
    {
        // Network File
        _fetch(u);
    }
}

void network::_fetch(const QUrl& url)
{
    _destination_file.setFileName(_destination_filename);
    if (!_destination_file.open(QIODevice::WriteOnly))
    {
        _request_error_string =
            tr("File '%1' cannot be written. %2").arg(_destination_filename, _destination_file.errorString());
        _emit_request_finished(false);
        return;
    }
    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader(
        "User-Agent",
        QString("cb2Bib/" + C2B_VERSION +
                " (https://www.molspaces.com/cb2bib/; mailto:cb2bib@molspaces.com; Bibliographic Browser Tool)")
        .toLatin1());
    if (_fetch_operation == QNetworkAccessManager::PostOperation)
    {
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        _current_reply = _fetcher->post(request, _fetch_url_query);
    }
    else
        _current_reply = _fetcher->get(request);
    connect(_current_reply, SIGNAL(readyRead()), this, SLOT(_fetch_ready_read()));
    connect(_current_reply, SIGNAL(finished()), SLOT(_fetch_finished()));
    connect(_current_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(logError()));
    connect(_current_reply, SIGNAL(downloadProgress(qint64,qint64)), this, SIGNAL(downloadProgress(qint64,qint64)));
}

void network::_fetch_finished()
{
    _destination_file.close();
    if (_current_reply->error() == QNetworkReply::OperationCanceledError)
        _destination_file.remove(); // Delete file
    else if (_redirection_count++ < _max_redirections)
    {
        const QUrl redirection(_current_reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl());
        if (redirection.isValid())
        {
            const QUrl ru(_current_reply->url().resolved(redirection));
            _source_filename = ru.toString();
            const int status(_current_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt());
            if ((status >= 301 && status <= 303) || status == 307)
                _fetch_operation = QNetworkAccessManager::GetOperation;
            _current_reply->deleteLater();
            _fetch(ru);
            return;
        }
    }
    const bool succeeded(_current_reply->error() == QNetworkReply::NoError);
    if (succeeded)
        _file_mimetype_string = _current_reply->header(QNetworkRequest::ContentTypeHeader).toString();
    else
        _request_error_string = _current_reply->errorString() + '.';
    _current_reply->deleteLater();
    _emit_request_finished(succeeded);
}

void network::_fetch_ready_read()
{
    _destination_file.write(_current_reply->readAll());
}

void network::logError()
{
    c2bUtils::warn(tr("network::QNetworkReply log: %1").arg(_current_reply->errorString()));
}
