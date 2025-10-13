/****************************************************************************
** Meta object code from reading C++ file 'confirmacion_pedido.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../confirmacion_pedido.h"
#include <QtGui/qtextcursor.h>
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'confirmacion_pedido.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN18ConfirmacionPedidoE_t {};
} // unnamed namespace

template <> constexpr inline auto ConfirmacionPedido::qt_create_metaobjectdata<qt_meta_tag_ZN18ConfirmacionPedidoE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ConfirmacionPedido",
        "pedidoConfirmado",
        "",
        "pedidoId",
        "volverAlCarrito",
        "errorEnPedido",
        "mensaje",
        "validarFormulario",
        "calcularCostoDelivery",
        "toggleTipoPedido",
        "toggleMetodoPago",
        "confirmarPedido",
        "volverCarrito",
        "onDireccionChanged",
        "validarCamposObligatorios",
        "procesarRespuestaConfirmacion",
        "QNetworkReply*",
        "reply"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'pedidoConfirmado'
        QtMocHelpers::SignalData<void(int)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Signal 'volverAlCarrito'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'errorEnPedido'
        QtMocHelpers::SignalData<void(const QString &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Slot 'validarFormulario'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'calcularCostoDelivery'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'toggleTipoPedido'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'toggleMetodoPago'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'confirmarPedido'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'volverCarrito'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onDireccionChanged'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'validarCamposObligatorios'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'procesarRespuestaConfirmacion'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(15, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 16, 17 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ConfirmacionPedido, qt_meta_tag_ZN18ConfirmacionPedidoE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ConfirmacionPedido::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18ConfirmacionPedidoE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18ConfirmacionPedidoE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN18ConfirmacionPedidoE_t>.metaTypes,
    nullptr
} };

void ConfirmacionPedido::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ConfirmacionPedido *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->pedidoConfirmado((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->volverAlCarrito(); break;
        case 2: _t->errorEnPedido((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->validarFormulario(); break;
        case 4: _t->calcularCostoDelivery(); break;
        case 5: _t->toggleTipoPedido(); break;
        case 6: _t->toggleMetodoPago(); break;
        case 7: _t->confirmarPedido(); break;
        case 8: _t->volverCarrito(); break;
        case 9: _t->onDireccionChanged(); break;
        case 10: _t->validarCamposObligatorios(); break;
        case 11: _t->procesarRespuestaConfirmacion((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QNetworkReply* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ConfirmacionPedido::*)(int )>(_a, &ConfirmacionPedido::pedidoConfirmado, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ConfirmacionPedido::*)()>(_a, &ConfirmacionPedido::volverAlCarrito, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ConfirmacionPedido::*)(const QString & )>(_a, &ConfirmacionPedido::errorEnPedido, 2))
            return;
    }
}

const QMetaObject *ConfirmacionPedido::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConfirmacionPedido::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18ConfirmacionPedidoE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ConfirmacionPedido::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void ConfirmacionPedido::pedidoConfirmado(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void ConfirmacionPedido::volverAlCarrito()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ConfirmacionPedido::errorEnPedido(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}
QT_WARNING_POP
