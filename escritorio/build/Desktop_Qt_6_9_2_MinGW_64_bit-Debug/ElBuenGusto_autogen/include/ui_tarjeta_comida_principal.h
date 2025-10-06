/********************************************************************************
** Form generated from reading UI file 'tarjeta_comida_principal.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TARJETA_COMIDA_PRINCIPAL_H
#define UI_TARJETA_COMIDA_PRINCIPAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tarjeta_comida_principal
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *tarjeta_comida_principal)
    {
        if (tarjeta_comida_principal->objectName().isEmpty())
            tarjeta_comida_principal->setObjectName("tarjeta_comida_principal");
        tarjeta_comida_principal->resize(190, 171);
        tarjeta_comida_principal->setStyleSheet(QString::fromUtf8("background-color:rgb(245,235,210);\n"
"border-radius:10;\n"
"padding:10;"));
        verticalLayout = new QVBoxLayout(tarjeta_comida_principal);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(tarjeta_comida_principal);
        label->setObjectName("label");
        label->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setStyleSheet(QString::fromUtf8("border-radius:20;\n"
"background-color:#0000ff;"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/hamburguesa.jpeg")));
        label->setScaledContents(true);
        label->setMargin(7);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(tarjeta_comida_principal);
        label_2->setObjectName("label_2");
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("background-color:rgb(80,50,20);"));
        label_2->setLineWidth(1);
        label_2->setMidLineWidth(0);
        label_2->setText(QString::fromUtf8(""));
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label_2);

        verticalLayout->setStretch(0, 9);
        verticalLayout->setStretch(1, 3);

        retranslateUi(tarjeta_comida_principal);

        QMetaObject::connectSlotsByName(tarjeta_comida_principal);
    } // setupUi

    void retranslateUi(QWidget *tarjeta_comida_principal)
    {
        tarjeta_comida_principal->setWindowTitle(QCoreApplication::translate("tarjeta_comida_principal", "Form", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class tarjeta_comida_principal: public Ui_tarjeta_comida_principal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TARJETA_COMIDA_PRINCIPAL_H
