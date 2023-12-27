/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef CB2BIB_UTILITIES_H
#define CB2BIB_UTILITIES_H

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QRegExp>
#include <QString>

#include <QtDebug>

#ifdef C2B_TRACE_MEMORY
#include <iostream>
#include <sys/resource.h>
#endif

class txtmatcher;


/**
    cb2Bib core utilities
*/
namespace c2bUtils
{

enum AsciiConversion
{
    Cleanup,
    Collation,
    FromBibTeX,
    KeepWords,
    Transliterate
};

extern QString setCapitalization(const QString& str);
extern QString toAscii(const QString& str, const AsciiConversion type);
extern QString& bibToC2b(QString& str);
extern QString& c2bToBib(QString& str);
extern QString& fillString(QString& str, const QRegExp& pattern, const QChar& ch);
extern QString& fillString(QString& str, const QRegularExpression& pattern, const QChar& ch);
extern QString& fillString(QString& str, const QString& pattern, const QChar& ch);
extern QString& fillString(QString& str, const QStringMatcher& pattern, const QChar& ch);
extern QString& fillString(QString& str, const txtmatcher& pattern, const QChar& ch);
extern QString& fullBibToC2b(QString& str);
extern QString& simplifyString(QString& str);
extern QString& stripDiacritics(QString& str);

extern const QRegExp nonAsciiLetter;
extern const QRegExp nonLetter;
extern const QString arxivUrl;
extern const QString metadatasection;
extern const QString pubmedUrl;

inline QString& cleanEquations(QString& str)
{
    // Simplify equations
    const QChar eq('$');
    int i(str.indexOf(eq));
    if (i == -1)
        return str;
    const QChar ob('{');
    const QChar cb('}');
    const QChar ca('^');
    const QChar sl('\\');
    const QChar us('_');
    const int n(str.length());
    int p(i);
    while (i < n)
    {
        if (str.at(i) == eq)
        {
            bool has_eq(false);
            for (int j = i + 1; j < std::min(i + 70, n); ++j) // Set a max equation length
                if (str.at(j) == eq)
                {
                    has_eq = true;
                    for (int k = i + 1; k < j; ++k)
                    {
                        const QChar& ck = str.at(k);
                        if (ck != us && ck != ca && ck != sl && ck != ob && ck != cb)
                            str[p++] = str.at(k);
                    }
                    i = j;
                    break;
                }
            if (!has_eq)
                str[p++] = str.at(i);
        }
        else
            str[p++] = str.at(i);
        ++i;
    }
    str.chop(n - p);
    return str;
}

inline QString& cleanTitle(QString& title, const bool clean_period = false)
{
    // Remove TeX braces and equation $
    cleanEquations(title);
    title.remove(QLatin1Char('{'));
    title.remove(QLatin1Char('}'));
    title = title.trimmed();
    if (clean_period && title.length() > 0)
        if (title[title.length() - 1] == QLatin1Char('.'))
            title.chop(1);
    return title;
}

inline QString toHtmlString(QString str)
{
    // Encode some symbols to HTML for proper browser display
    str.replace(QLatin1Char('<'), QLatin1String("&#060;"));
    str.replace(QLatin1Char('>'), QLatin1String("&#062;"));
    str.replace(QLatin1Char('%'), QLatin1String("&#037;"));
    str.replace(QRegExp("_\\{([^\\}]*)\\}"), "<sub>\\1</sub>");
    str.replace(QRegExp("\\^\\{([^\\}]*)\\}"), "<sup>\\1</sup>");
    cleanEquations(str);
    return str;
}

inline QString firstPage(QString pages)
{
    simplifyString(pages);
    pages.remove(QRegExp("[\\s\\-].*$"));
    return pages;
}

inline bool isLowerCaseString(const QString& str, const int pos0 = 0, int posn = -1)
{
    if (str.isEmpty())
        return false;
    if (posn < 0)
        posn = str.length();
    for (int i = pos0; i < posn; ++i)
        if (str.at(i).isLetter())
            if (str.at(i).category() == QChar::Letter_Uppercase)
                return false;
    return true;
}

inline bool isUpperCaseString(const QString& str, const int pos0 = 0, int posn = -1)
{
    if (str.isEmpty())
        return false;
    if (posn < 0)
        posn = str.length();
    for (int i = pos0; i < posn; ++i)
        if (str.at(i).isLetter())
            if (str.at(i).category() == QChar::Letter_Lowercase)
                return false;
    return true;
}

/**
    Gives a document absolute, full path-name
*/
inline QString documentAbsoluteName(const bool bibtexrelative, const QString& bibtexfn, const QString& docdir,
                                    const QString& docfn)
{
    QString name;
    if (bibtexrelative)
    {
        // The bibtexfn might be relative in USB mode, calling absolutePath will restore its fullname.
        QDir ddir(QFileInfo(bibtexfn).absolutePath());
        // When bibtexrelative, should only be relative to bibtexfn, (safely) disregard if it is absolute.
        if (QDir(docdir).isRelative())
            name = ddir.absolutePath() + QLatin1Char('/') + docdir + QLatin1Char('/') + QFileInfo(docfn).fileName();
        else
            name = ddir.absolutePath() + QLatin1Char('/') + QFileInfo(docfn).fileName();
    }
    else
        // The docdir should be absolute here, whether or not working in USB mode. If it was relative,
        // this will set it with respect the application directory.
        name = QDir(docdir).absolutePath() + QLatin1Char('/') + QFileInfo(docfn).fileName();
    return QDir::toNativeSeparators(QDir::cleanPath(name));
}

/**
    Gives a document filename, as it will be written to BibTeX file tag
*/
inline QString documentFilename(const bool bibtexrelative, const QString& bibtexfn, const QString& docdir,
                                const QString& docfn)
{
    QString name;
    if (bibtexrelative)
    {
        QDir ddir(QFileInfo(bibtexfn).absolutePath());
        if (QDir(docdir).isRelative())
            name = ddir.absolutePath() + QLatin1Char('/') + docdir + QLatin1Char('/') + QFileInfo(docfn).fileName();
        else
            name = ddir.absolutePath() + QLatin1Char('/') + QFileInfo(docfn).fileName();
        name = ddir.relativeFilePath(name);
    }
    else
        name = QDir(docdir).absolutePath() + QLatin1Char('/') + QFileInfo(docfn).fileName();
    return QDir::toNativeSeparators(QDir::cleanPath(name));
}

/**
    Gives a document path as it will be written to BibTeX file tag
*/
inline QString documentDirName(const bool bibtexrelative, const QString& bibtexfn, const QString& docdir)
{
    QString name;
    if (bibtexrelative)
    {
        QDir ddir(QFileInfo(bibtexfn).absolutePath());
        if (QDir(docdir).isRelative())
            name = ddir.absolutePath() + QLatin1Char('/') + docdir;
        else
            name = docdir + QLatin1Char('/');
        name = ddir.relativeFilePath(name);
    }
    else
        name = QDir(docdir).absolutePath();
    name = QDir::toNativeSeparators(QDir::cleanPath(name));
    return name;
}

inline QString fileToString(const QString& fn, bool delete_on_close = false)
{
    if (fn.isEmpty())
        return QString();
    QFile f(fn);
    if (f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&f);
        stream.setCodec("UTF-8");
        stream.setAutoDetectUnicode(true);
        const QString contents(stream.readAll());
        if (delete_on_close)
            f.remove();
        else
            f.close();
        return contents;
    }
    else
        return QString();
}

