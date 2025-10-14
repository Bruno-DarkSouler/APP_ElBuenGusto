#include "cocina.h"
#include "ui_cocina.h"

cocina::cocina(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cocina)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

}

cocina::~cocina()
{
    delete ui;
}
