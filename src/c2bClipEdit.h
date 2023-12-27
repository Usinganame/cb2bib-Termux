/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BCLIPEDIT_H
#define C2BCLIPEDIT_H

#include <QPlainTextEdit>


/**
    @author Pere Constans
*/
class c2bClipEdit : public QPlainTextEdit
{

    Q_OBJECT

public:
    enum Mode
    {
        Editor,
        Browser
    };

    explicit c2bClipEdit(const Mode mode, QWidget* parentw = 0);
    ~c2bClipEdit();

    void setText(const QString& text, const QString& tagged_text = QString());
    void setTaggedViewMode(bool tagged_view);
    void insertTag(const QString& tag);
    void updatePlainText(const QString& text);


signals:
    void userEndedSelection(const QPoint& position);


protected:
    virtual void contextMenuEvent(QContextMenuEvent* qevent);
    virtual void keyPressEvent(QKeyEvent* qevent);
    virtual void keyReleaseEvent(QKeyEvent* qevent);
    virtual void mouseReleaseEvent(QMouseEvent* qevent);


private slots:
    virtual void selectionHasChanged();


private:
    QString _tagged_text;
    QString _text;
    bool _has_selecting_ended;
    bool _is_tagged_view;
};

#endif
