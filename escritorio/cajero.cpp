#include "cajero.h"
#include "ui_cajero.h"
#include <QtWidgets/QApplication>
#include <QtCore/QRegularExpression>
#include <cmath>

PanelCajero::PanelCajero(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui_PanelCajero)
    , clienteEstaSeleccionado(false)
    , subtotal(0.0)
    , precioDelivery(0.0)
    , total(0.0)
    , horaApertura1(QTime(11, 0))
    , horaCierre1(QTime(15, 0))
    , horaApertura2(QTime(19, 0))
    , horaCierre2(QTime(23, 0))
    , networkManager(new QNetworkAccessManager(this))
    , apiUrl("C:\\Users\\NoxiePC\\Downloads\\WEB_ElBuenGusto\\api\\cajero.php")
{
    ui->setupUi(this);
    
    if (inicializarBaseDatos()) {
        cargarConfiguracion();
        cargarProductos();
        cargarClientes();
        mostrarProductos();
    } else {
        mostrarMensajeError("Error al conectar con la base de datos");
    }
    
    configurarEventos();
}

PanelCajero::~PanelCajero()
{
    delete ui;
}

bool PanelCajero::inicializarBaseDatos()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("rotiseria.db");
    
    if (!db.open()) {
        return false;
    }
    
    return true;
}

void PanelCajero::configurarEventos()
{
    // Conexiones de botones y controles
    connect(ui->pushButton_buscarCliente, &QPushButton::clicked, this, &PanelCajero::buscarCliente);
    connect(ui->comboBox_categorias, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &PanelCajero::filtrarProductos);
    connect(ui->lineEdit_buscarProducto, &QLineEdit::textChanged, this, &PanelCajero::buscarProductoPorNombre);
    connect(ui->pushButton_crearPedido, &QPushButton::clicked, this, &PanelCajero::crearPedido);
    connect(ui->radioButton_inmediato, &QRadioButton::toggled, this, &PanelCajero::toggleTipoPedido);
    connect(ui->radioButton_programado, &QRadioButton::toggled, this, &PanelCajero::toggleTipoPedido);
    
    // Configurar fecha mínima para pedidos programados
    ui->dateEdit_fecha->setDate(QDate::currentDate());
    ui->dateEdit_fecha->setMinimumDate(QDate::currentDate());
    
    // Configurar hora actual
    ui->timeEdit_hora->setTime(QTime::currentTime());
}

void PanelCajero::cargarConfiguracion()
{
    QSqlQuery query(db);
    query.prepare("SELECT clave, valor FROM configuracion WHERE clave IN ('hora_apertura_1', 'hora_cierre_1', 'hora_apertura_2', 'hora_cierre_2')");
    
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
            }
        }
    }
}

void PanelCajero::cargarProductos()
{
    productos.clear();
    
    QSqlQuery query(db);
    query.prepare("SELECT p.id, p.nombre, p.descripcion, p.precio, p.imagen, p.categoria_id, "
                  "p.ingredientes, p.tiempo_preparacion, p.disponible, p.valoracion_promedio, "
                  "p.total_valoraciones, p.activo FROM productos p WHERE p.activo = 1");
    
    if (query.exec()) {
        while (query.next()) {
            Producto producto;
            producto.id = query.value(0).toInt();
            producto.nombre = query.value(1).toString();
            producto.descripcion = query.value(2).toString();
            producto.precio = query.value(3).toDouble();
            producto.imagen = query.value(4).toString();
            producto.categoriaId = query.value(5).toInt();
            producto.ingredientes = query.value(6).toString();
            producto.tiempoPreparacion = query.value(7).toInt();
            producto.disponible = query.value(8).toBool();
            producto.valoracionPromedio = query.value(9).toDouble();
            producto.totalValoraciones = query.value(10).toInt();
            producto.activo = query.value(11).toBool();
            
            productos.append(producto);
        }
    }
}

void PanelCajero::cargarClientes()
{
    clientes.clear();
    
    QSqlQuery query(db);
    query.prepare("SELECT id, nombre, apellido, email, telefono, direccion, activo "
                  "FROM usuarios WHERE rol = 'cliente' AND activo = 1");
    
    if (query.exec()) {
        while (query.next()) {
            Cliente cliente;
            cliente.id = query.value(0).toInt();
            cliente.nombre = query.value(1).toString();
            cliente.apellido = query.value(2).toString();
            cliente.email = query.value(3).toString();
            cliente.telefono = query.value(4).toString();
            cliente.direccion = query.value(5).toString();
            cliente.activo = query.value(6).toBool();
            
            clientes.append(cliente);
        }
    }
}

