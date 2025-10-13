#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QLabel>
#include <QFrame>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , networkManager(new QNetworkAccessManager(this))
    , apiUrl("http://localhost/WEB_ElBuenGusto/api/productos.php")
    , ventanaCarrito(nullptr)
    , categoriaActual("Todos")
{
    ui->setupUi(this);

    connect(ui->barraBusqueda, &QLineEdit::textChanged, this, &MainWindow::on_barraBusqueda_textChanged);
    
    configurarBotonesCategorias();
    inicializarProductosEjemplo();
    cargarProductosDesdeAPI();
    
    // Crear instancia del carrito
    ventanaCarrito = new carrito(this);
    ventanaCarrito->hide();
    
    // Conectar señales del carrito
    connect(ventanaCarrito, &carrito::navegarASeccion, this, &MainWindow::navegarASeccion);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::configurarBotonesCategorias()
{
    // Obtener los botones del frame_3
    QPushButton* btnPedidoRapido = ui->pushButton_2;
    QPushButton* btnProgramarPedido = ui->pushButton_3;
    QPushButton* btnCarrito = ui->pushButton_4;
    QPushButton* btnPerfil = ui->pushButton_5;
    
    // Renombrar y configurar botones
    btnPedidoRapido->setText("Todos");
    btnProgramarPedido->setText("Minutas");
    btnCarrito->setText("Pastas");
    btnPerfil->setText("Ver Carrito");
    
    // Estilo consistente
    QString estiloBoton = 
        "QPushButton { background-color: rgb(200,30,45); color: rgb(245,235,210); "
        "border-radius: 8px; padding: 10px; font-weight: bold; font-size: 12px; } "
        "QPushButton:hover { background-color: rgb(180,25,40); } "
        "QPushButton:pressed { background-color: rgb(160,20,35); }";
    
    btnPedidoRapido->setStyleSheet(estiloBoton);
    btnProgramarPedido->setStyleSheet(estiloBoton);
    btnCarrito->setStyleSheet(estiloBoton);
    btnPerfil->setStyleSheet(
        "QPushButton { background-color: rgb(80,50,20); color: rgb(245,235,210); "
        "border-radius: 8px; padding: 10px; font-weight: bold; font-size: 12px; } "
        "QPushButton:hover { background-color: rgb(100,70,30); }"
    );
    
    // Conectar señales
    connect(btnPedidoRapido, &QPushButton::clicked, [this]() { 
        filtrarPorCategoria("Todos"); 
    });
    connect(btnProgramarPedido, &QPushButton::clicked, [this]() { 
        filtrarPorCategoria("Minutas"); 
    });
    connect(btnCarrito, &QPushButton::clicked, [this]() { 
        filtrarPorCategoria("Pastas"); 
    });
    connect(btnPerfil, &QPushButton::clicked, this, &MainWindow::mostrarCarrito);
}

void MainWindow::inicializarProductosEjemplo()
{
    todosLosProductos.clear();
    
    // MINUTAS (categoría 1)
    ProductoMain m1 = {1, "Milanesa con papas fritas", "Milanesa de carne con guarnición de papas fritas caseras", 2500.0, "hamburguesa.jpeg", 1, "Minutas", true, 25};
    ProductoMain m2 = {2, "Milanesa napolitana", "Milanesa con jamón, queso y salsa de tomate", 2800.0, "hamburguesa.jpeg", 1, "Minutas", true, 30};
    ProductoMain m3 = {3, "Suprema de pollo", "Pechuga de pollo con ensalada", 2300.0, "hamburguesa.jpeg", 1, "Minutas", true, 25};
    ProductoMain m4 = {4, "Bife de chorizo", "Bife de 300g con guarnición a elección", 3500.0, "hamburguesa.jpeg", 1, "Minutas", true, 20};
    ProductoMain m5 = {5, "Lomito completo", "Lomito con jamón, queso, huevo y verduras", 3200.0, "hamburguesa.jpeg", 1, "Minutas", true, 30};
    
    todosLosProductos << m1 << m2 << m3 << m4 << m5;
    
    // PASTAS (categoría 2)
    ProductoMain p1 = {6, "Ravioles de ricota", "Ravioles caseros con salsa a elección", 1800.0, "hamburguesa.jpeg", 2, "Pastas", true, 15};
    ProductoMain p2 = {7, "Sorrentinos de jamón y queso", "Sorrentinos con salsa fileto", 2000.0, "hamburguesa.jpeg", 2, "Pastas", true, 15};
    ProductoMain p3 = {8, "Ñoquis de papa", "Ñoquis caseros con salsa bolognesa", 1700.0, "hamburguesa.jpeg", 2, "Pastas", true, 20};
    ProductoMain p4 = {9, "Lasagna de carne", "Lasagna con carne picada y bechamel", 2200.0, "hamburguesa.jpeg", 2, "Pastas", true, 25};
    ProductoMain p5 = {10, "Canelones de verdura", "Canelones rellenos de espinaca y ricota", 1900.0, "hamburguesa.jpeg", 2, "Pastas", true, 20};
    
    todosLosProductos << p1 << p2 << p3 << p4 << p5;
    
    // GUISOS (categoría 3)
    ProductoMain g1 = {11, "Guiso de lentejas", "Guiso casero de lentejas con chorizo", 1500.0, "hamburguesa.jpeg", 3, "Guisos", true, 35};
    ProductoMain g2 = {12, "Locro", "Locro tradicional argentino", 2000.0, "hamburguesa.jpeg", 3, "Guisos", true, 40};
    ProductoMain g3 = {13, "Guiso de mondongo", "Mondongo con garbanzos y papas", 1800.0, "hamburguesa.jpeg", 3, "Guisos", true, 45};
    ProductoMain g4 = {14, "Carbonada", "Guiso de carne con frutas", 1700.0, "hamburguesa.jpeg", 3, "Guisos", true, 35};
    
    todosLosProductos << g1 << g2 << g3 << g4;
    
    // TARTAS (categoría 4)
    ProductoMain t1 = {16, "Tarta de jamón y queso", "Tarta casera con jamón y queso", 1800.0, "hamburguesa.jpeg", 4, "Tartas", true, 30};
    ProductoMain t2 = {17, "Tarta de verduras", "Tarta de espinaca y acelga", 1600.0, "hamburguesa.jpeg", 4, "Tartas", true, 30};
    ProductoMain t3 = {18, "Tarta de pollo", "Tarta con pollo desmenuzado", 1900.0, "hamburguesa.jpeg", 4, "Tartas", true, 30};
    
    todosLosProductos << t1 << t2 << t3;
    
    // EMPANADAS (categoría 5)
    ProductoMain e1 = {21, "Empanadas de carne (docena)", "Docena de empanadas de carne cortada a cuchillo", 3000.0, "hamburguesa.jpeg", 5, "Empanadas", true, 25};
    ProductoMain e2 = {22, "Empanadas de pollo (docena)", "Docena de empanadas de pollo con verduras", 2800.0, "hamburguesa.jpeg", 5, "Empanadas", true, 25};
    ProductoMain e3 = {23, "Empanadas de jamón y queso (docena)", "Docena de empanadas de jamón y queso", 2700.0, "hamburguesa.jpeg", 5, "Empanadas", true, 25};
    
    todosLosProductos << e1 << e2 << e3;
    
    // POSTRES (categoría 6)
    ProductoMain po1 = {26, "Flan casero", "Flan casero con dulce de leche", 800.0, "hamburguesa.jpeg", 6, "Postres", true, 5};
    ProductoMain po2 = {27, "Tiramisu", "Postre italiano con café", 1200.0, "hamburguesa.jpeg", 6, "Postres", true, 5};
    ProductoMain po3 = {28, "Panqueques con dulce de leche", "3 panqueques rellenos", 900.0, "hamburguesa.jpeg", 6, "Postres", true, 10};
    
    todosLosProductos << po1 << po2 << po3;
    
    // BEBIDAS (categoría 7)
    ProductoMain b1 = {31, "Coca Cola 2.25L", "Gaseosa Coca Cola", 1200.0, "hamburguesa.jpeg", 7, "Bebidas", true, 2};
    ProductoMain b2 = {32, "Sprite 2.25L", "Gaseosa Sprite", 1200.0, "hamburguesa.jpeg", 7, "Bebidas", true, 2};
    ProductoMain b3 = {33, "Agua mineral 2L", "Agua mineral sin gas", 600.0, "hamburguesa.jpeg", 7, "Bebidas", true, 2};
    
    todosLosProductos << b1 << b2 << b3;
    
    // EMBUTIDOS (categoría 8)
    ProductoMain em1 = {36, "Jamón cocido (100g)", "Jamón cocido premium", 450.0, "hamburguesa.jpeg", 8, "Embutidos", true, 2};
    ProductoMain em2 = {37, "Jamón crudo (100g)", "Jamón crudo importado", 850.0, "hamburguesa.jpeg", 8, "Embutidos", true, 2};
    ProductoMain em3 = {38, "Salame (100g)", "Salame tandilero", 600.0, "hamburguesa.jpeg", 8, "Embutidos", true, 2};
    
    todosLosProductos << em1 << em2 << em3;
    
    // COMIDAS RÁPIDAS (categoría 9)
    ProductoMain cr1 = {41, "Hamburguesa completa", "Hamburguesa con todos los ingredientes", 2000.0, "hamburguesa.jpeg", 9, "Comidas Rápidas", true, 15};
    ProductoMain cr2 = {42, "Pancho completo", "Pancho con papas fritas", 1500.0, "hamburguesa.jpeg", 9, "Comidas Rápidas", true, 10};
    ProductoMain cr3 = {43, "Pizza muzarella", "Pizza casera con muzarella", 2500.0, "hamburguesa.jpeg", 9, "Comidas Rápidas", true, 20};
    
    todosLosProductos << cr1 << cr2 << cr3;
    
    // OTROS (categoría 10)
    ProductoMain o1 = {46, "Pollo al espiedo entero", "Pollo al espiedo para llevar", 3500.0, "hamburguesa.jpeg", 10, "Otros", true, 30};
    ProductoMain o2 = {47, "Costillas al horno", "Costillas de cerdo al horno", 4000.0, "hamburguesa.jpeg", 10, "Otros", true, 40};
    ProductoMain o3 = {48, "Matambre a la pizza", "Matambre con salsa y queso", 3200.0, "hamburguesa.jpeg", 10, "Otros", true, 35};
    
    todosLosProductos << o1 << o2 << o3;
    
    productos = todosLosProductos;
}

void MainWindow::cargarProductosDesdeAPI()
{
    QNetworkRequest request;
    request.setUrl(QUrl(apiUrl));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    
    QNetworkReply *reply = networkManager->get(request);
    
    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            procesarRespuestaProductos(reply);
        } else {
            qDebug() << "Error al cargar productos:" << reply->errorString();
            mostrarProductos();
        }
        reply->deleteLater();
    });
}

