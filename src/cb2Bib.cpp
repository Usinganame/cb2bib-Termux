/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "cb2Bib.h"

#include "c2b.h"
#include "c2bBibMenu.h"
#include "c2bBibParser.h"
#include "c2bCiterWidget.h"
#include "c2bClipEdit.h"
#include "c2bClipboard.h"
#include "c2bEditor.h"
#include "c2bFileDialog.h"
#include "c2bNetworkQuery.h"
#include "c2bPdfImport.h"
#include "c2bPostprocess.h"
#include "c2bSaveRegExp.h"
#include "c2bSearchInFiles.h"
#include "c2bSettings.h"
#include "c2bTextBrowser.h"
#include "c2bUtils.h"

#include <bibSearcher.h>
#include <network.h>

#include <QtWidgets>


/** \page overview Overview

  cb2Bib is a free, open source, and multiplatform application for rapidly
  extracting unformatted, or unstandardized bibliographic references from email
  alerts, journal Web pages, and PDF files.

  cb2Bib facilitates the capture of single references from unformatted and non
  standard sources. Output references are written in BibTeX. Article files can
  be easily linked and renamed by dragging them onto the cb2Bib window.
  Additionally, it permits editing and browsing BibTeX files, citing
  references, searching references and the full contents of the referenced
  documents, inserting bibliographic metadata to documents, and writing short
  notes that interrelate several references.

  <b>Current version: cb2Bib GET_VERSION</b>. See \ref changelog for a
  detailed list of changes and acknowledgments, and \ref relnotes for
  additional notes and information.

  See \ref relnotes201.

<p>&nbsp;</p>

GET_TABLE_OF_CONTENTS

<p>&nbsp;</p>
\section descrip Description


  cb2Bib reads the clipboard text contents and process it against a set of
  predefined patterns. If this automatic detection is successful, cb2Bib
  formats the clipboard data according to the structured BibTeX reference
  syntax.

  Otherwise, if no predefined format pattern is found or if detection proves to
  be difficult, manual data extraction is greatly simplified by cb2Bib. In most
  cases, such manual data extraction will provide with a new, personalized
  pattern to be included within the predefined pattern set for future automatic
  extractions.

  Once the bibliographic reference is correctly extracted, it is added to a
  specified BibTeX database file. Optionally, document files are renamed to a
  DocumentID filename and moved to a desired directory as a personal article
  library, and their metadata is updated with the bibliographic reference. See
  \ref metadata section.

  cb2Bib facilitates writing short notes related to bibliographic collections.
  Notes are written using a minimalist markup on a plain text editor, and can
  latter be converted to HTML. Related references and links become easily
  accessible on any browser or by the embedded cb2Bib viewer. See \ref
  relnotes110.

  <p>&nbsp;</p>
\section usage Using cb2Bib

\subsection procedure Procedure

  - <b>Select the reference to import from the email or web browser</b> \n On
  Unix machines, cb2Bib automatically detects mouse selections and clipboard
  changes. On Windows machines, copy or Ctrl-C is necessary to activate cb2Bib
  automatic processing.

  - <b>cb2Bib automatic processing</b> \n Once text is selected cb2Bib
  initiates the automatic reference extraction. It uses the predefined patterns
  from file <tt>regexp.txt</tt> to attempt automatic extraction. See \ref
  c2bconf_files section for setting the user predefined pattern matching
  expression file. After a successful detection bibliographic fields appear on
  the cb2Bib item line edits. Manual editing is possible at this stage.

  - <b>cb2Bib manual processing</b> \n If no predefined format pattern is found
  or if detection proves to be difficult, a manual data extraction must be
  performed. Select, either using mouse or Shift+arrow keys, the reference
  fields from the cb2Bib clipboard area. A popup menu will appear after
  selection is made. Choose the corresponding bibliographic field. See \ref
  entrytype. If operating with the keyboard, first letter of the field is set
  as a menu shortcut. Then, typing 'A' sets selection to 'author', or '+A' to
  'add authors'. Selection is postprocessed and added to the cb2Bib item line
  edit. cb2Bib field tags will show on the cb2Bib clipboard area. Once the
  manual processing is done, cb2Bib clipboard area will contain the matching
  pattern. The pattern can be further edited and stored to the
  <tt>regexp.txt</tt> file using <b>Insert Regular Expression</b>, Alt+I. See
  the \ref clipboard and \ref regexpeditor sections.

  - <b>Download reference to cb2Bib</b> \n cb2Bib has the built-in
  functionality to interact with publishers "Download reference to Citation
  Manager" service. Choose BibTeX format, or any other format that you can
  translate using <b>External Clipboard Preparsing Command</b>. See \ref
  keyboard, <b>Alt C</b>. Click "Download" from your browser. When asked "Open
  with..." select cb2Bib. cb2Bib will be launched if no running instance is
  found. If already running, it will place the downloaded reference to the
  clipboard, and it will start processing. Make sure your running instance is
  aware of clipboard changes. See \ref c2bbuttons. For convenience, the shell
  script <tt>c2bimport</tt>, and the desktop config file
  <tt>c2bimport.desktop</tt> are also provided.

  - <b>Adding documents</b> \n PDF and other documents can be added to the
  BibTeX reference by dragging the file icon and dropping it into the cb2Bib's
  panel. Optionally, document files, are renamed to a DocumentID filename and
  moved to a desired directory as a personal article library (See \ref
  c2bconf_documents section). Linked to a reference documents correspond to the
  BibTeX tag <tt>file</tt>. Usual reference manager software will permit to
  retrieve and visualize these files. Download, copy and/or moving is scheduled
  and performed once the reference is accepted, e.g., once it is saved by
  pressing <b>Save Reference</b> button.

  - <b>Multiple retrieving from PDF files</b> \n Multiple PDF or convertible to
  text files can be sequentially processed by dragging a set of files into
  cb2Bib's PDFImport dialog. By starting the processing button, files are
  sequentially converted to text and send to cb2Bib clipboard panel for
  reference extraction. See \ref pdfimport for details.

  - <b>Journal-Volume-Page Queries</b> \n Takes input Journal, Volume, and
  first page from the corresponding edit lines and attempts to complete the
  reference. Additionally, queries consider <tt>title</tt>, <tt>DOI</tt>, and
  an <tt>excerpt</tt>, which is a simplified clipboard panel contents. See \ref
  c2bconf_network section, the distribution file <tt>netqinf.txt</tt>, and \ref
  relnotes035 for customization and details.

  - <b>BibTeX Editor</b> \n cb2Bib includes a practical text editor suitable
  for corrections and additions. cb2Bib capabilities are readily available
  within the editor. E.g., the reference is first sent to cb2Bib by selecting
  it, and later retrieved from cb2Bib to the editor using 'right click' +
  'Paste Current BibTeX'. Interconversions Unicode <-> LaTeX, long <->
  abbreviated journal name, and adding/renaming PDF files are easily available.
  BibTeX Editor is also accessible through a shell command line. See \ref
  commandline and \ref bibeditor.


\subsection c2bbuttons Buttons Functionality

  - \b About \n About cb2Bib, bookmarks, and online help.

  - \b Configure \n Configure cb2Bib. See \ref configuration section.

  - <b>Search references</b> \n Opens the cb2Bib's search dialog. The search is
  performed either on the current BibTeX file, or for all BibTeX files on the
  current directory. Optionally, the search is extended to reference's files.
  Hits are displayed on an editor window. See \ref bibsearch. See also \ref
  c2bconf_utilities section to configure the external to text converter.

  - \b PDFImport \n Launches cb2Bib's PDFImport window. Files dragged into
  PDFImport window are sequentially translated to text and sent to cb2Bib
  clipboard panel. cb2Bib automatic and manual capabilities are then easily
  available to extract and supervise reference extractions. See \ref pdfimport.

  - \b Exit \n Exits cb2Bib.

  - <b>Dis/Connect Clipboard</b> \n Toggles automatic cb2Bib and desktop
  clipboard connection. While the automatic cb2Bib-clipboard connection permits
  reducing keystrokes, the disconnected mode is needed in cases where multiple
  mouse selections or copies are required to complete a reference extraction.
  See also \ref relnotes041 and \ref relnotes021 if you experience problems
  with this feature.

  - <b>Network Reference Query</b> \n Starts Network Query. It usually takes
  input Journal, Volume, and first page from the corresponding edit lines and
  attempts to complete the reference. See \ref c2bconf_network network section
  to customize querying. See the distribution file <tt>netqinf.txt</tt> and
  also \ref relnotes035 for the details.

  - <b>View BibTeX Reference</b> \n View current reference as will be output to
  the BibTeX file. Eventual manual changes should be done on the item line
  edit.

  - <b>Save Reference</b> \n Inserts the current bibliographic reference to the
  output BibTeX file. This action decides whether or not a reference is
  accepted. Scheduled actions such as PDF downloading, copying or renaming will
  be performed at this time.

  - <b>Open BibTeX File</b> \n Opens the current BibTeX output file. Right
  click within the BibTeX Editor window for its particular functionality. See
  also \ref bibeditor.


\subsection keyboard Additional Keyboard Functionality

  Most keyboard shortcuts are customizable. See \ref c2bconf_shortcuts. In the
  following, default shortcuts are used to describe functionality.

  - <b>Alt A</b> \n Starts \ref c2bannote. Specify the note's filename in the
  dialog. A new note is created if the file name does not exist. The cb2Bib
  Annote is opened as a separate program. Exiting cb2Bib will not exit the
  note's viewer. On the viewer, pressing key E launches the default text
  editor. The viewer will track the editor, and will update the note's display
  each time the editor saves it. The viewer's functionality is disabled if
  cb2Bib was not compiled and linked against WebKit. See \ref commandline to
  use Annote in command line mode.

  - <b>Alt B</b> \n Edits the Bookmarks and Network Query Info file
  <tt>netqinf.txt</tt>.

  - <b>Alt C</b> \n Preparses cb2Bib's clipboard through a user specified
  external script or tool. Preparsing is necessary to catch formatted
  references that can not be easily extracted using recognition patterns, or
  that are written in ambiguous formats. Many available scripts or specific
  user-written tools can be incorporated to cb2Bib through this external
  preparsing capability. In addition, simple, one-line scripts can be used
  within PDFImport to provide, for instance, the journal name when missing from
  the PDF first page. The cb2Bib distribution contains the sample scripts
  <tt>isi2bib</tt> and <tt>ris2bib</tt> that convert ISI and RIS formatted
  strings to BibTeX. See \ref c2bconf_clipboard for details.

  - <b>Alt D</b> \n Deletes temporary BibTeX output file. This permits using
  cb2Bib output files as temporary media to transfer references to a preferred
  reference manager and preferred format. <b>Caution</b>: This feature is not
  intended for the users who actually store their references in one or several
  BibTeX files. Remember to import references prior to delete cb2Bib output
  file.

  - <b>Alt E</b> \n Edits the regular expression file. It permits an easy
  access and modification of stored extraction patterns. New patterns are
  conveniently added to to the regular expression file by using the <b>RegExp
  Editor</b> button functionality.

  - <b>Alt F</b> \n Launches a file dialog for selecting the source file name
  for the BibTeX entry <tt>file</tt>. Selected files are displayed either, as
  the actual source filename, or, as the target filename, depending on the file
  copy/rename/move settings. See \ref c2bconf_documents. Alternatively to
  <b>Alt F</b>, documents can be easily linked to a reference by dragging the
  document file and dropping it to the cb2Bib panel.

  - <b>Alt I</b> \n Edits and optionally inserts the current regular
    expression pattern. See the \ref clipboard and \ref regexpeditor sections.

  - <b>Alt J</b> \n Edits the Journal Abbreviations file.

  - <b>Alt O</b> \n Opens the currently linked document for browsing. Documents
  can be easily linked to a reference by dragging the document file and
  dropping it to the cb2Bib panel, or with <b>Alt F</b>. Linked documents
  correspond to the BibTeX tag <tt>file</tt>.

  - <b>Alt P</b> \n Postprocess BibTeX output file. It launches a user
  specified script or program to postprocess the current BibTeX file. The
  cb2Bib distribution contains two sample scripts. One, <tt>bib2pdf</tt> is a
  shell script for running <tt>latex</tt> and <tt>bibtex</tt>; this permits to
  check the BibTeX file for possible errors, and to easily produce a suitable
  output for printing. The other one, <tt>bib2end.bat</tt> is a batch script
  for running <tt>bib2xml</tt> and <tt>xml2end</tt>, which converts references
  into Endnote format. See \ref c2bconf_bibtex for details.

  - <b>Alt R</b> \n Restarts cb2Bib automatic engine. Takes input data not
  from the system clipboard but from the cb2Bib clipboard panel. This permits
  editting the input stream from poorly translated PDF captions, correcting for
  author superscripts, or helps in debugging regular expressions.

  - <b>Alt W</b> \n Writes current reference to the source document file. This
  option is intended for writing and updating bibliographic metadata to
  document files without needing to use BibTeX files. Only local and writable
  files are considered.

  - <b>Alt X</b> \n Check Repeated looks for existing references in the BibTeX
  directory similar to the current one. The search is done for exact cite ID,
  and for title and author field values, or, if empty, for booktitle and
  editor,using the
  \htmlonly
  <a href="https://arxiv.org/abs/0705.0751" target="_blank">approximate string</a>
  \endhtmlonly
  search pattern. See also \ref c2bconf_bibtex.

  - <b>F4</b> \n Toggles between Main and Other Fields reference edit tabs.

  - <b>Esc</b> \n Quits cb2Bib popup menu. The cb2Bib menu pops up each time a
  selection in made in the clipboard panel. This saves keystrokes in a normal
  bibliographic extraction. Press <b>Esc</b> or <b>Right Click</b> mouse button
  if you need to gain access to the editor cut/copy/paste functionality
  instead.


  <p>&nbsp;</p>

\section detail Advanced Features
  Advanced features, and processing and extraction details are described in the
  following sections:
    - \ref faq_automatic_extraction
    - \ref clipboard
    - \ref authorproc
    - \ref journalproc
    - \ref heuristics
    - \ref regexpeditor

  Configuration information is described in the following sections:
    - \ref configuration
    - \ref predefinedplaceholders

  Utilities and modules are described in the following sections:
    - \ref bibsearch
    - \ref bibeditor
    - \ref pdfimport
    - \ref metadata
    - \ref commandline
    - \ref c2bannote
    - \ref c2bciter


  <p>&nbsp;</p>

\section requirements Requirements

\subsection requirements_comp Compilation
  To compile cb2Bib, the following libraries must be present and accessible:

    - Qt 5.7.0 or later from
    \htmlonly
    <a href="https://www.qt.io/download" target="_blank">Qt Project</a>.
    \endhtmlonly
    On a Linux platform with Qt preinstalled, make sure that the <tt>devel</tt>
    packages and Qt tools are also present.

    - QtWebKit or QtWebEngine library (optional) to compile cb2Bib Annote
    viewer. No special action/flag is needed during compilation.

    - Compression libraries
    \htmlonly
    <a href="https://lz4.github.io/lz4/" target="_blank">LZ4</a>
    \endhtmlonly
     or
    \htmlonly
    <a href="https://www.oberhumer.com/opensource/lzo/" target="_blank">LZO</a>
    \endhtmlonly
     (optional). To chose a particular one, type <tt>configure --enable-lz4</tt> or <tt>configure --enable-lzo</tt>.
     On machines with SSE4 instruction set, the
    \htmlonly
    <a href="https://github.com/ConorStokes/LZSSE/" target="_blank">LZSSE</a>
    \endhtmlonly
     compressor can be used in place of LZ4 and LZO, by typing <tt>configure --enable-lzsse</tt>.
     If none of the above compressors were appropiate on a particular platform, type <tt>configure --enable-qt-zlib</tt>
     before compiling.

    - X11 header files if compiling on Unix platforms. Concretely, headers
    <tt>X11/Xlib.h</tt> and <tt>X11/Xatom.h</tt> are needed.

    - The header files <tt>fcntl.h</tt> and <tt>unistd.h</tt> from
    <tt>glibc-devel</tt> package are also required. Otherwise compilation will
    fail with <tt>`::close' undeclared</tt>.

\subsection requirements_run Deployment
    Although not needed for running cb2Bib, the following tools extend cb2Bib
    applicability:

    - <tt>MathJax</tt>, available at
    \htmlonly
    <a href="https://www.mathjax.org/" target="_blank">https://www.mathjax.org</a>,
    \endhtmlonly
    for displaying mathematical notation. Simply, download and unzip it in a desired directory. See \ref c2bconf_annote.

    - <tt>ExifTool</tt>, version 7.31 or later, available at
    \htmlonly
    <a href="https://exiftool.org/" target="_blank">https://exiftool.org</a>,
    \endhtmlonly
    for metadata insertion.

    - <tt>pdftotext</tt>, found packaged as <tt>xpdf</tt>, and downloadable from
    \htmlonly
    <a href="https://www.xpdfreader.com/download.html" target="_blank">https://www.xpdfreader.com/download.html</a>.
    \endhtmlonly

    - The <tt>bib2xml</tt> and <tt>xml2end</tt>
    \htmlonly
    <a href="http://bibutils.refbase.org/" target="_blank">BibUtils</a>,
    \endhtmlonly
    for the postprocessing script <tt>bib2end.bat</tt> on Windows platforms.

    - LaTeX packages, for checking BibTeX files correctness and for references
    printing through the shell script <tt>bib2pdf</tt>.


  <p>&nbsp;</p>
\section credits Credits and License

  The cb2Bib icons are taken from the <em>Oxygen</em>, <em>Crystal SVG</em>,
  and <em>Noia</em> icon sets, to be found at the
  \htmlonly
  <a href="https://kde.org/" target="_blank">KDE Desktop Environment</a>.
  \endhtmlonly
  Several people has contributed with suggestions, bug reports or patches. For
  a detailed list of acknowledgments see the \ref changelog.

  The cb2Bib program is licensed under the terms of the
  \htmlonly
  <a href="https://www.gnu.org/licenses/gpl-3.0.html" target="_blank">GNU General Public License</a>
  \endhtmlonly
  version 3.

  <p>&nbsp;</p>

>  <b><em>GET_UPDATEDON</em></b> \n
>  <em>First released version 0.1.0 on 2004-06-29.</em> \n
>  &copy; <em>2004-2021 Pere Constans</em> \n

*/


