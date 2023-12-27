/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "searchPattern.h"

#include "triads.h"

#include <QMap>


#ifndef __has_cpp_attribute
#define __has_cpp_attribute(name) 0
#endif
#if __has_cpp_attribute(fallthrough)
#define FALLTHROUGH [[fallthrough]]
#else
#define FALLTHROUGH
#endif


/**
    Top level driver for calling cb2Bib search types
*/
searchPattern::searchPattern(const QString& pattern, const QString& patternType)
    : _matcher(pattern, typemap().value(patternType), Qt::CaseInsensitive)
{
    _modifier.NOT = false;
    _modifier.string = _matcher.typedpattern;
    _rank = 0;
}

searchPattern::searchPattern(const bool NOT, const bool caseSensitive, const QString& patternType, const QString& scope,
                             const QChar& yearScope, const QString& pattern)
    : _matcher(pattern, typemap().value(patternType), qtcase(caseSensitive))
{
    _modifier.NOT = NOT;
    _modifier.string = _matcher.typedpattern;
    _modifier.scope = scope;
    _modifier.yearScope = yearScope;

    if (_modifier.NOT)
        _formatted_string += "NOT.";
    _formatted_string += QString(" [%1][%2|case=%3]").arg(_modifier.string, patternType).arg(caseSensitive);
    if (_modifier.scope == "year")
        _formatted_string += QString(" IN [%1(%2)]").arg(_modifier.scope).arg(_modifier.yearScope);
    else
        _formatted_string += QString(" IN [%1]").arg(_modifier.scope);

    // Set an approximate ranking to speed up composite searches
    _rank = 0;
    if (_modifier.scope == "file")
        _rank += 200;
    else if (_modifier.scope == "all")
        _rank += 100;
    else if (_modifier.scope == "year" || _modifier.scope == "volume" || _modifier.scope == "pages")
        _rank += 50;
    else
        _rank += 1;
    if (!caseSensitive)
        _rank *= 2;
    if (_matcher.type == FixedStringAllWords || _matcher.type == FixedStringAnyWord)
        _rank *= 5;
    else if (_matcher.type == ApproximateString)
        _rank *= 10;
    else if (_matcher.type == RegularExpression)
        _rank *= 20;
}

const QStringList searchPattern::types()
{
    return typemap().keys();
}

const QString searchPattern::type(const Type t)
{
    return typemap().key(t);
}

const QMap<QString, searchPattern::Type> searchPattern::typemap()
{
    QMap<QString, Type> tm;
    tm.insert(QObject::tr("Approximate string"), ApproximateString);
    tm.insert(QObject::tr("Context"), Context);
    tm.insert(QObject::tr("Fixed string: All Words"), FixedStringAllWords);
    tm.insert(QObject::tr("Fixed string: Any Word"), FixedStringAnyWord);
    tm.insert(QObject::tr("Fixed string: Context"), FixedStringContext);
    tm.insert(QObject::tr("Fixed string"), FixedString);
    tm.insert(QObject::tr("Regular expression"), RegularExpression);
    tm.insert(QObject::tr("Wildcard"), Wildcard);
    return tm;
}


searchPattern::matcher::matcher(const QString& pattern, const Type t, const Qt::CaseSensitivity cs)
    : csensitivity(cs), type(t), length(-1)
{
    _set_typed_pattern(pattern);

    switch (t)
    {
    default:
        c2bUtils::warn(QObject::tr("Internal Error: Invalid search pattern type. Set to 'Approximate string'"));
        FALLTHROUGH;
    case ApproximateString:
    {
        appexp.setPattern(typedpattern, cs);
        if (appexp.isMultipattern())
        {
            signature = triads::textSignature(typedpattern);
            subsignatures = triads::textSignature(appexp.substrings());
        }
        else // Skip signatures for regular expression case
        {
            regexp = appexp.regexp();
            type = RegularExpression;
        }
    }
    break;
    case Context:
    {
        cstemexp.setPattern(typedpattern, cs);
        signature = triads::textSignature(cstemexp.signatureString());
    }
    break;
    case FixedStringAnyWord:
    {
        wordexp.setPattern(typedpattern, wordPattern::AnyWord, cs);
        signature = triads::textSignature(typedpattern);
        subsignatures = triads::textSignature(wordexp.substrings());
    }
    break;
    case FixedStringAllWords:
    {
        wordexp.setPattern(typedpattern, wordPattern::AllWords, cs);
        signature = triads::textSignature(typedpattern);
        subsignatures.fill(signature, wordexp.subpatternCount());
    }
    break;
    case FixedStringContext:
    {
        cwordexp.setPattern(typedpattern, cs);
        signature = triads::textSignature(typedpattern);
    }
    break;
    case FixedString:
    {
        strexp.setPattern(typedpattern);
        strexp.setCaseSensitivity(cs);
        signature = triads::textSignature(typedpattern);
    }
    break;
    case RegularExpression:
    {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 4, 0)) && (QT_VERSION < QT_VERSION_CHECK(5, 12, 0))
        const QRegularExpression::PatternOptions po(QRegularExpression::DontCaptureOption |
                QRegularExpression::UseUnicodePropertiesOption |
                QRegularExpression::OptimizeOnFirstUsageOption);
#else
        const QRegularExpression::PatternOptions po(QRegularExpression::DontCaptureOption |
                QRegularExpression::UseUnicodePropertiesOption);
#endif
        regexp.setPattern(typedpattern);
        regexp.setPatternOptions(cs == Qt::CaseSensitive ? po : po | QRegularExpression::CaseInsensitiveOption);
    }
    break;
    case Wildcard:
    {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 4, 0)) && (QT_VERSION < QT_VERSION_CHECK(5, 12, 0))
        const QRegularExpression::PatternOptions po(
            QRegularExpression::InvertedGreedinessOption | QRegularExpression::DontCaptureOption |
            QRegularExpression::UseUnicodePropertiesOption | QRegularExpression::OptimizeOnFirstUsageOption);
