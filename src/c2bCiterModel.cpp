/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bCiterModel.h"

#include <bibParser.h>

#include "c2b.h"

#include <QDateTime>
#include <QIcon>

namespace
{

template <typename T>
class ascending
{
public:
    explicit ascending(const T& data) : _data(data) {}
    inline bool operator()(const int i, const int j)
    {
        return _data.at(i) < _data.at(j);
    }

private:
    const T& _data;
};

} // namespace


c2bCiterModel::c2bCiterModel(QObject* parento) : QAbstractTableModel(parento)
{
    _first_column_color = QApplication::palette().color(QPalette::Active, QPalette::Base).darker(110);
    _clear();
}


void c2bCiterModel::loadCitations(const QStringList& fns)
{
    emit layoutAboutToBeChanged();
    _clear();
    _analyzer.reload();
    for (int i = 0; i < fns.count(); ++i)
        _add_citations(fns.at(i));
    _set_table_data();
    _set_sort_indices();
    _update_format();
    emit layoutChanged();
    emit statusMessage(tr("Loaded %1 references from %2 files.").arg(_citation_count).arg(fns.count()));
}

void c2bCiterModel::loadCitations(const QString& fn)
{
    emit layoutAboutToBeChanged();
    _clear();
    _analyzer.reload();
    _add_citations(fn);
    _set_table_data();
    _set_sort_indices();
    _update_format();
    emit layoutChanged();
    emit statusMessage(tr("Loaded %1 references.").arg(_citation_count));
}

void c2bCiterModel::reloadCitations(const QStringList& fns, const c2bCiter::State& state, QModelIndex* current_index)
{
    emit layoutAboutToBeChanged();
    _clear();
    _analyzer.reload();
    for (int i = 0; i < fns.count(); ++i)
        _add_citations(fns.at(i));
    _set_table_data();
    _set_sort_indices();
    _update_format(state.format);
    const int current_item(_current_item(state.index_data));
    _update_current_index(current_item, current_index);
    _history.saveCurrentState(_format, _filter, current_item, current_index, _fstring);
    emit layoutChanged();
    emit statusMessage(tr("Loaded %1 references from %2 files.").arg(_citation_count).arg(fns.count()));
}

QVariant c2bCiterModel::data(const QModelIndex& i, int role) const
{
    if (role == Qt::DisplayRole)
        return (this->*_display_ptr)(i.row(), i.column());
    else if (role == Qt::DecorationRole)
    {
        if (_format == c2bCiter::K && i.column() == 0)
            return QVariant(QIcon(":/icons/icons/bullet.png"));
        if (i.column() == 0)
        {
            if (_is_selected.at(_offset(i.row())))
                return QVariant(QIcon(":/icons/icons/citer_citation_checked.png"));
            else
                return QVariant(QIcon(":/icons/icons/citer_citation.png"));
        }
        return QVariant();
    }
    else if (role == Qt::BackgroundRole)
    {
        if (i.column() == 0 && _column_count > 1 && _format != c2bCiter::K)
            return _first_column_color;
        else
            return QVariant();
    }
    else
        return QVariant();
}

QStringList c2bCiterModel::dataSelectedCiteIds() const
{
    QStringList ids;
    for (int i = 0; i < _citation_count; ++i)
        if (_is_selected.at(_map_yajt.at(i)))
            ids.append(_citeId.at(_map_yajt.at(i)));
    return ids;
}

