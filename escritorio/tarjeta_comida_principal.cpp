#include "tarjeta_comida_principal.h"
#include "ui_tarjeta_comida_principal.h"

tarjeta_comida_principal::tarjeta_comida_principal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::tarjeta_comida_principal)
{
    ui->setupUi(this);
}

tarjeta_comida_principal::~tarjeta_comida_principal()
{
    delete ui;
}

void tarjeta_comida_principal::setData(const QString data){
    ui->label_2->setText(data);
}
