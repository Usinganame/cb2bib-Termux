/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bSearchInFilesPattern.h"

#include "c2b.h"
#include "c2bBibParser.h"
#include "c2bSettings.h"

#include <searchPattern.h>

#include <QTreeWidgetItem>


c2bSearchInFilesPattern::c2bSearchInFilesPattern(QWidget* parentw) : QWidget(parentw)
{
    ui.setupUi(this);
    c2bBibParser* bp = c2b::bibParser();
    ui.patternType->addItems(searchPattern::types());
    ui.patternType->setCurrentIndex(c2bSettingsP->value("c2bSearchInFiles/PatternTypeIndex", 0).toInt());
    ui.patternScope->addItems(bp->sortedBibliographicFields());
    ui.yearScope->hide();
    ui.inputPattern->setFocus();

    connect(ui.clearB, SIGNAL(clicked()), this, SLOT(patternChanged()));
    connect(ui.inputPattern, SIGNAL(textEdited(QString)), this, SLOT(patternChanged()));
    connect(ui.patternScope, SIGNAL(currentIndexChanged(QString)), this, SLOT(showYearScope(QString)));
}

c2bSearchInFilesPattern::~c2bSearchInFilesPattern()
{
    c2bSettingsP->setValue("c2bSearchInFiles/PatternTypeIndex", ui.patternType->currentIndex());
}


void c2bSearchInFilesPattern::patternChanged()
{
    emit patternAvailable(isAvailable());
}

void c2bSearchInFilesPattern::setText(const QString& text)
{
    ui.inputPattern->setText(text);
    ui.inputPattern->setFocus();
}

void c2bSearchInFilesPattern::clear()
{
    ui.inputPattern->clear();
    ui.inputPattern->setFocus();
}

void c2bSearchInFilesPattern::setPattern(QTreeWidgetItem* pattern)
{
    if (!pattern)
        return;
    if (pattern->columnCount() != ITEMS_IN_SEARCH_PATTERN)
        return;

    if (pattern->text(0) == "NOT")
        ui.NOT->setChecked(true);
    else
        ui.NOT->setChecked(false);
    if (pattern->text(1) == "Sensitive")
        ui.caseSensitive->setChecked(true);
    else
        ui.caseSensitive->setChecked(false);
    ui.patternType->setCurrentIndex(ui.patternType->findText(pattern->text(2)));
    ui.patternScope->setCurrentIndex(ui.patternScope->findText(pattern->text(3)));
    if (pattern->text(4) == "=")
        ui.yearScope->setCurrentIndex(ui.yearScope->findText("Exact"));
    else if (pattern->text(4) == ">")
        ui.yearScope->setCurrentIndex(ui.yearScope->findText("Newer"));
    else
        ui.yearScope->setCurrentIndex(ui.yearScope->findText("Older"));
    ui.inputPattern->setText(pattern->text(5));
}

const QStringList c2bSearchInFilesPattern::patterns()
{
    QStringList p;
    if (ui.NOT->isChecked())
        p.append("NOT");
    else
        p.append(QString());
    if (ui.caseSensitive->isChecked())
        p.append("Sensitive");
    else
        p.append("Insensitive");
    p.append(ui.patternType->currentText());
    p.append(ui.patternScope->currentText());
    if (ui.yearScope->isHidden())
        p.append(" ");
    else if (ui.yearScope->currentText() == "Exact")
        p.append("=");
    else if (ui.yearScope->currentText() == "Newer")
        p.append(">");
    else if (ui.yearScope->currentText() == "Older")
        p.append("<");
    p.append(ui.inputPattern->text());
    return p;
}

void c2bSearchInFilesPattern::showYearScope(const QString& scope)
{
    if (scope == "year")
        ui.yearScope->show();
    else
        ui.yearScope->hide();
}

void c2bSearchInFilesPattern::setFocus()
{
    ui.inputPattern->setFocus();
}
