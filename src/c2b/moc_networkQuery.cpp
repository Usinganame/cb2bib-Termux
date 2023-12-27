/****************************************************************************
** Meta object code from reading C++ file 'networkQuery.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "networkQuery.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'networkQuery.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_networkQuery_t {
    QByteArrayData data[15];
    char stringdata0[188];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_networkQuery_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_networkQuery_t qt_meta_stringdata_networkQuery = {
    {
QT_MOC_LITERAL(0, 0, 12), // "networkQuery"
QT_MOC_LITERAL(1, 13, 10), // "queryEnded"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 9), // "succeeded"
QT_MOC_LITERAL(4, 35, 9), // "targetPDF"
QT_MOC_LITERAL(5, 45, 9), // "targetBib"
QT_MOC_LITERAL(6, 55, 13), // "statusMessage"
QT_MOC_LITERAL(7, 69, 2), // "ms"
QT_MOC_LITERAL(8, 72, 23), // "areQueryParametersValid"
QT_MOC_LITERAL(9, 96, 18), // "setQueryParameters"
QT_MOC_LITERAL(10, 115, 9), // "queryDone"
QT_MOC_LITERAL(11, 125, 12), // "submitQuery1"
QT_MOC_LITERAL(12, 138, 12), // "submitQuery2"
QT_MOC_LITERAL(13, 151, 12), // "submitQuery3"
QT_MOC_LITERAL(14, 164, 23) // "updateQueryPlaceholders"

    },
    "networkQuery\0queryEnded\0\0succeeded\0"
    "targetPDF\0targetBib\0statusMessage\0ms\0"
    "areQueryParametersValid\0setQueryParameters\0"
    "queryDone\0submitQuery1\0submitQuery2\0"
    "submitQuery3\0updateQueryPlaceholders"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_networkQuery[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   59,    2, 0x06 /* Public */,
       6,    1,   66,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   69,    2, 0x08 /* Private */,
       9,    0,   70,    2, 0x08 /* Private */,
      10,    1,   71,    2, 0x08 /* Private */,
      11,    0,   74,    2, 0x08 /* Private */,
      12,    1,   75,    2, 0x08 /* Private */,
      13,    1,   78,    2, 0x08 /* Private */,
      14,    0,   81,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::QString,    3,    4,    5,
    QMetaType::Void, QMetaType::QString,    7,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,

       0        // eod
};

void networkQuery::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<networkQuery *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->queryEnded((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 1: _t->statusMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: { bool _r = _t->areQueryParametersValid();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: { bool _r = _t->setQueryParameters();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->queryDone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->submitQuery1(); break;
        case 6: _t->submitQuery2((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->submitQuery3((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->updateQueryPlaceholders(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (networkQuery::*)(bool , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&networkQuery::queryEnded)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (networkQuery::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&networkQuery::statusMessage)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject networkQuery::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_networkQuery.data,
    qt_meta_data_networkQuery,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *networkQuery::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *networkQuery::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_networkQuery.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int networkQuery::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void networkQuery::queryEnded(bool _t1, const QString & _t2, const QString & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void networkQuery::statusMessage(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
