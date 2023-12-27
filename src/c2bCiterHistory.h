/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BCITERHISTORY_H
#define C2BCITERHISTORY_H

#include "c2bCiter.h"

#include <QModelIndex>
#include <QVarLengthArray>


class c2bCiterHistory
{

public:
    c2bCiterHistory();
    inline ~c2bCiterHistory() {}

    void clear();
    void saveCurrentState(const c2bCiter::Format format, const c2bCiter::Filter filter, const int iindex,
                          const int vindex, const QString fstring);

    inline void saveCurrentState(const c2bCiter::Format format, const c2bCiter::Filter filter, const int iindex,
                                 const QModelIndex* const index, const QString fstring)
    {
        if (index)
            saveCurrentState(format, filter, iindex, index->row(), fstring);
    }
    inline void saveCurrentItemIndex(const c2bCiter::Format format, const c2bCiter::Filter filter, const int iindex)
    {
        if (format == c2bCiter::K)
            _last_keyword = iindex;
        else if (filter == c2bCiter::Selected)
            _last_selection_citation = iindex;
        else
            _last_citation = iindex;
    }
    inline const c2bCiter::State& lastState() const
    {
        return _states[_index[_nstates]];
    }
    inline const c2bCiter::State& previousState()
    {
        if (_cstate == -1)
            _cstate = _nstates;
        else if (_cstate == 0)
            _cstate = 1;
        return _states[_index[--_cstate]];
    }
    inline const c2bCiter::State& nextState()
    {
        if (_cstate == _nstates)
            _cstate = _nstates - 1;
        return _states[_index[++_cstate]];
    }
    inline int currentState() const
    {
        return _cstate;
    }
    inline const c2bCiter::State& lastNonKeywordState() const
    {
        return _last_nonkeyword_state;
    }
    inline const c2bCiter::State& lastNonSelectedState() const
    {
        return _last_nonselected_state;
    }
    inline void saveCurrentCitationFormat(const c2bCiter::Format format)
    {
        _last_citation_format = (format == c2bCiter::R || format == c2bCiter::K) ? _last_citation_format : format;
    }
    inline c2bCiter::Format lastCitationFormat() const
    {
        return _last_citation_format;
    }
    inline int lastCitation() const
    {
        return _last_citation;
    }
    inline int lastSelectionCitation() const
    {
        return _last_selection_citation;
    }
    inline int lastKeyword() const
    {
        return _last_keyword;
    }


private:
    c2bCiter::Format _last_citation_format;
    int _cstate;
    int _last_citation;
    int _last_keyword;
    int _last_selection_citation;
    int _nstates;

    c2bCiter::State _last_nonkeyword_state;
    c2bCiter::State _last_nonselected_state;

    QVarLengthArray<c2bCiter::State> _states;
    QVarLengthArray<int> _index;
};

#endif
