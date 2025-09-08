#include "sign_in.h"
#include "ui_sign_in.h"

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::sign_in)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}






































































































