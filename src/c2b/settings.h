/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef SETTINGS_H
#define SETTINGS_H

#include "cb2bib_parameters.h"

#include <QDir>
#include <QSettings>
#include <QStringList>

class QCoreApplication;


class settings : public QSettings
{

    Q_OBJECT

public:
    explicit settings(QObject* parento = 0);
    virtual ~settings();

    // Command line data. (Set public for easiest access. Only settings or derived classes should modify it)
    QString cl_annote_filename;
    QString cl_extract_output_filename;
    QString cl_import_filename;
    QString cl_index_dirname;
    QStringList cl_bibedit_filenames;
    QStringList cl_citer_filenames;
    QStringList cl_extract_input_filenames;
    bool cl_bibedit;
    bool cl_cb2bib_import_mode;
    bool cl_cb2bib_information;
    bool cl_cb2bib_mode;
    bool cl_cb2bib_tests;
    bool cl_citer;
    bool cl_configure;
    bool cl_console_mode;
    bool cl_doc2bib;
    bool cl_html_annote;
    bool cl_import;
    bool cl_index;
    bool cl_sloppy;
    bool cl_txt2bib;
    bool cl_user_configured;
    bool cl_view_annote;

    // Get/Set filenames according to settings
    // PdfDirectory is a particular case. If relative, it is relative to the BibTeX file
    inline QString fileName(const QString& key) const
    {
        if (_is_usb_configured_mode)
        {
            const QString v(value(key).toString());
            if (key == "cb2Bib/PdfDirectory")
                if (value("cb2Bib/RelativePdfDirectory").toBool())
                    return QDir::toNativeSeparators(QDir::cleanPath(v));
            if (key.endsWith("Bin")) // Pathless binary to be found on PATH
                if (!(v.contains('/') || v.contains('\\')))
                    return v;
            return QDir::toNativeSeparators(QDir::cleanPath(_c2bAppDir.absoluteFilePath(v)));
        }
        else
            return QDir::toNativeSeparators(QDir::cleanPath(value(key).toString()));
    }
    inline void setFilename(const QString& key, const QString& fn)
    {
        if (_is_usb_configured_mode)
        {
            if (key == "cb2Bib/PdfDirectory")
            {
                if (value("cb2Bib/RelativePdfDirectory").toBool())
                {
                    setValue(key, fn);
                    return;
                }
            }
            setValue(key, _c2bAppDir.relativeFilePath(fn));
        }
        else
            setValue(key, fn);
    }

    inline bool loaded() const
    {
        return _is_loaded;
    }
    inline bool isUsbConfiguredMode() const
    {
        return _is_usb_configured_mode;
    }
    inline QStringList confCommandFlags() const
    {
        return _conf_command_flags;
    }
    inline QString tempPath() const
    {
        return _tmp_dir_path;
    }
    inline QString applicationPid() const
    {
        return _application_pid;
    }
    void setDefaultValue(const QString& key, const QVariant& defaulValue);
    QString applicationDataDir() const;

    static bool isConsoleMode(const int argc, char** argv);
    static bool isSingleApplicationMode(const int argc, char** argv);
    static settings* instance()
    {
        Q_ASSERT_X(_c2b_global_settings, "settings", "settings was not instantiated");
        return _c2b_global_settings;
    }


protected:
    settings(const QString& organization, const QString& application, QObject* parento = 0);
    explicit settings(const QString& fn, QObject* parento = 0);
    // init() has a virtual method, keep it out of the constructor
    void init(bool command_line = true);

    static bool isConfiguredMode();
    static const QString configuredFilename();
    virtual QString decodeFilename(const QString& fn) const;


private:
    QCoreApplication* _c2bApp;
    QDir _c2bAppDir;
    QString _application_pid;
    QString _tmp_dir_path;
    QStringList _conf_command_flags;
    bool _is_loaded;
    bool _is_usb_configured_mode;
    static settings* _c2b_global_settings;
    void _init();
    void checkCommand(bool* action, int* actions);
    void printUsage();
    void readCommandLine();
    void setDefaults();
};

#endif
