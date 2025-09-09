/********************************************************************************
** Form generated from reading UI file 'sign_up.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGN_UP_H
#define UI_SIGN_UP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sign_up
{
public:
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QFrame *frame_4;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *pushButton_4;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_3;
    QVBoxLayout *verticalLayout_11;
    QFrame *frame_7;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_3;
    QLineEdit *lineEdit_nombre;
    QFrame *frame_6;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_2;
    QLineEdit *lineEdit_email;
    QFrame *frame_8;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_4;
    QLineEdit *lineEdit_telefono;
    QFrame *frame_9;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_7;
    QLineEdit *lineEdit_fecha;
    QFrame *frame_10;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_8;
    QLineEdit *lineEdit_password;
    QPushButton *pushButton_3;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_9;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QFrame *frame_11;
    QVBoxLayout *verticalLayout_10;
    QPushButton *pushButton;
    QFrame *frame_5;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QPushButton *pushButton_2;

    void setupUi(QWidget *sign_up)
    {
        if (sign_up->objectName().isEmpty())
            sign_up->setObjectName("sign_up");
        sign_up->resize(618, 750);
        sign_up->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y0:1, x2:1, y2:1, stop:0 rgba(245, 235, 210, 255), stop:1 rgba(80, 50, 20, 255))"));
        horizontalLayout = new QHBoxLayout(sign_up);
        horizontalLayout->setObjectName("horizontalLayout");
        frame = new QFrame(sign_up);
        frame->setObjectName("frame");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setMinimumSize(QSize(600, 500));
        frame->setMaximumSize(QSize(396, 16777215));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 235, 210);\n"
"border: 2 solid rgb(80, 50, 20);\n"
"border-radius: 20;"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName("verticalLayout");
        frame_4 = new QFrame(frame);
        frame_4->setObjectName("frame_4");
        frame_4->setMaximumSize(QSize(16777215, 200));
        frame_4->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 235, 210);\n"
"border: 0 solid rgb(138, 133, 123);\n"
"border-radius: 0;"));
        frame_4->setFrameShape(QFrame::Shape::StyledPanel);
        frame_4->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_7 = new QVBoxLayout(frame_4);
        verticalLayout_7->setObjectName("verticalLayout_7");
        label_5 = new QLabel(frame_4);
        label_5->setObjectName("label_5");
        label_5->setMinimumSize(QSize(0, 0));
        label_5->setMaximumSize(QSize(100, 100));
        label_5->setPixmap(QPixmap(QString::fromUtf8(":/fondo2.jpg")));
        label_5->setScaledContents(true);

        verticalLayout_7->addWidget(label_5, 0, Qt::AlignmentFlag::AlignHCenter);

        label_6 = new QLabel(frame_4);
        label_6->setObjectName("label_6");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(18);
        font.setBold(true);
        label_6->setFont(font);
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(80,50,20);\n"
""));

        verticalLayout_7->addWidget(label_6, 0, Qt::AlignmentFlag::AlignHCenter);

        pushButton_4 = new QPushButton(frame_4);
        pushButton_4->setObjectName("pushButton_4");
        sizePolicy1.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setPointSize(10);
        font1.setBold(true);
        pushButton_4->setFont(font1);
        pushButton_4->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 235, 210);\n"
"color: rgba(80,50,20,0.50);\n"
"border: 0 solid rgb(80, 50, 20);\n"
"border-radius: 0;"));

        verticalLayout_7->addWidget(pushButton_4, 0, Qt::AlignmentFlag::AlignHCenter);


        verticalLayout->addWidget(frame_4);

        scrollArea = new QScrollArea(frame);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 235, 210);\n"
"border: 0 solid rgb(138, 133, 123);\n"
"border-radius: 0;"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName("scrollAreaWidgetContents_3");
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 561, 693));
        verticalLayout_11 = new QVBoxLayout(scrollAreaWidgetContents_3);
        verticalLayout_11->setObjectName("verticalLayout_11");
        frame_7 = new QFrame(scrollAreaWidgetContents_3);
        frame_7->setObjectName("frame_7");
        frame_7->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 235, 210);\n"
"border: 0 solid rgb(138, 133, 123);\n"
"border-radius: 0;"));
        frame_7->setFrameShape(QFrame::Shape::StyledPanel);
        frame_7->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_5 = new QVBoxLayout(frame_7);
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_3 = new QLabel(frame_7);
        label_3->setObjectName("label_3");
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial")});
        font2.setPointSize(12);
        font2.setBold(true);
        label_3->setFont(font2);
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(80,50,20);\n"
""));

        verticalLayout_5->addWidget(label_3, 0, Qt::AlignmentFlag::AlignLeft);

        lineEdit_nombre = new QLineEdit(frame_7);
        lineEdit_nombre->setObjectName("lineEdit_nombre");
        lineEdit_nombre->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border: 2 solid rgba(0, 0, 0,0.50);\n"
"border-radius: 20;\n"
"border-radius: 10;\n"
"padding: 10;"));
        lineEdit_nombre->setEchoMode(QLineEdit::EchoMode::Normal);

        verticalLayout_5->addWidget(lineEdit_nombre);


        verticalLayout_11->addWidget(frame_7);

        frame_6 = new QFrame(scrollAreaWidgetContents_3);
        frame_6->setObjectName("frame_6");
        frame_6->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 235, 210);\n"
"border: 0 solid rgb(138, 133, 123);\n"
"border-radius: 0;"));
        frame_6->setFrameShape(QFrame::Shape::StyledPanel);
        frame_6->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_4 = new QVBoxLayout(frame_6);
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_2 = new QLabel(frame_6);
        label_2->setObjectName("label_2");
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setFont(font2);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(80,50,20);\n"
""));

        verticalLayout_4->addWidget(label_2, 0, Qt::AlignmentFlag::AlignLeft);

        lineEdit_email = new QLineEdit(frame_6);
        lineEdit_email->setObjectName("lineEdit_email");
        lineEdit_email->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border: 2 solid rgba(0, 0, 0,0.50);\n"
"border-radius: 20;\n"
"border-radius: 10;\n"
"padding: 10;"));
        lineEdit_email->setEchoMode(QLineEdit::EchoMode::Normal);

        verticalLayout_4->addWidget(lineEdit_email);


        verticalLayout_11->addWidget(frame_6);

        frame_8 = new QFrame(scrollAreaWidgetContents_3);
        frame_8->setObjectName("frame_8");
        frame_8->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 235, 210);\n"
"border: 0 solid rgb(138, 133, 123);\n"
"border-radius: 0;"));
        frame_8->setFrameShape(QFrame::Shape::StyledPanel);
        frame_8->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_6 = new QVBoxLayout(frame_8);
        verticalLayout_6->setObjectName("verticalLayout_6");
        label_4 = new QLabel(frame_8);
        label_4->setObjectName("label_4");
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);
        label_4->setFont(font2);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(80,50,20);\n"
""));

        verticalLayout_6->addWidget(label_4, 0, Qt::AlignmentFlag::AlignLeft);

        lineEdit_telefono = new QLineEdit(frame_8);
        lineEdit_telefono->setObjectName("lineEdit_telefono");
        lineEdit_telefono->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border: 2 solid rgba(0, 0, 0,0.50);\n"
"border-radius: 20;\n"
"border-radius: 10;\n"
"padding: 10;"));
        lineEdit_telefono->setEchoMode(QLineEdit::EchoMode::Normal);

        verticalLayout_6->addWidget(lineEdit_telefono);


        verticalLayout_11->addWidget(frame_8);

        frame_9 = new QFrame(scrollAreaWidgetContents_3);
        frame_9->setObjectName("frame_9");
        frame_9->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 235, 210);\n"
"border: 0 solid rgb(138, 133, 123);\n"
"border-radius: 0;"));
        frame_9->setFrameShape(QFrame::Shape::StyledPanel);
        frame_9->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_8 = new QVBoxLayout(frame_9);
        verticalLayout_8->setObjectName("verticalLayout_8");
        label_7 = new QLabel(frame_9);
        label_7->setObjectName("label_7");
        sizePolicy1.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy1);
        label_7->setFont(font2);
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(80,50,20);\n"
""));

        verticalLayout_8->addWidget(label_7, 0, Qt::AlignmentFlag::AlignLeft);

        lineEdit_fecha = new QLineEdit(frame_9);
        lineEdit_fecha->setObjectName("lineEdit_fecha");
        lineEdit_fecha->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border: 2 solid rgba(0, 0, 0,0.50);\n"
"border-radius: 20;\n"
"border-radius: 10;\n"
"padding: 10;"));
        lineEdit_fecha->setEchoMode(QLineEdit::EchoMode::Normal);

        verticalLayout_8->addWidget(lineEdit_fecha);


        verticalLayout_11->addWidget(frame_9);

        frame_10 = new QFrame(scrollAreaWidgetContents_3);
        frame_10->setObjectName("frame_10");
        frame_10->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 235, 210);\n"
"border: 0 solid rgb(138, 133, 123);\n"
"border-radius: 0;"));
        frame_10->setFrameShape(QFrame::Shape::StyledPanel);
        frame_10->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_10);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_8 = new QLabel(frame_10);
        label_8->setObjectName("label_8");
        sizePolicy1.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy1);
        label_8->setFont(font2);
        label_8->setStyleSheet(QString::fromUtf8("color: rgb(80,50,20);\n"
""));

        verticalLayout_2->addWidget(label_8);

        lineEdit_password = new QLineEdit(frame_10);
        lineEdit_password->setObjectName("lineEdit_password");
        lineEdit_password->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border: 2 solid rgba(0, 0, 0,0.50);\n"
"border-radius: 20;\n"
"border-radius: 10;\n"
"padding: 10;"));
        lineEdit_password->setEchoMode(QLineEdit::EchoMode::Password);

        verticalLayout_2->addWidget(lineEdit_password);

        pushButton_3 = new QPushButton(frame_10);
        pushButton_3->setObjectName("pushButton_3");
        sizePolicy1.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy1);
        pushButton_3->setFont(font1);
        pushButton_3->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 235, 210);\n"
"color: rgba(80,50,20,0.50);\n"
"border: 0 solid rgb(80, 50, 20);\n"
"border-radius: 0;"));

        verticalLayout_2->addWidget(pushButton_3);


        verticalLayout_11->addWidget(frame_10);

        frame_2 = new QFrame(scrollAreaWidgetContents_3);
        frame_2->setObjectName("frame_2");
        frame_2->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 235, 210);\n"
"border: 0 solid rgb(138, 133, 123);\n"
"border-radius: 0;"));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_9 = new QVBoxLayout(frame_2);
        verticalLayout_9->setObjectName("verticalLayout_9");
        checkBox = new QCheckBox(frame_2);
        checkBox->setObjectName("checkBox");

        verticalLayout_9->addWidget(checkBox);

        checkBox_2 = new QCheckBox(frame_2);
        checkBox_2->setObjectName("checkBox_2");

        verticalLayout_9->addWidget(checkBox_2);


        verticalLayout_11->addWidget(frame_2);

        frame_11 = new QFrame(scrollAreaWidgetContents_3);
        frame_11->setObjectName("frame_11");
        frame_11->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 235, 210);\n"
"border: 0 solid rgb(138, 133, 123);\n"
"border-radius: 0;"));
        frame_11->setFrameShape(QFrame::Shape::StyledPanel);
        frame_11->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_10 = new QVBoxLayout(frame_11);
        verticalLayout_10->setObjectName("verticalLayout_10");
        pushButton = new QPushButton(frame_11);
        pushButton->setObjectName("pushButton");
        pushButton->setFont(font2);
        pushButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        verticalLayout_10->addWidget(pushButton);


        verticalLayout_11->addWidget(frame_11);

        frame_5 = new QFrame(scrollAreaWidgetContents_3);
        frame_5->setObjectName("frame_5");
        frame_5->setStyleSheet(QString::fromUtf8("background-color: rgba(191, 185, 171,0.50);\n"
"border: 2 solid rgb(138, 133, 123);\n"
"border-radius: 20"));
        frame_5->setFrameShape(QFrame::Shape::StyledPanel);
        frame_5->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_3 = new QVBoxLayout(frame_5);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label = new QLabel(frame_5);
        label->setObjectName("label");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setFont(font2);
        label->setStyleSheet(QString::fromUtf8("background-color: rgba(191, 185, 171,0);\n"
"color: rgba(80,50,20,0.50);\n"
"border: 0 solid rgba(80, 50, 20,0);\n"
"border-radius: 0;"));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(label, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);

        pushButton_2 = new QPushButton(frame_5);
        pushButton_2->setObjectName("pushButton_2");
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);
        pushButton_2->setFont(font2);
        pushButton_2->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 235, 210);\n"
"color: rgb(200,30,45);\n"
"border: 2 solid rgb(200, 30, 45);\n"
"border-radius: 10;\n"
"padding: 10;"));

        verticalLayout_3->addWidget(pushButton_2, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);


        verticalLayout_11->addWidget(frame_5);

        scrollArea->setWidget(scrollAreaWidgetContents_3);

        verticalLayout->addWidget(scrollArea);


        horizontalLayout->addWidget(frame);


        retranslateUi(sign_up);

        QMetaObject::connectSlotsByName(sign_up);
    } // setupUi

    void retranslateUi(QWidget *sign_up)
    {
        sign_up->setWindowTitle(QCoreApplication::translate("sign_up", "Form", nullptr));
        label_5->setText(QString());
        label_6->setText(QCoreApplication::translate("sign_up", "El buen gusto", nullptr));
        pushButton_4->setText(QCoreApplication::translate("sign_up", "Rotiser\303\255a - Comida casera", nullptr));
        label_3->setText(QCoreApplication::translate("sign_up", "Nombre*", nullptr));
        lineEdit_nombre->setText(QString());
        lineEdit_nombre->setPlaceholderText(QCoreApplication::translate("sign_up", "Tu nombre", nullptr));
        label_2->setText(QCoreApplication::translate("sign_up", "Email*", nullptr));
        lineEdit_email->setText(QString());
        lineEdit_email->setPlaceholderText(QCoreApplication::translate("sign_up", "tu@email.com", nullptr));
        label_4->setText(QCoreApplication::translate("sign_up", "Telefono*", nullptr));
        lineEdit_telefono->setText(QString());
        lineEdit_telefono->setPlaceholderText(QCoreApplication::translate("sign_up", "11-1234-5678", nullptr));
        label_7->setText(QCoreApplication::translate("sign_up", "Fecha de nacimiento*", nullptr));
        lineEdit_fecha->setText(QString());
        lineEdit_fecha->setPlaceholderText(QCoreApplication::translate("sign_up", "dd/mm/aaaa", nullptr));
        label_8->setText(QCoreApplication::translate("sign_up", "Contrase\303\261a*", nullptr));
        lineEdit_password->setText(QString());
        lineEdit_password->setPlaceholderText(QCoreApplication::translate("sign_up", "Crea una contrase\303\261a", nullptr));
        pushButton_3->setText(QCoreApplication::translate("sign_up", "M\303\255nimo 8 caracteres", nullptr));
        checkBox->setText(QCoreApplication::translate("sign_up", "Acepto los t\303\251rminos y condiciones y la pol\303\255tica de privacidad", nullptr));
        checkBox_2->setText(QCoreApplication::translate("sign_up", "Quiero recibir ofertas especiales y novedades por email", nullptr));
        pushButton->setText(QCoreApplication::translate("sign_up", "Iniciar Sesi\303\263n", nullptr));
        label->setText(QCoreApplication::translate("sign_up", "\302\277No tienes una cuenta?", nullptr));
        pushButton_2->setText(QCoreApplication::translate("sign_up", "Crear cuenta", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sign_up: public Ui_sign_up {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGN_UP_H
