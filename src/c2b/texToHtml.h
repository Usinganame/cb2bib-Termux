/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef TEXTOHTML_H
#define TEXTOHTML_H

#include "texParser.h"

#include "coreBibParser.h"


/**
    Minimalist TeX to HTML converter
*/
class texToHtml : public texParser
{

public:
    texToHtml();
    inline ~texToHtml() {}

    QString toHtml(const QString& tex);
    void toHtml(const QString& tex, const QString& fn);


private:
    QDir _current_dir;
    QHash<QString, bibReference> _references;
    QHash<QString, int> _cites;
    QList<QRegExp> _tex_macro_names_rx;
    QRegExp _extern_url_rx;
    QRegExp _macro_arguments_rx;
    QRegExp _named_extern_url_rx;
    QRegExp _named_url_rx;
    QRegExp _url_rx;
    QString _bibtex_directory;
    QString _html;
    QString _html_filename;
    QString _index;
    QString _tex_macros;
    QString _title;
    bool _close_subsection;
    bool _close_subsubsection;
    bool _make_index;
    bool _use_mathjax_rendering;
    bool _use_relative_links;
    coreBibParser _cbp;
    int _index_anchors;
    settings* _settingsP;
    void citesToHtml(QString* html);
    void extractCites(const QString& p);
    void extractMacro(const QString& v);
    void parseComment(const QString& p) override;
    void parseElement(const QString& p, const QString& e, const QString& v) override;
    void parseTextParagraph(const QString& p) override;
    void referencesToHtml(QString* reference_list_html);
    void retrieveReferences();

    inline void urlToHtml(QString* str) const
    {
        str->replace(_named_url_rx, "<a href=\"\\1\">\\2</a>");
        str->replace(_url_rx, "<a href=\"\\1\">\\1</a>\\2");
        str->replace(_named_extern_url_rx, "<a href=\"\\1\" target=\"_blank\">\\2</a>");
        str->replace(_extern_url_rx, "<a href=\"\\1\" target=\"_blank\">\\1</a>\\2");
    }

    inline QString toHtmlString(QString str, const bool do_macros = true) const
    {
        // Move LaTeX to Unicode
        c2bUtils::bibToC2b(str);
        // Encode some symbols to HTML for proper browser display
        str.replace('<', "&#060;");
        str.replace('>', "&#062;");
        str.replace('%', "&#037;");
        if (!_use_mathjax_rendering)
        {
            str.replace(QRegExp("_\\{([^\\}]*)\\}"), "<sub>\\1</sub>");
            str.replace(QRegExp("\\^\\{([^\\}]*)\\}"), "<sup>\\1</sup>");
        }
        // Insert $$ into LaTeX macros provided it can be reasonably assumed they are
        // outside a match environment
        if (do_macros)
            for (int i = 0; i < _tex_macro_names_rx.count(); ++i)
                str.replace(_tex_macro_names_rx.at(i), "$\\1$");
        return str;
    }
};

#endif
