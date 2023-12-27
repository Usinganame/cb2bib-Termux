/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#define C2B_CHECK_CAPITALIZATION 0
#define C2B_CHECK_CODE_DECOMPOSITION 0
#define C2B_CHECK_JOURNALS 0
#define C2B_CHECK_PATTERNS 0
#define C2B_CHECK_PDF_AUTHORS 0
#define C2B_CHECK_PDF_CODES 0
#include "c2bTests.h"

#include <bibParser.h>
#include <document.h>
#include <settings.h>
#include <txtmatcher.h>

#include <QCoreApplication>
#include <QDataStream>
#include <QSysInfo>
#include <QTextStream>


c2bTests::c2bTests() : cout(*(new QTextStream(stdout))), _failed_test_count(0), _test_count(0)
{
    cout.setCodec("UTF-8");

    cout << "============" << endl;
    cout << "cb2Bib tests" << endl;
    cout << "============" << endl;
    _bibliographic_dir = QFileInfo(settings::instance()->fileName("cb2Bib/BibTeXFile")).absolutePath();
}

c2bTests::~c2bTests()
{
    cout << endl;
    cout << "=================" << endl;
    cout << "cb2Bib tests done" << endl;
    cout << "=================" << endl << endl;
    delete &cout;
}


int c2bTests::allTests()
{
    _test_count = 0;
    _failed_test_count = 0;
#if C2B_CHECK_PATTERNS
    heuristic_check_patterns();
    return 0;
#endif
#if C2B_CHECK_JOURNALS
    check_abbreviations_txt();
    heuristic_journal();
#else
    author_parser();
    heuristic_pvny();
    heuristic_misc();
    heuristic_author();
    heuristic_check_patterns();
    compression_check();
    write_information();
#endif
    cout << endl << endl;
    cout << "Tests done. Tests: " << _test_count << " Failed: " << _failed_test_count << endl;
    return 0;
}

int c2bTests::writeInformation()
{
    write_information();
    return 0;
}

void c2bTests::compression_check()
{
    QString test;
    test += QChar(100);
    test += QChar(200);
    test += QChar(8700);
    test += QChar(56200);
    test += QChar(57000);
    test += QChar(10);
    test += QChar(100);
    test += QChar(200);
    test += QChar(8700);
    test += QChar(56200);
    test += QChar(57000);
    test += QChar(10);
    QByteArray ba = test.toUtf8();
    bool passed(c2bUtils::fromUtf8(ba) == QString::fromUtf8(ba));
    cout << endl;
    if (passed)
    {
        cout << "-----------------------------------------------------------------" << endl;
        cout << "Check for c2b utf8: passed" << endl;
        cout << "-----------------------------------------------------------------" << endl;
    }
    else
    {
        cout << "-----------------------------------------------------------------" << endl;
        cout << "WARNING: Check for c2b utf8 FAILED! Please report it as a bug" << endl;
        cout << "-----------------------------------------------------------------" << endl;
        ++_failed_test_count;
    }
    ++_test_count;

    test += "-----------------------------------------------------------------";
    test += "=================================================================";
    QByteArray cba(c2bUtils::compressString(test));
    QString dcs(c2bUtils::decompressString(cba));
    passed = (dcs == test) && (test.toUtf8().length() > cba.length()) && (dcs.utf16()[dcs.size()] == 0);
    if (passed)
    {
        cout << "-----------------------------------------------------------------" << endl;
        cout << "Check for compression: passed" << endl;
        cout << "-----------------------------------------------------------------" << endl;
    }
    else
    {
        cout << "-----------------------------------------------------------------" << endl;
        cout << "WARNING: Check for compression FAILED! Please report it as a bug" << endl;
        cout << "-----------------------------------------------------------------" << endl;
        ++_failed_test_count;
    }
    ++_test_count;
}

void c2bTests::write_information()
{
    cout << endl;
    cout << "-------------------------" << endl;
    cout << "Miscellaneous information" << endl;
    cout << "-------------------------" << endl;
    cout << endl;
    cout << "Version: cb2bib " << C2B_VERSION << endl;
#if defined(C2B_USE_LZSSE)
    cout << "Compression: lzsse" << endl;
#elif defined(C2B_USE_LZ4)
    cout << "Compression: lz4" << endl;
#elif defined(C2B_USE_LZO)
    cout << "Compression: lzo2" << endl;
#else
    cout << "Compression: zlib" << endl;
#endif
#if QT_VERSION >= QT_VERSION_CHECK(5, 4, 0)
    cout << "Optimized PCRE: yes" << endl;
#else
    cout << "Optimized PCRE: no" << endl;
#endif
#ifdef C2B_USE_TXTMATCHER_AVX2
    cout << "Optimized txtmatcher: AVX2" << endl;
#endif
#ifdef C2B_USE_TXTMATCHER_SSE2
    cout << "Optimized txtmatcher: SSE2" << endl;
#endif
#ifdef C2B_USE_TXTMATCHER_SCALAR
    cout << "Optimized txtmatcher: no" << endl;
#endif
#ifdef C2B_USE_QWEBKIT
    cout << "Compiled against QtWebKit: yes" << endl;
#else
    cout << "Compiled against QtWebKit: no" << endl;
#endif
#ifdef C2B_USE_QWEBENGINE
    cout << "Compiled against QtWebEngine: yes" << endl;
#else
    cout << "Compiled against QtWebEngine: no" << endl;
#endif
#ifdef C2B_USE_CBPOLL
    cout << "Clipboard polling: yes" << endl;
#else
    cout << "Clipboard polling: no" << endl;
#endif
    cout << "Application binary path: " << QCoreApplication::instance()->applicationDirPath() << endl;
    cout << "Application hardcoded data path: " << C2B_DATA_DIR << endl;
#ifdef Q_OS_MACOS
    QString C2B_DATA_DIR_MAC(C2B_DATA_DIR);
    if (QDir(C2B_DATA_DIR + "/data/").exists())
        C2B_DATA_DIR_MAC = QDir::cleanPath(C2B_DATA_DIR + '/');
    else if (QDir(QCoreApplication::instance()->applicationDirPath() + "/../Resources/data/").exists())
        C2B_DATA_DIR_MAC = QDir::cleanPath(QCoreApplication::instance()->applicationDirPath() + "/../Resources/");
    cout << "Application macosx data path: " << C2B_DATA_DIR_MAC << endl;
#endif
    cout << "\n-------------------------" << endl;
    cout << "OS:" << endl;
    cout << "Build CPU:       " << QSysInfo::buildCpuArchitecture() << endl;
    cout << "CPU:             " << QSysInfo::currentCpuArchitecture() << endl;
    cout << "Kernel Type:     " << QSysInfo::kernelType() << endl;
    cout << "Kernel Version:  " << QSysInfo::kernelVersion() << endl;
    cout << "Product Type:    " << QSysInfo::productType() << endl;
    cout << "Product Version: " << QSysInfo::productVersion() << '|' << int(QSysInfo::productVersion().toDouble()) << endl;
    cout << "Name:            " << QSysInfo::prettyProductName() << endl;
    cout << "-------------------------" << endl;
    cout << endl;
}

