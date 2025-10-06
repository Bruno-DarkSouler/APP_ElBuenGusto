#include "confirmacion_pedido.h"
#include "ui_confirmacion_pedido.h"
#include <QDebug>
#include <cmath>

ConfirmacionPedido::ConfirmacionPedido(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ConfirmacionPedido)
    , horaApertura1(QTime(11, 0))
    , horaCierre1(QTime(15, 0))
    , horaApertura2(QTime(19, 0))
    , horaCierre2(QTime(23, 0))
    , direccionSucursal("Cerrito 3966")
    , validadorTelefono(nullptr)
    , validadorEmail(nullptr)
    , networkManager(new QNetworkAccessManager(this))
    , apiUrl("http://localhost/WEB_ElBuenGusto/api/confirmacion_pedido.php")
{
    ui->setupUi(this);
    configurarInterfaz();
    configurarValidadores();
    configurarEventos();
    cargarConfiguracion();
    validarFormulario();
}

ConfirmacionPedido::ConfirmacionPedido(const QVector<ProductoConfirmacion>& productos, QWidget *parent)
    : ConfirmacionPedido(parent)
{
    establecerProductos(productos);
}

ConfirmacionPedido::~ConfirmacionPedido()
{
    delete ui;
    if (validadorTelefono) delete validadorTelefono;
    if (validadorEmail) delete validadorEmail;
}

void ConfirmacionPedido::configurarInterfaz()
{
    ui->dateEdit_fecha->setDate(QDate::currentDate());
    ui->dateEdit_fecha->setMinimumDate(QDate::currentDate());
    ui->dateEdit_fecha->setMaximumDate(QDate::currentDate().addDays(30));
    
    ui->timeEdit_hora->setTime(horaApertura1);
    
    configuracionPedido.subtotal = 0.0;
    configuracionPedido.costoDelivery = 0.0;
    configuracionPedido.total = 0.0;
    
    datosCliente.esClienteExistente = false;
    datosCliente.clienteId = -1;
    
    actualizarTotales();
}

void ConfirmacionPedido::configurarValidadores()
{
    QRegularExpression regexTelefono("^[0-9]{10,15}$");
    validadorTelefono = new QRegularExpressionValidator(regexTelefono, this);
    ui->lineEdit_telefono->setValidator(validadorTelefono);
    
    QRegularExpression regexEmail("^[\\w\\.-]+@[\\w\\.-]+\\.[a-zA-Z]{2,}$");
    validadorEmail = new QRegularExpressionValidator(regexEmail, this);
    ui->lineEdit_email->setValidator(validadorEmail);
}

void ConfirmacionPedido::configurarEventos()
{
    connect(ui->lineEdit_nombre, &QLineEdit::textChanged, this, &ConfirmacionPedido::validarCamposObligatorios);
    connect(ui->lineEdit_apellido, &QLineEdit::textChanged, this, &ConfirmacionPedido::validarCamposObligatorios);
    connect(ui->lineEdit_telefono, &QLineEdit::textChanged, this, &ConfirmacionPedido::validarCamposObligatorios);
    connect(ui->lineEdit_email, &QLineEdit::textChanged, this, &ConfirmacionPedido::validarCamposObligatorios);
    connect(ui->textEdit_direccion, &QTextEdit::textChanged, this, &ConfirmacionPedido::onDireccionChanged);
    
    connect(ui->radioButton_inmediato, &QRadioButton::toggled, this, &ConfirmacionPedido::toggleTipoPedido);
    connect(ui->radioButton_programado, &QRadioButton::toggled, this, &ConfirmacionPedido::toggleTipoPedido);
    
    connect(ui->radioButton_digital, &QRadioButton::toggled, this, &ConfirmacionPedido::toggleMetodoPago);
    connect(ui->radioButton_efectivo, &QRadioButton::toggled, this, &ConfirmacionPedido::toggleMetodoPago);
    
    connect(ui->pushButton_confirmar, &QPushButton::clicked, this, &ConfirmacionPedido::confirmarPedido);
    connect(ui->pushButton_volver, &QPushButton::clicked, this, &ConfirmacionPedido::volverCarrito);
    
    connect(ui->dateEdit_fecha, &QDateEdit::dateChanged, this, &ConfirmacionPedido::validarFormulario);
    connect(ui->timeEdit_hora, &QTimeEdit::timeChanged, this, &ConfirmacionPedido::validarFormulario);
}

