/********************************************************************************
** Form generated from reading UI file 'confirmacion_pedido.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIRMACION_PEDIDO_H
#define UI_CONFIRMACION_PEDIDO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfirmacionPedido
{
public:
    QVBoxLayout *verticalLayout_main;
    QFrame *frame_main;
    QVBoxLayout *verticalLayout_frame;
    QFrame *frame_header;
    QHBoxLayout *horizontalLayout_header;
    QLabel *label_logo;
    QLabel *label_titulo;
    QSpacerItem *horizontalSpacer_header;
    QScrollArea *scrollArea_main;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_scroll;
    QGroupBox *groupBox_datosPersonales;
    QVBoxLayout *verticalLayout_datosPersonales;
    QHBoxLayout *horizontalLayout_nombres;
    QLabel *label_nombre;
    QLineEdit *lineEdit_nombre;
    QLabel *label_apellido;
    QLineEdit *lineEdit_apellido;
    QHBoxLayout *horizontalLayout_contacto;
    QLabel *label_telefono;
    QLineEdit *lineEdit_telefono;
    QLabel *label_email;
    QLineEdit *lineEdit_email;
    QGroupBox *groupBox_direccionEntrega;
    QVBoxLayout *verticalLayout_direccion;
    QTextEdit *textEdit_direccion;
    QLabel *label_costoDelivery;
    QGroupBox *groupBox_tipoPedido;
    QVBoxLayout *verticalLayout_tipoPedido;
    QRadioButton *radioButton_inmediato;
    QRadioButton *radioButton_programado;
    QFrame *frame_programacion;
    QHBoxLayout *horizontalLayout_programacion;
    QLabel *label_fecha;
    QDateEdit *dateEdit_fecha;
    QLabel *label_hora;
    QTimeEdit *timeEdit_hora;
    QSpacerItem *horizontalSpacer_programacion;
    QLabel *label_horarioAtencion;
    QGroupBox *groupBox_metodoPago;
    QVBoxLayout *verticalLayout_metodoPago;
    QRadioButton *radioButton_digital;
    QRadioButton *radioButton_efectivo;
    QGroupBox *groupBox_resumenPedido;
    QVBoxLayout *verticalLayout_resumenPedido;
    QScrollArea *scrollArea_productos;
    QWidget *scrollAreaWidgetContents_productos;
    QVBoxLayout *verticalLayout_productos;
    QFrame *frame_totales;
    QVBoxLayout *verticalLayout_totales;
    QLabel *label_subtotal;
    QLabel *label_delivery;
    QLabel *label_total;
    QGroupBox *groupBox_comentarios;
    QVBoxLayout *verticalLayout_comentarios;
    QTextEdit *textEdit_comentarios;
    QFrame *frame_botones;
    QHBoxLayout *horizontalLayout_botones;
    QPushButton *pushButton_volver;
    QSpacerItem *horizontalSpacer_botones;
    QPushButton *pushButton_confirmar;

    void setupUi(QWidget *ConfirmacionPedido)
    {
        if (ConfirmacionPedido->objectName().isEmpty())
            ConfirmacionPedido->setObjectName("ConfirmacionPedido");
        ConfirmacionPedido->resize(600, 800);
        ConfirmacionPedido->setStyleSheet(QString::fromUtf8("\n"
"   QWidget {\n"
"       background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #8B4513, stop:1 #654321);\n"
"       font-family: 'Segoe UI', Arial, sans-serif;\n"
"   }\n"
"   "));
        verticalLayout_main = new QVBoxLayout(ConfirmacionPedido);
        verticalLayout_main->setSpacing(10);
        verticalLayout_main->setObjectName("verticalLayout_main");
        verticalLayout_main->setContentsMargins(20, 20, 20, 20);
        frame_main = new QFrame(ConfirmacionPedido);
        frame_main->setObjectName("frame_main");
        frame_main->setStyleSheet(QString::fromUtf8("background-color: #F5EBD2; border-radius: 15px;"));
        frame_main->setFrameShape(QFrame::Shape::StyledPanel);
        verticalLayout_frame = new QVBoxLayout(frame_main);
        verticalLayout_frame->setSpacing(15);
        verticalLayout_frame->setObjectName("verticalLayout_frame");
        verticalLayout_frame->setContentsMargins(20, 20, 20, 20);
        frame_header = new QFrame(frame_main);
        frame_header->setObjectName("frame_header");
        frame_header->setMaximumSize(QSize(16777215, 80));
        frame_header->setStyleSheet(QString::fromUtf8("background-color: rgba(200, 30, 45, 0.1); border-radius: 10px;"));
        horizontalLayout_header = new QHBoxLayout(frame_header);
        horizontalLayout_header->setObjectName("horizontalLayout_header");
        label_logo = new QLabel(frame_header);
        label_logo->setObjectName("label_logo");
        label_logo->setMaximumSize(QSize(50, 50));
        label_logo->setPixmap(QPixmap(QString::fromUtf8(":/logo.png")));
        label_logo->setScaledContents(true);

        horizontalLayout_header->addWidget(label_logo);

        label_titulo = new QLabel(frame_header);
        label_titulo->setObjectName("label_titulo");
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(18);
        font.setBold(true);
        label_titulo->setFont(font);
        label_titulo->setStyleSheet(QString::fromUtf8("color: rgb(80,50,20);"));

        horizontalLayout_header->addWidget(label_titulo);

        horizontalSpacer_header = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_header->addItem(horizontalSpacer_header);


        verticalLayout_frame->addWidget(frame_header);

        scrollArea_main = new QScrollArea(frame_main);
        scrollArea_main->setObjectName("scrollArea_main");
        scrollArea_main->setStyleSheet(QString::fromUtf8("QScrollArea { border: none; background-color: transparent; }"));
        scrollArea_main->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 538, 1200));
        verticalLayout_scroll = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_scroll->setObjectName("verticalLayout_scroll");
        groupBox_datosPersonales = new QGroupBox(scrollAreaWidgetContents);
        groupBox_datosPersonales->setObjectName("groupBox_datosPersonales");
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        groupBox_datosPersonales->setFont(font1);
        groupBox_datosPersonales->setStyleSheet(QString::fromUtf8("\n"
"             QGroupBox {\n"
"                 background-color: white;\n"
"                 border-radius: 10px;\n"
"                 padding-top: 15px;\n"
"                 color: rgb(80,50,20);\n"
"             }\n"
"             QGroupBox::title {\n"
"                 subcontrol-origin: margin;\n"
"                 left: 10px;\n"
"                 padding: 0 10px 0 10px;\n"
"             }\n"
"             "));
        verticalLayout_datosPersonales = new QVBoxLayout(groupBox_datosPersonales);
        verticalLayout_datosPersonales->setObjectName("verticalLayout_datosPersonales");
        horizontalLayout_nombres = new QHBoxLayout();
        horizontalLayout_nombres->setObjectName("horizontalLayout_nombres");
        label_nombre = new QLabel(groupBox_datosPersonales);
        label_nombre->setObjectName("label_nombre");
        QFont font2;
        font2.setBold(false);
        label_nombre->setFont(font2);

        horizontalLayout_nombres->addWidget(label_nombre);

        lineEdit_nombre = new QLineEdit(groupBox_datosPersonales);
        lineEdit_nombre->setObjectName("lineEdit_nombre");
        lineEdit_nombre->setStyleSheet(QString::fromUtf8("QLineEdit { padding: 8px; border: 2px solid #ddd; border-radius: 6px; }"));

        horizontalLayout_nombres->addWidget(lineEdit_nombre);

        label_apellido = new QLabel(groupBox_datosPersonales);
        label_apellido->setObjectName("label_apellido");
        label_apellido->setFont(font2);

        horizontalLayout_nombres->addWidget(label_apellido);

        lineEdit_apellido = new QLineEdit(groupBox_datosPersonales);
        lineEdit_apellido->setObjectName("lineEdit_apellido");
        lineEdit_apellido->setStyleSheet(QString::fromUtf8("QLineEdit { padding: 8px; border: 2px solid #ddd; border-radius: 6px; }"));

        horizontalLayout_nombres->addWidget(lineEdit_apellido);


        verticalLayout_datosPersonales->addLayout(horizontalLayout_nombres);

        horizontalLayout_contacto = new QHBoxLayout();
        horizontalLayout_contacto->setObjectName("horizontalLayout_contacto");
        label_telefono = new QLabel(groupBox_datosPersonales);
        label_telefono->setObjectName("label_telefono");
        label_telefono->setFont(font2);

        horizontalLayout_contacto->addWidget(label_telefono);

        lineEdit_telefono = new QLineEdit(groupBox_datosPersonales);
        lineEdit_telefono->setObjectName("lineEdit_telefono");
        lineEdit_telefono->setStyleSheet(QString::fromUtf8("QLineEdit { padding: 8px; border: 2px solid #ddd; border-radius: 6px; }"));

        horizontalLayout_contacto->addWidget(lineEdit_telefono);

        label_email = new QLabel(groupBox_datosPersonales);
        label_email->setObjectName("label_email");
        label_email->setFont(font2);

        horizontalLayout_contacto->addWidget(label_email);

        lineEdit_email = new QLineEdit(groupBox_datosPersonales);
        lineEdit_email->setObjectName("lineEdit_email");
        lineEdit_email->setStyleSheet(QString::fromUtf8("QLineEdit { padding: 8px; border: 2px solid #ddd; border-radius: 6px; }"));

        horizontalLayout_contacto->addWidget(lineEdit_email);


        verticalLayout_datosPersonales->addLayout(horizontalLayout_contacto);


        verticalLayout_scroll->addWidget(groupBox_datosPersonales);

        groupBox_direccionEntrega = new QGroupBox(scrollAreaWidgetContents);
        groupBox_direccionEntrega->setObjectName("groupBox_direccionEntrega");
        groupBox_direccionEntrega->setFont(font1);
        groupBox_direccionEntrega->setStyleSheet(QString::fromUtf8("\n"
"             QGroupBox {\n"
"                 background-color: white;\n"
"                 border-radius: 10px;\n"
"                 padding-top: 15px;\n"
"                 color: rgb(80,50,20);\n"
"             }\n"
"             QGroupBox::title {\n"
"                 subcontrol-origin: margin;\n"
"                 left: 10px;\n"
"                 padding: 0 10px 0 10px;\n"
"             }\n"
"             "));
        verticalLayout_direccion = new QVBoxLayout(groupBox_direccionEntrega);
        verticalLayout_direccion->setObjectName("verticalLayout_direccion");
        textEdit_direccion = new QTextEdit(groupBox_direccionEntrega);
        textEdit_direccion->setObjectName("textEdit_direccion");
        textEdit_direccion->setMaximumSize(QSize(16777215, 80));
        textEdit_direccion->setStyleSheet(QString::fromUtf8("QTextEdit { padding: 8px; border: 2px solid #ddd; border-radius: 6px; }"));

        verticalLayout_direccion->addWidget(textEdit_direccion);

        label_costoDelivery = new QLabel(groupBox_direccionEntrega);
        label_costoDelivery->setObjectName("label_costoDelivery");
        QFont font3;
        font3.setPointSize(11);
        font3.setBold(true);
        label_costoDelivery->setFont(font3);
        label_costoDelivery->setStyleSheet(QString::fromUtf8("color: rgb(200, 30, 45);"));

        verticalLayout_direccion->addWidget(label_costoDelivery);


        verticalLayout_scroll->addWidget(groupBox_direccionEntrega);

        groupBox_tipoPedido = new QGroupBox(scrollAreaWidgetContents);
        groupBox_tipoPedido->setObjectName("groupBox_tipoPedido");
        groupBox_tipoPedido->setFont(font1);
        groupBox_tipoPedido->setStyleSheet(QString::fromUtf8("\n"
"             QGroupBox {\n"
"                 background-color: white;\n"
"                 border-radius: 10px;\n"
"                 padding-top: 15px;\n"
"                 color: rgb(80,50,20);\n"
"             }\n"
"             QGroupBox::title {\n"
"                 subcontrol-origin: margin;\n"
"                 left: 10px;\n"
"                 padding: 0 10px 0 10px;\n"
"             }\n"
"             "));
        verticalLayout_tipoPedido = new QVBoxLayout(groupBox_tipoPedido);
        verticalLayout_tipoPedido->setObjectName("verticalLayout_tipoPedido");
        radioButton_inmediato = new QRadioButton(groupBox_tipoPedido);
        radioButton_inmediato->setObjectName("radioButton_inmediato");
        radioButton_inmediato->setChecked(true);
        radioButton_inmediato->setFont(font2);

        verticalLayout_tipoPedido->addWidget(radioButton_inmediato);

        radioButton_programado = new QRadioButton(groupBox_tipoPedido);
        radioButton_programado->setObjectName("radioButton_programado");
        radioButton_programado->setFont(font2);

        verticalLayout_tipoPedido->addWidget(radioButton_programado);

        frame_programacion = new QFrame(groupBox_tipoPedido);
        frame_programacion->setObjectName("frame_programacion");
        frame_programacion->setEnabled(false);
        horizontalLayout_programacion = new QHBoxLayout(frame_programacion);
        horizontalLayout_programacion->setObjectName("horizontalLayout_programacion");
        label_fecha = new QLabel(frame_programacion);
        label_fecha->setObjectName("label_fecha");

        horizontalLayout_programacion->addWidget(label_fecha);

        dateEdit_fecha = new QDateEdit(frame_programacion);
        dateEdit_fecha->setObjectName("dateEdit_fecha");
        dateEdit_fecha->setStyleSheet(QString::fromUtf8("QDateEdit { padding: 6px; border: 2px solid #ddd; border-radius: 4px; }"));
        dateEdit_fecha->setCalendarPopup(true);

        horizontalLayout_programacion->addWidget(dateEdit_fecha);

        label_hora = new QLabel(frame_programacion);
        label_hora->setObjectName("label_hora");

        horizontalLayout_programacion->addWidget(label_hora);

        timeEdit_hora = new QTimeEdit(frame_programacion);
        timeEdit_hora->setObjectName("timeEdit_hora");
        timeEdit_hora->setStyleSheet(QString::fromUtf8("QTimeEdit { padding: 6px; border: 2px solid #ddd; border-radius: 4px; }"));

        horizontalLayout_programacion->addWidget(timeEdit_hora);

        horizontalSpacer_programacion = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_programacion->addItem(horizontalSpacer_programacion);


        verticalLayout_tipoPedido->addWidget(frame_programacion);

        label_horarioAtencion = new QLabel(groupBox_tipoPedido);
        label_horarioAtencion->setObjectName("label_horarioAtencion");
        QFont font4;
        font4.setPointSize(10);
        font4.setBold(false);
        font4.setItalic(true);
        label_horarioAtencion->setFont(font4);
        label_horarioAtencion->setStyleSheet(QString::fromUtf8("color: #666;"));

        verticalLayout_tipoPedido->addWidget(label_horarioAtencion);


        verticalLayout_scroll->addWidget(groupBox_tipoPedido);

        groupBox_metodoPago = new QGroupBox(scrollAreaWidgetContents);
        groupBox_metodoPago->setObjectName("groupBox_metodoPago");
        groupBox_metodoPago->setFont(font1);
        groupBox_metodoPago->setStyleSheet(QString::fromUtf8("\n"
"             QGroupBox {\n"
"                 background-color: white;\n"
"                 border-radius: 10px;\n"
"                 padding-top: 15px;\n"
"                 color: rgb(80,50,20);\n"
"             }\n"
"             QGroupBox::title {\n"
"                 subcontrol-origin: margin;\n"
"                 left: 10px;\n"
"                 padding: 0 10px 0 10px;\n"
"             }\n"
"             "));
        verticalLayout_metodoPago = new QVBoxLayout(groupBox_metodoPago);
        verticalLayout_metodoPago->setObjectName("verticalLayout_metodoPago");
        radioButton_digital = new QRadioButton(groupBox_metodoPago);
        radioButton_digital->setObjectName("radioButton_digital");
        radioButton_digital->setChecked(true);
        radioButton_digital->setFont(font2);

        verticalLayout_metodoPago->addWidget(radioButton_digital);

        radioButton_efectivo = new QRadioButton(groupBox_metodoPago);
        radioButton_efectivo->setObjectName("radioButton_efectivo");
        radioButton_efectivo->setFont(font2);

        verticalLayout_metodoPago->addWidget(radioButton_efectivo);


        verticalLayout_scroll->addWidget(groupBox_metodoPago);

        groupBox_resumenPedido = new QGroupBox(scrollAreaWidgetContents);
        groupBox_resumenPedido->setObjectName("groupBox_resumenPedido");
        groupBox_resumenPedido->setFont(font1);
        groupBox_resumenPedido->setStyleSheet(QString::fromUtf8("\n"
"             QGroupBox {\n"
"                 background-color: white;\n"
"                 border-radius: 10px;\n"
"                 padding-top: 15px;\n"
"                 color: rgb(80,50,20);\n"
"             }\n"
"             QGroupBox::title {\n"
"                 subcontrol-origin: margin;\n"
"                 left: 10px;\n"
"                 padding: 0 10px 0 10px;\n"
"             }\n"
"             "));
        verticalLayout_resumenPedido = new QVBoxLayout(groupBox_resumenPedido);
        verticalLayout_resumenPedido->setObjectName("verticalLayout_resumenPedido");
        scrollArea_productos = new QScrollArea(groupBox_resumenPedido);
        scrollArea_productos->setObjectName("scrollArea_productos");
        scrollArea_productos->setMaximumSize(QSize(16777215, 200));
        scrollArea_productos->setStyleSheet(QString::fromUtf8("QScrollArea { border: 1px solid #ddd; border-radius: 6px; background-color: #f9f9f9; }"));
        scrollArea_productos->setWidgetResizable(true);
        scrollAreaWidgetContents_productos = new QWidget();
        scrollAreaWidgetContents_productos->setObjectName("scrollAreaWidgetContents_productos");
        scrollAreaWidgetContents_productos->setGeometry(QRect(0, 0, 494, 198));
        verticalLayout_productos = new QVBoxLayout(scrollAreaWidgetContents_productos);
        verticalLayout_productos->setSpacing(5);
        verticalLayout_productos->setObjectName("verticalLayout_productos");
        scrollArea_productos->setWidget(scrollAreaWidgetContents_productos);

        verticalLayout_resumenPedido->addWidget(scrollArea_productos);

        frame_totales = new QFrame(groupBox_resumenPedido);
        frame_totales->setObjectName("frame_totales");
        frame_totales->setStyleSheet(QString::fromUtf8("background-color: #f0f0f0; border-radius: 6px; padding: 10px;"));
        verticalLayout_totales = new QVBoxLayout(frame_totales);
        verticalLayout_totales->setObjectName("verticalLayout_totales");
        label_subtotal = new QLabel(frame_totales);
        label_subtotal->setObjectName("label_subtotal");
        QFont font5;
        font5.setPointSize(11);
        font5.setBold(false);
        label_subtotal->setFont(font5);

        verticalLayout_totales->addWidget(label_subtotal);

        label_delivery = new QLabel(frame_totales);
        label_delivery->setObjectName("label_delivery");
        label_delivery->setFont(font5);

        verticalLayout_totales->addWidget(label_delivery);

        label_total = new QLabel(frame_totales);
        label_total->setObjectName("label_total");
        QFont font6;
        font6.setPointSize(14);
        font6.setBold(true);
        label_total->setFont(font6);
        label_total->setStyleSheet(QString::fromUtf8("color: rgb(200, 30, 45);"));

        verticalLayout_totales->addWidget(label_total);


        verticalLayout_resumenPedido->addWidget(frame_totales);


        verticalLayout_scroll->addWidget(groupBox_resumenPedido);

        groupBox_comentarios = new QGroupBox(scrollAreaWidgetContents);
        groupBox_comentarios->setObjectName("groupBox_comentarios");
        groupBox_comentarios->setFont(font1);
        groupBox_comentarios->setStyleSheet(QString::fromUtf8("\n"
"             QGroupBox {\n"
"                 background-color: white;\n"
"                 border-radius: 10px;\n"
"                 padding-top: 15px;\n"
"                 color: rgb(80,50,20);\n"
"             }\n"
"             QGroupBox::title {\n"
"                 subcontrol-origin: margin;\n"
"                 left: 10px;\n"
"                 padding: 0 10px 0 10px;\n"
"             }\n"
"             "));
        verticalLayout_comentarios = new QVBoxLayout(groupBox_comentarios);
        verticalLayout_comentarios->setObjectName("verticalLayout_comentarios");
        textEdit_comentarios = new QTextEdit(groupBox_comentarios);
        textEdit_comentarios->setObjectName("textEdit_comentarios");
        textEdit_comentarios->setMaximumSize(QSize(16777215, 80));
        textEdit_comentarios->setStyleSheet(QString::fromUtf8("QTextEdit { padding: 8px; border: 2px solid #ddd; border-radius: 6px; }"));

        verticalLayout_comentarios->addWidget(textEdit_comentarios);


        verticalLayout_scroll->addWidget(groupBox_comentarios);

        scrollArea_main->setWidget(scrollAreaWidgetContents);

        verticalLayout_frame->addWidget(scrollArea_main);

        frame_botones = new QFrame(frame_main);
        frame_botones->setObjectName("frame_botones");
        frame_botones->setMaximumSize(QSize(16777215, 80));
        frame_botones->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        horizontalLayout_botones = new QHBoxLayout(frame_botones);
        horizontalLayout_botones->setObjectName("horizontalLayout_botones");
        pushButton_volver = new QPushButton(frame_botones);
        pushButton_volver->setObjectName("pushButton_volver");
        pushButton_volver->setMinimumSize(QSize(120, 45));
        pushButton_volver->setStyleSheet(QString::fromUtf8("\n"
"            QPushButton {\n"
"                background-color: #666;\n"
"                color: white;\n"
"                border: none;\n"
"                padding: 12px 20px;\n"
"                border-radius: 8px;\n"
"                font-size: 14px;\n"
"                font-weight: bold;\n"
"            }\n"
"            QPushButton:hover {\n"
"                background-color: #555;\n"
"            }\n"
"            "));

        horizontalLayout_botones->addWidget(pushButton_volver);

        horizontalSpacer_botones = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_botones->addItem(horizontalSpacer_botones);

        pushButton_confirmar = new QPushButton(frame_botones);
        pushButton_confirmar->setObjectName("pushButton_confirmar");
        pushButton_confirmar->setMinimumSize(QSize(150, 45));
        pushButton_confirmar->setStyleSheet(QString::fromUtf8("\n"
"            QPushButton {\n"
"                background-color: rgb(200, 30, 45);\n"
"                color: white;\n"
"                border: none;\n"
"                padding: 12px 20px;\n"
"                border-radius: 8px;\n"
"                font-size: 16px;\n"
"                font-weight: bold;\n"
"            }\n"
"            QPushButton:hover {\n"
"                background-color: rgb(180, 25, 40);\n"
"            }\n"
"            QPushButton:disabled {\n"
"                background-color: #ccc;\n"
"                color: #999;\n"
"            }\n"
"            "));

        horizontalLayout_botones->addWidget(pushButton_confirmar);


        verticalLayout_frame->addWidget(frame_botones);


        verticalLayout_main->addWidget(frame_main);


        retranslateUi(ConfirmacionPedido);

        QMetaObject::connectSlotsByName(ConfirmacionPedido);
    } // setupUi

    void retranslateUi(QWidget *ConfirmacionPedido)
    {
        ConfirmacionPedido->setWindowTitle(QCoreApplication::translate("ConfirmacionPedido", "Confirmar Pedido - Rotiser\303\255a El Buen Gusto", nullptr));
        label_logo->setText(QString());
        label_titulo->setText(QCoreApplication::translate("ConfirmacionPedido", "Confirmar Pedido", nullptr));
        groupBox_datosPersonales->setTitle(QCoreApplication::translate("ConfirmacionPedido", "Datos Personales", nullptr));
        label_nombre->setText(QCoreApplication::translate("ConfirmacionPedido", "Nombre:", nullptr));
        lineEdit_nombre->setPlaceholderText(QCoreApplication::translate("ConfirmacionPedido", "Ingrese su nombre", nullptr));
        label_apellido->setText(QCoreApplication::translate("ConfirmacionPedido", "Apellido:", nullptr));
        lineEdit_apellido->setPlaceholderText(QCoreApplication::translate("ConfirmacionPedido", "Ingrese su apellido", nullptr));
        label_telefono->setText(QCoreApplication::translate("ConfirmacionPedido", "Tel\303\251fono:", nullptr));
        lineEdit_telefono->setPlaceholderText(QCoreApplication::translate("ConfirmacionPedido", "Ej: 3516789123", nullptr));
        label_email->setText(QCoreApplication::translate("ConfirmacionPedido", "Email:", nullptr));
        lineEdit_email->setPlaceholderText(QCoreApplication::translate("ConfirmacionPedido", "ejemplo@email.com", nullptr));
        groupBox_direccionEntrega->setTitle(QCoreApplication::translate("ConfirmacionPedido", "Direcci\303\263n de Entrega", nullptr));
        textEdit_direccion->setPlaceholderText(QCoreApplication::translate("ConfirmacionPedido", "Ingrese la direcci\303\263n completa de entrega (calle, n\303\272mero, barrio, referencias)", nullptr));
        label_costoDelivery->setText(QCoreApplication::translate("ConfirmacionPedido", "Costo de delivery: Calculando...", nullptr));
        groupBox_tipoPedido->setTitle(QCoreApplication::translate("ConfirmacionPedido", "Tipo de Pedido", nullptr));
        radioButton_inmediato->setText(QCoreApplication::translate("ConfirmacionPedido", "Pedido Inmediato (entrega en horario de atenci\303\263n)", nullptr));
        radioButton_programado->setText(QCoreApplication::translate("ConfirmacionPedido", "Pedido Programado", nullptr));
        label_fecha->setText(QCoreApplication::translate("ConfirmacionPedido", "Fecha:", nullptr));
        label_hora->setText(QCoreApplication::translate("ConfirmacionPedido", "Hora:", nullptr));
        timeEdit_hora->setDisplayFormat(QCoreApplication::translate("ConfirmacionPedido", "HH:mm", nullptr));
        label_horarioAtencion->setText(QCoreApplication::translate("ConfirmacionPedido", "Horarios de atenci\303\263n: 11:00-15:00 y 19:00-23:00", nullptr));
        groupBox_metodoPago->setTitle(QCoreApplication::translate("ConfirmacionPedido", "M\303\251todo de Pago", nullptr));
        radioButton_digital->setText(QCoreApplication::translate("ConfirmacionPedido", "Pago Digital (Mercado Pago, Cuenta DNI, etc.)", nullptr));
        radioButton_efectivo->setText(QCoreApplication::translate("ConfirmacionPedido", "Efectivo (solo clientes autorizados)", nullptr));
        groupBox_resumenPedido->setTitle(QCoreApplication::translate("ConfirmacionPedido", "Resumen del Pedido", nullptr));
        label_subtotal->setText(QCoreApplication::translate("ConfirmacionPedido", "Subtotal: $0.00", nullptr));
        label_delivery->setText(QCoreApplication::translate("ConfirmacionPedido", "Delivery: $0.00", nullptr));
        label_total->setText(QCoreApplication::translate("ConfirmacionPedido", "Total: $0.00", nullptr));
        groupBox_comentarios->setTitle(QCoreApplication::translate("ConfirmacionPedido", "Comentarios Adicionales", nullptr));
        textEdit_comentarios->setPlaceholderText(QCoreApplication::translate("ConfirmacionPedido", "Comentarios especiales, preferencias de cocci\303\263n, sin sal, etc. (opcional)", nullptr));
        pushButton_volver->setText(QCoreApplication::translate("ConfirmacionPedido", "Volver al Carrito", nullptr));
        pushButton_confirmar->setText(QCoreApplication::translate("ConfirmacionPedido", "Confirmar Pedido", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfirmacionPedido: public Ui_ConfirmacionPedido {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIRMACION_PEDIDO_H
