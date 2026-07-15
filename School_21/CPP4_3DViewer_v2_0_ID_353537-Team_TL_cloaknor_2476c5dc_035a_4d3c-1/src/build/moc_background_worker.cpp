/****************************************************************************
** Meta object code from reading C++ file 'background_worker.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../view/background_worker.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'background_worker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_s21__BackgroundWorker_t {
    uint offsetsAndSizes[40];
    char stringdata0[22];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[6];
    char stringdata4[6];
    char stringdata5[17];
    char stringdata6[7];
    char stringdata7[14];
    char stringdata8[10];
    char stringdata9[5];
    char stringdata10[10];
    char stringdata11[2];
    char stringdata12[2];
    char stringdata13[2];
    char stringdata14[12];
    char stringdata15[9];
    char stringdata16[9];
    char stringdata17[9];
    char stringdata18[11];
    char stringdata19[6];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_s21__BackgroundWorker_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_s21__BackgroundWorker_t qt_meta_stringdata_s21__BackgroundWorker = {
    {
        QT_MOC_LITERAL(0, 21),  // "s21::BackgroundWorker"
        QT_MOC_LITERAL(22, 11),  // "ModelLoaded"
        QT_MOC_LITERAL(34, 0),  // ""
        QT_MOC_LITERAL(35, 5),  // "Scene"
        QT_MOC_LITERAL(41, 5),  // "scene"
        QT_MOC_LITERAL(47, 16),  // "SceneTransformed"
        QT_MOC_LITERAL(64, 6),  // "Failed"
        QT_MOC_LITERAL(71, 13),  // "error_message"
        QT_MOC_LITERAL(85, 9),  // "LoadModel"
        QT_MOC_LITERAL(95, 4),  // "path"
        QT_MOC_LITERAL(100, 9),  // "MoveScene"
        QT_MOC_LITERAL(110, 1),  // "x"
        QT_MOC_LITERAL(112, 1),  // "y"
        QT_MOC_LITERAL(114, 1),  // "z"
        QT_MOC_LITERAL(116, 11),  // "RotateScene"
        QT_MOC_LITERAL(128, 8),  // "x_degree"
        QT_MOC_LITERAL(137, 8),  // "y_degree"
        QT_MOC_LITERAL(146, 8),  // "z_degree"
        QT_MOC_LITERAL(155, 10),  // "ScaleScene"
        QT_MOC_LITERAL(166, 5)   // "scale"
    },
    "s21::BackgroundWorker",
    "ModelLoaded",
    "",
    "Scene",
    "scene",
    "SceneTransformed",
    "Failed",
    "error_message",
    "LoadModel",
    "path",
    "MoveScene",
    "x",
    "y",
    "z",
    "RotateScene",
    "x_degree",
    "y_degree",
    "z_degree",
    "ScaleScene",
    "scale"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_s21__BackgroundWorker[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   56,    2, 0x06,    1 /* Public */,
       5,    1,   59,    2, 0x06,    3 /* Public */,
       6,    1,   62,    2, 0x06,    5 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       8,    1,   65,    2, 0x0a,    7 /* Public */,
      10,    4,   68,    2, 0x0a,    9 /* Public */,
      14,    4,   77,    2, 0x0a,   14 /* Public */,
      18,    2,   86,    2, 0x0a,   19 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Double, QMetaType::Double, QMetaType::Double,    4,   11,   12,   13,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Double, QMetaType::Double, QMetaType::Double,    4,   15,   16,   17,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Double,    4,   19,

       0        // eod
};

Q_CONSTINIT const QMetaObject s21::BackgroundWorker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_s21__BackgroundWorker.offsetsAndSizes,
    qt_meta_data_s21__BackgroundWorker,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_s21__BackgroundWorker_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<BackgroundWorker, std::true_type>,
        // method 'ModelLoaded'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Scene, std::false_type>,
        // method 'SceneTransformed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Scene, std::false_type>,
        // method 'Failed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'LoadModel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'MoveScene'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Scene, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'RotateScene'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Scene, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'ScaleScene'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Scene, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>
    >,
    nullptr
} };

void s21::BackgroundWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BackgroundWorker *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ModelLoaded((*reinterpret_cast< std::add_pointer_t<Scene>>(_a[1]))); break;
        case 1: _t->SceneTransformed((*reinterpret_cast< std::add_pointer_t<Scene>>(_a[1]))); break;
        case 2: _t->Failed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->LoadModel((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->MoveScene((*reinterpret_cast< std::add_pointer_t<Scene>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[4]))); break;
        case 5: _t->RotateScene((*reinterpret_cast< std::add_pointer_t<Scene>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[4]))); break;
        case 6: _t->ScaleScene((*reinterpret_cast< std::add_pointer_t<Scene>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BackgroundWorker::*)(Scene );
            if (_t _q_method = &BackgroundWorker::ModelLoaded; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BackgroundWorker::*)(Scene );
            if (_t _q_method = &BackgroundWorker::SceneTransformed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (BackgroundWorker::*)(QString );
            if (_t _q_method = &BackgroundWorker::Failed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *s21::BackgroundWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *s21::BackgroundWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_s21__BackgroundWorker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int s21::BackgroundWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void s21::BackgroundWorker::ModelLoaded(Scene _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void s21::BackgroundWorker::SceneTransformed(Scene _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void s21::BackgroundWorker::Failed(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
