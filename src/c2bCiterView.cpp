/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bCiterView.h"

#include "c2bCiterExcerptView.h"

#include <bibSearcher.h>

#include <QApplication>
#include <QHeaderView>
#include <QKeyEvent>


c2bCiterView::c2bCiterView(QWidget* parentw) : QTableView(parentw)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setShowGrid(false);
    setTabKeyNavigation(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    horizontalHeader()->setVisible(false);
    verticalHeader()->setDefaultSectionSize(fontMetrics().height() + 5);
    verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader()->setVisible(false);

    _citationsP = 0;
    _filter_mode = false;
}


void c2bCiterView::reloadModel(QAbstractItemModel* citations, const QStringList& bibtex_files, const c2bCiter::State& s)
{
    _filter_mode = false;
    _filter_string.clear();
    if (!citations)
        return;
    if (_citationsP != citations)
    {
        _citationsP = static_cast<c2bCiterModel*>(citations);
        QTableView::setModel(_citationsP);
        connect(_citationsP, SIGNAL(patternFilterChanged(QString)), this, SLOT(updatePatternFilter(QString)));
    }
    QModelIndex i(currentIndex());
    _citationsP->reloadCitations(bibtex_files, s, &i);
    updateViewport();
    updateCurrentIndex(i);
}

c2bCiter::State c2bCiterView::currentState() const
{
    if (_citationsP)
        return _citationsP->currentState(currentIndex());
    else
        return c2bCiter::State();
}

void c2bCiterView::showPreviousState()
{
    QModelIndex i(currentIndex());
    _citationsP->restorePreviousState(&i);
    updateViewport();
    updateCurrentIndex(i);
}

void c2bCiterView::showNextState()
{
    QModelIndex i(currentIndex());
    _citationsP->restoreNextState(&i);
    updateViewport();
    updateCurrentIndex(i);
}

void c2bCiterView::clearCurrentFilter()
{
    QModelIndex i(currentIndex());
    _citationsP->clearCurrentFilter(&i);
    updateViewport();
    updateCurrentIndex(i);
}

void c2bCiterView::setPatternFilter(const QString& pattern)
{
    QModelIndex i(currentIndex());
    _filter_string = pattern;
    _citationsP->setPatternFilter(_filter_string, &i, _citationsP->currentFormat());
    updateViewport();
    updateCurrentIndex(i);
}

void c2bCiterView::updatePatternFilter(const QString& pattern)
{
    _filter_string = pattern;
    emit patternFilterChanged(false, _filter_string);
}

void c2bCiterView::setRelatedFilter()
{
    if (_citationsP->count() == 0)
        return;
    QModelIndex i(currentIndex());
    if (_citationsP->currentFormat() == c2bCiter::K)
    {
        const QString k(_citationsP->dataKeyword(i));
        _citationsP->setKeywordFilter(k, &i);
        updateViewport();
        updateCurrentIndex(i);
    }
    else
    {
        const QString f(_citationsP->dataFile(i));
        if (f.isEmpty())
            emit statusMessage(tr("No File contents in this reference."));
        else
        {
            _citationsP->setRelatedFilter(f, &i);
            updateViewport();
            updateCurrentIndex(i);
        }
    }
}

void c2bCiterView::toggleSelectedFilter()
{
    QModelIndex i(currentIndex());
    if (_citationsP->currentFilter() == c2bCiter::Selected)
        _citationsP->restoreLastNonSelectedState(&i);
    else
        _citationsP->setSelectedFilter(&i);
    updateViewport();
    updateCurrentIndex(i);
}

void c2bCiterView::toggleKeywordView()
{
    if (_citationsP->count() == 0)
        return;
    QModelIndex i(currentIndex());
    if (_citationsP->currentFormat() == c2bCiter::K)
    {
        _citationsP->restoreLastNonKeywordState(&i);
        updateViewport();
        updateCurrentIndex(i);
    }
    else
    {
        const QString f(_citationsP->dataFile(i));
        if (f.isEmpty())
            emit statusMessage(tr("No File contents in this reference."));
        else
        {
            _citationsP->setDocumentFilter(f, &i);
            updateViewport();
            updateCurrentIndex(i);
        }
    }
}

