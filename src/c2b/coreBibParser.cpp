/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "coreBibParser.h"


coreBibParser::coreBibParser(QObject* parento)
    : QObject(parento),
      _at(QLatin1Char('@')),
      _close(QLatin1Char('}')),
      _colon(QLatin1Char(':')),
      _comma(QLatin1Char(',')),
      _cr(13),
      _hyphen(QLatin1Char('-')),
      _lca(QLatin1Char('a')),
      _lcz(QLatin1Char('z')),
      _nl(10),
      _open(QLatin1Char('{')),
      _period(QLatin1Char('.')),
      _pound(QLatin1Char('#')),
      _quote(QLatin1Char('"')),
      _space(QLatin1Char(' ')),
      _tilde(QLatin1Char('~')),
      _uca(QLatin1Char('A')),
      _ucz(QLatin1Char('Z'))
{
    _settingsP = settings::instance();

    // Setting bibliographic types
    setTypes();
    // Setting bibliographic fields
    setFields();
    // Setting regular expressions
    setRegularExpressions();
}


bool coreBibParser::referencesIn(const QString& str, bibReference* ref)
{
    // File parsing for given fields in ref
    ref->clearReference();
    const int pos(referenceStarts(str, ref->pos));
    if (pos < 0)
        return false;
    referenceContents(str, ref, pos);
    return true;
}

bool coreBibParser::referenceAtKey(const QString& key, const QString& str, bibReference* ref)
{
    // File parsing for given fields in ref
    ref->clearReference();
    const int pos(referenceStarts(key, str));
    if (pos < 0)
        return false;
    referenceContents(str, ref, pos);
    return true;
}

QString coreBibParser::referenceToFomattedBibTeX(const bibReference& ref) const
{
    // Writes a BibTeX string from struct bibReference
    QString BibString(QLatin1Char('@') + ref.typeName + QLatin1Char('{') + ref.citeidName);
    const bool ConvertReferenceToLaTeX(_settingsP->value("cb2Bib/ConvertReferenceToLaTeX").toBool());
    const bool PostprocessMonth(_settingsP->value("cb2Bib/PostprocessMonth").toBool());
    const bool UseDoubleBraces(_settingsP->value("cb2Bib/UseDoubleBraces").toBool());
    QStringList::const_iterator it = _bibliographic_fields.begin();
    while (it != _bibliographic_fields.end())
    {
        QString fvalue(ref.value(*it));
        if (!fvalue.isEmpty())
        {
            if (ConvertReferenceToLaTeX)
                c2bUtils::c2bToBib(fvalue);
            const QString fd(*it);
            const QString padding(QString().fill(' ', 12 - fd.length()));
            if (fd == QLatin1String("title") || fd == QLatin1String("booktitle"))
            {
                if (UseDoubleBraces)
                    if (!fvalue.contains(QRegExp("^\\{.+\\}$")))
                        fvalue = '{' + fvalue + '}';
                fvalue = QLatin1Char('{') + fvalue + QLatin1Char('}');
            }
            else if (fd == QLatin1String("month"))
            {
                if (!PostprocessMonth)
                    fvalue = QLatin1Char('{') + fvalue + QLatin1Char('}');
            }
            else
                fvalue = QLatin1Char('{') + fvalue + QLatin1Char('}');
            BibString += QLatin1String(",\n") + fd + padding + QLatin1String(" = ") + fvalue;
        }
        ++it;
    }
    BibString += QLatin1String("\n}\n");
    return BibString;
}

QString coreBibParser::referenceToBibTeX(const bibReference& ref) const
{
    // Writes a BibTeX string from struct bibReference
    // No special formatting is done here
    QString BibString(QLatin1Char('@') + ref.typeName + QLatin1Char('{'));
    QStringList::const_iterator it(_bibliographic_fields.begin());
    while (it != _bibliographic_fields.end())
    {
        const QString fvalue(ref.value(*it));
        if (!fvalue.isEmpty())
        {
            const QString fd(*it);
            const QString padding(QString().fill(QLatin1Char(' '), 12 - fd.length()));
            BibString += QLatin1String(",\n") + fd + padding + QLatin1String(" = {") + fvalue + QLatin1Char('}');
        }
        ++it;
    }
    BibString += QLatin1String("\n}\n");
    return BibString;
}

