/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "bibSearcher.h"

#include "bibParser.h"
#include "settings.h"

#include <QCoreApplication>


/** \page bibsearch Search BibTeX and PDF Document Files

\section descrip Description

  - <b>Search pattern</b> \n Patterns and composite patterns can be either
  \htmlonly
  <a href="https://arxiv.org/abs/0705.0751" target="_blank">approximate strings</a>,
  \endhtmlonly
  strings, contexts, regular expressions, or wildcard filters. Patterns admit
  Unicode characters. The scope of each pattern can be the reference as a whole
  or be focused on a particular reference field. The fields <tt>year</tt>,
  <tt>file</tt>, and <tt>journal</tt> are treated specifically. The field
  <tt>year</tt> has the qualifiers <tt>Exact</tt>, <tt>Newer</tt>, and
  <tt>Older</tt>. The field <tt>file</tt> can optionally refer to either the
  filename or the contents of such a file. Finally, for <tt>journal</tt>, the
  input pattern is duplicated to the, if available, journal fullname, and they
  two are checked against the <tt>journal</tt> actual field contents and, if
  available, its expanded contents. For example, typing 'ijqc' retrieves all
  references with <tt>journal</tt> being 'Int. J. Quantum Chem.'. Or, typing
  'chemistry' retrieves any of 'J. Math. Chem.', 'J. Phys. Chem.', etc. This
  expansion is not performed when the pattern scope is set to <tt>all</tt>.

  - <b>Search scope</b> \n By default, searches are performed on the current
  BibTeX output file. If <b>Scan all BibTeX files</b> is checked the search
  will extend to all BibTeX files, extension .bib, present in the current
  directory. It might be therefore convenient to group all reference files in
  one common directory, or have them linked to that directory. When <b>Scan
  linked documents</b> is checked, and one or more pattern scope is
  <tt>all</tt> or <tt>file</tt>, the contents of the file in <tt>file</tt> is
  converted to text and scanned for that given pattern. See \ref
  c2bconf_utilities section to configure the external to text converter.

  - <b>Search modifier</b> \n
  \htmlonly
  cb2Bib converts TeX encoded characters to Unicode when parsing the
  references. This permits, for instance, for the pattern 'M&#248;ller' to
  retrieve either 'M&#248;ller' or 'M{\o}ller', without regard to how the
  BibTeX reference is written. By checking <b>Simplify source</b>, the
  reference and the converted PDF files are simplified to plain ASCII. In this
  way, the pattern '\bMoller\b' will hit any of 'M&#248;ller', 'M{\o}ller', or
  'Moller'. Additionally, all non-word characters are removed, preserving only
  the ASCII, word structure of the source. Note that source simplification is
  only performed for the patterns whose scope is <tt>all</tt> or <tt>file</tt>
  contents, and that and so far, cb2Bib has only a subset of such conversions.
  Implemented TeX to Unicode conversions can be easily checked by entering a
  reference. The Unicode to ASCII letter-only conversion, on the other hand, is
  the one that cb2Bib also uses to write the reference IDs and, hence, the
  renaming of dropped files. cb2Bib can understand minor sub and superscript
  formatting. For instance, the pattern 'H2O' will retrieve 'H<sub>2</sub>O'
  from a BibTeX string <code>H$_{2}$O</code>.
  \endhtmlonly


\section contextsearch Contextual Search

  A convenient way to retrieve documents is by matching a set of keywords
  appearing in a close proximity context, while disregarding the order in which
  the words might had been written. cb2Bib considers two types of contextual
  searches. One flexibilizes phrase matching only at the level of the
  constituting words. It is accessed by selecting <tt>Fixed string:
  Context</tt> in the pattern type box. The other one, in addition, stems the
  supplied keywords. It is accessed by selecting <tt>Context</tt>. By way of
  stemming, the keyword <i>analyze</i>, for example, will also match
  <i>analyse</i>, and <i>aluminum</i> will match <i>aluminium</i> too.


  The syntax for <tt>Context</tt> type patterns is summarized in the following
  table:

\verbatim


Operator   Example                          Expansion

space      contextual search                contextual AND search

|          contextual search|matching       contextual AND (search|match)

+          contextual search|+matching      contextual AND (search|\bmatching\b)

_          contextual_search                contextual.{0,25}search

-          non-parametric                   non.{0,1}parametr


Diacritics and Greek letters:

           naïve search                     (naïve|naive) AND search

           kendall tau                      kendall AND (tau|τ)


\endverbatim

  In the above examples, operator space <tt>AND</tt> means match words in any
  order. Operator <tt>_</tt> preserves word order, and operator <tt>+</tt>
  prevents stemming and forces exact word match. Operator <tt>-</tt> considers
  cases of words that might had been written either united, hyphenated, or
  space separated. Diacritics are expanded if the diacritic mark is specified.
  This is, <i>naive</i> will not match <i>naïve</i>. On the other hand, Greek
  letters are expanded only when typed by name.




\section notes Notes

  - cb2Bib uses an internal cache to speed up the search of linked files.
    By default data is stored as <tt>current_file.bib.c2b</tt>. It might be
    more convenient, however, to setup a temporary directory out of the user
    data backup directories. See <b>Search In Files Cache Directory</b> in \ref
    c2bconf_files. When a linked file is processed for the first time, cb2Bib
    does several string manipulations, such as removing end of line
    hyphenations. This process is time consuming for very large files.

  - The <b>approximate string</b> search is described in reference
  \htmlonly
  <a href="https://arxiv.org/abs/0705.0751" target="_blank">https://arxiv.org/abs/0705.0751</a>.
  \endhtmlonly
  It reduces the chance of missing a hit due to transcription and decoding
  errors in the document files. Approximate string is also a form of
  serendipitous information retrieval.

*/

