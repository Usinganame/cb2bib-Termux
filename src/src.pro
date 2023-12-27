FORMS += c2bCiterWidget.ui \
         c2bConfigure.ui \
         c2bConfigureFR.ui \
         c2bEditor.ui \
         c2bExportDialog.ui \
         c2bLogWidget.ui \
         c2bPdfImport.ui \
         c2bRLWebSearchSettings.ui \
         c2bReferenceList.ui \
         c2bSaveRegExp.ui \
         c2bSearchInFiles.ui \
         c2bSearchInFilesPattern.ui \
         c2bSearchInFilesPatternEdit.ui \
         c2bShortcutWidget.ui \
         cb2Bib.ui \
         findDialog.ui \
         proxyDialog.ui
RESOURCES += cb2bib.qrc 
HEADERS += bookmarkPlugin.h \
           c2b.h \
           c2bBibHighlighter.h \
           c2bBibMenu.h \
           c2bBibParser.h \
           c2bBibPreparserLog.h \
           c2bCitePatternLineEedit.h \
           c2bCiter.h \
           c2bCiterExcerptView.h \
           c2bCiterHistory.h \
           c2bCiterModel.h \
           c2bCiterView.h \
           c2bCiterWidget.h \
           c2bClipEdit.h \
           c2bClipboard.h \
           c2bCollectionIndex.h \
           c2bColors.h \
           c2bComboBox.h \
           c2bConfigure.h \
           c2bConfigureFR.h \
           c2bConsole.h \
           c2bCoreCiter.h \
           c2bEditor.h \
           c2bExport.h \
           c2bExportDialog.h \
           c2bFileDialog.h \
           c2bFileSystemWatcher.h \
           c2bHighlighter.h \
           c2bIdPatternLineEdit.h \
           c2bLineEdit.h \
           c2bNetworkQuery.h \
           c2bNetworkQueryInfo.h \
           c2bPdfImport.h \
           c2bPostprocess.h \
           c2bREHighlighter.h \
           c2bRLWebSearchSettings.h \
           c2bReferenceList.h \
           c2bSaveREHighlighter.h \
           c2bSaveRegExp.h \
           c2bSearchInFiles.h \
           c2bSearchInFilesPattern.h \
           c2bSettings.h \
           c2bShortcutPushButton.h \
           c2bShortcutWidget.h \
           c2bTests.h \
           c2bTextBrowser.h \
           c2bTextEdit.h \
           c2bUpdateMetadata.h \
           c2bUtils.h \
           cb2Bib.h \
           dialog.h \
           findDialog.h
SOURCES += bookmarkPlugin.cpp \
           c2b.cpp \
           c2bBibHighlighter.cpp \
           c2bBibMenu.cpp \
           c2bBibParser.cpp \
           c2bBibPreparserLog.cpp \
           c2bCitePatternLineEedit.cpp \
           c2bCiterExcerptView.cpp \
           c2bCiterHistory.cpp \
           c2bCiterModel.cpp \
           c2bCiterView.cpp \
           c2bCiterWidget.cpp \
           c2bClipEdit.cpp \
           c2bClipboard.cpp \
           c2bCollectionIndex.cpp \
           c2bColors.cpp \
           c2bComboBox.cpp \
           c2bConfigure.cpp \
           c2bConfigureFR.cpp \
           c2bConsole.cpp \
           c2bCoreCiter.cpp \
           c2bEditor.cpp \
           c2bExport.cpp \
           c2bExportDialog.cpp \
           c2bFileDialog.cpp \
           c2bFileSystemWatcher.cpp \
           c2bHighlighter.cpp \
           c2bIdPatternLineEdit.cpp \
           c2bLineEdit.cpp \
           c2bNetworkQuery.cpp \
           c2bNetworkQueryInfo.cpp \
           c2bPdfImport.cpp \
           c2bPostprocess.cpp \
           c2bREHighlighter.cpp \
           c2bRLWebSearchSettings.cpp \
           c2bReferenceList.cpp \
           c2bSaveREHighlighter.cpp \
           c2bSaveRegExp.cpp \
           c2bSearchInFiles.cpp \
           c2bSearchInFilesPattern.cpp \
           c2bSettings.cpp \
           c2bShortcutPushButton.cpp \
           c2bShortcutWidget.cpp \
           c2bTests.cpp \
           c2bTextBrowser.cpp \
           c2bTextEdit.cpp \
           c2bUpdateMetadata.cpp \
           c2bUtils.cpp \
           cb2Bib.cpp \
           findDialog.cpp \
           main.cpp

