#include "repartidor.h"
#include "ui_repartidor.h"
#include "pedido_pendiente.h"
#include "QNetworkAccessManager"
#include "QNetworkReply"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"

repartidor::repartidor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::repartidor)
{
    ui->setupUi(this);
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
                QJsonArray parseado = jsonDoc.array();
                qDebug() << "JSON recibido:" << obj;
                for(const QJsonValue &valor : parseado){
                    QJsonObject fila = valor.toObject();
                    pedido_pendiente *tarjeta_pedido_pendiente = new pedido_pendiente(fila["id"], fila["direccion"], fila["telefono"], fila["distancia"], fila["precio"], fila["tiempo"], fila["nombre"], this);

                }
            }
        } else {
            qDebug() << "Error en la petición:" << reply->errorString();
        }
        reply->deleteLater();
    });

}
