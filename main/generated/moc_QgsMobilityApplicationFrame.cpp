/****************************************************************************
** Meta object code from reading C++ file 'QgsMobilityApplicationFrame.h'
**
** Created: Thu Feb 7 16:52:05 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/QgsMobilityApplicationFrame.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QgsMobilityApplicationFrame.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QgsMobilityApplicationFrame[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      33,   29,   28,   28, 0x0a,
      59,   28,   28,   28, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QgsMobilityApplicationFrame[] = {
    "QgsMobilityApplicationFrame\0\0doc\0"
    "readProject(QDomDocument)\0updateRotate()\0"
};

void QgsMobilityApplicationFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QgsMobilityApplicationFrame *_t = static_cast<QgsMobilityApplicationFrame *>(_o);
        switch (_id) {
        case 0: _t->readProject((*reinterpret_cast< const QDomDocument(*)>(_a[1]))); break;
        case 1: _t->updateRotate(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QgsMobilityApplicationFrame::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QgsMobilityApplicationFrame::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_QgsMobilityApplicationFrame,
      qt_meta_data_QgsMobilityApplicationFrame, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QgsMobilityApplicationFrame::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QgsMobilityApplicationFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QgsMobilityApplicationFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QgsMobilityApplicationFrame))
        return static_cast<void*>(const_cast< QgsMobilityApplicationFrame*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int QgsMobilityApplicationFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
