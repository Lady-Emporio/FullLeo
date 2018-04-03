/****************************************************************************
** Meta object code from reading C++ file 'list_word_db.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../backend/list_word_db.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'list_word_db.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ListWordDB_t {
    QByteArrayData data[5];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ListWordDB_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ListWordDB_t qt_meta_stringdata_ListWordDB = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ListWordDB"
QT_MOC_LITERAL(1, 11, 21), // "connect_IN_bd_trigger"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 29), // "connect_FROM_NEW_LISR_trigger"
QT_MOC_LITERAL(4, 64, 19) // "connect_UpdateTable"

    },
    "ListWordDB\0connect_IN_bd_trigger\0\0"
    "connect_FROM_NEW_LISR_trigger\0"
    "connect_UpdateTable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ListWordDB[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x08 /* Private */,
       3,    2,   34,    2, 0x08 /* Private */,
       4,    0,   39,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,

       0        // eod
};

void ListWordDB::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ListWordDB *_t = static_cast<ListWordDB *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connect_IN_bd_trigger((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->connect_FROM_NEW_LISR_trigger((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->connect_UpdateTable(); break;
        default: ;
        }
    }
}

const QMetaObject ListWordDB::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ListWordDB.data,
      qt_meta_data_ListWordDB,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ListWordDB::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ListWordDB::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ListWordDB.stringdata0))
        return static_cast<void*>(const_cast< ListWordDB*>(this));
    return QWidget::qt_metacast(_clname);
}

int ListWordDB::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
