#include "cocina.h"
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
#include <QGraphicsDropShadowEffect>

cocina::cocina(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cocina)
    , networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

    setupScrollAreas();
    cargarPedidos();

    // Conectar botón de confirmar pedido
    connect(ui->widget_19, &QWidget::customContextMenuRequested, this, &cocina::confirmarPedido);
    ui->widget_19->installEventFilter(this);
    ui->widget_19->setProperty("es_boton_confirmar", true);
    ui->widget_19->setCursor(Qt::PointingHandCursor);

    connect(&timerActualizacion, &QTimer::timeout, this, &cocina::cargarPedidos);
    timerActualizacion.start(30000);
}

cocina::~cocina()
{
    delete ui;
}

void cocina::setupScrollAreas()
{
    // Área de pedidos activos (widget_21)
    QScrollArea *scrollActivos = new QScrollArea(ui->widget_21);
    scrollActivos->setWidgetResizable(true);
    scrollActivos->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollActivos->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollActivos->setStyleSheet("QScrollArea { border: none; background-color: #EAEAEA; }");

    contenedorActivos = new QWidget();
    layoutActivos = new QVBoxLayout(contenedorActivos);
    layoutActivos->setSpacing(10);
    layoutActivos->setContentsMargins(9, 9, 9, 9);
    layoutActivos->setAlignment(Qt::AlignTop);

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

    // Área de pedidos confirmados (widget_22)
    QScrollArea *scrollConfirmados = new QScrollArea(ui->widget_22);
    scrollConfirmados->setWidgetResizable(true);
    scrollConfirmados->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollConfirmados->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollConfirmados->setStyleSheet("QScrollArea { border: none; background-color: #EAEAEA; }");

    contenedorConfirmados = new QWidget();
    layoutConfirmados = new QVBoxLayout(contenedorConfirmados);
    layoutConfirmados->setSpacing(10);
    layoutConfirmados->setContentsMargins(9, 9, 9, 9);
    layoutConfirmados->setAlignment(Qt::AlignTop);

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
    QNetworkRequest request(QUrl("http://elbuengusto.shop/api/cocina.php"));
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

    // Pedidos pendientes van al widget_21
    QJsonArray pedidosPendientes = obj["pedidos_pendientes"].toArray();
    for (const QJsonValue &value : pedidosPendientes) {
        QJsonObject pedido = value.toObject();
        if (pedido["estado"].toString() == "pendiente") {
            QWidget *cardPedido = crearCardPedido(pedido, false);
            layoutActivos->addWidget(cardPedido);
        }
    }

    // Pedidos confirmados y en_proceso van al widget_22
    QJsonArray pedidosConfirmados = obj["pedidos_confirmados"].toArray();
    for (const QJsonValue &value : pedidosConfirmados) {
        QJsonObject pedido = value.toObject();
        QString estado = pedido["estado"].toString();
        if (estado == "confirmado" || estado == "en_proceso") {
            QWidget *cardPedido = crearCardPedido(pedido, true);
            layoutConfirmados->addWidget(cardPedido);
        }
    }
}

