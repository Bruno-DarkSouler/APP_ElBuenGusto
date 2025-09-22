#include "confirmacion_pedido.h"
#include "ui_confirmacion_pedido.h"
#include <QtCore/QDebug>
#include <QtCore/QStandardPaths>
#include <cmath>

ConfirmacionPedido::ConfirmacionPedido(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui_ConfirmacionPedido)
    , horaApertura1(QTime(11, 0))
    , horaCierre1(QTime(15, 0))
    , horaApertura2(QTime(19, 0))
    , horaCierre2(QTime(23, 0))
    , direccionSucursal("Cerrito 3966")
    , validadorTelefono(nullptr)
    , validadorEmail(nullptr)
    , networkManager(nullptr)
{
    ui->setupUi(this);
    
    if (inicializarBaseDatos()) {
        configurarInterfaz();
        configurarValidadores();
        configurarEventos();
        cargarConfiguracion();
        validarFormulario();
    } else {
        mostrarMensajeError("Error al conectar con la base de datos");
    }
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
    if (networkManager) delete networkManager;
}

bool ConfirmacionPedido::inicializarBaseDatos()
{
    db = QSqlDatabase::addDatabase("QSQLITE", "confirmacion_connection");
    db.setDatabaseName("rotiseria.db");
    
    if (!db.open()) {
        qDebug() << "Error al abrir base de datos:" << db.lastError().text();
        return false;
    }
    
    return true;
}

void ConfirmacionPedido::configurarInterfaz()
{
    // Configurar fechas mínimas y máximas
    ui->dateEdit_fecha->setDate(QDate::currentDate());
    ui->dateEdit_fecha->setMinimumDate(QDate::currentDate());
    ui->dateEdit_fecha->setMaximumDate(QDate::currentDate().addDays(30));
    
    // Configurar hora inicial
    ui->timeEdit_hora->setTime(horaApertura1);
    
    // Inicializar totales
    configuracionPedido.subtotal = 0.0;
    configuracionPedido.costoDelivery = 0.0;
    configuracionPedido.total = 0.0;
    
    // Configurar datos del cliente
    datosCliente.esClienteExistente = false;
    datosCliente.clienteId = -1;
    
    // Actualizar interfaz
    actualizarTotales();
}

void ConfirmacionPedido::configurarValidadores()
{
    // Validador para teléfono (formato argentino)
    QRegularExpression regexTelefono("^[0-9]{10,15}$");
    validadorTelefono = new QRegularExpressionValidator(regexTelefono, this);
    ui->lineEdit_telefono->setValidator(validadorTelefono);
    
    // Validador para email
    QRegularExpression regexEmail("^[\\w\\.-]+@[\\w\\.-]+\\.[a-zA-Z]{2,}$");
    validadorEmail = new QRegularExpressionValidator(regexEmail, this);
    ui->lineEdit_email->setValidator(validadorEmail);
}

void ConfirmacionPedido::configurarEventos()
{
    // Eventos de validación de campos
    connect(ui->lineEdit_nombre, &QLineEdit::textChanged, this, &ConfirmacionPedido::validarCamposObligatorios);
    connect(ui->lineEdit_apellido, &QLineEdit::textChanged, this, &ConfirmacionPedido::validarCamposObligatorios);
    connect(ui->lineEdit_telefono, &QLineEdit::textChanged, this, &ConfirmacionPedido::validarCamposObligatorios);
    connect(ui->lineEdit_email, &QLineEdit::textChanged, this, &ConfirmacionPedido::validarCamposObligatorios);
    connect(ui->textEdit_direccion, &QTextEdit::textChanged, this, &ConfirmacionPedido::onDireccionChanged);
    
    // Eventos de tipo de pedido
    connect(ui->radioButton_inmediato, &QRadioButton::toggled, this, &ConfirmacionPedido::toggleTipoPedido);
    connect(ui->radioButton_programado, &QRadioButton::toggled, this, &ConfirmacionPedido::toggleTipoPedido);
    
    // Eventos de método de pago
    connect(ui->radioButton_digital, &QRadioButton::toggled, this, &ConfirmacionPedido::toggleMetodoPago);
    connect(ui->radioButton_efectivo, &QRadioButton::toggled, this, &ConfirmacionPedido::toggleMetodoPago);
    
    // Eventos de botones
    connect(ui->pushButton_confirmar, &QPushButton::clicked, this, &ConfirmacionPedido::confirmarPedido);
    connect(ui->pushButton_volver, &QPushButton::clicked, this, &ConfirmacionPedido::volverCarrito);
    
    // Eventos de fecha y hora
    connect(ui->dateEdit_fecha, &QDateEdit::dateChanged, this, &ConfirmacionPedido::validarFormulario);
    connect(ui->timeEdit_hora, &QTimeEdit::timeChanged, this, &ConfirmacionPedido::validarFormulario);
}

