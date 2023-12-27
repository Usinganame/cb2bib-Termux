/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "collectionIndex.h"

#include "bibParser.h"
#include "cb2bib_utilities.h"
#include "documentCache.h"
#include "documentParser.h"
#include "posTagger.h"
#include "settings.h"

#include <QDataStream>
#include <QRegularExpression>

#include <time.h>

#define C2B_DEBUG_COLLECTIONINDEX 0

namespace
{
// Tunable parameters
static const int _document_length_threshold(100000);
static const int _in_long_document_sentence_repetition(3);
static const int _in_short_document_sentence_repetition(2);
static const int _inter_document_sentence_repetition(3);

#if (QT_VERSION >= QT_VERSION_CHECK(5, 4, 0)) && (QT_VERSION < QT_VERSION_CHECK(5, 12, 0))
static const QRegularExpression::PatternOptions _qre_pattern_options(QRegularExpression::UseUnicodePropertiesOption |
        QRegularExpression::OptimizeOnFirstUsageOption);
#else
static const QRegularExpression::PatternOptions _qre_pattern_options(QRegularExpression::UseUnicodePropertiesOption);
#endif

class reversedsorting
{
public:
    inline reversedsorting() {}
    inline bool operator()(const QString& si, const QString& sj) const
    {
        const int li(si.length());
        const int lj(sj.length());
        const QChar* a = si.unicode() + li - 1;
        const QChar* b = sj.unicode() + lj - 1;
        int cl(std::min(li, lj));
        while (cl-- > 0)
        {
            if (*a == *b)
            {
                --a;
                --b;
            }
            else
                return *a < *b;
        }
        return li < lj;
    }
};

class ussorting
{
public:
    inline ussorting() : ss(' '), us('_') {}
    inline bool operator()(const QString& si, const QString& sj)
    {
        QString ssi(si);
        QString ssj(sj);
        return ssi.replace(us, ss) < ssj.replace(us, ss);
    }
    const QChar ss;
    const QChar us;
};

} // namespace


collectionIndex::collectionIndex(bibParser* bp)
    : _out(*(new QTextStream(stdout))), _bpP(bp), _space_char(QChar(' ')), _nerrors(0), _settingsP(settings::instance()) {}

collectionIndex::~collectionIndex()
{
    delete &_out;
}


int collectionIndex::index(const QString& dir)
{
    const unsigned long start_time(clock());
    _nerrors = 0;
    _keysentences.clear();

    const QString bibtexdir(dir.isEmpty()
                            ? QDir::toNativeSeparators(QFileInfo(_settingsP->fileName("cb2Bib/BibTeXFile")).path())
                            : QDir::toNativeSeparators(dir));
    _out << QObject::tr("Indexing references from directory %1...").arg(bibtexdir) << endl;

    bibReference reference;
    documentCache dc;
    int documentid(0);
    QStringList documents;
    QStringList documentfns;

    const QStringList bibtexfns(c2bUtils::filesInDir(bibtexdir, QStringList() << "*.bib"));
    if (bibtexfns.count() == 0)
    {
        ++_nerrors;
        _out << QObject::tr("Error: No BibTeX files at %1").arg(bibtexdir) << endl;
        return _nerrors;
    }

    const QStringList fields(QStringList() << "file"
                             << "journal"
                             << "title"
                             << "booktitle");
    int nfailures(0);
    for (int i = 0; i < bibtexfns.count(); ++i)
    {
        const QString bibtexfn(bibtexfns.at(i));
        _out << QObject::tr("Indexing %1...").arg(bibtexfn) << endl;
        const QString bibtex(c2bUtils::fileToString(bibtexfn));
        dc.load(bibtexfn, documentContents::Complete);

        _bpP->initReferenceParsing(bibtexfn, fields, &reference);
        while (_bpP->referencesIn(bibtex, &reference))
        {
            QString docfn(reference.value("file"));
            if (docfn.isEmpty())
                continue;
            docfn = QDir::cleanPath(docfn);
            const QString journal(reference.value("journal"));
            QString title(reference.anyTitle());
            c2bUtils::cleanTitle(title, true);
            if (dc.setCurrent(docfn))
                setKeySentences(documentid, preprocessedText(journal, dc.current().text()));
            else
                ++nfailures;
            ++documentid;
            documents.append(title);
            documentfns.append(docfn);
        }
        dc.unload();
    }
    if (nfailures > 0)
    {
        _out << QObject::tr("Warning: %1 documents could not be converted to text. Check search converter is set.")
             .arg(nfailures)
             << endl;
        _out << QObject::tr("         Refresh cache by running a prove search including document contents.") << endl;
    }
    _out << QObject::tr("done") << endl;

    digestKeySentences();
    cleanupKeySentences();
    analyzeKeySentences();

#if C2B_DEBUG_COLLECTIONINDEX
    for (int i = 0; i < documents.count(); ++i)
    {
        QStringList sentences(_document_sentences.values(i));
        std::sort(sentences.begin(), sentences.end());
        _out << i << "  " << documents.at(i) << ':' << endl;
        for (int j = 0; j < sentences.count(); ++j)
            _out << "        " << sentences.at(j) << endl;
    }
#endif

    const QString cache_dir(_settingsP->fileName("cb2Bib/CacheDirectory"));
    const QString documentslfn(QDir::toNativeSeparators(cache_dir + "/documents.lc2b"));
    QFile documentslf(QDir::cleanPath(documentslfn));
    if (documentslf.open(QIODevice::WriteOnly))
    {
        _out << QObject::tr("Writing %1...").arg(documentslfn) << endl;
        QDataStream stream(&documentslf);
        stream << documentfns.count();
        for (int i = 0; i < documentfns.count(); ++i)
            stream << documentfns.at(i);
        documentslf.close();
    }
    else
    {
        ++_nerrors;
        _out << QObject::tr("Error: %1 can not be written").arg(documentslfn) << endl;
    }
    const QString documentsifn(QDir::toNativeSeparators(cache_dir + "/documents.ic2b"));
    QFile documentsif(documentsifn);
    if (documentsif.open(QIODevice::WriteOnly))
    {
        _out << QObject::tr("Writing %1...").arg(documentsifn) << endl;
        QDataStream stream(&documentsif);
        for (int i = 0; i < documents.count(); ++i)
        {
            QList<int> sentenceids(_document_sentenceids.values(i));
            std::sort(sentenceids.begin(), sentenceids.end());
            stream << sentenceids.count();
            for (int j = 0; j < sentenceids.count(); ++j)
                stream << sentenceids.at(j);
        }
        documentsif.close();
    }
    else
    {
        ++_nerrors;
        _out << QObject::tr("Error: %1 can not be written").arg(documentsifn) << endl;
    }

    _out << QObject::tr("done") << endl;
    const double time = double(clock() - start_time) / double(CLOCKS_PER_SEC);
    _out << QObject::tr("Indexing CPU time: %1s").arg(time) << endl;

    return _nerrors;
}

