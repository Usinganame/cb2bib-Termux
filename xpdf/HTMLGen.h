//========================================================================
//
// Modified pdftohtml (constans@molspaces.com, 2014)
//
// HTMLGen.h
//
// Copyright 2010 Glyph & Cog, LLC
//
//========================================================================

#ifndef HTMLGEN_H
#define HTMLGEN_H

#include <aconf.h>

#ifdef USE_GCC_PRAGMAS
#pragma interface
#endif

class PDFDoc;
class TextOutputDev;
class SplashOutputDev;

//------------------------------------------------------------------------

class HTMLGen
{
public:

    HTMLGen();
    ~HTMLGen();

    GBool isOk() const
    {
        return ok;
    }

    GBool getDrawInvisibleText() const
    {
        return drawInvisibleText;
    }
    void setDrawInvisibleText(GBool drawInvisibleTextA)
    {
        drawInvisibleText = drawInvisibleTextA;
    }

    void startDoc(PDFDoc* docA);
    int convertPage(int pg, int (*writeHTML)(void* stream, const char* data, int size), void* htmlStream);

private:

    double backgroundResolution;
    GBool drawInvisibleText;

    PDFDoc* doc;
    TextOutputDev* textOut;
    SplashOutputDev* splashOut;

    GBool ok;
};

#endif
