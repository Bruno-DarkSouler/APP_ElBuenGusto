#include "cajero.h"
#include "ui_cajero.h"
#include <QDebug>
#include <cmath>

PanelCajero::PanelCajero(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PanelCajero)
    , clienteEstaSeleccionado(false)
    , subtotal(0.0)
    , precioDelivery(0.0)
    , total(0.0)
    , horaApertura1(QTime(11, 0))
    , horaCierre1(QTime(15, 0))
    , horaApertura2(QTime(19, 0))
    , horaCierre2(QTime(23, 0))
    , networkManager(new QNetworkAccessManager(this))
    , apiUrl("http://localhost/WEB_ElBuenGusto/api/cajero.php")
    , relojTimer(new QTimer(this))
{
    ui->setupUi(this);

    cargarConfiguracion();
    configurarEventos();
    cargarDatosDesdeAPI();
    
    connect(relojTimer, &QTimer::timeout, this, &PanelCajero::actualizarReloj);
    relojTimer->start(1000);
    actualizarReloj();
}

PanelCajero::~PanelCajero()
{
    delete ui;
}

void PanelCajero::configurarEventos()
{
    connect(ui->pushButton_buscarCliente, &QPushButton::clicked, this, &PanelCajero::buscarCliente);
    connect(ui->pushButton_limpiarCliente, &QPushButton::clicked, this, &PanelCajero::limpiarSeleccionCliente);
    connect(ui->comboBox_categorias, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &PanelCajero::filtrarProductos);
    connect(ui->lineEdit_buscarProducto, &QLineEdit::textChanged, this, &PanelCajero::buscarProductoPorNombre);
    connect(ui->pushButton_crearPedido, &QPushButton::clicked, this, &PanelCajero::crearPedido);
    connect(ui->radioButton_inmediato, &QRadioButton::toggled, this, &PanelCajero::toggleTipoPedido);
    connect(ui->radioButton_programado, &QRadioButton::toggled, this, &PanelCajero::toggleTipoPedido);
    
    ui->dateEdit_fecha->setDate(QDate::currentDate());
    ui->dateEdit_fecha->setMinimumDate(QDate::currentDate());
    ui->timeEdit_hora->setTime(QTime::currentTime());
}

void PanelCajero::cargarConfiguracion()
{
    // Configuración por defecto
}

void PanelCajero::cargarDatosDesdeAPI()
{
    QNetworkRequest request;
    request.setUrl(QUrl(apiUrl));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    
    QNetworkReply *reply = networkManager->get(request);
    
    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            procesarRespuestaCajero(reply);
        } else {
            mostrarMensajeError("Error al conectar con la API: " + reply->errorString());
            cargarProductos();
            cargarClientes();
            mostrarProductos();
        }
        reply->deleteLater();
    });
}

void PanelCajero::procesarRespuestaCajero(QNetworkReply *reply)
{
    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    
    if (jsonDoc.isObject()) {
        QJsonObject obj = jsonDoc.object();
        
        // Procesar datos de ejemplo
        qDebug() << "Datos recibidos del cajero:" << obj;
    }
    
    cargarProductos();
    cargarClientes();
    mostrarProductos();
}

void PanelCajero::cargarProductos()
{
    productos.clear();
    
    // Productos de ejemplo para pruebas
    Producto p1;
    p1.id = 1;
    p1.nombre = "Milanesa con papas";
    p1.descripcion = "Milanesa de carne con papas fritas";
    p1.precio = 2500.0;
    p1.imagen = "hamburguesa.jpeg";
    p1.categoriaId = 1;
    p1.disponible = true;
    p1.activo = true;
    productos.append(p1);
    
    Producto p2;
    p2.id = 2;
    p2.nombre = "Empanadas (docena)";
    p2.descripcion = "Docena de empanadas de carne";
    p2.precio = 3000.0;
    p2.imagen = "hamburguesa.jpeg";
    p2.categoriaId = 5;
    p2.disponible = true;
    p2.activo = true;
    productos.append(p2);
    
    Producto p3;
    p3.id = 3;
    p3.nombre = "Tarta de jamón y queso";
    p3.descripcion = "Tarta casera de jamón y queso";
    p3.precio = 1800.0;
    p3.imagen = "hamburguesa.jpeg";
    p3.categoriaId = 4;
    p3.disponible = true;
    p3.activo = true;
    productos.append(p3);
}