void ConfirmacionPedido::cargarConfiguracion()
{
    QString horarioTexto = QString("Horarios de atención: %1-%2 y %3-%4")
                          .arg(horaApertura1.toString("HH:mm"))
                          .arg(horaCierre1.toString("HH:mm"))
                          .arg(horaApertura2.toString("HH:mm"))
                          .arg(horaCierre2.toString("HH:mm"));
    ui->label_horarioAtencion->setText(horarioTexto);
}

void ConfirmacionPedido::establecerProductos(const QVector<ProductoConfirmacion>& productos)
{
    productosCarrito = productos;
    calcularTotales();
    mostrarResumenProductos();
    validarFormulario();
}

void ConfirmacionPedido::establecerDatosCliente(const DatosCliente& cliente)
{
    datosCliente = cliente;
    
    ui->lineEdit_nombre->setText(cliente.nombre);
    ui->lineEdit_apellido->setText(cliente.apellido);
    ui->lineEdit_telefono->setText(cliente.telefono);
    ui->lineEdit_email->setText(cliente.email);
    ui->textEdit_direccion->setPlainText(cliente.direccion);
    
    if (cliente.esClienteExistente) {
        ui->lineEdit_nombre->setReadOnly(true);
        ui->lineEdit_apellido->setReadOnly(true);
        ui->lineEdit_telefono->setReadOnly(true);
        ui->lineEdit_email->setReadOnly(true);
    }
    
    calcularCostoDelivery();
    validarFormulario();
}

void ConfirmacionPedido::calcularTotales()
{
    configuracionPedido.subtotal = 0.0;
    
    for (const ProductoConfirmacion& producto : productosCarrito) {
        configuracionPedido.subtotal += producto.precioTotal;
    }
    
    configuracionPedido.total = configuracionPedido.subtotal + configuracionPedido.costoDelivery;
    actualizarTotales();
}

void ConfirmacionPedido::mostrarResumenProductos()
{
    QLayout* layout = ui->scrollAreaWidgetContents_productos->layout();
    if (layout) {
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete layout;
    }
    
    QVBoxLayout* productosLayout = new QVBoxLayout(ui->scrollAreaWidgetContents_productos);
    productosLayout->setSpacing(5);
    
    for (const ProductoConfirmacion& producto : productosCarrito) {
        QFrame* frameProducto = new QFrame();
        frameProducto->setStyleSheet("QFrame { background-color: white; border: 1px solid #ddd; border-radius: 4px; padding: 8px; }");
        
        QHBoxLayout* layoutProducto = new QHBoxLayout(frameProducto);
        
        QVBoxLayout* layoutInfo = new QVBoxLayout();
        
        QLabel* labelNombre = new QLabel(producto.nombre);
        labelNombre->setFont(QFont("Segoe UI", 11, QFont::Bold));
        
        QLabel* labelCantidad = new QLabel(QString("Cantidad: %1").arg(producto.cantidad));
        labelCantidad->setStyleSheet("color: #666; font-size: 10px;");
        
        layoutInfo->addWidget(labelNombre);
        layoutInfo->addWidget(labelCantidad);
        
        if (!producto.comentarios.isEmpty()) {
            QLabel* labelComentarios = new QLabel(QString("Comentarios: %1").arg(producto.comentarios));
            labelComentarios->setStyleSheet("color: #666; font-size: 9px; font-style: italic;");
            labelComentarios->setWordWrap(true);
            layoutInfo->addWidget(labelComentarios);
        }
        
        QLabel* labelPrecio = new QLabel(QString("$%1").arg(producto.precioTotal, 0, 'f', 2));
        labelPrecio->setFont(QFont("Segoe UI", 12, QFont::Bold));
        labelPrecio->setStyleSheet("color: rgb(200, 30, 45);");
        labelPrecio->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        
        layoutProducto->addLayout(layoutInfo, 1);
        layoutProducto->addWidget(labelPrecio);
        
        productosLayout->addWidget(frameProducto);
    }
    
    productosLayout->addStretch();
}

