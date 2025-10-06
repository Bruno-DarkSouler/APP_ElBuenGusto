#ifndef TARJETA_ESPECIALIDADES_H
#define TARJETA_ESPECIALIDADES_H

#include <QFrame>

namespace Ui {
class tarjeta_especialidades;
}

class tarjeta_especialidades : public QFrame
{
    Q_OBJECT

private slots:
    void abrirTarjeta(QString id);

public:
    explicit tarjeta_especialidades(QString nombre, QWidget *parent = nullptr);
    ~tarjeta_especialidades();
    void setData(QString texto);
    int id;

private:
    Ui::tarjeta_especialidades *ui;
};

#endif // TARJETA_ESPECIALIDADES_H