void c2bTests::heuristic_author()
{
    cout << endl;
    cout << "---------------------------------" << endl;
    cout << "Test heuristic author recognition" << endl;
    cout << "---------------------------------" << endl;

    QFileInfoList flist = QDir(_bibliographic_dir).entryInfoList(QStringList() << "*.bib");
    bibParser bp;
    bibReference reference;
    QStringList fields;
    fields.append("author");
    fields.append("editor");
    bp.initReferenceParsing(_bibliographic_dir, fields, &reference);

#if C2B_CHECK_CAPITALIZATION
    for (int f = 0; f < flist.count(); ++f)
    {
        const QString bib_file(flist.at(f).absoluteFilePath());
        bp.initReferenceParsing(_bibliographic_dir, fields, &reference);
        cout << "File: " << bib_file << endl;
        while (bp.referencesIn(c2bUtils::fileToString(bib_file), &reference))
        {
            const QString author(reference.value("author"));
            if (author.isEmpty())
                continue;
            bp.clearCurrentReference();
            bp.guessFields(author);
            const QString guess(bp.currentReference().value("author"));
            const bool passed(guess == author);
            ++_test_count;
            if (!passed)
                ++_failed_test_count;
            cout << QString("[%1]\t'%2'\n").arg(boolToStr(passed)).arg(author);
            if (!passed)
                cout << QString("\t'%1'\n").arg(guess);
        }
    }
    return;
#endif
#if C2B_CHECK_CODE_DECOMPOSITION
    for (int u = 1; u < 78790; ++u)
    {
        const QChar c(u);
        if (!c.isLetter())
            continue;
        if (c.decompositionTag() == QChar::NoDecomposition)
            continue;
        const QString dc(c.decomposition());
        if (dc.length() != 2)
            continue;
        if (dc.at(0).isLetter() && dc.at(1).isLetter())
            cout << '[' << c << ']' << " u: " << u << " decompose: " << decomposition(c)
                 << " category: " << c.category() << endl;
    }
    return;
#endif
#if C2B_CHECK_PDF_CODES
    QMap<QChar, long long> charfreq;
    long long char_count = 0;
    for (int f = 0; f < flist.count(); ++f)
    {
        const QString bib_file(flist.at(f).absoluteFilePath());
        fields.append("file");
        bp.initReferenceParsing(_bibliographic_dir, fields, &reference);
        cout << "File: " << bib_file << endl;
        while (bp.referencesIn(c2bUtils::fileToString(bib_file), &reference))
        {
            const QString file(reference.value("file"));
            document d(file, document::Raw);
            const QString doc(d.toString());
            for (int i = 0; i < doc.length(); ++i)
            {
                if (doc.at(i).unicode() > 800 && doc.at(i).unicode() < 900)
                {
                    cout << "At file: " << file << endl;
                    cout << '[' << doc.at(i) << "] " << doc.mid(i - 10, 20) << endl;
                }
                charfreq.insert(doc.at(i), 1 + charfreq.value(doc.at(i), 0));
            }
            char_count += doc.length();
        }
    }
    QList<QChar> cl = charfreq.keys();
    for (int i = 0; i < cl.count(); ++i)
        cout << '[' << cl.at(i) << ']' << " u: " << cl.at(i).unicode() << " letter: " << cl.at(i).isLetter()
             << " decompose: " << decomposition(cl.at(i)) << " category: " << cl.at(i).category()
             << " f: " << charfreq.value(cl.at(i)) << endl;
    cout << "\nTotal characters: " << char_count << endl;
    return;
#endif
#if C2B_CHECK_PDF_AUTHORS
    cout << endl;
    cout << "----------------------------------------" << endl;
    cout << "Test heuristic author recognition on PDF" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;
    cout << "Checking files at: " << _bibliographic_dir << endl;

    const QStringList excluded(c2bUtils::fileToString(_bibliographic_dir + "/c2b_test_exclude.txt")
                               .split(QRegExp("[\\n\\r]"), QString::SkipEmptyParts));
    QHash<QString, QString> doc_cache;
    const QString doc_cache_fn(_bibliographic_dir + "/c2b_test.cache");
    if (QFileInfo::exists(doc_cache_fn))
    {
        cout << "Reading from cache" << endl;
        QFile file(doc_cache_fn);
        file.open(QIODevice::ReadOnly);
        QDataStream ds(&file);
        ds >> doc_cache;
    }
    else
    {
        for (int f = 0; f < flist.count(); ++f)
        {
            const QString bib_file(flist.at(f).absoluteFilePath());
            fields.append("file");
            bp.initReferenceParsing(_bibliographic_dir, fields, &reference);
            cout << "File: " << bib_file << endl;
            while (bp.referencesIn(c2bUtils::fileToString(bib_file), &reference))
            {
                const QString file(reference.value("file"));
                if (excluded.contains(file) || file.contains("/stacks/"))
                    continue;
                document d(file, document::FirstPage);
                const QString doc(d.toString());
                doc_cache.insert(reference.value("file"), doc);
            }
        }
        if (doc_cache.size() > 0)
        {
            QFile file(doc_cache_fn);
            file.open(QIODevice::WriteOnly);
            QDataStream ds(&file);
            ds << doc_cache;
            cout << "Writing cache " << doc_cache_fn << endl;
            cout << "Delete cache when done" << endl;
        }
    }
    cout << "Check authors" << endl;
    int n_pdf(0);
    int n_failed_pdf(0);
    for (int f = 0; f < flist.count(); ++f)
    {
        const QString bib_file(flist.at(f).absoluteFilePath());
        fields.append("file");
        bp.initReferenceParsing(_bibliographic_dir, fields, &reference);
        cout << "File: " << bib_file << endl;
        while (bp.referencesIn(c2bUtils::fileToString(bib_file), &reference))
        {
            const QString file(reference.value("file"));
            if (file.isEmpty())
                continue;
            if (excluded.contains(file) || file.contains("/stacks/"))
                continue;
            const QString doc(doc_cache.value(reference.value("file")));
            QString check_doc(doc);
            check_doc.remove(c2bUtils::nonAsciiLetter);
            if (check_doc.isEmpty())
                continue;

            const QString author(reference.value("author"));
            bp.clearCurrentReference();
            bp.guessFields(doc);
            const QString guess(bp.currentReference().value("author"));
            bool passed(guess == author);
            if (!passed)
            {
                QString author_ascii(c2bUtils::toAscii(author, c2bUtils::Cleanup));
                QString guess_ascii(c2bUtils::toAscii(guess, c2bUtils::Cleanup));
                passed = guess_ascii == author_ascii;
                if (passed)
                    cout << QString("[%1*] '%2'\n").arg(boolToStr(passed), author);
                else
                    cout << QString("[%1]  '%2'\n").arg(boolToStr(passed), author);
                if (!passed)
                {
                    qDebug() << author;
                    qDebug() << guess;
                    qDebug() << reference.value("file");
                    qDebug() << "DOCUMENT: \n" << doc << endl << endl;
                    //                    for (int i = 0; i < doc.count(); ++i)
                    //                        cout << '[' << doc.at(i) << ']' << " u: " << doc.at(i).unicode() << "
                    //                        letter: " <<
                    //                             doc.at(i).isLetter() << endl;
                }
                cout << QString("          '%1'\n").arg(guess);
            }
            else
                cout << QString("[%1]  '%2'\n").arg(boolToStr(passed), author);
            ++n_pdf;
            if (!passed)
                ++n_failed_pdf;
        }
    }
    cout << "PDF Tests: " << n_pdf << endl;
    cout << "Succeded: " << n_pdf - n_failed_pdf << endl;
    _test_count += n_pdf;
    _failed_test_count += n_failed_pdf;
#endif
}