void ConfirmacionPedido::actualizarTotales()
{
    ui->label_subtotal->setText(QString("Subtotal: $%1").arg(configuracionPedido.subtotal, 0, 'f', 2));
    ui->label_delivery->setText(QString("Delivery: $%1").arg(configuracionPedido.costoDelivery, 0, 'f', 2));
    ui->label_total->setText(QString("Total: $%1").arg(configuracionPedido.total, 0, 'f', 2));
    ui->label_costoDelivery->setText(QString("Costo de delivery: $%1").arg(configuracionPedido.costoDelivery, 0, 'f', 2));
}

void ConfirmacionPedido::validarCamposObligatorios()
{
    validarFormulario();
}

void ConfirmacionPedido::onDireccionChanged()
{
    calcularCostoDelivery();
    validarFormulario();
}

void ConfirmacionPedido::calcularCostoDelivery()
{
    QString direccion = ui->textEdit_direccion->toPlainText().trimmed();
    
    if (direccion.isEmpty()) {
        configuracionPedido.costoDelivery = 0.0;
        ui->label_costoDelivery->setText("Costo de delivery: Ingrese dirección");
        return;
    }
    
    double distancia = calcularDistancia(direccion);
    configuracionPedido.costoDelivery = obtenerCostoDeliveryPorDistancia(distancia);
    
    configuracionPedido.total = configuracionPedido.subtotal + configuracionPedido.costoDelivery;
    actualizarTotales();
}

double ConfirmacionPedido::calcularDistancia(const QString& direccionDestino)
{
    QString direccionLower = direccionDestino.toLower();
    
    if (direccionLower.contains("centro") || direccionLower.contains("cerrito")) {
        return 1.0;
    } else if (direccionLower.contains("nueva cordoba") || direccionLower.contains("guemes")) {
        return 2.5;
    } else if (direccionLower.contains("alta cordoba") || direccionLower.contains("cerro")) {
        return 4.0;
    } else {
        return 6.0;
    }
}

double ConfirmacionPedido::obtenerCostoDeliveryPorDistancia(double distancia)
{
    if (distancia <= 1.5) {
        return 200.0;
    } else if (distancia <= 3.0) {
        return 350.0;
    } else if (distancia <= 5.0) {
        return 500.0;
    } else if (distancia <= 7.0) {
        return 700.0;
    } else {
        return 1000.0;
    }
}

void ConfirmacionPedido::toggleTipoPedido()
{
    bool esProgramado = ui->radioButton_programado->isChecked();
    ui->frame_programacion->setEnabled(esProgramado);
    
    if (esProgramado) {
        ui->dateEdit_fecha->setDate(QDate::currentDate());
        ui->timeEdit_hora->setTime(horaApertura1);
    }
    
    validarFormulario();
}

void ConfirmacionPedido::toggleMetodoPago()
{
    validarFormulario();
}

void ConfirmacionPedido::validarFormulario()
{
    bool formularioValido = true;
    
    if (productosCarrito.isEmpty()) {
        formularioValido = false;
    }
    
    if (!validarDatosPersonales()) {
        formularioValido = false;
    }
    
    if (!validarDireccionEntrega()) {
        formularioValido = false;
    }
    
    if (!validarTipoPedido()) {
        formularioValido = false;
    }
    
    if (!validarMetodoPago()) {
        formularioValido = false;
    }
    
    ui->pushButton_confirmar->setEnabled(formularioValido);
}

