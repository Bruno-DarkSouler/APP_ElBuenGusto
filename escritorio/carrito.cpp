#include "carrito.h"
#include "ui_carrito.h"
#include <QtCore/QDebug>

carrito::carrito(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui_carrito)
    , subtotal(0.0)
    , total(0.0)
    , networkManager(new QNetworkAccessManager(this))
    , apiUrl("C:\\Users\\NoxiePC\\Downloads\\WEB_ElBuenGusto\\api\\carrito.php")
{
    ui->setupUi(this);
    
    if (inicializarBaseDatos()) {
        configurarEventos();
        // Cargar productos desde la API en lugar de la base de datos local
        cargarProductosDesdeAPI();
        actualizarInterfaz();
    } else {
        mostrarMensajeError("Error al conectar con la base de datos");
    }
}

carrito::~carrito()
{
    delete ui;
    // El networkManager se eliminará automáticamente ya que es hijo de este objeto
}

bool carrito::validarPedido()
{
    // Verificar si hay productos en el carrito
    if (productos.isEmpty()) {
        QMessageBox::warning(this, "Carrito vacío", "No hay productos en el carrito para crear un pedido.");
        return false;
    }
    
    // Verificar si todos los productos están disponibles
    for (const ProductoCarrito &producto : productos) {
        if (!producto.disponible) {
            QMessageBox::warning(this, "Producto no disponible", 
                                "El producto " + producto.nombre + " no está disponible actualmente.");
            return false;
        }
    }
    
    return true;
}

bool carrito::inicializarBaseDatos()
{
    db = QSqlDatabase::addDatabase("QSQLITE", "carrito_connection");
    db.setDatabaseName("rotiseria.db");
    
    if (!db.open()) {
        qDebug() << "Error al abrir base de datos:" << db.lastError().text();
        return false;
    }
    
    return true;
}

void carrito::configurarEventos()
{
    // Conectar el botón de finalizar pedido mediante eventFilter en lugar de mousePressEvent
    // El evento se maneja en el método eventFilter
    
    // Nota: El botón "Finalizar pedido" en el .ui es un QLabel, lo convertiremos en clickeable
    ui->label->setCursor(Qt::PointingHandCursor);
    ui->label->installEventFilter(this);
}

bool carrito::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->label && event->type() == QEvent::MouseButtonPress) {
        finalizarPedido();
        return true;
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
        // Si el producto ya existe, aumentar la cantidad
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
        // Preparar la solicitud para agregar un producto al carrito
        QNetworkRequest request;
        request.setUrl(QUrl(apiUrl));
        request.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
        
        // Crear el objeto JSON para enviar
        QJsonObject jsonObj;
        jsonObj["accion"] = "agregar";
        jsonObj["producto_id"] = productoId;
        jsonObj["cantidad"] = cantidad;
        
        QJsonDocument doc(jsonObj);
        QByteArray data = doc.toJson();
        
        // Enviar la solicitud POST a la API
        QNetworkReply *reply = networkManager->post(request, data.constData());
        
        connect(reply, &QNetworkReply::finished, [this, reply, productoId, cantidad]() {
            if (reply->error() == QNetworkReply::NoError) {
                // Recargar el carrito desde la API para reflejar los cambios
                cargarProductosDesdeAPI();
            } else {
                mostrarMensajeError("Error al agregar producto: " + reply->errorString());
                
                // Como respaldo, intentar agregar desde la base de datos local
                ProductoCarrito nuevoProducto;
                cargarProductoDesdeDB(productoId, nuevoProducto);
                nuevoProducto.cantidad = cantidad;
                nuevoProducto.precioTotal = nuevoProducto.precio * cantidad;
                productos.append(nuevoProducto);
                actualizarInterfaz();
                emit carritoActualizado();
            }
            reply->deleteLater();
        });
    }
}