void MainWindow::procesarRespuestaProductos(QNetworkReply *reply)
{
    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    
    if (jsonDoc.isArray()) {
        todosLosProductos.clear();
        
        QJsonArray productosArray = jsonDoc.array();
        for (const QJsonValue &value : productosArray) {
            QJsonObject obj = value.toObject();
            
            ProductoMain producto;
            producto.id = obj["id"].toInt();
            producto.nombre = obj["nombre"].toString();
            producto.descripcion = obj["descripcion"].toString();
            producto.precio = obj["precio"].toDouble();
            producto.imagen = obj["imagen"].toString();
            producto.categoriaId = obj["categoria_id"].toInt();
            producto.categoriaNombre = obj["categoria_nombre"].toString();
            producto.disponible = obj["disponible"].toBool();
            producto.tiempoPreparacion = obj["tiempo_preparacion"].toInt(20);
            
            todosLosProductos.append(producto);
        }
        
        productos = todosLosProductos;
        mostrarProductos();
    }
}

void MainWindow::colocar_layouts()
{
    mostrarProductos();
}

void MainWindow::mostrarProductos()
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
    
    QVBoxLayout *contenedor_v = new QVBoxLayout;
    ui->scrollAreaWidgetContents->setLayout(contenedor_v);
    
    // Título de la categoría
    if (categoriaActual != "Todos") {
        QLabel* labelCategoria = new QLabel(categoriaActual);
        labelCategoria->setFont(QFont("Segoe UI", 18, QFont::Bold));
        labelCategoria->setStyleSheet("color: rgb(245,235,210); padding: 15px; background-color: rgba(0,0,0,0.3); border-radius: 10px; margin: 10px;");
        labelCategoria->setAlignment(Qt::AlignCenter);
        contenedor_v->addWidget(labelCategoria);
    }

    QVector<ProductoMain> productosFiltrados;
    
    if (categoriaActual == "Todos") {
        productosFiltrados = productos;
    } else {
        for (const ProductoMain& prod : productos) {
            if (prod.categoriaNombre == categoriaActual) {
                productosFiltrados.append(prod);
            }
        }
    }
    
    if (productosFiltrados.isEmpty()) {
        QLabel* labelVacio = new QLabel("No hay productos disponibles en esta categoría");
        labelVacio->setAlignment(Qt::AlignCenter);
        labelVacio->setStyleSheet("color: rgb(245,235,210); font-size: 16px; padding: 40px;");
        contenedor_v->addWidget(labelVacio);
    } else {
        for (const ProductoMain& producto : productosFiltrados) {
            crearTarjetaProducto(producto);
        }
    }
    
    contenedor_v->addStretch();
}