void c2bTests::check_abbreviations_txt()
{
#if C2B_CHECK_JOURNALS
    cout << endl;
    cout << "--------------------------------" << endl;
    cout << "Check journal abbreviations file" << endl;
    cout << "--------------------------------" << endl;
    cout << endl;

    const QString dbfile(settings::instance()->fileName("cb2Bib/JournalFile"));
    cout << dbfile << endl;
    journalDB jdb(dbfile);

    QStringList abbr1, abbr2, full1, full2, code;
    {
        QFile file(dbfile);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
        QTextStream stream(&file);
        stream.setCodec("UTF-8");
        stream.setAutoDetectUnicode(true);
        QString line;
        int line_number(0);
        while (!stream.atEnd())
        {
            line = stream.readLine();
            ++line_number;
            if (line.isEmpty() || line.startsWith('#'))
                continue;
            const QStringList spLine(line.split('|', QString::SkipEmptyParts));
            if (spLine.count() != 3)
            {
                cout << "Syntax error in journal file at line " << line_number << endl;
                continue;
            }
            const QStringList spAbbreviated(spLine.at(1).split('=', QString::SkipEmptyParts));
            const int na(spAbbreviated.count());
            if (na < 1 || na > 2)
            {
                cout << "Syntax error in journal file at line " << line_number << endl;
                continue;
            }
            const QStringList spExtended(spLine.at(2).split('=', QString::SkipEmptyParts));
            const int ne(spExtended.count());
            if (ne < 1 || ne > 2)
            {
                cout << "Syntax error in journal file at line " << line_number << endl;
                continue;
            }
            code += spLine.at(0);
            abbr1 += spAbbreviated.at(0);
            full1 += spExtended.at(0);
            abbr2 += (na == 2) ? spAbbreviated.at(1) : spAbbreviated.at(0);
            full2 += (ne == 2) ? spExtended.at(1) : spExtended.at(0);
        }
        file.close();
        const int njournals(code.count());
        QStringList counter;
        for (int i = 0; i < njournals; ++i)
            counter += code.at(i).toLower().remove(c2bUtils::nonLetter);
        counter.removeDuplicates();
        cout << "code total:  " << njournals << " unique: " << counter.count() << endl;
        counter.clear();
        for (int i = 0; i < njournals; ++i)
            counter += abbr1.at(i).toLower().remove(c2bUtils::nonLetter);
        counter.removeDuplicates();
        cout << "abbr1 total: " << njournals << " unique: " << counter.count() << endl;
        counter.clear();
        for (int i = 0; i < njournals; ++i)
            counter += full1.at(i).toLower().remove(c2bUtils::nonLetter);
        counter.removeDuplicates();
        cout << "full1 total: " << njournals << " unique: " << counter.count() << endl;
        counter.clear();
        for (int i = 0; i < njournals; ++i)
            counter += abbr2.at(i).toLower().remove(c2bUtils::nonLetter);
        counter.removeDuplicates();
        cout << "abbr2 total: " << njournals << " unique: " << counter.count() << endl;
        counter.clear();
        for (int i = 0; i < njournals; ++i)
            counter += full2.at(i).toLower().remove(c2bUtils::nonLetter);
        counter.removeDuplicates();
        cout << "full2 total: " << njournals << " unique: " << counter.count() << endl;
    }
    const int njournals(code.count());

    cout << endl;
    for (int i = 0; i < njournals; ++i)
        if (jdb.retrieve(code.at(i)) != abbr1.at(i))
            cout << "failed code to abbr1   " << code.at(i) << " | " << abbr1.at(i) << " | " << jdb.retrieve(code.at(i))
                 << endl;
    for (int i = 0; i < njournals; ++i)
        if (jdb.retrieveAlternate(code.at(i)) != abbr2.at(i))
            cout << "failed code to abbr2   " << code.at(i) << " | " << abbr2.at(i) << " | "
                 << jdb.retrieveAlternate(code.at(i)) << endl;
    for (int i = 0; i < njournals; ++i)
        if (jdb.retrieveFull(code.at(i)) != full1.at(i))
            cout << "failed code to full1   " << code.at(i) << " | " << full1.at(i) << " | "
                 << jdb.retrieveFull(code.at(i)) << endl;
    for (int i = 0; i < njournals; ++i)
        if (jdb.retrieveAlternateFull(code.at(i)) != full2.at(i))
            cout << "failed code to full2   " << code.at(i) << " | " << full2.at(i) << " | "
                 << jdb.retrieveAlternateFull(code.at(i)) << endl;

    cout << endl;
    for (int i = 0; i < njournals; ++i)
        if (jdb.retrieve(abbr1.at(i)) != abbr1.at(i))
            cout << "failed abbr1 to abbr1  " << abbr1.at(i) << " | " << abbr1.at(i) << " | "
                 << jdb.retrieve(abbr1.at(i)) << endl;
    for (int i = 0; i < njournals; ++i)
        if (jdb.retrieveAlternate(abbr1.at(i)) != abbr2.at(i))
            cout << "failed abbr1 to abbr2  " << abbr1.at(i) << " | " << abbr2.at(i) << " | "
                 << jdb.retrieveAlternate(abbr1.at(i)) << endl;
    for (int i = 0; i < njournals; ++i)
        if (jdb.retrieveFull(abbr1.at(i)) != full1.at(i))
            cout << "failed abbr1 to full1  " << abbr1.at(i) << " | " << full1.at(i) << " | "
                 << jdb.retrieveFull(abbr1.at(i)) << endl;
    for (int i = 0; i < njournals; ++i)
        if (jdb.retrieveAlternateFull(abbr1.at(i)) != full2.at(i))
            cout << "failed abbr1 to full2  " << abbr1.at(i) << " | " << full2.at(i) << " | "
                 << jdb.retrieveAlternateFull(abbr1.at(i)) << endl;

    cout << endl;
    for (int i = 0; i < njournals; ++i)
        if (jdb.retrieve(abbr2.at(i)) != abbr1.at(i))
            cout << "failed abbr2 to abbr1  " << abbr2.at(i) << " | " << abbr1.at(i) << " | "
                 << jdb.retrieve(abbr2.at(i)) << endl;
    for (int i = 0; i < njournals; ++i)
        if (jdb.retrieveAlternate(abbr2.at(i)) != abbr2.at(i))
            cout << "failed abbr2 to abbr2  " << abbr2.at(i) << " | " << abbr2.at(i) << " | "
                 << jdb.retrieveAlternate(abbr2.at(i)) << endl;
    for (int i = 0; i < njournals; ++i)
        if (jdb.retrieveFull(abbr2.at(i)) != full1.at(i))
            cout << "failed abbr2 to full1  " << abbr2.at(i) << " | " << full1.at(i) << " | "
                 << jdb.retrieveFull(abbr2.at(i)) << endl;
    for (int i = 0; i < njournals; ++i)
        if (jdb.retrieveAlternateFull(abbr2.at(i)) != full2.at(i))
            cout << "failed abbr2 to full2  " << abbr2.at(i) << " | " << full2.at(i) << " | "
                 << jdb.retrieveAlternateFull(abbr2.at(i)) << endl;

    cout << endl;
    for (int i = 0; i < njournals; ++i)
        if (jdb.retrieve(full1.at(i)) != abbr1.at(i))
            cout << "failed full1 to abbr1  " << full1.at(i) << " | " << abbr1.at(i) << " | "
                 << jdb.retrieve(full1.at(i)) << endl;
    for (int i = 0; i < njournals; ++i)
        if (jdb.retrieveAlternate(full1.at(i)) != abbr2.at(i))
            cout << "failed full1 to abbr2  " << full1.at(i) << " | " << abbr2.at(i) << " | "
                 << jdb.retrieveAlternate(full1.at(i)) << endl;
    for (int i = 0; i < njournals; ++i)
        if (jdb.retrieveFull(full1.at(i)) != full1.at(i))
            cout << "failed full1 to full1  " << full1.at(i) << " | " << full1.at(i) << " | "
                 << jdb.retrieveFull(full1.at(i)) << endl;
    for (int i = 0; i < njournals; ++i)
        if (jdb.retrieveAlternateFull(full1.at(i)) != full2.at(i))
            cout << "failed full1 to full2  " << full1.at(i) << " | " << full2.at(i) << " | "
                 << jdb.retrieveAlternateFull(full1.at(i)) << endl;

    cout << endl;
    for (int i = 0; i < njournals; ++i)
        if (jdb.retrieve(full2.at(i)) != abbr1.at(i))
            cout << "failed full2 to abbr1  " << full2.at(i) << " | " << abbr1.at(i) << " | "
                 << jdb.retrieve(full2.at(i)) << endl;
    for (int i = 0; i < njournals; ++i)
        if (jdb.retrieveAlternate(full2.at(i)) != abbr2.at(i))
            cout << "failed full2 to abbr2  " << full2.at(i) << " | " << abbr2.at(i) << " | "
                 << jdb.retrieveAlternate(full2.at(i)) << endl;
    for (int i = 0; i < njournals; ++i)
        if (jdb.retrieveFull(full2.at(i)) != full1.at(i))
            cout << "failed full2 to full1  " << full2.at(i) << " | " << full1.at(i) << " | "
                 << jdb.retrieveFull(full2.at(i)) << endl;
    for (int i = 0; i < njournals; ++i)
        if (jdb.retrieveAlternateFull(full2.at(i)) != full2.at(i))
            cout << "failed full2 to full2  " << full2.at(i) << " | " << full2.at(i) << " | "
                 << jdb.retrieveAlternateFull(full2.at(i)) << endl;
#endif
}

