#ifndef TARJETA_ESPECIALIDADES_H
#define TARJETA_ESPECIALIDADES_H

#include <QFrame>
#include <QArrayData>
#include <QPropertyAnimation>
#include <qjsonarray.h>

namespace Ui {
class tarjeta_especialidades;
}

class tarjeta_especialidades : public QFrame
{
    Q_OBJECT

private slots:
    void abrirTarjeta(QString id);

public:
    explicit tarjeta_especialidades(int id, QString nombre, QString imagen, QJsonArray condimentos, QWidget *parent = nullptr);
    ~tarjeta_especialidades();
    void setData(QString texto);
    int id = id;
    bool condimentos_abiertos;
    QString nombre = nombre;
    QString imagen = imagen;
    QJsonArray condimentos = condimentos;
    QPropertyAnimation *animacion_condimentos;

private slots:
    void alternarCondimentos();

private:
    Ui::tarjeta_especialidades *ui;
    void verificarCondimentos();

};

#endif // TARJETA_ESPECIALIDADES_H