inline bool stringToFile(const QString& str, const QString& fn)
{
    if (fn.isEmpty())
        return false;
    QFile f(fn);
    if (f.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&f);
        stream.setCodec("UTF-8");
        stream.setAutoDetectUnicode(true);
        stream << str;
        f.close();
        return true;
    }
    else
        return false;
}

inline QStringList filesInDir(const QString& dir, const QStringList& filters)
{
    QStringList files;
    QFileInfo fi(dir);
    if (!fi.exists())
        return files;
    if (fi.isDir())
    {
        QDir d(dir);
        const QFileInfoList dil(d.entryInfoList(filters));
        for (int i = 0; i < dil.count(); ++i)
            files.append(QDir::toNativeSeparators(QDir::cleanPath(dil.at(i).absoluteFilePath())));
    }
    else if (fi.isFile())
        files.append(QDir::toNativeSeparators(QDir::cleanPath(fi.absoluteFilePath())));
    return files;
}

inline int nearInteger(double a)
{
    int ia = int(a);
    a = a - double(ia);
    if (a >= 0.5)
        ia++;
    else if (a <= -0.5)
        ia--;
    return ia;
}

inline bool inBraces(const int pos, const QString& str, QString* in)
{
    if (str.at(pos - 1) == QLatin1Char('{')) // pos > 0 always
    {
        int open_braces(1);
        const QChar open('{');
        const QChar close('}');
        for (int i = pos; i < str.length(); ++i)
        {
            if (str.at(i) < open)
                continue;
            const QChar& si(str.at(i));
            if (si == open)
                open_braces++;
            else if (si == close)
                open_braces--;
            if (open_braces == 0)
            {
                *in = str.mid(pos, i - pos);
                return true;
            }
        }
    }
    else // in Quotes
    {
        const QChar quote('"');
        const QChar comma(',');
        for (int i = pos; i < str.length() - 1; ++i)
            if (str.at(i) == quote)
                if (str.at(i + 1) == comma)
                {
                    *in = str.mid(pos, i - pos);
                    return true;
                }
    }
    return false;
}

