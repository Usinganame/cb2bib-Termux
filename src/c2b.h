/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2B_H
#define C2B_H

#include "c2bBibParser.h"
#include "c2bNetworkQueryInfo.h"

#include <metadataParser.h>
#include <network.h>

#include <QObject>


class c2bClipboard;

class QProgressDialog;
class QWidget;


class c2b : public QObject
{

    Q_OBJECT

public:
    explicit c2b(QWidget* main, QObject* parento = 0);
    ~c2b();

    // Actions
    static inline const QString documentMetadata(const QString& fn)
    {
        return metaParser()->metadata(fn);
    }

    static inline const QString encodeLink(const QString& ln)
    {
        return netqinf()->encodeLink(ln);
    }

    static inline void showMessage(const QString& message)
    {
        instance()->emitMessage(message);
    }

    static inline void doSearchInFiles(const QString& string, const QString& fn)
    {
        instance()->emitSearchInFiles(string, fn);
    }

    // Pointers
    static inline c2b* instance()
    {
        Q_ASSERT_X(_c2b_single_instance, "c2b", "cb2Bib resources were not instantiated");
        return _c2b_single_instance;
    }

    static inline QWidget* mainWidget()
    {
        return instance()->_c2b_main;
    }

    static inline c2bClipboard* clipboard()
    {
        return instance()->_c2b_clipboard;
    }

    static inline network* net()
    {
        return instance()->_c2b_network;
    }

    static inline c2bNetworkQueryInfo* netqinf()
    {
        return instance()->_c2b_netqinf;
    }

    static inline c2bBibParser* bibParser()
    {
        return instance()->_c2b_bibparser;
    }

    static inline metadataParser* metaParser()
    {
        return instance()->_c2b_metadataparser;
    }


public slots:
    static void configure(int index = -1);
    void exitRequested();


signals:
    void searchInFiles(const QString& string, const QString& fn);
    void statusMessage(const QString& message);


private:
    QProgressDialog* _download_progress;
    QWidget* _c2b_main;
    c2bBibParser* _c2b_bibparser;
    c2bClipboard* _c2b_clipboard;
    c2bNetworkQueryInfo* _c2b_netqinf;
    metadataParser* _c2b_metadataparser;
    network* _c2b_network;
    static c2b* _c2b_single_instance;

    inline void emitMessage(const QString& message)
    {
        emit statusMessage(message);
    }

    inline void emitSearchInFiles(const QString& string, const QString& fn)
    {
        emit searchInFiles(string, fn);
    }


private slots:
    void proxyAuthenticationRequired(const QNetworkProxy& proxy, QAuthenticator* auth);
    void showMessage(const QString& title, const QString& ms);
    void updateDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
};

#endif
