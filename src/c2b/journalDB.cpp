/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "journalDB.h"

#include "cb2bib_utilities.h"

#include <QFile>
#include <QObject>
#include <QTextStream>


journalDB::journalDB(const QString& dbfile)
{
    if (dbfile.isEmpty())
    {
        c2bUtils::warn(QObject::tr("No journal file especified"));
        return;
    }
    _nitems = 0;
    QFile file(dbfile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        c2bUtils::warn(QObject::tr("Could not open journal file %1 for reading").arg(dbfile));
        return;
    }
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
            c2bUtils::warn(QObject::tr("Syntax error in journal file at line %1").arg(line_number));
            continue;
        }
        const QStringList spAbbreviated(spLine.at(1).split('=', QString::SkipEmptyParts));
        const int na(spAbbreviated.count());
        if (na < 1 || na > 2)
        {
            c2bUtils::warn(QObject::tr("Syntax error in journal file at line %1").arg(line_number));
            continue;
        }
        const QStringList spExtended(spLine.at(2).split('=', QString::SkipEmptyParts));
        const int ne(spExtended.count());
        if (ne < 1 || ne > 2)
        {
            c2bUtils::warn(QObject::tr("Syntax error in journal file at line %1").arg(line_number));
            continue;
        }
        for (int e = 0, c = 0; e < ne; ++e)
            for (int a = 0; a < na; ++a)
            {
                _nitems++;
                JCode += (c++ == 0) ? spLine.at(0).toLower() : QString();
                JAbbrev += spAbbreviated.at(a);
                JExtended += spExtended.at(e);
            }
    }
    file.close();
    JAbbrev_simp.resize(_nitems);
    JExtended_simp.resize(_nitems);
    for (int i = 0; i < _nitems; ++i)
    {
        JAbbrev_simp[i] = JAbbrev.at(i).toLower();
        JAbbrev_simp[i].remove(c2bUtils::nonLetter);
        JExtended_simp[i] = JExtended.at(i).toLower();
        JExtended_simp[i].remove(c2bUtils::nonLetter);
    }
}


/** \page journalproc Processing of Journal Names

  cb2Bib processes journal names according to its editable database, stored at
  <tt>abbreviations.txt</tt>. This file contains a list of journal names
  equivalences: a capital-letter acronym, the abbreviated form, and the title
  of the journal, all three on one single line.

  The <tt>abbreviations.txt</tt> file has the following structure:
\verbatim
JA|J. Abbrev.|Journal of Abbreviations
AN|Am. Nat.=Amer. Naturalist|American Naturalist=The American Naturalist
\endverbatim

  The first field, the capital-letter acronym, is a user-defined shorthand to
  access a journal title by typing it at the extraction panel.

  The second field is the abbreviated form of the journal. To adapt to multiple
  abbreviations in use, cb2Bib allows one alternate version of the
  abbreviation, indicated with an equal sign <tt>=</tt>. In the above example,
  the ISO 4 abbreviation 'Am. Nat.' is the primary one and 'Amer. Naturalist'
  is the alternate one.

  Finally, the third field is the full title of the journal. As for the
  abbreviations, the full title also admits one alternate form.

  Abbreviated and full title alternates serve two purposes: journal recognition
  and citation styling. The former is performed internally by cb2Bib as part of
  a bibliographic reference extraction, and the latter is accomplished in the
  embedded BibTeX editor by replacing back and forth abbreviated-full forms, in
  order to set journals in accordance to the guidelines of a particular
  publication.

  <p>&nbsp;</p>

  Journal names processing is performed whenever a string is recognized as
  'journal', and, additionally, when pressing <tt>Intro Key</tt> at the journal
  edit line.

  <p>&nbsp;</p>

  - Retrieves Journal name in <b>abbreviated form</b> if found.

  - If Journal name is not found in the database, returns input Journal name.

  - Search is case insensitive.

  - **Warning:** Journal codes can be duplicated. If duplicated, returns
    input Journal name.

  <p>&nbsp;</p>

  - Retrieves Journal name in <b>full form</b> if found.

  - If Journal name is not found in the database, returns input Journal name.

  - Search is case insensitive.

  - **Warning:** Journal codes can be duplicated. If duplicated, returns
    input Journal name.

  <p>&nbsp;</p>

  See \ref c2bconf_files, \ref c2bconf_bibtex, and \ref c2beditor_menu.

*/
QString journalDB::retrieve(const QString& JQuery) const
{
    const QString query(JQuery.toLower().remove(c2bUtils::nonLetter));
    if (query.isEmpty())
        return QString();
    for (int i = 0; i < _nitems; ++i)
    {
        if (JAbbrev_simp.at(i) == query)
        {
            if (i > 0 && JExtended_simp.at(i) == JExtended_simp.at(i - 1))
                return JAbbrev.at(i - 1);
            else
                return JAbbrev.at(i);
        }
        if (JExtended_simp.at(i) == query)
            return JAbbrev.at(i);
    }
    int journal_found(0);
    int journal_found_at(-1);
    for (int i = 0; i < _nitems; ++i)
        if (JCode.at(i) == query)
        {
            journal_found++;
            journal_found_at = i;
        }
    if (journal_found == 1)
        return JAbbrev.at(journal_found_at);
    else
        return JQuery;
}

