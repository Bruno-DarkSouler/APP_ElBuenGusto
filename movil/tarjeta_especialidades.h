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

public:

    explicit tarjeta_especialidades(int id, double precio, QString nombre, QString imagen, QByteArray condimentos, QWidget *parent = nullptr);
    ~tarjeta_especialidades();
    void actualizar_precio();
    void sumar_precio(double precio_condimento);
    void restar_precio(double precio_condimento);
    int id;
    double precio;
    bool condimentos_abiertos;
    QString nombre;
    QString imagen;
    QJsonDocument condimentos;
    QPropertyAnimation *animacion_condimentos;

/*private slots:
    void alternarCondimentos();*/

private:
    Ui::tarjeta_especialidades *ui;
    void verificarCondimentos();

};

#endif // TARJETA_ESPECIALIDADES_H
