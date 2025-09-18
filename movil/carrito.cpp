#include "carrito.h"
#include "ui_carrito.h"

carrito::carrito(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::carrito)
{
    ui->setupUi(this);
}

carrito::~carrito()
{
    delete ui;
}
