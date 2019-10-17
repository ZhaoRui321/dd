/********************************************************************************
** Form generated from reading UI file 'sFileWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SFILEWIDGET_H
#define UI_SFILEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sFileWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *E_FILENAME;
    QPushButton *PB_OK;
    QPushButton *PB_CANCEL;

    void setupUi(QWidget *sFileWidget)
    {
        if (sFileWidget->objectName().isEmpty())
            sFileWidget->setObjectName(QStringLiteral("sFileWidget"));
        sFileWidget->resize(600, 402);
        verticalLayout = new QVBoxLayout(sFileWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(sFileWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        label->setFont(font);

        horizontalLayout_2->addWidget(label);

        lineEdit = new QLineEdit(sFileWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setFont(font);

        horizontalLayout_2->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        tableWidget = new QTableWidget(sFileWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        QFont font1;
        font1.setPointSize(12);
        tableWidget->setFont(font1);

        verticalLayout->addWidget(tableWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        E_FILENAME = new QLineEdit(sFileWidget);
        E_FILENAME->setObjectName(QStringLiteral("E_FILENAME"));
        E_FILENAME->setMinimumSize(QSize(0, 40));
        E_FILENAME->setMaximumSize(QSize(16777215, 40));
        QPalette palette;
        QBrush brush(QColor(228, 218, 208, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        QBrush brush1(QColor(240, 240, 240, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        E_FILENAME->setPalette(palette);
        QFont font2;
        font2.setFamily(QStringLiteral("Microsoft YaHei UI"));
        font2.setPointSize(12);
        font2.setBold(false);
        font2.setWeight(50);
        E_FILENAME->setFont(font2);
        E_FILENAME->setAutoFillBackground(true);
        E_FILENAME->setReadOnly(true);

        horizontalLayout->addWidget(E_FILENAME);

        PB_OK = new QPushButton(sFileWidget);
        PB_OK->setObjectName(QStringLiteral("PB_OK"));
        PB_OK->setMinimumSize(QSize(75, 44));
        PB_OK->setMaximumSize(QSize(16777215, 44));
        QFont font3;
        font3.setFamily(QStringLiteral("Microsoft YaHei UI"));
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setWeight(75);
        PB_OK->setFont(font3);
        PB_OK->setStyleSheet(QLatin1String("background-color: #3c3c3c;\n"
"color:#E4DAD0;\n"
"border-style: outset;\n"
"border-width:2px;\n"
"border-radius:10px;\n"
"border-color:#E4DAD0;"));

        horizontalLayout->addWidget(PB_OK);

        PB_CANCEL = new QPushButton(sFileWidget);
        PB_CANCEL->setObjectName(QStringLiteral("PB_CANCEL"));
        PB_CANCEL->setMinimumSize(QSize(75, 44));
        PB_CANCEL->setMaximumSize(QSize(16777215, 44));
        PB_CANCEL->setFont(font3);
        PB_CANCEL->setStyleSheet(QLatin1String("background-color: #3c3c3c;\n"
"color:#E4DAD0;\n"
"border-style: outset;\n"
"border-width:2px;\n"
"border-radius:10px;\n"
"border-color:#E4DAD0;"));

        horizontalLayout->addWidget(PB_CANCEL);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(sFileWidget);

        QMetaObject::connectSlotsByName(sFileWidget);
    } // setupUi

    void retranslateUi(QWidget *sFileWidget)
    {
        sFileWidget->setWindowTitle(QApplication::translate("sFileWidget", "Form", nullptr));
        label->setText(QApplication::translate("sFileWidget", "FrameCount:", nullptr));
        lineEdit->setInputMask(QString());
        lineEdit->setText(QApplication::translate("sFileWidget", "1", nullptr));
        PB_OK->setText(QApplication::translate("sFileWidget", "OK", nullptr));
        PB_CANCEL->setText(QApplication::translate("sFileWidget", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sFileWidget: public Ui_sFileWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SFILEWIDGET_H