void c2bTests::heuristic_journal()
{
#if C2B_CHECK_JOURNALS
    cout << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Test heuristic journal recognition on PDF" << endl;
    cout << "-----------------------------------------" << endl;
    cout << endl;
    cout << "Checking files at: " << _bibliographic_dir << endl;

    QFileInfoList flist = QDir(_bibliographic_dir).entryInfoList(QStringList() << "*.bib");
    bibParser bp;
    bibReference reference;
    QStringList fields;
    fields.append("journal");
    fields.append("file");

    const QStringList excluded(c2bUtils::fileToString(_bibliographic_dir + "/c2b_test_exclude.txt")
                               .split(QRegExp("[\\n\\r]"), QString::SkipEmptyParts));
    QHash<QString, QString> doc_cache;
    const QString doc_cache_fn(_bibliographic_dir + "/c2b_test.cache");
    if (QFileInfo(doc_cache_fn).exists())
    {
        cout << "Reading from cache" << endl;
        QFile file(doc_cache_fn);
        file.open(QIODevice::ReadOnly);
        QDataStream ds(&file);
        ds >> doc_cache;
    }
    else
    {
        cout << "No cache. Return" << doc_cache_fn << endl;
        return;
    }
    cout << "Check journals" << endl;
    int n_pdf(0);
    int n_failed_pdf(0);
    QList<int> doclengths;
    for (int f = 0; f < flist.count(); ++f)
    {
        const QString bib_file(flist.at(f).absoluteFilePath());
        bp.initReferenceParsing(_bibliographic_dir, fields, &reference);
        cout << "File: " << bib_file << endl;
        while (bp.referencesIn(c2bUtils::fileToString(bib_file), &reference))
        {
            const QString file(reference.value("file"));
            if (file.isEmpty())
                continue;
            if (excluded.contains(file) || file.contains("/stacks/"))
                continue;
            const QString doc(doc_cache.value(file));
            QString check_doc(doc);
            check_doc.remove(c2bUtils::nonAsciiLetter);
            if (check_doc.isEmpty())
                continue;
            doclengths.append(check_doc.length());
            const QString ajournal(bp.abbreviatedJournal(reference.value("journal")));
            const QString fjournal(bp.fullJournal(reference.value("journal")));
            if (fjournal.isEmpty())
                continue;
            if (ajournal == fjournal && (ajournal.count('.') > 0 || ajournal.count(' ') > 0))
            {
                qDebug() << "not in db:" << fjournal;
                continue;
            }
            bp.clearCurrentReference();
            bp.guessFields(doc);
            // const QString guess(bp.abbreviatedJournal(bp.currentReference().value("journal")));
            const QString guess(bp.fullJournal(bp.currentReference().value("journal")));
            if (guess.isEmpty())
                continue;

            bool passed(guess == fjournal);
            if (!passed)
            {
                cout << QString("[%1]  '%2'\n").arg(boolToStr(passed)).arg(fjournal);
                cout << QString("          '%1'\n").arg(guess);

                qDebug() << "jn:" << fjournal;
                qDebug() << "gn:" << guess;
                qDebug() << reference.value("file");
                qDebug() << "DOCUMENT: \n" << doc << endl << endl;
            }
            else
                cout << QString("[%1]  '%2'\n").arg(boolToStr(passed)).arg(fjournal);
            ++n_pdf;
            if (!passed)
                ++n_failed_pdf;
        }
    }
    cout << "PDF Tests: " << n_pdf << endl;
    cout << "Succeded:  " << n_pdf - n_failed_pdf << endl;
    cout << "Ratio:     " << double(n_pdf) / double(n_failed_pdf) << endl;
    _test_count += n_pdf;
    _failed_test_count += n_failed_pdf;

    std::sort(doclengths.begin(), doclengths.end());
    cout << "doclengths min max median: " << doclengths.first() << ' ' << doclengths.last() << ' '
         << doclengths.at(doclengths.count() / 2) << endl;
#endif
}

