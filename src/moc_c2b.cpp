/****************************************************************************
** Meta object code from reading C++ file 'c2b.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "c2b.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'c2b.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_c2b_t {
    QByteArrayData data[21];
    char stringdata0[219];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_c2b_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_c2b_t qt_meta_stringdata_c2b = {
    {
QT_MOC_LITERAL(0, 0, 3), // "c2b"
QT_MOC_LITERAL(1, 4, 13), // "searchInFiles"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 6), // "string"
QT_MOC_LITERAL(4, 26, 2), // "fn"
QT_MOC_LITERAL(5, 29, 13), // "statusMessage"
QT_MOC_LITERAL(6, 43, 7), // "message"
QT_MOC_LITERAL(7, 51, 9), // "configure"
QT_MOC_LITERAL(8, 61, 5), // "index"
QT_MOC_LITERAL(9, 67, 13), // "exitRequested"
QT_MOC_LITERAL(10, 81, 27), // "proxyAuthenticationRequired"
QT_MOC_LITERAL(11, 109, 13), // "QNetworkProxy"
QT_MOC_LITERAL(12, 123, 5), // "proxy"
QT_MOC_LITERAL(13, 129, 15), // "QAuthenticator*"
QT_MOC_LITERAL(14, 145, 4), // "auth"
QT_MOC_LITERAL(15, 150, 11), // "showMessage"
QT_MOC_LITERAL(16, 162, 5), // "title"
QT_MOC_LITERAL(17, 168, 2), // "ms"
QT_MOC_LITERAL(18, 171, 22), // "updateDownloadProgress"
QT_MOC_LITERAL(19, 194, 13), // "bytesReceived"
QT_MOC_LITERAL(20, 208, 10) // "bytesTotal"

    },
    "c2b\0searchInFiles\0\0string\0fn\0statusMessage\0"
    "message\0configure\0index\0exitRequested\0"
    "proxyAuthenticationRequired\0QNetworkProxy\0"
    "proxy\0QAuthenticator*\0auth\0showMessage\0"
    "title\0ms\0updateDownloadProgress\0"
    "bytesReceived\0bytesTotal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_c2b[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,
       5,    1,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   62,    2, 0x0a /* Public */,
       7,    0,   65,    2, 0x2a /* Public | MethodCloned */,
       9,    0,   66,    2, 0x0a /* Public */,
      10,    2,   67,    2, 0x08 /* Private */,
      15,    2,   72,    2, 0x08 /* Private */,
      18,    2,   77,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11, 0x80000000 | 13,   12,   14,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   16,   17,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,   19,   20,

       0        // eod
};

void c2b::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<c2b *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->searchInFiles((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->statusMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->configure((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->configure(); break;
        case 4: _t->exitRequested(); break;
        case 5: _t->proxyAuthenticationRequired((*reinterpret_cast< const QNetworkProxy(*)>(_a[1])),(*reinterpret_cast< QAuthenticator*(*)>(_a[2]))); break;
        case 6: _t->showMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 7: _t->updateDownloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (c2b::*)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c2b::searchInFiles)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (c2b::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c2b::statusMessage)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject c2b::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_c2b.data,
    qt_meta_data_c2b,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *c2b::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *c2b::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_c2b.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int c2b::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void c2b::searchInFiles(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void c2b::statusMessage(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
