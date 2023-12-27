/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bRLWebSearchSettings.h"

#include "c2bSettings.h"


c2bRLWebSearchSettings::c2bRLWebSearchSettings(QWidget* parentw) : QDialog(parentw)
{
    ui.setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    resize(size().width(), 1);
    c2bSettings* settings(c2bSettingsP);
    const QString searchEngine(settings->value("c2bReferenceList/SearchEngine").toString());
    ui.searchEngine->addItem(searchEngine);
    ui.searchEngine->addItem("https://www.google.com/search?ie=UTF-8&q=");
    ui.searchEngine->addItem("https://scholar.google.com/scholar?ie=UTF-8&q=");
    ui.searchEngine->addItem("https://pubmed.ncbi.nlm.nih.gov/?term=");
    ui.searchEngine->setCurrentIndex(0);
    ui.searchEngine->setFocus();
    ui.addQuotes->setChecked(settings->value("c2bReferenceList/SearchEngineAddQuotes").toBool());
}

c2bRLWebSearchSettings::~c2bRLWebSearchSettings() {}


void c2bRLWebSearchSettings::accept()
{
    c2bSettings* settings(c2bSettingsP);
    settings->setValue("c2bReferenceList/SearchEngine", ui.searchEngine->currentText());
    settings->setValue("c2bReferenceList/SearchEngineAddQuotes", ui.addQuotes->isChecked());
    QDialog::accept();
}