void c2bTests::author_parser()
{
    cout << endl;
    cout << "------------------" << endl;
    cout << "Test author parser" << endl;
    cout << "------------------" << endl;

    bibParser bp;
    QString author;
    QString input;

    author = "J.-L. Smith and R. Jones and K. McGibbons";
    input = "SMITH, J.-L., R. JONES, AND K. MCGIBBONS";
    check_test(author == bp.parse("author", input), input, author);
    input = "Smith, J.-L., Jones, R., and McGibbons, K.";
    check_test(author == bp.parse("author", input), input, author);
    input = "Smith, J.-L., Jones, R., McGibbons, K.";
    check_test(author == bp.parse("author", input), input, author);

    author = "J. L. Brooks Jr";
    input = "Brooks Jr, John L";
    check_test(author == bp.parse("author", input), input, author);

    author = "E. B. Melissa and W. F. Tohnson Jr and C. Z. Ortiz and S. J. van der Burgh";
    input = "Melissa, Elizabeth Baines; Tohnson, Walter F., Jr.; Zapa Ortiz, Carlos; van der Burgh, S. J.";
    check_test(author == bp.parse("author", input), input, author);
    input = "Melissa, E.B., Tohnson Jr, Walter F., Zapa Ortiz, C., van der Burgh, S. J.";
    check_test(author == bp.parse("author", input), input, author);
    input = "Melissa, E.B., Tohnson Jr, Walter F., Zapa Ortiz, C., and van der Burgh, S. J.";
    check_test(author == bp.parse("author", input), input, author);

    author = "B. B. Aaaaaaa";
    input = "Aaaaaaa, BB";
    check_test(author == bp.parse("author", input), input, author);
    // author = "J. R. Aaaaaaa";
    // input = "Aaaaaaa, JR"; // Gives wrong processing of the initials JR (set to Jr)
    // check_test(author == bp.parse("author", input), input, author);

    author = "J. Pi";
    input = "Joan Pi";
    check_test(author == bp.parse("author", input), input, author);
    input = "JOAN PI";
    check_test(author == bp.parse("author", input), input, author);
    author = "P. I. Joan";
    input = "Joan PI";
    check_test(author == bp.parse("author", input), input, author);

    author = "C. V. Pi";
    input = "Carles Vidal Pi";
    check_test(author == bp.parse("author", input), input, author);
    input = "Carles VIDAL PI";
    check_test(author == bp.parse("author", input), input, author);
    input = "Vidal Pi, Carles";
    check_test(author == bp.parse("author", input), input, author);
    input = "Pi, Carles Vidal";
    check_test(author == bp.parse("author", input), input, author);
    input = "PI, CARLES VIDAL";
    check_test(author == bp.parse("author", input), input, author);

    author = "C. V. Pi and M. R. Catala";
    input = "Carles Vidal Pi, Maria Rosa Catala";
    check_test(author == bp.parse("author", input), input, author);
    input = "Vidal Pi, Carles and Catala, Maria Rosa";
    check_test(author == bp.parse("author", input), input, author);
    input = "Vidal Pi, Carles and Catala, MR";
    check_test(author == bp.parse("author", input), input, author);
    input = "VIDAL PI, Carles and CATALA, MR";
    check_test(author == bp.parse("author", input), input, author);
    input = "Vidal Pi, Carles and Catala, M.R.";
    check_test(author == bp.parse("author", input), input, author);

    author = "C. V. Pi and M. R. Catala";
    input = "Carles Vidal Pi, Maria Ros Catala";
    check_test(author == bp.parse("author", input), input, author);
    input = "Carles VIDAL PI, Maria ROS CATALA";
    check_test(author == bp.parse("author", input), input, author);
    input = "Vidal Pi, Carles and Ros Catala, Maria";
    check_test(author == bp.parse("author", input), input, author);

    author = "M. R. R. Catala";
    input = "Maria Rosa Ros Catala";
    check_test(author == bp.parse("author", input), input, author);
    input = "Ros Catala, MR";
    check_test(author == bp.parse("author", input), input, author);
    input = "Ros Catala, M R";
    check_test(author == bp.parse("author", input), input, author);
    input = "Ros Catala, M. R.";
    check_test(author == bp.parse("author", input), input, author);

    author = "M. d'Errico";
    input = "Monica d'Errico";
    check_test(author == bp.parse("author", input), input, author);

    author = "J. V. Mael Jr";
    input = "JAMES V. MAEL, Jr.";
    check_test(author == bp.parse("author", input), input, author);
    author = "J. V. Mael III";
    input = "JAMES V. MAEL, III";
    check_test(author == bp.parse("author", input), input, author);

    author = "V. Yu. Dmitri and A. Karpoff";
    input = "VICTOR Yu. DMITRI,3 ANDRIY KARPOFF";
    check_test(author == bp.parse("author", input), input, author);

    author = "Yu. Dmitri and A. Karpoff";
    input = "Yu. Dmitri,3 Andriy Karpoff";
    check_test(author == bp.parse("author", input), input, author);
    input = "Yu. DMITRI,3 ANDRIY KARPOFF";
    check_test(author == bp.parse("author", input), input, author);
    input = "YU. DMITRI,3 ANDRIY KARPOFF";
    check_test(author == bp.parse("author", input), input, author);

    cout << "From medline:" << endl;
    author = "C. L. Maggi III";
    input = "Maggi, Carla L., III";
    check_test(author == bp.parse("author", input), input, author);
    input = "Maggi III CL";
    check_test(author == bp.parse("author", input), input, author);
    check_test(author == bp.parse("author", bp.authorFromMedline(input)), input, author);
    input = "Maggi, Carla L 3rd";
    check_test(author == bp.parse("author", bp.authorFromMedline(input)), input, author);
    input = "Maggi CL 3rd";
    check_test(author == bp.parse("author", bp.authorFromMedline(input)), input, author);
    author = "A. M. C. Lourtau";
    input = "Carr Lourtau, A M";
    check_test(author == bp.parse("author", input), input, author);
    check_test(author == bp.parse("author", bp.authorFromMedline(input)), input, author);
    input = "Carr Lourtau, AM";
    check_test(author == bp.parse("author", input), input, author);
    // input = "Carr Lourtau AM"; // Gives 'L. A. Carr' (rare AU formatting)
    // check_test(author == bp.parse("author", author::fromMedline(input)), input, author);

    author = "B. de Rivas";
    input = "de Rivas, Beatriz";
    check_test(author == bp.parse("author", bp.authorFromMedline(input)), input, author);
    input = "de Rivas B";
    check_test(author == bp.parse("author", bp.authorFromMedline(input)), input, author);
    author = "B. De Baets";
    input = "  De Baets, B  ";
    check_test(author == bp.parse("author", bp.authorFromMedline(input)), input, author);
}