void MainWindow::mostrarProductosPorCategoria(const QString& categoria)
{
    categoriaActual = categoria;
    mostrarProductos();
}

void MainWindow::filtrarPorCategoria(const QString& categoria)
{
    categoriaActual = categoria;
    ui->barraBusqueda->clear();
    mostrarProductos();
}

void MainWindow::crearTarjetaProducto(const ProductoMain& producto)
{
    QFrame* frameProducto = new QFrame();
    frameProducto->setStyleSheet(
        "QFrame { "
        "background-color: rgb(245,235,210); "
        "border-radius: 15px; "
        "margin: 10px; "
        "padding: 15px; "
        "}"
    );
    frameProducto->setMaximumWidth(380);
    frameProducto->setMinimumHeight(280);
    
    QVBoxLayout* layoutProducto = new QVBoxLayout(frameProducto);
    
    // Imagen del producto
    QLabel* labelImagen = new QLabel();
    labelImagen->setFixedSize(330, 200);
    labelImagen->setScaledContents(true);
    labelImagen->setStyleSheet("border-radius: 10px;");
    
    QPixmap pixmap(":/" + producto.imagen);
    if (!pixmap.isNull()) {
        labelImagen->setPixmap(pixmap);
    } else {
        labelImagen->setText("Sin imagen");
        labelImagen->setAlignment(Qt::AlignCenter);
        labelImagen->setStyleSheet("background-color: #ddd; border-radius: 10px;");
    }
    
    // Nombre del producto
    QLabel* labelNombre = new QLabel(producto.nombre);
    labelNombre->setFont(QFont("Segoe UI", 14, QFont::Bold));
    labelNombre->setStyleSheet("color: rgb(80,50,20); margin-top: 10px;");
    labelNombre->setWordWrap(true);
    
    // Descripción
    QLabel* labelDescripcion = new QLabel(producto.descripcion);
    labelDescripcion->setWordWrap(true);
    labelDescripcion->setMaximumHeight(40);
    labelDescripcion->setStyleSheet("color: rgb(80,50,20); margin: 5px 0; font-size: 11px;");
    
    // Frame para precio y tiempo
    QHBoxLayout* layoutPrecioTiempo = new QHBoxLayout();
    
    QLabel* labelPrecio = new QLabel(QString("$%1").arg(producto.precio, 0, 'f', 2));
    labelPrecio->setFont(QFont("Segoe UI", 16, QFont::Bold));
    labelPrecio->setStyleSheet("color: rgb(200,30,45); margin: 5px 0;");
    
    QLabel* labelTiempo = new QLabel(QString("⏱ %1 min").arg(producto.tiempoPreparacion));
    labelTiempo->setStyleSheet("color: rgb(80,50,20); font-size: 11px;");
    
    layoutPrecioTiempo->addWidget(labelPrecio);
    layoutPrecioTiempo->addStretch();
    layoutPrecioTiempo->addWidget(labelTiempo);
    
    // Botón agregar al carrito
    QPushButton* btnAgregar = new QPushButton("Agregar al Carrito");
    btnAgregar->setFixedHeight(40);
    
    if (producto.disponible) {
        btnAgregar->setStyleSheet(
            "QPushButton { "
            "background-color: rgb(200,30,45); "
            "color: white; "
            "border: none; "
            "border-radius: 8px; "
            "font-size: 13px; "
            "font-weight: bold; "
            "padding: 10px; "
            "} "
            "QPushButton:hover { "
            "background-color: rgb(180,25,40); "
            "}"
        );
        
        connect(btnAgregar, &QPushButton::clicked, [this, producto]() {
            agregarAlCarrito(producto.id);
        });
    } else {
        btnAgregar->setText("No Disponible");
        btnAgregar->setEnabled(false);
        btnAgregar->setStyleSheet(
            "QPushButton { "
            "background-color: #ccc; "
            "color: #999; "
            "border: none; "
            "border-radius: 8px; "
            "font-size: 13px; "
            "font-weight: bold; "
            "padding: 10px; "
            "}"
        );
    }
    
    // Agregar widgets al layout
    layoutProducto->addWidget(labelImagen);
    layoutProducto->addWidget(labelNombre);
    layoutProducto->addWidget(labelDescripcion);
    layoutProducto->addLayout(layoutPrecioTiempo);
    layoutProducto->addWidget(btnAgregar);
    
    // Agregar el frame al contenedor principal
    QVBoxLayout* contenedor = qobject_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout());
    if (contenedor) {
        contenedor->addWidget(frameProducto);
    }
}

