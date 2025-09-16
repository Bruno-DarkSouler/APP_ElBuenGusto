#ifndef SIGN_IN_H
#define SIGN_IN_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui { class sign_in; }
QT_END_NAMESPACE

class sign_in : public QWidget
{
    Q_OBJECT

public:
    sign_in(QWidget *parent = nullptr);
    ~sign_in();

signals:
    void registrationSuccessful();

private slots:
    void validateEmail();
    void validatePassword();
    void on_iniciar_clicked();

private:
    Ui::sign_in *ui;
    void setFieldStyle(QLineEdit* field, const QString& status);
    bool isFormValid();
    void showError(const QString& message);
};

#endif // SIGN_IN_H
