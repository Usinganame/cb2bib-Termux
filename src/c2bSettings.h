/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BSETTINGS_H
#define C2BSETTINGS_H

#include "c2bColors.h"

#include <settings.h>

#include <QFont>
#include <QKeySequence>

class QAction;
class QProgressBar;
class QShortcut;


class c2bSettings : public settings
{

    Q_OBJECT

public:
    ~c2bSettings();

    QFont c2bMonoFont;
    c2bColors colors;
    void notify();
    void update();
    static c2bSettings* initSettings();

    void setKeysequence(const QString& fullname, QShortcut* shortcut);
    void setKeysequence(const QString& path, QAction* action);
    void setKeysequences(const QHash<QString, QKeySequence>& keysequences);
    inline QKeySequence keysequence(const QString& fullname) const
    {
        return value(fullname).value<QKeySequence>();
    }
    inline QKeySequence defaultKeysequence(const QString& fullname) const
    {
        return _default_keysequences.value(fullname);
    }
    inline QByteArray ksname(const QString& fullname) const
    {
        return value(fullname).value<QKeySequence>().toString(QKeySequence::NativeText).toLatin1();
    }
    inline QStringList shortcutNames() const
    {
        return _default_keysequences.keys();
    }


signals:
    void newSettings();


private:
    c2bSettings(const QString& organization, const QString& application, QObject* parento = 0);
    explicit c2bSettings(const QString& fn, QObject* parento = 0);

    QMap<QString, QKeySequence> _default_keysequences;
    QProgressBar* _progress_bar;
    void init();
    void processReferenceFile();
    void setDefaults();
#ifdef Q_OS_WIN
    QString decodeFilename(const QString& fn) const override;
#endif


private slots:
    void guiExits();
    void processReferenceFileEvent();
};

#define c2bSettingsP (static_cast<c2bSettings*>(settings::instance()))

#endif
