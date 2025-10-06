#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QScrollArea>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

struct ProductoMain {
    int id;
    QString nombre;
    QString descripcion;
    double precio;
    QString imagen;
    int categoriaId;
    bool disponible;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void colocar_layouts();
    void cargarProductosDesdeAPI();

private slots:
    void on_barraBusqueda_textChanged();
    void procesarRespuestaProductos(QNetworkReply *reply);
    void filtrarProductos(const QString& texto);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *networkManager;
    QString apiUrl;
    QVector<ProductoMain> productos;
    
    void mostrarProductos();
    void crearTarjetaProducto(const ProductoMain& producto);
};
#endif // MAINWINDOW_H