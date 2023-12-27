/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 *
 *   The LyX pipe procedure in citeToLyXPipe has been adapted from Tellico
 *   (Tellico (C) 2003-2005 by Robby Stephenson)
 ***************************************************************************/
#include "c2bCoreCiter.h"

#include "c2bFileDialog.h"

#include <settings.h>

#include <QApplication>
#include <QClipboard>
#include <QMessageBox>
#include <QTextStream>

// fifo to lyx
#include <fcntl.h>

#include <unistd.h>


c2bCoreCiter::c2bCoreCiter(QWidget* parentw) : QObject(parentw)
{
    _parentWP = parentw;
    _settingsP = settings::instance();
    _settingsP->setDefaultValue("c2bCoreCiter/LyXPipe",
                                QDir::cleanPath(QDir::homePath() + QDir::separator() + ".lyx/lyxpipe.in"));
    _lyxpipe = _settingsP->value("c2bCoreCiter/LyXPipe").toString();

    _citeids = QRegExp("^([^<]*)<<([^\\|]*)\\|citeids\\|([^>]*)>>(.*)$");
}

c2bCoreCiter::~c2bCoreCiter() {}


void c2bCoreCiter::cite(const QStringList& keys)
{
    if (keys.count() == 0)
        return;

    _command = _settingsP->value("cb2Bib/CiteCommandPattern").toString();
    const QByteArray pipe(QFile::encodeName(_lyxpipe));
    if (QFile::exists(pipe) && _command == C2B_CITE_COMMAND_PATTERN)
        _cite_to_lyx_pipe(keys);
    else
        _cite_to_clipboard(keys);
}

void c2bCoreCiter::_cite_to_clipboard(const QStringList& keys) const
{
    QString c;
    if (_command.isEmpty() || _command == C2B_CITE_COMMAND_PATTERN)
        c = QLatin1String("\\cite{") + keys.join(QLatin1String(", ")).trimmed() + QLatin1Char('}');
    else if (_command.contains(QLatin1String("<<citeid>>")))
        for (int i = 0; i < keys.count(); ++i)
            c += QString(_command).replace(QLatin1String("<<citeid>>"), keys.at(i)) + QLatin1Char(' ');
    else if (_citeids.indexIn(_command) >= 0)
    {
        c = _citeids.cap(2) + keys.at(0); // Note keys.count() > 0
        for (int i = 1; i < keys.count(); ++i)
            c += _citeids.cap(3) + QLatin1Char(' ') + _citeids.cap(2) + keys.at(i);
        c = _citeids.cap(1) + c.trimmed() + _citeids.cap(4);
    }

    if (c.isEmpty())
    {
        QMessageBox::warning(_parentWP, tr("Warning - cb2Bib"), tr("Cite Command Pattern is misspecified"),
                             QMessageBox::Ok);
        return;
    }

    QClipboard* cb(QApplication::clipboard());
    cb->setText(c.trimmed(), QClipboard::Clipboard);
}

void c2bCoreCiter::_cite_to_lyx_pipe(const QStringList& keys) const
{
    // This procedure was adapted from Tellico
    // Tellico (C) 2003-2005 by Robby Stephenson
    const QByteArray pipe(QFile::encodeName(_lyxpipe));
    const QString errorStr(tr("Unable to write to the server pipe at '%1'.").arg(QString(pipe)));

    if (!QFile::exists(pipe))
    {
        QMessageBox::warning(_parentWP, tr("Warning - cb2Bib"), errorStr, QMessageBox::Ok);
        return;
    }

    int pipeFd = ::open(pipe, O_WRONLY);
    QFile file(QString::fromUtf8(pipe));
    if (file.open(pipeFd, QIODevice::WriteOnly))
    {
        // pybliographer uses comma-space, and pyblink expects the space there
        const QString c(keys.join(", ").trimmed());
        QTextStream st(&file);
        st << QString::fromLatin1("LYXCMD:cb2bib:citation-insert:%1\n").arg(c).toLatin1();
        file.flush();
        file.close();
    }
    else
        QMessageBox::warning(_parentWP, tr("Warning - cb2Bib"), errorStr, QMessageBox::Ok);
    ::close(pipeFd);
}

void c2bCoreCiter::setLyXPipe()
{
    const QString new_pn(c2bFileDialog::getSystemFilename(_parentWP, "Select LyX pipe", _lyxpipe, "All (*)"));
    if (!new_pn.isEmpty())
    {
        _lyxpipe = new_pn;
        _settingsP->setValue("c2bCoreCiter/LyXPipe", _lyxpipe);
    }
}