/**
    Top level driver for searching BibTeX files
*/
bibSearcher::bibSearcher(bibParser* bp, QObject* parento)
    : QObject(parento), _bpP(bp), _do_rank_results(true), _do_search_similar(false)
{
    clear();
}

/**
    Top level driver for searching BibTeX files. Specialized constructor for
    searching repeated or similar references.
*/
bibSearcher::bibSearcher(bibParser* bp, const QString& bib_dir, QObject* parento)
    : QObject(parento), _bpP(bp), _do_rank_results(false), _do_search_similar(true)
{
    // Retrieve (any_author(context) AND any_title(approximate)) OR citeidName(exact)
    clear();
    setSearchScope(bib_dir, bib_dir, true, false);
    setSimplifySource(false);
    setBoolean(true);
    addPattern(false, false, searchPattern::type(searchPattern::Context), QLatin1String("all"), QChar(),
               _bpP->currentReference().anyAuthor());
    addPattern(false, false, searchPattern::type(searchPattern::ApproximateString), QLatin1String("all"), QChar(),
               _bpP->currentReference().anyTitle());
    _do_search_similar_citeid = _bpP->currentReference().citeidName;
    if (_do_search_similar_citeid.isEmpty())
        _do_search_similar_citeid = QLatin1Char('@');
}

bibSearcher::bibSearcher() : _bpP(0), _do_rank_results(false), _do_search_similar(false)
{
    clear();
}


void bibSearcher::addPattern(bool Not, bool caseSensitive, const QString& patternType, const QString& scope,
                             const QChar& yearScope, const QString& pattern)
{
    if (pattern.trimmed().isEmpty())
        return;
    _patterns.append(searchPattern(Not, caseSensitive, patternType, scope, yearScope, pattern));
    if (!_scopes.contains(scope))
        _scopes.append(scope);
}

