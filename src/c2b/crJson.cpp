/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "crJson.h"

#include "cb2bib_utilities.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <cmath>


crJson::crJson(const QString& json)
{
    _reference.clearReference();
    readReference(json);
}


void crJson::readReference(const QString& json)
{
    _has_error = true;
    _error_string.clear();

    QJsonParseError jerr;
    QJsonDocument jdoc(QJsonDocument::fromJson(json.toUtf8(), &jerr));
    if (jdoc.isNull() || jdoc.isEmpty())
    {
        _error_string =
            QObject::tr("Invalid data%1").arg(jerr.errorString().isEmpty() ? QString() : ": " + jerr.errorString());
        return;
    }
    QJsonObject jobj(jdoc.object().value("message").toObject());
    if (jobj.isEmpty())
    {
        _error_string = QObject::tr("Invalid reference data");
        return;
    }

#ifdef C2B_DEBUG
    for (QJsonObject::const_iterator i = jobj.constBegin(); i != jobj.constEnd(); ++i)
        qDebug() << "[crjson] " << i.key() << i.value();
#endif

    if (jobj.value("DOI").isUndefined())
    {
        _error_string = QObject::tr("Invalid reference data: no DOI parsed");
        return;
    }
    _reference["doi"] = jobj.value("DOI").toString();

    if (!jobj.value("published-print").isUndefined())
    {
        const QJsonValue jyear(
            jobj.value("published-print").toObject().value("date-parts").toArray().first().toArray().first());
        if (!jyear.isUndefined())
            _reference["year"] = QString::number(jyear.toDouble());
    }
    else if (!jobj.value("published-online").isUndefined())
    {
        // For articles no longer published in print
        const QJsonValue jyear(
            jobj.value("published-online").toObject().value("date-parts").toArray().first().toArray().first());
        if (!jyear.isUndefined())
            _reference["year"] = QString::number(jyear.toDouble());
    }

    _reference["volume"] = jobj.value("volume").toString();
    _reference["number"] = jobj.value("issue").toString();
    _reference["pages"] = jobj.value("page").toString();

    QStringList authors;
    const QJsonArray jauthors(jobj.value("author").toArray());
    for (QJsonArray::const_iterator i = jauthors.constBegin(); i != jauthors.constEnd(); ++i)
    {
        const QJsonObject ja((*i).toObject());
        authors.append(ja.value("given").toString() + ' ' + ja.value("family").toString());
    }
    _reference["author"] = authors.join(", ");

    QStringList editors;
    const QJsonArray jeditors(jobj.value("editor").toArray());
    for (QJsonArray::const_iterator i = jeditors.constBegin(); i != jeditors.constEnd(); ++i)
    {
        const QJsonObject je((*i).toObject());
        editors.append(je.value("given").toString() + ' ' + je.value("family").toString());
    }
    _reference["editor"] = editors.join(", ");

    QStringList titles;
    const QJsonArray jtitles(jobj.value("title").toArray());
    for (QJsonArray::const_iterator i = jtitles.constBegin(); i != jtitles.constEnd(); ++i)
        titles.append((*i).toString());
    _normalize_jtitles(&titles);

    QStringList subtitles;
    const QJsonArray jsubtitles(jobj.value("subtitle").toArray());
    for (QJsonArray::const_iterator i = jsubtitles.constBegin(); i != jsubtitles.constEnd(); ++i)
        subtitles.append((*i).toString());
    _normalize_jtitles(&subtitles);

    QStringList containertitles;
    const QJsonArray jcontainertitles(jobj.value("container-title").toArray());
    for (QJsonArray::const_iterator i = jcontainertitles.constBegin(); i != jcontainertitles.constEnd(); ++i)
        containertitles.append((*i).toString());
    _normalize_jtitles(&containertitles);

    const QString jisbn(jobj.value("ISBN").toArray().first().toString());
    const QString jpublisher(jobj.value("publisher").toString());
    const QString jabstract(jobj.value("abstract").toString());
    _reference["abstract"] = _normalize_jabstract(jabstract);
    _reference["title"] = _bibtex_title(titles, subtitles);

    const QString jtype(jobj.value("type").toString());

    if (jtype == "journal-article")
    {
        _reference.typeName = "article";
        _reference["journal"] = containertitles.count() > 0 ? containertitles.first() : QString();
    }
    else if (jtype == "proceedings-article")
    {
        _reference.typeName = "inproceedings";
        _reference["booktitle"] = _bibtex_booktitle(containertitles);
        _reference["series"] = _bibtex_series(containertitles);
        _reference["isbn"] = jisbn;
        _reference["publisher"] = jpublisher;
    }
    else if (jtype == "book")
    {
        _reference.typeName = "book";
        _reference["series"] = containertitles.count() > 0 ? containertitles.first() : QString();
        _reference["isbn"] = jisbn;
        _reference["publisher"] = jpublisher;
    }
    else if (jtype == "book-chapter")
    {
        _reference.typeName = "inbook";
        _reference["booktitle"] = _bibtex_booktitle(containertitles);
        _reference["series"] = _bibtex_series(containertitles);
        _reference["isbn"] = jisbn;
        _reference["publisher"] = jpublisher;
    }
    else
    {
        // jtype == "other"
        _reference.typeName = "misc";
        _reference["booktitle"] = _bibtex_booktitle(containertitles);
        _reference["series"] = _bibtex_series(containertitles);
        _reference["isbn"] = jisbn;
        _reference["publisher"] = jpublisher;
    }

    if (_reference.value("series") == _reference.value("booktitle"))
        _reference["series"] = QString();
    if (jtype == "book-chapter" && !_reference.value("series").isEmpty())
        _reference.typeName = "incollection";

#ifdef C2B_DEBUG
    qDebug() << "[crjson]  TITLES" << titles;
    qDebug() << "[crjson]  SUBTITLES" << subtitles;
    qDebug() << "[crjson]  CONTAINERTITLES" << containertitles;

    qDebug() << "[crjson]  BIBTEX";
    qDebug() << "[crjson]  type       " << _reference.typeName;
    qDebug() << "[crjson]  title      " << _reference.value("title");
    qDebug() << "[crjson]  booktitle  " << _reference.value("booktitle");
    qDebug() << "[crjson]  series     " << _reference.value("series");
    qDebug() << "[crjson]  publisher  " << _reference.value("publisher");
    qDebug() << "[crjson]  isbn       " << _reference.value("isbn");
    qDebug() << "[crjson]  year       " << _reference.value("year");
#endif

    _has_error = false;
}

