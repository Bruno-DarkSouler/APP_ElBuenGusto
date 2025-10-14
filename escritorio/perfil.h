#ifndef PERFIL_H
#define PERFIL_H

#include <QWidget>

namespace Ui {
class perfil;
}

class perfil : public QWidget
{
    Q_OBJECT

public:
    explicit perfil(QWidget *parent = nullptr);
    ~perfil();

private slots:
    void on_logout_clicked();
    void on_cargar_foto_clicked();
    void loadUserData();  // Añade esta línea

private:
    Ui::perfil *ui;
};

#endif // PERFIL_H
