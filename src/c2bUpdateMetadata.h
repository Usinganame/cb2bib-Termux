/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BUPDATEMETADATA_H
#define C2BUPDATEMETADATA_H

#include "ui_c2bLogWidget.h"

#include <QDialog>


class bibReference;
class c2bBibParser;


class c2bUpdateMetadata : public QDialog
{

    Q_OBJECT

public:
    explicit c2bUpdateMetadata(QWidget* parentw = 0);
    ~c2bUpdateMetadata();

    void update(const QString& fn, const QString& bibtex);


private slots:
    void aborted();
    void help();
    void update();


private:
    QPushButton* _buttonAbort;
    QString _bibtex;
    QString _fn;
    Ui::c2bLogWidget ui;
    bool _aborted;
    bool needsUpdating(const bibReference& ref, const bibReference& mref);
    c2bBibParser* _bpP;
    void writeDifferences(const bibReference& ref, const bibReference& mref);
};

#endif