void PanelCajero::cargarClientes()
{
    clientes.clear();
    
    // Clientes de ejemplo
    Cliente c1;
    c1.id = 1;
    c1.nombre = "Juan";
    c1.apellido = "Pérez";
    c1.email = "juan@example.com";
    c1.telefono = "1122334455";
    c1.direccion = "Av. Siempreviva 742";
    c1.activo = true;
    clientes.append(c1);
    
    Cliente c2;
    c2.id = 2;
    c2.nombre = "María";
    c2.apellido = "González";
    c2.email = "maria@example.com";
    c2.telefono = "1155667788";
    c2.direccion = "Calle Falsa 123";
    c2.activo = true;
    clientes.append(c2);
}

void PanelCajero::mostrarProductos()
{
    mostrarProductos("Todas las categorías");
}

void PanelCajero::mostrarProductos(const QString& filtroCategoria, const QString& filtroNombre)
{
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
    
    QVector<Producto> productosFiltrados;
    
    for (const Producto& producto : productos) {
        bool coincideCategoria = (filtroCategoria == "Todas las categorías");
        
        bool coincideNombre = filtroNombre.isEmpty() || 
                             producto.nombre.contains(filtroNombre, Qt::CaseInsensitive);
        
        if (coincideCategoria && coincideNombre) {
            productosFiltrados.append(producto);
        }
    }
    
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
    
    QLabel* labelImagen = new QLabel();
    labelImagen->setFixedSize(80, 80);
    labelImagen->setScaledContents(true);
    labelImagen->setStyleSheet("border-radius: 6px;");
    
    if (!producto.imagen.isEmpty()) {
        QPixmap pixmap(":/" + producto.imagen);
        if (!pixmap.isNull()) {
            labelImagen->setPixmap(pixmap);
        } else {
            labelImagen->setText("Sin\nImagen");
            labelImagen->setAlignment(Qt::AlignCenter);
        }
    }
    
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
    
    if (clientesEncontrados.size() >= 1) {
        seleccionarCliente(clientesEncontrados.first());
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
        frameItem->setMaximumHeight(120);
        
        QHBoxLayout* layoutItem = new QHBoxLayout(frameItem);
        
        QVBoxLayout* layoutInfo = new QVBoxLayout();
        QLabel* labelNombre = new QLabel(item.producto.nombre);
        labelNombre->setFont(QFont("Segoe UI", 10, QFont::Bold));
        
        QLabel* labelPrecio = new QLabel(QString("$%1 c/u").arg(item.producto.precio, 0, 'f', 2));
        labelPrecio->setStyleSheet("color: #666; font-size: 9px;");
        
        layoutInfo->addWidget(labelNombre);
        layoutInfo->addWidget(labelPrecio);
        
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
    
    if (distancia <= 1.0) {
        precioDelivery = 200.0;
    } else if (distancia <= 3.0) {
        precioDelivery = 350.0;
    } else if (distancia <= 5.0) {
        precioDelivery = 500.0;
    } else {
        precioDelivery = 700.0;
    }
}

double PanelCajero::calcularDistancia(const QString& direccionDestino)
{
    Q_UNUSED(direccionDestino)
    return 2.5;
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

bool PanelCajero::validarCreacionPedido()
{
    bool valido = !carrito.isEmpty() && clienteEstaSeleccionado;
    
    if (valido) {
        if (ui->radioButton_inmediato->isChecked()) {
            valido = validarPedidoInmediato();
        } else if (ui->radioButton_programado->isChecked()) {
            QDateTime fechaHora(ui->dateEdit_fecha->date(), ui->timeEdit_hora->time());
            valido = validarPedidoProgramado(fechaHora);
        }
    }
    
    ui->pushButton_crearPedido->setEnabled(valido);
    return valido;
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

void PanelCajero::crearPedido()
{
    if (!validarCreacionPedido()) {
        mostrarMensajeError("No se puede crear el pedido en este momento");
        return;
    }
    
    QString numeroPedido = generarNumeroPedido();
    mostrarMensajeExito(QString("Pedido creado exitosamente. Número: %1").arg(numeroPedido));
    limpiarCarrito();
    limpiarSeleccionCliente();
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

void PanelCajero::actualizarReloj()
{
    QTime horaActual = QTime::currentTime();
    ui->label_hora->setText(horaActual.toString("HH:mm:ss"));
}

QVector<Producto> PanelCajero::filtrarProductosPorCategoria(int categoriaId)
{
    QVector<Producto> resultado;
    for (const Producto& p : productos) {
        if (p.categoriaId == categoriaId) {
            resultado.append(p);
        }
    }
    return resultado;
}

QVector<Producto> PanelCajero::buscarProductosPorNombre(const QString& nombre)
{
    QVector<Producto> resultado;
    for (const Producto& p : productos) {
        if (p.nombre.contains(nombre, Qt::CaseInsensitive)) {
            resultado.append(p);
        }
    }
    return resultado;
}
