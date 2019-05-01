/****************************************************************************
** Meta object code from reading C++ file 'EntryUI.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../memoryAllocation/EntryUI.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EntryUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EntryUI_t {
    QByteArrayData data[19];
    char stringdata0[235];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EntryUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EntryUI_t qt_meta_stringdata_EntryUI = {
    {
QT_MOC_LITERAL(0, 0, 7), // "EntryUI"
QT_MOC_LITERAL(1, 8, 7), // "addHole"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 10), // "addProcess"
QT_MOC_LITERAL(4, 28, 10), // "addSegment"
QT_MOC_LITERAL(5, 39, 13), // "buttonClicked"
QT_MOC_LITERAL(6, 53, 15), // "ControlButtons*"
QT_MOC_LITERAL(7, 69, 12), // "sourceButton"
QT_MOC_LITERAL(8, 82, 15), // "startAllocation"
QT_MOC_LITERAL(9, 98, 15), // "processSelected"
QT_MOC_LITERAL(10, 114, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(11, 131, 15), // "selectedProcess"
QT_MOC_LITERAL(12, 147, 12), // "holeSelected"
QT_MOC_LITERAL(13, 160, 12), // "selectedHole"
QT_MOC_LITERAL(14, 173, 15), // "segmentSelected"
QT_MOC_LITERAL(15, 189, 15), // "selectedSegment"
QT_MOC_LITERAL(16, 205, 10), // "popSegment"
QT_MOC_LITERAL(17, 216, 7), // "popHole"
QT_MOC_LITERAL(18, 224, 10) // "popProcess"

    },
    "EntryUI\0addHole\0\0addProcess\0addSegment\0"
    "buttonClicked\0ControlButtons*\0"
    "sourceButton\0startAllocation\0"
    "processSelected\0QListWidgetItem*\0"
    "selectedProcess\0holeSelected\0selectedHole\0"
    "segmentSelected\0selectedSegment\0"
    "popSegment\0popHole\0popProcess"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EntryUI[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    1,   72,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    1,   76,    2, 0x08 /* Private */,
      12,    1,   79,    2, 0x08 /* Private */,
      14,    1,   82,    2, 0x08 /* Private */,
      16,    0,   85,    2, 0x08 /* Private */,
      17,    0,   86,    2, 0x08 /* Private */,
      18,    0,   87,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   13,
    QMetaType::Void, 0x80000000 | 10,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void EntryUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EntryUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addHole(); break;
        case 1: _t->addProcess(); break;
        case 2: _t->addSegment(); break;
        case 3: _t->buttonClicked((*reinterpret_cast< ControlButtons*(*)>(_a[1]))); break;
        case 4: _t->startAllocation(); break;
        case 5: _t->processSelected((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 6: _t->holeSelected((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 7: _t->segmentSelected((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 8: _t->popSegment(); break;
        case 9: _t->popHole(); break;
        case 10: _t->popProcess(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ControlButtons* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject EntryUI::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_EntryUI.data,
    qt_meta_data_EntryUI,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *EntryUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EntryUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EntryUI.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int EntryUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
