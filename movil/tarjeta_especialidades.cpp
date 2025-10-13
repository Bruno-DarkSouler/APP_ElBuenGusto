#include <QJsonArray>
#include <QCheckBox>
#include <QEasingCurve>
#include <qjsonobject.h>
#include "tarjeta_especialidades.h"
#include "condimento.h"
#include "ui_tarjeta_especialidades.h"

tarjeta_especialidades::tarjeta_especialidades(int id, double precio, QString nombre, QString imagen, QByteArray condimentos, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::tarjeta_especialidades)
{

    ui->setupUi(this);

    this->id = id;
    this->nombre = nombre;
    this->precio = precio;
    this->imagen = imagen;
    this->condimentos = QJsonDocument::fromJson(condimentos);

    if(!this->condimentos.array().isEmpty()){
        for(const QJsonValue &valor : this->condimentos.array()){
            QJsonObject fila = valor.toObject();
            condimento *caja = new condimento(fila["precio"].toDouble(), fila["nombre"].toString(), this, this);
            ui->contenedor_condimentos->addWidget(caja);
        }
    }else{
        ui->frame_condimentos->hide();
    }


    qDebug()<<this->precio;

    actualizar_precio();
}

tarjeta_especialidades::~tarjeta_especialidades()
{
    delete ui;
}

void tarjeta_especialidades::sumar_precio(double precio_condimento){
    this->precio += precio_condimento;
    qDebug()<<this->precio;
}

void tarjeta_especialidades::restar_precio(double precio_condimento){
    this->precio -= precio_condimento;
    qDebug()<<this->precio;
}

void tarjeta_especialidades::actualizar_precio(){
    ui->etiqueta_precio->setText(QString::number(this->precio));
}

/*void tarjeta_especialidades::verificarCondimentos(){
    if(condimentos.isEmpty()){
        ui->frame_condimentos->hide();
    }else{
        for(const QJsonValue &valor : condimentos){
            QJsonObject condimento = valor.toObject();
            QCheckBox *caja_condimento = new QCheckBox(this);
            caja_condimento->setText(condimento["nombre"].toString());
            ui->contenedor_condimentos->addWidget(caja_condimento);
        }
        animacion_condimentos = new QPropertyAnimation(this);
        animacion_condimentos->setDuration(500);
        animacion_condimentos->setTargetObject(ui->contenedor_condimentos);
        animacion_condimentos->setPropertyName("geometry");
        animacion_condimentos->setEasingCurve(QEasingCurve::OutQuad);
    }
}

void tarjeta_especialidades::alternarCondimentos(){
    condimentos_abiertos = !condimentos_abiertos;
    int comienzo_x, final_x;


    if(condimentos_abiertos){
        comienzo_x = 0;
        final_x = 100;
    }else{
        comienzo_x = 100;
        final_x = 0;
    }

    //animacion_condimentos->setStartValue(QRect(ui->contenedor_condimentos->geometry().x(), comienzo_x, ui->contenedor_condimentos->widt));
}*/
