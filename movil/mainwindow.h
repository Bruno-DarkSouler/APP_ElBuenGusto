#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPropertyAnimation>
#include "menu_carrito.h"
#include "menu_lateral.h"
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
    void vaciar_recomendaciones();
    void colocar_layouts();
    void mostrar_recomendaciones();
    void mostrar_resultados_busqueda(QString objetivo);
    QVBoxLayout *contenedor_v;
    menu_lateral *menu_lateral_w;
    bool menu_abierto = false;
    QPropertyAnimation *animacion;

    menu_carrito *menu_carrito_w;
    bool menu_carrito_abierto = false;
    QPropertyAnimation *animacion_menu_carrito;

private slots:
    //void mostrar_resultados_busqueda(QString &objetivo_busqueda);
    void on_barraBusqueda_textChanged();
    void abrir_menu_lateral();
    void abrir_menu_carrito();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
