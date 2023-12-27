/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bReferenceList.h"

#include "c2b.h"
#include "c2bBibParser.h"
#include "c2bCoreCiter.h"
#include "c2bRLWebSearchSettings.h"
#include "c2bSettings.h"
#include "c2bTextBrowser.h"
#include "c2bTextEdit.h"
#include "c2bUtils.h"

#include <bibSearcher.h>

#include <QHeaderView>
#include <QMenu>
#include <QScrollBar>
#include <QTimer>


class TreeWidgetItem : public QTreeWidgetItem
{
    // Reimplement sorting
public:
    explicit TreeWidgetItem(const QStringList& strings) : QTreeWidgetItem(strings) {}
    bool operator<(const QTreeWidgetItem& other) const
    {
        const int sortCol(treeWidget()->sortColumn());
        const QString str(c2bUtils::toAscii(text(sortCol), c2bUtils::Collation));
        const QString other_str(c2bUtils::toAscii(other.text(sortCol), c2bUtils::Collation));
        return str < other_str;
    }
};


c2bReferenceList::c2bReferenceList(c2bTextEdit* ed, c2bTextBrowser* br, QWidget* parentw) : QWidget(parentw)
{
    ui.setupUi(this);
    _editorP = ed;
    _browserP = br;
    _citerP = new c2bCoreCiter(this);
    _settingsP = c2bSettingsP;
    _settingsP->setDefaultValue("c2bReferenceList/SearchEngine", "https://www.google.com/search?ie=UTF-8&q=");
    _settingsP->setDefaultValue("c2bReferenceList/SearchEngineAddQuotes", false);
    setupFilterBar();

    _key_index = 0;
    _id_index = 1;
    _year_index = 2;
    _journal_index = 3;
    _author_index = 4;
    _title_index = 5;
    QStringList header;
    header.append(tr("Key"));
    header.append(tr("ID"));
    header.append(tr("Year"));
    header.append(tr("Journal"));
    header.append(tr("Author"));
    header.append(tr("Title"));
    ui.listView->sortItems(_key_index, Qt::AscendingOrder);
    ui.listView->setHeaderLabels(header);
    ui.listView->hideColumn(_id_index);
    ui.listView->setContextMenuPolicy(Qt::ActionsContextMenu);

    citeEntryAction = new QAction(this);
    citeEntryAction->setText(tr("Cite Selected Entries"));
    _settingsP->setKeysequence("Shortcuts/Editor/", citeEntryAction);
    connect(citeEntryAction, SIGNAL(triggered()), this, SLOT(citeEntry()));
    ui.listView->addAction(citeEntryAction);

    c2bUtils::addSeparator(ui.listView);
    openFileAction = new QAction(this);
    openFileAction->setText(tr("Open Document File"));
    openFileAction->setStatusTip(tr("Open document file"));
    _settingsP->setKeysequence("Shortcuts/Editor/", openFileAction);
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));
    ui.listView->addAction(openFileAction);

    openUrlAction = new QAction(this);
    openUrlAction->setText(tr("Open Document URL"));
    openUrlAction->setStatusTip(tr("Open document URL"));
    _settingsP->setKeysequence("Shortcuts/Editor/", openUrlAction);
    connect(openUrlAction, SIGNAL(triggered()), this, SLOT(openUrl()));
    ui.listView->addAction(openUrlAction);

    openDOIAction = new QAction(this);
    openDOIAction->setText(tr("Browse Reference by DOI"));
    openDOIAction->setStatusTip(tr("Browse reference by DOI"));
    _settingsP->setKeysequence("Shortcuts/Editor/", openDOIAction);
    connect(openDOIAction, SIGNAL(triggered()), this, SLOT(openDOI()));
    ui.listView->addAction(openDOIAction);

    c2bUtils::addSeparator(ui.listView);
    openAuthorsWebSearchAction = new QAction(this);
    openAuthorsWebSearchAction->setText(tr("Web Search by Author"));
    openAuthorsWebSearchAction->setStatusTip(tr("Web search by Author"));
    _settingsP->setKeysequence("Shortcuts/Editor/", openAuthorsWebSearchAction);
    connect(openAuthorsWebSearchAction, SIGNAL(triggered()), this, SLOT(openAuthorWebSearch()));
    ui.listView->addAction(openAuthorsWebSearchAction);
    openTitleWebSearchAction = new QAction(this);
    openTitleWebSearchAction->setText(tr("Web Search by Title"));
    openTitleWebSearchAction->setStatusTip(tr("Web search by Title"));
    _settingsP->setKeysequence("Shortcuts/Editor/", openTitleWebSearchAction);
    connect(openTitleWebSearchAction, SIGNAL(triggered()), this, SLOT(openTitleWebSearch()));
    ui.listView->addAction(openTitleWebSearchAction);

    c2bUtils::addSeparator(ui.listView);
    webSearchSettingsAction = new QAction(this);
    webSearchSettingsAction->setText(tr("Web Search Settings"));
    webSearchSettingsAction->setStatusTip(tr("Web search settings"));
    _settingsP->setKeysequence("Shortcuts/Editor/", webSearchSettingsAction);
    connect(webSearchSettingsAction, SIGNAL(triggered()), this, SLOT(webSearchSettings()));
    ui.listView->addAction(webSearchSettingsAction);

    c2bUtils::addSeparator(ui.listView);
    clearSelectionsAction = new QAction(this);
    clearSelectionsAction->setText(tr("Clear Entry Selection"));
    clearSelectionsAction->setStatusTip(tr("Clear entry selection"));
    _settingsP->setKeysequence("Shortcuts/Editor/", clearSelectionsAction);
    connect(clearSelectionsAction, SIGNAL(triggered()), this, SLOT(clearSelections()));
    ui.listView->addAction(clearSelectionsAction);

    c2bUtils::addSeparator(ui.listView);
    refreshListAction = new QAction(this);
    refreshListAction->setShortcut(QKeySequence(QKeySequence::Refresh));
    refreshListAction->setText(tr("Refresh List and Browser"));
    refreshListAction->setStatusTip(tr("Refresh list and browser"));
    connect(refreshListAction, SIGNAL(triggered()), this, SLOT(refreshList()));
    ui.listView->addAction(refreshListAction);
    connect(ui.listView, SIGNAL(itemActivated(QTreeWidgetItem*,int)), this, SLOT(goToReference(QTreeWidgetItem*)));

    // Actions dependent on selection and availability
    itemSelectionChanged();
    connect(ui.listView, SIGNAL(itemSelectionChanged()), this, SLOT(itemSelectionChanged()));

    // Browser functionality
    _references_html = c2bUtils::fileToString(":/htm/htm/references.html");
    _references_html.replace("GET_CB2BIB_VERSION_NUMBER", C2B_VERSION);
    _bib_item_html = c2bUtils::fileToString(":/htm/htm/bib_item.html");
    QString references_css(c2bUtils::fileToString(_settingsP->fileName("cb2Bib/BrowserCssFile")));
    if (references_css.isEmpty())
        references_css = c2bUtils::fileToString(":/htm/htm/references.css");
    _browserP->document()->setDefaultStyleSheet(references_css);

    openTextLocalSearchAction = new QAction(this);
    openTextLocalSearchAction->setText(tr("Local Search for Selected Text"));
    openTextLocalSearchAction->setStatusTip(tr("Local search for selected text"));
    _settingsP->setKeysequence("Shortcuts/Editor/", openTextLocalSearchAction);
    connect(openTextLocalSearchAction, SIGNAL(triggered()), this, SLOT(openTextLocalSearch()));
    openTextLocalSearchAction->setEnabled(false);
    connect(_browserP, SIGNAL(copyAvailable(bool)), openTextLocalSearchAction, SLOT(setEnabled(bool)));
    openTextWebSearchAction = new QAction(this);
    openTextWebSearchAction->setText(tr("Web Search for Selected Text"));
    openTextWebSearchAction->setStatusTip(tr("Web search for selected text"));
    _settingsP->setKeysequence("Shortcuts/Editor/", openTextWebSearchAction);
    connect(openTextWebSearchAction, SIGNAL(triggered()), this, SLOT(openTextWebSearch()));
    openTextWebSearchAction->setEnabled(false);
    connect(_browserP, SIGNAL(copyAvailable(bool)), openTextWebSearchAction, SLOT(setEnabled(bool)));

    QList<QAction*> al = ui.listView->actions();
    for (int i = 0; i < 2; ++i)
        _browserP->addAction(al.at(i));
    _browserP->addAction(openTextLocalSearchAction);
    _browserP->addAction(openTextWebSearchAction);
    c2bUtils::addSeparator(_browserP);
    for (int i = 6; i < al.count(); ++i)
        _browserP->addAction(al.at(i));
    _browserP->setContextMenuPolicy(Qt::ActionsContextMenu);

    connect(_browserP, SIGNAL(anchorClicked(QUrl)), this, SLOT(openLink(QUrl)));
    connect(_browserP, SIGNAL(highlighted(QString)), parentw->parent(), SLOT(showMessage(QString)));
}

