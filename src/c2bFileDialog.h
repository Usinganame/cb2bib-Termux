/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BFILEDIALOG_H
#define C2BFILEDIALOG_H

#include <QFileDialog>

class c2bSettings;


class c2bFileDialog : public QFileDialog
{

    Q_OBJECT

public:
    static QString getFilename(QWidget* parentw = 0, const QString& caption = QString(),
                               const QString& path = QString(), const QString& filter = QString());
    static QString getOpenFilename(QWidget* parentw = 0, const QString& caption = QString(),
                                   const QString& path = QString(), const QString& filter = QString());
    static QStringList getOpenFilenames(QWidget* parentw = 0, const QString& caption = QString(),
                                        const QString& path = QString(), const QString& filter = QString());
    static QString getSaveFilename(QWidget* parentw = 0, const QString& caption = QString(),
                                   const QString& path = QString(), const QString& filter = QString());
    static QString getExistingDirectory(QWidget* parentw = 0, const QString& caption = QString(),
                                        const QString& path = QString());
    static QString getSystemFilename(QWidget* parentw = 0, const QString& caption = QString(),
                                     const QString& path = QString(), const QString& filter = QString());


private:
    c2bFileDialog(QWidget* parentw, const QString& caption, const QString& fpath, const QString& ffilter);
    ~c2bFileDialog();

    QString _current_file;
    QString fileName(const QString& path);
    c2bSettings* settings;

    static QString _caption(const QString& generic, const QString& caption);
    static QString _dirpath(const QString& path);
    static QString _filename(const QString& path);
    static QString _path(const QString& path);
    void readSettings();
    void writeSettings();


private slots:
    void accept();
    void selectCurrentFile();
};

#endif
