#include "pedido_en_camino.h"
#include "ui_pedido_en_camino.h"

pedido_en_camino::pedido_en_camino(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::pedido_en_camino)
{
    ui->setupUi(this);
}

pedido_en_camino::~pedido_en_camino()
{
    delete ui;
}
