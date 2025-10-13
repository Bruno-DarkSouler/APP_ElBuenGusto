/****************************************************************************
** Meta object code from reading C++ file 'cajero.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../cajero.h"
#include <QtGui/qtextcursor.h>
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cajero.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN11PanelCajeroE_t {};
} // unnamed namespace

template <> constexpr inline auto PanelCajero::qt_create_metaobjectdata<qt_meta_tag_ZN11PanelCajeroE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PanelCajero",
        "buscarCliente",
        "",
        "limpiarBusquedaCliente",
        "mostrarFormularioNuevoCliente",
        "guardarNuevoCliente",
        "filtrarProductos",
        "buscarProductoPorNombre",
        "agregarProductoAlCarrito",
        "productoId",
        "eliminarDelCarrito",
        "index",
        "modificarCantidad",
        "nuevaCantidad",
        "actualizarTotales",
        "toggleTipoPedido",
        "crearPedido",
        "procesarRespuestaCajero",
        "QNetworkReply*",
        "reply",
        "actualizarReloj",
        "onCategoriaChanged",
        "on_timeEdit_hora_userTimeChanged",
        "hora"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'buscarCliente'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'limpiarBusquedaCliente'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'mostrarFormularioNuevoCliente'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'guardarNuevoCliente'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'filtrarProductos'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'buscarProductoPorNombre'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'agregarProductoAlCarrito'
        QtMocHelpers::SlotData<void(int)>(8, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 9 },
        }}),
        // Slot 'eliminarDelCarrito'
        QtMocHelpers::SlotData<void(int)>(10, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 11 },
        }}),
        // Slot 'modificarCantidad'
        QtMocHelpers::SlotData<void(int, int)>(12, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 11 }, { QMetaType::Int, 13 },
        }}),
        // Slot 'actualizarTotales'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'toggleTipoPedido'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'crearPedido'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'procesarRespuestaCajero'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(17, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 18, 19 },
        }}),
        // Slot 'actualizarReloj'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onCategoriaChanged'
        QtMocHelpers::SlotData<void(int)>(21, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 11 },
        }}),
        // Slot 'on_timeEdit_hora_userTimeChanged'
        QtMocHelpers::SlotData<void(const QTime &)>(22, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QTime, 23 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PanelCajero, qt_meta_tag_ZN11PanelCajeroE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PanelCajero::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11PanelCajeroE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11PanelCajeroE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11PanelCajeroE_t>.metaTypes,
    nullptr
} };

void PanelCajero::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PanelCajero *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->buscarCliente(); break;
        case 1: _t->limpiarBusquedaCliente(); break;
        case 2: _t->mostrarFormularioNuevoCliente(); break;
        case 3: _t->guardarNuevoCliente(); break;
        case 4: _t->filtrarProductos(); break;
        case 5: _t->buscarProductoPorNombre(); break;
        case 6: _t->agregarProductoAlCarrito((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->eliminarDelCarrito((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->modificarCantidad((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 9: _t->actualizarTotales(); break;
        case 10: _t->toggleTipoPedido(); break;
        case 11: _t->crearPedido(); break;
        case 12: _t->procesarRespuestaCajero((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 13: _t->actualizarReloj(); break;
        case 14: _t->onCategoriaChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 15: _t->on_timeEdit_hora_userTimeChanged((*reinterpret_cast< std::add_pointer_t<QTime>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QNetworkReply* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *PanelCajero::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PanelCajero::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11PanelCajeroE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PanelCajero::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
