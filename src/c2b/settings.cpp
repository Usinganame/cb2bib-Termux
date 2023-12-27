/***************************************************************************
 *   Copyright (C) 2004-2021 by Pere Constans
 *   constans@molspaces.com
 *   cb2Bib version 2.0.1. Licensed under the GNU GPL version 3.
 *   See the LICENSE file that comes with this distribution.
 ***************************************************************************/
#include "settings.h"

#include "cb2bib_utilities.h"

#include <QCoreApplication>
#include <QDir>


/**
    Global settings for cb2Bib
*/
settings::settings(const QString& organization, const QString& application, QObject* parento)
    : QSettings(organization, application, parento)
{
    _init();
}

settings::settings(const QString& fn, QObject* parento) : QSettings(fn, QSettings::IniFormat, parento)
{
    _init();
}

settings::settings(QObject* parento) : QSettings(C2B_ORGANIZATION, C2B_APPLICATION, parento)
{
    _init();
    init(false);
}

settings::~settings()
{
    _c2b_global_settings = 0;
}


void settings::init(bool command_line)
{
    if (command_line)
        readCommandLine();
    if (cl_user_configured)
        _is_usb_configured_mode =
            QDir::toNativeSeparators(QDir::cleanPath(QSettings::fileName())) ==
            QDir::toNativeSeparators(QDir::cleanPath(_c2bApp->applicationDirPath() + '/' + "cb2bib.conf"));
    else
        _is_usb_configured_mode = false;
    if (_is_usb_configured_mode)
    {
        _c2bAppDir = QDir(_c2bApp->applicationDirPath());
        _tmp_dir_path = _c2bApp->applicationDirPath();
    }
    else
    {
        // Use user's home as tmp_dir since tmp files are more accessible if they are needed,
        // for instance, for debugging netqinf
        // Using cb2bib remotely causes tmp_dir not being writable, fallback to machine's tmp
        const QFileInfo hpi(QDir::homePath());
        if (hpi.exists() && hpi.isWritable())
            _tmp_dir_path = QDir::homePath();
        else
            _tmp_dir_path = QDir::tempPath();
    }
    setDefaults();
    // Set relative to BibTeX file in USB mode, overriding defaults.
    if (_is_usb_configured_mode)
        setValue("cb2Bib/RelativePdfDirectory", true);
}

void settings::_init()
{
    _c2bApp = QCoreApplication::instance();
    Q_ASSERT_X(_c2bApp, "settings", "application was not instantiated");
    Q_ASSERT_X(!_c2b_global_settings, "settings", "settings already instantiated");
    settings::_c2b_global_settings = this;
    _application_pid = QString::number(_c2bApp->applicationPid());

    _is_loaded = true;
    cl_bibedit = false;
    cl_cb2bib_import_mode = false;
    cl_cb2bib_information = false;
    cl_cb2bib_tests = false;
    cl_citer = false;
    cl_configure = false;
    cl_doc2bib = false;
    cl_html_annote = false;
    cl_import = false;
    cl_index = false;
    cl_sloppy = false;
    cl_txt2bib = false;
    cl_user_configured = false;
    cl_view_annote = false;
}

void settings::setDefaultValue(const QString& key, const QVariant& defaulValue)
{
    // Makes sure a key is initialized
    setValue(key, value(key, defaulValue));
}

