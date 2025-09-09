/********************************************************************************
** Form generated from reading UI file 'carrito.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CARRITO_H
#define UI_CARRITO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_carrito
{
public:
    QHBoxLayout *horizontalLayout_4;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox;
    QFrame *frame_2;
    QLabel *label;
    QLabel *label_2;
    QFrame *frame_3;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QFrame *frame_4;
    QLabel *label_6;
    QFrame *line;
    QFrame *frame_5;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;

    void setupUi(QWidget *carrito)
    {
        if (carrito->objectName().isEmpty())
            carrito->setObjectName("carrito");
        carrito->resize(649, 388);
        carrito->setStyleSheet(QString::fromUtf8("\n"
"   QWidget {\n"
"       background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #8B4513, stop:1 #654321);\n"
"       font-family: 'Segoe UI', Arial, sans-serif;\n"
"   }\n"
"   "));
        horizontalLayout_4 = new QHBoxLayout(carrito);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        frame = new QFrame(carrito);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName("groupBox");
        groupBox->setStyleSheet(QString::fromUtf8("background-color: #EDE8D0;\n"
";\n"
""));
        frame_2 = new QFrame(groupBox);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(0, 0, 611, 61));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: #C81E2D;"));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        label = new QLabel(frame_2);
        label->setObjectName("label");
        label->setGeometry(QRect(150, 10, 341, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(20);
        label->setFont(font);
        label->setMouseTracking(true);
        label->setStyleSheet(QString::fromUtf8("color:white;"));
        label->setTextFormat(Qt::TextFormat::RichText);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_2 = new QLabel(frame_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 10, 51, 41));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/WhatsApp Image 2025-08-11 at 20.56.21.jpeg")));
        label_2->setScaledContents(true);
        frame_3 = new QFrame(groupBox);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(20, 80, 151, 121));
        frame_3->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border-radius:15px;"));
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        label_3 = new QLabel(frame_3);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 0, 151, 61));
        label_3->setStyleSheet(QString::fromUtf8("border-radius: 5px;"));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/hamburguesa.jpeg")));
        label_3->setScaledContents(true);
        label_4 = new QLabel(frame_3);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 70, 91, 16));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Segoe UI")});
        font1.setPointSize(7);
        label_4->setFont(font1);
        label_5 = new QLabel(frame_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(100, 70, 41, 16));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Segoe UI")});
        font2.setPointSize(8);
        label_5->setFont(font2);
        label_5->setStyleSheet(QString::fromUtf8("background-color:red;\n"
"color:white;\n"
"border-radius:6px;"));
        frame_4 = new QFrame(groupBox);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(479, 60, 131, 501));
        frame_4->setStyleSheet(QString::fromUtf8("background-color:white;"));
        frame_4->setFrameShape(QFrame::Shape::StyledPanel);
        frame_4->setFrameShadow(QFrame::Shadow::Raised);
        label_6 = new QLabel(frame_4);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(30, 10, 71, 21));
        label_6->setStyleSheet(QString::fromUtf8("text-align:center;"));
        label_6->setAlignment(Qt::AlignmentFlag::AlignCenter);
        line = new QFrame(frame_4);
        line->setObjectName("line");
        line->setGeometry(QRect(0, 30, 131, 20));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        frame_5 = new QFrame(groupBox);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(210, 80, 151, 121));
        frame_5->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border-radius:15px;"));
        frame_5->setFrameShape(QFrame::Shape::StyledPanel);
        frame_5->setFrameShadow(QFrame::Shadow::Raised);
        label_7 = new QLabel(frame_5);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(0, 0, 151, 61));
        label_7->setStyleSheet(QString::fromUtf8("border-radius: 5px;"));
        label_7->setPixmap(QPixmap(QString::fromUtf8(":/hamburguesa.jpeg")));
        label_7->setScaledContents(true);
        label_8 = new QLabel(frame_5);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 70, 91, 16));
        label_8->setFont(font1);
        label_9 = new QLabel(frame_5);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(100, 70, 41, 16));
        label_9->setFont(font2);
        label_9->setStyleSheet(QString::fromUtf8("background-color:red;\n"
"color:white;\n"
"border-radius:6px;"));

        horizontalLayout_3->addWidget(groupBox);


        horizontalLayout_4->addWidget(frame);


        retranslateUi(carrito);

        QMetaObject::connectSlotsByName(carrito);
    } // setupUi

    void retranslateUi(QWidget *carrito)
    {
        carrito->setWindowTitle(QCoreApplication::translate("carrito", "Carrito - Rotiser\303\255a El Buen Gusto", nullptr));
        groupBox->setTitle(QString());
        label->setText(QCoreApplication::translate("carrito", "Rotiseria el Buen Gusto", nullptr));
        label_2->setText(QString());
        label_3->setText(QString());
        label_4->setText(QCoreApplication::translate("carrito", "Hamburguesa Triple", nullptr));
        label_5->setText(QCoreApplication::translate("carrito", " $1500", nullptr));
        label_6->setText(QCoreApplication::translate("carrito", "Tu carrito", nullptr));
        label_7->setText(QString());
        label_8->setText(QCoreApplication::translate("carrito", "Hamburguesa Triple", nullptr));
        label_9->setText(QCoreApplication::translate("carrito", " $1500", nullptr));
    } // retranslateUi

};

namespace Ui {
    class carrito: public Ui_carrito {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARRITO_H
