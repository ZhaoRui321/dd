/********************************************************************************
** Form generated from reading UI file 'sManagerXIC.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMANAGERXIC_H
#define UI_SMANAGERXIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sManagerXIC
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *E_Event;
    QLabel *label_2;
    QLineEdit *E_Mass;
    QLabel *label_3;
    QLineEdit *E_Gain;
    QLabel *label_4;
    QLineEdit *E_Offset;
    QLabel *label_5;
    QPushButton *B_OK;
    QPushButton *B_Cancel;
    QPushButton *B_Color;

    void setupUi(QWidget *sManagerXIC)
    {
        if (sManagerXIC->objectName().isEmpty())
            sManagerXIC->setObjectName(QStringLiteral("sManagerXIC"));
        sManagerXIC->resize(273, 300);
        gridLayout = new QGridLayout(sManagerXIC);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(sManagerXIC);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        E_Event = new QLineEdit(sManagerXIC);
        E_Event->setObjectName(QStringLiteral("E_Event"));

        gridLayout->addWidget(E_Event, 0, 1, 1, 1);

        label_2 = new QLabel(sManagerXIC);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        E_Mass = new QLineEdit(sManagerXIC);
        E_Mass->setObjectName(QStringLiteral("E_Mass"));

        gridLayout->addWidget(E_Mass, 1, 1, 1, 1);

        label_3 = new QLabel(sManagerXIC);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        E_Gain = new QLineEdit(sManagerXIC);
        E_Gain->setObjectName(QStringLiteral("E_Gain"));

        gridLayout->addWidget(E_Gain, 2, 1, 1, 1);

        label_4 = new QLabel(sManagerXIC);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        E_Offset = new QLineEdit(sManagerXIC);
        E_Offset->setObjectName(QStringLiteral("E_Offset"));

        gridLayout->addWidget(E_Offset, 3, 1, 1, 1);

        label_5 = new QLabel(sManagerXIC);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        B_OK = new QPushButton(sManagerXIC);
        B_OK->setObjectName(QStringLiteral("B_OK"));

        gridLayout->addWidget(B_OK, 5, 0, 1, 1);

        B_Cancel = new QPushButton(sManagerXIC);
        B_Cancel->setObjectName(QStringLiteral("B_Cancel"));

        gridLayout->addWidget(B_Cancel, 5, 1, 1, 1);

        B_Color = new QPushButton(sManagerXIC);
        B_Color->setObjectName(QStringLiteral("B_Color"));

        gridLayout->addWidget(B_Color, 4, 1, 1, 1);


        retranslateUi(sManagerXIC);

        QMetaObject::connectSlotsByName(sManagerXIC);
    } // setupUi

    void retranslateUi(QWidget *sManagerXIC)
    {
        sManagerXIC->setWindowTitle(QApplication::translate("sManagerXIC", "Form", nullptr));
        label->setText(QApplication::translate("sManagerXIC", "Event", nullptr));
        label_2->setText(QApplication::translate("sManagerXIC", "Mass", nullptr));
        label_3->setText(QApplication::translate("sManagerXIC", "Gain", nullptr));
        label_4->setText(QApplication::translate("sManagerXIC", "Offset", nullptr));
        label_5->setText(QApplication::translate("sManagerXIC", "Color", nullptr));
        B_OK->setText(QApplication::translate("sManagerXIC", "OK", nullptr));
        B_Cancel->setText(QApplication::translate("sManagerXIC", "Cancel", nullptr));
        B_Color->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class sManagerXIC: public Ui_sManagerXIC {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMANAGERXIC_H
