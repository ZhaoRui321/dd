/********************************************************************************
** Form generated from reading UI file 'sControlSSC.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCONTROLSSC_H
#define UI_SCONTROLSSC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sControlSSC
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *L_connect;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *B_Update;
    QHBoxLayout *horizontalLayout_2;
    QTableWidget *TABLE_CCS;
    QGridLayout *gridLayout;
    QPushButton *UI_PB_IO5;
    QLabel *UI_L_SWITCH;
    QPushButton *UI_PB_IO3;
    QPushButton *UI_PB_IO6;
    QPushButton *UI_PB_IO2;
    QPushButton *UI_PB_IO0;
    QPushButton *UI_PB_IO4;
    QPushButton *UI_PB_IO1;
    QPushButton *UI_PB_IO7;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QTableWidget *TABLE_TempSet;
    QTableWidget *TABLE_DacSet;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *TABLE_TempGet;
    QTableWidget *TABLE_ADC1;
    QTableWidget *TABLE_ADC2;

    void setupUi(QWidget *sControlSSC)
    {
        if (sControlSSC->objectName().isEmpty())
            sControlSSC->setObjectName(QStringLiteral("sControlSSC"));
        sControlSSC->resize(1126, 645);
        sControlSSC->setMinimumSize(QSize(0, 0));
        verticalLayout_3 = new QVBoxLayout(sControlSSC);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        L_connect = new QLabel(sControlSSC);
        L_connect->setObjectName(QStringLiteral("L_connect"));

        horizontalLayout->addWidget(L_connect);

        label = new QLabel(sControlSSC);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(sControlSSC);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        B_Update = new QPushButton(sControlSSC);
        B_Update->setObjectName(QStringLiteral("B_Update"));

        horizontalLayout->addWidget(B_Update);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        TABLE_CCS = new QTableWidget(sControlSSC);
        if (TABLE_CCS->columnCount() < 4)
            TABLE_CCS->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        TABLE_CCS->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        TABLE_CCS->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        TABLE_CCS->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        TABLE_CCS->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        if (TABLE_CCS->rowCount() < 3)
            TABLE_CCS->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        TABLE_CCS->setVerticalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        TABLE_CCS->setVerticalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        TABLE_CCS->setVerticalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsEnabled);
        TABLE_CCS->setItem(0, 0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsEnabled);
        TABLE_CCS->setItem(0, 1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        __qtablewidgetitem9->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsEnabled);
        TABLE_CCS->setItem(0, 2, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        __qtablewidgetitem10->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsEnabled);
        TABLE_CCS->setItem(0, 3, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        TABLE_CCS->setItem(1, 0, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        TABLE_CCS->setItem(2, 0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        TABLE_CCS->setItem(2, 1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        TABLE_CCS->setItem(2, 2, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        TABLE_CCS->setItem(2, 3, __qtablewidgetitem15);
        TABLE_CCS->setObjectName(QStringLiteral("TABLE_CCS"));
        TABLE_CCS->setMinimumSize(QSize(0, 135));

        horizontalLayout_2->addWidget(TABLE_CCS);


        verticalLayout_3->addLayout(horizontalLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        UI_PB_IO5 = new QPushButton(sControlSSC);
        UI_PB_IO5->setObjectName(QStringLiteral("UI_PB_IO5"));

        gridLayout->addWidget(UI_PB_IO5, 0, 6, 1, 1);

        UI_L_SWITCH = new QLabel(sControlSSC);
        UI_L_SWITCH->setObjectName(QStringLiteral("UI_L_SWITCH"));

        gridLayout->addWidget(UI_L_SWITCH, 0, 0, 1, 1);

        UI_PB_IO3 = new QPushButton(sControlSSC);
        UI_PB_IO3->setObjectName(QStringLiteral("UI_PB_IO3"));

        gridLayout->addWidget(UI_PB_IO3, 0, 4, 1, 1);

        UI_PB_IO6 = new QPushButton(sControlSSC);
        UI_PB_IO6->setObjectName(QStringLiteral("UI_PB_IO6"));

        gridLayout->addWidget(UI_PB_IO6, 0, 7, 1, 1);

        UI_PB_IO2 = new QPushButton(sControlSSC);
        UI_PB_IO2->setObjectName(QStringLiteral("UI_PB_IO2"));

        gridLayout->addWidget(UI_PB_IO2, 0, 3, 1, 1);

        UI_PB_IO0 = new QPushButton(sControlSSC);
        UI_PB_IO0->setObjectName(QStringLiteral("UI_PB_IO0"));

        gridLayout->addWidget(UI_PB_IO0, 0, 1, 1, 1);

        UI_PB_IO4 = new QPushButton(sControlSSC);
        UI_PB_IO4->setObjectName(QStringLiteral("UI_PB_IO4"));

        gridLayout->addWidget(UI_PB_IO4, 0, 5, 1, 1);

        UI_PB_IO1 = new QPushButton(sControlSSC);
        UI_PB_IO1->setObjectName(QStringLiteral("UI_PB_IO1"));

        gridLayout->addWidget(UI_PB_IO1, 0, 2, 1, 1);

        UI_PB_IO7 = new QPushButton(sControlSSC);
        UI_PB_IO7->setObjectName(QStringLiteral("UI_PB_IO7"));

        gridLayout->addWidget(UI_PB_IO7, 0, 8, 1, 1);


        verticalLayout_3->addLayout(gridLayout);

        tabWidget = new QTabWidget(sControlSSC);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        TABLE_TempSet = new QTableWidget(tab);
        if (TABLE_TempSet->columnCount() < 6)
            TABLE_TempSet->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        TABLE_TempSet->setHorizontalHeaderItem(0, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        TABLE_TempSet->setHorizontalHeaderItem(1, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        TABLE_TempSet->setHorizontalHeaderItem(2, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        TABLE_TempSet->setHorizontalHeaderItem(3, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        TABLE_TempSet->setHorizontalHeaderItem(4, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        TABLE_TempSet->setHorizontalHeaderItem(5, __qtablewidgetitem21);
        if (TABLE_TempSet->rowCount() < 4)
            TABLE_TempSet->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        TABLE_TempSet->setVerticalHeaderItem(0, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        TABLE_TempSet->setVerticalHeaderItem(1, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        TABLE_TempSet->setVerticalHeaderItem(2, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        TABLE_TempSet->setVerticalHeaderItem(3, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        __qtablewidgetitem26->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        TABLE_TempSet->setItem(0, 0, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        __qtablewidgetitem27->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        TABLE_TempSet->setItem(0, 1, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        __qtablewidgetitem28->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        TABLE_TempSet->setItem(0, 2, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        __qtablewidgetitem29->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        TABLE_TempSet->setItem(0, 3, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        __qtablewidgetitem30->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        TABLE_TempSet->setItem(0, 4, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        __qtablewidgetitem31->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        TABLE_TempSet->setItem(0, 5, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        __qtablewidgetitem32->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        TABLE_TempSet->setItem(2, 0, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        TABLE_TempSet->setItem(2, 1, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        TABLE_TempSet->setItem(2, 2, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        TABLE_TempSet->setItem(2, 3, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        TABLE_TempSet->setItem(2, 4, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        TABLE_TempSet->setItem(2, 5, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        TABLE_TempSet->setItem(3, 0, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        TABLE_TempSet->setItem(3, 1, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        TABLE_TempSet->setItem(3, 2, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        TABLE_TempSet->setItem(3, 3, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        TABLE_TempSet->setItem(3, 4, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        TABLE_TempSet->setItem(3, 5, __qtablewidgetitem43);
        TABLE_TempSet->setObjectName(QStringLiteral("TABLE_TempSet"));
        TABLE_TempSet->setMinimumSize(QSize(0, 150));

        verticalLayout->addWidget(TABLE_TempSet);

        TABLE_DacSet = new QTableWidget(tab);
        if (TABLE_DacSet->columnCount() < 8)
            TABLE_DacSet->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        TABLE_DacSet->setHorizontalHeaderItem(0, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        TABLE_DacSet->setHorizontalHeaderItem(1, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        TABLE_DacSet->setHorizontalHeaderItem(2, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        TABLE_DacSet->setHorizontalHeaderItem(3, __qtablewidgetitem47);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        TABLE_DacSet->setHorizontalHeaderItem(4, __qtablewidgetitem48);
        QTableWidgetItem *__qtablewidgetitem49 = new QTableWidgetItem();
        TABLE_DacSet->setHorizontalHeaderItem(5, __qtablewidgetitem49);
        QTableWidgetItem *__qtablewidgetitem50 = new QTableWidgetItem();
        TABLE_DacSet->setHorizontalHeaderItem(6, __qtablewidgetitem50);
        QTableWidgetItem *__qtablewidgetitem51 = new QTableWidgetItem();
        TABLE_DacSet->setHorizontalHeaderItem(7, __qtablewidgetitem51);
        if (TABLE_DacSet->rowCount() < 3)
            TABLE_DacSet->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem52 = new QTableWidgetItem();
        TABLE_DacSet->setVerticalHeaderItem(0, __qtablewidgetitem52);
        QTableWidgetItem *__qtablewidgetitem53 = new QTableWidgetItem();
        TABLE_DacSet->setVerticalHeaderItem(1, __qtablewidgetitem53);
        QTableWidgetItem *__qtablewidgetitem54 = new QTableWidgetItem();
        TABLE_DacSet->setVerticalHeaderItem(2, __qtablewidgetitem54);
        QTableWidgetItem *__qtablewidgetitem55 = new QTableWidgetItem();
        TABLE_DacSet->setItem(0, 0, __qtablewidgetitem55);
        QTableWidgetItem *__qtablewidgetitem56 = new QTableWidgetItem();
        TABLE_DacSet->setItem(0, 1, __qtablewidgetitem56);
        QTableWidgetItem *__qtablewidgetitem57 = new QTableWidgetItem();
        TABLE_DacSet->setItem(0, 2, __qtablewidgetitem57);
        QTableWidgetItem *__qtablewidgetitem58 = new QTableWidgetItem();
        TABLE_DacSet->setItem(0, 3, __qtablewidgetitem58);
        QTableWidgetItem *__qtablewidgetitem59 = new QTableWidgetItem();
        TABLE_DacSet->setItem(0, 4, __qtablewidgetitem59);
        QTableWidgetItem *__qtablewidgetitem60 = new QTableWidgetItem();
        TABLE_DacSet->setItem(0, 5, __qtablewidgetitem60);
        QTableWidgetItem *__qtablewidgetitem61 = new QTableWidgetItem();
        TABLE_DacSet->setItem(0, 6, __qtablewidgetitem61);
        QTableWidgetItem *__qtablewidgetitem62 = new QTableWidgetItem();
        TABLE_DacSet->setItem(0, 7, __qtablewidgetitem62);
        QTableWidgetItem *__qtablewidgetitem63 = new QTableWidgetItem();
        TABLE_DacSet->setItem(2, 0, __qtablewidgetitem63);
        QTableWidgetItem *__qtablewidgetitem64 = new QTableWidgetItem();
        TABLE_DacSet->setItem(2, 1, __qtablewidgetitem64);
        QTableWidgetItem *__qtablewidgetitem65 = new QTableWidgetItem();
        TABLE_DacSet->setItem(2, 2, __qtablewidgetitem65);
        QTableWidgetItem *__qtablewidgetitem66 = new QTableWidgetItem();
        TABLE_DacSet->setItem(2, 3, __qtablewidgetitem66);
        QTableWidgetItem *__qtablewidgetitem67 = new QTableWidgetItem();
        TABLE_DacSet->setItem(2, 4, __qtablewidgetitem67);
        QTableWidgetItem *__qtablewidgetitem68 = new QTableWidgetItem();
        TABLE_DacSet->setItem(2, 5, __qtablewidgetitem68);
        QTableWidgetItem *__qtablewidgetitem69 = new QTableWidgetItem();
        TABLE_DacSet->setItem(2, 6, __qtablewidgetitem69);
        QTableWidgetItem *__qtablewidgetitem70 = new QTableWidgetItem();
        TABLE_DacSet->setItem(2, 7, __qtablewidgetitem70);
        TABLE_DacSet->setObjectName(QStringLiteral("TABLE_DacSet"));
        TABLE_DacSet->setMinimumSize(QSize(0, 120));

        verticalLayout->addWidget(TABLE_DacSet);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_2 = new QVBoxLayout(tab_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        TABLE_TempGet = new QTableWidget(tab_2);
        if (TABLE_TempGet->columnCount() < 6)
            TABLE_TempGet->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem71 = new QTableWidgetItem();
        TABLE_TempGet->setHorizontalHeaderItem(0, __qtablewidgetitem71);
        QTableWidgetItem *__qtablewidgetitem72 = new QTableWidgetItem();
        TABLE_TempGet->setHorizontalHeaderItem(1, __qtablewidgetitem72);
        QTableWidgetItem *__qtablewidgetitem73 = new QTableWidgetItem();
        TABLE_TempGet->setHorizontalHeaderItem(2, __qtablewidgetitem73);
        QTableWidgetItem *__qtablewidgetitem74 = new QTableWidgetItem();
        TABLE_TempGet->setHorizontalHeaderItem(3, __qtablewidgetitem74);
        QTableWidgetItem *__qtablewidgetitem75 = new QTableWidgetItem();
        TABLE_TempGet->setHorizontalHeaderItem(4, __qtablewidgetitem75);
        QTableWidgetItem *__qtablewidgetitem76 = new QTableWidgetItem();
        TABLE_TempGet->setHorizontalHeaderItem(5, __qtablewidgetitem76);
        if (TABLE_TempGet->rowCount() < 3)
            TABLE_TempGet->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem77 = new QTableWidgetItem();
        TABLE_TempGet->setVerticalHeaderItem(0, __qtablewidgetitem77);
        QTableWidgetItem *__qtablewidgetitem78 = new QTableWidgetItem();
        TABLE_TempGet->setVerticalHeaderItem(1, __qtablewidgetitem78);
        QTableWidgetItem *__qtablewidgetitem79 = new QTableWidgetItem();
        TABLE_TempGet->setVerticalHeaderItem(2, __qtablewidgetitem79);
        QTableWidgetItem *__qtablewidgetitem80 = new QTableWidgetItem();
        TABLE_TempGet->setItem(0, 0, __qtablewidgetitem80);
        QTableWidgetItem *__qtablewidgetitem81 = new QTableWidgetItem();
        TABLE_TempGet->setItem(0, 1, __qtablewidgetitem81);
        QTableWidgetItem *__qtablewidgetitem82 = new QTableWidgetItem();
        TABLE_TempGet->setItem(0, 2, __qtablewidgetitem82);
        QTableWidgetItem *__qtablewidgetitem83 = new QTableWidgetItem();
        TABLE_TempGet->setItem(0, 3, __qtablewidgetitem83);
        QTableWidgetItem *__qtablewidgetitem84 = new QTableWidgetItem();
        TABLE_TempGet->setItem(0, 4, __qtablewidgetitem84);
        QTableWidgetItem *__qtablewidgetitem85 = new QTableWidgetItem();
        TABLE_TempGet->setItem(0, 5, __qtablewidgetitem85);
        QTableWidgetItem *__qtablewidgetitem86 = new QTableWidgetItem();
        TABLE_TempGet->setItem(2, 0, __qtablewidgetitem86);
        QTableWidgetItem *__qtablewidgetitem87 = new QTableWidgetItem();
        TABLE_TempGet->setItem(2, 1, __qtablewidgetitem87);
        QTableWidgetItem *__qtablewidgetitem88 = new QTableWidgetItem();
        TABLE_TempGet->setItem(2, 2, __qtablewidgetitem88);
        QTableWidgetItem *__qtablewidgetitem89 = new QTableWidgetItem();
        TABLE_TempGet->setItem(2, 3, __qtablewidgetitem89);
        QTableWidgetItem *__qtablewidgetitem90 = new QTableWidgetItem();
        TABLE_TempGet->setItem(2, 4, __qtablewidgetitem90);
        QTableWidgetItem *__qtablewidgetitem91 = new QTableWidgetItem();
        TABLE_TempGet->setItem(2, 5, __qtablewidgetitem91);
        TABLE_TempGet->setObjectName(QStringLiteral("TABLE_TempGet"));
        TABLE_TempGet->setMinimumSize(QSize(0, 120));

        verticalLayout_2->addWidget(TABLE_TempGet);

        TABLE_ADC1 = new QTableWidget(tab_2);
        if (TABLE_ADC1->columnCount() < 8)
            TABLE_ADC1->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem92 = new QTableWidgetItem();
        TABLE_ADC1->setHorizontalHeaderItem(0, __qtablewidgetitem92);
        QTableWidgetItem *__qtablewidgetitem93 = new QTableWidgetItem();
        TABLE_ADC1->setHorizontalHeaderItem(1, __qtablewidgetitem93);
        QTableWidgetItem *__qtablewidgetitem94 = new QTableWidgetItem();
        TABLE_ADC1->setHorizontalHeaderItem(2, __qtablewidgetitem94);
        QTableWidgetItem *__qtablewidgetitem95 = new QTableWidgetItem();
        TABLE_ADC1->setHorizontalHeaderItem(3, __qtablewidgetitem95);
        QTableWidgetItem *__qtablewidgetitem96 = new QTableWidgetItem();
        TABLE_ADC1->setHorizontalHeaderItem(4, __qtablewidgetitem96);
        QTableWidgetItem *__qtablewidgetitem97 = new QTableWidgetItem();
        TABLE_ADC1->setHorizontalHeaderItem(5, __qtablewidgetitem97);
        QTableWidgetItem *__qtablewidgetitem98 = new QTableWidgetItem();
        TABLE_ADC1->setHorizontalHeaderItem(6, __qtablewidgetitem98);
        QTableWidgetItem *__qtablewidgetitem99 = new QTableWidgetItem();
        TABLE_ADC1->setHorizontalHeaderItem(7, __qtablewidgetitem99);
        if (TABLE_ADC1->rowCount() < 3)
            TABLE_ADC1->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem100 = new QTableWidgetItem();
        TABLE_ADC1->setVerticalHeaderItem(0, __qtablewidgetitem100);
        QTableWidgetItem *__qtablewidgetitem101 = new QTableWidgetItem();
        TABLE_ADC1->setVerticalHeaderItem(1, __qtablewidgetitem101);
        QTableWidgetItem *__qtablewidgetitem102 = new QTableWidgetItem();
        TABLE_ADC1->setVerticalHeaderItem(2, __qtablewidgetitem102);
        QTableWidgetItem *__qtablewidgetitem103 = new QTableWidgetItem();
        TABLE_ADC1->setItem(0, 0, __qtablewidgetitem103);
        QTableWidgetItem *__qtablewidgetitem104 = new QTableWidgetItem();
        TABLE_ADC1->setItem(0, 1, __qtablewidgetitem104);
        QTableWidgetItem *__qtablewidgetitem105 = new QTableWidgetItem();
        TABLE_ADC1->setItem(0, 2, __qtablewidgetitem105);
        QTableWidgetItem *__qtablewidgetitem106 = new QTableWidgetItem();
        TABLE_ADC1->setItem(0, 3, __qtablewidgetitem106);
        QTableWidgetItem *__qtablewidgetitem107 = new QTableWidgetItem();
        TABLE_ADC1->setItem(0, 4, __qtablewidgetitem107);
        QTableWidgetItem *__qtablewidgetitem108 = new QTableWidgetItem();
        TABLE_ADC1->setItem(0, 5, __qtablewidgetitem108);
        QTableWidgetItem *__qtablewidgetitem109 = new QTableWidgetItem();
        TABLE_ADC1->setItem(0, 6, __qtablewidgetitem109);
        QTableWidgetItem *__qtablewidgetitem110 = new QTableWidgetItem();
        TABLE_ADC1->setItem(0, 7, __qtablewidgetitem110);
        QTableWidgetItem *__qtablewidgetitem111 = new QTableWidgetItem();
        TABLE_ADC1->setItem(2, 0, __qtablewidgetitem111);
        QTableWidgetItem *__qtablewidgetitem112 = new QTableWidgetItem();
        TABLE_ADC1->setItem(2, 1, __qtablewidgetitem112);
        QTableWidgetItem *__qtablewidgetitem113 = new QTableWidgetItem();
        TABLE_ADC1->setItem(2, 2, __qtablewidgetitem113);
        QTableWidgetItem *__qtablewidgetitem114 = new QTableWidgetItem();
        TABLE_ADC1->setItem(2, 3, __qtablewidgetitem114);
        QTableWidgetItem *__qtablewidgetitem115 = new QTableWidgetItem();
        TABLE_ADC1->setItem(2, 4, __qtablewidgetitem115);
        QTableWidgetItem *__qtablewidgetitem116 = new QTableWidgetItem();
        TABLE_ADC1->setItem(2, 5, __qtablewidgetitem116);
        QTableWidgetItem *__qtablewidgetitem117 = new QTableWidgetItem();
        TABLE_ADC1->setItem(2, 6, __qtablewidgetitem117);
        QTableWidgetItem *__qtablewidgetitem118 = new QTableWidgetItem();
        TABLE_ADC1->setItem(2, 7, __qtablewidgetitem118);
        TABLE_ADC1->setObjectName(QStringLiteral("TABLE_ADC1"));
        TABLE_ADC1->setMinimumSize(QSize(0, 120));

        verticalLayout_2->addWidget(TABLE_ADC1);

        TABLE_ADC2 = new QTableWidget(tab_2);
        if (TABLE_ADC2->columnCount() < 8)
            TABLE_ADC2->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem119 = new QTableWidgetItem();
        TABLE_ADC2->setHorizontalHeaderItem(0, __qtablewidgetitem119);
        QTableWidgetItem *__qtablewidgetitem120 = new QTableWidgetItem();
        TABLE_ADC2->setHorizontalHeaderItem(1, __qtablewidgetitem120);
        QTableWidgetItem *__qtablewidgetitem121 = new QTableWidgetItem();
        TABLE_ADC2->setHorizontalHeaderItem(2, __qtablewidgetitem121);
        QTableWidgetItem *__qtablewidgetitem122 = new QTableWidgetItem();
        TABLE_ADC2->setHorizontalHeaderItem(3, __qtablewidgetitem122);
        QTableWidgetItem *__qtablewidgetitem123 = new QTableWidgetItem();
        TABLE_ADC2->setHorizontalHeaderItem(4, __qtablewidgetitem123);
        QTableWidgetItem *__qtablewidgetitem124 = new QTableWidgetItem();
        TABLE_ADC2->setHorizontalHeaderItem(5, __qtablewidgetitem124);
        QTableWidgetItem *__qtablewidgetitem125 = new QTableWidgetItem();
        TABLE_ADC2->setHorizontalHeaderItem(6, __qtablewidgetitem125);
        QTableWidgetItem *__qtablewidgetitem126 = new QTableWidgetItem();
        TABLE_ADC2->setHorizontalHeaderItem(7, __qtablewidgetitem126);
        if (TABLE_ADC2->rowCount() < 3)
            TABLE_ADC2->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem127 = new QTableWidgetItem();
        TABLE_ADC2->setVerticalHeaderItem(0, __qtablewidgetitem127);
        QTableWidgetItem *__qtablewidgetitem128 = new QTableWidgetItem();
        TABLE_ADC2->setVerticalHeaderItem(1, __qtablewidgetitem128);
        QTableWidgetItem *__qtablewidgetitem129 = new QTableWidgetItem();
        TABLE_ADC2->setVerticalHeaderItem(2, __qtablewidgetitem129);
        QTableWidgetItem *__qtablewidgetitem130 = new QTableWidgetItem();
        TABLE_ADC2->setItem(0, 0, __qtablewidgetitem130);
        QTableWidgetItem *__qtablewidgetitem131 = new QTableWidgetItem();
        TABLE_ADC2->setItem(0, 1, __qtablewidgetitem131);
        QTableWidgetItem *__qtablewidgetitem132 = new QTableWidgetItem();
        TABLE_ADC2->setItem(0, 2, __qtablewidgetitem132);
        QTableWidgetItem *__qtablewidgetitem133 = new QTableWidgetItem();
        TABLE_ADC2->setItem(0, 3, __qtablewidgetitem133);
        QTableWidgetItem *__qtablewidgetitem134 = new QTableWidgetItem();
        TABLE_ADC2->setItem(0, 4, __qtablewidgetitem134);
        QTableWidgetItem *__qtablewidgetitem135 = new QTableWidgetItem();
        TABLE_ADC2->setItem(0, 5, __qtablewidgetitem135);
        QTableWidgetItem *__qtablewidgetitem136 = new QTableWidgetItem();
        TABLE_ADC2->setItem(0, 6, __qtablewidgetitem136);
        QTableWidgetItem *__qtablewidgetitem137 = new QTableWidgetItem();
        TABLE_ADC2->setItem(0, 7, __qtablewidgetitem137);
        QTableWidgetItem *__qtablewidgetitem138 = new QTableWidgetItem();
        TABLE_ADC2->setItem(2, 0, __qtablewidgetitem138);
        QTableWidgetItem *__qtablewidgetitem139 = new QTableWidgetItem();
        TABLE_ADC2->setItem(2, 1, __qtablewidgetitem139);
        QTableWidgetItem *__qtablewidgetitem140 = new QTableWidgetItem();
        TABLE_ADC2->setItem(2, 2, __qtablewidgetitem140);
        QTableWidgetItem *__qtablewidgetitem141 = new QTableWidgetItem();
        TABLE_ADC2->setItem(2, 3, __qtablewidgetitem141);
        QTableWidgetItem *__qtablewidgetitem142 = new QTableWidgetItem();
        TABLE_ADC2->setItem(2, 4, __qtablewidgetitem142);
        QTableWidgetItem *__qtablewidgetitem143 = new QTableWidgetItem();
        TABLE_ADC2->setItem(2, 5, __qtablewidgetitem143);
        QTableWidgetItem *__qtablewidgetitem144 = new QTableWidgetItem();
        TABLE_ADC2->setItem(2, 6, __qtablewidgetitem144);
        QTableWidgetItem *__qtablewidgetitem145 = new QTableWidgetItem();
        TABLE_ADC2->setItem(2, 7, __qtablewidgetitem145);
        TABLE_ADC2->setObjectName(QStringLiteral("TABLE_ADC2"));
        TABLE_ADC2->setMinimumSize(QSize(0, 120));

        verticalLayout_2->addWidget(TABLE_ADC2);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_3->addWidget(tabWidget);


        retranslateUi(sControlSSC);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(sControlSSC);
    } // setupUi

    void retranslateUi(QWidget *sControlSSC)
    {
        sControlSSC->setWindowTitle(QApplication::translate("sControlSSC", "Form", nullptr));
        L_connect->setText(QApplication::translate("sControlSSC", "TextLabel", nullptr));
        label->setText(QApplication::translate("sControlSSC", "TextLabel", nullptr));
        B_Update->setText(QApplication::translate("sControlSSC", "Save", nullptr));
        QTableWidgetItem *___qtablewidgetitem = TABLE_CCS->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("sControlSSC", "CCS_ADC1", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = TABLE_CCS->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("sControlSSC", "CCS_ADC2", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = TABLE_CCS->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("sControlSSC", "CCS_ADC3", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = TABLE_CCS->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("sControlSSC", "CCS_ADC4", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = TABLE_CCS->verticalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("sControlSSC", "Original", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = TABLE_CCS->verticalHeaderItem(1);
        ___qtablewidgetitem5->setText(QApplication::translate("sControlSSC", "JavaScript", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = TABLE_CCS->verticalHeaderItem(2);
        ___qtablewidgetitem6->setText(QApplication::translate("sControlSSC", "Value", nullptr));

        const bool __sortingEnabled = TABLE_CCS->isSortingEnabled();
        TABLE_CCS->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem7 = TABLE_CCS->item(0, 0);
        ___qtablewidgetitem7->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = TABLE_CCS->item(0, 1);
        ___qtablewidgetitem8->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = TABLE_CCS->item(0, 2);
        ___qtablewidgetitem9->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = TABLE_CCS->item(0, 3);
        ___qtablewidgetitem10->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = TABLE_CCS->item(1, 0);
        ___qtablewidgetitem11->setText(QApplication::translate("sControlSSC", "return CCS_ADC1;", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = TABLE_CCS->item(2, 0);
        ___qtablewidgetitem12->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = TABLE_CCS->item(2, 1);
        ___qtablewidgetitem13->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = TABLE_CCS->item(2, 2);
        ___qtablewidgetitem14->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = TABLE_CCS->item(2, 3);
        ___qtablewidgetitem15->setText(QApplication::translate("sControlSSC", "0", nullptr));
        TABLE_CCS->setSortingEnabled(__sortingEnabled);

        UI_PB_IO5->setText(QApplication::translate("sControlSSC", "On", nullptr));
        UI_L_SWITCH->setText(QApplication::translate("sControlSSC", "Switch", nullptr));
        UI_PB_IO3->setText(QApplication::translate("sControlSSC", "On", nullptr));
        UI_PB_IO6->setText(QApplication::translate("sControlSSC", "On", nullptr));
        UI_PB_IO2->setText(QApplication::translate("sControlSSC", "On", nullptr));
        UI_PB_IO0->setText(QApplication::translate("sControlSSC", "On", nullptr));
        UI_PB_IO4->setText(QApplication::translate("sControlSSC", "On", nullptr));
        UI_PB_IO1->setText(QApplication::translate("sControlSSC", "On", nullptr));
        UI_PB_IO7->setText(QApplication::translate("sControlSSC", "On", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = TABLE_TempSet->horizontalHeaderItem(0);
        ___qtablewidgetitem16->setText(QApplication::translate("sControlSSC", "TempSet1", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = TABLE_TempSet->horizontalHeaderItem(1);
        ___qtablewidgetitem17->setText(QApplication::translate("sControlSSC", "TempSet2", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = TABLE_TempSet->horizontalHeaderItem(2);
        ___qtablewidgetitem18->setText(QApplication::translate("sControlSSC", "TempSet3", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = TABLE_TempSet->horizontalHeaderItem(3);
        ___qtablewidgetitem19->setText(QApplication::translate("sControlSSC", "TempSet4", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = TABLE_TempSet->horizontalHeaderItem(4);
        ___qtablewidgetitem20->setText(QApplication::translate("sControlSSC", "TempSet5", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = TABLE_TempSet->horizontalHeaderItem(5);
        ___qtablewidgetitem21->setText(QApplication::translate("sControlSSC", "TempSet6", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = TABLE_TempSet->verticalHeaderItem(0);
        ___qtablewidgetitem22->setText(QApplication::translate("sControlSSC", "Original", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = TABLE_TempSet->verticalHeaderItem(1);
        ___qtablewidgetitem23->setText(QApplication::translate("sControlSSC", "JavaScript", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = TABLE_TempSet->verticalHeaderItem(2);
        ___qtablewidgetitem24->setText(QApplication::translate("sControlSSC", "Value", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = TABLE_TempSet->verticalHeaderItem(3);
        ___qtablewidgetitem25->setText(QApplication::translate("sControlSSC", "PID", nullptr));

        const bool __sortingEnabled1 = TABLE_TempSet->isSortingEnabled();
        TABLE_TempSet->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem26 = TABLE_TempSet->item(0, 0);
        ___qtablewidgetitem26->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = TABLE_TempSet->item(0, 1);
        ___qtablewidgetitem27->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = TABLE_TempSet->item(0, 2);
        ___qtablewidgetitem28->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem29 = TABLE_TempSet->item(0, 3);
        ___qtablewidgetitem29->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem30 = TABLE_TempSet->item(0, 4);
        ___qtablewidgetitem30->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem31 = TABLE_TempSet->item(0, 5);
        ___qtablewidgetitem31->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem32 = TABLE_TempSet->item(2, 0);
        ___qtablewidgetitem32->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem33 = TABLE_TempSet->item(2, 1);
        ___qtablewidgetitem33->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem34 = TABLE_TempSet->item(2, 2);
        ___qtablewidgetitem34->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem35 = TABLE_TempSet->item(2, 3);
        ___qtablewidgetitem35->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem36 = TABLE_TempSet->item(2, 4);
        ___qtablewidgetitem36->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem37 = TABLE_TempSet->item(2, 5);
        ___qtablewidgetitem37->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem38 = TABLE_TempSet->item(3, 0);
        ___qtablewidgetitem38->setText(QApplication::translate("sControlSSC", "0@0@0", nullptr));
        QTableWidgetItem *___qtablewidgetitem39 = TABLE_TempSet->item(3, 1);
        ___qtablewidgetitem39->setText(QApplication::translate("sControlSSC", "0@0@0", nullptr));
        QTableWidgetItem *___qtablewidgetitem40 = TABLE_TempSet->item(3, 2);
        ___qtablewidgetitem40->setText(QApplication::translate("sControlSSC", "0@0@0", nullptr));
        QTableWidgetItem *___qtablewidgetitem41 = TABLE_TempSet->item(3, 3);
        ___qtablewidgetitem41->setText(QApplication::translate("sControlSSC", "0@0@0", nullptr));
        QTableWidgetItem *___qtablewidgetitem42 = TABLE_TempSet->item(3, 4);
        ___qtablewidgetitem42->setText(QApplication::translate("sControlSSC", "0@0@0", nullptr));
        QTableWidgetItem *___qtablewidgetitem43 = TABLE_TempSet->item(3, 5);
        ___qtablewidgetitem43->setText(QApplication::translate("sControlSSC", "0@0@0", nullptr));
        TABLE_TempSet->setSortingEnabled(__sortingEnabled1);

        QTableWidgetItem *___qtablewidgetitem44 = TABLE_DacSet->horizontalHeaderItem(0);
        ___qtablewidgetitem44->setText(QApplication::translate("sControlSSC", "DAC1", nullptr));
        QTableWidgetItem *___qtablewidgetitem45 = TABLE_DacSet->horizontalHeaderItem(1);
        ___qtablewidgetitem45->setText(QApplication::translate("sControlSSC", "DAC2", nullptr));
        QTableWidgetItem *___qtablewidgetitem46 = TABLE_DacSet->horizontalHeaderItem(2);
        ___qtablewidgetitem46->setText(QApplication::translate("sControlSSC", "DAC3", nullptr));
        QTableWidgetItem *___qtablewidgetitem47 = TABLE_DacSet->horizontalHeaderItem(3);
        ___qtablewidgetitem47->setText(QApplication::translate("sControlSSC", "DAC4", nullptr));
        QTableWidgetItem *___qtablewidgetitem48 = TABLE_DacSet->horizontalHeaderItem(4);
        ___qtablewidgetitem48->setText(QApplication::translate("sControlSSC", "DAC5", nullptr));
        QTableWidgetItem *___qtablewidgetitem49 = TABLE_DacSet->horizontalHeaderItem(5);
        ___qtablewidgetitem49->setText(QApplication::translate("sControlSSC", "DAC6", nullptr));
        QTableWidgetItem *___qtablewidgetitem50 = TABLE_DacSet->horizontalHeaderItem(6);
        ___qtablewidgetitem50->setText(QApplication::translate("sControlSSC", "DAC7", nullptr));
        QTableWidgetItem *___qtablewidgetitem51 = TABLE_DacSet->horizontalHeaderItem(7);
        ___qtablewidgetitem51->setText(QApplication::translate("sControlSSC", "DAC8", nullptr));
        QTableWidgetItem *___qtablewidgetitem52 = TABLE_DacSet->verticalHeaderItem(0);
        ___qtablewidgetitem52->setText(QApplication::translate("sControlSSC", "Original", nullptr));
        QTableWidgetItem *___qtablewidgetitem53 = TABLE_DacSet->verticalHeaderItem(1);
        ___qtablewidgetitem53->setText(QApplication::translate("sControlSSC", "JavaScript", nullptr));
        QTableWidgetItem *___qtablewidgetitem54 = TABLE_DacSet->verticalHeaderItem(2);
        ___qtablewidgetitem54->setText(QApplication::translate("sControlSSC", "Value", nullptr));

        const bool __sortingEnabled2 = TABLE_DacSet->isSortingEnabled();
        TABLE_DacSet->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem55 = TABLE_DacSet->item(0, 0);
        ___qtablewidgetitem55->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem56 = TABLE_DacSet->item(0, 1);
        ___qtablewidgetitem56->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem57 = TABLE_DacSet->item(0, 2);
        ___qtablewidgetitem57->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem58 = TABLE_DacSet->item(0, 3);
        ___qtablewidgetitem58->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem59 = TABLE_DacSet->item(0, 4);
        ___qtablewidgetitem59->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem60 = TABLE_DacSet->item(0, 5);
        ___qtablewidgetitem60->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem61 = TABLE_DacSet->item(0, 6);
        ___qtablewidgetitem61->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem62 = TABLE_DacSet->item(0, 7);
        ___qtablewidgetitem62->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem63 = TABLE_DacSet->item(2, 0);
        ___qtablewidgetitem63->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem64 = TABLE_DacSet->item(2, 1);
        ___qtablewidgetitem64->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem65 = TABLE_DacSet->item(2, 2);
        ___qtablewidgetitem65->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem66 = TABLE_DacSet->item(2, 3);
        ___qtablewidgetitem66->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem67 = TABLE_DacSet->item(2, 4);
        ___qtablewidgetitem67->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem68 = TABLE_DacSet->item(2, 5);
        ___qtablewidgetitem68->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem69 = TABLE_DacSet->item(2, 6);
        ___qtablewidgetitem69->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem70 = TABLE_DacSet->item(2, 7);
        ___qtablewidgetitem70->setText(QApplication::translate("sControlSSC", "0", nullptr));
        TABLE_DacSet->setSortingEnabled(__sortingEnabled2);

        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("sControlSSC", "Tab 1", nullptr));
        QTableWidgetItem *___qtablewidgetitem71 = TABLE_TempGet->horizontalHeaderItem(0);
        ___qtablewidgetitem71->setText(QApplication::translate("sControlSSC", "TempGet1", nullptr));
        QTableWidgetItem *___qtablewidgetitem72 = TABLE_TempGet->horizontalHeaderItem(1);
        ___qtablewidgetitem72->setText(QApplication::translate("sControlSSC", "TempGet2", nullptr));
        QTableWidgetItem *___qtablewidgetitem73 = TABLE_TempGet->horizontalHeaderItem(2);
        ___qtablewidgetitem73->setText(QApplication::translate("sControlSSC", "TempGet3", nullptr));
        QTableWidgetItem *___qtablewidgetitem74 = TABLE_TempGet->horizontalHeaderItem(3);
        ___qtablewidgetitem74->setText(QApplication::translate("sControlSSC", "TempGet4", nullptr));
        QTableWidgetItem *___qtablewidgetitem75 = TABLE_TempGet->horizontalHeaderItem(4);
        ___qtablewidgetitem75->setText(QApplication::translate("sControlSSC", "TempGet5", nullptr));
        QTableWidgetItem *___qtablewidgetitem76 = TABLE_TempGet->horizontalHeaderItem(5);
        ___qtablewidgetitem76->setText(QApplication::translate("sControlSSC", "TempGet6", nullptr));
        QTableWidgetItem *___qtablewidgetitem77 = TABLE_TempGet->verticalHeaderItem(0);
        ___qtablewidgetitem77->setText(QApplication::translate("sControlSSC", "Original", nullptr));
        QTableWidgetItem *___qtablewidgetitem78 = TABLE_TempGet->verticalHeaderItem(1);
        ___qtablewidgetitem78->setText(QApplication::translate("sControlSSC", "JavaScript", nullptr));
        QTableWidgetItem *___qtablewidgetitem79 = TABLE_TempGet->verticalHeaderItem(2);
        ___qtablewidgetitem79->setText(QApplication::translate("sControlSSC", "Value", nullptr));

        const bool __sortingEnabled3 = TABLE_TempGet->isSortingEnabled();
        TABLE_TempGet->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem80 = TABLE_TempGet->item(0, 0);
        ___qtablewidgetitem80->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem81 = TABLE_TempGet->item(0, 1);
        ___qtablewidgetitem81->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem82 = TABLE_TempGet->item(0, 2);
        ___qtablewidgetitem82->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem83 = TABLE_TempGet->item(0, 3);
        ___qtablewidgetitem83->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem84 = TABLE_TempGet->item(0, 4);
        ___qtablewidgetitem84->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem85 = TABLE_TempGet->item(0, 5);
        ___qtablewidgetitem85->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem86 = TABLE_TempGet->item(2, 0);
        ___qtablewidgetitem86->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem87 = TABLE_TempGet->item(2, 1);
        ___qtablewidgetitem87->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem88 = TABLE_TempGet->item(2, 2);
        ___qtablewidgetitem88->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem89 = TABLE_TempGet->item(2, 3);
        ___qtablewidgetitem89->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem90 = TABLE_TempGet->item(2, 4);
        ___qtablewidgetitem90->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem91 = TABLE_TempGet->item(2, 5);
        ___qtablewidgetitem91->setText(QApplication::translate("sControlSSC", "0", nullptr));
        TABLE_TempGet->setSortingEnabled(__sortingEnabled3);

        QTableWidgetItem *___qtablewidgetitem92 = TABLE_ADC1->horizontalHeaderItem(0);
        ___qtablewidgetitem92->setText(QApplication::translate("sControlSSC", "ADC1", nullptr));
        QTableWidgetItem *___qtablewidgetitem93 = TABLE_ADC1->horizontalHeaderItem(1);
        ___qtablewidgetitem93->setText(QApplication::translate("sControlSSC", "ADC2", nullptr));
        QTableWidgetItem *___qtablewidgetitem94 = TABLE_ADC1->horizontalHeaderItem(2);
        ___qtablewidgetitem94->setText(QApplication::translate("sControlSSC", "ADC3", nullptr));
        QTableWidgetItem *___qtablewidgetitem95 = TABLE_ADC1->horizontalHeaderItem(3);
        ___qtablewidgetitem95->setText(QApplication::translate("sControlSSC", "ADC4", nullptr));
        QTableWidgetItem *___qtablewidgetitem96 = TABLE_ADC1->horizontalHeaderItem(4);
        ___qtablewidgetitem96->setText(QApplication::translate("sControlSSC", "ADC5", nullptr));
        QTableWidgetItem *___qtablewidgetitem97 = TABLE_ADC1->horizontalHeaderItem(5);
        ___qtablewidgetitem97->setText(QApplication::translate("sControlSSC", "ADC6", nullptr));
        QTableWidgetItem *___qtablewidgetitem98 = TABLE_ADC1->horizontalHeaderItem(6);
        ___qtablewidgetitem98->setText(QApplication::translate("sControlSSC", "ADC7", nullptr));
        QTableWidgetItem *___qtablewidgetitem99 = TABLE_ADC1->horizontalHeaderItem(7);
        ___qtablewidgetitem99->setText(QApplication::translate("sControlSSC", "ADC8", nullptr));
        QTableWidgetItem *___qtablewidgetitem100 = TABLE_ADC1->verticalHeaderItem(0);
        ___qtablewidgetitem100->setText(QApplication::translate("sControlSSC", "Original", nullptr));
        QTableWidgetItem *___qtablewidgetitem101 = TABLE_ADC1->verticalHeaderItem(1);
        ___qtablewidgetitem101->setText(QApplication::translate("sControlSSC", "JavaScript", nullptr));
        QTableWidgetItem *___qtablewidgetitem102 = TABLE_ADC1->verticalHeaderItem(2);
        ___qtablewidgetitem102->setText(QApplication::translate("sControlSSC", "Value", nullptr));

        const bool __sortingEnabled4 = TABLE_ADC1->isSortingEnabled();
        TABLE_ADC1->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem103 = TABLE_ADC1->item(0, 0);
        ___qtablewidgetitem103->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem104 = TABLE_ADC1->item(0, 1);
        ___qtablewidgetitem104->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem105 = TABLE_ADC1->item(0, 2);
        ___qtablewidgetitem105->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem106 = TABLE_ADC1->item(0, 3);
        ___qtablewidgetitem106->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem107 = TABLE_ADC1->item(0, 4);
        ___qtablewidgetitem107->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem108 = TABLE_ADC1->item(0, 5);
        ___qtablewidgetitem108->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem109 = TABLE_ADC1->item(0, 6);
        ___qtablewidgetitem109->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem110 = TABLE_ADC1->item(0, 7);
        ___qtablewidgetitem110->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem111 = TABLE_ADC1->item(2, 0);
        ___qtablewidgetitem111->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem112 = TABLE_ADC1->item(2, 1);
        ___qtablewidgetitem112->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem113 = TABLE_ADC1->item(2, 2);
        ___qtablewidgetitem113->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem114 = TABLE_ADC1->item(2, 3);
        ___qtablewidgetitem114->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem115 = TABLE_ADC1->item(2, 4);
        ___qtablewidgetitem115->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem116 = TABLE_ADC1->item(2, 5);
        ___qtablewidgetitem116->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem117 = TABLE_ADC1->item(2, 6);
        ___qtablewidgetitem117->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem118 = TABLE_ADC1->item(2, 7);
        ___qtablewidgetitem118->setText(QApplication::translate("sControlSSC", "0", nullptr));
        TABLE_ADC1->setSortingEnabled(__sortingEnabled4);

        QTableWidgetItem *___qtablewidgetitem119 = TABLE_ADC2->horizontalHeaderItem(0);
        ___qtablewidgetitem119->setText(QApplication::translate("sControlSSC", "ADC9", nullptr));
        QTableWidgetItem *___qtablewidgetitem120 = TABLE_ADC2->horizontalHeaderItem(1);
        ___qtablewidgetitem120->setText(QApplication::translate("sControlSSC", "ADC10", nullptr));
        QTableWidgetItem *___qtablewidgetitem121 = TABLE_ADC2->horizontalHeaderItem(2);
        ___qtablewidgetitem121->setText(QApplication::translate("sControlSSC", "ADC11", nullptr));
        QTableWidgetItem *___qtablewidgetitem122 = TABLE_ADC2->horizontalHeaderItem(3);
        ___qtablewidgetitem122->setText(QApplication::translate("sControlSSC", "ADC12", nullptr));
        QTableWidgetItem *___qtablewidgetitem123 = TABLE_ADC2->horizontalHeaderItem(4);
        ___qtablewidgetitem123->setText(QApplication::translate("sControlSSC", "ADC13", nullptr));
        QTableWidgetItem *___qtablewidgetitem124 = TABLE_ADC2->horizontalHeaderItem(5);
        ___qtablewidgetitem124->setText(QApplication::translate("sControlSSC", "ADC14", nullptr));
        QTableWidgetItem *___qtablewidgetitem125 = TABLE_ADC2->horizontalHeaderItem(6);
        ___qtablewidgetitem125->setText(QApplication::translate("sControlSSC", "ADC15", nullptr));
        QTableWidgetItem *___qtablewidgetitem126 = TABLE_ADC2->horizontalHeaderItem(7);
        ___qtablewidgetitem126->setText(QApplication::translate("sControlSSC", "ADC16", nullptr));
        QTableWidgetItem *___qtablewidgetitem127 = TABLE_ADC2->verticalHeaderItem(0);
        ___qtablewidgetitem127->setText(QApplication::translate("sControlSSC", "Original", nullptr));
        QTableWidgetItem *___qtablewidgetitem128 = TABLE_ADC2->verticalHeaderItem(1);
        ___qtablewidgetitem128->setText(QApplication::translate("sControlSSC", "JavaScript", nullptr));
        QTableWidgetItem *___qtablewidgetitem129 = TABLE_ADC2->verticalHeaderItem(2);
        ___qtablewidgetitem129->setText(QApplication::translate("sControlSSC", "Value", nullptr));

        const bool __sortingEnabled5 = TABLE_ADC2->isSortingEnabled();
        TABLE_ADC2->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem130 = TABLE_ADC2->item(0, 0);
        ___qtablewidgetitem130->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem131 = TABLE_ADC2->item(0, 1);
        ___qtablewidgetitem131->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem132 = TABLE_ADC2->item(0, 2);
        ___qtablewidgetitem132->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem133 = TABLE_ADC2->item(0, 3);
        ___qtablewidgetitem133->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem134 = TABLE_ADC2->item(0, 4);
        ___qtablewidgetitem134->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem135 = TABLE_ADC2->item(0, 5);
        ___qtablewidgetitem135->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem136 = TABLE_ADC2->item(0, 6);
        ___qtablewidgetitem136->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem137 = TABLE_ADC2->item(0, 7);
        ___qtablewidgetitem137->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem138 = TABLE_ADC2->item(2, 0);
        ___qtablewidgetitem138->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem139 = TABLE_ADC2->item(2, 1);
        ___qtablewidgetitem139->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem140 = TABLE_ADC2->item(2, 2);
        ___qtablewidgetitem140->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem141 = TABLE_ADC2->item(2, 3);
        ___qtablewidgetitem141->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem142 = TABLE_ADC2->item(2, 4);
        ___qtablewidgetitem142->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem143 = TABLE_ADC2->item(2, 5);
        ___qtablewidgetitem143->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem144 = TABLE_ADC2->item(2, 6);
        ___qtablewidgetitem144->setText(QApplication::translate("sControlSSC", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem145 = TABLE_ADC2->item(2, 7);
        ___qtablewidgetitem145->setText(QApplication::translate("sControlSSC", "0", nullptr));
        TABLE_ADC2->setSortingEnabled(__sortingEnabled5);

        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("sControlSSC", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sControlSSC: public Ui_sControlSSC {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCONTROLSSC_H
