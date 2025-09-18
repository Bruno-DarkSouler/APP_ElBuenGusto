#include "repartidor.h"
#include "ui_repartidor.h"

repartidor::repartidor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::repartidor)
{
    ui->setupUi(this);
}

repartidor::~repartidor()
{
    delete ui;
}
