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
    QByteArrayData data[12];
    char stringdata0[253];
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
QT_MOC_LITERAL(4, 64, 19), // "connect_UpdateTable"
QT_MOC_LITERAL(5, 84, 28), // "connect_TextChanged_FindWord"
QT_MOC_LITERAL(6, 113, 11), // "currentText"
QT_MOC_LITERAL(7, 125, 27), // "connect_FROM_FINDER_trigger"
QT_MOC_LITERAL(8, 153, 28), // "connect_SORT_list_db_trigger"
QT_MOC_LITERAL(9, 182, 24), // "connect_Word_shift_right"
QT_MOC_LITERAL(10, 207, 23), // "connect_Word_shift_left"
QT_MOC_LITERAL(11, 231, 21) // "connect_NeedReplaceDB"

    },
    "ListWordDB\0connect_IN_bd_trigger\0\0"
    "connect_FROM_NEW_LISR_trigger\0"
    "connect_UpdateTable\0connect_TextChanged_FindWord\0"
    "currentText\0connect_FROM_FINDER_trigger\0"
    "connect_SORT_list_db_trigger\0"
    "connect_Word_shift_right\0"
    "connect_Word_shift_left\0connect_NeedReplaceDB"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ListWordDB[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x08 /* Private */,
       3,    2,   64,    2, 0x08 /* Private */,
       4,    0,   69,    2, 0x08 /* Private */,
       5,    1,   70,    2, 0x08 /* Private */,
       7,    2,   73,    2, 0x08 /* Private */,
       8,    1,   78,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
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
        case 3: _t->connect_TextChanged_FindWord((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->connect_FROM_FINDER_trigger((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->connect_SORT_list_db_trigger((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->connect_Word_shift_right(); break;
        case 7: _t->connect_Word_shift_left(); break;
        case 8: _t->connect_NeedReplaceDB(); break;
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
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
