#include "cajero.h"
#include "ui_cajero.h"
#include <QDebug>
#include <cmath>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

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
    , apiUrl("http://localhost/WEB_ElBuenGusto/apiQT/cajero.php")
    , relojTimer(new QTimer(this))
    , groupBoxNuevoCliente(nullptr)
{
    ui->setupUi(this);
    
    crearFormularioNuevoCliente();
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

void PanelCajero::crearFormularioNuevoCliente()
{
    groupBoxNuevoCliente = new QGroupBox("Registrar Nuevo Cliente");
    groupBoxNuevoCliente->setMaximumSize(16777215, 300);
    groupBoxNuevoCliente->setFont(QFont("Segoe UI", 12, QFont::Bold));
    groupBoxNuevoCliente->setStyleSheet(
        "QGroupBox { background-color: white; border-radius: 8px; "
        "padding-top: 15px; color: rgb(80,50,20); } "
        "QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 8px; }"
    );
    groupBoxNuevoCliente->setVisible(false);
    
    QVBoxLayout* layoutNuevoCliente = new QVBoxLayout(groupBoxNuevoCliente);
    
    QHBoxLayout* layoutNombres = new QHBoxLayout();
    QLabel* lblNombre = new QLabel("Nombre:");
    lineEditNuevoNombre = new QLineEdit();
    lineEditNuevoNombre->setStyleSheet("padding: 6px; border: 2px solid #ddd; border-radius: 4px;");
    lineEditNuevoNombre->setPlaceholderText("Ingrese nombre");
    
    QLabel* lblApellido = new QLabel("Apellido:");
    lineEditNuevoApellido = new QLineEdit();
    lineEditNuevoApellido->setStyleSheet("padding: 6px; border: 2px solid #ddd; border-radius: 4px;");
    lineEditNuevoApellido->setPlaceholderText("Ingrese apellido");
    
    layoutNombres->addWidget(lblNombre);
    layoutNombres->addWidget(lineEditNuevoNombre);
    layoutNombres->addWidget(lblApellido);
    layoutNombres->addWidget(lineEditNuevoApellido);
    
    QHBoxLayout* layoutContacto = new QHBoxLayout();
    QLabel* lblTelefono = new QLabel("Teléfono:");
    lineEditNuevoTelefono = new QLineEdit();
    lineEditNuevoTelefono->setStyleSheet("padding: 6px; border: 2px solid #ddd; border-radius: 4px;");
    lineEditNuevoTelefono->setPlaceholderText("Ej: 3516789123");
    
    QLabel* lblEmail = new QLabel("Email:");
    lineEditNuevoEmail = new QLineEdit();
    lineEditNuevoEmail->setStyleSheet("padding: 6px; border: 2px solid #ddd; border-radius: 4px;");
    lineEditNuevoEmail->setPlaceholderText("ejemplo@email.com");
    
    layoutContacto->addWidget(lblTelefono);
    layoutContacto->addWidget(lineEditNuevoTelefono);
    layoutContacto->addWidget(lblEmail);
    layoutContacto->addWidget(lineEditNuevoEmail);
    
    QLabel* lblDireccion = new QLabel("Dirección:");
    textEditNuevaDireccion = new QTextEdit();
    textEditNuevaDireccion->setMaximumHeight(60);
    textEditNuevaDireccion->setStyleSheet("padding: 6px; border: 2px solid #ddd; border-radius: 4px;");
    textEditNuevaDireccion->setPlaceholderText("Dirección completa");
    
    QHBoxLayout* layoutBotones = new QHBoxLayout();
    btnGuardarNuevoCliente = new QPushButton("Guardar Cliente");
    btnGuardarNuevoCliente->setStyleSheet(
        "QPushButton { background-color: rgb(200, 30, 45); color: white; "
        "border: none; padding: 8px; border-radius: 4px; font-weight: bold; } "
        "QPushButton:hover { background-color: rgb(180, 25, 40); }"
    );
    
    btnCancelarNuevoCliente = new QPushButton("Cancelar");
    btnCancelarNuevoCliente->setStyleSheet(
        "QPushButton { background-color: #666; color: white; border: none; "
        "padding: 8px; border-radius: 4px; font-weight: bold; } "
        "QPushButton:hover { background-color: #555; }"
    );
    
    layoutBotones->addWidget(btnGuardarNuevoCliente);
    layoutBotones->addWidget(btnCancelarNuevoCliente);
    layoutBotones->addStretch();
    
    layoutNuevoCliente->addLayout(layoutNombres);
    layoutNuevoCliente->addLayout(layoutContacto);
    layoutNuevoCliente->addWidget(lblDireccion);
    layoutNuevoCliente->addWidget(textEditNuevaDireccion);
    layoutNuevoCliente->addLayout(layoutBotones);
    
    connect(btnGuardarNuevoCliente, &QPushButton::clicked, this, &PanelCajero::guardarNuevoCliente);
    connect(btnCancelarNuevoCliente, &QPushButton::clicked, this, &PanelCajero::ocultarFormularioNuevoCliente);
    
    QVBoxLayout* layoutRight = qobject_cast<QVBoxLayout*>(ui->frame_right->layout());
    if (layoutRight) {
        layoutRight->insertWidget(1, groupBoxNuevoCliente);
    }
}


void PanelCajero::configurarEventos()
{
    connect(ui->pushButton_buscarCliente, &QPushButton::clicked, this, &PanelCajero::buscarCliente);
    connect(ui->pushButton_limpiarCliente, &QPushButton::clicked, this, &PanelCajero::limpiarBusquedaCliente);
    connect(ui->comboBox_categorias, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &PanelCajero::onCategoriaChanged);
    connect(ui->lineEdit_buscarProducto, &QLineEdit::textChanged, this, &PanelCajero::buscarProductoPorNombre);
    connect(ui->pushButton_crearPedido, &QPushButton::clicked, this, &PanelCajero::crearPedido);
    connect(ui->radioButton_inmediato, &QRadioButton::toggled, this, &PanelCajero::toggleTipoPedido);
    connect(ui->radioButton_programado, &QRadioButton::toggled, this, &PanelCajero::toggleTipoPedido);
    connect(ui->timeEdit_hora, &QTimeEdit::userTimeChanged, this, &PanelCajero::on_timeEdit_hora_userTimeChanged);

    
    ui->dateEdit_fecha->setDate(QDate::currentDate());
    ui->dateEdit_fecha->setMinimumDate(QDate::currentDate());
    ui->timeEdit_hora->setTime(QTime::currentTime());
}

void PanelCajero::cargarConfiguracion()
{
    // Configuración por defecto
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
        QMessageBox::StandardButton respuesta = QMessageBox::question(
            this, 
            "Cliente no encontrado",
            "No se encontró ningún cliente con ese criterio.\n¿Desea registrar un nuevo cliente?",
            QMessageBox::Yes | QMessageBox::No
        );
        
        if (respuesta == QMessageBox::Yes) {
            mostrarFormularioNuevoCliente();
        }
        return;
    }
    
    if (clientesEncontrados.size() >= 1) {
        seleccionarCliente(clientesEncontrados.first());
    }
}

