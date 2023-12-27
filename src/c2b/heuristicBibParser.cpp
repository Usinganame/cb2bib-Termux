/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "heuristicBibParser.h"

#include "bibParser.h"
#include "journalDB.h"

#include <QDate>

#include <cmath>


heuristicBibParser::heuristicBibParser(bibParser* bp)
    : _bpP(bp),
      _current_reference(bp->_current_reference),
      _reliable_number(false),
      _reliable_pages(false),
      _reliable_volume(false),
      _abstract("abstract"),
      _addauthors("addauthors"),
      _author("author"),
      _isbn("isbn"),
      _keywords("keywords"),
      _number("number"),
      _pages("pages"),
      _title("title"),
      _volume("volume"),
      _year("year"),
      _bibliographic_fields(bp->_bibliographic_fields),
      _journal_db(*bp->_journal_dbP)
{
    _leading_non_letters = QRegExp("^[^<\\w]+");
    // Char 65533 appears many times in pdftotext outputs due to encoding errors
    _hyphens = QRegExp("\\s*[-" + QString(QChar(8211)) + QString(QChar(8722)) + QString(QChar(65533)) + "]+\\s*");
    _hyphen_nums = "(?:\\d+|\\d+-\\d+)";
    _hyphen_pages = "(?:\\d+|\\d+-\\d+p{0,2}|\\d+ \\d+pp)";
    _max_year = 3 + QDate::currentDate().year();

    // Setup author recognition
    // Implementation of author field extraction
    // P. Constans. A Simple Extraction Procedure for Bibliographical Author Field.
    // arXiv:0902.0755, 2009.
    _word_prefix_lexicon =
        c2bUtils::fileToString(":/txt/txt/word_prefix_lexicon.txt").split(c2bUtils::nonLetter, QString::SkipEmptyParts);
    for (int i = 0; i < _word_prefix_lexicon.count(); ++i)
    {
        _word_prefix_lexicon[i].replace('_', ' ');
        _word_prefix_lexicon[i].squeeze();
    }
    const QString author_lc_t("(?:n%1n|n%1%1n|%1n|%1nn|%1%1n|%1%1%1n|n%1nn|nn%1n|%1%1nn|%1n%1n|nn|nnn)");
    const QString author_uc_t(
        "(?:[nN]%1N|[nN]%1%1N|%1N|%1[nN]N|%1%1N|%1%1%1N|[nN]%1[nN]N|[nN]N%1N|%1%1[nN]N|%1[nN]%1N|[nN]N|[nN][nN]N)");
    const QString author_initial("Ip{0,1}");
    const QString author_line("L%1(?:[,;&L]+%1)*(?=L)");
    const QString author_lc(author_line.arg(author_lc_t.arg(author_initial)));
    const QString author_uc(author_line.arg(author_uc_t.arg(author_initial)));
    const QString author_address("(?:L[^L]*)");

    _author_sb = QRegExp(QString("L%1(?:[,;&]+L{0,2}%1)*[,;&L]*L").arg(author_lc_t.arg(author_initial)),
                         Qt::CaseInsensitive, QRegExp::RegExp);
    _author_sb_lc = QRegExp(QString("L%1(?:[,;&L]+%1)*(?=L)").arg(author_lc_t.arg(author_initial)), Qt::CaseSensitive,
                            QRegExp::RegExp);
    _author_sb_uc = QRegExp(QString("L%1(?:[,;&L]+%1)*(?=L)").arg(author_uc_t.arg(author_initial)), Qt::CaseSensitive,
                            QRegExp::RegExp);
    _author_sb.setMinimal(false);
    _author_sb_lc.setMinimal(false);
    _author_sb_uc.setMinimal(false);
    // Note: Syntax must be RegExp and not RegExp2.
    // If not, in cases as 'LnnL ... Lnn,nn,Lnn,&nnL' it will overextend addresses to include Lnn,nn,L.
    // This is not related to minimal/greedy.
    // Note also that Lnn,nn,L will not be taken, unless it is followed by another author line. This is a feature.
    _author_b2_lc_rx =
        new QRegExp(QString("(%1)%2{0,7}(%1)").arg(author_lc, author_address), Qt::CaseSensitive, QRegExp::RegExp);
    _author_b2_uc_rx =
        new QRegExp(QString("(%1)%2{0,7}(%1)").arg(author_uc, author_address), Qt::CaseSensitive, QRegExp::RegExp);
    _author_b3_lc_rx = new QRegExp(QString("(%1)%2{0,7}(%1)%2{0,7}(%1)").arg(author_lc, author_address),
                                   Qt::CaseSensitive, QRegExp::RegExp);
    _author_b3_uc_rx = new QRegExp(QString("(%1)%2{0,7}(%1)%2{0,7}(%1)").arg(author_uc, author_address),
                                   Qt::CaseSensitive, QRegExp::RegExp);
    _author_b4_lc_rx = new QRegExp(QString("(%1)%2{0,7}(%1)%2{0,7}(%1)%2{0,7}(%1)").arg(author_lc, author_address),
                                   Qt::CaseSensitive, QRegExp::RegExp);
    _author_b4_uc_rx = new QRegExp(QString("(%1)%2{0,7}(%1)%2{0,7}(%1)%2{0,7}(%1)").arg(author_uc, author_address),
                                   Qt::CaseSensitive, QRegExp::RegExp);
    _author_b5_lc_rx =
        new QRegExp(QString("(%1)%2{0,7}(%1)%2{0,7}(%1)%2{0,7}(%1)%2{0,7}(%1)").arg(author_lc, author_address),
                    Qt::CaseSensitive, QRegExp::RegExp);
    _author_b5_uc_rx =
        new QRegExp(QString("(%1)%2{0,7}(%1)%2{0,7}(%1)%2{0,7}(%1)%2{0,7}(%1)").arg(author_uc, author_address),
                    Qt::CaseSensitive, QRegExp::RegExp);
    _author_b2_lc_rx->setMinimal(true);
    _author_b2_uc_rx->setMinimal(true);
    _author_b3_lc_rx->setMinimal(true);
    _author_b3_uc_rx->setMinimal(true);
    _author_b4_lc_rx->setMinimal(true);
    _author_b4_uc_rx->setMinimal(true);
    _author_b5_lc_rx->setMinimal(true);
    _author_b5_uc_rx->setMinimal(true);
}

