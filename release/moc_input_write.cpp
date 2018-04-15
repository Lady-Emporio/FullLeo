/****************************************************************************
** Meta object code from reading C++ file 'input_write.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../act/write/input_write.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'input_write.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TableWrite_t {
    QByteArrayData data[3];
    char stringdata0[32];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TableWrite_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TableWrite_t qt_meta_stringdata_TableWrite = {
    {
QT_MOC_LITERAL(0, 0, 10), // "TableWrite"
QT_MOC_LITERAL(1, 11, 19), // "singal_needNexRound"
QT_MOC_LITERAL(2, 31, 0) // ""

    },
    "TableWrite\0singal_needNexRound\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TableWrite[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void TableWrite::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TableWrite *_t = static_cast<TableWrite *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->singal_needNexRound(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TableWrite::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TableWrite::singal_needNexRound)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject TableWrite::staticMetaObject = {
    { &QTableWidget::staticMetaObject, qt_meta_stringdata_TableWrite.data,
      qt_meta_data_TableWrite,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TableWrite::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TableWrite::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TableWrite.stringdata0))
        return static_cast<void*>(const_cast< TableWrite*>(this));
    return QTableWidget::qt_metacast(_clname);
}

int TableWrite::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void TableWrite::singal_needNexRound()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
struct qt_meta_stringdata_InputWrite_t {
    QByteArrayData data[3];
    char stringdata0[37];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_InputWrite_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_InputWrite_t qt_meta_stringdata_InputWrite = {
    {
QT_MOC_LITERAL(0, 0, 10), // "InputWrite"
QT_MOC_LITERAL(1, 11, 24), // "connectNextRound_trigger"
QT_MOC_LITERAL(2, 36, 0) // ""

    },
    "InputWrite\0connectNextRound_trigger\0"
    ""
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_InputWrite[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void InputWrite::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        InputWrite *_t = static_cast<InputWrite *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectNextRound_trigger(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject InputWrite::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_InputWrite.data,
      qt_meta_data_InputWrite,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *InputWrite::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InputWrite::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_InputWrite.stringdata0))
        return static_cast<void*>(const_cast< InputWrite*>(this));
    return QWidget::qt_metacast(_clname);
}

int InputWrite::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_OneTableOneRow_t {
    QByteArrayData data[4];
    char stringdata0[52];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OneTableOneRow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OneTableOneRow_t qt_meta_stringdata_OneTableOneRow = {
    {
QT_MOC_LITERAL(0, 0, 14), // "OneTableOneRow"
QT_MOC_LITERAL(1, 15, 19), // "singal_needNexRound"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 15) // "singal_nextWord"

    },
    "OneTableOneRow\0singal_needNexRound\0\0"
    "singal_nextWord"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OneTableOneRow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,
       3,    0,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void OneTableOneRow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OneTableOneRow *_t = static_cast<OneTableOneRow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->singal_needNexRound(); break;
        case 1: _t->singal_nextWord(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (OneTableOneRow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OneTableOneRow::singal_needNexRound)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (OneTableOneRow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OneTableOneRow::singal_nextWord)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject OneTableOneRow::staticMetaObject = {
    { &QTableWidget::staticMetaObject, qt_meta_stringdata_OneTableOneRow.data,
      qt_meta_data_OneTableOneRow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *OneTableOneRow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OneTableOneRow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_OneTableOneRow.stringdata0))
        return static_cast<void*>(const_cast< OneTableOneRow*>(this));
    return QTableWidget::qt_metacast(_clname);
}

int OneTableOneRow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void OneTableOneRow::singal_needNexRound()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void OneTableOneRow::singal_nextWord()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
struct qt_meta_stringdata_OneLongRowTable_t {
    QByteArrayData data[4];
    char stringdata0[67];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OneLongRowTable_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OneLongRowTable_t qt_meta_stringdata_OneLongRowTable = {
    {
QT_MOC_LITERAL(0, 0, 15), // "OneLongRowTable"
QT_MOC_LITERAL(1, 16, 24), // "connectNextRound_trigger"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 24) // "connectNext_Word_trigger"

    },
    "OneLongRowTable\0connectNextRound_trigger\0"
    "\0connectNext_Word_trigger"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OneLongRowTable[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void OneLongRowTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OneLongRowTable *_t = static_cast<OneLongRowTable *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectNextRound_trigger(); break;
        case 1: _t->connectNext_Word_trigger(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject OneLongRowTable::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_OneLongRowTable.data,
      qt_meta_data_OneLongRowTable,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *OneLongRowTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OneLongRowTable::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_OneLongRowTable.stringdata0))
        return static_cast<void*>(const_cast< OneLongRowTable*>(this));
    return QWidget::qt_metacast(_clname);
}

int OneLongRowTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