void MainWindow::agregarAlCarrito(int productoId)
{
    if (ventanaCarrito) {
        ventanaCarrito->agregarProducto(productoId, 1);
        
        QMessageBox msgBox;
        msgBox.setWindowTitle("Producto agregado");
        msgBox.setText("El producto se agregó al carrito exitosamente");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Open);
        msgBox.button(QMessageBox::Open)->setText("Ver Carrito");
        
        int ret = msgBox.exec();
        if (ret == QMessageBox::Open) {
            mostrarCarrito();
        }
    }
}

void MainWindow::mostrarCarrito()
{
    if (ventanaCarrito) {
        ventanaCarrito->show();
        ventanaCarrito->raise();
        ventanaCarrito->activateWindow();
    }
}

void MainWindow::navegarASeccion(const QString& seccion)
{
    qDebug() << "Navegando a sección:" << seccion;
    
    if (seccion == "Inicio") {
        filtrarPorCategoria("Todos");
    } else if (seccion == "Minutas") {
        filtrarPorCategoria("Minutas");
    } else if (seccion == "Pastas") {
        filtrarPorCategoria("Pastas");
    } else if (seccion == "Guisos") {
        filtrarPorCategoria("Guisos");
    } else if (seccion == "Tartas") {
        filtrarPorCategoria("Tartas");
    } else if (seccion == "Empanadas") {
        filtrarPorCategoria("Empanadas");
    } else if (seccion == "Postres") {
        filtrarPorCategoria("Postres");
    } else if (seccion == "Bebidas") {
        filtrarPorCategoria("Bebidas");
    } else if (seccion == "Embutidos") {
        filtrarPorCategoria("Embutidos");
    } else if (seccion == "ComidasRapidas") {
        filtrarPorCategoria("Comidas Rápidas");
    } else if (seccion == "Otros") {
        filtrarPorCategoria("Otros");
    } else if (seccion == "MisPedidos") {
        QMessageBox::information(this, "Mis Pedidos", "Sección en desarrollo");
    } else if (seccion == "Perfil") {
        QMessageBox::information(this, "Mi Perfil", "Sección en desarrollo");
    }
    
    // Ocultar carrito si está abierto
    if (ventanaCarrito && ventanaCarrito->isVisible()) {
        ventanaCarrito->hide();
    }
}

