/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "networkQuery.h"

#include "bibParser.h"
#include "cb2bib_utilities.h"
#include "network.h"
#include "settings.h"

#include <QTimer>


networkQuery::networkQuery(bibParser* bp, QObject* parento) : QObject(parento), _bpP(bp)
{
    Q_ASSERT_X(_bpP, "networkQuery", "bibParser was not instantiated");
    _networkP = new network(this);
    init();
}

networkQuery::networkQuery(bibParser* bp, network* net, QObject* parento) : QObject(parento), _bpP(bp), _networkP(net)
{
    Q_ASSERT_X(_bpP, "networkQuery", "bibParser was not instantiated");
    Q_ASSERT_X(_networkP, "networkQuery", "network was not instantiated");
    init();
}


void networkQuery::init()
{
    _settingsP = settings::instance();
    _settingsP->setValue("networkQuery/isSupervised", true);
    _networkquery_tmp_fn1 = _settingsP->tempPath() + "/cb2bib_query_tmp_html1_" + _settingsP->applicationPid();
    _networkquery_tmp_fn2 = _settingsP->tempPath() + "/cb2bib_query_tmp_html2_" + _settingsP->applicationPid();
    _timing = QDateTime::currentDateTime();
}

void networkQuery::submitQuery(const bibReference& reference, const QString& raw_reference, const bool check_document)
{
    // Submission Initialization
    _error_string.clear();
    _query_parameter_count.clear();
    _is_end_of_file = false;
    _pdfurl_is_captured = false;
    _check_document = check_document && _settingsP->value("cb2Bib/AutomaticPdfDownload").toBool();

    // Query data
    _Qtitle = reference.value("title");
    _Qjournal = _bpP->fullJournal(reference.value("journal"));
    _Qvolume = reference.value("volume");
    _Qpage = c2bUtils::firstPage(reference.value("pages"));
    _Qdoi = reference.value("doi").trimmed();
    if (!_Qdoi.isEmpty() && !_Qdoi.contains(QRegExp("^10\\.[\\d\\.]+/\\S+$")))
    {
        _Qdoi.clear();
        c2bUtils::warn(tr("Warning: DOI skipped: '%1' is not a valid DOI").arg(_Qdoi));
    }
    _Qauthor = reference.value("author");
    _Qauthor.replace(QRegExp("(?:\\b\\w\\b|\\band\\b|\\W)"), " ");
    _Qauthor = c2bUtils::simplifyString(_Qauthor);
    _Qexcerpt = _bpP->excerpt(raw_reference, QStringList() << _Qdoi << _Qauthor << _Qtitle);
    _Qeprint = reference.value("eprint").trimmed();

    _raw_reference = raw_reference;
    // Remove raw metadata in case user repeats the network query
    _raw_reference.remove(QRegExp("\\n\\[Raw Metadata.+$"));

    if (_timing.msecsTo(QDateTime::currentDateTime()) < 550)
        QTimer::singleShot(550, this, SLOT(submitQuery1()));
    else
        submitQuery1();
}

void networkQuery::submitQuery1()
{
    _raw_metadata.clear();

    // Submission, first step, setting journal codes
    if (!setQueryParameters())
    {
        _error_string = tr("No data for query.");
        emit queryEnded(false, _targetQ, _networkquery_tmp_fn1);
        return;
    }
    if (_is_end_of_file)
    {
        _error_string = tr("Performed %1 queries: No reference found.").arg(_query_parameter_count.count());
        emit queryEnded(false, _targetQ, _networkquery_tmp_fn1);
        return;
    }

    c2bUtils::debug(tr("Query Number = %1").arg(_query_parameter_count.count()));
    c2bUtils::debug(tr("targetQ[%1]").arg(_targetQ));
    c2bUtils::debug(tr("captionQ[%1]").arg(_captionQ));
    c2bUtils::debug(tr("referenceurl_prefix[%1]").arg(_referenceurl_prefix));
    c2bUtils::debug(tr("referenceurl_sufix[%1]").arg(_referenceurl_sufix));
    c2bUtils::debug(tr("pdfurl_prefix[%1]").arg(_pdfurl_prefix));
    c2bUtils::debug(tr("pdfurl_sufix[%1]").arg(_pdfurl_sufix));
    c2bUtils::debug(tr("action[%1]").arg(_action));
    c2bUtils::debug(tr("POST1[%1]").arg(_targetQ));

    if (_action == "browse_query")
    {
        if (openFile(encodeUrl(_targetQ)))
        {
            _error_string = tr("Browsing query.");
            emit queryEnded(true, QString(), QString());
        }
        else
        {
            _error_string = tr("Could not open URL '%1'.").arg(encodeUrl(_targetQ));
            emit queryEnded(false, QString(), QString());
        }
        return;
    }

    _timing = QDateTime::currentDateTime();
    if (_action == "htm2txt_query")
        emit statusMessage(tr("Importing: %1.").arg(_targetQ));
    else
        emit statusMessage(tr("Query: %1.").arg(_targetQ));
    _networkP->getFile(_targetQ, _networkquery_tmp_fn1, network::Copy, this, SLOT(submitQuery2(bool)),
                       !_settingsP->value("cb2Bib/KeepTmpNQFiles").toBool());
}

