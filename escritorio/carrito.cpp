#include "carrito.h"
#include "ui_carrito.h"
#include "confirmacion_pedido.h"
#include <QDebug>

carrito::carrito(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::carrito)
    , subtotal(0.0)
    , total(0.0)
    , networkManager(new QNetworkAccessManager(this))
    , apiUrl("http://localhost/WEB_ElBuenGusto/api/carrito.php")
    , menuNavegacion(nullptr)
    , labelMenuHamburguesa(nullptr)
{
    ui->setupUi(this);
    crearMenuNavegacion();
    configurarEventos();
    cargarProductosDesdeAPI();
    actualizarInterfaz();
}

carrito::~carrito()
{
    delete ui;
    if (menuNavegacion) {
        delete menuNavegacion;
    }
}

void carrito::crearMenuNavegacion()
{
    // Encontrar el label del menú hamburguesa
    labelMenuHamburguesa = ui->label_2;

    if (labelMenuHamburguesa) {
        labelMenuHamburguesa->setCursor(Qt::PointingHandCursor);
        labelMenuHamburguesa->installEventFilter(this);

        // Crear el menú contextual
        menuNavegacion = new QMenu(this);
        menuNavegacion->setStyleSheet(
            "QMenu { "
            "background-color: rgb(245,235,210); "
            "border: 2px solid rgb(80,50,20); "
            "border-radius: 8px; "
            "padding: 8px; "
            "} "
            "QMenu::item { "
            "padding: 10px 25px; "
            "background-color: transparent; "
            "color: rgb(80,50,20); "
            "font-size: 13px; "
            "font-weight: bold; "
            "} "
            "QMenu::item:selected { "
            "background-color: rgb(200,30,45); "
            "color: white; "
            "border-radius: 4px; "
            "} "
            "QMenu::separator { "
            "height: 2px; "
            "background-color: rgb(200,30,45); "
            "margin: 5px 10px; "
            "}"
            );

        // Agregar opciones al menú
        QAction* accionInicio = menuNavegacion->addAction("🏠 Inicio");
        QAction* accionMinutas = menuNavegacion->addAction("🍽️ Minutas");
        QAction* accionPastas = menuNavegacion->addAction("🍝 Pastas");
        QAction* accionGuisos = menuNavegacion->addAction("🍲 Guisos");
        QAction* accionTartas = menuNavegacion->addAction("🥧 Tartas");
        QAction* accionEmpanadas = menuNavegacion->addAction("🥟 Empanadas");
        menuNavegacion->addSeparator();
        QAction* accionPostres = menuNavegacion->addAction("🍰 Postres");
        QAction* accionBebidas = menuNavegacion->addAction("🥤 Bebidas");
        QAction* accionEmbutidos = menuNavegacion->addAction("🥓 Embutidos");
        menuNavegacion->addSeparator();
        QAction* accionComidasRapidas = menuNavegacion->addAction("🍔 Comidas Rápidas");
        QAction* accionOtros = menuNavegacion->addAction("📦 Otros");
        menuNavegacion->addSeparator();
        QAction* accionMisPedidos = menuNavegacion->addAction("📋 Mis Pedidos");
        QAction* accionPerfil = menuNavegacion->addAction("👤 Mi Perfil");

        // Conectar señales
        connect(accionInicio, &QAction::triggered, [this]() {
            emit navegarASeccion("Inicio");
            this->hide();
        });
        connect(accionMinutas, &QAction::triggered, [this]() {
            emit navegarASeccion("Minutas");
            this->hide();
        });
        connect(accionPastas, &QAction::triggered, [this]() {
            emit navegarASeccion("Pastas");
            this->hide();
        });
        connect(accionGuisos, &QAction::triggered, [this]() {
            emit navegarASeccion("Guisos");
            this->hide();
        });
        connect(accionTartas, &QAction::triggered, [this]() {
            emit navegarASeccion("Tartas");
            this->hide();
        });
        connect(accionEmpanadas, &QAction::triggered, [this]() {
            emit navegarASeccion("Empanadas");
            this->hide();
        });
        connect(accionPostres, &QAction::triggered, [this]() {
            emit navegarASeccion("Postres");
            this->hide();
        });
        connect(accionBebidas, &QAction::triggered, [this]() {
            emit navegarASeccion("Bebidas");
            this->hide();
        });
        connect(accionEmbutidos, &QAction::triggered, [this]() {
            emit navegarASeccion("Embutidos");
            this->hide();
        });
        connect(accionComidasRapidas, &QAction::triggered, [this]() {
            emit navegarASeccion("ComidasRapidas");
            this->hide();
        });
        connect(accionOtros, &QAction::triggered, [this]() {
            emit navegarASeccion("Otros");
            this->hide();
        });
        connect(accionMisPedidos, &QAction::triggered, [this]() {
            emit navegarASeccion("MisPedidos");
            this->hide();
        });
        connect(accionPerfil, &QAction::triggered, [this]() {
            emit navegarASeccion("Perfil");
            this->hide();
        });
    }
}

