#ifndef CARRITO_H
#define CARRITO_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QMessageBox>
#include <QtCore/QTimer>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QVector>

QT_BEGIN_NAMESPACE
class Ui_carrito;
QT_END_NAMESPACE

// Estructura para representar un producto en el carrito
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
};

// Estructura para condimentos
struct Condimento {
    int id;
    QString nombre;
    QString tipo;
    bool seleccionado;
};

class carrito : public QWidget
{
    Q_OBJECT

public:
    carrito(QWidget *parent = nullptr);
    ~carrito();

    // Métodos públicos para manejar el carrito
    void agregarProducto(int productoId, int cantidad = 1);
    void eliminarProducto(int productoId);
    void modificarCantidad(int productoId, int nuevaCantidad);
    void limpiarCarrito();
    
    // Getters
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

private slots:
    void aumentarCantidad(int productoId);
    void disminuirCantidad(int productoId);
    void eliminarDelCarrito(int productoId);
    void finalizarPedido();
    void actualizarInterfaz();

private:
    Ui_carrito *ui;
    
    // Base de datos
    QSqlDatabase db;
    bool inicializarBaseDatos();
    
    // Datos del carrito
    QVector<ProductoCarrito> productos;
    double subtotal;
    double total;
    
    // Métodos privados
    void cargarProductoDesdeDB(int productoId, ProductoCarrito& producto);
    void crearWidgetProducto(const ProductoCarrito& producto);
    void actualizarTotales();
    void actualizarVisualizacion();
    bool validarStock(int productoId, int cantidadSolicitada);
    void mostrarMensajeError(const QString& mensaje);
    void mostrarMensajeExito(const QString& mensaje);
    ProductoCarrito* buscarProducto(int productoId);
    void limpiarLayout();
    void configurarEventos();
    
    // Métodos para condimentos
    QVector<Condimento> cargarCondimentosDisponibles();
    void mostrarSelectorCondimentos(int productoId);
};

#endif // CARRITO_H