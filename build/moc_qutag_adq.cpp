/****************************************************************************
** Meta object code from reading C++ file 'qutag_adq.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../source/qutag_adq.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qutag_adq.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_qutagadq_t {
    QByteArrayData data[10];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_qutagadq_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_qutagadq_t qt_meta_stringdata_qutagadq = {
    {
QT_MOC_LITERAL(0, 0, 8), // "qutagadq"
QT_MOC_LITERAL(1, 9, 9), // "dataready"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 10), // "timetagsPP"
QT_MOC_LITERAL(4, 31, 6), // "TTdata"
QT_MOC_LITERAL(5, 38, 13), // "channelsTDCPP"
QT_MOC_LITERAL(6, 52, 6), // "CHdata"
QT_MOC_LITERAL(7, 59, 6), // "nevent"
QT_MOC_LITERAL(8, 66, 5), // "adqui"
QT_MOC_LITERAL(9, 72, 11) // "clockchange"

    },
    "qutagadq\0dataready\0\0timetagsPP\0TTdata\0"
    "channelsTDCPP\0CHdata\0nevent\0adqui\0"
    "clockchange"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qutagadq[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   36,    2, 0x0a /* Public */,
       9,    1,   37,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, QMetaType::Int,    4,    6,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void qutagadq::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<qutagadq *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dataready((*reinterpret_cast< const timetagsPP(*)>(_a[1])),(*reinterpret_cast< const channelsTDCPP(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->adqui(); break;
        case 2: _t->clockchange((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (qutagadq::*)(const timetagsPP & , const channelsTDCPP & , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&qutagadq::dataready)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject qutagadq::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_qutagadq.data,
    qt_meta_data_qutagadq,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *qutagadq::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qutagadq::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_qutagadq.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int qutagadq::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void qutagadq::dataready(const timetagsPP & _t1, const channelsTDCPP & _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