void c2bCiterModel::setPatternFilter(const QString& pattern, QModelIndex* current_index, const c2bCiter::Format format)
{
    _history.saveCurrentState(_format, _filter, _current_item(current_index), current_index, _fstring);
    emit layoutAboutToBeChanged();
    const QStringList word(pattern.split(c2bUtils::nonLetter, QString::SkipEmptyParts));
    _filter = word.count() > 0 ? c2bCiter::Pattern : c2bCiter::None;
    _format = format;
    if (_filter == c2bCiter::Pattern)
    {
        _fstring = pattern;
        if (_format == c2bCiter::K)
        {
            int j(0);
            for (int i = 0; i < _keyword_count; ++i)
            {
                const QString& str = _analyzer.sentence(i);
                bool mf(true);
                for (int w = 0; w < word.count(); ++w)
                    if (!str.contains(word.at(w), Qt::CaseSensitive))
                    {
                        mf = false;
                        break;
                    }
                if (mf)
                    _map_filter[j++] = i;
            }
            _row_count = j;
        }
        else
        {
            for (int i = 0; i < _citation_count; ++i)
            {
                _matches_filter[i] = true;
                const QString& str = _search_string.at(i);
                for (int w = 0; w < word.count(); ++w)
                    if (!str.contains(word.at(w), Qt::CaseSensitive))
                    {
                        _matches_filter[i] = false;
                        break;
                    }
            }
        }
    }
    else
        _fstring.clear();
    _update_format(_format == c2bCiter::R ? _history.lastCitationFormat() : _format);
    _update_current_index(_format == c2bCiter::K ? _history.lastKeyword() : _history.lastCitation(), current_index);
    emit layoutChanged();
}

void c2bCiterModel::setSelectedFilter(QModelIndex* current_index)
{
    emit statusLabel(tr("Selected"));
    _history.saveCurrentState(_format, _filter, _current_item(current_index), current_index, _fstring);
    emit layoutAboutToBeChanged();
    for (int i = 0; i < _citation_count; ++i)
        _matches_filter[i] = _is_selected.at(i);
    _filter = c2bCiter::Selected;
    _fstring.clear();
    _update_format(_history.lastCitationFormat());
    _update_current_index(_history.lastSelectionCitation(), current_index);
    emit layoutChanged();
}

void c2bCiterModel::setRelatedFilter(const QString& documentfn, QModelIndex* current_index,
                                     const c2bCiter::Format format)
{
    _analyzer.setSimilarDocuments(documentfn);
    if (_analyzer.similarCount() == 0)
    {
        emit statusMessage(tr("No related references."));
        return;
    }
    emit statusLabel(tr("Related to '%1'").arg(_title.at(_file.value(documentfn))));
    _history.saveCurrentState(_format, _filter, _current_item(current_index), current_index, _fstring);
    emit layoutAboutToBeChanged();
    for (int i = 0; i < _citation_count; ++i)
        _matches_filter[i] = false;
    const int sc(_analyzer.similarCount());
    _related_count = 0;
    for (int i = 0; i < sc; ++i)
    {
        // Note that data in collectionAnalyzer index might not match
        // BibTeX files data (outdated index or users browsing
        // particular BibTeX file sets). Use full path document
        // filenames to set a mapping.
        const int j(_file.value(_analyzer.similar(i), -1));
        if (j == -1)
        {
            _analyzer.skipSimilarDocument(i);
            continue;
        }
        _matches_filter[j] = true;
        _map_filter[i] = j;
        ++_related_count;
    }
    _filter = c2bCiter::Related;
    _fstring = documentfn;
    _update_format(format);
    _update_current_index(_history.lastCitation(), current_index);
    emit layoutChanged();
}

void c2bCiterModel::setKeywordFilter(const QString& keyword, QModelIndex* current_index)
{
    _analyzer.setKeywordDocuments(keyword);
    if (_analyzer.documentCount() == 0)
    {
        emit statusMessage(tr("No related references."));
        return;
    }
    emit statusLabel(tr("Related to '%1'").arg(keyword));
    _history.saveCurrentState(_format, _filter, _current_item(current_index), current_index, _fstring);
    emit layoutAboutToBeChanged();
    for (int i = 0; i < _citation_count; ++i)
        _matches_filter[i] = false;
    const int dc(_analyzer.documentCount());
    for (int i = 0; i < dc; ++i)
    {
        // See comment at c2bCiterModel::setRelatedFilter
        const int j(_file.value(_analyzer.document(i), -1));
        if (j == -1)
            continue;
        _matches_filter[j] = true;
    }
    _filter = c2bCiter::Keyword;
    _fstring = keyword;
    _update_format(_history.lastCitationFormat());
    _update_current_index(_history.lastKeyword(), current_index);
    emit layoutChanged();
}