/** \page relnotes Release Notes

\section relnotes201 Release Note cb2Bib 2.0.1


  To optimize search on PDF's contents, cb2Bib keeps a cache with the extracted
  text streams, that are compressed to reduce disk space and reading overhead.
  Nowadays, compressors with extremely high decompression speed are available.
  Two of them are LZSSE, for SSE4 capable architectures, and LZ4, for a broader
  range of CPUs. These two compressors can now be used by cb2Bib, with the
  latter set as the default compression library in cb2Bib builds. When
  upgrading to version 2.0.1, the <b>first search</b> on the document
  collection will recreate the cache, and this step <b>will be noticeably
  slow</b>.

  Additionally, cb2Bib 2.0.1 includes original, optimized text matching code
  for AVX2 capable architectures that is used for search matching and BibTeX
  parsing. This code is <b>not set</b> in default builds and needs to be
  explicitly enabled at compilation time.

  Finally, it is important mentioning the inclusion in version 2.0.1 of stemmed
  context search, see \ref contextsearch for details, and contributed feedback
  in handling citations and extending cite commands to markdown syntax, see
  \ref predefinedplaceholders.

  <p>&nbsp;</p>
*/


/** \page relnotes Release Notes

\section relnotes200 Release Note cb2Bib 2.0.0

  Throughout the 1.9.x series, the cb2Bib sources were updated to the improved
  string processing capabilities of Qt5 and PCRE libraries. This update has
  brought a remarkable speedup for in-document searches and full search
  indexing.

  Alternate normalization of journal titles and abbreviations, upgrading jsMath
  to MathJax, extending network queries syntax, and a PDF user manual are the
  additional enhancements in cb2Bib 2.0.0.

  Back in version 0.3.3, cb2Bib introduced network queries to obtain the data
  for a citation. While convenient, queries to publishers' websites were
  difficult to setup and fragile. Nowadays, fortunately, arXiv, PubMed and
  Crossref offer structured APIs. These interfaces provide to the end user an
  easy setup for completing bibliographic citations.

  <p>&nbsp;</p>
*/


/** \page relnotes Release Notes

\section relnotes190 Release Note cb2Bib 1.9.0

  The cb2Bib sources have been ported to Qt5. To highlight this major update
  in library requirements the version number is set to 1.9.0. Later, once
  stabilized and new functionality related to Qt5 enhancements are applied,
  version number will be set to 2.

  At this point cb2Bib has exactly the same functionality as its preceding
  version 1.5.0. To build the program, however, only qmake and its related
  config procedure are available. The cmake scripts have not yet been ported.

  Qt5 brings important enhancements related to regular expressions and string
  processing. Some careful updates to the cb2Bib sources are needed to fully
  benefit from them. They will implemented through the 1.9.x series. We
  expect by then a performance boost on full text, regular expression based
  searches.

  <p>&nbsp;</p>
*/


/** \page relnotes Release Notes

\section relnotes150 Release Note cb2Bib 1.5.0

  Included in version 1.5.0 sources there is a patch for XPDF 3.0.4, the
  default tool to convert PDF documents to plain text. The modified code
  separates superscripts to avoid words being joined to reference numbers and
  author names joined to affiliations' glyphs. Interested users will need to
  download the package, apply the patch, and compile it.

  Additionally, this version improves converted text postprocessing. This
  step normalizes character codes, reverts ligatures, restores when possible
  orphan diacritics and broken words, and undoes text hyphenation.

  Conversion to text and postprocessing is important for reference extraction,
  and document indexing and searching. It is therefore recommended to delete
  cached document-to-text data to benefit from the present improvements. cb2Bib
  stores cached texts in *c2b files in an user specified directory. After that,
  by performing a search or initiating indexing an updated cache will be
  created.

  <p>&nbsp;</p>
*/


/** \page relnotes Release Notes

\section relnotes147 Release Note cb2Bib 1.4.7

  Approximate and context searches effectively locate our references of
  interest. As collections grow in size, and low performance devices,
  netbooks and tablets, start being used, complete document searches become
  demanding. Besides, it is often not clear what to query for, and then a
  glossary of terms provides guidance. Often too, interest lies on subsetting
  documents by being similar to a given one.

  Version 1.4.7 adds a pragmatic term or keyword extraction from the document
  contents. Accepted keywords are set as the substrings appearing at least
  twice in one document, appearing at least in three documents, and
  conforming to predefined part-of-speech (POS) sequences. Keyword extraction
  is performed by either clicking on <tt>Index Documents</tt> at the
  <tt>c2bciter</tt> desktop tray menu, or, by typing <tt>cb2bib --index
  [bibdirname]</tt> on a shell. During extraction, the <tt>Part Of Speech
  (POS) Lexicon</tt> distribution file must be available and readable. On
  termination, indexing files are saved on the <tt>Search In Files Cache
  Directory</tt>. Simply copying this directory will synchronize keyword
  indexing to a second computer.

  After refreshing <tt>c2bciter</tt> module, pressing key G displays the
  glossary of terms. On a reference, pressing K displays its list of
  keywords. Pressing R on a keyword lists the references related to that
  keyword. Pressing R on a reference lists similarly related references.
  Similarity is assessed based on keyword occurrences. Left and Right keys
  provide previous and next navigation. Pressing V on either a reference
  keyword, or a keyword reference, visualizes the keyword excerpts from the
  reference's document. To close excerpt dialog press Esc or Left keys.


  See also \ref c2bciter, \ref c2bconf_files, and \ref commandline.

  <p>&nbsp;</p>
*/


/** \page relnotes Release Notes

\section relnotes140 Release Note cb2Bib 1.4.0

  The <tt>c2bciter</tt> module was introduced in version 1.3.0. Its name, as
  it was described, states its purpose of being "aimed to ease inserting
  citation IDs into documents". In fact, it does have such functionality.
  And, it has also another, equally important one: it provides a very fast
  way to retrieve a given work from our personal collections.

  Retrieving is accomplished through pre-sorted views of the references and
  filtering. Both, views and filtering, scale on the (tens of) thousands
  references. Usually, we recall a work from its publication year, a few
  words from its title, or (some of the letters of) one of its authors names.
  Often, what we remember is when a reference was included into our
  collection. Therefore, having such a chronological view was desirable.

  The implementation of this sorted-by-inclusion-date view was not done
  during the 1.3.x series, but postponed to version 1.4.0; somehow, to
  indicate that some sort of 'proprietary' BibTeX tag might be required to
  specify inclusion timestamps. I have been reluctant through the cb2Bib's
  life span to introduce 'cb2Bib-only' tags in the BibTeX outputs. I believe
  that there is little gain, and it costs, possibly, breaking
  interoperability.

  In the end, the choice was to not write any 'timestamp' tag in references.
  Instead, <tt>c2bciter</tt> checks for the last modified date of the linked
  documents to build an approximated chronological view. The advantage is
  that all, not just 'version 1.4.0 or later', references are sorted.
  Furthermore, if a reference is later corrected, and the document metadata
  is updated too, the modification date is reflected in the view. The obvious
  inconvenience is that no such sorting can be done for references without an
  attached document.


  See also \ref c2bciter.

  <p>&nbsp;</p>
*/

/** \page relnotes Release Notes

\section relnotes130 Release Note cb2Bib 1.3.0

  When version 0.2.7 came up, it was mentioned in \ref relnotes027 that cb2Bib
  'doesn't have the means to automatically discern an author name from a
  department or street name'. I forgot mentioning, that I did not expect cb2Bib
  would have had such a feature. Since the last \ref relnotes110, the cb2Bib
  internals had changed significantly. Some changes, such heuristic recognition
  for interlaced authors and affiliations, get easily noticed. Other changes,
  however, do not, and need additional explanation.

  From version 1.2.3, the switches <tt>--txt2bib</tt> and <tt>--doc2bib</tt>
  set cb2Bib to work on console mode. The non-exact nature of the involved
  extractions makes logging necessary. On Windows, graphic or console modes
  must be decided not at run time, but when the application is built. So far,
  logging and globing were missing. This release adds the convenience wrapper
  <tt>c2bconsole</tt>. Typing <tt>c2bconsole --txt2bib i*.txt out.bib</tt>, for
  instance, will work as it does in the other platforms.

  Lists of references are now sorted case and diacritic insensitive. For some
  languages such a choice is not the expected one, and some operating systems
  offer local-aware collation. Due to usual inconsistencies and inaccuracies
  in references, this decision was taken to group together 'Density Matrix'
  with 'Density-matrix', and
  \htmlonly
  M&#248;ller
  \endhtmlonly
  with Moller, which, in a personal collection, most probably, refer to the
  same concept and to the same person. Additionally, document to text
  converted strings are now clean from extraneous, non-textual symbols.
  Therefore, recreating cache files is recommended.

  Finally, this release introduces a new module, named <tt>c2bciter</tt>, and
  aimed to ease inserting citation IDs into documents. The module should
  ideally stay idle at the system tray, and be recalled as needed by pressing
  a global, desktop shortcut. This functionality, while desirable, and usual
  in dictionaries, is platform and desktop dependent. On KDE there are
  currently known issues when switching among virtual desktops.

  See also \ref c2bciter, and \ref commandline.

  <p>&nbsp;</p>
*/

