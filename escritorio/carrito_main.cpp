#include "carrito.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    carrito w;
    w.show();
    return a.exec();
}