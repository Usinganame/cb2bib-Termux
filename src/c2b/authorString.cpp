/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "authorString.h"


namespace author
{

unifier::unifier()
    : name("(?:\\w[-'\\w]{1,})"),
      initials("(?:\\s*-{0,1}\\b\\w\\b\\.{0,1}){1,3}"),
      double_initials("(Al|Ch|Kh|Md|Th|Xh|Ya|Yu|Zs)"),
      prefixes("(da|de|dal|del|der|di|do|du|dos|el|la|le|lo|van|vande|von|zur)"),
      reversed_romance_name("(?:\\w[-'\\w]{1,})\\s+(?:\\w[-'\\w]{1,}),\\s*(?:\\w[-'\\w]{1,}|" + initials + ')'),

      reversed_name_rx('^' + name + ','),
      // Cases 'n1 n2, n3', 'n1 n2, n3 and n4 n5, n6', 'n1 n2, n3 and n4, n5 n6' are necessarily reverse order
      reversed_romance_name_rx("^(?:" + reversed_romance_name + '|' + reversed_romance_name + " and " +
                               reversed_romance_name + '|' + reversed_romance_name +
                               " and (?:\\w[-'\\w]{1,}),\\s*(?:\\w[-'\\w]{1,}|\\w[-'\\w]{1,} \\w[-'\\w]{1,}|" + initials +
                               "))$"),

      unifier_rx1("(\\w\\w)\\si\\s(\\w\\w)(?!d\\b)", Qt::CaseSensitive),
      unifier_rx2("\\b" + prefixes + "\\s(?!(?:,|and\\b))", Qt::CaseInsensitive),
      unifier_rx3("\\b" + double_initials + "\\.", Qt::CaseInsensitive),
      unifier_rx4("\\b(\\w[-'\\w]{2,})\\W+Jr\\.", Qt::CaseInsensitive),
      unifier_rx5("\\b(\\w[-'\\w]{2,})\\W+Jr\\b", Qt::CaseInsensitive),
      unifier_rx6("(\\w),{0,1}\\s(II|III|IV)\\b", Qt::CaseSensitive),
      unifier_rx7("([^\\w-])[a-z](?=[^\\w'])"),