QWidget* cocina::crearCardPedido(const QJsonObject &pedido, bool esConfirmado)
{
    QWidget *card = new QWidget();
    card->setMinimumHeight(160);
    card->setMaximumHeight(160);
    card->setStyleSheet(
        "QWidget { "
        "background-color: white; "
        "border-radius: 13px; "
        "}"
        );
    card->setCursor(Qt::PointingHandCursor);
    card->setProperty("hover_state", false);
    card->setProperty("es_card_pedido", true);

    // Agregar efecto de sombra
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(10);
    shadow->setColor(QColor(0, 0, 0, 30));
    shadow->setOffset(0, 2);
    card->setGraphicsEffect(shadow);

    card->installEventFilter(this);
    card->setProperty("pedido_data", QVariant::fromValue(pedido));

    QVBoxLayout *layoutCard = new QVBoxLayout(card);
    layoutCard->setContentsMargins(15, 10, 15, 10);

    // Header
    QWidget *headerWidget = new QWidget();
    headerWidget->setMaximumHeight(60);
    QHBoxLayout *headerLayout = new QHBoxLayout(headerWidget);
    headerLayout->setContentsMargins(0, 0, 0, 0);

    QString nombreCompleto = pedido["cliente_nombre"].toString() + " " + pedido["cliente_apellido"].toString();
    QLabel *lblNombre = new QLabel(nombreCompleto);
    lblNombre->setStyleSheet("font-size: 16px; font-weight: bold;");
    headerLayout->addWidget(lblNombre);

    headerLayout->addStretch();

    if (esConfirmado) {
        QWidget *badgeEstado = new QWidget();
        badgeEstado->setMinimumHeight(30);
        badgeEstado->setMaximumHeight(30);

        QString estado = pedido["estado"].toString();
        QString colorBadge = estado == "en_proceso" ? "#E09225" : "#27AE60";
        QString estadoTexto = estado == "en_proceso" ? "En proceso" : "Confirmado";

        badgeEstado->setStyleSheet(QString(
                                       "background-color: %1; "
                                       "border-radius: 13px; "
                                       "color: white; "
                                       "padding: 5px 10px;"
                                       ).arg(colorBadge));

        QHBoxLayout *badgeLayout = new QHBoxLayout(badgeEstado);
        badgeLayout->setContentsMargins(10, 5, 10, 5);

        QLabel *lblEstado = new QLabel(estadoTexto);
        lblEstado->setStyleSheet("font-size: 12px; font-weight: bold;");
        badgeLayout->addWidget(lblEstado);

        headerLayout->addWidget(badgeEstado);
    }

    QString tipoPedido = pedido["tipo_pedido"].toString() == "programado" ? "Programado" : "Inmediato";
    QLabel *lblTipo = new QLabel(tipoPedido);
    lblTipo->setStyleSheet("color: #6B6B6B; font-size: 13px; margin-left: 8px;");
    headerLayout->addWidget(lblTipo);

    layoutCard->addWidget(headerWidget);

    // Línea separadora
    QFrame *linea = new QFrame();
    linea->setFrameShape(QFrame::HLine);
    linea->setStyleSheet("background-color: #E0E0E0; max-height: 1px;");
    layoutCard->addWidget(linea);

    // Unidades
    QWidget *unidadesWidget = new QWidget();
    QVBoxLayout *unidadesLayout = new QVBoxLayout(unidadesWidget);
    unidadesLayout->setContentsMargins(0, 5, 0, 5);
    QLabel *lblUnidades = new QLabel(QString::number(pedido["total_unidades"].toInt()) + " unidades");
    lblUnidades->setStyleSheet("color: #6B6B6B; font-size: 14px;");
    unidadesLayout->addWidget(lblUnidades);
    layoutCard->addWidget(unidadesWidget);

    layoutCard->addStretch();

    // Footer
    QWidget *footerWidget = new QWidget();
    QHBoxLayout *footerLayout = new QHBoxLayout(footerWidget);
    footerLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *lblPrecio = new QLabel("$" + QString::number(pedido["total"].toDouble(), 'f', 2));
    lblPrecio->setStyleSheet("font-size: 18px; font-weight: bold; color: #C81E2D;");
    footerLayout->addWidget(lblPrecio);

    footerLayout->addStretch();

    QLabel *lblNumero = new QLabel("#" + pedido["numero_pedido"].toString());
    lblNumero->setStyleSheet("font-size: 16px; color: #6B6B6B;");
    footerLayout->addWidget(lblNumero);

    layoutCard->addWidget(footerWidget);

    return card;
}

