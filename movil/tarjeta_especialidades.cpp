#include "tarjeta_especialidades.h"
#include "ui_tarjeta_especialidades.h"

tarjeta_especialidades::tarjeta_especialidades(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::tarjeta_especialidades)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, [=]{
        tarjeta_especialidades::abrirTarjeta("HOLA Mundo");
    });
}

tarjeta_especialidades::~tarjeta_especialidades()
{
    delete ui;
}

void tarjeta_especialidades::setData(const QString data){
    ui->pushButton->setText(data);
    this->id = 1;
}

void tarjeta_especialidades::abrirTarjeta(QString id){
    qInfo("id");
}
