/****************************************************************************
** Meta object code from reading C++ file 'cb2Bib.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "cb2Bib.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cb2Bib.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_cb2Bib_t {
    QByteArrayData data[77];
    char stringdata0[994];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_cb2Bib_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_cb2Bib_t qt_meta_stringdata_cb2Bib = {
    {
QT_MOC_LITERAL(0, 0, 6), // "cb2Bib"
QT_MOC_LITERAL(1, 7, 14), // "addedBibToFile"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 15), // "endedProcessing"
QT_MOC_LITERAL(4, 39, 6), // "status"
QT_MOC_LITERAL(5, 46, 4), // "show"
QT_MOC_LITERAL(6, 51, 19), // "abbreviationsEditor"
QT_MOC_LITERAL(7, 71, 10), // "addAuthors"
QT_MOC_LITERAL(8, 82, 10), // "addEditors"
QT_MOC_LITERAL(9, 93, 11), // "addMetadata"
QT_MOC_LITERAL(10, 105, 9), // "addToFile"
QT_MOC_LITERAL(11, 115, 5), // "ready"
QT_MOC_LITERAL(12, 121, 10), // "anyPattern"
QT_MOC_LITERAL(13, 132, 9), // "bibEditor"
QT_MOC_LITERAL(14, 142, 10), // "bibtexfile"
QT_MOC_LITERAL(15, 153, 12), // "bibSearcher*"
QT_MOC_LITERAL(16, 166, 8), // "searcher"
QT_MOC_LITERAL(17, 175, 11), // "bibModified"
QT_MOC_LITERAL(18, 187, 8), // "modified"
QT_MOC_LITERAL(19, 196, 15), // "bookmarksEditor"
QT_MOC_LITERAL(20, 212, 7), // "c2bInit"
QT_MOC_LITERAL(21, 220, 13), // "checkRepeated"
QT_MOC_LITERAL(22, 234, 11), // "dataChanged"
QT_MOC_LITERAL(23, 246, 3), // "str"
QT_MOC_LITERAL(24, 250, 12), // "deleteTmpBib"
QT_MOC_LITERAL(25, 263, 15), // "doSearchInFiles"
QT_MOC_LITERAL(26, 279, 6), // "string"
QT_MOC_LITERAL(27, 286, 2), // "fn"
QT_MOC_LITERAL(28, 289, 11), // "fileDropped"
QT_MOC_LITERAL(29, 301, 15), // "forceDataChange"
QT_MOC_LITERAL(30, 317, 11), // "guessFields"
QT_MOC_LITERAL(31, 329, 12), // "insertRegExp"
QT_MOC_LITERAL(32, 342, 11), // "linkClicked"
QT_MOC_LITERAL(33, 354, 2), // "ln"
QT_MOC_LITERAL(34, 357, 12), // "loadSettings"
QT_MOC_LITERAL(35, 370, 12), // "makeNetQuery"
QT_MOC_LITERAL(36, 383, 13), // "netQueryEnded"
QT_MOC_LITERAL(37, 397, 9), // "succeeded"
QT_MOC_LITERAL(38, 407, 9), // "targetPDF"
QT_MOC_LITERAL(39, 417, 9), // "targetBib"
QT_MOC_LITERAL(40, 427, 18), // "on_AddBibB_clicked"
QT_MOC_LITERAL(41, 446, 20), // "on_BibTeXDir_clicked"
QT_MOC_LITERAL(42, 467, 21), // "on_ConfigureB_clicked"
QT_MOC_LITERAL(43, 489, 19), // "on_ConnectB_clicked"
QT_MOC_LITERAL(44, 509, 22), // "on_EditBibTeXB_clicked"
QT_MOC_LITERAL(45, 532, 16), // "on_ExitB_clicked"
QT_MOC_LITERAL(46, 549, 28), // "on_MakeNetworkQueryB_clicked"
QT_MOC_LITERAL(47, 578, 21), // "on_PdfImportB_clicked"
QT_MOC_LITERAL(48, 600, 25), // "on_SearchInFilesB_clicked"
QT_MOC_LITERAL(49, 626, 21), // "on_ViewAboutB_clicked"
QT_MOC_LITERAL(50, 648, 19), // "on_ViewBibB_clicked"
QT_MOC_LITERAL(51, 668, 10), // "openAnnote"
QT_MOC_LITERAL(52, 679, 16), // "openFileDocument"
QT_MOC_LITERAL(53, 696, 17), // "postprocessBibTeX"
QT_MOC_LITERAL(54, 714, 17), // "preparseClipboard"
QT_MOC_LITERAL(55, 732, 9), // "readField"
QT_MOC_LITERAL(56, 742, 8), // "position"
QT_MOC_LITERAL(57, 751, 13), // "regExpsEditor"
QT_MOC_LITERAL(58, 765, 13), // "restartEngine"
QT_MOC_LITERAL(59, 779, 11), // "savePattern"
QT_MOC_LITERAL(60, 791, 2), // "rx"
QT_MOC_LITERAL(61, 794, 6), // "rxname"
QT_MOC_LITERAL(62, 801, 10), // "selectFile"
QT_MOC_LITERAL(63, 812, 19), // "setDocumentFilename"
QT_MOC_LITERAL(64, 832, 21), // "setTaggedClipEditMode"
QT_MOC_LITERAL(65, 854, 6), // "tagged"
QT_MOC_LITERAL(66, 861, 14), // "setWindowTitle"
QT_MOC_LITERAL(67, 876, 5), // "title"
QT_MOC_LITERAL(68, 882, 8), // "showLink"
QT_MOC_LITERAL(69, 891, 11), // "showMessage"
QT_MOC_LITERAL(70, 903, 2), // "ms"
QT_MOC_LITERAL(71, 906, 19), // "toggleReferenceTabs"
QT_MOC_LITERAL(72, 926, 25), // "updateCheckRepeatedAction"
QT_MOC_LITERAL(73, 952, 19), // "updateOpenDocuments"
QT_MOC_LITERAL(74, 972, 3), // "obj"
QT_MOC_LITERAL(75, 976, 8), // "old_name"
QT_MOC_LITERAL(76, 985, 8) // "new_name"

    },
    "cb2Bib\0addedBibToFile\0\0endedProcessing\0"
    "status\0show\0abbreviationsEditor\0"
    "addAuthors\0addEditors\0addMetadata\0"
    "addToFile\0ready\0anyPattern\0bibEditor\0"
    "bibtexfile\0bibSearcher*\0searcher\0"
    "bibModified\0modified\0bookmarksEditor\0"
    "c2bInit\0checkRepeated\0dataChanged\0str\0"
    "deleteTmpBib\0doSearchInFiles\0string\0"
    "fn\0fileDropped\0forceDataChange\0"
    "guessFields\0insertRegExp\0linkClicked\0"
    "ln\0loadSettings\0makeNetQuery\0netQueryEnded\0"
    "succeeded\0targetPDF\0targetBib\0"
    "on_AddBibB_clicked\0on_BibTeXDir_clicked\0"
    "on_ConfigureB_clicked\0on_ConnectB_clicked\0"
    "on_EditBibTeXB_clicked\0on_ExitB_clicked\0"
    "on_MakeNetworkQueryB_clicked\0"
    "on_PdfImportB_clicked\0on_SearchInFilesB_clicked\0"
    "on_ViewAboutB_clicked\0on_ViewBibB_clicked\0"
    "openAnnote\0openFileDocument\0"
    "postprocessBibTeX\0preparseClipboard\0"
    "readField\0position\0regExpsEditor\0"
    "restartEngine\0savePattern\0rx\0rxname\0"
    "selectFile\0setDocumentFilename\0"
    "setTaggedClipEditMode\0tagged\0"
    "setWindowTitle\0title\0showLink\0showMessage\0"
    "ms\0toggleReferenceTabs\0updateCheckRepeatedAction\0"
    "updateOpenDocuments\0obj\0old_name\0"
    "new_name"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_cb2Bib[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      58,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  304,    2, 0x06 /* Public */,
       3,    1,  307,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,  310,    2, 0x0a /* Public */,
       6,    0,  311,    2, 0x08 /* Private */,
       7,    0,  312,    2, 0x08 /* Private */,
       8,    0,  313,    2, 0x08 /* Private */,
       9,    0,  314,    2, 0x08 /* Private */,
      10,    1,  315,    2, 0x08 /* Private */,
      12,    0,  318,    2, 0x08 /* Private */,
      13,    2,  319,    2, 0x08 /* Private */,
      13,    1,  324,    2, 0x28 /* Private | MethodCloned */,
      17,    1,  327,    2, 0x08 /* Private */,
      19,    0,  330,    2, 0x08 /* Private */,
      20,    0,  331,    2, 0x08 /* Private */,
      21,    0,  332,    2, 0x08 /* Private */,
      22,    1,  333,    2, 0x08 /* Private */,
      24,    0,  336,    2, 0x08 /* Private */,
      25,    2,  337,    2, 0x08 /* Private */,
      25,    1,  342,    2, 0x28 /* Private | MethodCloned */,
      25,    0,  345,    2, 0x28 /* Private | MethodCloned */,
      28,    1,  346,    2, 0x08 /* Private */,
      29,    1,  349,    2, 0x08 /* Private */,
      30,    0,  352,    2, 0x08 /* Private */,
      31,    0,  353,    2, 0x08 /* Private */,
      32,    1,  354,    2, 0x08 /* Private */,
      34,    0,  357,    2, 0x08 /* Private */,
      35,    0,  358,    2, 0x08 /* Private */,
      36,    3,  359,    2, 0x08 /* Private */,
      40,    0,  366,    2, 0x08 /* Private */,
      41,    0,  367,    2, 0x08 /* Private */,
      42,    0,  368,    2, 0x08 /* Private */,
      43,    0,  369,    2, 0x08 /* Private */,
      44,    0,  370,    2, 0x08 /* Private */,
      45,    0,  371,    2, 0x08 /* Private */,
      46,    0,  372,    2, 0x08 /* Private */,
      47,    0,  373,    2, 0x08 /* Private */,
      48,    0,  374,    2, 0x08 /* Private */,
      49,    0,  375,    2, 0x08 /* Private */,
      50,    0,  376,    2, 0x08 /* Private */,
      51,    0,  377,    2, 0x08 /* Private */,
      52,    0,  378,    2, 0x08 /* Private */,
      53,    0,  379,    2, 0x08 /* Private */,
      54,    0,  380,    2, 0x08 /* Private */,
      55,    1,  381,    2, 0x08 /* Private */,
      57,    0,  384,    2, 0x08 /* Private */,
      58,    0,  385,    2, 0x08 /* Private */,
      59,    2,  386,    2, 0x08 /* Private */,
      62,    0,  391,    2, 0x08 /* Private */,
      63,    0,  392,    2, 0x08 /* Private */,
      64,    1,  393,    2, 0x08 /* Private */,
      66,    1,  396,    2, 0x08 /* Private */,
      66,    0,  399,    2, 0x28 /* Private | MethodCloned */,
      68,    1,  400,    2, 0x08 /* Private */,
      69,    1,  403,    2, 0x08 /* Private */,
      71,    0,  406,    2, 0x08 /* Private */,
      72,    0,  407,    2, 0x08 /* Private */,
      73,    1,  408,    2, 0x08 /* Private */,
      73,    2,  411,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Bool,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 15,   14,   16,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   23,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   26,   27,
    QMetaType::Void, QMetaType::QString,   26,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   27,
    QMetaType::Void, QMetaType::QString,   23,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QUrl,   33,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::QString,   37,   38,   39,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   56,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   60,   61,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   65,
    QMetaType::Void, QMetaType::QString,   67,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   33,
    QMetaType::Void, QMetaType::QString,   70,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QObjectStar,   74,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   75,   76,

       0        // eod
};

