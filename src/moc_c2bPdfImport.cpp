/****************************************************************************
** Meta object code from reading C++ file 'c2bPdfImport.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "c2bPdfImport.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'c2bPdfImport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_c2bPdfImport_t {
    QByteArrayData data[21];
    char stringdata0[227];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_c2bPdfImport_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_c2bPdfImport_t qt_meta_stringdata_c2bPdfImport = {
    {
QT_MOC_LITERAL(0, 0, 12), // "c2bPdfImport"
QT_MOC_LITERAL(1, 13, 13), // "fileProcessed"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 8), // "filename"
QT_MOC_LITERAL(4, 37, 20), // "saveReferenceRequest"
QT_MOC_LITERAL(5, 58, 20), // "setClipboardDisabled"
QT_MOC_LITERAL(6, 79, 7), // "disable"
QT_MOC_LITERAL(7, 87, 13), // "textProcessed"
QT_MOC_LITERAL(8, 101, 4), // "text"
QT_MOC_LITERAL(9, 106, 11), // "processNext"
QT_MOC_LITERAL(10, 118, 17), // "referenceExtacted"
QT_MOC_LITERAL(11, 136, 6), // "status"
QT_MOC_LITERAL(12, 143, 4), // "show"
QT_MOC_LITERAL(13, 148, 11), // "showMessage"
QT_MOC_LITERAL(14, 160, 2), // "ms"
QT_MOC_LITERAL(15, 163, 5), // "abort"
QT_MOC_LITERAL(16, 169, 4), // "help"
QT_MOC_LITERAL(17, 174, 12), // "loadSettings"
QT_MOC_LITERAL(18, 187, 14), // "processOneFile"
QT_MOC_LITERAL(19, 202, 12), // "saveSettings"
QT_MOC_LITERAL(20, 215, 11) // "selectFiles"

    },
    "c2bPdfImport\0fileProcessed\0\0filename\0"
    "saveReferenceRequest\0setClipboardDisabled\0"
    "disable\0textProcessed\0text\0processNext\0"
    "referenceExtacted\0status\0show\0showMessage\0"
    "ms\0abort\0help\0loadSettings\0processOneFile\0"
    "saveSettings\0selectFiles"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_c2bPdfImport[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       4,    0,   87,    2, 0x06 /* Public */,
       5,    1,   88,    2, 0x06 /* Public */,
       7,    1,   91,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   94,    2, 0x0a /* Public */,
      10,    1,   95,    2, 0x0a /* Public */,
      12,    0,   98,    2, 0x0a /* Public */,
      13,    1,   99,    2, 0x0a /* Public */,
      15,    0,  102,    2, 0x08 /* Private */,
      16,    0,  103,    2, 0x08 /* Private */,
      17,    0,  104,    2, 0x08 /* Private */,
      18,    0,  105,    2, 0x08 /* Private */,
      19,    0,  106,    2, 0x08 /* Private */,
      20,    0,  107,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::QString,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void c2bPdfImport::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<c2bPdfImport *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->fileProcessed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->saveReferenceRequest(); break;
        case 2: _t->setClipboardDisabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->textProcessed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->processNext(); break;
        case 5: _t->referenceExtacted((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->show(); break;
        case 7: _t->showMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->abort(); break;
        case 9: _t->help(); break;
        case 10: _t->loadSettings(); break;
        case 11: _t->processOneFile(); break;
        case 12: _t->saveSettings(); break;
        case 13: _t->selectFiles(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (c2bPdfImport::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c2bPdfImport::fileProcessed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (c2bPdfImport::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c2bPdfImport::saveReferenceRequest)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (c2bPdfImport::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c2bPdfImport::setClipboardDisabled)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (c2bPdfImport::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c2bPdfImport::textProcessed)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject c2bPdfImport::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_c2bPdfImport.data,
    qt_meta_data_c2bPdfImport,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *c2bPdfImport::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *c2bPdfImport::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_c2bPdfImport.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int c2bPdfImport::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void c2bPdfImport::fileProcessed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void c2bPdfImport::saveReferenceRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void c2bPdfImport::setClipboardDisabled(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void c2bPdfImport::textProcessed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
