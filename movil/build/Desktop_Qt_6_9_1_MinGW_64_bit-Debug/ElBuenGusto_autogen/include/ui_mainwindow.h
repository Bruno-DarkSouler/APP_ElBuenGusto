/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *frame;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *pushButton;
    QFrame *frame_2;
    QLineEdit *lineEdit;
    QLabel *label;
    QFrame *frame_3;
    QLabel *label_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QFrame *frame_4;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(677, 844);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 677, 50));
        frame->setStyleSheet(QString::fromUtf8("background-color:rgb(245,235,210);"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(40, 10, 31, 31));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/WhatsApp Image 2025-08-11 at 20.56.21.jpeg")));
        label_3->setScaledContents(true);
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(70, 10, 201, 16));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        label_4->setFont(font);
        label_4->setStyleSheet(QString::fromUtf8("color:rgb(80,50,20);"));
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(70, 27, 231, 16));
        label_5->setStyleSheet(QString::fromUtf8("color:rgb(200,30,45);"));
        pushButton = new QPushButton(frame);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(470, 10, 31, 31));
        pushButton->setAutoFillBackground(false);
        pushButton->setStyleSheet(QString::fromUtf8("background-color:rgb(200,30,45);\n"
"border-radius:15px;\n"
"color:rgb(245,235,210);"));
        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(-1, 50, 681, 631));
        frame_2->setStyleSheet(QString::fromUtf8("background-color:rgb(200,30,45);"));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        lineEdit = new QLineEdit(frame_2);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(200, 60, 291, 41));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color:rgb(245,235,210\n"
");\n"
"border-radius: 20px;"));
        label = new QLabel(frame_2);
        label->setObjectName("label");
        label->setGeometry(QRect(220, 140, 241, 31));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("color:rgb(245,235,210);"));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        frame_3 = new QFrame(frame_2);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(50, 510, 581, 91));
        frame_3->setStyleSheet(QString::fromUtf8("background-color:rgb(245,235,210);\n"
"border-radius:10px;"));
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        label_2 = new QLabel(frame_3);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(220, 10, 141, 21));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        label_2->setFont(font2);
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        pushButton_2 = new QPushButton(frame_3);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(20, 50, 121, 31));
        QFont font3;
        font3.setBold(true);
        pushButton_2->setFont(font3);
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color:rgb(200,30,50);\n"
"border-radius:5px;\n"
"color:rgb(245,235,210);"));
        pushButton_3 = new QPushButton(frame_3);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(160, 50, 121, 31));
        pushButton_3->setFont(font3);
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color:rgb(200,30,50);\n"
"border-radius:5px;color:rgb(245,235,210);"));
        pushButton_4 = new QPushButton(frame_3);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(300, 50, 121, 31));
        pushButton_4->setFont(font3);
        pushButton_4->setStyleSheet(QString::fromUtf8("background-color:rgb(80,50,20);\n"
"border-radius:5px;color:rgb(245,235,210);"));
        pushButton_5 = new QPushButton(frame_3);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(440, 50, 121, 31));
        QFont font4;
        font4.setPointSize(9);
        font4.setBold(true);
        pushButton_5->setFont(font4);
        pushButton_5->setStyleSheet(QString::fromUtf8("background-color:rgb(80,50,20);\n"
"border-radius:5px;\n"
"color:rgb(245,235,210);"));
        frame_4 = new QFrame(centralwidget);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(0, 680, 681, 171));
        frame_4->setStyleSheet(QString::fromUtf8("background-color:rgb(80,50,20);"));
        frame_4->setFrameShape(QFrame::Shape::StyledPanel);
        frame_4->setFrameShadow(QFrame::Shadow::Raised);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_3->setText(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "Rotiser\303\255a El Buen Gusto", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Los mejores sabores caseros desde 1995", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\302\277Qu\303\251 se te antoja hoy? Ped\303\255 tu plato favorito...", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Nuestras Especialidades", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Acciones r\303\241pidas", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Pedido R\303\241pido", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Programar Pedido", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Pedido R\303\241pido", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Pedido R\303\241pido", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
