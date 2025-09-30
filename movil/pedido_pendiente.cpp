#include "pedido_pendiente.h"
#include "ui_pedido_pendiente.h"
#include "QNetworkAccessManager"
#include "QNetworkReply"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"

pedido_pendiente::pedido_pendiente(int id, QString direccion, QString telefono, double distancia, double precio, double tiempo, QString nombre, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::pedido_pendiente)
{
    ui->setupUi(this);
    this->id = id;
    this->tiempo = tiempo;
    this->precio = precio;
    this->telefono = telefono;
    this->direccion = direccion;
    this->distancia = distancia;
    this->nombre_cliente = nombre;

    connect(ui->boton_marcar, &QPushButton::clicked, this, &pedido_pendiente::marcar_aceptado);
}

pedido_pendiente::~pedido_pendiente()
{
    delete ui;
}

void pedido_pendiente::actualizar_etiquetas(){
    ui->ui_id_pedido->setText("Pedido N" + QString::number(this->id));
    ui->ui_direccion->setText(this->direccion);
    ui->ui_tiempo->setText(QString::number(this->tiempo));
    ui->ui_tele->setText(this->telefono);
    ui->ui_precio->setText(QString::number(this->precio));
    ui->ui_nombre->setText(this->nombre_cliente);
    ui->ui_distancia->setText(QString::number(this->distancia));
}

void pedido_pendiente::marcar_aceptado(){
    QNetworkAccessManager *conexion = new QNetworkAccessManager(this);

    QUrl url("http://localhost/WEB_ElBuenGusto/api/entregar_pedido.php/endpoint-post");
    QNetworkRequest request(url);

    QJsonObject datos_envio;
    datos_envio["id_pedido"] = "LOL";
    QJsonDocument datos_envio_json(datos_envio);
    QByteArray array_envio = datos_envio_json.toJson();

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QNetworkReply *respuesta = conexion->post(request, array_envio);
    qInfo("HOLA MUNDO");
    connect(respuesta, &QNetworkReply::finished, this, [=]{
        if(respuesta->error() == QNetworkReply::NoError){
            QByteArray datos = respuesta->readAll();
            qDebug() << datos;
            //QJsonDocument json_doc = QJsonDocument::fromJson(datos);
        }
    });
}