c2bReferenceList::~c2bReferenceList() {}


void c2bReferenceList::loadList(const QString& txt, bibSearcher* searcher)
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    c2bBibParser* bpP(c2b::bibParser());
    QString references_html(_references_html);
    QString references;

    QStringList fields;
    fields.append("abstract");
    fields.append("author");
    fields.append("booktitle");
    fields.append("doi");
    fields.append("editor");
    fields.append("file");
    fields.append("journal");
    fields.append("pages");
    fields.append("title");
    fields.append("url");
    fields.append("volume");
    fields.append("year");
    bibReference ref;
    bpP->initReferenceParsing(_editorP->editorFilename(), fields, &ref);
    const QRegExp initials1("\\b\\w\\b");
    const QRegExp initials2("[^\\w\\s]");
    const QRegExp nonletters("[^\\w\\s-]");
    int ref_counter(0);

    while (bpP->referencesIn(txt, &ref))
    {
        QString author(ref.anyAuthor());
        QString author_long;
        if (!author.isEmpty())
        {
            author = bpP->authorFromBibTeX(author);
            author_long = author;
            author_long.remove(nonletters);
            author_long.replace(" and ", ", ");
            c2bUtils::simplifyString(author_long);
            author_long += '.';
            author.remove(initials1);
            author.remove(initials2);
            author.replace(" and ", ", ");
            c2bUtils::simplifyString(author);
        }

        QString title(ref.anyTitle());
        c2bUtils::cleanTitle(title, true);

        QString doi(ref.value("doi"));
        if (!doi.isEmpty())
            if (!doi.startsWith("http"))
                doi = "https://dx.doi.org/" + QUrl::toPercentEncoding(doi);

        const QString file(ref.value("file"));
        const QString url(ref.value("url"));
        QString link;
        if (!file.isEmpty())
            link = QDir::cleanPath(file);
        else if (!url.isEmpty())
            link = url;
        else if (!doi.isEmpty())
            link = doi;

        QString ID;
        ID.setNum(ref_counter + 1);
        QString year(ref.value("year"));
        const QString abstract(ref.value("abstract"));
        const QString journal(ref.anyJournal());
        const QString key(ref.citeidName);

        _doiList.append(doi);
        _fileList.append(file);
        _urlList.append(url);
        _positionList.append(ref.positionValue);
        QStringList dataList;
        dataList.append(key);
        dataList.append(ID);
        dataList.append(year);
        dataList.append(journal);
        dataList.append(author);
        dataList.append(title);
        TreeWidgetItem* qi(new TreeWidgetItem(dataList));
        qi->setStatusTip(_journal_index, bpP->fullJournal(journal));
        qi->setStatusTip(_author_index, author_long);
        qi->setStatusTip(_title_index, title);
        ui.listView->insertTopLevelItem(0, qi);

        QString pages(ref.value("pages"));
        const QString volume(ref.value("volume"));
        if (!pages.isEmpty())
        {
            if (!volume.isEmpty())
                pages = ", " + pages;
            else
                pages = ' ' + pages;
        }
        if (!year.isEmpty())
            year = '(' + year + ").";
        QString bib_item_html(_bib_item_html);
        bib_item_html.replace("GET_REFERENCE_ANCHOR_ID", ID);
        bib_item_html.replace("GET_REFERENCE_ANCHOR_NAME", ID);
        bib_item_html.replace("GET_REFERENCE_AUTHOR", author_long);
        bib_item_html.replace("GET_REFERENCE_LINK", link);
        bib_item_html.replace("GET_REFERENCE_PAGES", pages);
        bib_item_html.replace("GET_REFERENCE_SOURCE", journal);
        bib_item_html.replace("GET_REFERENCE_TITLE", c2bUtils::toHtmlString(title));
        bib_item_html.replace("GET_REFERENCE_VOLUME", volume);
        bib_item_html.replace("GET_REFERENCE_YEAR", year);
        if (searcher)
        {
            if (searcher->isSearchSimilar())
                bib_item_html.replace("GET_REFERENCE_ABSTRACT",
                                      c2bUtils::toHtmlString(abstract) + searcher->hitHtmlDatum(ref_counter));
            else
                bib_item_html.replace("GET_REFERENCE_ABSTRACT",
                                      searcher->hitHtmlAbstract(ref_counter) + searcher->hitHtmlDatum(ref_counter));
        }
        else
            bib_item_html.replace("GET_REFERENCE_ABSTRACT", c2bUtils::toHtmlString(abstract));
        references += bib_item_html;
        ++ref_counter;
    }
    if (searcher && ref_counter != searcher->hitsCount())
        c2bUtils::warn(tr("Mismatch while loading searched references"));

    ui.listView->sortItems(ui.listView->sortColumn(), ui.listView->header()->sortIndicatorOrder());
    ui.listView->resizeColumnToContents(_year_index);
    references_html.replace("GET_REFERENCES", references);
    _browserP->updateHtml(references_html);
    QApplication::restoreOverrideCursor();
    c2b::showMessage(tr("Parsed %1 references.").arg(ref_counter));
}

