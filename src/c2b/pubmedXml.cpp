/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "pubmedXml.h"

#include "cb2bib_utilities.h"


pubmedXml::pubmedXml(const QString& xml) : QXmlStreamReader()
{
    _reference.clearReference();
    addData(xml);
    readReference();
}


void pubmedXml::readReference()
{
    if (hasError())
        return;

    while (reading("PubmedArticle"))
        if (name() == "Journal")
            readJournal();
        else if (name() == "AuthorList")
            readAuthors();
        else if (name() == "MeshHeadingList")
            readKeywords();
        else if (name() == "ArticleTitle")
            readField("title");
        else if (name() == "AbstractText")
            readField("abstract");
        else if (name() == "MedlinePgn")
        {
            readNext();
            _reference["pages"] = text().toString().remove(QRegExp("\\,[\\s\\d]+")); // Cases "11-5, 25"
        }
        else if (name() == "PMID")
        {
            readNext();
            _reference["url"] = c2bUtils::pubmedUrl.arg(text().toString());
        }
        else if (name() == "ArticleId")
        {
            if (attributes().count() > 0)
                if (attributes().at(0).value().toString() == "doi")
                    readField("doi");
        }
}

void pubmedXml::readField(const QString& field)
{
    _reference[field] = readElementText(QXmlStreamReader::IncludeChildElements);
}

void pubmedXml::readAuthors()
{
    QStringList authors;
    while (reading("AuthorList"))
    {
        if (name() == "Author" && attributes().value("ValidYN") != "N")
        {
            QString a, i;
            bool abbreviated(true);
            while (reading("Author"))
                if (name() == "LastName")
                {
                    readNext();
                    a = a + ' ' + text().toString();
                }
                else if (name() == "ForeName" || name() == "FirstName")
                {
                    readNext();
                    a = text().toString() + ' ' + a;
                    abbreviated = false;
                }
                else if (name() == "Suffix")
                {
                    readNext();
                    if (text() == "2nd")
                        a = a + " II";
                    else if (text() == "3rd")
                        a = a + " III";
                    else
                        a = a + ' ' + text().toString();
                }
                else if (name() == "Initials")
                {
                    readNext();
                    i = text().toString();
                }
            if (abbreviated)
                authors.append(i + ' ' + a);
            else
                authors.append(a);
        }
    }
    _reference["author"] = authors.join(", ");
}

void pubmedXml::readJournal()
{
    QString ja, jf, mldate;
    while (reading("Journal"))
        if (name() == "ISOAbbreviation")
        {
            readNext();
            ja = text().toString();
        }
        else if (name() == "Title")
        {
            readNext();
            jf = text().toString();
        }
        else if (name() == "Volume")
            readField("volume");
        else if (name() == "Issue")
            readField("number");
        else if (name() == "Year")
            readField("year");
        else if (name() == "MedlineDate")
        {
            readNext();
            mldate = text().toString();
        }
    if (jf.isEmpty())
        _reference["journal"] = ja;
    else
        _reference["journal"] = jf;
    if (_reference.value("year").isEmpty())
    {
        mldate.remove(QRegExp("[^\\d\\s-]"));
        mldate.remove(QRegExp("\\b\\d{1,3}\\b"));
        _reference["year"] = mldate;
    }
}

void pubmedXml::readKeywords()
{
    QStringList k;
    while (reading("MeshHeadingList"))
        if (name() == "DescriptorName")
        {
            readNext();
            k.append(text().toString());
        }
    _reference["keywords"] = k.join(", ");
}

bool pubmedXml::reading(const QString& tag)
{
    while (!atEnd())
    {
        TokenType t = readNext();
        if (t == StartElement)
            return true;
        else if (t == EndElement)
            if (name() == tag)
                return false;
    }
    return false;
}
