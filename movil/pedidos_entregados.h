#ifndef PEDIDOS_ENTREGADOS_H
#define PEDIDOS_ENTREGADOS_H

#include <QFrame>

namespace Ui {
class pedidos_entregados;
}

class pedidos_entregados : public QFrame
{
    Q_OBJECT

public:
    explicit pedidos_entregados(QWidget *parent = nullptr);
    ~pedidos_entregados();

private:
    Ui::pedidos_entregados *ui;
};

#endif // PEDIDOS_ENTREGADOS_H