void carrito::mostrarMenuNavegacion()
{
    if (menuNavegacion && labelMenuHamburguesa) {
        QPoint posicion = labelMenuHamburguesa->mapToGlobal(QPoint(0, labelMenuHamburguesa->height()));
        menuNavegacion->exec(posicion);
    }
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
    // Menú hamburguesa
    if (obj == labelMenuHamburguesa && event->type() == QEvent::MouseButtonPress) {
        mostrarMenuNavegacion();
        return true;
    }

    // Botón finalizar pedido
    if (obj == ui->label && event->type() == QEvent::MouseButtonPress) {
        finalizarPedido();
        return true;
    }

    // Controles del carrito
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

    if (!validarPedido()) {
        return;
    }

    irAConfirmacionPedido();
}

void carrito::irAConfirmacionPedido()
{
    // Convertir productos del carrito a formato de confirmación
    QVector<ProductoConfirmacion> productosConfirmacion;

    for (const ProductoCarrito& prod : productos) {
        ProductoConfirmacion prodConf;
        prodConf.id = prod.id;
        prodConf.nombre = prod.nombre;
        prodConf.descripcion = prod.descripcion;
        prodConf.precio = prod.precio;
        prodConf.cantidad = prod.cantidad;
        prodConf.precioTotal = prod.precioTotal;
        prodConf.comentarios = prod.comentarios;

        productosConfirmacion.append(prodConf);
    }

    // Crear ventana de confirmación
    ConfirmacionPedido* ventanaConfirmacion = new ConfirmacionPedido(productosConfirmacion);
    ventanaConfirmacion->setAttribute(Qt::WA_DeleteOnClose);

    // Conectar señales
    connect(ventanaConfirmacion, &ConfirmacionPedido::pedidoConfirmado, [this](int pedidoId) {
        limpiarCarrito();
        mostrarMensajeExito(QString("¡Pedido #%1 confirmado exitosamente!\n\nRecibirás una factura en tu email.").arg(pedidoId));
        this->hide();
    });

    connect(ventanaConfirmacion, &ConfirmacionPedido::volverAlCarrito, [ventanaConfirmacion, this]() {
        ventanaConfirmacion->close();
        this->show();
        this->raise();
        this->activateWindow();
    });

    // Ocultar carrito y mostrar ventana de confirmación
    this->hide();
    ventanaConfirmacion->setWindowModality(Qt::ApplicationModal);
    ventanaConfirmacion->show();
    ventanaConfirmacion->raise();
    ventanaConfirmacion->activateWindow();
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
            qDebug() << "Error al cargar productos del carrito:" << reply->errorString();
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
            producto.disponible = obj["disponible"].toBool();
            producto.descripcion = obj["descripcion"].toString();
            producto.imagen = obj["imagen"].toString();
            producto.ingredientes = obj["ingredientes"].toString();
            producto.comentarios = "";
            producto.tiempoPreparacion = obj["tiempo_preparacion"].toInt(20);

            productos.append(producto);
        }

        actualizarTotales();
        actualizarVisualizacion();

        emit carritoActualizado();
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
            labelImagen->setStyleSheet("background-color: #ddd; border-radius: 5px;");
        }
    }

    QLabel* labelNombre = new QLabel(producto.nombre);
    labelNombre->setMaximumSize(280, 40);
    labelNombre->setFont(QFont("Segoe UI", 12, QFont::Bold));
    labelNombre->setWordWrap(true);
    labelNombre->setStyleSheet("color: rgb(80,50,20);");

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
    labelPrecio->setFont(QFont("Segoe UI", 13, QFont::Bold));
    labelPrecio->setStyleSheet("background-color: rgb(200,30,45); color: white; border-radius: 6px; padding: 4px;");

    QLabel* labelCantidad = new QLabel(QString::number(producto.cantidad));
    labelCantidad->setMaximumSize(20, 30);
    labelCantidad->setAlignment(Qt::AlignCenter);
    labelCantidad->setStyleSheet("font-weight: bold; font-size: 13px; color: rgb(80,50,20);");

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
        labelVacio->setStyleSheet("color: rgb(80,50,20); font-size: 16px; font-style: italic; padding: 40px;");

        QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->groupBox->layout());
        if (!layout) {
            layout = new QVBoxLayout(ui->groupBox);
        }
        layout->addWidget(labelVacio);

        // Actualizar texto del botón
        ui->label->setText("Carrito Vacío");
        ui->label->setStyleSheet(
            "QLabel { background-color: #999; color: white; border-radius: 6px; "
            "padding: 10px; font-size: 14px; font-weight: bold; text-align: center; }"
            );
        ui->label->setCursor(Qt::ArrowCursor);
    } else {
        for (const ProductoCarrito& producto : productos) {
            crearWidgetProducto(producto);
        }

        // Actualizar texto del botón
        ui->label->setText(QString("Finalizar Pedido (%1 items) - $%2")
                               .arg(obtenerCantidadItems())
                               .arg(total, 0, 'f', 2));
        ui->label->setStyleSheet(
            "QLabel { background-color: rgb(200,30,45); color: white; border-radius: 6px; "
            "padding: 10px; font-size: 14px; font-weight: bold; text-align: center; }"
            );
        ui->label->setCursor(Qt::PointingHandCursor);
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
    // En producción aquí verificarías el stock real desde la BD
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
    // Aquí cargarías los condimentos desde la API
    return condimentos;
}

void carrito::mostrarSelectorCondimentos(int productoId)
{
    Q_UNUSED(productoId)
    // Aquí implementarías el selector de condimentos
}
