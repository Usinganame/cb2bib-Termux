/****************************************************************************
** Meta object code from reading C++ file 'c2bCitePatternLineEedit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "c2bCitePatternLineEedit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'c2bCitePatternLineEedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_c2bCitePatternLineEedit_t {
    QByteArrayData data[11];
    char stringdata0[110];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_c2bCitePatternLineEedit_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_c2bCitePatternLineEedit_t qt_meta_stringdata_c2bCitePatternLineEedit = {
    {
QT_MOC_LITERAL(0, 0, 23), // "c2bCitePatternLineEedit"
QT_MOC_LITERAL(1, 24, 13), // "statusMessage"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 2), // "ms"
QT_MOC_LITERAL(4, 42, 5), // "check"
QT_MOC_LITERAL(5, 48, 7), // "pattern"
QT_MOC_LITERAL(6, 56, 6), // "citeid"
QT_MOC_LITERAL(7, 63, 13), // "citeids_comma"
QT_MOC_LITERAL(8, 77, 17), // "citeids_semicolon"
QT_MOC_LITERAL(9, 95, 5), // "latex"
QT_MOC_LITERAL(10, 101, 8) // "markdown"

    },
    "c2bCitePatternLineEedit\0statusMessage\0"
    "\0ms\0check\0pattern\0citeid\0citeids_comma\0"
    "citeids_semicolon\0latex\0markdown"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_c2bCitePatternLineEedit[] = {

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
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   52,    2, 0x09 /* Protected */,
       6,    0,   55,    2, 0x09 /* Protected */,
       7,    0,   56,    2, 0x09 /* Protected */,
       8,    0,   57,    2, 0x09 /* Protected */,
       9,    0,   58,    2, 0x09 /* Protected */,
      10,    0,   59,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void c2bCitePatternLineEedit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<c2bCitePatternLineEedit *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->statusMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->check((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->citeid(); break;
        case 3: _t->citeids_comma(); break;
        case 4: _t->citeids_semicolon(); break;
        case 5: _t->latex(); break;
        case 6: _t->markdown(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (c2bCitePatternLineEedit::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c2bCitePatternLineEedit::statusMessage)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject c2bCitePatternLineEedit::staticMetaObject = { {
    QMetaObject::SuperData::link<c2bLineEdit::staticMetaObject>(),
    qt_meta_stringdata_c2bCitePatternLineEedit.data,
    qt_meta_data_c2bCitePatternLineEedit,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *c2bCitePatternLineEedit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *c2bCitePatternLineEedit::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_c2bCitePatternLineEedit.stringdata0))
        return static_cast<void*>(this);
    return c2bLineEdit::qt_metacast(_clname);
}

int c2bCitePatternLineEedit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = c2bLineEdit::qt_metacall(_c, _id, _a);
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
void c2bCitePatternLineEedit::statusMessage(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
