#include "mainwindow.h"
#include "tarjeta_especialidades.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->barraBusqueda, &QLineEdit::editingFinished, this, &MainWindow::on_barraBusqueda_textChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::colocar_layouts(){
    QVBoxLayout *contenedor_v = new QVBoxLayout;
    ui->scrollAreaWidgetContents->setLayout(contenedor_v);
    std::vector<QString> productos = {"Camisa", "Hola", "Zapatos"};

    for (const auto &nombre : productos){
        tarjeta_especialidades *tarjeta = new tarjeta_especialidades(this);
        tarjeta->setData(nombre);
        contenedor_v->addWidget(tarjeta);
    }
}

void MainWindow::on_barraBusqueda_textChanged(){
    QWidget* ventana_contenedor = ui->scrollArea->widget();
    QLayout* colocador = ventana_contenedor->layout();
    for(int i=0; i < colocador->count(); i++){
        if(colocador->itemAt(i)->childAt(1)->text() == "Hola"){
            qInfo('ege');
        }
    }
}
