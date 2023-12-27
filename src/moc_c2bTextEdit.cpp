/****************************************************************************
** Meta object code from reading C++ file 'c2bTextEdit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "c2bTextEdit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'c2bTextEdit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_c2bTextEdit_t {
    QByteArrayData data[11];
    char stringdata0[152];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_c2bTextEdit_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_c2bTextEdit_t qt_meta_stringdata_c2bTextEdit = {
    {
QT_MOC_LITERAL(0, 0, 11), // "c2bTextEdit"
QT_MOC_LITERAL(1, 12, 20), // "overwriteModeChanged"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 18), // "toggleWordWrapping"
QT_MOC_LITERAL(4, 53, 13), // "convert2LaTeX"
QT_MOC_LITERAL(5, 67, 15), // "convert2Unicode"
QT_MOC_LITERAL(6, 83, 12), // "loadSettings"
QT_MOC_LITERAL(7, 96, 25), // "updateLineNumberAreaWidth"
QT_MOC_LITERAL(8, 122, 20), // "updateLineNumberArea"
QT_MOC_LITERAL(9, 143, 5), // "qrect"
QT_MOC_LITERAL(10, 149, 2) // "dy"

    },
    "c2bTextEdit\0overwriteModeChanged\0\0"
    "toggleWordWrapping\0convert2LaTeX\0"
    "convert2Unicode\0loadSettings\0"
    "updateLineNumberAreaWidth\0"
    "updateLineNumberArea\0qrect\0dy"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_c2bTextEdit[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x09 /* Protected */,
       5,    0,   52,    2, 0x09 /* Protected */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    2,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QRect, QMetaType::Int,    9,   10,

       0        // eod
};

void c2bTextEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<c2bTextEdit *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->overwriteModeChanged(); break;
        case 1: _t->toggleWordWrapping(); break;
        case 2: _t->convert2LaTeX(); break;
        case 3: _t->convert2Unicode(); break;
        case 4: _t->loadSettings(); break;
        case 5: _t->updateLineNumberAreaWidth(); break;
        case 6: _t->updateLineNumberArea((*reinterpret_cast< const QRect(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (c2bTextEdit::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c2bTextEdit::overwriteModeChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject c2bTextEdit::staticMetaObject = { {
    QMetaObject::SuperData::link<QPlainTextEdit::staticMetaObject>(),
    qt_meta_stringdata_c2bTextEdit.data,
    qt_meta_data_c2bTextEdit,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *c2bTextEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *c2bTextEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_c2bTextEdit.stringdata0))
        return static_cast<void*>(this);
    return QPlainTextEdit::qt_metacast(_clname);
}

int c2bTextEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPlainTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void c2bTextEdit::overwriteModeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