void c2bReferenceList::citeEntry()
{
    QStringList keys;
    QTreeWidgetItemIterator it(ui.listView, QTreeWidgetItemIterator::Selected | QTreeWidgetItemIterator::NotHidden);
    while (*it)
    {
        if (!(*it)->text(_key_index).isEmpty())
            keys.append((*it)->text(_key_index));
        ++it;
    }
    _citerP->cite(keys);
}

void c2bReferenceList::openDOI()
{
    bool zdoi(false);
    QTreeWidgetItemIterator it(ui.listView, QTreeWidgetItemIterator::Selected | QTreeWidgetItemIterator::NotHidden);
    while (*it)
    {
        const QString doi(_doiList.at((*it)->text(_id_index).toInt() - 1));
        if (!doi.isEmpty())
        {
            zdoi = true;
            c2bUtils::openFile(doi, parentWidget());
        }
        ++it;
    }
    if (!zdoi)
        c2b::showMessage(tr("No DOI entry among selected references."));
}

void c2bReferenceList::openFile()
{
    bool zfile(false);
    QTreeWidgetItemIterator it(ui.listView, QTreeWidgetItemIterator::Selected | QTreeWidgetItemIterator::NotHidden);
    while (*it)
    {
        const QString file(_fileList.at((*it)->text(_id_index).toInt() - 1));
        if (!file.isEmpty())
        {
            zfile = true;
            c2bUtils::openFile(file, parentWidget());
        }
        ++it;
    }
    if (!zfile)
        c2b::showMessage(tr("No file entry among selected references."));
}

