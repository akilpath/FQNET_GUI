/****************************************************************************
** Meta object code from reading C++ file 'qutag_anl.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../source/qutag_anl.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qutag_anl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_qutaganl_t {
    QByteArrayData data[8];
    char stringdata0[66];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_qutaganl_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_qutaganl_t qt_meta_stringdata_qutaganl = {
    {
QT_MOC_LITERAL(0, 0, 8), // "qutaganl"
QT_MOC_LITERAL(1, 9, 9), // "inputdata"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 10), // "timetagsPP"
QT_MOC_LITERAL(4, 31, 6), // "TTdata"
QT_MOC_LITERAL(5, 38, 13), // "channelsTDCPP"
QT_MOC_LITERAL(6, 52, 6), // "CHdata"
QT_MOC_LITERAL(7, 59, 6) // "nevent"

    },
    "qutaganl\0inputdata\0\0timetagsPP\0TTdata\0"
    "channelsTDCPP\0CHdata\0nevent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qutaganl[] = {

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
       1,    3,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, QMetaType::Int,    4,    6,    7,

       0        // eod
};

void qutaganl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<qutaganl *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->inputdata((*reinterpret_cast< const timetagsPP(*)>(_a[1])),(*reinterpret_cast< const channelsTDCPP(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject qutaganl::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_qutaganl.data,
    qt_meta_data_qutaganl,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *qutaganl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qutaganl::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_qutaganl.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int qutaganl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
