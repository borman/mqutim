/****************************************************************************
** Meta object code from reading C++ file 'joinconferenceform.h'
**
** Created: Sun Feb 15 15:02:21 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/conference/joinconferenceform.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'joinconferenceform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_JoinConferenceForm[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_JoinConferenceForm[] = {
    "JoinConferenceForm\0\0on_joinButton_clicked()\0"
};

const QMetaObject JoinConferenceForm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_JoinConferenceForm,
      qt_meta_data_JoinConferenceForm, 0 }
};

const QMetaObject *JoinConferenceForm::metaObject() const
{
    return &staticMetaObject;
}

void *JoinConferenceForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_JoinConferenceForm))
	return static_cast<void*>(const_cast< JoinConferenceForm*>(this));
    return QWidget::qt_metacast(_clname);
}

int JoinConferenceForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_joinButton_clicked(); break;
        }
        _id -= 1;
    }
    return _id;
}