void c2bCiterModel::setDocumentFilter(const QString& documentfn, QModelIndex* current_index)
{
    _analyzer.setDocumentKeywords(documentfn);
    const int nk(_analyzer.keywordCount());
    if (nk == 0)
    {
        emit statusMessage(tr("No keywords from this reference."));
        return;
    }
    emit statusLabel(tr("Keywords from '%1'").arg(_title.at(_file.value(documentfn))));
    _history.saveCurrentState(_format, _filter, _current_item(current_index), current_index, _fstring);
    emit layoutAboutToBeChanged();
    int j(0);
    for (int i = 0; i < nk; ++i)
        _map_filter[j++] = _analyzer.keywordid(i);
    _row_count = j;
    _filter = c2bCiter::Document;
    _fstring = documentfn;
    _update_format(c2bCiter::K);
    _update_current_index(_history.lastKeyword(), current_index);
    emit layoutChanged();
}

void c2bCiterModel::setGlossaryView(QModelIndex* current_index)
{
    _history.saveCurrentState(_format, _filter, _current_item(current_index), current_index, _fstring);
    emit layoutAboutToBeChanged();
    _filter = c2bCiter::None;
    _fstring.clear();
    _update_format(c2bCiter::K);
    _update_current_index(_history.lastKeyword(), current_index);
    emit patternFilterChanged(_fstring);
    emit layoutChanged();
}

void c2bCiterModel::selectCitation(const QModelIndex& i)
{
    if (_format == c2bCiter::K)
        return;
    _is_selected[_offset(i.row())] = !_is_selected.at(_offset(i.row()));
    emit layoutChanged();
}

QList<int> c2bCiterModel::sizeHintForColumns() const
{
    QList<int> sizes;
    switch (_format)
    {
    case c2bCiter::AJYT:
        sizes.append(std::min(20, _author_max_length + 2));
        sizes.append(20);
        sizes.append(6);
        sizes.append(100);
        break;
    case c2bCiter::IT:
        sizes.append(12);
        sizes.append(100);
        break;
    case c2bCiter::JYA:
        sizes.append(std::min(25, _journal_max_length));
        sizes.append(6);
        sizes.append(100);
        break;
    case c2bCiter::K:
        sizes.append(100);
        break;
    case c2bCiter::R:
        sizes.append(9);
        sizes.append(100);
        break;
    case c2bCiter::T:
        sizes.append(100);
        break;
    case c2bCiter::YAJT:
    default:
        sizes.append(8);
        sizes.append(75);
        sizes.append(25);
        sizes.append(100);
        break;
    }
    return sizes;
}

void c2bCiterModel::clearSelection()
{
    emit layoutAboutToBeChanged();
    for (int i = 0; i < _citation_count; ++i)
        _is_selected[i] = false;
    emit layoutChanged();
}

void c2bCiterModel::clearCurrentFilter(QModelIndex* current_index)
{
    if (_filter == c2bCiter::None)
        return;
    if (_filter != c2bCiter::Pattern && _history.lastState().filter == c2bCiter::Pattern)
    {
        const c2bCiter::State& s(_history.lastState());
        setPatternFilter(s.filter_string, current_index, s.format);
        emit patternFilterChanged(s.filter_string);
    }
    else
    {
        _history.saveCurrentState(_format, _filter, _current_item(current_index), current_index, _fstring);
        emit layoutAboutToBeChanged();
        _filter = c2bCiter::None;
        _fstring.clear();
        _update_format(_format == c2bCiter::R ? _history.lastCitationFormat() : _format);
        _update_current_index(_format == c2bCiter::K ? _history.lastKeyword() : _history.lastCitation(), current_index);
        emit patternFilterChanged(_fstring);
        emit layoutChanged();
    }
}

c2bCiter::State c2bCiterModel::currentState(const QModelIndex& current_index) const
{
    const int current_item(_current_item(current_index));
    c2bCiter::State s(_format == c2bCiter::R ? _history.lastCitationFormat() : _format, _filter, current_index.row(),
                      _fstring);
    if (current_item > -1)
        s.index_data = (_format == c2bCiter::K) ? _analyzer.sentence(current_item) : _search_string.at(current_item);
    return s;
}

