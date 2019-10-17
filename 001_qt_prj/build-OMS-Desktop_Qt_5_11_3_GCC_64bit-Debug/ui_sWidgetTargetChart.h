/********************************************************************************
** Form generated from reading UI file 'sWidgetTargetChart.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SWIDGETTARGETCHART_H
#define UI_SWIDGETTARGETCHART_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sWidgetTargetChart
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QVBoxLayout *UI_LAYOUT_CHART;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_17;
    QLineEdit *UI_LE_MASS;
    QSpacerItem *horizontalSpacer_7;

    void setupUi(QWidget *sWidgetTargetChart)
    {
        if (sWidgetTargetChart->objectName().isEmpty())
            sWidgetTargetChart->setObjectName(QStringLiteral("sWidgetTargetChart"));
        sWidgetTargetChart->resize(150, 150);
        sWidgetTargetChart->setMinimumSize(QSize(150, 150));
        sWidgetTargetChart->setMaximumSize(QSize(150, 150));
        verticalLayout_2 = new QVBoxLayout(sWidgetTargetChart);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        widget = new QWidget(sWidgetTargetChart);
        widget->setObjectName(QStringLiteral("widget"));
        UI_LAYOUT_CHART = new QVBoxLayout(widget);
        UI_LAYOUT_CHART->setObjectName(QStringLiteral("UI_LAYOUT_CHART"));

        verticalLayout_2->addWidget(widget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_17 = new QLabel(sWidgetTargetChart);
        label_17->setObjectName(QStringLiteral("label_17"));

        horizontalLayout->addWidget(label_17);

        UI_LE_MASS = new QLineEdit(sWidgetTargetChart);
        UI_LE_MASS->setObjectName(QStringLiteral("UI_LE_MASS"));

        horizontalLayout->addWidget(UI_LE_MASS);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(sWidgetTargetChart);

        QMetaObject::connectSlotsByName(sWidgetTargetChart);
    } // setupUi

    void retranslateUi(QWidget *sWidgetTargetChart)
    {
        sWidgetTargetChart->setWindowTitle(QApplication::translate("sWidgetTargetChart", "Form", nullptr));
        label_17->setText(QApplication::translate("sWidgetTargetChart", "m/z:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sWidgetTargetChart: public Ui_sWidgetTargetChart {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SWIDGETTARGETCHART_H
