#ifndef PEDIDO_PENDIENTE_H
#define PEDIDO_PENDIENTE_H

#include <QFrame>

namespace Ui {
class pedido_pendiente;
}

class pedido_pendiente : public QFrame
{
    Q_OBJECT

public:
    //explicit pedido_pendiente(QWidget *parent = nullptr);
    ~pedido_pendiente();
    explicit pedido_pendiente(int id, QString direccion, QString telefono, double distancia, double precio, double tiempo, QString nombre, QWidget *parent);
    void actualizar_etiquetas();

private slots:
    void marcar_aceptado();

private:
    int id;
    QString direccion;
    QString telefono;
    double distancia;
    double tiempo;
    double precio;
    QString nombre_cliente;
    Ui::pedido_pendiente *ui;
};

#endif // PEDIDO_PENDIENTE_H
