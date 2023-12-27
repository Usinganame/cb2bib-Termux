/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BCITERMODEL_H
#define C2BCITERMODEL_H

#include "c2bCiter.h"
#include "c2bCiterHistory.h"

#include <collectionAnalyzer.h>

#include <QAbstractTableModel>
#include <QColor>
#include <QHash>
#include <QStringList>
#include <QVector>


class c2bCiterModel : public QAbstractTableModel
{

    Q_OBJECT

public:
    explicit c2bCiterModel(QObject* parento = 0);
    inline ~c2bCiterModel() {}

    QList<int> sizeHintForColumns() const;
    QStringList dataSelectedCiteIds() const;
    QVariant data(const QModelIndex& i, int role = Qt::DisplayRole) const;
    c2bCiter::State currentState(const QModelIndex& current_index) const;
    void clearCurrentFilter(QModelIndex* current_index);
    void clearSelection();
    void loadCitations(const QString& fn);
    void loadCitations(const QStringList& fns);
    void reloadCitations(const QStringList& fns, const c2bCiter::State& state, QModelIndex* current_index);
    void restoreNextState(QModelIndex* current_index);
    void restorePreviousState(QModelIndex* current_index);
    void restoreState(const c2bCiter::State& s, QModelIndex* current_index);
    void setDocumentFilter(const QString& documentfn, QModelIndex* current_index);
    void setGlossaryView(QModelIndex* current_index);
    void setKeywordFilter(const QString& keyword, QModelIndex* current_index);
    void setPatternFilter(const QString& pattern, QModelIndex* current_index, const c2bCiter::Format format);
    void setRelatedFilter(const QString& documentfn, QModelIndex* current_index,
                          const c2bCiter::Format format = c2bCiter::R);
    void setSelectedFilter(QModelIndex* current_index);
    void updateFormat(const c2bCiter::Format format, QModelIndex* current_index);

    inline QString dataBibTeXPosition(const QModelIndex& i) const
    {
        if (_is_index_valid(i))
            return _bibtex_position.at(_offset(i.row()));
        else
            return QString();
    }
    inline QString dataBibTeXFile(const QModelIndex& i) const
    {
        return dataBibTeXPosition(i).remove(QRegExp(":(\\d+)$"));
    }
    inline QString dataFile(const QModelIndex& i) const
    {
        if (_is_index_valid(i))
            return _file.key(_offset(i.row()));
        else
            return QString();
    }
    inline QString dataUrl(const QModelIndex& i) const
    {
        if (_is_index_valid(i))
            return _url.at(_offset(i.row()));
        else
            return QString();
    }
    inline QString dataKeyword(const QModelIndex& i) const
    {
        if (_format == c2bCiter::K && _is_index_valid(i))
            return _analyzer.sentence(_offset(i.row()));
        else
            return QString();
    }
    inline c2bCiter::KeywordData keywordData(const QModelIndex& i) const
    {
        c2bCiter::KeywordData kd;
        if (_filter == c2bCiter::Document && _format == c2bCiter::K)
        {
            kd.bibtexfn = QString(_bibtex_position.at(_file.value(_fstring))).remove(QRegExp(":(\\d+)$"));
            kd.documentfn = _fstring;
            kd.keyword = dataKeyword(i);
        }
        else if (_filter == c2bCiter::Keyword)
        {
            kd.bibtexfn = dataBibTeXFile(i);
            kd.documentfn = dataFile(i);
            kd.keyword = _fstring;
        }
        kd.valid = !kd.bibtexfn.isEmpty() && !kd.documentfn.isEmpty() && !kd.keyword.isEmpty();
        return kd;
    }
    inline bool isKeywordView() const
    {
        return _format == c2bCiter::K;
    }
    inline Qt::ItemFlags flags(const QModelIndex& /* i */) const
    {
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    }
    inline int count() const
    {
        return _row_count;
    }
    inline int rowCount(const QModelIndex& /* parent */ = QModelIndex()) const
    {
        return _row_count;
    }
    inline int columnCount(const QModelIndex& /* parent */ = QModelIndex()) const
    {
        return _column_count;
    }
    inline c2bCiter::Filter currentFilter() const
    {
        return _filter;
    }
    inline c2bCiter::Format currentFormat() const
    {
        return _format;
    }
    inline c2bCiter::Format lastCitationFormat() const
    {
        return _history.lastCitationFormat();
    }
    inline void restoreLastNonKeywordState(QModelIndex* current_index)
    {
        restoreState(_history.lastNonKeywordState(), current_index);
    }
    inline void restoreLastNonSelectedState(QModelIndex* current_index)
    {
        restoreState(_history.lastNonSelectedState(), current_index);
    }


public slots:
    void selectCitation(const QModelIndex& i);


signals:
    void patternFilterChanged(const QString& pattern);
    void statusLabel(const QString& label);
    void statusMessage(const QString& message);


private:
    Q_DISABLE_COPY(c2bCiterModel)

    QColor _first_column_color;
    QString _display_ajyt(const int row, const int column) const;
    QString _display_it(const int row, const int column) const;
    QString _display_jya(const int row, const int column) const;
    QString _display_k(const int row, const int column) const;
    QString _display_r(const int row, const int column) const;
    QString _display_t(const int row, const int column) const;
    QString _display_yajt(const int row, const int column) const;
    QString(c2bCiterModel::*_display_ptr)(const int row, const int column) const;
    int _current_item(const QString& index_data) const;
    int _offset(const int i) const;
    void _add_citations(const QString& fn);
    void _clear();
    void _set_mapping();
    void _set_sort_indices();
    void _set_table_data();
    void _update_current_index(const int current_item, QModelIndex* current_index) const;
    void _update_format(const c2bCiter::Format format = c2bCiter::AJYT);

    inline bool _is_index_valid(const QModelIndex& i) const
    {
        const int r(i.row());
        return _row_count > 0 && r >= 0 && r < _row_count;
    }
    inline int _current_item(const QModelIndex& current_index) const
    {
        return _is_index_valid(current_index) ? _offset(current_index.row()) : -1;
    }
    inline int _current_item(const QModelIndex* const current_index) const
    {
        return current_index ? _current_item(*current_index) : -1;
    }

    // Collection analyzer helper
    collectionAnalyzer _analyzer;

    // History helper
    QString _fstring;
    c2bCiter::Filter _filter;
    c2bCiter::Format _format;
    c2bCiterHistory _history;

    // Model data
    QHash<QString, int> _file;
    QList<uint> _included_date;
    QStringList _author_string;
    QStringList _bibtex_position;
    QStringList _citeId;
    QStringList _journal;
    QStringList _title;
    QStringList _url;
    QStringList _year;
    QVector<QString> _author;
    QVector<QString> _search_string;
    QVector<bool> _is_selected;
    QVector<bool> _matches_filter;
    QVector<int> _map_ajyt;
    QVector<int> _map_author;
    QVector<int> _map_filter;
    QVector<int> _map_it;
    QVector<int> _map_jya;
    QVector<int> _map_t;
    QVector<int> _map_yajt;
    QVector<int>* _mapping;
    int _author_count;
    int _author_max_length;
    int _citation_count;
    int _column_count;
    int _journal_max_length;
    int _keyword_count;
    int _related_count;
    int _row_count;
};

#endif