void c2bTests::heuristic_pvny()
{
    cout << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "Test heuristic pages - volume - number - year recognition" << endl;
    cout << "---------------------------------------------------------" << endl;

    bibParser bp;
    bibReference reference;

    /****************************************************************
    journal-pages-volume
    ****************************************************************/
    reference.clearReference();
    reference.insert("journal", bp.parse("journal", "Science"));
    reference.insert("pages", bp.parse("pages", "927"));
    reference.insert("volume", bp.parse("volume", "120"));
    write(bp, reference);
    heuristic(bp, reference, "Science. 120: 927");
    heuristic(bp, reference, "Science. 120, 927");
    heuristic(bp, reference, "Science 120, 927");
    heuristic(bp, reference, "Science 120, pp. 927");

    reference.clearReference();
    reference.insert("journal", bp.parse("journal", "Science"));
    reference.insert("pages", bp.parse("pages", "927 - 993"));
    reference.insert("volume", bp.parse("volume", "120"));
    write(bp, reference);
    heuristic(bp, reference, "Science. 120: 927 - 993");
    heuristic(bp, reference, "Science. 120, 927 - 93");
    heuristic(bp, reference, "Science 120, 927 - 993");
    heuristic(bp, reference, "Science 120, pp. 927 - 993");

    /****************************************************************
    journal-pages-volume-number
    ****************************************************************/
    reference.clearReference();
    reference.insert("journal", bp.parse("journal", "Science"));
    reference.insert("pages", bp.parse("pages", "927"));
    reference.insert("volume", bp.parse("volume", "120"));
    reference.insert("number", bp.parse("number", "1 - 3"));
    write(bp, reference);
    heuristic(bp, reference, "Science 120(1 - 3), 927");
    heuristic(bp, reference, "Science 120(1 - 3), pp. 927");

    reference.clearReference();
    reference.insert("journal", bp.parse("journal", "Science"));
    reference.insert("pages", bp.parse("pages", "927 - 993"));
    reference.insert("volume", bp.parse("volume", "120"));
    reference.insert("number", bp.parse("number", "1 - 3"));
    write(bp, reference);
    heuristic(bp, reference, "Science 120(1 - 3), 927 - 993");
    heuristic(bp, reference, "Science 120(1 - 3), pp. 927 - 993");

    reference.clearReference();
    reference.insert("journal", bp.parse("journal", "Science"));
    reference.insert("pages", bp.parse("pages", "927 - 993"));
    reference.insert("volume", bp.parse("volume", "120"));
    reference.insert("number", bp.parse("number", "1"));
    write(bp, reference);
    heuristic(bp, reference, "Science, Volume 120, Number 1, 927 - 993");

    /****************************************************************
    journal-pages-volume-year
    ****************************************************************/
    reference.clearReference();
    reference.insert("journal", bp.parse("journal", "Science"));
    reference.insert("pages", bp.parse("pages", "1922"));
    reference.insert("volume", bp.parse("volume", "120"));
    reference.insert("year", bp.parse("year", "2007"));
    write(bp, reference);
    heuristic(bp, reference, "Science 2007, 120, 1922");
    heuristic(bp, reference, "Science 2007 120: 1922");
    heuristic(bp, reference, "Science. 120: 1922, 2007");
    heuristic(bp, reference, "(2007) Science 120: 1922");
    heuristic(bp, reference, "Science 120, 1922 2007");
    heuristic(bp, reference, "Science 120, 1922(2007)");
    heuristic(bp, reference, "Science 120(2007) 1922");
    heuristic(bp, reference, "Science 2007;120:1922.");
    heuristic(bp, reference, "Science 2007 May 2;120:1922");

    reference.clearReference();
    reference.insert("journal", bp.parse("journal", "Science"));
    reference.insert("pages", bp.parse("pages", "22"));
    reference.insert("volume", bp.parse("volume", "120"));
    reference.insert("year", bp.parse("year", "2007"));
    write(bp, reference);
    heuristic(bp, reference, "Science 2007, 120, 22");
    heuristic(bp, reference, "Science 2007 120: 22");
    heuristic(bp, reference, "Science 2007 May 2, 120: 22");
    heuristic(bp, reference, "Science. 120: 22, 2007");
    heuristic(bp, reference, "(2007) Science 120: 22");
    heuristic(bp, reference, "Science 120, 22 2007");
    heuristic(bp, reference, "Science 120, 22(2007)");
    heuristic(bp, reference, "Science 120(2007) 22");

    // Usual pages
    reference.clearReference();
    reference.insert("journal", bp.parse("journal", "Science"));
    reference.insert("pages", bp.parse("pages", "3 - 7"));
    reference.insert("volume", bp.parse("volume", "120"));
    reference.insert("year", bp.parse("year", "2007"));
    write(bp, reference);
    heuristic(bp, reference, "Science. 120, 3 - 7(2007)");
    heuristic(bp, reference, "Science. 120: 3 - 7, 2007");
    heuristic(bp, reference, "Science, 120(2007), pp. 3 - 7");
    heuristic(bp, reference, "Science 120(2007) 3 - 7");
    heuristic(bp, reference, "2007 Science 120 3 - 7");
    heuristic(bp, reference, "Science. 2007, 120, 3 - 7");
    heuristic(bp, reference, "Science. 2007 120: 3 - 7");
    heuristic(bp, reference, "Science. 2007 May 2, 120: 3 - 7");
    heuristic(bp, reference, "Science. 2007, 120, 3 - 5pp");
    heuristic(bp, reference, "Science 2007;120: 3 - 7");

    // Pages susceptible to be confused by years
    reference.clearReference();
    reference.insert("journal", bp.parse("journal", "Science"));
    reference.insert("pages", bp.parse("pages", "1997 - 2001"));
    reference.insert("volume", bp.parse("volume", "120"));
    reference.insert("year", bp.parse("year", "2007"));
    write(bp, reference);
    heuristic(bp, reference, "Science. 120, 1997 - 2001(2007)");
    heuristic(bp, reference, "Science. 120, 1997 - 2001, 2007");
    heuristic(bp, reference, "Science. 120: 1997 - 2001, 2007");
    heuristic(bp, reference, "Science, 120(2007), pp. 1997 - 2001");
    heuristic(bp, reference, "Science 120(2007) 1997 - 2001");
    heuristic(bp, reference, "2007 Science 120 1997 - 2001");
    heuristic(bp, reference, "Science. 2007, 120, 1997 - 2001");
    heuristic(bp, reference, "Science. 2007 May 2, 120, 1997 - 2001");
    heuristic(bp, reference, "Science. 2007 120: 1997 - 2001");
    heuristic(bp, reference, "Science. 2007, 120, 1997 - 5pp");
    heuristic(bp, reference, "Science 2007;120: 1997 - 2001");

    // Pages starting by zero
    reference.clearReference();
    reference.insert("journal", bp.parse("journal", "Science"));
    reference.insert("pages", bp.parse("pages", "044103 - 044110"));
    reference.insert("volume", bp.parse("volume", "120"));
    reference.insert("year", bp.parse("year", "2007"));
    write(bp, reference);
    heuristic(bp, reference, "Science. 120, 044103 - 044110(2007)");
    heuristic(bp, reference, "Science. 120: 044103 - 044110, 2007");
    heuristic(bp, reference, "Science, 120(2007), pp. 044103 - 044110");
    heuristic(bp, reference, "Science 120(2007) 044103 - 044110");
    heuristic(bp, reference, "2007 Science 120 044103 - 044110");
    heuristic(bp, reference, "Science. 2007, 120, 044103 - 044110");
    heuristic(bp, reference, "Science. 2007 May 2; 120, 044103 - 044110");
    heuristic(bp, reference, "Science. 2007 120: 044103 - 044110");
    heuristic(bp, reference, "Science 2007;120: 044103 - 044110");

    /****************************************************************
    journal-pages-volume-number-year
    ****************************************************************/
    // Usual pages
    reference.clearReference();
    reference.insert("journal", bp.parse("journal", "Science"));
    reference.insert("pages", bp.parse("pages", "117"));
    reference.insert("volume", bp.parse("volume", "120"));
    reference.insert("number", bp.parse("number", "1"));
    reference.insert("year", bp.parse("year", "2007"));
    write(bp, reference);
    heuristic(bp, reference, "Science 120(1), 117(2007)");
    heuristic(bp, reference, "Science 120(1), 117(2007)");
    heuristic(bp, reference, "Science 120(1): 117, 2007");
    heuristic(bp, reference, "Science 2007, 120(1): 117");
    heuristic(bp, reference, "Science 2007 120(1): 117");
    heuristic(bp, reference, "Science 2007, 120(1), 117");
    heuristic(bp, reference, "Science, 2007, 120 (1), p 117");
    heuristic(bp, reference, "Science 2007 January 25; 120(1), 117");
    heuristic(bp, reference, "Science 2007 January 25 120(1), 117");
    heuristic(bp, reference, "Science 2007 May 25 120(1), 117");
    heuristic(bp, reference, "Science (2007), 120, 1, 117");
    heuristic(bp, reference, "Science, Vol. 120, No. 1 (2007) 117");

    reference.clearReference();
    reference.insert("journal", bp.parse("journal", "Science"));
    reference.insert("pages", bp.parse("pages", "10 - 17"));
    reference.insert("volume", bp.parse("volume", "120"));
    reference.insert("number", bp.parse("number", "1"));
    reference.insert("year", bp.parse("year", "2007"));
    write(bp, reference);
    heuristic(bp, reference, "Science 120(1), 10 - 17(2007)");
    heuristic(bp, reference, "Science 120(1), 10 - 17(2007)");
    heuristic(bp, reference, "Science 120(1): 10 - 17, 2007");
    heuristic(bp, reference, "Science 2007, 120(1): 10 - 17");
    heuristic(bp, reference, "Science. 2007, 120(1): 10 - 7");
    heuristic(bp, reference, "Science. 2007 120(1): 10 - 7");
    heuristic(bp, reference, "Science. 2007, 120(1): 10 8pp");
    heuristic(bp, reference, "Science. 2007, 120(1), 10 - 17");
    heuristic(bp, reference, "Science. 2007, 120(1), pp 10 - 17");
    heuristic(bp, reference, "Science. 2007 January 25, 120(1), pp 10 - 17");
    heuristic(bp, reference, "Science (2007), 120, 1, pp. 10-17");

    reference.clearReference();
    reference.insert("journal", bp.parse("journal", "Science"));
    reference.insert("pages", bp.parse("pages", "117"));
    reference.insert("volume", bp.parse("volume", "120"));
    reference.insert("number", bp.parse("number", "1 - 6"));
    reference.insert("year", bp.parse("year", "2007"));
    write(bp, reference);
    heuristic(bp, reference, "Science 120(1 - 6), 117(2007)");
    heuristic(bp, reference, "Science 120(1 - 6), 117(2007)");
    heuristic(bp, reference, "Science 120(1 - 6): 117, 2007");
    heuristic(bp, reference, "Science 2007, 120(1 - 6): 117");
    heuristic(bp, reference, "Science 2007 120(1 - 6): 117");
    heuristic(bp, reference, "Science 2007 May 25 120(1 - 6): 117");

    reference.clearReference();
    reference.insert("journal", bp.parse("journal", "Science"));
    reference.insert("pages", bp.parse("pages", "10 - 17"));
    reference.insert("volume", bp.parse("volume", "120"));
    reference.insert("number", bp.parse("number", "1 - 6"));
    reference.insert("year", bp.parse("year", "2007"));
    write(bp, reference);
    heuristic(bp, reference, "Science 120(1 - 6), 10 - 17(2007)");
    heuristic(bp, reference, "Science 120(1 - 6), 10 - 17(2007)");
    heuristic(bp, reference, "Science 120(1 - 6): 10 - 17, 2007");
    heuristic(bp, reference, "Science 2007, 120(1 - 6): 10 - 17");
    heuristic(bp, reference, "Science. 2007, 120(1 - 6): 10 - 7");
    heuristic(bp, reference, "Science. 2007, 120(1 - 6): 10 8pp");
    heuristic(bp, reference, "Science 2007 120(1 - 6): 10 8pp");
    heuristic(bp, reference, "Science 2007 May 25 120(1 - 6): 10 8pp");

    // Pages susceptible to be confused by years
    reference.clearReference();
    reference.insert("journal", bp.parse("journal", "Science"));
    reference.insert("pages", bp.parse("pages", "1922"));
    reference.insert("volume", bp.parse("volume", "120"));
    reference.insert("number", bp.parse("number", "1"));
    reference.insert("year", bp.parse("year", "2007"));
    write(bp, reference);
    heuristic(bp, reference, "Science 120(1), 1922(2007)");
    heuristic(bp, reference, "Science 120(1), 1922(2007)");
    heuristic(bp, reference, "Science 120(1): 1922, 2007");
    heuristic(bp, reference, "Science 2007, 120(1): 1922");
    heuristic(bp, reference, "Science 2007, 120(1), 1922");
    heuristic(bp, reference, "Science 2007 120(1): 1922");
    heuristic(bp, reference, "Science 2007 May 25 120(1): 1922");
    heuristic(bp, reference, "Science, Vol. 120, No. 1 (2007) 1922");

    reference.clearReference();
    reference.insert("journal", bp.parse("journal", "Science"));
    reference.insert("pages", bp.parse("pages", "1922 - 1927"));
    reference.insert("volume", bp.parse("volume", "120"));
    reference.insert("number", bp.parse("number", "1"));
    reference.insert("year", bp.parse("year", "2007"));
    write(bp, reference);
    heuristic(bp, reference, "Science 120(1), 1922 - 1927(2007)");
    heuristic(bp, reference, "Science 120(1), 1922 - 1927(2007)");
    heuristic(bp, reference, "Science 120(1): 1922 - 1927, 2007");
    heuristic(bp, reference, "Science 2007, 120(1): 1922 - 1927");
    heuristic(bp, reference, "Science. 2007, 120(1): 1922 - 1927");
    heuristic(bp, reference, "Science. 2007, 120(1): 1922 6pp");
    heuristic(bp, reference, "Science. 2007 120(1): 1922 6pp");
    heuristic(bp, reference, "Science. 2007, 120(1), 1922 - 1927");
    heuristic(bp, reference, "Science. 2007, 120(1), pp 1922 - 1927");
    heuristic(bp, reference, "Science. 2007 May 25, 120(1), pp 1922 - 1927");
    heuristic(bp, reference, "Science (2007), 120, 1, pp. 1922-1927");
    heuristic(bp, reference, "Science, Vol. 120, No. 1 (2007) 1922 - 1927");

    reference.clearReference();
    reference.insert("journal", bp.parse("journal", "Science"));
    reference.insert("pages", bp.parse("pages", "1922"));
    reference.insert("volume", bp.parse("volume", "120"));
    reference.insert("number", bp.parse("number", "1 - 6"));
    reference.insert("year", bp.parse("year", "2007"));
    write(bp, reference);
    heuristic(bp, reference, "Science 120(1 - 6), 1922(2007)");
    heuristic(bp, reference, "Science 120(1 - 6), 1922(2007)");
    heuristic(bp, reference, "Science 120(1 - 6): 1922, 2007");
    heuristic(bp, reference, "Science 2007, 120(1 - 6): 1922");
    heuristic(bp, reference, "Science 2007 120(1 - 6): 1922");
    heuristic(bp, reference, "Science 2007 May 25 120(1 - 6): 1922");

    reference.clearReference();
    reference.insert("journal", bp.parse("journal", "Science"));
    reference.insert("pages", bp.parse("pages", "1922 - 1927"));
    reference.insert("volume", bp.parse("volume", "120"));
    reference.insert("number", bp.parse("number", "1 - 6"));
    reference.insert("year", bp.parse("year", "2007"));
    write(bp, reference);
    heuristic(bp, reference, "Science 120(1 - 6), 1922 - 1927(2007)");
    heuristic(bp, reference, "Science 120(1 - 6), 1922 - 1927(2007)");
    heuristic(bp, reference, "Science 120(1 - 6): 1922 - 1927, 2007");
    heuristic(bp, reference, "Science 2007, 120(1 - 6): 1922 - 1927");
    heuristic(bp, reference, "Science 2007 120(1 - 6): 1922 - 1927");
    heuristic(bp, reference, "Science. 2007, 120(1 - 6): 1922 - 7");
    heuristic(bp, reference, "Science. 2007, 120(1 - 6): 1922 6pp");
    heuristic(bp, reference, "Science. 2007 May 25, 120(1 - 6): 1922 6pp");
}

