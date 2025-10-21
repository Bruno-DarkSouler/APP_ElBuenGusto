#include "mainwindow.h"
#include "sign_in.h"
#include "ui_sign_in.h"
#include "sign_up.h"
#include "carrito.h"
#include "perfil.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QDate>
#include <QCheckBox>
#include <QPushButton>
#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSettings>

sign_in::sign_in(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::sign_in)
{
    ui->setupUi(this);

    // Conectar validaciones en tiempo real
    connect(ui->lineEdit_email, &QLineEdit::textChanged, this, &sign_in::validateEmail);
    connect(ui->lineEdit_password, &QLineEdit::textChanged, this, &sign_in::validatePassword);

    // Conectar el botón de iniciar sesión y el de ir a registro
    connect(ui->pushButton_sign_in, &QPushButton::clicked, this, &sign_in::on_iniciar_clicked);
    connect(ui->pushButton_sign_up, &QPushButton::clicked, this, &sign_in::on_ir_a_sign_up_clicked);
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

    QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@gmail\\.com$");
    if (!emailRegex.match(email).hasMatch()) {
        showError("El email debe ser una dirección válida de Gmail (@gmail.com)");
        return false;
    }

    if (password.length() < 8) {
        showError("La contraseña debe tener al menos 8 caracteres");
        return false;
    }

    return true;
}

void sign_in::showError(const QString& message)
{
    QMessageBox::warning(this, "Error de Inicio de Sesión", message);
}

void sign_in::on_ir_a_sign_up_clicked()
{
    this->close();
    sign_up *signUpWindow = new sign_up();
    signUpWindow->show();
}

void sign_in::on_iniciar_clicked()
{
    if (!isFormValid()) {
        return;
    }

    // 1. Preparar datos y UI
    ui->pushButton_sign_in->setEnabled(false); // Deshabilita el botón

    QString email = ui->lineEdit_email->text().trimmed();
    QString password = ui->lineEdit_password->text();

    // 2. Construir el JSON para el servidor
    QJsonObject jsonPayload;
    jsonPayload["username"] = email;
    jsonPayload["password"] = password;

    QJsonDocument doc(jsonPayload);
    QByteArray postData = doc.toJson(QJsonDocument::Compact);

    // 3. Configurar y enviar la solicitud POST
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QUrl url("http://localhost/WEB_ElBuenGusto/api/sign_in.php");
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, postData);

    // 4. Manejar la respuesta del servidor (ASÍNCRONO)
    connect(reply, &QNetworkReply::finished, this, [=]() {
        // Habilitar el botón de nuevo
        ui->pushButton_sign_in->setEnabled(true);

        if (reply->error() == QNetworkReply::NoError) {

            QByteArray response_data = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response_data);

            if (!jsonDoc.isNull() && jsonDoc.isObject()) {
                QJsonObject response = jsonDoc.object();
                QString status = response["status"].toString();
                QString message = response["message"].toString();

                if (status == "success") {
                    // Éxito: Servidor confirma el inicio de sesión
                    QMessageBox::information(this, "Acceso Autorizado", message);

                    // Extraer el rol del usuario
                    QString rol = response["rol"].toString();
                    QWidget *nextWindow = nullptr;

                    // Lógica de Redirección basada en Rol
                    if (rol == "cliente") {
                        // Si es cliente, llevar a la ventana principal
                        nextWindow = new perfil();

                    } else if (rol == "repartidor") {
                        // Si es repartidor, llevar al Carrito (ej. gestión de pedidos)
                        nextWindow = new carrito();

                    } else if (rol == "cajero") {
                        // Si es cajero, llevar al Perfil (ej. gestión de caja)
                        nextWindow = new MainWindow();

                    } else {
                        // Rol desconocido o por defecto
                        nextWindow = new MainWindow();
                    }

                    // Verificar si los datos del usuario están presentes
                    if (nextWindow && response.contains("user_data") && response["user_data"].isObject()) {
                        // Guardar datos en QSettings
                        QSettings settings("YourCompany", "YourApp");
                        settings.setValue("user_id", response["user_id"].toInt());
                        QJsonObject userData = response["user_data"].toObject();
                        settings.setValue("user_nombre_completo", userData["nombre_completo"].toString());
                        settings.setValue("user_email", userData["email"].toString());
                        settings.setValue("user_telefono", userData["telefono"].toString());
                        settings.setValue("user_direccion", userData["direccion"].toString());
                        settings.setValue("user_fecha_nacimiento", userData["fecha_nacimiento"].toString());

                        nextWindow->show();
                        this->close();
                    } else {
                        // Manejar el caso en que no haya datos de usuario
                        showError("No se encontraron datos de usuario.");
                    }
                } else {
                    // Fallo Lógico: Credenciales incorrectas, usuario no encontrado, etc.
                    showError(message);
                }
            } else {
                // Error al interpretar la respuesta como JSON
                showError("Error al procesar la respuesta del servidor.");
            }
        } else {
            // Error de Conexión o de Red
            showError("Error de conexión al servidor: " + reply->errorString());
        }

        reply->deleteLater();
        manager->deleteLater();
    });
}