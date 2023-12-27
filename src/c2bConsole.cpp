/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bConsole.h"

#include "c2bNetworkQuery.h"
#include "c2bSettings.h"
#include "c2bTests.h"

#include <bibExtractor.h>
#include <bibParser.h>
#include <collectionIndex.h>
#include <metadataParser.h>
#include <texToHtml.h>

#include <QCoreApplication>
#include <QTimer>


c2bConsole::c2bConsole(QObject* parento) : QObject(parento) {}

c2bConsole::~c2bConsole() {}


void c2bConsole::load()
{
    // Send _process to application cue
    QTimer::singleShot(0, this, SLOT(_process()));
}

void c2bConsole::_process()
{
    int code(0);
    if (c2bSettingsP->cl_html_annote)
        code = cl_html_annote();
    else if (c2bSettingsP->cl_doc2bib)
        code = cl_doc2bib();
    else if (c2bSettingsP->cl_txt2bib)
        code = cl_txt2bib();
    else if (c2bSettingsP->cl_index)
        code = cl_index();
    else if (c2bSettingsP->cl_cb2bib_tests)
        code = cl_cb2bib_tests();
    else if (c2bSettingsP->cl_cb2bib_information)
        code = cl_cb2bib_information();
    QCoreApplication::exit(code);
}

int c2bConsole::cl_html_annote()
{
    if (QFileInfo::exists(c2bSettingsP->cl_annote_filename))
    {
        const QString tex(c2bUtils::fileToString(c2bSettingsP->cl_annote_filename));
        const QString htmlf(c2bSettingsP->cl_annote_filename + ".html");
        texToHtml t2h;
        t2h.toHtml(tex, htmlf);
        return 0;
    }
    else
    {
        c2bUtils::warn(QObject::tr("Error: Could not open %1 file for reading").arg(c2bSettingsP->cl_annote_filename));
        return 1;
    }
}

int c2bConsole::cl_doc2bib()
{
    bibParser bp;
    metadataParser mp(&bp);
    c2bNetworkQuery nq(&bp); // needs c2bUtils::fromHtmlString
    bibExtractor be(&bp, &mp, &nq);
    const int c(be.extract(c2bSettingsP->cl_extract_input_filenames, c2bSettingsP->cl_extract_output_filename,
                           bibExtractor::Document));
    return c;
}

int c2bConsole::cl_txt2bib()
{
    bibParser bp;
    metadataParser mp(&bp);
    c2bNetworkQuery nq(&bp);
    bibExtractor be(&bp, &mp, &nq);
    const int c(be.extract(c2bSettingsP->cl_extract_input_filenames, c2bSettingsP->cl_extract_output_filename,
                           bibExtractor::PlainText));
    return c;
}

int c2bConsole::cl_index()
{
    bibParser bp;
    collectionIndex ci(&bp);
    const int c(ci.index(c2bSettingsP->cl_index_dirname));
    return c;
}

int c2bConsole::cl_cb2bib_information()
{
    c2bTests* t(new c2bTests());
    const int passed(t->writeInformation());
    delete t;
    return passed;
}

int c2bConsole::cl_cb2bib_tests()
{
    c2bTests* t(new c2bTests());
    const int passed(t->allTests());
    delete t;
    return passed;
}
