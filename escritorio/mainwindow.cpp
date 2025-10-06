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
    , apiUrl("file:///C:/Users/Alumnos/Downloads/WEB_ElBuenGusto/api/productos.php")
{
    ui->setupUi(this);

    connect(ui->barraBusqueda, &QLineEdit::textChanged, this, &MainWindow::on_barraBusqueda_textChanged);
    
    cargarProductosDesdeAPI();
}

MainWindow::~MainWindow()
{
    delete ui;
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
            // Cargar productos de ejemplo si falla la API
            ProductoMain p1;
            p1.id = 1;
            p1.nombre = "Milanesa con papas";
            p1.descripcion = "Deliciosa milanesa con papas fritas";
            p1.precio = 2500.0;
            p1.imagen = "hamburguesa.jpeg";
            p1.categoriaId = 1;
            p1.disponible = true;
            productos.append(p1);
            
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
        productos.clear();
        
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
            producto.disponible = obj["disponible"].toBool();
            
            productos.append(producto);
        }
        
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

    for (const ProductoMain& producto : productos) {
        crearTarjetaProducto(producto);
    }
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
    frameProducto->setMaximumWidth(350);
    frameProducto->setMinimumHeight(200);
    
    QVBoxLayout* layoutProducto = new QVBoxLayout(frameProducto);
    
    // Imagen del producto
    QLabel* labelImagen = new QLabel();
    labelImagen->setFixedSize(300, 200);
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
    labelNombre->setFont(QFont("Segoe UI", 16, QFont::Bold));
    labelNombre->setStyleSheet("color: rgb(80,50,20); margin-top: 10px;");
    
    // Descripción
    QLabel* labelDescripcion = new QLabel(producto.descripcion);
    labelDescripcion->setWordWrap(true);
    labelDescripcion->setStyleSheet("color: rgb(80,50,20); margin: 5px 0;");
    
    // Precio
    QLabel* labelPrecio = new QLabel(QString("$%1").arg(producto.precio, 0, 'f', 2));
    labelPrecio->setFont(QFont("Segoe UI", 18, QFont::Bold));
    labelPrecio->setStyleSheet("color: rgb(200,30,45); margin: 5px 0;");
    
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
            "font-size: 14px; "
            "font-weight: bold; "
            "padding: 10px; "
            "} "
            "QPushButton:hover { "
            "background-color: rgb(180,25,40); "
            "}"
        );
    } else {
        btnAgregar->setText("No Disponible");
        btnAgregar->setEnabled(false);
        btnAgregar->setStyleSheet(
            "QPushButton { "
            "background-color: #ccc; "
            "color: #999; "
            "border: none; "
            "border-radius: 8px; "
            "font-size: 14px; "
            "font-weight: bold; "
            "padding: 10px; "
            "}"
        );
    }
    
    // Agregar widgets al layout
    layoutProducto->addWidget(labelImagen);
    layoutProducto->addWidget(labelNombre);
    layoutProducto->addWidget(labelDescripcion);
    layoutProducto->addWidget(labelPrecio);
    layoutProducto->addWidget(btnAgregar);
    
    // Agregar el frame al contenedor principal
    QVBoxLayout* contenedor = qobject_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout());
    if (contenedor) {
        contenedor->addWidget(frameProducto);
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
    
    // Filtrar y mostrar productos
    for (const ProductoMain& producto : productos) {
        if (texto.isEmpty() || 
            producto.nombre.contains(texto, Qt::CaseInsensitive) ||
            producto.descripcion.contains(texto, Qt::CaseInsensitive)) {
            crearTarjetaProducto(producto);
        }
    }
}
