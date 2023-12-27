/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "bibParser.h"

#include "arxivXml.h"
#include "bibPreparser.h"
#include "crJson.h"
#include "document.h"
#include "heuristicBibParser.h"
#include "idMaker.h"
#include "preprocess.h"
#include "pubmedXml.h"
#include "settings.h"

#include <QCoreApplication>
#include <QUrl>


bibParser::bibParser(QObject* parento) : coreBibParser(parento)
{
    // Creating journal name database
    _journal_dbP = new journalDB(_settingsP->fileName("cb2Bib/JournalFile"));

    // Creating month list
    _month_dbP = new monthDB();

    // Creating cite and document ID makers
    _cite_idmP = new idMaker("cb2Bib/CiteIdPattern", this);
    _file_idmP = new idMaker("cb2Bib/DocumentIdPattern", this);

    // Creating (external) reference preparser
    _preparserP = new bibPreparser(this);
    connect(_preparserP, SIGNAL(statusMessage(QString)), this, SIGNAL(statusMessage(QString)));

    // Creating stream preprocess object
    _preprocessP = new preprocess(this);

    // Creating heuristic bibliographic parser
    _heuristic_parserP = new heuristicBibParser(this);
}

bibParser::~bibParser()
{
    delete _journal_dbP;
    delete _month_dbP;
    delete _heuristic_parserP;
}

/**
    Process each field and set its final format
*/
QString bibParser::parse(const QString& field, const QString& value, const QString& init_value)
{
    QString v(value);
    if (field == QLatin1String("file"))
        return v.trimmed();
    if (field == "abstract")
        document::normalize(v, document::Complete);
    v = removeTags(v);
    if (v.isEmpty())
        return v;
    c2bUtils::fullBibToC2b(v);
    if (field == QLatin1String("author"))
    {
        c2bUtils::debug(v);
        v = _authorString.toBibTeX(v, _settingsP->value("cb2Bib/UseFullNames").toBool());
    }
    else if (field == QLatin1String("addauthors"))
    {
        c2bUtils::debug(v);
        if (init_value.isEmpty())
            v = _authorString.toBibTeX(v, _settingsP->value("cb2Bib/UseFullNames").toBool());
        else
            v = init_value + " and " + _authorString.toBibTeX(v, _settingsP->value("cb2Bib/UseFullNames").toBool());
    }
    else if (field == QLatin1String("editor"))
    {
        c2bUtils::debug(v);
        v.remove(QRegExp("\\((Editor|Editors|Ed|Eds)\\.{0,1}\\)", Qt::CaseInsensitive));
        v = _authorString.toBibTeX(v, _settingsP->value("cb2Bib/UseFullNames").toBool());
    }
    else if (field == QLatin1String("addeditors"))
    {
        c2bUtils::debug(v);
        v.remove(QRegExp("\\((Editor|Editors|Ed|Eds)\\.{0,1}\\)", Qt::CaseInsensitive));
        if (init_value.isEmpty())
            v = _authorString.toBibTeX(v, _settingsP->value("cb2Bib/UseFullNames").toBool());
        else
            v = init_value + " and " + _authorString.toBibTeX(v, _settingsP->value("cb2Bib/UseFullNames").toBool());
    }
    else if (field == QLatin1String("doi"))
    {
        v.remove(QRegExp("^.+(?=10\\.[\\d\\.]+/\\S+)"));
        if (v.endsWith(QLatin1Char('.')) || v.endsWith(QLatin1Char(',')) || v.endsWith(QLatin1Char(';')))
            v.chop(1);
    }
    else if (field == QLatin1String("url"))
    {
        // Remove redundant DOI URLs
        if (v.contains("doi.org/10."))
            v.clear();
    }
    else if (field == QLatin1String("isbn"))
        v.remove(' ');
    else if (field == QLatin1String("journal"))
    {
        if (_settingsP->value("cb2Bib/SetJournalsToFullname").toBool())
            v = fullJournal(v);
        else
            v = abbreviatedJournal(v);
    }
    else if (field == QLatin1String("keywords"))
    {
        v.replace(" - ", ",");
        QStringList kl(v.split(QRegExp("[^\\w\\s-']"), QString::SkipEmptyParts));
        kl.removeAll(" ");
        kl.removeDuplicates();
        v = kl.join(", ");
        v.replace(QRegExp("\\s+,"), ",");
        v = v.toLower();
    }
    else if (field == QLatin1String("month"))
        v = _month_dbP->retrieve(v);
    // Fields edition and note require first letter capitalization
    else if (field == QLatin1String("edition"))
        v = c2bUtils::setCapitalization(v);
    else if (field == QLatin1String("note"))
        v = c2bUtils::setCapitalization(v);
    // Process pages, volume, number, and year to set hyphenation
    else if (field == QLatin1String("pages"))
        v = adjacentNumbers(v);
    else if (field == QLatin1String("volume"))
        v = adjacentNumbers(v);
    else if (field == QLatin1String("number"))
        v = adjacentNumbers(v);
    else if (field == QLatin1String("year"))
        v = adjacentNumbers(v);
    else if (field == QLatin1String("title") || field == QLatin1String("booktitle"))
        v = c2bUtils::setCapitalization(v);
    else if (field == QLatin1String("addtitle"))
    {
        if (!init_value.isEmpty())
            v = init_value + QLatin1String(": ") + v;
        v = c2bUtils::setCapitalization(v);
    }
    return c2bUtils::simplifyString(v);
}

