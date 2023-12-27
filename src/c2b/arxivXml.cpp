/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "arxivXml.h"


arxivXml::arxivXml(const QString& xml) : QXmlStreamReader()
{
    _reference.clearReference();
    addData(xml);
    readReference();
}


void arxivXml::readReference()
{
    if (hasError())
        return;

    QStringList authors;

    while (reading("entry"))
        if (name() == "author")
            appendAuthor(&authors);
        else if (name() == "journal_ref")
            readField("note");
        else if (name() == "title")
            readField("title");
        else if (name() == "summary")
            readField("abstract");
        else if (name() == "doi")
            readField("doi");
        else if (name() == "id")
            processId();
        else if (name() == "published")
            processDate();

    _reference["author"] = authors.join(", ");
}

void arxivXml::readField(const QString& field)
{
    readNext();
    _reference[field] = text().toString();
}

void arxivXml::processId()
{
    readNext();
    QRegExp rxarxiv("abs/(.+)$");
    if (text().toString().contains(rxarxiv))
    {
        QString aid(rxarxiv.cap(1));
        aid.remove(QRegExp("v\\d{1,2}$"));
        _reference["eprint"] = aid;
        _reference["journal"] = "arXiv:" + aid;
        _reference["url"] = c2bUtils::arxivUrl.arg(aid);
    }
}

void arxivXml::processDate()
{
    readNext();
    _reference["year"] = text().toString().left(4);
}

void arxivXml::appendAuthor(QStringList* authors)
{
    while (reading("name"))
        if (name() == "name")
        {
            readNext();
            authors->append(text().toString());
        }
}

bool arxivXml::reading(const QString& tag)
{
    if (tokenType() == NoToken)
        while (!atEnd())
            if (readNext() == StartElement && name() == tag)
                return true;
    while (!atEnd())
    {
        TokenType t = readNext();
        if (t == StartElement)
            return true;
        else if (t == EndElement && name() == tag)
            return false;
    }
    return false;
}