void settings::setDefaults()
{
    QHash<QString, QVariant> defaults;
    const QString dsep(QDir::separator());

    // Files
    defaults["cb2Bib/BibTeXFile"] = QDir::cleanPath(QDir::homePath() + dsep + "references.bib");
    defaults["cb2Bib/CacheDirectory"] = QDir::cleanPath(QDir::homePath() + dsep + "PdfDocuments" + dsep + "c2b.tmp");
    defaults["cb2Bib/PdfDirectory"] = QDir::cleanPath(QDir::homePath() + dsep + "PdfDocuments");

#if defined(Q_OS_WIN)
    const QString C2B_APP_DIR(_c2bApp->applicationDirPath() + dsep);
    defaults["c2bAnnote/AnnoteCssFile"] = C2B_APP_DIR + "data\\tex2html.css";
    defaults["c2bAnnote/MathJaxHeaderFile"] = C2B_APP_DIR + "data\\tex2html_mathjax_header.html";
    defaults["c2bBibSearcher/Pdf2TextBin"] = C2B_APP_DIR + "externtools\\xpdf\\pdf2cb.exe";
    defaults["c2bPdfImport/LastFile"] = C2B_APP_DIR + "testPDFImport\\nomeaning1.pdf";
    defaults["c2bPdfImport/Pdf2TextBin"] = C2B_APP_DIR + "externtools\\xpdf\\pdf2cb.exe";
    defaults["cb2Bib/BrowserCssFile"] = C2B_APP_DIR + "data\\references.css";
    defaults["cb2Bib/JournalFile"] = C2B_APP_DIR + "data\\abbreviations.txt";
    defaults["cb2Bib/NetworkFile"] = C2B_APP_DIR + "data\\netqinf.txt";
    defaults["cb2Bib/PosLexiconFile"] = C2B_APP_DIR + "data\\lexicon.pos";
    defaults["cb2Bib/PostprocessBibTeXBin"] = C2B_APP_DIR + C2B_POSTPROCESS_BIBTEX_BIN;
    defaults["cb2Bib/PreparserBin"] = C2B_APP_DIR + "c2btools\\ris2bib.bat";
    defaults["cb2Bib/RegularExpressionFile"] = C2B_APP_DIR + "data\\regexps.txt";
#elif defined(Q_OS_MACOS)
    QString C2B_DATA_DIR_MAC(C2B_DATA_DIR);
    if (QDir(C2B_DATA_DIR + "/data/").exists())
        C2B_DATA_DIR_MAC = QDir::cleanPath(C2B_DATA_DIR + '/');
    else if (QDir(_c2bApp->applicationDirPath() + "/../Resources/data/").exists())
        C2B_DATA_DIR_MAC = QDir::cleanPath(_c2bApp->applicationDirPath() + "/../Resources/");
    defaults["c2bAnnote/AnnoteCssFile"] = QDir::cleanPath(C2B_DATA_DIR_MAC + "/data/tex2html.css");
    defaults["c2bAnnote/MathJaxHeaderFile"] =
        QDir::cleanPath(C2B_DATA_DIR_MAC + "/data/tex2html_local_mathjax_header.html");
    defaults["c2bBibSearcher/Pdf2TextBin"] = QDir::cleanPath(C2B_BIBSEARCHER_PDF2TXT_BIN);
    defaults["c2bPdfImport/LastFile"] = QDir::cleanPath(C2B_DATA_DIR_MAC + "/testPDFImport/nomeaning1.pdf");
    defaults["c2bPdfImport/Pdf2TextBin"] = QDir::cleanPath(C2B_PDFIMPORT_PDF2TXT_BIN);
    defaults["cb2Bib/BrowserCssFile"] = QDir::cleanPath(C2B_DATA_DIR_MAC + "/data/references.css");
    defaults["cb2Bib/ExifToolBin"] = QDir::cleanPath(C2B_METADATAPARSER_EXIFTOOL_BIN);
    defaults["cb2Bib/JournalFile"] = QDir::cleanPath(C2B_DATA_DIR_MAC + "/data/abbreviations.txt");
    defaults["cb2Bib/NetworkFile"] = QDir::cleanPath(C2B_DATA_DIR_MAC + "/data/netqinf.txt");
    defaults["cb2Bib/PosLexiconFile"] = QDir::cleanPath(C2B_DATA_DIR_MAC + dsep + "data/lexicon.pos");
    defaults["cb2Bib/PostprocessBibTeXBin"] = QDir::cleanPath(C2B_DATA_DIR_MAC + C2B_POSTPROCESS_BIBTEX_BIN);
    defaults["cb2Bib/PreparserBin"] = QDir::cleanPath(C2B_DATA_DIR_MAC + "/c2btools/ris2bib");
    defaults["cb2Bib/RegularExpressionFile"] = QDir::cleanPath(C2B_DATA_DIR_MAC + "/data/regexps.txt");
#else // Q_OS_UNIX
    defaults["c2bAnnote/AnnoteCssFile"] = QDir::cleanPath(C2B_DATA_DIR + dsep + "data/tex2html.css");
    defaults["c2bAnnote/MathJaxHeaderFile"] =
        QDir::cleanPath(C2B_DATA_DIR + dsep + "data/tex2html_local_mathjax_header.html");
    defaults["c2bBibSearcher/Pdf2TextBin"] = QDir::cleanPath(C2B_BIBSEARCHER_PDF2TXT_BIN);
    defaults["c2bPdfImport/LastFile"] = QDir::cleanPath(C2B_DATA_DIR + dsep + "testPDFImport/nomeaning1.pdf");
    defaults["c2bPdfImport/Pdf2TextBin"] = QDir::cleanPath(C2B_PDFIMPORT_PDF2TXT_BIN);
    defaults["cb2Bib/BrowserCssFile"] = QDir::cleanPath(C2B_DATA_DIR + dsep + "data/references.css");
    defaults["cb2Bib/ExifToolBin"] = QDir::cleanPath(C2B_METADATAPARSER_EXIFTOOL_BIN);
    defaults["cb2Bib/JournalFile"] = QDir::cleanPath(C2B_DATA_DIR + dsep + "data/abbreviations.txt");
    defaults["cb2Bib/NetworkFile"] = QDir::cleanPath(C2B_DATA_DIR + dsep + "data/netqinf.txt");
    defaults["cb2Bib/PosLexiconFile"] = QDir::cleanPath(C2B_DATA_DIR + dsep + "data/lexicon.pos");
    defaults["cb2Bib/PostprocessBibTeXBin"] = QDir::cleanPath(C2B_DATA_DIR + dsep + C2B_POSTPROCESS_BIBTEX_BIN);
    defaults["cb2Bib/PreparserBin"] = QDir::cleanPath(C2B_DATA_DIR + dsep + "c2btools/ris2bib");
    defaults["cb2Bib/RegularExpressionFile"] = QDir::cleanPath(C2B_DATA_DIR + dsep + "data/regexps.txt");
#endif

    // External file manager
    defaults["cb2Bib/FmClient"] = false;
    defaults["cb2Bib/FmClientCopyArg"] = C2B_FM_CLIENT_COPY_ARG;
    defaults["cb2Bib/FmClientCopyBin"] = QDir::cleanPath(C2B_FM_CLIENT_COPY_BIN);
    defaults["cb2Bib/FmClientMoveArg"] = C2B_FM_CLIENT_MOVE_ARG;
    defaults["cb2Bib/FmClientMoveBin"] = QDir::cleanPath(C2B_FM_CLIENT_MOVE_BIN);

    // Proxy
    defaults["cb2Bib/UseProxy"] = false;
    defaults["cb2Bib/ProxyPort"] = 8080;
    defaults["cb2Bib/ProxyType"] = 0;

    // Postprocess BibTeX
    defaults["cb2Bib/PostprocessBibTeXArg"] = C2B_POSTPROCESS_BIBTEX_ARG;
    defaults["cb2Bib/PostprocessBibTeXExt"] = C2B_POSTPROCESS_BIBTEX_EXT;

    // Misc
    defaults["c2bAnnote/IncludeCSS"] = true;
    defaults["c2bAnnote/UseRelativeLinks"] = false;
    defaults["cb2Bib/AddMetadata"] = true;
    defaults["cb2Bib/AutomaticPdfDownload"] = false;
    defaults["cb2Bib/AutomaticQuery"] = false;
    defaults["cb2Bib/CheckRepeatedOnSave"] = false;
    defaults["cb2Bib/CiteCommandPattern"] = C2B_CITE_COMMAND_PATTERN;
    defaults["cb2Bib/CiteIdPattern"] = C2B_CITE_ID_PATTERN;
    defaults["cb2Bib/ConvertReferenceToLaTeX"] = true;
    defaults["cb2Bib/CopyMovePdf"] = "copy";
    defaults["cb2Bib/DoHeuristicGuess"] = true;
    defaults["cb2Bib/DocumentIdPattern"] = C2B_DOCUMENT_ID_PATTERN;
    defaults["cb2Bib/FindReplaceInput"] = true;
    defaults["cb2Bib/FindReplaceInputList"] = QString(C2B_FIND_REPLACE_LIST).split("^e");
    defaults["cb2Bib/InsertMetadata"] = false;
    defaults["cb2Bib/KeepTmpNQFiles"] = false;
    defaults["cb2Bib/MovePdf"] = false;
    defaults["cb2Bib/PageNumberSeparator"] = " - ";
    defaults["cb2Bib/PostprocessMonth"] = false;
    defaults["cb2Bib/PreAppendMetadata"] = "prepend";
    defaults["cb2Bib/PreparserAutomatic"] = false;
    defaults["cb2Bib/PreparserShowLog"] = true;
    defaults["cb2Bib/RelativePdfDirectory"] = false;
    defaults["cb2Bib/SetJournalsToFullname"] = false;
    defaults["cb2Bib/UseDoubleBraces"] = true;
    defaults["cb2Bib/UseFullNames"] = false;

    // Pdf2Text arguments
    defaults["c2bBibSearcher/Pdf2TextArg"] = "-q";
    defaults["c2bPdfImport/Pdf2TextArg"] = "-q -f 1 -l 1";

    // Construct current settings
    const QStringList keys(defaults.keys());
    for (int i = 0; i < keys.count(); ++i)
        setValue(keys.at(i), value(keys.at(i), defaults.value(keys.at(i))));
}

