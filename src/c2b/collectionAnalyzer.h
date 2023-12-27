/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef COLLECTIONANALYZER_H
#define COLLECTIONANALYZER_H

#include <QStringList>
#include <QVarLengthArray>


class settings;


class collectionAnalyzer
{

public:
    collectionAnalyzer();
    inline ~collectionAnalyzer() {}

    void reload();
    void setDocumentKeywords(const QString& documentfn);
    void setKeywordDocuments(const QString& keyword);
    void setSimilarDocuments(const QString& documentfn);
    void skipSimilarDocument(const int i);

    inline int similarCount() const
    {
        return _nsimilar;
    }
    inline const QString& similar(const int i) const
    {
        return _documents[_similar[i]];
    }
    inline const QVarLengthArray<double>& similarity() const
    {
        return _similarity;
    }
    inline double similarity(const int i) const
    {
        return _similarity[i];
    }
    inline int sentenceCount() const
    {
        return _sentences.size();
    }
    inline const QString& sentence(const int i) const
    {
        return _sentences[i];
    }
    inline int keywordCount() const
    {
        return _document_keyword_ids.size();
    }
    inline int keywordid(const int i) const
    {
        return _document_keyword_ids.at(i);
    }
    inline int documentCount() const
    {
        return _sdocuments.size();
    }
    inline const QString& document(const int i) const
    {
        return _documents[_sdocuments[i]];
    }


private:
    int _document_id(const QString& documentfn) const;
    int _sentence_id(const QString& keyword) const;
    void grepDocuments(const QString& documentfn, QVector<int>* dsentences) const;
    void grepSentences(const QString& keyword, QVarLengthArray<int>* sdocuments) const;

    QList<int> _document_keyword_ids;
    QString _document_keyword;
    QString _documentsif_fn;
    QString _documentslf_fn;
    QString _keyword_document_fn;
    QString _sentencesif_fn;
    QString _sentenceslf_fn;
    QString _similar_document_fn;
    QVarLengthArray<QString> _documents;
    QVarLengthArray<QString> _sentences;
    QVarLengthArray<double> _similarity;
    QVarLengthArray<int> _sdocuments;
    QVarLengthArray<int> _similar;
    QVarLengthArray<ushort> _document_norms;

    int _ndocuments;
    int _nsentences;
    int _nsimilar;
    settings* _settingsP;
};

#endif