void c2bReferenceList::openUrl()
{
    bool zurl(false);
    QTreeWidgetItemIterator it(ui.listView, QTreeWidgetItemIterator::Selected | QTreeWidgetItemIterator::NotHidden);
    while (*it)
    {
        const QString url(_urlList.at((*it)->text(_id_index).toInt() - 1));
        if (!url.isEmpty())
        {
            zurl = true;
            c2bUtils::openFile(url, parentWidget());
        }
        ++it;
    }
    if (!zurl)
        c2b::showMessage(tr("No URL entry among selected references."));
}

void c2bReferenceList::openLink(const QUrl& ln)
{
    QString ln_str(QUrl::fromPercentEncoding(ln.toEncoded()));
    if (ln_str.isEmpty())
        c2b::showMessage(tr("No link available for this reference."));
    else if (ln_str.startsWith("Select reference "))
        scrollToReference(ln_str.remove(QRegExp("\\D")));
    else if (ln_str.contains(QRegExp(":\\d+$")))
        emit openFile(ln_str);
    else
        c2bUtils::openFile(ln_str, parentWidget());
}

void c2bReferenceList::openAuthorWebSearch()
{
    const QString searchEngine(_settingsP->value("c2bReferenceList/SearchEngine").toString());
    bool zwebs(false);
    QTreeWidgetItemIterator it(ui.listView, QTreeWidgetItemIterator::Selected | QTreeWidgetItemIterator::NotHidden);
    while (*it)
    {
        if (!(*it)->text(_author_index).isEmpty())
        {
            zwebs = true;
            QString webs((*it)->text(_author_index));
            webs.remove(',');
            webs = searchEngine + webs.simplified();
            c2bUtils::openFile(webs, parentWidget());
        }
        ++it;
    }
    if (!zwebs)
        c2b::showMessage(tr("No author entry among selected references."));
}

