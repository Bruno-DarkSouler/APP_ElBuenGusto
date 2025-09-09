/********************************************************************************
** Form generated from reading UI file 'tarjeta_especialidades.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TARJETA_ESPECIALIDADES_H
#define UI_TARJETA_ESPECIALIDADES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_tarjeta_especialidades
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QFrame *tarjeta_especialidades)
    {
        if (tarjeta_especialidades->objectName().isEmpty())
            tarjeta_especialidades->setObjectName("tarjeta_especialidades");
        tarjeta_especialidades->resize(333, 302);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tarjeta_especialidades->sizePolicy().hasHeightForWidth());
        tarjeta_especialidades->setSizePolicy(sizePolicy);
        tarjeta_especialidades->setMaximumSize(QSize(16777215, 872));
        tarjeta_especialidades->setStyleSheet(QString::fromUtf8("background-color:rgb(245, 235, 210); "));
        verticalLayout = new QVBoxLayout(tarjeta_especialidades);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(tarjeta_especialidades);
        label->setObjectName("label");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMaximumSize(QSize(16777215, 302));
        label->setFrameShape(QFrame::Shape::NoFrame);
        label->setPixmap(QPixmap(QString::fromUtf8(":/hamburguesa.jpeg")));
        label->setScaledContents(true);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(tarjeta_especialidades);
        label_2->setObjectName("label_2");
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label_2);


        retranslateUi(tarjeta_especialidades);

        QMetaObject::connectSlotsByName(tarjeta_especialidades);
    } // setupUi

    void retranslateUi(QFrame *tarjeta_especialidades)
    {
        tarjeta_especialidades->setWindowTitle(QCoreApplication::translate("tarjeta_especialidades", "Frame", nullptr));
        label->setText(QString());
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class tarjeta_especialidades: public Ui_tarjeta_especialidades {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TARJETA_ESPECIALIDADES_H