/** \page relnotes Release Notes

\section relnotes110 Release Note cb2Bib 1.1.0

  A frequent request from cb2Bib users has been to expand the command line
  functionality. So far few progress has been seen in this regard. First, the
  addition of in-document searches and reading/inserting metadata were
  priorities. Second, cb2Bib is not the tool to interconvert among
  bibliographic formats. And third, cb2Bib is designed to involve the user in
  the search process, in the archiving and validation of the discovered works
  and references.

  For the latter reason, and for not knowing a priori how would such a tool
  be designed, the cb2Bib internals had been interlaced to its graphical
  interface. At the time of version 0.7.0, when the graphical libraries
  changed, and a major refactoring was required, the code started moving
  toward a better modularization and structure. The current release pushes
  code organization further. As a result, it adds two new command line
  switches: <tt>--html-annote</tt> and <tt>--view-annote</tt>.

  The new cb2Bib module is named after the BibTeX key 'annote'. Annote is not
  for a 'one reference annotation' though. Instead, Annote is for short notes
  that interrelate several references. Annote takes a plain text note, with
  minimal or no markup, inserts the bibliographic citations, and converts it
  to a HTML page with links to the referenced documents.

  From within cb2Bib, to write your notes, type Alt+A, enter a filename, either
  new or existing, and once in Annote, type E to launch your default text
  editor. For help, type F1. Each time you save the document the viewer will be
  updated. To display mathematical notations, install
  \htmlonly
  <a href="http://www.math.union.edu/~dpvc/jsMath/" target="_blank">jsMath</a>
  \endhtmlonly
  locally. And, remember, code refactoring introduces bugs.

  See also \ref c2bannote and \ref commandline.

  <p>&nbsp;</p>
*/

/** \page relnotes Release Notes

\section relnotes100 Release Note cb2Bib 1.0.0

  Approximately four years ago the first cb2Bib was released. It included the
  possibility of easily linking a document to its bibliographic reference, in a
  handy way, by dragging the file to the main (at that time, single) panel.
  Now, in version 1.0.0, when a file is dropped, cb2Bib scans the document for
  metadata packets, and checks, in a rather experimental way, whether or not
  they contain relevant bibliographic information.

  Publishers metadata might or might not be accurate. Some, for instance,
  assign the DOI to the key Title. cb2Bib extracts possibly relevant key-value
  pairs and adds them to clipboard panel. Whenever key-value pairs are found
  accurate, just pressing Alt+G imports them to the line edits. If keys with
  the prefix <tt>bibtex</tt> are found, their values are automatically
  imported.

  The preparsed metadata that is added to the clipboard panel begins with
  <tt>[Bibliographic Metadata</tt> and ends with <tt>/Bibliographic
  Metadata]</tt>. Therefore, if you are using PDFImport together with a set
  of regular expressions, such that they contain the begin (^) or end ($)
  anchors, you can safely replace them by the above tags. In this manner,
  existing regular expressions remain useful with this minor change. And,
  with the advantage that, if recognition fails for a given document,
  metadata might give the hardest fields to extract from a PDF article,
  which are author and title.

  See also \ref metadata.


  <p>&nbsp;</p>
*/

/** \page relnotes Release Notes

\section relnotes084 Release Note cb2Bib 0.8.4

  The previous cb2Bib release added the command line option <tt>--conf
  [full_path]cb2bib.conf</tt> to specify the settings location. This feature
  was intended, mainly, as a clean way to run the program on a host computer
  from a removable drive. The work done focused on arranging the command line
  and settings related code. It was left for a later release to solve some
  requirements regarding the managing of file pathnames and temporary files.

  This release addresses these two points. Now, when cb2Bib is launched as
  <tt>cb2bib --conf</tt> --without a configuration filename-- it treats
  filenames as being relative to the cb2Bib actual location. Temporary files,
  if needed, will be placed at this location as well. Therefore, no data is
  being written on the host, and cb2Bib works independently of the actual
  address that the host assigns to the removable drive.

  The Windows' un/installer cleans/sets configuration data on the registry.
  Being aware of this particular, it might be better not to install the
  program directly to the USB drive. Just copy the cb2Bib base directory from
  a home/own computer to the removable drive, and then run it on the host
  computer as <tt>cb2bib --conf</tt>.

  <p>&nbsp;</p>
*/

/** \page relnotes Release Notes

\section relnotes083 Release Note cb2Bib 0.8.3

  cb2Bib accepts several arguments on its command line to access specific
  functionality. So far, the command <tt>cb2bib tmp_ref</tt> permits
  importing references from the browser, whenever a <em>download to reference
  manager</em> choice is available. In addition, the command <tt>cb2bib
  --bibedit ref.bib</tt> directly launches the BibTeX editor for file
  browsing and editing.

  This release adds the command line option <tt>--conf
  [full_path]cb2bib.conf</tt> to specifically set a file where all internal
  settings are being retrieved and stored. This has two interesting
  applications. On one hand, it easily permits switching from several sets of
  extraction rules, since the files <tt>abbreviations.txt</tt>,
  <tt>regexps.txt</tt>, and <tt>netqinf.txt</tt> are all stored in the
  cb2Bib's settings. And, on the other hand, it allows installing the program
  on a USB flash drive, and cleanly running it on any (e. g., library)
  computer. Settings can be stored and kept on the external device, and
  therefore, no data will be written on the registry or settings directory of
  the host computer.

  So far, however, this feature should be regarded as experimental. The Qt
  library to which cb2Bib is linked does read/write access to system settings
  in a few places (concretely, in file and color dialogs). On Unix and Mac OS
  systems this access can be modified by setting the environment variable
  DAG_CONFIG_HOME. No such workaround is presently available in Windows.

  See \ref commandline for a detailed syntax description.

  <p>&nbsp;</p>
*/

/** \page relnotes Release Notes

\section relnotes081 Release Note cb2Bib 0.8.1

  Several changes in this release affect installation and deployment. First,
  the cb2Bib internals for settings management has been reorganized. Version
  0.8.1 will not read previous settings, as user colors, file locations, etc.
  On Unix, settings are stored at <tt>~/.config/MOLspaces/cb2Bib.conf</tt>.
  This file can be removed, or renamed. On Windows, it is recommended to
  uninstall previous versions before upgrading.

  Second, cb2Bib tags are not shown by default. Instead, it is shown plain,
  raw clipboard data, as it is easier to identify with the original source.
  To write a regular expression, right click, on the menu, check 'View Tagged
  Clipboard Data', and perform the extraction from this view.

  And finally, cb2Bib adds the tag <<excerpt>> for network queries. It takes a
  simplified version of the clipboard contents and sends it to, e.g. Google
  Scholar. From there, one can easily import BibTeX references related to that
  contents. Therefore one should unchecked in most cases the 'Perform Network
  Queries after automatic reference extractions' box.

  <p>&nbsp;</p>
*/

/** \page relnotes Release Notes

\section relnotes072 Release Note cb2Bib 0.7.2

  cb2Bib reads the clipboard contents, processes it, and places it to the
  main cb2Bib's panel. If clipboard contents can be recognized as a
  reference, it writes the corresponding BibTeX entry. If not, the user can
  interact from the cb2Bib panel and complete or correct the reference.
  Additionally, this process permits to write down a regular expression
  matching the reference's pattern.

  To ease pattern writing, cb2Bib preprocesses the raw input data. This can
  consider format conversion by external tools and general substitutions, in
  addition to including some special tags. The resulting preprocessed data is
  usually less readable. A particularly illustrating case is when input data
  comes from a PDF article.

  cb2Bib now optionally presents input data, as raw, unprocessed data. This
  preserves the block text format of the source, and thus identifying the
  relevant bibliographic fields by visual inspection is more straightforward.
  In this raw mode view panel, interaction works in a similar manner. Except
  that, no conversions or substitutions are seen there, and that no regular
  expression tags are written.

  <p>&nbsp;</p>
*/

/** \page relnotes Release Notes

\section relnotes070 Release Note cb2Bib 0.7.0

  This release moves forward cb2Bib base requirement to Qt 4.2.0. Compilation
  errors related to rehighlight() library calls, kindly reported by Bongard,
  Seemann, and Luisser, should not appear anymore. File/URL opening is
  carried now by this library, in a desktop integrated manner. Additionally,
  Gnome users will enjoy better integration, as Cleanlooks widget style is
  available.

  All known regressions in 0.6.9x series have been fixed. Also, a few minor
  improvements have been included. In particular, file selection dialogs
  display navigation history, and BibTeX output file can be conveniently
  selected from the list of '*.bib' files at the current directory. Such a
  feature will be specially useful to users that sort references in thematic
  files located at a given directory.

  <p>&nbsp;</p>
*/

/** \page relnotes Release Notes

\section relnotes0691 Release Note cb2Bib 0.6.91

  This release fixes a regression in the cb2Bib network capabilities.
  Network, and hence querying was erratic, both for the internal HTTP
  routines and for external clients. In addition to this fix, the
  <tt>netqinf.txt</tt> has been updated. PubMed is working again. Queries are
  also extended to include DOI's. A possible applicability will be for
  indexing a set of PDF articles with PDFImport. If the article contains its
  DOI number, and 'Perform Network Queries after automatic reference
  extractions' is checked, chances are that automatic extractions will work
  smooth.

  <p>&nbsp;</p>
*/

/** \page relnotes Release Notes

\section relnotes0690 Release Note cb2Bib 0.6.90

  cb2Bib has been ported from Qt3 to Qt4, a migration in its underlying system
  library. Qt experienced many changes and improvements in this major release
  upgrade. Relevant to cb2Bib, these changes will provide a better file
  management, word completion, faster searches, and better desktop integration.

  Upgrading to Qt4 it is not a "plug and recompile" game. Thorough
  refactoring and rewriting was required. The resulting cb2Bib code is
  cleaner and more suitable to further development. As one might expect,
  major upgrades introduce new bugs that must be fixed. The cb2Bib 0.6.90 is
  actually a preview version. It has approximately the same functionality
  than its predecessor. So, no additions were considered at this point. Its
  use, bug reporting, and feedback are encouraged. This will help to get
  sooner a stable cb2Bib 0.7.

  To compile it, type <tt>./configure</tt> as usual. The <tt>configure</tt>
  script calls the <tt>qmake</tt> tool to generate an appropriate
  <tt>Makefile</tt>. To make sure the right, Qt4 <tt>qmake</tt> is invocated,
  you can setup <tt>QTDIR</tt> environment variable prior to
  <tt>./configure</tt>. The <tt>configure</tt>'s call statement will then be
  <tt>'$QTDIR/bin/qmake'</tt>. E. g., type <tt>'setenv QTDIR /usr'</tt> if
  <tt>qmake</tt> happens to be at the directory<tt>/usr/bin</tt>.

  <p>&nbsp;</p>
*/

/** \page relnotes Release Notes

\section relnotes060 Release Note cb2Bib 0.6.0

  cb2Bib uses the internal tags <tt><<NewLine_n>></tt> and <tt><<Tab_n>></tt>
  to ease the creation of regular expressions for reference extraction. New
  line and tabular codes from the input stream are substituted by these
  numbered tags. Numbering new lines and tabulars gives an extra safety when
  writing down a regular expression. E. g., suppose field title is 'anything'
  between '<tt><<NewLine1>></tt> and <tt><<NewLine2>></tt>'. We can then easily
  write 'anything' as '.+' without the risk of overextending the caption to
  several '\\n' codes. On the other hand, one still can use
  <tt><<NewLine\\d>></tt> if not interested in a specific numbering. All these
  internal tags are later removed, once cb2Bib postprocesses the entry fields.

  The cb2Bib identified so far new lines by checking for '\\n' codes. I was
  unaware that this was a platform dependent, as well as a not completely
  accurate way of detecting new lines. McKay Euan reported that
  <tt><<NewLine_n>></tt> tags were not appearing as expected in the MacOSX
  version. I later learn that MacOSX uses '\\r' codes, and that Windows uses
  '\\r\\n', instead of '\\n' for new line encoding.

  This release addresses this issue. It is supposed now that the cb2Bib
  regular expressions will be more transferable among the different
  platforms. Extraction from plain text sources is expected to be completely
  platform independent. Extraction from web pages will still remain browser
  dependent. In fact, each browser adds its peculiar interpretation of a
  given HTML source. For example, in Wiley webpages we see the sectioning
  header 'Abstract' in its source and in several browsers, but we see, and
  get, 'ABSTRACT' if using Konqueror.

  What we pay for this more uniform approach is, however, a <b>break in
  compatibility</b> with previous versions of cb2Bib. Unix/Linux users should
  not expect many differences, though. Only one from the nine regular
  expressions in the examples needed to be modified, and the two contributed
  regular expressions work perfectly without any change. Windows users will
  not see a duplication of <tt><<NewLine_n>></tt> tags. To update previous
  expressions it should be enough just shifting the <tt><<NewLine_n>></tt>
  numbering. And, of course, any working regular expression that does not
  uses <tt><<NewLine_n>></tt> tags will still be working in this new version.

  Finally, just to mention that I do not have a MacOSX to test any of the
  cb2Bib releases in this particular platform. I am therefore assuming that
  these changes will fix the problem at hand. If otherwise, please, let me
  know. Also, let me know if release 0.6.0 'break' your own expressions. I
  consider this release a sort of experimental or beta version, and the
  previous version 0.5.3, will still be available during this testing period.

  <p>&nbsp;</p>
*/

