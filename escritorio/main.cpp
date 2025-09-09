#include "sign_up.h".h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    sign_up w;
    w.show();
    return a.exec();
}
