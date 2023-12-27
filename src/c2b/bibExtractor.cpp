/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "bibExtractor.h"

#include "bibParser.h"
#include "cb2bib_utilities.h"
#include "document.h"
#include "metadataParser.h"
#include "network.h"
#include "networkQuery.h"
#include "settings.h"

#include <QEventLoop>


bibExtractor::bibExtractor(QObject* parento) : QObject(parento), cout(*(new QTextStream(stdout)))
{
    _settingsP = settings::instance();
    _bpP = new bibParser(this);
    _mpP = new metadataParser(_bpP, this);
    _networkQP = new networkQuery(_bpP, this);
    init();
}

bibExtractor::bibExtractor(bibParser* bp, metadataParser* mp, networkQuery* nq, QObject* parento)
    : QObject(parento), cout(*(new QTextStream(stdout))), _bpP(bp), _mpP(mp), _networkQP(nq)
{
    _settingsP = settings::instance();
    Q_ASSERT_X(_bpP, "bibExtractor", "bibParser was not instantiated");
    Q_ASSERT_X(_networkQP, "bibExtractor", "networkQuery was not instantiated");
    init();
}

bibExtractor::~bibExtractor()
{
    delete &cout;
}


void bibExtractor::init()
{
    connect(_networkQP, SIGNAL(queryEnded(bool,QString,QString)), this, SLOT(queryEnded(bool,QString,QString)),
            Qt::QueuedConnection);
    connect(_networkQP->networkPtr(), SIGNAL(proxyAuthenticationRequired(QNetworkProxy,QAuthenticator*)), this,
            SLOT(proxyLogMessage()));
    _event_loop = new QEventLoop(this);
}

/**
    Extracts a bibliographic reference from files input_fns and writes it to the
    BibTeX file output_fn
*/
int bibExtractor::extract(const QStringList& input_fns, const QString& output_fn, const InputType& type)
{
    _input_type = type;
    QString bibtex;
    for (int i = 0; i < input_fns.count(); ++i)
    {
        const QString& input_fn = input_fns.at(i);
        if (!QFileInfo::exists(input_fn))
        {
            logMessage(tr("Error: File %1 does not exist.").arg(input_fn));
            continue;
        }
        logMessage(tr("Processing %1...").arg(input_fn));
        if (_input_type == Document)
        {
            _document_fn = input_fn;
            const QString text(documentToString(input_fn));
            extract(text);
        }
        else
        {
            _document_fn.clear();
            const QString text(c2bUtils::fileToString(input_fn));
            extract(text);
        }
        if (_settingsP->value("cb2Bib/MovePdf").toBool() && !_document_fn.isEmpty() && isReliable())
        {
            const QString file(_bpP->documentFilename(_document_fn, output_fn));
            const QString target_doc_fn(
                c2bUtils::documentAbsoluteName(_settingsP->value("cb2Bib/RelativePdfDirectory").toBool(), output_fn,
                                               _settingsP->fileName("cb2Bib/PdfDirectory"), file));
            const QString doc_dirname(QFileInfo(target_doc_fn).absolutePath());
            QDir doc_dir(doc_dirname);
            if (!doc_dir.exists())
                if (!doc_dir.mkpath(doc_dirname))
                    logMessage(tr("Error: Unable to create directory %1.").arg(doc_dirname));
            if (doc_dir.exists())
            {
                const network::Action action(network::actionType(_settingsP->value("cb2Bib/CopyMovePdf").toString()));
                logMessage(tr("Copying/moving to %1...").arg(target_doc_fn));
                _networkQP->networkPtr()->getFile(_document_fn, target_doc_fn, action, this, SLOT(copyMoveEnded(bool)));
                _event_loop->exec();
                if (_is_copymove_ok)
                {
                    if (_settingsP->value("cb2Bib/InsertMetadata").toBool())
                    {
                        QString mp_error;
                        if (!_mpP->insertMetadata(_bpP->currentReference(), target_doc_fn, &mp_error))
                        {
                            logMessage(tr("Warning: Unable to insert metadata to file %1.").arg(target_doc_fn));
                            logMessage(mp_error);
                        }
                    }
                    _document_fn = file;
                }
                else
                {
                    if (_settingsP->cl_sloppy)
                    {
                        logMessage(tr("Warning: Skipping file field %1.").arg(_document_fn));
                        _document_fn.clear();
                    }
                    else
                        _bpP->clearCurrentReference();
                }
            }
        }
        if (isReliable())
        {
            if (!_document_fn.isEmpty())
                _bpP->setField("file", _document_fn);
            bibtex += _bpP->toBibTeX();
        }
        else
            logMessage(tr("Warning: Skip writing reference for file %1.").arg(input_fn));
        logMessage(QString());
    }
    if (bibtex.isEmpty())
        logMessage(tr("Warning: No reference extracted."));
    else
    {
        logMessage(tr("Writing %1...").arg(output_fn));
        if (c2bUtils::stringToFile(bibtex, output_fn))
            return 0;
        else
            logMessage(tr("Error: Unable to write file %1.").arg(output_fn));
    }
    return 1;
}

