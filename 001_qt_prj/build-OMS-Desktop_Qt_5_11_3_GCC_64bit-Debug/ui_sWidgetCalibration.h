/********************************************************************************
** Form generated from reading UI file 'sWidgetCalibration.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SWIDGETCALIBRATION_H
#define UI_SWIDGETCALIBRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sWidgetCalibration
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QFrame *line_3;
    QCheckBox *UI_CB_ENABLE;
    QPushButton *UI_PB_CALIBRAT;
    QLineEdit *UI_LE_EXPECT0;
    QLineEdit *UI_LE_EXPECT3;
    QFrame *line;
    QLineEdit *UI_LE_EXPECT2;
    QLineEdit *UI_LE_EXPECT5;
    QLineEdit *UI_LE_EXPECT4;
    QLineEdit *UI_LE_EXPECT1;
    QLabel *label_2;
    QLineEdit *UI_LE_CURRENT5;
    QLineEdit *UI_LE_CURRENT2;
    QLineEdit *UI_LE_PLOY_D;
    QLineEdit *UI_LE_CURRENT4;
    QLineEdit *UI_LE_CURRENT1;
    QLabel *label_4;
    QLabel *label_3;
    QLineEdit *UI_LE_CURRENT3;
    QLineEdit *UI_LE_CURRENT0;
    QLineEdit *UI_LE_MassExtension;
    QFrame *line_2;
    QLabel *label;

    void setupUi(QWidget *sWidgetCalibration)
    {
        if (sWidgetCalibration->objectName().isEmpty())
            sWidgetCalibration->setObjectName(QStringLiteral("sWidgetCalibration"));
        sWidgetCalibration->resize(401, 239);
        gridLayout = new QGridLayout(sWidgetCalibration);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        line_3 = new QFrame(sWidgetCalibration);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_3);

        UI_CB_ENABLE = new QCheckBox(sWidgetCalibration);
        UI_CB_ENABLE->setObjectName(QStringLiteral("UI_CB_ENABLE"));

        horizontalLayout_2->addWidget(UI_CB_ENABLE);

        UI_PB_CALIBRAT = new QPushButton(sWidgetCalibration);
        UI_PB_CALIBRAT->setObjectName(QStringLiteral("UI_PB_CALIBRAT"));

        horizontalLayout_2->addWidget(UI_PB_CALIBRAT);


        gridLayout->addLayout(horizontalLayout_2, 8, 3, 2, 1);

        UI_LE_EXPECT0 = new QLineEdit(sWidgetCalibration);
        UI_LE_EXPECT0->setObjectName(QStringLiteral("UI_LE_EXPECT0"));

        gridLayout->addWidget(UI_LE_EXPECT0, 1, 0, 1, 3);

        UI_LE_EXPECT3 = new QLineEdit(sWidgetCalibration);
        UI_LE_EXPECT3->setObjectName(QStringLiteral("UI_LE_EXPECT3"));

        gridLayout->addWidget(UI_LE_EXPECT3, 4, 0, 1, 3);

        line = new QFrame(sWidgetCalibration);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 7, 0, 1, 4);

        UI_LE_EXPECT2 = new QLineEdit(sWidgetCalibration);
        UI_LE_EXPECT2->setObjectName(QStringLiteral("UI_LE_EXPECT2"));

        gridLayout->addWidget(UI_LE_EXPECT2, 3, 0, 1, 3);

        UI_LE_EXPECT5 = new QLineEdit(sWidgetCalibration);
        UI_LE_EXPECT5->setObjectName(QStringLiteral("UI_LE_EXPECT5"));

        gridLayout->addWidget(UI_LE_EXPECT5, 6, 0, 1, 3);

        UI_LE_EXPECT4 = new QLineEdit(sWidgetCalibration);
        UI_LE_EXPECT4->setObjectName(QStringLiteral("UI_LE_EXPECT4"));

        gridLayout->addWidget(UI_LE_EXPECT4, 5, 0, 1, 3);

        UI_LE_EXPECT1 = new QLineEdit(sWidgetCalibration);
        UI_LE_EXPECT1->setObjectName(QStringLiteral("UI_LE_EXPECT1"));

        gridLayout->addWidget(UI_LE_EXPECT1, 2, 0, 1, 3);

        label_2 = new QLabel(sWidgetCalibration);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 0, 3, 1, 1);

        UI_LE_CURRENT5 = new QLineEdit(sWidgetCalibration);
        UI_LE_CURRENT5->setObjectName(QStringLiteral("UI_LE_CURRENT5"));

        gridLayout->addWidget(UI_LE_CURRENT5, 6, 3, 1, 1);

        UI_LE_CURRENT2 = new QLineEdit(sWidgetCalibration);
        UI_LE_CURRENT2->setObjectName(QStringLiteral("UI_LE_CURRENT2"));

        gridLayout->addWidget(UI_LE_CURRENT2, 3, 3, 1, 1);

        UI_LE_PLOY_D = new QLineEdit(sWidgetCalibration);
        UI_LE_PLOY_D->setObjectName(QStringLiteral("UI_LE_PLOY_D"));

        gridLayout->addWidget(UI_LE_PLOY_D, 9, 2, 1, 1);

        UI_LE_CURRENT4 = new QLineEdit(sWidgetCalibration);
        UI_LE_CURRENT4->setObjectName(QStringLiteral("UI_LE_CURRENT4"));

        gridLayout->addWidget(UI_LE_CURRENT4, 5, 3, 1, 1);

        UI_LE_CURRENT1 = new QLineEdit(sWidgetCalibration);
        UI_LE_CURRENT1->setObjectName(QStringLiteral("UI_LE_CURRENT1"));

        gridLayout->addWidget(UI_LE_CURRENT1, 2, 3, 1, 1);

        label_4 = new QLabel(sWidgetCalibration);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 8, 0, 1, 1);

        label_3 = new QLabel(sWidgetCalibration);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 8, 2, 1, 1);

        UI_LE_CURRENT3 = new QLineEdit(sWidgetCalibration);
        UI_LE_CURRENT3->setObjectName(QStringLiteral("UI_LE_CURRENT3"));

        gridLayout->addWidget(UI_LE_CURRENT3, 4, 3, 1, 1);

        UI_LE_CURRENT0 = new QLineEdit(sWidgetCalibration);
        UI_LE_CURRENT0->setObjectName(QStringLiteral("UI_LE_CURRENT0"));

        gridLayout->addWidget(UI_LE_CURRENT0, 1, 3, 1, 1);

        UI_LE_MassExtension = new QLineEdit(sWidgetCalibration);
        UI_LE_MassExtension->setObjectName(QStringLiteral("UI_LE_MassExtension"));

        gridLayout->addWidget(UI_LE_MassExtension, 9, 0, 1, 1);

        line_2 = new QFrame(sWidgetCalibration);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 8, 1, 2, 1);

        label = new QLabel(sWidgetCalibration);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 3);


        retranslateUi(sWidgetCalibration);

        QMetaObject::connectSlotsByName(sWidgetCalibration);
    } // setupUi

    void retranslateUi(QWidget *sWidgetCalibration)
    {
        sWidgetCalibration->setWindowTitle(QApplication::translate("sWidgetCalibration", "Form", nullptr));
        UI_CB_ENABLE->setText(QApplication::translate("sWidgetCalibration", "\345\220\257\347\224\250\346\240\241\346\255\243\345\217\202\346\225\260", nullptr));
        UI_PB_CALIBRAT->setText(QApplication::translate("sWidgetCalibration", "\351\207\215\346\226\260\346\240\241\346\255\243", nullptr));
        label_2->setText(QApplication::translate("sWidgetCalibration", "\345\256\236\351\231\205\350\264\250\351\207\217\345\200\274", nullptr));
        UI_LE_PLOY_D->setText(QApplication::translate("sWidgetCalibration", "3", nullptr));
        label_4->setText(QApplication::translate("sWidgetCalibration", "\350\264\250\351\207\217\346\213\223\345\261\225\357\274\210Th\357\274\211\357\274\232", nullptr));
        label_3->setText(QApplication::translate("sWidgetCalibration", "\346\213\237\345\220\210\351\230\266\346\225\260\357\274\232", nullptr));
        label->setText(QApplication::translate("sWidgetCalibration", "\347\220\206\350\256\272\350\264\250\351\207\217\345\200\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sWidgetCalibration: public Ui_sWidgetCalibration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SWIDGETCALIBRATION_H
