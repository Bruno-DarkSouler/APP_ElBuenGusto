#include "condimento.h"
#include "ui_condimento.h"
#include "tarjeta_especialidades.h"
#include <qlabel.h>

condimento::condimento(double precio, QString nombre, tarjeta_especialidades *tarjeta, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::condimento)
{
    ui->setupUi(this);

    this->precio = precio;
    this->nombre = nombre;

    ui->checkBox->setText(this->nombre);

    connect(ui->checkBox, &QCheckBox::checkStateChanged, this, [=]()mutable{
        if(ui->checkBox->isChecked()){
            tarjeta->sumar_precio(precio);
        }else{
            tarjeta->restar_precio(precio);
        }
        tarjeta->actualizar_precio();
    });
}

condimento::~condimento()
{
    delete ui;
}

void condimento::sumar_precio(double &tarjeta_precio, QLabel etiqueta_precio){
    tarjeta_precio += this->precio;
    etiqueta_precio.setText(QString::number(tarjeta_precio));
}

void condimento::restar_precio(double &tarjeta_precio, QLabel etiqueta_precio){
    tarjeta_precio -= this->precio;
    etiqueta_precio.setText(QString::number(tarjeta_precio));
}