void crJson::_normalize_jtitles(QStringList* titles)
{
    if (titles->count() == 0)
        return;
    titles->removeDuplicates();
    for (int i = 0; i < titles->count(); ++i)
    {
        QString t(titles->at(i).simplified());
        for (int j = 0; j < t.length(); ++j)
            if (t.at(j).category() == QChar::Punctuation_Dash)
                t[j] = '-';
        t.replace(" - ", ": ");
        t.replace(" : ", ": ");
        (*titles)[i] = t;
    }
}

QString crJson::_normalize_jabstract(const QString& abstract)
{
    if (abstract.isEmpty())
        return abstract;
    QString na(abstract);
    na.replace("&lt;", "<");
    na.replace("&gt;", ">");
    na.replace(QRegExp("<[^>]+>"), " ");
    na.remove(QRegExp("^\\W*(abstract|synopsis|summary)\\.*", Qt::CaseInsensitive));
    return na.simplified();
}

QString crJson::_bibtex_title(const QStringList& titles, const QStringList& subtitles)
{
    if (titles.count() > 0 && subtitles.count() > 0 && !titles.first().contains(": "))
    {
        const int wt(_words(titles.first()));
        const int ws(_words(subtitles.first()));
        const int wu(_words(titles.first() + ' ' + subtitles.first()));
        const int s(100 * (wt + ws - wu) / sqrt(double(wt * ws)));
        if (s < 30)
            return titles.first() + ": " + subtitles.first();
    }
    return titles.count() > 0 ? titles.first() : QString();
}

QString crJson::_bibtex_booktitle(const QStringList& titles)
{
    if (titles.count() == 0)
        return QString();
    if (titles.count() == 2)
        return (!titles.at(1).contains(
                    QRegExp("(advances|series|lecture notes|studies in|topics in)", Qt::CaseInsensitive)))
               ? titles.at(1)
               : titles.at(0);
    return titles.first();
}

QString crJson::_bibtex_series(const QStringList& titles)
{
    if (titles.count() == 2)
        return (titles.at(1).contains(
                    QRegExp("(advances|series|lecture notes|studies in|topics in)", Qt::CaseInsensitive)))
               ? titles.at(1)
               : titles.at(0);
    return QString();
}

int crJson::_words(const QString& s)
{
    QStringList wl(s.split(QRegExp("\\W"), QString::SkipEmptyParts));
    wl.removeDuplicates();
    return wl.count();
}
