/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 *
 *   Improvements and modifications:
 *   July 2009 - Added <<author_all_abbreviated>>, (C) 2009 by Dayu Huang
 ***************************************************************************/
#include "idMaker.h"

#include "settings.h"


idMaker::idMaker(const QString& patternKey, QObject* parento) : QObject(parento), _pattern_key(patternKey)
{
    loadSettings();
    connect(settings::instance(), SIGNAL(newSettings()), this, SLOT(loadSettings()));
}


/** \page predefinedplaceholders Predefined Placeholders


  \section idplaceholders Cite and Document ID Placeholders


    - <tt><<author_all_abbreviated>></tt> Takes first three letters of the last
    word of all authors's last name in cite, and converts to lowercase.

    - <tt><<author_all_initials>></tt> Takes capitalized initials of all
    authors in cite.

    - <tt><<author_first>></tt> Takes first author last name.

    - <tt><<author_first_lowercase>></tt> Takes first author last name in
    lowercase.

    - <tt><<citeid>></tt> This placeholder is meant to be used <b>alone, and
    only for document IDs</b>. It takes the pattern defined for the cite ID. If
    the cite ID is modified manually, the document ID is synchronized
    automatically.

    - <tt><<journal_initials>></tt> Takes capitalized initials of journal name.

    - <tt><<pages_first>></tt> First page.

    - <tt><<ppages_first>></tt> First page, written as, e. g., 'p125'.

    - <tt><<title>></tt> Title. To truncate titles exceeding a maximum length
    <tt>l</tt> use <tt><<title_l>></tt>, where <tt>l</tt> stands for an integer
    value.

    - <tt><<title_underscored>></tt> Title with blanks set to underscores. To
    truncate title to <tt>l</tt> characters use
    <tt><<title_underscored_l>></tt>.

    - <tt><<title_first_word>></tt> First word in title, in lowercase.

    - <tt><<volume>></tt> Volume number.

    - <tt><<year_abbreviated>></tt> Last two digits from year.

    - <tt><<year_full>></tt> All digits from year.


    <b>Note:</b> If <tt>author</tt> is empty, <tt>editor</tt> will be
    considered instead. On conference proceedings or monographs this situation
    is usual. Similarly, if <tt>title</tt> is empty, <tt>booktitle</tt> is
    considered.

    <b>Note:</b> Only one placeholder of a given field, e. g.
    <tt><<author_first>></tt> or <tt><<author_all_initials>></tt>, should be
    used to compose the ID patterns. cb2Bib only performs one substitution per
    field placeholder.

    <b>Note:</b> cb2Bib performs a series of string manipulations, such as
    stripping diacritics and ligatures, aimed to provide ID values suitable for
    BibTeX keys and platform independent filenames. Currently only ASCII
    characters are considered.


  \section citeplaceholders Cite Command Placeholders

    - <tt><<citeid>></tt> The <tt>citeid</tt> placeholder replicates the
    pattern for each citation in the selected citation list. For example, the
    pattern <tt>\\citenum{<<citeid>>}</tt> expands to <tt>\\citenum{cid1}
    \\citenum{cid2} ... </tt>

    - <tt><<prefix|citeids|separator>></tt> The <tt>citeids</tt> placeholder
    replaces the selected citation list by prepending <tt>prefix</tt> and
    appending <tt>separator</tt> within the pattern. For example, the markdown
    pattern <tt>[<<\@|citeids|;>>]</tt> expands to <tt>[\@cid1; \@cid2;
    ...]</tt>, and the LaTeX pattern <tt>\\citeauthor{<<|citeids|,>>}</tt>
    expands to <tt>\\citeauthor{cid1, cid2, ...}</tt>.


    <b>Note:</b> For additional information on cite commands see
    \htmlonly
    <a href="https://en.wikibooks.org/wiki/LaTeX/Bibliography_Management" target="_blank">LaTeX Bibliography
  Management</a>
    \endhtmlonly
    and
    \htmlonly
    <a href="https://pandoc.org/MANUAL.html#citations" target="_blank">Pandoc User's Guide</a>.
    \endhtmlonly

*/
QString idMaker::makeID(const bibReference& reference)
{
    if (_id_pattern.isEmpty())
        return QString();
    if (_id_pattern.contains(QLatin1String("<<citeid>>")))
        return reference.citeidName;

    // Initialize fields
    _author = reference.anyAuthor();
    _journal = reference.value(QLatin1String("journal"));
    _pages = reference.value(QLatin1String("pages"));
    _title = reference.anyTitle();
    _volume = reference.value(QLatin1String("volume"));
    _year = reference.value(QLatin1String("year"));

    // Set cite ID
    QString id(_id_pattern);
    if (_id_pattern.contains(QLatin1String("<<author_first>>")))
        make_author_first(&id);
    else if (_id_pattern.contains(QLatin1String("<<author_first_lowercase>>")))
        make_author_first_lowercase(&id);
    else if (_id_pattern.contains(QLatin1String("<<author_all_abbreviated>>")))
        make_author_all_abbreviated(&id);
    else if (_id_pattern.contains(QLatin1String("<<author_all_initials>>")))
        make_author_all_initials(&id);

    if (_id_pattern.contains(QLatin1String("<<journal_initials>>")))
        make_journal_initials(&id);

    if (_id_pattern.contains(QLatin1String("<<pages_first>>")))
        make_pages_first(&id);
    else if (_id_pattern.contains(QLatin1String("<<ppages_first>>")))
        make_ppages_first(&id);

    if (!_title_pattern.isEmpty())
        if (_id_pattern.contains(_title_pattern))
            make_title(&id);

    if (_id_pattern.contains(QLatin1String("<<title_first_word>>")))
        make_title_first_word(&id);

    if (_id_pattern.contains(QLatin1String("<<volume>>")))
        make_volume(&id);

    if (_id_pattern.contains(QLatin1String("<<year_abbreviated>>")))
        make_year_abbreviated(&id);
    else if (_id_pattern.contains(QLatin1String("<<year_full>>")))
        make_year_full(&id);

    return id;
}

