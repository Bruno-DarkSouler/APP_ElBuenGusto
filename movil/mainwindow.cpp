#include "mainwindow.h"
#include "menu_lateral.h"
#include "tarjeta_especialidades.h"
#include "./ui_mainwindow.h"
#include "QNetworkAccessManager"
#include "QNetworkReply"
#include "QGuiApplication"
#include "QRect"
#include "QScreen"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    contenedor_v = new QVBoxLayout;
    ui->scrollAreaWidgetContents->setLayout(contenedor_v);

    menu_lateral_w = new class menu_lateral(this);
    menu_lateral_w->setGeometry(-this->width(), 0, this->width(), this->height());
    animacion = new QPropertyAnimation(this);
    animacion->setDuration(1000);
    animacion->setTargetObject(menu_lateral_w);
    animacion->setPropertyName("geometry");
    animacion->setEasingCurve(QEasingCurve::OutQuad);

    menu_carrito_w = new class menu_carrito(this);
    menu_carrito_w->setGeometry(-this->width(), 0, this->width(), this->height());
    animacion_menu_carrito = new QPropertyAnimation(this);
    animacion_menu_carrito->setDuration(1000);
    animacion_menu_carrito->setTargetObject(menu_carrito_w);
    animacion_menu_carrito->setPropertyName("geometry");
    animacion_menu_carrito->setEasingCurve(QEasingCurve::OutQuad);


    connect(ui->abrir_menu, &QPushButton::clicked, this, &MainWindow::abrir_menu_lateral);
    connect(menu_lateral_w->devolver_boton_cerrar(), &QPushButton::clicked, this, &MainWindow::abrir_menu_lateral);
    connect(ui->abrir_carrito, &QPushButton::clicked, this, &MainWindow::abrir_menu_carrito);
    connect(menu_carrito_w->devolver_boton_cerrar(), &QPushButton::clicked, this, &MainWindow::abrir_menu_carrito);

    connect(ui->barraBusqueda, &QLineEdit::editingFinished, this, &MainWindow::on_barraBusqueda_textChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mostrar_recomendaciones(){
    QNetworkAccessManager *conexion = new QNetworkAccessManager(this);
    QUrl url("http://localhost/WEB_ElBuenGusto/api/buscar_productos.php?objetivo=pizz");
    QNetworkRequest peticion(url);
    QNetworkReply *respuesta = conexion->get(peticion);
    qInfo("Hola1");
    connect(respuesta, &QNetworkReply::finished, this, [=](){
        if(respuesta->error() == QNetworkReply::NoError){
            QByteArray datos_respuesta = respuesta->readAll();

            QJsonDocument datos_json = QJsonDocument::fromJson(datos_respuesta);
            qInfo("HOLAAAAA");
            qDebug() << datos_respuesta;
            if(!datos_json.isNull()){
                qInfo("HOLA3");
                QJsonArray general = datos_json.array();
                for(const QJsonValue &valor : general){
                    QJsonObject fila = valor.toObject();
                    tarjeta_especialidades *tarjeta_comida = new tarjeta_especialidades(fila["nombre"].toString(), this);
                    contenedor_v->addWidget(tarjeta_comida);
                }
            }
        }
    });
}

void MainWindow::mostrar_resultados_busqueda(QString objetivo){
    QNetworkAccessManager *conexion = new QNetworkAccessManager(this);
    QUrl url("http://localhost/WEB_ElBuenGusto/api/buscar_productos.php?objetivo=" + objetivo);
    QNetworkRequest peticion(url);
    QNetworkReply *respuesta = conexion->get(peticion);
    connect(respuesta, &QNetworkReply::finished, this, [=](){
        if(respuesta->error() == QNetworkReply::NoError){
            QByteArray datos_respuesta = respuesta->readAll();

            QJsonDocument datos_json = QJsonDocument::fromJson(datos_respuesta);
            if(!datos_json.isNull()){
                QJsonArray general = datos_json.array();
                for(const QJsonValue &valor : general){
                    QJsonObject fila = valor.toObject();
                    tarjeta_especialidades *tarjeta_comida = new tarjeta_especialidades(fila["id"].toInt(), fila["nombre"].toString(), fila["imagen"].toString(), fila["condimentos"].toArray(), this);
                    contenedor_v->addWidget(tarjeta_comida);
                }
            }
        }
    });
}

void MainWindow::on_barraBusqueda_textChanged(){
    vaciar_recomendaciones();
    mostrar_resultados_busqueda(ui->barraBusqueda->text());
}

void MainWindow::vaciar_recomendaciones(){
    QLayoutItem *objeto;

    while((objeto = contenedor_v->itemAt(0)) != nullptr){
        if(objeto->widget()){
            delete objeto->widget();
        }
    }
}

void MainWindow::abrir_menu_lateral(){
    menu_abierto = !menu_abierto;
    int ancho_menu = menu_lateral_w->width();
    int comienzoX, finalX;

    if(menu_abierto){
        comienzoX = -ancho_menu;
        finalX = 0;
    }else{
        finalX = -ancho_menu;
        comienzoX = 0;
    }

    menu_lateral_w->show();
    qInfo("Hola Mundo");


    animacion->setStartValue(QRect(comienzoX, 0, menu_lateral_w->width(), menu_lateral_w->height()));
    animacion->setEndValue(QRect(finalX, 0, menu_lateral_w->width(), menu_lateral_w->height()));
    animacion->start();

}

void MainWindow::abrir_menu_carrito(){
    menu_carrito_abierto = !menu_carrito_abierto;
    int ancho_menu = menu_carrito_w->width();
    int comienzoX, finalX;

    if(menu_carrito_abierto){
        comienzoX = -ancho_menu;
        finalX = 0;
    }else{
        finalX = -ancho_menu;
        comienzoX = 0;
    }

    menu_carrito_w->show();
    qInfo("Hola Mundo");


    animacion_menu_carrito->setStartValue(QRect(comienzoX, 0, menu_carrito_w->width(), menu_carrito_w->height()));
    animacion_menu_carrito->setEndValue(QRect(finalX, 0, menu_carrito_w->width(), menu_carrito_w->height()));
    animacion_menu_carrito->start();

}