heuristicBibParser::~heuristicBibParser()
{
    delete _author_b2_lc_rx;
    delete _author_b2_uc_rx;
    delete _author_b3_lc_rx;
    delete _author_b3_uc_rx;
    delete _author_b4_lc_rx;
    delete _author_b4_uc_rx;
    delete _author_b5_lc_rx;
    delete _author_b5_uc_rx;
}


void heuristicBibParser::guessFields(const QString& clean_text, const QString& tagged_text)
{
    QString clean_num(clean_text);
    clean_num.replace(_hyphens, "-");
    // Order is important to increase the chances of a proper recognition
    guessJournal(clean_text);
    guessAbstract(tagged_text);
    guessAuthor(tagged_text);
    guessKeywords(tagged_text);
    guessYear(clean_num);
    _debug_guess("guessYear");
    guessVolume(clean_num);
    _debug_guess("guessVolume");
    guessNumber(clean_num);
    _debug_guess("guessNumber");
    guessPages(clean_num);
    _debug_guess("guessPages");
    guessTitle(tagged_text);
    guessISBN(clean_num);
    guessVolumeYearPages(clean_num);
    _debug_guess("guessVolumeYearPages");
    guessYearVolumePages(clean_num);
    _debug_guess("guessYearVolumePages");
    guessVolumePagesYear(clean_num);
    _debug_guess("guessVolumePagesYear");
    guessFromMetadata(clean_text);
}

void heuristicBibParser::heuristicFields(const QString& text)
{
    // Heuristics for reasonably secure extraction
    QRegExp rxdoi("(10\\.[\\d\\.]+/\\S+)");
    if (rxdoi.indexIn(text) > -1)
    {
        QString cdoi(rxdoi.cap(1));
        // This happens when publishers set doi to title in metadata: <title>doi:10. ... </title>
        if (cdoi.endsWith("</title>"))
            cdoi.chop(8);
        cdoi.remove(QRegExp("[\\,\"\\}\\)]+$"));
        _current_reference["doi"] = _bpP->parse("doi", cdoi);
    }

    QRegExp rxarxiv("arXiv:([\\w\\./-]+)");
    if (rxarxiv.indexIn(text) > -1)
    {
        // https://arxiv.org/hypertex/bibstyles/
        QString aid(rxarxiv.cap(1));
        aid.remove(QRegExp("v\\d{1,2}$"));
        _current_reference["eprint"] = _bpP->parse("eprint", aid);
        _current_reference["journal"] = _bpP->parse("journal", "arXiv:" + aid);
        _current_reference["url"] = _bpP->parse("url", c2bUtils::arxivUrl.arg(aid));
    }

    QRegExp rxhtml("((http://|https://|ftp://|www\\.|ftp\\.)(www\\.|ftp\\.){0,1}\\S+)");
    if (rxhtml.indexIn(text) > -1)
        _current_reference["url"] = _bpP->parse("url", rxhtml.cap(1));
}

