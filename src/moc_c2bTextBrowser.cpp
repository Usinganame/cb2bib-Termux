/****************************************************************************
** Meta object code from reading C++ file 'c2bTextBrowser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "c2bTextBrowser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'c2bTextBrowser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_c2bTextBrowser_t {
    QByteArrayData data[4];
    char stringdata0[31];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_c2bTextBrowser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_c2bTextBrowser_t qt_meta_stringdata_c2bTextBrowser = {
    {
QT_MOC_LITERAL(0, 0, 14), // "c2bTextBrowser"
QT_MOC_LITERAL(1, 15, 9), // "setSource"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 4) // "name"

    },
    "c2bTextBrowser\0setSource\0\0name"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_c2bTextBrowser[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QUrl,    3,

       0        // eod
};

void c2bTextBrowser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<c2bTextBrowser *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setSource((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject c2bTextBrowser::staticMetaObject = { {
    QMetaObject::SuperData::link<QTextBrowser::staticMetaObject>(),
    qt_meta_stringdata_c2bTextBrowser.data,
    qt_meta_data_c2bTextBrowser,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *c2bTextBrowser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *c2bTextBrowser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_c2bTextBrowser.stringdata0))
        return static_cast<void*>(this);
    return QTextBrowser::qt_metacast(_clname);
}

int c2bTextBrowser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextBrowser::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