void networkQuery::submitQuery2(bool succeeded)
{
    // Submission, second part: check query replay and PDF existence
    if (!succeeded)
    {
        _error_string = _networkP->errorString();
        emit statusMessage(tr("Query failed with %1.").arg(_error_string));
        QTimer::singleShot(10, this, SLOT(submitQuery1()));
        return;
    }

    QString lines(c2bUtils::fileToString(_networkquery_tmp_fn1, !_settingsP->value("cb2Bib/KeepTmpNQFiles").toBool()));

    // For the single query cases with no htm2txt_query and referenceurl_prefix use
    // non empty capture_from_query to check for result availability
    QString captured;
    if (!_captionQ.isEmpty())
    {
        QRegExp rx(_captionQ);
        rx.setMinimal(true);
        if (!rx.isValid())
            c2bUtils::warn(tr("Warning: RegExp '%1' is not valid").arg(_captionQ));
        const int ncap(rx.indexIn(lines));
        if (ncap == -1)
        {
            QTimer::singleShot(10, this, SLOT(submitQuery1()));
            return;
        }
        captured = fromHtmlString(rx.cap(1));
        c2bUtils::debug(tr("CAPTURED[%1]").arg(captured));
    }
    if (_action == "htm2txt_query")
    {
        _error_string = tr("Importing query URL.");
        emit queryEnded(true, QString(), fromHtmlString(lines, true));
        return;
    }
    if (_action == "merge_all_metadata")
        _raw_metadata = _raw_reference + c2bUtils::metadatasection.arg(lines.trimmed());
    else if (_action == "merge_referenceurl_metadata")
        _raw_metadata = _raw_reference;
    else
        _raw_metadata = c2bUtils::metadatasection.arg(lines.trimmed());
    if (_referenceurl_prefix.isEmpty() && _pdfurl_prefix.isEmpty())
    {
        _error_string = tr("Importing query URL.");
        emit queryEnded(true, QString(), _raw_metadata);
        return;
    }
    if (captured.isEmpty())
    {
        QTimer::singleShot(10, this, SLOT(submitQuery1()));
        return;
    }
    if (_referenceurl_prefix.isEmpty())
        _targetBib.clear();
    else
        _targetBib = _referenceurl_prefix + captured + _referenceurl_sufix;
    if (_check_document && !_pdfurl_prefix.isEmpty())
    {
        if (_pdfurl_is_captured)
            _targetPDF = _pdfurl_prefix + _pdfurl_sufix;
        else
            _targetPDF = _pdfurl_prefix + captured + _pdfurl_sufix;
        emit statusMessage(tr("Checking: %1").arg(_targetPDF));
        _networkP->headFile(_targetPDF, this, SLOT(submitQuery3(bool)));
    }
    else
        submitQuery3(false);
}

void networkQuery::submitQuery3(bool succeeded)
{
    // Submission, third part: extracting reference location
    if (!succeeded || !_networkP->mimetypeString().contains(QRegExp("\\b(chm|djvu|pdf|ps)\\b")))
        _targetPDF.clear();
    else
        _targetPDF = _networkP->sourceFilename();

    if (_referenceurl_prefix.isEmpty())
    {
        emit queryEnded(true, _targetPDF, _raw_metadata);
        return;
    }

    c2bUtils::debug(tr("POST2[%1]").arg(_targetBib));
    c2bUtils::debug(tr("POST3[%1]").arg(_targetPDF));

    if (_action == "browse_referenceurl")
    {
        if (openFile(encodeUrl(_targetBib)))
        {
            _error_string = tr("Browsing reference.");
            emit queryEnded(true, QString(), QString());
        }
        else
        {
            _error_string = tr("Could not open URL '%1'.").arg(encodeUrl(_targetBib));
            emit queryEnded(false, QString(), QString());
        }
        return;
    }
    if (_action == "htm2txt_referenceurl")
        emit statusMessage(tr("Importing: %1.").arg(_targetBib));
    else
        emit statusMessage(tr("Retrieving: %1.").arg(_targetBib));
    _networkP->getFile(_targetBib, _networkquery_tmp_fn2, network::Copy, this, SLOT(queryDone(bool)),
                       !_settingsP->value("cb2Bib/KeepTmpNQFiles").toBool());
}

