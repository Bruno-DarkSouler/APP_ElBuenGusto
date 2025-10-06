#include "carrito.h"
#include "ui_carrito.h"
#include <QDebug>

carrito::carrito(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::carrito)
    , subtotal(0.0)
    , total(0.0)
    , networkManager(new QNetworkAccessManager(this))
    , apiUrl("http://localhost/WEB_ElBuenGusto/api/carrito.php")
{
    ui->setupUi(this);
    configurarEventos();
    cargarProductosDesdeAPI();
    actualizarInterfaz();
}

carrito::~carrito()
{
    delete ui;
}

bool carrito::validarPedido()
{
    if (productos.isEmpty()) {
        QMessageBox::warning(this, "Carrito vacío", "No hay productos en el carrito para crear un pedido.");
        return false;
    }
    
    for (const ProductoCarrito &producto : productos) {
        if (!producto.disponible) {
            QMessageBox::warning(this, "Producto no disponible", 
                                "El producto " + producto.nombre + " no está disponible actualmente.");
            return false;
        }
    }
    
    return true;
}

void carrito::configurarEventos()
{
    ui->label->setCursor(Qt::PointingHandCursor);
    ui->label->installEventFilter(this);
}

bool carrito::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->label && event->type() == QEvent::MouseButtonPress) {
        finalizarPedido();
        return true;
    }
    
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            QLabel* label = qobject_cast<QLabel*>(obj);
            if (label) {
                QVariant productoIdVar = label->property("productoId");
                QVariant accionVar = label->property("accion");
                
                if (productoIdVar.isValid() && accionVar.isValid()) {
                    int productoId = productoIdVar.toInt();
                    QString accion = accionVar.toString();
                    
                    if (accion == "aumentar") {
                        aumentarCantidad(productoId);
                    } else if (accion == "disminuir") {
                        disminuirCantidad(productoId);
                    } else if (accion == "eliminar") {
                        eliminarDelCarrito(productoId);
                    }
                    return true;
                }
            }
        }
    }
    
    return QWidget::eventFilter(obj, event);
}

void carrito::agregarProducto(int productoId, int cantidad)
{
    if (!validarStock(productoId, cantidad)) {
        mostrarMensajeError("Stock insuficiente para este producto");
        return;
    }
    
    ProductoCarrito* productoExistente = buscarProducto(productoId);
    
    if (productoExistente) {
        int nuevaCantidad = productoExistente->cantidad + cantidad;
        if (validarStock(productoId, nuevaCantidad)) {
            productoExistente->cantidad = nuevaCantidad;
            productoExistente->precioTotal = productoExistente->precio * nuevaCantidad;
            actualizarInterfaz();
            emit carritoActualizado();
        } else {
            mostrarMensajeError("No hay suficiente stock para agregar más unidades");
            return;
        }
    } else {
        QNetworkRequest request;
        request.setUrl(QUrl(apiUrl));
        request.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
        
        QJsonObject jsonObj;
        jsonObj["accion"] = "agregar";
        jsonObj["producto_id"] = productoId;
        jsonObj["cantidad"] = cantidad;
        
        QJsonDocument doc(jsonObj);
        QByteArray data = doc.toJson();
        
        QNetworkReply *reply = networkManager->post(request, data);
        
        connect(reply, &QNetworkReply::finished, [this, reply]() {
            if (reply->error() == QNetworkReply::NoError) {
                cargarProductosDesdeAPI();
            } else {
                mostrarMensajeError("Error al agregar producto: " + reply->errorString());
            }
            reply->deleteLater();
        });
    }
}

void carrito::eliminarProducto(int productoId)
{
    QNetworkRequest request;
    request.setUrl(QUrl(apiUrl));
    request.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
    
    QJsonObject jsonObj;
    jsonObj["accion"] = "eliminar";
    jsonObj["producto_id"] = productoId;
    
    QJsonDocument doc(jsonObj);
    QByteArray data = doc.toJson();
    
    QNetworkReply *reply = networkManager->post(request, data);
    
    connect(reply, &QNetworkReply::finished, [this, productoId, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            cargarProductosDesdeAPI();
            emit productoEliminado(productoId);
        } else {
            mostrarMensajeError("Error al eliminar producto: " + reply->errorString());
            
            for (int i = 0; i < productos.size(); ++i) {
                if (productos[i].id == productoId) {
                    productos.removeAt(i);
                    break;
                }
            }
            
            actualizarInterfaz();
            emit carritoActualizado();
            emit productoEliminado(productoId);
        }
        reply->deleteLater();
    });
}

