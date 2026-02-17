/****************************************************************************
** Meta object code from reading C++ file 'camwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../camwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'camwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CamWindow_t {
    QByteArrayData data[17];
    char stringdata0[189];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CamWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CamWindow_t qt_meta_stringdata_CamWindow = {
    {
QT_MOC_LITERAL(0, 0, 9), // "CamWindow"
QT_MOC_LITERAL(1, 10, 9), // "OpenAlbum"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 10), // "Return2Cam"
QT_MOC_LITERAL(4, 32, 15), // "ShowPreviousPic"
QT_MOC_LITERAL(5, 48, 11), // "ShowNextPic"
QT_MOC_LITERAL(6, 60, 13), // "onFreshCurImg"
QT_MOC_LITERAL(7, 74, 3), // "img"
QT_MOC_LITERAL(8, 78, 12), // "CamOpenError"
QT_MOC_LITERAL(9, 91, 13), // "SavePic2Album"
QT_MOC_LITERAL(10, 105, 11), // "StopShowPic"
QT_MOC_LITERAL(11, 117, 9), // "DeletePic"
QT_MOC_LITERAL(12, 127, 11), // "RecordVideo"
QT_MOC_LITERAL(13, 139, 12), // "PlayRecVideo"
QT_MOC_LITERAL(14, 152, 12), // "VideoPlayEnd"
QT_MOC_LITERAL(15, 165, 11), // "RotateLabel"
QT_MOC_LITERAL(16, 177, 11) // "rotate_flag"

    },
    "CamWindow\0OpenAlbum\0\0Return2Cam\0"
    "ShowPreviousPic\0ShowNextPic\0onFreshCurImg\0"
    "img\0CamOpenError\0SavePic2Album\0"
    "StopShowPic\0DeletePic\0RecordVideo\0"
    "PlayRecVideo\0VideoPlayEnd\0RotateLabel\0"
    "rotate_flag"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CamWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    1,   83,    2, 0x08 /* Private */,
       8,    0,   86,    2, 0x08 /* Private */,
       9,    0,   87,    2, 0x08 /* Private */,
      10,    0,   88,    2, 0x08 /* Private */,
      11,    0,   89,    2, 0x08 /* Private */,
      12,    0,   90,    2, 0x08 /* Private */,
      13,    0,   91,    2, 0x08 /* Private */,
      14,    0,   92,    2, 0x08 /* Private */,
      15,    1,   93,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   16,

       0        // eod
};

void CamWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CamWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OpenAlbum(); break;
        case 1: _t->Return2Cam(); break;
        case 2: _t->ShowPreviousPic(); break;
        case 3: _t->ShowNextPic(); break;
        case 4: _t->onFreshCurImg((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 5: _t->CamOpenError(); break;
        case 6: _t->SavePic2Album(); break;
        case 7: _t->StopShowPic(); break;
        case 8: _t->DeletePic(); break;
        case 9: _t->RecordVideo(); break;
        case 10: _t->PlayRecVideo(); break;
        case 11: _t->VideoPlayEnd(); break;
        case 12: _t->RotateLabel((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CamWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CamWindow.data,
    qt_meta_data_CamWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CamWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CamWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CamWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CamWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