/**
    Process each field and set its final format for a complete reference
*/
bibReference& bibParser::parse(bibReference& reference)
{
    QMutableHashIterator<QString, QString> i(reference);
    while (i.hasNext())
    {
        i.next();
        const QString v(parse(i.key(), i.value()));
        i.setValue(v);
    }
    return reference;
}

QString bibParser::setJournalsToFull(const QString& text, const bool alternate)
{
    const bool ConvertReferenceToLaTeX(_settingsP->value("cb2Bib/ConvertReferenceToLaTeX").toBool());
    QString substituted_text(text);
    QRegExp jnre("\\bjournal\\s*=\\s*[\\{\"]", Qt::CaseInsensitive);
    QString jn;
    int pos(0);
    uint nj(0);
    while (pos >= 0)
    {
        pos = jnre.indexIn(substituted_text, pos);
        if (pos > 0 && c2bUtils::inBraces(pos + jnre.matchedLength(), substituted_text, &jn))
        {
            const int jnlength(jn.length());
            c2bUtils::bibToC2b(jn);
            jn = alternate ? alternateFullJournal(jn) : fullJournal(jn);
            if (ConvertReferenceToLaTeX)
                c2bUtils::c2bToBib(jn);
            pos += jnre.matchedLength();
            substituted_text.replace(pos, jnlength, jn);
            nj++;
        }
        else if (pos >= 0)
            ++pos;
    }
    emit statusMessage(tr("Processed %1 journal names.").arg(nj));
    return substituted_text;
}

QString bibParser::setJournalsToAbbreviated(const QString& text, const bool alternate)
{
    const bool ConvertReferenceToLaTeX(_settingsP->value("cb2Bib/ConvertReferenceToLaTeX").toBool());
    QString substituted_text(text);
    QRegExp jnre("\\bjournal\\s*=\\s*[\\{\"]", Qt::CaseInsensitive);
    QString jn;
    int pos(0);
    uint nj(0);
    while (pos >= 0)
    {
        pos = jnre.indexIn(substituted_text, pos);
        if (pos > 0 && c2bUtils::inBraces(pos + jnre.matchedLength(), substituted_text, &jn))
        {
            const int jnlength(jn.length());
            c2bUtils::bibToC2b(jn);
            jn = alternate ? alternateAbbreviatedJournal(jn) : abbreviatedJournal(jn);
            if (ConvertReferenceToLaTeX)
                c2bUtils::c2bToBib(jn);
            pos += jnre.matchedLength();
            substituted_text.replace(pos, jnlength, jn);
            nj++;
        }
        else if (pos >= 0)
            ++pos;
    }
    emit statusMessage(tr("Processed %1 journal names.").arg(nj));
    return substituted_text;
}