void idMaker::make_author_first(QString* id)
{
    QRegExp rx("([-'\\s\\w]+)(?:\\sand|$)");
    rx.setMinimal(true);
    rx.indexIn(_author);
    _author = rx.cap(1);
    if (_author.contains(c2bUtils::nonAsciiLetter))
        _author = c2bUtils::toAscii(_author, c2bUtils::Cleanup);
    id->replace(QLatin1String("<<author_first>>"), _author);
}

void idMaker::make_author_first_lowercase(QString* id)
{
    QRegExp rx("([-'\\s\\w]+)(?:\\sand|$)");
    rx.setMinimal(true);
    rx.indexIn(_author);
    _author = rx.cap(1).toLower();
    if (_author.contains(c2bUtils::nonAsciiLetter))
        _author = c2bUtils::toAscii(_author, c2bUtils::Cleanup);
    id->replace(QLatin1String("<<author_first_lowercase>>"), _author);
}

void idMaker::make_author_all_abbreviated(QString* id)
{
    // If there is less than 3 letters in their last name's last word,
    // then use all the letters in the last name's last word
    QString temp_author;
    QRegExp rx("([-'\\w]{1,3})(?:[-'\\w]*)(?:\\sand|$)");
    rx.setMinimal(true);
    rx.indexIn(_author);
    int pos(0);
    while ((pos = rx.indexIn(_author, pos)) != -1)
    {
        temp_author += rx.cap(1);
        pos += rx.matchedLength();
    }
    _author = temp_author.toLower();
    if (_author.contains(c2bUtils::nonAsciiLetter))
        _author = c2bUtils::toAscii(_author, c2bUtils::Cleanup);
    id->replace(QLatin1String("<<author_all_abbreviated>>"), _author);
}

void idMaker::make_author_all_initials(QString* id)
{
    _author.remove(QRegExp("\\b\\w\\b"));
    _author.remove(" and ");
    if (_author.contains(c2bUtils::nonAsciiLetter))
        _author = c2bUtils::toAscii(_author, c2bUtils::Cleanup);
    _author.remove(QRegExp("[a-z]"));
    id->replace(QLatin1String("<<author_all_initials>>"), _author);
}

void idMaker::make_journal_initials(QString* id)
{
    _journal.remove(QRegExp("[^A-Z]"));
    id->replace(QLatin1String("<<journal_initials>>"), _journal);
}

void idMaker::make_pages_first(QString* id)
{
    _pages = c2bUtils::firstPage(_pages);
    id->replace(QLatin1String("<<pages_first>>"), _pages);
}

void idMaker::make_ppages_first(QString* id)
{
    _pages = c2bUtils::firstPage(_pages);
    if (!_pages.isEmpty())
        if (_pages.at(0).isDigit())
            _pages = 'p' + _pages;
    id->replace(QLatin1String("<<ppages_first>>"), _pages);
}

void idMaker::make_title(QString* id)
{
    if (_title.contains(c2bUtils::nonAsciiLetter))
        _title = c2bUtils::toAscii(_title, c2bUtils::FromBibTeX);
    _title = _title.left(_title_max_length).trimmed(); // Avoid possible trailing blank
    if (_is_title_underscored)
        _title.replace(QLatin1Char(' '), QLatin1Char('_'));
    id->replace(_title_pattern, _title);
}

void idMaker::make_title_first_word(QString* id)
{
    if (_title.contains(c2bUtils::nonAsciiLetter))
        _title = c2bUtils::toAscii(_title, c2bUtils::FromBibTeX);
    const QStringList ws(_title.toLower().split(c2bUtils::nonAsciiLetter, QString::SkipEmptyParts));
    _title.resize(0);
    for (int w = 0; w < ws.count(); ++w)
        if (ws.at(w).length() > 2 && ws.at(w) != QLatin1String("are") && ws.at(w) != QLatin1String("the"))
        {
            _title = ws.at(w);
            break;
        }
    id->replace(QLatin1String("<<title_first_word>>"), _title);
}

void idMaker::make_volume(QString* id)
{
    _volume.remove(' ');
    id->replace(QLatin1String("<<volume>>"), _volume);
}

void idMaker::make_year_abbreviated(QString* id)
{
    _year = _year.right(2);
    id->replace(QLatin1String("<<year_abbreviated>>"), _year);
}

void idMaker::make_year_full(QString* id)
{
    id->replace(QLatin1String("<<year_full>>"), _year);
}

void idMaker::loadSettings()
{
    _id_pattern = settings::instance()->value(_pattern_key).toString();
    QRegExp title_pattern("(<<title(?:_underscored)?(?:_\\d+)?>>)");
    if (title_pattern.indexIn(_id_pattern) > -1)
    {
        _title_pattern = title_pattern.cap(1);
        _title_pattern.remove(QRegExp("\\D"));
        _title_max_length = _title_pattern.toInt();
        if (_title_max_length == 0)
            _title_max_length = -1;
        _title_pattern = title_pattern.cap(1);
        _is_title_underscored = _title_pattern.contains(QRegExp("_underscored(?:_\\d+)?>>"));
    }
    else
        _title_pattern.clear();
}
