#ifndef CARRITO_H
#define CARRITO_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QScrollArea>
#include <QMessageBox>
#include <QTimer>
#include <QVector>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QEvent>
#include <QMouseEvent>
#include <QMenu>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class carrito; }
QT_END_NAMESPACE

struct ProductoCarrito {
    int id;
    QString nombre;
    QString descripcion;
    double precio;
    QString imagen;
    QString ingredientes;
    int cantidad;
    double precioTotal;
    bool disponible;
    QString comentarios;
    int tiempoPreparacion;
};

struct Condimento {
    int id;
    QString nombre;
    QString tipo;
    bool seleccionado;
};
class ConfirmacionPedido; // Declaración adelantada
struct ProductoConfirmacion; // Declaración adelantada del struct usado

class carrito : public QWidget
{
    Q_OBJECT

public:
    carrito(QWidget *parent = nullptr);
    ~carrito();

    bool eventFilter(QObject *obj, QEvent *event);

    ConfirmacionPedido* getConfirmacionPedido(void);

    void agregarProducto(int productoId, int cantidad = 1);
    void eliminarProducto(int productoId);
    void modificarCantidad(int productoId, int nuevaCantidad);
    void limpiarCarrito();

    QVector<ProductoCarrito> obtenerProductos() const;
    double obtenerSubtotal() const;
    double obtenerTotal() const;
    int obtenerCantidadItems() const;
    bool estaVacio() const;

signals:
    void carritoActualizado();
    void productoEliminado(int productoId);
    void cantidadModificada(int productoId, int nuevaCantidad);
    void finalizarPedidoClicked();
    void navegarASeccion(const QString& seccion);

private slots:
    void aumentarCantidad(int productoId);
    void disminuirCantidad(int productoId);
    void eliminarDelCarrito(int productoId);
    void finalizarPedido();
    void actualizarInterfaz();
    void procesarRespuestaAPI(QNetworkReply *reply);
    void mostrarMenuNavegacion();
    void irAConfirmacionPedido();

private:
    Ui::carrito *ui;

    QVector<ProductoCarrito> productos;
    double subtotal;
    double total;

    QNetworkAccessManager *networkManager;
    QString apiUrl;
    QLabel* labelMenuHamburguesa;
    QMenu* menuNavegacion;

    void cargarProductosDesdeAPI();
    bool validarPedido();
    void crearWidgetProducto(const ProductoCarrito& producto);
    void actualizarTotales();
    void actualizarVisualizacion();
    bool validarStock(int productoId, int cantidadSolicitada);
    void mostrarMensajeError(const QString& mensaje);
    void mostrarMensajeExito(const QString& mensaje);
    ProductoCarrito* buscarProducto(int productoId);
    void limpiarLayout();
    void configurarEventos();
    void crearMenuNavegacion();

    QVector<Condimento> cargarCondimentosDisponibles();
    void mostrarSelectorCondimentos(int productoId);
};

#endif // CARRITO_H
