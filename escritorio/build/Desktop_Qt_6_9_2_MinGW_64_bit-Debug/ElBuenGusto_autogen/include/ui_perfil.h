/********************************************************************************
** Form generated from reading UI file 'perfil.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PERFIL_H
#define UI_PERFIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
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
    QFrame *frame_3;
    QFrame *frame_4;
    QFrame *frame_5;
    QFrame *frame_6;

    void setupUi(QWidget *perfil)
    {
        if (perfil->objectName().isEmpty())
            perfil->setObjectName("perfil");
        perfil->resize(631, 601);
        perfil->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 235, 210);\n"
"padding: 0;"));
        verticalLayout = new QVBoxLayout(perfil);
        verticalLayout->setObjectName("verticalLayout");
        scrollArea = new QScrollArea(perfil);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setStyleSheet(QString::fromUtf8("border: none;"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 613, 583));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setObjectName("verticalLayout_2");
        frame = new QFrame(scrollAreaWidgetContents);
        frame->setObjectName("frame");
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(200, 35, 40);\n"
"color: rgb(255, 255, 255);"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_3 = new QVBoxLayout(frame);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label = new QLabel(frame);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(20);
        label->setFont(font);

        verticalLayout_3->addWidget(label);

        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(245,235,210);"));

        verticalLayout_3->addWidget(label_2);


        verticalLayout_2->addWidget(frame);

        frame_2 = new QFrame(scrollAreaWidgetContents);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);

        verticalLayout_2->addWidget(frame_2);

        frame_3 = new QFrame(scrollAreaWidgetContents);
        frame_3->setObjectName("frame_3");
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);

        verticalLayout_2->addWidget(frame_3);

        frame_4 = new QFrame(scrollAreaWidgetContents);
        frame_4->setObjectName("frame_4");
        frame_4->setFrameShape(QFrame::Shape::StyledPanel);
        frame_4->setFrameShadow(QFrame::Shadow::Raised);

        verticalLayout_2->addWidget(frame_4);

        frame_5 = new QFrame(scrollAreaWidgetContents);
        frame_5->setObjectName("frame_5");
        frame_5->setFrameShape(QFrame::Shape::StyledPanel);
        frame_5->setFrameShadow(QFrame::Shadow::Raised);

        verticalLayout_2->addWidget(frame_5);

        frame_6 = new QFrame(scrollAreaWidgetContents);
        frame_6->setObjectName("frame_6");
        frame_6->setFrameShape(QFrame::Shape::StyledPanel);
        frame_6->setFrameShadow(QFrame::Shadow::Raised);

        verticalLayout_2->addWidget(frame_6);

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
    } // retranslateUi

};

namespace Ui {
    class perfil: public Ui_perfil {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERFIL_H
