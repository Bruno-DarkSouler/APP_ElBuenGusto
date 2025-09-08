#include "mainwindow.h"
#include "tarjeta_especialidades.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->barraBusqueda, &QLineEdit::textChanged, this, &MainWindow::on_barraBusqueda_textChanged);
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
        tarjeta_especialidades *tarjeta = new tarjeta_especialidades(this);
        tarjeta->setData(nombre);
        contenedor_v->addWidget(tarjeta);
    }
}

void MainWindow::on_barraBusqueda_textChanged(){
    qInfo("HOLAAAAA");
}
