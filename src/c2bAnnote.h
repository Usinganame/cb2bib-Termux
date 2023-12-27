/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#ifndef C2BANNOTE_H
#define C2BANNOTE_H

#include <QMainWindow>


class c2bFileSystemWatcher;
class c2bSettings;
class c2bWebBrowser;
class texToHtml;

class c2bAnnote : public QMainWindow
{

    Q_OBJECT

public:
    explicit c2bAnnote(QWidget* parentw = 0);
    ~c2bAnnote();

    bool show();


private:
    QString _annote_filename;
    QString _html_filename;
    c2bFileSystemWatcher* _fsw;
    c2bSettings* _settingsP;
    c2bWebBrowser* _view_port;
    texToHtml* _t2h;


private slots:
    void annote();
    void configure();
    void edit();
    void help();
    void loadSettings();
    void setWindowTitle(const QString& title);
    void showMessage(const QString& ms);
    void update();
};

#endif
