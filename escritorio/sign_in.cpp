#include "mainwindow.h"
#include "sign_in.h"
#include "ui_sign_in.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QDate>
#include <QCheckBox>
#include <QPushButton>
#include <QLineEdit>

sign_in::sign_in(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::sign_in)
{
    ui->setupUi(this);
    // Conectar validaciones en tiempo real
    connect(ui->lineEdit_email, &QLineEdit::textChanged, this, &sign_in::validateEmail);
    connect(ui->lineEdit_password, &QLineEdit::textChanged, this, &sign_in::validatePassword);
    // Conectar el botón de iniciar sesión
    connect(ui->pushButton_sign_in, &QPushButton::clicked, this, &sign_in::on_iniciar_clicked);
}

sign_in::~sign_in()
{
    delete ui;
}

void sign_in::validateEmail()
{
    QString email = ui->lineEdit_email->text().trimmed();
    if (email.isEmpty()) {
        setFieldStyle(ui->lineEdit_email, "normal");
        return;
    }
    // Validar formato de email y que termine con @gmail.com
    QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@gmail\\.com$");
    if (emailRegex.match(email).hasMatch()) {
        setFieldStyle(ui->lineEdit_email, "valid");
    } else {
        setFieldStyle(ui->lineEdit_email, "invalid");
    }
}

void sign_in::validatePassword()
{
    QString password = ui->lineEdit_password->text();
    if (password.isEmpty()) {
        setFieldStyle(ui->lineEdit_password, "normal");
        return;
    }
    // Validar longitud mínima de 8 caracteres
    if (password.length() >= 8) {
        setFieldStyle(ui->lineEdit_password, "valid");
    } else {
        setFieldStyle(ui->lineEdit_password, "invalid");
    }
}

void sign_in::setFieldStyle(QLineEdit* field, const QString& status)
{
    if (status == "valid") {
        field->setStyleSheet("background-color: rgb(255, 255, 255);"
                             "border: 2px solid #4CAF50;"
                             "border-radius: 5px;"
                             "padding: 10px;");
    } else if (status == "invalid") {
        field->setStyleSheet("background-color: rgb(255, 255, 255);"
                             "border: 2px solid #F44336;"
                             "border-radius: 5px;"
                             "padding: 10px;");
    } else {
        field->setStyleSheet("background-color: rgb(255, 255, 255);"
                             "border: 2px solid rgba(0, 0, 0, 0.50);"
                             "border-radius: 5px;"
                             "padding: 10px;");
    }
}

bool sign_in::isFormValid()
{
    QString email = ui->lineEdit_email->text().trimmed();
    QString password = ui->lineEdit_password->text();

    // Validar email
    QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@gmail\\.com$");
    if (!emailRegex.match(email).hasMatch()) {
        showError("El email debe ser una dirección válida de Gmail (@gmail.com)");
        return false;
    }

    // Validar contraseña
    if (password.length() < 8) {
        showError("La contraseña debe tener al menos 8 caracteres");
        return false;
    }

    return true;
}

void sign_in::showError(const QString& message)
{
    QMessageBox::warning(this, "Error de validación", message);
}

void sign_in::on_iniciar_clicked()
{
    if (isFormValid()) {
        // Mostrar mensaje de éxito
        QMessageBox::information(this, "Registro exitoso",
                                 "¡Registro completado correctamente!\nRedirigiendo...");

        emit registrationSuccessful();

        // Crear y mostrar la ventana principal
        MainWindow *mainwindow = new MainWindow();
        mainwindow->show();

        // Cerrar esta ventana
        this->close();
    }
}
