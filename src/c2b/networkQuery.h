/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef NETWORKQUERY_H
#define NETWORKQUERY_H

#include <QDateTime>
#include <QObject>
#include <QRegExp>

class bibParser;
class bibReference;
class network;
class settings;


/**
    cb2Bib Network Queries

    @author Pere Constans
*/
class networkQuery : public QObject
{

    Q_OBJECT

public:
    explicit networkQuery(bibParser* bp, QObject* parento = 0);
    networkQuery(bibParser* bp, network* net, QObject* parento = 0);
    inline virtual ~networkQuery() {}

    void submitQuery(const bibReference& reference, const QString& raw_reference, const bool check_document);
    inline QString errorString() const
    {
        return _error_string;
    }
    inline network* networkPtr() const
    {
        return _networkP;
    }

signals:
    void queryEnded(bool succeeded, const QString& targetPDF, const QString& targetBib);
    void statusMessage(const QString& ms);


protected:
    virtual bool checkQueryFile(const QString& fn) const;
    virtual inline QString fromHtmlString(const QString& str, const bool /* addMetadata */ = false) const
    {
        // Note: fromHtmlString in c2bUtils uses QTextDocument to perform HTML to text
        // conversions. c2bUtils::fromHtmlString is not set in the c2blib because GUI classes
        // are excluded from the core library.
        return str;
    }
    virtual bool openFile(const QString& /* fn */) const
    {
        // Reimplement to open files in GUI mode
        return false;
    }


private:
    QDateTime _timing;
    QList<uint> _query_parameter_count;
    QString _Qauthor;
    QString _Qdoi;
    QString _Qeprint;
    QString _Qexcerpt;
    QString _Qjournal;
    QString _QjournalCode;
    QString _Qpage;
    QString _Qtitle;
    QString _Qvolume;
    QString _action;
    QString _captionQ;
    QString _error_string;
    QString _networkquery_tmp_fn1;
    QString _networkquery_tmp_fn2;
    QString _pdfurl_prefix;
    QString _pdfurl_sufix;
    QString _raw_metadata;
    QString _raw_reference;
    QString _referenceurl_prefix;
    QString _referenceurl_sufix;
    QString _targetBib;
    QString _targetPDF;
    QString _targetQ;
    bibParser* _bpP;
    bool _check_document;
    bool _is_end_of_file;
    bool _pdfurl_is_captured;
    const QString encodeUrl(const QString& url) const;
    network* _networkP;
    settings* _settingsP;
    void init();


private slots:
    bool areQueryParametersValid();
    bool setQueryParameters();
    void queryDone(bool succeeded);
    void submitQuery1();
    void submitQuery2(bool succeeded);
    void submitQuery3(bool succeeded);
    void updateQueryPlaceholders();
};

#endif