QString coreBibParser::adjacentNumbers(const QString& numbers) const
{
    // Originally for pages, used also for multiple volume, number and year
    QString anums(numbers);
    anums.replace(c2bUtils::nonLetter, QLatin1String(" "));
    anums = c2bUtils::simplifyString(anums);
    if (anums.isEmpty() || anums == QLatin1String("0"))
        return QString();
    anums.replace(' ', '-');
    QRegExp rx1("^(\\d+)-(\\d+)-*pp$");
    QRegExp rx2("^(\\d+)-(\\d+)$");
    if (rx1.indexIn(anums) > -1)
    {
        anums = rx1.cap(1);
        int ilp(rx1.cap(2).toInt() - 1);
        if (ilp > 0)
            anums += QLatin1Char('-') + QString().setNum(rx1.cap(1).toInt() + ilp); // eg, 123-7pp  ->  123 - 129
    }
    else if (rx2.indexIn(anums) > -1)
    {
        QString fp(rx2.cap(1));
        anums = fp + '-';
        QString lp(rx2.cap(2));
        uint lfp(fp.length());
        uint llp(lp.length());
        if (lfp > llp)
            lp = fp.remove(lfp - llp, llp) + lp; // eg, 123-7  ->  123 - 127
        anums += lp;
    }
    const QString separator(_settingsP->value("cb2Bib/PageNumberSeparator").toString());
    if (separator.isEmpty())
        anums.replace('-', " - ");
    else
        anums.replace('-', separator);
    return anums;
}

void coreBibParser::setFields()
{
    _bibliographic_fields << QLatin1String("title") << QLatin1String("author") << QLatin1String("journal")
                          << QLatin1String("booktitle") << QLatin1String("series") << QLatin1String("chapter")
                          << QLatin1String("pages") << QLatin1String("volume") << QLatin1String("number")
                          << QLatin1String("edition") << QLatin1String("institution") << QLatin1String("organization")
                          << QLatin1String("school") << QLatin1String("address") << QLatin1String("month")
                          << QLatin1String("year") << QLatin1String("editor") << QLatin1String("publisher")
                          << QLatin1String("abstract") << QLatin1String("keywords") << QLatin1String("isbn")
                          << QLatin1String("issn") << QLatin1String("doi") << QLatin1String("eprint")
                          << QLatin1String("file") << QLatin1String("url") << QLatin1String("note")
                          << QLatin1String("annote");
    _sorted_bibliographic_fields = _bibliographic_fields;
    std::sort(_sorted_bibliographic_fields.begin(), _sorted_bibliographic_fields.end());
}

void coreBibParser::setTypes()
{
    _bibliographic_types << QLatin1String("") << QLatin1String("article") << QLatin1String("book")
                         << QLatin1String("booklet") << QLatin1String("conference") << QLatin1String("inbook")
                         << QLatin1String("incollection") << QLatin1String("inproceedings") << QLatin1String("manual")
                         << QLatin1String("mastersthesis") << QLatin1String("misc") << QLatin1String("periodical")
                         << QLatin1String("phdthesis") << QLatin1String("proceedings") << QLatin1String("techreport")
                         << QLatin1String("unpublished");
}

void coreBibParser::setRegularExpressions()
{
    _bib_begin0_re = QRegExp("^\\s*@\\w+\\s*\\{");
    _bib_begin1_re = QRegExp("[\\r\\n]\\s*@\\w+\\s*\\{");
    _bib_begin_at = txtmatcher("@", Qt::CaseSensitive, 0);
    _bib_begin_re = QRegExp("^@\\w+\\s*\\{");
    _bib_field_delimiter = txtmatcher("=", Qt::CaseSensitive, 0);
    _field_re = QRegExp("\\b(" + _bibliographic_fields.join("|") + ")\\b");
}

void coreBibParser::initReferenceParsing(const QString& dir, const QStringList& fields, bibReference* ref)
{
    setReferenceParsingDir(dir);
    // Init file parsing for given fields
    ref->clearFields();
    ref->clearReference();
    _current_bibliographic_fields = fields;
}

