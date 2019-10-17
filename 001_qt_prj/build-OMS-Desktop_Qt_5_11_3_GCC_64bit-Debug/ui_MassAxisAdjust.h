/********************************************************************************
** Form generated from reading UI file 'MassAxisAdjust.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MASSAXISADJUST_H
#define UI_MASSAXISADJUST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MassAxisAdjust
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *source1;
    QLineEdit *source2;
    QLineEdit *source3;
    QLineEdit *source4;
    QLineEdit *source5;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLineEdit *target1;
    QLineEdit *target2;
    QLineEdit *target3;
    QLineEdit *target4;
    QLineEdit *target5;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *MassAxisAdjust)
    {
        if (MassAxisAdjust->objectName().isEmpty())
            MassAxisAdjust->setObjectName(QStringLiteral("MassAxisAdjust"));
        MassAxisAdjust->resize(472, 385);
        horizontalLayoutWidget = new QWidget(MassAxisAdjust);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 30, 431, 241));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        source1 = new QLineEdit(horizontalLayoutWidget);
        source1->setObjectName(QStringLiteral("source1"));
        source1->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(source1);

        source2 = new QLineEdit(horizontalLayoutWidget);
        source2->setObjectName(QStringLiteral("source2"));
        source2->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(source2);

        source3 = new QLineEdit(horizontalLayoutWidget);
        source3->setObjectName(QStringLiteral("source3"));
        source3->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(source3);

        source4 = new QLineEdit(horizontalLayoutWidget);
        source4->setObjectName(QStringLiteral("source4"));
        source4->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(source4);

        source5 = new QLineEdit(horizontalLayoutWidget);
        source5->setObjectName(QStringLiteral("source5"));
        source5->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(source5);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        target1 = new QLineEdit(horizontalLayoutWidget);
        target1->setObjectName(QStringLiteral("target1"));
        target1->setMinimumSize(QSize(0, 30));

        verticalLayout_2->addWidget(target1);

        target2 = new QLineEdit(horizontalLayoutWidget);
        target2->setObjectName(QStringLiteral("target2"));
        target2->setMinimumSize(QSize(0, 30));

        verticalLayout_2->addWidget(target2);

        target3 = new QLineEdit(horizontalLayoutWidget);
        target3->setObjectName(QStringLiteral("target3"));
        target3->setMinimumSize(QSize(0, 30));

        verticalLayout_2->addWidget(target3);

        target4 = new QLineEdit(horizontalLayoutWidget);
        target4->setObjectName(QStringLiteral("target4"));
        target4->setMinimumSize(QSize(0, 30));

        verticalLayout_2->addWidget(target4);

        target5 = new QLineEdit(horizontalLayoutWidget);
        target5->setObjectName(QStringLiteral("target5"));
        target5->setMinimumSize(QSize(0, 30));

        verticalLayout_2->addWidget(target5);


        horizontalLayout->addLayout(verticalLayout_2);

        pushButton = new QPushButton(MassAxisAdjust);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(110, 310, 111, 51));
        pushButton_2 = new QPushButton(MassAxisAdjust);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(260, 310, 111, 51));

        retranslateUi(MassAxisAdjust);

        QMetaObject::connectSlotsByName(MassAxisAdjust);
    } // setupUi

    void retranslateUi(QWidget *MassAxisAdjust)
    {
        MassAxisAdjust->setWindowTitle(QApplication::translate("MassAxisAdjust", "Form", nullptr));
        label->setText(QApplication::translate("MassAxisAdjust", "\345\216\237\345\247\213\350\264\250\351\207\217\346\225\260", nullptr));
        label_2->setText(QApplication::translate("MassAxisAdjust", "\347\233\256\346\240\207\350\264\250\351\207\217\346\225\260", nullptr));
        pushButton->setText(QApplication::translate("MassAxisAdjust", "\346\240\241\345\257\271", nullptr));
        pushButton_2->setText(QApplication::translate("MassAxisAdjust", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MassAxisAdjust: public Ui_MassAxisAdjust {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MASSAXISADJUST_H