void bibSearcher::exec()
{
    if (_patterns.count() == 0 && !_do_search_similar)
        return;
    std::sort(_patterns.begin(), _patterns.end());
    _include_documents =
        _include_documents && (_scopes.contains(QLatin1String("all")) || _scopes.contains(QLatin1String("file")));
    if (_include_documents && !_scopes.contains(QLatin1String("file")))
        _scopes.append(QLatin1String("file"));
    _scopes.removeAll(QLatin1String("all"));

    QString and_or;
    if (_boolean_and)
        and_or = QLatin1String(".AND.");
    else
        and_or = QLatin1String(".OR.");
    for (int i = 0; i < _patterns.count(); ++i)
    {
        const searchPattern& pattern = _patterns.at(i);
        _log_string += tr("% Pattern%1: %2%3\n").arg(i + 1).arg(and_or, pattern.toString());
    }

    // Search In Files
    const QStringList flist(_all_bibtex_files ? c2bUtils::filesInDir(_bibtex_dir, QStringList() << "*.bib")
                            : c2bUtils::filesInDir(_bibtex_file, QStringList() << "*.bib"));
    for (int i = 0; i < flist.count(); ++i)
    {
        search(flist.at(i));
        if (_aborted)
        {
            clear();
            _error_counter = -1;
            return;
        }
    }

    // Search Done
    _log_string += tr("% Scanned References: %1  BibTeX Files: %2  Linked Files: %3\n")
                   .arg(_reference_counter)
                   .arg(_bibtex_counter)
                   .arg(_document_counter);
    if (_include_documents)
        _documents.unload();
    if (_result_references.count() == 0)
        return;
    if (_do_rank_results)
        quadrupleSortDescending(&_result_scores, &_result_references, &_result_html_data, &_result_html_abstracts);
    _result_string = "\n\n" + _result_references.join("\n\n") + "\n\n";
    _log_string += tr("% Total Unique Hits: %1\n").arg(_result_references.count());
#ifdef C2B_DEBUG_SEARCHING
    if (_result_scores.count() > 0)
        qDebug() << "Scores: " << _result_scores;
#endif
}

QString bibSearcher::searchDocumentKeyword(const QString& bibtexfn, const QString& documentfn, const QString& keyword)
{
    bibSearcher bs;
    QString exc;
    bs._documents.load(bibtexfn, documentContents::Complete);
    if (bs._documents.setCurrent(documentfn))
    {
        QString p(keyword);
        p.replace(QRegExp("\\W"), ".{0,5}");
        p.replace("s", ".?");
        p = "\\b" + p + "\\w*\\b";
        bs.addPattern(false, false, searchPattern::type(searchPattern::RegularExpression), QLatin1String("all"),
                      QChar(), p);
        QString document(bs._documents.current().text());
        c2bUtils::stripDiacritics(document);
        if (bs._patterns.at(0).matches(document))
        {
            exc = c2bUtils::fileToString(":/htm/htm/excerpts.html");
            exc.replace("GET_EXCERPTS_TITLE", keyword);
            exc.replace("GET_EXCERPTS", bs.excerpts(document).mid(20));
        }
    }
    bs._documents.unload();
    return exc;
}

void bibSearcher::abort()
{
    _aborted = true;
}

void bibSearcher::clear()
{
    _aborted = false;
    _all_bibtex_files = false;
    _bibtex_counter = 0;
    _bibtex_dir.clear();
    _bibtex_file.clear();
    _boolean_and = true;
    _do_search_similar_citeid.clear();
    _document_counter = 0;
    _error_counter = 0;
    _include_documents = false;
    _log_string = "% cb2Bib " + C2B_VERSION + " / BibTeX Search Log\n";
    _patterns.clear();
    _reference_counter = 0;
    _reference_match_counter = 0;
    _reference_score = double(0);
    _result_html_abstracts.clear();
    _result_html_data.clear();
    _result_references.clear();
    _result_scores.clear();
    _result_string.clear();
    _scopes.clear();
    _simplify_source = false;
}

