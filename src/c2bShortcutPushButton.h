/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BSHORTCUTPUSHBUTTON_H
#define C2BSHORTCUTPUSHBUTTON_H

#include <QPushButton>


class c2bShortcutPushButton : public QPushButton
{

    Q_OBJECT

public:
    explicit inline c2bShortcutPushButton(QWidget* parentw = 0) : QPushButton(parentw) {}
    inline ~c2bShortcutPushButton() {}

    void setKeysequence(const QKeySequence& ks);
    void setDefaultKeysequence(const QKeySequence& ks)
    {
        _default_keysequence = ks;
    }
    inline QKeySequence keysequence() const
    {
        return _keysequence;
    }


signals:
    void shortcutChanged(const QKeySequence& oldks, const QKeySequence& newks);


public slots:
    void clear();
    void reset();


protected:
    virtual void keyPressEvent(QKeyEvent* qevent);


private:
    inline void _set_keysequence(const QKeySequence& ks)
    {
        const QKeySequence oldks(_keysequence);
        setKeysequence(ks);
        emit shortcutChanged(oldks, ks);
    }

    QKeySequence _default_keysequence;
    QKeySequence _keysequence;
};

#endif