      simplify_string_rx1(QString("%1(?=\\w)").arg(QChar(8217))),
      simplify_string_rx2("\'(?!\\w)"),
      simplify_string_rx3("\\d\\d+"),
      simplify_string_rx4("\\d(?=\\s\\w\\w)"),
      simplify_string_rx5("\\d[\\*,;][a-z]\\b"),
      simplify_string_rx6("\\d"),
      simplify_string_rx7("[^-',;:\\|/&\\.\\s\\w]") {}


QString& unifier::unifyNames(QString& author) const
{
    // Composite Names temporary unified
    author.replace(unifier_rx1, "\\1+i+\\2");
    author.replace(unifier_rx2, "\\1+");
    author.replace("Da+", "Da ", Qt::CaseSensitive);
    author.replace(unifier_rx3, "\\1+ ");
    if (author.contains("Jr", Qt::CaseInsensitive))
    {
        // Remove period and first comma if there
        author.replace(unifier_rx4, "\\1+JR");
        author.replace(unifier_rx5, "\\1+JR");
    }
    if (author.contains('I', Qt::CaseSensitive))
        author.replace(unifier_rx6, "\\1+\\2");
    author.replace('+', '_');
    author.replace(unifier_rx7, "\\1 "); // Cleaning affiliation 'superscripts'. Avoid cleaning 'M.-m. Lin'
    return author;
}

QString& unifier::simplifyString(QString& author, const bool full) const
{
    if (full) // Characters | and : are used for the encoder
    {
        author.replace('|', ' ');
        author.replace(':', ' ');
    }
    author.replace(simplify_string_rx1, "\'"); // Normalize apostrophe
    author.remove(simplify_string_rx2);        // Remove spurious apostrophes
    author.replace(simplify_string_rx3, "/");  // Break dates, addresses, etc, but remove from author's foot notes.
    author.replace(simplify_string_rx4, ",");  // Help no-separator designs, and also break zip codes.
    author.replace(simplify_string_rx5, " ");
    author.remove(
        simplify_string_rx6); // Better remove if no conflict. It will help to not confuse with chemical formula.
    author.replace(simplify_string_rx7, " ");
    author = c2bUtils::simplifyString(author);
    return author;
}

QString unifier::fromMedline(const QString& author) const
{
    // Preprocess Author from Medline 'AAAAAAA BB' to Aaaaaaa, BB'
    // which can be unambiguously translated to 'B. B. Aaaaaaa'
    // Takes care of cb2Bib included prefixes and suffixes
    // FAU  -  Foa, Edna B
    // AU   -  Foa EB
    // FAU  -  Steketee, Gail S
    // AU   -  Steketee GS

    QString FullN(author.simplified());
    FullN.replace(QRegExp("\\b" + prefixes + "\\s", Qt::CaseInsensitive), "\\1+");
    FullN.replace('+', '_');
    QStringList parts;
    QString LastN;
    if (FullN.contains(',')) // Some FAU are 'Last1 Last2, First'
    {
        parts = FullN.split(',', QString::SkipEmptyParts);
        if (parts.count() > 1)
            LastN = parts.takeFirst();
    }
    else
    {
        parts = FullN.split(' ', QString::SkipEmptyParts);
        if (parts.count() > 1)
            LastN = parts.takeFirst();
    }
    FullN = parts.join(" ");
    parts = FullN.split(' ', QString::SkipEmptyParts);
    if (!LastN.isEmpty())
        if (c2bUtils::isUpperCaseString(LastN))
        {
            LastN = LastN.toLower();
            LastN[0] = LastN.at(0).toUpper();
            int ii(LastN.indexOf(QRegExp("[-']")));
            if (ii++ > 0)
                LastN[ii] = LastN.at(ii).toUpper();
        }
    QString FirstN;
    for (int i = 0; i < parts.count(); ++i)
        FirstN += ' ' + parts.at(i);
    QString isSuffix;
    if (parts.count() > 0)
        isSuffix = parts.last();
    if (isSuffix.contains(QRegExp("\\b(?:2nd|3rd|Jr|II|III)\\b")))
    {
        isSuffix.replace(QRegExp("\\b2nd\\b"), "II");
        isSuffix.replace(QRegExp("\\b3rd\\b"), "III");
        LastN += ' ' + isSuffix;
        FirstN.remove(QRegExp("\\b(?:2nd|3rd|Jr|II|III)\\b"));
    }
    LastN.replace(QRegExp(prefixes + '_', Qt::CaseInsensitive), "\\1 ");
    FullN = LastN + ',' + FirstN;
    return FullN;
}


/**
    Implementation of author field extraction
    P. Constans. A Simple Extraction Procedure for Bibliographical Author Field.
    arXiv:0902.0755, 2009.
*/
void encoder::encode(const QString& raw)
{
    clear();
    QString str(raw);
    aunifier.unifyNames(str);
    int position(0);
    int length(0);
    for (int i = 0; i < str.length(); ++i)
    {
        const QChar& si = str[i];
        if (si.isLetter())
            ++length;
        else if (si == '_')
            ++length;
        else if (si == '-')
            ++length;
        else if (si == '\'')
            ++length;
        else
        {
            if (length > 0)
                fragments.append(str.mid(position, length));
            position = i + 1;
            length = 0;
            if (si != ' ')
                fragments.append(str.at(i));
        }
    }
    if (length > 0)
        fragments.append(str.mid(position, length));
    for (int i = 0; i < fragments.count(); ++i)
    {
        const QString& w = fragments.at(i);
        if (isSeparator(w))
            code += '&';
        else if (isAdparticle(w))
            code += 'a';
        else if (isInitial(w))
            code += 'I';
        else if (isPlainWord(w))
            code += 'w';
        else if (isName(w))
        {
            if (isCapitalName(w))
                code += 'N';
            else
                code += 'n';
        }
        else if (w.at(0) == '.')
            code += 'p';
        else if (w.at(0) == ',')
            code += ',';
        else if (w.at(0) == ';')
            code += ';';
        else if (w.at(0) == ':')
            code += ':';
        else if (w.at(0) == '|')
            code += 'L';
        else
            code += 'o';
    }
    scapePattern("aL+[nN]{1,2}");
    scapePattern("a[nNw]&L+[nN]{1,2}"); // in Linear and / Sublinear Time
    scapePattern(":L+[InN]{1,2}");      // ... Structure Classification: / A Survey
    scapePattern("[nN]*&L[nN]L");       // Not an & for author
}

QString encoder::decoded(const int position, const int length) const
{
    if (position < 0)
        return QString();
    if (length < 1 || position + length > fragments.count())
        return QString();
    QString d(fragments.at(position));
    for (int i = 1; i < length; ++i)
        d += ' ' + fragments.at(position + i);
    // Above extra spaces are fine, except in these cases
    d.replace(" . -", ".-");
    d.replace(" ,", ",");
    return d;
}

bool encoder::isPlainWord(const QString& w)
{
    if (w.length() > 1)
    {
        if (w.contains('_') || w.contains('-'))
            return c2bUtils::isLowerCaseString(w);
        if (w.at(0).isLetter())
            if (w.at(0).category() == QChar::Letter_Lowercase)
                return true;
    }
    return false;
}

bool encoder::isInitial(const QString& w)
{
    if (w.length() == 1)
        if (w.at(0).isLetter())
            return w.at(0).isUpper();
    if (w.length() == 2)
        if (w.at(0) == '-')
            if (w.at(1).isLetter())
                return true; // Chinese composite might(?) be lower
    return false;
}

bool encoder::isName(const QString& w)
{
    if (w.length() < 2)
        return false;
    if (w.at(0).isUpper())
        return true;
    if (w.contains('_'))
        return hasUpper(w);
    return false;
}

bool encoder::isAdparticle(const QString& w)
{
    const int ws(w.size());
    if (ws < 2)
        return false;
    if (ws > 6)
        return false;
    const QByteArray ba(w.toLatin1());
    const char* s = ba.data();
    const int ss(ws * int(sizeof(char)));
    if (ws == 2)
    {
        if (memcmp("of", s, ss) == 0)
            return true;
        if (memcmp("on", s, ss) == 0)
            return true;
        if (memcmp("to", s, ss) == 0)
            return true;
        if (memcmp("in", s, ss) == 0)
            return true;
        if (memcmp("as", s, ss) == 0)
            return true;
        if (memcmp("vs", s, ss) == 0)
            return true;
        if (memcmp("at", s, ss) == 0)
            return true;
        if (memcmp("is", s, ss) == 0)
            return true;
        if (memcmp("an", s, ss) == 0)
            return true;
    }
    if (ws == 3)
    {
        if (memcmp("for", s, ss) == 0)
            return true;
        if (memcmp("but", s, ss) == 0)
            return true;
        if (memcmp("are", s, ss) == 0)
            return true;
        if (memcmp("its", s, ss) == 0)
            return true;
        if (memcmp("the", s, ss) == 0)
            return true;
    }
    if (ws == 4)
    {
        if (memcmp("from", s, ss) == 0)
            return true;
        if (memcmp("with", s, ss) == 0)
            return true;
        if (memcmp("into", s, ss) == 0)
            return true;
    }
    if (ws == 6)
    {
        if (memcmp("within", s, ss) == 0)
            return true;
    }
    return false;
}

} // namespace author


