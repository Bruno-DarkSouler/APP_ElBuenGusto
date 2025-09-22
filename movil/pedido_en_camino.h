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
    explicit pedido_en_camino(QWidget *parent = nullptr);
    ~pedido_en_camino();

private:
    Ui::pedido_en_camino *ui;
};

#endif // PEDIDO_EN_CAMINO_H