bool ConfirmacionPedido::validarDatosPersonales()
{
    QString nombre = ui->lineEdit_nombre->text().trimmed();
    QString apellido = ui->lineEdit_apellido->text().trimmed();
    QString telefono = ui->lineEdit_telefono->text().trimmed();
    QString email = ui->lineEdit_email->text().trimmed();
    
    if (nombre.isEmpty() || apellido.isEmpty() || telefono.isEmpty() || email.isEmpty()) {
        return false;
    }
    
    int pos = 0;
    QString telefonoCopy = telefono;
    if (validadorTelefono->validate(telefonoCopy, pos) == QValidator::Invalid) {
        return false;
    }
    
    int posEmail = 0;
    QString emailCopy = email;
    if (validadorEmail->validate(emailCopy, posEmail) == QValidator::Invalid) {
        return false;
    }
    
    return true;
}

bool ConfirmacionPedido::validarDireccionEntrega()
{
    QString direccion = ui->textEdit_direccion->toPlainText().trimmed();
    return !direccion.isEmpty() && direccion.length() >= 10;
}

bool ConfirmacionPedido::validarTipoPedido()
{
    if (ui->radioButton_inmediato->isChecked()) {
        return validarPedidoInmediato();
    } else if (ui->radioButton_programado->isChecked()) {
        QDateTime fechaHora(ui->dateEdit_fecha->date(), ui->timeEdit_hora->time());
        return validarPedidoProgramado(fechaHora);
    }
    
    return false;
}

bool ConfirmacionPedido::validarPedidoInmediato()
{
    QTime horaActual = QTime::currentTime();
    return esHorarioLaboral(horaActual);
}

bool ConfirmacionPedido::validarPedidoProgramado(const QDateTime& fechaHora)
{
    QDateTime ahora = QDateTime::currentDateTime();
    if (fechaHora <= ahora) {
        return false;
    }
    
    QDateTime maximaFecha = ahora.addDays(7);
    if (fechaHora > maximaFecha) {
        return false;
    }
    
    return esHorarioLaboral(fechaHora.time());
}

bool ConfirmacionPedido::esHorarioLaboral(const QTime& hora)
{
    return (hora >= horaApertura1 && hora <= horaCierre1) ||
           (hora >= horaApertura2 && hora <= horaCierre2);
}

bool ConfirmacionPedido::validarMetodoPago()
{
    return ui->radioButton_digital->isChecked() || ui->radioButton_efectivo->isChecked();
}

void ConfirmacionPedido::confirmarPedido()
{
    if (!validarDatosPersonales() || !validarDireccionEntrega() || !validarTipoPedido()) {
        mostrarMensajeError("Por favor, complete todos los campos obligatorios correctamente");
        return;
    }
    
    datosCliente.nombre = ui->lineEdit_nombre->text().trimmed();
    datosCliente.apellido = ui->lineEdit_apellido->text().trimmed();
    datosCliente.telefono = ui->lineEdit_telefono->text().trimmed();
    datosCliente.email = ui->lineEdit_email->text().trimmed();
    datosCliente.direccion = ui->textEdit_direccion->toPlainText().trimmed();
    
    configuracionPedido.tipoPedido = ui->radioButton_inmediato->isChecked() ? "inmediato" : "programado";
    
    if (ui->radioButton_programado->isChecked()) {
        configuracionPedido.fechaEntrega = QDateTime(ui->dateEdit_fecha->date(), ui->timeEdit_hora->time());
    }
    
    configuracionPedido.metodoPago = ui->radioButton_digital->isChecked() ? "digital" : "efectivo";
    configuracionPedido.comentarios = ui->textEdit_comentarios->toPlainText().trimmed();
    
    bloquearFormulario(true);
    
    QJsonObject pedidoJson;
    pedidoJson["cliente"] = QJsonObject{
        {"nombre", datosCliente.nombre},
        {"apellido", datosCliente.apellido},
        {"telefono", datosCliente.telefono},
        {"email", datosCliente.email},
        {"direccion", datosCliente.direccion}
    };
    
    QJsonArray itemsArray;
    for (const auto& producto : productosCarrito) {
        itemsArray.append(QJsonObject{
            {"id", producto.id},
            {"nombre", producto.nombre},
            {"cantidad", producto.cantidad},
            {"precio", producto.precio},
            {"subtotal", producto.precioTotal}
        });
    }
    
    pedidoJson["items"] = itemsArray;
    pedidoJson["tipo_pedido"] = configuracionPedido.tipoPedido;
    pedidoJson["metodo_pago"] = configuracionPedido.metodoPago;
    pedidoJson["subtotal"] = configuracionPedido.subtotal;
    pedidoJson["costo_envio"] = configuracionPedido.costoDelivery;
    pedidoJson["total"] = configuracionPedido.total;
    pedidoJson["comentarios"] = configuracionPedido.comentarios;
    
    if (configuracionPedido.fechaEntrega.isValid()) {
        pedidoJson["fecha_entrega"] = configuracionPedido.fechaEntrega.toString(Qt::ISODate);
    }
    
    QNetworkRequest request;
    request.setUrl(QUrl(apiUrl));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    
    QNetworkReply* reply = networkManager->post(request, QJsonDocument(pedidoJson).toJson());
    
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        procesarRespuestaConfirmacion(reply);
    });
}