/** \page heuristics Field Recognition Rules

- <b>Abstract</b>
  - If <tt>Abstract\b</tt> is found.
  - If <tt>Summary\b</tt> is found.

*/
void heuristicBibParser::guessAbstract(const QString& text)
{
    // Check whether text might come from a web page or from a PDF with new lines
    // Set line length to 93
    // Check first for abstract, check later for summary
    if (text.contains("Abstract", Qt::CaseInsensitive))
    {
        const QString crl(QChar(169)); // Avoid abstract overextending to copyright line.
        QRegExp rxH("(?:<NewLine\\d+>|<Tab\\d+>)\\s*Abstract[\\s\\.:]*<NewLine\\d+>(.+)(?:" + crl + "|<NewLine|$)",
                    Qt::CaseInsensitive);
        rxH.setMinimal(true);
        int nH(rxH.indexIn(text));
        if (nH > -1)
            if (rxH.cap(1).length() > 93)
            {
                const QString val(rxH.cap(1).remove(_leading_non_letters));
                _current_reference[_abstract] = _bpP->parse(_abstract, val);
                return;
            }
        rxH = QRegExp("(?:<NewLine\\d+>|<Tab\\d+>)\\s*Abstract[\\s\\.:]*<NewLine\\d+>(.+)(?:" + crl +
                      "|<NewLine\\d+>\\s*<NewLine|$)",
                      Qt::CaseInsensitive);
        rxH.setMinimal(true);
        nH = rxH.indexIn(text);
        if (nH > -1)
        {
            const QString val(rxH.cap(1).remove(_leading_non_letters));
            _current_reference[_abstract] = _bpP->parse(_abstract, val);
            return;
        }
        rxH = QRegExp("(?:<NewLine\\d+>|<Tab\\d+>)\\s*Abstract\\b(.+)(?:" + crl + "|<NewLine|$)", Qt::CaseInsensitive);
        rxH.setMinimal(true);
        nH = rxH.indexIn(text);
        if (nH > -1)
            if (rxH.cap(1).length() > 93)
            {
                const QString val(rxH.cap(1).remove(_leading_non_letters));
                _current_reference[_abstract] = _bpP->parse(_abstract, val);
                return;
            }
        rxH = QRegExp("(?:<NewLine\\d+>|<Tab\\d+>)\\s*Abstract\\b(.+)(?:" + crl + "|<NewLine\\d+>\\s*<NewLine|$)",
                      Qt::CaseInsensitive);
        rxH.setMinimal(true);
        nH = rxH.indexIn(text);
        if (nH > -1)
        {
            const QString val(rxH.cap(1).remove(_leading_non_letters));
            _current_reference[_abstract] = _bpP->parse(_abstract, val);
            return;
        }
    }
    if (text.contains("Summary", Qt::CaseInsensitive))
    {
        QRegExp rxH("(?:<NewLine\\d+>|<Tab\\d+>)\\s*Summary[\\s\\.:]*<NewLine\\d+>(.+)(?:<NewLine|$)",
                    Qt::CaseInsensitive);
        rxH.setMinimal(true);
        int nH(rxH.indexIn(text));
        if (nH > -1)
            if (rxH.cap(1).length() > 93)
            {
                const QString val(rxH.cap(1).remove(_leading_non_letters));
                _current_reference[_abstract] = _bpP->parse(_abstract, val);
                return;
            }
        rxH =
            QRegExp("(?:<NewLine\\d+>|<Tab\\d+>)\\s*Summary[\\s\\.:]*<NewLine\\d+>(.+)(?:<NewLine\\d+>\\s*<NewLine|$)",
                    Qt::CaseInsensitive);
        rxH.setMinimal(true);
        nH = rxH.indexIn(text);
        if (nH > -1)
        {
            const QString val(rxH.cap(1).remove(_leading_non_letters));
            _current_reference[_abstract] = _bpP->parse(_abstract, val);
            return;
        }
        rxH = QRegExp("(?:<NewLine\\d+>|<Tab\\d+>)\\s*Summary\\b(.+)(?:<NewLine|$)", Qt::CaseInsensitive);
        rxH.setMinimal(true);
        nH = rxH.indexIn(text);
        if (nH > -1)
            if (rxH.cap(1).length() > 93)
            {
                const QString val(rxH.cap(1).remove(_leading_non_letters));
                _current_reference[_abstract] = _bpP->parse(_abstract, val);
                return;
            }
        rxH =
            QRegExp("(?:<NewLine\\d+>|<Tab\\d+>)\\s*Summary\\b(.+)(?:<NewLine\\d+>\\s*<NewLine|$)", Qt::CaseInsensitive);
        rxH.setMinimal(true);
        nH = rxH.indexIn(text);
        if (nH > -1)
        {
            const QString val(rxH.cap(1).remove(_leading_non_letters));
            _current_reference[_abstract] = _bpP->parse(_abstract, val);
            return;
        }
    }
}

/** \page heuristics Field Recognition Rules

- <b>Author</b>
  - Check capitalization patterns. See
    \htmlonly
    <a href="https://arxiv.org/abs/0902.0755" target="_blank">
    A Simple Extraction Procedure for Bibliographical Author Field</a>.
    \endhtmlonly

*/
void heuristicBibParser::guessAuthor(const QString& tagged_text)
{
    // Prepare input stream
    QString simplified_text("| " + tagged_text + " |");
    simplified_text.replace('|', ' ');
    simplified_text = "| " + simplified_text + " |";

    simplified_text.replace(QRegExp("<NewLine\\d+>"), " | ");
    simplified_text.replace(QRegExp("(\\w)<Tab\\d+>(\\w)"), "\\1 , \\2");
    simplified_text.replace(QRegExp("<Tab\\d+>"), " ");

    simplified_text.remove(QRegExp("author.{0,3}:{0,1}", Qt::CaseInsensitive));
    simplified_text.replace(QRegExp("(\\w{4,10})[a-z]\\)", Qt::CaseSensitive),
                            "\\1 "); // Remove superscript, e. g. LASTNAMEa
    simplified_text.replace(QRegExp("([A-Z]{2,10})[a-z]\\b", Qt::CaseSensitive),
                            "\\1 "); // Remove superscript, e. g. LASTNAMEa)
    simplified_text.replace(_hyphens, "-");
    simplified_text.replace(QChar(183), ',');               // Fancy author separator
    simplified_text.replace(' ' + QChar(198) + ' ', " , "); // Fancy author separator
    simplified_text.replace(QChar(8226), ',');              // Fancy author separator
    simplified_text.replace(QChar(178), ' ');               // Superscript dagger as sometimes translated by pdftotext
    _aencoder.aunifier.simplifyString(simplified_text);

    // Capitalize and encode
    for (int i = 0; i < _word_prefix_lexicon.count(); ++i)
    {
        const QString& wp = _word_prefix_lexicon.at(i);
        simplified_text.replace(wp, wp, Qt::CaseInsensitive);
    }
    simplified_text.replace(" by ", " ");
    _aencoder.encode(simplified_text);
    const QString sb_author(guessAuthor_single_block());
    const int n_sb_author(authorCount(sb_author));
    const QString mb_author(guessAuthor_multi_block());
    const int n_mb_author(authorCount(mb_author));
    if (n_mb_author > n_sb_author)
        _current_reference[_author] = mb_author;
    else
        _current_reference[_author] = sb_author;
}

