/********************************************************************************
** Form generated from reading UI file 'perfil.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PERFIL_H
#define UI_PERFIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_perfil
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QLabel *label_2;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_6;
    QFrame *frame_5;
    QFormLayout *formLayout;
    QFrame *frame_8;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_nombre;
    QLabel *label_login;
    QLabel *label_vip;
    QFrame *frame_7;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_foto;
    QPushButton *pushButton_foto;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_7;
    QLineEdit *lineEdit_nombre;
    QFrame *frame_4;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_8;
    QLineEdit *lineEdit_email;
    QFrame *frame_6;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_9;
    QLineEdit *lineEdit_telefono;
    QFrame *frame_9;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_10;
    QLineEdit *lineEdit_nacimiento;
    QFrame *frame_10;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_11;
    QLineEdit *lineEdit_direccion;

    void setupUi(QWidget *perfil)
    {
        if (perfil->objectName().isEmpty())
            perfil->setObjectName("perfil");
        perfil->resize(671, 600);
        perfil->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setPointSize(9);
        perfil->setFont(font);
        perfil->setStyleSheet(QString::fromUtf8("background-color: rgb(245,235,210);"));
        verticalLayout = new QVBoxLayout(perfil);
        verticalLayout->setObjectName("verticalLayout");
        scrollArea = new QScrollArea(perfil);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setStyleSheet(QString::fromUtf8("border: none;"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, -72, 636, 654));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setObjectName("verticalLayout_2");
        frame = new QFrame(scrollAreaWidgetContents);
        frame->setObjectName("frame");
        frame->setMaximumSize(QSize(16777215, 100));
        QFont font1;
        font1.setPointSize(14);
        frame->setFont(font1);
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(200, 35, 40);\n"
"color: rgb(255, 255, 255);"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_3 = new QVBoxLayout(frame);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label = new QLabel(frame);
        label->setObjectName("label");
        QFont font2;
        font2.setPointSize(20);
        label->setFont(font2);

        verticalLayout_3->addWidget(label);

        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(245,235,210);"));

        verticalLayout_3->addWidget(label_2);


        verticalLayout_2->addWidget(frame);

        frame_2 = new QFrame(scrollAreaWidgetContents);
        frame_2->setObjectName("frame_2");
        frame_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255,255,255);"));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_6 = new QVBoxLayout(frame_2);
        verticalLayout_6->setObjectName("verticalLayout_6");
        frame_5 = new QFrame(frame_2);
        frame_5->setObjectName("frame_5");
        frame_5->setStyleSheet(QString::fromUtf8(""));
        frame_5->setFrameShape(QFrame::Shape::StyledPanel);
        frame_5->setFrameShadow(QFrame::Shadow::Raised);
        formLayout = new QFormLayout(frame_5);
        formLayout->setObjectName("formLayout");
        frame_8 = new QFrame(frame_5);
        frame_8->setObjectName("frame_8");
        frame_8->setFrameShape(QFrame::Shape::StyledPanel);
        frame_8->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_4 = new QVBoxLayout(frame_8);
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_nombre = new QLabel(frame_8);
        label_nombre->setObjectName("label_nombre");
        label_nombre->setStyleSheet(QString::fromUtf8("color: rgb(80,50,20);"));

        verticalLayout_4->addWidget(label_nombre);

        label_login = new QLabel(frame_8);
        label_login->setObjectName("label_login");
        label_login->setStyleSheet(QString::fromUtf8("color: rgb(70,85,90);"));

        verticalLayout_4->addWidget(label_login);

        label_vip = new QLabel(frame_8);
        label_vip->setObjectName("label_vip");
        label_vip->setStyleSheet(QString::fromUtf8("color: rgb(200,30,45);"));

        verticalLayout_4->addWidget(label_vip);


        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, frame_8);

        frame_7 = new QFrame(frame_5);
        frame_7->setObjectName("frame_7");
        frame_7->setFrameShape(QFrame::Shape::StyledPanel);
        frame_7->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_5 = new QVBoxLayout(frame_7);
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_foto = new QLabel(frame_7);
        label_foto->setObjectName("label_foto");

        verticalLayout_5->addWidget(label_foto);

        pushButton_foto = new QPushButton(frame_7);
        pushButton_foto->setObjectName("pushButton_foto");
        pushButton_foto->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(200, 30, 45);\n"
"	color: rgb(255,255,255);\n"
"	border-radius: 10;\n"
"	padding: 10;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: rgb(171,17,27);\n"
"	color: rgb(255,255,255);\n"
"	box-shadow: 0 100 200 rgba(0, 0, 0, 0.3);\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgb(124,10,25);\n"
"}"));

        verticalLayout_5->addWidget(pushButton_foto);


        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, frame_7);


        verticalLayout_6->addWidget(frame_5);

        frame_3 = new QFrame(frame_2);
        frame_3->setObjectName("frame_3");
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_7 = new QVBoxLayout(frame_3);
        verticalLayout_7->setObjectName("verticalLayout_7");
        label_7 = new QLabel(frame_3);
        label_7->setObjectName("label_7");

        verticalLayout_7->addWidget(label_7);

        lineEdit_nombre = new QLineEdit(frame_3);
        lineEdit_nombre->setObjectName("lineEdit_nombre");
        lineEdit_nombre->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border: 2 solid rgba(0, 0, 0,0.50);\n"
"border-radius: 10;\n"
"padding: 10;"));

        verticalLayout_7->addWidget(lineEdit_nombre);


        verticalLayout_6->addWidget(frame_3);

        frame_4 = new QFrame(frame_2);
        frame_4->setObjectName("frame_4");
        frame_4->setFrameShape(QFrame::Shape::StyledPanel);
        frame_4->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_8 = new QVBoxLayout(frame_4);
        verticalLayout_8->setObjectName("verticalLayout_8");
        label_8 = new QLabel(frame_4);
        label_8->setObjectName("label_8");

        verticalLayout_8->addWidget(label_8);

        lineEdit_email = new QLineEdit(frame_4);
        lineEdit_email->setObjectName("lineEdit_email");
        lineEdit_email->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border: 2 solid rgba(0, 0, 0,0.50);\n"
"border-radius: 10;\n"
"padding: 10;"));

        verticalLayout_8->addWidget(lineEdit_email);


        verticalLayout_6->addWidget(frame_4);

        frame_6 = new QFrame(frame_2);
        frame_6->setObjectName("frame_6");
        frame_6->setFrameShape(QFrame::Shape::StyledPanel);
        frame_6->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_9 = new QVBoxLayout(frame_6);
        verticalLayout_9->setObjectName("verticalLayout_9");
        label_9 = new QLabel(frame_6);
        label_9->setObjectName("label_9");

        verticalLayout_9->addWidget(label_9);

        lineEdit_telefono = new QLineEdit(frame_6);
        lineEdit_telefono->setObjectName("lineEdit_telefono");
        lineEdit_telefono->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border: 2 solid rgba(0, 0, 0,0.50);\n"
"border-radius: 10;\n"
"padding: 10;"));

        verticalLayout_9->addWidget(lineEdit_telefono);


        verticalLayout_6->addWidget(frame_6);

        frame_9 = new QFrame(frame_2);
        frame_9->setObjectName("frame_9");
        frame_9->setFrameShape(QFrame::Shape::StyledPanel);
        frame_9->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_10 = new QVBoxLayout(frame_9);
        verticalLayout_10->setObjectName("verticalLayout_10");
        label_10 = new QLabel(frame_9);
        label_10->setObjectName("label_10");

        verticalLayout_10->addWidget(label_10);

        lineEdit_nacimiento = new QLineEdit(frame_9);
        lineEdit_nacimiento->setObjectName("lineEdit_nacimiento");
        lineEdit_nacimiento->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border: 2 solid rgba(0, 0, 0,0.50);\n"
"border-radius: 10;\n"
"padding: 10;"));

        verticalLayout_10->addWidget(lineEdit_nacimiento);


        verticalLayout_6->addWidget(frame_9);

        frame_10 = new QFrame(frame_2);
        frame_10->setObjectName("frame_10");
        frame_10->setFrameShape(QFrame::Shape::StyledPanel);
        frame_10->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_11 = new QVBoxLayout(frame_10);
        verticalLayout_11->setObjectName("verticalLayout_11");
        label_11 = new QLabel(frame_10);
        label_11->setObjectName("label_11");

        verticalLayout_11->addWidget(label_11);

        lineEdit_direccion = new QLineEdit(frame_10);
        lineEdit_direccion->setObjectName("lineEdit_direccion");
        lineEdit_direccion->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border: 2 solid rgba(0, 0, 0,0.50);\n"
"border-radius: 10;\n"
"padding: 10;"));

        verticalLayout_11->addWidget(lineEdit_direccion);


        verticalLayout_6->addWidget(frame_10);


        verticalLayout_2->addWidget(frame_2);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        retranslateUi(perfil);

        QMetaObject::connectSlotsByName(perfil);
    } // setupUi

    void retranslateUi(QWidget *perfil)
    {
        perfil->setWindowTitle(QCoreApplication::translate("perfil", "Form", nullptr));
        label->setText(QCoreApplication::translate("perfil", "\360\237\221\244 Mi Perfil", nullptr));
        label_2->setText(QCoreApplication::translate("perfil", "Informaci\303\263n personal y preferenciasl", nullptr));
        label_nombre->setText(QString());
        label_login->setText(QString());
        label_vip->setText(QString());
        label_foto->setText(QString());
        pushButton_foto->setText(QCoreApplication::translate("perfil", "Cargar foto", nullptr));
        label_7->setText(QCoreApplication::translate("perfil", "Nombre Completo *", nullptr));
        lineEdit_nombre->setText(QString());
        label_8->setText(QCoreApplication::translate("perfil", "Email *", nullptr));
        lineEdit_email->setText(QString());
        label_9->setText(QCoreApplication::translate("perfil", "Tel\303\251fono *", nullptr));
        lineEdit_telefono->setText(QString());
        label_10->setText(QCoreApplication::translate("perfil", "Fecha de Nacimiento", nullptr));
        lineEdit_nacimiento->setText(QString());
        label_11->setText(QCoreApplication::translate("perfil", "Direcci\303\263n Principal *", nullptr));
        lineEdit_direccion->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class perfil: public Ui_perfil {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERFIL_H
