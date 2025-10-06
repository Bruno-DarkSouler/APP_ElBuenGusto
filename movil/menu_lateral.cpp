#include "menu_lateral.h"
#include "ui_menu_lateral.h"

menu_lateral::menu_lateral(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::menu_lateral)
{
    ui->setupUi(this);
}

menu_lateral::~menu_lateral()
{
    delete ui;
}
