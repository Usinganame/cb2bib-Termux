/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BSAVEREGEXP_H
#define C2BSAVEREGEXP_H

#include "ui_c2bSaveRegExp.h"

#include <QDialog>


class c2bSaveREHighlighter;

class c2bSaveRegExp : public QDialog
{

    Q_OBJECT

public:
    c2bSaveRegExp(const QStringList& pattern, const QString& input, QWidget* parentw = 0);
    ~c2bSaveRegExp();


signals:
    void savePatternInfo(const QString& rx, const QString& rxname);


public slots:
    void accept();
    void help();
    void updateInput(const QString& text);


private:
    QRegExp _pattern_rx;
    QString _input_text;
    Ui::c2bSaveRegExp ui;
    c2bSaveREHighlighter* _sreS;


private slots:
    void inputMightHaveChanged();
    void setInformation();
};

#endif
