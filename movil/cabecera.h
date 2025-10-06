#ifndef CABECERA_H
#define CABECERA_H

#include "menu_lateral.h"
#include "menu_carrito.h"
#include <QFrame>
#include <qpropertyanimation.h>

namespace Ui {
class cabecera;
}

class cabecera : public QFrame
{
    Q_OBJECT

public:
    explicit cabecera(int alto_pantalla, int ancho_pantalla, QWidget *parent = nullptr);
    ~cabecera();
    menu_lateral *menu_lateral;
    bool menu_abierto = false;
    QPropertyAnimation *animacion;

    menu_carrito *menu_carrito;
    bool menu_carrito_abierto = false;
    QPropertyAnimation *animacion_menu_carrito;

    int ancho_pantalla = ancho_pantalla;
    int alto_pantalla = alto_pantalla;

private slots:
    void abrir_menu_lateral();
    void abrir_menu_carrito();

private:
    Ui::cabecera *ui;
};

#endif // CABECERA_H