void bibSearcher::search(const QString& bib_file)
{
    _bibtex_counter++;
    QString bib_file_contents;
    QFile file(bib_file);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        _error_counter++;
        _log_string +=
            tr("% [cb2bib] Unable to open the file %1 for reading. Error: '%2'.\n").arg(bib_file, file.errorString());
        return;
    }
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    stream.setAutoDetectUnicode(true);
    bib_file_contents = stream.readAll();
    _log_string += tr("% Scanning file %1\n").arg(bib_file.trimmed());
    if (_include_documents)
    {
        if (_simplify_source)
            _documents.load(bib_file, documentContents::Simplified);
        else
            _documents.load(bib_file, documentContents::Complete);
    }

    const int hits(_result_references.count());
    bibReference ref;
    _bpP->initReferenceParsing(bib_file, _scopes, &ref);
    while (_bpP->referencesIn(bib_file_contents, &ref))
    {
        _reference_counter++;
        if (_do_search_similar)
            searchSimilarReferences(bib_file, ref);
        else
            searchReference(bib_file, ref);
        QCoreApplication::processEvents();
        if (_aborted)
            return;
    }
    _log_string += tr("% File %1. Hits: %2\n").arg(bib_file.trimmed()).arg(_result_references.count() - hits);
}

void bibSearcher::searchReference(const QString& bib_file, const bibReference& ref)
{
    const bool include_document(
        _include_documents &&
        _documents.setCurrent(ref.value(QLatin1String("file")), &_document_counter, &_log_string, &_error_counter));

    // Initialize composite search
    bool hit(_boolean_and);

    // Composite search
    for (int i = 0; i < _patterns.count(); ++i)
    {
        const searchPattern& pattern(_patterns.at(i));
        const searchPattern::modifiers& modifier(pattern.modifier());
        bool ihit(false);

        if (modifier.scope == QLatin1String("year"))
        {
            int istr(ref.value(modifier.scope).toInt());
            int jstr(modifier.string.toInt());
            if (modifier.yearScope == QLatin1Char('='))
                ihit = istr == jstr;
            else if (modifier.yearScope == QLatin1Char('>'))
                ihit = istr >= jstr;
            else if (modifier.yearScope == QLatin1Char('<'))
                ihit = istr <= jstr;
        }
        else if (modifier.scope == QLatin1String("all"))
        {
            if (_simplify_source)
                ihit = pattern.matches(c2bUtils::toAscii(ref.unicodeReference, c2bUtils::FromBibTeX));
            else
                ihit = pattern.matches(ref.unicodeReference);
            if (!ihit)
                if (include_document)
                    ihit = pattern.matches(_documents.current());
        }
        else if (modifier.scope == QLatin1String("journal"))
        {
            const QString pattern_full(_bpP->fullJournal(modifier.string));
            const QString j_orig(ref.value(modifier.scope));
            const QString j_full(_bpP->fullJournal(j_orig));
            ihit = j_full == pattern_full || pattern.matches(j_orig) || pattern.matches(j_full);
        }
        else if (modifier.scope == QLatin1String("file") && include_document)
            ihit = pattern.matches(_documents.current());
        else
            ihit = pattern.matches(ref.value(modifier.scope));

        if (modifier.NOT)
            ihit = !ihit;
        if (_boolean_and)
        {
            hit = hit && ihit;
            if (!hit)
                break;
        }
        else
        {
            hit = hit || ihit;
            if (hit)
                break;
        }
    }
    if (hit)
        if (!_result_references.contains(ref.rawReference))
        {
            _result_references.append(ref.rawReference);
            _reference_score = double(0);
            _reference_match_counter = 0;
            if (_scopes.contains(QLatin1String("title")))
                setTitleRank(ref.value(QLatin1String("title")));
            else if (_scopes.contains(QLatin1String("booktitle")))
                setTitleRank(ref.value(QLatin1String("booktitle")));
            if (_scopes.contains(QLatin1String("abstract")))
                _result_html_abstracts.append(highlight(ref.value(QLatin1String("abstract"))));
            else
                _result_html_abstracts.append(highlight(_bpP->singleReferenceField(QLatin1String("abstract"), ref)));
            if (include_document)
                _result_html_data.append(location(bib_file, ref) + excerpts(_documents.current().text()));
            else
                _result_html_data.append(location(bib_file, ref));
            _result_scores.append(_reference_score);
#if C2B_DEBUG_SCORER
            _debug_scorer_scores.append(_reference_score);
            _debug_scorer_occurrences.append(_reference_match_counter);
            _debug_scorer_documents.append(_bpP->singleReferenceField(QLatin1String("title"), ref));
#endif
        }
}