void collectionIndex::setKeySentences(const int documentid, const QString& text)
{
    QHash<QStringRef, int> docsentences;
    documentParser dp(text, 7);
    while (dp.parses())
    {
        if (dp.nlength() < 4 * dp.nwords())
            continue;
        const QStringRef s(dp.subsentence());
        docsentences.insert(s, 1 + docsentences.value(s));
    }
    const int dsr(text.length() < _document_length_threshold ? _in_short_document_sentence_repetition
                  : _in_long_document_sentence_repetition);
    for (QHash<QStringRef, int>::const_iterator si = docsentences.constBegin(); si != docsentences.constEnd(); ++si)
    {
        if (si.value() < dsr)
            continue;
        const QString ss(si.key().toString());
        if (!isValidKeySentence(ss))
            continue;
        if (_keysentences.contains(ss))
            _keysentences[ss].update(documentid);
        else
            _keysentences.insert(ss, KeysentenceData(documentid));
    }
}

void collectionIndex::analyzeKeySentences()
{
    _out << QObject::tr("Analysing keyword sentences...") << endl;

    posTagger pt;
    if (!pt.loadLexicon())
    {
        ++_nerrors;
        _out << QObject::tr("Error: cb2Bib POS lexicon could not be loaded; check Configure Files") << endl;
        return;
    }
    QStringList validlist;
#if C2B_DEBUG_COLLECTIONINDEX
    QStringList taggedvalidlist;
#endif

    for (QMap<QString, KeysentenceData>::const_iterator si = _keysentences.constBegin(); si != _keysentences.constEnd();
         ++si)
    {
        const QString& s(si.key());
        const KeysentenceData& sdata(si.value());
        if (sdata.ndocuments < _inter_document_sentence_repetition)
            continue;
        const QString pts(pt.tagged(s));
        if (pt.contains(pts))
        {
            validlist.append(s);
#if C2B_DEBUG_COLLECTIONINDEX
            taggedvalidlist.append(pts + "   " + s);
            for (int j = 0; j < sdata.documents.count(); ++j)
                _document_sentences.insert(sdata.documents.at(j), s);
#endif
        }
    }
    ussorting uss;
    std::sort(validlist.begin(), validlist.end(), uss);

    const QString cache_dir(_settingsP->fileName("cb2Bib/CacheDirectory"));
    const QString sentenceslfn(QDir::toNativeSeparators(QDir::cleanPath(cache_dir + "/sentences.lc2b")));
    QFile sentenceslf(sentenceslfn);
    if (sentenceslf.open(QIODevice::WriteOnly))
    {
        _out << QObject::tr("Writing %1...").arg(sentenceslfn) << endl;
        QDataStream stream(&sentenceslf);
        stream << validlist.count();
        const QChar hs('-');
        const QChar us('_');
        const QString ss("\\1 ");
        QRegularExpression aprx(_bpP->authorPrefixes() + '_', _qre_pattern_options);
        for (int i = 0; i < validlist.count(); ++i)
        {
            QString v(validlist.at(i));
            v.replace(aprx, ss);
            stream << v.replace(us, hs);
        }
        sentenceslf.close();
    }
    else
    {
        ++_nerrors;
        _out << QObject::tr("Error: %1 can not be written").arg(sentenceslfn) << endl;
    }
    const QString sentencesifn(QDir::toNativeSeparators(QDir::cleanPath(cache_dir + "/sentences.ic2b")));
    QFile sentencesif(sentencesifn);
    if (sentencesif.open(QIODevice::WriteOnly))
    {
        _out << QObject::tr("Writing %1...").arg(sentencesifn) << endl;
        QDataStream stream(&sentencesif);
        for (int i = 0; i < validlist.count(); ++i)
        {
            const QString& s(validlist.at(i));
            const KeysentenceData& sdata(_keysentences.value(s));
            QList<int> dl(sdata.documents);
            std::sort(dl.begin(), dl.end());
            stream << dl.count();
            for (int j = 0; j < dl.count(); ++j)
                stream << dl.at(j);
        }
        sentencesif.close();
    }
    else
    {
        ++_nerrors;
        _out << QObject::tr("Error: %1 can not be written").arg(sentencesifn) << endl;
    }
#ifdef C2B_TRACE_MEMORY
    qDebug() << "After writing sentencesifn:";
    c2bUtils::print_maximum_resident_set_size();
#endif
    const QString documentsifn(QDir::toNativeSeparators(cache_dir + "/documents.ic2b.tmp"));
    QFile documentsif(documentsifn);
    int document_sentenceids_count(0);
    if (documentsif.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&documentsif);
        for (int i = 0; i < validlist.count(); ++i)
        {
            const QString& s(validlist.at(i));
            const KeysentenceData& sdata(_keysentences.value(s));
            document_sentenceids_count += sdata.documents.count();
            for (int j = 0; j < sdata.documents.count(); ++j)
                stream << sdata.documents.at(j) << i;
        }
        documentsif.close();
    }
    else
    {
        ++_nerrors;
        _out << QObject::tr("Error: %1 can not be written").arg(documentsifn) << endl;
    }

    _out << QObject::tr("Raw keyword sentences: ") << _keysentences.size() << endl;
    _out << QObject::tr("Keyword sentences: ") << validlist.count() << endl;
    _out << QObject::tr("done") << endl;
#if !C2B_DEBUG_COLLECTIONINDEX
    _out << QObject::tr("Clearing arrays...") << endl;
    _keysentences.clear();
    _document_sentences.clear();
    _out << QObject::tr("done") << endl;
#endif
#ifdef C2B_TRACE_MEMORY
    qDebug() << "After clearing arrays:";
    c2bUtils::print_maximum_resident_set_size();
#endif
    if (documentsif.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&documentsif);
        for (int l = 0, d, i; l < document_sentenceids_count; ++l)
        {
            stream >> d >> i;
            _document_sentenceids.insert(d, i);
        }
        documentsif.close();
        documentsif.remove();
    }
    else
    {
        ++_nerrors;
        _out << QObject::tr("Error: %1 can not be read").arg(documentsifn) << endl;
    }
#ifdef C2B_TRACE_MEMORY
    qDebug() << "After inserting _document_sentenceids:";
    c2bUtils::print_maximum_resident_set_size();
#endif
#if C2B_DEBUG_COLLECTIONINDEX
    std::sort(taggedvalidlist.begin(), taggedvalidlist.end());
    for (int i = 0; i < taggedvalidlist.count(); ++i)
        _out << taggedvalidlist.at(i) << endl;
#endif
}

