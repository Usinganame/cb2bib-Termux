/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef DOCUMENTCONTENTS_H
#define DOCUMENTCONTENTS_H

#include "cb2bib_utilities.h"

#include <QHash>
#include <QString>


class documentContents
{

public:
    enum Type
    {
        Simplified,
        Complete
    };

    inline const QString& signature() const
    {
        if (!_is_signature_loaded)
        {
            _signature = c2bUtils::byteArrayToString(_cache.value(_signature_key));
            _is_signature_loaded = true;
        }
        return _signature;
    }

    inline const QString& text() const
    {
        if (!_is_text_loaded)
        {
            if (_type == Simplified)
                _text = c2bUtils::toAscii(c2bUtils::decompressString(_cache.value(_text_key)), c2bUtils::KeepWords);
            else
                _text = c2bUtils::decompressString(_cache.value(_text_key));
            _is_text_loaded = true;
        }
        return _text;
    }


private:
    inline explicit documentContents(const QHash<QString, QByteArray>& cache)
        : _type(Complete), _cache(cache), _is_signature_loaded(false), _is_text_loaded(false) {}
    inline ~documentContents() {}


    inline void clear()
    {
        _is_signature_loaded = false;
        _is_text_loaded = false;
        _signature.clear();
        _signature_key.clear();
        _text.clear();
        _text_key.clear();
    }

    inline void preload(const QString& skey, const QString& tkey, const Type type)
    {
        clear();
        _signature_key = skey;
        _text_key = tkey;
        _type = type;
    }

    QString _signature_key;
    QString _text_key;
    Type _type;
    const QHash<QString, QByteArray>& _cache;
    mutable QString _signature;
    mutable QString _text;
    mutable bool _is_signature_loaded;
    mutable bool _is_text_loaded;

    friend class documentCache;
};

#endif
