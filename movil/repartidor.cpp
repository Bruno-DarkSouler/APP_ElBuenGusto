#include "repartidor.h"
#include "ui_repartidor.h"
#include "pedido_pendiente.h"
#include "pedido_en_camino.h"
#include "pedido_entregado.h"
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
            QLayout *colocador_pedidos_pendientes = new QVBoxLayout;
            QLayout *colocador_pedidos_en_camino = new QVBoxLayout;
            QLayout *colocador_pedidos_entregados = new QVBoxLayout;
            ui->ventana_pedidos_pendientes->setLayout(colocador_pedidos_pendientes);
            ui->ventana_pedidos_en_camino->setLayout(colocador_pedidos_en_camino);
            ui->ventana_pedidos_entregados->setLayout(colocador_pedidos_entregados);

            QByteArray response_data = reply->readAll();
            qDebug() << "Respuesta:" << response_data;

            // Parsear el JSON
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response_data);
            if (!jsonDoc.isNull()){
                QJsonObject general = jsonDoc.object();
                QJsonArray pendientes_parseado = general["pendientes"].toArray();
                QJsonArray en_camino_parseado = general["pendientes"].toArray();
                QJsonArray entregados_parseado = general["pendientes"].toArray();
                for(const QJsonValue &valor : pendientes_parseado){
                    QJsonObject fila = valor.toObject();
                    pedido_pendiente *tarjeta_pedido_pendiente = new pedido_pendiente(fila["id"].toInt(), fila["direccion"].toString(), fila["telefono"].toString(), fila["distancia"].toDouble(), fila["precio"].toDouble(), fila["tiempo"].toInt(), fila["nombre"].toString(), this);
                    tarjeta_pedido_pendiente->actualizar_etiquetas();
                    colocador_pedidos_pendientes->addWidget(tarjeta_pedido_pendiente);
                }
                for(const QJsonValue &valor : en_camino_parseado){
                    QJsonObject fila = valor.toObject();
                    pedido_en_camino *tarjeta_pedido_en_camino = new pedido_en_camino(fila["id"].toInt(), fila["direccion"].toString(), fila["telefono"].toString(), fila["precio"].toDouble(), fila["nombre"].toString(), this);
                    tarjeta_pedido_en_camino->actualizar_etiquetas();
                    colocador_pedidos_en_camino->addWidget(tarjeta_pedido_en_camino);
                }
                for(const QJsonValue &valor : entregados_parseado){
                    QJsonObject fila = valor.toObject();
                    pedido_entregado *tarjeta_pedido_entregado = new pedido_entregado(fila["id"].toInt(), fila["direccion"].toString(), fila["hora"].toInt(), fila["nombre"].toString(), this);
                    tarjeta_pedido_entregado->actualizar_etiquetas();
                    colocador_pedidos_entregados->addWidget(tarjeta_pedido_entregado);
                }
            }
        } else {
            qDebug() << "Error en la petición:" << reply->errorString();
        }
        reply->deleteLater();
    });

}
