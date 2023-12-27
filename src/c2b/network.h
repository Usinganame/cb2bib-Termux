/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef NETWORK_H
#define NETWORK_H

#include <QFile>
#include <QNetworkAccessManager>
#include <QObject>
#include <QProcess>
#include <QUrl>


/**
    cb2Bib Network file copy/move

    @author Pere Constans
*/
class network : public QObject
{

    Q_OBJECT

public:
    explicit network(QObject* parento = 0);
    inline ~network() {}

    enum Action
    {
        Copy,
        Move
    };

    void getFile(const QString& source, const QString& destination, const Action action = Copy, QObject* receiver = 0,
                 const char* callback = 0, const bool overwrite = false);
    void headFile(const QString& source, QObject* receiver = 0, const char* callback = 0);

    inline const QString destinationFilename() const
    {
        return _destination_filename;
    }

    inline const QString sourceFilename() const
    {
        return _source_filename;
    }

    inline const QString errorString() const
    {
        return _request_error_string;
    }

    inline const QString mimetypeString() const
    {
        return _file_mimetype_string;
    }

    static inline Action actionType(const QString& action)
    {
        return action == "move" ? Move : Copy;
    }


signals:
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void proxyAuthenticationRequired(const QNetworkProxy& proxy, QAuthenticator* auth);
    void requestFinished(bool succeeded);


public slots:
    void cancelDownload();


private:
    QByteArray _fetch_url_query;
    QFile _destination_file;
    QNetworkAccessManager* _fetcher;
    QNetworkAccessManager::Operation _fetch_operation;
    QNetworkReply* _current_reply;
    QProcess* _fetcher_client;
    QString FmClientCopyArg;
    QString FmClientCopyBin;
    QString FmClientMoveArg;
    QString FmClientMoveBin;
    QString _destination_filename;
    QString _file_mimetype_string;
    QString _request_error_string;
    QString _source_filename;
    bool FmClient;
    bool _is_fetching;
    bool _request_succeeded;
    bool checkDestination();
    const int _max_redirections;
    int _redirection_count;
    void _emit_request_finished(bool succeeded);
    void _fetch(const QUrl& url);
    void _fetch_c2b(const Action action,
                    const QNetworkAccessManager::Operation operation = QNetworkAccessManager::GetOperation);
    void _fetch_client(const Action action);
    void _head(const QUrl& url);
    void getFilePrivate(const Action action);
    void headFilePrivate();

    inline void setup(const QString& source, const QString& destination = QString())
    {
        _destination_filename = destination;
        _source_filename = source;
        _file_mimetype_string.clear();
        _request_error_string.clear();
        _is_fetching = true;
        _redirection_count = 0;
    }


private slots:
    void _client_finished(int exitCode, QProcess::ExitStatus exitStatus);
    void _emit_request_finished();
    void _fetch_finished();
    void _fetch_ready_read();
    void _head_finished();
    void loadSettings();
    void logError();
};

#endif