inline bool patternLengthMoreThan(const QRegExp& s1, const QRegExp& s2)
{
    return s1.pattern().length() > s2.pattern().length();
}

inline QString fromQtXmlString(QString str)
{
    // Workaround (It will be fixed in Qt 4.5)
    // Escape toXmlString already done by ExifTool
    str.replace(QLatin1String("%%#39;"), QLatin1String("'"));
    str.replace(QLatin1String("%%amp;"), QLatin1String("&"));
    str.replace(QLatin1String("%%gt;"), QLatin1String(">"));
    str.replace(QLatin1String("%%lt;"), QLatin1String("<"));
    str.replace(QLatin1String("%%quot;"), QLatin1String("\""));
    return str;
}

inline QString toQtXmlString(QString str)
{
    // Workaround (It will be fixed in Qt 4.5)
    // Escape toXmlString already done by ExifTool
    str.replace(QLatin1String("&#39;"), QLatin1String("%%#39;"));
    str.replace(QLatin1String("&amp;"), QLatin1String("%%amp;"));
    str.replace(QLatin1String("&gt;"), QLatin1String("%%gt;"));
    str.replace(QLatin1String("&lt;"), QLatin1String("%%lt;"));
    str.replace(QLatin1String("&quot;"), QLatin1String("%%quot;"));
    return str;
}
#ifdef C2B_TRACE_MEMORY
inline void print_maximum_resident_set_size()
{
    rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0)
        std::cerr << "[cb2bib] maxrss: " << usage.ru_maxrss << std::endl;
}
#endif
inline void warn(const QString& ms)
{
    qWarning("[cb2bib] %s.", (const char*)ms.toLatin1());
}

inline void debug(const QString&
#ifdef C2B_DEBUG
                  debug_ms
#endif
                 )
{
#ifdef C2B_DEBUG
    qDebug() << "[cb2bib] " << debug_ms;
#endif
}

inline QByteArray stringToByteArray(const QString& s)
{
    return QByteArray(reinterpret_cast<const char*>(s.unicode()), s.size() * sizeof(ushort));
}

inline QString byteArrayToString(const QByteArray& ba)
{
    return QString(reinterpret_cast<const QChar*>(ba.constData()), ba.size() / sizeof(ushort));
}

extern QString fromUtf8(const QByteArray& ba);
extern QByteArray compressString(const QString& decompressed);
extern QString decompressString(const QByteArray& compressed);

} // namespace c2bUtils

#endif