void carrito::eliminarProducto(int productoId)
{
    // Preparar la solicitud para eliminar un producto del carrito
    QNetworkRequest request;
    request.setUrl(QUrl(apiUrl));
    request.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
    
    // Crear el objeto JSON para enviar
    QJsonObject jsonObj;
    jsonObj["accion"] = "eliminar";
    jsonObj["producto_id"] = productoId;
    
    QJsonDocument doc(jsonObj);
    QByteArray data = doc.toJson();
    
    // Enviar la solicitud POST
    QNetworkReply *reply = networkManager->post(request, data.constData());
    
    connect(reply, &QNetworkReply::finished, [this, productoId, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            // Recargar el carrito desde la API para reflejar los cambios
            cargarProductosDesdeAPI();
            emit productoEliminado(productoId);
        } else {
            mostrarMensajeError("Error al eliminar producto: " + reply->errorString());
            
            // Como respaldo, eliminar localmente
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
    
    // Preparar la solicitud para modificar la cantidad de un producto
    QNetworkRequest request;
    request.setUrl(QUrl(apiUrl));
    request.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
    
    // Crear el objeto JSON para enviar
    QJsonObject jsonObj;
    jsonObj["accion"] = "modificar";
    jsonObj["producto_id"] = productoId;
    jsonObj["cantidad"] = nuevaCantidad;
    
    QJsonDocument doc(jsonObj);
    QByteArray data = doc.toJson();
    
    // Enviar la solicitud POST
    QNetworkReply *reply = networkManager->post(request, data.constData());
    
    connect(reply, &QNetworkReply::finished, [this, productoId, nuevaCantidad, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            // Recargar el carrito desde la API para reflejar los cambios
            cargarProductosDesdeAPI();
            emit cantidadModificada(productoId, nuevaCantidad);
        } else {
            mostrarMensajeError("Error al modificar cantidad: " + reply->errorString());
            
            // Como respaldo, modificar localmente
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
    // Preparar la solicitud para limpiar el carrito
    QNetworkRequest request;
    request.setUrl(QUrl(apiUrl));
    request.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
    
    // Crear el objeto JSON para enviar
    QJsonObject jsonObj;
    jsonObj["accion"] = "limpiar";
    
    QJsonDocument doc(jsonObj);
    QByteArray data = doc.toJson();
    
    // Enviar la solicitud POST
    QNetworkReply *reply = networkManager->post(request, data.constData());
    
    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            // Recargar el carrito desde la API para reflejar los cambios
            productos.clear();
            actualizarInterfaz();
            emit carritoActualizado();
        } else {
            mostrarMensajeError("Error al limpiar carrito: " + reply->errorString());
            
            // Como respaldo, limpiar localmente
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

// Método para cargar productos desde la API
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
            // Si falla la API, intentar cargar desde la base de datos local como respaldo
            inicializarBaseDatos();
        }
        reply->deleteLater();
    });
}

// Método para procesar la respuesta de la API
void carrito::procesarRespuestaAPI(QNetworkReply *reply)
{
    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    
    if (jsonDoc.isArray()) {
        // Limpiar productos actuales
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
            
            // Agregar el producto al vector
            productos.append(producto);
        }
        
        // Actualizar la interfaz con los nuevos productos
        actualizarTotales();
        actualizarVisualizacion();
        
        emit carritoActualizado();
    } else {
        mostrarMensajeError("Formato de respuesta de API inválido");
    }
}

void carrito::cargarProductoDesdeDB(int productoId, ProductoCarrito& producto)
{
    QSqlQuery query(db);
    query.prepare("SELECT id, nombre, descripcion, precio, imagen, ingredientes, disponible "
                  "FROM productos WHERE id = ? AND activo = 1");
    query.addBindValue(productoId);
    
    if (query.exec() && query.next()) {
        producto.id = query.value(0).toInt();
        producto.nombre = query.value(1).toString();
        producto.descripcion = query.value(2).toString();
        producto.precio = query.value(3).toDouble();
        producto.imagen = query.value(4).toString();
        producto.ingredientes = query.value(5).toString();
        producto.disponible = query.value(6).toBool();
        producto.cantidad = 0;
        producto.precioTotal = 0.0;
        producto.comentarios = "";
    }
}

