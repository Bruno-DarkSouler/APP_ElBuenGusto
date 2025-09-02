#include "tarjeta_especialidades.h"
#include "ui_tarjeta_especialidades.h"

tarjeta_especialidades::tarjeta_especialidades(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::tarjeta_especialidades)
{
    ui->setupUi(this);
}

tarjeta_especialidades::~tarjeta_especialidades()
{
    delete ui;
}

void tarjeta_especialidades::setData(const QString data){
    ui->label_2->setText(data);
}
