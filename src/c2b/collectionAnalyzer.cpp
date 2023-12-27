/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "collectionAnalyzer.h"

#include "settings.h"

#include <QDataStream>
#include <QVector>

#include <cmath>

namespace
{

template <typename T>
class lengthsorting
{
public:
    explicit lengthsorting(const T& data) : _data(data) {}
    inline bool operator()(const int i, const int j)
    {
        const int ni(_data[i].length());
        const int nj(_data[j].length());
        if (ni == nj)
            return _data[i] < _data[j];
        else
            return ni < nj;
    }

private:
    const T& _data;
};

// Template double_sort was adapted from qSortHelper by Pere Constans.
// qSortHelper is copyrighted by
// (C) 2011 Nokia Corporation and/or its subsidiary(-ies),
// and released under GLP/LGPL license.
template <typename T1, typename T2>
void double_sort(int start, int end, T1* v1, T2* v2)
{
top:
    int span = end - start;
    if (span < 2)
        return;
    --end;
    int low = start;
    int high = end - 1;
    int pivot = start + span / 2;
    if ((*v1)[end] > (*v1)[start])
    {
        std::swap((*v1)[end], (*v1)[start]);
        std::swap((*v2)[end], (*v2)[start]);
    }
    if (span == 2)
        return;
    if ((*v1)[pivot] > (*v1)[start])
    {
        std::swap((*v1)[pivot], (*v1)[start]);
        std::swap((*v2)[pivot], (*v2)[start]);
    }
    if ((*v1)[end] > (*v1)[pivot])
    {
        std::swap((*v1)[end], (*v1)[pivot]);
        std::swap((*v2)[end], (*v2)[pivot]);
    }
    if (span == 3)
        return;
    std::swap((*v1)[pivot], (*v1)[end]);
    std::swap((*v2)[pivot], (*v2)[end]);
    while (low < high)
    {
        while (low < high && (*v1)[low] > (*v1)[end])
            ++low;
        while (high > low && (*v1)[end] > (*v1)[high])
            --high;
        if (low < high)
        {
            std::swap((*v1)[low], (*v1)[high]);
            std::swap((*v2)[low], (*v2)[high]);
            ++low;
            --high;
        }
        else
            break;
    }
    if ((*v1)[low] > (*v1)[end])
        ++low;
    std::swap((*v1)[end], (*v1)[low]);
    std::swap((*v2)[end], (*v2)[low]);
    double_sort(start, low, v1, v2);
    start = low + 1;
    ++end;
    goto top;
}

} // namespace


collectionAnalyzer::collectionAnalyzer()
    : _ndocuments(0), _nsentences(0), _nsimilar(0), _settingsP(settings::instance()) {}


void collectionAnalyzer::reload()
{
    _ndocuments = 0;
    _nsentences = 0;
    _nsimilar = 0;
    _document_keyword.clear();
    _keyword_document_fn.clear();
    _similar_document_fn.clear();
    const QString cache_dir(_settingsP->fileName("cb2Bib/CacheDirectory"));

    _documentslf_fn = QDir::cleanPath(cache_dir + "/documents.lc2b");
    QFile documentslf(_documentslf_fn);
    if (documentslf.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&documentslf);
        stream >> _ndocuments;
        _documents.resize(_ndocuments);
        for (int i = 0; i < _ndocuments; ++i)
            stream >> _documents[i];
        documentslf.close();
    }
    _similar.resize(_ndocuments);
    _similarity.resize(_ndocuments);

    _sentenceslf_fn = QDir::cleanPath(cache_dir + "/sentences.lc2b");
    QFile sentenceslf(_sentenceslf_fn);
    if (sentenceslf.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&sentenceslf);
        stream >> _nsentences;
        _sentences.resize(_nsentences);
        for (int i = 0; i < _nsentences; ++i)
            stream >> _sentences[i];
        sentenceslf.close();
    }

    _documentsif_fn = QDir::cleanPath(cache_dir + "/documents.ic2b");
    QFile documentsif(_documentsif_fn);
    if (documentsif.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&documentsif);
        _document_norms.resize(_ndocuments);
        int ns;
        int ss;
        for (int d = 0; d < _ndocuments; ++d)
        {
            stream >> ns;
            _document_norms[d] = ns;
            for (int s = 0; s < ns; ++s)
                stream >> ss;
        }
        documentsif.close();
    }

    _sentencesif_fn = QDir::cleanPath(cache_dir + "/sentences.ic2b");
}

