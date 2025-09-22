#ifndef CONFIRMACIONPEDIDO_H
#define CONFIRMACIONPEDIDO_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QGroupBox>
#include <QtCore/QTimer>
#include <QtCore/QDateTime>
#include <QtCore/QRegularExpression>
#include <QtCore/QRegularExpressionValidator>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QVector>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
class Ui_ConfirmacionPedido;
QT_END_NAMESPACE

// Estructura para representar un producto del carrito en la confirmación
struct ProductoConfirmacion {
    int id;
    QString nombre;
    QString descripcion;
    double precio;
    int cantidad;
    double precioTotal;
    QString comentarios;
};

// Estructura para datos del cliente
struct DatosCliente {
    QString nombre;
    QString apellido;
    QString telefono;
    QString email;
    QString direccion;
    bool esClienteExistente;
    int clienteId;
};

// Estructura para configuración del pedido
struct ConfiguracionPedido {
    QString tipoPedido; // "inmediato" o "programado"
    QDateTime fechaEntrega;
    QString metodoPago; // "digital" o "efectivo"
    QString comentarios;
    double subtotal;
    double costoDelivery;
    double total;
};

class ConfirmacionPedido : public QWidget
{
    Q_OBJECT

public:
    ConfirmacionPedido(QWidget *parent = nullptr);
    ConfirmacionPedido(const QVector<ProductoConfirmacion>& productos, QWidget *parent = nullptr);
    ~ConfirmacionPedido();

    // Métodos para configurar datos iniciales
    void establecerProductos(const QVector<ProductoConfirmacion>& productos);
    void establecerDatosCliente(const DatosCliente& cliente);

signals:
    void pedidoConfirmado(int pedidoId);
    void volverAlCarrito();
    void errorEnPedido(const QString& mensaje);

private slots:
    void validarFormulario();
    void calcularCostoDelivery();
    void toggleTipoPedido();
    void toggleMetodoPago();
    void confirmarPedido();
    void volverCarrito();
    void onDireccionChanged();
    void validarCamposObligatorios();

private:
    Ui_ConfirmacionPedido *ui;
    
    // Base de datos
    QSqlDatabase db;
    bool inicializarBaseDatos();
    
    // Datos
    QVector<ProductoConfirmacion> productosCarrito;
    DatosCliente datosCliente;
    ConfiguracionPedido configuracionPedido;
    
    // Configuración del sistema
    QTime horaApertura1;
    QTime horaCierre1;
    QTime horaApertura2;
    QTime horaCierre2;
    QString direccionSucursal;
    
    // Validadores
    QRegularExpressionValidator* validadorTelefono;
    QRegularExpressionValidator* validadorEmail;
    
    // Red para cálculo de distancia (opcional)
    QNetworkAccessManager* networkManager;
    
    // Métodos privados de inicialización
    void configurarInterfaz();
    void configurarValidadores();
    void configurarEventos();
    void cargarConfiguracion();
    
    // Métodos de validación
    bool validarDatosPersonales();
    bool validarDireccionEntrega();
    bool validarTipoPedido();
    bool validarHorarioLaboral(const QDateTime& fechaHora);
    bool validarEdadCliente();
    bool validarMetodoPago();
    
    // Métodos de cálculo
    void calcularTotales();
    double calcularDistancia(const QString& direccionDestino);
    double obtenerCostoDeliveryPorDistancia(double distancia);
    
    // Métodos de interfaz
    void mostrarResumenProductos();
    void actualizarTotales();
    void habilitarDeshabilitarConfirmacion();
    void limpiarErrores();
    void mostrarError(QWidget* campo, const QString& mensaje);
    
    // Métodos de base de datos
    bool existeCliente(const QString& telefono, const QString& email);
    int obtenerIdCliente(const QString& telefono, const QString& email);
    int crearCliente(const DatosCliente& cliente);
    int crearPedido();
    bool agregarItemsPedido(int pedidoId);
    bool crearSeguimientoPedido(int pedidoId);
    bool enviarFacturaPorEmail(int pedidoId);
    
    // Métodos de utilidad
    QString generarNumeroPedido();
    QString formatearDireccion(const QString& direccion);
    bool esHorarioLaboral(const QTime& hora);
    void mostrarMensajeError(const QString& mensaje);
    void mostrarMensajeExito(const QString& mensaje);
    void mostrarMensajeAdvertencia(const QString& mensaje);
    
    // Métodos de navegación
    void limpiarFormulario();
    void bloquearFormulario(bool bloqueado);
};

#endif // CONFIRMACIONPEDIDO_H