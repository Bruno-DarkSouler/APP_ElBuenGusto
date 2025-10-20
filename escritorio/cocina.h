#ifndef COCINA_H
#define COCINA_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>
#include <QJsonArray>
#include <QJsonObject>
#include <QVBoxLayout>

namespace Ui {
class cocina;
}

class cocina : public QDialog
{
    Q_OBJECT

public:
    explicit cocina(QWidget *parent = nullptr);
    ~cocina();

private slots:
    void cargarPedidos();
    void confirmarPedido();

private:
    Ui::cocina *ui;
    QNetworkAccessManager *networkManager;
    QTimer timerActualizacion;
    
    // Widgets dinámicos
    QWidget *contenedorActivos;
    QWidget *contenedorConfirmados;
    QVBoxLayout *layoutActivos;
    QVBoxLayout *layoutConfirmados;
    
    // Datos
    QJsonArray repartidoresDisponibles;
    QJsonObject pedidoActual;
    
    // Métodos auxiliares
    void setupScrollAreas();
    void procesarRespuesta(const QByteArray &data);
    QWidget* crearCardPedido(const QJsonObject &pedido, bool esConfirmado);
    QWidget* crearWidgetProducto(const QJsonObject &item);
    void mostrarDetallePedido(const QJsonObject &pedido);
    void cargarComboRepartidores();
    void limpiarLayout(QVBoxLayout *layout);
    
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // COCINA_H