void collectionAnalyzer::setDocumentKeywords(const QString& documentfn)
{
    if (documentfn == _keyword_document_fn)
        return;
    _keyword_document_fn = documentfn;
    _document_keyword_ids.clear();

    QVector<int> dsentences;
    grepDocuments(documentfn, &dsentences);
    const int ndsentences(dsentences.size());
    if (ndsentences == 0)
        return;

    lengthsorting<QVarLengthArray<QString>> ls(_sentences);
    std::sort(dsentences.begin(), dsentences.end(), ls);

    for (int i = 0; i < ndsentences; ++i)
    {
        const QString& si(_sentences[dsentences.at(i)]);
        bool redundant(false);
        for (int j = i + 1; j < ndsentences; ++j)
            if (_sentences[dsentences.at(j)].contains(si))
            {
                redundant = true;
                break;
            }
        if (!redundant)
            _document_keyword_ids.append(dsentences.at(i));
    }
    std::sort(_document_keyword_ids.begin(), _document_keyword_ids.end());
}

void collectionAnalyzer::setKeywordDocuments(const QString& keyword)
{
    if (keyword == _document_keyword)
        return;
    _document_keyword = keyword;

    grepSentences(keyword, &_sdocuments);
}

void collectionAnalyzer::setSimilarDocuments(const QString& documentfn)
{
    if (documentfn == _similar_document_fn)
        return;
    _similar_document_fn = documentfn;
    _nsimilar = 0;

    QVector<int> dsentences;
    grepDocuments(documentfn, &dsentences);
    const int ndsentences(dsentences.size());
    if (ndsentences == 0)
        return;

    QVarLengthArray<int> overlaps(_ndocuments);
    for (int i = 0; i < _ndocuments; ++i)
        overlaps[i] = 0;

    QFile sentencesif(_sentencesif_fn);
    if (sentencesif.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&sentencesif);
        int nd;
        int dd;
        int s0(0);
        for (int i = 0; i < ndsentences; ++i)
        {
            const int sentenceid(dsentences[i]);
            for (int s = s0; s < sentenceid; ++s)
            {
                stream >> nd;
                for (int d = 0; d < nd; ++d)
                    stream >> dd;
            }
            stream >> nd;
            for (int d = 0; d < nd; ++d)
            {
                stream >> dd;
                overlaps[dd] += 1;
            }
            s0 = sentenceid + 1;
        }
        sentencesif.close();
    }

    const int documentid(_document_id(documentfn));
    for (int i = 0; i < _ndocuments; ++i)
    {
        const int o(overlaps[i]);
        if (o == 0)
            continue;
        const double s(double(o) / sqrt(double(_document_norms[documentid] * _document_norms[i])));
        if (s < 0.051)
            continue;
        _similarity[_nsimilar] = s;
        _similar[_nsimilar++] = i;
    }

    double_sort(0, _nsimilar, &_similarity, &_similar);
}

void collectionAnalyzer::skipSimilarDocument(const int i)
{
    --_nsimilar;
    for (int j = i; j < _nsimilar; ++j)
        _similarity[j] = _similarity[j + 1];
    for (int j = i; j < _nsimilar; ++j)
        _similarity[j] = _similarity[j + 1];
}

void collectionAnalyzer::grepDocuments(const QString& documentfn, QVector<int>* dsentences) const
{
    dsentences->clear();
    const int documentid(_document_id(documentfn));
    if (documentid == -1)
        return;

    QFile documentsif(_documentsif_fn);
    if (documentsif.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&documentsif);
        int ns;
        int ss;
        for (int d = 0; d < documentid; ++d)
        {
            stream >> ns;
            for (int s = 0; s < ns; ++s)
                stream >> ss;
        }
        stream >> ns;
        dsentences->resize(ns);
        for (int s = 0; s < ns; ++s)
            stream >> (*dsentences)[s];
        documentsif.close();
    }
}

void collectionAnalyzer::grepSentences(const QString& keyword, QVarLengthArray<int>* sdocuments) const
{
    sdocuments->clear();
    const int sentenceid(_sentence_id(keyword));
    if (sentenceid == -1)
        return;

    QFile sentencesif(_sentencesif_fn);
    if (sentencesif.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&sentencesif);
        int nd;
        int dd;
        for (int s = 0; s < sentenceid; ++s)
        {
            stream >> nd;
            for (int d = 0; d < nd; ++d)
                stream >> dd;
        }
        stream >> nd;
        sdocuments->resize(nd);
        for (int d = 0; d < nd; ++d)
            stream >> (*sdocuments)[d];
        sentencesif.close();
    }
}

int collectionAnalyzer::_document_id(const QString& documentfn) const
{
    for (int i = 0; i < _ndocuments; ++i)
        if (_documents[i] == documentfn)
            return i;
    return -1;
}

int collectionAnalyzer::_sentence_id(const QString& keyword) const
{
    for (int i = 0; i < _nsentences; ++i)
        if (_sentences[i] == keyword)
            return i;
    return -1;
}
