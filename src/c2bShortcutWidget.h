/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BSHORTCUTWIDGET_H
#define C2BSHORTCUTWIDGET_H

#include "ui_c2bShortcutWidget.h"


#include <QHash>
#include <QWidget>


class c2bSettings;


class c2bShortcutWidget : public QWidget
{

    Q_OBJECT

public:
    explicit c2bShortcutWidget(QWidget* parentw = 0);
    inline ~c2bShortcutWidget() {}

    void setShortcutNames(const QString& path, const QStringList& fullnames);
    inline const QHash<QString, QKeySequence>& modifiedKeysequences() const
    {
        return _modified_keysequences;
    }


signals:
    void statusMessage(const QString& ms);


private slots:
    void currentIndexChanged(const QString& name);
    void shortcutChanged(const QKeySequence& oldks, const QKeySequence& newks);


private:
    QHash<QString, QKeySequence> _modified_keysequences;
    QList<QKeySequence> _standard_keysequences;
    QString _shortcut_path;
    QStringList _fullnames;
    Ui::c2bShortcutWidget ui;
    c2bSettings* _settingsP;
};

#endif
