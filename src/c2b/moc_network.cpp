/****************************************************************************
** Meta object code from reading C++ file 'network.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "network.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'network.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_network_t {
    QByteArrayData data[23];
    char stringdata0[313];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_network_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_network_t qt_meta_stringdata_network = {
    {
QT_MOC_LITERAL(0, 0, 7), // "network"
QT_MOC_LITERAL(1, 8, 16), // "downloadProgress"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 13), // "bytesReceived"
QT_MOC_LITERAL(4, 40, 10), // "bytesTotal"
QT_MOC_LITERAL(5, 51, 27), // "proxyAuthenticationRequired"
QT_MOC_LITERAL(6, 79, 13), // "QNetworkProxy"
QT_MOC_LITERAL(7, 93, 5), // "proxy"
QT_MOC_LITERAL(8, 99, 15), // "QAuthenticator*"
QT_MOC_LITERAL(9, 115, 4), // "auth"
QT_MOC_LITERAL(10, 120, 15), // "requestFinished"
QT_MOC_LITERAL(11, 136, 9), // "succeeded"
QT_MOC_LITERAL(12, 146, 14), // "cancelDownload"
QT_MOC_LITERAL(13, 161, 16), // "_client_finished"
QT_MOC_LITERAL(14, 178, 8), // "exitCode"
QT_MOC_LITERAL(15, 187, 20), // "QProcess::ExitStatus"
QT_MOC_LITERAL(16, 208, 10), // "exitStatus"
QT_MOC_LITERAL(17, 219, 22), // "_emit_request_finished"
QT_MOC_LITERAL(18, 242, 15), // "_fetch_finished"
QT_MOC_LITERAL(19, 258, 17), // "_fetch_ready_read"
QT_MOC_LITERAL(20, 276, 14), // "_head_finished"
QT_MOC_LITERAL(21, 291, 12), // "loadSettings"
QT_MOC_LITERAL(22, 304, 8) // "logError"

    },
    "network\0downloadProgress\0\0bytesReceived\0"
    "bytesTotal\0proxyAuthenticationRequired\0"
    "QNetworkProxy\0proxy\0QAuthenticator*\0"
    "auth\0requestFinished\0succeeded\0"
    "cancelDownload\0_client_finished\0"
    "exitCode\0QProcess::ExitStatus\0exitStatus\0"
    "_emit_request_finished\0_fetch_finished\0"
    "_fetch_ready_read\0_head_finished\0"
    "loadSettings\0logError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_network[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   69,    2, 0x06 /* Public */,
       5,    2,   74,    2, 0x06 /* Public */,
      10,    1,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,   82,    2, 0x0a /* Public */,
      13,    2,   83,    2, 0x08 /* Private */,
      17,    0,   88,    2, 0x08 /* Private */,
      18,    0,   89,    2, 0x08 /* Private */,
      19,    0,   90,    2, 0x08 /* Private */,
      20,    0,   91,    2, 0x08 /* Private */,
      21,    0,   92,    2, 0x08 /* Private */,
      22,    0,   93,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    3,    4,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 8,    7,    9,
    QMetaType::Void, QMetaType::Bool,   11,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 15,   14,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void network::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<network *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->downloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 1: _t->proxyAuthenticationRequired((*reinterpret_cast< const QNetworkProxy(*)>(_a[1])),(*reinterpret_cast< QAuthenticator*(*)>(_a[2]))); break;
        case 2: _t->requestFinished((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->cancelDownload(); break;
        case 4: _t->_client_finished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 5: _t->_emit_request_finished(); break;
        case 6: _t->_fetch_finished(); break;
        case 7: _t->_fetch_ready_read(); break;
        case 8: _t->_head_finished(); break;
        case 9: _t->loadSettings(); break;
        case 10: _t->logError(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (network::*)(qint64 , qint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&network::downloadProgress)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (network::*)(const QNetworkProxy & , QAuthenticator * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&network::proxyAuthenticationRequired)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (network::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&network::requestFinished)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject network::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_network.data,
    qt_meta_data_network,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *network::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *network::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_network.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int network::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void network::downloadProgress(qint64 _t1, qint64 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void network::proxyAuthenticationRequired(const QNetworkProxy & _t1, QAuthenticator * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void network::requestFinished(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