void carrito::modificarCantidad(int productoId, int nuevaCantidad)
{
    if (nuevaCantidad <= 0) {
        eliminarProducto(productoId);
        return;
    }
    
    if (!validarStock(productoId, nuevaCantidad)) {
        mostrarMensajeError("Stock insuficiente");
        return;
    }
    
    QNetworkRequest request;
    request.setUrl(QUrl(apiUrl));
    request.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
    
    QJsonObject jsonObj;
    jsonObj["accion"] = "modificar";
    jsonObj["producto_id"] = productoId;
    jsonObj["cantidad"] = nuevaCantidad;
    
    QJsonDocument doc(jsonObj);
    QByteArray data = doc.toJson();
    
    QNetworkReply *reply = networkManager->post(request, data);
    
    connect(reply, &QNetworkReply::finished, [this, productoId, nuevaCantidad, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            cargarProductosDesdeAPI();
            emit cantidadModificada(productoId, nuevaCantidad);
        } else {
            mostrarMensajeError("Error al modificar cantidad: " + reply->errorString());
            
            ProductoCarrito* producto = buscarProducto(productoId);
            if (producto) {
                producto->cantidad = nuevaCantidad;
                producto->precioTotal = producto->precio * nuevaCantidad;
                actualizarInterfaz();
                emit carritoActualizado();
                emit cantidadModificada(productoId, nuevaCantidad);
            }
        }
        reply->deleteLater();
    });
}

void carrito::limpiarCarrito()
{
    QNetworkRequest request;
    request.setUrl(QUrl(apiUrl));
    request.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
    
    QJsonObject jsonObj;
    jsonObj["accion"] = "limpiar";
    
    QJsonDocument doc(jsonObj);
    QByteArray data = doc.toJson();
    
    QNetworkReply *reply = networkManager->post(request, data);
    
    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            productos.clear();
            actualizarInterfaz();
            emit carritoActualizado();
        } else {
            mostrarMensajeError("Error al limpiar carrito: " + reply->errorString());
            
            productos.clear();
            actualizarInterfaz();
            emit carritoActualizado();
        }
        reply->deleteLater();
    });
}

QVector<ProductoCarrito> carrito::obtenerProductos() const
{
    return productos;
}

double carrito::obtenerSubtotal() const
{
    return subtotal;
}

double carrito::obtenerTotal() const
{
    return total;
}

int carrito::obtenerCantidadItems() const
{
    int total = 0;
    for (const ProductoCarrito& producto : productos) {
        total += producto.cantidad;
    }
    return total;
}

bool carrito::estaVacio() const
{
    return productos.isEmpty();
}

void carrito::aumentarCantidad(int productoId)
{
    ProductoCarrito* producto = buscarProducto(productoId);
    if (producto) {
        modificarCantidad(productoId, producto->cantidad + 1);
    }
}

void carrito::disminuirCantidad(int productoId)
{
    ProductoCarrito* producto = buscarProducto(productoId);
    if (producto) {
        if (producto->cantidad > 1) {
            modificarCantidad(productoId, producto->cantidad - 1);
        } else {
            eliminarProducto(productoId);
        }
    }
}

void carrito::eliminarDelCarrito(int productoId)
{
    eliminarProducto(productoId);
}

void carrito::finalizarPedido()
{
    if (estaVacio()) {
        mostrarMensajeError("El carrito está vacío");
        return;
    }
    
    emit finalizarPedidoClicked();
}

void carrito::actualizarInterfaz()
{
    actualizarVisualizacion();
    actualizarTotales();
}

