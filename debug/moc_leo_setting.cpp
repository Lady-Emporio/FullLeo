/****************************************************************************
** Meta object code from reading C++ file 'leo_setting.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../backend/leo_setting.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'leo_setting.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Settings_t {
    QByteArrayData data[14];
    char stringdata0[249];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Settings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Settings_t qt_meta_stringdata_Settings = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Settings"
QT_MOC_LITERAL(1, 9, 16), // "connectIntFromDB"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 15), // "connectPathToDB"
QT_MOC_LITERAL(4, 43, 15), // "connectFontSize"
QT_MOC_LITERAL(5, 59, 17), // "connectFontFamily"
QT_MOC_LITERAL(6, 77, 15), // "connectRowTable"
QT_MOC_LITERAL(7, 93, 15), // "connectColTable"
QT_MOC_LITERAL(8, 109, 18), // "connectALG_trigger"
QT_MOC_LITERAL(9, 128, 24), // "connectStyleJson_trigger"
QT_MOC_LITERAL(10, 153, 29), // "connectAUTOCOMPLETION_trigger"
QT_MOC_LITERAL(11, 183, 19), // "connectJUMP_trigger"
QT_MOC_LITERAL(12, 203, 20), // "connectAudio_trigger"
QT_MOC_LITERAL(13, 224, 24) // "connectGRIDTABLE_trigger"

    },
    "Settings\0connectIntFromDB\0\0connectPathToDB\0"
    "connectFontSize\0connectFontFamily\0"
    "connectRowTable\0connectColTable\0"
    "connectALG_trigger\0connectStyleJson_trigger\0"
    "connectAUTOCOMPLETION_trigger\0"
    "connectJUMP_trigger\0connectAudio_trigger\0"
    "connectGRIDTABLE_trigger"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Settings[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x08 /* Private */,
       3,    1,   77,    2, 0x08 /* Private */,
       4,    1,   80,    2, 0x08 /* Private */,
       5,    1,   83,    2, 0x08 /* Private */,
       6,    1,   86,    2, 0x08 /* Private */,
       7,    1,   89,    2, 0x08 /* Private */,
       8,    1,   92,    2, 0x08 /* Private */,
       9,    1,   95,    2, 0x08 /* Private */,
      10,    0,   98,    2, 0x08 /* Private */,
      11,    0,   99,    2, 0x08 /* Private */,
      12,    0,  100,    2, 0x08 /* Private */,
      13,    0,  101,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Settings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Settings *_t = static_cast<Settings *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectIntFromDB((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->connectPathToDB((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->connectFontSize((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->connectFontFamily((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->connectRowTable((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->connectColTable((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->connectALG_trigger((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->connectStyleJson_trigger((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->connectAUTOCOMPLETION_trigger(); break;
        case 9: _t->connectJUMP_trigger(); break;
        case 10: _t->connectAudio_trigger(); break;
        case 11: _t->connectGRIDTABLE_trigger(); break;
        default: ;
        }
    }
}

const QMetaObject Settings::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Settings.data,
      qt_meta_data_Settings,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Settings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Settings::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Settings.stringdata0))
        return static_cast<void*>(const_cast< Settings*>(this));
    return QWidget::qt_metacast(_clname);
}

int Settings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
