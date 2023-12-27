/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BEXPORTDIALOG_H
#define C2BEXPORTDIALOG_H

#include "c2bExport.h"

#include "ui_c2bExportDialog.h"

#include <QDialog>


class c2bSettings;

class c2bExportDialog : public QDialog
{

    Q_OBJECT

public:
    c2bExportDialog(const QString& fn, const QString& contents, const QStringList& keys, QWidget* parentw = 0);
    ~c2bExportDialog();

    inline const QString exportFilename() const
    {
        return ui.ExportFile->text();
    }


private:
    Ui::c2bExportDialog ui;
    c2bExport::export_data _ed;
    c2bSettings* settings;


private slots:
    void _export();
    void getDocumentsDirectory();
    void getExportFile();
    void help();
};

#endif