QString settings::applicationDataDir() const
{
// Base application data dir containing ./data/ ./doc/ ./c2btools/
#if defined(Q_OS_WIN)
    const QString app_data_dir(_c2bApp->applicationDirPath());
#elif defined(Q_OS_MACOS)
    QString app_data_dir(C2B_DATA_DIR);
    if (!QDir(app_data_dir).exists())
        app_data_dir = _c2bApp->applicationDirPath() + "/../Resources/";
#else // Q_OS_UNIX
    const QString app_data_dir(C2B_DATA_DIR);
#endif
    if (QDir(app_data_dir + "/data/").exists())
        return QDir::cleanPath(app_data_dir);
    else
        return QString();
}

settings* settings::_c2b_global_settings = 0;


/***************************************************************************
 *  Command line processing
 ***************************************************************************/

/** \page commandline cb2Bib Command Line


  The complete listing of command line uses follows.


\htmlonly
<pre style="font-size: xx-small;">
 Usage: cb2bib
        cb2bib [action] [filename1 [filename2 ... ]] [--conf [filename.conf]]

 Actions:
        --configure [filename.conf]                        Edit configuration

        --bibedit [filename1.bib [filename2.bib ... ]]     Edit/browse BibTeX files
        --citer [filename1.bib   [filename2.bib ... ]]     Start cb2Bib citer
        --import tmp_reference_filename                    Import reference, usually from ad hoc websites

        --doc2bib fn1.doc [fn2.doc ... ] reference.bib     Extract reference from document file
        --txt2bib fn1.txt [fn2.txt ... ] reference.bib     Extract reference from text file

        --index [bibdirname]                               Extract keywords from document files

        --html-annote filename.tex                         Convert annote file to HTML
        --view-annote filename.tex                         Convert and visualize annote file
        --view-annote filename.tex.html                    Visualize annote file

 Switches:
        --conf [filename.conf]                             Use configuration file
        --sloppy                                           Accept guesses in automatic reference extraction

 Examples:
        cb2bib                                             Start cb2Bib extraction panel
        cb2bib --import tmp_reference_filename             Import reference
        cb2bib --bibedit filename.bib                      Edit BibTeX filename.bib
        cb2bib --conf                                      Start cb2Bib in USB mode
        cb2bib --doc2bib *.pdf references.bib              Extract references from PDF title pages

 Notes:
  -Use switch --conf to particularize specific settings for specific actions.
  -The file cb2bib.conf must be readable and writable. If it does not exist, cb2Bib will create one
   based on predefined defaults.
  -If starting cb2Bib from a removable media, use the command 'cb2bib --conf' without configuration
   filename. Settings will be read from and written to /cb2bib/full/path/cb2bib.conf, being therefore
   independent of the mounting address that the host computer will provide.
  -To import references from a browser select when asked c2bimport, which expands to 'cb2bib --import %f'.
   The browser will provide the temporary reference filename.
  -A number of factors influence the reliability of automatic extractions. Consider writing customized
   regular expressions and network queries, and use metadata when available.

 Important:
  -The commands --doc2bib and --txt2bib do not append the references to the references.bib. They create
   a new file, or silently overwrite it if already exists.

</pre>
\endhtmlonly


 - <b>Note:</b> On Windows use <tt>c2bconsole</tt> instead of <tt>cb2bib</tt>.
 See \ref relnotes130.

 - <b>Note:</b> If using reference extraction command, see \ref
 faq_automatic_extraction.

*/