void c2bCiterModel::restoreState(const c2bCiter::State& s, QModelIndex* current_index)
{
    if (current_index)
        _history.saveCurrentItemIndex(_format, _filter, _current_item(current_index));
    switch (s.filter)
    {
    case c2bCiter::None:
        emit layoutAboutToBeChanged();
        _filter = c2bCiter::None;
        _fstring.clear();
        _update_format(s.format);
        emit patternFilterChanged(_fstring);
        emit layoutChanged();
        break;
    case c2bCiter::Document:
        if (_file.contains(s.filter_string))
            emit statusLabel(tr("Keywords from '%1'").arg(_title.at(_file.value(s.filter_string))));
        setDocumentFilter(s.filter_string, 0);
        break;
    case c2bCiter::Keyword:
        setKeywordFilter(s.filter_string, 0);
        break;
    case c2bCiter::Pattern:
        setPatternFilter(s.filter_string, 0, s.format);
        emit patternFilterChanged(s.filter_string);
        break;
    case c2bCiter::Related:
        setRelatedFilter(s.filter_string, 0, s.format);
        break;
    case c2bCiter::Selected:
        emit statusLabel(tr("Selected"));
        setSelectedFilter(0);
        break;
    default:
        break;
    }
    if (current_index)
        *current_index = index(s.viewer_index, 0);
}

void c2bCiterModel::restorePreviousState(QModelIndex* current_index)
{
    if (_history.currentState() == -1)
        _history.saveCurrentState(_format, _filter, _current_item(current_index), current_index, _fstring);
    const c2bCiter::State& s(_history.previousState());
    restoreState(s, 0);
    if (current_index)
        *current_index = index(s.viewer_index, 0);
}

void c2bCiterModel::restoreNextState(QModelIndex* current_index)
{
    if (_history.currentState() == -1)
        return;
    const c2bCiter::State& s(_history.nextState());
    restoreState(s, 0);
    if (current_index)
        *current_index = index(s.viewer_index, 0);
}

void c2bCiterModel::updateFormat(const c2bCiter::Format format, QModelIndex* current_index)
{
    if (_format == c2bCiter::K)
    {
        c2bCiter::State s(_history.lastNonKeywordState());
        s.format = format;
        restoreState(s, current_index);
    }
    else
    {
        emit layoutAboutToBeChanged();
        const int current_item(_current_item(current_index));
        _update_format(format);
        _update_current_index(current_item, current_index);
        emit layoutChanged();
    }
}

void c2bCiterModel::_update_format(const c2bCiter::Format format)
{
    _format = format;
    _history.saveCurrentCitationFormat(_format);
    switch (_format)
    {
    case c2bCiter::AJYT:
        _column_count = 4;
        _display_ptr = &c2bCiterModel::_display_ajyt;
        break;
    case c2bCiter::IT:
        _column_count = 2;
        _display_ptr = &c2bCiterModel::_display_it;
        break;
    case c2bCiter::JYA:
        _column_count = 3;
        _display_ptr = &c2bCiterModel::_display_jya;
        break;
    case c2bCiter::K:
        _column_count = 1;
        _display_ptr = &c2bCiterModel::_display_k;
        break;
    case c2bCiter::R:
        _column_count = 2;
        _display_ptr = &c2bCiterModel::_display_r;
        break;
    case c2bCiter::T:
        _column_count = 1;
        _display_ptr = &c2bCiterModel::_display_t;
        break;
    case c2bCiter::YAJT:
    default:
        _column_count = 4;
        _display_ptr = &c2bCiterModel::_display_yajt;
        break;
    }
    _set_mapping();
}

int c2bCiterModel::_current_item(const QString& index_data) const
{
    int current_item(-1);
    if (!index_data.isEmpty())
    {
        if (_format == c2bCiter::K)
        {
            for (int i = 0; i < _keyword_count; ++i)
                if (index_data == _analyzer.sentence(i))
                {
                    current_item = i;
                    break;
                }
        }
        else
        {
            for (int i = 0; i < _citation_count; ++i)
                if (index_data == _search_string.at(i))
                {
                    current_item = i;
                    break;
                }
        }
    }
    return current_item;
}

