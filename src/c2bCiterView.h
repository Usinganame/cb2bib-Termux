/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BCITERVIEW_H
#define C2BCITERVIEW_H

#include "c2bCiterModel.h"

#include <QTableView>


class c2bCiterView : public QTableView
{

    Q_OBJECT

public:
    explicit c2bCiterView(QWidget* parentw = 0);
    inline ~c2bCiterView() {}

    c2bCiter::State currentState() const;
    void reloadModel(QAbstractItemModel* citations, const QStringList& bibtex_files, const c2bCiter::State& s);
    void setPatternFilter(const QString& pattern);


signals:
    void citeReferences();
    void editReference();
    void hideCiter();
    void openAnnote();
    void openFile();
    void openUrl();
    void patternFilterChanged(const bool mode, const QString& pattern);
    void statusMessage(const QString& message);


protected:
    void keyPressEvent(QKeyEvent* qevent);
    void keyboardSearch(const QString& search);
    void resizeEvent(QResizeEvent* qevent);


public slots:
    void updatePatternFilter(const QString& pattern);


private:
    void clearCurrentFilter();
    void keywordDocumentSearch();
    void setRelatedFilter();
    void showNextState();
    void showPreviousState();
    void toggleGlossaryView();
    void toggleKeywordView();
    void toggleSelectedFilter();
    void updateCurrentIndex(const QModelIndex& i);
    void updateFormat(const c2bCiter::Format& format);
    void updateViewport();

    QString _filter_string;
    bool _filter_mode;
    c2bCiterModel* _citationsP;
};

#endif
