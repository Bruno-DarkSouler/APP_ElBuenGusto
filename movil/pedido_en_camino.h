#ifndef PEDIDO_EN_CAMINO_H
#define PEDIDO_EN_CAMINO_H

#include <QFrame>

namespace Ui {
class pedido_en_camino;
}

class pedido_en_camino : public QFrame
{
    Q_OBJECT

public:
    explicit pedido_en_camino(int id, QString direccion, QString telefono, double precio, QString nombre, QWidget *parent);
    void actualizar_etiquetas();
    ~pedido_en_camino();

private:
    int id;
    QString direccion;
    QString telefono;
    double precio;
    QString nombre_cliente;
    Ui::pedido_en_camino *ui;
};

#endif // PEDIDO_EN_CAMINO_H
