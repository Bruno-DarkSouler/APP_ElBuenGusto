#include <QJsonArray>
#include <QCheckBox>
#include <QEasingCurve>
#include "tarjeta_especialidades.h"
#include "ui_tarjeta_especialidades.h"

tarjeta_especialidades::tarjeta_especialidades(int id, QString nombre, QString imagen, QJsonArray condimentos, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::tarjeta_especialidades)
{
    ui->setupUi(this);

    if(!condimentos.isEmpty()){

    }

    ui->pushButton->setText(nombre);

    connect(ui->pushButton, &QPushButton::clicked, this, [=]{
        tarjeta_especialidades::abrirTarjeta("HOLA Mundo");
    });
}

tarjeta_especialidades::~tarjeta_especialidades()
{
    delete ui;
}

void tarjeta_especialidades::verificarCondimentos(){
    if(condimentos.isEmpty()){
        ui->frame_condimentos->hide();
    }else{
        for(QJsonValue &valor : condimentos){
            QJsonObject condimento = valor.toObject();
            QCheckBox *caja_condimento = new QCheckBox(this);
            caja_condimento->setText(valor["nombre"]);
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
    int comienzo_
}
