#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.mostrar_recomendaciones();
    w.show();
    return a.exec();
}