/**
    Extracts a bibliographic reference from input string text writes it to the
    output string bibtex
*/
int bibExtractor::extract(const QString& text, QString* bibtex)
{
    _document_fn.clear();
    _input_type = PlainText;
    extract(text);
    *bibtex = _bpP->toBibTeX();
    if (_bpP->isAutoRecognized())
        return 0;
    else if (_bpP->fieldCount() > 0)
        return 1;
    else
        return 2;
}

void bibExtractor::extract(const QString& text)
{
    _extract(text);
    if (_settingsP->value("cb2Bib/AutomaticQuery").toBool())
        if (!_bpP->autoRecognizedString().contains("BibTeX") && _bpP->fieldCount() > 0)
        {
            logMessage(tr("Submitting query..."));
            _settingsP->setValue("networkQuery/isSupervised", false);
            _networkQP->submitQuery(_bpP->currentReference(), text, _input_type == PlainText);
            _event_loop->exec();
            _settingsP->setValue("networkQuery/isSupervised", true);
        }
    _bpP->setCiteID();
}

void bibExtractor::_extract(const QString& text)
{
    _bpP->clearCurrentReference();
    _bpP->setReferenceType("unknown");
    if (text.trimmed().isEmpty())
    {
        logMessage(tr("Warning: Empty input string."));
        return;
    }
    QString out_text, out_tagtext;
    if (_settingsP->value("cb2Bib/PreparserAutomatic").toBool())
        _bpP->preparse(text, &out_text);
    _bpP->parse(text, &out_text, &out_tagtext);
    if (_bpP->fieldCount() > 0)
        _bpP->setReferenceType("article");
    logMessage(_bpP->autoRecognizedString());
}

void bibExtractor::queryEnded(bool succeeded, const QString& targetPDF, const QString& targetBib)
{
    if (succeeded)
    {
        _extract(targetBib);
        if (_input_type == PlainText && _bpP->isAutoRecognized() && !targetPDF.isEmpty())
            _document_fn = targetPDF;
    }
    _event_loop->exit();
}

void bibExtractor::copyMoveEnded(bool ok)
{
    _is_copymove_ok = ok;
    if (!_is_copymove_ok)
        logMessage(tr("Error: Copy/move failed. %1").arg(_networkQP->networkPtr()->errorString()));
    _event_loop->exit();
}

void bibExtractor::proxyLogMessage() const
{
    _networkQP->networkPtr()->cancelDownload();
    logMessage(tr("Warning: Proxy authentication dialog is disabled in command line mode."));
}

void bibExtractor::logMessage(const QString& ms) const
{
    cout << "[cb2bib] " << ms << endl;
}

bool bibExtractor::isReliable() const
{
    if (_settingsP->cl_sloppy)
        return true;
    else
        return _bpP->isAutoRecognized();
}

QString bibExtractor::documentToString(const QString& fn) const
{
    document doc(fn, document::FirstPage);
    const QString text(doc.toString());
    if (!doc.errorString().isEmpty())
        logMessage("Error: " + doc.errorString());
    if (_settingsP->value("cb2Bib/AddMetadata").toBool())
    {
        // Add metadata to document text
        const QString metadata(_mpP->metadata(fn));
        if (_settingsP->value("cb2Bib/PreAppendMetadata").toString() == "prepend")
            return metadata + text;
        else
            return text + '\n' + metadata;
    }
    else
        return text;
}