QString heuristicBibParser::guessAuthor_single_block()
{
    QString author;
    if (_author_sb_lc.indexIn(_aencoder.code) > -1)
        author = _bpP->parse(_author, _aencoder.decoded(_author_sb_lc.pos(0), _author_sb_lc.matchedLength()));
    else if (_author_sb_uc.indexIn(_aencoder.code) > -1)
        author = _bpP->parse(_author, _aencoder.decoded(_author_sb_uc.pos(0), _author_sb_uc.matchedLength()));
    else if (_author_sb.indexIn(_aencoder.code) > -1)
        // Few cases are extracted by _author_sb, keep it for cases 'A. Name,', with ',' usually coming
        // from a faulty plain text conversion.
        author = _bpP->parse(_author, _aencoder.decoded(_author_sb.pos(0), _author_sb.matchedLength()));
    return author;
}

QString heuristicBibParser::guessAuthor_multi_block()
{
    QString author;
    if (_author_b5_uc_rx->indexIn(_aencoder.code) > -1)
        for (int i = 1; i < _author_b5_uc_rx->capturedTexts().count(); ++i)
            author = _bpP->parse(
                         _addauthors, _aencoder.decoded(_author_b5_uc_rx->pos(i), _author_b5_uc_rx->cap(i).length()), author);
    else if (_author_b5_lc_rx->indexIn(_aencoder.code) > -1)
        for (int i = 1; i < _author_b5_lc_rx->capturedTexts().count(); ++i)
            author = _bpP->parse(
                         _addauthors, _aencoder.decoded(_author_b5_lc_rx->pos(i), _author_b5_lc_rx->cap(i).length()), author);
    else if (_author_b4_uc_rx->indexIn(_aencoder.code) > -1)
        for (int i = 1; i < _author_b4_uc_rx->capturedTexts().count(); ++i)
            author = _bpP->parse(
                         _addauthors, _aencoder.decoded(_author_b4_uc_rx->pos(i), _author_b4_uc_rx->cap(i).length()), author);
    else if (_author_b4_lc_rx->indexIn(_aencoder.code) > -1)
        for (int i = 1; i < _author_b4_lc_rx->capturedTexts().count(); ++i)
            author = _bpP->parse(
                         _addauthors, _aencoder.decoded(_author_b4_lc_rx->pos(i), _author_b4_lc_rx->cap(i).length()), author);
    else if (_author_b3_uc_rx->indexIn(_aencoder.code) > -1)
        for (int i = 1; i < _author_b3_uc_rx->capturedTexts().count(); ++i)
            author = _bpP->parse(
                         _addauthors, _aencoder.decoded(_author_b3_uc_rx->pos(i), _author_b3_uc_rx->cap(i).length()), author);
    else if (_author_b3_lc_rx->indexIn(_aencoder.code) > -1)
        for (int i = 1; i < _author_b3_lc_rx->capturedTexts().count(); ++i)
            author = _bpP->parse(
                         _addauthors, _aencoder.decoded(_author_b3_lc_rx->pos(i), _author_b3_lc_rx->cap(i).length()), author);
    else if (_author_b2_uc_rx->indexIn(_aencoder.code) > -1)
        for (int i = 1; i < _author_b2_uc_rx->capturedTexts().count(); ++i)
            author = _bpP->parse(
                         _addauthors, _aencoder.decoded(_author_b2_uc_rx->pos(i), _author_b2_uc_rx->cap(i).length()), author);
    else if (_author_b2_lc_rx->indexIn(_aencoder.code) > -1)
        for (int i = 1; i < _author_b2_lc_rx->capturedTexts().count(); ++i)
            author = _bpP->parse(
                         _addauthors, _aencoder.decoded(_author_b2_lc_rx->pos(i), _author_b2_lc_rx->cap(i).length()), author);
    return author;
}

int heuristicBibParser::authorCount(const QString& authors)
{
    if (authors.isEmpty())
        return 0;
    return 1 + authors.count(" and ");
}

/** \page heuristics

- <b>Keywords</b>
  - If <tt>Key\\s{0,1}words\b</tt> is found.

*/
void heuristicBibParser::guessKeywords(const QString& text)
{
    QRegExp rxH("<(?:NewLine|Tab)\\d+>\\s*Key\\s{0,1}words and phrases[\\s\\.:]*<NewLine\\d+>(.+)(<NewLine|$)",
                Qt::CaseInsensitive);
    rxH.setMinimal(true);
    int nH(rxH.indexIn(text));
    if (nH > -1)
    {
        const QString val(rxH.cap(1).remove(_leading_non_letters));
        _current_reference[_keywords] = _bpP->parse(_keywords, val);
        return;
    }
    rxH = QRegExp("<(?:NewLine|Tab)\\d+>\\s*Key\\s{0,1}words and phrases\\b(.+)(<NewLine|$)", Qt::CaseInsensitive);
    rxH.setMinimal(true);
    nH = rxH.indexIn(text);
    if (nH > -1)
    {
        const QString val(rxH.cap(1).remove(_leading_non_letters));
        _current_reference[_keywords] = _bpP->parse(_keywords, val);
    }

    rxH =
        QRegExp("<(?:NewLine|Tab)\\d+>\\s*Key\\s{0,1}words[\\s\\.:]*<NewLine\\d+>(.+)(<NewLine|$)", Qt::CaseInsensitive);
    rxH.setMinimal(true);
    nH = rxH.indexIn(text);
    if (nH > -1)
    {
        const QString val(rxH.cap(1).remove(_leading_non_letters));
        _current_reference[_keywords] = _bpP->parse(_keywords, val);
        return;
    }
    rxH = QRegExp("<(?:NewLine|Tab)\\d+>\\s*Key\\s{0,1}words\\b(.+)(<NewLine|$)", Qt::CaseInsensitive);
    rxH.setMinimal(true);
    nH = rxH.indexIn(text);
    if (nH > -1)
    {
        const QString val(rxH.cap(1).remove(_leading_non_letters));
        _current_reference[_keywords] = _bpP->parse(_keywords, val);
    }
}