void collectionIndex::cleanupKeySentences()
{
    _out << QObject::tr("Cleaning keyword sentences...") << endl;

    QStringList keysentenceskeys;
    for (QMap<QString, KeysentenceData>::const_iterator si = _keysentences.constBegin(); si != _keysentences.constEnd();
         ++si)
    {
        if (si.value().ndocuments < _inter_document_sentence_repetition)
            continue;
        keysentenceskeys.append(si.key());
    }
    const int nkeysentenceskeys(keysentenceskeys.count());

    std::sort(keysentenceskeys.begin(), keysentenceskeys.end());
    for (int i = 0; i < nkeysentenceskeys - 1; ++i)
    {
        const QString& si(keysentenceskeys.at(i));
        const QString& sj(keysentenceskeys.at(i + 1));
        if (sj.startsWith(si) && _keysentences.value(si).ndocuments == _keysentences.value(sj).ndocuments)
            _keysentences[si].ndocuments = 0;
    }

    reversedsorting rs;
    std::sort(keysentenceskeys.begin(), keysentenceskeys.end(), rs);
    for (int i = 0; i < nkeysentenceskeys - 1; ++i)
    {
        const QString& si(keysentenceskeys.at(i));
        const QString& sj(keysentenceskeys.at(i + 1));
        if (sj.endsWith(si) && _keysentences.value(si).ndocuments == _keysentences.value(sj).ndocuments)
            _keysentences[si].ndocuments = 0;
    }
    _out << QObject::tr("done") << endl;
}

void collectionIndex::digestKeySentences()
{
    _out << QObject::tr("Digesting keyword sentences...") << endl;

    const QChar hyphen('_');

    const QString coordination_and(" and ");
    const QString coordination_in(" in ");
    const QString coordination_of(" of ");
    const QString coordination_on(" on ");
    const QString coordination_or(" or ");

    const QRegularExpression trailing_ae("ae\\b", _qre_pattern_options);
    const QRegularExpression trailing_ches("ches\\b", _qre_pattern_options);
    const QRegularExpression trailing_dices("dices\\b", _qre_pattern_options);
    const QRegularExpression trailing_ices("ices\\b", _qre_pattern_options);
    const QRegularExpression trailing_ies("ies\\b", _qre_pattern_options);
    const QRegularExpression trailing_is("is\\b", _qre_pattern_options);
    const QRegularExpression trailing_us("us\\b", _qre_pattern_options);
    const QRegularExpression trailing_s("s\\b", _qre_pattern_options);
    const QRegularExpression trailing_ss("ss\\b", _qre_pattern_options);
    const QRegularExpression trailing_sses("sses\\b", _qre_pattern_options);

    const QRegularExpression trailing_ap("'\\b", _qre_pattern_options);
    const QRegularExpression trailing_aps("'s\\b", _qre_pattern_options);

    for (QMap<QString, KeysentenceData>::iterator si = _keysentences.begin(); si != _keysentences.end(); ++si)
    {
        if (si.value().ndocuments == 0)
            continue;

        const QString& s(si.key());
        KeysentenceData* ksdndmax(&si.value());
        int ndmax(ksdndmax->ndocuments);

        // Unify hyphenation
        if (s.contains(hyphen))
        {
            QString sp(s);
            sp.remove(hyphen);
            if (_keysentences.contains(sp))
                ksdndmax = _digest_sentence(&_keysentences[sp], ksdndmax, &ndmax);
            sp = s;
            sp.replace(hyphen, _space_char);
            if (_keysentences.contains(sp))
                ksdndmax = _digest_sentence(&_keysentences[sp], ksdndmax, &ndmax);
        }

        // Unify simple coordinations
        if (s.count(coordination_and) == 1)
        {
            const QStringList p(s.split(coordination_and, QString::SkipEmptyParts));
            const QString sp(p.at(1) + coordination_and + p.at(0));
            if (_keysentences.contains(sp))
                ksdndmax = _digest_sentence(&_keysentences[sp], ksdndmax, &ndmax);
        }
        else if (s.count(coordination_or) == 1)
        {
            const QStringList p(s.split(coordination_or, QString::SkipEmptyParts));
            const QString sp(p.at(1) + coordination_or + p.at(0));
            if (_keysentences.contains(sp))
                ksdndmax = _digest_sentence(&_keysentences[sp], ksdndmax, &ndmax);
        }
        else if (s.count(coordination_of) == 1)
        {
            const QStringList p(s.split(coordination_of, QString::SkipEmptyParts));
            const QString sp(p.at(1) + _space_char + p.at(0));
            if (_keysentences.contains(sp))
                ksdndmax = _digest_sentence(&_keysentences[sp], ksdndmax, &ndmax);
        }
        else if (s.count(coordination_on) == 1)
        {
            const QStringList p(s.split(coordination_on, QString::SkipEmptyParts));
            const QString sp(p.at(1) + _space_char + p.at(0));
            if (_keysentences.contains(sp))
                ksdndmax = _digest_sentence(&_keysentences[sp], ksdndmax, &ndmax);
        }
        else if (s.count(coordination_in) == 1)
        {
            const QStringList p(s.split(coordination_in, QString::SkipEmptyParts));
            const QString sp(p.at(1) + _space_char + p.at(0));
            if (_keysentences.contains(sp))
                ksdndmax = _digest_sentence(&_keysentences[sp], ksdndmax, &ndmax);
        }

        // Unify genitives
        if (s.contains(trailing_aps) || s.contains(trailing_ap))
        {
            QString sp(s);
            sp.remove(trailing_aps);
            sp.remove(trailing_ap);
            if (s.length() != sp.length() && _keysentences.contains(sp))
                ksdndmax = _digest_sentence(&_keysentences[sp], ksdndmax, &ndmax);
        }

        // Unify number
        if (s.contains(trailing_s) || s.contains(trailing_ae))
        {
            QString sp(s);
            sp.replace(trailing_dices, "dex");
            sp.replace(trailing_ices, "ix");
            sp.replace(trailing_ae, "a");
            sp.replace(trailing_ies, "y");
            sp.replace(trailing_ches, "ch");
            sp.replace(trailing_ss, "sss");
            sp.replace(trailing_us, "uss");
            sp.replace(trailing_aps, "'ss");
            sp.replace(trailing_sses, "sss");
            sp.replace(trailing_is, "iss");
            sp.remove(trailing_s);
            if (s.length() != sp.length() && _keysentences.contains(sp))
                ksdndmax = _digest_sentence(&_keysentences[sp], ksdndmax, &ndmax);
        }

        ksdndmax->ndocuments = ksdndmax->documents.count();
    }

    _out << QObject::tr("done") << endl;
}

collectionIndex::KeysentenceData* collectionIndex::_digest_sentence(KeysentenceData* ksd, KeysentenceData* ksdndmax,
        int* ndmax) const
{
    if (ksd->ndocuments > *ndmax)
    {
        // Transfer from ksdndmax
        *ndmax = ksd->ndocuments;
        const int nd(ksdndmax->documents.count());
        for (int i = 0; i < nd; ++i)
        {
            const int did(ksdndmax->documents.at(i));
            if (!ksd->documents.contains(did))
                ksd->documents.append(did);
        }
        ksdndmax->ndocuments = 0;
        return ksd;
    }
    else
    {
        // Transfer to ksdndmax
        const int nd(ksd->documents.count());
        for (int i = 0; i < nd; ++i)
        {
            const int did(ksd->documents.at(i));
            if (!ksdndmax->documents.contains(did))
                ksdndmax->documents.append(did);
        }
        ksd->ndocuments = 0;
        return ksdndmax;
    }
}

