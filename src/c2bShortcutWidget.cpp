/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "c2bShortcutWidget.h"

#include "c2bSettings.h"


c2bShortcutWidget::c2bShortcutWidget(QWidget* parentw) : QWidget(parentw)
{
    ui.setupUi(this);
    _settingsP = c2bSettingsP;
    _standard_keysequences.append(QKeySequence::Close);
    _standard_keysequences.append(QKeySequence::Copy);
    _standard_keysequences.append(QKeySequence::Cut);
    _standard_keysequences.append(QKeySequence::Find);
    _standard_keysequences.append(QKeySequence::FindNext);
    _standard_keysequences.append(QKeySequence::FindPrevious);
    _standard_keysequences.append(QKeySequence::HelpContents);
    _standard_keysequences.append(QKeySequence::Open);
    _standard_keysequences.append(QKeySequence::Paste);
    _standard_keysequences.append(QKeySequence::Redo);
    _standard_keysequences.append(QKeySequence::Refresh);
    _standard_keysequences.append(QKeySequence::Save);
    _standard_keysequences.append(QKeySequence::SelectAll);
    _standard_keysequences.append(QKeySequence::Undo);
    _standard_keysequences.append(QKeySequence::ZoomIn);
    _standard_keysequences.append(QKeySequence::ZoomOut);
    _standard_keysequences.append(Qt::Key_F2);
    _standard_keysequences.append(QKeySequence::Quit);
    _standard_keysequences.append(QKeySequence::SaveAs);

    connect(ui.Clear, SIGNAL(clicked()), ui.Shortcut, SLOT(clear()));
    connect(ui.Reset, SIGNAL(clicked()), ui.Shortcut, SLOT(reset()));
}


void c2bShortcutWidget::setShortcutNames(const QString& path, const QStringList& fullnames)
{
    disconnect(ui.Shortcut, SIGNAL(shortcutChanged(QKeySequence,QKeySequence)), this,
               SLOT(shortcutChanged(QKeySequence,QKeySequence)));
    disconnect(ui.Description, SIGNAL(currentIndexChanged(QString)), this, SLOT(currentIndexChanged(QString)));
    _modified_keysequences.clear();

    _shortcut_path = path;
    _fullnames = fullnames.filter(path);
    const int n(_fullnames.count());
    const int p(path.length());
    for (int i = 0; i < n; ++i)
        if (_fullnames.at(i).startsWith(path))
            ui.Description->addItem(_fullnames.at(i).mid(p));

    ui.Shortcut->setKeysequence(_settingsP->keysequence(_shortcut_path + ui.Description->currentText()));
    ui.Shortcut->setDefaultKeysequence(_settingsP->defaultKeysequence(_shortcut_path + ui.Description->currentText()));

    connect(ui.Shortcut, SIGNAL(shortcutChanged(QKeySequence,QKeySequence)), this,
            SLOT(shortcutChanged(QKeySequence,QKeySequence)));
    connect(ui.Description, SIGNAL(currentIndexChanged(QString)), this, SLOT(currentIndexChanged(QString)));
}

void c2bShortcutWidget::currentIndexChanged(const QString& name)
{
    const QString fullname(_shortcut_path + name);
    if (_modified_keysequences.contains(fullname))
        ui.Shortcut->setKeysequence(_modified_keysequences.value(fullname));
    else
        ui.Shortcut->setKeysequence(_settingsP->keysequence(fullname));
    ui.Shortcut->setDefaultKeysequence(_settingsP->defaultKeysequence(fullname));
}

void c2bShortcutWidget::shortcutChanged(const QKeySequence& oldks, const QKeySequence& newks)
{
    const QString fullname(_shortcut_path + ui.Description->currentText());
    if (!newks.isEmpty())
    {
        if (_standard_keysequences.contains(newks))
        {
            ui.Shortcut->setKeysequence(oldks);
            ui.Shortcut->setChecked(true);
            emit statusMessage(
                tr("Key sequence %1 is used by standard shortcuts").arg(newks.toString(QKeySequence::NativeText)));
            return;
        }
        if (_modified_keysequences.size() == 0)
        {
            const int n(_fullnames.count());
            for (int i = 0; i < n; ++i)
                _modified_keysequences.insert(_fullnames.at(i), _settingsP->keysequence(_fullnames.at(i)));
        }
        if (_modified_keysequences.values().contains(newks) && _modified_keysequences.value(fullname) != newks)
        {
            ui.Shortcut->setKeysequence(oldks);
            ui.Shortcut->setChecked(true);
            emit statusMessage(tr("Key sequence %1 is already assigned").arg(newks.toString(QKeySequence::NativeText)));
            return;
        }
    }
    _modified_keysequences[fullname] = newks;
    emit statusMessage(QString());
}
