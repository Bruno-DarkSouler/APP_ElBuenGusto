#ifndef SIGN_UP_H
#define SIGN_UP_H

#include <QWidget>
#include <QDateEdit>

namespace Ui {
class sign_up;
}

class sign_up : public QWidget
{
    Q_OBJECT

public:
    explicit sign_up(QWidget *parent = nullptr);
    ~sign_up();

private slots:
    void on_iniciar_clicked();
    void on_ir_a_sign_in_clicked();

    void validateName();
    void validateApellido();
    void validateEmail();
    void validatePhone();
    void validateDate();
    void validatePassword();

    void setFieldStyle(QWidget* field, const QString& status);
    void showError(const QString& message);
    bool isFormValid();

private:
    Ui::sign_up *ui;
};

#endif // SIGN_UP_H
