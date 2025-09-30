#ifndef SIGN_UP_H
#define SIGN_UP_H

#include <QWidget>
#include <QLineEdit>

namespace Ui {
class sign_up;
}

class sign_up : public QWidget
{
    Q_OBJECT

public:
    explicit sign_up(QWidget *parent = nullptr);
    ~sign_up();

signals:
    void registrationSuccessful(); // Señal para informar éxito

private slots:
    // Slots de validación que ya tenías
    void validateName();
    // -----------------------------------------------------------------
    // CORRECCIÓN: Se añade la declaración de validateApellido()
    // -----------------------------------------------------------------
    void validateApellido(); // <-- ¡AÑADIDA! Esto resuelve el error de compilación
    // -----------------------------------------------------------------
    void validateEmail();
    void validatePhone();
    void validateDate();
    void validatePassword();

    void on_ir_a_sign_in_clicked(); // <--- ¡AÑADE ESTA LÍNEA!
    void on_iniciar_clicked();

private:
    Ui::sign_up *ui;

    // Métodos de ayuda
    void setFieldStyle(QLineEdit* field, const QString& status);
    bool isFormValid();
    void showError(const QString& message);
};

#endif // SIGN_UP_H
