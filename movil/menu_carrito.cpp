#include "menu_carrito.h"
#include "ui_menu_carrito.h"

menu_carrito::menu_carrito(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::menu_carrito)
{
    ui->setupUi(this);
}

menu_carrito::~menu_carrito()
{
    delete ui;
}