/** \page relnotes Release Notes

\section relnotes050 Release Note cb2Bib 0.5.0

  Two issues had appeared regarding cb2Bib installation and deployment on
  MacOSX platforms.

  First, if you encounter a 'nothing to install'-error during installation on
  MacOSX 10.4.x using the cb2Bib binary installer available at naranja.umh.es/~atg/,
  please delete the cb2bib-receipts from <tt>/Library/Receipts</tt> and then
  rerun the installer. See also M. Bongard's clarifying note 'MACOSX 10.4.X
  "NOTHING TO INSTALL"-ERROR' for details.

  Second, and also extensible to other cb2Bib platform versions, if PDFImport
  issues the error message 'Failed to call <i>some_format_to_text</i>' tool,
  make sure such a tool is installed and available. Go to
  Configure->PDFImport, click at the 'Select External Convert Tool' button,
  and navigate to set its full path. Since version 0.5.0 the default full
  path for the MacOSX is already set, and pointing to
  <tt>/usr/local/bin/pdftotext</tt>.

  <p>&nbsp;</p>
*/

/** \page relnotes Release Notes

\section relnotes041 Release Note cb2Bib 0.4.1

  Qt/KDE applications emit notifications whenever they change the clipboard
  contents. cb2Bib uses these notifications to automatically start its
  'clipboard to BibTeX' processing. Other applications, however, does not
  notify about them. Since version 0.2.1, see \ref relnotes021, cb2Bib started
  checking the clipboard periodically. This checking was later disabled as a
  default, needing a few lines of code to be uncomented to activate it. Without
  such a checking, cb2Bib appears unresponsive when selecting/copying from
  e.g., acroread or Mozilla. This release includes the class
  <tt>clipboardpoll</tt> written by L. Lunak for the KDE's Klipper. Checking is
  performed in a very optimized way. This checking is enabled by default. If
  you experience problems with this feature, or if the required X11 headers
  aren't available, consider disabling it by typing <tt>./configure
  --disable-cbpoll</tt> prior to compilation. This will disable checking
  completely. If the naive, old checking is preferred, uncomment the four usual
  lines, <tt>./configure --disable-cbpoll</tt>, and compile.

  <p>&nbsp;</p>
*/

/** \page relnotes Release Notes

\section relnotes035 Release Note cb2Bib 0.3.5

  Releases 0.3.3 and 0.3.4 brought querying functionality to cb2Bib. In
  essence, cb2Bib was rearranged to accommodate copying and opening of
  network files. Queries were then implemented as user customizable HTML
  posts to journal databases. In addition, these arrangements permitted
  defining convenience, dynamic bookmarks that were placed at the cb2Bib's
  'About' panel.

  cb2Bib contains three viewing panels: 'About', 'Clipboard' and 'View
  BibTeX', being the 'Clipboard' panel the main working area. To keep cb2Bib
  simple, only two buttons, 'About' and 'View BibTeX', are set to navigate
  through the panels. The 'About' and 'View BibTeX' buttons are toggle
  buttons for momentarily displaying their corresponding panels. Guidance was
  so far provided by enabling/disabling the buttons.

  After the bookmark introduction, the 'About' panel has greatly increased
  its usefullness. Button functionality has been slightly redesigned now to
  avoid as many keystrokes and mouse clicks as possible. The buttons remain
  switchable, but they no longer disable the other buttons. User is guided by
  icon changes instead. Hopefully these changes will not be confusing or
  counterintuitive.

  Bookmarks and querying functionality are customizable through the
  <tt>netqinf.txt</tt> file, which is editable by pressing the <tt>Alt+B</tt>
  keys. Supported queries are of the form 'Journal-Volume-First Page'. cb2Bib
  parses <tt>netqinf.txt</tt> each time a query is performed. It looks for
  <tt>journal=<i>Full_Name|[code]</i></tt> to obtain the required information
  for a specific journal. Empty, '<tt>journal=</tt>' entries have a meaning
  of 'any journal'. New in this release, cb2Bib will test all possible
  queries for a given journal instead of giving up at the first <tt><i>No
  article found</i></tt> message. The query process stops at the first
  successfull hit or, otherwise, once <tt>netqinf.txt</tt> is parsed
  completely (in an equivalent way as the automatic pattern recognition
  works). This permits querying multiple -and incomplete- journal databases.

  Users should order the <tt>netqinf.txt</tt> file in a way it is more
  convenient. E.g., put PubMed in front of JACS if desired an automatic
  extraction. Or JACS in front of PubMed and extract from the journal web
  page, if author accented characters are wanted.

  So far, this querying functionality is still tagged as
  <em>experimental</em>. Either the querying itself or its syntax seem quite
  successful. However, downloading of PDF files, on windows OS + T1 network,
  <b>was found to freeze</b> once progress reaches the 30-50%. Any feedback
  on this issue will be greatly appreciated. Also, information on
  <tt>kfmclient</tt> equivalent tools for non KDE desktops would be worth to
  be included in the cb2Bib documentation.

  <p>&nbsp;</p>
*/

/** \page relnotes Release Notes

\section relnotes030 Release Note cb2Bib 0.3.0

  cb2Bib considers the whole set of authors as an author-string pattern. This
  string is later postprocessed, without requirements on the actual number of
  authors it may contain, or on how the names are written. Once considered
  author-string patterns, the extraction of bibliographic references by means
  of regular expressions becomes relatively simple.


  There are situations, however, where several author-strings are required.
  The following box shows one of these cases. Authors are grouped according
  to their affiliations. Selecting from 'F. N. First' to 'F. N. Fifth' would
  include 'First Affiliation' within the author string. Cleaning up whatever
  wording 'First Affiliation' may contain is a rather ill-posed problem.
  Instead, cb2Bib includes an <tt>Add Authors</tt> option. The way of
  operation is then to select 'F. N. First, F. N. Second, F. N. Third' and
  chose <tt>Authors</tt> and right after, select 'F. N. Fourth and F. N.
  Fifth' and chose <tt>Add Authors</tt>.

\verbatim
                                             Journal Name, 10, 1100-1105, 2004

                      AN EXAMPLE WITH MULTIPLE AUTHOR SETS

                     F. N. First, F. N. Second, F. N. Third
                                First Affiliation

                           F. N. Fourth and F. N. Fifth
                                Second Affiliation

  Abstract: Select from "Journal Name ..." to "... second author set.". The 'F.
  N. First, F. N. Second, F. N. Third' author string is automatically processed
  as one author set, while 'F. N. Fourth and F. N. Fifth' is processed as
  another, second author set.
\endverbatim

  At this point in the manual extraction, the user was faced with a red
  <tt><<moreauthors>></tt> tag in the cb2Bib clipboard panel. The
  <tt><<moreauthors>></tt> tag was intended to warn the user about the fact
  that cb2Bib would not be able to consider the resulting extraction pattern
  as a valid, general regular expression. Usual regular expressions are built
  up from an a priori known level of nesting. In these cases, however, the
  level of nesting is variable. It depends on the number of different
  affiliations occurring in a particular reference.

  So far the <tt><<moreauthors>></tt> tag has become a true FAQ about cb2Bib
  and a source of many confusions. There is no real need, however, for such
  an user warning. The <tt><<moreauthors>></tt> has therefore been removed
  and cb2Bib has taken an step further, to its 0.3.0 version.

  The cb2Bib 0.3.0 manual extraction works as usual. By clicking
  <tt>Authors</tt> the Authors edit line is reseted and selection contents
  moved there. Alternatively, if <tt>Add Authors</tt> is clicked, selection
  contents is added to the author field. On this version, however, both
  operations are tagged as <tt><<author>></tt> (singular form, as it is the
  BibTeX keyword for Authors). The generated extraction pattern can now
  contain any number of <tt><<author>></tt> fields.

  In automatic mode, cb2Bib now adds all <tt>author</tt> captions to Authors.
  In this way, cb2Bib can treat interlaced author-affiliation cases.
  Obviously, users needing such extractions will have to write particular
  regular expressions for cases with one set of authors, for two sets, and so
  on. Eventhough it is not rare a work having a hundred of authors, it would
  be quite umprobable that they were working on so many different
  institutions. Therefore, few regular expressions should actually be
  required in practice. Although not elegant, this breaks what was a cb2Bib
  limitation and broadens its use when extracting from PDF sources. Remember
  here to sort these regular expressions in decreasing order, since at
  present, cb2Bib stops at the first hit. Also, consider <tt>Any Pattern</tt>
  to get ride of the actual affiliation contents, as you might not want to
  extract authors addresses.

  <p>&nbsp;</p>
*/

/** \page relnotes Release Notes

\section relnotes027 Release Note cb2Bib 0.2.7

  The cb2Bib 0.2.7 release introduces multiple retrieving from PDF files. PDF
  documents are becoming more and more widely used, not only to transfer and
  printing articles, but also are substituting the personal paper files and
  classifiers for the electronic equivalents.

  cb2Bib is intended to help updating personal databases of papers. It is a
  tool focused on what is left behind in database retrieving. Cases such as
  email alerts, or inter colleague references and PDF sharing are example
  situations. Though in an electronic format, sources are not standardized or
  not globally used as to permit using habitual import filters in reference
  managers. cb2Bib is designed to consider a direct user intervention, either
  by creating its own useful filters or by a simple copy-paste assistance
  when handtyping.

  Hopefully someday cb2Bib will be able to take that old directory, with
  perhaps a few hundreds of papers, to automatically index the references and
  rename the files by author, in a consistent manner. The required mechanism
  is already there, in this version. But I guess that this new feature will
  manifest some present limitations in cb2Bib. For instance, most printed and
  PDF papers interlace author names and affiliations. cb2Bib doesn't have the
  means to automatically discern an author name from a department or street
  name. So far one needs to manually use the 'Add to Authors' feature to deal
  with these situations. Also, the managing of regular expressions needs
  developing, specially thinking in the spread variety of design patterns in
  publications.

  In summary, this current version is already useful in classifying and
  extracting the reference of that couple of papers that someone send right
  before submitting a work. A complete unsupervised extraction is still far
  away, however.

  <p>&nbsp;</p>
*/

/** \page relnotes Release Notes

\section relnotes021 Release Note cb2Bib 0.2.1

  The cb2Bib mechanism 'select-and-catch' failed in some cases. Acrobat and
  Mozilla selections were not always notified to cb2Bib. Indeed, this 'window
  manager - application' connection seems to be broken on a KDE 3.3.0 Qt 3.3.3
  system.

  The cb2Bib 0.2.1 continues to listen to system clipboard change
  notifications, whenever they are received and whenever cb2Bib is on
  connected mode. Additionally, the cb2Bib 0.2.1 periodically checks for
  changes in the system clipboard. Checks are performed every second,
  approximately. This permits cb2Bib to work as usual, although one could
  experience 1-2 seconds delays in systems where the automatic notification
  is broken.

  If the 'select-and-catch' functionality appears 'sticky', possibly
  happening while using non KDE applications from where text is selected,
  check the source file <tt>c2bclipboard</tt><tt>.cpp</tt>, look for
  <tt>'Setting timer'</tt>, and set variable <tt>interval</tt> to 1000. This
  is the interval of time in ms that cb2Bib will use to check for clipboard
  changes.

  <p>&nbsp;</p>
*/


