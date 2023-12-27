/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "texToHtml.h"

#include "cb2bib_parameters.h"
#include "settings.h"

#include <QUrl>


texToHtml::texToHtml() : texParser()
{
    _macro_arguments_rx = QRegExp("\\}\\s*\\[\\s*(\\d+)\\s*\\]\\s*\\{");
    _named_extern_url_rx = QRegExp("_((?:file|http|https|ftp)://(?:[^\\s\\n\\r\\[]+))\\[([^\\]]*)\\]");
    _named_url_rx = QRegExp("\\b((?:file|http|https|ftp)://(?:[^\\s\\n\\r\\[]+))\\[([^\\]]*)\\]");
    _extern_url_rx = QRegExp("_((?:file|http|https|ftp)(?!.+\">)://(?:[^\\s\\n\\r\\[]+))(\\.[\\s\\n\\r]){0,1}");
    _url_rx = QRegExp("\\b((?:file|http|https|ftp)(?!.+\">)://(?:[^\\s\\n\\r\\[]+))(\\.[\\s\\n\\r]){0,1}");

    _close_subsection = false;
    _close_subsubsection = false;
    _make_index = false;
    _use_mathjax_rendering = false;
    _use_relative_links = false;
    _index_anchors = 0;

    _settingsP = settings::instance();
}


void texToHtml::toHtml(const QString& tex, const QString& fn)
{
    _html_filename = fn;
    c2bUtils::stringToFile(toHtml(tex), fn);
}

QString texToHtml::toHtml(const QString& tex)
{
    _bibtex_directory.clear();
    _cites.clear();
    _close_subsection = false;
    _close_subsubsection = false;
    _html.clear();
    _index = "<ul>\n";
    _index_anchors = 0;
    _make_index = false;
    _use_mathjax_rendering = false;
    _references.clear();
    _tex_macro_names_rx.clear();
    _tex_macros.clear();
    _title.clear();

    _use_relative_links = _settingsP->value("c2bAnnote/UseRelativeLinks").toBool();
    if (_html_filename.isEmpty())
        _use_relative_links = false;
    else
        _current_dir = QDir(QFileInfo(_html_filename).absolutePath());

    QString tex2html(c2bUtils::fileToString(":/htm/htm/tex2html.html"));
    QString mathjax_head(c2bUtils::fileToString(_settingsP->fileName("c2bAnnote/MathJaxHeaderFile")).trimmed());
    if (!mathjax_head.isEmpty())
        _use_mathjax_rendering = true;

    parse(tex);

    if (_close_subsubsection)
        _index += "</ul></li>\n";
    if (_close_subsection)
        _index += "</ul></li>\n";
    _index += "</ul>";
    if (_use_mathjax_rendering)
    {
        if (!_tex_macros.isEmpty())
        {
            QString t("\n\n<script type=\"text/x-mathjax-config\">\n  MathJax.Hub.Config({\n   TeX: {\n    Macros: "
                      "{%1\n    }\n   }\n  });\n</script>\n");
            mathjax_head += t.arg(_tex_macros);
        }
        tex2html.replace("GET_MATHJAX_HEAD", mathjax_head);
    }
    else
        tex2html.remove("GET_MATHJAX_HEAD");
    if (_settingsP->value("c2bAnnote/IncludeCSS").toBool())
    {
        QString css(c2bUtils::fileToString(_settingsP->fileName("c2bAnnote/AnnoteCssFile")).trimmed());
        if (css.isEmpty())
            css = c2bUtils::fileToString(":/htm/htm/tex2html.css");
        tex2html.replace("GET_CSS", "<style type=\"text/css\">\n" + css.trimmed() + "\n</style>\n");
    }
    else
    {
        QString cssfn(_settingsP->fileName("c2bAnnote/AnnoteCssFile"));
        if (cssfn.isEmpty())
            tex2html.remove("GET_CSS");
        else
        {
            if (_use_relative_links)
                cssfn = _current_dir.relativeFilePath(cssfn);
            tex2html.replace("GET_CSS", "\n <link href=\"" + cssfn + "\" rel=\"stylesheet\" type=\"text/css\"/>\n");
        }
    }
    tex2html.replace("GET_TITLE", _title);
    retrieveReferences();
    QString reference_list_html;
    referencesToHtml(&reference_list_html);
    tex2html.replace("GET_REFERENCES", reference_list_html);
    citesToHtml(&_html);
    if (_make_index && _index_anchors > 1)
    {
        _index = c2bUtils::fileToString(":/htm/htm/tex2html_index.html").arg(_index);
        tex2html.replace("GET_INDEX", _index);
    }
    else
        tex2html.remove("GET_INDEX");
    tex2html.replace("GET_HTML", _html);
    tex2html.replace("GET_CB2BIB_VERSION_NUMBER", C2B_VERSION);

    _html_filename.clear();
    return tex2html;
}

