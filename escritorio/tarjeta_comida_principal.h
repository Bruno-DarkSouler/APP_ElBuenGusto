#ifndef TARJETA_COMIDA_PRINCIPAL_H
#define TARJETA_COMIDA_PRINCIPAL_H

#include <QWidget>

namespace Ui {
class tarjeta_comida_principal;
}

class tarjeta_comida_principal : public QWidget
{
    Q_OBJECT

public:
    explicit tarjeta_comida_principal(QWidget *parent = nullptr);
    ~tarjeta_comida_principal();
    void setData(QString texto);

private:
    Ui::tarjeta_comida_principal *ui;
};

#endif // TARJETA_COMIDA_PRINCIPAL_H
