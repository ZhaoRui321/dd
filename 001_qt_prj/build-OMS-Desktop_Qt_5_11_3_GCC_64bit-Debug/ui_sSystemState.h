/********************************************************************************
** Form generated from reading UI file 'sSystemState.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SSYSTEMSTATE_H
#define UI_SSYSTEMSTATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sSystemState
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QLabel *L_AD0;
    QLabel *label_9;
    QLabel *L_AD2;
    QLabel *label_11;
    QLabel *L_AD3;
    QLabel *label_7;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *L_AD1;
    QLabel *label;
    QLabel *label_6;
    QLabel *label_8;

    void setupUi(QWidget *sSystemState)
    {
        if (sSystemState->objectName().isEmpty())
            sSystemState->setObjectName(QStringLiteral("sSystemState"));
        sSystemState->resize(298, 185);
        verticalLayout = new QVBoxLayout(sSystemState);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_5 = new QLabel(sSystemState);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        L_AD0 = new QLabel(sSystemState);
        L_AD0->setObjectName(QStringLiteral("L_AD0"));

        gridLayout->addWidget(L_AD0, 0, 1, 1, 1);

        label_9 = new QLabel(sSystemState);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 1, 0, 1, 1);

        L_AD2 = new QLabel(sSystemState);
        L_AD2->setObjectName(QStringLiteral("L_AD2"));

        gridLayout->addWidget(L_AD2, 2, 1, 1, 1);

        label_11 = new QLabel(sSystemState);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout->addWidget(label_11, 0, 0, 1, 1);

        L_AD3 = new QLabel(sSystemState);
        L_AD3->setObjectName(QStringLiteral("L_AD3"));

        gridLayout->addWidget(L_AD3, 3, 1, 1, 1);

        label_7 = new QLabel(sSystemState);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 2, 0, 1, 1);

        label_2 = new QLabel(sSystemState);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 5, 0, 1, 1);

        label_4 = new QLabel(sSystemState);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 5, 1, 1, 1);

        label_3 = new QLabel(sSystemState);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 4, 1, 1, 1);

        L_AD1 = new QLabel(sSystemState);
        L_AD1->setObjectName(QStringLiteral("L_AD1"));

        gridLayout->addWidget(L_AD1, 1, 1, 1, 1);

        label = new QLabel(sSystemState);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 4, 0, 1, 1);

        label_6 = new QLabel(sSystemState);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 6, 0, 1, 2);

        label_8 = new QLabel(sSystemState);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 7, 0, 1, 2);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(sSystemState);

        QMetaObject::connectSlotsByName(sSystemState);
    } // setupUi

    void retranslateUi(QWidget *sSystemState)
    {
        sSystemState->setWindowTitle(QApplication::translate("sSystemState", "Form", nullptr));
        label_5->setText(QApplication::translate("sSystemState", "Pressure 3 (Pa)", nullptr));
        L_AD0->setText(QApplication::translate("sSystemState", "TextLabel", nullptr));
        label_9->setText(QApplication::translate("sSystemState", "QA_MIG_Feedback (V)", nullptr));
        L_AD2->setText(QApplication::translate("sSystemState", "TextLabel", nullptr));
        label_11->setText(QApplication::translate("sSystemState", "Vacuum Chamber (Pa)", nullptr));
        L_AD3->setText(QApplication::translate("sSystemState", "TextLabel", nullptr));
        label_7->setText(QApplication::translate("sSystemState", "Pressure 2 (Pa)", nullptr));
        label_2->setText(QApplication::translate("sSystemState", "Pump rotation speed (Hz)", nullptr));
        label_4->setText(QApplication::translate("sSystemState", "TextLabel", nullptr));
        label_3->setText(QApplication::translate("sSystemState", "TextLabel", nullptr));
        L_AD1->setText(QApplication::translate("sSystemState", "TextLabel", nullptr));
        label->setText(QApplication::translate("sSystemState", "Pump drive current (A)", nullptr));
        label_6->setText(QApplication::translate("sSystemState", "TextLabel", nullptr));
        label_8->setText(QApplication::translate("sSystemState", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sSystemState: public Ui_sSystemState {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SSYSTEMSTATE_H
