#ifndef PANELCAJERO_H
#define PANELCAJERO_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QSpinBox>
#include <QtCore/QTimer>
#include <QtCore/QDateTime>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QVector>
#include <QMap>

QT_BEGIN_NAMESPACE
class Ui_PanelCajero;
QT_END_NAMESPACE

// Estructura para representar un producto
struct Producto {
    int id;
    QString nombre;
    QString descripcion;
    double precio;
    QString imagen;
    int categoriaId;
    QString ingredientes;
    int tiempoPreparacion;
    bool disponible;
    double valoracionPromedio;
    int totalValoraciones;
    bool activo;
};

// Estructura para representar un cliente
struct Cliente {
    int id;
    QString nombre;
    QString apellido;
    QString email;
    QString telefono;
    QString direccion;
    bool activo;
};

// Estructura para item del carrito
struct ItemCarrito {
    Producto producto;
    int cantidad;
    double precioTotal;
    QString comentarios;
};

class PanelCajero : public QWidget
{
    Q_OBJECT

public:
    PanelCajero(QWidget *parent = nullptr);
    ~PanelCajero();

private slots:
    void buscarCliente();
    void filtrarProductos();
    void buscarProductoPorNombre();
    void agregarProductoAlCarrito(int productoId);
    void eliminarDelCarrito(int index);
    void modificarCantidad(int index, int nuevaCantidad);
    void actualizarTotales();
    void toggleTipoPedido();
    void crearPedido();
    void validarHorarioLaboral();

private:
    Ui_PanelCajero *ui;
    
    // Base de datos
    QSqlDatabase db;
    bool inicializarBaseDatos();
    
    // Datos
    QVector<Producto> productos;
    QVector<Cliente> clientes;
    QVector<ItemCarrito> carrito;
    Cliente clienteSeleccionado;
    bool clienteEstaSeleccionado;
    
    // Cálculos
    double subtotal;
    double precioDelivery;
    double total;
    
    // Configuración del horario
    QTime horaApertura1;
    QTime horaCierre1;
    QTime horaApertura2;
    QTime horaCierre2;
    
    // Métodos privados
    void cargarProductos();
    void cargarClientes();
    void mostrarProductos();
    void mostrarProductos(const QString& filtroCategoria, const QString& filtroNombre = "");
    void crearWidgetProducto(const Producto& producto, QVBoxLayout* layout);
    void actualizarCarritoVisual();
    void seleccionarCliente(const Cliente& cliente);
    void limpiarSeleccionCliente();
    void calcularPrecioDelivery(const QString& direccion);
    double calcularDistancia(const QString& direccionDestino);
    bool validarPedidoInmediato();
    bool validarPedidoProgramado(const QDateTime& fechaHora);
    void limpiarCarrito();
    void mostrarMensajeError(const QString& mensaje);
    void mostrarMensajeExito(const QString& mensaje);
    QString generarNumeroPedido();
    void configurarEventos();
    void cargarConfiguracion();
    
    // Métodos de búsqueda
    QVector<Cliente> buscarClientesPorTexto(const QString& texto);
    QVector<Producto> filtrarProductosPorCategoria(int categoriaId);
    QVector<Producto> buscarProductosPorNombre(const QString& nombre);
};

#endif // PANELCAJERO_H