/** \page authorproc Processing of Author Names

    cb2Bib automatically processes the author names string. It uses a set of
    heuristic rules. First, the authors separator is identified. And second, it
    is decided whether or not author names are in natural or reverse order, or
    in the 'Abcd, E., F. Ghij, ...' mixed order.

*/
authorString::authorString() : _full_form(false) {}


/** \page authorproc

   Cleanup author string:

   - Escape BibTeX to Unicode

   - Remove digits from authors string

   - Remove any character except <tt>-',;&\\.\\s\\w</tt>

   - Simplify white spaces

   - Consider composing prefixes <tt>(da|de|dal|del|der|di|do|du|dos|el|la|le|lo|van|vande|von|zur)</tt>

   - Consider composing suffixes <tt>(II|III|IV|Jr)</tt>

   - Some publishers use superscripts to refer to multiple author affiliations.
   Text clipboard copying loses superscript formatting. Author strings are
   clean from 'orphan' lowcase, single letters in a preprocessing step.
   Everything following the pattern <b>[a-z]</b> is removed. Fortunately,
   abbreviated initials are most normally input as uppercase letters, thus
   permitting a correct superscript clean up. \n <em>Caution:</em> Lowcase,
   single, a to z letters are removed from author's string.\n <em>Caution:</em>
   Supperscripts <b>will be added to author Last Name</b> if no separation is
   provided. Users should care about it and correct these cases.


   Rules to identify separators:
   - Contains comma and semicolon -> ';'
   - Contains pattern <tt>'^Abcd, E.-F.,'</tt> -> ','
   - Contains pattern <tt>'^Abcd,'</tt> -> 'and'
   - Contains comma -> ','
   - Contains semicolon -> ';'
   - Any other -> 'and'

*/
QString authorString::toBibTeX(const QString& author, bool full_form)
{
    _full_form = full_form;
    _author_string = author;
    // BibTeX braces interfere with authorString, remove them even though some BibTeX meaning might be lost
    _author_string.remove('{');
    _author_string.remove('}');
    au.simplifyString(_author_string, true);
    au.unifyNames(_author_string);
    const bool has_comma(_author_string.contains(','));
    const bool has_semicolon(_author_string.contains(';'));
    const bool has_ands(_author_string.count(" and ") > 1);
    const bool is_first_reversed(_author_string.contains(au.reversed_name_rx));
    const bool is_special_case(_author_string.contains(au.reversed_romance_name_rx));
    bool is_string_reversed((has_comma && has_semicolon) || (has_comma && has_ands) || is_special_case);

    QString separator;
    if (is_special_case)
        separator = " and ";
    else if (has_comma && has_semicolon)
        separator = ';'; // Multiple Authors, separated by semicolon, reversed naming
    else if (has_comma)
    {
        if (is_first_reversed)
        {
            if (_author_string.contains(QRegExp('^' + au.name + ",(?:\\s*-{0,1}\\b\\w\\b\\.){1,3},\\s*" + au.name)))
            {
                _author_string.replace(QRegExp("\\bJr.", Qt::CaseSensitive), "Jr");
                _author_string.replace(".,", ".;");
                // Reversed, comma separated 'Abrahamsson, A.-L., Springett, J., Karlsson, L., Ottosson, T.'
                separator = ';';
                is_string_reversed = true;
            }
            else if (_author_string.contains(QRegExp('^' + au.name + ',' + au.initials + ',')))
            {
                _author_string.replace(QRegExp("^([-'\\w]+),"), "\\1 ");
                separator = ','; // Mixed naming 'Smith, J.-L., R. Jones, and K. Gibbons'
            }
            else
                separator = " and "; // Reversed naming
        }
        else if (has_ands)
            separator = " and ";
        else // Natural naming
            separator = ',';
    }
    else if (has_semicolon)
        separator = ';'; // Multiple Authors, separated by semicolon
    else
        separator = " and ";
    c2bUtils::debug(QObject::tr("Separator: |%1|").arg(separator));
    c2bUtils::debug("1--|" + _author_string + '|');
    _author_string.replace(QRegExp("\\band\\b", Qt::CaseInsensitive), separator);
    _author_string.replace(QRegExp("\\s&\\s", Qt::CaseInsensitive), separator);
    c2bUtils::debug("2--|" + _author_string + '|');
    _author_string.remove(QRegExp("[^\\w\\.]+$")); // Removing of duplicate commas and semicolons
    _author_string.replace(QRegExp(",\\s*"), ",");
    c2bUtils::debug("3--|" + _author_string + '|');
    _author_string.replace(QRegExp(",+"), ",");
    _author_string.replace(QRegExp(";\\s*"), ";");
    _author_string.replace(QRegExp(";+"), ";");
    c2bUtils::debug("4--|" + _author_string + '|');
    const bool are_authors_in_uppercase(containUpperCaseLetter(_author_string) &&
                                        !containLowerCaseLetter(_author_string));
    if (are_authors_in_uppercase)
        c2bUtils::debug("Input Authors in Uppercase");
    QStringList authors;
    if (separator == " and ")
        authors = _author_string.split(QRegExp("\\band\\b"));
    else
        authors = _author_string.split(separator);

    // Setting author ordering
    const QString first_author(authors.first().trimmed());
    bool is_current_reversed(is_string_reversed || is_first_reversed || isReverseOrder(first_author));
    const QString last_author(authors.last().trimmed());
    const bool is_last_reversed(is_string_reversed || last_author.contains(au.reversed_name_rx) ||
                                isReverseOrder(last_author));
    const bool is_string_mixed(is_current_reversed && !is_last_reversed);
    if (is_string_mixed) // Mixed naming 'Smith, J., R. Jones'
        c2bUtils::debug("Mixed order");

    // Process each author name
    for (int ai = 0; ai < authors.count(); ++ai)
    {
        QString author_i(authors.at(ai));
        c2bUtils::debug(author_i);
        author_i.replace(QRegExp("\\.{0,1}\\s{0,1}-"), "-"); // Abbreviated cases, eg M.-H. Something
        author_i.replace(QRegExp("[^-'\\w,]"), " ");         // Only these characters compose a name; keep commas
        author_i = c2bUtils::simplifyString(author_i);

        // Split author name
        QStringList fore_name_parts;
        QString last_name;
        if (is_current_reversed)
        {
            const QStringList parts(author_i.split(',', QString::SkipEmptyParts));
            const int nparts(parts.count());
            if (nparts == 2)
            {
                QStringList p(parts.first().split(' ', QString::SkipEmptyParts));
                if (p.count() > 0)
                    last_name = p.takeLast();
                fore_name_parts = parts.last().split(' ', QString::SkipEmptyParts) + p;
            }
            else if (nparts == 3)
            {
                QStringList p(parts.first().split(' ', QString::SkipEmptyParts));
                if (p.count() > 0)
                    last_name = p.takeLast();
                fore_name_parts = parts.at(1).split(' ', QString::SkipEmptyParts) + p;
                if (parts.last().contains(QRegExp("^(?:Jr|II|III|IV)$"))) // If otherwise, ignore it
                    last_name += '_' + parts.last();
            }
            else
            {
                fore_name_parts = author_i.split(' ', QString::SkipEmptyParts);
                if (fore_name_parts.count() > 0)
                    last_name = fore_name_parts.takeFirst();
            }
            c2bUtils::debug("Reversed order");
        }
        else
        {
            fore_name_parts = author_i.split(' ', QString::SkipEmptyParts);
            if (fore_name_parts.count() > 0)
                last_name = fore_name_parts.takeLast();
            c2bUtils::debug("Natural order");
        }

        // Process first and middle names
        QString author_name;
        for (int i = 0; i < fore_name_parts.count(); ++i)
        {
            c2bUtils::debug("First and Midle: " + fore_name_parts.at(i));
            if (fore_name_parts.at(i).contains('-')) // Composite names
            {
                const QStringList fnpi(fore_name_parts.at(i).split('-'));
                if (fnpi.count() > 1)
                {
                    author_name += processFirstMiddle(fnpi.at(0)) + '-';
                    author_name += processFirstMiddle(fnpi.at(1)) + ' '; // Shouldn't be more than 2 parts...
                }
            }
            else // Regular names
            {
                QString fore_name(fore_name_parts.at(i));
                const int fore_length(fore_name.length());
                const bool is_uppercase(!containLowerCaseLetter(fore_name));
                if (fore_name_parts.count() == 1 && fore_length > 1 &&
                    !fore_name.contains(QRegExp("\\b" + au.double_initials + '_', Qt::CaseInsensitive)) &&
                    !are_authors_in_uppercase && is_uppercase)
                {
                    // Cases 'Last, FST': Always abbreviated, no call to processFirstMiddle
                    for (int l = 0; l < fore_length; ++l)
                        author_name += fore_name[l] + ". ";
                }
                else if (fore_name_parts.count() == 2 && fore_length > 1 && fore_length < 3 && is_current_reversed &&
                         !are_authors_in_uppercase && is_uppercase)
                {
                    // Cases 'Last1 Last2, FST': Always abbreviated, no call to processFirstMiddle
                    for (int l = 0; l < fore_length; ++l)
                        author_name += fore_name[l] + ". ";
                }
                else if (i == 1 && fore_name_parts.count() == 2 && fore_length > 1 && fore_length < 3 &&
                         !is_current_reversed && !are_authors_in_uppercase && is_uppercase)
                {
                    // Cases 'Fore IJ Last': Process initials
                    for (int l = 0; l < fore_length; ++l)
                        author_name += fore_name[l] + ". ";
                }
                else
                    author_name += processFirstMiddle(fore_name) + ' ';
            }
        }
        // Add last name
        author_name += capitalize(last_name);
        authors[ai] = author_name;
        c2bUtils::debug(author_name);
        if (is_string_mixed) // Mixed naming 'Smith, J., R. Jones'
            is_current_reversed = false;
    }

    authors.removeAll(QString());
    _author_string = authors.join(" and ");
    // Restore Composite Names white spaces
    _author_string.replace("_i_", " i ");
    _author_string.replace(QRegExp("_II\\b", Qt::CaseInsensitive), " II"); // Suffix can be lower case here
    _author_string.replace(QRegExp("_III\\b", Qt::CaseInsensitive), " III");
    _author_string.replace(QRegExp("_IV\\b", Qt::CaseInsensitive), " IV");
    _author_string.replace(QRegExp("_JR\\b", Qt::CaseInsensitive), " Jr");
    _author_string.replace(QRegExp(au.prefixes + '_', Qt::CaseInsensitive), "\\1 ");
    _author_string.replace(QRegExp("\\b" + au.double_initials + '_', Qt::CaseInsensitive), "\\1.");
    _author_string = c2bUtils::simplifyString(_author_string);

    return _author_string;
}