QString journalDB::retrieveFull(const QString& JQuery) const
{
    const QString query(JQuery.toLower().remove(c2bUtils::nonLetter));
    if (query.isEmpty())
        return QString();
    for (int i = 0; i < _nitems; ++i)
    {
        if (JAbbrev_simp.at(i) == query)
            return JExtended.at(i);
        if (JExtended_simp.at(i) == query)
        {
            if (i > 0 && JAbbrev_simp.at(i) == JAbbrev_simp.at(i - 1))
                return JExtended.at(i - 1);
            else if (i > 1 && JAbbrev_simp.at(i) == JAbbrev_simp.at(i - 2))
                return JExtended.at(i - 2);
            else
                return JExtended.at(i);
        }
    }
    int journal_found(0);
    int journal_found_at(-1);
    for (int i = 0; i < _nitems; ++i)
        if (JCode.at(i) == query)
        {
            journal_found++;
            journal_found_at = i;
        }
    if (journal_found == 1)
        return JExtended.at(journal_found_at);
    else
        return JQuery;
}

QString journalDB::retrieveAlternate(const QString& JQuery) const
{
    const QString query(JQuery.toLower().remove(c2bUtils::nonLetter));
    if (query.isEmpty())
        return QString();
    for (int i = _nitems - 1; i >= 0; --i)
    {
        if (JAbbrev_simp.at(i) == query)
        {
            if (i + 1 < _nitems && JExtended_simp.at(i) == JExtended_simp.at(i + 1))
                return JAbbrev.at(i + 1);
            else
                return JAbbrev.at(i);
        }
        if (JExtended_simp.at(i) == query)
            return JAbbrev.at(i);
    }
    int journal_found(0);
    int journal_found_at(-1);
    for (int i = 0; i < _nitems; i++)
        if (JCode.at(i) == query)
        {
            journal_found++;
            journal_found_at = i;
        }
    if (journal_found == 1)
    {
        if (journal_found_at + 1 < _nitems && JCode.at(journal_found_at + 1).isEmpty())
            return JAbbrev.at(journal_found_at + 1);
        else
            return JAbbrev.at(journal_found_at);
    }
    else
        return JQuery;
}

QString journalDB::retrieveAlternateFull(const QString& JQuery) const
{
    const QString query(JQuery.toLower().remove(c2bUtils::nonLetter));
    if (query.isEmpty())
        return QString();
    for (int i = _nitems - 1; i >= 0; --i)
    {
        if (JAbbrev_simp.at(i) == query)
            return JExtended.at(i);
        if (JExtended_simp.at(i) == query)
        {
            if (i + 2 < _nitems && JAbbrev_simp.at(i) == JAbbrev_simp.at(i + 2))
                return JExtended.at(i + 2);
            else if (i + 1 < _nitems && JAbbrev_simp.at(i) == JAbbrev_simp.at(i + 1))
                return JExtended.at(i + 1);
            else
                return JExtended.at(i);
        }
    }
    int journal_found(0);
    int journal_found_at(-1);
    for (int i = 0; i < _nitems; ++i)
        if (JCode.at(i) == query)
        {
            journal_found++;
            journal_found_at = i;
        }
    if (journal_found == 1)
    {
        if (journal_found_at + 2 < _nitems && JCode.at(journal_found_at + 1).isEmpty() &&
            JCode.at(journal_found_at + 2).isEmpty())
            return JExtended.at(journal_found_at + 2);
        else if (journal_found_at + 1 < _nitems && JCode.at(journal_found_at + 1).isEmpty())
            return JExtended.at(journal_found_at + 1);
        else
            return JExtended.at(journal_found_at);
    }
    else
        return JQuery;
}
