#include "Perfil.h"
#include "ui_perfil.h"  // Asegúrate de que este archivo existe y está en el mismo directorio
#include <QSettings>
#include <QMessageBox>
#include "sign_in.h"  // Asegúrate de que este archivo existe y está en el mismo directorio
#include <QFileDialog>
#include <QPixmap>

perfil::perfil(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::perfil)
{
    ui->setupUi(this);
    loadUserData();  // Cargar datos del usuario al iniciar la ventana

    // Conexión del botón de cargar foto
    connect(ui->pushButton_foto, &QPushButton::clicked, this, &perfil::on_cargar_foto_clicked);
}

perfil::~perfil()
{
    delete ui;
}

void perfil::loadUserData()
{
    QSettings settings("YourCompany", "YourApp");
    int user_id = settings.value("user_id", -1).toInt();
    QString nombre_completo = settings.value("user_nombre_completo", "").toString();
    QString email = settings.value("user_email", "").toString();
    QString telefono = settings.value("user_telefono", "").toString();
    QString direccion = settings.value("user_direccion", "").toString();
    QString fecha_nacimiento = settings.value("user_fecha_nacimiento", "").toString();
    QString foto_perfil = settings.value("user_foto_perfil", "").toString();

    if (user_id != -1) {
        // Mostrar los datos del usuario en la interfaz
        ui->lineEdit_nombre->setText(nombre_completo);
        ui->lineEdit_email->setText(email);
        ui->lineEdit_telefono->setText(telefono);
        ui->lineEdit_direccion->setText(direccion);
        ui->lineEdit_nacimiento->setText(fecha_nacimiento);

        // Mostrar la foto de perfil si existe
        if (!foto_perfil.isEmpty()) {
            QPixmap pixmap(foto_perfil);
            if (!pixmap.isNull()) {
                ui->label_foto->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            }
        }
    } else {
        // Manejar el caso en que no haya datos de usuario
        QMessageBox::warning(this, "Advertencia", "No se encontraron datos de usuario.");
    }
}

void perfil::on_logout_clicked()
{
    QSettings settings("YourCompany", "YourApp");
    settings.remove("user_id");
    settings.remove("user_nombre_completo");
    settings.remove("user_email");
    settings.remove("user_telefono");
    settings.remove("user_direccion");
    settings.remove("user_fecha_nacimiento");
    settings.remove("user_foto_perfil");  // También eliminar la foto de perfil

    // Redirigir a la ventana de inicio de sesión o a la pantalla principal
    this->close();
    sign_in *signInWindow = new sign_in();
    signInWindow->show();
}

void perfil::on_cargar_foto_clicked()
{
    // Abrir cuadro de diálogo para seleccionar una imagen
    QString filePath = QFileDialog::getOpenFileName(this, "Seleccionar Foto de Perfil", "", "Imágenes (*.png *.jpg *.jpeg *.bmp *.gif)");
    if (!filePath.isEmpty()) {
        // Cargar la imagen seleccionada en el QLabel
        QPixmap pixmap(filePath);
        if (!pixmap.isNull()) {
            ui->label_foto->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));

            // Guardar la ruta de la foto de perfil en las configuraciones
            QSettings settings("YourCompany", "YourApp");
            settings.setValue("user_foto_perfil", filePath);
        } else {
            QMessageBox::warning(this, "Error", "No se pudo cargar la imagen seleccionada.");
        }
    }
}