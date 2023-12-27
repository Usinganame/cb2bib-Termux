/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bNetworkQueryInfo.h"

#include "c2b.h"
#include "c2bBibParser.h"
#include "c2bFileSystemWatcher.h"
#include "c2bSettings.h"
#include "c2bUtils.h"

#include <QAction>
#include <QTextStream>
#include <QUrl>


c2bNetworkQueryInfo::c2bNetworkQueryInfo(QObject* parento) : QObject(parento)
{
    _bpP = c2b::instance()->bibParser();
    connect(c2bSettingsP, SIGNAL(newSettings()), this, SLOT(loadSettings()));
    _fsw = new c2bFileSystemWatcher(this);
    connect(_fsw, SIGNAL(fileChanged(QString)), this, SLOT(parseBookmarks()));
    loadSettings();
}

c2bNetworkQueryInfo::~c2bNetworkQueryInfo() {}


void c2bNetworkQueryInfo::loadSettings()
{
    const QString nfn(c2bSettingsP->fileName("cb2Bib/NetworkFile"));
    if (nfn == NetworkFile)
        return;
    if (QFileInfo::exists(nfn))
    {
        if (!NetworkFile.isEmpty())
            _fsw->removePath(NetworkFile);
        NetworkFile = nfn;
        _fsw->addPath(NetworkFile);
    }
    parseBookmarks();
}

void c2bNetworkQueryInfo::parseBookmarks()
{
    BookmarkList.clear();
    if (NetworkFile.isEmpty())
        return;
    QFile file(NetworkFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QRegExp _bookmark("^bookmark=");
    QString line;
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    stream.setAutoDetectUnicode(true);
    while (!stream.atEnd())
    {
        line = stream.readLine();
        if (line.contains(_bookmark))
        {
            line.remove(_bookmark);
            if (line.count('|') == 0)
                c2bUtils::warn(tr("c2bNetworkQueryInfo::parseBookmarks: Syntax error at '%1'").arg(line));
            else
                BookmarkList.append(line);
        }
    }
    file.close();
    while (!BookmarkActionList.isEmpty())
        delete BookmarkActionList.takeFirst();
    const QRegExp rx("<<.+>>");
    for (int i = 0; i < BookmarkList.count(); ++i)
        if (BookmarkList.at(i).contains(rx))
        {
            const QStringList bm_parts(BookmarkList.at(i).split('|'));
            if (bm_parts.count() > 1)
            {
                QAction* act = new QAction(bm_parts.at(0), this);
                act->setData(bm_parts.at(1));
                act->setStatusTip(QString("%1  [%2]").arg(bm_parts.at(0), bm_parts.at(1)));
                connect(act, SIGNAL(triggered()), this, SLOT(openBookmark()));
                BookmarkActionList.append(act);
            }
        }
}

QList<QAction*> c2bNetworkQueryInfo::bookmarkActions(const QString& selection)
{
    _current_selection = selection;
    for (int i = 0; i < BookmarkActionList.count(); ++i)
        BookmarkActionList[i]->setVisible(false);
    const QRegExp rx("<<.+>>");
    for (int i = 0; i < BookmarkActionList.count(); ++i)
    {
        QString bmd(BookmarkActionList.at(i)->data().toString());
        const QStringList& bibliographicFields = _bpP->bibliographicFields();
        for (int j = 0; j < bibliographicFields.count(); ++j)
        {
            const QString& name = bibliographicFields.at(j);
            const QString tag(QString("<<%1>>").arg(name));
            if (bmd.contains(tag))
                if (!_bpP->field(name).isEmpty())
                    bmd.remove(tag);
        }
        if (bmd.contains("<<selection>>"))
            if (!_current_selection.isEmpty())
                bmd.remove("<<selection>>");
        BookmarkActionList[i]->setVisible(!bmd.contains(rx));
    }
    return BookmarkActionList;
}

void c2bNetworkQueryInfo::openBookmark()
{
    QAction* act = static_cast<QAction*>(sender());
    if (act)
    {
        const QString link(act->data().toString());
        c2bUtils::openFile(encodeLink(link), c2b::mainWidget());
    }
}

const QString c2bNetworkQueryInfo::encodeLink(const QString& ln) const
{
    QString eln(ln);
    // See comment in c2bNetworkQueryInfo::bookmarksToHtml
    eln.replace("[[[", "<<");
    eln.replace("]]]", ">>");
    const QRegExp rx("<<.+>>");
    if (eln.contains(rx))
    {
        const QStringList& bibliographicFields = _bpP->bibliographicFields();
        for (int j = 0; j < bibliographicFields.count(); ++j)
        {
            const QString& name = bibliographicFields.at(j);
            const QString tag(QString("<<%1>>").arg(name));
            if (eln.contains(tag))
            {
                QString fld;
                if (name == "pages")
                    fld = _bpP->field(name).replace(QRegExp("-.+$"), QString());
                else if (name == "author")
                {
                    fld = _bpP->field(name);
                    fld.replace(" and ", " ");
                }
                else if (name == "title")
                {
                    fld = _bpP->field(name);
                    fld = fld.remove('{');
                    fld = fld.remove('}');
                }
                else
                    fld = _bpP->field(name);
                fld = QUrl::toPercentEncoding(fld);
                eln.replace(tag, fld);
                if (!eln.contains(rx))
                    return eln;
            }
        }
        eln.replace("<<selection>>", _current_selection);
    }
    return eln;
}

const QString c2bNetworkQueryInfo::bookmarksToHtml() const
{
    if (BookmarkList.count() == 0)
        return QString();
    QString html("<p align=\"center\">Bookmarks:<br /><p align=\"center\"><em>");
    for (int i = 0; i < BookmarkList.count(); ++i)
    {
        int separator(BookmarkList.at(i).indexOf('|'));
        if (separator == -1)
            continue;
        QString url_name(BookmarkList.at(i).mid(0, separator));
        QString url(BookmarkList.at(i).mid(separator + 1));
        // Tags <<.>> conflict with the Qt > 4.4.x HTML parser, even being them inside a
        // literal, quoted string. The substitution below works as a workaround to prevent
        // cb2Bib tags from clashing with the parser.
        // See c2bNetworkQueryInfo::encodeLink. A similar issue was resolved in
        // fromQtXmlString/toQtXmlString.
        url.replace("<<", "[[[");
        url.replace(">>", "]]]");
        url = "<a href=\"" + url + "\">" + url_name + "</a>";
        html += url + " <br />";
    }
    html += "</em></p><br />";
    return html;
}
