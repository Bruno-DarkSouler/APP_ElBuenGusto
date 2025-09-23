#include "repartidor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    repartidor w;
    w.show();
    w.instancia_tarjetas();
    return a.exec();
}
