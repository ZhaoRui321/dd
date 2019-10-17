/********************************************************************************
** Form generated from reading UI file 'sSystem.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SSYSTEM_H
#define UI_SSYSTEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "sSystem/MyControl.h"

QT_BEGIN_NAMESPACE

class Ui_sSystem
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *btnWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *UI_PB_CONTROL;
    QPushButton *UI_PB_MANUAL;
    QPushButton *UI_PB_AUTO;
    QSpacerItem *horizontalSpacer;
    QPushButton *UI_PB_SHOW_PWM;
    QPushButton *UI_PB_SHOW_SSC;
    QPushButton *UI_PB_QUIT;
    QStackedWidget *stackedWidget;
    MyControl *control;

    void setupUi(QWidget *sSystem)
    {
        if (sSystem->objectName().isEmpty())
            sSystem->setObjectName(QStringLiteral("sSystem"));
        sSystem->resize(1429, 697);
        verticalLayout = new QVBoxLayout(sSystem);
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(50, 20, 100, 10);
        btnWidget = new QWidget(sSystem);
        btnWidget->setObjectName(QStringLiteral("btnWidget"));
        btnWidget->setMinimumSize(QSize(0, 60));
        btnWidget->setMaximumSize(QSize(16777215, 90));
        horizontalLayout = new QHBoxLayout(btnWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        UI_PB_CONTROL = new QPushButton(btnWidget);
        UI_PB_CONTROL->setObjectName(QStringLiteral("UI_PB_CONTROL"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(UI_PB_CONTROL->sizePolicy().hasHeightForWidth());
        UI_PB_CONTROL->setSizePolicy(sizePolicy);
        UI_PB_CONTROL->setMinimumSize(QSize(200, 0));
        UI_PB_CONTROL->setMaximumSize(QSize(200, 16777215));
        QFont font;
        font.setPointSize(12);
        UI_PB_CONTROL->setFont(font);

        horizontalLayout->addWidget(UI_PB_CONTROL);

        UI_PB_MANUAL = new QPushButton(btnWidget);
        UI_PB_MANUAL->setObjectName(QStringLiteral("UI_PB_MANUAL"));
        sizePolicy.setHeightForWidth(UI_PB_MANUAL->sizePolicy().hasHeightForWidth());
        UI_PB_MANUAL->setSizePolicy(sizePolicy);
        UI_PB_MANUAL->setMinimumSize(QSize(200, 0));
        UI_PB_MANUAL->setMaximumSize(QSize(200, 16777215));
        UI_PB_MANUAL->setFont(font);

        horizontalLayout->addWidget(UI_PB_MANUAL);

        UI_PB_AUTO = new QPushButton(btnWidget);
        UI_PB_AUTO->setObjectName(QStringLiteral("UI_PB_AUTO"));
        sizePolicy.setHeightForWidth(UI_PB_AUTO->sizePolicy().hasHeightForWidth());
        UI_PB_AUTO->setSizePolicy(sizePolicy);
        UI_PB_AUTO->setMinimumSize(QSize(200, 0));
        UI_PB_AUTO->setMaximumSize(QSize(200, 16777215));
        UI_PB_AUTO->setFont(font);

        horizontalLayout->addWidget(UI_PB_AUTO);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        UI_PB_SHOW_PWM = new QPushButton(btnWidget);
        UI_PB_SHOW_PWM->setObjectName(QStringLiteral("UI_PB_SHOW_PWM"));
        sizePolicy.setHeightForWidth(UI_PB_SHOW_PWM->sizePolicy().hasHeightForWidth());
        UI_PB_SHOW_PWM->setSizePolicy(sizePolicy);
        UI_PB_SHOW_PWM->setMinimumSize(QSize(200, 0));
        UI_PB_SHOW_PWM->setMaximumSize(QSize(200, 16777215));

        horizontalLayout->addWidget(UI_PB_SHOW_PWM);

        UI_PB_SHOW_SSC = new QPushButton(btnWidget);
        UI_PB_SHOW_SSC->setObjectName(QStringLiteral("UI_PB_SHOW_SSC"));
        sizePolicy.setHeightForWidth(UI_PB_SHOW_SSC->sizePolicy().hasHeightForWidth());
        UI_PB_SHOW_SSC->setSizePolicy(sizePolicy);
        UI_PB_SHOW_SSC->setMinimumSize(QSize(200, 0));
        UI_PB_SHOW_SSC->setMaximumSize(QSize(200, 16777215));

        horizontalLayout->addWidget(UI_PB_SHOW_SSC);

        UI_PB_QUIT = new QPushButton(btnWidget);
        UI_PB_QUIT->setObjectName(QStringLiteral("UI_PB_QUIT"));
        sizePolicy.setHeightForWidth(UI_PB_QUIT->sizePolicy().hasHeightForWidth());
        UI_PB_QUIT->setSizePolicy(sizePolicy);
        UI_PB_QUIT->setMinimumSize(QSize(200, 0));
        UI_PB_QUIT->setMaximumSize(QSize(200, 16777215));

        horizontalLayout->addWidget(UI_PB_QUIT);


        verticalLayout->addWidget(btnWidget);

        stackedWidget = new QStackedWidget(sSystem);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        control = new MyControl();
        control->setObjectName(QStringLiteral("control"));
        stackedWidget->addWidget(control);

        verticalLayout->addWidget(stackedWidget);


        retranslateUi(sSystem);

        QMetaObject::connectSlotsByName(sSystem);
    } // setupUi

    void retranslateUi(QWidget *sSystem)
    {
        sSystem->setWindowTitle(QApplication::translate("sSystem", "Form", nullptr));
        UI_PB_CONTROL->setText(QApplication::translate("sSystem", "\347\263\273\347\273\237\346\216\247\345\210\266", nullptr));
        UI_PB_MANUAL->setText(QApplication::translate("sSystem", "\346\211\213\345\212\250\350\260\203\350\260\220", nullptr));
        UI_PB_AUTO->setText(QApplication::translate("sSystem", "\350\207\252\345\212\250\350\260\203\350\260\220", nullptr));
        UI_PB_SHOW_PWM->setText(QApplication::translate("sSystem", "PWM", nullptr));
        UI_PB_SHOW_SSC->setText(QApplication::translate("sSystem", "SSC", nullptr));
        UI_PB_QUIT->setText(QApplication::translate("sSystem", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sSystem: public Ui_sSystem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SSYSTEM_H