void c2bCiterModel::_update_current_index(const int current_item, QModelIndex* current_index) const
{
    if (!current_index)
        return;
    if (current_item >= 0)
        for (int i = 0; i < _row_count; ++i)
            if (_offset(i) == current_item)
            {
                *current_index = index(i, 0);
                return;
            }
    *current_index = index(0, 0);
}

void c2bCiterModel::_add_citations(const QString& fn)
{
    bibParser* bpP = c2b::bibParser();
    const QString tag_author("author");
    const QString tag_booktitle("booktitle");
    const QString tag_doi("doi");
    const QString tag_editor("editor");
    const QString tag_file("file");
    const QString tag_journal("journal");
    const QString tag_title("title");
    const QString tag_url("url");
    const QString tag_year("year");
    const QString template_position("%1:%2");
    QStringList fields;
    fields.append(tag_author);
    fields.append(tag_booktitle);
    fields.append(tag_doi);
    fields.append(tag_editor);
    fields.append(tag_file);
    fields.append(tag_journal);
    fields.append(tag_title);
    fields.append(tag_url);
    fields.append(tag_year);
    bibReference ref;
    bpP->initReferenceParsing(fn, fields, &ref);
    const QRegExp initials1("\\b\\w\\b");
    const QRegExp initials2("[^\\w\\s]");
    const QString bibtex(c2bUtils::fileToString(fn));

    while (bpP->referencesIn(bibtex, &ref))
    {
        QString author(ref.anyAuthor());
        if (!author.isEmpty())
        {
            author = bpP->authorFromBibTeX(author);
            author.remove(initials1);
            author.remove(initials2);
            author.replace(" and ", ", ");
            c2bUtils::simplifyString(author);
        }

        QString title(ref.anyTitle());
        c2bUtils::cleanTitle(title, true);

        QString url(ref.value(tag_url));
        if (url.isEmpty())
        {
            const QString doi(ref.value(tag_doi));
            if (!doi.isEmpty())
            {
                if (doi.startsWith("http"))
                    url = QUrl::toPercentEncoding(doi);
                else
                    url = "https://dx.doi.org/" + QUrl::toPercentEncoding(doi);
            }
        }

        QString file(ref.value(tag_file));
        if (!file.isEmpty())
            file = QDir::cleanPath(file);

        uint included_date;
        const QFileInfo finf(file);
        if (finf.exists())
            included_date = QDateTime(finf.lastModified().date()).toTime_t();
        else
            included_date = 0;

        _author_string.append(author);
        _bibtex_position.append(template_position.arg(fn).arg(ref.positionValue));
        _citeId.append(ref.citeidName);
        _included_date.append(included_date);
        _journal.append(ref.anyJournal());
        _title.append(title);
        _url.append(url);
        _year.append(ref.value(tag_year));
        if (!file.isEmpty())
            _file.insert(file, _citation_count);

        _citation_count++;
    }
}

void c2bCiterModel::_clear()
{
    _filter = c2bCiter::None;
    _format = c2bCiter::AJYT;

    _author.clear();
    _author_string.clear();
    _bibtex_position.clear();
    _citeId.clear();
    _file.clear();
    _fstring.clear();
    _history.clear();
    _included_date.clear();
    _is_selected.clear();
    _journal.clear();
    _map_ajyt.clear();
    _map_author.clear();
    _map_filter.clear();
    _map_it.clear();
    _map_jya.clear();
    _map_t.clear();
    _map_yajt.clear();
    _matches_filter.clear();
    _search_string.clear();
    _title.clear();
    _url.clear();
    _year.clear();

    _author_count = 0;
    _author_max_length = 0;
    _citation_count = 0;
    _column_count = 0;
    _journal_max_length = 0;
    _keyword_count = 0;
    _mapping = 0;
    _related_count = 0;
    _row_count = 0;
}


/****************************************************************************

  SETTING DATA POINTERS

*****************************************************************************/

