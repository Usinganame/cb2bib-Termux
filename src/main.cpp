/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "qtsingleapplication/src/qtsingleapplication.h"
#include "qtsingleapplication/src/qtsinglecoreapplication.h"

#include "c2bConfigure.h"
#include "c2bConsole.h"
#include "c2bSettings.h"
#include "cb2Bib.h"

#ifdef C2B_USE_QWEB
#include "c2bAnnote.h"
#endif


int main(int argc, char* argv[])
{
    Q_INIT_RESOURCE(cb2bib);
    Q_INIT_RESOURCE(c2blib);

    c2bSettings* c2b_settings; // Delete before app, this avoids QVariant::save: unable to save type 67/64
    int code(0);

    if (c2bSettings::isConsoleMode(argc, argv))
    {
        // Cannot use QCoreApplication, QTextDocument is required by c2bUtils::fromHtmlString
        // Needs also workaround c2bSettings::decodeFilename()
        QApplication app(argc, argv);
        app.setOrganizationName(C2B_ORGANIZATION);
        app.setApplicationName(C2B_APPLICATION);
        c2b_settings = c2bSettings::initSettings();
        if (c2b_settings->loaded())
        {
            c2bConsole c2B;
            c2B.load();
            code = app.exec();
        }
        delete c2b_settings;
    }
    else if (c2bSettings::isSingleApplicationMode(argc, argv))
    {
        // Avoid connecting to the graphic server. On Windows it would create a void window.
        {
            QtSingleCoreApplication* capp = new QtSingleCoreApplication(argc, argv);
            const bool is_running = capp->sendMessage(QString());
            delete capp;
            if (is_running)
                return code;
        }
        QtSingleApplication app(argc, argv);
        if (app.isRunning()) // Activate local peer
            return code;
        app.setQuitOnLastWindowClosed(false);
        app.setOrganizationName(C2B_ORGANIZATION);
        app.setApplicationName(C2B_APPLICATION);
        app.setWindowIcon(QIcon(":/icons/icons/cb2bib.ico"));
        c2b_settings = c2bSettings::initSettings();
        if (c2b_settings->loaded())
        {
            cb2Bib c2B;
            c2B.show();
            QObject::connect(&app, SIGNAL(messageReceived(QString)), &c2B, SLOT(show()));
            code = app.exec();
        }
        delete c2b_settings;
    }
    else
    {
        QApplication app(argc, argv);
        app.setOrganizationName(C2B_ORGANIZATION);
        app.setApplicationName(C2B_APPLICATION);
        app.setWindowIcon(QIcon(":/icons/icons/cb2bib.ico"));
        c2b_settings = c2bSettings::initSettings();
        if (c2b_settings->loaded())
        {
            if (c2b_settings->cl_cb2bib_import_mode)
                code = app.exec();
            else if (c2b_settings->cl_configure)
            {
                c2bConfigure c2B;
                c2B.show();
                code = app.exec();
            }
            else if (c2b_settings->cl_view_annote)
            {
#ifdef C2B_USE_QWEB
                c2bAnnote c2B;
                if (c2B.show())
                    code = app.exec();
#else
                fprintf(stdout, "cb2Bib Annote is disabled. Recompile using QtWebKit or QtWebEngine library.\n");
#endif
            }
            else
            {
                cb2Bib c2B;
                c2B.show();
                code = app.exec();
            }
        }
        delete c2b_settings;
    }

    return code;
}