void texToHtml::parseElement(const QString& p, const QString& e, const QString& v)
{
    if (e == "section")
    {
        const QString sv(toHtmlString(v));
        ++_index_anchors;
        _html += QString("\n<h1><a id=\"sect%1\"></a>%2</h1>\n\n").arg(_index_anchors).arg(sv);
        if (_close_subsubsection)
            _index += "</ul></li>\n";
        if (_close_subsection)
            _index += "</ul></li>\n";
        _index += QString("<li><a href=\"#sect%1\">%2</a></li>\n").arg(_index_anchors).arg(sv);
        _close_subsubsection = false;
        _close_subsection = false;
    }
    else if (e == "subsection")
    {
        const QString sv(toHtmlString(v));
        ++_index_anchors;
        _html += QString("\n<h2><a id=\"sect%1\"></a>%2</h2>\n\n").arg(_index_anchors).arg(sv);
        if (_close_subsubsection)
            _index += "</ul></li>\n";
        if (!_close_subsection)
            _index += "<li style=\"list-style: none\"><ul>\n";
        _index += QString("<li><a href=\"#sect%1\">%2</a></li>\n").arg(_index_anchors).arg(sv);
        _close_subsubsection = false;
        _close_subsection = true;
    }
    else if (e == "subsubsection")
    {
        const QString sv(toHtmlString(v));
        ++_index_anchors;
        _html += QString("\n<h3><a id=\"sect%1\"></a>%2</h3>\n\n").arg(_index_anchors).arg(sv);
        if (!_close_subsubsection)
            _index += "<li style=\"list-style: none\"><ul>\n";
        _index += QString("<li><a href=\"#sect%1\">%2</a></li>\n").arg(_index_anchors).arg(sv);
        _close_subsubsection = true;
    }
    else if (e == "title")
        _title = toHtmlString(v);
    else if (e == "itemize")
    {
        const QStringList items(v.trimmed().split("\\item ", QString::SkipEmptyParts));
        for (int i = 0; i < items.count(); ++i)
            parseTextParagraph("- " + items.at(i).simplified());
    }
    else if (e == "abstract")
        _html += QString("\n<div id=\"abstract\" class=\"abstract\">\n%1\n</div><br /><hr />\n\n")
                 .arg(toHtmlString(v.trimmed(), false));
    else if (e == "verbatim")
        _html += QString("\n<pre>%1</pre>\n\n").arg(v);
    else if (e == "newcommand")
        extractMacro(v);
    else
        _html += QString("\n<div>\n%1\n</div>\n\n").arg(p);
}

void texToHtml::parseComment(const QString& p)
{
    if (p.startsWith("%\\c2b_bibtex_directory{"))
        c2bUtils::inBraces(p.indexOf('{') + 1, p, &_bibtex_directory);
    else if (p == "%\\c2b_makeindex")
        _make_index = true;
}

void texToHtml::parseTextParagraph(const QString& p)
{
    extractCites(p);
    QString pstr(toHtmlString(p, false));
    urlToHtml(&pstr);
    if (p.startsWith("- "))
        _html += QString("\n<ul><li>%1</li></ul>\n\n").arg(pstr.mid(2));
    else
        _html += QString("\n<p>%1</p>\n\n").arg(pstr);
}

void texToHtml::extractMacro(const QString& v)
{
    QString name;
    if (!c2bUtils::inBraces(1, v, &name))
        return;
    // Substitution '\macro' -> '$\macro[args]$'. MathJax will not process macros outside equation environments.
    _tex_macro_names_rx.append(QRegExp("(\\" + name + "\\S*)"));
    // To minimize clashes, the replacement must be performed from longest to shortest names.
    // Sort now, even if this needs multiple sortings. This way, substitutions can be done while parsing.
    std::sort(_tex_macro_names_rx.begin(), _tex_macro_names_rx.end(), c2bUtils::patternLengthMoreThan);
    QString definition;
    for (int i = name.length() + 2; i < v.length(); ++i)
        if (v.at(i) == '{')
        {
            if (c2bUtils::inBraces(i + 1, v, &definition))
                break;
            else
                return;
        }
    if (definition.isEmpty())
        return;
    name.remove("\\");
    definition.remove("\\ensuremath");
    definition.replace("\\", "\\\\");
    if (_macro_arguments_rx.indexIn(v) > -1)
        _tex_macros += QString("\n     %1: ['%2',%3],").arg(name, definition, _macro_arguments_rx.cap(1));
    else
        _tex_macros += QString("\n     %1: '%2',").arg(name, definition);
}

void texToHtml::extractCites(const QString& p)
{
    int pos(p.indexOf("\\cite{", 0));
    while (pos >= 0)
    {
        QString cites;
        if (c2bUtils::inBraces(pos + 6, p, &cites))
        {
            const QStringList cite(cites.split(',', QString::SkipEmptyParts));
            for (int i = 0; i < cite.count(); ++i)
            {
                const QString c(cite.at(i).trimmed());
                if (!_cites.contains(c))
                    _cites.insert(c, -(1 + _cites.count()));
            }
        }
        pos = p.indexOf("\\cite{", pos + 6);
    }
}