QString bibParser::excerpt(const QString& text, const QStringList& hints) const
{
    QString txt(removeTags(text));
    txt.replace(QRegExp("\\[Bibliographic Metadata.+/Bibliographic Metadata\\]"), " ");
    txt.replace(QRegExp("(http://|https://|ftp://|www\\.|ftp\\.)(www\\.|ftp\\.){0,1}\\S+"), " ");
    txt.replace(QRegExp("\\b[A-Z]+\\b"), " ");
    txt.replace(QRegExp("\\d"), " ");
    txt.replace(c2bUtils::nonLetter, " ");
    txt.replace(QRegExp("\\b\\w{1,2}\\b"), " ");
    txt.replace(
        QRegExp("\\b(about|and|are|com|for|from|how|into|that|the|their|this|where|with|www)\\b", Qt::CaseInsensitive),
        " ");
    txt.replace(QRegExp("\\b(january|february|march|april|may|june|july|august|september|october|november|december)\\b",
                        Qt::CaseInsensitive),
                " ");
    txt = hints.join(" ") + ' ' + txt;
    txt = c2bUtils::simplifyString(txt);
    const QStringList txtlist(txt.split(' ', QString::SkipEmptyParts));
    QStringList txtlistSimp;
    for (int i = 0; i < std::min(15, txtlist.count()); ++i)
        txtlistSimp.append(txtlist.at(i));
    return txtlistSimp.join(" ");
}

void bibParser::setField(const QString& name, const QString& value)
{
    _current_reference[name] = parse(name, value);
}

void bibParser::setReferenceType(const QString& type)
{
    _current_reference.typeName = type;
}

void bibParser::setCiteID()
{
    _current_reference.citeidName = _cite_idmP->makeID(_current_reference);
}

QString bibParser::documentFilename(const QString& base_fn, const QString& bibtex_fn)
{
    if (base_fn.isEmpty())
        return base_fn;
    if (!_settingsP->value("cb2Bib/MovePdf").toBool())
    {
        const QUrl u(base_fn);
        const QString scheme(u.scheme());
        if (scheme == "file")
            return parse("file", u.toLocalFile());
        else
            return parse("file", base_fn);
    }
    QString filename(_file_idmP->makeID(_current_reference));
    if (filename.isEmpty())
        filename = "no_cite_id";
    QFileInfo fi(base_fn);
    QString docExtension('.' + fi.suffix().toLower());
    // Possible document extensions
    if (!docExtension.contains(QRegExp("^\\.\\w{2,4}$")))
        docExtension = ".pdf"; // Default
    if (docExtension == ".gz")
        if (fi.completeSuffix().toLower() == ".ps.gz")
            docExtension = ".ps.gz"; // Composite extension
    filename = c2bUtils::documentFilename(_settingsP->value("cb2Bib/RelativePdfDirectory").toBool(), bibtex_fn,
                                          _settingsP->fileName("cb2Bib/PdfDirectory"), filename + docExtension);
    return parse("file", filename);
}


/****************************************************************************

AUTOMATIC BIB CAPTION

*****************************************************************************/

void bibParser::preparse(const QString& text, QString* out_text)
{
    _preparserP->preparse(text, out_text);
}

