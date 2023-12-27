/****************************************************************************
** Meta object code from reading C++ file 'findDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "findDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'findDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_findDialog_t {
    QByteArrayData data[12];
    char stringdata0[104];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_findDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_findDialog_t qt_meta_stringdata_findDialog = {
    {
QT_MOC_LITERAL(0, 0, 10), // "findDialog"
QT_MOC_LITERAL(1, 11, 4), // "exec"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 8), // "findNext"
QT_MOC_LITERAL(4, 26, 12), // "findPrevious"
QT_MOC_LITERAL(5, 39, 8), // "findText"
QT_MOC_LITERAL(6, 48, 9), // "setEditor"
QT_MOC_LITERAL(7, 58, 15), // "QPlainTextEdit*"
QT_MOC_LITERAL(8, 74, 6), // "editor"
QT_MOC_LITERAL(9, 81, 10), // "QTextEdit*"
QT_MOC_LITERAL(10, 92, 4), // "show"
QT_MOC_LITERAL(11, 97, 6) // "accept"

    },
    "findDialog\0exec\0\0findNext\0findPrevious\0"
    "findText\0setEditor\0QPlainTextEdit*\0"
    "editor\0QTextEdit*\0show\0accept"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_findDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    0,   55,    2, 0x0a /* Public */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    1,   58,    2, 0x0a /* Public */,
       6,    1,   61,    2, 0x0a /* Public */,
      10,    0,   64,    2, 0x0a /* Public */,
      11,    0,   65,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 9,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void findDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<findDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: { int _r = _t->exec();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->findNext(); break;
        case 2: _t->findPrevious(); break;
        case 3: _t->findText(); break;
        case 4: _t->setEditor((*reinterpret_cast< QPlainTextEdit*(*)>(_a[1]))); break;
        case 5: _t->setEditor((*reinterpret_cast< QTextEdit*(*)>(_a[1]))); break;
        case 6: _t->show(); break;
        case 7: _t->accept(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject findDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_findDialog.data,
    qt_meta_data_findDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *findDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *findDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_findDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int findDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