void texToHtml::citesToHtml(QString* html)
{
    QString key("\\b%1\\b");
    QHash<QString, bibReference>::const_iterator i = _references.constBegin();
    while (i != _references.constEnd())
    {
        const QString k(i.key());
        html->replace(QRegExp(key.arg(k)), QString("<a href=\"#%1\">%2</a>").arg(k).arg(_cites.value(k)));
        ++i;
    }
    html->replace(QRegExp("\\\\cite\\{([^\\{]+)\\}"), "<span class=\"citations\">[\\1]</span>");
}

/**
    Retrieve references from BibTeX files directory
*/
void texToHtml::retrieveReferences()
{
    if (_bibtex_directory.isEmpty())
        _bibtex_directory = QFileInfo(_settingsP->fileName("cb2Bib/BibTeXFile")).path();
    const QStringList flist(c2bUtils::filesInDir(_bibtex_directory, QStringList() << "*.bib"));
    const QStringList keys(_cites.keys());
    QStringList fields;
    fields.append("author");
    fields.append("booktitle");
    fields.append("doi");
    fields.append("editor");
    fields.append("file");
    fields.append("journal");
    fields.append("pages");
    fields.append("title");
    fields.append("url");
    fields.append("volume");
    fields.append("year");
    bibReference ref;
    _cbp.initReferenceParsing(_bibtex_directory + '/', fields, &ref);
    bool done(false);
    for (int i = 0; i < flist.count(); ++i)
    {
        if (done)
            return;
        const QString bib_contents(c2bUtils::fileToString(flist.at(i)));
        done = true;
        for (int j = 0; j < keys.count(); ++j)
        {
            if (_cites.value(keys.at(j)) > 0)
                continue;
            done = false;
            const QString key(keys.at(j));
            if (_cbp.referenceAtKey(key, bib_contents, &ref))
            {
                _references.insert(key, ref);
                _cites[key] = -_cites[key];
            }
        }
    }
}

void texToHtml::referencesToHtml(QString* reference_list_html)
{
    reference_list_html->clear();
    if (_references.count() == 0)
        return;

    QStringList keys(_references.keys());
    QMap<int, QString> ordering;
    for (int i = 0; i < keys.count(); ++i)
        ordering.insert(_cites.value(keys.at(i)), keys.at(i));
    keys = ordering.values();

    const QString reference_item_html(c2bUtils::fileToString(":/htm/htm/reference_item.html"));
    const QRegExp nonletters("[^\\w\\s-]");
    QString references;
    for (int i = 0; i < keys.count(); ++i)
    {
        const bibReference& ref = _references.value(keys.at(i));

        QString author(ref.anyAuthor());
        if (!author.isEmpty())
        {
            author = _cbp.authorFromBibTeX(author);
            author.remove(nonletters);
            author.replace(" and ", ", ");
            c2bUtils::simplifyString(author);
            author += '.';
        }

        QString title(ref.anyTitle());
        c2bUtils::cleanTitle(title, true);

        // Do not percent encode file (some browsers dont like encoded local files) and url
        // (it might already be, if needed, decode prior to encode)
        const QString doi(ref.value("doi"));
        const QString file(ref.value("file"));
        const QString url(ref.value("url"));
        QString link;
        if (!file.isEmpty())
        {
            if (_use_relative_links)
                link = QDir::cleanPath(_current_dir.relativeFilePath(file));
            else
                link = QDir::cleanPath(file);
        }
        else if (!url.isEmpty())
            link = url;
        else if (!doi.isEmpty())
        {
            if (doi.startsWith("http"))
                link = doi;
            else
                link = "https://dx.doi.org/" + QUrl::toPercentEncoding(doi);
        }

        const QString journal(ref.anyJournal());
        const QString volume(ref.value("volume"));

        QString pages(ref.value("pages"));
        if (!pages.isEmpty())
        {
            if (!volume.isEmpty())
                pages = ", " + pages.remove(' ');
            else
                pages = ' ' + pages.remove(' ');
        }

        QString year(ref.value("year"));
        if (!year.isEmpty())
            year = '(' + year + ").";

        QString item(reference_item_html);
        item.replace("GET_REFERENCE_ANCHOR_ID", ref.citeidName);
        item.replace("GET_REFERENCE_ANCHOR_NAME", ref.citeidName);
        item.replace("GET_REFERENCE_AUTHOR", author);
        if (link.isEmpty())
            item.remove("href=\"GET_REFERENCE_LINK\"");
        else
            item.replace("GET_REFERENCE_LINK", link);
        item.replace("GET_REFERENCE_PAGES", pages);
        item.replace("GET_REFERENCE_SOURCE", journal);
        item.replace("GET_REFERENCE_TITLE", c2bUtils::toHtmlString(title));
        item.replace("GET_REFERENCE_VOLUME", volume);
        item.replace("GET_REFERENCE_YEAR", year);
        references += item;

        // Update _cites values according to this list
        _cites[keys.at(i)] = i + 1;
    }
    *reference_list_html = c2bUtils::fileToString(":/htm/htm/reference_list.html");
    reference_list_html->replace("GET_REFERENCES", references);
}