bool cocina::eventFilter(QObject *obj, QEvent *event)
{
    QWidget *widget = qobject_cast<QWidget*>(obj);

    if (widget) {
        // Efecto hover para cards de pedidos
        if (widget->property("es_card_pedido").toBool()) {
            if (event->type() == QEvent::Enter) {
                widget->setProperty("hover_state", true);
                widget->setStyleSheet(
                    "QWidget { "
                    "background-color: #F5F5F5; "
                    "border-radius: 13px; "
                    "}"
                    );

                QGraphicsDropShadowEffect *shadow = qobject_cast<QGraphicsDropShadowEffect*>(widget->graphicsEffect());
                if (shadow) {
                    shadow->setBlurRadius(15);
                    shadow->setOffset(0, 4);
                }
            } else if (event->type() == QEvent::Leave) {
                widget->setProperty("hover_state", false);
                widget->setStyleSheet(
                    "QWidget { "
                    "background-color: white; "
                    "border-radius: 13px; "
                    "}"
                    );

                QGraphicsDropShadowEffect *shadow = qobject_cast<QGraphicsDropShadowEffect*>(widget->graphicsEffect());
                if (shadow) {
                    shadow->setBlurRadius(10);
                    shadow->setOffset(0, 2);
                }
            } else if (event->type() == QEvent::MouseButtonPress) {
                if (widget->property("pedido_data").isValid()) {
                    QJsonObject pedido = widget->property("pedido_data").toJsonObject();
                    mostrarDetallePedido(pedido);
                    return true;
                }
            }
        }

        // Efecto hover para botón de confirmar
        if (widget->property("es_boton_confirmar").toBool()) {
            if (event->type() == QEvent::Enter) {
                ui->widget_19->setStyleSheet("background-color: #A01825;");
            } else if (event->type() == QEvent::Leave) {
                ui->widget_19->setStyleSheet("background-color: #C81E2D;");
            } else if (event->type() == QEvent::MouseButtonPress) {
                confirmarPedido();
                return true;
            }
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
        layoutProductos->setSpacing(10);
        layoutProductos->setContentsMargins(10, 10, 10, 10);
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

    // Cambiar el color del botón según si hay repartidor asignado
    bool tieneRepartidor = !pedido["repartidor_id"].isNull() && pedido["repartidor_id"].toInt() > 0;

    if (tieneRepartidor) {
        ui->widget_19->setStyleSheet("background-color: #27AE60;"); // Verde - listo para confirmar
    } else {
        ui->widget_19->setStyleSheet("background-color: #C81E2D;"); // Rojo - falta asignar repartidor
    }
}

QWidget* cocina::crearWidgetProducto(const QJsonObject &item)
{
    QWidget *widget = new QWidget();
    widget->setStyleSheet("background-color: white; border-radius: 8px; padding: 10px;");
    widget->setMinimumHeight(120);

    QHBoxLayout *layout = new QHBoxLayout(widget);
    layout->setSpacing(15);

    QLabel *lblImagen = new QLabel();
    lblImagen->setMaximumSize(130, 113);
    lblImagen->setMinimumSize(130, 113);
    lblImagen->setStyleSheet("background-color: #EAEAEA; border-radius: 8px;");
    lblImagen->setText("Imagen");
    lblImagen->setAlignment(Qt::AlignCenter);
    layout->addWidget(lblImagen);

    QWidget *infoWidget = new QWidget();
    QVBoxLayout *infoLayout = new QVBoxLayout(infoWidget);
    infoLayout->setSpacing(5);
    infoLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *lblNombre = new QLabel(item["producto_nombre"].toString());
    lblNombre->setStyleSheet("font-size: 18px; font-weight: bold;");
    infoLayout->addWidget(lblNombre);

    QLabel *lblCantidad = new QLabel("Cantidad: " + QString::number(item["cantidad"].toInt()) + " unidades");
    lblCantidad->setStyleSheet("color: #6B6B6B; font-size: 14px;");
    infoLayout->addWidget(lblCantidad);

    QJsonArray condimentos = item["condimentos"].toArray();
    if (condimentos.size() > 0) {
        QString txtCondimentos = "Condimentos: ";
        for (int i = 0; i < condimentos.size(); i++) {
            if (i > 0) txtCondimentos += ", ";
            txtCondimentos += condimentos[i].toObject()["nombre"].toString();
        }
        QLabel *lblCondimentos = new QLabel(txtCondimentos);
        lblCondimentos->setStyleSheet("color: #6B6B6B; font-size: 13px;");
        lblCondimentos->setWordWrap(true);
        infoLayout->addWidget(lblCondimentos);
    }

    infoLayout->addStretch();

    QLabel *lblPrecio = new QLabel("Precio $" + QString::number(item["precio_total"].toDouble(), 'f', 2) + " ARS");
    lblPrecio->setStyleSheet("font-size: 16px; font-weight: bold; color: #C81E2D;");
    infoLayout->addWidget(lblPrecio);

    layout->addWidget(infoWidget);

    return widget;
}

void cocina::cargarComboRepartidores()
{
    // Limpiar el widget_18 y crear un nuevo layout si es necesario
    QLayout *oldLayout = ui->widget_18->layout();
    if (oldLayout) {
        QLayoutItem *item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            if (item->widget()) {
                delete item->widget();
            }
            delete item;
        }
        delete oldLayout;
    }

    QHBoxLayout *layout = new QHBoxLayout(ui->widget_18);
    layout->setContentsMargins(13, 0, 13, 0);
    layout->setSpacing(10);

    QLabel *label = new QLabel("Asignar repartidor:");
    label->setStyleSheet("color: #2C3E50; font-size: 14px;");
    layout->addWidget(label);

    if (repartidoresDisponibles.size() > 0) {
        QComboBox *comboRepartidores = new QComboBox();
        comboRepartidores->setStyleSheet(
            "QComboBox {"
            "   background-color: white;"
            "   border: 1px solid #CECECE;"
            "   border-radius: 8px;"
            "   padding: 8px 12px;"
            "   font-size: 13px;"
            "   min-width: 200px;"
            "}"
            "QComboBox:hover {"
            "   border: 1px solid #C81E2D;"
            "   background-color: #F9F9F9;"
            "}"
            "QComboBox::drop-down {"
            "   border: none;"
            "   width: 30px;"
            "}"
            "QComboBox::down-arrow {"
            "   image: url(:/down_arrow.png);"
            "   width: 12px;"
            "   height: 12px;"
            "}"
            "QComboBox QAbstractItemView {"
            "   background-color: white;"
            "   border: 1px solid #CECECE;"
            "   selection-background-color: #C81E2D;"
            "   selection-color: white;"
            "   padding: 5px;"
            "}"
            );

        comboRepartidores->addItem("-- Seleccionar repartidor --", -1);

        for (int i = 0; i < repartidoresDisponibles.size(); i++) {
            QJsonObject repartidor = repartidoresDisponibles[i].toObject();
            QString nombreCompleto = repartidor["nombre"].toString() + " " + repartidor["apellido"].toString();
            int id = repartidor["id"].toInt();
            comboRepartidores->addItem(nombreCompleto, id);
        }

        // Conectar evento de selección
        connect(comboRepartidores, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, [this, comboRepartidores](int index) {
                    if (index > 0) {
                        int repartidorId = comboRepartidores->currentData().toInt();
                        asignarRepartidor(repartidorId);
                    }
                });

        layout->addWidget(comboRepartidores);
    } else {
        QLabel *lblSinRepartidores = new QLabel("No hay repartidores disponibles");
        lblSinRepartidores->setStyleSheet("color: #E74C3C; font-size: 13px; font-style: italic;");
        layout->addWidget(lblSinRepartidores);
    }

    layout->addStretch();
}

void cocina::confirmarPedido()
{
    if (pedidoActual.isEmpty()) {
        QMessageBox::warning(this, "Error", "No hay ningún pedido seleccionado");
        return;
    }

    // Verificar que haya un repartidor asignado
    if (pedidoActual["repartidor_id"].isNull() || pedidoActual["repartidor_id"].toInt() == 0) {
        QMessageBox::warning(
            this,
            "Repartidor no asignado",
            "Debe asignar un repartidor antes de confirmar el pedido.\n\n"
            "Por favor, seleccione un repartidor de la lista 'Asignar repartidor'."
            );
        return;
    }

    QString nombreRepartidor = pedidoActual["repartidor_nombre"].toString() + " " + pedidoActual["repartidor_apellido"].toString();

    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirmar Pedido",
        "¿Está seguro de confirmar el pedido #" + pedidoActual["numero_pedido"].toString() + "?\n\n"
                                                                                             "Repartidor asignado: " + nombreRepartidor,
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        // Enviar confirmación al servidor
        QJsonObject data;
        data["id_pedido"] = pedidoActual["id"].toInt();
        data["accion"] = "confirmar";

        QJsonDocument doc(data);
        QByteArray jsonData = doc.toJson();

        QNetworkRequest request(QUrl("http://elbuengusto.shop/api/cocina.php"));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QNetworkReply *reply = networkManager->post(request, jsonData);

        connect(reply, &QNetworkReply::finished, this, [this, reply]() {
            if (reply->error() == QNetworkReply::NoError) {
                QMessageBox::information(this, "Éxito", "Pedido confirmado correctamente");
                cargarPedidos();
            } else {
                QMessageBox::warning(this, "Error", "No se pudo confirmar el pedido: " + reply->errorString());
            }
            reply->deleteLater();
        });
    }
}

