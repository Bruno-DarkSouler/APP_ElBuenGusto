/********************************************************************************
** Form generated from reading UI file 'sign_in.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGN_IN_H
#define UI_SIGN_IN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sign_in
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame_4;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *pushButton_4;
    QFrame *frame_5;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_3;
    QLineEdit *email;
    QFrame *frame_6;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_2;
    QLineEdit *contra;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_5;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QPushButton *pushButton_2;

    void setupUi(QWidget *sign_in)
    {
        if (sign_in->objectName().isEmpty())
            sign_in->setObjectName("sign_in");
        sign_in->resize(671, 624);
        sign_in->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y0:1, x2:1, y2:1, stop:0 rgba(245, 235, 210, 255), stop:1 rgba(80, 50, 20, 255))"));
        verticalLayout = new QVBoxLayout(sign_in);
        verticalLayout->setObjectName("verticalLayout");
        frame = new QFrame(sign_in);
        frame->setObjectName("frame");
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 235, 210);\n"
"border: 2 solid rgb(80, 50, 20);\n"
"border-radius: 20;"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName("verticalLayout_2");
        frame_4 = new QFrame(frame);
        frame_4->setObjectName("frame_4");
        frame_4->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 235, 210);\n"
"border: 0 solid rgb(138, 133, 123);\n"
"border-radius: 0;"));
        frame_4->setFrameShape(QFrame::Shape::StyledPanel);
        frame_4->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_7 = new QVBoxLayout(frame_4);
        verticalLayout_7->setObjectName("verticalLayout_7");
        label_4 = new QLabel(frame_4);
        label_4->setObjectName("label_4");
        label_4->setMinimumSize(QSize(0, 0));
        label_4->setMaximumSize(QSize(100, 100));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/fondo2.jpg")));
        label_4->setScaledContents(true);

        verticalLayout_7->addWidget(label_4, 0, Qt::AlignmentFlag::AlignHCenter);

        label_5 = new QLabel(frame_4);
        label_5->setObjectName("label_5");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(18);
        font.setBold(true);
        label_5->setFont(font);
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(80,50,20);\n"
""));

        verticalLayout_7->addWidget(label_5, 0, Qt::AlignmentFlag::AlignHCenter);

        pushButton_4 = new QPushButton(frame_4);
        pushButton_4->setObjectName("pushButton_4");
        sizePolicy.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy);
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


        verticalLayout_2->addWidget(frame_4);

        frame_5 = new QFrame(frame);
        frame_5->setObjectName("frame_5");
        frame_5->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 235, 210);\n"
"border: 0 solid rgb(138, 133, 123);\n"
"border-radius: 0;"));
        frame_5->setFrameShape(QFrame::Shape::StyledPanel);
        frame_5->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_6 = new QVBoxLayout(frame_5);
        verticalLayout_6->setObjectName("verticalLayout_6");
        label_3 = new QLabel(frame_5);
        label_3->setObjectName("label_3");
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial")});
        font2.setPointSize(12);
        font2.setBold(true);
        label_3->setFont(font2);
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(80,50,20);\n"
""));

        verticalLayout_6->addWidget(label_3);

        email = new QLineEdit(frame_5);
        email->setObjectName("email");
        email->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border: 2 solid rgba(0, 0, 0,0.50);\n"
"border-radius: 20;\n"
"border-radius: 10;\n"
"padding: 10;"));

        verticalLayout_6->addWidget(email);


        verticalLayout_2->addWidget(frame_5);

        frame_6 = new QFrame(frame);
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
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setFont(font2);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(80,50,20);\n"
""));

        verticalLayout_4->addWidget(label_2, 0, Qt::AlignmentFlag::AlignLeft);

        contra = new QLineEdit(frame_6);
        contra->setObjectName("contra");
        contra->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border: 2 solid rgba(0, 0, 0,0.50);\n"
"border-radius: 20;\n"
"border-radius: 10;\n"
"padding: 10;"));
        contra->setEchoMode(QLineEdit::EchoMode::Password);

        verticalLayout_4->addWidget(contra);


        verticalLayout_2->addWidget(frame_6);

        frame_2 = new QFrame(frame);
        frame_2->setObjectName("frame_2");
        frame_2->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 235, 210);\n"
"border: 0 solid rgb(138, 133, 123);\n"
"border-radius: 0;"));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_5 = new QVBoxLayout(frame_2);
        verticalLayout_5->setObjectName("verticalLayout_5");
        pushButton = new QPushButton(frame_2);
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

        verticalLayout_5->addWidget(pushButton);

        pushButton_3 = new QPushButton(frame_2);
        pushButton_3->setObjectName("pushButton_3");
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);
        pushButton_3->setFont(font1);
        pushButton_3->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 235, 210);\n"
"color: rgba(80,50,20,0.50);\n"
"border: 0 solid rgb(80, 50, 20);\n"
"border-radius: 0;"));

        verticalLayout_5->addWidget(pushButton_3, 0, Qt::AlignmentFlag::AlignHCenter);


        verticalLayout_2->addWidget(frame_2);

        frame_3 = new QFrame(frame);
        frame_3->setObjectName("frame_3");
        frame_3->setStyleSheet(QString::fromUtf8("background-color: rgba(191, 185, 171,0.50);\n"
"border: 2 solid rgb(138, 133, 123);\n"
"border-radius: 20"));
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_3 = new QVBoxLayout(frame_3);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label = new QLabel(frame_3);
        label->setObjectName("label");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setFont(font2);
        label->setStyleSheet(QString::fromUtf8("background-color: rgba(191, 185, 171,0);\n"
"color: rgba(80,50,20,0.50);\n"
"border: 0 solid rgba(80, 50, 20,0);\n"
"border-radius: 0;"));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(label, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);

        pushButton_2 = new QPushButton(frame_3);
        pushButton_2->setObjectName("pushButton_2");
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);
        pushButton_2->setFont(font2);
        pushButton_2->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 235, 210);\n"
"color: rgb(200,30,45);\n"
"border: 2 solid rgb(200, 30, 45);\n"
"border-radius: 10;\n"
"padding: 10;"));

        verticalLayout_3->addWidget(pushButton_2, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);


        verticalLayout_2->addWidget(frame_3);


        verticalLayout->addWidget(frame);


        retranslateUi(sign_in);

        QMetaObject::connectSlotsByName(sign_in);
    } // setupUi

    void retranslateUi(QWidget *sign_in)
    {
        sign_in->setWindowTitle(QCoreApplication::translate("sign_in", "Form", nullptr));
        label_4->setText(QString());
        label_5->setText(QCoreApplication::translate("sign_in", "El buen gusto", nullptr));
        pushButton_4->setText(QCoreApplication::translate("sign_in", "Rotiser\303\255a - Comida casera", nullptr));
        label_3->setText(QCoreApplication::translate("sign_in", "Email", nullptr));
        email->setText(QString());
        email->setPlaceholderText(QCoreApplication::translate("sign_in", "Ingresa tu email", nullptr));
        label_2->setText(QCoreApplication::translate("sign_in", "Contrase\303\261a", nullptr));
        contra->setText(QString());
        contra->setPlaceholderText(QCoreApplication::translate("sign_in", "Ingresa tu contrase\303\261a", nullptr));
        pushButton->setText(QCoreApplication::translate("sign_in", "Iniciar Sesi\303\263n", nullptr));
        pushButton_3->setText(QCoreApplication::translate("sign_in", "\302\277Olvidaste tu contrase\303\261a?", nullptr));
        label->setText(QCoreApplication::translate("sign_in", "\302\277No tienes una cuenta?", nullptr));
        pushButton_2->setText(QCoreApplication::translate("sign_in", "Crear cuenta", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sign_in: public Ui_sign_in {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGN_IN_H