void PanelCajero::limpiarBusquedaCliente()
{
    ui->lineEdit_buscarCliente->clear();
    limpiarSeleccionCliente();
}

void PanelCajero::mostrarFormularioNuevoCliente()
{
    if (groupBoxNuevoCliente) {
        groupBoxNuevoCliente->setVisible(true);
        ui->groupBox_datosCliente->setVisible(false);
        
        // Limpiar campos
        lineEditNuevoNombre->clear();
        lineEditNuevoApellido->clear();
        lineEditNuevoEmail->clear();
        lineEditNuevoTelefono->clear();
        textEditNuevaDireccion->clear();
        
        lineEditNuevoNombre->setFocus();
    }
}

void PanelCajero::ocultarFormularioNuevoCliente()
{
    if (groupBoxNuevoCliente) {
        groupBoxNuevoCliente->setVisible(false);
        ui->groupBox_datosCliente->setVisible(true);
    }
}

bool PanelCajero::validarDatosNuevoCliente()
{
    if (lineEditNuevoNombre->text().trimmed().isEmpty()) {
        mostrarMensajeError("El nombre es obligatorio");
        return false;
    }
    
    if (lineEditNuevoApellido->text().trimmed().isEmpty()) {
        mostrarMensajeError("El apellido es obligatorio");
        return false;
    }
    
    if (lineEditNuevoTelefono->text().trimmed().isEmpty()) {
        mostrarMensajeError("El teléfono es obligatorio");
        return false;
    }
    
    QString telefono = lineEditNuevoTelefono->text().trimmed();
    if (telefono.length() < 10) {
        mostrarMensajeError("El teléfono debe tener al menos 10 dígitos");
        return false;
    }
    
    if (lineEditNuevoEmail->text().trimmed().isEmpty()) {
        mostrarMensajeError("El email es obligatorio");
        return false;
    }
    
    QString email = lineEditNuevoEmail->text().trimmed();
    if (!email.contains("@") || !email.contains(".")) {
        mostrarMensajeError("El email no es válido");
        return false;
    }
    
    if (textEditNuevaDireccion->toPlainText().trimmed().isEmpty()) {
        mostrarMensajeError("La dirección es obligatoria");
        return false;
    }
    
    return true;
}