cb2Bib::cb2Bib(QWidget* parentw)
    : QMainWindow(parentw), _connected(false), _is_check_repeated_done(false), _modified(false), _tagged_view_mode(false)
{
    _settingsP = c2bSettingsP;
    ui.setupUi(this);
    connect(ui.id, SIGNAL(textChanged(QString)), this, SLOT(setWindowTitle(QString)));

    // Creating cb2Bib global resources
    c2b* c2b_resources = new c2b(this, this);
    connect(c2b_resources, SIGNAL(statusMessage(QString)), this, SLOT(showMessage(QString)));
    connect(c2b_resources, SIGNAL(searchInFiles(QString,QString)), this, SLOT(doSearchInFiles(QString,QString)));

    // Actions and shortcuts
    c2bUtils::addSeparator(this);
    addAction(ui.checkRepeatedAction);
    _settingsP->setKeysequence("Shortcuts/cb2Bib/", ui.checkRepeatedAction);
    c2bUtils::addSeparator(this);
    addAction(ui.clearFieldsAction);
    _settingsP->setKeysequence("Shortcuts/cb2Bib/", ui.clearFieldsAction);
    addAction(ui.guessFieldsAction);
    _settingsP->setKeysequence("Shortcuts/cb2Bib/", ui.guessFieldsAction);
    addAction(ui.startEngineAction);
    _settingsP->setKeysequence("Shortcuts/cb2Bib/", ui.startEngineAction);
    c2bUtils::addSeparator(this);
    addAction(ui.preparseClipboardAction);
    _settingsP->setKeysequence("Shortcuts/cb2Bib/", ui.preparseClipboardAction);
    addAction(ui.postprocessBibTeXAction);
    _settingsP->setKeysequence("Shortcuts/cb2Bib/", ui.postprocessBibTeXAction);
    c2bUtils::addSeparator(this);
    addAction(ui.editBookmarksAction);
    _settingsP->setKeysequence("Shortcuts/cb2Bib/", ui.editBookmarksAction);
    addAction(ui.editAbbreviationsAction);
    _settingsP->setKeysequence("Shortcuts/cb2Bib/", ui.editAbbreviationsAction);
    addAction(ui.editRegExpsAction);
    _settingsP->setKeysequence("Shortcuts/cb2Bib/", ui.editRegExpsAction);
    c2bUtils::addSeparator(this);
    addAction(ui.openAnnoteAction);
    _settingsP->setKeysequence("Shortcuts/cb2Bib/", ui.openAnnoteAction);
    c2bUtils::addSeparator(this);
    addAction(ui.insertRegExpAction);
    _settingsP->setKeysequence("Shortcuts/cb2Bib/", ui.insertRegExpAction);
    addAction(ui.viewTaggedClipEditAction);
    _settingsP->setKeysequence("Shortcuts/cb2Bib/", ui.viewTaggedClipEditAction);
    setAcceptDrops(true);

    c2bUtils::addSeparator(ui.file);
    ui.file->addAction(ui.selectFileAction);
    _settingsP->setKeysequence("Shortcuts/cb2Bib/", ui.selectFileAction);
    ui.file->addAction(ui.openFileDocumentAction);
    _settingsP->setKeysequence("Shortcuts/cb2Bib/", ui.openFileDocumentAction);
    ui.openFileDocumentAction->setEnabled(false);

    QShortcut* sc(new QShortcut(this));
    _settingsP->setKeysequence("Shortcuts/cb2Bib/Delete Temporary BibTeX File", sc);
    connect(sc, SIGNAL(activated()), this, SLOT(deleteTmpBib()));
    sc = new QShortcut(this);
    _settingsP->setKeysequence("Shortcuts/cb2Bib/Write Metadata to Document", sc);
    connect(sc, SIGNAL(activated()), this, SLOT(addMetadata()));
    sc = new QShortcut(this);
    _settingsP->setKeysequence("Shortcuts/cb2Bib/Toggle Reference Tabs", sc);
    connect(sc, SIGNAL(activated()), this, SLOT(toggleReferenceTabs()));
    sc = new QShortcut(QKeySequence(Qt::Key_F2), this); // Made consistent with c2bCiter and c2bEditor
    connect(sc, SIGNAL(activated()), this, SLOT(hide()));

    ClipEdit = new c2bClipEdit(c2bClipEdit::Editor, this);
    ClipEdit->setObjectName("ClipEdit");
    ClipEdit->addActions(actions());
    ui.stackedWidget->addWidget(ClipEdit);

    AboutBrowser = new c2bTextBrowser(this);
    AboutBrowser->setObjectName("AboutBrowser");
    AboutBrowser->addActions(actions());
    ui.stackedWidget->addWidget(AboutBrowser);

    BibBrowser = new c2bClipEdit(c2bClipEdit::Browser, this);
    BibBrowser->setObjectName("BibBrowser");
    BibBrowser->addActions(actions());
    ui.stackedWidget->addWidget(BibBrowser);
    connect(AboutBrowser, SIGNAL(anchorClicked(QUrl)), this, SLOT(linkClicked(QUrl)));
    connect(AboutBrowser, SIGNAL(highlighted(QString)), this, SLOT(showLink(QString)));

    // Connect Actions
    connect(ui.checkRepeatedAction, SIGNAL(triggered()), this, SLOT(checkRepeated()));
    connect(ui.clearFieldsAction, SIGNAL(triggered()), this, SLOT(c2bInit()));
    connect(ui.editAbbreviationsAction, SIGNAL(triggered()), this, SLOT(abbreviationsEditor()));
    connect(ui.editBookmarksAction, SIGNAL(triggered()), this, SLOT(bookmarksEditor()));
    connect(ui.editRegExpsAction, SIGNAL(triggered()), this, SLOT(regExpsEditor()));
    connect(ui.guessFieldsAction, SIGNAL(triggered()), this, SLOT(guessFields()));
    connect(ui.insertRegExpAction, SIGNAL(triggered()), this, SLOT(insertRegExp()));
    connect(ui.openAnnoteAction, SIGNAL(triggered()), this, SLOT(openAnnote()));
    connect(ui.openFileDocumentAction, SIGNAL(triggered()), this, SLOT(openFileDocument()));
    connect(ui.postprocessBibTeXAction, SIGNAL(triggered()), this, SLOT(postprocessBibTeX()));
    connect(ui.preparseClipboardAction, SIGNAL(triggered()), this, SLOT(preparseClipboard()));
    connect(ui.selectFileAction, SIGNAL(triggered()), this, SLOT(selectFile()));
    connect(ui.startEngineAction, SIGNAL(triggered()), this, SLOT(restartEngine()));
    connect(ui.viewTaggedClipEditAction, SIGNAL(triggered(bool)), this, SLOT(setTaggedClipEditMode(bool)));
    setBibMenu();
    _pdfImportP = 0;
    _searchInFilesP = 0;
    setTaggedClipEditMode(false);

    // Set checkRepeated
    ui.checkRepeatedAction->setVisible(false);
    connect(ui.author, SIGNAL(textChanged(QString)), this, SLOT(updateCheckRepeatedAction()));
    connect(ui.booktitle, SIGNAL(textChanged(QString)), this, SLOT(updateCheckRepeatedAction()));
    connect(ui.editor, SIGNAL(textChanged(QString)), this, SLOT(updateCheckRepeatedAction()));
    connect(ui.id, SIGNAL(textChanged(QString)), this, SLOT(updateCheckRepeatedAction()));
    connect(ui.title, SIGNAL(textChanged(QString)), this, SLOT(updateCheckRepeatedAction()));

    // cb2Bib Settings
    loadSettings();
    connect(_settingsP, SIGNAL(newSettings()), this, SLOT(loadSettings()));
    resize(_settingsP->value("cb2Bib/size", size()).toSize());
    ui.bibtexfile->completer()->setCompletionMode(QCompleter::PopupCompletion);
    updateBibfile(_settingsP->fileName("cb2Bib/BibTeXFile"));

    // Setting Bibliographic Parser
    _bpP = c2b::bibParser();
    setWidgetMapping();
    ui.AddBibB->setEnabled(_modified);

    // Setting cb2bib network queries
    _netQP = new c2bNetworkQuery(_bpP, c2b::net(), this);
    connect(_netQP, SIGNAL(statusMessage(QString)), c2b_resources, SIGNAL(statusMessage(QString)));
    connect(_netQP, SIGNAL(queryEnded(bool,QString,QString)), this, SLOT(netQueryEnded(bool,QString,QString)));

    // Set citer
    if (_settingsP->cl_citer)
    {
        _citerP = new c2bCiterWidget;
        _citerP->setTrayIcon();
        _citerP->load();
        connect(_citerP, SIGNAL(openAnnote()), this, SLOT(openAnnote()));
        connect(_citerP, SIGNAL(openFile(QString)), this, SLOT(bibEditor(QString)));
    }
    else
        _citerP = 0;

    // Connecting cb2Bib clipboard and start
    c2bClipboard* cbP = c2b::clipboard();
    connect(cbP, SIGNAL(cbDataChanged(QString)), this, SLOT(dataChanged(QString)));
    on_ConnectB_clicked(); // Set button and update _connected
    dataChanged(QString());
    if (_settingsP->cl_bibedit)
        initAsBibTeXEditor();
}

cb2Bib::~cb2Bib()
{
    delete _citerP;
    delete _searchInFilesP;
}


/****************************************************************************

  GUI FUNCTIONALITY

*****************************************************************************/

void cb2Bib::show()
{
    if (_settingsP->cl_citer && _citerP)
        _citerP->toggleVisible();
    else if (!_settingsP->cl_bibedit)
        QMainWindow::show();
}

void cb2Bib::on_ViewAboutB_clicked()
{
    if (ui.stackedWidget->currentWidget() == AboutBrowser)
    {
        ui.stackedWidget->setCurrentWidget(ClipEdit);
        ClipEdit->setFocus();
    }
    else
    {
        const QColor linkColor(palette().buttonText().color());
        const QString sheet(QString::fromLatin1("a { text-decoration: underline; color: %1 }").arg(linkColor.name()));
        AboutBrowser->document()->setDefaultStyleSheet(sheet);
        const QString AboutS(
            tr("<br /><br /><p align=\"center\"><b>cb2Bib %1</b></p>"
               "<p align=\"center\">"
               "Bibliographic Reference Extracting and Managing Tool<br />"
               "<p align=\"center\"><img src=\":/icons/icons/cb2bib128.png\"></p>"
               "<p align=\"center\">"
               "<a href=\"https://www.molspaces.com/cb2bib/\">"
               "cb2Bib Help and User's Guide</a></p><br />"
               "<p align=\"center\">Additional Functionality:</p>"
               "<table border=\"1\" align=\"center\" cellspacing=\"0\" cellpadding=\"4\">"
               "<thead><tr>"
               "<th>Keys</th><th>Description</th></tr>"
               "</thead><tbody><tr>"
               "<td>" +
               _settingsP->ksname("Shortcuts/cb2Bib/Check Repeated") + "</td><td>Check repeated</td></tr><tr>"
               "<td>" +
               _settingsP->ksname("Shortcuts/cb2Bib/Delete Temporary BibTeX File") +
               "</td><td>Delete temporary BibTeX file</td></tr><tr>"
               "<td>" +
               _settingsP->ksname("Shortcuts/cb2Bib/Edit Bookmarks") + "</td><td>Edit bookmarks</td></tr><tr>"
               "<td>" +
               _settingsP->ksname("Shortcuts/cb2Bib/Edit Journal Abbreviations") +
               "</td><td>Edit journal abbreviations</td></tr><tr>"
               "<td>" +
               _settingsP->ksname("Shortcuts/cb2Bib/Edit Regular Expressions") +
               "</td><td>Edit regular expressions</td></tr><tr>"
               "<td>" +
               _settingsP->ksname("Shortcuts/cb2Bib/Insert Regular Expression") +
               "</td><td>Insert regular expression</td></tr><tr>"
               "<td>" +
               _settingsP->ksname("Shortcuts/cb2Bib/Open Document") + "</td><td>Open document</td></tr><tr>"
               "<td>" +
               _settingsP->ksname("Shortcuts/cb2Bib/Postprocess BibTeX") + "</td><td>Postprocess BibTeX</td></tr><tr>"
               "<td>" +
               _settingsP->ksname("Shortcuts/cb2Bib/Preparse Clipboard") + "</td><td>Preparse clipboard</td></tr><tr>"
               "<td>" +
               _settingsP->ksname("Shortcuts/cb2Bib/Restart Recognition") + "</td><td>Restart recognition</td></tr><tr>"
               "<td>" +
               _settingsP->ksname("Shortcuts/cb2Bib/Select Document File") + "</td><td>Select document file</td></tr><tr>"
               "<td>" +
               _settingsP->ksname("Shortcuts/cb2Bib/Annote Editor") + "</td><td>Open cb2Bib Annote</td></tr><tr>"
               "<td>" +
               _settingsP->ksname("Shortcuts/cb2Bib/Toggle Reference Tabs") +
               "</td><td>Toggle reference tabs</td></tr><tr>"
               "<td>" +
               _settingsP->ksname("Shortcuts/cb2Bib/Write Metadata to Document") +
               "</td><td>Write metadata to document</td></tr><tr>"
               "<td>Esc</td><td>Quit cb2Bib popup menu</td></tr><tr>"
               "<td>Right Click</td><td>Show cb2Bib main panel popup menu"
               "</td></tr></tbody>"
               "</table>"
               "<br /> %2 <br />"
               "<p align=\"center\">Copyright (C) 2004-2021 by Pere Constans<br />"
               "<a href=\"https://www.molspaces.com/cb2bib/\">"
               "https://www.molspaces.com/cb2bib/</a></p>&nbsp;"
               "<p align=\"center\"><i>cb2Bib is licensed under the terms of the "
               "<a href=\"https://www.gnu.org/licenses/gpl-3.0.html\">"
               "GNU General Public License</a> version 3"
               "</i><br /></p>&nbsp;")
            .arg(C2B_VERSION, c2b::netqinf()->bookmarksToHtml()));
        const int scrollPosition(AboutBrowser->verticalScrollBar()->value());
        AboutBrowser->setHtml(AboutS);
        AboutBrowser->verticalScrollBar()->setValue(scrollPosition);
        ui.stackedWidget->setCurrentWidget(AboutBrowser);
        AboutBrowser->setFocus();
    }
    updateViewButtons();
}

void cb2Bib::on_ConfigureB_clicked()
{
    c2b::configure();
}

void cb2Bib::on_SearchInFilesB_clicked()
{
    doSearchInFiles();
}

void cb2Bib::on_PdfImportB_clicked()
{
    if (!_pdfImportP)
    {
        _pdfImportP = new c2bPdfImport;
        _pdfImportP->setAttribute(Qt::WA_DeleteOnClose);
        connect(this, SIGNAL(addedBibToFile(QString)), _pdfImportP, SLOT(processNext()));
        connect(this, SIGNAL(endedProcessing(bool)), _pdfImportP, SLOT(referenceExtacted(bool)));
        connect(_pdfImportP, SIGNAL(textProcessed(QString)), this, SLOT(forceDataChange(QString)));
        connect(_pdfImportP, SIGNAL(fileProcessed(QString)), this, SLOT(fileDropped(QString)));
        connect(_pdfImportP, SIGNAL(saveReferenceRequest()), this, SLOT(on_AddBibB_clicked()));
        connect(_pdfImportP, SIGNAL(setClipboardDisabled(bool)), ui.ConnectB, SLOT(setDisabled(bool)));
        showMessage(tr("PDF Import launched."));
    }
    _pdfImportP->show();
}

