/****************************************************************************
** Meta object code from reading C++ file 'deletecontactdialog.h'
**
** Created: Mon Feb 9 20:47:00 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../deletecontactdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'deletecontactdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_deleteContactDialog[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_deleteContactDialog[] = {
    "deleteContactDialog\0"
};

const QMetaObject deleteContactDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_deleteContactDialog,
      qt_meta_data_deleteContactDialog, 0 }
};

const QMetaObject *deleteContactDialog::metaObject() const
{
    return &staticMetaObject;
}

void *deleteContactDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_deleteContactDialog))
	return static_cast<void*>(const_cast< deleteContactDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int deleteContactDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