void networkQuery::queryDone(bool succeeded)
{
    // Submission Done
    if (!succeeded)
    {
        QTimer::singleShot(10, this, SLOT(submitQuery1()));
        return;
    }
    QString lines(c2bUtils::fileToString(_networkquery_tmp_fn2, !_settingsP->value("cb2Bib/KeepTmpNQFiles").toBool()));
    if (_action == "htm2txt_referenceurl")
    {
        _error_string = tr("Importing reference URL.");
        emit queryEnded(true, _targetPDF, fromHtmlString(lines, true));
        return;
    }
    if (_action == "merge_all_metadata" || _action == "merge_referenceurl_metadata")
        _raw_metadata += c2bUtils::metadatasection.arg(lines.trimmed());
    else
        _raw_metadata = c2bUtils::metadatasection.arg(lines.trimmed());
    emit queryEnded(true, _targetPDF, _raw_metadata);
}

bool networkQuery::setQueryParameters()
{
    if (!checkQueryFile(_settingsP->fileName("cb2Bib/NetworkFile")))
        return false;

    QFile file(_settingsP->fileName("cb2Bib/NetworkFile"));
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    stream.setAutoDetectUnicode(true);
    QRegExp Journal("journal=" + _Qjournal + "\\|");
    QRegExp AnyJournal("journal=\\s*$");
    uint readQueryParams(0);
    _is_end_of_file = false;
    QString line;
    while (!stream.atEnd())
    {
        line = stream.readLine();
        if (line.startsWith("%c2b_stop_parsing"))
            break;
        // Skip comments and blanks
        if (!(line.isEmpty() || line.contains(QRegExp("^#"))))
        {
            if (line.contains(Journal))
            {
                const QStringList lc(line.split('|'));
                if (lc.count() > 1)
                    _QjournalCode = lc.at(1);
                else
                    _QjournalCode.clear();
            }
            else if (line.contains(AnyJournal))
            {
                _QjournalCode = _Qjournal;
                _QjournalCode.replace(" & ", " and "); // Avoid sending '&' to confuse URLs
                _QjournalCode.replace(QRegExp("\\W"), " ");
                _QjournalCode = _QjournalCode.simplified();
                _QjournalCode.replace(" ", "+");
            }
            // Get appropiate parameters for Journal or AnyJournal
            if (line.contains(Journal) || line.contains(AnyJournal))
            {
                // Skip if already performed
                if (!_query_parameter_count.contains(++readQueryParams))
                {
                    while (line.contains(QRegExp("^journal=")))
                        line = stream.readLine();
                    _targetQ = line.remove(QRegExp("^query="));
                    line = stream.readLine();
                    _captionQ = line.remove(QRegExp("^capture_from_query="));
                    line = stream.readLine();
                    _referenceurl_prefix = line.remove(QRegExp("^referenceurl_prefix="));
                    line = stream.readLine();
                    _referenceurl_sufix = line.remove(QRegExp("^referenceurl_sufix="));
                    line = stream.readLine();
                    _pdfurl_prefix = line.remove(QRegExp("^pdfurl_prefix="));
                    line = stream.readLine();
                    _pdfurl_sufix = line.remove(QRegExp("^pdfurl_sufix="));
                    line = stream.readLine();
                    _action = line.remove(QRegExp("^action="));
                    // Setting Query Parameters
                    updateQueryPlaceholders();
                    // Finally, check for unresolved cb2Bib tags
                    if (areQueryParametersValid())
                    {
                        _query_parameter_count.append(readQueryParams);
                        return true;
                    }
                }
            }
        }
    }
    file.close();
    _is_end_of_file = true;
    return (!_query_parameter_count.isEmpty());
}

