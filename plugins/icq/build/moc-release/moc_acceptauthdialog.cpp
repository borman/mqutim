/****************************************************************************
** Meta object code from reading C++ file 'acceptauthdialog.h'
**
** Created: Sat Feb 14 22:20:17 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../acceptauthdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'acceptauthdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_acceptAuthDialog[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      20,   18,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      52,   17,   17,   17, 0x08,
      78,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_acceptAuthDialog[] = {
    "acceptAuthDialog\0\0,\0sendAuthReqAnswer(bool,QString)\0"
    "on_acceptButton_clicked()\0"
    "on_declineButton_clicked()\0"
};

const QMetaObject acceptAuthDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_acceptAuthDialog,
      qt_meta_data_acceptAuthDialog, 0 }
};

const QMetaObject *acceptAuthDialog::metaObject() const
{
    return &staticMetaObject;
}

void *acceptAuthDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_acceptAuthDialog))
	return static_cast<void*>(const_cast< acceptAuthDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int acceptAuthDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sendAuthReqAnswer((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: on_acceptButton_clicked(); break;
        case 2: on_declineButton_clicked(); break;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void acceptAuthDialog::sendAuthReqAnswer(bool _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}