void PanelCajero::mostrarProductos()
{
    mostrarProductos("Todas las categorías");
}

void PanelCajero::mostrarProductos(const QString& filtroCategoria, const QString& filtroNombre)
{
    // Limpiar layout existente
    QLayout* layout = ui->scrollAreaWidgetContents->layout();
    if (layout) {
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete layout;
    }
    
    QVBoxLayout* productosLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    productosLayout->setSpacing(10);
    
    // Filtrar productos
    QVector<Producto> productosFiltrados;
    
    for (const Producto& producto : productos) {
        bool coincideCategoria = (filtroCategoria == "Todas las categorías");
        if (!coincideCategoria) {
            // Aquí deberías mapear el nombre de categoría con el ID
            // Por simplicidad, asumimos que coincide si el nombre contiene la categoría
            coincideCategoria = true; // Implementar lógica de filtrado por categoría
        }
        
        bool coincideNombre = filtroNombre.isEmpty() || 
                             producto.nombre.contains(filtroNombre, Qt::CaseInsensitive);
        
        if (coincideCategoria && coincideNombre) {
            productosFiltrados.append(producto);
        }
    }
    
    // Crear widgets de productos
    for (const Producto& producto : productosFiltrados) {
        crearWidgetProducto(producto, productosLayout);
    }
    
    productosLayout->addStretch();
}

void PanelCajero::crearWidgetProducto(const Producto& producto, QVBoxLayout* layout)
{
    QFrame* frameProducto = new QFrame();
    frameProducto->setStyleSheet("QFrame { background-color: white; border-radius: 8px; margin: 2px; }");
    frameProducto->setMaximumHeight(120);
    
    QHBoxLayout* layoutProducto = new QHBoxLayout(frameProducto);
    
    // Imagen del producto
    QLabel* labelImagen = new QLabel();
    labelImagen->setFixedSize(80, 80);
    labelImagen->setScaledContents(true);
    labelImagen->setStyleSheet("border-radius: 6px;");
    
    if (!producto.imagen.isEmpty()) {
        QPixmap pixmap(":/img/" + producto.imagen);
        if (!pixmap.isNull()) {
            labelImagen->setPixmap(pixmap);
        } else {
            labelImagen->setText("Sin\nImagen");
            labelImagen->setAlignment(Qt::AlignCenter);
        }
    }
    
    // Información del producto
    QVBoxLayout* layoutInfo = new QVBoxLayout();
    
    QLabel* labelNombre = new QLabel(producto.nombre);
    labelNombre->setFont(QFont("Segoe UI", 12, QFont::Bold));
    
    QLabel* labelDescripcion = new QLabel(producto.descripcion);
    labelDescripcion->setWordWrap(true);
    labelDescripcion->setMaximumHeight(40);
    labelDescripcion->setStyleSheet("color: #666;");
    
    QLabel* labelPrecio = new QLabel(QString("$%1").arg(producto.precio, 0, 'f', 2));
    labelPrecio->setFont(QFont("Segoe UI", 14, QFont::Bold));
    labelPrecio->setStyleSheet("color: rgb(200, 30, 45);");
    
    layoutInfo->addWidget(labelNombre);
    layoutInfo->addWidget(labelDescripcion);
    layoutInfo->addWidget(labelPrecio);
    
    // Botón agregar
    QPushButton* btnAgregar = new QPushButton("Agregar");
    btnAgregar->setFixedSize(80, 35);
    
    if (producto.disponible) {
        btnAgregar->setStyleSheet(
            "QPushButton { background-color: rgb(200, 30, 45); color: white; border: none; "
            "border-radius: 4px; font-weight: bold; } "
            "QPushButton:hover { background-color: rgb(180, 25, 40); }"
        );
        connect(btnAgregar, &QPushButton::clicked, [this, producto]() {
            agregarProductoAlCarrito(producto.id);
        });
    } else {
        btnAgregar->setText("No disponible");
        btnAgregar->setEnabled(false);
        btnAgregar->setStyleSheet("QPushButton { background-color: #ccc; color: #999; border: none; border-radius: 4px; }");
    }
    
    // Estado del producto
    QLabel* labelEstado = new QLabel();
    if (!producto.disponible) {
        labelEstado->setText("Sin Stock");
        labelEstado->setStyleSheet("color: red; font-weight: bold;");
    } else {
        labelEstado->setText("Disponible");
        labelEstado->setStyleSheet("color: green; font-weight: bold;");
    }
    
    QVBoxLayout* layoutBotones = new QVBoxLayout();
    layoutBotones->addWidget(btnAgregar);
    layoutBotones->addWidget(labelEstado);
    layoutBotones->addStretch();
    
    layoutProducto->addWidget(labelImagen);
    layoutProducto->addLayout(layoutInfo, 1);
    layoutProducto->addLayout(layoutBotones);
    
    layout->addWidget(frameProducto);
}