void networkQuery::updateQueryPlaceholders()
{
    const QString pdfurl_prefix(_pdfurl_prefix);
    if (!_Qtitle.isEmpty())
    {
        _targetQ.replace("<<title>>", _Qtitle);
        _captionQ.replace("<<title>>", _Qtitle);
        _referenceurl_prefix.replace("<<title>>", _Qtitle);
        _referenceurl_sufix.replace("<<title>>", _Qtitle);
        _pdfurl_prefix.replace("<<title>>", _Qtitle);
        _pdfurl_sufix.replace("<<title>>", _Qtitle);
    }
    if (!_QjournalCode.isEmpty())
    {
        _targetQ.replace("<<journal>>", _QjournalCode);
        _captionQ.replace("<<journal>>", _QjournalCode);
        _referenceurl_prefix.replace("<<journal>>", _QjournalCode);
        _referenceurl_sufix.replace("<<journal>>", _QjournalCode);
        _pdfurl_prefix.replace("<<journal>>", _QjournalCode);
        _pdfurl_sufix.replace("<<journal>>", _QjournalCode);
    }
    if (!_Qpage.isEmpty())
    {
        _targetQ.replace("<<pages>>", _Qpage);
        _captionQ.replace("<<pages>>", _Qpage);
        _referenceurl_prefix.replace("<<pages>>", _Qpage);
        _referenceurl_sufix.replace("<<pages>>", _Qpage);
        _pdfurl_prefix.replace("<<pages>>", _Qpage);
        _pdfurl_sufix.replace("<<pages>>", _Qpage);
    }
    if (!_Qvolume.isEmpty())
    {
        _targetQ.replace("<<volume>>", _Qvolume);
        _captionQ.replace("<<volume>>", _Qvolume);
        _referenceurl_prefix.replace("<<volume>>", _Qvolume);
        _referenceurl_sufix.replace("<<volume>>", _Qvolume);
        _pdfurl_prefix.replace("<<volume>>", _Qvolume);
        _pdfurl_sufix.replace("<<volume>>", _Qvolume);
    }
    if (!_Qdoi.isEmpty())
    {
        _targetQ.replace("<<doi>>", _Qdoi);
        _captionQ.replace("<<doi>>", _Qdoi);
        _referenceurl_prefix.replace("<<doi>>", _Qdoi);
        _referenceurl_sufix.replace("<<doi>>", _Qdoi);
        _pdfurl_prefix.replace("<<doi>>", _Qdoi);
        _pdfurl_sufix.replace("<<doi>>", _Qdoi);
    }
    if (!_Qexcerpt.isEmpty())
    {
        _targetQ.replace("<<excerpt>>", _Qexcerpt);
        _captionQ.replace("<<excerpt>>", _Qexcerpt);
        _referenceurl_prefix.replace("<<excerpt>>", _Qexcerpt);
        _referenceurl_sufix.replace("<<excerpt>>", _Qexcerpt);
        _pdfurl_prefix.replace("<<excerpt>>", _Qexcerpt);
        _pdfurl_sufix.replace("<<excerpt>>", _Qexcerpt);
    }
    if (!_Qeprint.isEmpty())
    {
        _targetQ.replace("<<eprint>>", _Qeprint);
        _captionQ.replace("<<eprint>>", QRegExp::escape(_Qeprint));
        _referenceurl_prefix.replace("<<eprint>>", _Qeprint);
        _referenceurl_sufix.replace("<<eprint>>", _Qeprint);
        _pdfurl_prefix.replace("<<eprint>>", _Qeprint);
        _pdfurl_sufix.replace("<<eprint>>", _Qeprint);
    }
    _pdfurl_is_captured = (pdfurl_prefix != _pdfurl_prefix);
}

bool networkQuery::areQueryParametersValid()
{
    if (!_action.isEmpty())
    {
        if (_action == "browse_query" || _action == "browse_referenceurl")
        {
            if (!_settingsP->value("networkQuery/isSupervised").toBool())
                return false;
        }
        else if (!(_action == "htm2txt_query" || _action == "htm2txt_referenceurl" || _action == "merge_all_metadata" ||
                   _action == "merge_referenceurl_metadata"))
            return false;
    }
    const QString allParams(_targetQ + _captionQ + _referenceurl_prefix + _referenceurl_sufix + _pdfurl_prefix +
                            _pdfurl_sufix);
    return !(
               allParams.contains(QRegExp("(?:<<title>>|<<journal>>|<<pages>>|<<volume>>|<<doi>>|<<excerpt>>|<<eprint>>)")));
}

const QString networkQuery::encodeUrl(const QString& url) const
{
    // Removes <<post>> tag if present and encodes URL to percent encoding
    QString encoded_url(url);
    encoded_url.remove(QRegExp("^<<post>>"));
    encoded_url = QUrl::toPercentEncoding(encoded_url, "+:/?=&\\");
    return encoded_url;
}

bool networkQuery::checkQueryFile(const QString& fn) const
{
    if (fn.isEmpty())
    {
        c2bUtils::warn(tr("No network query file especified"));
        return false;
    }
    QFileInfo fi(fn);
    if (!fi.exists() || !fi.isReadable())
    {
        c2bUtils::warn(tr("Could not open network query file %1 for reading").arg(fn));
        return false;
    }
    return true;
}
