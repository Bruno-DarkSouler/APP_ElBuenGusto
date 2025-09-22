#ifndef REPARTIDOR_H
#define REPARTIDOR_H

#include <QWidget>

namespace Ui {
class repartidor;
}

class repartidor : public QWidget
{
    Q_OBJECT

public:
    explicit repartidor(QWidget *parent = nullptr);
    ~repartidor();
    void instancia_tarjetas();

private:
    Ui::repartidor *ui;
};

#endif // REPARTIDOR_H