void c2bCiterView::toggleGlossaryView()
{
    QModelIndex i(currentIndex());
    if (_citationsP->currentFormat() == c2bCiter::K &&
        (_citationsP->currentFilter() == c2bCiter::None || _citationsP->currentFilter() == c2bCiter::Pattern))
        _citationsP->restoreLastNonKeywordState(&i);
    else
        _citationsP->setGlossaryView(&i);
    updateViewport();
    updateCurrentIndex(i);
}

void c2bCiterView::keywordDocumentSearch()
{
    const c2bCiter::KeywordData kd(_citationsP->keywordData(currentIndex()));
    if (!kd.valid)
        return;

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    const QString excerpt(bibSearcher::searchDocumentKeyword(kd.bibtexfn, kd.documentfn, kd.keyword));
    QApplication::restoreOverrideCursor();
    if (excerpt.isEmpty())
    {
        emit statusMessage(tr("Keyword variation '%1' not available in this reference.").arg(kd.keyword));
        return;
    }
    c2bCiterExcerptView cev(excerpt, this);
    cev.exec();
}

void c2bCiterView::updateCurrentIndex(const QModelIndex& i)
{
    setCurrentIndex(i);
    scrollTo(i, PositionAtCenter);
}

void c2bCiterView::updateFormat(const c2bCiter::Format& format)
{
    if (!_citationsP)
        return;
    QModelIndex i(currentIndex());
    _citationsP->updateFormat(format, &i);
    updateViewport();
    updateCurrentIndex(i);
}

void c2bCiterView::updateViewport()
{
    if (!_citationsP)
        return;
    const int nc(_citationsP->columnCount());
    if (nc < 1)
        return;
    const int vp_w(viewport()->size().width());
    if (nc == 1)
    {
        setColumnWidth(0, vp_w);
        return;
    }
    QList<int> w = _citationsP->sizeHintForColumns();
#if QT_VERSION >= QT_VERSION_CHECK(5, 11, 0)
    const int char_w(fontMetrics().horizontalAdvance(QLatin1Char('N')));
#else
    const int char_w(fontMetrics().width(QLatin1Char('N')));
#endif
    for (int i = 0; i < nc; ++i)
        w[i] *= char_w;
    int required_w(w.at(0));
    if (required_w >= vp_w)
    {
        setColumnWidth(0, vp_w);
        for (int i = 1; i < nc; ++i)
            setColumnWidth(i, 0);
        return;
    }
    for (int i = 1; i < nc; ++i)
        required_w += w.at(i);
    if (required_w > vp_w)
    {
        int available_w(vp_w - w.at(0));
        int div[] = { 0, 0, 0, 0 };
        while (available_w > 0)
            for (int i = 1; i < nc; ++i)
                if (div[i] < w.at(i))
                {
                    div[i] += 1;
                    --available_w;
                }
        for (int i = 1; i < nc; ++i)
            w[i] = div[i];
    }
    else
        w[nc - 1] += vp_w - required_w;
    for (int i = 0; i < nc; ++i)
        setColumnWidth(i, w.at(i));
}

