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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_carrito
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_10;
    QLabel *label_9;
    QLabel *label_2;
    QFrame *line;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_3;
    QLabel *label_4;
    QFrame *frame_8;
    QHBoxLayout *horizontalLayout_5;
    QFrame *frame_9;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QLabel *label_15;
    QLabel *label_14;
    QFrame *frame_10;
    QLabel *label_16;
    QFrame *frame_5;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_7;
    QLabel *label_8;
    QFrame *frame_6;
    QHBoxLayout *horizontalLayout_3;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QLabel *label_12;
    QLabel *label_11;
    QFrame *frame_7;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_13;
    QLabel *label;

    void setupUi(QWidget *carrito)
    {
        if (carrito->objectName().isEmpty())
            carrito->setObjectName("carrito");
        carrito->resize(358, 720);
        carrito->setMaximumSize(QSize(500, 2000));
        carrito->setStyleSheet(QString::fromUtf8("\n"
"   QWidget {\n"
"       background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #8B4513, stop:1 #654321);\n"
"       font-family: 'Segoe UI', Arial, sans-serif;\n"
"   }\n"
"   "));
        verticalLayout = new QVBoxLayout(carrito);
        verticalLayout->setObjectName("verticalLayout");
        frame = new QFrame(carrito);
        frame->setObjectName("frame");
        frame->setMaximumSize(QSize(340, 1200));
        frame->setStyleSheet(QString::fromUtf8("background-color:beige;"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName("verticalLayout_2");
        frame_2 = new QFrame(frame);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout = new QHBoxLayout(frame_2);
        horizontalLayout->setObjectName("horizontalLayout");
        label_10 = new QLabel(frame_2);
        label_10->setObjectName("label_10");
        label_10->setMaximumSize(QSize(35, 35));
        label_10->setPixmap(QPixmap(QString::fromUtf8(":/logo.png")));
        label_10->setScaledContents(true);

        horizontalLayout->addWidget(label_10);

        label_9 = new QLabel(frame_2);
        label_9->setObjectName("label_9");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);
        label_9->setMaximumSize(QSize(200, 16777215));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(12);
        font.setBold(true);
        label_9->setFont(font);
        label_9->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(80,50,20);\n"
""));
        label_9->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_9->setMargin(6);

        horizontalLayout->addWidget(label_9);

        label_2 = new QLabel(frame_2);
        label_2->setObjectName("label_2");
        label_2->setMaximumSize(QSize(35, 35));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/menu-hamb.png")));
        label_2->setScaledContents(true);

        horizontalLayout->addWidget(label_2);


        verticalLayout_2->addWidget(frame_2);

        line = new QFrame(frame);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_2->addWidget(line);

        groupBox = new QGroupBox(frame);
        groupBox->setObjectName("groupBox");
        groupBox->setMaximumSize(QSize(320, 16777215));
        groupBox->setStyleSheet(QString::fromUtf8("background-color: #EDE8D0;\n"
";\n"
""));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName("verticalLayout_3");
        frame_3 = new QFrame(groupBox);
        frame_3->setObjectName("frame_3");
        frame_3->setMaximumSize(QSize(300, 300));
        frame_3->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border-radius:15px;"));
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_4 = new QVBoxLayout(frame_3);
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_3 = new QLabel(frame_3);
        label_3->setObjectName("label_3");
        label_3->setMaximumSize(QSize(400, 200));
        label_3->setStyleSheet(QString::fromUtf8("border-radius: 5px;"));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/hamburguesa.jpeg")));
        label_3->setScaledContents(true);

        verticalLayout_4->addWidget(label_3);

        label_4 = new QLabel(frame_3);
        label_4->setObjectName("label_4");
        label_4->setMaximumSize(QSize(200, 30));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Segoe UI")});
        font1.setPointSize(14);
        font1.setItalic(false);
        label_4->setFont(font1);

        verticalLayout_4->addWidget(label_4);

        frame_8 = new QFrame(frame_3);
        frame_8->setObjectName("frame_8");
        frame_8->setMaximumSize(QSize(380, 40));
        frame_8->setFrameShape(QFrame::Shape::StyledPanel);
        frame_8->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame_8);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        frame_9 = new QFrame(frame_8);
        frame_9->setObjectName("frame_9");
        frame_9->setMaximumSize(QSize(180, 40));
        frame_9->setFrameShape(QFrame::Shape::StyledPanel);
        frame_9->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_6 = new QHBoxLayout(frame_9);
        horizontalLayout_6->setSpacing(9);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(frame_9);
        label_5->setObjectName("label_5");
        label_5->setMaximumSize(QSize(70, 30));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Segoe UI")});
        font2.setPointSize(14);
        label_5->setFont(font2);
        label_5->setStyleSheet(QString::fromUtf8("background-color:red;\n"
"color:white;\n"
"border-radius:6px;"));

        horizontalLayout_6->addWidget(label_5);

        label_15 = new QLabel(frame_9);
        label_15->setObjectName("label_15");
        label_15->setMaximumSize(QSize(30, 30));
        label_15->setPixmap(QPixmap(QString::fromUtf8(":/mas-top.png")));
        label_15->setScaledContents(true);

        horizontalLayout_6->addWidget(label_15);

        label_14 = new QLabel(frame_9);
        label_14->setObjectName("label_14");
        label_14->setMaximumSize(QSize(30, 30));
        label_14->setPixmap(QPixmap(QString::fromUtf8(":/menos-top.png")));
        label_14->setScaledContents(true);

        horizontalLayout_6->addWidget(label_14);


        horizontalLayout_5->addWidget(frame_9);

        frame_10 = new QFrame(frame_8);
        frame_10->setObjectName("frame_10");
        frame_10->setMaximumSize(QSize(30, 40));
        frame_10->setFrameShape(QFrame::Shape::StyledPanel);
        frame_10->setFrameShadow(QFrame::Shadow::Raised);

        horizontalLayout_5->addWidget(frame_10);

        label_16 = new QLabel(frame_8);
        label_16->setObjectName("label_16");
        label_16->setMaximumSize(QSize(35, 35));
        label_16->setPixmap(QPixmap(QString::fromUtf8(":/trash.png")));
        label_16->setScaledContents(true);

        horizontalLayout_5->addWidget(label_16);


        verticalLayout_4->addWidget(frame_8);


        verticalLayout_3->addWidget(frame_3);

        frame_5 = new QFrame(groupBox);
        frame_5->setObjectName("frame_5");
        frame_5->setMaximumSize(QSize(300, 300));
        frame_5->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border-radius:15px;"));
        frame_5->setFrameShape(QFrame::Shape::StyledPanel);
        frame_5->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_5 = new QVBoxLayout(frame_5);
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_7 = new QLabel(frame_5);
        label_7->setObjectName("label_7");
        label_7->setMaximumSize(QSize(400, 200));
        label_7->setStyleSheet(QString::fromUtf8("border-radius: 5px;"));
        label_7->setPixmap(QPixmap(QString::fromUtf8(":/hamburguesa.jpeg")));
        label_7->setScaledContents(true);

        verticalLayout_5->addWidget(label_7);

        label_8 = new QLabel(frame_5);
        label_8->setObjectName("label_8");
        label_8->setMaximumSize(QSize(200, 30));
        label_8->setFont(font2);

        verticalLayout_5->addWidget(label_8);

        frame_6 = new QFrame(frame_5);
        frame_6->setObjectName("frame_6");
        frame_6->setMaximumSize(QSize(380, 40));
        frame_6->setFrameShape(QFrame::Shape::StyledPanel);
        frame_6->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_6);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        frame_4 = new QFrame(frame_6);
        frame_4->setObjectName("frame_4");
        frame_4->setMaximumSize(QSize(180, 40));
        frame_4->setFrameShape(QFrame::Shape::StyledPanel);
        frame_4->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_4);
        horizontalLayout_2->setSpacing(9);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(frame_4);
        label_6->setObjectName("label_6");
        label_6->setMaximumSize(QSize(70, 30));
        label_6->setFont(font2);
        label_6->setStyleSheet(QString::fromUtf8("background-color:red;\n"
"color:white;\n"
"border-radius:6px;"));

        horizontalLayout_2->addWidget(label_6);

        label_12 = new QLabel(frame_4);
        label_12->setObjectName("label_12");
        label_12->setMaximumSize(QSize(30, 30));
        label_12->setPixmap(QPixmap(QString::fromUtf8(":/mas-top.png")));
        label_12->setScaledContents(true);

        horizontalLayout_2->addWidget(label_12);

        label_11 = new QLabel(frame_4);
        label_11->setObjectName("label_11");
        label_11->setMaximumSize(QSize(30, 30));
        label_11->setPixmap(QPixmap(QString::fromUtf8(":/menos-top.png")));
        label_11->setScaledContents(true);

        horizontalLayout_2->addWidget(label_11);


        horizontalLayout_3->addWidget(frame_4);

        frame_7 = new QFrame(frame_6);
        frame_7->setObjectName("frame_7");
        frame_7->setMaximumSize(QSize(30, 40));
        frame_7->setFrameShape(QFrame::Shape::StyledPanel);
        frame_7->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame_7);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(15, -1, -1, -1);

        horizontalLayout_3->addWidget(frame_7);

        label_13 = new QLabel(frame_6);
        label_13->setObjectName("label_13");
        label_13->setMaximumSize(QSize(35, 35));
        label_13->setStyleSheet(QString::fromUtf8("float: right;"));
        label_13->setPixmap(QPixmap(QString::fromUtf8(":/trash.png")));
        label_13->setScaledContents(true);

        horizontalLayout_3->addWidget(label_13);


        verticalLayout_5->addWidget(frame_6);


        verticalLayout_3->addWidget(frame_5);


        verticalLayout_2->addWidget(groupBox);

        label = new QLabel(frame);
        label->setObjectName("label");
        label->setMaximumSize(QSize(380, 90));
        label->setFont(font2);
        label->setStyleSheet(QString::fromUtf8("background-color:red;\n"
"color:white;\n"
"border-radius:6px;"));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label);

        verticalLayout_2->setStretch(2, 5);

        verticalLayout->addWidget(frame);


        retranslateUi(carrito);

        QMetaObject::connectSlotsByName(carrito);
    } // setupUi

    void retranslateUi(QWidget *carrito)
    {
        carrito->setWindowTitle(QCoreApplication::translate("carrito", "Carrito - Rotiser\303\203\302\255a El Buen Gusto", nullptr));
        label_10->setText(QString());
        label_9->setText(QCoreApplication::translate("carrito", "Carrito - El Buen Gusto", nullptr));
        label_2->setText(QString());
        groupBox->setTitle(QString());
        label_3->setText(QString());
        label_4->setText(QCoreApplication::translate("carrito", "Hamburguesa Triple X1", nullptr));
        label_5->setText(QCoreApplication::translate("carrito", " $1500", nullptr));
        label_15->setText(QString());
        label_14->setText(QString());
        label_16->setText(QString());
        label_7->setText(QString());
        label_8->setText(QCoreApplication::translate("carrito", " Hamburguesa Triple X1", nullptr));
        label_6->setText(QCoreApplication::translate("carrito", " $1500", nullptr));
        label_12->setText(QString());
        label_11->setText(QString());
        label_13->setText(QString());
        label->setText(QCoreApplication::translate("carrito", "Finalizar pedido", nullptr));
    } // retranslateUi

};

namespace Ui {
    class carrito: public Ui_carrito {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARRITO_H
