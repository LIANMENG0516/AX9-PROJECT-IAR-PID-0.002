/****************************************************************************
** Meta object code from reading C++ file 'serialportthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../serialportthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serialportthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SerialPortThread_t {
    QByteArrayData data[5];
    char stringdata0[71];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SerialPortThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SerialPortThread_t qt_meta_stringdata_SerialPortThread = {
    {
QT_MOC_LITERAL(0, 0, 16), // "SerialPortThread"
QT_MOC_LITERAL(1, 17, 14), // "serialPortData"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 18), // "readSerialPortSlot"
QT_MOC_LITERAL(4, 52, 18) // "sendReadVolCmdSlot"

    },
    "SerialPortThread\0serialPortData\0\0"
    "readSerialPortSlot\0sendReadVolCmdSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SerialPortThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   32,    2, 0x0a /* Public */,
       4,    0,   33,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SerialPortThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SerialPortThread *_t = static_cast<SerialPortThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->serialPortData((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->readSerialPortSlot(); break;
        case 2: _t->sendReadVolCmdSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SerialPortThread::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SerialPortThread::serialPortData)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject SerialPortThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_SerialPortThread.data,
      qt_meta_data_SerialPortThread,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SerialPortThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SerialPortThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SerialPortThread.stringdata0))
        return static_cast<void*>(const_cast< SerialPortThread*>(this));
    return QThread::qt_metacast(_clname);
}

int SerialPortThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void SerialPortThread::serialPortData(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
