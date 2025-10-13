/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_3;
    QFrame *frame_5;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame_6;
    QVBoxLayout *verticalLayout;
    QLineEdit *barraBusqueda;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QFrame *frame_4;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 844);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setStyleSheet(QString::fromUtf8("background-color:rgb(245,235,210);"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(10, 0, 10, 0);
        frame_5 = new QFrame(frame);
        frame_5->setObjectName("frame_5");
        frame_5->setFrameShape(QFrame::Shape::StyledPanel);
        frame_5->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout = new QHBoxLayout(frame_5);
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton = new QPushButton(frame_5);
        pushButton->setObjectName("pushButton");
        pushButton->setBaseSize(QSize(0, 0));
        pushButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton->setAutoFillBackground(false);
        pushButton->setStyleSheet(QString::fromUtf8("background-color:rgb(200,30,45);\n"
"border-radius:15px;\n"
"color:rgb(245,235,210);\n"
"padding: 8;"));
        pushButton->setIconSize(QSize(16, 16));

        horizontalLayout->addWidget(pushButton);


        horizontalLayout_3->addWidget(frame_5);

        horizontalLayout_3->setStretch(0, 1);

        verticalLayout_3->addWidget(frame);

        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName("frame_2");
        frame_2->setStyleSheet(QString::fromUtf8("background-color:rgb(200,30,45);"));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        frame_6 = new QFrame(frame_2);
        frame_6->setObjectName("frame_6");
        frame_6->setFrameShape(QFrame::Shape::StyledPanel);
        frame_6->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout = new QVBoxLayout(frame_6);
        verticalLayout->setObjectName("verticalLayout");
        barraBusqueda = new QLineEdit(frame_6);
        barraBusqueda->setObjectName("barraBusqueda");
        barraBusqueda->setStyleSheet(QString::fromUtf8("background-color:rgb(245,235,210\n"
");\n"
"border-radius: 15px;\n"
"padding: 10 5;\n"
"margin: 0 10;"));

        verticalLayout->addWidget(barraBusqueda);

        scrollArea = new QScrollArea(frame_6);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 758, 631));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        verticalLayout_2->addWidget(frame_6);

        frame_3 = new QFrame(frame_2);
        frame_3->setObjectName("frame_3");
        frame_3->setStyleSheet(QString::fromUtf8("background-color:rgb(245,235,210);\n"
"border-radius:10px;"));
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_3);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        pushButton_2 = new QPushButton(frame_3);
        pushButton_2->setObjectName("pushButton_2");
        QFont font;
        font.setBold(true);
        pushButton_2->setFont(font);
        pushButton_2->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color:rgb(200,30,50);\n"
"border-radius:5px;\n"
"color:rgb(245,235,210);\n"
"padding:10 0;"));

        horizontalLayout_2->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(frame_3);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setFont(font);
        pushButton_3->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color:rgb(200,30,50);\n"
"border-radius:5px;color:rgb(245,235,210);\n"
"padding:10 0;"));

        horizontalLayout_2->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(frame_3);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setFont(font);
        pushButton_4->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_4->setStyleSheet(QString::fromUtf8("background-color:rgb(80,50,20);\n"
"border-radius:5px;color:rgb(245,235,210);\n"
"padding:10 0;"));

        horizontalLayout_2->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(frame_3);
        pushButton_5->setObjectName("pushButton_5");
        QFont font1;
        font1.setPointSize(9);
        font1.setBold(true);
        pushButton_5->setFont(font1);
        pushButton_5->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_5->setStyleSheet(QString::fromUtf8("background-color:rgb(80,50,20);\n"
"border-radius:5px;\n"
"color:rgb(245,235,210);\n"
"padding:10 0;"));

        horizontalLayout_2->addWidget(pushButton_5);


        verticalLayout_2->addWidget(frame_3);


        verticalLayout_3->addWidget(frame_2);

        frame_4 = new QFrame(centralwidget);
        frame_4->setObjectName("frame_4");
        frame_4->setStyleSheet(QString::fromUtf8("background-color:rgb(80,50,20);"));
        frame_4->setFrameShape(QFrame::Shape::StyledPanel);
        frame_4->setFrameShadow(QFrame::Shadow::Raised);

        verticalLayout_3->addWidget(frame_4);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        barraBusqueda->setPlaceholderText(QCoreApplication::translate("MainWindow", "\302\277Qu\303\251 se te antoja hoy? Ped\303\255 tu plato favorito...", nullptr));
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