void cb2Bib::on_ExitB_clicked()
{
    c2b::instance()->exitRequested();
}

void cb2Bib::on_ConnectB_clicked()
{
    if (_connected)
    {
        ui.ConnectB->setIcon(QIcon(C2B_ICON_DIR + C2B_ICON_DISCONNECT_B));
        ui.ConnectB->setStatusTip(buttonStatusTip(tr("Connect clipboard"), ui.ConnectB->shortcut()));
        _connected = false;
    }
    else
    {
        ui.ConnectB->setIcon(QIcon(C2B_ICON_DIR + C2B_ICON_CONNECT_B));
        ui.ConnectB->setStatusTip(buttonStatusTip(tr("Disconnect clipboard"), ui.ConnectB->shortcut()));
        _connected = true;
    }
}

void cb2Bib::on_MakeNetworkQueryB_clicked()
{
    makeNetQuery();
}

void cb2Bib::on_ViewBibB_clicked()
{
    if (ui.stackedWidget->currentWidget() == BibBrowser)
    {
        ui.stackedWidget->setCurrentWidget(ClipEdit);
        ClipEdit->setFocus();
    }
    else
    {
        BibBrowser->updatePlainText(_bpP->toBibTeX());
        ui.stackedWidget->setCurrentWidget(BibBrowser);
        BibBrowser->setFocus();
    }
    updateViewButtons();
}

void cb2Bib::on_AddBibB_clicked()
{
    // Prepare Save Reference to file
    ui.AddBibB->setEnabled(false);
    if (!_is_check_repeated_done && _settingsP->value("cb2Bib/CheckRepeatedOnSave").toBool())
    {
        _is_check_repeated_done = true;
        if (isReferenceRepeated())
        {
            ui.AddBibB->setEnabled(_modified);
            return;
        }
    }
    QFile bibtexfile(ui.bibtexfile->currentText());
    bool is_writable;
    if (bibtexfile.exists())
        is_writable = bibtexfile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
    else
        is_writable = bibtexfile.open(QIODevice::WriteOnly | QIODevice::Text);
    if (!is_writable)
    {
        QMessageBox::information(this, tr("Information - cb2Bib"),
                                 tr("Unable to open file %1 for writing.\nError: '%2'.")
                                 .arg(ui.bibtexfile->currentText(), bibtexfile.errorString()),
                                 QMessageBox::Ok);
        ui.AddBibB->setEnabled(_modified);
        return;
    }
    if (_dropped_document_file.isEmpty() || ui.file->text().isEmpty() || !_settingsP->value("cb2Bib/MovePdf").toBool())
    {
        _target_document_file.clear();
        addToFile(true);
    }
    else
    {
        _target_document_file = c2bUtils::documentAbsoluteName(
                                    _settingsP->value("cb2Bib/RelativePdfDirectory").toBool(), ui.bibtexfile->currentText(),
                                    _settingsP->fileName("cb2Bib/PdfDirectory"), ui.file->text());
        const QString doc_dir_name(QFileInfo(_target_document_file).absolutePath());
        QDir doc_dir(doc_dir_name);
        if (!doc_dir.exists())
            if (!doc_dir.mkpath(doc_dir_name))
            {
                QMessageBox::information(this, tr("Information - cb2Bib"),
                                         tr("Unable to create directory %1.").arg(doc_dir_name), QMessageBox::Ok);
                ui.AddBibB->setEnabled(_modified);
                return;
            }
        const network::Action CopyMovePdf(network::actionType(_settingsP->value("cb2Bib/CopyMovePdf").toString()));
        c2b::net()->getFile(_dropped_document_file, _target_document_file, CopyMovePdf, this, SLOT(addToFile(bool)));
    }
}

void cb2Bib::on_EditBibTeXB_clicked()
{
    bibEditor(ui.bibtexfile->currentText());
}

void cb2Bib::on_BibTeXDir_clicked()
{
    const QString fn(c2bFileDialog::getFilename(this, "Select a BibTeX filename", ui.bibtexfile->currentText(),
                     "BibTeX (*.bib);;All (*)"));
    if (!fn.isEmpty())
        updateBibfile(fn);
}

void cb2Bib::loadSettings()
{
    ClipEdit->setFont(_settingsP->c2bMonoFont);
    BibBrowser->setFont(_settingsP->c2bMonoFont);
    AboutBrowser->setFont(_settingsP->c2bMonoFont);

    ui.AddBibB->setShortcut(QKeySequence::Save);
    ui.EditBibTeXB->setShortcut(QKeySequence::Open);
    ui.SearchInFilesB->setShortcut(QKeySequence::Find);
    ui.ExitB->setShortcut(QKeySequence::Quit);

    ui.BibTeXDir->setShortcut(_settingsP->keysequence("Shortcuts/cb2Bib/Select BibTeX File"));
    ui.ConfigureB->setShortcut(_settingsP->keysequence("Shortcuts/cb2Bib/Button Configure"));
    ui.ConnectB->setShortcut(_settingsP->keysequence("Shortcuts/cb2Bib/Button Toggle Connection"));
    ui.MakeNetworkQueryB->setShortcut(_settingsP->keysequence("Shortcuts/cb2Bib/Button Network Query"));
    ui.PdfImportB->setShortcut(_settingsP->keysequence("Shortcuts/cb2Bib/Button Start PDFImport"));
    ui.ViewAboutB->setShortcut(_settingsP->keysequence("Shortcuts/cb2Bib/Button About and Bookmarks"));
    ui.ViewBibB->setShortcut(_settingsP->keysequence("Shortcuts/cb2Bib/Button View BibTeX"));

    ui.AddBibB->setStatusTip(buttonStatusTip(tr("Save reference to BibTeX file"), ui.AddBibB->shortcut()));
    ui.BibTeXDir->setStatusTip(buttonStatusTip(tr("Select BibTeX file"), ui.BibTeXDir->shortcut()));
    ui.ConfigureB->setStatusTip(buttonStatusTip(tr("Configure cb2Bib"), ui.ConfigureB->shortcut()));
    ui.ConnectB->setStatusTip(
        buttonStatusTip(_connected ? tr("Disconnect clipboard") : tr("Connect clipboard"), ui.ConnectB->shortcut()));
    ui.EditBibTeXB->setStatusTip(buttonStatusTip(tr("Open BibTeX file"), ui.EditBibTeXB->shortcut()));
    ui.ExitB->setStatusTip(buttonStatusTip(tr("Close all windows and exit"), ui.ExitB->shortcut()));
    ui.MakeNetworkQueryB->setStatusTip(
        buttonStatusTip(tr("Network query for current reference"), ui.MakeNetworkQueryB->shortcut()));
    ui.PdfImportB->setStatusTip(
        buttonStatusTip(tr("Import references from a set of PDF files"), ui.PdfImportB->shortcut()));
    ui.SearchInFilesB->setStatusTip(
        buttonStatusTip(tr("Search BibTeX file for references"), ui.SearchInFilesB->shortcut()));
    updateViewButtons();
}

QString cb2Bib::buttonStatusTip(const QString& ms, const QKeySequence& ks) const
{
    if (ks.isEmpty())
        return ms;
    else
        return ms + QLatin1String("  -  ") + ks.toString(QKeySequence::NativeText);
}

void cb2Bib::updateViewButtons()
{
    QWidget* viewing = ui.stackedWidget->currentWidget();
    if (viewing == BibBrowser)
    {
        ui.ViewBibB->setIcon(QIcon(C2B_ICON_DIR + C2B_ICON_VIEWC2B_B));
        ui.ViewAboutB->setIcon(QIcon(C2B_ICON_DIR + C2B_ICON_ABOUT_B));
        ui.ViewBibB->setStatusTip(buttonStatusTip(tr("View cb2Bib clipboard"), ui.ViewBibB->shortcut()));
        ui.ViewAboutB->setStatusTip(
            buttonStatusTip(tr("About cb2bib and cb2bib bookmarks"), ui.ViewAboutB->shortcut()));
    }
    else if (viewing == AboutBrowser)
    {
        ui.ViewBibB->setIcon(QIcon(C2B_ICON_DIR + C2B_ICON_VIEWBIB_B));
        ui.ViewAboutB->setIcon(QIcon(C2B_ICON_DIR + C2B_ICON_ABOUT_B_BACK));
        ui.ViewBibB->setStatusTip(buttonStatusTip(tr("View BibTeX for current reference"), ui.ViewBibB->shortcut()));
        ui.ViewAboutB->setStatusTip(buttonStatusTip(tr("Back to cb2Bib clipboard"), ui.ViewAboutB->shortcut()));
    }
    else
    {
        ui.ViewBibB->setIcon(QIcon(C2B_ICON_DIR + C2B_ICON_VIEWBIB_B));
        ui.ViewAboutB->setIcon(QIcon(C2B_ICON_DIR + C2B_ICON_ABOUT_B));
        ui.ViewBibB->setStatusTip(buttonStatusTip(tr("View BibTeX for current reference"), ui.ViewBibB->shortcut()));
        ui.ViewAboutB->setStatusTip(
            buttonStatusTip(tr("About cb2bib and cb2bib bookmarks"), ui.ViewAboutB->shortcut()));
    }
}

void cb2Bib::toggleReferenceTabs()
{
    if (ui.tabWidget->currentIndex() == 0)
        ui.tabWidget->setCurrentIndex(1);
    else
        ui.tabWidget->setCurrentIndex(0);
}

void cb2Bib::updateBibfile(const QString& fn)
{
    ui.bibtexfile->clear();
    QFileInfo fi(fn);
    const QStringList flist(fi.isDir() ? c2bUtils::filesInDir(fn, QStringList() << "*.bib")
                            : c2bUtils::filesInDir(fi.absolutePath(), QStringList() << "*.bib"));
    for (int i = 0; i < flist.count(); ++i)
        ui.bibtexfile->addItem(flist.at(i));
    const int index(ui.bibtexfile->findText(fn));
    if (index == -1)
        ui.bibtexfile->setEditText(fn);
    else
        ui.bibtexfile->setCurrentIndex(index);
}

void cb2Bib::showLink(const QString& ln)
{
    statusBar()->showMessage(c2b::encodeLink(ln), C2B_MESSAGE_TIME);
}

void cb2Bib::showMessage(const QString& ms)
{
    statusBar()->showMessage(ms, C2B_MESSAGE_TIME);
}

void cb2Bib::dragEnterEvent(QDragEnterEvent* qevent)
{
    if (qevent->mimeData()->hasUrls())
        qevent->acceptProposedAction();
}

void cb2Bib::dropEvent(QDropEvent* qevent)
{
    QList<QUrl> fns = qevent->mimeData()->urls();
    if (fns.count() > 0)
    {
        if (fns.at(0).scheme() == "file")
        {
            c2bUtils::setWidgetOnTop(this);
            fileDroppedByUser(fns.at(0).toLocalFile().trimmed());
        }
        else
            fileDroppedByUser(fns.at(0).toString().trimmed());
    }
    qevent->acceptProposedAction();
}

void cb2Bib::fileDroppedByUser(const QString& fn)
{
    if (fn.isEmpty())
        return;
    bool has_bibtex(false);
    if (_settingsP->value("cb2Bib/AddMetadata").toBool())
    {
        const QString metadata(c2b::documentMetadata(fn));
        if (!metadata.isEmpty())
        {
            QString text(ClipEdit->toPlainText());
            if (_settingsP->value("cb2Bib/PreAppendMetadata").toString() == "prepend")
                text = metadata + text;
            else
                text = text + '\n' + metadata;
            has_bibtex = _bpP->hasBibTeX(metadata);
            if (has_bibtex)
                forceDataChange(text);
            else
                ClipEdit->setText(text);
        }
    }
    fileDropped(fn);
    if (!has_bibtex)
        showMessage(tr("Scheduled inclusion of file '%1'.").arg(fn));
    if (QFileInfo::exists(fn))
        _settingsP->setFilename("cb2Bib/LastDroppedFile", fn);
}

void cb2Bib::fileDropped(const QString& fn)
{
    if (fn.isEmpty())
        return;
    _dropped_document_file = fn.trimmed();
    ui.openFileDocumentAction->setEnabled(true);
    ui.openFileDocumentAction->setText(tr("Open '%1'").arg(_dropped_document_file));
    setDocumentFilename();
    if (_settingsP->value("cb2Bib/MovePdf").toBool())
        ui.file->setStatusTip(tr("From file '%1'.").arg(_dropped_document_file));
}

void cb2Bib::closeEvent(QCloseEvent* qevent)
{
    if (_pdfImportP)
        _pdfImportP->close();
    if (_searchInFilesP)
        _searchInFilesP->close();
    _settingsP->setValue("cb2Bib/size", size());
    _settingsP->setFilename("cb2Bib/BibTeXFile", QFileInfo(ui.bibtexfile->currentText()).absoluteFilePath());
    qevent->accept();
}

