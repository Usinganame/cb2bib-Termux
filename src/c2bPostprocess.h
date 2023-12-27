/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BPOSTPROCESS_H
#define C2BPOSTPROCESS_H

#include "ui_c2bLogWidget.h"

#include <QDialog>


class QProcess;

class c2bPostprocess : public QDialog
{

    Q_OBJECT

public:
    explicit c2bPostprocess(const QString& fn, QWidget* parentw = 0);
    ~c2bPostprocess();


protected:
    void PProcessFile();
    void addToLog();


protected slots:
    void conversionEnded();
    void help();
    void openFile();


private:
    QProcess* _ppBibTeX;
    QPushButton* _buttonOpenFile;
    QString PPBIBTEX_ARG;
    QString PPBIBTEX_BIN;
    QString PPBIBTEX_EXT;
    QString _bib;
    QString _out;
    Ui::c2bLogWidget ui;
};

#endif
