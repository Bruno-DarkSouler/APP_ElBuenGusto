#include "repartidor.h"
#include "ui_repartidor.h"
#include "pedido_pendiente.h"
#include "QNetworkAccessManager"
#include "QNetworkReply"
#include "QJsonDocument"
#include "QJsonObject"

repartidor::repartidor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::repartidor)
{
    ui->setupUi(this);
    /*connect(reply, &QNetworkReply::finished, this, [=](){
        if(reply->error() == QNetworkReply::NoError)
            });*/
}

repartidor::~repartidor()
{
    delete ui;
}

void repartidor::instancia_tarjetas(){
    QNetworkAccessManager *conexion = new QNetworkAccessManager(this);

    QUrl url("http://localhost/WEB_ElBuenGusto/api/pedidos.php");
    QNetworkRequest request(url);

    QNetworkReply *reply = conexion->get(request);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response_data = reply->readAll();
            qDebug() << "Respuesta:" << response_data;

            // Parsear el JSON
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response_data);
            if (!jsonDoc.isNull()) {
                QJsonObject obj = jsonDoc.object();
                qDebug() << "JSON recibido:" << obj;
            }
        } else {
            qDebug() << "Error en la petición:" << reply->errorString();
        }
        reply->deleteLater();
    });

}