void carrito::crearWidgetProducto(const ProductoCarrito& producto)
{
    // Crear frame principal del producto
    QFrame* frameProducto = new QFrame();
    frameProducto->setStyleSheet("QFrame { background-color: white; border-radius: 15px; margin: 5px; padding: 10px; }");
    frameProducto->setMaximumSize(300, 300);
    frameProducto->setMinimumSize(280, 250);
    
    QVBoxLayout* layoutProducto = new QVBoxLayout(frameProducto);
    
    // Imagen del producto
    QLabel* labelImagen = new QLabel();
    labelImagen->setMaximumSize(400, 200);
    labelImagen->setStyleSheet("border-radius: 5px;");
    labelImagen->setScaledContents(true);
    
    if (!producto.imagen.isEmpty()) {
        QPixmap pixmap(":/img/" + producto.imagen);
        if (!pixmap.isNull()) {
            labelImagen->setPixmap(pixmap);
        } else {
            labelImagen->setText("Sin imagen");
            labelImagen->setAlignment(Qt::AlignCenter);
        }
    }
    
    // Nombre del producto
    QLabel* labelNombre = new QLabel(producto.nombre);
    labelNombre->setMaximumSize(200, 30);
    labelNombre->setFont(QFont("Segoe UI", 14));
    labelNombre->setStyleSheet("font-weight: bold;");
    
    // Frame de controles (precio, botones, eliminar)
    QFrame* frameControles = new QFrame();
    frameControles->setMaximumSize(380, 40);
    
    QHBoxLayout* layoutControles = new QHBoxLayout(frameControles);
    layoutControles->setContentsMargins(0, 0, 0, 0);
    
    // Frame de precio y botones
    QFrame* framePrecioBotones = new QFrame();
    framePrecioBotones->setMaximumSize(180, 40);
    
    QHBoxLayout* layoutPrecioBotones = new QHBoxLayout(framePrecioBotones);
    layoutPrecioBotones->setSpacing(9);
    layoutPrecioBotones->setContentsMargins(0, 0, 0, 0);
    
    // Precio
    QLabel* labelPrecio = new QLabel(QString(" $%1").arg(producto.precioTotal, 0, 'f', 2));
    labelPrecio->setMaximumSize(70, 30);
    labelPrecio->setFont(QFont("Segoe UI", 14));
    labelPrecio->setStyleSheet(
        "background-color: red; color: white; border-radius: 6px; padding: 4px;"
    );
    
    // Botón más
    QLabel* labelMas = new QLabel();
    labelMas->setMaximumSize(30, 30);
    labelMas->setPixmap(QPixmap(":/mas-top.png"));
    labelMas->setScaledContents(true);
    labelMas->setCursor(Qt::PointingHandCursor);
    
    // Botón menos
    QLabel* labelMenos = new QLabel();
    labelMenos->setMaximumSize(30, 30);
    labelMenos->setPixmap(QPixmap(":/menos-top.png"));
    labelMenos->setScaledContents(true);
    labelMenos->setCursor(Qt::PointingHandCursor);
    
    // Cantidad
    QLabel* labelCantidad = new QLabel(QString::number(producto.cantidad));
    labelCantidad->setMaximumSize(20, 30);
    labelCantidad->setAlignment(Qt::AlignCenter);
    labelCantidad->setStyleSheet("font-weight: bold; font-size: 14px;");
    
    layoutPrecioBotones->addWidget(labelPrecio);
    layoutPrecioBotones->addWidget(labelCantidad);
    layoutPrecioBotones->addWidget(labelMas);
    layoutPrecioBotones->addWidget(labelMenos);
    
    // Spacer
    QFrame* frameSpacer = new QFrame();
    frameSpacer->setMaximumSize(30, 40);
    
    // Botón eliminar
    QLabel* labelEliminar = new QLabel();
    labelEliminar->setMaximumSize(35, 35);
    labelEliminar->setPixmap(QPixmap(":/trash.png"));
    labelEliminar->setScaledContents(true);
    labelEliminar->setCursor(Qt::PointingHandCursor);
    
    layoutControles->addWidget(framePrecioBotones);
    layoutControles->addWidget(frameSpacer);
    layoutControles->addWidget(labelEliminar);
    
    // Agregar todo al layout principal
    layoutProducto->addWidget(labelImagen);
    layoutProducto->addWidget(labelNombre);
    layoutProducto->addWidget(frameControles);
    
    // Instalar event filters para hacer los botones clickeables
    labelMas->installEventFilter(this);
    labelMenos->installEventFilter(this);
    labelEliminar->installEventFilter(this);
    
    // Almacenar el ID del producto en los widgets para identificarlos
    labelMas->setProperty("productoId", producto.id);
    labelMas->setProperty("accion", "aumentar");
    
    labelMenos->setProperty("productoId", producto.id);
    labelMenos->setProperty("accion", "disminuir");
    
    labelEliminar->setProperty("productoId", producto.id);
    labelEliminar->setProperty("accion", "eliminar");
    
    // Agregar el frame al layout principal del carrito
    QVBoxLayout* layoutCarrito = qobject_cast<QVBoxLayout*>(ui->groupBox->layout());
    if (!layoutCarrito) {
        layoutCarrito = new QVBoxLayout(ui->groupBox);
    }
    
    layoutCarrito->addWidget(frameProducto);
}


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
        if (mouseEvent->button() == Qt::LeftButton) {
            QVariant productoIdVar = qobject_cast<QLabel*>(sender())->property("productoId");
            QVariant accionVar = qobject_cast<QLabel*>(sender())->property("accion");
            
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
    
    return QWidget::eventFilter(obj, event);
}