void c2bCiterModel::_set_table_data()
{
    const QString sep(", ");
    const QChar dot('.');
    for (int i = 0; i < _citation_count; ++i)
        _author_count += _author_string.at(i).count(sep) + 1;
    _author.resize(_author_count);
    _map_author.resize(_author_count);
    int ij(0);
    for (int i = 0; i < _citation_count; ++i)
    {
        const QStringList authors(_author_string.at(i).split(sep, QString::KeepEmptyParts));
        for (int j = 0; j < authors.count(); ++j)
        {
            _author[ij] = authors.at(j).trimmed();
            _map_author[ij] = i;
            _author_max_length = std::max(_author_max_length, _author.at(ij).length());
            ++ij;
        }
    }
    if (_author_count != ij)
        qFatal("c2bCiterModel::_set_table_data: Mismatch author mapping");

    bibParser* bpP = c2b::bibParser();
    for (int i = 0; i < _citation_count; ++i)
    {
        _journal[i] = bpP->abbreviatedJournal(_journal.at(i));
        _journal[i].remove(dot);
        _journal_max_length = std::max(_journal_max_length, _journal.at(i).length());
    }

    _is_selected.resize(_citation_count);
    for (int i = 0; i < _citation_count; ++i)
        _is_selected[i] = false;

    _keyword_count = _analyzer.sentenceCount();
    const int mca(std::max(_citation_count, _author_count));
    const int mcas(std::max(mca, _keyword_count));
    _matches_filter.resize(mca);
    _map_filter.resize(mcas);
}

void c2bCiterModel::_set_sort_indices()
{
    const QChar sp(' ');

    // AJYT
    // Use _search_string as temporary for sorting
    _search_string.resize(_author_count);
    for (int i = 0; i < _author_count; ++i)
    {
        const int j(_map_author.at(i));
        _search_string[i] = c2bUtils::toAscii(
                                _author.at(i) + sp + _journal.at(j) + sp + _year.at(j) + sp + _title.at(j), c2bUtils::Collation);
    }
    _map_ajyt.resize(_author_count);
    for (int i = 0; i < _author_count; ++i)
        _map_ajyt[i] = i;
    ascending<QVector<QString>> ajyt(_search_string);
    std::sort(_map_ajyt.begin(), _map_ajyt.end(), ajyt);

    // IT
    _search_string.resize(_citation_count);
    const int current_dtt(QDateTime::currentDateTime().toTime_t());
    const QString dtt("%1");
    const QChar padding('0');
    for (int i = 0; i < _citation_count; ++i)
        _search_string[i] = c2bUtils::toAscii(
                                dtt.arg(current_dtt - _included_date.at(i), 10, 10, padding) + sp + _title.at(i), c2bUtils::Collation);
    _map_it.resize(_citation_count);
    for (int i = 0; i < _citation_count; ++i)
        _map_it[i] = i;
    ascending<QVector<QString>> it(_search_string);
    std::sort(_map_it.begin(), _map_it.end(), it);

    // JYA
    for (int i = 0; i < _citation_count; ++i)
        _search_string[i] =
            c2bUtils::toAscii(_journal.at(i) + sp + _year.at(i) + sp + _author_string.at(i), c2bUtils::Collation);
    _map_jya.resize(_citation_count);
    for (int i = 0; i < _citation_count; ++i)
        _map_jya[i] = i;
    ascending<QVector<QString>> jya(_search_string);
    std::sort(_map_jya.begin(), _map_jya.end(), jya);

    // T
    for (int i = 0; i < _citation_count; ++i)
        _search_string[i] = c2bUtils::toAscii(_title.at(i), c2bUtils::Collation);
    _map_t.resize(_citation_count);
    for (int i = 0; i < _citation_count; ++i)
        _map_t[i] = i;
    ascending<QVector<QString>> t(_search_string);
    std::sort(_map_t.begin(), _map_t.end(), t);

    // YAJT
    for (int i = 0; i < _citation_count; ++i)
        _search_string[i] = c2bUtils::toAscii(
                                _year.at(i) + sp + _author_string.at(i) + sp + _journal.at(i) + sp + _title.at(i), c2bUtils::Collation);
    _map_yajt.resize(_citation_count);
    for (int i = 0; i < _citation_count; ++i)
        _map_yajt[i] = i;
    ascending<QVector<QString>> yajt(_search_string);
    std::sort(_map_yajt.begin(), _map_yajt.end(), yajt);
    // Keep _search_string for filtering
}