QString authorString::processFirstMiddle(const QString& first_middle) const
{
    // Process First and Middle parts
    // Abbreviates if required
    // Takes care of abbreviation periods
    QString proc_fm;
    if (_full_form)
    {
        if (first_middle.length() > 1)
            proc_fm = capitalize(first_middle);
        else
            proc_fm = first_middle + '.';
    }
    else
    {
        if (first_middle.contains('_')) // Composite names should not be abbreviated
        {
            proc_fm = capitalize(first_middle);
            if (first_middle.length() - first_middle.indexOf('_') == 2)
                proc_fm += '.';
        }
        else if (first_middle.length() > 0)
            proc_fm = first_middle.at(0) + '.';
    }
    return proc_fm;
}

QString authorString::capitalize(const QString& name) const
{
    // Capitalizes author's name
    if (name.isEmpty())
        return QString();
    QString proc_name(name);
    int ii(0);
    const int prefixes(proc_name.count(QRegExp(au.prefixes + "_(?!(?:Jr|II|III|IV)\\b)", Qt::CaseInsensitive)));
    for (int p = 0; p < prefixes; ++p)
    {
        const int iin(proc_name.indexOf('_', ii));
        if (c2bUtils::isUpperCaseString(proc_name, ii, iin))
            for (int i = 0; i < iin; ++i)
                proc_name[i] = proc_name.at(i).toLower();
        ii = std::min(iin + 1, proc_name.length() - 1);
    }
    if (c2bUtils::isUpperCaseString(proc_name, ii))
    {
        proc_name[ii] = proc_name.at(ii).toUpper();
        for (int i = ++ii; i < proc_name.length(); ++i)
            proc_name[i] = proc_name.at(i).toLower();
        ii = proc_name.indexOf(QRegExp("[\\s-']")); // As before, assume just one part
        if (ii++ > 0)
            if (ii < proc_name.length())
                proc_name[ii] = proc_name.at(ii).toUpper();
        if (proc_name.startsWith("Mc"))
            if (proc_name.length() > 4)
                proc_name[2] = proc_name.at(2).toUpper();
    }
    return proc_name;
}

