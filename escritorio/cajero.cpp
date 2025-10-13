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
    , groupBoxNuevoCliente(nullptr)
{
    ui->setupUi(this);
    
    crearFormularioNuevoCliente();
    cargarConfiguracion();
    configurarEventos();
    inicializarProductosEjemplo();
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

void PanelCajero::inicializarProductosEjemplo()
{
    todosLosProductos.clear();
    
    // MINUTAS
    Producto m1 = {1, "Milanesa con papas fritas", "Milanesa de carne con guarnición de papas fritas caseras", 2500.0, "hamburguesa.jpeg", 1, "Minutas", "Carne, pan rallado, papas", 25, true, 4.5, 120, true};
    Producto m2 = {2, "Milanesa napolitana", "Milanesa con jamón, queso y salsa de tomate", 2800.0, "hamburguesa.jpeg", 1, "Minutas", "Carne, jamón, queso, tomate", 30, true, 4.7, 150, true};
    Producto m3 = {3, "Suprema de pollo", "Pechuga de pollo con ensalada", 2300.0, "hamburguesa.jpeg", 1, "Minutas", "Pollo, lechuga, tomate", 25, true, 4.3, 90, true};
    Producto m4 = {4, "Bife de chorizo", "Bife de 300g con guarnición a elección", 3500.0, "hamburguesa.jpeg", 1, "Minutas", "Carne de res", 20, true, 4.8, 200, true};
    Producto m5 = {5, "Lomito completo", "Lomito con jamón, queso, huevo y verduras", 3200.0, "hamburguesa.jpeg", 1, "Minutas", "Carne, jamón, queso, huevo", 30, true, 4.6, 180, true};
    
    todosLosProductos << m1 << m2 << m3 << m4 << m5;
    
    // PASTAS
    Producto p1 = {6, "Ravioles de ricota", "Ravioles caseros con salsa a elección", 1800.0, "hamburguesa.jpeg", 2, "Pastas", "Masa, ricota, salsa", 15, true, 4.4, 110, true};
    Producto p2 = {7, "Sorrentinos de jamón y queso", "Sorrentinos con salsa fileto", 2000.0, "hamburguesa.jpeg", 2, "Pastas", "Masa, jamón, queso, tomate", 15, true, 4.6, 130, true};
    Producto p3 = {8, "Ñoquis de papa", "Ñoquis caseros con salsa bolognesa", 1700.0, "hamburguesa.jpeg", 2, "Pastas", "Papa, harina, carne picada", 20, true, 4.2, 95, true};
    Producto p4 = {9, "Lasagna de carne", "Lasagna con carne picada y bechamel", 2200.0, "hamburguesa.jpeg", 2, "Pastas", "Pasta, carne, bechamel", 25, true, 4.7, 140, true};
    Producto p5 = {10, "Canelones de verdura", "Canelones rellenos de espinaca y ricota", 1900.0, "hamburguesa.jpeg", 2, "Pastas", "Pasta, espinaca, ricota", 20, true, 4.3, 85, true};
    
    todosLosProductos << p1 << p2 << p3 << p4 << p5;
    
    // GUISOS
    Producto g1 = {11, "Guiso de lentejas", "Guiso casero de lentejas con chorizo", 1500.0, "hamburguesa.jpeg", 3, "Guisos", "Lentejas, chorizo, verduras", 35, true, 4.5, 100, true};
    Producto g2 = {12, "Locro", "Locro tradicional argentino", 2000.0, "hamburguesa.jpeg", 3, "Guisos", "Maíz, porotos, carne, chorizo", 40, true, 4.8, 160, true};
    Producto g3 = {13, "Guiso de mondongo", "Mondongo con garbanzos y papas", 1800.0, "hamburguesa.jpeg", 3, "Guisos", "Mondongo, garbanzos, papa", 45, true, 4.4, 80, true};
    Producto g4 = {14, "Carbonada", "Guiso de carne con frutas", 1700.0, "hamburguesa.jpeg", 3, "Guisos", "Carne, durazno, papa, choclo", 35, true, 4.3, 70, true};
    Producto g5 = {15, "Guiso carrero", "Guiso de arroz con carne", 1600.0, "hamburguesa.jpeg", 3, "Guisos", "Arroz, carne, verduras", 30, true, 4.2, 90, true};
    
    todosLosProductos << g1 << g2 << g3 << g4 << g5;
    
    // TARTAS
    Producto t1 = {16, "Tarta de jamón y queso", "Tarta casera con jamón y queso", 1800.0, "hamburguesa.jpeg", 4, "Tartas", "Masa, jamón, queso", 30, true, 4.4, 120, true};
    Producto t2 = {17, "Tarta de verduras", "Tarta de espinaca y acelga", 1600.0, "hamburguesa.jpeg", 4, "Tartas", "Masa, espinaca, acelga, huevo", 30, true, 4.3, 95, true};
    Producto t3 = {18, "Tarta de pollo", "Tarta con pollo desmenuzado", 1900.0, "hamburguesa.jpeg", 4, "Tartas", "Masa, pollo, cebolla", 30, true, 4.5, 110, true};
    Producto t4 = {19, "Tarta de atún", "Tarta con atún y vegetales", 2000.0, "hamburguesa.jpeg", 4, "Tartas", "Masa, atún, tomate, cebolla", 30, true, 4.2, 85, true};
    Producto t5 = {20, "Tarta caprese", "Tarta de tomate, mozzarella y albahaca", 2100.0, "hamburguesa.jpeg", 4, "Tartas", "Masa, tomate, mozzarella, albahaca", 30, true, 4.6, 130, true};
    
    todosLosProductos << t1 << t2 << t3 << t4 << t5;
    
    // EMPANADAS
    Producto e1 = {21, "Empanadas de carne (docena)", "Docena de empanadas de carne cortada a cuchillo", 3000.0, "hamburguesa.jpeg", 5, "Empanadas", "Masa, carne, cebolla, especias", 25, true, 4.7, 200, true};
    Producto e2 = {22, "Empanadas de pollo (docena)", "Docena de empanadas de pollo con verduras", 2800.0, "hamburguesa.jpeg", 5, "Empanadas", "Masa, pollo, cebolla, morrón", 25, true, 4.5, 180, true};
    Producto e3 = {23, "Empanadas de jamón y queso (docena)", "Docena de empanadas de jamón y queso", 2700.0, "hamburguesa.jpeg", 5, "Empanadas", "Masa, jamón, queso", 25, true, 4.6, 170, true};
    Producto e4 = {24, "Empanadas de verdura (docena)", "Docena de empanadas de verdura", 2500.0, "hamburguesa.jpeg", 5, "Empanadas", "Masa, acelga, cebolla, queso", 25, true, 4.3, 140, true};
    Producto e5 = {25, "Empanadas árabes (docena)", "Docena de empanadas de carne con limón", 3200.0, "hamburguesa.jpeg", 5, "Empanadas", "Masa, carne, limón, especias", 25, true, 4.8, 190, true};
    
    todosLosProductos << e1 << e2 << e3 << e4 << e5;
    
    // POSTRES
    Producto po1 = {26, "Flan casero", "Flan casero con dulce de leche", 800.0, "hamburguesa.jpeg", 6, "Postres", "Huevo, leche, azúcar", 5, true, 4.5, 150, true};
    Producto po2 = {27, "Tiramisu", "Postre italiano con café", 1200.0, "hamburguesa.jpeg", 6, "Postres", "Mascarpone, café, vainillas", 5, true, 4.7, 180, true};
    Producto po3 = {28, "Panqueques con dulce de leche", "3 panqueques rellenos", 900.0, "hamburguesa.jpeg", 6, "Postres", "Harina, huevo, dulce de leche", 10, true, 4.4, 120, true};
    Producto po4 = {29, "Arroz con leche", "Arroz con leche casero", 700.0, "hamburguesa.jpeg", 6, "Postres", "Arroz, leche, azúcar, canela", 5, true, 4.2, 100, true};
    Producto po5 = {30, "Ensalada de frutas", "Ensalada de frutas frescas de estación", 850.0, "hamburguesa.jpeg", 6, "Postres", "Frutas variadas", 5, true, 4.3, 110, true};
    
    todosLosProductos << po1 << po2 << po3 << po4 << po5;
    
    // BEBIDAS
    Producto b1 = {31, "Coca Cola 2.25L", "Gaseosa Coca Cola", 1200.0, "hamburguesa.jpeg", 7, "Bebidas", "", 2, true, 4.0, 300, true};
    Producto b2 = {32, "Sprite 2.25L", "Gaseosa Sprite", 1200.0, "hamburguesa.jpeg", 7, "Bebidas", "", 2, true, 4.0, 280, true};
    Producto b3 = {33, "Fanta 2.25L", "Gaseosa Fanta", 1200.0, "hamburguesa.jpeg", 7, "Bebidas", "", 2, true, 4.0, 270, true};
    Producto b4 = {34, "Agua mineral 2L", "Agua mineral sin gas", 600.0, "hamburguesa.jpeg", 7, "Bebidas", "", 2, true, 4.1, 200, true};
    Producto b5 = {35, "Cerveza Quilmes 1L", "Cerveza Quilmes", 1000.0, "hamburguesa.jpeg", 7, "Bebidas", "", 2, false, 4.3, 250, true};
    
    todosLosProductos << b1 << b2 << b3 << b4 << b5;
    
    // EMBUTIDOS (por 100g)
    Producto em1 = {36, "Jamón cocido (100g)", "Jamón cocido premium", 450.0, "hamburguesa.jpeg", 8, "Embutidos", "Cerdo", 2, true, 4.4, 150, true};
    Producto em2 = {37, "Jamón crudo (100g)", "Jamón crudo importado", 850.0, "hamburguesa.jpeg", 8, "Embutidos", "Cerdo curado", 2, true, 4.6, 130, true};
    Producto em3 = {38, "Salame (100g)", "Salame tandilero", 600.0, "hamburguesa.jpeg", 8, "Embutidos", "Carne de cerdo", 2, true, 4.5, 140, true};
    Producto em4 = {39, "Queso provolone (100g)", "Queso provolone", 500.0, "hamburguesa.jpeg", 8, "Embutidos", "Leche de vaca", 2, true, 4.4, 120, true};
    Producto em5 = {40, "Mortadela (100g)", "Mortadela con aceitunas", 350.0, "hamburguesa.jpeg", 8, "Embutidos", "Carne de cerdo", 2, true, 4.2, 100, true};
    
    todosLosProductos << em1 << em2 << em3 << em4 << em5;
    
    // COMIDAS RÁPIDAS
    Producto cr1 = {41, "Hamburguesa completa", "Hamburguesa con todos los ingredientes", 2000.0, "hamburguesa.jpeg", 9, "Comidas Rápidas", "Pan, carne, lechuga, tomate, queso", 15, true, 4.5, 220, true};
    Producto cr2 = {42, "Pancho completo", "Pancho con papas fritas", 1500.0, "hamburguesa.jpeg", 9, "Comidas Rápidas", "Pan, salchicha, salsas", 10, true, 4.3, 180, true};
    Producto cr3 = {43, "Pizza muzarella", "Pizza casera con muzarella", 2500.0, "hamburguesa.jpeg", 9, "Comidas Rápidas", "Masa, tomate, queso", 20, true, 4.6, 250, true};
    Producto cr4 = {44, "Sandwich de milanesa", "Sandwich con milanesa y guarnición", 1800.0, "hamburguesa.jpeg", 9, "Comidas Rápidas", "Pan, milanesa, lechuga, tomate", 15, true, 4.4, 160, true};
    Producto cr5 = {45, "Papas fritas grandes", "Porción grande de papas fritas", 1200.0, "hamburguesa.jpeg", 9, "Comidas Rápidas", "Papas", 10, true, 4.2, 200, true};
    
    todosLosProductos << cr1 << cr2 << cr3 << cr4 << cr5;
    
    // OTROS
    Producto o1 = {46, "Pollo al espiedo entero", "Pollo al espiedo para llevar", 3500.0, "hamburguesa.jpeg", 10, "Otros", "Pollo", 30, true, 4.8, 300, true};
    Producto o2 = {47, "Costillas al horno", "Costillas de cerdo al horno", 4000.0, "hamburguesa.jpeg", 10, "Otros", "Costillas de cerdo", 40, true, 4.7, 180, true};
    Producto o3 = {48, "Matambre a la pizza", "Matambre con salsa y queso", 3200.0, "hamburguesa.jpeg", 10, "Otros", "Matambre, salsa, queso", 35, true, 4.6, 150, true};
    Producto o4 = {49, "Bondiola al horno", "Bondiola de cerdo al horno", 3800.0, "hamburguesa.jpeg", 10, "Otros", "Bondiola de cerdo", 45, true, 4.5, 120, true};
    Producto o5 = {50, "Vacío a la parrilla", "Vacío para 4 personas", 5000.0, "hamburguesa.jpeg", 10, "Otros", "Carne vacuna", 35, true, 4.9, 200, true};
    
    todosLosProductos << o1 << o2 << o3 << o4 << o5;
    
    productos = todosLosProductos;
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
        precioDelivery = 200.0;
    } else if (distancia <= 3.0) {
        precioDelivery = 350.0;
    } else if (distancia <= 5.0) {
        precioDelivery = 500.0;
    } else if (distancia <= 7.0) {
        precioDelivery = 700.0;
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
        ui->dateEdit_fecha->setDate(QDate::currentDate());
        ui->dateEdit_fecha->setMinimumDate(QDate::currentDate());
        ui->dateEdit_fecha->setMaximumDate(QDate::currentDate().addDays(7));
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
    QDateTime ahora = QDateTime::currentDateTime();
    if (fechaHora <= ahora) {
        return false;
    }
    
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
    QString tipoPedido = ui->radioButton_inmediato->isChecked() ? "Inmediato" : "Programado";
    
    QString mensaje = QString("Pedido creado exitosamente!\n\n"
                             "Número: %1\n"
                             "Cliente: %2 %3\n"
                             "Tipo: %4\n"
                             "Total: $%5")
                        .arg(numeroPedido)
                        .arg(clienteSeleccionado.nombre)
                        .arg(clienteSeleccionado.apellido)
                        .arg(tipoPedido)
                        .arg(total, 0, 'f', 2);
    
    if (ui->radioButton_programado->isChecked()) {
        QDateTime fechaEntrega(ui->dateEdit_fecha->date(), ui->timeEdit_hora->time());
        mensaje += QString("\nEntrega: %1").arg(fechaEntrega.toString("dd/MM/yyyy HH:mm"));
    }
    
    mostrarMensajeExito(mensaje);
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

void PanelCajero::cargarDatosDesdeAPI()
{
    // Cargar clientes de ejemplo
    cargarClientes();
    mostrarProductos();
}

void PanelCajero::cargarClientes()
{
    clientes.clear();
    
    Cliente c1 = {1, "Juan", "Pérez", "juan.perez@example.com", "3511234567", "Av. Colón 1234, Centro", true, false};
    Cliente c2 = {2, "María", "González", "maria.gonzalez@example.com", "3519876543", "Calle Lima 567, Nueva Córdoba", true, false};
    Cliente c3 = {3, "Carlos", "Rodríguez", "carlos.rodriguez@example.com", "3515555555", "Av. Vélez Sarsfield 2345, Güemes", true, false};
    Cliente c4 = {4, "Ana", "Martínez", "ana.martinez@example.com", "3517777777", "Rondeau 890, Centro", true, false};
    Cliente c5 = {5, "Pedro", "López", "pedro.lopez@example.com", "3513333333", "Chacabuco 456, Alberdi", true, false};
    
    clientes << c1 << c2 << c3 << c4 << c5;
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
