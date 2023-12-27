/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bExport.h"

#include "c2b.h"

#include <cb2bib_parameters.h>


c2bExport::c2bExport(QObject* parento) : QObject(parento) {}

c2bExport::~c2bExport() {}


void c2bExport::exportEntries(const export_data& ed)
{
    // Note. Assume caller performs export_data validity check for files and directories.
    // Prefer replacing filenames to a full BibTeX parsing: This will preserve the
    // original entry and possibly available non cb2Bib tags.
    bibParser* bp = c2b::bibParser();
    QStringList fields;
    if (ed.copy_documents)
        fields.append("file");
    QRegExp filere("\\bfile\\s*=\\s*[\\{\"](.*)[\\}\"]", Qt::CaseInsensitive);
    filere.setMinimal(true);
    QString export_contents("\n\n");
    QString export_log;
    bibReference ref;
    bp->initReferenceParsing(ed.bibtex_fn, fields, &ref);
    while (bp->referencesIn(ed.bibtex_contents, &ref))
    {
        if (!ed.bibtex_keys.contains(ref.citeidName, Qt::CaseSensitive))
            continue;
        if (ed.copy_documents)
        {
            const QString sfn(ref.value("file"));
            if (!sfn.isEmpty())
            {
                const QString dfn(c2bUtils::documentAbsoluteName(ed.relative_dir, ed.export_fn, ed.documents_dir, sfn));
                QFile source(sfn);
                if (!source.copy(dfn))
                    export_log += tr("% Unable to copy file %1 to %2. %3.\n").arg(sfn, dfn, source.errorString());
                if (QFileInfo::exists(dfn))
                {
                    const int pos(filere.indexIn(ref.rawReference, 0));
                    if (pos > -1)
                    {
                        QString line(filere.cap(0));
                        const QString file(filere.cap(1));
                        line.replace(file,
                                     c2bUtils::documentFilename(ed.relative_dir, ed.export_fn, ed.documents_dir, sfn));
                        ref.rawReference.replace(pos, filere.matchedLength(), line);
                    }
                }
            }
        }
        export_contents += ref.rawReference + "\n\n";
    }
    if (!export_log.isEmpty())
        export_contents = "% cb2Bib " + C2B_VERSION + " / Export Error Log\n" + export_log + export_contents;
    if (!c2bUtils::stringToFile(export_contents, ed.export_fn))
        c2bUtils::warn(tr("Unable to write file %1").arg(ed.export_fn));
}
