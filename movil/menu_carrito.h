#ifndef MENU_CARRITO_H
#define MENU_CARRITO_H

#include "ui_menu_carrito.h"
#include <QWidget>
#include <qpushbutton.h>

namespace Ui {
class menu_carrito;
}

class menu_carrito : public QWidget
{
    Q_OBJECT

public:
    explicit menu_carrito(QWidget *parent = nullptr);
    ~menu_carrito();
    QPushButton *devolver_boton_cerrar() const {return ui->pushButton;};

private:
    Ui::menu_carrito *ui;
};

#endif // MENU_CARRITO_H
