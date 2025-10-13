#ifndef CONFIRMACIONPEDIDO_H
#define CONFIRMACIONPEDIDO_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QRadioButton>
#include <QDateEdit>
#include <QTimeEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QScrollArea>
#include <QMessageBox>
#include <QGroupBox>
#include <QTimer>
#include <QDateTime>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QVector>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

QT_BEGIN_NAMESPACE
namespace Ui { class ConfirmacionPedido; }
QT_END_NAMESPACE

struct ProductoConfirmacion {
    int id;
    QString nombre;
    QString descripcion;
    double precio;
    int cantidad;
    double precioTotal;
    QString comentarios;
};

struct DatosCliente {
    QString nombre;
    QString apellido;
    QString telefono;
    QString email;
    QString direccion;
    bool esClienteExistente;
    int clienteId;
};

struct ConfiguracionPedido {
    QString tipoPedido;
    QDateTime fechaEntrega;
    QString metodoPago;
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

    void establecerProductos(const QVector<ProductoConfirmacion>& productos);
    void establecerDatosCliente(const DatosCliente& cliente);

    bool validarDatosPersonales();
    bool validarDireccionEntrega();
    bool validarTipoPedido();
    bool validarPedidoInmediato();
    bool validarPedidoProgramado(const QDateTime& fechaHora);
    int calcularTiempoPreparacionTotal();  // AGREGAR ESTA LÍNEA

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
    void procesarRespuestaConfirmacion(QNetworkReply *reply);

private:
    Ui::ConfirmacionPedido *ui;

    QVector<ProductoConfirmacion> productosCarrito;
    DatosCliente datosCliente;
    ConfiguracionPedido configuracionPedido;

    QTime horaApertura1;
    QTime horaCierre1;
    QTime horaApertura2;
    QTime horaCierre2;
    QString direccionSucursal;

    QRegularExpressionValidator* validadorTelefono;
    QRegularExpressionValidator* validadorEmail;

    QNetworkAccessManager* networkManager;
    QString apiUrl;

    void configurarInterfaz();
    void configurarValidadores();
    void configurarEventos();
    void cargarConfiguracion();

    bool validarHorarioLaboral(const QDateTime& fechaHora);
    bool validarMetodoPago();
    bool esHorarioLaboral(const QTime& hora);

    void calcularTotales();
    double calcularDistancia(const QString& direccionDestino);
    double obtenerCostoDeliveryPorDistancia(double distancia);

    void mostrarResumenProductos();
    void actualizarTotales();
    void limpiarFormulario();
    void bloquearFormulario(bool bloqueado);

    void mostrarMensajeError(const QString& mensaje);
    void mostrarMensajeExito(const QString& mensaje);
    void mostrarMensajeAdvertencia(const QString& mensaje);

    QString generarNumeroPedido();
    QString formatearDireccion(const QString& direccion);
};

#endif // CONFIRMACIONPEDIDO_H
