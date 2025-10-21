#include "cocina.h"
#include "ui_cocina.h"

cocina::cocina(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cocina)
{
    ui->setupUi(this);
}

cocina::~cocina()
{
    delete ui;
}
