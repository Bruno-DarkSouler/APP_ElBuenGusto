#ifndef CONDIMENTO_H
#define CONDIMENTO_H

#include "tarjeta_especialidades.h"
#include <QFrame>
#include <qlabel.h>

namespace Ui {
class condimento;
}

class condimento : public QFrame
{
    Q_OBJECT

public:
    explicit condimento(double precio, QString nombre, tarjeta_especialidades *tarjeta, QWidget *parent = nullptr);
    ~condimento();
    void sumar_precio(double &tarjeta_precio, QLabel etiqueta_precio);
    void restar_precio(double &tarjeta_precio, QLabel etiqueta_precio);


private:
    Ui::condimento *ui;
    double precio;
    QString nombre;
};

#endif // CONDIMENTO_H
