/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bSearchInFiles.h"

#include "c2b.h"
#include "c2bUtils.h"

#include <bibSearcher.h>

#include <time.h>


c2bSearchInFiles::c2bSearchInFiles(const QString& file, QWidget* parentw) : QDialog(parentw)
{
    ui.setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    // Set blank title to columns 0 and 4. Qt 4.4.0 needs it, otherwise it takes column number as default title.
    // Recheck whenever ui files are generated for 4.4 instead of current 4.2.
    ui.patternList->headerItem()->setText(0, QApplication::translate("c2bSearchInFiles", "", 0));
    ui.patternList->headerItem()->setText(4, QApplication::translate("c2bSearchInFiles", "", 0));

    for (int i = 0; i < ITEMS_IN_SEARCH_PATTERN; ++i)
        ui.patternList->resizeColumnToContents(i);
    ui.buttonBox->button(QDialogButtonBox::Abort)->setAutoDefault(false);
    ui.buttonBox->button(QDialogButtonBox::Abort)->setDefault(false);
    ui.buttonBox->button(QDialogButtonBox::Abort)->setEnabled(false);
    ui.buttonBox->button(QDialogButtonBox::Close)->setAutoDefault(false);
    ui.buttonBox->button(QDialogButtonBox::Close)->setDefault(false);
    _searchB = new QPushButton(tr("Search"));
    ui.buttonBox->addButton(_searchB, QDialogButtonBox::ActionRole);
    _searchB->setAutoDefault(true);
    _searchB->setDefault(true);
    _searchB->setEnabled(false);

    _bibtex_file.clear();
    _bibtex_dir.clear();
    setBibTeXFile(file);

    connect(_searchB, SIGNAL(clicked()), this, SLOT(searchB_clicked()));
    connect(ui.allBibFiles, SIGNAL(clicked()), this, SLOT(setBibTeXFile()));
    connect(ui.buttonBox, SIGNAL(helpRequested()), this, SLOT(help()));
    connect(ui.pattern, SIGNAL(patternAvailable(bool)), this, SLOT(updateForm()));
    connect(ui.patternList, SIGNAL(itemActivated(QTreeWidgetItem*,int)), this, SLOT(on_editPatternB_clicked()));
    connect(ui.patternList, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(updateForm()));
}

c2bSearchInFiles::~c2bSearchInFiles() {}


void c2bSearchInFiles::updateForm()
{
    ui.addPatternB->setEnabled(ui.pattern->isAvailable());
    ui.Boolean->setEnabled((ui.patternList->topLevelItemCount() > 1) ||
                           (ui.pattern->isAvailable() && ui.patternList->topLevelItemCount() > 0));
    _searchB->setEnabled(!_bibtex_dir.isEmpty() &&
                         (ui.pattern->isAvailable() || ui.patternList->topLevelItemCount() > 0));
    if (ui.patternList->currentItem())
    {
        ui.deletePatternB->setEnabled(true);
        ui.editPatternB->setEnabled(true);
    }
    else
    {
        ui.deletePatternB->setEnabled(false);
        ui.editPatternB->setEnabled(false);
    }
    ui.searchLog->setText(_search_log);
}

void c2bSearchInFiles::on_addPatternB_clicked()
{
    new QTreeWidgetItem(ui.patternList, ui.pattern->patterns());
    for (int i = 0; i < ITEMS_IN_SEARCH_PATTERN; ++i)
        ui.patternList->resizeColumnToContents(i);
    ui.pattern->clear();
    updateForm();
}

void c2bSearchInFiles::on_deletePatternB_clicked()
{
    QTreeWidgetItem* item = ui.patternList->currentItem();
    delete item;
    item = ui.patternList->currentItem();
    if (item)
        ui.patternList->currentItem()->setSelected(true);
    updateForm();
}

void c2bSearchInFiles::on_editPatternB_clicked()
{
    QDialog editor(this);
    ui_editor.setupUi(&editor);
    QTreeWidgetItem* item = ui.patternList->currentItem();
    ui_editor.pattern->setPattern(item);
    connect(ui_editor.pattern, SIGNAL(patternAvailable(bool)), ui_editor.buttonBox->button(QDialogButtonBox::Ok),
            SLOT(setEnabled(bool)));
    if (editor.exec() == QDialog::Accepted)
    {
        const QStringList pattern(ui_editor.pattern->patterns());
        for (int i = 0; i < ITEMS_IN_SEARCH_PATTERN; ++i)
            item->setText(i, pattern.at(i));
        for (int i = 0; i < ITEMS_IN_SEARCH_PATTERN; ++i)
            ui.patternList->resizeColumnToContents(i);
    }
}

