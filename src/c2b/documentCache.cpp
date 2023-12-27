/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "documentCache.h"

#include "cb2bib_utilities.h"
#include "document.h"
#include "settings.h"
#include "triads.h"

#include <QDataStream>


documentCache::documentCache()
    : _current(_cache), _content_type(documentContents::Complete), _cache_load_size(0), _settingsP(settings::instance()) {}

documentCache::~documentCache()
{
    save();
}


void documentCache::load(const QString& fn, const documentContents::Type type)
{
    _content_type = type;
    if (_load_filename == fn)
        return;
    unload();
    _load_filename = fn;
    const QString cache_dir(_settingsP->fileName("cb2Bib/CacheDirectory"));
    if (QFileInfo::exists(cache_dir) && QFileInfo(cache_dir).isDir())
        _cache_filename = QDir::cleanPath(cache_dir + '/' + QFileInfo(_load_filename).fileName() + ".c2b");
    else
        _cache_filename = _load_filename.trimmed() + ".c2b";
    if (QFileInfo::exists(_cache_filename))
    {
        QFile file(_cache_filename);
        if (file.open(QIODevice::ReadOnly))
        {
            QDataStream ds(&file);
            ds >> _cache;
        }
    }
#if defined(C2B_USE_LZSSE)
    if (!_cache.contains("clzsse"))
    {
        _cache.clear();
        _cache.insert("clzsse", QByteArray());
    }
#elif defined(C2B_USE_LZ4)
    if (!_cache.contains("clz4"))
    {
        _cache.clear();
        _cache.insert("clz4", QByteArray());
    }
#elif defined(C2B_USE_LZO)
    if (!_cache.contains("clzo"))
    {
        _cache.clear();
        _cache.insert("clzo", QByteArray());
    }
#else
    if (!_cache.contains("czlib"))
    {
        _cache.clear();
        _cache.insert("czlib", QByteArray());
    }
#endif
    _cache_load_size = _cache.size();
}

void documentCache::unload()
{
    // Release cache memory
    save();
    _cache.clear();
    _cache_filename.clear();
    _cache_load_size = 0;
    _load_filename.clear();
}

bool documentCache::setCurrent(const QString& fn, int* pdfCounter, QString* logString, int* errorCounter)
{
    const QString doc_fn(QDir::cleanPath(fn.trimmed()));
    if (doc_fn.isEmpty())
    {
        _current.clear();
        return false;
    }
    const QString skey("sign:" + doc_fn);
    const QString tkey(doc_fn);
    _current.preload(skey, tkey, _content_type);

    if (!_cache.contains(tkey))
    {
        document doc(doc_fn, document::Complete);
        _current._text = doc.toString();
        if (!doc.errorString().isEmpty())
        {
            ++(*errorCounter);
            (*logString) += QObject::tr("% [cb2bib] %1\n").arg(doc.errorString());
            return false;
        }
        _cache.insert(doc_fn, c2bUtils::compressString(_current._text));
        if (_content_type == documentContents::Simplified)
        {
            _current._text = c2bUtils::toAscii(_current._text, c2bUtils::KeepWords);
            _current._signature = triads::asciiTextSignature(_current._text);
        }
        else
            _current._signature = triads::textSignature(_current._text);
        _cache.insert(skey, c2bUtils::stringToByteArray(_current._signature));
        _current._is_text_loaded = true;
        _current._is_signature_loaded = true;
    }
    ++(*pdfCounter);
    return true;
}

bool documentCache::setCurrent(const QString& fn)
{
    const QString doc_fn(QDir::cleanPath(fn.trimmed()));
    if (doc_fn.isEmpty())
    {
        _current.clear();
        return false;
    }
    const QString skey("sign:" + doc_fn);
    const QString tkey(doc_fn);
    _current.preload(skey, tkey, _content_type);

    if (!_cache.contains(tkey))
    {
        document doc(doc_fn, document::Complete);
        _current._text = doc.toString();
        if (!doc.errorString().isEmpty())
            return false;
        _cache.insert(doc_fn, c2bUtils::compressString(_current._text));
        if (_content_type == documentContents::Simplified)
        {
            _current._text = c2bUtils::toAscii(_current._text, c2bUtils::KeepWords);
            _current._signature = triads::asciiTextSignature(_current._text);
        }
        else
            _current._signature = triads::textSignature(_current._text);
        _cache.insert(skey, c2bUtils::stringToByteArray(_current._signature));
        _current._is_text_loaded = true;
        _current._is_signature_loaded = true;
    }
    return true;
}

void documentCache::save()
{
    if (_cache_load_size != _cache.size() && !_cache_filename.isEmpty())
    {
        QFile file(_cache_filename);
        if (file.open(QIODevice::WriteOnly))
        {
            QDataStream ds(&file);
            ds << _cache;
        }
    }
}
