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
    QByteArrayData data[29];
    char stringdata0[367];
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
QT_MOC_LITERAL(3, 20, 11), // "vectorInt64"
QT_MOC_LITERAL(4, 32, 14), // "vectorTimetags"
QT_MOC_LITERAL(5, 47, 10), // "vectorInt8"
QT_MOC_LITERAL(6, 58, 14), // "vectorChannels"
QT_MOC_LITERAL(7, 73, 7), // "tsvalid"
QT_MOC_LITERAL(8, 81, 9), // "qutaghist"
QT_MOC_LITERAL(9, 91, 12), // "vectorDouble"
QT_MOC_LITERAL(10, 104, 7), // "TTdata1"
QT_MOC_LITERAL(11, 112, 7), // "TTdata2"
QT_MOC_LITERAL(12, 120, 5), // "adqui"
QT_MOC_LITERAL(13, 126, 13), // "setHistograms"
QT_MOC_LITERAL(14, 140, 14), // "adqpausechange"
QT_MOC_LITERAL(15, 155, 5), // "chang"
QT_MOC_LITERAL(16, 161, 5), // "Break"
QT_MOC_LITERAL(17, 167, 9), // "filterset"
QT_MOC_LITERAL(18, 177, 19), // "Chang_in_binsinplot"
QT_MOC_LITERAL(19, 197, 3), // "val"
QT_MOC_LITERAL(20, 201, 18), // "Chang_in_histStart"
QT_MOC_LITERAL(21, 220, 16), // "Chang_in_histEnd"
QT_MOC_LITERAL(22, 237, 18), // "Chang_in_startChan"
QT_MOC_LITERAL(23, 256, 16), // "Chang_in_adqtime"
QT_MOC_LITERAL(24, 273, 18), // "Chang_in_PlotAChn1"
QT_MOC_LITERAL(25, 292, 18), // "Chang_in_PlotAChn2"
QT_MOC_LITERAL(26, 311, 18), // "Chang_in_PlotBChn1"
QT_MOC_LITERAL(27, 330, 18), // "Chang_in_PlotBChn2"
QT_MOC_LITERAL(28, 349, 17) // "Chang_anlAvilable"

    },
    "qutagadq\0dataready\0\0vectorInt64\0"
    "vectorTimetags\0vectorInt8\0vectorChannels\0"
    "tsvalid\0qutaghist\0vectorDouble\0TTdata1\0"
    "TTdata2\0adqui\0setHistograms\0adqpausechange\0"
    "chang\0Break\0filterset\0Chang_in_binsinplot\0"
    "val\0Chang_in_histStart\0Chang_in_histEnd\0"
    "Chang_in_startChan\0Chang_in_adqtime\0"
    "Chang_in_PlotAChn1\0Chang_in_PlotAChn2\0"
    "Chang_in_PlotBChn1\0Chang_in_PlotBChn2\0"
    "Chang_anlAvilable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qutagadq[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   99,    2, 0x06 /* Public */,
       8,    2,  106,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,  111,    2, 0x0a /* Public */,
      13,    0,  112,    2, 0x0a /* Public */,
      14,    1,  113,    2, 0x0a /* Public */,
      16,    0,  116,    2, 0x0a /* Public */,
      17,    0,  117,    2, 0x0a /* Public */,
      18,    1,  118,    2, 0x0a /* Public */,
      20,    1,  121,    2, 0x0a /* Public */,
      21,    1,  124,    2, 0x0a /* Public */,
      22,    1,  127,    2, 0x0a /* Public */,
      23,    1,  130,    2, 0x0a /* Public */,
      24,    1,  133,    2, 0x0a /* Public */,
      25,    1,  136,    2, 0x0a /* Public */,
      26,    1,  139,    2, 0x0a /* Public */,
      27,    1,  142,    2, 0x0a /* Public */,
      28,    1,  145,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, QMetaType::Int,    4,    6,    7,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 9,   10,   11,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Double,   19,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Bool,   19,

       0        // eod
};

void qutagadq::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<qutagadq *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dataready((*reinterpret_cast< const vectorInt64(*)>(_a[1])),(*reinterpret_cast< const vectorInt8(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->qutaghist((*reinterpret_cast< const vectorDouble(*)>(_a[1])),(*reinterpret_cast< const vectorDouble(*)>(_a[2]))); break;
        case 2: _t->adqui(); break;
        case 3: _t->setHistograms(); break;
        case 4: _t->adqpausechange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->Break(); break;
        case 6: { int _r = _t->filterset();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->Chang_in_binsinplot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->Chang_in_histStart((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->Chang_in_histEnd((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->Chang_in_startChan((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->Chang_in_adqtime((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->Chang_in_PlotAChn1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->Chang_in_PlotAChn2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->Chang_in_PlotBChn1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->Chang_in_PlotBChn2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->Chang_anlAvilable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (qutagadq::*)(const vectorInt64 & , const vectorInt8 & , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&qutagadq::dataready)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (qutagadq::*)(const vectorDouble & , const vectorDouble & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&qutagadq::qutaghist)) {
                *result = 1;
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
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void qutagadq::dataready(const vectorInt64 & _t1, const vectorInt8 & _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void qutagadq::qutaghist(const vectorDouble & _t1, const vectorDouble & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
