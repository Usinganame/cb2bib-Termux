/****************************************************************************
** Meta object code from reading C++ file 'bookmarkPlugin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "bookmarkPlugin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bookmarkPlugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_bookmarkPlugin_t {
    QByteArrayData data[8];
    char stringdata0[75];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_bookmarkPlugin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_bookmarkPlugin_t qt_meta_stringdata_bookmarkPlugin = {
    {
QT_MOC_LITERAL(0, 0, 14), // "bookmarkPlugin"
QT_MOC_LITERAL(1, 15, 13), // "editBookmarks"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 8), // "openFile"
QT_MOC_LITERAL(4, 39, 2), // "fn"
QT_MOC_LITERAL(5, 42, 4), // "init"
QT_MOC_LITERAL(6, 47, 12), // "openBookmark"
QT_MOC_LITERAL(7, 60, 14) // "parseBookmarks"

    },
    "bookmarkPlugin\0editBookmarks\0\0openFile\0"
    "fn\0init\0openBookmark\0parseBookmarks"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_bookmarkPlugin[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    1,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   43,    2, 0x08 /* Private */,
       6,    0,   44,    2, 0x08 /* Private */,
       7,    0,   45,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void bookmarkPlugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<bookmarkPlugin *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->editBookmarks(); break;
        case 1: _t->openFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->init(); break;
        case 3: _t->openBookmark(); break;
        case 4: _t->parseBookmarks(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (bookmarkPlugin::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&bookmarkPlugin::editBookmarks)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (bookmarkPlugin::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&bookmarkPlugin::openFile)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject bookmarkPlugin::staticMetaObject = { {
    QMetaObject::SuperData::link<QMenu::staticMetaObject>(),
    qt_meta_stringdata_bookmarkPlugin.data,
    qt_meta_data_bookmarkPlugin,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *bookmarkPlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *bookmarkPlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_bookmarkPlugin.stringdata0))
        return static_cast<void*>(this);
    return QMenu::qt_metacast(_clname);
}

int bookmarkPlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMenu::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void bookmarkPlugin::editBookmarks()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void bookmarkPlugin::openFile(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
