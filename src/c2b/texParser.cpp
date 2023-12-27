/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "texParser.h"

#include "cb2bib_utilities.h"


void texParser::parse(QString tex)
{
    _stream.setString(&tex, QIODevice::ReadOnly);
    _paragraph.clear();
    _stop_parsing = false;
    while (!_stream.atEnd() && !_stop_parsing)
    {
        readLine(true);
        if (_line.isEmpty())
        {
            flush();
            parseEmptyLine();
        }
        else if (_line.startsWith('%'))
        {
            flush();
            parseComment(_line);
        }
        else if (_line.startsWith('\\'))
            doElement();
        else
            _paragraph += ' ' + _line;
    }
    flush();
}

void texParser::doElement()
{
    if (_line.startsWith("\\begin{"))
        gotoEnd("begin");
    else if (_line.startsWith("\\section{"))
        gotoEndBraces("section");
    else if (_line.startsWith("\\subsection{"))
        gotoEndBraces("subsection");
    else if (_line.startsWith("\\subsubsection{"))
        gotoEndBraces("subsubsection");
    else if (_line.startsWith("\\title{"))
        gotoEndBraces("title");
    else if (_line.startsWith("\\author{"))
        gotoEndBraces("author");
    else if (_line.startsWith("\\newcommand{"))
        gotoEndMacro("newcommand");
    else if (_line.startsWith("\\documentclass"))
        flushLaTeXMarkup("documentclass");
    else if (_line.startsWith("\\maketitle"))
        flushLaTeXMarkup("maketitle");
    else if (_line.startsWith("\\end{document}"))
        flushLaTeXMarkup("document");
    else if (_line.startsWith("\\bibliography"))
        flushLaTeXMarkup("bibliography");
    else
        _paragraph += ' ' + _line;
}

void texParser::gotoEnd(const QString& e)
{
    QString block_name;
    QString block_contents;
    const int pos(e.length() + 2);
    c2bUtils::inBraces(pos, _line, &block_name);
    if (block_name == "document")
    {
        flushLaTeXMarkup("document");
        return;
    }
    QRegExp end_block(QString("^\\s*\\\\end\\{%1\\}").arg(block_name));
    _element = _line;
    while (!_stream.atEnd())
    {
        readLine();
        if (_line.contains(end_block))
        {
            _element += '\n' + _line.trimmed();
            break;
        }
        else
        {
            _element += '\n' + _line;
            block_contents += '\n' + _line;
        }
    }
    flushElement(block_name, block_contents);
}

void texParser::gotoEndBraces(const QString& e)
{
    QString in;
    const int pos(e.length() + 2);
    _element = _line;
    while (!_stream.atEnd() && !c2bUtils::inBraces(pos, _element, &in))
        _element += '\n' + readLine();
    flushElement(e, c2bUtils::simplifyString(in));
}

void texParser::gotoEndMacro(const QString& e)
{
    // Macro syntax: \newcommand{name}[number of arguments]{definition}
    int line_init_pos(e.length() + 3);
    int element_init_pos(0);
    _element = _line;
    while (!_stream.atEnd())
    {
        // Find the begining of macro definition
        for (int pos = line_init_pos; pos < _line.length(); ++pos)
            if (_line.at(pos) == '{')
            {
                QString in;
                while (!_stream.atEnd() && !c2bUtils::inBraces(element_init_pos + pos + 1, _element, &in))
                    _element += '\n' + readLine();
                in = _element;
                in.remove('\\' + e);
                flushElement(e, c2bUtils::simplifyString(in));
                return;
            }
        // Try next line
        line_init_pos = 0;
        element_init_pos = _element.length() + 1;
        _element += '\n' + readLine();
    }
}
