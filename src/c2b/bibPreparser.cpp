/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "bibPreparser.h"

#include "cb2bib_utilities.h"
#include "settings.h"

#include <QProcess>


bibPreparser::bibPreparser(QObject* parento) : QObject(parento)
{
    settings* settingsP = settings::instance();
    m_inp_file = settingsP->tempPath() + "/cb2bib_clipborad_inp.tmp_" + settingsP->applicationPid();
    m_out_file = settingsP->tempPath() + "/cb2bib_clipborad_out.tmp_" + settingsP->applicationPid();
}


void bibPreparser::preparse(const QString& text, QString* out_text)
{
    out_text->clear();
    if (!c2bUtils::stringToFile(text + '\n', m_inp_file))
    {
        emit statusMessage(tr("Unable to open the file %1 for writing.").arg(m_inp_file));
        return;
    }

    // External preparsing
    QStringList arguments;
    arguments.append(m_inp_file);
    arguments.append(m_out_file);
    QProcess preparser;
    preparser.start(settings::instance()->fileName("cb2Bib/PreparserBin"), arguments);
    if (!preparser.waitForFinished(2000))
    {
        preparser.kill();
        QFile ifile(m_inp_file);
        ifile.remove();
        QFile ofile(m_out_file);
        ofile.remove();
        emit statusMessage(tr("Failed to call %1.").arg(settings::instance()->fileName("cb2Bib/PreparserBin")));
        return;
    }

    QFile ifile(m_inp_file);
    ifile.remove();
    (*out_text) = c2bUtils::fileToString(m_out_file, true);
    if (out_text->isEmpty())
    {
        emit statusMessage(tr("External Parsing ended. Input string remains unchanged."));
        (*out_text) = text;
    }
    else
        emit statusMessage(tr("External Parsing ended."));
    if (settings::instance()->value("cb2Bib/PreparserShowLog").toBool())
    {
        QString log_string(QString::fromUtf8(preparser.readAllStandardOutput()) + '\n');
        log_string += QString::fromUtf8(preparser.readAllStandardError()) + '\n';
        log_string += QString("Input[\n%1\n]\n").arg(text);
        log_string += QString("Output[\n%1\n]\n").arg(*out_text);
        emit preparserLogAvailable(log_string);
    }
}