void PanelCajero::buscarCliente()
{
    QString textoBusqueda = ui->lineEdit_buscarCliente->text().trimmed();
    if (textoBusqueda.isEmpty()) {
        mostrarMensajeError("Ingrese un nombre o teléfono para buscar");
        return;
    }
    
    QVector<Cliente> clientesEncontrados = buscarClientesPorTexto(textoBusqueda);
    
    if (clientesEncontrados.isEmpty()) {
        mostrarMensajeError("No se encontraron clientes con ese criterio de búsqueda");
        limpiarSeleccionCliente();
        return;
    }
    
    if (clientesEncontrados.size() == 1) {
        seleccionarCliente(clientesEncontrados.first());
    } else {
        // Si hay múltiples resultados, mostrar el primero o implementar selector
        seleccionarCliente(clientesEncontrados.first());
        // Podrías implementar aquí un diálogo para seleccionar entre múltiples clientes
    }
}

QVector<Cliente> PanelCajero::buscarClientesPorTexto(const QString& texto)
{
    QVector<Cliente> resultado;
    
    for (const Cliente& cliente : clientes) {
        QString nombreCompleto = cliente.nombre + " " + cliente.apellido;
        if (nombreCompleto.contains(texto, Qt::CaseInsensitive) ||
            cliente.telefono.contains(texto)) {
            resultado.append(cliente);
        }
    }
    
    return resultado;
}

void PanelCajero::seleccionarCliente(const Cliente& cliente)
{
    clienteSeleccionado = cliente;
    clienteEstaSeleccionado = true;
    
    ui->label_nombreCliente->setText(cliente.nombre + " " + cliente.apellido);
    ui->label_telefonoCliente->setText("Teléfono: " + cliente.telefono);
    ui->label_direccionCliente->setText("Dirección: " + cliente.direccion);
    ui->label_emailCliente->setText("Email: " + cliente.email);
    
    calcularPrecioDelivery(cliente.direccion);
    actualizarTotales();
    validarCreacionPedido();
}

void PanelCajero::limpiarSeleccionCliente()
{
    clienteEstaSeleccionado = false;
    
    ui->label_nombreCliente->setText("Cliente no seleccionado");
    ui->label_telefonoCliente->setText("Teléfono: -");
    ui->label_direccionCliente->setText("Dirección: -");
    ui->label_emailCliente->setText("Email: -");
    
    precioDelivery = 0.0;
    actualizarTotales();
    validarCreacionPedido();
}

void PanelCajero::filtrarProductos()
{
    QString categoriaSeleccionada = ui->comboBox_categorias->currentText();
    QString filtroNombre = ui->lineEdit_buscarProducto->text();
    mostrarProductos(categoriaSeleccionada, filtroNombre);
}

void PanelCajero::buscarProductoPorNombre()
{
    filtrarProductos();
}

void PanelCajero::agregarProductoAlCarrito(int productoId)
{
    // Buscar el producto
    Producto* producto = nullptr;
    for (auto& p : productos) {
        if (p.id == productoId) {
            producto = &p;
            break;
        }
    }
    
    if (!producto || !producto->disponible) {
        mostrarMensajeError("Producto no disponible");
        return;
    }
    
    // Verificar si ya está en el carrito
    bool encontrado = false;
    for (auto& item : carrito) {
        if (item.producto.id == productoId) {
            item.cantidad++;
            item.precioTotal = item.cantidad * item.producto.precio;
            encontrado = true;
            break;
        }
    }
    
    if (!encontrado) {
        ItemCarrito nuevoItem;
        nuevoItem.producto = *producto;
        nuevoItem.cantidad = 1;
        nuevoItem.precioTotal = producto->precio;
        carrito.append(nuevoItem);
    }
    
    actualizarCarritoVisual();
    actualizarTotales();
    validarCreacionPedido();
}