void cb2Bib::setTaggedClipEditMode(bool tagged)
{
    _tagged_view_mode = tagged;
    ui.insertRegExpAction->setEnabled(tagged);
    ClipEdit->setTaggedViewMode(tagged);
    if (_tagged_view_mode)
        _bib_menu->setAnyPatternText(tr("Any Pattern"));
    else
        _bib_menu->setAnyPatternText(tr("Delete"));
    ui.stackedWidget->setCurrentWidget(ClipEdit);
    ClipEdit->setFocus();
    updateViewButtons();
}

void cb2Bib::doSearchInFiles(const QString& string, const QString& fn)
{
    if (!_searchInFilesP)
    {
        _searchInFilesP = new c2bSearchInFiles(ui.bibtexfile->currentText());
        connect(ui.bibtexfile, SIGNAL(editTextChanged(QString)), _searchInFilesP, SLOT(setBibTeXFile(QString)));
        connect(_searchInFilesP, SIGNAL(searchDone(QString,bibSearcher*)), this,
                SLOT(bibEditor(QString,bibSearcher*)));
        showMessage(tr("BibTeX Search launched."));
    }
    if (fn.isEmpty())
        _searchInFilesP->setBibTeXFile(ui.bibtexfile->currentText());
    else
        _searchInFilesP->setBibTeXFile(fn);
    _searchInFilesP->setCurrentText(string);
    _searchInFilesP->show();
}

void cb2Bib::setWindowTitle(const QString& title)
{
    if (title.isEmpty())
        QMainWindow::setWindowTitle(tr("cb2Bib"));
    else
        QMainWindow::setWindowTitle(tr("%1 - cb2Bib").arg(title));
}


/****************************************************************************

  CB2BIB FUNCTIONALITY

*****************************************************************************/

void cb2Bib::setWidgetMapping()
{
    _bpP->addField("abstract", ui.abstract);
    _bpP->addField("address", ui.address);
    _bpP->addField("annote", ui.annote);
    _bpP->addField("author", ui.author);
    _bpP->addField("booktitle", ui.booktitle);
    _bpP->addField("chapter", ui.chapter);
    _bpP->addField("doi", ui.doi);
    _bpP->addField("edition", ui.edition);
    _bpP->addField("editor", ui.editor);
    _bpP->addField("eprint", ui.eprint);
    _bpP->addField("file", ui.file);
    _bpP->addField("id", ui.id);
    _bpP->addField("institution", ui.institution);
    _bpP->addField("isbn", ui.isbn);
    _bpP->addField("issn", ui.issn);
    _bpP->addField("journal", ui.journal);
    _bpP->addField("keywords", ui.keywords);
    _bpP->addField("month", ui.month);
    _bpP->addField("note", ui.note);
    _bpP->addField("number", ui.number);
    _bpP->addField("organization", ui.organization);
    _bpP->addField("pages", ui.pages);
    _bpP->addField("publisher", ui.publisher);
    _bpP->addField("school", ui.school);
    _bpP->addField("series", ui.series);
    _bpP->addField("title", ui.title);
    _bpP->addField("url", ui.url);
    _bpP->addField("volume", ui.volume);
    _bpP->addField("year", ui.year);
    _bpP->addTypes(ui.typecombo);
    _bpP->setWidgetMapping();
    connect(_bpP, SIGNAL(bibModified(bool)), this, SLOT(bibModified(bool)));
}

void cb2Bib::setBibMenu()
{
    _bib_menu = new c2bBibMenu(this);
    connect(_bib_menu->addAuthorAction(), SIGNAL(triggered()), this, SLOT(addAuthors()));
    connect(_bib_menu->addEditorAction(), SIGNAL(triggered()), this, SLOT(addEditors()));
    connect(_bib_menu->anyPatternAction(), SIGNAL(triggered()), this, SLOT(anyPattern()));
    connect(ClipEdit, SIGNAL(userEndedSelection(QPoint)), this, SLOT(readField(QPoint)));
}

void cb2Bib::readField(const QPoint& position)
{
    QAction* action = _bib_menu->exec(position);
    if (!action)
        return;
    const QString field(action->data().toString());
    if (field.isEmpty())
        return;
    _bpP->setField(field, ClipEdit->textCursor().selectedText());
    ClipEdit->insertTag("<<" + field + ">>");
}

void cb2Bib::addAuthors()
{
    _bpP->setField("addauthors", ClipEdit->textCursor().selectedText(), ui.author->text());
    ClipEdit->insertTag("<<author>>");
    if (_tagged_view_mode)
        showMessage(tr("Info: Creating a pattern with multiple author sets."));
}

void cb2Bib::addEditors()
{
    _bpP->setField("addeditors", ClipEdit->textCursor().selectedText(), ui.editor->text());
    ClipEdit->insertTag("<<editor>>");
    if (_tagged_view_mode)
        showMessage(tr("Info: Creating a pattern with multiple ui.editor sets."));
}

void cb2Bib::anyPattern()
{
    if (_tagged_view_mode)
        ClipEdit->insertTag("<AnyPattern>");
    else
        ClipEdit->insertPlainText(QString());
}

void cb2Bib::preparseClipboard()
{
    c2bPreparse(_raw_input_data);
}

void cb2Bib::restartEngine()
{
    const QString text(ClipEdit->toPlainText());
    if (!text.isEmpty())
        c2bParse(text);
}

void cb2Bib::guessFields()
{
    const QString text(ClipEdit->toPlainText());
    if (!text.isEmpty())
    {
        const QString keep_dropped_article_file(_dropped_document_file);
        c2bInit();
        _bpP->guessFields(text);
        fileDropped(keep_dropped_article_file);
        processingEnded();
    }
}

void cb2Bib::dataChanged(const QString& str)
{
    bool do_allow(isVisible());
    if (ui.stackedWidget->currentWidget() == ClipEdit)
    {
        if (ClipEdit->textCursor().hasSelection())
            do_allow = false;
    }
    else if (ui.stackedWidget->currentWidget() == BibBrowser)
    {
        if (BibBrowser->textCursor().hasSelection())
            do_allow = false;
    }
    if (_connected && ui.ConnectB->isEnabled() && do_allow)
        forceDataChange(str);
}

void cb2Bib::forceDataChange(const QString& str)
{
    if (!str.isEmpty())
    {
        _raw_input_data = str.trimmed();
        if (_settingsP->value("cb2Bib/PreparserAutomatic").toBool())
            c2bPreparse(str);
        else
            c2bParse(str);
    }
}

void cb2Bib::c2bInit()
{
    _dropped_document_file.clear();
    ui.openFileDocumentAction->setEnabled(false);
    ui.openFileDocumentAction->setText(tr("Open File Document"));
    ui.file->setStatusTip(QString());
    disconnect(_bpP, SIGNAL(setDocumentFilename()), this, SLOT(setDocumentFilename()));
    _bpP->clearCurrentReference();
    _is_check_repeated_done = false;
    _modified = false;
    ui.AddBibB->setEnabled(_modified);
}

void cb2Bib::c2bParse(const QString& text)
{
    c2bInit();
    QString out_text, out_tagtext;
    _bpP->parse(text, &out_text, &out_tagtext);
    ClipEdit->setText(out_text, out_tagtext);
    processingEnded();
}

void cb2Bib::c2bPreparse(const QString& text)
{
    QString out_text;
    _bpP->preparse(text, &out_text);
    if (!out_text.isEmpty())
        c2bParse(out_text);
}

void cb2Bib::deleteTmpBib()
{
    QMessageBox msgBox(this);
    QPushButton* deleteButton = msgBox.addButton(tr("&Delete"), QMessageBox::DestructiveRole);
    msgBox.setDefaultButton(msgBox.addButton(QMessageBox::Cancel));
    msgBox.setWindowTitle(tr("Confirmation - cb2Bib"));
    msgBox.setText(tr("Delete temporary BibTeX file %1 ?").arg(ui.bibtexfile->currentText()));
    msgBox.setIcon(QMessageBox::Question);
    msgBox.exec();
    if (msgBox.clickedButton() == deleteButton)
    {
        QFile BibFile(ui.bibtexfile->currentText());
        if (BibFile.remove())
            showMessage(tr("File %1 deleted.").arg(ui.bibtexfile->currentText()));
        else
            QMessageBox::warning(
                this, tr("Warning - cb2Bib"),
                tr("Unable to delete the file %1.\nError: '%2'").arg(ui.bibtexfile->currentText(), BibFile.errorString()),
                QMessageBox::Ok);
    }
}

void cb2Bib::insertRegExp()
{
    QStringList pattern;

    // Extracting Reference Type
    pattern.append(ui.typecombo->currentText());

    // Extracting Field Order
    QString order(ClipEdit->toPlainText());
    QRegExp rx("<<(" + _bpP->bibliographicFields().join("|") + ")>>");
    QStringList list;
    int ipos(0);
    while (ipos >= 0)
    {
        ipos = rx.indexIn(order, ipos);
        if (ipos > -1)
        {
            list += rx.cap(1);
            ipos += rx.matchedLength();
            c2bUtils::debug(rx.cap(1));
        }
    }
    order = list.join(" ");
    c2bUtils::debug(order);
    pattern.append(order);

    // Parsing Regular Expression
    QString str('^' + QRegExp::escape(ClipEdit->toPlainText()) + '$');
    str.replace(QRegExp("<<abstract>>"), "(.+)");
    str.replace(QRegExp("<<address>>"), "(.+)");
    str.replace(QRegExp("<<annote>>"), "(.+)");
    str.replace(QRegExp("<AnyPattern>"), ".+");
    str.replace(QRegExp("<<author>>"), "(.+)");
    str.replace(QRegExp("<<booktitle>>"), "(.+)");
    str.replace(QRegExp("<<chapter>>"), "(\\d+)");
    str.replace(QRegExp("<<doi>>"), "(10\\.[\\d\\.]+/\\S+)");
    str.replace(QRegExp("<<edition>>"), "(.+)");
    str.replace(QRegExp("<<editor>>"), "(.+)");
    str.replace(QRegExp("<<eprint>>"), "(.+)");
    str.replace(QRegExp("<<file>>"), "(\\S+)");
    str.replace(QRegExp("<<institution>>"), "(.+)");
    str.replace(QRegExp("<<isbn>>"), "(.+)");
    str.replace(QRegExp("<<issn>>"), "(.+)");
    str.replace(QRegExp("<<journal>>"), "(.+)");
    str.replace(QRegExp("<<keywords>>"), "(.+)");
    str.replace(QRegExp("<<month>>"), "(.+)");
    str.replace(QRegExp("<<note>>"), "(.+)");
    str.replace(QRegExp("<<number>>"), "(\\d+)");
    str.replace(QRegExp("<<organization>>"), "(.+)");
    str.replace(QRegExp("<<pages>>"), "([\\d\\-" + QString(QChar(8211)) + "\\s]+)");
    str.replace(QRegExp("<<publisher>>"), "(.+)");
    str.replace(QRegExp("<<school>>"), "(.+)");
    str.replace(QRegExp("<<series>>"), "(.+)");
    str.replace(QRegExp("<<title>>"), "(.+)");
    str.replace(QRegExp("<<url>>"), "(\\S+)");
    str.replace(QRegExp("<<volume>>"), "(\\d+)");
    str.replace(QRegExp("<<year>>"), "(\\d\\d\\d\\d)");
    c2bUtils::debug(str);
    pattern.append(str);

    // User Editting
    c2bSaveRegExp Sdiag(pattern, _raw_input_data, this);
    connect(c2b::clipboard(), SIGNAL(cbDataChanged(QString)), &Sdiag, SLOT(updateInput(QString)));
    connect(&Sdiag, SIGNAL(savePatternInfo(QString,QString)), this, SLOT(savePattern(QString,QString)));
    ui.ConnectB->setDisabled(true);
    if (Sdiag.exec() == QDialog::Rejected)
        showMessage(tr("Cancelled."));
    ui.ConnectB->setDisabled(false);
}

void cb2Bib::savePattern(const QString& rx, const QString& rxname)
{
    const QString regular_expression_f(_settingsP->fileName("cb2Bib/RegularExpressionFile"));
    QFile file(regular_expression_f);
    bool fopen;
    if (file.exists())
        fopen = file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
    else
        fopen = file.open(QIODevice::WriteOnly | QIODevice::Text);

    if (fopen)
    {
        QTextStream stream(&file);
        stream.setCodec("UTF-8");
        stream.setAutoDetectUnicode(true);
        stream << ("# cb2Bib " + C2B_VERSION + "  Pattern:") << endl << rxname << endl << rx << endl << endl;
        file.close();
        showMessage(tr("Pattern '%1' added to %2.").arg(rxname, regular_expression_f));
    }
    else
        QMessageBox::warning(
            this, tr("Warning - cb2Bib"),
            tr("Unable to open the file %1 for writing.\nError: '%2'.").arg(regular_expression_f, file.errorString()),
            QMessageBox::Ok);
    c2bUtils::debug("signal:");
    c2bUtils::debug(rx);
    c2bUtils::debug(rxname);
}

void cb2Bib::setDocumentFilename()
{
    disconnect(_bpP, SIGNAL(setDocumentFilename()), this, SLOT(setDocumentFilename()));
    if (_dropped_document_file.isEmpty())
        return;
    ui.file->setText(_bpP->documentFilename(_dropped_document_file, ui.bibtexfile->currentText()));
    connect(_bpP, SIGNAL(setDocumentFilename()), this, SLOT(setDocumentFilename()));
}