void c2bCiterModel::_set_mapping()
{
    switch (_format)
    {
    case c2bCiter::AJYT:
        _row_count = _author_count;
        _mapping = &_map_ajyt;
        break;
    case c2bCiter::IT:
        _row_count = _citation_count;
        _mapping = &_map_it;
        break;
    case c2bCiter::JYA:
        _row_count = _citation_count;
        _mapping = &_map_jya;
        break;
    case c2bCiter::K:
        _row_count = _filter == c2bCiter::None ? _keyword_count : _row_count;
        break;
    case c2bCiter::R:
        _row_count = _related_count;
        _mapping = &_map_filter;
        break;
    case c2bCiter::T:
        _row_count = _citation_count;
        _mapping = &_map_t;
        break;
    case c2bCiter::YAJT:
    default:
        _row_count = _citation_count;
        _mapping = &_map_yajt;
        break;
    }

    if (_filter == c2bCiter::None)
        return;
    if (_format == c2bCiter::K)
    {
        _mapping = &_map_filter;
        return;
    }
    if (_format == c2bCiter::R) // _map_filter is already set in setRelatedFilter
        return;

    int r(0);
    if (_format == c2bCiter::AJYT)
    {
        for (int i = 0; i < _row_count; ++i)
            if (_matches_filter.at(_map_author.at(_mapping->at(i))))
                _map_filter[r++] = _mapping->at(i);
    }
    else
    {
        for (int i = 0; i < _row_count; ++i)
            if (_matches_filter.at(_mapping->at(i)))
                _map_filter[r++] = _mapping->at(i);
    }
    _row_count = r;
    _mapping = &_map_filter;
}

QString c2bCiterModel::_display_ajyt(const int row, const int column) const
{
    switch (column)
    {
    case 0:
        return _author.at(_mapping->at(row));
    case 1:
        return _journal.at(_map_author.at(_mapping->at(row)));
    case 2:
        return _year.at(_map_author.at(_mapping->at(row)));
    case 3:
        return _title.at(_map_author.at(_mapping->at(row)));
    default:
        return QString();
    }
}

QString c2bCiterModel::_display_it(const int row, const int column) const
{
    switch (column)
    {
    case 0:
        return _included_date.at(_offset(row)) > 0
               ? QDateTime::fromTime_t(_included_date.at(_offset(row))).date().toString(Qt::ISODate)
               : QString();
    case 1:
        return _title.at(_offset(row));
    default:
        return QString();
    }
}

QString c2bCiterModel::_display_jya(const int row, const int column) const
{
    switch (column)
    {
    case 0:
        return _journal.at(_offset(row));
    case 1:
        return _year.at(_offset(row));
    case 2:
        return _author_string.at(_offset(row));
    default:
        return QString();
    }
}

QString c2bCiterModel::_display_k(const int row, const int column) const
{
    switch (column)
    {
    case 0:
        return _analyzer.sentence(_offset(row));
    default:
        return QString();
    }
}

QString c2bCiterModel::_display_r(const int row, const int column) const
{
    switch (column)
    {
    case 0:
        return QString("%1%").arg(100 * _analyzer.similarity(row), 3, 'f', 0);
    case 1:
        return _title.at(_offset(row));
    default:
        return QString();
    }
}

QString c2bCiterModel::_display_t(const int row, const int column) const
{
    switch (column)
    {
    case 0:
        return _title.at(_offset(row));
    default:
        return QString();
    }
}

QString c2bCiterModel::_display_yajt(const int row, const int column) const
{
    switch (column)
    {
    case 0:
        return _year.at(_offset(row));
    case 1:
        return _author_string.at(_offset(row));
    case 2:
        return _journal.at(_offset(row));
    case 3:
        return _title.at(_offset(row));
    default:
        return QString();
    }
}

int c2bCiterModel::_offset(const int i) const
{
    if (_format == c2bCiter::AJYT)
        return _map_author.at(_mapping->at(i));
    else if (_format == c2bCiter::K && _filter == c2bCiter::None)
        return i;
    else
        return _mapping->at(i);
}
