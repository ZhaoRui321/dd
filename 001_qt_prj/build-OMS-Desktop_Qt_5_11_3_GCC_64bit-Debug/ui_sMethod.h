/********************************************************************************
** Form generated from reading UI file 'sMethod.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMETHOD_H
#define UI_SMETHOD_H

#include <QSwitchButton.h>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <SIM.h>
#include "AllScan.h"

QT_BEGIN_NAMESPACE

class Ui_sMethod
{
public:
    QVBoxLayout *verticalLayout_4;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *btnWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *allSacnBtn;
    QPushButton *simBtn;
    QPushButton *msnBtn;
    QSpacerItem *horizontalSpacer_2;
    QSwitchButton *switchBtn_AGC;
    QLabel *label_2;
    QSwitchButton *switchBtn;
    QLabel *label;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QStackedWidget *stackedWidget;
    AllScan *allScan;
    SIM *sim;
    QWidget *msn;

    void setupUi(QWidget *sMethod)
    {
        if (sMethod->objectName().isEmpty())
            sMethod->setObjectName(QStringLiteral("sMethod"));
        sMethod->resize(1374, 697);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sMethod->sizePolicy().hasHeightForWidth());
        sMethod->setSizePolicy(sizePolicy);
        verticalLayout_4 = new QVBoxLayout(sMethod);
        verticalLayout_4->setSpacing(10);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(100, 100, 100, 100);
        widget = new QWidget(sMethod);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy1);
        widget->setMinimumSize(QSize(0, 60));
        widget->setMaximumSize(QSize(16777215, 60));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        btnWidget = new QWidget(widget);
        btnWidget->setObjectName(QStringLiteral("btnWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnWidget->sizePolicy().hasHeightForWidth());
        btnWidget->setSizePolicy(sizePolicy2);
        horizontalLayout = new QHBoxLayout(btnWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        allSacnBtn = new QPushButton(btnWidget);
        allSacnBtn->setObjectName(QStringLiteral("allSacnBtn"));
        sizePolicy.setHeightForWidth(allSacnBtn->sizePolicy().hasHeightForWidth());
        allSacnBtn->setSizePolicy(sizePolicy);
        allSacnBtn->setMinimumSize(QSize(200, 50));
        allSacnBtn->setMaximumSize(QSize(200, 120));
        QFont font;
        font.setPointSize(12);
        font.setBold(false);
        font.setWeight(50);
        allSacnBtn->setFont(font);

        horizontalLayout->addWidget(allSacnBtn);

        simBtn = new QPushButton(btnWidget);
        simBtn->setObjectName(QStringLiteral("simBtn"));
        sizePolicy.setHeightForWidth(simBtn->sizePolicy().hasHeightForWidth());
        simBtn->setSizePolicy(sizePolicy);
        simBtn->setMinimumSize(QSize(200, 50));
        simBtn->setMaximumSize(QSize(200, 120));
        QFont font1;
        font1.setPointSize(12);
        simBtn->setFont(font1);

        horizontalLayout->addWidget(simBtn);

        msnBtn = new QPushButton(btnWidget);
        msnBtn->setObjectName(QStringLiteral("msnBtn"));
        sizePolicy.setHeightForWidth(msnBtn->sizePolicy().hasHeightForWidth());
        msnBtn->setSizePolicy(sizePolicy);
        msnBtn->setMinimumSize(QSize(200, 50));
        msnBtn->setMaximumSize(QSize(200, 120));
        msnBtn->setFont(font1);

        horizontalLayout->addWidget(msnBtn);


        horizontalLayout_2->addWidget(btnWidget);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        switchBtn_AGC = new QSwitchButton(widget);
        switchBtn_AGC->setObjectName(QStringLiteral("switchBtn_AGC"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(switchBtn_AGC->sizePolicy().hasHeightForWidth());
        switchBtn_AGC->setSizePolicy(sizePolicy3);
        switchBtn_AGC->setMinimumSize(QSize(150, 0));

        horizontalLayout_2->addWidget(switchBtn_AGC);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font2;
        font2.setPointSize(15);
        font2.setBold(true);
        font2.setWeight(75);
        label_2->setFont(font2);
        label_2->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_2->setMargin(5);

        horizontalLayout_2->addWidget(label_2);

        switchBtn = new QSwitchButton(widget);
        switchBtn->setObjectName(QStringLiteral("switchBtn"));
        sizePolicy3.setHeightForWidth(switchBtn->sizePolicy().hasHeightForWidth());
        switchBtn->setSizePolicy(sizePolicy3);
        switchBtn->setMinimumSize(QSize(150, 0));

        horizontalLayout_2->addWidget(switchBtn);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font2);
        label->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label->setMargin(5);

        horizontalLayout_2->addWidget(label);


        verticalLayout_4->addWidget(widget);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        stackedWidget = new QStackedWidget(sMethod);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy4);
        allScan = new AllScan();
        allScan->setObjectName(QStringLiteral("allScan"));
        allScan->setAutoFillBackground(true);
        stackedWidget->addWidget(allScan);
        sim = new SIM();
        sim->setObjectName(QStringLiteral("sim"));
        stackedWidget->addWidget(sim);
        msn = new QWidget();
        msn->setObjectName(QStringLiteral("msn"));
        stackedWidget->addWidget(msn);

        verticalLayout_2->addWidget(stackedWidget);


        verticalLayout_3->addLayout(verticalLayout_2);


        verticalLayout_4->addLayout(verticalLayout_3);


        retranslateUi(sMethod);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(sMethod);
    } // setupUi

    void retranslateUi(QWidget *sMethod)
    {
        sMethod->setWindowTitle(QApplication::translate("sMethod", "Form", nullptr));
        allSacnBtn->setText(QApplication::translate("sMethod", "\345\205\250\346\211\253\346\217\217", nullptr));
        simBtn->setText(QApplication::translate("sMethod", "SIM", nullptr));
        msnBtn->setText(QApplication::translate("sMethod", "MSN", nullptr));
        switchBtn_AGC->setText(QString());
        label_2->setText(QApplication::translate("sMethod", "AGC", nullptr));
        switchBtn->setText(QString());
        label->setText(QApplication::translate("sMethod", "\347\246\273\345\255\220\346\236\201\346\200\247", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sMethod: public Ui_sMethod {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMETHOD_H
