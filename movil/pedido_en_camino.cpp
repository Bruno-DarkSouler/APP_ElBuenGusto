#include "pedido_en_camino.h"
#include "ui_pedido_en_camino.h"

pedido_en_camino::pedido_en_camino(int id, QString direccion, QString telefono, double precio, QString nombre, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::pedido_en_camino)
{
    ui->setupUi(this);
    this->id = id;
    this->precio = precio;
    this->telefono = telefono;
    this->direccion = direccion;
    this->nombre_cliente = nombre;
}

pedido_en_camino::~pedido_en_camino()
{
    delete ui;
}

void pedido_en_camino::actualizar_etiquetas(){
    ui->ui_id_pedido->setText("Pedido N" + QString::number(this->id));
    ui->ui_direccion->setText(this->direccion);
    ui->ui_tele->setText(this->telefono);
    ui->ui_precio->setText(QString::number(this->precio));
    ui->ui_nombre->setText(this->nombre_cliente);
}