void cb2Bib::addToFile(bool ready)
{
    if (!ready)
    {
        QMessageBox::information(this, tr("Information - cb2Bib"),
                                 tr("Not ready to add reference.\n%2").arg(c2b::net()->errorString()), QMessageBox::Ok);
        ui.AddBibB->setEnabled(_modified);
        return;
    }
    QFile file(ui.bibtexfile->currentText());
    bool fopen;
    if (file.exists())
        fopen = file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
    else
        fopen = file.open(QIODevice::WriteOnly | QIODevice::Text);

    if (fopen)
    {
        QTextStream stream(&file);
        stream.setCodec("UTF-8");
        stream.setAutoDetectUnicode(true);
        stream << _bpP->toBibTeX();
        file.close();
        c2b::showMessage(tr("Bib Item %1 added to %2.").arg(ui.id->text(), ui.bibtexfile->currentText()));
        if (_settingsP->value("cb2Bib/InsertMetadata").toBool())
            if (!_target_document_file.isEmpty())
                if (!c2b::metaParser()->insertMetadata(_bpP->currentReference(), _target_document_file))
                    c2b::showMessage(tr("Unable to insert metadata to file %1.").arg(_target_document_file));
        _is_check_repeated_done = false;
        _modified = false;
        ui.AddBibB->setEnabled(_modified);
        emit addedBibToFile(ui.bibtexfile->currentText());
    }
    else
        QMessageBox::warning(
            this, tr("Warning - cb2Bib"),
            tr("Unable to open file %1 for writing.\nError: '%2'.").arg(ui.bibtexfile->currentText(), file.errorString()),
            QMessageBox::Ok);
}

void cb2Bib::addMetadata()
{
    if (!_dropped_document_file.isEmpty())
    {
        if (QFileInfo(_dropped_document_file).isWritable() &&
            c2b::metaParser()->insertMetadata(_bpP->currentReference(), _dropped_document_file))
            c2b::showMessage(tr("Inserted metadata to file %1.").arg(_dropped_document_file));
        else
            c2b::showMessage(tr("Unable to insert metadata to file %1.").arg(_dropped_document_file));
    }
}

void cb2Bib::postprocessBibTeX()
{
    c2bPostprocess* ppBib = new c2bPostprocess(ui.bibtexfile->currentText(), this);
    showMessage(tr("BibTeX Postprocessing launched."));
    if (ppBib->exec() != QDialog::Accepted)
        showMessage(tr("BibTeX Postprocessing exited."));
}

void cb2Bib::bookmarksEditor()
{
    if (_openDocuments.contains("bookmark_network_editor"))
    {
        c2bUtils::setWidgetOnTop(_openDocuments.value("bookmark_network_editor"));
        return;
    }
    c2bEditor* ed = new c2bEditor(_settingsP->fileName("cb2Bib/NetworkFile"), c2bEditor::NetQInfo, this);
    ed->setObjectName("bookmark_network_editor");
    _openDocuments.insert("bookmark_network_editor", ed);
    ui.editBookmarksAction->setEnabled(false);
    connect(ed, SIGNAL(restartQuery()), this, SLOT(makeNetQuery()));
    connect(ed, SIGNAL(destroyed(QObject*)), this, SLOT(updateOpenDocuments(QObject*)));
    connect(ed, SIGNAL(openFile(QString)), this, SLOT(bibEditor(QString)));
    ed->show();
    showMessage(tr("Bookmark File Editor launched."));
}

void cb2Bib::abbreviationsEditor()
{
    c2bEditor* ed = new c2bEditor(_settingsP->fileName("cb2Bib/JournalFile"), c2bEditor::JAbbrev, this);
    ed->setObjectName("journal_abbreviations_editor");
    _openDocuments.insert("journal_abbreviations_editor", ed);
    ui.editAbbreviationsAction->setEnabled(false);
    connect(ed, SIGNAL(destroyed(QObject*)), this, SLOT(updateOpenDocuments(QObject*)));
    connect(ed, SIGNAL(openFile(QString)), this, SLOT(bibEditor(QString)));
    connect(ed, SIGNAL(openBookmarks()), this, SLOT(bookmarksEditor()));
    ed->show();
    showMessage(tr("Journal Abbreviations Editor launched."));
}

void cb2Bib::regExpsEditor()
{
    c2bEditor* ed = new c2bEditor(_settingsP->fileName("cb2Bib/RegularExpressionFile"), c2bEditor::RegExp, this);
    ed->setObjectName("regular_expression_editor");
    _openDocuments.insert("regular_expression_editor", ed);
    ui.editRegExpsAction->setEnabled(false);
    connect(ed, SIGNAL(restartEngine()), this, SLOT(restartEngine()));
    connect(ed, SIGNAL(destroyed(QObject*)), this, SLOT(updateOpenDocuments(QObject*)));
    connect(ed, SIGNAL(openFile(QString)), this, SLOT(bibEditor(QString)));
    connect(ed, SIGNAL(openBookmarks()), this, SLOT(bookmarksEditor()));
    ed->show();
    showMessage(tr("RegExp File Editor launched."));
}

void cb2Bib::annoteEditor(const QString& annotefile)
{
    c2bEditor* ed = new c2bEditor(annotefile, c2bEditor::Annote, this);
    ed->setObjectName("annote_editor");
    _openDocuments.insert("annote_editor", ed);
    connect(ed, SIGNAL(destroyed(QObject*)), this, SLOT(updateOpenDocuments(QObject*)));
    connect(ed, SIGNAL(openFile(QString)), this, SLOT(bibEditor(QString)));
    connect(ed, SIGNAL(openBookmarks()), this, SLOT(bookmarksEditor()));
    ed->show();
    showMessage(tr("Annote Editor launched."));
}

void cb2Bib::initAsBibTeXEditor()
{
    for (int i = 0; i < _settingsP->cl_bibedit_filenames.count(); ++i)
        bibEditor(_settingsP->cl_bibedit_filenames.at(i));
}

void cb2Bib::bibEditor(const QString& bibtexfile, bibSearcher* searcher)
{
    if (bibtexfile.isEmpty())
        return;
    if (_openDocuments.contains(bibtexfile))
    {
        c2bUtils::setWidgetOnTop(_openDocuments.value(bibtexfile));
        return;
    }
    c2bEditor* ed = new c2bEditor(bibtexfile, searcher, this);
    ed->setObjectName(ed->editorFilename());
    _openDocuments.insert(ed->editorFilename(), ed);
    connect(ed, SIGNAL(destroyed(QObject*)), this, SLOT(updateOpenDocuments(QObject*)));
    connect(ed, SIGNAL(openFile(QString)), this, SLOT(bibEditor(QString)));
    connect(ed, SIGNAL(openBookmarks()), this, SLOT(bookmarksEditor()));
    connect(ed, SIGNAL(editFileRenamed(QString,QString)), this, SLOT(updateOpenDocuments(QString,QString)));
    ed->show();
    showMessage(tr("BibTeX Editor launched."));
}

void cb2Bib::updateOpenDocuments(QObject* obj)
{
    _openDocuments.remove(obj->objectName());

    if (!_openDocuments.contains("bookmark_network_editor"))
        ui.editBookmarksAction->setEnabled(true);
    if (!_openDocuments.contains("journal_abbreviations_editor"))
        ui.editAbbreviationsAction->setEnabled(true);
    if (!_openDocuments.contains("regular_expression_editor"))
        ui.editRegExpsAction->setEnabled(true);

    if (_settingsP->cl_bibedit && _openDocuments.count() == 0 && isHidden())
        close();
}

void cb2Bib::updateOpenDocuments(const QString& old_name, const QString& new_name)
{
    c2bEditor* ed = _openDocuments.take(old_name);
    if (ed)
    {
        if (ed->objectName() == "bookmark_network_editor" || ed->objectName() == "journal_abbreviations_editor" ||
            ed->objectName() == "regular_expression_editor" || ed->objectName() == "annote_editor")
            return;
        ed->setObjectName(new_name);
        _openDocuments.insert(new_name, ed);
        updateBibfile(new_name);
    }
}

void cb2Bib::bibModified(bool modified)
{
    _modified = modified;
    ui.AddBibB->setEnabled(_modified);
    if (ui.stackedWidget->currentWidget() == BibBrowser)
        BibBrowser->updatePlainText(_bpP->toBibTeX());
}

void cb2Bib::updateCheckRepeatedAction()
{
    // Do not use anyAuthor/anyTitle, _bpP->currentReference() might not yet be set
    ui.checkRepeatedAction->setVisible(!ui.author->text().isEmpty() || !ui.title->text().isEmpty() ||
                                       !ui.editor->text().isEmpty() || !ui.booktitle->text().isEmpty() ||
                                       !ui.id->text().isEmpty());
}

void cb2Bib::checkRepeated()
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    isReferenceRepeated();
    QApplication::restoreOverrideCursor();
}

bool cb2Bib::isReferenceRepeated()
{
    QFileInfo fi(ui.bibtexfile->currentText());
    showMessage(tr("Checking for similar references at %1.").arg(fi.absolutePath()));
    bibSearcher searcher(_bpP, fi.absolutePath());
    searcher.exec();
    const bool repeated(searcher.hitsCount() > 0);
    if (repeated)
    {
        QApplication::processEvents();
        bibEditor(fi.absolutePath(), &searcher);
        QApplication::processEvents();
        if (searcher.hitsCount() == 1)
            c2b::showMessage(tr("Found %1 similar reference.").arg(searcher.hitsCount()));
        else
            c2b::showMessage(tr("Found %1 similar references.").arg(searcher.hitsCount()));
    }
    else
        showMessage(tr("No similar references found at %1.").arg(fi.absolutePath()));
    return repeated;
}


/****************************************************************************

  NETWORK FUNCTIONALITY

*****************************************************************************/

void cb2Bib::makeNetQuery()
{
    if (!ui.MakeNetworkQueryB->isEnabled())
    {
        showMessage(tr("Currently processing previous query. Resubmit later."));
        return;
    }
    ui.MakeNetworkQueryB->setEnabled(false);
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    _netQP->submitQuery(_bpP->currentReference(), ClipEdit->toPlainText(), !_pdfImportP);
}

void cb2Bib::netQueryEnded(bool succeeded, const QString& targetPDF, const QString& targetBib)
{
    if (!succeeded)
    {
        emit endedProcessing(false);
        c2b::showMessage(tr("Query submission information. %1").arg(_netQP->errorString()));
    }
    else if (targetPDF.isEmpty() && targetBib.isEmpty())
    {
        emit endedProcessing(false);
        c2b::showMessage(tr("Query submitted. %1").arg(_netQP->errorString()));
    }
    else
    {
        const QString previous_article_file(
            _dropped_document_file); // Keep dropped file in case this is auto recognized
        forceDataChange(targetBib);
        if (_bpP->isAutoRecognized() && !targetPDF.isEmpty())
            fileDropped(targetPDF);
        else if (_bpP->isAutoRecognized())
            fileDropped(previous_article_file);
    }
    QApplication::restoreOverrideCursor();
    ui.MakeNetworkQueryB->setEnabled(true);
}

void cb2Bib::processingEnded()
{
    if (_settingsP->value("cb2Bib/AutomaticQuery").toBool())
        if (ui.MakeNetworkQueryB->isEnabled() && !_bpP->autoRecognizedString().contains("BibTeX"))
        {
            makeNetQuery();
            return;
        }
    if (_pdfImportP)
        fileDropped(_pdfImportP->processedFile);
    emit endedProcessing(_bpP->isAutoRecognized());
}

void cb2Bib::linkClicked(const QUrl& ln)
{
    // Encode link sets dynamic link.
    c2bUtils::openFile(c2b::encodeLink(ln.toString()), this);
}

void cb2Bib::openFileDocument()
{
    if (!_dropped_document_file.isEmpty())
        c2bUtils::openFile(_dropped_document_file, this);
}

void cb2Bib::selectFile()
{
    const QString fn(c2bFileDialog::getOpenFilename(
                         this, QString(), _settingsP->fileName("cb2Bib/LastDroppedFile"),
                         "Portable Document Format (*.pdf);;DjVu (*.djvu);;Post Script (*.ps);;TeX (*.tex);;All (*)"));
    if (!fn.isEmpty())
        fileDroppedByUser(fn);
}

void cb2Bib::openAnnote()
{
    const QString fn(c2bFileDialog::getFilename(this, QString(), _settingsP->fileName("cb2Bib/LastAnnoteFile"),
                     "Annote HTML output (*.tex.html);;LaTeX (*.tex);;All (*)"));
    if (fn.isEmpty())
        return;
    const QString tex_fn(QString(fn).remove(QRegExp("\\.html$")));
    if (!QFileInfo::exists(tex_fn))
    {
        const QString empty_note("%\\c2b_bibtex_directory{" + QFileInfo(ui.bibtexfile->currentText()).absolutePath() +
                                 "}\n%\\c2b_makeindex\n\n\n\\title{New Note}\n\n\n\n");
        if (!c2bUtils::stringToFile(empty_note, tex_fn))
        {
            QMessageBox::information(this, tr("Information - cb2Bib"),
                                     tr("Unable to create new note %1.\nCheck writing permission.").arg(tex_fn),
                                     QMessageBox::Ok);
            return;
        }
    }
    _settingsP->setFilename("cb2Bib/LastAnnoteFile", fn);
#ifdef C2B_USE_QWEB
    const QStringList flags(QStringList() << "--view-annote" << fn << _settingsP->confCommandFlags());
    QProcess::startDetached(QCoreApplication::applicationFilePath(), flags);
#else
    annoteEditor(tex_fn);
#endif
}