/** \page authorproc

    Rules to identify ordering:
    - Contains comma and semicolon -> Reverse
    - Pattern <tt>'^Abcd,'</tt> -> Reverse
    - Pattern <tt>'^Abcd EF Ghi'</tt> -> Natural
    - Pattern <tt>'^Abcd EF'</tt> -> Reverse
    - Pattern <tt>'^Abcd E.F.'</tt> -> Reverse
    - Any other pattern -> Natural

*/
bool authorString::isReverseOrder(const QString& author) const
{
    // Returns true if Author Name is in reversed order as "Him DF, Her SR, "
    // ISI doesn't contain point - return for safety
    // Consider "Him DF Last"
    const QString author_line(author.simplified());
    QRegExp rRevNISI("^([-'\\w]+) ((\\w\\.\\s*)+)$");
    rRevNISI.setMinimal(false);
    if (rRevNISI.indexIn(author_line) > -1)
    {
        const QString Last(rRevNISI.cap(3));
        if (Last != "and")
            return true;
    }
    if (author_line.contains('.'))
        return false;
    rRevNISI = QRegExp("^([-'\\w]+) ([-'\\w]+) ([-'\\w]+)");
    rRevNISI.setMinimal(false);
    if (rRevNISI.indexIn(author_line) > -1)
    {
        const QString Last(rRevNISI.cap(3));
        if (Last != "and")
            return false;
    }
    rRevNISI = QRegExp("^([-'\\w]+) ([-\\w]{1,3})$"); // Consider only 1 to 3 initials
    rRevNISI.setMinimal(false);
    if (rRevNISI.indexIn(author_line) > -1)
    {
        const QString Last(rRevNISI.cap(1));
        const QString First(rRevNISI.cap(2));
        c2bUtils::debug(QObject::tr("ISI:  |%1| |%2|").arg(Last, First));
        if (containLowerCaseLetter(First))
            return false;
        if (!containLowerCaseLetter(Last))
            return false;
        return true;
    }
    return false;
}

bool authorString::containLowerCaseLetter(const QString& author) const
{
    QString author_line(author);
    author_line.remove(QRegExp("\\band\\b"));                                 // Remove possible 'and' separator
    author_line.remove(QRegExp(au.prefixes + '_', Qt::CaseInsensitive));      // Remove possible prefixes
    author_line.remove(QRegExp(au.double_initials + '_', Qt::CaseSensitive)); // Remove possible two-letter initials
    for (int i = 0; i < author_line.length(); i++)
    {
        if (author_line.at(i).isLetter())
            if (author_line.at(i).category() == QChar::Letter_Lowercase)
                return true;
    }
    return false;
}

bool authorString::containUpperCaseLetter(const QString& author)
{
    for (int i = 0; i < author.length(); i++)
    {
        if (author.at(i).isLetter())
            if (author.at(i).category() == QChar::Letter_Uppercase)
                return true;
    }
    return false;
}
