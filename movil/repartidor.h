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

private:
    Ui::repartidor *ui;
};

#endif // REPARTIDOR_H