/** \page clipboard Extracting Data from the Clipboard

    Clipboard contents is processed according to the following rules:

    - Perform external, user-defined preparsing on input stream. See \ref c2bconf_clipboard.

    - Perform user-defined substitutions on input stream. See \ref c2bconf_clipboard.

    - Check if input stream is already a BibTeX entry. If so, process entry.

    - Check if input stream is, in this order of preference, a PubMed XML,
    arXiv XML, CR JSON, or Medline entry. If so, process entry.

    - Preprocess author names: PI JOAN III -> Pi III, J.
    (care of name prefixes, suffixes, and removal of ambiguities).


    If otherwise,

    - Extract DOI \n (DOI, URL and FILE/PDF are preprocessed, performed before
    the automatic recognition takes place.)

    - Extract URL

    - Remove leading and trailing white spaces, TABs and CRs.

    - "\r\n", "\n" and/or "\r" replaced by the line indicator tag <code><NewLineN></code>.

    - Replace "\t" and ten or more consecutive "\s" by the tabular tag <code><TabN></code>.

    - Simplify white spaces

    - Start the automatic recognition engine.


    If the automatic recognition engine fails, optionally, a heuristic guessing
    will be performed.


    See also \ref heuristics and \ref metadata.

*/
void bibParser::parse(const QString& text, QString* out_text, QString* out_tagtext)
{
    QString& otext = *out_text;
    otext = text;
    QString& ottext = *out_tagtext;
    ottext.clear();
    _preprocessP->preprocessText(out_text);

    if (hasBibTeX(otext))
    {
        _current_reference = wholeReference(otext);
        parse(_current_reference);
        currentReferenceUpdated();
        _auto_recognized_string = tr("Processed as 'BibTeX'.");
        _auto_recognized = true;
        emit statusMessage(_auto_recognized_string);
        return;
    }

    const QString pubmed_identifier("<PubmedArticle>");
    if (otext.contains(pubmed_identifier))
    {
        pubmedXml pxml(metadataSection(otext, pubmed_identifier));
        if (pxml.hasError())
        {
            _auto_recognized_string = tr("Error parsing 'PubMed XML': %1.").arg(pxml.errorString());
            _auto_recognized = false;
        }
        else
        {
            _current_reference = pxml.reference();
            parse(_current_reference);
            currentReferenceUpdated();
            _auto_recognized_string = tr("Processed as 'PubMed XML'.");
            _auto_recognized = true;
        }
        emit statusMessage(_auto_recognized_string);
        return;
    }

    const QString arxiv_identifier("arxiv.org/api/");
    const QString cr_identifier("{\"status\":\"ok\",\"message-type\":\"work\"");
    if (otext.contains(arxiv_identifier) || otext.contains(cr_identifier))
    {
        if (otext.contains(cr_identifier))
        {
            crJson crjson(metadataSection(otext, cr_identifier));
            if (crjson.hasError())
            {
                _auto_recognized_string = tr("Error parsing 'CR JSON': %1.").arg(crjson.errorString());
                _auto_recognized = false;
                emit statusMessage(_auto_recognized_string);
                return;
            }
            else
            {
                _current_reference = crjson.reference();
                _auto_recognized_string = tr("Processed as 'CR JSON'.");
            }
        }
        if (otext.contains(arxiv_identifier))
        {
            arxivXml axml(metadataSection(otext, arxiv_identifier));
            if (axml.hasError())
            {
                _auto_recognized_string = tr("Error parsing 'arXiv XML': %1.").arg(axml.errorString());
                _auto_recognized = false;
                if (_current_reference.size() > 0)
                    _current_reference.clearReference();
                emit statusMessage(_auto_recognized_string);
                return;
            }
            else
            {
                if (_current_reference.size() == 0)
                {
                    _current_reference = axml.reference();
                    _auto_recognized_string = tr("Processed as 'arXiv XML'.");
                }
                else
                {
                    // Merging arXiv and CR metadata
                    const bibReference& areference(axml.reference());
                    if (!areference.value("abstract").isEmpty())
                        _current_reference["abstract"] = areference.value("abstract");
                    if (!areference.value("title").isEmpty())
                        _current_reference["title"] = areference.value("title");
                    if (!areference.value("eprint").isEmpty())
                        _current_reference["eprint"] = areference.value("eprint");
                    if (!areference.value("url").isEmpty())
                        _current_reference["url"] = areference.value("url");
                    _auto_recognized_string = tr("Processed as merged 'arXiv XML' and 'CR JSON'.");
                }
            }
        }
        parse(_current_reference);
        currentReferenceUpdated();
        _auto_recognized = true;
        emit statusMessage(_auto_recognized_string);
        return;
    }

    if (otext.contains(QRegExp("^\\s*PMID\\s*-")))
    {
        _current_reference.typeName = "article";
        otext = ' ' + otext;
        ottext = otext;
        // http://www.nlm.nih.gov/bsd/mms/medlineelements.html
        ottext.replace(QRegExp("[\\n\\r]\\s*([A-Z]{2,4}\\s*-)"), "][\\1"); // Two to four capital letter in field tags
        ottext = c2bUtils::simplifyString(ottext);
        if (!ottext.contains(QRegExp("\\[FAU\\s+-")))
            ottext.replace(QRegExp("\\[(AU\\s*-\\s*[-'\\w]+)"), "[F\\1 ");
        QStringList fList(ottext.split("]["));
        QString kw;
        QRegExp fld("^([A-Z]{2,4})\\s{0,1}-\\s*(.+)$");
        fld.setPatternSyntax(QRegExp::RegExp2);
        for (QStringList::Iterator it = fList.begin(); it != fList.end(); ++it)
        {
            if (fld.indexIn(*it) == -1)
                continue;
            const QString tag(fld.cap(1));
            QString value(fld.cap(2));
            if (tag == "AB")
                _current_reference["abstract"] = parse("abstract", value);
            else if (tag == "FAU")
                _current_reference["author"] =
                    parse("addauthors", authorFromMedline(value), _current_reference.value("author"));
            else if (tag == "TA")
                _current_reference["journal"] = parse("journal", value);
            else if (tag == "IP")
                _current_reference["number"] = parse("number", value);
            else if (tag == "PG")
                _current_reference["pages"] = parse("pages", value);
            else if (tag == "TI")
                _current_reference["title"] = parse("title", value);
            else if (tag == "PMID")
                _current_reference["url"] = parse("url", c2bUtils::pubmedUrl.arg(value));
            else if (tag == "VI")
                _current_reference["volume"] = parse("volume", value);
            else if (tag == "AID")
            {
                if (value.contains("[doi]"))
                    _current_reference["doi"] = parse("doi", value.remove("[doi]"));
            }
            else if (tag == "DP")
                _current_reference["year"] = parse("year", value.replace(QRegExp("^([\\d\\s]+).*$"), "\\1"));
            else if (tag == "MH")
                kw += "; " + value.trimmed();
        }
        if (!kw.isEmpty())
            _current_reference["keywords"] = parse("keywords", kw.remove(0, 2));
        currentReferenceUpdated();
        _auto_recognized_string = tr("Processed as 'PubMed - Medline Journals'.");
        _auto_recognized = true;
        emit statusMessage(_auto_recognized_string);
        return;
    }

    _heuristic_parserP->heuristicFields(otext);

    // Set tags and start regular expression extraction
    ottext = setTags(otext);
    QString regular_expression_f(_settingsP->fileName("cb2Bib/RegularExpressionFile"));
    checkRegExpFile(regular_expression_f);
    QFile file(regular_expression_f);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString ItemX;
    QString line;
    QString reftype;
    QString fieldset;
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    stream.setAutoDetectUnicode(true);
    int nfilters(0);

    while (!stream.atEnd())
    {
        line = stream.readLine();
        if (!(line.isEmpty() || line.contains(QRegExp("^#"))))
        {
            reftype = stream.readLine();
            fieldset = stream.readLine();
            ItemX = stream.readLine();

            c2bUtils::debug(tr("The RegExp file contains1: |%1|").arg(line));
            c2bUtils::debug(tr("The RegExp file contains2: |%1|").arg(reftype));
            c2bUtils::debug(tr("The RegExp file contains3: |%1|").arg(fieldset));
            c2bUtils::debug(tr("The RegExp file contains4: |%1|").arg(ItemX));

            QRegExp rx(ItemX);
            rx.setMinimal(true);
            if (!rx.isValid())
                c2bUtils::warn(tr("RegExp |%1| is not valid").arg(ItemX));

            const QStringList list(fieldset.split(' ', QString::SkipEmptyParts));
            const int efields(list.count());
            const int cfields(rx.captureCount());
            int npos(rx.indexIn(ottext));
            c2bUtils::debug(tr("Expected Fields: |%1|").arg(efields));
            c2bUtils::debug(tr("Captured Fields: |%1|").arg(cfields));
            c2bUtils::debug(tr("Position: |%1|").arg(npos));
            if (efields != cfields)
            {
                c2bUtils::warn(
                    tr("RegExp |%1| is not valid. Mismatch between expected and actual captures").arg(ItemX));
                npos = -1;
            }
            nfilters++;

            if (npos > -1)
            {
                for (int i = 0; i < cfields; i++)
                {
                    const QString& listi = list.at(i);
                    int ii(i + 1);
                    c2bUtils::debug(QString("Fields in Template %1: |%2|").arg(i).arg(rx.cap(ii)));
                    if (_field_re.indexIn(listi) > -1)
                    {
                        if (listi == "author")
                            // Reminder: "addauthors" requires to init _current_reference["author"]
                            _current_reference[listi] =
                                parse("addauthors", rx.cap(ii), _current_reference.value(listi));
                        else if (listi == "editor")
                            // Reminder: "addeditors" requires to init _current_reference["editor"]
                            _current_reference[listi] =
                                parse("addeditors", rx.cap(ii), _current_reference.value(listi));
                        else if (listi == "title")
                            // Reminder: "addtitle" requires to init _current_reference["title"]
                            _current_reference[listi] = parse("addtitle", rx.cap(ii), _current_reference.value(listi));
                        else
                            _current_reference[listi] = parse(listi, rx.cap(ii));
                    }
                }
                _current_reference.typeName = reftype;
                currentReferenceUpdated();
                _auto_recognized_string = tr("Processed as '%1'.").arg(line);
                _auto_recognized = true;
                emit statusMessage(_auto_recognized_string);
                file.close();
                return;
            }
        }
    }
    file.close();

    // Heuristic Bib Parsing
    if (_settingsP->value("cb2Bib/DoHeuristicGuess").toBool())
    {
        // Sometimes (if user is on tag mode) tag could be on otext. Revert tags here, just in case.
        const QString clean_text(removeTags(ottext));
        _heuristic_parserP->guessFields(clean_text, ottext);
        currentReferenceUpdated();
        _auto_recognized_string =
            tr("Applied %1 filters: No automatic format detection. %2 fields guessed.").arg(nfilters).arg(fieldCount());
    }
    else
        _auto_recognized_string = tr("Applied %1 filters: No automatic format detection.").arg(nfilters);
    emit statusMessage(_auto_recognized_string);
}