bibReference coreBibParser::wholeReference(const QString& str) const
{
    // Skip positionValue as it is not needed here
    bibReference ref;
    int pos(referenceStarts(str));
    if (pos < 0)
        return ref;
    QString str_ref(referenceAt(str, &pos));
    c2bUtils::fullBibToC2b(str_ref);
    c2bUtils::simplifyString(str_ref);
    setReferenceEnd(&str_ref);
    _parse_reference_fields(str_ref, _bibliographic_fields, &ref);
    return ref;
}

void coreBibParser::referenceContents(const QString& str, bibReference* ref, int pos) const
{
    // File parsing for_current_bibliographic_fields in ref
    ref->positionValue = pos;
    QString str_ref(referenceAt(str, &pos));
    ref->pos = pos;
    ref->rawReference = str_ref;
    c2bUtils::bibToC2b(str_ref);
    c2bUtils::simplifyString(str_ref);
    setReferenceEnd(&str_ref);
    ref->unicodeReference = str_ref;
    _parse_reference_fields(str_ref, _current_bibliographic_fields, ref);
    if (ref->contains(QLatin1String("file")))
        if (!QDir::isAbsolutePath(ref->value(QLatin1String("file"))))
            (*ref)[QLatin1String("file")] = _bib_file_dir + ref->value(QLatin1String("file"));
}

QString coreBibParser::singleReferenceField(const QString& field, const bibReference& ref) const
{
    // Simplified _parse_reference_fields function, excludes month and keywords peculiarities
    const QChar* const b(ref.unicodeReference.constData());
    const int length(ref.unicodeReference.length());
    if (length == 0 || b[0] != _at || field.isEmpty())
        return QString();
    const QChar lclc(field.at(field.length() - 1).toLower()), lcuc(field.at(field.length() - 1).toUpper());
    int cursor(1);
    while (true)
    {
        const int cd(_bib_field_delimiter.indexIn(b, length, cursor));
        if (cd < 1)
            break;
        const int fends(b[cd - 1] == _space ? cd - 2 : cd - 1);
        if (b[fends] != lclc && b[fends] != lcuc)
        {
            cursor = cd + 2;
            continue;
        }
        for (cursor = fends; cursor > 1; --cursor)
            if ((b[cursor] >= _lca && b[cursor] <= _lcz) || (b[cursor] >= _uca && b[cursor] <= _ucz))
                continue;
            else
                break;
        if (field.compare(ref.unicodeReference.midRef(cursor + 1, fends - cursor), Qt::CaseInsensitive) != 0)
        {
            cursor = cd + 2;
            continue;
        }
        const int vstarts(b[cd + 1] == _space ? cd + 2 : cd + 1);
        const int vends(_in_braces_ends(b, vstarts, length));
        if (vends > 0)
        {
            const int vs(b[vstarts + 1] == _space ? vstarts + 2 : vstarts + 1);
            return ref.unicodeReference.mid(vs, std::max(0, vends - vs + 1));
        }
        for (cursor = vstarts; cursor < length; ++cursor)
            if (!b[cursor].isLetterOrNumber())
                break;
        const int vnbends(cursor);
        if (b[cursor] == _space)
            ++cursor;
        if (b[cursor] == _comma)
            return ref.unicodeReference.mid(vstarts, std::max(0, vnbends - vstarts));
        cursor = cd + 2;
    }
    return QString();
}

static inline const QString* _ci_fields_index_of(const QStringList& fields, const ushort* const b, const int length)
{
    for (QStringList::const_iterator i = fields.constBegin(); i != fields.constEnd(); ++i)
    {
        if (length != i->length() || (b[0] | 0x20) != i->at(0).unicode())
            continue;
        for (int l = 1; l < length; ++l)
            if ((b[l] | 0x20) != i->at(l).unicode())
                goto next;
        return &(*i);
next:
        continue;
    }
    return nullptr;
}

