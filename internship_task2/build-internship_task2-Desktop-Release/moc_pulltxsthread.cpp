/****************************************************************************
** Meta object code from reading C++ file 'pulltxsthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../pulltxsthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pulltxsthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PullTXsThread_t {
    QByteArrayData data[5];
    char stringdata0[51];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PullTXsThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PullTXsThread_t qt_meta_stringdata_PullTXsThread = {
    {
QT_MOC_LITERAL(0, 0, 13), // "PullTXsThread"
QT_MOC_LITERAL(1, 14, 14), // "upd_gui_signal"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 10), // "pass_error"
QT_MOC_LITERAL(4, 41, 9) // "pass_info"

    },
    "PullTXsThread\0upd_gui_signal\0\0pass_error\0"
    "pass_info"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PullTXsThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,
       3,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Double,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void PullTXsThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PullTXsThread *_t = static_cast<PullTXsThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->upd_gui_signal((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const double(*)>(_a[2]))); break;
        case 1: _t->pass_error((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->pass_info((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PullTXsThread::*_t)(const QString & , const double & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PullTXsThread::upd_gui_signal)) {
                *result = 0;
            }
        }
        {
            typedef void (PullTXsThread::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PullTXsThread::pass_error)) {
                *result = 1;
            }
        }
        {
            typedef void (PullTXsThread::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PullTXsThread::pass_info)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject PullTXsThread::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PullTXsThread.data,
      qt_meta_data_PullTXsThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PullTXsThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PullTXsThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PullTXsThread.stringdata0))
        return static_cast<void*>(const_cast< PullTXsThread*>(this));
    return QObject::qt_metacast(_clname);
}

int PullTXsThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void PullTXsThread::upd_gui_signal(const QString & _t1, const double & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PullTXsThread::pass_error(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PullTXsThread::pass_info(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
