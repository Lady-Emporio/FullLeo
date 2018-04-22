/****************************************************************************
** Meta object code from reading C++ file 'error_count.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../backend/error_count.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'error_count.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ErrorCount_t {
    QByteArrayData data[6];
    char stringdata0[105];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ErrorCount_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ErrorCount_t qt_meta_stringdata_ErrorCount = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ErrorCount"
QT_MOC_LITERAL(1, 11, 21), // "connectUpdate_trigger"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 29), // "connectAccept_changes_trigger"
QT_MOC_LITERAL(4, 64, 23), // "slotCustomMenuRequested"
QT_MOC_LITERAL(5, 88, 16) // "slotRemoveRecord"

    },
    "ErrorCount\0connectUpdate_trigger\0\0"
    "connectAccept_changes_trigger\0"
    "slotCustomMenuRequested\0slotRemoveRecord"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ErrorCount[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x0a /* Public */,
       4,    1,   36,    2, 0x0a /* Public */,
       5,    0,   39,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void,

       0        // eod
};

void ErrorCount::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ErrorCount *_t = static_cast<ErrorCount *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectUpdate_trigger(); break;
        case 1: _t->connectAccept_changes_trigger(); break;
        case 2: _t->slotCustomMenuRequested((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 3: _t->slotRemoveRecord(); break;
        default: ;
        }
    }
}

const QMetaObject ErrorCount::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ErrorCount.data,
      qt_meta_data_ErrorCount,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ErrorCount::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ErrorCount::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ErrorCount.stringdata0))
        return static_cast<void*>(const_cast< ErrorCount*>(this));
    return QWidget::qt_metacast(_clname);
}

int ErrorCount::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
