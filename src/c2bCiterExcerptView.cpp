/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bCiterExcerptView.h"

#include "c2bSettings.h"
#include "c2bTextBrowser.h"
#include "c2bUtils.h"

#include <QGridLayout>


c2bCiterExcerptView::c2bCiterExcerptView(const QString& html, QWidget* parentw) : QDialog(parentw)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle(tr("Document Excerpt - cb2Bib"));
    QGridLayout* gl;
    gl = new QGridLayout(this);
    gl->setContentsMargins(0, 0, 0, 0);
    _browserP = new c2bTextBrowser(this);
    gl->addWidget(_browserP, 0, 0, 1, 1);

    c2bSettings* settings(c2bSettingsP);
    resize(settings->value("c2bCiterExcerptView/size", QSize(500, 500)).toSize());
    move(settings->value("c2bCiterExcerptView/position", pos()).toPoint());

    _browserP->setFont(QFont(QFont().family(),
                             settings->value("c2bCiterExcerptView/BrowserFontPointSize", QFont().pointSize()).toInt()));
    QString css(c2bUtils::fileToString(settings->fileName("cb2Bib/BrowserCssFile")));
    if (css.isEmpty())
        css = c2bUtils::fileToString(":/htm/htm/references.css");
    _browserP->document()->setDefaultStyleSheet(css);

    QAction* c(new QAction(this));
    c->setShortcut(QKeySequence(Qt::Key_Left));
    addAction(c);
    connect(c, SIGNAL(triggered()), this, SLOT(close()));

    QAction* vzi(new QAction(this));
    vzi->setShortcut(QKeySequence(QKeySequence::ZoomIn));
    addAction(vzi);
    connect(vzi, SIGNAL(triggered()), _browserP, SLOT(zoomIn()));
    QAction* vzo(new QAction(this));
    vzo->setShortcut(QKeySequence(QKeySequence::ZoomOut));
    addAction(vzo);
    connect(vzo, SIGNAL(triggered()), _browserP, SLOT(zoomOut()));

    _browserP->updateHtml(html);
}

c2bCiterExcerptView::~c2bCiterExcerptView()
{
    c2bSettings* settings(c2bSettingsP);
    if (!isFullScreen())
    {
        settings->setValue("c2bCiterExcerptView/position", pos());
        settings->setValue("c2bCiterExcerptView/size", size());
    }
    settings->setValue("c2bCiterExcerptView/BrowserFontPointSize", _browserP->font().pointSize());
}
