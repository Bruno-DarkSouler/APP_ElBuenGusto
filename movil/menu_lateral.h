#ifndef MENU_LATERAL_H
#define MENU_LATERAL_H

#include "ui_menu_lateral.h"
#include <QWidget>
#include <qpushbutton.h>

namespace Ui {
class menu_lateral;
}

class menu_lateral : public QWidget
{
    Q_OBJECT

public:
    explicit menu_lateral(QWidget *parent = nullptr);
    ~menu_lateral();
    QPushButton *devolver_boton_cerrar() const {return ui->boton_cerrar_menu;};


private:
    Ui::menu_lateral *ui;
};

#endif // MENU_LATERAL_H