void MainWindow::on_barraBusqueda_textChanged()
{
    QString texto = ui->barraBusqueda->text();
    filtrarProductos(texto);
}

void MainWindow::filtrarProductos(const QString& texto)
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
    
    QVBoxLayout *contenedor_v = new QVBoxLayout;
    ui->scrollAreaWidgetContents->setLayout(contenedor_v);
    
    // Si hay texto de búsqueda, mostrar título
    if (!texto.isEmpty()) {
        QLabel* labelBusqueda = new QLabel(QString("Resultados para: \"%1\"").arg(texto));
        labelBusqueda->setFont(QFont("Segoe UI", 16, QFont::Bold));
        labelBusqueda->setStyleSheet("color: rgb(245,235,210); padding: 10px; background-color: rgba(0,0,0,0.3); border-radius: 8px; margin: 10px;");
        contenedor_v->addWidget(labelBusqueda);
    }
    
    int resultados = 0;
    
    // Filtrar y mostrar productos
    for (const ProductoMain& producto : todosLosProductos) {
        bool coincide = false;
        
        if (texto.isEmpty()) {
            // Si no hay búsqueda, aplicar filtro de categoría
            if (categoriaActual == "Todos") {
                coincide = true;
            } else {
                coincide = (producto.categoriaNombre == categoriaActual);
            }
        } else {
            // Si hay búsqueda, buscar en nombre, descripción y categoría
            coincide = producto.nombre.contains(texto, Qt::CaseInsensitive) ||
                      producto.descripcion.contains(texto, Qt::CaseInsensitive) ||
                      producto.categoriaNombre.contains(texto, Qt::CaseInsensitive);
        }
        
        if (coincide) {
            crearTarjetaProducto(producto);
            resultados++;
        }
    }
    
    if (resultados == 0) {
        QLabel* labelVacio = new QLabel("No se encontraron productos");
        labelVacio->setAlignment(Qt::AlignCenter);
        labelVacio->setStyleSheet("color: rgb(245,235,210); font-size: 16px; padding: 40px;");
        contenedor_v->addWidget(labelVacio);
    }
    
    contenedor_v->addStretch();
}