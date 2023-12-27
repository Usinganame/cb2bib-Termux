/****************************************************************************
** Meta object code from reading C++ file 'c2bSearchInFiles.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "c2bSearchInFiles.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'c2bSearchInFiles.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_c2bSearchInFiles_t {
    QByteArrayData data[15];
    char stringdata0[189];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_c2bSearchInFiles_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_c2bSearchInFiles_t qt_meta_stringdata_c2bSearchInFiles = {
    {
QT_MOC_LITERAL(0, 0, 16), // "c2bSearchInFiles"
QT_MOC_LITERAL(1, 17, 10), // "searchDone"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 8), // "filename"
QT_MOC_LITERAL(4, 38, 12), // "bibSearcher*"
QT_MOC_LITERAL(5, 51, 8), // "searcher"
QT_MOC_LITERAL(6, 60, 13), // "setBibTeXFile"
QT_MOC_LITERAL(7, 74, 4), // "file"
QT_MOC_LITERAL(8, 79, 4), // "show"
QT_MOC_LITERAL(9, 84, 4), // "help"
QT_MOC_LITERAL(10, 89, 22), // "on_addPatternB_clicked"
QT_MOC_LITERAL(11, 112, 25), // "on_deletePatternB_clicked"
QT_MOC_LITERAL(12, 138, 23), // "on_editPatternB_clicked"
QT_MOC_LITERAL(13, 162, 15), // "searchB_clicked"
QT_MOC_LITERAL(14, 178, 10) // "updateForm"

    },
    "c2bSearchInFiles\0searchDone\0\0filename\0"
    "bibSearcher*\0searcher\0setBibTeXFile\0"
    "file\0show\0help\0on_addPatternB_clicked\0"
    "on_deletePatternB_clicked\0"
    "on_editPatternB_clicked\0searchB_clicked\0"
    "updateForm"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_c2bSearchInFiles[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   69,    2, 0x0a /* Public */,
       6,    0,   72,    2, 0x2a /* Public | MethodCloned */,
       8,    0,   73,    2, 0x0a /* Public */,
       9,    0,   74,    2, 0x08 /* Private */,
      10,    0,   75,    2, 0x08 /* Private */,
      11,    0,   76,    2, 0x08 /* Private */,
      12,    0,   77,    2, 0x08 /* Private */,
      13,    0,   78,    2, 0x08 /* Private */,
      14,    0,   79,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4,    3,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void c2bSearchInFiles::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<c2bSearchInFiles *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->searchDone((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bibSearcher*(*)>(_a[2]))); break;
        case 1: _t->setBibTeXFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->setBibTeXFile(); break;
        case 3: _t->show(); break;
        case 4: _t->help(); break;
        case 5: _t->on_addPatternB_clicked(); break;
        case 6: _t->on_deletePatternB_clicked(); break;
        case 7: _t->on_editPatternB_clicked(); break;
        case 8: _t->searchB_clicked(); break;
        case 9: _t->updateForm(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (c2bSearchInFiles::*)(const QString & , bibSearcher * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c2bSearchInFiles::searchDone)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject c2bSearchInFiles::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_c2bSearchInFiles.data,
    qt_meta_data_c2bSearchInFiles,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *c2bSearchInFiles::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *c2bSearchInFiles::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_c2bSearchInFiles.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int c2bSearchInFiles::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void c2bSearchInFiles::searchDone(const QString & _t1, bibSearcher * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
