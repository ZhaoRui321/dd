/********************************************************************************
** Form generated from reading UI file 'sFileDir.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SFILEDIR_H
#define UI_SFILEDIR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sFileDir
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;

    void setupUi(QWidget *sFileDir)
    {
        if (sFileDir->objectName().isEmpty())
            sFileDir->setObjectName(QStringLiteral("sFileDir"));
        sFileDir->resize(400, 300);
        verticalLayout = new QVBoxLayout(sFileDir);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableWidget = new QTableWidget(sFileDir);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        QFont font;
        font.setPointSize(12);
        tableWidget->setFont(font);

        verticalLayout->addWidget(tableWidget);


        retranslateUi(sFileDir);

        QMetaObject::connectSlotsByName(sFileDir);
    } // setupUi

    void retranslateUi(QWidget *sFileDir)
    {
        sFileDir->setWindowTitle(QApplication::translate("sFileDir", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sFileDir: public Ui_sFileDir {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SFILEDIR_H
