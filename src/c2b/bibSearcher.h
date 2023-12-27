/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef BIBSEARCHER_H
#define BIBSEARCHER_H

#include "documentCache.h"
#include "searchPattern.h"

#include <QObject>
#include <QStringList>


class bibParser;
class bibReference;


class bibSearcher : public QObject
{

    Q_OBJECT

public:
    explicit bibSearcher(bibParser* bp, QObject* parento = 0);
    bibSearcher(bibParser* bp, const QString& bib_dir, QObject* parento = 0);
    inline ~bibSearcher() {}

    static QString searchDocumentKeyword(const QString& bibtexfn, const QString& documentfn, const QString& keyword);

    void addPattern(bool Not, bool caseSensitive, const QString& patternType, const QString& scope,
                    const QChar& yearScope, const QString& pattern);
    void clear();
    void exec();

    inline void setBoolean(bool AND)
    {
        _boolean_and = AND;
    }
    inline void setSearchScope(const QString& file, const QString& dir, bool all, bool documents)
    {
        _bibtex_file = file;
        _bibtex_dir = dir;
        _all_bibtex_files = all;
        _include_documents = documents;
    }
    inline void setSimplifySource(bool simplify)
    {
        _simplify_source = simplify;
    }
    inline int errorsCount() const
    {
        return _error_counter;
    }
    inline int hitsCount() const
    {
        return _result_references.count();
    }
    inline QString hitsString() const
    {
        return _result_string;
    }
    inline QString hitHtmlDatum(const int index) const
    {
        return index < _result_html_data.count() ? _result_html_data.at(index) : QString();
    }
    inline QString hitHtmlAbstract(const int index) const
    {
        return index < _result_html_abstracts.count() ? _result_html_abstracts.at(index) : QString();
    }
    inline int patternsCount() const
    {
        return _patterns.count();
    }
    inline int referencesCount() const
    {
        return _reference_counter;
    }
    inline QString logString() const
    {
        return _log_string;
    }
    inline bool isSearchSimilar() const
    {
        return _do_search_similar;
    }


public slots:
    void abort();


private:
    bibSearcher();


    QString excerpts(const QString& contents);
    QString highlight(const QString& abstract);
    QString location(const QString& fn, const bibReference& ref) const;
    void search(const QString& bib_file);
    void searchReference(const QString& bib_file, const bibReference& ref);
    void searchSimilarReferences(const QString& bib_file, const bibReference& ref);
    void setTitleRank(const QString& title);

    template <typename T1, typename T2, typename T3, typename T4>
    void quadrupleSortDescending(int start, int end, T1* v1, T2* v2, T3* v3, T4* v4)
    {
        // Template quadrupleSortDescending was adapted from qSortHelper by Pere Constans.
        // qSortHelper is copyrighted by
        // (C) 2011 Nokia Corporation and/or its subsidiary(-ies),
        // and released under GLP/LGPL license.
top:
        int span = end - start;
        if (span < 2)
            return;
        --end;
        int low = start;
        int high = end - 1;
        int pivot = start + span / 2;
        if (v1->at(end) > v1->at(start))
        {
            std::swap((*v1)[end], (*v1)[start]);
            std::swap((*v2)[end], (*v2)[start]);
            std::swap((*v3)[end], (*v3)[start]);
            std::swap((*v4)[end], (*v4)[start]);
        }
        if (span == 2)
            return;
        if (v1->at(pivot) > v1->at(start))
        {
            std::swap((*v1)[pivot], (*v1)[start]);
            std::swap((*v2)[pivot], (*v2)[start]);
            std::swap((*v3)[pivot], (*v3)[start]);
            std::swap((*v4)[pivot], (*v4)[start]);
        }
        if (v1->at(end) > v1->at(pivot))
        {
            std::swap((*v1)[end], (*v1)[pivot]);
            std::swap((*v2)[end], (*v2)[pivot]);
            std::swap((*v3)[end], (*v3)[pivot]);
            std::swap((*v4)[end], (*v4)[pivot]);
        }
        if (span == 3)
            return;
        std::swap((*v1)[pivot], (*v1)[end]);
        std::swap((*v2)[pivot], (*v2)[end]);
        std::swap((*v3)[pivot], (*v3)[end]);
        std::swap((*v4)[pivot], (*v4)[end]);
        while (low < high)
        {
            while (low < high && v1->at(low) > v1->at(end))
                ++low;
            while (high > low && v1->at(end) > v1->at(high))
                --high;
            if (low < high)
            {
                std::swap((*v1)[low], (*v1)[high]);
                std::swap((*v2)[low], (*v2)[high]);
                std::swap((*v3)[low], (*v3)[high]);
                std::swap((*v4)[low], (*v4)[high]);
                ++low;
                --high;
            }
            else
                break;
        }
        if (v1->at(low) > v1->at(end))
            ++low;
        std::swap((*v1)[end], (*v1)[low]);
        std::swap((*v2)[end], (*v2)[low]);
        std::swap((*v3)[end], (*v3)[low]);
        std::swap((*v4)[end], (*v4)[low]);
        quadrupleSortDescending(start, low, v1, v2, v3, v4);
        start = low + 1;
        ++end;
        goto top;
    }
    template <typename T1, typename T2, typename T3, typename T4>
    void quadrupleSortDescending(T1* v1, T2* v2, T3* v3, T4* v4)
    {
        const int n(v1->size());
        if (n != v2->size() && n != v3->size() && n != v4->size())
            c2bUtils::warn(tr("Invalid array dimensions at quadrupleSortDescending"));
        else
            quadrupleSortDescending(0, n, v1, v2, v3, v4);
    }

    QList<double> _result_scores;
    QString _result_string;
    QStringList _result_html_abstracts;
    QStringList _result_html_data;
    QStringList _result_references;

    QList<searchPattern> _patterns;
    QString _bibtex_dir;
    QString _bibtex_file;
    QString _do_search_similar_citeid;
    QString _log_string;
    QStringList _scopes;
    bibParser* _bpP;
    bool _aborted;
    bool _all_bibtex_files;
    bool _boolean_and;
    bool _include_documents;
    bool _simplify_source;
    documentCache _documents;
    double _reference_score;
    int _bibtex_counter;
    int _document_counter;
    int _error_counter;
    int _reference_counter;
    int _reference_match_counter;

    const bool _do_rank_results;
    const bool _do_search_similar;
};

#endif