void PanelCajero::guardarNuevoCliente()
{
    if (!validarDatosNuevoCliente()) {
        return;
    }
    
    Cliente nuevoCliente;
    nuevoCliente.id = clientes.size() + 100; // ID temporal
    nuevoCliente.nombre = lineEditNuevoNombre->text().trimmed();
    nuevoCliente.apellido = lineEditNuevoApellido->text().trimmed();
    nuevoCliente.email = lineEditNuevoEmail->text().trimmed();
    nuevoCliente.telefono = lineEditNuevoTelefono->text().trimmed();
    nuevoCliente.direccion = textEditNuevaDireccion->toPlainText().trimmed();
    nuevoCliente.activo = true;
    nuevoCliente.esNuevo = true;
    
    // Agregar a la lista de clientes
    clientes.append(nuevoCliente);
    
    // Seleccionar el nuevo cliente
    seleccionarCliente(nuevoCliente);
    
    // Ocultar formulario
    ocultarFormularioNuevoCliente();
    
    mostrarMensajeExito("Cliente registrado exitosamente");
    
    // Aquí se enviaría a la API en un entorno real
    QJsonObject clienteJson;
    clienteJson["nombre"] = nuevoCliente.nombre;
    clienteJson["apellido"] = nuevoCliente.apellido;
    clienteJson["email"] = nuevoCliente.email;
    clienteJson["telefono"] = nuevoCliente.telefono;
    clienteJson["direccion"] = nuevoCliente.direccion;
    
    qDebug() << "Nuevo cliente a guardar en BD:" << clienteJson;
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

void PanelCajero::onCategoriaChanged(int index)
{
    filtrarProductos();
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
    
    for (const Producto& producto : todosLosProductos) {
        bool coincideCategoria = (filtroCategoria == "Todas las categorías" || 
                                  producto.categoriaNombre == filtroCategoria);
        
        bool coincideNombre = filtroNombre.isEmpty() || 
                             producto.nombre.contains(filtroNombre, Qt::CaseInsensitive) ||
                             producto.descripcion.contains(filtroNombre, Qt::CaseInsensitive);
        
        if (coincideCategoria && coincideNombre) {
            productosFiltrados.append(producto);
        }
    }
    
    if (productosFiltrados.isEmpty()) {
        QLabel* labelVacio = new QLabel("No se encontraron productos con los filtros seleccionados");
        labelVacio->setAlignment(Qt::AlignCenter);
        labelVacio->setStyleSheet("color: #666; font-size: 14px; padding: 20px;");
        productosLayout->addWidget(labelVacio);
    } else {
        for (const Producto& producto : productosFiltrados) {
            crearWidgetProducto(producto, productosLayout);
        }
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
        // Intentar cargar desde URL
        QNetworkAccessManager *imgManager = new QNetworkAccessManager(this);
        QNetworkRequest imgRequest(QUrl(producto.imagen));

        QNetworkReply *imgReply = imgManager->get(imgRequest);

        connect(imgReply, &QNetworkReply::finished, [labelImagen, imgReply]() {
            if (imgReply->error() == QNetworkReply::NoError) {
                QByteArray imageData = imgReply->readAll();
                QPixmap pixmap;
                if (pixmap.loadFromData(imageData)) {
                    labelImagen->setPixmap(pixmap);
                } else {
                    labelImagen->setText("Sin\nImagen");
                    labelImagen->setAlignment(Qt::AlignCenter);
                    labelImagen->setStyleSheet("border-radius: 6px; color: #999; font-size: 9px;");
                }
            } else {
                labelImagen->setText("Sin\nImagen");
                labelImagen->setAlignment(Qt::AlignCenter);
                labelImagen->setStyleSheet("border-radius: 6px; color: #999; font-size: 9px;");
            }
            imgReply->deleteLater();
        });
    } else {
        labelImagen->setText("Sin\nImagen");
        labelImagen->setAlignment(Qt::AlignCenter);
        labelImagen->setStyleSheet("border-radius: 6px; color: #999; font-size: 9px;");
    }
    
    QVBoxLayout* layoutInfo = new QVBoxLayout();
    
    QLabel* labelNombre = new QLabel(producto.nombre);
    labelNombre->setFont(QFont("Segoe UI", 11, QFont::Bold));
    
    QLabel* labelDescripcion = new QLabel(producto.descripcion);
    labelDescripcion->setWordWrap(true);
    labelDescripcion->setMaximumHeight(35);
    labelDescripcion->setStyleSheet("color: #666; font-size: 9px;");
    
    QHBoxLayout* layoutPrecioTiempo = new QHBoxLayout();
    QLabel* labelPrecio = new QLabel(QString("$%1").arg(producto.precio, 0, 'f', 2));
    labelPrecio->setFont(QFont("Segoe UI", 13, QFont::Bold));
    labelPrecio->setStyleSheet("color: rgb(200, 30, 45);");
    
    QLabel* labelTiempo = new QLabel(QString("⏱ %1 min").arg(producto.tiempoPreparacion));
    labelTiempo->setStyleSheet("color: #666; font-size: 9px;");
    
    layoutPrecioTiempo->addWidget(labelPrecio);
    layoutPrecioTiempo->addWidget(labelTiempo);
    layoutPrecioTiempo->addStretch();
    
    layoutInfo->addWidget(labelNombre);
    layoutInfo->addWidget(labelDescripcion);
    layoutInfo->addLayout(layoutPrecioTiempo);
    
    QPushButton* btnAgregar = new QPushButton("Agregar");
    btnAgregar->setFixedSize(80, 35);
    
    if (producto.disponible) {
        btnAgregar->setStyleSheet(
            "QPushButton { background-color: rgb(200, 30, 45); color: white; border: none; "
            "border-radius: 4px; font-weight: bold; font-size: 10px; } "
            "QPushButton:hover { background-color: rgb(180, 25, 40); }"
        );
        connect(btnAgregar, &QPushButton::clicked, [this, producto]() {
            agregarProductoAlCarrito(producto.id);
        });
    } else {
        btnAgregar->setText("Sin Stock");
        btnAgregar->setEnabled(false);
        btnAgregar->setStyleSheet("QPushButton { background-color: #ccc; color: #999; border: none; border-radius: 4px; font-size: 9px; }");
    }
    
    QVBoxLayout* layoutBotones = new QVBoxLayout();
    layoutBotones->addWidget(btnAgregar);
    layoutBotones->addStretch();
    
    layoutProducto->addWidget(labelImagen);
    layoutProducto->addLayout(layoutInfo, 1);
    layoutProducto->addLayout(layoutBotones);
    
    layout->addWidget(frameProducto);
}

void PanelCajero::agregarProductoAlCarrito(int productoId)
{
    Producto* producto = nullptr;
    for (auto& p : todosLosProductos) {
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
        frameItem->setMaximumHeight(100);
        
        QHBoxLayout* layoutItem = new QHBoxLayout(frameItem);
        
        QVBoxLayout* layoutInfo = new QVBoxLayout();
        QLabel* labelNombre = new QLabel(item.producto.nombre);
        labelNombre->setFont(QFont("Segoe UI", 9, QFont::Bold));
        labelNombre->setWordWrap(true);
        labelNombre->setMaximumHeight(30);
        
        QLabel* labelPrecio = new QLabel(QString("$%1 c/u").arg(item.producto.precio, 0, 'f', 2));
        labelPrecio->setStyleSheet("color: #666; font-size: 8px;");
        
        layoutInfo->addWidget(labelNombre);
        layoutInfo->addWidget(labelPrecio);
        
        QHBoxLayout* layoutControles = new QHBoxLayout();
        
        QPushButton* btnMenos = new QPushButton("-");
        btnMenos->setFixedSize(22, 22);
        btnMenos->setStyleSheet("QPushButton { background-color: #ddd; border: none; border-radius: 3px; font-weight: bold; font-size: 12px; }");
        
        QLabel* labelCantidad = new QLabel(QString::number(item.cantidad));
        labelCantidad->setAlignment(Qt::AlignCenter);
        labelCantidad->setFixedWidth(25);
        labelCantidad->setStyleSheet("font-weight: bold; font-size: 11px;");
        
        QPushButton* btnMas = new QPushButton("+");
        btnMas->setFixedSize(22, 22);
        btnMas->setStyleSheet("QPushButton { background-color: #ddd; border: none; border-radius: 3px; font-weight: bold; font-size: 12px; }");
        
        QPushButton* btnEliminar = new QPushButton("×");
        btnEliminar->setFixedSize(22, 22);
        btnEliminar->setStyleSheet("QPushButton { background-color: red; color: white; border: none; border-radius: 3px; font-weight: bold; font-size: 14px; }");
        
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
        layoutDerecha->setAlignment(Qt::AlignTop);
        
        layoutItem->addLayout(layoutInfo, 1);
        layoutItem->addLayout(layoutDerecha);
        
        carritoLayout->addWidget(frameItem);
    }
    
    if (carrito.isEmpty()) {
        QLabel* labelVacio = new QLabel("Carrito vacío");
        labelVacio->setAlignment(Qt::AlignCenter);
        labelVacio->setStyleSheet("color: #999; font-style: italic; padding: 20px;");
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
    
    if (distancia <= 1.5) {
        precioDelivery = 2000.0;
    } else if (distancia <= 3.0) {
        precioDelivery = 3500.0;
    } else if (distancia <= 5.0) {
        precioDelivery = 5000.0;
    } else if (distancia <= 7.0) {
        precioDelivery = 7000.0;
    } else {
        precioDelivery = 1000.0;
    }
}

double PanelCajero::calcularDistancia(const QString& direccionDestino)
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

void PanelCajero::toggleTipoPedido()
{
    bool esProgramado = ui->radioButton_programado->isChecked();
    ui->frame_programacion->setEnabled(esProgramado);

    if (esProgramado) {
        // Fecha mínima = hoy, máxima = 7 días después
        ui->dateEdit_fecha->setDate(QDate::currentDate());
        ui->dateEdit_fecha->setMinimumDate(QDate::currentDate());
        ui->dateEdit_fecha->setMaximumDate(QDate::currentDate().addDays(7));

        // Hora inicial por defecto: apertura de mañana
        ui->timeEdit_hora->setTime(horaApertura1);
    } else {
        // Si es inmediato, deshabilitamos los campos
        ui->frame_programacion->setEnabled(false);
    }

    validarCreacionPedido();
}

void PanelCajero::on_timeEdit_hora_userTimeChanged(const QTime &hora)
{
    // Si está fuera de rango de horario permitido, se ajusta automáticamente
    bool dentroHorario1 = (hora >= horaApertura1 && hora <= horaCierre1);
    bool dentroHorario2 = (hora >= horaApertura2 && hora <= horaCierre2);

    if (!dentroHorario1 && !dentroHorario2) {
        // Ajusta a la hora más cercana válida
        if (hora < horaApertura1)
            ui->timeEdit_hora->setTime(horaApertura1);
        else if (hora > horaCierre2)
            ui->timeEdit_hora->setTime(horaCierre2);
        else if (hora > horaCierre1 && hora < horaApertura2)
            ui->timeEdit_hora->setTime(horaApertura2);
    }

    validarCreacionPedido();
}


bool PanelCajero::validarCreacionPedido()
{
    qDebug() << "=== Validando creación de pedido ===";
    qDebug() << "Carrito vacío:" << carrito.isEmpty();
    qDebug() << "Cliente seleccionado:" << clienteEstaSeleccionado;

    bool valido = !carrito.isEmpty() && clienteEstaSeleccionado;

    if (valido) {
        if (ui->radioButton_inmediato->isChecked()) {
            qDebug() << "Validando pedido inmediato...";
            valido = validarPedidoInmediato();
            qDebug() << "Pedido inmediato válido:" << valido;
        } else if (ui->radioButton_programado->isChecked()) {
            qDebug() << "Validando pedido programado...";
            QDateTime fechaHora(ui->dateEdit_fecha->date(), ui->timeEdit_hora->time());
            qDebug() << "Fecha/Hora seleccionada:" << fechaHora.toString();
            valido = validarPedidoProgramado(fechaHora);
            qDebug() << "Pedido programado válido:" << valido;
        }
    }

    qDebug() << "Botón habilitado:" << valido;
    ui->pushButton_crearPedido->setEnabled(valido);
    return valido;
}

bool PanelCajero::validarPedidoInmediato()
{
    // Para pruebas, permitir siempre crear pedidos inmediatos
    // Comentar estas líneas cuando quieras activar la validación de horario
    return true;

    // Descomentar estas líneas para validar horarios:
    /*
    QTime ahora = QTime::currentTime();
    return (ahora >= horaApertura1 && ahora <= horaCierre1) ||
           (ahora >= horaApertura2 && ahora <= horaCierre2);
    */
}

bool PanelCajero::validarPedidoProgramado(const QDateTime& fechaHora)
{
    QDateTime ahora = QDateTime::currentDateTime();

    // Permitir al menos 30 minutos de anticipación
    if (fechaHora <= ahora.addSecs(1800)) {
        qDebug() << "Pedido programado debe ser al menos 30 minutos en el futuro";
        return false;
    }

    QTime hora = fechaHora.time();
    bool horarioValido = (hora >= horaApertura1 && hora <= horaCierre1) ||
                         (hora >= horaApertura2 && hora <= horaCierre2);

    if (!horarioValido) {
        qDebug() << "Horario no válido:" << hora.toString();
    }

    return horarioValido;
}

void PanelCajero::crearPedido()
{
    if (!validarCreacionPedido()) {
        mostrarMensajeError("No se puede crear el pedido en este momento");
        return;
    }

    // Preparar datos del pedido
    QJsonObject pedidoJson;

    // Datos del cliente
    QJsonObject clienteJson;
    clienteJson["nombre"] = clienteSeleccionado.nombre;
    clienteJson["apellido"] = clienteSeleccionado.apellido;
    clienteJson["email"] = clienteSeleccionado.email;
    clienteJson["telefono"] = clienteSeleccionado.telefono;
    clienteJson["direccion"] = clienteSeleccionado.direccion;

    pedidoJson["cliente"] = clienteJson;

    // Tipo de pedido
    pedidoJson["tipo_pedido"] = ui->radioButton_inmediato->isChecked() ? "inmediato" : "programado";

    // Dirección de entrega
    pedidoJson["direccion_entrega"] = clienteSeleccionado.direccion;

    // Método de pago
    pedidoJson["metodo_pago"] = "digital"; // Puedes permitir que el usuario seleccione

    // Totales
    pedidoJson["subtotal"] = subtotal;
    pedidoJson["precio_delivery"] = precioDelivery;
    pedidoJson["total"] = total;
    pedidoJson["cajero_id"] = 1; // ID del cajero actual (puedes hacerlo dinámico)
    pedidoJson["comentarios"] = "";

    // Fecha y hora si es programado
    if (ui->radioButton_programado->isChecked()) {
        QDateTime fechaHora(ui->dateEdit_fecha->date(), ui->timeEdit_hora->time());
        pedidoJson["fecha_entrega"] = fechaHora.toString(Qt::ISODate);
    }

    // Items del carrito
    QJsonArray itemsArray;
    for (const ItemCarrito& item : carrito) {
        QJsonObject itemJson;
        itemJson["id"] = item.producto.id;
        itemJson["nombre"] = item.producto.nombre;
        itemJson["cantidad"] = item.cantidad;
        itemJson["precio"] = item.producto.precio;
        itemJson["precioTotal"] = item.precioTotal;
        itemsArray.append(itemJson);
    }
    pedidoJson["items"] = itemsArray;

    // Enviar a la API
    QNetworkRequest request;
    request.setUrl(QUrl("http://localhost/dashboard/WEB_ElBuenGusto/apiQT/guardar_pedido_cajero.php"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = networkManager->post(request, QJsonDocument(pedidoJson).toJson());

    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
            QJsonObject obj = jsonDoc.object();

            if (obj["success"].toBool()) {
                int pedidoId = obj["pedido_id"].toInt();
                QString numeroPedido = obj["numero_pedido"].toString();

                QString mensaje = QString("¡Pedido creado exitosamente!\n\n"
                                          "Número: %1\n"
                                          "Cliente: %2 %3\n"
                                          "Total: $%4")
                                      .arg(numeroPedido)
                                      .arg(clienteSeleccionado.nombre)
                                      .arg(clienteSeleccionado.apellido)
                                      .arg(total, 0, 'f', 2);

                mostrarMensajeExito(mensaje);

                // Limpiar después de crear
                limpiarCarrito();
                limpiarSeleccionCliente();
            } else {
                mostrarMensajeError("Error: " + obj["error"].toString());
            }
        } else {
            mostrarMensajeError("Error de conexión: " + reply->errorString());
        }
        reply->deleteLater();
    });
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

void PanelCajero::cargarDatosDesdeAPI()
{
    cargarClientes();
    cargarProductosDesdeAPI();
}

void PanelCajero::cargarClientes()
{
    QNetworkRequest request;
    request.setUrl(QUrl("http://localhost/dashboard/WEB_ElBuenGusto/apiQT/clientes.php"));

    QNetworkReply *reply = networkManager->get(request);

    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
            QJsonArray clientesArray = jsonDoc.array();

            clientes.clear();

            for (const QJsonValue &value : clientesArray) {
                QJsonObject obj = value.toObject();

                Cliente c;
                c.id = obj["id"].toInt();
                c.nombre = obj["nombre"].toString();
                c.apellido = obj["apellido"].toString();
                c.email = obj["email"].toString();
                c.telefono = obj["telefono"].toString();
                c.direccion = obj["direccion"].toString();
                c.activo = obj["activo"].toBool();
                c.esNuevo = false;

                clientes.append(c);
            }

            qDebug() << "Clientes cargados:" << clientes.size();
        } else {
            mostrarMensajeError("Error al cargar clientes: " + reply->errorString());
        }
        reply->deleteLater();
    });
}

