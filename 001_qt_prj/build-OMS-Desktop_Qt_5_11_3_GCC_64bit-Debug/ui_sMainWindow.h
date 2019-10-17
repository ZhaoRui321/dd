/********************************************************************************
** Form generated from reading UI file 'sMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMAINWINDOW_H
#define UI_SMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sMainWindow
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *UI_W_MENU;
    QVBoxLayout *verticalLayout;
    QPushButton *UI_PB_METHOD;
    QPushButton *UI_PB_ACQUISITION;
    QPushButton *UI_PB_ANALYSIS;
    QPushButton *UI_PB_SYSTEM;
    QSpacerItem *verticalSpacer_2;
    QLabel *timer;
    QWidget *verticalWidget;
    QVBoxLayout *verticalLayout_4;
    QWidget *logWidget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QPushButton *headBtn;
    QLabel *countLabel;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_5;
    QWidget *UI_W_CENTRE;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *tipEdit;
    QWidget *UI_W_STATE;
    QVBoxLayout *verticalLayout_2;
    QLabel *stateTitle;
    QLabel *PumpState;
    QLabel *GUIState;
    QPushButton *vacuumBtn;
    QPushButton *hightBtn;
    QPushButton *heatBtn;
    QSpacerItem *verticalSpacer_3;
    QPushButton *snapBtn;
    QPushButton *UI_PB_STOP;

    void setupUi(QWidget *sMainWindow)
    {
        if (sMainWindow->objectName().isEmpty())
            sMainWindow->setObjectName(QStringLiteral("sMainWindow"));
        sMainWindow->resize(1178, 1384);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sMainWindow->sizePolicy().hasHeightForWidth());
        sMainWindow->setSizePolicy(sizePolicy);
        sMainWindow->setMaximumSize(QSize(2160, 1440));
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
        sMainWindow->setPalette(palette);
        sMainWindow->setFocusPolicy(Qt::ClickFocus);
        sMainWindow->setAutoFillBackground(true);
        horizontalLayout = new QHBoxLayout(sMainWindow);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        UI_W_MENU = new QWidget(sMainWindow);
        UI_W_MENU->setObjectName(QStringLiteral("UI_W_MENU"));
        UI_W_MENU->setMinimumSize(QSize(240, 0));
        UI_W_MENU->setMaximumSize(QSize(150, 16777215));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush5(QColor(111, 111, 111, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush5);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush1);
        QBrush brush6(QColor(247, 247, 247, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush6);
        QBrush brush7(QColor(120, 120, 120, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush7);
        QBrush brush8(QColor(160, 160, 160, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush8);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush5);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush5);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette1.setBrush(QPalette::Active, QPalette::AlternateBase, brush6);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush7);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush8);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        QBrush brush9(QColor(240, 240, 240, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        UI_W_MENU->setPalette(palette1);
        UI_W_MENU->setAutoFillBackground(false);
        UI_W_MENU->setStyleSheet(QStringLiteral("background-color: rgb(111, 111, 111);"));
        verticalLayout = new QVBoxLayout(UI_W_MENU);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 100, 0, 50);
        UI_PB_METHOD = new QPushButton(UI_W_MENU);
        UI_PB_METHOD->setObjectName(QStringLiteral("UI_PB_METHOD"));
        UI_PB_METHOD->setMinimumSize(QSize(80, 200));
        UI_PB_METHOD->setMaximumSize(QSize(16777215, 16777215));
        UI_PB_METHOD->setStyleSheet(QStringLiteral("background-image: url(:/picture/icons/R1-1.png);"));

        verticalLayout->addWidget(UI_PB_METHOD);

        UI_PB_ACQUISITION = new QPushButton(UI_W_MENU);
        UI_PB_ACQUISITION->setObjectName(QStringLiteral("UI_PB_ACQUISITION"));
        UI_PB_ACQUISITION->setMinimumSize(QSize(0, 200));
        UI_PB_ACQUISITION->setMaximumSize(QSize(16777215, 16777215));
        UI_PB_ACQUISITION->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/R2-0.png);"));

        verticalLayout->addWidget(UI_PB_ACQUISITION);

        UI_PB_ANALYSIS = new QPushButton(UI_W_MENU);
        UI_PB_ANALYSIS->setObjectName(QStringLiteral("UI_PB_ANALYSIS"));
        UI_PB_ANALYSIS->setMinimumSize(QSize(0, 200));
        UI_PB_ANALYSIS->setMaximumSize(QSize(16777215, 16777215));
        UI_PB_ANALYSIS->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/R3-0.png);"));

        verticalLayout->addWidget(UI_PB_ANALYSIS);

        UI_PB_SYSTEM = new QPushButton(UI_W_MENU);
        UI_PB_SYSTEM->setObjectName(QStringLiteral("UI_PB_SYSTEM"));
        UI_PB_SYSTEM->setMinimumSize(QSize(0, 200));
        UI_PB_SYSTEM->setMaximumSize(QSize(16777215, 16777215));
        UI_PB_SYSTEM->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/R4-0.png);"));

        verticalLayout->addWidget(UI_PB_SYSTEM);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        timer = new QLabel(UI_W_MENU);
        timer->setObjectName(QStringLiteral("timer"));
        QFont font;
        font.setPointSize(16);
        timer->setFont(font);
        timer->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(timer);


        horizontalLayout->addWidget(UI_W_MENU);

        verticalWidget = new QWidget(sMainWindow);
        verticalWidget->setObjectName(QStringLiteral("verticalWidget"));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush9);
        palette2.setBrush(QPalette::Active, QPalette::Light, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Midlight, brush6);
        palette2.setBrush(QPalette::Active, QPalette::Dark, brush7);
        palette2.setBrush(QPalette::Active, QPalette::Mid, brush8);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush);
        palette2.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush9);
        palette2.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette2.setBrush(QPalette::Active, QPalette::AlternateBase, brush6);
        palette2.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette2.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush9);
        palette2.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Midlight, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::Dark, brush7);
        palette2.setBrush(QPalette::Inactive, QPalette::Mid, brush8);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush9);
        palette2.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette2.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush7);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush9);
        palette2.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Midlight, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::Dark, brush7);
        palette2.setBrush(QPalette::Disabled, QPalette::Mid, brush8);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush7);
        palette2.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush7);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush9);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush9);
        palette2.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush9);
        palette2.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette2.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        verticalWidget->setPalette(palette2);
        verticalLayout_4 = new QVBoxLayout(verticalWidget);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        logWidget = new QWidget(verticalWidget);
        logWidget->setObjectName(QStringLiteral("logWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(logWidget->sizePolicy().hasHeightForWidth());
        logWidget->setSizePolicy(sizePolicy1);
        logWidget->setMinimumSize(QSize(0, 100));
        logWidget->setMaximumSize(QSize(16777215, 100));
        logWidget->setStyleSheet(QStringLiteral("border-bottom: 2px solid rgb(216,216,216);"));
        horizontalLayout_4 = new QHBoxLayout(logWidget);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(40, 20, 8, 20);
        label = new QLabel(logWidget);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(300, 0));
        QFont font1;
        font1.setPointSize(30);
        label->setFont(font1);
        label->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/LOGO.png);"));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        headBtn = new QPushButton(logWidget);
        headBtn->setObjectName(QStringLiteral("headBtn"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(headBtn->sizePolicy().hasHeightForWidth());
        headBtn->setSizePolicy(sizePolicy2);
        headBtn->setMinimumSize(QSize(60, 0));
        headBtn->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/USER.png);"));

        horizontalLayout_4->addWidget(headBtn);

        countLabel = new QLabel(logWidget);
        countLabel->setObjectName(QStringLiteral("countLabel"));
        countLabel->setMinimumSize(QSize(150, 0));
        QFont font2;
        font2.setPointSize(16);
        font2.setBold(false);
        font2.setWeight(50);
        countLabel->setFont(font2);
        countLabel->setFocusPolicy(Qt::ClickFocus);
        countLabel->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        horizontalLayout_4->addWidget(countLabel);


        verticalLayout_4->addWidget(logWidget);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 0, -1, -1);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        UI_W_CENTRE = new QWidget(verticalWidget);
        UI_W_CENTRE->setObjectName(QStringLiteral("UI_W_CENTRE"));
        sizePolicy1.setHeightForWidth(UI_W_CENTRE->sizePolicy().hasHeightForWidth());
        UI_W_CENTRE->setSizePolicy(sizePolicy1);
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Active, QPalette::Button, brush9);
        palette3.setBrush(QPalette::Active, QPalette::Light, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Midlight, brush6);
        palette3.setBrush(QPalette::Active, QPalette::Dark, brush7);
        palette3.setBrush(QPalette::Active, QPalette::Mid, brush8);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush);
        palette3.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush1);
        QBrush brush10(QColor(216, 216, 216, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush10);
        palette3.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette3.setBrush(QPalette::Active, QPalette::AlternateBase, brush6);
        palette3.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette3.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush9);
        palette3.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Midlight, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::Dark, brush7);
        palette3.setBrush(QPalette::Inactive, QPalette::Mid, brush8);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush10);
        palette3.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette3.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush7);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush9);
        palette3.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Midlight, brush6);
        palette3.setBrush(QPalette::Disabled, QPalette::Dark, brush7);
        palette3.setBrush(QPalette::Disabled, QPalette::Mid, brush8);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush7);
        palette3.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush7);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush10);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush10);
        palette3.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush9);
        palette3.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette3.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        UI_W_CENTRE->setPalette(palette3);
        UI_W_CENTRE->setFocusPolicy(Qt::ClickFocus);
        UI_W_CENTRE->setAutoFillBackground(true);
        UI_W_CENTRE->setStyleSheet(QStringLiteral(""));
        verticalLayout_3 = new QVBoxLayout(UI_W_CENTRE);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));

        verticalLayout_5->addWidget(UI_W_CENTRE);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(20, -1, 0, -1);
        tipEdit = new QLineEdit(verticalWidget);
        tipEdit->setObjectName(QStringLiteral("tipEdit"));
        tipEdit->setMinimumSize(QSize(0, 60));
        QFont font3;
        font3.setPointSize(18);
        tipEdit->setFont(font3);
        tipEdit->setFocusPolicy(Qt::NoFocus);
        tipEdit->setStyleSheet(QStringLiteral("border-right: 2px solid rgb(216,216,216);"));
        tipEdit->setFrame(false);
        tipEdit->setCursorPosition(0);

        horizontalLayout_2->addWidget(tipEdit);


        verticalLayout_5->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout_5);

        UI_W_STATE = new QWidget(verticalWidget);
        UI_W_STATE->setObjectName(QStringLiteral("UI_W_STATE"));
        UI_W_STATE->setMinimumSize(QSize(160, 0));
        UI_W_STATE->setMaximumSize(QSize(160, 16777215));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Active, QPalette::Button, brush9);
        palette4.setBrush(QPalette::Active, QPalette::Light, brush1);
        palette4.setBrush(QPalette::Active, QPalette::Midlight, brush6);
        palette4.setBrush(QPalette::Active, QPalette::Dark, brush7);
        palette4.setBrush(QPalette::Active, QPalette::Mid, brush8);
        palette4.setBrush(QPalette::Active, QPalette::Text, brush);
        palette4.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette4.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette4.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette4.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette4.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette4.setBrush(QPalette::Active, QPalette::AlternateBase, brush6);
        palette4.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette4.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Button, brush9);
        palette4.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Midlight, brush6);
        palette4.setBrush(QPalette::Inactive, QPalette::Dark, brush7);
        palette4.setBrush(QPalette::Inactive, QPalette::Mid, brush8);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush6);
        palette4.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette4.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush7);
        palette4.setBrush(QPalette::Disabled, QPalette::Button, brush9);
        palette4.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Midlight, brush6);
        palette4.setBrush(QPalette::Disabled, QPalette::Dark, brush7);
        palette4.setBrush(QPalette::Disabled, QPalette::Mid, brush8);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush7);
        palette4.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::ButtonText, brush7);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush9);
        palette4.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette4.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        UI_W_STATE->setPalette(palette4);
        UI_W_STATE->setAutoFillBackground(true);
        UI_W_STATE->setStyleSheet(QStringLiteral(""));
        verticalLayout_2 = new QVBoxLayout(UI_W_STATE);
        verticalLayout_2->setSpacing(3);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 150, 0, 30);
        stateTitle = new QLabel(UI_W_STATE);
        stateTitle->setObjectName(QStringLiteral("stateTitle"));
        stateTitle->setMinimumSize(QSize(100, 50));
        QFont font4;
        font4.setPointSize(12);
        stateTitle->setFont(font4);
        stateTitle->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(stateTitle);

        PumpState = new QLabel(UI_W_STATE);
        PumpState->setObjectName(QStringLiteral("PumpState"));
        PumpState->setMinimumSize(QSize(50, 0));
        PumpState->setLayoutDirection(Qt::RightToLeft);
        PumpState->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(PumpState);

        GUIState = new QLabel(UI_W_STATE);
        GUIState->setObjectName(QStringLiteral("GUIState"));
        GUIState->setMinimumSize(QSize(50, 0));
        GUIState->setLayoutDirection(Qt::RightToLeft);
        GUIState->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(GUIState);

        vacuumBtn = new QPushButton(UI_W_STATE);
        vacuumBtn->setObjectName(QStringLiteral("vacuumBtn"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(vacuumBtn->sizePolicy().hasHeightForWidth());
        vacuumBtn->setSizePolicy(sizePolicy3);
        vacuumBtn->setMinimumSize(QSize(0, 200));
        vacuumBtn->setMaximumSize(QSize(16777215, 200));
        vacuumBtn->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/V-ON.png);"));

        verticalLayout_2->addWidget(vacuumBtn);

        hightBtn = new QPushButton(UI_W_STATE);
        hightBtn->setObjectName(QStringLiteral("hightBtn"));
        sizePolicy3.setHeightForWidth(hightBtn->sizePolicy().hasHeightForWidth());
        hightBtn->setSizePolicy(sizePolicy3);
        hightBtn->setMinimumSize(QSize(0, 200));
        hightBtn->setMaximumSize(QSize(16777215, 200));
        hightBtn->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/HV-ON.png);"));

        verticalLayout_2->addWidget(hightBtn);

        heatBtn = new QPushButton(UI_W_STATE);
        heatBtn->setObjectName(QStringLiteral("heatBtn"));
        QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(heatBtn->sizePolicy().hasHeightForWidth());
        heatBtn->setSizePolicy(sizePolicy4);
        heatBtn->setMinimumSize(QSize(0, 200));
        heatBtn->setMaximumSize(QSize(16777215, 200));
        heatBtn->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/DL-ON.png);"));

        verticalLayout_2->addWidget(heatBtn);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        snapBtn = new QPushButton(UI_W_STATE);
        snapBtn->setObjectName(QStringLiteral("snapBtn"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(snapBtn->sizePolicy().hasHeightForWidth());
        snapBtn->setSizePolicy(sizePolicy5);
        snapBtn->setMinimumSize(QSize(0, 200));
        snapBtn->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/SNAP.png);"));

        verticalLayout_2->addWidget(snapBtn);

        UI_PB_STOP = new QPushButton(UI_W_STATE);
        UI_PB_STOP->setObjectName(QStringLiteral("UI_PB_STOP"));
        sizePolicy4.setHeightForWidth(UI_PB_STOP->sizePolicy().hasHeightForWidth());
        UI_PB_STOP->setSizePolicy(sizePolicy4);
        UI_PB_STOP->setMinimumSize(QSize(160, 200));
        UI_PB_STOP->setMaximumSize(QSize(160, 200));
        UI_PB_STOP->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/START.png);"));

        verticalLayout_2->addWidget(UI_PB_STOP);


        horizontalLayout_3->addWidget(UI_W_STATE);


        verticalLayout_4->addLayout(horizontalLayout_3);


        horizontalLayout->addWidget(verticalWidget);


        retranslateUi(sMainWindow);

        QMetaObject::connectSlotsByName(sMainWindow);
    } // setupUi

    void retranslateUi(QWidget *sMainWindow)
    {
        sMainWindow->setWindowTitle(QApplication::translate("sMainWindow", "Form", nullptr));
        UI_PB_METHOD->setText(QString());
        UI_PB_ACQUISITION->setText(QString());
        UI_PB_ANALYSIS->setText(QString());
        UI_PB_SYSTEM->setText(QString());
        timer->setText(QString());
        label->setText(QString());
        headBtn->setText(QString());
        countLabel->setText(QApplication::translate("sMainWindow", "\347\224\250\346\210\267\345\220\215", nullptr));
        stateTitle->setText(QApplication::translate("sMainWindow", "\347\212\266 \346\200\201 \346\240\217", nullptr));
        PumpState->setText(QString());
        GUIState->setText(QString());
        vacuumBtn->setText(QString());
        hightBtn->setText(QString());
        heatBtn->setText(QString());
        snapBtn->setText(QString());
        UI_PB_STOP->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class sMainWindow: public Ui_sMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMAINWINDOW_H