/** \page heuristics

- <b>Volume</b>
  - If <tt>Volume:{0,1}</tt> is found.
  - If <tt>Vol.{0,1}</tt> is found.
  - If <tt>\\b(\\d+)[,:]\\s*\\d+\\W+\\d+</tt> is found.
  - If <tt>\\b(\\d+)\\s*\\(\\d+\\)</tt> is found.
  - If <tt>\\b(\\d+)[,:]\\s*\\d+\\b</tt> is found.

*/
void heuristicBibParser::guessVolume(const QString& text)
{
    _reliable_volume = true;
    QRegExp rxH("Volumes{0,1}:{0,1}\\s*(" + _hyphen_nums + ')', Qt::CaseInsensitive);
    int nH(rxH.indexIn(text));
    if (nH > -1)
    {
        _current_reference[_volume] = _bpP->parse(_volume, rxH.cap(1));
        return;
    }
    rxH = QRegExp("Vols{0,1}\\.{0,1}\\s*(" + _hyphen_nums + ')', Qt::CaseInsensitive);
    nH = rxH.indexIn(text);
    if (nH > -1)
    {
        _current_reference[_volume] = _bpP->parse(_volume, rxH.cap(1));
        return;
    }
    rxH = QRegExp("\\b(\\d+)\\s*\\(" + _hyphen_nums + "\\)[,:]\\s*pp\\.{0,1}\\s*\\d+", Qt::CaseInsensitive);
    nH = rxH.indexIn(text);
    if (nH > -1)
    {
        _current_reference[_volume] = _bpP->parse(_volume, rxH.cap(1));
        return;
    }
    rxH = QRegExp("\\b(\\d+)[,:]\\s*pp\\.{0,1}\\s*\\d+", Qt::CaseInsensitive);
    nH = rxH.indexIn(text);
    if (nH > -1)
    {
        _current_reference[_volume] = _bpP->parse(_volume, rxH.cap(1));
        return;
    }
    _reliable_volume = false;
    rxH = QRegExp("(\\d+)\\s*\\(" + _hyphen_nums + "\\)[,:]\\s*\\d+", Qt::CaseInsensitive);
    nH = rxH.indexIn(text);
    if (nH > -1)
    {
        _current_reference[_volume] = _bpP->parse(_volume, rxH.cap(1));
        return;
    }
    rxH = QRegExp("\\b(\\d+)\\s*\\(\\d+\\)");
    nH = rxH.indexIn(text);
    if (nH > -1)
    {
        _current_reference[_volume] = _bpP->parse(_volume, rxH.cap(1));
        return;
    }
    rxH = QRegExp("\\b(\\d+)[,:]\\s*" + _hyphen_nums, Qt::CaseInsensitive);
    nH = rxH.indexIn(text);
    if (nH > -1)
    {
        _current_reference[_volume] = _bpP->parse(_volume, rxH.cap(1));
        return;
    }
    rxH = QRegExp("\\b(\\d+)[,:]\\s*\\d+\\b");
    nH = rxH.indexIn(text);
    if (nH > -1)
        _current_reference[_volume] = _bpP->parse(_volume, rxH.cap(1));
}

/** \page heuristics

- <b>Number</b>
  - If <tt>Numbers{0,1}:{0,1}\\s*([\\d-]+)</tt> is found.
  - If <tt>No\\.{0,1}\\s*(\\d+)</tt> is found.
  - If <tt>Issue\\:{0,1}\\s*(\\d+)</tt> is found.
  - If <tt>\\d\\s*\\((\\d+)\\)[^\\.]</tt> is found.

*/
void heuristicBibParser::guessNumber(const QString& text)
{
    _reliable_number = true;
    QRegExp rxH("Numbers{0,1}\\:{0,1}\\s*(" + _hyphen_nums + ')', Qt::CaseInsensitive);
    int nH(rxH.indexIn(text));
    if (nH > -1)
    {
        _current_reference[_number] = _bpP->parse(_number, rxH.cap(1));
        return;
    }
    rxH = QRegExp("Nos{0,1}\\.{0,1}\\s*(" + _hyphen_nums + ')', Qt::CaseInsensitive);
    nH = rxH.indexIn(text);
    if (nH > -1)
    {
        _current_reference[_number] = _bpP->parse(_number, rxH.cap(1));
        return;
    }
    rxH = QRegExp("Issues{0,1}\\:{0,1}\\s*(" + _hyphen_nums + ')', Qt::CaseInsensitive);
    nH = rxH.indexIn(text);
    if (nH > -1)
    {
        _current_reference[_number] = _bpP->parse(_number, rxH.cap(1));
        return;
    }
    _reliable_number = false;
    rxH = QRegExp("\\d\\s*\\((" + _hyphen_nums + ")\\)[^\\.]");
    nH = rxH.indexIn(text);
    if (nH > -1)
        if (rxH.cap(1) != _current_reference.value(_year)) // Avoid confusing (number) and (year)
            _current_reference[_number] = _bpP->parse(_number, rxH.cap(1));
}