bool collectionIndex::isValidKeySentence(const QString& text) const
{
    const ushort fc(text.at(0).unicode());
    if (fc == 39)
        return false;
    if (fc == 95)
        return false;
    if (fc == 97)
    {
        if (text.startsWith(QLatin1String("a ")))
            return false;
        if (text.startsWith(QLatin1String("ability ")))
            return false;
        if (text.startsWith(QLatin1String("able ")))
            return false;
        if (text.startsWith(QLatin1String("about ")))
            return false;
        if (text.startsWith(QLatin1String("above ")))
            return false;
        if (text.startsWith(QLatin1String("academy of ")))
            return false;
        if (text.startsWith(QLatin1String("according ")))
            return false;
        if (text.startsWith(QLatin1String("acknowledgment ")))
            return false;
        if (text.startsWith(QLatin1String("across ")))
            return false;
        if (text.startsWith(QLatin1String("added ")))
            return false;
        if (text.startsWith(QLatin1String("advances in ")))
            return false;
        if (text.startsWith(QLatin1String("after ")))
            return false;
        if (text.startsWith(QLatin1String("agreement ")))
            return false;
        if (text.startsWith(QLatin1String("all ")) && text.count(_space_char) < 3)
            return false;
        if (text.startsWith(QLatin1String("along ")))
            return false;
        if (text.startsWith(QLatin1String("also ")))
            return false;
        if (text.startsWith(QLatin1String("although ")))
            return false;
        if (text.startsWith(QLatin1String("among ")))
            return false;
        if (text.startsWith(QLatin1String("an ")))
            return false;
        if (text.startsWith(QLatin1String("and ")))
            return false;
        if (text.startsWith(QLatin1String("annals of ")))
            return false;
        if (text.startsWith(QLatin1String("any ")) && text.count(_space_char) < 3)
            return false;
        if (text.startsWith(QLatin1String("are ")))
            return false;
        if (text.startsWith(QLatin1String("as ")))
            return false;
        if (text.startsWith(QLatin1String("at ")))
            return false;
        if (text.startsWith(QLatin1String("author ")))
            return false;
        if (text.startsWith(QLatin1String("author's ")))
            return false;
        if (text.startsWith(QLatin1String("authors ")))
            return false;
    }
    else if (fc == 98)
    {
        if (text.startsWith(QLatin1String("based on ")))
            return false;
        if (text.startsWith(QLatin1String("be ")))
            return false;
        if (text.startsWith(QLatin1String("been ")))
            return false;
        if (text.startsWith(QLatin1String("before ")))
            return false;
        if (text.startsWith(QLatin1String("between ")))
            return false;
        if (text.startsWith(QLatin1String("both ")))
            return false;
        if (text.startsWith(QLatin1String("but ")))
            return false;
        if (text.startsWith(QLatin1String("by ")))
            return false;
    }
    else if (fc == 99)
    {
        if (text.startsWith(QLatin1String("calculated ")) && text.count(_space_char) < 3)
            return false;
        if (text.startsWith(QLatin1String("calculations ")))
            return false;
        if (text.startsWith(QLatin1String("can ")))
            return false;
        if (text.startsWith(QLatin1String("cannot ")))
            return false;
        if (text.startsWith(QLatin1String("capable ")))
            return false;
        if (text.startsWith(QLatin1String("carried ")))
            return false;
        if (text.startsWith(QLatin1String("case ")))
            return false;
        if (text.startsWith(QLatin1String("chapter ")))
            return false;
        if (text.startsWith(QLatin1String("chapters ")))
            return false;
        if (text.startsWith(QLatin1String("college of ")))
            return false;
        if (text.startsWith(QLatin1String("come ")))
            return false;
        if (text.startsWith(QLatin1String("conference on ")))
            return false;
        if (text.startsWith(QLatin1String("contribution from ")))
            return false;
        if (text.startsWith(QLatin1String("corresponding ")))
            return false;
        if (text.startsWith(QLatin1String("could ")))
            return false;
        if (text.startsWith(QLatin1String("current ")))
            return false;
        if (text.startsWith(QLatin1String("currently ")))
            return false;
    }
    else if (fc == 100)
    {
        if (text.startsWith(QLatin1String("data ")))
            return false;
        if (text.startsWith(QLatin1String("de ")))
            return false;
        if (text.startsWith(QLatin1String("department ")))
            return false;
        if (text.startsWith(QLatin1String("depicted ")))
            return false;
        if (text.startsWith(QLatin1String("depicts ")))
            return false;
        if (text.startsWith(QLatin1String("der ")))
            return false;
        if (text.startsWith(QLatin1String("described ")))
            return false;
        if (text.startsWith(QLatin1String("detailed ")))
            return false;
        if (text.startsWith(QLatin1String("details ")))
            return false;
        if (text.startsWith(QLatin1String("determined ")))
            return false;
        if (text.startsWith(QLatin1String("did not ")))
            return false;
        if (text.startsWith(QLatin1String("different ")) && text.count(_space_char) < 3)
            return false;
        if (text.startsWith(QLatin1String("difficult ")))
            return false;
        if (text.startsWith(QLatin1String("discussed ")))
            return false;
        if (text.startsWith(QLatin1String("dissolved ")))
            return false;
        if (text.startsWith(QLatin1String("do ")))
            return false;
        if (text.startsWith(QLatin1String("does ")))
            return false;
        if (text.startsWith(QLatin1String("due ")) && text.count(_space_char) < 3)
            return false;
        if (text.startsWith(QLatin1String("during ")))
            return false;
    }
    else if (fc == 101)
    {
        if (text.startsWith(QLatin1String("each ")))
            return false;
        if (text.startsWith(QLatin1String("easily ")))
            return false;
        if (text.startsWith(QLatin1String("easy ")))
            return false;
        if (text.startsWith(QLatin1String("edited ")))
            return false;
        if (text.startsWith(QLatin1String("effect ")) && text.count(_space_char) < 3)
            return false;
        if (text.startsWith(QLatin1String("effects ")) && text.count(_space_char) < 3)
            return false;
        if (text.startsWith(QLatin1String("either ")))
            return false;
        if (text.startsWith(QLatin1String("elsevier ")))
            return false;
    }
    else if (fc == 102)
    {
        if (text.startsWith(QLatin1String("faculty of ")))
            return false;
        if (text.startsWith(QLatin1String("figure ")))
            return false;
        if (text.startsWith(QLatin1String("figures ")))
            return false;
        if (text.startsWith(QLatin1String("find ")))
            return false;
        if (text.startsWith(QLatin1String("finding ")))
            return false;
        if (text.startsWith(QLatin1String("findings ")))
            return false;
        if (text.startsWith(QLatin1String("first ")) && text.count(_space_char) < 3)
            return false;
        if (text.startsWith(QLatin1String("followed ")))
            return false;
        if (text.startsWith(QLatin1String("following ")))
            return false;
        if (text.startsWith(QLatin1String("footnote ")))
            return false;
        if (text.startsWith(QLatin1String("for ")))
            return false;
        if (text.startsWith(QLatin1String("form ")))
            return false;
        if (text.startsWith(QLatin1String("found ")))
            return false;
        if (text.startsWith(QLatin1String("foundation ")))
            return false;
        if (text.startsWith(QLatin1String("free of charge ")))
            return false;
        if (text.startsWith(QLatin1String("from ")))
            return false;
        if (text.startsWith(QLatin1String("fur ")))
            return false;
        if (text.startsWith(QLatin1String("further ")))
            return false;
    }
    else if (fc == 103)
    {
        if (text.startsWith(QLatin1String("gave ")))
            return false;
        if (text.startsWith(QLatin1String("give ")))
            return false;
        if (text.startsWith(QLatin1String("given ")))
            return false;
        if (text.startsWith(QLatin1String("gives ")))
            return false;
        if (text.startsWith(QLatin1String("go ")))
            return false;
        if (text.startsWith(QLatin1String("goes ")))
            return false;
        if (text.startsWith(QLatin1String("going ")))
            return false;
        if (text.startsWith(QLatin1String("groups ")))
            return false;
    }
    else if (fc == 104)
    {
        if (text.startsWith(QLatin1String("has ")))
            return false;
        if (text.startsWith(QLatin1String("have ")))
            return false;
        if (text.startsWith(QLatin1String("he ")))
            return false;
        if (text.startsWith(QLatin1String("highlighted ")))
            return false;
        if (text.startsWith(QLatin1String("his ")))
            return false;
        if (text.startsWith(QLatin1String("how ")))
            return false;
    }
    else if (fc == 105)
    {
        if (text.startsWith(QLatin1String("i ")))
            return false;
        if (text.startsWith(QLatin1String("if ")))
            return false;
        if (text.startsWith(QLatin1String("ii ")))
            return false;
        if (text.startsWith(QLatin1String("iii ")))
            return false;
        if (text.startsWith(QLatin1String("in ")))
            return false;
        if (text.startsWith(QLatin1String("initially ")))
            return false;
        if (text.startsWith(QLatin1String("int j ")))
            return false;
        if (text.startsWith(QLatin1String("international conference on ")))
            return false;
        if (text.startsWith(QLatin1String("international journal ")))
            return false;
        if (text.startsWith(QLatin1String("into ")))
            return false;
        if (text.startsWith(QLatin1String("is ")))
            return false;
        if (text.startsWith(QLatin1String("it ")))
            return false;
        if (text.startsWith(QLatin1String("its ")))
            return false;
    }
    else if (fc == 106)
    {
        if (text.startsWith(QLatin1String("j ")))
            return false;
        if (text.startsWith(QLatin1String("journal of ")))
            return false;
        if (text.startsWith(QLatin1String("journal on ")))
            return false;
        if (text.startsWith(QLatin1String("just ")))
            return false;
    }
    else if (fc == 107)
    {
        if (text.startsWith(QLatin1String("kept ")))
            return false;
    }
    else if (fc == 108)
    {
        if (text.startsWith(QLatin1String("laboratory for ")))
            return false;
        if (text.startsWith(QLatin1String("laboratory of ")))
            return false;
        if (text.startsWith(QLatin1String("larger ")))
            return false;
        if (text.startsWith(QLatin1String("less ")))
            return false;
        if (text.startsWith(QLatin1String("let ")))
            return false;
        if (text.startsWith(QLatin1String("lower ")))
            return false;
    }
    else if (fc == 109)
    {
        if (text.startsWith(QLatin1String("may ")))
            return false;
        if (text.startsWith(QLatin1String("mol ")))
            return false;
        if (text.startsWith(QLatin1String("more ")))
            return false;
        if (text.startsWith(QLatin1String("most ")) && text.count(_space_char) < 3)
            return false;
        if (text.startsWith(QLatin1String("much ")) && text.count(_space_char) < 3)
            return false;
        if (text.startsWith(QLatin1String("my ")))
            return false;
    }
    else if (fc == 110)
    {
        if (text.startsWith(QLatin1String("national academy of ")))
            return false;
        if (text.startsWith(QLatin1String("need ")))
            return false;
        if (text.startsWith(QLatin1String("new ")))
            return false;
        if (text.startsWith(QLatin1String("not ")) && text.count(_space_char) < 3)
            return false;
    }
    else if (fc == 111)
    {
        if (text.startsWith(QLatin1String("observed ")))
            return false;
        if (text.startsWith(QLatin1String("obtained ")))
            return false;
        if (text.startsWith(QLatin1String("occur ")))
            return false;
        if (text.startsWith(QLatin1String("occurs ")))
            return false;
        if (text.startsWith(QLatin1String("of ")))
            return false;
        if (text.startsWith(QLatin1String("office ")))
            return false;
        if (text.startsWith(QLatin1String("on ")))
            return false;
        if (text.startsWith(QLatin1String("only ")))
            return false;
        if (text.startsWith(QLatin1String("onto ")))
            return false;
        if (text.startsWith(QLatin1String("or ")))
            return false;
        if (text.startsWith(QLatin1String("other ")))
            return false;
        if (text.startsWith(QLatin1String("otherwise ")))
            return false;
        if (text.startsWith(QLatin1String("our ")))
            return false;
        if (text.startsWith(QLatin1String("over ")))
            return false;
    }
    else if (fc == 112)
    {
        if (text.startsWith(QLatin1String("per ")))
            return false;
        if (text.startsWith(QLatin1String("permission of ")))
            return false;
        if (text.startsWith(QLatin1String("play ")))
            return false;
        if (text.startsWith(QLatin1String("played ")))
            return false;
        if (text.startsWith(QLatin1String("please ")))
            return false;
        if (text.startsWith(QLatin1String("possible ")))
            return false;
        if (text.startsWith(QLatin1String("present")))
            return false;
        if (text.startsWith(QLatin1String("previous ")))
            return false;
        if (text.startsWith(QLatin1String("proceedings ")))
            return false;
        if (text.startsWith(QLatin1String("proof ")))
            return false;
    }
    else if (fc == 113)
    {
        if (text.startsWith(QLatin1String("quite ")))
            return false;
    }
    else if (fc == 114)
    {
        if (text.startsWith(QLatin1String("rather ")))
            return false;
        if (text.startsWith(QLatin1String("rest of ")))
            return false;
        if (text.startsWith(QLatin1String("result of ")))
            return false;
        if (text.startsWith(QLatin1String("reviews in ")))
            return false;
        if (text.startsWith(QLatin1String("run ")))
            return false;
    }
    else if (fc == 115)
    {
        if (text.startsWith(QLatin1String("same ")))
            return false;
        if (text.startsWith(QLatin1String("see ")))
            return false;
        if (text.startsWith(QLatin1String("several ")))
            return false;
        if (text.startsWith(QLatin1String("shall ")))
            return false;
        if (text.startsWith(QLatin1String("show ")))
            return false;
        if (text.startsWith(QLatin1String("shown ")))
            return false;
        if (text.startsWith(QLatin1String("since ")))
            return false;
        if (text.startsWith(QLatin1String("so ")))
            return false;
        if (text.startsWith(QLatin1String("some ")))
            return false;
        if (text.startsWith(QLatin1String("strongly ")))
            return false;
        if (text.startsWith(QLatin1String("studied ")))
            return false;
        if (text.startsWith(QLatin1String("studies ")))
            return false;
        if (text.startsWith(QLatin1String("study ")))
            return false;
        if (text.startsWith(QLatin1String("such ")))
            return false;
        if (text.startsWith(QLatin1String("supporting ")))
            return false;
        if (text.startsWith(QLatin1String("suppose ")))
            return false;
        if (text.startsWith(QLatin1String("symposium on ")))
            return false;
    }
    else if (fc == 116)
    {
        if (text.startsWith(QLatin1String("than ")))
            return false;
        if (text.startsWith(QLatin1String("thank ")))
            return false;
        if (text.startsWith(QLatin1String("that ")))
            return false;
        if (text.startsWith(QLatin1String("the ")))
            return false;
        if (text.startsWith(QLatin1String("their ")))
            return false;
        if (text.startsWith(QLatin1String("then ")))
            return false;
        if (text.startsWith(QLatin1String("there ")))
            return false;
        if (text.startsWith(QLatin1String("these ")))
            return false;
        if (text.startsWith(QLatin1String("they ")))
            return false;
        if (text.startsWith(QLatin1String("this ")))
            return false;
        if (text.startsWith(QLatin1String("those ")))
            return false;
        if (text.startsWith(QLatin1String("thus ")))
            return false;
        if (text.startsWith(QLatin1String("title ")))
            return false;
        if (text.startsWith(QLatin1String("to ")))
            return false;
        if (text.startsWith(QLatin1String("too ")))
            return false;
        if (text.startsWith(QLatin1String("top ")))
            return false;
        if (text.startsWith(QLatin1String("transactions on ")))
            return false;
    }
    else if (fc == 117)
    {
        if (text.startsWith(QLatin1String("under ")))
            return false;
        if (text.startsWith(QLatin1String("us ")))
            return false;
        if (text.startsWith(QLatin1String("use ")))
            return false;
        if (text.startsWith(QLatin1String("used ")))
            return false;
        if (text.startsWith(QLatin1String("uses ")))
            return false;
        if (text.startsWith(QLatin1String("using ")))
            return false;
    }
    else if (fc == 118)
    {
        if (text.startsWith(QLatin1String("very ")) && text.count(_space_char) < 3)
            return false;
    }
    else if (fc == 119)
    {
        if (text.startsWith(QLatin1String("was ")))
            return false;
        if (text.startsWith(QLatin1String("we ")))
            return false;
        if (text.startsWith(QLatin1String("were ")))
            return false;
        if (text.startsWith(QLatin1String("were ")))
            return false;
        if (text.startsWith(QLatin1String("what ")))
            return false;
        if (text.startsWith(QLatin1String("when ")))
            return false;
        if (text.startsWith(QLatin1String("whenever ")))
            return false;
        if (text.startsWith(QLatin1String("where ")))
            return false;
        if (text.startsWith(QLatin1String("whether ")))
            return false;
        if (text.startsWith(QLatin1String("which ")))
            return false;
        if (text.startsWith(QLatin1String("while ")))
            return false;
        if (text.startsWith(QLatin1String("whose ")))
            return false;
        if (text.startsWith(QLatin1String("wiley ")))
            return false;
        if (text.startsWith(QLatin1String("will ")))
            return false;
        if (text.startsWith(QLatin1String("with ")))
            return false;
        if (text.startsWith(QLatin1String("within ")))
            return false;
        if (text.startsWith(QLatin1String("without ")))
            return false;
        if (text.startsWith(QLatin1String("work ")))
            return false;
        if (text.startsWith(QLatin1String("workshop on ")))
            return false;
        if (text.startsWith(QLatin1String("worth ")))
            return false;
        if (text.startsWith(QLatin1String("would ")))
            return false;
    }
    else if (fc == 120)
    {
        if (text.startsWith(QLatin1String("x ")))
            return false;
    }
    else if (fc == 121)
    {
        if (text.startsWith(QLatin1String("yes ")))
            return false;
        if (text.startsWith(QLatin1String("you ")))
            return false;
        if (text.startsWith(QLatin1String("your ")))
            return false;
    }

    const ushort lc(text.at(text.length() - 1).unicode());
    if (lc == 95)
        return false;
    if (lc == 97)
    {
        if (text.endsWith(QLatin1String(" a")))
            return false;
        if (text.endsWith(QLatin1String(" via")))
            return false;
    }
    else if (lc == 100)
    {
        if (text.endsWith(QLatin1String(" and")))
            return false;
        if (text.endsWith(QLatin1String(" applied")))
            return false;
        if (text.endsWith(QLatin1String(" carried")))
            return false;
        if (text.endsWith(QLatin1String(" could")))
            return false;
        if (text.endsWith(QLatin1String(" performed")))
            return false;
        if (text.endsWith(QLatin1String(" second")))
            return false;
        if (text.endsWith(QLatin1String(" should")))
            return false;
        if (text.endsWith(QLatin1String(" showed")))
            return false;
        if (text.endsWith(QLatin1String(" third")))
            return false;
        if (text.endsWith(QLatin1String(" used")))
            return false;
        if (text.endsWith(QLatin1String(" would")))
            return false;
    }
    else if (lc == 101)
    {
        if (text.endsWith(QLatin1String(" above")))
            return false;
        if (text.endsWith(QLatin1String(" are")))
            return false;
        if (text.endsWith(QLatin1String(" available")))
            return false;
        if (text.endsWith(QLatin1String(" be")))
            return false;
        if (text.endsWith(QLatin1String(" because")))
            return false;
        if (text.endsWith(QLatin1String(" due")))
            return false;
        if (text.endsWith(QLatin1String(" gave")))
            return false;
        if (text.endsWith(QLatin1String(" have")))
            return false;
        if (text.endsWith(QLatin1String(" he")))
            return false;
        if (text.endsWith(QLatin1String(" here")))
            return false;
        if (text.endsWith(QLatin1String(" importance")))
            return false;
        if (text.endsWith(QLatin1String(" indicate")))
            return false;
        if (text.endsWith(QLatin1String(" like")))
            return false;
        if (text.endsWith(QLatin1String(" made")))
            return false;
        if (text.endsWith(QLatin1String(" more")))
            return false;
        if (text.endsWith(QLatin1String(" same")))
            return false;
        if (text.endsWith(QLatin1String(" since")))
            return false;
        if (text.endsWith(QLatin1String(" the")))
            return false;
        if (text.endsWith(QLatin1String(" there")))
            return false;
        if (text.endsWith(QLatin1String(" these")))
            return false;
        if (text.endsWith(QLatin1String(" we")))
            return false;
        if (text.endsWith(QLatin1String(" were")))
            return false;
        if (text.endsWith(QLatin1String(" where")))
            return false;
        if (text.endsWith(QLatin1String(" where")))
            return false;
        if (text.endsWith(QLatin1String(" while")))
            return false;
        if (text.endsWith(QLatin1String(" whose")))
            return false;
    }
    else if (lc == 102)
    {
        if (text.endsWith(QLatin1String(" if")))
            return false;
        if (text.endsWith(QLatin1String(" of")))
            return false;
    }
    else if (lc == 103)
    {
        if (text.endsWith(QLatin1String(" according")))
            return false;
        if (text.endsWith(QLatin1String(" along")))
            return false;
        if (text.endsWith(QLatin1String(" belonging")))
            return false;
        if (text.endsWith(QLatin1String(" containing")))
            return false;
        if (text.endsWith(QLatin1String(" corresponding")))
            return false;
        if (text.endsWith(QLatin1String(" during")))
            return false;
        if (text.endsWith(QLatin1String(" fig")))
            return false;
        if (text.endsWith(QLatin1String(" having")))
            return false;
        if (text.endsWith(QLatin1String(" involving")))
            return false;
        if (text.endsWith(QLatin1String(" using")))
            return false;
    }
    else if (lc == 104)
    {
        if (text.endsWith(QLatin1String(" although")))
            return false;
        if (text.endsWith(QLatin1String(" both")))
            return false;
        if (text.endsWith(QLatin1String(" much")))
            return false;
        if (text.endsWith(QLatin1String(" such")))
            return false;
        if (text.endsWith(QLatin1String(" through")))
            return false;
        if (text.endsWith(QLatin1String(" which")))
            return false;
        if (text.endsWith(QLatin1String(" with")))
            return false;
    }
    else if (lc == 105)
    {
        if (text.endsWith(QLatin1String(" i")))
            return false;
    }
    else if (lc == 108)
    {
        if (text.endsWith(QLatin1String(" all")))
            return false;
        if (text.endsWith(QLatin1String(" several")))
            return false;
        if (text.endsWith(QLatin1String(" will")))
            return false;
    }
    else if (lc == 109)
    {
        if (text.endsWith(QLatin1String(" from")))
            return false;
        if (text.endsWith(QLatin1String(" them")))
            return false;
    }
    else if (lc == 110)
    {
        if (text.endsWith(QLatin1String(" an")))
            return false;
        if (text.endsWith(QLatin1String(" been")))
            return false;
        if (text.endsWith(QLatin1String(" between")))
            return false;
        if (text.endsWith(QLatin1String(" can")))
            return false;
        if (text.endsWith(QLatin1String(" in")))
            return false;
        if (text.endsWith(QLatin1String(" known")))
            return false;
        if (text.endsWith(QLatin1String(" on")))
            return false;
        if (text.endsWith(QLatin1String(" shown")))
            return false;
        if (text.endsWith(QLatin1String(" shown")))
            return false;
        if (text.endsWith(QLatin1String(" supporting information")))
            return false;
        if (text.endsWith(QLatin1String(" taken")))
            return false;
        if (text.endsWith(QLatin1String(" than")))
            return false;
        if (text.endsWith(QLatin1String(" then")))
            return false;
        if (text.endsWith(QLatin1String(" upon")))
            return false;
        if (text.endsWith(QLatin1String(" when")))
            return false;
        if (text.endsWith(QLatin1String(" within")))
            return false;
    }
    else if (lc == 111)
    {
        if (text.endsWith(QLatin1String(" also")))
            return false;
        if (text.endsWith(QLatin1String(" do")))
            return false;
        if (text.endsWith(QLatin1String(" into")))
            return false;
        if (text.endsWith(QLatin1String(" to")))
            return false;
        if (text.endsWith(QLatin1String(" two")))
            return false;
        if (text.endsWith(QLatin1String(" who")))
            return false;
    }
    else if (lc == 114)
    {
        if (text.endsWith(QLatin1String(" after")))
            return false;
        if (text.endsWith(QLatin1String(" chapter")))
            return false;
        if (text.endsWith(QLatin1String(" elsevier")))
            return false;
        if (text.endsWith(QLatin1String(" for")))
            return false;
        if (text.endsWith(QLatin1String(" or")))
            return false;
        if (text.endsWith(QLatin1String(" our")))
            return false;
        if (text.endsWith(QLatin1String(" over")))
            return false;
        if (text.endsWith(QLatin1String(" per")))
            return false;
        if (text.endsWith(QLatin1String(" their")))
            return false;
        if (text.endsWith(QLatin1String(" under")))
            return false;
        if (text.endsWith(QLatin1String(" whether")))
            return false;
        if (text.endsWith(QLatin1String(" your")))
            return false;
    }
    else if (lc == 115)
    {
        if (text.endsWith(QLatin1String(" across")))
            return false;
        if (text.endsWith(QLatin1String(" as")))
            return false;
        if (text.endsWith(QLatin1String(" does")))
            return false;
        if (text.endsWith(QLatin1String(" does")))
            return false;
        if (text.endsWith(QLatin1String(" figs")))
            return false;
        if (text.endsWith(QLatin1String(" follows")))
            return false;
        if (text.endsWith(QLatin1String(" gives")))
            return false;
        if (text.endsWith(QLatin1String(" has")))
            return false;
        if (text.endsWith(QLatin1String(" his")))
            return false;
        if (text.endsWith(QLatin1String(" is")))
            return false;
        if (text.endsWith(QLatin1String(" its")))
            return false;
        if (text.endsWith(QLatin1String(" ones")))
            return false;
        if (text.endsWith(QLatin1String(" shows")))
            return false;
        if (text.endsWith(QLatin1String(" this")))
            return false;
        if (text.endsWith(QLatin1String(" us")))
            return false;
        if (text.endsWith(QLatin1String(" was")))
            return false;
        if (text.endsWith(QLatin1String(" yes")))
            return false;
        if (text.endsWith(QLatin1String("acids res")))
            return false;
    }
    else if (lc == 116)
    {
        if (text.endsWith(QLatin1String(" about")))
            return false;
        if (text.endsWith(QLatin1String(" at")))
            return false;
        if (text.endsWith(QLatin1String(" department")))
            return false;
        if (text.endsWith(QLatin1String(" et")))
            return false;
        if (text.endsWith(QLatin1String(" first")))
            return false;
        if (text.endsWith(QLatin1String(" important")))
            return false;
        if (text.endsWith(QLatin1String(" it")))
            return false;
        if (text.endsWith(QLatin1String(" let")))
            return false;
        if (text.endsWith(QLatin1String(" most")))
            return false;
        if (text.endsWith(QLatin1String(" must")))
            return false;
        if (text.endsWith(QLatin1String(" not")))
            return false;
        if (text.endsWith(QLatin1String(" out")))
            return false;
        if (text.endsWith(QLatin1String(" suggest")))
            return false;
        if (text.endsWith(QLatin1String(" that")))
            return false;
        if (text.endsWith(QLatin1String(" without")))
            return false;
    }
    else if (lc == 117)
    {
        if (text.endsWith(QLatin1String(" you")))
            return false;
    }
    else if (lc == 119)
    {
        if (text.endsWith(QLatin1String(" how")))
            return false;
        if (text.endsWith(QLatin1String(" new")))
            return false;
        if (text.endsWith(QLatin1String(" show")))
            return false;
    }
    else if (lc == 121)
    {
        if (text.endsWith(QLatin1String(" any")))
            return false;
        if (text.endsWith(QLatin1String(" by")))
            return false;
        if (text.endsWith(QLatin1String(" may")))
            return false;
        if (text.endsWith(QLatin1String(" my")))
            return false;
        if (text.endsWith(QLatin1String(" only")))
            return false;
        if (text.endsWith(QLatin1String(" society")))
            return false;
        if (text.endsWith(QLatin1String(" they")))
            return false;
        if (text.endsWith(QLatin1String(" wiley")))
            return false;
    }

    if (text.contains(QLatin1String("_ ")))
        return false;
    if (text.contains(QLatin1String(" _")))
        return false;

    if (_last_equals_first(text))
        return false;

    return true;
}

