/********************************************************************************
** Form generated from reading UI file 'ControlDemo.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLDEMO_H
#define UI_CONTROLDEMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QSwitchButton.h"

QT_BEGIN_NAMESPACE

class Ui_ControlDemo
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QLabel *descriptLaber;
    QFrame *line_2;
    QVBoxLayout *verticalLayout_2;
    QSwitchButton *switchBtn;

    void setupUi(QWidget *ControlDemo)
    {
        if (ControlDemo->objectName().isEmpty())
            ControlDemo->setObjectName(QStringLiteral("ControlDemo"));
        ControlDemo->resize(400, 333);
        verticalLayout = new QVBoxLayout(ControlDemo);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(ControlDemo);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(30);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        line = new QFrame(ControlDemo);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEdit = new QLineEdit(ControlDemo);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 180));
        QFont font1;
        font1.setPointSize(20);
        lineEdit->setFont(font1);
        lineEdit->setFrame(false);
        lineEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(lineEdit);

        descriptLaber = new QLabel(ControlDemo);
        descriptLaber->setObjectName(QStringLiteral("descriptLaber"));
        QFont font2;
        font2.setPointSize(15);
        descriptLaber->setFont(font2);

        horizontalLayout->addWidget(descriptLaber);


        verticalLayout->addLayout(horizontalLayout);

        line_2 = new QFrame(ControlDemo);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(50, 40, 0, -1);
        switchBtn = new QSwitchButton(ControlDemo);
        switchBtn->setObjectName(QStringLiteral("switchBtn"));

        verticalLayout_2->addWidget(switchBtn);


        verticalLayout->addLayout(verticalLayout_2);


        retranslateUi(ControlDemo);

        QMetaObject::connectSlotsByName(ControlDemo);
    } // setupUi

    void retranslateUi(QWidget *ControlDemo)
    {
        ControlDemo->setWindowTitle(QApplication::translate("ControlDemo", "Form", nullptr));
        label->setText(QApplication::translate("ControlDemo", "TextLabel", nullptr));
        descriptLaber->setText(QString());
        switchBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ControlDemo: public Ui_ControlDemo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLDEMO_H