void cocina::asignarRepartidor(int repartidorId)
{
    if (pedidoActual.isEmpty()) {
        QMessageBox::warning(this, "Error", "No hay ningún pedido seleccionado");
        return;
    }

    // Buscar el nombre del repartidor
    QString nombreRepartidor;
    QJsonObject repartidorSeleccionado;
    for (int i = 0; i < repartidoresDisponibles.size(); i++) {
        QJsonObject rep = repartidoresDisponibles[i].toObject();
        if (rep["id"].toInt() == repartidorId) {
            nombreRepartidor = rep["nombre"].toString() + " " + rep["apellido"].toString();
            repartidorSeleccionado = rep;
            break;
        }
    }

    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Asignar Repartidor",
        "¿Desea asignar a " + nombreRepartidor + " al pedido #" + pedidoActual["numero_pedido"].toString() + "?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        // Enviar asignación al servidor
        QJsonObject data;
        data["id_pedido"] = pedidoActual["id"].toInt();
        data["repartidor_id"] = repartidorId;
        data["accion"] = "asignar_repartidor";

        QJsonDocument doc(data);
        QByteArray jsonData = doc.toJson();

        QNetworkRequest request(QUrl("http://elbuengusto.shop/api/cocina.php"));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QNetworkReply *netReply = networkManager->post(request, jsonData);

        connect(netReply, &QNetworkReply::finished, this, [this, netReply, nombreRepartidor, repartidorSeleccionado, repartidorId]() {
            if (netReply->error() == QNetworkReply::NoError) {
                // Actualizar el pedidoActual con el repartidor asignado
                pedidoActual["repartidor_id"] = repartidorId;
                pedidoActual["repartidor_nombre"] = repartidorSeleccionado["nombre"];
                pedidoActual["repartidor_apellido"] = repartidorSeleccionado["apellido"];

                // Actualizar el estilo del botón de confirmar para indicar que está listo
                ui->widget_19->setStyleSheet("background-color: #27AE60;"); // Verde para indicar que está listo

                QMessageBox::information(this, "Éxito", "Repartidor " + nombreRepartidor + " asignado correctamente\n\nAhora puede confirmar el pedido.");
                cargarPedidos();
            } else {
                QMessageBox::warning(this, "Error", "No se pudo asignar el repartidor: " + netReply->errorString());
            }
            netReply->deleteLater();
        });
    }
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
