/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BCONSOLE_H
#define C2BCONSOLE_H

#include <QObject>


/**
    Interface for console functionality
*/
class c2bConsole : public QObject
{

    Q_OBJECT

public:
    explicit c2bConsole(QObject* parento = 0);
    ~c2bConsole();

    void load();


private:
    int cl_cb2bib_information();
    int cl_cb2bib_tests();
    int cl_doc2bib();
    int cl_html_annote();
    int cl_index();
    int cl_txt2bib();


private slots:
    void _process();
};

#endif