void ConfirmacionPedido::procesarRespuestaConfirmacion(QNetworkReply *reply)
{
    bloquearFormulario(false);
    
    if (reply->error() != QNetworkReply::NoError) {
        mostrarMensajeError("Error al conectar con el servidor: " + reply->errorString());
        reply->deleteLater();
        return;
    }
    
    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    
    if (jsonDoc.isObject()) {
        QJsonObject obj = jsonDoc.object();
        int pedidoId = obj["pedido_id"].toInt();
        QString estado = obj["estado"].toString();
        
        if (estado == "confirmado") {
            mostrarMensajeExito(QString("¡Pedido confirmado exitosamente!\nNúmero de pedido: %1").arg(pedidoId));
            emit pedidoConfirmado(pedidoId);
        } else {
            mostrarMensajeError("Error al procesar el pedido");
        }
    }
    
    reply->deleteLater();
}

QString ConfirmacionPedido::generarNumeroPedido()
{
    return QString("P%1%2")
        .arg(QDate::currentDate().toString("yyyyMMdd"))
        .arg(QTime::currentTime().toString("hhmmss"));
}

void ConfirmacionPedido::volverCarrito()
{
    emit volverAlCarrito();
}

void ConfirmacionPedido::bloquearFormulario(bool bloqueado)
{
    ui->pushButton_confirmar->setEnabled(!bloqueado);
    ui->pushButton_volver->setEnabled(!bloqueado);
    
    if (bloqueado) {
        ui->pushButton_confirmar->setText("Procesando...");
    } else {
        ui->pushButton_confirmar->setText("Confirmar Pedido");
    }
}

void ConfirmacionPedido::mostrarMensajeError(const QString& mensaje)
{
    QMessageBox::critical(this, "Error", mensaje);
}

void ConfirmacionPedido::mostrarMensajeExito(const QString& mensaje)
{
    QMessageBox::information(this, "Éxito", mensaje);
}

void ConfirmacionPedido::mostrarMensajeAdvertencia(const QString& mensaje)
{
    QMessageBox::warning(this, "Advertencia", mensaje);
}

QString ConfirmacionPedido::formatearDireccion(const QString& direccion)
{
    return direccion.trimmed();
}

void ConfirmacionPedido::limpiarFormulario()
{
    ui->lineEdit_nombre->clear();
    ui->lineEdit_apellido->clear();
    ui->lineEdit_telefono->clear();
    ui->lineEdit_email->clear();
    ui->textEdit_direccion->clear();
    ui->textEdit_comentarios->clear();
    ui->radioButton_inmediato->setChecked(true);
    ui->radioButton_digital->setChecked(true);
}

bool ConfirmacionPedido::validarHorarioLaboral(const QDateTime& fechaHora)
{
    return esHorarioLaboral(fechaHora.time());
}
