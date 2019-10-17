/********************************************************************************
** Form generated from reading UI file 'massinput.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MASSINPUT_H
#define UI_MASSINPUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MassInput
{
public:
    QGridLayout *gridLayout;
    QWidget *verticalWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QWidget *inputWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit;

    void setupUi(QWidget *MassInput)
    {
        if (MassInput->objectName().isEmpty())
            MassInput->setObjectName(QStringLiteral("MassInput"));
        MassInput->resize(407, 269);
        MassInput->setAutoFillBackground(false);
        MassInput->setStyleSheet(QStringLiteral("background-color:rgb(255, 255, 255);"));
        gridLayout = new QGridLayout(MassInput);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(20, -1, 20, -1);
        verticalWidget = new QWidget(MassInput);
        verticalWidget->setObjectName(QStringLiteral("verticalWidget"));
        verticalLayout = new QVBoxLayout(verticalWidget);
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(100, -1, 100, -1);
        label = new QLabel(verticalWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setStyleSheet(QStringLiteral("border-image: url(:/pathView/images/timg0.jpg);"));

        horizontalLayout_2->addWidget(label);


        verticalLayout->addLayout(horizontalLayout_2);

        inputWidget = new QWidget(verticalWidget);
        inputWidget->setObjectName(QStringLiteral("inputWidget"));
        inputWidget->setMinimumSize(QSize(0, 20));
        horizontalLayout = new QHBoxLayout(inputWidget);
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, -1, 10, -1);
        label_2 = new QLabel(inputWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(0, 20));
        QFont font;
        font.setPointSize(16);
        label_2->setFont(font);

        horizontalLayout->addWidget(label_2);

        lineEdit = new QLineEdit(inputWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 20));
        QFont font1;
        font1.setPointSize(18);
        lineEdit->setFont(font1);
        lineEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addWidget(inputWidget);


        gridLayout->addWidget(verticalWidget, 0, 1, 1, 1);


        retranslateUi(MassInput);

        QMetaObject::connectSlotsByName(MassInput);
    } // setupUi

    void retranslateUi(QWidget *MassInput)
    {
        MassInput->setWindowTitle(QApplication::translate("MassInput", "Form", nullptr));
        label->setText(QString());
        label_2->setText(QApplication::translate("MassInput", "\350\264\250\351\207\217\346\225\260:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MassInput: public Ui_MassInput {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MASSINPUT_H
