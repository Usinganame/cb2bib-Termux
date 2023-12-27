/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BCITERWIDGET_H
#define C2BCITERWIDGET_H

#include "ui_c2bCiterWidget.h"

#include <QSystemTrayIcon>


class QLabel;
class c2bCiterModel;
class c2bCoreCiter;
class c2bSettings;


class c2bCiterWidget : public QWidget
{

    Q_OBJECT

public:
    explicit c2bCiterWidget(QWidget* parentw = 0);
    ~c2bCiterWidget();


public:
    void load();
    void setTrayIcon();


public slots:
    void show();
    void toggleVisible();


signals:
    void openAnnote();
    void openFile(const QString& fn);


private:
    QString _status_label;
    QStringList _bibtex_files;
    QSystemTrayIcon* _tray_icon;
    Ui::c2bCiterWidget ui;
    bool _clipboard_connected;
    c2bCiterModel* _citations;
    c2bCoreCiter* _citerP;
    c2bSettings* _settingsP;
    void reload(const c2bCiter::State& state);
    void setActions();


private slots:
    void citeReferences();
    void doSearchInFiles();
    void editReference();
    void filterDataChanged(const QString& filter);
    void help();
    void indexDocuments();
    void openDirectory();
    void openFile();
    void openFiles();
    void openUrl();
    void reload();
    void showLabel();
    void showLabel(const QString& label);
    void showMessage(const QString& message);
    void toggleCb2Bib();
    void toggleClipboard();
    void toggleFullScreen();
    void trayIconActivated(QSystemTrayIcon::ActivationReason r);
    void updatePatternFilter(const bool mode, const QString& pattern);
};

#endif