void c2bReferenceList::openTitleWebSearch()
{
    const QString searchEngine(_settingsP->value("c2bReferenceList/SearchEngine").toString());
    const bool addQuotes(_settingsP->value("c2bReferenceList/SearchEngineAddQuotes").toBool());
    bool zwebs(false);
    QTreeWidgetItemIterator it(ui.listView, QTreeWidgetItemIterator::Selected | QTreeWidgetItemIterator::NotHidden);
    while (*it)
    {
        if (!(*it)->text(_title_index).isEmpty())
        {
            zwebs = true;
            QString webs((*it)->text(_title_index));
            if (addQuotes)
                webs = '\"' + webs + '\"';
            webs = searchEngine + webs;
            c2bUtils::openFile(webs, parentWidget());
        }
        ++it;
    }
    if (!zwebs)
        c2b::showMessage(tr("No title entry among selected references."));
}

void c2bReferenceList::openTextWebSearch()
{
    const QString searchEngine(_settingsP->value("c2bReferenceList/SearchEngine").toString());
    QString webs(_browserP->textCursor().selectedText());
    if (_settingsP->value("c2bReferenceList/SearchEngineAddQuotes").toBool())
        webs = '\"' + webs + '\"';
    webs = searchEngine + webs;
    c2bUtils::openFile(webs, parentWidget());
}

void c2bReferenceList::webSearchSettings()
{
    c2bRLWebSearchSettings searchSettings(this);
    searchSettings.exec();
}

void c2bReferenceList::openTextLocalSearch()
{
    const QString text(_browserP->textCursor().selectedText());
    const QString fn(_editorP->editorFilename());
    c2b::doSearchInFiles(text, fn);
}