void PanelCajero::eliminarDelCarrito(int index)
{
    if (index >= 0 && index < carrito.size()) {
        carrito.removeAt(index);
        actualizarCarritoVisual();
        actualizarTotales();
        validarCreacionPedido();
    }
}

void PanelCajero::modificarCantidad(int index, int nuevaCantidad)
{
    if (index >= 0 && index < carrito.size() && nuevaCantidad > 0) {
        carrito[index].cantidad = nuevaCantidad;
        carrito[index].precioTotal = nuevaCantidad * carrito[index].producto.precio;
        actualizarCarritoVisual();
        actualizarTotales();
    }
}

void PanelCajero::actualizarCarritoVisual()
{
    // Limpiar layout del carrito
    QLayout* layout = ui->scrollAreaWidgetContents_carrito->layout();
    if (layout) {
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete layout;
    }
    
    QVBoxLayout* carritoLayout = new QVBoxLayout(ui->scrollAreaWidgetContents_carrito);
    carritoLayout->setSpacing(5);
    
    for (int i = 0; i < carrito.size(); ++i) {
        const ItemCarrito& item = carrito[i];
        
        QFrame* frameItem = new QFrame();
        frameItem->setStyleSheet("QFrame { background-color: #f9f9f9; border-radius: 6px; padding: 4px; }");
        frameItem->setMaximumHeight(80);
        
        QHBoxLayout* layoutItem = new QHBoxLayout(frameItem);
        
        // Nombre del producto
        QVBoxLayout* layoutInfo = new QVBoxLayout();
        QLabel* labelNombre = new QLabel(item.producto.nombre);
        labelNombre->setFont(QFont("Segoe UI", 10, QFont::Bold));
        
        QLabel* labelPrecio = new QLabel(QString("$%1 c/u").arg(item.producto.precio, 0, 'f', 2));
        labelPrecio->setStyleSheet("color: #666; font-size: 9px;");
        
        layoutInfo->addWidget(labelNombre);
        layoutInfo->addWidget(labelPrecio);
        
        // Controles de cantidad
        QHBoxLayout* layoutControles = new QHBoxLayout();
        
        QPushButton* btnMenos = new QPushButton("-");
        btnMenos->setFixedSize(25, 25);
        btnMenos->setStyleSheet("QPushButton { background-color: #ddd; border: none; border-radius: 3px; font-weight: bold; }");
        
        QLabel* labelCantidad = new QLabel(QString::number(item.cantidad));
        labelCantidad->setAlignment(Qt::AlignCenter);
        labelCantidad->setFixedWidth(30);
        
        QPushButton* btnMas = new QPushButton("+");
        btnMas->setFixedSize(25, 25);
        btnMas->setStyleSheet("QPushButton { background-color: #ddd; border: none; border-radius: 3px; font-weight: bold; }");
        
        QPushButton* btnEliminar = new QPushButton("×");
        btnEliminar->setFixedSize(25, 25);
        btnEliminar->setStyleSheet("QPushButton { background-color: red; color: white; border: none; border-radius: 3px; font-weight: bold; }");
        
        QLabel* labelTotal = new QLabel(QString("$%1").arg(item.precioTotal, 0, 'f', 2));
        labelTotal->setFont(QFont("Segoe UI", 10, QFont::Bold));
        labelTotal->setStyleSheet("color: rgb(200, 30, 45);");
        
        // Conectar eventos
        connect(btnMenos, &QPushButton::clicked, [this, i]() {
            if (carrito[i].cantidad > 1) {
                modificarCantidad(i, carrito[i].cantidad - 1);
            }
        });
        
        connect(btnMas, &QPushButton::clicked, [this, i]() {
            modificarCantidad(i, carrito[i].cantidad + 1);
        });
        
        connect(btnEliminar, &QPushButton::clicked, [this, i]() {
            eliminarDelCarrito(i);
        });
        
        layoutControles->addWidget(btnMenos);
        layoutControles->addWidget(labelCantidad);
        layoutControles->addWidget(btnMas);
        layoutControles->addWidget(btnEliminar);
        
        QVBoxLayout* layoutDerecha = new QVBoxLayout();
        layoutDerecha->addLayout(layoutControles);
        layoutDerecha->addWidget(labelTotal);
        
        layoutItem->addLayout(layoutInfo, 1);
        layoutItem->addLayout(layoutDerecha);
        
        carritoLayout->addWidget(frameItem);
    }
    
    if (carrito.isEmpty()) {
        QLabel* labelVacio = new QLabel("Carrito vacío");
        labelVacio->setAlignment(Qt::AlignCenter);
        labelVacio->setStyleSheet("color: #999; font-style: italic;");
        carritoLayout->addWidget(labelVacio);
    }
    
    carritoLayout->addStretch();
}

