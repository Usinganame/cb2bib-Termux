//========================================================================
//
// Modified pdftohtml (constans@molspaces.com, 2014)
//
// HTMLGen.cc
//
// Copyright 2010 Glyph & Cog, LLC
//
//========================================================================

#include <aconf.h>

#ifdef USE_GCC_PRAGMAS
#pragma implementation
#endif

#include <stdlib.h>

#include "gmem.h"
#include "GString.h"
#include "GList.h"
#include "PDFDoc.h"
#include "TextOutputDev.h"
#include "SplashOutputDev.h"
#include "ErrorCodes.h"

#include "HTMLGen.h"

#ifdef _WIN32
#  define strcasecmp stricmp
#  define strncasecmp strnicmp
#endif

//------------------------------------------------------------------------

// Map Unicode indexes from the private use area, following the Adobe
// Glyph list.
#define privateUnicodeMapStart 0xf6f9
#define privateUnicodeMapEnd   0xf7ff
static int
privateUnicodeMap[privateUnicodeMapEnd - privateUnicodeMapStart + 1] =
{
    0x0141, 0x0152, 0,      0,      0x0160, 0,      0x017d,         // f6f9
    0,      0,      0,      0,      0,      0,      0,      0,      // f700
    0,      0,      0,      0,      0,      0,      0,      0,
    0,      0,      0,      0,      0,      0,      0,      0,      // f710
    0,      0,      0,      0,      0,      0,      0,      0,
    0,      0x0021, 0,      0,      0x0024, 0,      0x0026, 0,      // f720
    0,      0,      0,      0,      0,      0,      0,      0,
    0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, // f730
    0x0038, 0x0039, 0,      0,      0,      0,      0,      0x003f,
    0,      0,      0,      0,      0,      0,      0,      0,      // f740
    0,      0,      0,      0,      0,      0,      0,      0,
    0,      0,      0,      0,      0,      0,      0,      0,      // f750
    0,      0,      0,      0,      0,      0,      0,      0,
    0,      0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, // f760
    0x0048, 0x0049, 0x004a, 0x004b, 0x004c, 0x004d, 0x004e, 0x004f,
    0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, // f770
    0x0058, 0x0059, 0x005a, 0,      0,      0,      0,      0,
    0,      0,      0,      0,      0,      0,      0,      0,      // f780
    0,      0,      0,      0,      0,      0,      0,      0,
    0,      0,      0,      0,      0,      0,      0,      0,      // f790
    0,      0,      0,      0,      0,      0,      0,      0,
    0,      0x00a1, 0x00a2, 0,      0,      0,      0,      0,      // f7a0
    0,      0,      0,      0,      0,      0,      0,      0,
    0,      0,      0,      0,      0,      0,      0,      0,      // f7b0
    0,      0,      0,      0,      0,      0,      0,      0x00bf,
    0,      0,      0,      0,      0,      0,      0,      0,      // f7c0
    0,      0,      0,      0,      0,      0,      0,      0,
    0,      0,      0,      0,      0,      0,      0,      0,      // f7d0
    0,      0,      0,      0,      0,      0,      0,      0,
    0x00c0, 0x00c1, 0x00c2, 0x00c3, 0x00c4, 0x00c5, 0x00c6, 0x00c7, // f7e0
    0x00c8, 0x00c9, 0x00ca, 0x00cb, 0x00cc, 0x00cd, 0x00ce, 0x00cf,
    0x00d0, 0x00d1, 0x00d2, 0x00d3, 0x00d4, 0x00d5, 0x00d6, 0,      // f7f0
    0x00d8, 0x00d9, 0x00da, 0x00db, 0x00dc, 0x00dd, 0x00de, 0x0178
};

//------------------------------------------------------------------------



//------------------------------------------------------------------------

HTMLGen::HTMLGen()
{
    TextOutputControl textOutControl;
    SplashColor paperColor;

    ok = gTrue;

    backgroundResolution = 150;
    drawInvisibleText = gTrue;

    // set up the TextOutputDev
    textOutControl.mode = textOutReadingOrder;
    textOutControl.html = gTrue;
    textOut = new TextOutputDev(NULL, &textOutControl, gFalse);
    if (!textOut->isOk())
    {
        ok = gFalse;
    }

    // set up the SplashOutputDev
    paperColor[0] = paperColor[1] = paperColor[2] = 0xff;
    splashOut = new SplashOutputDev(splashModeRGB8, 1, gFalse, paperColor);
    splashOut->setSkipText(gTrue, gFalse);
}