void c2bSearchInFiles::searchB_clicked()
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    _searchB->setEnabled(false);
    ui.buttonBox->button(QDialogButtonBox::Abort)->setEnabled(true);

    ui.searchLog->setText(_search_log);
    bibSearcher searcher(c2b::bibParser());
    connect(ui.buttonBox->button(QDialogButtonBox::Abort), SIGNAL(clicked()), &searcher, SLOT(abort()));
    searcher.setSearchScope(_bibtex_file, _bibtex_dir, ui.allBibFiles->isChecked(), ui.documentFiles->isChecked());
    searcher.setSimplifySource(ui.simplifySource->isChecked());
    searcher.setBoolean(ui.Boolean->currentText() == "All");
    if (ui.addPatternB->isEnabled())
    {
        const QStringList p(ui.pattern->patterns());
        searcher.addPattern(p.at(0) == "NOT", p.at(1) == "Sensitive", p.at(2), p.at(3), p.at(4).at(0), p.at(5));
    }
    QTreeWidgetItemIterator it(ui.patternList);
    while (*it)
    {
        QStringList p;
        for (int i = 0; i < ITEMS_IN_SEARCH_PATTERN; ++i)
            p.append((*it)->text(i));
        searcher.addPattern(p.at(0) == "NOT", p.at(1) == "Sensitive", p.at(2), p.at(3), p.at(4).at(0), p.at(5));
        ++it;
    }
    if (searcher.patternsCount() == 0)
        return;

    const unsigned long start_time(clock());

    searcher.exec();

    const double time(double(clock() - start_time) / double(CLOCKS_PER_SEC));

    QString search_status;
    if (searcher.hitsCount() > 0 || searcher.errorsCount() > 0)
    {
        if (searcher.hitsCount() > 0)
            search_status = tr("Found %1 hits from %2 references (%3s)")
                            .arg(searcher.hitsCount())
                            .arg(searcher.referencesCount())
                            .arg(time, 0, 'g', 3);
        else
            ui.searchLog->setText(_search_log);
        QApplication::processEvents();
        emit searchDone(_bibtex_dir, &searcher);
    }
    else if (searcher.errorsCount() < 0)
        search_status = tr("Search aborted");
    else
        search_status = tr("No reference found (%1s)").arg(time, 0, 'g', 3);
    if (!search_status.isEmpty())
    {
        ui.searchLog->setText(search_status);
        c2b::showMessage(search_status);
    }
    ui.buttonBox->button(QDialogButtonBox::Abort)->setEnabled(false);
    _searchB->setEnabled(true);
    QApplication::restoreOverrideCursor();
}

void c2bSearchInFiles::setBibTeXFile(const QString& file)
{
    if (!file.isEmpty())
    {
        QFileInfo fi(file);
        QDir d(fi.absolutePath());
        if (d.exists())
        {
            _bibtex_file = fi.absoluteFilePath();
            _bibtex_dir = fi.absolutePath();
        }
        else
            _bibtex_dir.clear();
    }
    if (_bibtex_dir.isEmpty())
        _search_log = tr("No existing file or directory set for searching");
    else if (ui.allBibFiles->isChecked())
        _search_log = tr("Search in files at %1").arg(_bibtex_dir);
    else
        _search_log = tr("Search in file %1").arg(_bibtex_file);
    updateForm();
}

void c2bSearchInFiles::setCurrentText(const QString& text)
{
    if (text.isEmpty())
        return;
    ui.pattern->setText(text);
    updateForm();
}

void c2bSearchInFiles::show()
{
    c2bUtils::setWidgetOnTop(this);
    ui.pattern->setFocus();
    QDialog::show();
}

void c2bSearchInFiles::help()
{
    c2bUtils::displayHelp("https://www.molspaces.com/cb2bib/doc/bibsearch/");
}