void PanelCajero::actualizarTotales()
{
    subtotal = 0.0;
    for (const ItemCarrito& item : carrito) {
        subtotal += item.precioTotal;
    }
    
    total = subtotal + precioDelivery;
    
    ui->label_subtotal->setText(QString("Subtotal: $%1").arg(subtotal, 0, 'f', 2));
    ui->label_delivery->setText(QString("Delivery: $%1").arg(precioDelivery, 0, 'f', 2));
    ui->label_total->setText(QString("Total: $%1").arg(total, 0, 'f', 2));
}

void PanelCajero::calcularPrecioDelivery(const QString& direccion)
{
    double distancia = calcularDistancia(direccion);
    
    // Lógica simple de precio por distancia
    if (distancia <= 1.0) {
        precioDelivery = 200.0; // Zona cercana
    } else if (distancia <= 3.0) {
        precioDelivery = 350.0; // Zona media
    } else if (distancia <= 5.0) {
        precioDelivery = 500.0; // Zona lejana
    } else {
        precioDelivery = 700.0; // Zona muy lejana
    }
}

double PanelCajero::calcularDistancia(const QString& direccionDestino)
{
    // Implementación simplificada
    // En una implementación real, usarías una API de mapas
    Q_UNUSED(direccionDestino)
    return 2.5; // Distancia simulada
}

void PanelCajero::toggleTipoPedido()
{
    bool esProgramado = ui->radioButton_programado->isChecked();
    ui->frame_programacion->setEnabled(esProgramado);
    
    if (esProgramado) {
        ui->dateEdit_fecha->setDate(QDate::currentDate());
        ui->timeEdit_hora->setTime(horaApertura1);
    }
    
    validarCreacionPedido();
}

// Implementación para validar la creación del pedido
bool PanelCajero::validarCreacionPedido()
{
    // Verificar si el carrito está vacío
    if (carrito.isEmpty()) {
        mostrarMensajeError("El carrito está vacío. Agregue productos antes de crear un pedido.");
        return false;
    }
    
    // Verificar si hay un cliente seleccionado
    if (!clienteEstaSeleccionado) {
        mostrarMensajeError("Debe seleccionar un cliente para crear el pedido.");
        return false;
    }
    
    // Validar según el tipo de pedido (inmediato o programado)
    if (ui->radioButton_inmediato->isChecked()) {
        return validarPedidoInmediato();
    } else if (ui->radioButton_programado->isChecked()) {
        QDateTime fechaHora(ui->dateEdit_fecha->date(), ui->timeEdit_hora->time());
        return validarPedidoProgramado(fechaHora);
    }
    
    return true;
}

bool PanelCajero::validarPedidoInmediato()
{
    QTime ahora = QTime::currentTime();
    return (ahora >= horaApertura1 && ahora <= horaCierre1) ||
           (ahora >= horaApertura2 && ahora <= horaCierre2);
}

bool PanelCajero::validarPedidoProgramado(const QDateTime& fechaHora)
{
    QTime hora = fechaHora.time();
    return (hora >= horaApertura1 && hora <= horaCierre1) ||
           (hora >= horaApertura2 && hora <= horaCierre2);
}

// Única implementación para validar la creación del pedido
bool PanelCajero::validarCreacionPedido()
{
    // Verificar si el carrito está vacío
    if (carrito.isEmpty()) {
        mostrarMensajeError("El carrito está vacío. Agregue productos antes de crear un pedido.");
        return false;
    }
    
    // Verificar si hay un cliente seleccionado
    if (!clienteEstaSeleccionado) {
        mostrarMensajeError("Debe seleccionar un cliente para crear el pedido.");
        return false;
    }
    
    // Validar según el tipo de pedido (inmediato o programado)
    if (ui->radioButton_inmediato->isChecked()) {
        if (!validarPedidoInmediato()) {
            mostrarMensajeError("No se puede crear un pedido inmediato fuera del horario laboral");
            return false;
        }
    } else if (ui->radioButton_programado->isChecked()) {
        QDateTime fechaHora(ui->dateEdit_fecha->date(), ui->timeEdit_hora->time());
        if (!validarPedidoProgramado(fechaHora)) {
            mostrarMensajeError("No se puede programar un pedido fuera del horario laboral");
            return false;
        }
    }
    
    return true;
}