void carrito::actualizarTotales()
{
    subtotal = 0.0;
    for (const ProductoCarrito& producto : productos) {
        subtotal += producto.precioTotal;
    }
    total = subtotal; // El delivery se calcula en otro lugar
    
    // Actualizar etiquetas si existen en el UI
    // Nota: En el .ui actual no hay etiquetas para totales, 
    // pero podrías agregarlas si es necesario
}

void carrito::actualizarVisualizacion()
{
    limpiarLayout();
    
    if (productos.isEmpty()) {
        // Mostrar mensaje de carrito vacío
        QLabel* labelVacio = new QLabel("Carrito vacío");
        labelVacio->setAlignment(Qt::AlignCenter);
        labelVacio->setStyleSheet("color: #999; font-size: 16px; font-style: italic; padding: 20px;");
        
        QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->groupBox->layout());
        if (!layout) {
            layout = new QVBoxLayout(ui->groupBox);
        }
        layout->addWidget(labelVacio);
    } else {
        // Mostrar productos
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
    // En una implementación real, verificarías el stock en la base de datos
    // Por ahora, asumimos que hay stock disponible
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
    
    QSqlQuery query(db);
    query.prepare("SELECT id, nombre, tipo FROM condimentos WHERE activo = 1 ORDER BY tipo, nombre");
    
    if (query.exec()) {
        while (query.next()) {
            Condimento condimento;
            condimento.id = query.value(0).toInt();
            condimento.nombre = query.value(1).toString();
            condimento.tipo = query.value(2).toString();
            condimento.seleccionado = false;
            condimentos.append(condimento);
        }
    }
    
    return condimentos;
}

void carrito::mostrarSelectorCondimentos(int productoId)
{
    // Implementación del selector de condimentos
    // Podrías crear un diálogo para seleccionar condimentos
    Q_UNUSED(productoId)
    // Esta funcionalidad se puede expandir según las necesidades
}