bool settings::isConsoleMode(const int argc, char** argv)
{
    for (int i = 0; i < argc; ++i)
        if (strcmp(argv[i], "--html-annote") == 0 || strcmp(argv[i], "--doc2bib") == 0 ||
            strcmp(argv[i], "--txt2bib") == 0 || strcmp(argv[i], "--index") == 0 || strcmp(argv[i], "--c2binfo") == 0 ||
            strcmp(argv[i], "--test") == 0)
            return true;
    return false;
}

bool settings::isSingleApplicationMode(const int argc, char** argv)
{
    for (int i = 0; i < argc; ++i)
        if (strcmp(argv[i], "--citer") == 0)
            return true;
    return false;
}

bool settings::isConfiguredMode()
{
    const QCoreApplication* capp = QCoreApplication::instance();
    const QStringList argv(capp->arguments());
    const int argc(argv.count());
    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
            if (argv.at(i) == "--conf")
                return true;
        for (int i = 1; i < argc; ++i)
            if (argv.at(i) == "--configure")
            {
                const int j(i + 1);
                if (j < argc)
                    if (!argv.at(j).startsWith('-'))
                        return true;
                return false;
            }
    }
    return false;
}

const QString settings::configuredFilename()
{
    const QCoreApplication* capp = QCoreApplication::instance();
    QStringList arguments(capp->arguments());
    arguments.removeAll(QString());
    const int argc(arguments.count());
    QString filename;
    for (int i = 1; i < argc - 1; ++i)
        if (arguments.at(i) == "--conf" || arguments.at(i) == "--configure")
        {
            const int j(i + 1);
            if (!arguments.at(j).startsWith('-'))
                filename = QFile::decodeName(arguments.at(j).toLocal8Bit());
            break;
        }
    if (filename.isEmpty())
        filename = capp->applicationDirPath() + QDir::separator() + "cb2bib.conf";
    QFileInfo fi(filename);
    if (fi.isDir())
    {
        c2bUtils::warn(QObject::tr("Error: Could not open %1 configuration file for reading/writing").arg(filename));
        c2bUtils::warn(QObject::tr("Error: Filename is a directory"));
        exit(1);
    }
    QFile file(filename);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        c2bUtils::warn(QObject::tr("Error: Could not open %1 configuration file for reading/writing").arg(filename));
        c2bUtils::warn(QObject::tr("Error: %1.").arg(file.errorString()));
        exit(1);
    }
    return filename;
}