void PanelCajero::crearPedido()
{
    if (!validarCreacionPedido()) {
        mostrarMensajeError("No se puede crear el pedido en este momento");
        return;
    }
    
    QSqlQuery query(db);
    
    // Iniciar transacción
    db.transaction();
    
    try {
        // Crear el pedido
        query.prepare("INSERT INTO pedidos (numero_pedido, usuario_id, tipo_pedido, fecha_pedido, "
                      "fecha_entrega_programada, direccion_entrega, telefono_contacto, metodo_pago, "
                      "estado, subtotal, precio_delivery, total, cajero_id) "
                      "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
        
        QString numeroPedido = generarNumeroPedido();
        QString tipoPedido = ui->radioButton_inmediato->isChecked() ? "inmediato" : "programado";
        QDateTime fechaEntrega;
        
        if (ui->radioButton_programado->isChecked()) {
            fechaEntrega = QDateTime(ui->dateEdit_fecha->date(), ui->timeEdit_hora->time());
        }
        
        query.addBindValue(numeroPedido);
        query.addBindValue(clienteSeleccionado.id);
        query.addBindValue(tipoPedido);
        query.addBindValue(QDateTime::currentDateTime());
        query.addBindValue(fechaEntrega.isValid() ? fechaEntrega : QVariant());
        query.addBindValue(clienteSeleccionado.direccion);
        query.addBindValue(clienteSeleccionado.telefono);
        query.addBindValue("efectivo");
        query.addBindValue("pendiente");
        query.addBindValue(subtotal);
        query.addBindValue(precioDelivery);
        query.addBindValue(total);
        query.addBindValue(1); // ID del cajero actual - deberías obtenerlo del login
        
        if (!query.exec()) {
            throw QString("Error al crear el pedido: " + query.lastError().text());
        }
        
        int pedidoId = query.lastInsertId().toInt();
        
        // Agregar los items del pedido
        for (const ItemCarrito& item : carrito) {
            query.prepare("INSERT INTO pedido_items (pedido_id, producto_id, cantidad, precio_unitario, precio_total) "
                          "VALUES (?, ?, ?, ?, ?)");
            query.addBindValue(pedidoId);
            query.addBindValue(item.producto.id);
            query.addBindValue(item.cantidad);
            query.addBindValue(item.producto.precio);
            query.addBindValue(item.precioTotal);
            
            if (!query.exec()) {
                throw QString("Error al agregar items del pedido: " + query.lastError().text());
            }
        }
        
        // Agregar seguimiento del pedido
        query.prepare("INSERT INTO seguimiento_pedidos (pedido_id, estado_anterior, estado_nuevo, usuario_cambio_id, comentarios) "
                      "VALUES (?, ?, ?, ?, ?)");
        query.addBindValue(pedidoId);
        query.addBindValue(QVariant());
        query.addBindValue("pendiente");
        query.addBindValue(1); // ID del cajero actual
        query.addBindValue("Pedido creado por cajero");
        
        if (!query.exec()) {
            throw QString("Error al crear seguimiento: " + query.lastError().text());
        }
        
        // Confirmar transacción
        db.commit();
        
        mostrarMensajeExito(QString("Pedido creado exitosamente. Número: %1").arg(numeroPedido));
        limpiarCarrito();
        limpiarSeleccionCliente();
        
    } catch (const QString& error) {
        db.rollback();
        mostrarMensajeError(error);
    }
}

QString PanelCajero::generarNumeroPedido()
{
    return QString("P%1%2")
        .arg(QDate::currentDate().toString("yyyyMMdd"))
        .arg(QTime::currentTime().toString("hhmmss"));
}

void PanelCajero::limpiarCarrito()
{
    carrito.clear();
    actualizarCarritoVisual();
    actualizarTotales();
    validarCreacionPedido();
}

void PanelCajero::mostrarMensajeError(const QString& mensaje)
{
    QMessageBox::warning(this, "Error", mensaje);
}

void PanelCajero::mostrarMensajeExito(const QString& mensaje)
{
    QMessageBox::information(this, "Éxito", mensaje);
}