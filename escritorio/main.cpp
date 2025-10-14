#include "cocina.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    cocina w;
    w.show();
    return a.exec();
}
