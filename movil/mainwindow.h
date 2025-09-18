#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include "tarjeta_comida_principal.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void colocar_layouts();

private slots:
    void on_barraBusqueda_textChanged();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
