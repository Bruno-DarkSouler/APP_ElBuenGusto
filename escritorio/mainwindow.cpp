#include "mainwindow.h"
#include "tarjeta_comida_principal.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::colocar_layouts(){
    QVBoxLayout *contenedor_v = new QVBoxLayout;
    ui->scrollAreaWidgetContents->setLayout(contenedor_v);
    std::vector<QString> productos = {"Camisa", "Pantalón", "Zapatos"};

    for (const auto &nombre : productos) {
        qInfo("HELLO WORLD");
        tarjeta_comida_principal *tarjeta = new tarjeta_comida_principal(this);
        tarjeta->setData(nombre);
        contenedor_v->addWidget(tarjeta);
    }
}

void MainWindow::conseguir_comida(){


}
