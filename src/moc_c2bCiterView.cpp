/****************************************************************************
** Meta object code from reading C++ file 'c2bCiterView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "c2bCiterView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'c2bCiterView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_c2bCiterView_t {
    QByteArrayData data[14];
    char stringdata0[157];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_c2bCiterView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_c2bCiterView_t qt_meta_stringdata_c2bCiterView = {
    {
QT_MOC_LITERAL(0, 0, 12), // "c2bCiterView"
QT_MOC_LITERAL(1, 13, 14), // "citeReferences"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 13), // "editReference"
QT_MOC_LITERAL(4, 43, 9), // "hideCiter"
QT_MOC_LITERAL(5, 53, 10), // "openAnnote"
QT_MOC_LITERAL(6, 64, 8), // "openFile"
QT_MOC_LITERAL(7, 73, 7), // "openUrl"
QT_MOC_LITERAL(8, 81, 20), // "patternFilterChanged"
QT_MOC_LITERAL(9, 102, 4), // "mode"
QT_MOC_LITERAL(10, 107, 7), // "pattern"
QT_MOC_LITERAL(11, 115, 13), // "statusMessage"
QT_MOC_LITERAL(12, 129, 7), // "message"
QT_MOC_LITERAL(13, 137, 19) // "updatePatternFilter"

    },
    "c2bCiterView\0citeReferences\0\0editReference\0"
    "hideCiter\0openAnnote\0openFile\0openUrl\0"
    "patternFilterChanged\0mode\0pattern\0"
    "statusMessage\0message\0updatePatternFilter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_c2bCiterView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    0,   60,    2, 0x06 /* Public */,
       4,    0,   61,    2, 0x06 /* Public */,
       5,    0,   62,    2, 0x06 /* Public */,
       6,    0,   63,    2, 0x06 /* Public */,
       7,    0,   64,    2, 0x06 /* Public */,
       8,    2,   65,    2, 0x06 /* Public */,
      11,    1,   70,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    1,   73,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    9,   10,
    QMetaType::Void, QMetaType::QString,   12,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   10,

       0        // eod
};

void c2bCiterView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<c2bCiterView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->citeReferences(); break;
        case 1: _t->editReference(); break;
        case 2: _t->hideCiter(); break;
        case 3: _t->openAnnote(); break;
        case 4: _t->openFile(); break;
        case 5: _t->openUrl(); break;
        case 6: _t->patternFilterChanged((*reinterpret_cast< const bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 7: _t->statusMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->updatePatternFilter((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (c2bCiterView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c2bCiterView::citeReferences)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (c2bCiterView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c2bCiterView::editReference)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (c2bCiterView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c2bCiterView::hideCiter)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (c2bCiterView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c2bCiterView::openAnnote)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (c2bCiterView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c2bCiterView::openFile)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (c2bCiterView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c2bCiterView::openUrl)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (c2bCiterView::*)(const bool , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c2bCiterView::patternFilterChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (c2bCiterView::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c2bCiterView::statusMessage)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject c2bCiterView::staticMetaObject = { {
    QMetaObject::SuperData::link<QTableView::staticMetaObject>(),
    qt_meta_stringdata_c2bCiterView.data,
    qt_meta_data_c2bCiterView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *c2bCiterView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *c2bCiterView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_c2bCiterView.stringdata0))
        return static_cast<void*>(this);
    return QTableView::qt_metacast(_clname);
}

int c2bCiterView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableView::qt_metacall(_c, _id, _a);
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
void c2bCiterView::citeReferences()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void c2bCiterView::editReference()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void c2bCiterView::hideCiter()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void c2bCiterView::openAnnote()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void c2bCiterView::openFile()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void c2bCiterView::openUrl()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void c2bCiterView::patternFilterChanged(const bool _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void c2bCiterView::statusMessage(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
