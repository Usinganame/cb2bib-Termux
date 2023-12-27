/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef BIBPREPARSER_H
#define BIBPREPARSER_H

#include <QObject>


/**
    This class handles external processing of bibliographic items. It's
    formally an extension of the bibParser.
*/
class bibPreparser : public QObject
{

    Q_OBJECT

public:
    explicit bibPreparser(QObject* parento = 0);
    inline ~bibPreparser() {}

    void preparse(const QString& text, QString* out_text);


signals:
    void preparserLogAvailable(const QString& log);
    void statusMessage(const QString& ms);


private:
    QString m_inp_file;
    QString m_out_file;
};

#endif
