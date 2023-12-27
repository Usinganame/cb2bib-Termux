/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bCiterHistory.h"


static const int _maximum_history_states(35);


c2bCiterHistory::c2bCiterHistory()
{
    _last_citation_format = c2bCiter::AJYT;
    _index.resize(_maximum_history_states);
    _states.resize(_maximum_history_states);
    clear();
}


void c2bCiterHistory::clear()
{
    _last_citation = 0;
    _last_keyword = 0;
    _last_selection_citation = 0;
    _last_nonkeyword_state = c2bCiter::State();
    _last_nonselected_state = c2bCiter::State();
    _cstate = -1;
    _nstates = -1;
    for (int i = 0; i < _maximum_history_states; ++i)
        _index[i] = i;
}

void c2bCiterHistory::saveCurrentState(const c2bCiter::Format format, const c2bCiter::Filter filter, const int iindex,
                                       const int vindex, const QString fstring)
{
    if (_cstate != -1)
        _nstates = _cstate - 1;
    _cstate = -1;
    const c2bCiter::State s(format, filter, vindex, fstring);
    if (_nstates > -1 && s == _states[_index[_nstates]])
        return;
    if (++_nstates >= _maximum_history_states)
    {
        // Move, e.g., 0 1 2 3 4 to 1 2 3 4 0
        const int oldest(_index[0]);
        for (int i = 0; i < _maximum_history_states - 1; ++i)
            _index[i] = _index[i + 1];
        _index[--_nstates] = oldest;
    }
    _states[_index[_nstates]] = s;
    if (format != c2bCiter::K)
    {
        _last_nonkeyword_state = s;
        if (filter != c2bCiter::Selected)
            _last_nonselected_state = s;
    }
    saveCurrentItemIndex(format, filter, iindex);
}