void c2bTests::heuristic_misc()
{
    cout << endl;
    cout << "-----------------------------" << endl;
    cout << "Test miscellaneous heuristics" << endl;
    cout << "-----------------------------" << endl;

    bibParser bp;
    bibReference reference;

    // abstract
    reference.clearReference();
    reference.insert("abstract", bp.parse("abstract", "Some text."));
    write(bp, reference);
    heuristic(bp, reference, "...\n\nAbstract. Some text.\n");
    heuristic(bp, reference, "...\n\nAbstract.\n Some text.\n");
    heuristic(bp, reference, "...\n\nAbstract:\n Some text.\n");
    heuristic(bp, reference, "...\n\nAbstract\n Some text.\n");
    heuristic(bp, reference, "...\n\nSummary. Some text.\n");
    heuristic(bp, reference, "...\n\nSummary:\n Some text.\n");
    heuristic(bp, reference, "...\n\nSummary\n Some text.\n");

    // keywords
    reference.clearReference();
    reference.insert("keywords", bp.parse("keywords", "Some text."));
    write(bp, reference);
    heuristic(bp, reference, "...\n\nKeywords:\n Some text.\n");
    heuristic(bp, reference, "...\n\nKeywords. Some text.\n");

    // title
    reference.clearReference();
    reference.insert("title", bp.parse("title", "Some text."));
    write(bp, reference);
    heuristic(bp, reference, "...\n\nTitle: Some text.\n");
    heuristic(bp, reference, "...\n\nTitle:\n Some text.\n");
}

