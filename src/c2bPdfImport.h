/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BPDFIMPORT_H
#define C2BPDFIMPORT_H

#include "ui_c2bPdfImport.h"
#include <QDialog>


class c2bSettings;

class c2bPdfImport : public QDialog
{

    Q_OBJECT

public:
    explicit c2bPdfImport(QWidget* parentw = 0);
    ~c2bPdfImport();

    QString processedFile;


public slots:
    void processNext();
    void referenceExtacted(bool status);
    void show();
    void showMessage(const QString& ms);


signals:
    void fileProcessed(const QString& filename);
    void saveReferenceRequest();
    void setClipboardDisabled(bool disable);
    void textProcessed(const QString& text);


protected:
    bool event(QEvent* qevent);
    void dragEnterEvent(QDragEnterEvent* qevent);
    void dropEvent(QDropEvent* qevent);


private slots:
    void abort();
    void help();
    void loadSettings();
    void processOneFile();
    void saveSettings();
    void selectFiles();


private:
    QPushButton* buttonProcess;
    QPushButton* buttonSelectFiles;
    Ui::c2bPdfImport ui;
    bool c2bAutomaticQuery;
    bool m_aborted;
    c2bSettings* settings;
    void processDocument();
};

#endif