#else
        const QRegularExpression::PatternOptions po(QRegularExpression::InvertedGreedinessOption |
                QRegularExpression::DontCaptureOption |
                QRegularExpression::UseUnicodePropertiesOption);
#endif
        regexp.setPattern(_wildcard_escaped(typedpattern));
        regexp.setPatternOptions(cs == Qt::CaseSensitive ? po : po | QRegularExpression::CaseInsensitiveOption);
        signature = triads::textSignature(typedpattern);
    }
    break;
    }
}

bool searchPattern::matcher::match(const QString& contents) const
{
    length = -1;
    switch (type)
    {
    case ApproximateString:
        return appexp.matches(contents);
    case Context:
        return cstemexp.indexIn(contents) != -1;
    case FixedStringAnyWord:
    case FixedStringAllWords:
        return wordexp.matches(contents);
    case FixedStringContext:
        return cwordexp.indexIn(contents) != -1;
    case FixedString:
        return strexp.indexIn(contents) != -1;
    default:
        return regexp.match(contents).hasMatch();
    }
}

bool searchPattern::matcher::match(const documentContents& contents) const
{
    length = -1;
    switch (type)
    {
    case ApproximateString:
        return _match_any(appexp.subpatternCount(), appexp.submatchers(), contents);
    case Context:
        return _match(cstemexp, signature, contents);
    case FixedStringAnyWord:
        return _match_any(wordexp.subpatternCount(), wordexp.submatchers(), contents);
    case FixedStringAllWords:
        return _match_all(wordexp.subpatternCount(), wordexp.submatchers(), contents);
    case FixedStringContext:
        return _match(cwordexp, signature, contents);
    case FixedString:
        return _match(strexp, signature, contents);
    default:
        return _match(regexp, signature, contents);
    }
}

int searchPattern::matcher::index(const QString& contents, const int from) const
{
    int i;
    switch (type)
    {
    case ApproximateString:
        i = appexp.indexIn(contents, from);
        length = appexp.matchedLength();
        return i;
    case Context:
        i = cstemexp.indexIn(contents, from);
        length = cstemexp.matchedLength();
        return i;
    case FixedStringAnyWord:
    case FixedStringAllWords:
        i = wordexp.indexIn(contents, from);
        length = wordexp.matchedLength();
        return i;
    case FixedStringContext:
        i = cwordexp.indexIn(contents, from);
        length = cwordexp.matchedLength();
        return i;
    case FixedString:
        i = strexp.indexIn(contents, from);
        length = strexp.pattern().length();
        return i;
    default:
        regexp_match = regexp.match(contents, from);
        i = regexp_match.capturedStart();
        length = regexp_match.capturedLength();
        return i;
    }
}

void searchPattern::matcher::_set_typed_pattern(const QString& pattern)
{
    const QRegExp rmors("\\|[^\\s]*");
    const QRegExp rmnws("[\\W_]");
    const QRegExp rmnls("[\\W\\d]");

    QString stripped(pattern);
    switch (type)
    {
    case ApproximateString:
    case Context:
    case FixedStringAllWords:
        stripped.replace(rmors, " ");
        stripped.replace(rmnws, " ");
        break;
    case FixedStringAnyWord:
        stripped.replace(rmnws, " ");
        break;
    case FixedStringContext:
        stripped.replace(rmors, " ");
        break;
    case RegularExpression:
        stripped.replace(rmnls, " ");
        break;
    default:
        break;
    }
    stripped = stripped.simplified();
    plength = type == FixedStringAllWords || type == FixedStringAnyWord ? 0 : stripped.length();

    switch (type)
    {
    case Context:
    case FixedString:
    case RegularExpression:
    case Wildcard:
        typedpattern = pattern.simplified();
        break;
    default:
        typedpattern = stripped;
        break;
    }
#ifdef C2B_DEBUG_SEARCHING
    qDebug() << "searchPattern::matcher::_set_typed_pattern pattern      " << pattern << pattern.length();
    qDebug() << "searchPattern::matcher::_set_typed_pattern stripped     " << stripped << stripped.length() << plength;
    qDebug() << "searchPattern::matcher::_set_typed_pattern typedpattern " << typedpattern << typedpattern.length();
#endif
}

QString searchPattern::matcher::_wildcard_escaped(const QString& pattern)
{
    QString scaped;
    for (int i = 0; i < pattern.length(); ++i)
        if (pattern.at(i) == '*')
            scaped += ".*";
        else if (pattern.at(i) == '?')
            scaped += '.';
        else
            scaped += QRegularExpression::escape(pattern.at(i));
    return scaped;
}
