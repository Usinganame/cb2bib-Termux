LANGUAGE = C++
CONFIG += c++11
HEADERS += $$files(*.h)
SOURCES += $$files(*.cpp)
SOURCES -= $$files(moc_*.cpp)
SOURCES -= $$files(qrc_*.cpp)
RESOURCES += c2blib.qrc
INCLUDEPATH += .
QT = core network
win32 {
    TARGET = ../../c2b
} else {
    TARGET = ../c2b
}
CONFIG -= dll
CONFIG += staticlib
VERSION = 0.0.0
TEMPLATE = lib
QMAKE_CXXFLAGS_DEBUG += -DC2B_DEBUG

!use_lzsse : !use_lz4 : !use_lzo : !use_qt_zlib {
    CONFIG += use_lz4
}
use_lzsse {
    message(cb2Bib will be linked against LZSSE library)
    DEFINES += C2B_USE_LZSSE
    SOURCES += ./lzsse4/lzsse4.cpp
    INCLUDEPATH += ./lzsse4
}
use_lz4 {
    message(cb2Bib will be linked against LZ4 library)
    DEFINES += C2B_USE_LZ4
}
use_lzo {
    message(cb2Bib will be linked against LZO library)
    DEFINES += C2B_USE_LZO
}
use_qt_zlib {
    message(cb2Bib will be linked against Qt ZLIB library)
    DEFINES += C2B_USE_ZLIB
}
use_avx2 {
    QMAKE_CXXFLAGS += -mavx2
}
