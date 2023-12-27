/****************************************************************************
** Meta object code from reading C++ file 'c2bWebBrowser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "qweb/kit/c2bWebBrowser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'c2bWebBrowser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_c2bWebBrowser_t {
    QByteArrayData data[19];
    char stringdata0[163];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_c2bWebBrowser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_c2bWebBrowser_t qt_meta_stringdata_c2bWebBrowser = {
    {
QT_MOC_LITERAL(0, 0, 13), // "c2bWebBrowser"
QT_MOC_LITERAL(1, 14, 13), // "statusMessage"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 2), // "ms"
QT_MOC_LITERAL(4, 32, 8), // "loadPage"
QT_MOC_LITERAL(5, 41, 5), // "p_url"
QT_MOC_LITERAL(6, 47, 12), // "setFixedFont"
QT_MOC_LITERAL(7, 60, 5), // "qfont"
QT_MOC_LITERAL(8, 66, 7), // "setFont"
QT_MOC_LITERAL(9, 74, 11), // "setHomePage"
QT_MOC_LITERAL(10, 86, 6), // "hp_url"
QT_MOC_LITERAL(11, 93, 4), // "copy"
QT_MOC_LITERAL(12, 98, 4), // "home"
QT_MOC_LITERAL(13, 103, 6), // "zoomIn"
QT_MOC_LITERAL(14, 110, 7), // "zoomOut"
QT_MOC_LITERAL(15, 118, 17), // "_set_window_title"
QT_MOC_LITERAL(16, 136, 9), // "pagetitle"
QT_MOC_LITERAL(17, 146, 11), // "linkHovered"
QT_MOC_LITERAL(18, 158, 4) // "link"

    },
    "c2bWebBrowser\0statusMessage\0\0ms\0"
    "loadPage\0p_url\0setFixedFont\0qfont\0"
    "setFont\0setHomePage\0hp_url\0copy\0home\0"
    "zoomIn\0zoomOut\0_set_window_title\0"
    "pagetitle\0linkHovered\0link"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_c2bWebBrowser[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   72,    2, 0x0a /* Public */,
       6,    1,   75,    2, 0x0a /* Public */,
       8,    1,   78,    2, 0x0a /* Public */,
       9,    1,   81,    2, 0x0a /* Public */,
      11,    0,   84,    2, 0x09 /* Protected */,
      12,    0,   85,    2, 0x09 /* Protected */,
      13,    0,   86,    2, 0x09 /* Protected */,
      14,    0,   87,    2, 0x09 /* Protected */,
      15,    1,   88,    2, 0x08 /* Private */,
      17,    1,   91,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QFont,    7,
    QMetaType::Void, QMetaType::QFont,    7,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   18,

       0        // eod
};

void c2bWebBrowser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<c2bWebBrowser *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->statusMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->loadPage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->setFixedFont((*reinterpret_cast< const QFont(*)>(_a[1]))); break;
        case 3: _t->setFont((*reinterpret_cast< const QFont(*)>(_a[1]))); break;
        case 4: _t->setHomePage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->copy(); break;
        case 6: _t->home(); break;
        case 7: _t->zoomIn(); break;
        case 8: _t->zoomOut(); break;
        case 9: _t->_set_window_title((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->linkHovered((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (c2bWebBrowser::*)(const QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c2bWebBrowser::statusMessage)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject c2bWebBrowser::staticMetaObject = { {
    QMetaObject::SuperData::link<QWebView::staticMetaObject>(),
    qt_meta_stringdata_c2bWebBrowser.data,
    qt_meta_data_c2bWebBrowser,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *c2bWebBrowser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *c2bWebBrowser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_c2bWebBrowser.stringdata0))
        return static_cast<void*>(this);
    return QWebView::qt_metacast(_clname);
}

int c2bWebBrowser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWebView::qt_metacall(_c, _id, _a);
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
void c2bWebBrowser::statusMessage(const QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
