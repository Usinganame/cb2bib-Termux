/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef CB2BIB_PARAMETERS_H
#define CB2BIB_PARAMETERS_H

#include <QString>

const int C2B_MESSAGE_TIME(6000);
const QLatin1String C2B_APPLICATION("cb2Bib");
const QLatin1String C2B_CITE_COMMAND_PATTERN("\\cite{<<|citeids|,>>}");
const QLatin1String C2B_CITE_ID_PATTERN("<<author_first>><<year_abbreviated>><<ppages_first>>");
const QLatin1String C2B_DOCUMENT_ID_PATTERN("<<citeid>>");
const QLatin1String C2B_FIND_REPLACE_LIST("Corresponding Author Contact Information||ScienceDirect alt tag^e"
        "E-mail The Corresponding Author||ScienceDirect alt tag^e"
        "small pi, Greek|$\\pi$|ScienceDirect alt tag^e"
        "{sect}||PNAS - Author String^e"
        "{dagger}||PNAS - Author String");
const QLatin1String C2B_ICON_ABOUT_B_BACK("back_cb2bib_32.png");
const QLatin1String C2B_ICON_ABOUT_B("cb2bib.png");
const QLatin1String C2B_ICON_CONNECT_B("connect_established.png");
const QLatin1String C2B_ICON_DIR(":/icons/icons/");
const QLatin1String C2B_ICON_DISCONNECT_B("connect_no.png");
const QLatin1String C2B_ICON_VIEWBIB_B("viewbib.png");
const QLatin1String C2B_ICON_VIEWC2B_B("viewcb.png");
const QLatin1String C2B_ORGANIZATION("MOLspaces");
const QLatin1String C2B_VERSION("2.0.1");

#if defined(Q_OS_WIN)
const QLatin1String C2B_DATA_DIR("/data/data/com.termux/files/usr/share/cb2bib/");
#else
const QLatin1String C2B_DATA_DIR("/data/data/com.termux/files/usr/share/cb2bib/");
#endif

// File Manager Client
#if defined(Q_OS_WIN)
const QLatin1String C2B_FM_CLIENT_COPY_ARG("");
const QLatin1String C2B_FM_CLIENT_COPY_BIN("");
const QLatin1String C2B_FM_CLIENT_MOVE_ARG("");
const QLatin1String C2B_FM_CLIENT_MOVE_BIN("");
#elif defined(Q_OS_MACOS)
const QLatin1String C2B_FM_CLIENT_COPY_ARG("");
const QLatin1String C2B_FM_CLIENT_COPY_BIN("");
const QLatin1String C2B_FM_CLIENT_MOVE_ARG("");
const QLatin1String C2B_FM_CLIENT_MOVE_BIN("");
#else // Q_OS_UNIX
const QLatin1String C2B_FM_CLIENT_COPY_ARG("copy");
const QLatin1String C2B_FM_CLIENT_COPY_BIN("kfmclient");
const QLatin1String C2B_FM_CLIENT_MOVE_ARG("move");
const QLatin1String C2B_FM_CLIENT_MOVE_BIN("kfmclient");
#endif

// To text converter
#if defined(Q_OS_WIN)
const QLatin1String C2B_METADATAPARSER_EXIFTOOL_BIN("C:\\Windows\\exiftool.exe");
const QLatin1String C2B_PDFIMPORT_PDF2TXT_BIN("C:\\Program Files\\xpdf-3.04-win32\\pdf2cb.exe");
const QLatin1String C2B_BIBSEARCHER_PDF2TXT_BIN("C:\\Program Files\\xpdf-3.04-win32\\pdf2cb.exe");
#elif defined(Q_OS_MACOS)
const QLatin1String C2B_METADATAPARSER_EXIFTOOL_BIN("exiftool");
const QLatin1String C2B_BIBSEARCHER_PDF2TXT_BIN("pdftotext");
const QLatin1String C2B_PDFIMPORT_PDF2TXT_BIN("pdftotext");
#else // Q_OS_UNIX
const QLatin1String C2B_METADATAPARSER_EXIFTOOL_BIN("exiftool");
const QLatin1String C2B_BIBSEARCHER_PDF2TXT_BIN("pdftotext");
const QLatin1String C2B_PDFIMPORT_PDF2TXT_BIN("pdftotext");
#endif

// BibTeX postprocessing
#if defined(Q_OS_WIN)
const QLatin1String C2B_POSTPROCESS_BIBTEX_BIN("c2btools\\bib2end.bat");
const QLatin1String C2B_POSTPROCESS_BIBTEX_ARG("%finput %foutput");
const QLatin1String C2B_POSTPROCESS_BIBTEX_EXT("end");
#elif defined(Q_OS_MACOS)
const QLatin1String C2B_POSTPROCESS_BIBTEX_BIN("c2btools/bib2pdf");
const QLatin1String C2B_POSTPROCESS_BIBTEX_ARG("%finput %foutput");
const QLatin1String C2B_POSTPROCESS_BIBTEX_EXT("bib.pdf");
#else // Q_OS_UNIX
const QLatin1String C2B_POSTPROCESS_BIBTEX_BIN("c2btools/bib2pdf");
const QLatin1String C2B_POSTPROCESS_BIBTEX_ARG("%finput %foutput");
const QLatin1String C2B_POSTPROCESS_BIBTEX_EXT("bib.pdf");
#endif

#endif
