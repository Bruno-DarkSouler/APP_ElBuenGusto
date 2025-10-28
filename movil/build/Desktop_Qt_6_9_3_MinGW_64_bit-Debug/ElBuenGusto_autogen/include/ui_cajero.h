/********************************************************************************
** Form generated from reading UI file 'cajero.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAJERO_H
#define UI_CAJERO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
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
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PanelCajero
{
public:
    QHBoxLayout *horizontalLayout_main;
    QFrame *frame_left;
    QVBoxLayout *verticalLayout_left;
    QFrame *frame_header;
    QHBoxLayout *horizontalLayout_header;
    QLabel *label_logo;
    QLabel *label_titulo;
    QSpacerItem *horizontalSpacer_header;
    QLabel *label_hora;
    QFrame *frame_busqueda;
    QHBoxLayout *horizontalLayout_busqueda;
    QLineEdit *lineEdit_buscarCliente;
    QPushButton *pushButton_buscarCliente;
    QPushButton *pushButton_limpiarCliente;
    QFrame *frame_filtros;
    QHBoxLayout *horizontalLayout_filtros;
    QLabel *label_categoria;
    QComboBox *comboBox_categorias;
    QLineEdit *lineEdit_buscarProducto;
    QScrollArea *scrollArea_productos;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_productos;
    QFrame *frame_right;
    QVBoxLayout *verticalLayout_right;
    QGroupBox *groupBox_datosCliente;
    QVBoxLayout *verticalLayout_datosCliente;
    QLabel *label_nombreCliente;
    QLabel *label_telefonoCliente;
    QLabel *label_direccionCliente;
    QLabel *label_emailCliente;
    QGroupBox *groupBox_tipoPedido;
    QVBoxLayout *verticalLayout_tipoPedido;
    QRadioButton *radioButton_inmediato;
    QRadioButton *radioButton_programado;
    QFrame *frame_programacion;
    QHBoxLayout *horizontalLayout_programacion;
    QLabel *label_fecha;
    QDateEdit *dateEdit_fecha;
    QLabel *label_hora1;
    QTimeEdit *timeEdit_hora;
    QGroupBox *groupBox_carrito;
    QVBoxLayout *verticalLayout_carrito;
    QScrollArea *scrollArea_carrito;
    QWidget *scrollAreaWidgetContents_carrito;
    QVBoxLayout *verticalLayout_carritoItems;
    QGroupBox *groupBox_totales;
    QVBoxLayout *verticalLayout_totales;
    QLabel *label_subtotal;
    QLabel *label_delivery;
    QLabel *label_total;
    QPushButton *pushButton_crearPedido;

    void setupUi(QWidget *PanelCajero)
    {
        if (PanelCajero->objectName().isEmpty())
            PanelCajero->setObjectName("PanelCajero");
        PanelCajero->resize(1200, 800);
        PanelCajero->setStyleSheet(QString::fromUtf8("\n"
"   QWidget {\n"
"       background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #8B4513, stop:1 #654321);\n"
"       font-family: 'Segoe UI', Arial, sans-serif;\n"
"   }\n"
"   "));
        horizontalLayout_main = new QHBoxLayout(PanelCajero);
        horizontalLayout_main->setSpacing(10);
        horizontalLayout_main->setObjectName("horizontalLayout_main");
        horizontalLayout_main->setContentsMargins(10, 10, 10, 10);
        frame_left = new QFrame(PanelCajero);
        frame_left->setObjectName("frame_left");
        frame_left->setMaximumSize(QSize(750, 16777215));
        frame_left->setStyleSheet(QString::fromUtf8("background-color: #F5EBD2; border-radius: 10px; margin: 5px;"));
        frame_left->setFrameShape(QFrame::Shape::StyledPanel);
        verticalLayout_left = new QVBoxLayout(frame_left);
        verticalLayout_left->setSpacing(10);
        verticalLayout_left->setObjectName("verticalLayout_left");
        verticalLayout_left->setContentsMargins(15, 15, 15, 15);
        frame_header = new QFrame(frame_left);
        frame_header->setObjectName("frame_header");
        frame_header->setMaximumSize(QSize(16777215, 100));
        frame_header->setStyleSheet(QString::fromUtf8("background-color: rgba(200, 30, 45, 0.1); border-radius: 8px; padding: 8px;"));
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
        label_titulo->setMaximumSize(QSize(16777215, 90));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(18);
        font.setBold(true);
        label_titulo->setFont(font);
        label_titulo->setStyleSheet(QString::fromUtf8("color: rgb(80,50,20);"));

        horizontalLayout_header->addWidget(label_titulo);

        horizontalSpacer_header = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_header->addItem(horizontalSpacer_header);

        label_hora = new QLabel(frame_header);
        label_hora->setObjectName("label_hora");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Segoe UI")});
        font1.setPointSize(12);
        font1.setBold(true);
        label_hora->setFont(font1);
        label_hora->setStyleSheet(QString::fromUtf8("color: rgb(80,50,20);"));
        label_hora->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_header->addWidget(label_hora);


        verticalLayout_left->addWidget(frame_header);

        frame_busqueda = new QFrame(frame_left);
        frame_busqueda->setObjectName("frame_busqueda");
        frame_busqueda->setMaximumSize(QSize(16777215, 100));
        frame_busqueda->setStyleSheet(QString::fromUtf8("background-color: white; border-radius: 8px; padding: 5px;"));
        horizontalLayout_busqueda = new QHBoxLayout(frame_busqueda);
        horizontalLayout_busqueda->setObjectName("horizontalLayout_busqueda");
        lineEdit_buscarCliente = new QLineEdit(frame_busqueda);
        lineEdit_buscarCliente->setObjectName("lineEdit_buscarCliente");
        lineEdit_buscarCliente->setStyleSheet(QString::fromUtf8("QLineEdit { padding: 8px; border: 2px solid #ddd; border-radius: 4px; font-size: 12px; }"));

        horizontalLayout_busqueda->addWidget(lineEdit_buscarCliente);

        pushButton_buscarCliente = new QPushButton(frame_busqueda);
        pushButton_buscarCliente->setObjectName("pushButton_buscarCliente");
        pushButton_buscarCliente->setMaximumSize(QSize(80, 16777215));
        pushButton_buscarCliente->setStyleSheet(QString::fromUtf8("QPushButton { background-color: rgb(200, 30, 45); color: white; border: none; padding: 8px; border-radius: 4px; font-weight: bold; font-size: 11px; }\n"
"QPushButton:hover { background-color: rgb(180, 25, 40); }"));

        horizontalLayout_busqueda->addWidget(pushButton_buscarCliente);

        pushButton_limpiarCliente = new QPushButton(frame_busqueda);
        pushButton_limpiarCliente->setObjectName("pushButton_limpiarCliente");
        pushButton_limpiarCliente->setMaximumSize(QSize(60, 16777215));
        pushButton_limpiarCliente->setStyleSheet(QString::fromUtf8("QPushButton { background-color: #666; color: white; border: none; padding: 8px; border-radius: 4px; font-weight: bold; font-size: 11px; }\n"
"QPushButton:hover { background-color: #555; }"));

        horizontalLayout_busqueda->addWidget(pushButton_limpiarCliente);


        verticalLayout_left->addWidget(frame_busqueda);

        frame_filtros = new QFrame(frame_left);
        frame_filtros->setObjectName("frame_filtros");
        frame_filtros->setMaximumSize(QSize(16777215, 100));
        frame_filtros->setStyleSheet(QString::fromUtf8("background-color: white; border-radius: 8px; padding: 5px;"));
        horizontalLayout_filtros = new QHBoxLayout(frame_filtros);
        horizontalLayout_filtros->setObjectName("horizontalLayout_filtros");
        label_categoria = new QLabel(frame_filtros);
        label_categoria->setObjectName("label_categoria");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Segoe UI")});
        font2.setPointSize(11);
        font2.setBold(true);
        label_categoria->setFont(font2);

        horizontalLayout_filtros->addWidget(label_categoria);

        comboBox_categorias = new QComboBox(frame_filtros);
        comboBox_categorias->addItem(QString());
        comboBox_categorias->addItem(QString());
        comboBox_categorias->addItem(QString());
        comboBox_categorias->addItem(QString());
        comboBox_categorias->addItem(QString());
        comboBox_categorias->addItem(QString());
        comboBox_categorias->addItem(QString());
        comboBox_categorias->addItem(QString());
        comboBox_categorias->addItem(QString());
        comboBox_categorias->addItem(QString());
        comboBox_categorias->addItem(QString());
        comboBox_categorias->setObjectName("comboBox_categorias");
        comboBox_categorias->setStyleSheet(QString::fromUtf8("QComboBox { padding: 6px; border: 2px solid #ddd; border-radius: 4px; font-size: 11px; }"));

        horizontalLayout_filtros->addWidget(comboBox_categorias);

        lineEdit_buscarProducto = new QLineEdit(frame_filtros);
        lineEdit_buscarProducto->setObjectName("lineEdit_buscarProducto");
        lineEdit_buscarProducto->setStyleSheet(QString::fromUtf8("QLineEdit { padding: 6px; border: 2px solid #ddd; border-radius: 4px; font-size: 11px; }"));

        horizontalLayout_filtros->addWidget(lineEdit_buscarProducto);


        verticalLayout_left->addWidget(frame_filtros);

        scrollArea_productos = new QScrollArea(frame_left);
        scrollArea_productos->setObjectName("scrollArea_productos");
        scrollArea_productos->setMaximumSize(QSize(16777215, 550));
        scrollArea_productos->setStyleSheet(QString::fromUtf8("QScrollArea { border: none; background-color: transparent; }"));
        scrollArea_productos->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 690, 433));
        verticalLayout_productos = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_productos->setSpacing(8);
        verticalLayout_productos->setObjectName("verticalLayout_productos");
        scrollArea_productos->setWidget(scrollAreaWidgetContents);

        verticalLayout_left->addWidget(scrollArea_productos);


        horizontalLayout_main->addWidget(frame_left);

        frame_right = new QFrame(PanelCajero);
        frame_right->setObjectName("frame_right");
        frame_right->setMaximumSize(QSize(430, 16777215));
        frame_right->setStyleSheet(QString::fromUtf8("background-color: #F5EBD2; border-radius: 10px; margin: 5px;"));
        frame_right->setFrameShape(QFrame::Shape::StyledPanel);
        verticalLayout_right = new QVBoxLayout(frame_right);
        verticalLayout_right->setSpacing(10);
        verticalLayout_right->setObjectName("verticalLayout_right");
        verticalLayout_right->setContentsMargins(15, 15, 15, 15);
        groupBox_datosCliente = new QGroupBox(frame_right);
        groupBox_datosCliente->setObjectName("groupBox_datosCliente");
        groupBox_datosCliente->setMaximumSize(QSize(16777215, 150));
        groupBox_datosCliente->setFont(font1);
        groupBox_datosCliente->setStyleSheet(QString::fromUtf8("\n"
"         QGroupBox {\n"
"             background-color: white;\n"
"             border-radius: 8px;\n"
"             padding-top: 15px;\n"
"             color: rgb(80,50,20);\n"
"         }\n"
"         QGroupBox::title {\n"
"             subcontrol-origin: margin;\n"
"             left: 10px;\n"
"             padding: 0 8px 0 8px;\n"
"         }\n"
"         "));
        verticalLayout_datosCliente = new QVBoxLayout(groupBox_datosCliente);
        verticalLayout_datosCliente->setObjectName("verticalLayout_datosCliente");
        label_nombreCliente = new QLabel(groupBox_datosCliente);
        label_nombreCliente->setObjectName("label_nombreCliente");
        label_nombreCliente->setFont(font2);
        label_nombreCliente->setStyleSheet(QString::fromUtf8("color: rgb(200, 30, 45);"));

        verticalLayout_datosCliente->addWidget(label_nombreCliente);

        label_telefonoCliente = new QLabel(groupBox_datosCliente);
        label_telefonoCliente->setObjectName("label_telefonoCliente");
        label_telefonoCliente->setMaximumSize(QSize(16777215, 25));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Segoe UI")});
        font3.setPointSize(10);
        font3.setBold(false);
        label_telefonoCliente->setFont(font3);

        verticalLayout_datosCliente->addWidget(label_telefonoCliente);

        label_direccionCliente = new QLabel(groupBox_datosCliente);
        label_direccionCliente->setObjectName("label_direccionCliente");
        label_direccionCliente->setMaximumSize(QSize(16777215, 25));
        label_direccionCliente->setFont(font3);
        label_direccionCliente->setWordWrap(true);

        verticalLayout_datosCliente->addWidget(label_direccionCliente);

        label_emailCliente = new QLabel(groupBox_datosCliente);
        label_emailCliente->setObjectName("label_emailCliente");
        label_emailCliente->setMaximumSize(QSize(16777215, 25));
        label_emailCliente->setFont(font3);

        verticalLayout_datosCliente->addWidget(label_emailCliente);


        verticalLayout_right->addWidget(groupBox_datosCliente);

        groupBox_tipoPedido = new QGroupBox(frame_right);
        groupBox_tipoPedido->setObjectName("groupBox_tipoPedido");
        groupBox_tipoPedido->setMaximumSize(QSize(16777215, 380));
        groupBox_tipoPedido->setFont(font1);
        groupBox_tipoPedido->setStyleSheet(QString::fromUtf8("\n"
"        QGroupBox {\n"
"            background-color: white;\n"
"            border-radius: 8px;\n"
"            padding-top: 15px;\n"
"            color: rgb(80,50,20);\n"
"        }\n"
"        QGroupBox::title {\n"
"            subcontrol-origin: margin;\n"
"            left: 10px;\n"
"            padding: 0 8px 0 8px;\n"
"        }\n"
"        QLabel {\n"
"            color: rgb(80,50,20);\n"
"            font-size: 10pt;\n"
"        }\n"
"        "));
        verticalLayout_tipoPedido = new QVBoxLayout(groupBox_tipoPedido);
        verticalLayout_tipoPedido->setObjectName("verticalLayout_tipoPedido");
        radioButton_inmediato = new QRadioButton(groupBox_tipoPedido);
        radioButton_inmediato->setObjectName("radioButton_inmediato");
        radioButton_inmediato->setMaximumSize(QSize(16777215, 25));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Segoe UI")});
        font4.setPointSize(11);
        radioButton_inmediato->setFont(font4);
        radioButton_inmediato->setChecked(true);

        verticalLayout_tipoPedido->addWidget(radioButton_inmediato);

        radioButton_programado = new QRadioButton(groupBox_tipoPedido);
        radioButton_programado->setObjectName("radioButton_programado");
        radioButton_programado->setMaximumSize(QSize(16777215, 25));
        radioButton_programado->setFont(font4);

        verticalLayout_tipoPedido->addWidget(radioButton_programado);

        frame_programacion = new QFrame(groupBox_tipoPedido);
        frame_programacion->setObjectName("frame_programacion");
        frame_programacion->setEnabled(false);
        frame_programacion->setMaximumSize(QSize(16777215, 80));
        horizontalLayout_programacion = new QHBoxLayout(frame_programacion);
        horizontalLayout_programacion->setSpacing(10);
        horizontalLayout_programacion->setObjectName("horizontalLayout_programacion");
        label_fecha = new QLabel(frame_programacion);
        label_fecha->setObjectName("label_fecha");

        horizontalLayout_programacion->addWidget(label_fecha);

        dateEdit_fecha = new QDateEdit(frame_programacion);
        dateEdit_fecha->setObjectName("dateEdit_fecha");
        dateEdit_fecha->setStyleSheet(QString::fromUtf8("\n"
"                QDateEdit {\n"
"                    padding: 4px;\n"
"                    border: 2px solid #ddd;\n"
"                    border-radius: 4px;\n"
"                    font-size: 10pt;\n"
"                    background-color: #fff;\n"
"                }\n"
"                "));
        dateEdit_fecha->setCalendarPopup(true);

        horizontalLayout_programacion->addWidget(dateEdit_fecha);

        label_hora1 = new QLabel(frame_programacion);
        label_hora1->setObjectName("label_hora1");

        horizontalLayout_programacion->addWidget(label_hora1);

        timeEdit_hora = new QTimeEdit(frame_programacion);
        timeEdit_hora->setObjectName("timeEdit_hora");
        timeEdit_hora->setStyleSheet(QString::fromUtf8("\n"
"                QTimeEdit {\n"
"                    padding: 4px;\n"
"                    border: 2px solid #ddd;\n"
"                    border-radius: 4px;\n"
"                    font-size: 10pt;\n"
"                    background-color: #fff;\n"
"                }\n"
"                "));

        horizontalLayout_programacion->addWidget(timeEdit_hora);


        verticalLayout_tipoPedido->addWidget(frame_programacion);


        verticalLayout_right->addWidget(groupBox_tipoPedido);

        groupBox_carrito = new QGroupBox(frame_right);
        groupBox_carrito->setObjectName("groupBox_carrito");
        groupBox_carrito->setMaximumSize(QSize(16777215, 400));
        groupBox_carrito->setFont(font1);
        groupBox_carrito->setStyleSheet(QString::fromUtf8("\n"
"         QGroupBox {\n"
"             background-color: white;\n"
"             border-radius: 8px;\n"
"             padding-top: 15px;\n"
"             color: rgb(80,50,20);\n"
"         }\n"
"         QGroupBox::title {\n"
"             subcontrol-origin: margin;\n"
"             left: 10px;\n"
"             padding: 0 8px 0 8px;\n"
"         }\n"
"         "));
        verticalLayout_carrito = new QVBoxLayout(groupBox_carrito);
        verticalLayout_carrito->setObjectName("verticalLayout_carrito");
        scrollArea_carrito = new QScrollArea(groupBox_carrito);
        scrollArea_carrito->setObjectName("scrollArea_carrito");
        scrollArea_carrito->setMaximumSize(QSize(16777215, 400));
        scrollArea_carrito->setStyleSheet(QString::fromUtf8("QScrollArea { border: 1px solid #ddd; border-radius: 6px; background-color: #f9f9f9; }"));
        scrollArea_carrito->setWidgetResizable(true);
        scrollAreaWidgetContents_carrito = new QWidget();
        scrollAreaWidgetContents_carrito->setObjectName("scrollAreaWidgetContents_carrito");
        scrollAreaWidgetContents_carrito->setGeometry(QRect(0, 0, 350, 141));
        verticalLayout_carritoItems = new QVBoxLayout(scrollAreaWidgetContents_carrito);
        verticalLayout_carritoItems->setSpacing(5);
        verticalLayout_carritoItems->setObjectName("verticalLayout_carritoItems");
        scrollArea_carrito->setWidget(scrollAreaWidgetContents_carrito);

        verticalLayout_carrito->addWidget(scrollArea_carrito);


        verticalLayout_right->addWidget(groupBox_carrito);

        groupBox_totales = new QGroupBox(frame_right);
        groupBox_totales->setObjectName("groupBox_totales");
        groupBox_totales->setMaximumSize(QSize(16777215, 130));
        groupBox_totales->setFont(font1);
        groupBox_totales->setStyleSheet(QString::fromUtf8("\n"
"         QGroupBox {\n"
"             background-color: rgba(200, 30, 45, 0.1);\n"
"             border-radius: 8px;\n"
"             padding-top: 15px;\n"
"             color: rgb(80,50,20);\n"
"         }\n"
"         QGroupBox::title {\n"
"             subcontrol-origin: margin;\n"
"             left: 10px;\n"
"             padding: 0 8px 0 8px;\n"
"         }\n"
"         "));
        verticalLayout_totales = new QVBoxLayout(groupBox_totales);
        verticalLayout_totales->setObjectName("verticalLayout_totales");
        label_subtotal = new QLabel(groupBox_totales);
        label_subtotal->setObjectName("label_subtotal");
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Segoe UI")});
        font5.setPointSize(11);
        font5.setBold(false);
        label_subtotal->setFont(font5);

        verticalLayout_totales->addWidget(label_subtotal);

        label_delivery = new QLabel(groupBox_totales);
        label_delivery->setObjectName("label_delivery");
        label_delivery->setFont(font5);

        verticalLayout_totales->addWidget(label_delivery);

        label_total = new QLabel(groupBox_totales);
        label_total->setObjectName("label_total");
        label_total->setMaximumSize(QSize(16777215, 25));
        label_total->setFont(font2);
        label_total->setStyleSheet(QString::fromUtf8("color: rgb(200, 30, 45);"));

        verticalLayout_totales->addWidget(label_total);


        verticalLayout_right->addWidget(groupBox_totales);

        pushButton_crearPedido = new QPushButton(frame_right);
        pushButton_crearPedido->setObjectName("pushButton_crearPedido");
        pushButton_crearPedido->setEnabled(false);
        pushButton_crearPedido->setMinimumSize(QSize(0, 50));
        pushButton_crearPedido->setMaximumSize(QSize(16777215, 40));
        pushButton_crearPedido->setStyleSheet(QString::fromUtf8("QPushButton { background-color: rgb(200, 30, 45); color: white; border: none; padding: 12px; border-radius: 8px; font-size: 16px; font-weight: bold; }\n"
"QPushButton:hover { background-color: rgb(180, 25, 40); }\n"
"QPushButton:disabled { background-color: #ccc; color: #999; }"));

        verticalLayout_right->addWidget(pushButton_crearPedido);


        horizontalLayout_main->addWidget(frame_right);


        retranslateUi(PanelCajero);

        QMetaObject::connectSlotsByName(PanelCajero);
    } // setupUi

    void retranslateUi(QWidget *PanelCajero)
    {
        PanelCajero->setWindowTitle(QCoreApplication::translate("PanelCajero", "Panel Cajero - Rotiser\303\255a El Buen Gusto", nullptr));
        label_logo->setText(QString());
        label_titulo->setText(QCoreApplication::translate("PanelCajero", "Panel del Cajero", nullptr));
        label_hora->setText(QCoreApplication::translate("PanelCajero", "00:00:00", nullptr));
        lineEdit_buscarCliente->setPlaceholderText(QCoreApplication::translate("PanelCajero", "Buscar cliente por nombre o tel\303\251fono...", nullptr));
        pushButton_buscarCliente->setText(QCoreApplication::translate("PanelCajero", "Buscar", nullptr));
        pushButton_limpiarCliente->setText(QCoreApplication::translate("PanelCajero", "Limpiar", nullptr));
        label_categoria->setText(QCoreApplication::translate("PanelCajero", "Categor\303\255a:", nullptr));
        comboBox_categorias->setItemText(0, QCoreApplication::translate("PanelCajero", "Todas las categor\303\255as", nullptr));
        comboBox_categorias->setItemText(1, QCoreApplication::translate("PanelCajero", "Minutas", nullptr));
        comboBox_categorias->setItemText(2, QCoreApplication::translate("PanelCajero", "Pastas", nullptr));
        comboBox_categorias->setItemText(3, QCoreApplication::translate("PanelCajero", "Guisos", nullptr));
        comboBox_categorias->setItemText(4, QCoreApplication::translate("PanelCajero", "Tartas", nullptr));
        comboBox_categorias->setItemText(5, QCoreApplication::translate("PanelCajero", "Empanadas", nullptr));
        comboBox_categorias->setItemText(6, QCoreApplication::translate("PanelCajero", "Postres", nullptr));
        comboBox_categorias->setItemText(7, QCoreApplication::translate("PanelCajero", "Bebidas", nullptr));
        comboBox_categorias->setItemText(8, QCoreApplication::translate("PanelCajero", "Embutidos", nullptr));
        comboBox_categorias->setItemText(9, QCoreApplication::translate("PanelCajero", "Comidas R\303\241pidas", nullptr));
        comboBox_categorias->setItemText(10, QCoreApplication::translate("PanelCajero", "Otros", nullptr));

        lineEdit_buscarProducto->setPlaceholderText(QCoreApplication::translate("PanelCajero", "Buscar producto...", nullptr));
        groupBox_datosCliente->setTitle(QCoreApplication::translate("PanelCajero", "Cliente Seleccionado", nullptr));
        label_nombreCliente->setText(QCoreApplication::translate("PanelCajero", "Cliente no seleccionado", nullptr));
        label_telefonoCliente->setText(QCoreApplication::translate("PanelCajero", "Tel\303\251fono: -", nullptr));
        label_direccionCliente->setText(QCoreApplication::translate("PanelCajero", "Direcci\303\263n: -", nullptr));
        label_emailCliente->setText(QCoreApplication::translate("PanelCajero", "Email: -", nullptr));
        groupBox_tipoPedido->setTitle(QCoreApplication::translate("PanelCajero", "Tipo de Pedido", nullptr));
        radioButton_inmediato->setText(QCoreApplication::translate("PanelCajero", "Pedido Inmediato (entrega en horario de atenci\303\263n)", nullptr));
        radioButton_programado->setText(QCoreApplication::translate("PanelCajero", "Pedido Programado", nullptr));
        label_fecha->setText(QCoreApplication::translate("PanelCajero", " Fecha:", nullptr));
        label_hora1->setText(QCoreApplication::translate("PanelCajero", " Hora:", nullptr));
        timeEdit_hora->setDisplayFormat(QCoreApplication::translate("PanelCajero", "HH:mm", nullptr));
        groupBox_carrito->setTitle(QCoreApplication::translate("PanelCajero", "Carrito de Compras", nullptr));
        groupBox_totales->setTitle(QCoreApplication::translate("PanelCajero", "Totales", nullptr));
        label_subtotal->setText(QCoreApplication::translate("PanelCajero", "Subtotal: $0.00", nullptr));
        label_delivery->setText(QCoreApplication::translate("PanelCajero", "Delivery: $0.00", nullptr));
        label_total->setText(QCoreApplication::translate("PanelCajero", "Total: $0.00", nullptr));
        pushButton_crearPedido->setText(QCoreApplication::translate("PanelCajero", "Crear Pedido", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PanelCajero: public Ui_PanelCajero {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAJERO_H