HTMLGen::~HTMLGen()
{
    delete textOut;
    delete splashOut;
}

void HTMLGen::startDoc(PDFDoc* docA)
{
    doc = docA;
    splashOut->startDoc(doc->getXRef());
}

int HTMLGen::convertPage(int pg, int (*writeHTML)(void* stream, const char* data, int size), void* htmlStream)
{
    TextPage* text;
    GList* cols, *pars, *lines, *words;
    TextColumn* col;
    TextParagraph* par;
    TextLine* line;
    TextWord* word1;
    GString* s;
    double base;
    int colIdx, parIdx, lineIdx, wordIdx;
    int i, u;
    const char parsep('\n');

    // get the PDF text
    doc->displayPage(textOut, pg, 72, 72, 0, gFalse, gTrue, gFalse);
    text = textOut->takeText();

    // generate the PDF text
    cols = text->makeColumns();
    for (colIdx = 0; colIdx < cols->getLength(); ++colIdx)
    {
        col = (TextColumn*)cols->get(colIdx);
        pars = col->getParagraphs();
        for (parIdx = 0; parIdx < pars->getLength(); ++parIdx)
        {
            par = (TextParagraph*)pars->get(parIdx);
            lines = par->getLines();
            for (lineIdx = 0; lineIdx < lines->getLength(); ++lineIdx)
            {
                line = (TextLine*)lines->get(lineIdx);
                words = line->getWords();
                base = line->getBaseline();
                s = new GString();
                for (wordIdx = 0; wordIdx < words->getLength(); ++wordIdx)
                {
                    word1 = (TextWord*)words->get(wordIdx);
                    if (word1->getBaseline() - base < -0.55)
                        s->append(' ');  // superscript
                    for (i = 0; i < word1->getLength(); ++i)
                    {
                        u = word1->getChar(i);
                        if (u >= privateUnicodeMapStart &&
                            u <= privateUnicodeMapEnd &&
                            privateUnicodeMap[u - privateUnicodeMapStart])
                        {
                            u = privateUnicodeMap[u - privateUnicodeMapStart];
                        }
                        if (u <= 0x7f)
                        {
                            s->append((char)u);
                        }
                        else if (u <= 0x7ff)
                        {
                            s->append((char)(0xc0 + (u >> 6)));
                            s->append((char)(0x80 + (u & 0x3f)));
                        }
                        else if (u <= 0xffff)
                        {
                            s->append((char)0xe0 + (u >> 12));
                            s->append((char)0x80 + ((u >> 6) & 0x3f));
                            s->append((char)0x80 + (u & 0x3f));
                        }
                        else if (u <= 0x1fffff)
                        {
                            s->append((char)0xf0 + (u >> 18));
                            s->append((char)0x80 + ((u >> 12) & 0x3f));
                            s->append((char)0x80 + ((u >> 6) & 0x3f));
                            s->append((char)0x80 + (u & 0x3f));
                        }
                        else if (u <= 0x3ffffff)
                        {
                            s->append((char)0xf8 + (u >> 24));
                            s->append((char)0x80 + ((u >> 18) & 0x3f));
                            s->append((char)0x80 + ((u >> 12) & 0x3f));
                            s->append((char)0x80 + ((u >> 6) & 0x3f));
                            s->append((char)0x80 + (u & 0x3f));
                        }
                        else if (u <= 0x7fffffff)
                        {
                            s->append((char)0xfc + (u >> 30));
                            s->append((char)0x80 + ((u >> 24) & 0x3f));
                            s->append((char)0x80 + ((u >> 18) & 0x3f));
                            s->append((char)0x80 + ((u >> 12) & 0x3f));
                            s->append((char)0x80 + ((u >> 6) & 0x3f));
                            s->append((char)0x80 + (u & 0x3f));
                        }
                    }
                    if (word1->getSpaceAfter())
                        s->append(' ');
                }
                s->append('\n');
                writeHTML(htmlStream, s->getCString(), s->getLength());
                delete s;
            }
            writeHTML(htmlStream, &parsep, 1);
        }
    }
    delete text;
    deleteGList(cols, TextColumn);

    return errNone;
}
