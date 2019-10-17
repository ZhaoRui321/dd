/********************************************************************************
** Form generated from reading UI file 'MyControl.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYCONTROL_H
#define UI_MYCONTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>
#include <sSystem/ControlDemo.h>

QT_BEGIN_NAMESPACE

class Ui_MyControl
{
public:
    QGridLayout *gridLayout;
    ControlDemo *dynodeWidget;
    ControlDemo *iconWidget;
    ControlDemo *increaseWidget;
    ControlDemo *tempterature;
    ControlDemo *DFWidget;
    ControlDemo *ZSQWidgeht;

    void setupUi(QWidget *MyControl)
    {
        if (MyControl->objectName().isEmpty())
            MyControl->setObjectName(QStringLiteral("MyControl"));
        MyControl->resize(774, 512);
        gridLayout = new QGridLayout(MyControl);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(100);
        gridLayout->setVerticalSpacing(50);
        gridLayout->setContentsMargins(100, -1, 100, -1);
        dynodeWidget = new ControlDemo(MyControl);
        dynodeWidget->setObjectName(QStringLiteral("dynodeWidget"));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        dynodeWidget->setPalette(palette);

        gridLayout->addWidget(dynodeWidget, 0, 0, 1, 1);

        iconWidget = new ControlDemo(MyControl);
        iconWidget->setObjectName(QStringLiteral("iconWidget"));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Base, brush);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush);
        iconWidget->setPalette(palette1);

        gridLayout->addWidget(iconWidget, 0, 1, 1, 1);

        increaseWidget = new ControlDemo(MyControl);
        increaseWidget->setObjectName(QStringLiteral("increaseWidget"));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Base, brush);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush);
        increaseWidget->setPalette(palette2);

        gridLayout->addWidget(increaseWidget, 0, 2, 1, 1);

        tempterature = new ControlDemo(MyControl);
        tempterature->setObjectName(QStringLiteral("tempterature"));

        gridLayout->addWidget(tempterature, 1, 0, 1, 1);

        DFWidget = new ControlDemo(MyControl);
        DFWidget->setObjectName(QStringLiteral("DFWidget"));

        gridLayout->addWidget(DFWidget, 1, 1, 1, 1);

        ZSQWidgeht = new ControlDemo(MyControl);
        ZSQWidgeht->setObjectName(QStringLiteral("ZSQWidgeht"));

        gridLayout->addWidget(ZSQWidgeht, 1, 2, 1, 1);


        retranslateUi(MyControl);

        QMetaObject::connectSlotsByName(MyControl);
    } // setupUi

    void retranslateUi(QWidget *MyControl)
    {
        MyControl->setWindowTitle(QApplication::translate("MyControl", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyControl: public Ui_MyControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYCONTROL_H
