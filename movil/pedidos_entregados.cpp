#include "pedidos_entregados.h"
#include "ui_pedidos_entregados.h"

pedidos_entregados::pedidos_entregados(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::pedidos_entregados)
{
    ui->setupUi(this);
}

pedidos_entregados::~pedidos_entregados()
{
    delete ui;
}
