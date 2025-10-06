#include "cajero.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PanelCajero w;
    w.show();
    return a.exec();
}
