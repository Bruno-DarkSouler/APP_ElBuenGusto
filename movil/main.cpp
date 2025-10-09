#include "repartidor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    repartidor w;
    w.mostrar_recomendaciones();
    w.show();
    return a.exec();
}
