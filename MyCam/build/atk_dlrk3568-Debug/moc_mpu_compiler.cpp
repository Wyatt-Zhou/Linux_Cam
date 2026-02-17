/****************************************************************************
** Meta object code from reading C++ file 'mpu_compiler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../mpu_compiler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mpu_compiler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MPU_CompilerWorker_t {
    QByteArrayData data[13];
    char stringdata0[160];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MPU_CompilerWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MPU_CompilerWorker_t qt_meta_stringdata_MPU_CompilerWorker = {
    {
QT_MOC_LITERAL(0, 0, 18), // "MPU_CompilerWorker"
QT_MOC_LITERAL(1, 19, 11), // "resultReady"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 6), // "result"
QT_MOC_LITERAL(4, 39, 14), // "sigRotatelabel"
QT_MOC_LITERAL(5, 54, 11), // "rotate_flag"
QT_MOC_LITERAL(6, 66, 6), // "doWork"
QT_MOC_LITERAL(7, 73, 9), // "arguments"
QT_MOC_LITERAL(8, 83, 16), // "compilerFinished"
QT_MOC_LITERAL(9, 100, 8), // "exitCode"
QT_MOC_LITERAL(10, 109, 20), // "QProcess::ExitStatus"
QT_MOC_LITERAL(11, 130, 10), // "exitStatus"
QT_MOC_LITERAL(12, 141, 18) // "readStandardOutput"

    },
    "MPU_CompilerWorker\0resultReady\0\0result\0"
    "sigRotatelabel\0rotate_flag\0doWork\0"
    "arguments\0compilerFinished\0exitCode\0"
    "QProcess::ExitStatus\0exitStatus\0"
    "readStandardOutput"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MPU_CompilerWorker[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   45,    2, 0x0a /* Public */,
       8,    2,   48,    2, 0x08 /* Private */,
      12,    0,   53,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Bool,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QStringList,    7,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10,    9,   11,
    QMetaType::Void,

       0        // eod
};

void MPU_CompilerWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MPU_CompilerWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resultReady((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->sigRotatelabel((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->doWork((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 3: _t->compilerFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 4: _t->readStandardOutput(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MPU_CompilerWorker::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MPU_CompilerWorker::resultReady)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MPU_CompilerWorker::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MPU_CompilerWorker::sigRotatelabel)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MPU_CompilerWorker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MPU_CompilerWorker.data,
    qt_meta_data_MPU_CompilerWorker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MPU_CompilerWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MPU_CompilerWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MPU_CompilerWorker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MPU_CompilerWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void MPU_CompilerWorker::resultReady(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MPU_CompilerWorker::sigRotatelabel(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_MPU_CompilerController_t {
    QByteArrayData data[7];
    char stringdata0[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MPU_CompilerController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MPU_CompilerController_t qt_meta_stringdata_MPU_CompilerController = {
    {
QT_MOC_LITERAL(0, 0, 22), // "MPU_CompilerController"
QT_MOC_LITERAL(1, 23, 7), // "operate"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 14), // "threadFinished"
QT_MOC_LITERAL(4, 47, 13), // "sigSendRotate"
QT_MOC_LITERAL(5, 61, 13), // "handleResults"
QT_MOC_LITERAL(6, 75, 12) // "handleRotate"

    },
    "MPU_CompilerController\0operate\0\0"
    "threadFinished\0sigSendRotate\0handleResults\0"
    "handleRotate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MPU_CompilerController[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       3,    0,   42,    2, 0x06 /* Public */,
       4,    1,   43,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   46,    2, 0x08 /* Private */,
       6,    1,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QStringList,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

void MPU_CompilerController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MPU_CompilerController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->operate((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 1: _t->threadFinished(); break;
        case 2: _t->sigSendRotate((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 3: _t->handleResults((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->handleRotate((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MPU_CompilerController::*)(const QStringList & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MPU_CompilerController::operate)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MPU_CompilerController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MPU_CompilerController::threadFinished)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MPU_CompilerController::*)(const bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MPU_CompilerController::sigSendRotate)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MPU_CompilerController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MPU_CompilerController.data,
    qt_meta_data_MPU_CompilerController,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MPU_CompilerController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MPU_CompilerController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MPU_CompilerController.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MPU_CompilerController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void MPU_CompilerController::operate(const QStringList & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MPU_CompilerController::threadFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MPU_CompilerController::sigSendRotate(const bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
