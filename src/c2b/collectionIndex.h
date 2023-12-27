/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef COLLECTIONINDEX_H
#define COLLECTIONINDEX_H

#include <QMap>
#include <QString>


class bibParser;
class settings;

class QTextStream;


class collectionIndex
{

public:
    explicit collectionIndex(bibParser* bp);
    ~collectionIndex();

    int index(const QString& dir);


private:
    struct KeysentenceData
    {
        inline KeysentenceData() : ndocuments(0) {}
        inline explicit KeysentenceData(const int document) : ndocuments(1)
        {
            documents.append(document);
        }
        inline void update(const int document)
        {
            ++ndocuments;
            documents.append(document);
        }
        int ndocuments;
        QList<int> documents;
    };

    static inline bool _last_equals_first(const QString& text)
    {
        const ushort* r((const ushort*)text.constData());
        const ushort* const cn(r + text.length());
        const ushort* s;
        for (s = cn - 1; s > r; --s)
            if (*s == 32)
                break;
        ++s;
        while (s < cn)
            if (*(s++) != *(r++))
                return false;
        return *r == 32;
    }

    KeysentenceData* _digest_sentence(KeysentenceData* ksd, KeysentenceData* ksdndmax, int* ndmax) const;
    QString preprocessedText(const QString& journal, const QString& text) const;
    QString& replace(QString& str, const QChar& a, const QChar& b) const;
    bool isValidKeySentence(const QString& text) const;
    void analyzeKeySentences();
    void cleanupKeySentences();
    void digestKeySentences();
    void setKeySentences(const int documentid, const QString& text);

    QTextStream& _out;
    bibParser* _bpP;
    const QChar _space_char;
    int _nerrors;
    settings* _settingsP;

    QMap<QString, KeysentenceData> _keysentences;
    QMultiMap<int, QString> _document_sentences;
    QMultiMap<int, int> _document_sentenceids;
};

#endif