void carrito::cargarProductosDesdeAPI()
{
    QNetworkRequest request;
    request.setUrl(QUrl(apiUrl));
    request.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
    
    QNetworkReply *reply = networkManager->get(request);
    
    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            procesarRespuestaAPI(reply);
        } else {
            mostrarMensajeError("Error al conectar con la API: " + reply->errorString());
        }
        reply->deleteLater();
    });
}

void carrito::procesarRespuestaAPI(QNetworkReply *reply)
{
    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    
    if (jsonDoc.isArray()) {
        productos.clear();
        
        QJsonArray productosArray = jsonDoc.array();
        for (const QJsonValue &value : productosArray) {
            QJsonObject obj = value.toObject();
            
            ProductoCarrito producto;
            producto.id = obj["id"].toInt();
            producto.nombre = obj["nombre"].toString();
            producto.precio = obj["precio"].toDouble();
            producto.cantidad = obj["cantidad"].toInt();
            producto.precioTotal = producto.precio * producto.cantidad;
            producto.disponible = true;
            producto.descripcion = "";
            producto.imagen = "hamburguesa.jpeg";
            producto.ingredientes = "";
            producto.comentarios = "";
            
            productos.append(producto);
        }
        
        actualizarTotales();
        actualizarVisualizacion();
        
        emit carritoActualizado();
    } else {
        mostrarMensajeError("Formato de respuesta de API inválido");
    }
}

void carrito::crearWidgetProducto(const ProductoCarrito& producto)
{
    QFrame* frameProducto = new QFrame();
    frameProducto->setStyleSheet("QFrame { background-color: white; border-radius: 15px; margin: 5px; padding: 10px; }");
    frameProducto->setMaximumSize(300, 300);
    frameProducto->setMinimumSize(280, 250);
    
    QVBoxLayout* layoutProducto = new QVBoxLayout(frameProducto);
    
    QLabel* labelImagen = new QLabel();
    labelImagen->setMaximumSize(400, 200);
    labelImagen->setStyleSheet("border-radius: 5px;");
    labelImagen->setScaledContents(true);
    
    if (!producto.imagen.isEmpty()) {
        QPixmap pixmap(":/" + producto.imagen);
        if (!pixmap.isNull()) {
            labelImagen->setPixmap(pixmap);
        } else {
            labelImagen->setText("Sin imagen");
            labelImagen->setAlignment(Qt::AlignCenter);
        }
    }
    
    QLabel* labelNombre = new QLabel(producto.nombre);
    labelNombre->setMaximumSize(200, 30);
    labelNombre->setFont(QFont("Segoe UI", 14));
    labelNombre->setStyleSheet("font-weight: bold;");
    
    QFrame* frameControles = new QFrame();
    frameControles->setMaximumSize(380, 40);
    
    QHBoxLayout* layoutControles = new QHBoxLayout(frameControles);
    layoutControles->setContentsMargins(0, 0, 0, 0);
    
    QFrame* framePrecioBotones = new QFrame();
    framePrecioBotones->setMaximumSize(180, 40);
    
    QHBoxLayout* layoutPrecioBotones = new QHBoxLayout(framePrecioBotones);
    layoutPrecioBotones->setSpacing(9);
    layoutPrecioBotones->setContentsMargins(0, 0, 0, 0);
    
    QLabel* labelPrecio = new QLabel(QString(" $%1").arg(producto.precioTotal, 0, 'f', 2));
    labelPrecio->setMaximumSize(70, 30);
    labelPrecio->setFont(QFont("Segoe UI", 14));
    labelPrecio->setStyleSheet("background-color: red; color: white; border-radius: 6px; padding: 4px;");
    
    QLabel* labelCantidad = new QLabel(QString::number(producto.cantidad));
    labelCantidad->setMaximumSize(20, 30);
    labelCantidad->setAlignment(Qt::AlignCenter);
    labelCantidad->setStyleSheet("font-weight: bold; font-size: 14px;");
    
    QLabel* labelMas = new QLabel();
    labelMas->setMaximumSize(30, 30);
    labelMas->setPixmap(QPixmap(":/mas-top.png"));
    labelMas->setScaledContents(true);
    labelMas->setCursor(Qt::PointingHandCursor);
    labelMas->setProperty("productoId", producto.id);
    labelMas->setProperty("accion", "aumentar");
    labelMas->installEventFilter(this);
    
    QLabel* labelMenos = new QLabel();
    labelMenos->setMaximumSize(30, 30);
    labelMenos->setPixmap(QPixmap(":/menos-top.png"));
    labelMenos->setScaledContents(true);
    labelMenos->setCursor(Qt::PointingHandCursor);
    labelMenos->setProperty("productoId", producto.id);
    labelMenos->setProperty("accion", "disminuir");
    labelMenos->installEventFilter(this);
    
    layoutPrecioBotones->addWidget(labelPrecio);
    layoutPrecioBotones->addWidget(labelCantidad);
    layoutPrecioBotones->addWidget(labelMas);
    layoutPrecioBotones->addWidget(labelMenos);
    
    QFrame* frameSpacer = new QFrame();
    frameSpacer->setMaximumSize(30, 40);
    
    QLabel* labelEliminar = new QLabel();
    labelEliminar->setMaximumSize(35, 35);
    labelEliminar->setPixmap(QPixmap(":/trash.png"));
    labelEliminar->setScaledContents(true);
    labelEliminar->setCursor(Qt::PointingHandCursor);
    labelEliminar->setProperty("productoId", producto.id);
    labelEliminar->setProperty("accion", "eliminar");
    labelEliminar->installEventFilter(this);
    
    layoutControles->addWidget(framePrecioBotones);
    layoutControles->addWidget(frameSpacer);
    layoutControles->addWidget(labelEliminar);
    
    layoutProducto->addWidget(labelImagen);
    layoutProducto->addWidget(labelNombre);
    layoutProducto->addWidget(frameControles);
    
    QVBoxLayout* layoutCarrito = qobject_cast<QVBoxLayout*>(ui->groupBox->layout());
    if (!layoutCarrito) {
        layoutCarrito = new QVBoxLayout(ui->groupBox);
    }
    
    layoutCarrito->addWidget(frameProducto);
}

