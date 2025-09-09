#ifndef SIGN_UP_H
#define SIGN_UP_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>

QT_BEGIN_NAMESPACE
namespace Ui { class sign_up; }
QT_END_NAMESPACE

class sign_up : public QWidget
{
    Q_OBJECT

public:
    explicit sign_up(QWidget *parent = nullptr);
    ~sign_up();

signals:
    void registrationSuccessful(); // Señal para notificar registro exitoso

private slots:
    void validateName();           // Validar nombre
    void validateEmail();          // Validar email
    void validatePhone();          // Validar teléfono
    void validateDate();           // Validar fecha
    void validatePassword();       // Validar contraseña
    void on_iniciar_clicked();     // Manejar clic en "Iniciar Sesión"

private:
    Ui::sign_up *ui;

    // Funciones auxiliares
    void setFieldStyle(QLineEdit* field, const QString& status);
    bool isFormValid();
    void showError(const QString& message);
};

#endif // SIGN_UP_H