void cb2Bib::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<cb2Bib *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->addedBibToFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->endedProcessing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->show(); break;
        case 3: _t->abbreviationsEditor(); break;
        case 4: _t->addAuthors(); break;
        case 5: _t->addEditors(); break;
        case 6: _t->addMetadata(); break;
        case 7: _t->addToFile((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->anyPattern(); break;
        case 9: _t->bibEditor((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bibSearcher*(*)>(_a[2]))); break;
        case 10: _t->bibEditor((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->bibModified((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->bookmarksEditor(); break;
        case 13: _t->c2bInit(); break;
        case 14: _t->checkRepeated(); break;
        case 15: _t->dataChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 16: _t->deleteTmpBib(); break;
        case 17: _t->doSearchInFiles((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 18: _t->doSearchInFiles((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 19: _t->doSearchInFiles(); break;
        case 20: _t->fileDropped((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 21: _t->forceDataChange((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 22: _t->guessFields(); break;
        case 23: _t->insertRegExp(); break;
        case 24: _t->linkClicked((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 25: _t->loadSettings(); break;
        case 26: _t->makeNetQuery(); break;
        case 27: _t->netQueryEnded((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 28: _t->on_AddBibB_clicked(); break;
        case 29: _t->on_BibTeXDir_clicked(); break;
        case 30: _t->on_ConfigureB_clicked(); break;
        case 31: _t->on_ConnectB_clicked(); break;
        case 32: _t->on_EditBibTeXB_clicked(); break;
        case 33: _t->on_ExitB_clicked(); break;
        case 34: _t->on_MakeNetworkQueryB_clicked(); break;
        case 35: _t->on_PdfImportB_clicked(); break;
        case 36: _t->on_SearchInFilesB_clicked(); break;
        case 37: _t->on_ViewAboutB_clicked(); break;
        case 38: _t->on_ViewBibB_clicked(); break;
        case 39: _t->openAnnote(); break;
        case 40: _t->openFileDocument(); break;
        case 41: _t->postprocessBibTeX(); break;
        case 42: _t->preparseClipboard(); break;
        case 43: _t->readField((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 44: _t->regExpsEditor(); break;
        case 45: _t->restartEngine(); break;
        case 46: _t->savePattern((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 47: _t->selectFile(); break;
        case 48: _t->setDocumentFilename(); break;
        case 49: _t->setTaggedClipEditMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 50: _t->setWindowTitle((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 51: _t->setWindowTitle(); break;
        case 52: _t->showLink((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 53: _t->showMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 54: _t->toggleReferenceTabs(); break;
        case 55: _t->updateCheckRepeatedAction(); break;
        case 56: _t->updateOpenDocuments((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 57: _t->updateOpenDocuments((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (cb2Bib::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&cb2Bib::addedBibToFile)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (cb2Bib::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&cb2Bib::endedProcessing)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject cb2Bib::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_cb2Bib.data,
    qt_meta_data_cb2Bib,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *cb2Bib::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *cb2Bib::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_cb2Bib.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int cb2Bib::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 58)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 58;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 58)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 58;
    }
    return _id;
}

// SIGNAL 0
void cb2Bib::addedBibToFile(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void cb2Bib::endedProcessing(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
