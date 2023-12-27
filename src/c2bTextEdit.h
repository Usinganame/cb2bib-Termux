/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BTEXTEDIT_H
#define C2BTEXTEDIT_H

#include <QPlainTextEdit>


class c2bSettings;


class c2bTextEdit : public QPlainTextEdit
{

    Q_OBJECT

public:
    explicit c2bTextEdit(QWidget* parentw = 0);
    ~c2bTextEdit();

    QAction* convertSelection2LaTeXAction;
    QAction* convertSelection2UnicodeAction;
    QAction* journalsToAbbreviatedAction;
    QAction* journalsToAlternateAbbreviatedAction;
    QAction* journalsToAlternateFullAction;
    QAction* journalsToFullAction;
    QAction* pasteCurrentBibTeXAction;
    QAction* toggleWordWrappingAction;
    QAction* updateMetadataAction;
    void cursorPosition(int* line_number, int* line_position) const;
    void setBibTeXActions();
    void setLaTeXActions();
    void updatePlainText(const QString& text);

    inline const QString editorFilename() const
    {
        return _editor_filename;
    }

    void setEditorFilename(const QString& fn)
    {
        _editor_filename = fn;
    }


signals:
    void overwriteModeChanged();


public slots:
    void toggleWordWrapping();


protected slots:
    void convert2LaTeX();
    void convert2Unicode();


protected:
    void contextMenuEvent(QContextMenuEvent* qevent);
    void keyPressEvent(QKeyEvent* qevent);
    void resizeEvent(QResizeEvent* qevent);


private:
    QColor _line_number_area_color;
    QColor* _line_number_color_p;
    QString _editor_filename;
    QWidget* _line_number_area;
    c2bSettings* _settingsP;
    int lineNumberAreaWidth();
    void lineNumberAreaPaintEvent(QPaintEvent* qevent);


private slots:
    void loadSettings();
    void updateLineNumberAreaWidth();
    void updateLineNumberArea(const QRect& qrect, int dy);


    friend class LineNumberArea;
};


/***************************************************************************
 *  Line number area (From CodeEditor Qt's example)
 ***************************************************************************/
class LineNumberArea : public QWidget
{

public:
    explicit LineNumberArea(c2bTextEdit* editor) : QWidget(editor)
    {
        _editor = editor;
    }
    ~LineNumberArea() {}

    QSize sizeHint() const
    {
        return QSize(_editor->lineNumberAreaWidth(), 0);
    }


protected:
    void paintEvent(QPaintEvent* qevent)
    {
        _editor->lineNumberAreaPaintEvent(qevent);
    }


private:
    c2bTextEdit* _editor;
};

#endif
