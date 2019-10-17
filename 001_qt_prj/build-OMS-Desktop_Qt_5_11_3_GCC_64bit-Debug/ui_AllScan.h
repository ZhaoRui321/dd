/********************************************************************************
** Form generated from reading UI file 'AllScan.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALLSCAN_H
#define UI_ALLSCAN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AllScan
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QWidget *widget_3;
    QWidget *btnWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_9;
    QPushButton *userModelBtn;
    QVBoxLayout *verticalLayout_11;
    QPushButton *smallModelBtn;
    QVBoxLayout *verticalLayout_10;
    QPushButton *bigModelBtn;
    QSpacerItem *verticalSpacer;
    QWidget *horizontalWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_5;
    QWidget *widget;
    QLabel *label;
    QVBoxLayout *verticalLayout_6;
    QWidget *widget_2;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *doubleSliderLayout;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *oneSliderLayout;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_12;

    void setupUi(QWidget *AllScan)
    {
        if (AllScan->objectName().isEmpty())
            AllScan->setObjectName(QStringLiteral("AllScan"));
        AllScan->resize(704, 947);
        verticalLayout_2 = new QVBoxLayout(AllScan);
        verticalLayout_2->setSpacing(90);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(9, 9, 9, 9);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(50);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 100, -1, -1);
        widget_3 = new QWidget(AllScan);
        widget_3->setObjectName(QStringLiteral("widget_3"));

        verticalLayout->addWidget(widget_3);

        btnWidget = new QWidget(AllScan);
        btnWidget->setObjectName(QStringLiteral("btnWidget"));
        btnWidget->setMinimumSize(QSize(100, 0));
        horizontalLayout_2 = new QHBoxLayout(btnWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        userModelBtn = new QPushButton(btnWidget);
        userModelBtn->setObjectName(QStringLiteral("userModelBtn"));
        userModelBtn->setMinimumSize(QSize(0, 250));
        QFont font;
        font.setPointSize(30);
        userModelBtn->setFont(font);

        verticalLayout_9->addWidget(userModelBtn);


        horizontalLayout_2->addLayout(verticalLayout_9);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        smallModelBtn = new QPushButton(btnWidget);
        smallModelBtn->setObjectName(QStringLiteral("smallModelBtn"));
        smallModelBtn->setMinimumSize(QSize(0, 250));
        QFont font1;
        font1.setPointSize(25);
        smallModelBtn->setFont(font1);

        verticalLayout_11->addWidget(smallModelBtn);


        horizontalLayout_2->addLayout(verticalLayout_11);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        bigModelBtn = new QPushButton(btnWidget);
        bigModelBtn->setObjectName(QStringLiteral("bigModelBtn"));
        bigModelBtn->setMinimumSize(QSize(0, 250));
        bigModelBtn->setFont(font1);

        verticalLayout_10->addWidget(bigModelBtn);


        horizontalLayout_2->addLayout(verticalLayout_10);


        verticalLayout->addWidget(btnWidget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalWidget = new QWidget(AllScan);
        horizontalWidget->setObjectName(QStringLiteral("horizontalWidget"));
        horizontalWidget->setMinimumSize(QSize(300, 0));
        horizontalLayout = new QHBoxLayout(horizontalWidget);
        horizontalLayout->setSpacing(50);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, 200, -1);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(25);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        widget = new QWidget(horizontalWidget);
        widget->setObjectName(QStringLiteral("widget"));

        verticalLayout_5->addWidget(widget);

        label = new QLabel(horizontalWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(80, 0));
        QFont font2;
        font2.setPointSize(24);
        font2.setBold(true);
        font2.setWeight(75);
        font2.setKerning(true);
        label->setFont(font2);
        label->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        label->setMargin(5);

        verticalLayout_5->addWidget(label);


        verticalLayout_4->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        widget_2 = new QWidget(horizontalWidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));

        verticalLayout_6->addWidget(widget_2);

        label_2 = new QLabel(horizontalWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(50, 0));
        QFont font3;
        font3.setPointSize(24);
        font3.setBold(true);
        font3.setWeight(75);
        label_2->setFont(font3);
        label_2->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        label_2->setMargin(5);

        verticalLayout_6->addWidget(label_2);


        verticalLayout_4->addLayout(verticalLayout_6);


        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(25);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout_7->addLayout(horizontalLayout_3);

        doubleSliderLayout = new QHBoxLayout();
        doubleSliderLayout->setObjectName(QStringLiteral("doubleSliderLayout"));
        doubleSliderLayout->setContentsMargins(30, 10, 30, 10);

        verticalLayout_7->addLayout(doubleSliderLayout);


        verticalLayout_3->addLayout(verticalLayout_7);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        verticalLayout_8->addLayout(horizontalLayout_5);

        oneSliderLayout = new QHBoxLayout();
        oneSliderLayout->setObjectName(QStringLiteral("oneSliderLayout"));
        oneSliderLayout->setContentsMargins(30, 10, 30, 10);

        verticalLayout_8->addLayout(oneSliderLayout);


        verticalLayout_3->addLayout(verticalLayout_8);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout->addWidget(horizontalWidget);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));

        verticalLayout->addLayout(verticalLayout_12);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(AllScan);

        QMetaObject::connectSlotsByName(AllScan);
    } // setupUi

    void retranslateUi(QWidget *AllScan)
    {
        AllScan->setWindowTitle(QApplication::translate("AllScan", "Form", nullptr));
        userModelBtn->setText(QApplication::translate("AllScan", "\350\207\252\345\256\232\344\271\211\346\250\241\345\274\217", nullptr));
        smallModelBtn->setText(QApplication::translate("AllScan", "\345\260\217\345\210\206\345\255\220\346\250\241\345\274\217", nullptr));
        bigModelBtn->setText(QApplication::translate("AllScan", "\345\244\247\345\210\206\345\255\220\346\250\241\345\274\217", nullptr));
        label->setText(QApplication::translate("AllScan", "\350\264\250\351\207\217\350\214\203\345\233\264", nullptr));
        label_2->setText(QApplication::translate("AllScan", "\350\264\250\351\207\217\346\211\253\351\200\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AllScan: public Ui_AllScan {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALLSCAN_H