void bibParser::checkRegExpFile(const QString& fn)
{
    if (fn.isEmpty())
    {
        c2bUtils::warn(tr("No regular expression file especified"));
        return;
    }
    QFileInfo fi(fn);
    if (!fi.exists() || !fi.isReadable())
    {
        c2bUtils::warn(tr("Could not open regular expression file %1 for reading").arg(fn));
        return;
    }
}

void bibParser::guessFields(const QString& text)
{
    const QString clean_text(text.simplified());
    const QString tagged_text(setTags(text));
    _heuristic_parserP->heuristicFields(clean_text);
    _heuristic_parserP->guessFields(clean_text, tagged_text);
    currentReferenceUpdated();
    _auto_recognized_string = tr("%1 fields guessed.").arg(fieldCount());
    emit statusMessage(_auto_recognized_string);
}

QString bibParser::setTags(const QString& text) const
{
    QString tagged_text(text.trimmed());
    tagged_text.replace(QRegExp("\\r\\n"), "<found_new_line>"); // Windows new line
    tagged_text.replace(QRegExp("\\n"), "<found_new_line>");    // Linux new line, LF
    tagged_text.replace(QRegExp("\\r"), "<found_new_line>");    // OSX new line, CR
    QStringList spText(tagged_text.split("<found_new_line>"));
    int n(spText.count());
    tagged_text.clear();
    for (int i = 0; i < n - 1; i++)
        tagged_text += spText.at(i) + QString("<NewLine%1>").arg(i + 1);
    tagged_text += spText[n - 1];
    spText = tagged_text.split(QRegExp("(\\s{10,}|\\t)"));
    n = spText.count();
    tagged_text.clear();
    for (int i = 0; i < n - 1; i++)
        tagged_text += spText.at(i) + QString("<Tab%1>").arg(i + 1);
    tagged_text += spText[n - 1];
    tagged_text = c2bUtils::simplifyString(tagged_text);
    return tagged_text;
}

