/********************************************************************************
** Form generated from reading UI file 'sManualTuning.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMANUALTUNING_H
#define UI_SMANUALTUNING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "myLineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_sManualTuning
{
public:
    QVBoxLayout *verticalLayout_3;
    QWidget *UI_TUNING_GRAPHICS;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *UI_PB_TARGET;
    QPushButton *UI_PB_FULL;
    QSpacerItem *horizontalSpacer_2;
    QWidget *UI_W_CHART;
    QHBoxLayout *UI_LAYOUT_CHART;
    QWidget *UI_W_TARGET_CHART;
    QGridLayout *UI_LAYOUT_TARGET;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_12;
    QLabel *label_20;
    QLineEdit *UI_LE_MASS3;
    QSpacerItem *horizontalSpacer_13;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_17;
    QLineEdit *UI_LE_MASS0;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_19;
    QLineEdit *UI_LE_MASS1;
    QSpacerItem *horizontalSpacer_9;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label_18;
    QLineEdit *UI_LE_MASS2;
    QSpacerItem *horizontalSpacer_11;
    QWidget *widget_3;
    QWidget *UI_W_FILE;
    QVBoxLayout *UI_LAYOUT_FILE;
    QWidget *UI_W_FILEMENU;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *E_FILENAME;
    QPushButton *UI_PB_OK;
    QPushButton *UI_PB_CANCEL;
    QWidget *UI_TUNING_METHOD;
    QHBoxLayout *UI_LAYOUT_TUNING_METHOD;
    QGridLayout *gridLayout;
    myLineEdit *UI_LE_VOLT_RF;
    QLabel *label_6;
    QWidget *widget_12;
    QSpacerItem *verticalSpacer_2;
    QWidget *widget_6;
    QWidget *widget_9;
    QLabel *label_11;
    QLabel *label_10;
    QWidget *widget_2;
    QLabel *label_3;
    myLineEdit *UI_LE_F_CAP_OFF;
    QLabel *label_2;
    myLineEdit *UI_LE_SPEED;
    myLineEdit *UI_LE_FEILD_VOLT;
    QLabel *label_8;
    myLineEdit *UI_LE_VOLT_QARRAY;
    myLineEdit *UI_LE_TIME_CO;
    QLabel *label_14;
    myLineEdit *UI_LE_STARTMASS;
    QSpacerItem *verticalSpacer_3;
    myLineEdit *UI_LE_PHASE_AC;
    myLineEdit *UI_LE_F_CAP_ON;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QLabel *label_7;
    QLabel *label_15;
    QWidget *widget_8;
    myLineEdit *UI_LE_DUTYCYCLE_AC;
    QWidget *widget_4;
    myLineEdit *UI_LE_TIME_E;
    QLabel *label_4;
    QLabel *label_5;
    myLineEdit *UI_LE_OFFSET_AQRRAY;
    QWidget *widget_15;
    QWidget *widget_11;
    QWidget *widget_13;
    myLineEdit *UI_LE_VOLT_AC;
    QLabel *label_13;
    QWidget *widget;
    myLineEdit *UI_LE_ENDMASS;
    QLabel *label_9;
    QWidget *widget_17;
    myLineEdit *UI_LE_TIME_I;
    QWidget *widget_7;
    QLabel *label_16;
    QWidget *widget_5;
    QLabel *label_12;
    QWidget *widget_10;
    QWidget *widget_16;
    QWidget *widget_14;
    myLineEdit *UI_LE_B_CAP;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_5;
    QWidget *UI_W_TUNINGMENU;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *UI_PB_LOADFILE;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *UI_PB_SAVEFILE;
    QSpacerItem *horizontalSpacer_15;
    QPushButton *UI_PB_BASELINE;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *UI_PB_TUNING_FIT;
    QSpacerItem *horizontalSpacer_14;
    QPushButton *UI_PB_TUNING_SCAN;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QWidget *sManualTuning)
    {
        if (sManualTuning->objectName().isEmpty())
            sManualTuning->setObjectName(QStringLiteral("sManualTuning"));
        sManualTuning->resize(1194, 645);
        verticalLayout_3 = new QVBoxLayout(sManualTuning);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        UI_TUNING_GRAPHICS = new QWidget(sManualTuning);
        UI_TUNING_GRAPHICS->setObjectName(QStringLiteral("UI_TUNING_GRAPHICS"));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Light, brush1);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        QBrush brush2(QColor(127, 127, 127, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush2);
        QBrush brush3(QColor(170, 170, 170, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush3);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush1);
        QBrush brush4(QColor(255, 255, 220, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        UI_TUNING_GRAPHICS->setPalette(palette);
        UI_TUNING_GRAPHICS->setAutoFillBackground(true);
        verticalLayout = new QVBoxLayout(UI_TUNING_GRAPHICS);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        UI_PB_TARGET = new QPushButton(UI_TUNING_GRAPHICS);
        UI_PB_TARGET->setObjectName(QStringLiteral("UI_PB_TARGET"));

        horizontalLayout_3->addWidget(UI_PB_TARGET);

        UI_PB_FULL = new QPushButton(UI_TUNING_GRAPHICS);
        UI_PB_FULL->setObjectName(QStringLiteral("UI_PB_FULL"));

        horizontalLayout_3->addWidget(UI_PB_FULL);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_3);

        UI_W_CHART = new QWidget(UI_TUNING_GRAPHICS);
        UI_W_CHART->setObjectName(QStringLiteral("UI_W_CHART"));
        UI_LAYOUT_CHART = new QHBoxLayout(UI_W_CHART);
        UI_LAYOUT_CHART->setObjectName(QStringLiteral("UI_LAYOUT_CHART"));

        verticalLayout->addWidget(UI_W_CHART);

        UI_W_TARGET_CHART = new QWidget(UI_TUNING_GRAPHICS);
        UI_W_TARGET_CHART->setObjectName(QStringLiteral("UI_W_TARGET_CHART"));
        UI_LAYOUT_TARGET = new QGridLayout(UI_W_TARGET_CHART);
        UI_LAYOUT_TARGET->setObjectName(QStringLiteral("UI_LAYOUT_TARGET"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_12);

        label_20 = new QLabel(UI_W_TARGET_CHART);
        label_20->setObjectName(QStringLiteral("label_20"));

        horizontalLayout_7->addWidget(label_20);

        UI_LE_MASS3 = new QLineEdit(UI_W_TARGET_CHART);
        UI_LE_MASS3->setObjectName(QStringLiteral("UI_LE_MASS3"));

        horizontalLayout_7->addWidget(UI_LE_MASS3);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_13);


        UI_LAYOUT_TARGET->addLayout(horizontalLayout_7, 1, 3, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_17 = new QLabel(UI_W_TARGET_CHART);
        label_17->setObjectName(QStringLiteral("label_17"));

        horizontalLayout->addWidget(label_17);

        UI_LE_MASS0 = new QLineEdit(UI_W_TARGET_CHART);
        UI_LE_MASS0->setObjectName(QStringLiteral("UI_LE_MASS0"));

        horizontalLayout->addWidget(UI_LE_MASS0);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);


        UI_LAYOUT_TARGET->addLayout(horizontalLayout, 1, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_8);

        label_19 = new QLabel(UI_W_TARGET_CHART);
        label_19->setObjectName(QStringLiteral("label_19"));

        horizontalLayout_6->addWidget(label_19);

        UI_LE_MASS1 = new QLineEdit(UI_W_TARGET_CHART);
        UI_LE_MASS1->setObjectName(QStringLiteral("UI_LE_MASS1"));

        horizontalLayout_6->addWidget(UI_LE_MASS1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_9);


        UI_LAYOUT_TARGET->addLayout(horizontalLayout_6, 1, 1, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_10);

        label_18 = new QLabel(UI_W_TARGET_CHART);
        label_18->setObjectName(QStringLiteral("label_18"));

        horizontalLayout_5->addWidget(label_18);

        UI_LE_MASS2 = new QLineEdit(UI_W_TARGET_CHART);
        UI_LE_MASS2->setObjectName(QStringLiteral("UI_LE_MASS2"));

        horizontalLayout_5->addWidget(UI_LE_MASS2);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_11);


        UI_LAYOUT_TARGET->addLayout(horizontalLayout_5, 1, 2, 1, 1);

        widget_3 = new QWidget(UI_W_TARGET_CHART);
        widget_3->setObjectName(QStringLiteral("widget_3"));

        UI_LAYOUT_TARGET->addWidget(widget_3, 0, 0, 1, 1);


        verticalLayout->addWidget(UI_W_TARGET_CHART);

        UI_W_FILE = new QWidget(UI_TUNING_GRAPHICS);
        UI_W_FILE->setObjectName(QStringLiteral("UI_W_FILE"));
        UI_LAYOUT_FILE = new QVBoxLayout(UI_W_FILE);
        UI_LAYOUT_FILE->setObjectName(QStringLiteral("UI_LAYOUT_FILE"));
        UI_LAYOUT_FILE->setContentsMargins(0, 0, 0, 0);
        UI_W_FILEMENU = new QWidget(UI_W_FILE);
        UI_W_FILEMENU->setObjectName(QStringLiteral("UI_W_FILEMENU"));
        horizontalLayout_2 = new QHBoxLayout(UI_W_FILEMENU);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(9, 0, 9, 0);
        E_FILENAME = new QLineEdit(UI_W_FILEMENU);
        E_FILENAME->setObjectName(QStringLiteral("E_FILENAME"));
        E_FILENAME->setMinimumSize(QSize(0, 40));
        E_FILENAME->setMaximumSize(QSize(16777215, 40));
        QPalette palette1;
        QBrush brush5(QColor(228, 218, 208, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush5);
        QBrush brush6(QColor(240, 240, 240, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush6);
        E_FILENAME->setPalette(palette1);
        QFont font;
        font.setFamily(QStringLiteral("Microsoft YaHei UI"));
        font.setPointSize(12);
        font.setBold(false);
        font.setWeight(50);
        E_FILENAME->setFont(font);
        E_FILENAME->setAutoFillBackground(true);
        E_FILENAME->setReadOnly(true);

        horizontalLayout_2->addWidget(E_FILENAME);

        UI_PB_OK = new QPushButton(UI_W_FILEMENU);
        UI_PB_OK->setObjectName(QStringLiteral("UI_PB_OK"));
        UI_PB_OK->setMinimumSize(QSize(96, 32));

        horizontalLayout_2->addWidget(UI_PB_OK);

        UI_PB_CANCEL = new QPushButton(UI_W_FILEMENU);
        UI_PB_CANCEL->setObjectName(QStringLiteral("UI_PB_CANCEL"));
        UI_PB_CANCEL->setMinimumSize(QSize(96, 32));

        horizontalLayout_2->addWidget(UI_PB_CANCEL);


        UI_LAYOUT_FILE->addWidget(UI_W_FILEMENU);


        verticalLayout->addWidget(UI_W_FILE);


        verticalLayout_3->addWidget(UI_TUNING_GRAPHICS);

        UI_TUNING_METHOD = new QWidget(sManualTuning);
        UI_TUNING_METHOD->setObjectName(QStringLiteral("UI_TUNING_METHOD"));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Light, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Dark, brush2);
        palette2.setBrush(QPalette::Active, QPalette::Mid, brush3);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush);
        palette2.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette2.setBrush(QPalette::Active, QPalette::AlternateBase, brush1);
        palette2.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette2.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Dark, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::Mid, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette2.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Dark, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Mid, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette2.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        UI_TUNING_METHOD->setPalette(palette2);
        UI_TUNING_METHOD->setAutoFillBackground(true);
        UI_LAYOUT_TUNING_METHOD = new QHBoxLayout(UI_TUNING_METHOD);
        UI_LAYOUT_TUNING_METHOD->setObjectName(QStringLiteral("UI_LAYOUT_TUNING_METHOD"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(16);
        gridLayout->setVerticalSpacing(0);
        gridLayout->setContentsMargins(24, -1, 24, -1);
        UI_LE_VOLT_RF = new myLineEdit(UI_TUNING_METHOD);
        UI_LE_VOLT_RF->setObjectName(QStringLiteral("UI_LE_VOLT_RF"));
        UI_LE_VOLT_RF->setMinimumSize(QSize(0, 24));
        UI_LE_VOLT_RF->setStyleSheet(QStringLiteral("background:transparent;border-width:0;border-style:outset"));

        gridLayout->addWidget(UI_LE_VOLT_RF, 4, 7, 1, 1);

        label_6 = new QLabel(UI_TUNING_METHOD);
        label_6->setObjectName(QStringLiteral("label_6"));
        QFont font1;
        font1.setPointSize(9);
        label_6->setFont(font1);

        gridLayout->addWidget(label_6, 4, 2, 1, 1);

        widget_12 = new QWidget(UI_TUNING_METHOD);
        widget_12->setObjectName(QStringLiteral("widget_12"));
        widget_12->setMinimumSize(QSize(0, 1));
        widget_12->setMaximumSize(QSize(16777215, 1));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Button, brush);
        palette3.setBrush(QPalette::Active, QPalette::Light, brush);
        palette3.setBrush(QPalette::Active, QPalette::Midlight, brush);
        palette3.setBrush(QPalette::Active, QPalette::Dark, brush);
        palette3.setBrush(QPalette::Active, QPalette::Mid, brush);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette3.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush);
        palette3.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette3.setBrush(QPalette::Active, QPalette::AlternateBase, brush);
        palette3.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette3.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Midlight, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Dark, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Mid, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette3.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Dark, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Mid, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette3.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        widget_12->setPalette(palette3);
        widget_12->setAutoFillBackground(true);

        gridLayout->addWidget(widget_12, 8, 4, 1, 2);

        verticalSpacer_2 = new QSpacerItem(20, 24, QSizePolicy::Minimum, QSizePolicy::Maximum);

        gridLayout->addItem(verticalSpacer_2, 6, 0, 1, 1);

        widget_6 = new QWidget(UI_TUNING_METHOD);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        widget_6->setMinimumSize(QSize(0, 1));
        widget_6->setMaximumSize(QSize(16777215, 1));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette4.setBrush(QPalette::Active, QPalette::Button, brush);
        palette4.setBrush(QPalette::Active, QPalette::Light, brush);
        palette4.setBrush(QPalette::Active, QPalette::Midlight, brush);
        palette4.setBrush(QPalette::Active, QPalette::Dark, brush);
        palette4.setBrush(QPalette::Active, QPalette::Mid, brush);
        palette4.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette4.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette4.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette4.setBrush(QPalette::Active, QPalette::Base, brush);
        palette4.setBrush(QPalette::Active, QPalette::Window, brush);
        palette4.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette4.setBrush(QPalette::Active, QPalette::AlternateBase, brush);
        palette4.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette4.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Midlight, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Dark, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Mid, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette4.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Dark, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Mid, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette4.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        widget_6->setPalette(palette4);
        widget_6->setAutoFillBackground(true);

        gridLayout->addWidget(widget_6, 5, 0, 1, 2);

        widget_9 = new QWidget(UI_TUNING_METHOD);
        widget_9->setObjectName(QStringLiteral("widget_9"));
        widget_9->setMinimumSize(QSize(0, 1));
        widget_9->setMaximumSize(QSize(16777215, 1));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette5.setBrush(QPalette::Active, QPalette::Button, brush);
        palette5.setBrush(QPalette::Active, QPalette::Light, brush);
        palette5.setBrush(QPalette::Active, QPalette::Midlight, brush);
        palette5.setBrush(QPalette::Active, QPalette::Dark, brush);
        palette5.setBrush(QPalette::Active, QPalette::Mid, brush);
        palette5.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette5.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette5.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette5.setBrush(QPalette::Active, QPalette::Base, brush);
        palette5.setBrush(QPalette::Active, QPalette::Window, brush);
        palette5.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette5.setBrush(QPalette::Active, QPalette::AlternateBase, brush);
        palette5.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette5.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette5.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Midlight, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Dark, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Mid, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette5.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette5.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette5.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette5.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Dark, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Mid, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette5.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette5.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        widget_9->setPalette(palette5);
        widget_9->setAutoFillBackground(true);

        gridLayout->addWidget(widget_9, 5, 6, 1, 2);

        label_11 = new QLabel(UI_TUNING_METHOD);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setFont(font1);

        gridLayout->addWidget(label_11, 4, 6, 1, 1);

        label_10 = new QLabel(UI_TUNING_METHOD);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setFont(font1);

        gridLayout->addWidget(label_10, 7, 4, 1, 1);

        widget_2 = new QWidget(UI_TUNING_METHOD);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setMinimumSize(QSize(0, 1));
        widget_2->setMaximumSize(QSize(16777215, 1));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette6.setBrush(QPalette::Active, QPalette::Button, brush);
        palette6.setBrush(QPalette::Active, QPalette::Light, brush);
        palette6.setBrush(QPalette::Active, QPalette::Midlight, brush);
        palette6.setBrush(QPalette::Active, QPalette::Dark, brush);
        palette6.setBrush(QPalette::Active, QPalette::Mid, brush);
        palette6.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette6.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette6.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette6.setBrush(QPalette::Active, QPalette::Base, brush);
        palette6.setBrush(QPalette::Active, QPalette::Window, brush);
        palette6.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette6.setBrush(QPalette::Active, QPalette::AlternateBase, brush);
        palette6.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette6.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette6.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Midlight, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Dark, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Mid, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette6.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette6.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette6.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette6.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::Dark, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::Mid, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette6.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette6.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        widget_2->setPalette(palette6);
        widget_2->setAutoFillBackground(true);

        gridLayout->addWidget(widget_2, 2, 0, 1, 2);

        label_3 = new QLabel(UI_TUNING_METHOD);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font1);

        gridLayout->addWidget(label_3, 1, 4, 1, 1);

        UI_LE_F_CAP_OFF = new myLineEdit(UI_TUNING_METHOD);
        UI_LE_F_CAP_OFF->setObjectName(QStringLiteral("UI_LE_F_CAP_OFF"));
        UI_LE_F_CAP_OFF->setMinimumSize(QSize(0, 24));
        UI_LE_F_CAP_OFF->setStyleSheet(QStringLiteral("background:transparent;border-width:0;border-style:outset"));

        gridLayout->addWidget(UI_LE_F_CAP_OFF, 7, 3, 1, 1);

        label_2 = new QLabel(UI_TUNING_METHOD);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font1);

        gridLayout->addWidget(label_2, 1, 2, 1, 1);

        UI_LE_SPEED = new myLineEdit(UI_TUNING_METHOD);
        UI_LE_SPEED->setObjectName(QStringLiteral("UI_LE_SPEED"));
        UI_LE_SPEED->setMinimumSize(QSize(0, 24));
        UI_LE_SPEED->setStyleSheet(QStringLiteral("background:transparent;border-width:0;border-style:outset"));

        gridLayout->addWidget(UI_LE_SPEED, 1, 7, 1, 1);

        UI_LE_FEILD_VOLT = new myLineEdit(UI_TUNING_METHOD);
        UI_LE_FEILD_VOLT->setObjectName(QStringLiteral("UI_LE_FEILD_VOLT"));
        UI_LE_FEILD_VOLT->setMinimumSize(QSize(0, 24));
        UI_LE_FEILD_VOLT->setStyleSheet(QStringLiteral("background:transparent;border-width:0;border-style:outset"));

        gridLayout->addWidget(UI_LE_FEILD_VOLT, 7, 7, 1, 1);

        label_8 = new QLabel(UI_TUNING_METHOD);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setFont(font1);

        gridLayout->addWidget(label_8, 7, 0, 1, 1);

        UI_LE_VOLT_QARRAY = new myLineEdit(UI_TUNING_METHOD);
        UI_LE_VOLT_QARRAY->setObjectName(QStringLiteral("UI_LE_VOLT_QARRAY"));
        UI_LE_VOLT_QARRAY->setMinimumSize(QSize(0, 24));
        UI_LE_VOLT_QARRAY->setStyleSheet(QStringLiteral("background:transparent;border-width:0;border-style:outset"));

        gridLayout->addWidget(UI_LE_VOLT_QARRAY, 10, 3, 1, 1);

        UI_LE_TIME_CO = new myLineEdit(UI_TUNING_METHOD);
        UI_LE_TIME_CO->setObjectName(QStringLiteral("UI_LE_TIME_CO"));
        UI_LE_TIME_CO->setMinimumSize(QSize(0, 24));
        UI_LE_TIME_CO->setStyleSheet(QStringLiteral("background:transparent;border-width:0;border-style:outset"));

        gridLayout->addWidget(UI_LE_TIME_CO, 1, 3, 1, 1);

        label_14 = new QLabel(UI_TUNING_METHOD);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setFont(font1);

        gridLayout->addWidget(label_14, 10, 0, 1, 1);

        UI_LE_STARTMASS = new myLineEdit(UI_TUNING_METHOD);
        UI_LE_STARTMASS->setObjectName(QStringLiteral("UI_LE_STARTMASS"));
        UI_LE_STARTMASS->setMinimumSize(QSize(0, 24));
        UI_LE_STARTMASS->setStyleSheet(QStringLiteral("background:transparent;border-width:0;border-style:outset"));

        gridLayout->addWidget(UI_LE_STARTMASS, 10, 5, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 24, QSizePolicy::Minimum, QSizePolicy::Maximum);

        gridLayout->addItem(verticalSpacer_3, 9, 0, 1, 1);

        UI_LE_PHASE_AC = new myLineEdit(UI_TUNING_METHOD);
        UI_LE_PHASE_AC->setObjectName(QStringLiteral("UI_LE_PHASE_AC"));
        UI_LE_PHASE_AC->setMinimumSize(QSize(0, 24));
        UI_LE_PHASE_AC->setStyleSheet(QStringLiteral("background:transparent;border-width:0;border-style:outset"));

        gridLayout->addWidget(UI_LE_PHASE_AC, 4, 1, 1, 1);

        UI_LE_F_CAP_ON = new myLineEdit(UI_TUNING_METHOD);
        UI_LE_F_CAP_ON->setObjectName(QStringLiteral("UI_LE_F_CAP_ON"));
        UI_LE_F_CAP_ON->setMinimumSize(QSize(0, 24));
        UI_LE_F_CAP_ON->setStyleSheet(QStringLiteral("background:transparent;border-width:0;border-style:outset"));

        gridLayout->addWidget(UI_LE_F_CAP_ON, 7, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 24, QSizePolicy::Minimum, QSizePolicy::Maximum);

        gridLayout->addItem(verticalSpacer, 3, 0, 1, 1);

        label = new QLabel(UI_TUNING_METHOD);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font1);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        label_7 = new QLabel(UI_TUNING_METHOD);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font1);

        gridLayout->addWidget(label_7, 4, 4, 1, 1);

        label_15 = new QLabel(UI_TUNING_METHOD);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setFont(font1);

        gridLayout->addWidget(label_15, 10, 2, 1, 1);

        widget_8 = new QWidget(UI_TUNING_METHOD);
        widget_8->setObjectName(QStringLiteral("widget_8"));
        widget_8->setMinimumSize(QSize(0, 1));
        widget_8->setMaximumSize(QSize(16777215, 1));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette7.setBrush(QPalette::Active, QPalette::Button, brush);
        palette7.setBrush(QPalette::Active, QPalette::Light, brush);
        palette7.setBrush(QPalette::Active, QPalette::Midlight, brush);
        palette7.setBrush(QPalette::Active, QPalette::Dark, brush);
        palette7.setBrush(QPalette::Active, QPalette::Mid, brush);
        palette7.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette7.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette7.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette7.setBrush(QPalette::Active, QPalette::Base, brush);
        palette7.setBrush(QPalette::Active, QPalette::Window, brush);
        palette7.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette7.setBrush(QPalette::Active, QPalette::AlternateBase, brush);
        palette7.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette7.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette7.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Midlight, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Dark, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Mid, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette7.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette7.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette7.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette7.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::Dark, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::Mid, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette7.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette7.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        widget_8->setPalette(palette7);
        widget_8->setAutoFillBackground(true);

        gridLayout->addWidget(widget_8, 5, 4, 1, 2);

        UI_LE_DUTYCYCLE_AC = new myLineEdit(UI_TUNING_METHOD);
        UI_LE_DUTYCYCLE_AC->setObjectName(QStringLiteral("UI_LE_DUTYCYCLE_AC"));
        UI_LE_DUTYCYCLE_AC->setMinimumSize(QSize(0, 24));
        UI_LE_DUTYCYCLE_AC->setStyleSheet(QStringLiteral("background:transparent;border-width:0;border-style:outset"));

        gridLayout->addWidget(UI_LE_DUTYCYCLE_AC, 4, 3, 1, 1);

        widget_4 = new QWidget(UI_TUNING_METHOD);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setMinimumSize(QSize(0, 1));
        widget_4->setMaximumSize(QSize(16777215, 1));
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette8.setBrush(QPalette::Active, QPalette::Button, brush);
        palette8.setBrush(QPalette::Active, QPalette::Light, brush);
        palette8.setBrush(QPalette::Active, QPalette::Midlight, brush);
        palette8.setBrush(QPalette::Active, QPalette::Dark, brush);
        palette8.setBrush(QPalette::Active, QPalette::Mid, brush);
        palette8.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette8.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette8.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette8.setBrush(QPalette::Active, QPalette::Base, brush);
        palette8.setBrush(QPalette::Active, QPalette::Window, brush);
        palette8.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette8.setBrush(QPalette::Active, QPalette::AlternateBase, brush);
        palette8.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette8.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette8.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::Midlight, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::Dark, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::Mid, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette8.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette8.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette8.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette8.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::Dark, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::Mid, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette8.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette8.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        widget_4->setPalette(palette8);
        widget_4->setAutoFillBackground(true);

        gridLayout->addWidget(widget_4, 2, 4, 1, 2);

        UI_LE_TIME_E = new myLineEdit(UI_TUNING_METHOD);
        UI_LE_TIME_E->setObjectName(QStringLiteral("UI_LE_TIME_E"));
        UI_LE_TIME_E->setMinimumSize(QSize(0, 24));
        UI_LE_TIME_E->setStyleSheet(QStringLiteral("background:transparent;border-width:0;border-style:outset"));

        gridLayout->addWidget(UI_LE_TIME_E, 1, 5, 1, 1);

        label_4 = new QLabel(UI_TUNING_METHOD);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font1);

        gridLayout->addWidget(label_4, 1, 6, 1, 1);

        label_5 = new QLabel(UI_TUNING_METHOD);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font1);

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        UI_LE_OFFSET_AQRRAY = new myLineEdit(UI_TUNING_METHOD);
        UI_LE_OFFSET_AQRRAY->setObjectName(QStringLiteral("UI_LE_OFFSET_AQRRAY"));
        UI_LE_OFFSET_AQRRAY->setMinimumSize(QSize(0, 24));
        UI_LE_OFFSET_AQRRAY->setStyleSheet(QStringLiteral("background:transparent;border-width:0;border-style:outset"));

        gridLayout->addWidget(UI_LE_OFFSET_AQRRAY, 10, 1, 1, 1);

        widget_15 = new QWidget(UI_TUNING_METHOD);
        widget_15->setObjectName(QStringLiteral("widget_15"));
        widget_15->setMinimumSize(QSize(0, 1));
        widget_15->setMaximumSize(QSize(16777215, 1));
        QPalette palette9;
        palette9.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette9.setBrush(QPalette::Active, QPalette::Button, brush);
        palette9.setBrush(QPalette::Active, QPalette::Light, brush);
        palette9.setBrush(QPalette::Active, QPalette::Midlight, brush);
        palette9.setBrush(QPalette::Active, QPalette::Dark, brush);
        palette9.setBrush(QPalette::Active, QPalette::Mid, brush);
        palette9.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette9.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette9.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette9.setBrush(QPalette::Active, QPalette::Base, brush);
        palette9.setBrush(QPalette::Active, QPalette::Window, brush);
        palette9.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette9.setBrush(QPalette::Active, QPalette::AlternateBase, brush);
        palette9.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette9.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette9.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::Midlight, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::Dark, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::Mid, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette9.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette9.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette9.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette9.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::Dark, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::Mid, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette9.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette9.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        widget_15->setPalette(palette9);
        widget_15->setAutoFillBackground(true);

        gridLayout->addWidget(widget_15, 12, 2, 1, 2);

        widget_11 = new QWidget(UI_TUNING_METHOD);
        widget_11->setObjectName(QStringLiteral("widget_11"));
        widget_11->setMinimumSize(QSize(0, 1));
        widget_11->setMaximumSize(QSize(16777215, 1));
        QPalette palette10;
        palette10.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette10.setBrush(QPalette::Active, QPalette::Button, brush);
        palette10.setBrush(QPalette::Active, QPalette::Light, brush);
        palette10.setBrush(QPalette::Active, QPalette::Midlight, brush);
        palette10.setBrush(QPalette::Active, QPalette::Dark, brush);
        palette10.setBrush(QPalette::Active, QPalette::Mid, brush);
        palette10.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette10.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette10.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette10.setBrush(QPalette::Active, QPalette::Base, brush);
        palette10.setBrush(QPalette::Active, QPalette::Window, brush);
        palette10.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette10.setBrush(QPalette::Active, QPalette::AlternateBase, brush);
        palette10.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette10.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette10.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette10.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette10.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette10.setBrush(QPalette::Inactive, QPalette::Midlight, brush);
        palette10.setBrush(QPalette::Inactive, QPalette::Dark, brush);
        palette10.setBrush(QPalette::Inactive, QPalette::Mid, brush);
        palette10.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette10.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette10.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette10.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette10.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette10.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette10.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush);
        palette10.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette10.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette10.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette10.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette10.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette10.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        palette10.setBrush(QPalette::Disabled, QPalette::Dark, brush);
        palette10.setBrush(QPalette::Disabled, QPalette::Mid, brush);
        palette10.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette10.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette10.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette10.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette10.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette10.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette10.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush);
        palette10.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette10.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        widget_11->setPalette(palette10);
        widget_11->setAutoFillBackground(true);

        gridLayout->addWidget(widget_11, 8, 2, 1, 2);

        widget_13 = new QWidget(UI_TUNING_METHOD);
        widget_13->setObjectName(QStringLiteral("widget_13"));
        widget_13->setMinimumSize(QSize(0, 1));
        widget_13->setMaximumSize(QSize(16777215, 1));
        QPalette palette11;
        palette11.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette11.setBrush(QPalette::Active, QPalette::Button, brush);
        palette11.setBrush(QPalette::Active, QPalette::Light, brush);
        palette11.setBrush(QPalette::Active, QPalette::Midlight, brush);
        palette11.setBrush(QPalette::Active, QPalette::Dark, brush);
        palette11.setBrush(QPalette::Active, QPalette::Mid, brush);
        palette11.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette11.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette11.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette11.setBrush(QPalette::Active, QPalette::Base, brush);
        palette11.setBrush(QPalette::Active, QPalette::Window, brush);
        palette11.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette11.setBrush(QPalette::Active, QPalette::AlternateBase, brush);
        palette11.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette11.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette11.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette11.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette11.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette11.setBrush(QPalette::Inactive, QPalette::Midlight, brush);
        palette11.setBrush(QPalette::Inactive, QPalette::Dark, brush);
        palette11.setBrush(QPalette::Inactive, QPalette::Mid, brush);
        palette11.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette11.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette11.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette11.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette11.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette11.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette11.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush);
        palette11.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette11.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette11.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette11.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette11.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette11.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        palette11.setBrush(QPalette::Disabled, QPalette::Dark, brush);
        palette11.setBrush(QPalette::Disabled, QPalette::Mid, brush);
        palette11.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette11.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette11.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette11.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette11.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette11.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette11.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush);
        palette11.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette11.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        widget_13->setPalette(palette11);
        widget_13->setAutoFillBackground(true);

        gridLayout->addWidget(widget_13, 8, 6, 1, 2);

        UI_LE_VOLT_AC = new myLineEdit(UI_TUNING_METHOD);
        UI_LE_VOLT_AC->setObjectName(QStringLiteral("UI_LE_VOLT_AC"));
        UI_LE_VOLT_AC->setMinimumSize(QSize(0, 24));
        UI_LE_VOLT_AC->setStyleSheet(QStringLiteral("background:transparent;border-width:0;border-style:outset"));

        gridLayout->addWidget(UI_LE_VOLT_AC, 4, 5, 1, 1);

        label_13 = new QLabel(UI_TUNING_METHOD);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setFont(font1);

        gridLayout->addWidget(label_13, 10, 4, 1, 1);

        widget = new QWidget(UI_TUNING_METHOD);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(0, 1));
        widget->setMaximumSize(QSize(16777215, 1));
        QPalette palette12;
        palette12.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette12.setBrush(QPalette::Active, QPalette::Button, brush);
        palette12.setBrush(QPalette::Active, QPalette::Light, brush);
        palette12.setBrush(QPalette::Active, QPalette::Midlight, brush);
        palette12.setBrush(QPalette::Active, QPalette::Dark, brush);
        palette12.setBrush(QPalette::Active, QPalette::Mid, brush);
        palette12.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette12.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette12.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette12.setBrush(QPalette::Active, QPalette::Base, brush);
        palette12.setBrush(QPalette::Active, QPalette::Window, brush);
        palette12.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette12.setBrush(QPalette::Active, QPalette::AlternateBase, brush);
        palette12.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette12.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette12.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette12.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette12.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette12.setBrush(QPalette::Inactive, QPalette::Midlight, brush);
        palette12.setBrush(QPalette::Inactive, QPalette::Dark, brush);
        palette12.setBrush(QPalette::Inactive, QPalette::Mid, brush);
        palette12.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette12.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette12.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette12.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette12.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette12.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette12.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush);
        palette12.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette12.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette12.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette12.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette12.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette12.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        palette12.setBrush(QPalette::Disabled, QPalette::Dark, brush);
        palette12.setBrush(QPalette::Disabled, QPalette::Mid, brush);
        palette12.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette12.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette12.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette12.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette12.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette12.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette12.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush);
        palette12.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette12.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        widget->setPalette(palette12);
        widget->setAutoFillBackground(true);

        gridLayout->addWidget(widget, 2, 2, 1, 2);

        UI_LE_ENDMASS = new myLineEdit(UI_TUNING_METHOD);
        UI_LE_ENDMASS->setObjectName(QStringLiteral("UI_LE_ENDMASS"));
        UI_LE_ENDMASS->setMinimumSize(QSize(0, 24));
        UI_LE_ENDMASS->setStyleSheet(QStringLiteral("background:transparent;border-width:0;border-style:outset"));

        gridLayout->addWidget(UI_LE_ENDMASS, 10, 7, 1, 1);

        label_9 = new QLabel(UI_TUNING_METHOD);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setFont(font1);

        gridLayout->addWidget(label_9, 7, 2, 1, 1);

        widget_17 = new QWidget(UI_TUNING_METHOD);
        widget_17->setObjectName(QStringLiteral("widget_17"));
        widget_17->setMinimumSize(QSize(0, 1));
        widget_17->setMaximumSize(QSize(16777215, 1));
        QPalette palette13;
        palette13.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette13.setBrush(QPalette::Active, QPalette::Button, brush);
        palette13.setBrush(QPalette::Active, QPalette::Light, brush);
        palette13.setBrush(QPalette::Active, QPalette::Midlight, brush);
        palette13.setBrush(QPalette::Active, QPalette::Dark, brush);
        palette13.setBrush(QPalette::Active, QPalette::Mid, brush);
        palette13.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette13.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette13.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette13.setBrush(QPalette::Active, QPalette::Base, brush);
        palette13.setBrush(QPalette::Active, QPalette::Window, brush);
        palette13.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette13.setBrush(QPalette::Active, QPalette::AlternateBase, brush);
        palette13.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette13.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette13.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette13.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette13.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette13.setBrush(QPalette::Inactive, QPalette::Midlight, brush);
        palette13.setBrush(QPalette::Inactive, QPalette::Dark, brush);
        palette13.setBrush(QPalette::Inactive, QPalette::Mid, brush);
        palette13.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette13.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette13.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette13.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette13.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette13.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette13.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush);
        palette13.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette13.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette13.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette13.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette13.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette13.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        palette13.setBrush(QPalette::Disabled, QPalette::Dark, brush);
        palette13.setBrush(QPalette::Disabled, QPalette::Mid, brush);
        palette13.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette13.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette13.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette13.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette13.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette13.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette13.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush);
        palette13.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette13.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        widget_17->setPalette(palette13);
        widget_17->setAutoFillBackground(true);

        gridLayout->addWidget(widget_17, 12, 6, 1, 2);

        UI_LE_TIME_I = new myLineEdit(UI_TUNING_METHOD);
        UI_LE_TIME_I->setObjectName(QStringLiteral("UI_LE_TIME_I"));
        UI_LE_TIME_I->setMinimumSize(QSize(0, 24));
        UI_LE_TIME_I->setStyleSheet(QStringLiteral("background:transparent;border-width:0;border-style:outset"));

        gridLayout->addWidget(UI_LE_TIME_I, 1, 1, 1, 1);

        widget_7 = new QWidget(UI_TUNING_METHOD);
        widget_7->setObjectName(QStringLiteral("widget_7"));
        widget_7->setMinimumSize(QSize(0, 1));
        widget_7->setMaximumSize(QSize(16777215, 1));
        QPalette palette14;
        palette14.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette14.setBrush(QPalette::Active, QPalette::Button, brush);
        palette14.setBrush(QPalette::Active, QPalette::Light, brush);
        palette14.setBrush(QPalette::Active, QPalette::Midlight, brush);
        palette14.setBrush(QPalette::Active, QPalette::Dark, brush);
        palette14.setBrush(QPalette::Active, QPalette::Mid, brush);
        palette14.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette14.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette14.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette14.setBrush(QPalette::Active, QPalette::Base, brush);
        palette14.setBrush(QPalette::Active, QPalette::Window, brush);
        palette14.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette14.setBrush(QPalette::Active, QPalette::AlternateBase, brush);
        palette14.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette14.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette14.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette14.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette14.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette14.setBrush(QPalette::Inactive, QPalette::Midlight, brush);
        palette14.setBrush(QPalette::Inactive, QPalette::Dark, brush);
        palette14.setBrush(QPalette::Inactive, QPalette::Mid, brush);
        palette14.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette14.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette14.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette14.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette14.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette14.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette14.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush);
        palette14.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette14.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette14.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette14.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette14.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette14.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        palette14.setBrush(QPalette::Disabled, QPalette::Dark, brush);
        palette14.setBrush(QPalette::Disabled, QPalette::Mid, brush);
        palette14.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette14.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette14.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette14.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette14.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette14.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette14.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush);
        palette14.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette14.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        widget_7->setPalette(palette14);
        widget_7->setAutoFillBackground(true);

        gridLayout->addWidget(widget_7, 5, 2, 1, 2);

        label_16 = new QLabel(UI_TUNING_METHOD);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setFont(font1);

        gridLayout->addWidget(label_16, 10, 6, 1, 1);

        widget_5 = new QWidget(UI_TUNING_METHOD);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        widget_5->setMinimumSize(QSize(0, 1));
        widget_5->setMaximumSize(QSize(16777215, 1));
        QPalette palette15;
        palette15.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette15.setBrush(QPalette::Active, QPalette::Button, brush);
        palette15.setBrush(QPalette::Active, QPalette::Light, brush);
        palette15.setBrush(QPalette::Active, QPalette::Midlight, brush);
        palette15.setBrush(QPalette::Active, QPalette::Dark, brush);
        palette15.setBrush(QPalette::Active, QPalette::Mid, brush);
        palette15.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette15.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette15.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette15.setBrush(QPalette::Active, QPalette::Base, brush);
        palette15.setBrush(QPalette::Active, QPalette::Window, brush);
        palette15.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette15.setBrush(QPalette::Active, QPalette::AlternateBase, brush);
        palette15.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette15.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette15.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette15.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette15.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette15.setBrush(QPalette::Inactive, QPalette::Midlight, brush);
        palette15.setBrush(QPalette::Inactive, QPalette::Dark, brush);
        palette15.setBrush(QPalette::Inactive, QPalette::Mid, brush);
        palette15.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette15.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette15.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette15.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette15.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette15.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette15.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush);
        palette15.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette15.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette15.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette15.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette15.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette15.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        palette15.setBrush(QPalette::Disabled, QPalette::Dark, brush);
        palette15.setBrush(QPalette::Disabled, QPalette::Mid, brush);
        palette15.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette15.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette15.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette15.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette15.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette15.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette15.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush);
        palette15.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette15.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        widget_5->setPalette(palette15);
        widget_5->setAutoFillBackground(true);

        gridLayout->addWidget(widget_5, 2, 6, 1, 2);

        label_12 = new QLabel(UI_TUNING_METHOD);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setFont(font1);

        gridLayout->addWidget(label_12, 7, 6, 1, 1);

        widget_10 = new QWidget(UI_TUNING_METHOD);
        widget_10->setObjectName(QStringLiteral("widget_10"));
        widget_10->setMinimumSize(QSize(0, 1));
        widget_10->setMaximumSize(QSize(16777215, 1));
        QPalette palette16;
        palette16.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette16.setBrush(QPalette::Active, QPalette::Button, brush);
        palette16.setBrush(QPalette::Active, QPalette::Light, brush);
        palette16.setBrush(QPalette::Active, QPalette::Midlight, brush);
        palette16.setBrush(QPalette::Active, QPalette::Dark, brush);
        palette16.setBrush(QPalette::Active, QPalette::Mid, brush);
        palette16.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette16.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette16.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette16.setBrush(QPalette::Active, QPalette::Base, brush);
        palette16.setBrush(QPalette::Active, QPalette::Window, brush);
        palette16.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette16.setBrush(QPalette::Active, QPalette::AlternateBase, brush);
        palette16.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette16.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette16.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette16.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette16.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette16.setBrush(QPalette::Inactive, QPalette::Midlight, brush);
        palette16.setBrush(QPalette::Inactive, QPalette::Dark, brush);
        palette16.setBrush(QPalette::Inactive, QPalette::Mid, brush);
        palette16.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette16.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette16.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette16.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette16.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette16.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette16.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush);
        palette16.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette16.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette16.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette16.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette16.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette16.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        palette16.setBrush(QPalette::Disabled, QPalette::Dark, brush);
        palette16.setBrush(QPalette::Disabled, QPalette::Mid, brush);
        palette16.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette16.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette16.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette16.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette16.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette16.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette16.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush);
        palette16.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette16.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        widget_10->setPalette(palette16);
        widget_10->setAutoFillBackground(true);

        gridLayout->addWidget(widget_10, 8, 0, 1, 2);

        widget_16 = new QWidget(UI_TUNING_METHOD);
        widget_16->setObjectName(QStringLiteral("widget_16"));
        widget_16->setMinimumSize(QSize(0, 1));
        widget_16->setMaximumSize(QSize(16777215, 1));
        QPalette palette17;
        palette17.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette17.setBrush(QPalette::Active, QPalette::Button, brush);
        palette17.setBrush(QPalette::Active, QPalette::Light, brush);
        palette17.setBrush(QPalette::Active, QPalette::Midlight, brush);
        palette17.setBrush(QPalette::Active, QPalette::Dark, brush);
        palette17.setBrush(QPalette::Active, QPalette::Mid, brush);
        palette17.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette17.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette17.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette17.setBrush(QPalette::Active, QPalette::Base, brush);
        palette17.setBrush(QPalette::Active, QPalette::Window, brush);
        palette17.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette17.setBrush(QPalette::Active, QPalette::AlternateBase, brush);
        palette17.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette17.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette17.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette17.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette17.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette17.setBrush(QPalette::Inactive, QPalette::Midlight, brush);
        palette17.setBrush(QPalette::Inactive, QPalette::Dark, brush);
        palette17.setBrush(QPalette::Inactive, QPalette::Mid, brush);
        palette17.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette17.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette17.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette17.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette17.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette17.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette17.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush);
        palette17.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette17.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette17.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette17.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette17.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette17.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        palette17.setBrush(QPalette::Disabled, QPalette::Dark, brush);
        palette17.setBrush(QPalette::Disabled, QPalette::Mid, brush);
        palette17.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette17.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette17.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette17.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette17.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette17.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette17.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush);
        palette17.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette17.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        widget_16->setPalette(palette17);
        widget_16->setAutoFillBackground(true);

        gridLayout->addWidget(widget_16, 12, 4, 1, 2);

        widget_14 = new QWidget(UI_TUNING_METHOD);
        widget_14->setObjectName(QStringLiteral("widget_14"));
        widget_14->setMinimumSize(QSize(0, 1));
        widget_14->setMaximumSize(QSize(16777215, 1));
        QPalette palette18;
        palette18.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette18.setBrush(QPalette::Active, QPalette::Button, brush);
        palette18.setBrush(QPalette::Active, QPalette::Light, brush);
        palette18.setBrush(QPalette::Active, QPalette::Midlight, brush);
        palette18.setBrush(QPalette::Active, QPalette::Dark, brush);
        palette18.setBrush(QPalette::Active, QPalette::Mid, brush);
        palette18.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette18.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette18.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette18.setBrush(QPalette::Active, QPalette::Base, brush);
        palette18.setBrush(QPalette::Active, QPalette::Window, brush);
        palette18.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette18.setBrush(QPalette::Active, QPalette::AlternateBase, brush);
        palette18.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette18.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette18.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette18.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette18.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette18.setBrush(QPalette::Inactive, QPalette::Midlight, brush);
        palette18.setBrush(QPalette::Inactive, QPalette::Dark, brush);
        palette18.setBrush(QPalette::Inactive, QPalette::Mid, brush);
        palette18.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette18.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette18.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette18.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette18.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette18.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette18.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush);
        palette18.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette18.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette18.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette18.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette18.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette18.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        palette18.setBrush(QPalette::Disabled, QPalette::Dark, brush);
        palette18.setBrush(QPalette::Disabled, QPalette::Mid, brush);
        palette18.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette18.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette18.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette18.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette18.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette18.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette18.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush);
        palette18.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette18.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        widget_14->setPalette(palette18);
        widget_14->setAutoFillBackground(true);

        gridLayout->addWidget(widget_14, 12, 0, 1, 2);

        UI_LE_B_CAP = new myLineEdit(UI_TUNING_METHOD);
        UI_LE_B_CAP->setObjectName(QStringLiteral("UI_LE_B_CAP"));
        UI_LE_B_CAP->setMinimumSize(QSize(0, 24));
        UI_LE_B_CAP->setStyleSheet(QStringLiteral("background:transparent;border-width:0;border-style:outset"));

        gridLayout->addWidget(UI_LE_B_CAP, 7, 5, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 24, QSizePolicy::Minimum, QSizePolicy::Maximum);

        gridLayout->addItem(verticalSpacer_4, 0, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 24, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        gridLayout->addItem(verticalSpacer_5, 13, 0, 1, 1);


        UI_LAYOUT_TUNING_METHOD->addLayout(gridLayout);


        verticalLayout_3->addWidget(UI_TUNING_METHOD);

        UI_W_TUNINGMENU = new QWidget(sManualTuning);
        UI_W_TUNINGMENU->setObjectName(QStringLiteral("UI_W_TUNINGMENU"));
        horizontalLayout_4 = new QHBoxLayout(UI_W_TUNINGMENU);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_3 = new QSpacerItem(117, 96, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        UI_PB_LOADFILE = new QPushButton(UI_W_TUNINGMENU);
        UI_PB_LOADFILE->setObjectName(QStringLiteral("UI_PB_LOADFILE"));
        UI_PB_LOADFILE->setMinimumSize(QSize(96, 32));
        QPalette palette19;
        palette19.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette19.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette19.setBrush(QPalette::Active, QPalette::Light, brush1);
        palette19.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        palette19.setBrush(QPalette::Active, QPalette::Dark, brush2);
        palette19.setBrush(QPalette::Active, QPalette::Mid, brush1);
        palette19.setBrush(QPalette::Active, QPalette::Text, brush);
        palette19.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette19.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette19.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette19.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette19.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette19.setBrush(QPalette::Active, QPalette::AlternateBase, brush1);
        palette19.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette19.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette19.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette19.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette19.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette19.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette19.setBrush(QPalette::Inactive, QPalette::Dark, brush2);
        palette19.setBrush(QPalette::Inactive, QPalette::Mid, brush1);
        palette19.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette19.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette19.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette19.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette19.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette19.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette19.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush1);
        palette19.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette19.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette19.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette19.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette19.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette19.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette19.setBrush(QPalette::Disabled, QPalette::Dark, brush2);
        palette19.setBrush(QPalette::Disabled, QPalette::Mid, brush1);
        palette19.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette19.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette19.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette19.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette19.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette19.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette19.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette19.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette19.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        UI_PB_LOADFILE->setPalette(palette19);
        UI_PB_LOADFILE->setAutoFillBackground(true);

        horizontalLayout_4->addWidget(UI_PB_LOADFILE);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        UI_PB_SAVEFILE = new QPushButton(UI_W_TUNINGMENU);
        UI_PB_SAVEFILE->setObjectName(QStringLiteral("UI_PB_SAVEFILE"));
        UI_PB_SAVEFILE->setMinimumSize(QSize(96, 32));
        QPalette palette20;
        palette20.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette20.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette20.setBrush(QPalette::Active, QPalette::Light, brush1);
        palette20.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        palette20.setBrush(QPalette::Active, QPalette::Dark, brush2);
        palette20.setBrush(QPalette::Active, QPalette::Mid, brush1);
        palette20.setBrush(QPalette::Active, QPalette::Text, brush);
        palette20.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette20.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette20.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette20.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette20.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette20.setBrush(QPalette::Active, QPalette::AlternateBase, brush1);
        palette20.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette20.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette20.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette20.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette20.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette20.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette20.setBrush(QPalette::Inactive, QPalette::Dark, brush2);
        palette20.setBrush(QPalette::Inactive, QPalette::Mid, brush1);
        palette20.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette20.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette20.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette20.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette20.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette20.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette20.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush1);
        palette20.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette20.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette20.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette20.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette20.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette20.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette20.setBrush(QPalette::Disabled, QPalette::Dark, brush2);
        palette20.setBrush(QPalette::Disabled, QPalette::Mid, brush1);
        palette20.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette20.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette20.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette20.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette20.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette20.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette20.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette20.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette20.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        UI_PB_SAVEFILE->setPalette(palette20);
        UI_PB_SAVEFILE->setAutoFillBackground(true);

        horizontalLayout_4->addWidget(UI_PB_SAVEFILE);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_15);

        UI_PB_BASELINE = new QPushButton(UI_W_TUNINGMENU);
        UI_PB_BASELINE->setObjectName(QStringLiteral("UI_PB_BASELINE"));
        UI_PB_BASELINE->setMinimumSize(QSize(96, 32));
        QPalette palette21;
        palette21.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette21.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette21.setBrush(QPalette::Active, QPalette::Light, brush1);
        palette21.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        palette21.setBrush(QPalette::Active, QPalette::Dark, brush2);
        palette21.setBrush(QPalette::Active, QPalette::Mid, brush1);
        palette21.setBrush(QPalette::Active, QPalette::Text, brush);
        palette21.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette21.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette21.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette21.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette21.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette21.setBrush(QPalette::Active, QPalette::AlternateBase, brush1);
        palette21.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette21.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette21.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette21.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette21.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette21.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette21.setBrush(QPalette::Inactive, QPalette::Dark, brush2);
        palette21.setBrush(QPalette::Inactive, QPalette::Mid, brush1);
        palette21.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette21.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette21.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette21.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette21.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette21.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette21.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush1);
        palette21.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette21.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette21.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette21.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette21.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette21.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette21.setBrush(QPalette::Disabled, QPalette::Dark, brush2);
        palette21.setBrush(QPalette::Disabled, QPalette::Mid, brush1);
        palette21.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette21.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette21.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette21.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette21.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette21.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette21.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette21.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette21.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        UI_PB_BASELINE->setPalette(palette21);
        UI_PB_BASELINE->setAutoFillBackground(true);

        horizontalLayout_4->addWidget(UI_PB_BASELINE);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        UI_PB_TUNING_FIT = new QPushButton(UI_W_TUNINGMENU);
        UI_PB_TUNING_FIT->setObjectName(QStringLiteral("UI_PB_TUNING_FIT"));
        UI_PB_TUNING_FIT->setMinimumSize(QSize(96, 32));

        horizontalLayout_4->addWidget(UI_PB_TUNING_FIT);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_14);

        UI_PB_TUNING_SCAN = new QPushButton(UI_W_TUNINGMENU);
        UI_PB_TUNING_SCAN->setObjectName(QStringLiteral("UI_PB_TUNING_SCAN"));
        UI_PB_TUNING_SCAN->setMinimumSize(QSize(96, 32));
        QPalette palette22;
        palette22.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette22.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette22.setBrush(QPalette::Active, QPalette::Light, brush1);
        palette22.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        palette22.setBrush(QPalette::Active, QPalette::Dark, brush2);
        palette22.setBrush(QPalette::Active, QPalette::Mid, brush1);
        palette22.setBrush(QPalette::Active, QPalette::Text, brush);
        palette22.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette22.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette22.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette22.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette22.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette22.setBrush(QPalette::Active, QPalette::AlternateBase, brush1);
        palette22.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette22.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette22.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette22.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette22.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette22.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette22.setBrush(QPalette::Inactive, QPalette::Dark, brush2);
        palette22.setBrush(QPalette::Inactive, QPalette::Mid, brush1);
        palette22.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette22.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette22.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette22.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette22.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette22.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette22.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush1);
        palette22.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette22.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette22.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette22.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette22.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette22.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette22.setBrush(QPalette::Disabled, QPalette::Dark, brush2);
        palette22.setBrush(QPalette::Disabled, QPalette::Mid, brush1);
        palette22.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette22.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette22.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette22.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette22.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette22.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette22.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette22.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette22.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        UI_PB_TUNING_SCAN->setPalette(palette22);
        UI_PB_TUNING_SCAN->setAutoFillBackground(true);

        horizontalLayout_4->addWidget(UI_PB_TUNING_SCAN);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);


        verticalLayout_3->addWidget(UI_W_TUNINGMENU);


        retranslateUi(sManualTuning);

        QMetaObject::connectSlotsByName(sManualTuning);
    } // setupUi

    void retranslateUi(QWidget *sManualTuning)
    {
        sManualTuning->setWindowTitle(QApplication::translate("sManualTuning", "Form", nullptr));
        UI_PB_TARGET->setText(QApplication::translate("sManualTuning", "\347\233\256\346\240\207\347\246\273\345\255\220\350\260\261", nullptr));
        UI_PB_FULL->setText(QApplication::translate("sManualTuning", "\345\205\250\350\260\261", nullptr));
        label_20->setText(QApplication::translate("sManualTuning", "m/z:", nullptr));
        label_17->setText(QApplication::translate("sManualTuning", "m/z:", nullptr));
        label_19->setText(QApplication::translate("sManualTuning", "m/z:", nullptr));
        label_18->setText(QApplication::translate("sManualTuning", "m/z:", nullptr));
        UI_PB_OK->setText(QApplication::translate("sManualTuning", "\346\211\223\345\274\200", nullptr));
        UI_PB_CANCEL->setText(QApplication::translate("sManualTuning", "\345\217\226\346\266\210", nullptr));
        label_6->setText(QApplication::translate("sManualTuning", "LIT AC\345\215\240\347\251\272\346\257\224/%", nullptr));
        label_11->setText(QApplication::translate("sManualTuning", "LIT RF\345\271\205\345\200\274/Vpp", nullptr));
        label_10->setText(QApplication::translate("sManualTuning", "LIT\345\220\216\347\253\257\347\233\226/V", nullptr));
        label_3->setText(QApplication::translate("sManualTuning", "\346\270\205\347\251\272\346\227\266\351\227\264/ms", nullptr));
        label_2->setText(QApplication::translate("sManualTuning", "\345\206\267\345\215\264\346\227\266\351\227\264/ms", nullptr));
        label_8->setText(QApplication::translate("sManualTuning", "LIT\345\211\215\347\253\257\347\233\226\345\274\200/V", nullptr));
        label_14->setText(QApplication::translate("sManualTuning", "Q-array\345\201\217\347\275\256/V", nullptr));
        label->setText(QApplication::translate("sManualTuning", "\345\274\225\345\205\245\346\227\266\351\227\264/ms", nullptr));
        label_7->setText(QApplication::translate("sManualTuning", "LIT AC\345\271\205\345\200\274/V", nullptr));
        label_15->setText(QApplication::translate("sManualTuning", "Q-array RF\345\271\205\345\200\274/Vpp", nullptr));
        label_4->setText(QApplication::translate("sManualTuning", "\350\264\250\351\207\217\346\211\253\351\200\237/ Th/s", nullptr));
        label_5->setText(QApplication::translate("sManualTuning", "LIT AC\345\210\235\345\247\213\347\233\270\344\275\215/\345\272\246", nullptr));
        label_13->setText(QApplication::translate("sManualTuning", "\350\265\267\345\247\213\346\211\253\346\217\217\350\264\250\351\207\217", nullptr));
        label_9->setText(QApplication::translate("sManualTuning", "LIT\345\211\215\347\253\257\347\233\226\351\227\255/V", nullptr));
        label_16->setText(QApplication::translate("sManualTuning", "\347\273\210\346\255\242\346\211\253\346\217\217\350\264\250\351\207\217", nullptr));
        label_12->setText(QApplication::translate("sManualTuning", "LIT\345\234\272\350\260\203\347\224\265\346\236\201/V", nullptr));
        UI_PB_LOADFILE->setText(QApplication::translate("sManualTuning", "\350\275\275\345\205\245\350\260\203\350\260\220\346\226\207\344\273\266", nullptr));
        UI_PB_SAVEFILE->setText(QApplication::translate("sManualTuning", "\345\217\246\345\255\230\344\270\272\350\260\203\350\260\220\346\226\207\344\273\266", nullptr));
        UI_PB_BASELINE->setText(QApplication::translate("sManualTuning", "\345\237\272\347\272\277\344\277\256\346\255\243", nullptr));
        UI_PB_TUNING_FIT->setText(QApplication::translate("sManualTuning", "\345\263\260\344\275\215\346\240\241\346\255\243", nullptr));
        UI_PB_TUNING_SCAN->setText(QApplication::translate("sManualTuning", "\346\211\247\350\241\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sManualTuning: public Ui_sManualTuning {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMANUALTUNING_H
