#include "perfil.h"
#include "ui_perfil.h"

perfil::perfil(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::perfil)
{
    ui->setupUi(this);
}

perfil::~perfil()
{
    delete ui;
}
