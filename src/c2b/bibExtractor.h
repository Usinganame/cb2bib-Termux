/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef BIBEXTRACTOR_H
#define BIBEXTRACTOR_H

#include <QObject>


class bibParser;
class metadataParser;
class networkQuery;
class settings;

class QEventLoop;
class QTextStream;


/**
    Wrapper class for handling the whole bibliographic extraction/recognition
    process.
*/
class bibExtractor : public QObject
{

    Q_OBJECT

public:
    explicit bibExtractor(QObject* parento = 0);
    bibExtractor(bibParser* bp, metadataParser* mp, networkQuery* nq, QObject* parento = 0);
    ~bibExtractor();

    enum InputType
    {
        PlainText,
        Document
    };

    int extract(const QString& text, QString* bibtex);
    int extract(const QStringList& input_fns, const QString& output_fn, const InputType& type);


private:
    InputType _input_type;
    QEventLoop* _event_loop;
    QString _document_fn;
    QString documentToString(const QString& fn) const;
    QTextStream& cout;
    bibParser* _bpP;
    bool _is_copymove_ok;
    bool isReliable() const;
    metadataParser* _mpP;
    networkQuery* _networkQP;
    settings* _settingsP;
    void _extract(const QString& text);
    void extract(const QString& text);
    void init();


private slots:
    void copyMoveEnded(bool ok);
    void logMessage(const QString& ms) const;
    void proxyLogMessage() const;
    void queryEnded(bool succeeded, const QString& targetPDF, const QString& targetBib);
};

#endif
