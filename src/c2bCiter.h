/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BCITER_H
#define C2BCITER_H

#include <QString>


/** \page c2bciter cb2Bib Citer

    The cb2Bib Citer is a keyboard based module for inserting citation IDs into
    a working document. Conveniently, the command <tt>c2bciter</tt>, or its
    expansion <tt>cb2bib --citer</tt>, can be assigned to a global, desktop
    wide shortcut key. This will provide an easy access to the citer from
    within any text editor. Pressing the shortcut turns on and off the citer
    panel. Once appropriate references are selected, pressing key C sets the
    citations either to the clipboard or to a LyX pipe, closes the citer panel,
    and returns keyboard focus to the editor.

    By default, <tt>c2bciter</tt> loads all references from the current
    directory, specified in the cb2Bib main panel. On the desktop tray, the
    cb2Bib icon indicates that the citer is running. Its context menu offers
    the possibility to load other files or directories, or to toggle full
    screen mode.

    Search, filtering, navigation, and citation are keyword based. Pressing
    keys A, I, J, T, and Y sorts the references by author, included date,
    journal, title, and year, respectively. Key F initiates filtering, and Esc
    leaves filtering mode. References are selected when pressing enter. Key S
    toggles the current selection display, and Del clears the selection. The
    combination Shift + letter navigates through the rows starting by the
    letter.

    Advanced filtering capabilities are available after indexing the documents.
    Document indexing, or term or key sentence extraction, is performed by
    clicking the tray icon menu action Index Documents. Once indexing is done
    and after clicking Refresh, pressing K displays the document extracted
    keywords, and pressing G, the collection glossary of terms. On a keyword,
    pressing R display all documents indexed by the keyword. On a document,
    pressing R display related documents. Relatedness is set from keyword based
    similarity measures.

    Key sequence Alt+C toggles clipboard connection on and off. When connection
    is on, the clipboard contents is set, each time it changes, as the filter
    string. This provides a fast way to retrieve a given reference while
    browsing elsewhere.



\verbatim
   Usage:      cb2bib --citer [dirname1 [dirname2 ... ]]
               cb2bib --citer [filename1.bib [filename2.bib ... ]]

\endverbatim

\verbatim
   Display Keys
      A        author - journal - year - title
      I        included date - title
      J        journal - year - author
      T        title
      Y        year - author - journal - title

\endverbatim

\verbatim
   Filter Keys
      D        Delete last filter
      F        Enter pattern filter mode
      G        Toggle glossary of terms view
      K        Toggle document keywords view
      R        Display related documents

      Left     Move to previous filtered view
      Right    Move to next filtered view

\endverbatim

\verbatim
   Action Keys
      C        Cite selected citations and close citer window
      Del      Unselect all citations
      E        Edit current citation's source
      Enter    Select current citation
      Esc      Exit filter mode or close citer window
      O        Open current citation's file
      S        Display the set of selected citations
      V        Display document excerpts in keywords view
      Shift+   Keyboard search naviagation
      U        Open current citation's URL
      W        Write notes using Annote

\endverbatim

\verbatim
   Tray Icon Actions
      F1       Citer help
      Ctrl+O   Open BibTeX directory
      Alt+O    Open BibTeX files
      F5       Refresh
      Ctrl+F   Search in files
      Alt+L    Set Lyx pipe
      F2       Toggle cb2Bib
      Alt+C    Toggle clipboard
      Alt+F    Toggle full screen
               Index documents

\endverbatim



  See also \ref relnotes130, \ref relnotes140, \ref relnotes147, \ref
  commandline and \ref c2bannote.

*/


namespace c2bCiter
{

enum Format
{
    AJYT,
    IT,
    JYA,
    T,
    YAJT,
    R,
    K
};
enum Filter
{
    None,
    Document,
    Keyword,
    Pattern,
    Related,
    Selected
};

struct State
{
    inline State() : format(AJYT), filter(None), viewer_index(0) {}
    inline State(const Format fo, const Filter fi, const int vi, const QString fs)
        : format(fo), filter(fi), viewer_index(vi), filter_string(fs) {}

    inline bool operator==(const State& s) const
    {
        return format == s.format && filter == s.filter && viewer_index == s.viewer_index &&
               filter_string == s.filter_string;
    }

    Format format;
    Filter filter;
    int viewer_index;
    QString filter_string;
    QString index_data;
};

struct KeywordData
{
    bool valid;
    QString bibtexfn;
    QString documentfn;
    QString keyword;
};

} // namespace c2bCiter

#endif
