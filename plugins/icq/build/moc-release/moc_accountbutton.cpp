/****************************************************************************
** Meta object code from reading C++ file 'accountbutton.h'
**
** Created: Mon Feb 9 20:46:50 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../accountbutton.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'accountbutton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_accountButton[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_accountButton[] = {
    "accountButton\0"
};

const QMetaObject accountButton::staticMetaObject = {
    { &QToolButton::staticMetaObject, qt_meta_stringdata_accountButton,
      qt_meta_data_accountButton, 0 }
};

const QMetaObject *accountButton::metaObject() const
{
    return &staticMetaObject;
}

void *accountButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_accountButton))
	return static_cast<void*>(const_cast< accountButton*>(this));
    return QToolButton::qt_metacast(_clname);
}

int accountButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
