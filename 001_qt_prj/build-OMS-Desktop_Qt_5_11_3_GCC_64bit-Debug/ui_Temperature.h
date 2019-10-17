/********************************************************************************
** Form generated from reading UI file 'Temperature.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEMPERATURE_H
#define UI_TEMPERATURE_H

#include <QSwitchButton.h>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Temperature
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSwitchButton *switchBtn;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSlider *verticalSlider;

    void setupUi(QWidget *Temperature)
    {
        if (Temperature->objectName().isEmpty())
            Temperature->setObjectName(QStringLiteral("Temperature"));
        Temperature->resize(210, 377);
        verticalLayout = new QVBoxLayout(Temperature);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_4 = new QLabel(Temperature);
        label_4->setObjectName(QStringLiteral("label_4"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setMinimumSize(QSize(0, 50));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_4);

        line_2 = new QFrame(Temperature);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(Temperature);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(70, 50));
        label_2->setMaximumSize(QSize(70, 16777215));
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_2);

        switchBtn = new QSwitchButton(Temperature);
        switchBtn->setObjectName(QStringLiteral("switchBtn"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(switchBtn->sizePolicy().hasHeightForWidth());
        switchBtn->setSizePolicy(sizePolicy1);
        switchBtn->setMinimumSize(QSize(100, 50));
        switchBtn->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(switchBtn);


        verticalLayout->addLayout(horizontalLayout_2);

        line = new QFrame(Temperature);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(Temperature);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(40, 0));
        label->setMaximumSize(QSize(60, 16777215));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        verticalSlider = new QSlider(Temperature);
        verticalSlider->setObjectName(QStringLiteral("verticalSlider"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(verticalSlider->sizePolicy().hasHeightForWidth());
        verticalSlider->setSizePolicy(sizePolicy2);
        verticalSlider->setMinimumSize(QSize(60, 0));
        verticalSlider->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(verticalSlider);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Temperature);

        QMetaObject::connectSlotsByName(Temperature);
    } // setupUi

    void retranslateUi(QWidget *Temperature)
    {
        Temperature->setWindowTitle(QApplication::translate("Temperature", "Form", nullptr));
        label_4->setText(QApplication::translate("Temperature", "\345\274\200\345\205\263/\350\260\203\350\212\202", nullptr));
        label_2->setText(QApplication::translate("Temperature", "\345\212\240  \347\203\255", nullptr));
        switchBtn->setText(QString());
        label->setText(QApplication::translate("Temperature", "\346\270\251\345\272\246", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Temperature: public Ui_Temperature {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEMPERATURE_H