HEADERS += $$files(qtsingleapplication/src/*.h)
SOURCES += $$files(qtsingleapplication/src/*.cpp)

TEMPLATE = app
QT += widgets network
CONFIG += c++11
LIBS += -lc2b
QMAKE_LIBDIR += .
INCLUDEPATH += c2b .

qtHaveModule(webkitwidgets){
    CONFIG += use_webkit
} else {
qtHaveModule(webenginewidgets){
    CONFIG += use_webengine
}}
CONFIG(use_webkit) {
    message(cb2Bib will be linked against QtWebKit library)
    HEADERS += c2bAnnote.h qweb/kit/c2bWebBrowser.h
    SOURCES += c2bAnnote.cpp qweb/kit/c2bWebBrowser.cpp
    INCLUDEPATH += ./qweb/kit
    DEFINES += C2B_USE_QWEB C2B_USE_QWEBKIT
    QT += webkitwidgets
}
CONFIG(use_webengine) {
    message(cb2Bib will be linked against QtWebEngine library)
    HEADERS += c2bAnnote.h qweb/engine/c2bWebBrowser.h
    SOURCES += c2bAnnote.cpp qweb/engine/c2bWebBrowser.cpp
    INCLUDEPATH += ./qweb/engine
    DEFINES += C2B_USE_QWEB C2B_USE_QWEBENGINE
    QT += webenginewidgets
}

!use_lzsse : !use_lz4 : !use_lzo : !use_qt_zlib {
    CONFIG += use_lz4
}
use_lzsse {
    message(cb2Bib will be linked against LZSSE library)
    DEFINES += C2B_USE_LZSSE
}
use_lz4 {
    message(cb2Bib will be linked against LZ4 library)
    LIBS += -llz4
    DEFINES += C2B_USE_LZ4
}
use_lzo {
    message(cb2Bib will be linked against LZO library)
    LIBS += -llzo2
    DEFINES += C2B_USE_LZO
}
use_qt_zlib {
    message(cb2Bib will be linked against Qt ZLIB library)
    DEFINES += C2B_USE_ZLIB
}
use_avx2 {
    QMAKE_CXXFLAGS += -mavx2
}

TARGET = cb2bib
DESTDIR = ../bin
DEPENDPATH += .
POST_TARGETDEPS += libc2b.a
QMAKE_CXXFLAGS_DEBUG += -DC2B_DEBUG

enable_cbpoll {
unix {
    message(Building with clipboardPoll)
    QT += x11extras
    HEADERS += clipboardPoll.h
    SOURCES += clipboardPoll.cpp
    DEFINES += C2B_USE_CBPOLL
    LIBS += -lX11
}}

unix {
INSTALLS += target script cb2bibdata cb2bibdoc icons desktop
target.path = /data/data/com.termux/files/usr/bin
script.files += ../c2bscripts/c2bimport ../c2bscripts/c2bciter
script.path = /data/data/com.termux/files/usr/bin
desktop.files += ../c2bscripts/cb2bib.desktop ../c2bscripts/c2bciter.desktop ../c2bscripts/c2bimport.desktop
desktop.path = /data/data/com.termux/files/usr/share/applications
icons.files += ../src/icons/cb2bib.png
icons.path = /data/data/com.termux/files/usr/share/pixmaps
cb2bibdata.files += ../AUTHORS ../COPYRIGHT ../LICENSE ../CHANGELOG ../data ../c2btools ../testPDFImport
cb2bibdata.path = /data/data/com.termux/files/usr/share/cb2bib
cb2bibdoc.files += ../doc/cb2bib_user_manual.pdf
cb2bibdoc.path = /data/data/com.termux/files/usr/share/cb2bib/doc
}
win32 {
RC_FILE = ../cb2bib.rc
}
macx {
ICON = ../src/icons/cb2bib.icns
INSTALLS += target script cb2bibdata
target.path = /data/data/com.termux/files/usr/bin
script.files += ../c2bscripts/c2bimport ../c2bscripts/c2bciter
script.path = /data/data/com.termux/files/usr/bin
cb2bibdata.files += ../AUTHORS ../COPYRIGHT ../LICENSE ../CHANGELOG ../data ../doc ../c2btools ../testPDFImport
cb2bibdata.path = /data/data/com.termux/files/usr/share/cb2bib
QMAKE_BUNDLE_DATA += script cb2bibdata
#   Set this directory if third party tools, like pdftotext are packaged
#   INSTALLS += externtools
#   externtools.files +=
#   externtools.path = c2bExternTools
#   Set Library data
#   QMAKE_BUNDLE_DATA += externtools
}