void ConfirmacionPedido::cargarConfiguracion()
{
    QSqlQuery query(db);
    query.prepare("SELECT clave, valor FROM configuracion WHERE clave IN (?, ?, ?, ?, ?)");
    query.addBindValue("hora_apertura_1");
    query.addBindValue("hora_cierre_1");
    query.addBindValue("hora_apertura_2");
    query.addBindValue("hora_cierre_2");
    query.addBindValue("direccion_sucursal");
    
    if (query.exec()) {
        while (query.next()) {
            QString clave = query.value(0).toString();
            QString valor = query.value(1).toString();
            
            if (clave == "hora_apertura_1") {
                horaApertura1 = QTime::fromString(valor, "HH:mm");
            } else if (clave == "hora_cierre_1") {
                horaCierre1 = QTime::fromString(valor, "HH:mm");
            } else if (clave == "hora_apertura_2") {
                horaApertura2 = QTime::fromString(valor, "HH:mm");
            } else if (clave == "hora_cierre_2") {
                horaCierre2 = QTime::fromString(valor, "HH:mm");
            } else if (clave == "direccion_sucursal") {
                direccionSucursal = valor;
            }
        }
    }
    
    // Actualizar label de horario
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
    
    // Si es cliente existente, deshabilitar algunos campos
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
    // Limpiar layout existente
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
        
        // Información del producto
        QVBoxLayout* layoutInfo = new QVBoxLayout();
        
        QLabel* labelNombre = new QLabel(producto.nombre);
        labelNombre->setFont(QFont("Segoe UI", 11, QFont::Bold));
        
        QLabel* labelCantidad = new QLabel(QString("Cantidad: %1").arg(producto.cantidad));
        labelCantidad->setStyleSheet("color: #666; font-size: 10px;");
        
        if (!producto.comentarios.isEmpty()) {
            QLabel* labelComentarios = new QLabel(QString("Comentarios: %1").arg(producto.comentarios));
            labelComentarios->setStyleSheet("color: #666; font-size: 9px; font-style: italic;");
            labelComentarios->setWordWrap(true);
            layoutInfo->addWidget(labelComentarios);
        }
        
        layoutInfo->addWidget(labelNombre);
        layoutInfo->addWidget(labelCantidad);
        
        // Precio
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
    // Implementación simplificada de cálculo de distancia
    // En una implementación real, usarías una API de mapas como Google Maps
    Q_UNUSED(direccionDestino)
    
    // Simulación basada en palabras clave de la dirección
    QString direccionLower = direccionDestino.toLower();
    
    if (direccionLower.contains("centro") || direccionLower.contains("cerrito")) {
        return 1.0; // Zona muy cercana
    } else if (direccionLower.contains("nueva cordoba") || direccionLower.contains("guemes")) {
        return 2.5; // Zona cercana
    } else if (direccionLower.contains("alta cordoba") || direccionLower.contains("cerro")) {
        return 4.0; // Zona media
    } else {
        return 6.0; // Zona lejana
    }
}

double ConfirmacionPedido::obtenerCostoDeliveryPorDistancia(double distancia)
{
    if (distancia <= 1.5) {
        return 200.0; // Zona muy cercana
    } else if (distancia <= 3.0) {
        return 350.0; // Zona cercana
    } else if (distancia <= 5.0) {
        return 500.0; // Zona media
    } else if (distancia <= 7.0) {
        return 700.0; // Zona lejana
    } else {
        return 1000.0; // Zona muy lejana
    }
}

