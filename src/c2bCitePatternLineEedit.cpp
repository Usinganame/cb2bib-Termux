/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bCitePatternLineEedit.h"

#include "c2bUtils.h"

#include <cb2bib_parameters.h>

#include <QAction>


c2bCitePatternLineEedit::c2bCitePatternLineEedit(QWidget* parentw) : c2bLineEdit(parentw)
{
    a_citeid = new QAction(this);
    a_citeids_comma = new QAction(this);
    a_citeids_semicolon = new QAction(this);
    a_latex = new QAction(this);
    a_markdown = new QAction(this);

    c2bUtils::addSeparator(this);
    addAction(a_latex);
    addAction(a_markdown);
    c2bUtils::addSeparator(this);
    addAction(a_citeid);
    addAction(a_citeids_comma);
    addAction(a_citeids_semicolon);
    c2bUtils::addSeparator(this);

    a_citeid->setText(tr("Insert <<citeid>>"));
    a_citeids_comma->setText(tr("Insert << |citeids|,>>"));
    a_citeids_semicolon->setText(tr("Insert << |citeids|;>>"));
    a_latex->setText(tr("LaTeX Command"));
    a_markdown->setText(tr("Markdown Command"));

    connect(a_citeid, SIGNAL(triggered()), this, SLOT(citeid()));
    connect(a_citeids_comma, SIGNAL(triggered()), this, SLOT(citeids_comma()));
    connect(a_citeids_semicolon, SIGNAL(triggered()), this, SLOT(citeids_semicolon()));
    connect(a_latex, SIGNAL(triggered()), this, SLOT(latex()));
    connect(a_markdown, SIGNAL(triggered()), this, SLOT(markdown()));
    connect(this, SIGNAL(textEdited(QString)), this, SLOT(check(QString)));

    setPlaceholderText(C2B_CITE_COMMAND_PATTERN);
    _citeids = QRegExp("^[^<]*<<[^\\|]*\\|citeids\\|[^>]*>>.*$");
}

c2bCitePatternLineEedit::~c2bCitePatternLineEedit() {}


void c2bCitePatternLineEedit::check(const QString& pattern)
{
    if (!pattern.isEmpty() && ((!pattern.contains(_citeids) && !pattern.contains(QLatin1String("<<citeid>>"))) ||
                               pattern.count(QLatin1String("citeid")) > 1))
        emit statusMessage(tr("Cite Command Pattern is misspecified"));
    else
        emit statusMessage(QString());
}

void c2bCitePatternLineEedit::latex()
{
    setText(C2B_CITE_COMMAND_PATTERN);
}

void c2bCitePatternLineEedit::markdown()
{
    setText(QLatin1String("[<<@|citeids|;>>]"));
}

void c2bCitePatternLineEedit::citeid()
{
    insert(QLatin1String("<<citeid>>"));
}

void c2bCitePatternLineEedit::citeids_comma()
{
    insert(QLatin1String("<< |citeids|,>>"));
}

void c2bCitePatternLineEedit::citeids_semicolon()
{
    insert(QLatin1String("<< |citeids|;>>"));
}