/** \page heuristics

- <b>Pages</b>
  - If <tt>\\bPages{0,1}[:\\.]{0,1}([\\d\\s-]+)</tt> is found.
  - If <tt>\\bp{1,2}\\.{0,1}\\s+(\\d+)</tt> is found.
  - If <tt>\\b(\\d+)\\s*-{1,2}\\s*(\\d+pp)\\b</tt> is found.
  - If <tt>\\b(\\d+)\\s*-{1,2}\\s*(\\d+)\\b</tt> is found.

*/
void heuristicBibParser::guessPages(const QString& text)
{
    _reliable_pages = true;
    QRegExp rxH("\\bPages{0,1}[:\\.]{0,1}\\s*((?!\\()" + _hyphen_nums + "(?!\\)))", Qt::CaseInsensitive);
    int nH(rxH.indexIn(text));
    if (nH > -1)
    {
        _current_reference[_pages] = _bpP->parse(_pages, rxH.cap(1));
        return;
    }
    rxH = QRegExp("(?!\\()(\\d+[\\s-]\\d+pp)(?!\\))", Qt::CaseInsensitive);
    nH = rxH.indexIn(text);
    if (nH > -1)
    {
        _current_reference[_pages] = _bpP->parse(_pages, rxH.cap(1));
        return;
    }
    rxH = QRegExp("\\bpp\\.{0,1}\\s+(" + _hyphen_nums + ')', Qt::CaseInsensitive);
    nH = rxH.indexIn(text);
    if (nH > -1)
    {
        _current_reference[_pages] = _bpP->parse(_pages, rxH.cap(1));
        return;
    }
    _reliable_pages = false;
    rxH = QRegExp("\\bp\\.{0,1}\\s+(" + _hyphen_nums + ')');
    nH = rxH.indexIn(text);
    if (nH > -1)
    {
        _current_reference[_pages] = _bpP->parse(_pages, rxH.cap(1));
        return;
    }
    rxH = QRegExp("\\d+\\s*\\(" + _hyphen_nums + "\\),{0,1}\\s*(" + _hyphen_nums + ')');
    nH = rxH.indexIn(text); // 120 (1-3), 927
    if (nH > -1)
    {
        _current_reference[_pages] = _bpP->parse(_pages, rxH.cap(1));
        return;
    }
    rxH = QRegExp("(?!\\()(\\d+)\\s*-{1,2}\\s*(\\d+)\\b(?!\\))");
    nH = 0;
    while (nH >= 0)
    {
        nH = rxH.indexIn(text, nH);
        if (nH > -1)
        {
            if (!rxH.cap(1).startsWith('0'))
            {
                const QString pp(_bpP->parse(_pages, QString("%1 %2").arg(rxH.cap(1), rxH.cap(2))));
                const QStringList flpp(pp.split(QRegExp("\\D"), QString::SkipEmptyParts));
                if (flpp.count() != 2)
                    continue;
                const int fp(flpp.first().toInt());
                const int lp(flpp.last().toInt());
                if (fp < lp && lp - fp < 250)
                {
                    _current_reference[_pages] = pp;
                    return;
                }
            }
            nH += rxH.matchedLength();
        }
    }
}

/** \page heuristics

- <b>Year</b>
  - If <tt>\\b(19|20)(\\d\\d)\\b</tt> is found.

*/
void heuristicBibParser::guessYear(const QString& text)
{
    QRegExp rxH("\\((19|20)(\\d\\d)\\)");
    int nH(rxH.indexIn(text));
    if (nH > -1)
    {
        const QString y(_bpP->parse(_year, rxH.cap(1) + rxH.cap(2)));
        if (y.toInt() < _max_year)
        {
            _current_reference[_year] = y;
            return;
        }
    }
    rxH = QRegExp("\\d+:" + _hyphen_nums + "[,\\s]+(19|20)(\\d\\d)\\b");
    nH = rxH.indexIn(text); // 44:2077 – 2082, 2004.
    if (nH > -1)
    {
        const QString y(_bpP->parse(_year, rxH.cap(1) + rxH.cap(2)));
        if (y.toInt() < _max_year)
        {
            _current_reference[_year] = y;
            return;
        }
    }
    rxH = QRegExp("\\b(19|20)(\\d\\d)\\b");
    nH = rxH.indexIn(text);
    if (nH > -1)
    {
        const QString y(_bpP->parse(_year, rxH.cap(1) + rxH.cap(2)));
        if (y.toInt() < _max_year)
        {
            _current_reference[_year] = y;
            return;
        }
    }
}

/** \page heuristics

- <b>Title</b>
  - If <tt>\\bTitle:{0,1}</tt> is found.

*/
void heuristicBibParser::guessTitle(const QString& text)
{
    QRegExp rxH("\\bTitle:{0,1}\\s*<NewLine\\d+>(.+)(<NewLine|$)", Qt::CaseInsensitive);
    rxH.setMinimal(true);
    int nH(rxH.indexIn(text));
    if (nH > -1)
    {
        QString val(rxH.cap(1).remove(_leading_non_letters));
        _current_reference[_title] = _bpP->parse(_title, val);
        return;
    }
    rxH = QRegExp("\\bTitle:{0,1}(.+)(<NewLine|$)", Qt::CaseInsensitive);
    rxH.setMinimal(true);
    nH = rxH.indexIn(text);
    if (nH > -1)
    {
        QString val(rxH.cap(1).remove(_leading_non_letters));
        _current_reference[_title] = _bpP->parse(_title, val);
    }
}