void c2bCiterView::keyPressEvent(QKeyEvent* qevent)
{
    if (_filter_mode)
    {
        switch (qevent->key())
        {
        case Qt::Key_Enter:
        case Qt::Key_Return:
        case Qt::Key_Down:
        case Qt::Key_Escape:
        case Qt::Key_Up:
        case Qt::Key_Tab:
            _filter_mode = false;
            emit patternFilterChanged(_filter_mode, _filter_string);
            qevent->accept();
            return;
        }
        switch (qevent->key())
        {
        case Qt::Key_Backspace:
            _filter_string.chop(1);
            break;
        default:
            _filter_string += c2bUtils::toAscii(qevent->text(), c2bUtils::Collation);
        }
        emit patternFilterChanged(_filter_mode, _filter_string);
        setPatternFilter(_filter_string);
        qevent->ignore();
        return;
    }
    if (qevent->modifiers() & Qt::ShiftModifier)
    {
        if (!qevent->text().isEmpty())
            QTableView::keyboardSearch(qevent->text());
        qevent->accept();
        return;
    }
    switch (qevent->key())
    {
    // Formats
    case Qt::Key_A:
        updateFormat(c2bCiter::AJYT);
        qevent->accept();
        return;
    case Qt::Key_I:
        updateFormat(c2bCiter::IT);
        qevent->accept();
        return;
    case Qt::Key_J:
        updateFormat(c2bCiter::JYA);
        qevent->accept();
        return;
    case Qt::Key_T:
        updateFormat(c2bCiter::T);
        qevent->accept();
        return;
    case Qt::Key_Y:
        updateFormat(c2bCiter::YAJT);
        qevent->accept();
        return;

    // Filters
    case Qt::Key_Delete:
        _citationsP->clearSelection();
        qevent->accept();
        return;
    case Qt::Key_D:
        clearCurrentFilter();
        qevent->accept();
        return;
    case Qt::Key_F:
        _filter_mode = true;
        emit patternFilterChanged(_filter_mode, _filter_string);
        qevent->accept();
        return;
    case Qt::Key_G:
        toggleGlossaryView();
        qevent->accept();
        return;
    case Qt::Key_K:
        toggleKeywordView();
        qevent->accept();
        return;
    case Qt::Key_R:
        setRelatedFilter();
        qevent->accept();
        return;
    case Qt::Key_S:
        toggleSelectedFilter();
        qevent->accept();
        return;

    // Actions
    case Qt::Key_Left:
        showPreviousState();
        qevent->accept();
        return;
    case Qt::Key_Right:
        showNextState();
        qevent->accept();
        return;
    case Qt::Key_C:
        emit citeReferences();
        qevent->accept();
        return;
    case Qt::Key_E:
        emit editReference();
        qevent->accept();
        return;
    case Qt::Key_O:
        emit openFile();
        qevent->accept();
        return;
    case Qt::Key_U:
        emit openUrl();
        qevent->accept();
        return;
    case Qt::Key_V:
        keywordDocumentSearch();
        qevent->accept();
        return;
    case Qt::Key_W:
        emit openAnnote();
        qevent->accept();
        return;
    case Qt::Key_Escape:
        emit hideCiter();
        qevent->accept();
        return;

    // Navigation
    case Qt::Key_Tab:
    {
        QKeyEvent ke(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier);
        QTableView::keyPressEvent(&ke);
        qevent->accept();
        return;
    }
    case Qt::Key_Backspace:
    {
        QKeyEvent ke(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
        QTableView::keyPressEvent(&ke);
        qevent->accept();
        return;
    }
    case Qt::Key_Home:
    {
        QKeyEvent ke(QEvent::KeyPress, Qt::Key_Home, Qt::ControlModifier);
        QTableView::keyPressEvent(&ke);
        qevent->accept();
        return;
    }
    case Qt::Key_End:
    {
        QKeyEvent ke(QEvent::KeyPress, Qt::Key_End, Qt::ControlModifier);
        QTableView::keyPressEvent(&ke);
        qevent->accept();
        return;
    }
    case Qt::Key_Space:
    {
        QKeyEvent ke(QEvent::KeyPress, Qt::Key_PageDown, Qt::NoModifier);
        QTableView::keyPressEvent(&ke);
        qevent->accept();
        return;
    }
    case Qt::Key_Enter:
    case Qt::Key_Return:
    {
        QTableView::keyPressEvent(qevent);
        QKeyEvent ke(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier);
        QTableView::keyPressEvent(&ke);
        qevent->accept();
        return;
    }
    default:
        QTableView::keyPressEvent(qevent);
        qevent->ignore();
    }
}

void c2bCiterView::resizeEvent(QResizeEvent* qevent)
{
    updateViewport();
    QTableView::resizeEvent(qevent);
}

void c2bCiterView::keyboardSearch(const QString& /* search */) {}
