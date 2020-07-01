/****************************************************************************
** Meta object code from reading C++ file 'dbcontrol.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../source/dbcontrol.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dbcontrol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DBControl_t {
    QByteArrayData data[22];
    char stringdata0[139];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DBControl_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DBControl_t qt_meta_stringdata_DBControl = {
    {
QT_MOC_LITERAL(0, 0, 9), // "DBControl"
QT_MOC_LITERAL(1, 10, 13), // "SaveAndValues"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 4), // "and1"
QT_MOC_LITERAL(4, 30, 4), // "and2"
QT_MOC_LITERAL(5, 35, 4), // "and3"
QT_MOC_LITERAL(6, 40, 6), // "orgate"
QT_MOC_LITERAL(7, 47, 4), // "bsm1"
QT_MOC_LITERAL(8, 52, 4), // "bsm2"
QT_MOC_LITERAL(9, 57, 7), // "andTime"
QT_MOC_LITERAL(10, 65, 9), // "delayline"
QT_MOC_LITERAL(11, 75, 14), // "SaveRateValues"
QT_MOC_LITERAL(12, 90, 3), // "Ra1"
QT_MOC_LITERAL(13, 94, 3), // "Ra2"
QT_MOC_LITERAL(14, 98, 3), // "Ra3"
QT_MOC_LITERAL(15, 102, 3), // "Rb1"
QT_MOC_LITERAL(16, 106, 3), // "Rb2"
QT_MOC_LITERAL(17, 110, 3), // "Rb3"
QT_MOC_LITERAL(18, 114, 3), // "Rc1"
QT_MOC_LITERAL(19, 118, 3), // "Rc2"
QT_MOC_LITERAL(20, 122, 3), // "Rc3"
QT_MOC_LITERAL(21, 126, 12) // "hist_adqtime"

    },
    "DBControl\0SaveAndValues\0\0and1\0and2\0"
    "and3\0orgate\0bsm1\0bsm2\0andTime\0delayline\0"
    "SaveRateValues\0Ra1\0Ra2\0Ra3\0Rb1\0Rb2\0"
    "Rb3\0Rc1\0Rc2\0Rc3\0hist_adqtime"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DBControl[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    8,   24,    2, 0x0a /* Public */,
      11,   10,   41,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Float, QMetaType::Int,    3,    4,    5,    6,    7,    8,    9,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Float,   12,   13,   14,   15,   16,   17,   18,   19,   20,   21,

       0        // eod
};

void DBControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DBControl *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SaveAndValues((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< float(*)>(_a[7])),(*reinterpret_cast< int(*)>(_a[8]))); break;
        case 1: _t->SaveRateValues((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7])),(*reinterpret_cast< int(*)>(_a[8])),(*reinterpret_cast< int(*)>(_a[9])),(*reinterpret_cast< float(*)>(_a[10]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DBControl::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_DBControl.data,
    qt_meta_data_DBControl,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DBControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DBControl::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DBControl.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int DBControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
