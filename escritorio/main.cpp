#include "confirmacion_pedido.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConfirmacionPedido w;
    w.show();
    return a.exec();
}
