#include "cabecera.h"
#include "ui_cabecera.h"

cabecera::cabecera(int alto_pantalla, int ancho_pantalla, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::cabecera)
{
    ui->setupUi(this);

    menu_lateral = new class menu_lateral(this);
    menu_lateral->setGeometry(-ancho_pantalla, 0, ancho_pantalla, alto_pantalla);
    animacion = new QPropertyAnimation(this);
    animacion->setDuration(1000);
    animacion->setTargetObject(menu_lateral);
    animacion->setPropertyName("geometry");
    animacion->setEasingCurve(QEasingCurve::OutQuad);

    menu_carrito = new class menu_carrito(this);
    menu_carrito->setGeometry(-ancho_pantalla, 0, ancho_pantalla, alto_pantalla);
    animacion_menu_carrito = new QPropertyAnimation(this);
    animacion_menu_carrito->setDuration(1000);
    animacion_menu_carrito->setTargetObject(menu_carrito);
    animacion_menu_carrito->setPropertyName("geometry");
    animacion_menu_carrito->setEasingCurve(QEasingCurve::OutQuad);


    connect(ui->abrir_menu, &QPushButton::clicked, this, &cabecera::abrir_menu_lateral);
    connect(menu_lateral->devolver_boton_cerrar(), &QPushButton::clicked, this, &cabecera::abrir_menu_lateral);
    connect(ui->abrir_carrito, &QPushButton::clicked, this, &cabecera::abrir_menu_carrito);
    connect(menu_carrito->devolver_boton_cerrar(), &QPushButton::clicked, this, &cabecera::abrir_menu_carrito);
}

cabecera::~cabecera()
{
    delete ui;
}