void ConfirmacionPedido::toggleTipoPedido()
{
    bool esProgramado = ui->radioButton_programado->isChecked();
    ui->frame_programacion->setEnabled(esProgramado);
    
    if (esProgramado) {
        // Configurar fecha y hora mínimas para pedidos programados
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
    
    // Validar que hay productos en el carrito
    if (productosCarrito.isEmpty()) {
        formularioValido = false;
    }
    
    // Validar datos personales
    if (!validarDatosPersonales()) {
        formularioValido = false;
    }
    
    // Validar dirección de entrega
    if (!validarDireccionEntrega()) {
        formularioValido = false;
    }
    
    // Validar tipo de pedido
    if (!validarTipoPedido()) {
        formularioValido = false;
    }
    
    // Validar método de pago
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
    
    // Validar formato de teléfono
    if (!validadorTelefono->validate(telefono, 0)) {
        return false;
    }
    
    // Validar formato de email
    if (!validadorEmail->validate(email, 0)) {
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
    QTime ahora = QTime::currentTime();
    return esHorarioLaboral(ahora);
}

bool ConfirmacionPedido::validarPedidoProgramado(const QDateTime& fechaHora)
{
    // Validar que la fecha no sea pasada
    if (fechaHora.date() < QDate::currentDate()) {
        return false;
    }
    
    // Si es hoy, validar que la hora no sea pasada
    if (fechaHora.date() == QDate::currentDate() && 
        fechaHora.time() <= QTime::currentTime().addSecs(3600)) { // Mínimo 1 hora de anticipación
        return false;
    }
    
    // Validar que esté en horario laboral
    return esHorarioLaboral(fechaHora.time());
}

bool ConfirmacionPedido::esHorarioLaboral(const QTime& hora)
{
    return (hora >= horaApertura1 && hora <= horaCierre1) ||
           (hora >= horaApertura2 && hora <= horaCierre2);
}

bool ConfirmacionPedido::validarMetodoPago()
{
    if (ui->radioButton_efectivo->isChecked()) {
        // Validar si el cliente puede pagar en efectivo (solo clientes autorizados)
        // Por ahora, permitimos a todos los clientes
        return true;
    }
    
    return ui->radioButton_digital->isChecked() || ui->radioButton_efectivo->isChecked();
}

void ConfirmacionPedido::confirmarPedido()
{
    if (!validarFormulario()) {
        mostrarMensajeError("Por favor, complete todos los campos obligatorios correctamente");
        return;
    }
    
    // Recopilar datos del cliente
    datosCliente.nombre = ui->lineEdit_nombre->text().trimmed();
    datosCliente.apellido = ui->lineEdit_apellido->text().trimmed();
    datosCliente.telefono = ui->lineEdit_telefono->text().trimmed();
    datosCliente.email = ui->lineEdit_email->text().trimmed();
    datosCliente.direccion = ui->textEdit_direccion->toPlainText().trimmed();
    
    // Recopilar configuración del pedido
    configuracionPedido.tipoPedido = ui->radioButton_inmediato->isChecked() ? "inmediato" : "programado";
    
    if (ui->radioButton_programado->isChecked()) {
        configuracionPedido.fechaEntrega = QDateTime(ui->dateEdit_fecha->date(), ui->timeEdit_hora->time());
    } else {
        configuracionPedido.fechaEntrega = QDateTime(); // Nulo para pedidos inmediatos
    }
    
    configuracionPedido.metodoPago = ui->radioButton_digital->isChecked() ? "digital" : "efectivo";
    configuracionPedido.comentarios = ui->textEdit_comentarios->toPlainText().trimmed();
    
    // Bloquear formulario durante el procesamiento
    bloquearFormulario(true);
    
    try {
        // Verificar o crear cliente
        if (!datosCliente.esClienteExistente) {
            if (existeCliente(datosCliente.telefono, datosCliente.email)) {
                datosCliente.clienteId = obtenerIdCliente(datosCliente.telefono, datosCliente.email);
                datosCliente.esClienteExistente = true;
            } else {
                datosCliente.clienteId = crearCliente(datosCliente);
                if (datosCliente.clienteId <= 0) {
                    throw QString("Error al registrar los datos del cliente");
                }
            }
        }
        
        // Crear el pedido
        int pedidoId = crearPedido();
        if (pedidoId <= 0) {
            throw QString("Error al crear el pedido");
        }
        
        // Agregar items al pedido
        if (!agregarItemsPedido(pedidoId)) {
            throw QString("Error al agregar los productos al pedido");
        }
        
        // Crear seguimiento del pedido
        if (!crearSeguimientoPedido(pedidoId)) {
            throw QString("Error al crear el seguimiento del pedido");
        }
        
        // Enviar factura por email
        if (!enviarFacturaPorEmail(pedidoId)) {
            qDebug() << "Advertencia: No se pudo enviar la factura por email";
        }
        
        mostrarMensajeExito(QString("¡Pedido confirmado exitosamente!\nNúmero de pedido: %1").arg(pedidoId));
        
        emit pedidoConfirmado(pedidoId);
        
    } catch (const QString& error) {
        mostrarMensajeError(error);
        bloquearFormulario(false);
    }
}

int ConfirmacionPedido::crearPedido()
{
    QSqlQuery query(db);
    
    // Iniciar transacción
    db.transaction();
    
    try {
        query.prepare("INSERT INTO pedidos (numero_pedido, usuario_id, tipo_pedido, fecha_pedido, "
                      "fecha_entrega_programada, direccion_entrega, telefono_contacto, metodo_pago, "
                      "estado, subtotal, precio_delivery, total, comentarios_cliente) "
                      "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
        
        QString numeroPedido = generarNumeroPedido();
        
        query.addBindValue(numeroPedido);
        query.addBindValue(datosCliente.clienteId);
        query.addBindValue(configuracionPedido.tipoPedido);
        query.addBindValue(QDateTime::currentDateTime());
        query.addBindValue(configuracionPedido.fechaEntrega.isValid() ? configuracionPedido.fechaEntrega : QVariant());
        query.addBindValue(datosCliente.direccion);
        query.addBindValue(datosCliente.telefono);
        query.addBindValue(configuracionPedido.metodoPago);
        query.addBindValue("pendiente");
        query.addBindValue(configuracionPedido.subtotal);
        query.addBindValue(configuracionPedido.costoDelivery);
        query.addBindValue(configuracionPedido.total);
        query.addBindValue(configuracionPedido.comentarios);
        
        if (!query.exec()) {
            throw QString("Error en la consulta SQL: " + query.lastError().text());
        }
        
        int pedidoId = query.lastInsertId().toInt();
        
        // Confirmar transacción
        db.commit();
        
        return pedidoId;
        
    } catch (const QString& error) {
        db.rollback();
        throw error;
    }
}

bool ConfirmacionPedido::agregarItemsPedido(int pedidoId)
{
    QSqlQuery query(db);
    
    for (const ProductoConfirmacion& producto : productosCarrito) {
        query.prepare("INSERT INTO pedido_items (pedido_id, producto_id, cantidad, precio_unitario, precio_total) "
                      "VALUES (?, ?, ?, ?, ?)");
        query.addBindValue(pedidoId);
        query.addBindValue(producto.id);
        query.addBindValue(producto.cantidad);
        query.addBindValue(producto.precio);
        query.addBindValue(producto.precioTotal);
        
        if (!query.exec()) {
            qDebug() << "Error al agregar item:" << query.lastError().text();
            return false;
        }
    }
    
    return true;
}

bool ConfirmacionPedido::crearSeguimientoPedido(int pedidoId)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO seguimiento_pedidos (pedido_id, estado_anterior, estado_nuevo, "
                  "usuario_cambio_id, comentarios) VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(pedidoId);
    query.addBindValue(QVariant()); // Estado anterior nulo
    query.addBindValue("pendiente");
    query.addBindValue(datosCliente.clienteId);
    query.addBindValue("Pedido creado por el cliente");
    
    return query.exec();
}

bool ConfirmacionPedido::existeCliente(const QString& telefono, const QString& email)
{
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM usuarios WHERE (telefono = ? OR email = ?) AND rol = 'cliente' AND activo = 1");
    query.addBindValue(telefono);
    query.addBindValue(email);
    
    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    
    return false;
}

int ConfirmacionPedido::obtenerIdCliente(const QString& telefono, const QString& email)
{
    QSqlQuery query(db);
    query.prepare("SELECT id FROM usuarios WHERE (telefono = ? OR email = ?) AND rol = 'cliente' AND activo = 1 LIMIT 1");
    query.addBindValue(telefono);
    query.addBindValue(email);
    
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    
    return -1;
}

int ConfirmacionPedido::crearCliente(const DatosCliente& cliente)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO usuarios (nombre, apellido, email, telefono, direccion, contraseña, rol) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(cliente.nombre);
    query.addBindValue(cliente.apellido);
    query.addBindValue(cliente.email);
    query.addBindValue(cliente.telefono);
    query.addBindValue(cliente.direccion);
    query.addBindValue("temp_password"); // Contraseña temporal
    query.addBindValue("cliente");
    
    if (query.exec()) {
        return query.lastInsertId().toInt();
    }
    
    return -1;
}

bool ConfirmacionPedido::enviarFacturaPorEmail(int pedidoId)
{
    // Implementación simplificada
    // En una implementación real, generarías y enviarías un PDF por email
    Q_UNUSED(pedidoId)
    return true;
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
    
    // Cambiar texto del botón mientras procesa
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