void c2bReferenceList::refreshList()
{
    _doiList.clear();
    _fileList.clear();
    _urlList.clear();
    _positionList.clear();
    ui.listView->clear();
    ui.comboFilter->clearEditText();
    loadList(_editorP->toPlainText());
}

void c2bReferenceList::goToReference(const QString& id)
{
    QTextCursor tc(_editorP->textCursor());
    tc.setPosition(_positionList.at(id.toInt() - 1));
    _editorP->setTextCursor(tc);
    _editorP->verticalScrollBar()->setValue(_editorP->verticalScrollBar()->maximum());
    _editorP->ensureCursorVisible();

    _browserP->scrollToAnchor(id);
    int scrollPosition(_browserP->verticalScrollBar()->value());
    _browserP->verticalScrollBar()->setValue(scrollPosition - 10);
}

void c2bReferenceList::goToReference(const int position)
{
    // Maps position to internal reference id. It is needed by the search browser, when a
    // citation is edited in the original file. If this file is changed multiple times,
    // positions in the search browser get outdated, so the mapping position-id is inexact.
    // Thus, search for the closest reference.
    int ip(0);
    int pdiff_min(1000000);
    for (int i = 0; i < _positionList.count(); ++i)
    {
        int p(_positionList.at(i));
        if (p == position)
        {
            ip = i;
            break;
        }
        int pdiff(abs(p - position));
        if (pdiff < pdiff_min)
        {
            pdiff_min = pdiff;
            ip = i;
        }
    }
    QString id;
    goToReference(id.setNum(ip + 1));
}

void c2bReferenceList::goToReference(QTreeWidgetItem* ref)
{
    if (ref == 0)
        return;
    const QString id(ref->text(_id_index));
    goToReference(id);
}

void c2bReferenceList::scrollToReference(const QString& id)
{
    if (id.isEmpty())
        return;
    QList<QTreeWidgetItem*> items(ui.listView->findItems(id, Qt::MatchExactly, 1));
    if (items.count() == 0)
        return;
    QTreeWidgetItem* item(items.at(0));
    ui.listView->setFocus();
    item->setSelected(!item->isSelected());
    ui.listView->scrollToItem(item);

    QTextCursor tc(_editorP->textCursor());
    tc.setPosition(_positionList.at(id.toInt() - 1));
    _editorP->setTextCursor(tc);
    _editorP->verticalScrollBar()->setValue(_editorP->verticalScrollBar()->maximum());
    _editorP->ensureCursorVisible();
}

void c2bReferenceList::clearSelections()
{
    disconnect(ui.listView, SIGNAL(itemSelectionChanged()), this, SLOT(itemSelectionChanged()));
    QTreeWidgetItemIterator it(ui.listView, QTreeWidgetItemIterator::Selected);
    while (*it)
    {
        (*it)->setSelected(false);
        ++it;
    }
    itemSelectionChanged();
    connect(ui.listView, SIGNAL(itemSelectionChanged()), this, SLOT(itemSelectionChanged()));
}

void c2bReferenceList::itemSelectionChanged()
{
    int entries(0);
    int doi(0);
    int file(0);
    int url(0);
    int author(0);
    int title(0);
    QTreeWidgetItemIterator it(ui.listView, QTreeWidgetItemIterator::Selected | QTreeWidgetItemIterator::NotHidden);
    while (*it)
    {
        if (!_doiList.at((*it)->text(_id_index).toInt() - 1).isEmpty())
            ++doi;
        if (!_fileList.at((*it)->text(_id_index).toInt() - 1).isEmpty())
            ++file;
        if (!_urlList.at((*it)->text(_id_index).toInt() - 1).isEmpty())
            ++url;
        if (!(*it)->text(_author_index).isEmpty())
            ++author;
        if (!(*it)->text(_title_index).isEmpty())
            ++title;
        ++entries;
        ++it;
    }
    citeEntryAction->setEnabled(entries > 0);
    citeEntryAction->setStatusTip(tr("Cite selected entries. %1 Entries selected.").arg(entries));
    openDOIAction->setEnabled(doi > 0);
    openDOIAction->setStatusTip(tr("Browse reference by DOI. %1 DOIs in selected entries.").arg(doi));
    openFileAction->setEnabled(file > 0);
    openFileAction->setStatusTip(tr("Open document file. %1 Files in selected entries.").arg(file));
    openUrlAction->setEnabled(url > 0);
    openUrlAction->setStatusTip(tr("Open document URL. %1 URLs in selected entries.").arg(url));
    openAuthorsWebSearchAction->setEnabled(author > 0);
    openAuthorsWebSearchAction->setStatusTip(tr("Web search by Author. %1 Entries selected.").arg(author));
    openTitleWebSearchAction->setEnabled(title > 0);
    openTitleWebSearchAction->setStatusTip(tr("Web search by Title. %1 Entries selected.").arg(title));
    emit hasSelectedItems(entries > 0);
}

