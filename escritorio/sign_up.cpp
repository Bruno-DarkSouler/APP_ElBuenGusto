#include "sign_up.h"
#include "ui_sign_up.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QDate>
#include <QCheckBox>
#include <QPushButton>
#include <QLineEdit>

sign_up::sign_up(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::sign_up)
{
    ui->setupUi(this);

    // Conectar validaciones en tiempo real
    connect(ui->lineEdit_nombre, &QLineEdit::textChanged, this, &sign_up::validateName);
    connect(ui->lineEdit_email, &QLineEdit::textChanged, this, &sign_up::validateEmail);
    connect(ui->lineEdit_telefono, &QLineEdit::textChanged, this, &sign_up::validatePhone);
    connect(ui->lineEdit_fecha, &QLineEdit::textChanged, this, &sign_up::validateDate);
    connect(ui->lineEdit_password, &QLineEdit::textChanged, this, &sign_up::validatePassword);

    // Conectar el botón de iniciar sesión
    connect(ui->pushButton, &QPushButton::clicked, this, &sign_up::on_iniciar_clicked);

    // Configurar placeholder para fecha
    ui->lineEdit_fecha->setPlaceholderText("dd/mm/aaaa");

    // Configurar máscara para teléfono (opcional)
    ui->lineEdit_telefono->setInputMask("99-9999-9999");
}

sign_up::~sign_up()
{
    delete ui;
}

void sign_up::validateName()
{
    QString name = ui->lineEdit_nombre->text().trimmed();

    if (name.isEmpty()) {
        setFieldStyle(ui->lineEdit_nombre, "normal");
        return;
    }

    // Validar que solo contenga letras y espacios
    QRegularExpression nameRegex("^[a-zA-ZÀ-ÿ\\s]+$");
    if (name.length() >= 2 && nameRegex.match(name).hasMatch()) {
        setFieldStyle(ui->lineEdit_nombre, "valid");
    } else {
        setFieldStyle(ui->lineEdit_nombre, "invalid");
    }
}

void sign_up::validateEmail()
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

void sign_up::validatePhone()
{
    QString phone = ui->lineEdit_telefono->text().trimmed();

    if (phone.isEmpty()) {
        setFieldStyle(ui->lineEdit_telefono, "normal");
        return;
    }

    // Remover caracteres no numéricos para validación
    QString cleanPhone = phone;
    cleanPhone.remove(QRegularExpression("[^0-9]"));

    if (cleanPhone.length() >= 10) {
        setFieldStyle(ui->lineEdit_telefono, "valid");
    } else {
        setFieldStyle(ui->lineEdit_telefono, "invalid");
    }
}

void sign_up::validateDate()
{
    QString dateStr = ui->lineEdit_fecha->text().trimmed();

    if (dateStr.isEmpty()) {
        setFieldStyle(ui->lineEdit_fecha, "normal");
        return;
    }

    // Validar formato dd/mm/yyyy
    QRegularExpression dateRegex("^\\d{2}/\\d{2}/\\d{4}$");
    if (!dateRegex.match(dateStr).hasMatch()) {
        setFieldStyle(ui->lineEdit_fecha, "invalid");
        return;
    }

    // Validar que sea una fecha válida
    QDate date = QDate::fromString(dateStr, "dd/MM/yyyy");
    if (date.isValid() && date <= QDate::currentDate()) {
        // Verificar edad mínima (ejemplo: 13 años)
        int age = date.daysTo(QDate::currentDate()) / 365;
        if (age >= 13) {
            setFieldStyle(ui->lineEdit_fecha, "valid");
        } else {
            setFieldStyle(ui->lineEdit_fecha, "invalid");
        }
    } else {
        setFieldStyle(ui->lineEdit_fecha, "invalid");
    }
}

void sign_up::validatePassword()
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

void sign_up::setFieldStyle(QLineEdit* field, const QString& status)
{
    if (status == "valid") {
        field->setStyleSheet("background-color: rgb(255, 255, 255);"
                             "border: 2 solid #4CAF50;"
                             "border-radius: 5px;"
                             "padding: 10;");
    } else if (status == "invalid") {
        field->setStyleSheet("background-color: rgb(255, 255, 255);"
                             "border: 2 solid #F44336;"
                             "border-radius: 5px;"
                             "padding: 10;");
    } else {
        field->setStyleSheet("background-color: rgb(255, 255, 255);"
                             "border: 2 solid rgba(0, 0, 0,0.50);"
                             "border-radius: 5px;"
                             "padding: 10;");
    }
}

bool sign_up::isFormValid()
{
    QString name = ui->lineEdit_nombre->text().trimmed();
    QString email = ui->lineEdit_email->text().trimmed();
    QString phone = ui->lineEdit_telefono->text().trimmed();
    QString dateStr = ui->lineEdit_fecha->text().trimmed();
    QString password = ui->lineEdit_password->text();

    // Validar nombre
    if (name.length() < 2) {
        showError("El nombre debe tener al menos 2 caracteres");
        return false;
    }

    QRegularExpression nameRegex("^[a-zA-ZÀ-ÿ\\s]+$");
    if (!nameRegex.match(name).hasMatch()) {
        showError("El nombre solo debe contener letras");
        return false;
    }

    // Validar email
    QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@gmail\\.com$");
    if (!emailRegex.match(email).hasMatch()) {
        showError("El email debe ser una dirección válida de Gmail (@gmail.com)");
        return false;
    }

    // Validar teléfono
    QString cleanPhone = phone;
    cleanPhone.remove(QRegularExpression("[^0-9]"));
    if (cleanPhone.length() < 10) {
        showError("El teléfono debe tener al menos 10 dígitos");
        return false;
    }

    // Validar fecha
    QDate date = QDate::fromString(dateStr, "dd/MM/yyyy");
    if (!date.isValid()) {
        showError("La fecha debe tener el formato dd/mm/aaaa y ser válida");
        return false;
    }

    int age = date.daysTo(QDate::currentDate()) / 365;
    if (age < 13) {
        showError("Debes tener al menos 13 años para registrarte");
        return false;
    }

    // Validar contraseña
    if (password.length() < 8) {
        showError("La contraseña debe tener al menos 8 caracteres");
        return false;
    }

    // Verificar términos y condiciones
    if (!ui->checkBox->isChecked()) {
        showError("Debes aceptar los términos y condiciones");
        return false;
    }

    return true;
}

void sign_up::showError(const QString& message)
{
    QMessageBox::warning(this, "Error de validación", message);
}

void sign_up::on_iniciar_clicked()
{
    if (isFormValid()) {
        // Mostrar mensaje de éxito
        QMessageBox::information(this, "Registro exitoso",
                                 "¡Registro completado correctamente!\nRedirigiendo...");

        emit registrationSuccessful();

        // O cerrar esta ventana y abrir otra
        this->close();

        // Si tienes otra ventana para abrir:
        // MainWindow *mainWindow = new MainWindow();
        // mainWindow->show();
    }
}
