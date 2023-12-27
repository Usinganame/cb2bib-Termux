/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef TEXPARSER_H
#define TEXPARSER_H

#include <QString>
#include <QTextStream>


/**
    Minimalist TeX parser
*/
class texParser
{

public:
    inline texParser() : _stop_parsing(false) {}
    inline virtual ~texParser() {}


protected:
    virtual void parseComment(const QString& /* p */) {}
    virtual void parseElement(const QString& /* p */, const QString& /* e */, const QString& /* v */) {}
    virtual void parseEmptyLine() {}
    virtual void parseLaTeXMarkup(const QString& /* p */, const QString& /* e */) {}
    virtual void parseTextParagraph(const QString& /* p */) {}
    void parse(QString tex);

    inline void stop()
    {
        _stop_parsing = true;
    }


private:
    QString _element;
    QString _line;
    QString _paragraph;
    QTextStream _stream;
    bool _stop_parsing;
    void doElement();
    void gotoEnd(const QString& e);
    void gotoEndBraces(const QString& e);
    void gotoEndMacro(const QString& e);

    inline const QString& readLine(const bool trim = false)
    {
        if (trim)
            _line = _stream.readLine().trimmed();
        else
            _line = _stream.readLine();
        return _line;
    }

    inline void flushElement(const QString& e, const QString& v)
    {
        flush();
        parseElement(_element, e, v);
    }

    inline void flushLaTeXMarkup(const QString& e)
    {
        _element = _line;
        flush();
        parseLaTeXMarkup(_element, e);
    }

    inline void flush()
    {
        if (_paragraph.isEmpty())
            return;
        parseTextParagraph(_paragraph.mid(1));
        _paragraph.clear();
    }
};

#endif
