#ifndef PANELCAJERO_H
#define PANELCAJERO_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QRadioButton>
#include <QDateEdit>
#include <QTimeEdit>
#include <QMessageBox>
#include <QSpinBox>
#include <QTimer>
#include <QDateTime>
#include <QVector>
#include <QMap>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

QT_BEGIN_NAMESPACE
namespace Ui { class PanelCajero; }
QT_END_NAMESPACE

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

struct Cliente {
    int id;
    QString nombre;
    QString apellido;
    QString email;
    QString telefono;
    QString direccion;
    bool activo;
};

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
    void procesarRespuestaCajero(QNetworkReply *reply);
    void actualizarReloj();

private:
    Ui::PanelCajero *ui;
    
    QVector<Producto> productos;
    QVector<Cliente> clientes;
    QVector<ItemCarrito> carrito;
    Cliente clienteSeleccionado;
    bool clienteEstaSeleccionado;
    
    double subtotal;
    double precioDelivery;
    double total;
    
    QTime horaApertura1;
    QTime horaCierre1;
    QTime horaApertura2;
    QTime horaCierre2;
    
    QNetworkAccessManager *networkManager;
    QString apiUrl;
    QTimer *relojTimer;
    
    void cargarProductos();
    void cargarClientes();
    void cargarDatosDesdeAPI();
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
    bool validarCreacionPedido();
    void limpiarCarrito();
    void mostrarMensajeError(const QString& mensaje);
    void mostrarMensajeExito(const QString& mensaje);
    QString generarNumeroPedido();
    void configurarEventos();
    void cargarConfiguracion();
    
    QVector<Cliente> buscarClientesPorTexto(const QString& texto);
    QVector<Producto> filtrarProductosPorCategoria(int categoriaId);
    QVector<Producto> buscarProductosPorNombre(const QString& nombre);
};

#endif // PANELCAJERO_H