/** \page heuristics

- <b>ISBN</b>
  - If <tt>\\bISBN\\b(?:-\\d+){0,1}:{0,1}(?:-\\d+){0,1}\\s*(\\d+-[\\d-]+-\\d+)</tt> is found.
  - If <tt>\\bISBN\\b(?:-\\d+){0,1}:{0,1}(?:-\\d+){0,1}\\s*(\\d+)</tt> is found.

*/
void heuristicBibParser::guessISBN(const QString& text)
{
    QRegExp rxH("\\bISBN\\b(?:[ -]\\d+){0,1}:{0,1}(?:-\\d+){0,1}\\s*(\\d+-[\\d-]+-\\d+)", Qt::CaseInsensitive);
    int nH(rxH.indexIn(text));
    if (nH > -1)
    {
        _current_reference[_isbn] = _bpP->parse(_isbn, rxH.cap(1));
        return;
    }
    rxH = QRegExp("\\bISBN\\b(?:[ -]\\d+){0,1}:{0,1}(?:-\\d+){0,1}\\s*(\\d+)", Qt::CaseInsensitive);
    nH = rxH.indexIn(text);
    if (nH > -1)
    {
        _current_reference[_isbn] = _bpP->parse(_isbn, rxH.cap(1));
        return;
    }
}

/** \page heuristics

- <b>Journal</b>
  - Check cb2Bib internal database.

*/
void heuristicBibParser::guessJournal(const QString& text)
{
    QString stext(text.toLower());
    stext.remove(c2bUtils::nonLetter);
    if (stext.length() < 3 || stext.length() > 10000)
        return;

    const int pheader(0);
    const int pfooter(stext.length());
    double oscore(0);
    int oindex(-1);

    QStringMatcher blank(" ");
    for (int i = 0; i < _journal_db.count(); ++i)
        if (blank.indexIn(_journal_db.retrieveFull(i)) >= 0)
        {
            const int p(stext.indexOf(_journal_db.fullsimplifiedFull(i), 0, Qt::CaseSensitive));
            if (p == -1)
                continue;
            const int jlength(_journal_db.fullsimplifiedFull(i).length());
            const int d(1 + std::min(p - pheader, pfooter - p - jlength));
            const double score(pow(double(jlength), 1.75) / double(d));
            if (score > oscore)
            {
                oscore = score;
                oindex = i;
            }
        }
    for (int i = 0; i < _journal_db.count(); ++i)
    {
        const int p(stext.indexOf(_journal_db.fullsimplified(i), 0, Qt::CaseSensitive));
        if (p == -1)
            continue;
        const int jlength(_journal_db.fullsimplified(i).length());
        const int d(1 + std::min(p - pheader, pfooter - p - jlength));
        const double score(pow(double(jlength), 1.75) / double(d));
        if (score > oscore)
        {
            oscore = score;
            oindex = i;
        }
    }
    if (oscore > double(1) && oindex > -1)
        _current_reference["journal"] = _bpP->parse("journal", _journal_db.retrieve(oindex));
}

void heuristicBibParser::guessFromMetadata(const QString& text)
{
    if (!text.contains("[Bibliographic Metadata"))
        return;
    QRegExp bf;
    bf.setMinimal(true);
    bf.setCaseSensitivity(Qt::CaseSensitive);
    QString p("<%1>(.+)</%1>");
    for (int i = 0; i < _bibliographic_fields.count(); ++i)
    {
        bf.setPattern(p.arg(_bibliographic_fields.at(i)));
        if (bf.indexIn(text) > -1)
            _current_reference[_bibliographic_fields.at(i)] = _bpP->parse(_bibliographic_fields.at(i), bf.cap(1));
    }
}

void heuristicBibParser::guessVolumePagesYear(const QString& text)
{
    // Does several volume pages year formats
    if (_reliable_pages && _reliable_volume && _reliable_number)
        return;
    // J. Sci., 108 (15), 3206, 2004
    // J. Sci., 108 (15), 3206 2004
    QRegExp rxH("(\\d+)\\s*\\((" + _hyphen_nums + ")\\)\\s*[,:]\\s*(" + _hyphen_pages + ")[,\\s]+(19|20)(\\d\\d)");
    int nH(rxH.indexIn(text));
    if (nH > -1)
    {
        _current_reference[_volume] = _bpP->parse(_volume, rxH.cap(1));
        _current_reference[_number] = _bpP->parse(_number, rxH.cap(2));
        _current_reference[_pages] = _bpP->parse(_pages, rxH.cap(3));
        _current_reference[_year] = _bpP->parse(_year, rxH.cap(4) + rxH.cap(5));
        return;
    }
    // J. Sci., 108 (15), 3206 (2004)
    rxH =
        QRegExp("(\\d+)\\s*\\((" + _hyphen_nums + ")\\)\\s*[,:]\\s*(" + _hyphen_pages + ")[,\\s]*\\((19|20)(\\d\\d)\\)");
    nH = rxH.indexIn(text);
    if (nH > -1)
    {
        _current_reference[_volume] = _bpP->parse(_volume, rxH.cap(1));
        _current_reference[_number] = _bpP->parse(_number, rxH.cap(2));
        _current_reference[_pages] = _bpP->parse(_pages, rxH.cap(3));
        _current_reference[_year] = _bpP->parse(_year, rxH.cap(4) + rxH.cap(5));
        return;
    }
    if (_reliable_pages && _reliable_volume)
        return;
    // J. Sci. 124, 204109 2006
    // J. Sci. 124, 204109, 2006
    rxH = QRegExp("(\\d+)[,:]\\s*(" + _hyphen_pages + ")[,\\s]+(19|20)(\\d\\d)");
    nH = rxH.indexIn(text);
    if (nH > -1)
    {
        _current_reference[_volume] = _bpP->parse(_volume, rxH.cap(1));
        _current_reference[_pages] = _bpP->parse(_pages, rxH.cap(2));
        _current_reference[_year] = _bpP->parse(_year, rxH.cap(3) + rxH.cap(4));
        return;
    }
    // 120, 8425 - 8433 (2004)
    // J. Sci. 30, 2745 (1984)
    rxH = QRegExp("(\\d+)[,:]\\s*(" + _hyphen_pages + ")[,\\s]*\\((19|20)(\\d\\d)\\)");
    nH = rxH.indexIn(text);
    if (nH > -1)
    {
        _current_reference[_volume] = _bpP->parse(_volume, rxH.cap(1));
        _current_reference[_pages] = _bpP->parse(_pages, rxH.cap(2));
        _current_reference[_year] = _bpP->parse(_year, rxH.cap(3) + rxH.cap(4));
        return;
    }
}

