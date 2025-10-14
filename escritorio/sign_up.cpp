#include "sign_in.h"
#include "sign_up.h"
#include "ui_sign_up.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QDate>
#include <QCheckBox>
#include <QPushButton>
#include <QLineEdit>
#include <QDateEdit>  // Añadir esta línea

// Librerías de Red y JSON
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>  // Añadir esta línea para depuración

sign_up::sign_up(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::sign_up)
{
    ui->setupUi(this);

    // Conexiones de validación para todos los campos
    connect(ui->lineEdit_nombre, &QLineEdit::textChanged, this, &sign_up::validateName);
    connect(ui->lineEdit_apellido, &QLineEdit::textChanged, this, &sign_up::validateApellido);
    connect(ui->lineEdit_email, &QLineEdit::textChanged, this, &sign_up::validateEmail);
    connect(ui->lineEdit_telefono, &QLineEdit::textChanged, this, &sign_up::validatePhone);
    connect(ui->dateEdit_fecha_nacimiento, &QDateEdit::dateChanged, this, &sign_up::validateDate);
    connect(ui->lineEdit_password, &QLineEdit::textChanged, this, &sign_up::validatePassword);

    // Conexión del botón de registro
    connect(ui->pushButton, &QPushButton::clicked, this, &sign_up::on_iniciar_clicked);

    // ----------------------------------------------------------------------
    // CAMBIO 1: CONEXIÓN DEL BOTÓN DE NAVEGACIÓN A INICIAR SESIÓN
    // ----------------------------------------------------------------------
    // Asumiendo que el botón para ir a Sign In se llama pushButton_sign_in en sign_up.ui
    connect(ui->pushButton_sign_in, &QPushButton::clicked, this, &sign_up::on_ir_a_sign_in_clicked);

    // Máscaras y Placeholders
    ui->lineEdit_telefono->setInputMask("99-9999-9999");
}

sign_up::~sign_up()
{
    delete ui;
}

// ----------------------------------------------------
// Métodos de Validación
// ----------------------------------------------------
void sign_up::validateName() {
    QString nombre = ui->lineEdit_nombre->text().trimmed();
    if (nombre.isEmpty()) {
        setFieldStyle(ui->lineEdit_nombre, "invalid");
    } else {
        setFieldStyle(ui->lineEdit_nombre, "valid");
    }
}

void sign_up::validateApellido() {
    QString apellido = ui->lineEdit_apellido->text().trimmed();
    if (apellido.isEmpty()) {
        setFieldStyle(ui->lineEdit_apellido, "invalid");
    } else {
        setFieldStyle(ui->lineEdit_apellido, "valid");
    }
}

void sign_up::validateEmail() {
    QString email = ui->lineEdit_email->text().trimmed();
    QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@gmail\\.com$");
    if (email.isEmpty() || !emailRegex.match(email).hasMatch()) {
        setFieldStyle(ui->lineEdit_email, "invalid");
    } else {
        setFieldStyle(ui->lineEdit_email, "valid");
    }
}

void sign_up::validatePhone() {
    QString telefono = ui->lineEdit_telefono->text().trimmed();
    QRegularExpression phoneRegex("^\\d{2}-\\d{4}-\\d{4}$");
    if (telefono.isEmpty() || !phoneRegex.match(telefono).hasMatch()) {
        setFieldStyle(ui->lineEdit_telefono, "invalid");
    } else {
        setFieldStyle(ui->lineEdit_telefono, "valid");
    }
}

void sign_up::validateDate() {
    QDate fecha_nacimiento = ui->dateEdit_fecha_nacimiento->date();
    if (fecha_nacimiento.isNull()) {
        setFieldStyle(ui->dateEdit_fecha_nacimiento, "invalid");
    } else {
        setFieldStyle(ui->dateEdit_fecha_nacimiento, "valid");
    }
}

void sign_up::validatePassword() {
    QString password = ui->lineEdit_password->text();
    if (password.length() < 8) {
        setFieldStyle(ui->lineEdit_password, "invalid");
    } else {
        setFieldStyle(ui->lineEdit_password, "valid");
    }
}

