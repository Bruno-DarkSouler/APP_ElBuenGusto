#ifndef SIGN_IN_H
#define SIGN_IN_H

#include <QWidget>
#include <QLineEdit> // Necesario para QLineEdit

namespace Ui {
class sign_in;
}

class sign_in : public QWidget
{
    Q_OBJECT

public:
    explicit sign_in(QWidget *parent = nullptr);
    ~sign_in();

signals:
    // Señal para notificar a otras partes de la aplicación cuando el inicio de sesión es exitoso
    void registrationSuccessful();

private slots:
    // Slots de validación que ya tenías
    void validateEmail();
    void validatePassword();

    // Slot principal de click del botón, ahora maneja la conexión con la API
    void on_ir_a_sign_up_clicked(); // <--- ¡AÑADE ESTA LÍNEA!
    void on_iniciar_clicked();

private:
    Ui::sign_in *ui;

    // Métodos de ayuda
    void setFieldStyle(QLineEdit* field, const QString& status);
    bool isFormValid();
    void showError(const QString& message);
};

#endif