void c2bTests::heuristic(bibParser& bp, const bibReference& reference, const QString& text)
{
    bp.clearCurrentReference();
    bp.guessFields(text);
    const bool passed(bp.toBibTeX() == bp.toBibTeX(reference));
    ++_test_count;
    if (!passed)
        ++_failed_test_count;
    cout << QString("[%1]\t'%2'\n").arg(boolToStr(passed), text);
    if (!passed)
        qDebug() << "Guessed:\n" << bp.toBibTeX();
}

void c2bTests::check_test(const bool passed, const QString& input, const QString& output)
{
    ++_test_count;
    if (!passed)
        ++_failed_test_count;
    cout << QString("[%1]\t'%2'\n").arg(boolToStr(passed), input);
    if (!passed)
        qDebug() << output;
}

void c2bTests::write(const bibParser& bp, const bibReference& reference)
{
    cout << endl;
    const QStringList& bibliographicFields = bp.bibliographicFields();
    for (int i = 0; i < bibliographicFields.count(); ++i)
    {
        const QString fvalue(reference.value(bibliographicFields.at(i)));
        if (!fvalue.isEmpty())
        {
            const QString& fd = bibliographicFields.at(i);
            const QString padding(QString().fill(' ', 12 - fd.length()));
            cout << (fd + padding + " = {" + fvalue + '}') << endl;
        }
    }
}

#if C2B_CHECK_PATTERNS
#include "frequentPatterns.h"
#endif
void c2bTests::heuristic_check_patterns()
{
#if C2B_CHECK_PATTERNS
    frequentPatterns fp;
    fp.process();
    return;
#endif
    cout << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "Check pattern clashes in heuristic author recognition" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << endl;
    QFileInfoList flist = QDir(_bibliographic_dir).entryInfoList(QStringList() << "*.bib");
    bibParser bp;
    bibReference reference;
    QStringList fields;
    fields.append("author");
    QHash<QString, int> adictionary;

    for (int f = 0; f < flist.count(); ++f)
    {
        const QString bib_file(flist.at(f).absoluteFilePath());
        bp.initReferenceParsing(_bibliographic_dir, fields, &reference);
        while (bp.referencesIn(c2bUtils::fileToString(bib_file), &reference))
        {
            const QString a(c2bUtils::toAscii(reference.value("author"), c2bUtils::Collation));
            const QStringList as(a.split(c2bUtils::nonLetter));
            for (int i = 0; i < as.count(); ++i)
                adictionary.insert(as.at(i), 1 + adictionary.value(as.at(i), 0));
        }
    }
    QStringList word_prefix_lexicon(
        c2bUtils::fileToString(":/txt/txt/word_prefix_lexicon.txt").split(c2bUtils::nonLetter, QString::SkipEmptyParts));
    for (int i = 0; i < word_prefix_lexicon.count(); ++i)
        word_prefix_lexicon[i].replace('_', "\\b");

    QStringList anames(adictionary.keys());
    QRegExp wre;
    for (int i = 0; i < word_prefix_lexicon.count(); ++i)
        for (int j = 0; j < anames.count(); ++j)
        {
            const QString& wp = word_prefix_lexicon.at(i);
            const QString& a = anames.at(j);
            wre.setPattern(wp);
            if (a.contains(wre))
                cout << "LEXICON CLASH: " << wp << ' ' << a << endl;
        }
}

QString c2bTests::decomposition(const QChar& c)
{
    // Write char decomposition
    const QString d(c.decomposition());
    QString wd;
    for (int i = 0; i < d.length(); ++i)
        wd += '[' + d.at(i) + ']';
    return wd;
}