void sign_up::setFieldStyle(QWidget* field, const QString& status) {
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

void sign_up::showError(const QString& message) {
    QMessageBox::warning(this, "Error de validación", message);
}

bool sign_up::isFormValid() {
    QString nombre = ui->lineEdit_nombre->text().trimmed();
    QString apellido = ui->lineEdit_apellido->text().trimmed();
    QString email = ui->lineEdit_email->text().trimmed();
    QString telefono = ui->lineEdit_telefono->text().trimmed();
    QDate fecha_nacimiento = ui->dateEdit_fecha_nacimiento->date();
    QString password = ui->lineEdit_password->text();

    if (nombre.isEmpty()) {
        showError("El nombre no puede estar vacío.");
        return false;
    }

    if (apellido.isEmpty()) {
        showError("El apellido no puede estar vacío.");
        return false;
    }

    QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@gmail\\.com$");
    if (!emailRegex.match(email).hasMatch()) {
        showError("El email debe ser una dirección válida de Gmail (@gmail.com).");
        return false;
    }

    QRegularExpression phoneRegex("^\\d{2}-\\d{4}-\\d{4}$");
    if (!phoneRegex.match(telefono).hasMatch()) {
        showError("El teléfono debe tener el formato 99-9999-9999.");
        return false;
    }

    if (fecha_nacimiento.isNull()) {
        showError("La fecha de nacimiento no puede estar vacía.");
        return false;
    }

    if (password.length() < 8) {
        showError("La contraseña debe tener al menos 8 caracteres.");
        return false;
    }

    return true;
}

// ----------------------------------------------------
// Lógica de Registro (Envío a la API)
// ----------------------------------------------------
void sign_up::on_iniciar_clicked()
{
    if (!isFormValid()) {
        return;
    }

    // 1. Preparar datos y UI
    ui->pushButton->setEnabled(false); // Deshabilitar el botón

    // Extracción de todos los datos necesarios para la BD
    QString nombre = ui->lineEdit_nombre->text().trimmed();
    QString apellido = ui->lineEdit_apellido->text().trimmed();
    QString email = ui->lineEdit_email->text().trimmed();
    QString password = ui->lineEdit_password->text();
    QString telefono = ui->lineEdit_telefono->text().trimmed();
    QDate fecha_nacimiento = ui->dateEdit_fecha_nacimiento->date();
    QString fecha_nacimiento_str = fecha_nacimiento.toString("yyyy-MM-dd"); // Formatear la fecha en formato SQL

    // 2. Construir el JSON para el servidor
    QJsonObject jsonPayload;
    jsonPayload["nombre"] = nombre;
    jsonPayload["apellido"] = apellido;
    jsonPayload["telefono"] = telefono;
    jsonPayload["username"] = email;
    jsonPayload["password"] = password;
    jsonPayload["fecha_nacimiento"] = fecha_nacimiento_str;

    QJsonDocument doc(jsonPayload);
    QByteArray postData = doc.toJson(QJsonDocument::Compact);

    // 3. Configurar y enviar la solicitud POST
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QUrl url("http://localhost/WEB_ElBuenGusto/api/sign_up.php");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, postData);

    // 4. Manejar la respuesta del servidor (ASÍNCRONO)
    connect(reply, &QNetworkReply::finished, this, [=]() {

        ui->pushButton->setEnabled(true); // Habilitar botón

        if (reply->error() == QNetworkReply::NoError) {

            QByteArray response_data = reply->readAll();
            qDebug() << "Respuesta del servidor:" << response_data; // Depuración

            QJsonDocument jsonDoc = QJsonDocument::fromJson(response_data);

            if (!jsonDoc.isNull() && jsonDoc.isObject()) {
                QJsonObject response = jsonDoc.object();
                QString status = response["status"].toString();
                QString message = response["message"].toString();

                if (status == "success") {
                    // Éxito: Registro completado
                    QMessageBox::information(this, "Registro exitoso", message);

                    // Redirigir a la ventana de inicio de sesión (Ya existía)
                    this->close();
                    sign_in *signInWindow = new sign_in();
                    signInWindow->show();

                } else {
                    // Fallo Lógico (ej. email ya existe)
                    showError(message);
                }
            } else {
                showError("Error al procesar la respuesta del servidor. (JSON inválido)");
            }
        } else {
            // Error de Conexión
            showError("Error de conexión al servidor: " + reply->errorString());
        }

        reply->deleteLater();
        manager->deleteLater();
    });
}

void sign_up::on_ir_a_sign_in_clicked()
{
    this->close();
    sign_in *signInWindow = new sign_in();
    signInWindow->show();
}