void heuristicBibParser::guessVolumeYearPages(const QString& text)
{
    // Does several volume year pages formats
    if (_reliable_number && _reliable_volume)
        return;
    // J. Sci. 203 (2003) 209.
    QRegExp rxH("(\\d+)\\s*\\(" + _current_reference.value(_year) + "\\)\\s*(" + _hyphen_pages + ')');
    int nH(rxH.indexIn(text));
    if (nH > -1)
    {
        _current_reference[_volume] = _bpP->parse(_volume, rxH.cap(1));
        _current_reference[_pages] = _bpP->parse(_pages, rxH.cap(2));
        return;
    }
}

void heuristicBibParser::guessYearVolumePages(const QString& text)
{
    // Does several year volume pages formats
    if (_reliable_pages && _reliable_volume && _reliable_number)
        return;
    // J. Sci. 1995 January 25; 247(4):536-40.
    // J. Sci. 1995, 247(4):536-40.
    QRegExp rxH(_current_reference.value(_year) + "[\\w ]{0,15}[,:; ]\\s*(\\d+)\\s*\\((" + _hyphen_nums +
                ")\\)\\s*[,:;]\\s*(" + _hyphen_pages + ')');
    int nH(rxH.indexIn(text));
    if (nH > -1)
    {
        _current_reference[_volume] = _bpP->parse(_volume, rxH.cap(1));
        _current_reference[_number] = _bpP->parse(_number, rxH.cap(2));
        _current_reference[_pages] = _bpP->parse(_pages, rxH.cap(3));
        _reliable_pages = true;
        _reliable_volume = true;
        return;
    }
    // J. Sci. (1999), 86, 3, pp. 635-648
    rxH = QRegExp("\\(" + _current_reference.value(_year) + "\\)" + "\\s*[,:;]\\s*(\\d+)\\s*[,:;]\\s*(" + _hyphen_nums +
                  ")\\s*[,:;]\\s*(?:pp)?\\.?\\s*(" + _hyphen_pages + ')');
    nH = rxH.indexIn(text);
    if (nH > -1)
    {
        _current_reference[_volume] = _bpP->parse(_volume, rxH.cap(1));
        _current_reference[_number] = _bpP->parse(_number, rxH.cap(2));
        _current_reference[_pages] = _bpP->parse(_pages, rxH.cap(3));
        _reliable_pages = true;
        _reliable_volume = true;
        return;
    }
    if (_reliable_volume)
        return;
    // J. Sci. 1995 January 25; 247:536-40.
    // J. Sci. 2005, 103, 818
    // J. Sci. 2002;9:101–106.5.
    rxH =
        QRegExp(_current_reference.value(_year) + "\\s*[\\w ]{0,15}[,:;]\\s*(\\d+)\\s*[,:;]\\s*(" + _hyphen_pages + ')');
    nH = rxH.indexIn(text);
    if (nH > -1)
    {
        _current_reference[_volume] = _bpP->parse(_volume, rxH.cap(1));
        _current_reference[_pages] = _bpP->parse(_pages, rxH.cap(2));
        _reliable_pages = true;
        _reliable_volume = true;
        return;
    }
    // J. Sci. 2005 103:818
    rxH = QRegExp(_current_reference.value(_year) + "\\s+(\\d+)\\s*:\\s*(" + _hyphen_pages + ')');
    nH = rxH.indexIn(text);
    if (nH > -1)
    {
        _current_reference[_volume] = _bpP->parse(_volume, rxH.cap(1));
        _current_reference[_pages] = _bpP->parse(_pages, rxH.cap(2));
        return;
    }
    // (2006) J. Sci. 39:3047
    rxH = QRegExp("\\(" + _current_reference.value(_year) + "\\)\\D{5,30}(\\d+)\\s*[,:;]\\s*(" + _hyphen_pages + ')');
    nH = rxH.indexIn(text);
    if (nH > -1)
    {
        _current_reference[_volume] = _bpP->parse(_volume, rxH.cap(1));
        _current_reference[_pages] = _bpP->parse(_pages, rxH.cap(2));
        return;
    }
    // 2006 J. Sci. 39 3047
    rxH = QRegExp(_current_reference.value(_year) + "\\D{5,30}(\\d+)\\s*[,:; ]\\s*(" + _hyphen_pages + ')');
    nH = rxH.indexIn(text);
    if (nH > -1)
    {
        _current_reference[_volume] = _bpP->parse(_volume, rxH.cap(1));
        _current_reference[_pages] = _bpP->parse(_pages, rxH.cap(2));
        return;
    }
}