QString collectionIndex::preprocessedText(const QString& journal, const QString& text) const
{
    QString pt(text.toLower());
    if (journal.contains(_space_char))
    {
        QStringList jns;
        jns.append(journal.toLower());
        jns.append(_bpP->fullJournal(journal).toLower());
        jns.append(_bpP->abbreviatedJournal(journal).toLower());
        jns.append(QString(jns.at(0)).remove('.'));
        jns.append(QString(jns.at(1)).remove('.'));
        jns.append(QString(jns.at(2)).remove('.'));
        jns.removeDuplicates();
        for (int i = 0; i < jns.count(); ++i)
            c2bUtils::fillString(pt, QStringMatcher(jns.at(i), Qt::CaseSensitive), '.');
    }

    c2bUtils::fillString(pt, txtmatcher("\"", Qt::CaseSensitive, 0), ' ');
    c2bUtils::fillString(pt, txtmatcher("-", Qt::CaseSensitive, 0), '_');
    pt.replace(QRegularExpression("_{2,}", _qre_pattern_options), "_");

    pt.replace(QRegularExpression("\\bin *situ\\b", _qre_pattern_options), " in_situ ");
    pt.replace(QRegularExpression("\\bin *vivo\\b", _qre_pattern_options), " in_vivo ");
    pt.replace(QRegularExpression("\\bin *vitro\\b", _qre_pattern_options), " in_vitro ");
    pt.replace(QRegularExpression("\\bex *situ\\b", _qre_pattern_options), " ex_situ ");
    pt.replace(QRegularExpression("\\bex *vivo\\b", _qre_pattern_options), " ex_vivo ");
    pt.replace(QRegularExpression("\\bex *vitro\\b", _qre_pattern_options), " ex_vitro ");

    // Clear some strings
    c2bUtils::fillString(pt, QRegularExpression("\\bbased (?=on\\b)", _qre_pattern_options), ' ');
    c2bUtils::fillString(pt, QRegularExpression("\\bin order (?=to\\b)", _qre_pattern_options), ' ');

    c2bUtils::fillString(pt, txtmatcher(" a ", Qt::CaseSensitive, 0), ' ');
    c2bUtils::fillString(pt, txtmatcher(" an ", Qt::CaseSensitive, 2), ' ');
    c2bUtils::fillString(pt, txtmatcher(" its ", Qt::CaseSensitive, 3), ' ');
    c2bUtils::fillString(pt, txtmatcher(" the ", Qt::CaseSensitive, 2), ' ');
    c2bUtils::fillString(pt, txtmatcher(" their ", Qt::CaseSensitive, 2), ' ');
    c2bUtils::fillString(pt, txtmatcher(" '", Qt::CaseSensitive, 1), ' ');
    c2bUtils::fillString(pt, txtmatcher("' ", Qt::CaseSensitive, 0), ' ');

    // Set additional breakpoints
    c2bUtils::fillString(pt, txtmatcher(" are ", Qt::CaseSensitive, 2), '.');
    c2bUtils::fillString(pt, txtmatcher(" be ", Qt::CaseSensitive, 1), '.');
    c2bUtils::fillString(pt, txtmatcher(" is ", Qt::CaseSensitive, 2), '.');
    c2bUtils::fillString(pt, txtmatcher(" was ", Qt::CaseSensitive, 1), '.');
    c2bUtils::fillString(pt, txtmatcher(" were ", Qt::CaseSensitive, 1), '.');

    c2bUtils::fillString(pt, QRegularExpression("\\binstitut\\w*", _qre_pattern_options), '.');
    c2bUtils::fillString(pt, QRegularExpression("\\buniversi\\w*", _qre_pattern_options), '.');
    c2bUtils::fillString(pt, QRegularExpression("\\bdoi\\w*", _qre_pattern_options), '.');
    c2bUtils::fillString(pt, QRegularExpression("\\bet al\\w*", _qre_pattern_options), '.');

    // Normalize proper names
    c2bUtils::fillString(pt, QRegularExpression("\\bdo not\\b", _qre_pattern_options), '.');
    pt.replace(QRegularExpression("\\b" + _bpP->authorPrefixes() + "\\s", _qre_pattern_options),
               QString("\\1%1").arg(QChar(127)));
    replace(pt, QChar(127), '_');

    // Remove noisy elements from PDF articles
    c2bUtils::fillString(pt, QStringMatcher("page intentionally left", Qt::CaseSensitive), '.');
    c2bUtils::fillString(pt, QStringMatcher("journal article", Qt::CaseSensitive), '.');
    c2bUtils::fillString(pt, QRegularExpression(" \\w \\w \\w ", _qre_pattern_options), '.');

    c2bUtils::stripDiacritics(pt);
    c2bUtils::simplifyString(pt);

    return pt;
}

QString& collectionIndex::replace(QString& str, const QChar& a, const QChar& b) const
{
    const int length(str.length());
    QChar* const s(str.data());
    int i(0);
    while (i < length)
    {
        QChar& c(s[i]);
        if (c == a)
            c = b;
        ++i;
    }
    return str;
}
