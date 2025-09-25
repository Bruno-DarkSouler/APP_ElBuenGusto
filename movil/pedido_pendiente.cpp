#include "pedido_pendiente.h"
#include "ui_pedido_pendiente.h"

pedido_pendiente::pedido_pendiente(int id, QString direccion, QString telefono, double distancia, double precio, double tiempo, QString nombre, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::pedido_pendiente)
{
    ui->setupUi(this);
    this->id = id;
    this->tiempo = tiempo;
    this->precio = precio;
    this->telefono = telefono;
    this->direccion = direccion;
    this->distancia = distancia;
    this->nombre_cliente = nombre;
}

pedido_pendiente::~pedido_pendiente()
{
    delete ui;
}

void pedido_pendiente::actualizar_etiquetas(){
    ui->ui_id_pedido->setText("Pedido N" + QString::number(this->id));
    ui->ui_direccion->setText(this->direccion);
    ui->ui_tiempo->setText(QString::number(this->tiempo));
    ui->ui_tele->setText(this->telefono);
    ui->ui_precio->setText(QString::number(this->precio));
    ui->ui_nombre->setText(this->nombre_cliente);
    ui->ui_distancia->setText(QString::number(this->distancia));
}
