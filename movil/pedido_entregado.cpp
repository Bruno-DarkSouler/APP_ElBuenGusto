#include "pedido_entregado.h"
#include "ui_pedido_entregado.h"

pedido_entregado::pedido_entregado(int id, QString direccion, double hora, QString nombre, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::pedido_entregado)
{
    ui->setupUi(this);
    this->id = id;
    this->hora = hora;
    this->direccion = direccion;
    this->nombre_cliente = nombre;
}

pedido_entregado::~pedido_entregado()
{
    delete ui;
}

void pedido_entregado::actualizar_etiquetas(){
    ui->ui_id_pedido->setText("Pedido N" + QString::number(this->id));
    ui->ui_hora->setText(QString::number(this->hora));
    ui->ui_nombre->setText(this->nombre_cliente);
    ui->ui_hora->setText(this->direccion);
}