void settings::readCommandLine()
{
    QStringList arguments(_c2bApp->arguments());
    arguments.removeAll(QString());
    int actions(0);
    for (int i = 1; i < arguments.count(); ++i)
        if (arguments.at(i).startsWith('-'))
        {
            // switches
            if (arguments.at(i) == "--conf")
            {
                checkCommand(&cl_user_configured, &actions);
                _conf_command_flags.append("--conf");
                const int j(i + 1);
                if (j < arguments.count() && !arguments.at(j).startsWith('-'))
                    _conf_command_flags.append(arguments.at(j));
                --actions;
            }
            else if (arguments.at(i) == "--sloppy")
            {
                checkCommand(&cl_sloppy, &actions);
                --actions;
            }
            // actions
            else if (arguments.at(i) == "--configure")
                checkCommand(&cl_configure, &actions);
            else if (arguments.at(i) == "--bibedit")
                checkCommand(&cl_bibedit, &actions);
            else if (arguments.at(i) == "--citer")
                checkCommand(&cl_citer, &actions);
            else if (arguments.at(i) == "--import")
                checkCommand(&cl_import, &actions);
            else if (arguments.at(i) == "--html-annote")
                checkCommand(&cl_html_annote, &actions);
            else if (arguments.at(i) == "--view-annote")
                checkCommand(&cl_view_annote, &actions);
            else if (arguments.at(i) == "--doc2bib")
                checkCommand(&cl_doc2bib, &actions);
            else if (arguments.at(i) == "--txt2bib")
                checkCommand(&cl_txt2bib, &actions);
            else if (arguments.at(i) == "--index")
                checkCommand(&cl_index, &actions);
            else if (arguments.at(i) == "--c2binfo")
                cl_cb2bib_information = true;
            else if (arguments.at(i).startsWith("--test"))
                cl_cb2bib_tests = true;
            else
                _is_loaded = false;
        }
    if (actions > 1)
        _is_loaded = false;
    if (cl_user_configured && cl_configure)
        _is_loaded = false;
    if (cl_sloppy && !(cl_doc2bib || cl_txt2bib))
        _is_loaded = false;
    if (cl_index &&
        (cl_bibedit || cl_citer || cl_import || cl_html_annote || cl_view_annote || cl_doc2bib || cl_txt2bib))
        _is_loaded = false;
    if (!_is_loaded)
    {
        printUsage();
        return;
    }
    cl_console_mode =
        cl_html_annote || cl_cb2bib_information || cl_cb2bib_tests || cl_doc2bib || cl_txt2bib || cl_index;
    cl_cb2bib_mode = !(cl_console_mode || cl_configure || cl_view_annote);

    // Check for cl_user_configured
    if (cl_configure)
        for (int i = 1; i < arguments.count() - 1; ++i)
            if (arguments.at(i) == "--configure")
            {
                if (!arguments.at(i + 1).startsWith('-'))
                    cl_user_configured = true;
                break;
            }
    // Check for --bibedit files
    if (cl_bibedit)
    {
        for (int i = 1; i < arguments.count(); ++i)
            if (arguments.at(i) == "--bibedit")
            {
                for (int j = i + 1; j < arguments.count(); ++j)
                    if (arguments.at(j).startsWith('-'))
                        break;
                    else
                        cl_bibedit_filenames.append(decodeFilename(arguments.at(j)));
                break;
            }
        if (cl_bibedit_filenames.count() == 0)
            cl_bibedit = false;
        else
            setValue("cb2Bib/BibTeXFile", cl_bibedit_filenames.first());
    }
    // Check for --citer files
    else if (cl_citer)
    {
        for (int i = 1; i < arguments.count(); ++i)
            if (arguments.at(i) == "--citer")
            {
                for (int j = i + 1; j < arguments.count(); ++j)
                    if (arguments.at(j).startsWith('-'))
                        break;
                    else
                        cl_citer_filenames.append(decodeFilename(arguments.at(j)));
                break;
            }
    }
    // Check for --index BibTeX dirname
    else if (cl_index)
    {
        for (int i = 1; i < arguments.count(); ++i)
            if (arguments.at(i) == "--index")
            {
                const int j(i + 1);
                if (j < arguments.count() && !arguments.at(j).startsWith('-'))
                    cl_index_dirname.append(decodeFilename(arguments.at(j)));
                break;
            }
    }
    // Check for annote file
    else if (cl_html_annote || cl_view_annote)
    {
        for (int i = 1; i < arguments.count(); ++i)
            if (arguments.at(i) == "--html-annote" || arguments.at(i) == "--view-annote")
            {
                const int j(i + 1);
                if (j < arguments.count())
                    if (!arguments.at(j).startsWith('-'))
                        cl_annote_filename = decodeFilename(arguments.at(j));
                if (cl_annote_filename.isEmpty())
                    _is_loaded = false;
            }
    }
    // Check for extraction files
    else if (cl_doc2bib || cl_txt2bib)
    {
        for (int i = 1; i < arguments.count(); ++i)
            if (arguments.at(i) == "--doc2bib" || arguments.at(i) == "--txt2bib")
            {
                for (int j = i + 1; j < arguments.count(); ++j)
                    if (arguments.at(j).startsWith('-'))
                        break;
                    else
                        cl_extract_input_filenames.append(decodeFilename(arguments.at(j)));
                break;
            }
        if (cl_extract_input_filenames.count() < 2)
            _is_loaded = false;
        else
            cl_extract_output_filename = cl_extract_input_filenames.takeLast();
    }
    // Check for import reference file
    else if (cl_import)
    {
        if (arguments.count() > 2)
            if (!arguments.at(2).startsWith('-'))
            {
                cl_import_filename = QFileInfo(QFile::decodeName(arguments.at(2).toLocal8Bit())).absoluteFilePath();
                return;
            }
        cl_import = false;
        _is_loaded = false;
    }
    // Accept also 'cb2bib filename' as '--import' to ease import on Windows
    else if (arguments.count() > 1)
        if (!arguments.at(1).startsWith('-'))
        {
            cl_import_filename = QFileInfo(QFile::decodeName(arguments.at(1).toLocal8Bit())).absoluteFilePath();
            cl_import = true;
            return;
        }
    if (!_is_loaded)
        printUsage();
}

