/****************************************************************************
** Meta object code from reading C++ file 'network_player.h'
**
** Created: Wed Jul 21 14:25:51 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "network_player.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'network_player.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Network_Player[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,
      27,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      44,   15,   15,   15, 0x08,
      60,   15,   15,   15, 0x08,
      76,   15,   15,   15, 0x08,
      96,   15,   15,   15, 0x08,
     122,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Network_Player[] = {
    "Network_Player\0\0giveMuve()\0conectComplite()\0"
    "slotReadyRead()\0slotConnected()\0"
    "slotNewConnection()\0processPendingDatagrams()\0"
    "processPendingDatagramsinput()\0"
};

const QMetaObject Network_Player::staticMetaObject = {
    { &Player::staticMetaObject, qt_meta_stringdata_Network_Player,
      qt_meta_data_Network_Player, 0 }
};

const QMetaObject *Network_Player::metaObject() const
{
    return &staticMetaObject;
}

void *Network_Player::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Network_Player))
        return static_cast<void*>(const_cast< Network_Player*>(this));
    return Player::qt_metacast(_clname);
}

int Network_Player::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Player::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: giveMuve(); break;
        case 1: conectComplite(); break;
        case 2: slotReadyRead(); break;
        case 3: slotConnected(); break;
        case 4: slotNewConnection(); break;
        case 5: processPendingDatagrams(); break;
        case 6: processPendingDatagramsinput(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Network_Player::giveMuve()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Network_Player::conectComplite()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
