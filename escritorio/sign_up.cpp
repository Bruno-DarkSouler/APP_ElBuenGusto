#include "sign_in.h"
#include "sign_up.h"
#include "ui_sign_up.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QDate>
#include <QCheckBox>
#include <QPushButton>
#include <QLineEdit>

// Librerías de Red y JSON
#include "QNetworkAccessManager"
#include "QNetworkRequest"
#include "QNetworkReply"
#include "QJsonDocument"
#include "QJsonObject"

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
    connect(ui->lineEdit_fecha, &QLineEdit::textChanged, this, &sign_up::validateDate);
    connect(ui->lineEdit_password, &QLineEdit::textChanged, this, &sign_up::validatePassword);

    // Conexión del botón de registro
    connect(ui->pushButton, &QPushButton::clicked, this, &sign_up::on_iniciar_clicked);

    // ----------------------------------------------------------------------
    // CAMBIO 1: CONEXIÓN DEL BOTÓN DE NAVEGACIÓN A INICIAR SESIÓN
    // ----------------------------------------------------------------------
    // Asumiendo que el botón para ir a Sign In se llama pushButton_sign_in en sign_up.ui
    connect(ui->pushButton_sign_in, &QPushButton::clicked, this, &sign_up::on_ir_a_sign_in_clicked);

    // Máscaras y Placeholders
    ui->lineEdit_fecha->setPlaceholderText("dd/mm/aaaa");
    ui->lineEdit_telefono->setInputMask("99-9999-9999");
}

sign_up::~sign_up()
{
    delete ui;
}

// ----------------------------------------------------
// Métodos de Validación
// ----------------------------------------------------
void sign_up::validateName() { /* ... Tu código de validación de nombre ... */ }
void sign_up::validateApellido() { /* ... Tu código de validación de apellido ... */ }
void sign_up::validateEmail() { /* ... Tu código de validación de email ... */ }
void sign_up::validatePhone() { /* ... Tu código de validación de teléfono ... */ }
void sign_up::validateDate() { /* ... Tu código de validación de fecha ... */ }
void sign_up::validatePassword() { /* ... Tu código de validación de contraseña ... */ }

void sign_up::setFieldStyle(QLineEdit* field, const QString& status) { /* ... Tu código de estilo ... */ }
void sign_up::showError(const QString& message) { QMessageBox::warning(this, "Error de validación", message); }
bool sign_up::isFormValid() { /* ... Tu código de validación final ... */ return true; }

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

    // 2. Construir el JSON para el servidor
    QJsonObject jsonPayload;
    jsonPayload["nombre"] = nombre;
    jsonPayload["apellido"] = apellido;
    jsonPayload["telefono"] = telefono;
    jsonPayload["username"] = email;
    jsonPayload["password"] = password;

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
