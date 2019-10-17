/********************************************************************************
** Form generated from reading UI file 'sAutoTuning.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAUTOTUNING_H
#define UI_SAUTOTUNING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sAutoTuning
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *sAutoTuning)
    {
        if (sAutoTuning->objectName().isEmpty())
            sAutoTuning->setObjectName(QStringLiteral("sAutoTuning"));
        sAutoTuning->resize(400, 300);
        verticalLayout = new QVBoxLayout(sAutoTuning);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 248, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(sAutoTuning);

        QMetaObject::connectSlotsByName(sAutoTuning);
    } // setupUi

    void retranslateUi(QWidget *sAutoTuning)
    {
        sAutoTuning->setWindowTitle(QApplication::translate("sAutoTuning", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sAutoTuning: public Ui_sAutoTuning {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAUTOTUNING_H
