/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

#include <QString>


class documentParser
{

public:
    documentParser(const QString& text, const int maximum);
    ~documentParser();

    bool parses();
    inline QStringRef subsentence() const
    {
        return _text.midRef(_current_ssentence_origin, _current_ssentence_length);
    }
    inline int nlength() const
    {
        return _current_ssentence_length;
    }
    inline int nwords() const
    {
        return _current_nwords;
    }


private:
    int nextWord(const int pos) const;

    static inline bool _is_letter(const QChar& c)
    {
        const ushort uc(c.unicode());
        if ((uc > 96 && uc < 123) || uc == 95 || uc == 39)
            return true;
        else
            return c.isLetter();
    }
    static inline bool _is_letter_or_number(const QChar& c)
    {
        const ushort uc(c.unicode());
        if ((uc > 96 && uc < 123) || (uc > 47 && uc < 58) || uc == 95 || uc == 39)
            return true;
        else
            return c.isLetterOrNumber();
    }

    bool _all_done;
    int _current_nwords;
    int _current_ssentence_length;
    int _current_ssentence_origin;
    int _nwords;
    int _position;
    int _ssentence_origin;

    const QChar _space;
    const QString _text;
    const int _maximum_words;
    const int _minimum_words;
    const int _text_length;
};

#endif