void bibSearcher::searchSimilarReferences(const QString& bib_file, const bibReference& ref)
{
    if (ref.citeidName == _do_search_similar_citeid)
    {
        if (!_result_references.contains(ref.rawReference))
        {
            _result_references.append(ref.rawReference);
            _result_html_data.append(location(bib_file, ref));
        }
        return;
    }
    if (_patterns.count() == 0)
        return;

    // Initialize composite search
    bool hit(_boolean_and);

    // Composite search
    for (int i = 0; i < _patterns.count(); ++i)
    {
        const searchPattern& pattern(_patterns.at(i));
        hit = hit && pattern.matches(ref.unicodeReference);
        if (!hit)
            break;
    }
    if (hit)
        if (!_result_references.contains(ref.rawReference))
        {
            _result_references.append(ref.rawReference);
            _result_html_data.append(location(bib_file, ref));
        }
}

void bibSearcher::setTitleRank(const QString& title)
{
    if (!_do_rank_results || title.isEmpty())
        return;
    for (int i = 0; i < _patterns.count(); ++i)
    {
        const searchPattern& pattern(_patterns.at(i));
        const searchPattern::modifiers& modifier(pattern.modifier());
        pattern.initializeScores();
        if (modifier.NOT)
            continue;
        if (modifier.scope != QLatin1String("title") && modifier.scope != QLatin1String("booktitle"))
            continue;
        int pos(0);
        while (pos >= 0)
        {
            pos = pattern.indexIn(title, pos);
            if (pos > -1)
            {
                pattern.updateScore();
                pos += pattern.matchedLength();
            }
        }
        _reference_score += 10 * pattern.matchedScore();
    }
}

QString bibSearcher::excerpts(const QString& contents)
{
    const int max_excerpts(25);
    const int max_unmerged_excerpts(max_excerpts + 100);
    QMap<int, int> exc_endpos;

    for (int i = 0; i < _patterns.count(); ++i)
    {
        const searchPattern& pattern(_patterns.at(i));
        const searchPattern::modifiers& modifier(pattern.modifier());
        pattern.initializeScores();
        if (modifier.NOT)
            continue;
        if (modifier.scope != QLatin1String("all") && modifier.scope != QLatin1String("file"))
            continue;
        int n_excerpts(0);
        int pos(0);
        while (pos >= 0)
        {
            pos = pattern.indexIn(contents, pos);
            if (pos > -1)
            {
                if (++n_excerpts > max_unmerged_excerpts)
                    break;
                if (_do_rank_results)
                    pattern.updateScore();
                exc_endpos.insert(pos, std::max(pos + pattern.matchedLength(), exc_endpos.value(pos)));
                pos += pattern.matchedLength();
            }
        }
        if (_do_rank_results)
        {
            _reference_score += pattern.matchedScore();
            _reference_match_counter = pattern.matchedCounter();
        }
    }
    if (exc_endpos.isEmpty())
        return QString();

    // Merge
    QList<int> i_pos = exc_endpos.keys();
    int pos0(i_pos.at(0));
    for (int i = 1; i < i_pos.count(); ++i)
    {
        const int posi(i_pos.at(i));
        if (exc_endpos.value(pos0) < posi)
            pos0 = posi;
        else
        {
            const int endposi(exc_endpos.value(posi));
            exc_endpos.remove(posi);
            exc_endpos.insert(pos0, endposi);
        }
    }
    i_pos = exc_endpos.keys();

    const int context_length(75);
    QString exc;
    QRegExp lead_truncated_words("^.*\\s(?=\\w)");
    lead_truncated_words.setMinimal(true);
    QRegExp tail_truncated_words("\\W+\\w+\\W*$");
    tail_truncated_words.setMinimal(true);

    bool item_begins(true);
    bool item_complete;
    const int items(std::min(i_pos.count(), max_excerpts));

    for (int i = 0; i < items; ++i)
    {
        const int pos(i_pos.at(i));
        const int length(exc_endpos.value(pos) - pos);
        const QString match(QLatin1String("<span>") + c2bUtils::toHtmlString(contents.mid(pos, length)) +
                            QLatin1String("</span>"));

        if (item_begins)
        {
            QString pre_match(contents.mid(pos - context_length, context_length));
            pre_match.remove(lead_truncated_words);
            pre_match = c2bUtils::toHtmlString(pre_match);
            exc += QLatin1String("&#8226; ...") + pre_match + match;
        }
        else
            exc += match;

        if (i + 1 == items)
            item_complete = true;
        else
            item_complete = exc_endpos.value(pos) + (2 * context_length) < i_pos.at(i + 1);
        if (item_complete)
        {
            QString post_match(contents.mid(pos + length, context_length));
            post_match.remove(tail_truncated_words);
            post_match = c2bUtils::toHtmlString(post_match);
            exc += post_match + "... ";
            item_begins = true;
        }
        else
        {
            exc += contents.midRef(pos + length, i_pos.at(i + 1) - pos - length);
            item_begins = false;
        }
    }

    exc = QLatin1String("</p><p id=\"excerpt\">") + exc;
    if (i_pos.count() >= max_excerpts)
        exc += tr("</p><p><b>Found more than %1 occurrences</b>.").arg(max_excerpts);
    return exc;
}