void coreBibParser::_parse_reference_fields(const QString& bibstr, const QStringList& fields, bibReference* ref) const
{
    const QChar* const b(bibstr.constData());
    const int length(bibstr.length());

    if (length == 0 || b[0] != _at)
        return;
    int cursor;
    for (cursor = 1; cursor < length; ++cursor)
        if (!b[cursor].isLetterOrNumber())
            break;
    const int tends(cursor);
    if (b[cursor] == _space)
        ++cursor;
    if (b[cursor] == _open)
    {
        ref->typeName = bibstr.mid(1, tends - 1).toLower();
        ++cursor;
        if (b[cursor] == _space)
            ++cursor;
        const int kstarts(cursor);
        for (; cursor < length; ++cursor)
            if (b[cursor].isLetterOrNumber() || b[cursor] == _colon || b[cursor] == _hyphen || b[cursor] == _period)
                continue;
            else
                break;
        const int kends(cursor);
        if (b[cursor] == _space)
            ++cursor;
        if (b[cursor] == _comma)
            ref->citeidName = bibstr.mid(kstarts, kends - kstarts);
    }
    if (fields.isEmpty())
        return;
    while (true)
    {
        const int cd(_bib_field_delimiter.indexIn(b, length, cursor));
        if (cd < 1)
            break;

        const int fends(b[cd - 1] == _space ? cd - 2 : cd - 1);
        for (cursor = fends; cursor > 1; --cursor)
            if ((b[cursor] >= _lca && b[cursor] <= _lcz) || (b[cursor] >= _uca && b[cursor] <= _ucz))
                continue;
            else
                break;
        const QString* const fp(
            _ci_fields_index_of(fields, reinterpret_cast<const ushort*>(b + cursor + 1), fends - cursor));
        if (fp == nullptr)
        {
            cursor = cd + 2;
            continue;
        }
        const QString& field(*fp);

        const int vstarts(b[cd + 1] == _space ? cd + 2 : cd + 1);
        if (b[vstarts] != _open && field == QLatin1String("month"))
        {
            // Month macro
            for (cursor = vstarts; cursor < length; ++cursor)
                if (b[cursor].isLetterOrNumber() || b[cursor] == _space || b[cursor] == _tilde || b[cursor] == _pound ||
                    b[cursor] == _quote)
                    continue;
                else
                    break;
            if (b[cursor] == _comma && !ref->contains(field))
                ref->insert(field, bibstr.mid(vstarts, cursor - vstarts).trimmed());
            cursor = cd + 2;
            continue;
        }
        const int vends(_in_braces_ends(b, vstarts, length));
        if (vends > 0)
        {
            const int vs(b[vstarts + 1] == _space ? vstarts + 2 : vstarts + 1);
            const int vl(vends - vs + 1);
            if (vl > 0)
            {
                if (!ref->contains(field))
                    ref->insert(field, bibstr.mid(vs, vl));
                else if (field == QLatin1String("keywords"))
                    ref->insert(field, ref->value(field) + QLatin1Char(';') + bibstr.mid(vs, vl));
            }
            cursor = cd + 2;
            continue;
        }

        for (cursor = vstarts; cursor < length; ++cursor)
            if (!b[cursor].isLetterOrNumber())
                break;
        const int vnbends(cursor);
        if (b[cursor] == _space)
            ++cursor;
        if (b[cursor] == _comma)
        {
            const int vl(vnbends - vstarts);
            if (vl > 0)
            {
                if (!ref->contains(field))
                    ref->insert(field, bibstr.mid(vstarts, vl));
                else if (field == QLatin1String("keywords"))
                    ref->insert(field, ref->value(field) + QLatin1Char(';') + bibstr.mid(vstarts, vl));
            }
        }
        cursor = cd + 2;
    }
}

int coreBibParser::_in_braces_ends(const QChar* const b, const int p, const int length) const
{
    if (b[p] == _open)
        for (int i = p + 1, open_braces = 1; i < length; ++i)
        {
            if (b[i] < _open)
                continue;
            if (b[i] == _open)
                ++open_braces;
            else if (b[i] == _close)
                --open_braces;
            if (open_braces == 0)
                return (b[i - 1] == _space) ? i - 2 : i - 1;
        }
    else if (b[p] == _quote)
        for (int i = p + 1; i < length; ++i)
            if (b[i] == _quote && b[i + 1] == _comma)
                return (b[i - 1] == _space) ? i - 2 : i - 1;
    return 0;
}