void PanelCajero::cargarProductosDesdeAPI()
{
    QNetworkRequest request;
    request.setUrl(QUrl("http://localhost/dashboard/WEB_ElBuenGusto/apiQT/productos.php"));

    QNetworkReply *reply = networkManager->get(request);

    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
            QJsonArray productosArray = jsonDoc.array();

            todosLosProductos.clear();
            productos.clear();

            for (const QJsonValue &value : productosArray) {
                QJsonObject obj = value.toObject();

                Producto p;
                p.id = obj["id"].toInt();
                p.nombre = obj["nombre"].toString();
                p.descripcion = obj["descripcion"].toString();
                p.precio = obj["precio"].toDouble();
                p.imagen = obj["imagen"].toString();
                p.categoriaId = obj["categoria_id"].toInt();
                p.categoriaNombre = obj["categoria_nombre"].toString();
                p.ingredientes = obj["ingredientes"].toString();
                p.tiempoPreparacion = obj["tiempo_preparacion"].toInt();
                p.disponible = obj["disponible"].toBool();
                p.valoracionPromedio = obj["valoracion_promedio"].toDouble();
                p.totalValoraciones = obj["total_valoraciones"].toInt();
                p.activo = obj["activo"].toBool();

                todosLosProductos.append(p);
            }

            productos = todosLosProductos;
            mostrarProductos();
        } else {
            mostrarMensajeError("Error al cargar productos: " + reply->errorString());
        }
        reply->deleteLater();
    });
}



void PanelCajero::procesarRespuestaCajero(QNetworkReply *reply)
{
    // Implementación para procesar respuesta de API
}

void PanelCajero::cargarProductos()
{
    productos = todosLosProductos;
}



QVector<Producto> PanelCajero::filtrarProductosPorCategoria(const QString& categoriaNombre)
{
    QVector<Producto> resultado;
    for (const Producto& p : todosLosProductos) {
        if (p.categoriaNombre == categoriaNombre) {
            resultado.append(p);
        }
    }
    return resultado;
}

QVector<Producto> PanelCajero::buscarProductosPorNombre(const QString& nombre)
{
    QVector<Producto> resultado;
    for (const Producto& p : todosLosProductos) {
        if (p.nombre.contains(nombre, Qt::CaseInsensitive)) {
            resultado.append(p);
        }
    }
    return resultado;
}