QStringList c2bReferenceList::selectedKeys() const
{
    QStringList keys;
    QTreeWidgetItemIterator it(ui.listView, QTreeWidgetItemIterator::Selected | QTreeWidgetItemIterator::NotHidden);
    while (*it)
    {
        if (!(*it)->text(_key_index).isEmpty())
            keys.append((*it)->text(_key_index));
        ++it;
    }
    return keys;
}

void c2bReferenceList::setLyXPipe()
{
    _citerP->setLyXPipe();
}


/***************************************************************************
    Filter Bar
 ***************************************************************************/

void c2bReferenceList::setupFilterBar()
{
    const QStringList types(searchPattern::types());
    _filter_mode = _settingsP->value("c2bReferenceList/FilterMode", types.first()).toString();
    QActionGroup* filterMode = new QActionGroup(this);
    filterMode->setExclusive(true);
    for (int i = 0; i < types.count(); ++i)
    {
        const QString& t = types.at(i);
        QAction* act = filterMode->addAction(t);
        act->setCheckable(true);
        if (_filter_mode == t)
            act->setChecked(true);
    }
    QMenu* filterModeM = new QMenu(this);
    filterModeM->addActions(filterMode->actions());
    ui.filterB->setMenu(filterModeM);
    connect(filterMode, SIGNAL(triggered(QAction*)), this, SLOT(setFilterMode(QAction*)));
    connect(ui.comboFilter, SIGNAL(editTextChanged(QString)), this, SLOT(blockFilterSignals()));
}

void c2bReferenceList::setFilterMode(QAction* mode)
{
    _filter_mode = mode->text();
    _settingsP->setValue("c2bReferenceList/FilterMode", _filter_mode);
    filterList();
}

void c2bReferenceList::blockFilterSignals()
{
    ui.comboFilter->blockSignals(true);
    QTimer::singleShot(500, this, SLOT(filterList()));
}

void c2bReferenceList::filterList()
{
    const QString text(ui.comboFilter->currentText());
    if (text.isEmpty())
    {
        QTreeWidgetItemIterator it(ui.listView);
        while (*it)
        {
            (*it)->setHidden(false);
            ++it;
        }
    }
    else
    {
        searchPattern pattern(text, _filter_mode);
        QTreeWidgetItemIterator it(ui.listView);
        while (*it)
        {
            QTreeWidgetItem* item = *it;
            if (pattern.matches(item->text(_author_index)) || pattern.matches(item->text(_title_index)))
                item->setHidden(false);
            else
                item->setHidden(true);
            ++it;
        }
        QTimer::singleShot(5000, this, SLOT(keepFilterPattern()));
    }
    itemSelectionChanged();
    ui.comboFilter->blockSignals(false);
}

void c2bReferenceList::keepFilterPattern()
{
    const QString text(ui.comboFilter->currentText());
    if (!text.isEmpty())
        if (ui.comboFilter->findText(text) < 0)
            ui.comboFilter->addItem(text);
}
