#include <QtNetwork>
#include "cocina.h"
#include "ui_cocina.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QScrollArea>
#include <QPushButton>
#include <QMessageBox>
#include <QComboBox>

cocina::cocina(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cocina)
    , networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    
    // Hacer los widgets scrolleables#include "cocina.h"
#include "ui_cocina.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QScrollArea>
#include <QPushButton>
#include <QMessageBox>
#include <QComboBox>
#include <QMouseEvent>

cocina::cocina(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cocina)
    , networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    
    setupScrollAreas();
    cargarPedidos();
    
    connect(&timerActualizacion, &QTimer::timeout, this, &cocina::cargarPedidos);
    timerActualizacion.start(30000);
}

cocina::~cocina()
{
    delete ui;
}

void cocina::setupScrollAreas()
{
    // Área de pedidos activos
    QScrollArea *scrollActivos = new QScrollArea(ui->widget_21);
    scrollActivos->setWidgetResizable(true);
    scrollActivos->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollActivos->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollActivos->setStyleSheet("QScrollArea { border: none; background-color: #EAEAEA; }");
    
    contenedorActivos = new QWidget();
    layoutActivos = new QVBoxLayout(contenedorActivos);
    layoutActivos->setSpacing(10);
    layoutActivos->setContentsMargins(9, 9, 9, 9);
    
    scrollActivos->setWidget(contenedorActivos);
    
    QVBoxLayout *layoutWidget21 = qobject_cast<QVBoxLayout*>(ui->widget_21->layout());
    if (layoutWidget21) {
        QLayoutItem *item;
        while ((item = layoutWidget21->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        layoutWidget21->addWidget(scrollActivos);
    }
    
    // Área de pedidos confirmados
    QScrollArea *scrollConfirmados = new QScrollArea(ui->widget_22);
    scrollConfirmados->setWidgetResizable(true);
    scrollConfirmados->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollConfirmados->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollConfirmados->setStyleSheet("QScrollArea { border: none; background-color: #EAEAEA; }");
    
    contenedorConfirmados = new QWidget();
    layoutConfirmados = new QVBoxLayout(contenedorConfirmados);
    layoutConfirmados->setSpacing(10);
    layoutConfirmados->setContentsMargins(9, 9, 9, 9);
    
    scrollConfirmados->setWidget(contenedorConfirmados);
    
    QVBoxLayout *layoutWidget22 = qobject_cast<QVBoxLayout*>(ui->widget_22->layout());
    if (layoutWidget22) {
        QLayoutItem *item;
        while ((item = layoutWidget22->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        layoutWidget22->addWidget(scrollConfirmados);
    }
}

void cocina::cargarPedidos()
{
    QNetworkRequest request(QUrl("http://localhost/dashboard/WEB_ElBuenGusto/escritorio/cocina.php"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    
    QNetworkReply *reply = networkManager->get(request);
    
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            procesarRespuesta(response);
        } else {
            QMessageBox::warning(this, "Error", "No se pudo conectar con el servidor: " + reply->errorString());
        }
        reply->deleteLater();
    });
}

void cocina::procesarRespuesta(const QByteArray &data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    
    if (!doc.isObject()) {
        return;
    }
    
    QJsonObject obj = doc.object();
    
    if (!obj["success"].toBool()) {
        QMessageBox::warning(this, "Error", obj["message"].toString());
        return;
    }
    
    repartidoresDisponibles = obj["repartidores_disponibles"].toArray();
    
    limpiarLayout(layoutActivos);
    limpiarLayout(layoutConfirmados);
    
    QJsonArray pedidosPendientes = obj["pedidos_pendientes"].toArray();
    for (const QJsonValue &value : pedidosPendientes) {
        QWidget *cardPedido = crearCardPedido(value.toObject(), false);
        layoutActivos->addWidget(cardPedido);
    }
    layoutActivos->addStretch();
    
    QJsonArray pedidosConfirmados = obj["pedidos_confirmados"].toArray();
    for (const QJsonValue &value : pedidosConfirmados) {
        QWidget *cardPedido = crearCardPedido(value.toObject(), true);
        layoutConfirmados->addWidget(cardPedido);
    }
    layoutConfirmados->addStretch();
}

QWidget* cocina::crearCardPedido(const QJsonObject &pedido, bool esConfirmado)
{
    QWidget *card = new QWidget();
    card->setMinimumHeight(160);
    card->setMaximumHeight(160);
    card->setStyleSheet("background-color: white; border-radius: 13px;");
    card->setCursor(Qt::PointingHandCursor);
    
    card->installEventFilter(this);
    card->setProperty("pedido_data", QVariant::fromValue(pedido));
    
    QVBoxLayout *layoutCard = new QVBoxLayout(card);
    
    // Header
    QWidget *headerWidget = new QWidget();
    headerWidget->setMaximumHeight(60);
    QHBoxLayout *headerLayout = new QHBoxLayout(headerWidget);
    
    QString nombreCompleto = pedido["cliente_nombre"].toString() + " " + pedido["cliente_apellido"].toString();
    QLabel *lblNombre = new QLabel(nombreCompleto);
    lblNombre->setStyleSheet("font-size: 16px;");
    headerLayout->addWidget(lblNombre);
    
    headerLayout->addStretch();
    
    if (esConfirmado) {
        QWidget *badgeEstado = new QWidget();
        badgeEstado->setMinimumHeight(30);
        badgeEstado->setMaximumHeight(30);
        badgeEstado->setStyleSheet("background-color: #E09225; border-radius: 13px; color: white; padding: 5px 10px;");
        QHBoxLayout *badgeLayout = new QHBoxLayout(badgeEstado);
        
        QString estadoTexto = pedido["estado"].toString() == "confirmado" ? "Confirmado" : "En proceso";
        QLabel *lblEstado = new QLabel(estadoTexto);
        badgeLayout->addWidget(lblEstado);
        
        headerLayout->addWidget(badgeEstado);
    }
    
    QString tipoPedido = pedido["tipo_pedido"].toString() == "programado" ? "Programado" : "Inmediato";
    QLabel *lblTipo = new QLabel(tipoPedido);
    lblTipo->setStyleSheet("color: #6B6B6B;");
    headerLayout->addWidget(lblTipo);
    
    layoutCard->addWidget(headerWidget);
    
    // Unidades
    QWidget *unidadesWidget = new QWidget();
    QVBoxLayout *unidadesLayout = new QVBoxLayout(unidadesWidget);
    QLabel *lblUnidades = new QLabel(QString::number(pedido["total_unidades"].toInt()) + " unidades");
    lblUnidades->setStyleSheet("color: #6B6B6B;");
    unidadesLayout->addWidget(lblUnidades);
    layoutCard->addWidget(unidadesWidget);
    
    // Footer
    QWidget *footerWidget = new QWidget();
    QHBoxLayout *footerLayout = new QHBoxLayout(footerWidget);
    
    QLabel *lblPrecio = new QLabel("$" + QString::number(pedido["total"].toDouble(), 'f', 2));
    lblPrecio->setStyleSheet("font-size: 16px;");
    footerLayout->addWidget(lblPrecio);
    
    footerLayout->addStretch();
    
    QLabel *lblNumero = new QLabel("#" + pedido["numero_pedido"].toString());
    lblNumero->setStyleSheet("font-size: 16px;");
    footerLayout->addWidget(lblNumero);
    
    layoutCard->addWidget(footerWidget);
    
    return card;
}

bool cocina::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QWidget *widget = qobject_cast<QWidget*>(obj);
        if (widget && widget->property("pedido_data").isValid()) {
            QJsonObject pedido = widget->property("pedido_data").toJsonObject();
            mostrarDetallePedido(pedido);
            return true;
        }
    }
    return QDialog::eventFilter(obj, event);
}

void cocina::mostrarDetallePedido(const QJsonObject &pedido)
{
    pedidoActual = pedido;
    
    QString nombreCompleto = pedido["cliente_nombre"].toString() + " " + pedido["cliente_apellido"].toString();
    ui->label_4->setText("Pedido de: " + nombreCompleto);
    
    QString tipoPedido = pedido["tipo_pedido"].toString() == "programado" ? "Programado" : "Inmediato";
    ui->label_5->setText(tipoPedido);
    
    ui->label_6->setText("Numero de pedido: " + pedido["numero_pedido"].toString());
    ui->label_7->setText(pedido["direccion_entrega"].toString());
    
    QVBoxLayout *layoutProductos = qobject_cast<QVBoxLayout*>(ui->widget_14->layout());
    if (layoutProductos) {
        QLayoutItem *item;
        while ((item = layoutProductos->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    } else {
        layoutProductos = new QVBoxLayout(ui->widget_14);
    }
    
    QJsonArray items = pedido["items"].toArray();
    for (const QJsonValue &itemValue : items) {
        QJsonObject item = itemValue.toObject();
        QWidget *productoWidget = crearWidgetProducto(item);
        layoutProductos->addWidget(productoWidget);
    }
    layoutProductos->addStretch();
    
    ui->label_22->setText("$" + QString::number(pedido["total"].toDouble(), 'f', 2));
    ui->label_16->setText(pedido["fecha_pedido"].toString());
    
    QString fechaEntrega = pedido["fecha_entrega_programada"].toString();
    if (fechaEntrega.isEmpty() || fechaEntrega == "null") {
        ui->label_18->setText("Entrega inmediata");
    } else {
        ui->label_18->setText(fechaEntrega);
    }
    
    cargarComboRepartidores();
}

QWidget* cocina::crearWidgetProducto(const QJsonObject &item)
{
    QWidget *widget = new QWidget();
    widget->setStyleSheet("background-color: white; border-radius: 8px;");
    widget->setMinimumHeight(120);
    
    QHBoxLayout *layout = new QHBoxLayout(widget);
    
    QLabel *lblImagen = new QLabel();
    lblImagen->setMaximumSize(130, 113);
    lblImagen->setStyleSheet("background-color: #EAEAEA; border-radius: 8px;");
    lblImagen->setText("Imagen");
    lblImagen->setAlignment(Qt::AlignCenter);
    layout->addWidget(lblImagen);
    
    QWidget *infoWidget = new QWidget();
    QVBoxLayout *infoLayout = new QVBoxLayout(infoWidget);
    
    QLabel *lblNombre = new QLabel(item["producto_nombre"].toString());
    lblNombre->setStyleSheet("font-size: 18px;");
    infoLayout->addWidget(lblNombre);
    
    QLabel *lblCantidad = new QLabel("Cantidad: " + QString::number(item["cantidad"].toInt()) + " unidades");
    lblCantidad->setStyleSheet("color: #6B6B6B;");
    infoLayout->addWidget(lblCantidad);
    
    QJsonArray condimentos = item["condimentos"].toArray();
    if (condimentos.size() > 0) {
        QString txtCondimentos = "Condimentos: ";
        for (int i = 0; i < condimentos.size(); i++) {
            if (i > 0) txtCondimentos += ", ";
            txtCondimentos += condimentos[i].toObject()["nombre"].toString();
        }
        QLabel *lblCondimentos = new QLabel(txtCondimentos);
        lblCondimentos->setStyleSheet("color: #6B6B6B;");
        infoLayout->addWidget(lblCondimentos);
    }
    
    QLabel *lblPrecio = new QLabel("Precio $" + QString::number(item["precio_total"].toDouble(), 'f', 2) + " ARS");
    infoLayout->addWidget(lblPrecio);
    
    layout->addWidget(infoWidget);
    
    return widget;
}

void cocina::cargarComboRepartidores()
{
    if (repartidoresDisponibles.size() > 0) {
        ui->label_19->setText("Repartidores disponibles: " + QString::number(repartidoresDisponibles.size()));
    } else {
        ui->label_19->setText("No hay repartidores disponibles");
    }
}

void cocina::confirmarPedido()
{
    QMessageBox::information(this, "Confirmar", "Pedido #" + pedidoActual["numero_pedido"].toString() + " confirmado");
}

void cocina::limpiarLayout(QVBoxLayout *layout)
{
    if (!layout) return;
    
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}
    setupScrollAreas();
    
    // Cargar datos iniciales
    cargarPedidos();
    
    // Actualizar cada 30 segundos
    connect(&timerActualizacion, &QTimer::timeout, this, &cocina::cargarPedidos);
    timerActualizacion.start(30000); // 30 segundos
}

cocina::~cocina()
{
    delete ui;
}

void cocina::setupScrollAreas()
{
    // Hacer scrolleable el área de pedidos activos (widget_21)
    QScrollArea *scrollActivos = new QScrollArea(ui->widget_21);
    scrollActivos->setWidgetResizable(true);
    scrollActivos->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollActivos->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollActivos->setStyleSheet("QScrollArea { border: none; background-color: #EAEAEA; }");
    
    contenedorActivos = new QWidget();
    layoutActivos = new QVBoxLayout(contenedorActivos);
    layoutActivos->setSpacing(10);
    layoutActivos->setContentsMargins(9, 9, 9, 9);
    
    scrollActivos->setWidget(contenedorActivos);
    
    QVBoxLayout *layoutWidget21 = qobject_cast<QVBoxLayout*>(ui->widget_21->layout());
    if (layoutWidget21) {
        // Limpiar layout existente
        QLayoutItem *item;
        while ((item = layoutWidget21->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        layoutWidget21->addWidget(scrollActivos);
    }
    
    // Hacer scrolleable el área de pedidos confirmados (widget_22)
    QScrollArea *scrollConfirmados = new QScrollArea(ui->widget_22);
    scrollConfirmados->setWidgetResizable(true);
    scrollConfirmados->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollConfirmados->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollConfirmados->setStyleSheet("QScrollArea { border: none; background-color: #EAEAEA; }");
    
    contenedorConfirmados = new QWidget();
    layoutConfirmados = new QVBoxLayout(contenedorConfirmados);
    layoutConfirmados->setSpacing(10);
    layoutConfirmados->setContentsMargins(9, 9, 9, 9);
    
    scrollConfirmados->setWidget(contenedorConfirmados);
    
    QVBoxLayout *layoutWidget22 = qobject_cast<QVBoxLayout*>(ui->widget_22->layout());
    if (layoutWidget22) {
        QLayoutItem *item;
        while ((item = layoutWidget22->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        layoutWidget22->addWidget(scrollConfirmados);
    }
}

void cocina::cargarPedidos()
{
    QNetworkRequest request(QUrl("http://localhost/dashboard/WEB_ElBuenGusto/escritorio/cocina.php"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    
    QNetworkReply *reply = networkManager->get(request);
    
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            procesarRespuesta(response);
        } else {
            QMessageBox::warning(this, "Error", "No se pudo conectar con el servidor: " + reply->errorString());
        }
        reply->deleteLater();
    });
}

void cocina::procesarRespuesta(const QByteArray &data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    
    if (!doc.isObject()) {
        return;
    }
    
    QJsonObject obj = doc.object();
    
    if (!obj["success"].toBool()) {
        QMessageBox::warning(this, "Error", obj["message"].toString());
        return;
    }
    
    // Guardar repartidores disponibles
    repartidoresDisponibles = obj["repartidores_disponibles"].toArray();
    
    // Limpiar layouts
    limpiarLayout(layoutActivos);
    limpiarLayout(layoutConfirmados);
    
    // Cargar pedidos pendientes
    QJsonArray pedidosPendientes = obj["pedidos_pendientes"].toArray();
    for (const QJsonValue &value : pedidosPendientes) {
        QWidget *cardPedido = crearCardPedido(value.toObject(), false);
        layoutActivos->addWidget(cardPedido);
    }
    layoutActivos->addStretch();
    
    // Cargar pedidos confirmados
    QJsonArray pedidosConfirmados = obj["pedidos_confirmados"].toArray();
    for (const QJsonValue &value : pedidosConfirmados) {
        QWidget *cardPedido = crearCardPedido(value.toObject(), true);
        layoutConfirmados->addWidget(cardPedido);
    }
    layoutConfirmados->addStretch();
}

QWidget* cocina::crearCardPedido(const QJsonObject &pedido, bool esConfirmado)
{
    QWidget *card = new QWidget();
    card->setMinimumHeight(160);
    card->setMaximumHeight(160);
    card->setStyleSheet("background-color: white; border-radius: 13px;");
    card->setCursor(Qt::PointingHandCursor);
    
    // Hacer clickeable
    card->installEventFilter(this);
    card->setProperty("pedido_data", QVariant::fromValue(pedido));
    
    QVBoxLayout *layoutCard = new QVBoxLayout(card);
    
    // Header con nombre y tipo
    QWidget *headerWidget = new QWidget();
    headerWidget->setMaximumHeight(60);
    QHBoxLayout *headerLayout = new QHBoxLayout(headerWidget);
    
    QString nombreCompleto = pedido["cliente_nombre"].toString() + " " + pedido["cliente_apellido"].toString();
    QLabel *lblNombre = new QLabel(nombreCompleto);
    lblNombre->setStyleSheet("font-size: 16px;");
    headerLayout->addWidget(lblNombre);
    
    headerLayout->addStretch();
    
    if (esConfirmado) {
        // Badge de estado
        QWidget *badgeEstado = new QWidget();
        badgeEstado->setMinimumHeight(30);
        badgeEstado->setMaximumHeight(30);
        badgeEstado->setStyleSheet("background-color: #E09225; border-radius: 13px; color: white; padding: 5px 10px;");
        QHBoxLayout *badgeLayout = new QHBoxLayout(badgeEstado);
        
        QString estadoTexto = pedido["estado"].toString() == "confirmado" ? "Confirmado" : "En proceso";
        QLabel *lblEstado = new QLabel(estadoTexto);
        badgeLayout->addWidget(lblEstado);
        
        headerLayout->addWidget(badgeEstado);
    }
    
    QString tipoPedido = pedido["tipo_pedido"].toString() == "programado" ? "Programado" : "Inmediato";
    QLabel *lblTipo = new QLabel(tipoPedido);
    lblTipo->setStyleSheet("color: #6B6B6B;");
    headerLayout->addWidget(lblTipo);
    
    layoutCard->addWidget(headerWidget);
    
    // Cantidad de unidades
    QWidget *unidadesWidget = new QWidget();
    QVBoxLayout *unidadesLayout = new QVBoxLayout(unidadesWidget);
    QLabel *lblUnidades = new QLabel(QString::number(pedido["total_unidades"].toInt()) + " unidades");
    lblUnidades->setStyleSheet("color: #6B6B6B;");
    unidadesLayout->addWidget(lblUnidades);
    layoutCard->addWidget(unidadesWidget);
    
    // Footer con precio y número
    QWidget *footerWidget = new QWidget();
    QHBoxLayout *footerLayout = new QHBoxLayout(footerWidget);
    
    QLabel *lblPrecio = new QLabel("$" + QString::number(pedido["total"].toDouble(), 'f', 2));
    lblPrecio->setStyleSheet("font-size: 16px;");
    footerLayout->addWidget(lblPrecio);
    
    footerLayout->addStretch();
    
    QLabel *lblNumero = new QLabel("#" + pedido["numero_pedido"].toString());
    lblNumero->setStyleSheet("font-size: 16px;");
    footerLayout->addWidget(lblNumero);
    
    layoutCard->addWidget(footerWidget);
    
    return card;
}

bool cocina::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QWidget *widget = qobject_cast<QWidget*>(obj);
        if (widget && widget->property("pedido_data").isValid()) {
            QJsonObject pedido = widget->property("pedido_data").toJsonObject();
            mostrarDetallePedido(pedido);
            return true;
        }
    }
    return QDialog::eventFilter(obj, event);
}

void cocina::mostrarDetallePedido(const QJsonObject &pedido)
{
    pedidoActual = pedido;
    
    // Actualizar header
    QString nombreCompleto = pedido["cliente_nombre"].toString() + " " + pedido["cliente_apellido"].toString();
    ui->label_4->setText("Pedido de: " + nombreCompleto);
    
    // Tipo de pedido
    QString tipoPedido = pedido["tipo_pedido"].toString() == "programado" ? "Programado" : "Inmediato";
    ui->label_5->setText(tipoPedido);
    
    // Número y dirección
    ui->label_6->setText("Numero de pedido: " + pedido["numero_pedido"].toString());
    ui->label_7->setText(pedido["direccion_entrega"].toString());
    
    // Limpiar productos anteriores
    QVBoxLayout *layoutProductos = qobject_cast<QVBoxLayout*>(ui->widget_14->layout());
    if (layoutProductos) {
        QLayoutItem *item;
        while ((item = layoutProductos->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    } else {
        layoutProductos = new QVBoxLayout(ui->widget_14);
    }
    
    // Agregar productos
    QJsonArray items = pedido["items"].toArray();
    for (const QJsonValue &itemValue : items) {
        QJsonObject item = itemValue.toObject();
        QWidget *productoWidget = crearWidgetProducto(item);
        layoutProductos->addWidget(productoWidget);
    }
    layoutProductos->addStretch();
    
    // Total
    ui->label_22->setText("$" + QString::number(pedido["total"].toDouble(), 'f', 2));
    
    // Fechas
    ui->label_16->setText(pedido["fecha_pedido"].toString());
    
    QString fechaEntrega = pedido["fecha_entrega_programada"].toString();
    if (fechaEntrega.isEmpty() || fechaEntrega == "null") {
        ui->label_18->setText("Entrega inmediata");
    } else {
        ui->label_18->setText(fechaEntrega);
    }
    
    // Cargar combo de repartidores
    cargarComboRepartidores();
    
    // Conectar botón confirmar
    connect(ui->widget_19, &QWidget::customContextMenuRequested, this, &cocina::confirmarPedido);
}

QWidget* cocina::crearWidgetProducto(const QJsonObject &item)
{
    QWidget *widget = new QWidget();
    widget->setStyleSheet("background-color: white; border-radius: 8px;");
    widget->setMinimumHeight(120);
    
    QHBoxLayout *layout = new QHBoxLayout(widget);
    
    // Imagen del producto (placeholder por ahora)
    QLabel *lblImagen = new QLabel();
    lblImagen->setMaximumSize(130, 113);
    lblImagen->setStyleSheet("background-color: #EAEAEA; border-radius: 8px;");
    lblImagen->setText("Imagen");
    lblImagen->setAlignment(Qt::AlignCenter);
    layout->addWidget(lblImagen);
    
    // Info del producto
    QWidget *infoWidget = new QWidget();
    QVBoxLayout *infoLayout = new QVBoxLayout(infoWidget);
    
    QLabel *lblNombre = new QLabel(item["producto_nombre"].toString());
    lblNombre->setStyleSheet("font-size: 18px;");
    infoLayout->addWidget(lblNombre);
    
    QLabel *lblCantidad = new QLabel("Cantidad: " + QString::number(item["cantidad"].toInt()) + " unidades");
    lblCantidad->setStyleSheet("color: #6B6B6B;");
    infoLayout->addWidget(lblCantidad);
    
    // Condimentos
    QJsonArray condimentos = item["condimentos"].toArray();
    if (condimentos.size() > 0) {
        QString txtCondimentos = "Condimentos: ";
        for (int i = 0; i < condimentos.size(); i++) {
            if (i > 0) txtCondimentos += ", ";
            txtCondimentos += condimentos[i].toObject()["nombre"].toString();
        }
        QLabel *lblCondimentos = new QLabel(txtCondimentos);
        lblCondimentos->setStyleSheet("color: #6B6B6B;");
        infoLayout->addWidget(lblCondimentos);
    }
    
    QLabel *lblPrecio = new QLabel("Precio $" + QString::number(item["precio_total"].toDouble(), 'f', 2) + " ARS");
    infoLayout->addWidget(lblPrecio);
    
    layout->addWidget(infoWidget);
    
    return widget;
}

void cocina::cargarComboRepartidores()
{
    // Aquí deberías reemplazar el QLabel por un QComboBox
    // Por ahora solo actualizamos el texto
    if (repartidoresDisponibles.size() > 0) {
        ui->label_19->setText("Repartidores disponibles: " + QString::number(repartidoresDisponibles.size()));
    } else {
        ui->label_19->setText("No hay repartidores disponibles");
    }
}

void cocina::confirmarPedido()
{
    // Implementar lógica de confirmación
    QMessageBox::information(this, "Confirmar", "Pedido #" + pedidoActual["numero_pedido"].toString() + " confirmado");
}

void cocina::limpiarLayout(QVBoxLayout *layout)
{
    if (!layout) return;
    
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}
