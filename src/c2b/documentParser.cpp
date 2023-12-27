/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "documentParser.h"


documentParser::documentParser(const QString& text, const int maximum)
    : _space(QChar(' ')), _text(text), _maximum_words(maximum), _minimum_words(2), _text_length(text.length())
{
    _current_nwords = 0;
    _current_ssentence_length = 0;
    _current_ssentence_origin = 0;
    _nwords = 0;
    _position = 0;

    if (_text_length > 0)
    {
        if (_is_letter(_text.at(0)))
        {
            _ssentence_origin = 0;
            _all_done = false;
        }
        else
        {
            _ssentence_origin = nextWord(0);
            _position = _ssentence_origin;
            _all_done = (_ssentence_origin == _text_length);
        }
    }
    else
        _all_done = true;
}

documentParser::~documentParser() {}


bool documentParser::parses()
{
    if (_all_done)
        return false;

    // Assumed 0-terminated string, i.e., text[_text_length] = 0
    const QChar* const text(_text.constData());
    int i(_position);
    while (i++ < _text_length)
    {
        const QChar& c(text[i]);
        if (_is_letter_or_number(c))
            continue;
        ++_nwords;
        // Contiguous words within a subsentence
        if (c == _space && _is_letter(text[i + 1]))
        {
            if (_nwords < _minimum_words)
                continue;
            if (_nwords < _maximum_words)
            {
                _position = i + 1;
                _current_nwords = _nwords;
                _current_ssentence_origin = _ssentence_origin;
                _current_ssentence_length = i - _ssentence_origin;
                return true;
            }
        }
        // Subsentence terminated at c
        else if (_nwords < _minimum_words)
        {
            // Too few words in subsentence, move forward to next subsentence
            _ssentence_origin = nextWord(i);
            i = _ssentence_origin;
            _nwords = 0;
            continue;
        }
        _position = nextWord(_ssentence_origin);
        _current_nwords = _nwords;
        _current_ssentence_origin = _ssentence_origin;
        _current_ssentence_length = i - _ssentence_origin;
        _nwords = 0;
        _ssentence_origin = _position;
        return true;
    }

    _all_done = true;
    return false;
}

int documentParser::nextWord(const int pos) const
{
    for (int i = pos + 1; i < _text_length; ++i)
        if (_is_letter(_text.at(i)) && !_is_letter_or_number(_text.at(i - 1)))
            return i;
    return _text_length;
}