QString bibParser::removeTags(const QString& text) const
{
    QString clean(text);
    clean.remove("[[");
    clean.remove("]]");
    clean.replace(QRegExp("<NewLine\\d+>"), " ");
    clean.replace(QRegExp("<Tab\\d+>"), " ");
    clean = c2bUtils::simplifyString(clean);
    return clean;
}

QString bibParser::metadataSection(const QString& text, const QString& identifier) const
{
    const QStringList lines(text.split(QRegExp("[\\r\\n]"), QString::KeepEmptyParts));
    const int nl(lines.count());
    int il(-1);
    int sl(0);
    int el(0);
    for (int l = 0; l < nl; ++l)
        if (lines.at(l).contains(identifier))
        {
            il = l;
            break;
        }
    if (il == -1)
        return QString();
    for (int l = il + 1; l < nl; ++l)
        if (lines.at(l) == "/Raw Metadata]")
        {
            el = l;
            break;
        }
    for (int l = il; l >= 0; --l)
        if (lines.at(l) == "[Raw Metadata")
        {
            sl = l;
            break;
        }
    if (sl == 0 && el == 0)
        return text.trimmed();
    if (sl == 0 || el == 0)
        return QString();
    QString section;
    for (int l = sl + 1; l < el; ++l)
        section += '\n' + lines.at(l);
    return section.trimmed();
}
