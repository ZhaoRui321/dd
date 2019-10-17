/********************************************************************************
** Form generated from reading UI file 'sChartXIC.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCHARTXIC_H
#define UI_SCHARTXIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sChartXIC
{
public:
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QListWidget *listWidget;
    QGridLayout *gridLayout;
    QPushButton *B_Modify;
    QPushButton *B_Cancel;
    QSpacerItem *verticalSpacer_2;
    QPushButton *B_Add;
    QSpacerItem *verticalSpacer;
    QPushButton *B_OK;
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QLineEdit *lineEdit;
    QWidget *widget;
    QPushButton *B_Remove;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QWidget *sChartXIC)
    {
        if (sChartXIC->objectName().isEmpty())
            sChartXIC->setObjectName(QStringLiteral("sChartXIC"));
        sChartXIC->resize(633, 469);
        verticalLayout_3 = new QVBoxLayout(sChartXIC);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(sChartXIC);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(60, 60, 60, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(90, 90, 90, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(75, 75, 75, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(30, 30, 30, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(40, 40, 40, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QBrush brush6(QColor(0, 0, 0, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush4);
        QBrush brush7(QColor(255, 255, 220, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
        widget_2->setPalette(palette);
        widget_2->setAutoFillBackground(true);
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 9, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        listWidget = new QListWidget(widget_2);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        QFont font;
        font.setFamily(QStringLiteral("Microsoft YaHei UI"));
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        listWidget->setFont(font);
        listWidget->setStyleSheet(QLatin1String("QListWidget{background-color: rgb(60, 60, 60); border-style:none;\n"
"color:rgb(228,218,208);}\n"
"QListWidget::Item{height:44px;}\n"
"QListWidget::Item:hover{color:#EFD98B;}\n"
"QListWidget::item:selected{color:#EFD98B;}\n"
"QListWidget::item:selected:active{color:#EFD98B;}"));

        horizontalLayout->addWidget(listWidget);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(0);
        gridLayout->setVerticalSpacing(6);
        B_Modify = new QPushButton(widget_2);
        B_Modify->setObjectName(QStringLiteral("B_Modify"));
        B_Modify->setMinimumSize(QSize(120, 44));
        B_Modify->setMaximumSize(QSize(120, 16777215));
        B_Modify->setFont(font);
        B_Modify->setStyleSheet(QLatin1String("background-color: rgba(0,0,0,0);\n"
"color:rgb(228,218,208);\n"
"border-style: outset;\n"
"border-width:2px;\n"
"border-radius:10px;\n"
"border-color:rgb(228,218,208);\n"
"padding:6px;"));

        gridLayout->addWidget(B_Modify, 7, 0, 1, 1);

        B_Cancel = new QPushButton(widget_2);
        B_Cancel->setObjectName(QStringLiteral("B_Cancel"));
        B_Cancel->setMinimumSize(QSize(120, 44));
        B_Cancel->setMaximumSize(QSize(120, 16777215));
        B_Cancel->setFont(font);
        B_Cancel->setStyleSheet(QLatin1String("background-color: #EFD98B;\n"
"color:#3c3c3c;\n"
"border-style:none;\n"
"border-radius:10px;\n"
"border-color:#EFD98B;\n"
"padding:6px;"));

        gridLayout->addWidget(B_Cancel, 11, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 9, 0, 1, 1);

        B_Add = new QPushButton(widget_2);
        B_Add->setObjectName(QStringLiteral("B_Add"));
        B_Add->setMinimumSize(QSize(120, 44));
        B_Add->setMaximumSize(QSize(120, 16777215));
        B_Add->setFont(font);
        B_Add->setStyleSheet(QLatin1String("background-color: rgba(0,0,0,0);\n"
"color:rgb(228,218,208);\n"
"border-style: outset;\n"
"border-width:2px;\n"
"border-radius:10px;\n"
"border-color:rgb(228,218,208);\n"
"padding:6px;"));

        gridLayout->addWidget(B_Add, 6, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 0, 1, 1);

        B_OK = new QPushButton(widget_2);
        B_OK->setObjectName(QStringLiteral("B_OK"));
        B_OK->setMinimumSize(QSize(120, 44));
        B_OK->setMaximumSize(QSize(120, 16777215));
        B_OK->setFont(font);
        B_OK->setStyleSheet(QLatin1String("background-color: #EFD98B;\n"
"color:#3c3c3c;\n"
"border-style:none;\n"
"border-radius:10px;\n"
"border-color:#EFD98B;\n"
"padding:6px;"));

        gridLayout->addWidget(B_OK, 10, 0, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label = new QLabel(widget_2);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(0, 44));
        label->setMaximumSize(QSize(120, 16777215));
        QPalette palette1;
        QBrush brush8(QColor(228, 218, 208, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush8);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        label->setPalette(palette1);
        label->setFont(font);

        verticalLayout_4->addWidget(label);

        lineEdit = new QLineEdit(widget_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMinimumSize(QSize(120, 44));
        lineEdit->setMaximumSize(QSize(120, 16777215));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush8);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush9(QColor(90, 90, 90, 0));
        brush9.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Light, brush9);
        QBrush brush10(QColor(75, 75, 75, 0));
        brush10.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Midlight, brush10);
        QBrush brush11(QColor(30, 30, 30, 0));
        brush11.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Dark, brush11);
        QBrush brush12(QColor(40, 40, 40, 0));
        brush12.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Mid, brush12);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush8);
        palette2.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        QBrush brush13(QColor(30, 30, 30, 127));
        brush13.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::AlternateBase, brush13);
        palette2.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette2.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush8);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Light, brush9);
        palette2.setBrush(QPalette::Inactive, QPalette::Midlight, brush10);
        palette2.setBrush(QPalette::Inactive, QPalette::Dark, brush11);
        palette2.setBrush(QPalette::Inactive, QPalette::Mid, brush12);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush8);
        palette2.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush13);
        palette2.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette2.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush11);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Light, brush9);
        palette2.setBrush(QPalette::Disabled, QPalette::Midlight, brush10);
        palette2.setBrush(QPalette::Disabled, QPalette::Dark, brush11);
        palette2.setBrush(QPalette::Disabled, QPalette::Mid, brush12);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush11);
        palette2.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush11);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        QBrush brush14(QColor(60, 60, 60, 0));
        brush14.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush14);
        palette2.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette2.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
        lineEdit->setPalette(palette2);
        lineEdit->setFont(font);
        lineEdit->setAutoFillBackground(false);
        lineEdit->setStyleSheet(QLatin1String("background-color: rgb(60, 60, 60);\n"
"border-style: none;"));
        lineEdit->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        verticalLayout_4->addWidget(lineEdit);

        widget = new QWidget(widget_2);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(0, 2));
        widget->setMaximumSize(QSize(16777215, 2));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush6);
        palette3.setBrush(QPalette::Active, QPalette::Button, brush8);
        palette3.setBrush(QPalette::Active, QPalette::Light, brush);
        QBrush brush15(QColor(241, 236, 231, 255));
        brush15.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Midlight, brush15);
        QBrush brush16(QColor(114, 109, 104, 255));
        brush16.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Dark, brush16);
        QBrush brush17(QColor(152, 145, 139, 255));
        brush17.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Mid, brush17);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush6);
        palette3.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush6);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush8);
        palette3.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        palette3.setBrush(QPalette::Active, QPalette::AlternateBase, brush15);
        palette3.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette3.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush8);
        palette3.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Midlight, brush15);
        palette3.setBrush(QPalette::Inactive, QPalette::Dark, brush16);
        palette3.setBrush(QPalette::Inactive, QPalette::Mid, brush17);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush8);
        palette3.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush15);
        palette3.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette3.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush16);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush8);
        palette3.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Midlight, brush15);
        palette3.setBrush(QPalette::Disabled, QPalette::Dark, brush16);
        palette3.setBrush(QPalette::Disabled, QPalette::Mid, brush17);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush16);
        palette3.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush16);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush8);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush8);
        palette3.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette3.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush8);
        palette3.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette3.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
        widget->setPalette(palette3);
        widget->setAutoFillBackground(true);

        verticalLayout_4->addWidget(widget);


        gridLayout->addLayout(verticalLayout_4, 4, 0, 1, 1);

        B_Remove = new QPushButton(widget_2);
        B_Remove->setObjectName(QStringLiteral("B_Remove"));
        B_Remove->setMinimumSize(QSize(120, 44));
        B_Remove->setMaximumSize(QSize(120, 16777215));
        B_Remove->setFont(font);
        B_Remove->setStyleSheet(QLatin1String("background-color: rgba(0,0,0,0);\n"
"color:rgb(228,218,208);\n"
"border-style: outset;\n"
"border-width:2px;\n"
"border-radius:10px;\n"
"border-color:rgb(228,218,208);\n"
"padding:6px;"));

        gridLayout->addWidget(B_Remove, 8, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 12, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_3->addWidget(widget_2);


        retranslateUi(sChartXIC);

        QMetaObject::connectSlotsByName(sChartXIC);
    } // setupUi

    void retranslateUi(QWidget *sChartXIC)
    {
        sChartXIC->setWindowTitle(QApplication::translate("sChartXIC", "Form", nullptr));
        B_Modify->setText(QApplication::translate("sChartXIC", "Modify", nullptr));
        B_Cancel->setText(QApplication::translate("sChartXIC", "Cancel", nullptr));
        B_Add->setText(QApplication::translate("sChartXIC", "Add", nullptr));
        B_OK->setText(QApplication::translate("sChartXIC", "OK", nullptr));
        label->setText(QApplication::translate("sChartXIC", "Mass offset(Th):", nullptr));
        lineEdit->setText(QApplication::translate("sChartXIC", "0.5", nullptr));
        B_Remove->setText(QApplication::translate("sChartXIC", "Remove", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sChartXIC: public Ui_sChartXIC {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCHARTXIC_H