QString bibSearcher::highlight(const QString& abstract)
{
    if (abstract.isEmpty())
        return abstract;
    QMap<int, int> endpos;
    for (int i = 0; i < _patterns.count(); ++i)
    {
        const searchPattern& pattern(_patterns.at(i));
        const searchPattern::modifiers& modifier(pattern.modifier());
        pattern.initializeScores();
        if (modifier.NOT)
            continue;
        if (modifier.scope != QLatin1String("all") && modifier.scope != QLatin1String("abstract"))
            continue;
        int pos(0);
        while (pos >= 0)
        {
            pos = pattern.indexIn(abstract, pos);
            if (pos > -1)
            {
                if (_do_rank_results)
                    pattern.updateScore();
                endpos.insert(pos, std::max(pos + pattern.matchedLength(), endpos.value(pos)));
                pos += pattern.matchedLength();
            }
        }
        if (_do_rank_results)
        {
            _reference_score += pattern.matchedScore();
            _reference_match_counter = pattern.matchedCounter();
        }
    }
    if (endpos.isEmpty())
        return c2bUtils::toHtmlString(abstract);

    // Merge
    QList<int> i_pos = endpos.keys();
    int pos0(i_pos.at(0));
    for (int i = 1; i < i_pos.count(); ++i)
    {
        const int posi(i_pos.at(i));
        if (endpos.value(pos0) < posi)
            pos0 = posi;
        else
        {
            const int endposi(endpos.value(posi));
            endpos.remove(posi);
            endpos.insert(pos0, endposi);
        }
    }
    i_pos = endpos.keys();

    QString hla;
    int npos(0);
    for (int i = 0; i < i_pos.count(); ++i)
    {
        const int pos(i_pos.at(i));
        const int length(endpos.value(pos) - pos);
        hla += c2bUtils::toHtmlString(abstract.mid(npos, pos - npos)) + QLatin1String("<span>") +
               c2bUtils::toHtmlString(abstract.mid(pos, length)) + QLatin1String("</span>");
        npos = endpos.value(pos);
    }
    hla += c2bUtils::toHtmlString(abstract.mid(npos, abstract.length() - npos));
    return hla;
}

QString bibSearcher::location(const QString& fn, const bibReference& ref) const
{
    const QString at("<a href=\"%1:%2\" class=\"anchor\">"
                     "<img src=\":/icons/icons/edit16.png\" alt=\"action\" width=\"16\" height=\"16\" /></a>");
    return at.arg(QDir::cleanPath(fn)).arg(ref.positionValue);
}
