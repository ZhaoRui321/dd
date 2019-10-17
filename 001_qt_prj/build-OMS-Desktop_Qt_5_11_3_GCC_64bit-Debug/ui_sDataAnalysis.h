/********************************************************************************
** Form generated from reading UI file 'sDataAnalysis.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SDATAANALYSIS_H
#define UI_SDATAANALYSIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sDataAnalysis
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QWidget *UI_W_MENU;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_Inform;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelFileName;
    QLabel *labelFileTime;
    QLabel *labelCurrentPage;
    QGroupBox *groupBox_tools;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *BtnAdd;
    QPushButton *BtnChange;
    QHBoxLayout *HLayout_XICList;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *UI_PB_TIC_CHOOSE;
    QPushButton *UI_PB_ACCTIC;
    QPushButton *UI_PB_TIC_CLEAR;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *UI_PB_MASS_CHOOSE;
    QPushButton *UI_PB_CALCULATE;
    QPushButton *UI_PB_MASS_CLEAR;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_4;
    QWidget *UI_W_TIC;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *labelMin;
    QWidget *widgetForTouch;
    QLabel *labelMax;
    QWidget *UI_W_MASS;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButton;
    QWidget *verticalWidget_2;
    QVBoxLayout *verticalLayout_5;
    QWidget *verticalWidget_3;
    QVBoxLayout *verticalLayout_6;
    QPushButton *delBtn;
    QPushButton *btn_saveFrame;

    void setupUi(QMainWindow *sDataAnalysis)
    {
        if (sDataAnalysis->objectName().isEmpty())
            sDataAnalysis->setObjectName(QStringLiteral("sDataAnalysis"));
        sDataAnalysis->resize(1173, 702);
        centralWidget = new QWidget(sDataAnalysis);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, 0, -1);
        UI_W_MENU = new QWidget(centralWidget);
        UI_W_MENU->setObjectName(QStringLiteral("UI_W_MENU"));
        UI_W_MENU->setMaximumSize(QSize(16777215, 150));
        horizontalLayout = new QHBoxLayout(UI_W_MENU);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 0, -1, 0);
        groupBox_Inform = new QGroupBox(UI_W_MENU);
        groupBox_Inform->setObjectName(QStringLiteral("groupBox_Inform"));
        groupBox_Inform->setMinimumSize(QSize(300, 0));
        verticalLayout_7 = new QVBoxLayout(groupBox_Inform);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        labelFileName = new QLabel(groupBox_Inform);
        labelFileName->setObjectName(QStringLiteral("labelFileName"));
        labelFileName->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(labelFileName);

        labelFileTime = new QLabel(groupBox_Inform);
        labelFileTime->setObjectName(QStringLiteral("labelFileTime"));
        labelFileTime->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(labelFileTime);


        verticalLayout_7->addLayout(horizontalLayout_5);

        labelCurrentPage = new QLabel(groupBox_Inform);
        labelCurrentPage->setObjectName(QStringLiteral("labelCurrentPage"));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        labelCurrentPage->setFont(font);
        labelCurrentPage->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(labelCurrentPage);


        horizontalLayout->addWidget(groupBox_Inform);

        groupBox_tools = new QGroupBox(UI_W_MENU);
        groupBox_tools->setObjectName(QStringLiteral("groupBox_tools"));
        groupBox_tools->setMinimumSize(QSize(300, 0));
        horizontalLayout_6 = new QHBoxLayout(groupBox_tools);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        BtnAdd = new QPushButton(groupBox_tools);
        BtnAdd->setObjectName(QStringLiteral("BtnAdd"));
        BtnAdd->setMinimumSize(QSize(100, 50));

        horizontalLayout_6->addWidget(BtnAdd);

        BtnChange = new QPushButton(groupBox_tools);
        BtnChange->setObjectName(QStringLiteral("BtnChange"));
        BtnChange->setMinimumSize(QSize(100, 50));

        horizontalLayout_6->addWidget(BtnChange);


        horizontalLayout->addWidget(groupBox_tools);

        HLayout_XICList = new QHBoxLayout();
        HLayout_XICList->setSpacing(6);
        HLayout_XICList->setObjectName(QStringLiteral("HLayout_XICList"));

        horizontalLayout->addLayout(HLayout_XICList);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        groupBox = new QGroupBox(UI_W_MENU);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        UI_PB_TIC_CHOOSE = new QPushButton(groupBox);
        UI_PB_TIC_CHOOSE->setObjectName(QStringLiteral("UI_PB_TIC_CHOOSE"));

        horizontalLayout_2->addWidget(UI_PB_TIC_CHOOSE);

        UI_PB_ACCTIC = new QPushButton(groupBox);
        UI_PB_ACCTIC->setObjectName(QStringLiteral("UI_PB_ACCTIC"));
        UI_PB_ACCTIC->setEnabled(false);

        horizontalLayout_2->addWidget(UI_PB_ACCTIC);

        UI_PB_TIC_CLEAR = new QPushButton(groupBox);
        UI_PB_TIC_CLEAR->setObjectName(QStringLiteral("UI_PB_TIC_CLEAR"));

        horizontalLayout_2->addWidget(UI_PB_TIC_CLEAR);


        horizontalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(UI_W_MENU);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        UI_PB_MASS_CHOOSE = new QPushButton(groupBox_2);
        UI_PB_MASS_CHOOSE->setObjectName(QStringLiteral("UI_PB_MASS_CHOOSE"));

        horizontalLayout_3->addWidget(UI_PB_MASS_CHOOSE);

        UI_PB_CALCULATE = new QPushButton(groupBox_2);
        UI_PB_CALCULATE->setObjectName(QStringLiteral("UI_PB_CALCULATE"));
        UI_PB_CALCULATE->setEnabled(false);

        horizontalLayout_3->addWidget(UI_PB_CALCULATE);

        UI_PB_MASS_CLEAR = new QPushButton(groupBox_2);
        UI_PB_MASS_CLEAR->setObjectName(QStringLiteral("UI_PB_MASS_CLEAR"));

        horizontalLayout_3->addWidget(UI_PB_MASS_CLEAR);


        horizontalLayout->addWidget(groupBox_2);


        verticalLayout->addWidget(UI_W_MENU);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        UI_W_TIC = new QWidget(centralWidget);
        UI_W_TIC->setObjectName(QStringLiteral("UI_W_TIC"));
        UI_W_TIC->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout_2 = new QVBoxLayout(UI_W_TIC);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));

        verticalLayout_4->addWidget(UI_W_TIC);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        labelMin = new QLabel(centralWidget);
        labelMin->setObjectName(QStringLiteral("labelMin"));
        labelMin->setMinimumSize(QSize(0, 25));
        labelMin->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_7->addWidget(labelMin);

        widgetForTouch = new QWidget(centralWidget);
        widgetForTouch->setObjectName(QStringLiteral("widgetForTouch"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widgetForTouch->sizePolicy().hasHeightForWidth());
        widgetForTouch->setSizePolicy(sizePolicy);
        widgetForTouch->setMinimumSize(QSize(0, 25));
        widgetForTouch->setMaximumSize(QSize(16777215, 25));
        widgetForTouch->setStyleSheet(QStringLiteral("background-color: rgb(85, 170, 255);"));

        horizontalLayout_7->addWidget(widgetForTouch);

        labelMax = new QLabel(centralWidget);
        labelMax->setObjectName(QStringLiteral("labelMax"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelMax->sizePolicy().hasHeightForWidth());
        labelMax->setSizePolicy(sizePolicy1);
        labelMax->setMinimumSize(QSize(100, 25));
        labelMax->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_7->addWidget(labelMax);


        verticalLayout_4->addLayout(horizontalLayout_7);

        UI_W_MASS = new QWidget(centralWidget);
        UI_W_MASS->setObjectName(QStringLiteral("UI_W_MASS"));
        verticalLayout_3 = new QVBoxLayout(UI_W_MASS);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(9, 9, 9, 9);

        verticalLayout_4->addWidget(UI_W_MASS);


        horizontalLayout_4->addLayout(verticalLayout_4);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy2);
        pushButton->setMinimumSize(QSize(50, 600));
        pushButton->setMaximumSize(QSize(50, 16777215));
        pushButton->setAutoFillBackground(false);
        pushButton->setStyleSheet(QStringLiteral("border-image: url(:/picture/Icon_Left.jpg);"));

        horizontalLayout_4->addWidget(pushButton);

        verticalWidget_2 = new QWidget(centralWidget);
        verticalWidget_2->setObjectName(QStringLiteral("verticalWidget_2"));
        verticalWidget_2->setMinimumSize(QSize(0, 0));
        verticalWidget_2->setMaximumSize(QSize(200, 16777215));
        verticalLayout_5 = new QVBoxLayout(verticalWidget_2);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalWidget_3 = new QWidget(verticalWidget_2);
        verticalWidget_3->setObjectName(QStringLiteral("verticalWidget_3"));
        verticalWidget_3->setMinimumSize(QSize(0, 0));
        verticalLayout_6 = new QVBoxLayout(verticalWidget_3);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);

        verticalLayout_5->addWidget(verticalWidget_3);

        delBtn = new QPushButton(verticalWidget_2);
        delBtn->setObjectName(QStringLiteral("delBtn"));
        delBtn->setMinimumSize(QSize(0, 0));
        delBtn->setMaximumSize(QSize(200, 16777215));

        verticalLayout_5->addWidget(delBtn);

        btn_saveFrame = new QPushButton(verticalWidget_2);
        btn_saveFrame->setObjectName(QStringLiteral("btn_saveFrame"));
        btn_saveFrame->setMinimumSize(QSize(0, 100));

        verticalLayout_5->addWidget(btn_saveFrame);


        horizontalLayout_4->addWidget(verticalWidget_2);


        verticalLayout->addLayout(horizontalLayout_4);

        sDataAnalysis->setCentralWidget(centralWidget);

        retranslateUi(sDataAnalysis);

        QMetaObject::connectSlotsByName(sDataAnalysis);
    } // setupUi

    void retranslateUi(QMainWindow *sDataAnalysis)
    {
        sDataAnalysis->setWindowTitle(QApplication::translate("sDataAnalysis", "sDataAnalysis", nullptr));
        groupBox_Inform->setTitle(QApplication::translate("sDataAnalysis", "Information", nullptr));
        labelFileName->setText(QString());
        labelFileTime->setText(QString());
        labelCurrentPage->setText(QString());
        groupBox_tools->setTitle(QApplication::translate("sDataAnalysis", "Tools", nullptr));
        BtnAdd->setText(QApplication::translate("sDataAnalysis", "\346\267\273\345\212\240\351\200\232\351\201\223", nullptr));
        BtnChange->setText(QApplication::translate("sDataAnalysis", "showAll", nullptr));
        groupBox->setTitle(QApplication::translate("sDataAnalysis", "Accumulation", nullptr));
        UI_PB_TIC_CHOOSE->setText(QApplication::translate("sDataAnalysis", "Enable", nullptr));
        UI_PB_ACCTIC->setText(QApplication::translate("sDataAnalysis", "Accumulate", nullptr));
        UI_PB_TIC_CLEAR->setText(QApplication::translate("sDataAnalysis", "ClearLine", nullptr));
        groupBox_2->setTitle(QApplication::translate("sDataAnalysis", "FWHM  Area", nullptr));
        UI_PB_MASS_CHOOSE->setText(QApplication::translate("sDataAnalysis", "Enable", nullptr));
        UI_PB_CALCULATE->setText(QApplication::translate("sDataAnalysis", "Calculate", nullptr));
        UI_PB_MASS_CLEAR->setText(QApplication::translate("sDataAnalysis", "ClearLine", nullptr));
        labelMin->setText(QString());
        labelMax->setText(QString());
        pushButton->setText(QString());
        delBtn->setText(QApplication::translate("sDataAnalysis", "Delete", nullptr));
        btn_saveFrame->setText(QApplication::translate("sDataAnalysis", "\344\277\235\345\255\230\345\275\223\345\211\215\345\270\247", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sDataAnalysis: public Ui_sDataAnalysis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SDATAANALYSIS_H
