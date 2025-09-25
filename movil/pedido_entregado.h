#ifndef PEDIDO_ENTREGADO_H
#define PEDIDO_ENTREGADO_H

#include <QFrame>

namespace Ui {
class pedido_entregado;
}

class pedido_entregado : public QFrame
{
    Q_OBJECT

public:
    explicit pedido_entregado(int id, QString direccion, double hora, QString nombre, QWidget *parent);
    void actualizar_etiquetas();
    ~pedido_entregado();

private:
    int id;
    QString direccion;
    double hora;
    QString nombre_cliente;
    Ui::pedido_entregado *ui;
};

#endif // PEDIDO_ENTREGADO_H