void carrito::actualizarTotales()
{
    subtotal = 0.0;
    for (const ProductoCarrito& producto : productos) {
        subtotal += producto.precioTotal;
    }
    total = subtotal;
}

void carrito::actualizarVisualizacion()
{
    limpiarLayout();
    
    if (productos.isEmpty()) {
        QLabel* labelVacio = new QLabel("Carrito vacío");
        labelVacio->setAlignment(Qt::AlignCenter);
        labelVacio->setStyleSheet("color: #999; font-size: 16px; font-style: italic; padding: 20px;");
        
        QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->groupBox->layout());
        if (!layout) {
            layout = new QVBoxLayout(ui->groupBox);
        }
        layout->addWidget(labelVacio);
    } else {
        for (const ProductoCarrito& producto : productos) {
            crearWidgetProducto(producto);
        }
    }
}

void carrito::limpiarLayout()
{
    QLayout* layout = ui->groupBox->layout();
    if (layout) {
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != nullptr) {
            if (item->widget()) {
                delete item->widget();
            }
            delete item;
        }
    }
}

bool carrito::validarStock(int productoId, int cantidadSolicitada)
{
    Q_UNUSED(productoId)
    Q_UNUSED(cantidadSolicitada)
    return true;
}

ProductoCarrito* carrito::buscarProducto(int productoId)
{
    for (ProductoCarrito& producto : productos) {
        if (producto.id == productoId) {
            return &producto;
        }
    }
    return nullptr;
}

void carrito::mostrarMensajeError(const QString& mensaje)
{
    QMessageBox::warning(this, "Error", mensaje);
}

void carrito::mostrarMensajeExito(const QString& mensaje)
{
    QMessageBox::information(this, "Éxito", mensaje);
}

QVector<Condimento> carrito::cargarCondimentosDisponibles()
{
    QVector<Condimento> condimentos;
    return condimentos;
}

void carrito::mostrarSelectorCondimentos(int productoId)
{
    Q_UNUSED(productoId)
}