void settings::checkCommand(bool* action, int* actions)
{
    if (*action)
        _is_loaded = false;
    *action = true;
    *actions += 1;
}

QString settings::decodeFilename(const QString& fn) const
{
    // This function is meant for fn given by the command shell and that will end up being visible
    return QDir::toNativeSeparators(QFileInfo(QFile::decodeName(fn.toLocal8Bit())).absoluteFilePath());
}

void settings::printUsage()
{
    fprintf(stdout, "Usage: cb2bib\n");
    fprintf(stdout, "       cb2bib [action] [filename1 [filename2 ... ]] [--conf [filename.conf]]\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "Actions:\n");
    fprintf(stdout, "       --configure [filename.conf]                        Edit configuration\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "       --bibedit [filename1.bib [filename2.bib ... ]]     Edit/browse BibTeX files\n");
    fprintf(stdout, "       --citer [filename1.bib [filename2.bib ... ]]       Start cb2Bib citer\n");
    fprintf(
        stdout,
        "       --import tmp_reference_filename                    Import reference, usually from ad hoc websites\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "       --doc2bib fn1.doc [fn2.doc ... ] reference.bib     Extract reference from document file\n");
    fprintf(stdout, "       --txt2bib fn1.txt [fn2.txt ... ] reference.bib     Extract reference from text file\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "       --index [bibdirname]                               Extract keywords from document files\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "       --html-annote filename.tex                         Convert annote file to HTML\n");
    fprintf(stdout, "       --view-annote filename.tex                         Convert and visualize annote file\n");
    fprintf(stdout, "       --view-annote filename.tex.html                    Visualize annote file\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "Switches:\n");
    fprintf(stdout, "       --conf [filename.conf]                             Use configuration file\n");
    fprintf(
        stdout,
        "       --sloppy                                           Accept guesses in automatic reference extraction\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "Examples:\n");
    fprintf(stdout, "       cb2bib                                             Start cb2Bib extraction panel\n");
    fprintf(stdout, "       cb2bib --import tmp_reference_filename             Import reference\n");
    fprintf(stdout, "       cb2bib --bibedit filename.bib                      Edit BibTeX filename.bib\n");
    fprintf(stdout, "       cb2bib --conf                                      Start cb2Bib in USB mode\n");
    fprintf(stdout,
            "       cb2bib --doc2bib *.pdf references.bib              Extract references from PDF title pages\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "Notes:\n");
    fprintf(stdout, " -Use switch --conf to particularize specific settings for specific actions.\n");
    fprintf(stdout,
            " -The file cb2bib.conf must be readable and writable. If it does not exist, cb2Bib will create one\n");
    fprintf(stdout, "  based on predefined defaults.\n");
    fprintf(stdout,
            " -If starting cb2Bib from a removable media use, the command 'cb2bib --conf' without configuration\n");
    fprintf(stdout,
            "  filename. Settings will be read from and written to /cb2bib/full/path/cb2bib.conf, being therefore\n");
    fprintf(stdout, "  independent of the mounting address that the host computer will provide.\n");
    fprintf(
        stdout,
        " -To import references from a browser select when asked c2bimport, which expands to 'cb2bib --import %%f'.\n");
    fprintf(stdout, "  The browser will provide the temporary reference filename.\n");
    fprintf(stdout,
            " -A number of factors influence the reliability of automatic extractions. Consider writing customized\n");
    fprintf(stdout, "  regular expressions and network queries, and use metadata when available.\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "Important:\n");
    fprintf(stdout,
            " -The commands --doc2bib and --txt2bib do not append the references to the references.bib. They create\n");
    fprintf(stdout, "  a new file, or silently overwrite it if already exists.\n");
    fprintf(stdout, "\n");
}
