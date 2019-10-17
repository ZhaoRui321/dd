/********************************************************************************
** Form generated from reading UI file 'sTICList.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STICLIST_H
#define UI_STICLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sTICList
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBox;
    QLabel *label;
    QLabel *label_2;
    QListWidget *listWidget;
    QLineEdit *lineEdit;
    QPushButton *BtnAdd;

    void setupUi(QWidget *sTICList)
    {
        if (sTICList->objectName().isEmpty())
            sTICList->setObjectName(QStringLiteral("sTICList"));
        sTICList->resize(168, 373);
        sTICList->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout = new QVBoxLayout(sTICList);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(2, 2, 2, 2);
        checkBox = new QCheckBox(sTICList);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(checkBox->sizePolicy().hasHeightForWidth());
        checkBox->setSizePolicy(sizePolicy);
        checkBox->setMinimumSize(QSize(25, 25));
        checkBox->setIconSize(QSize(25, 25));

        horizontalLayout_2->addWidget(checkBox);

        label = new QLabel(sTICList);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(15);
        label->setFont(font);

        horizontalLayout_2->addWidget(label);

        label_2 = new QLabel(sTICList);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_2);


        verticalLayout->addLayout(horizontalLayout_2);

        listWidget = new QListWidget(sTICList);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setAutoFillBackground(false);
        listWidget->setStyleSheet(QStringLiteral("background-color:transparent"));
        listWidget->setFrameShape(QFrame::NoFrame);

        verticalLayout->addWidget(listWidget);

        lineEdit = new QLineEdit(sTICList);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 40));
        lineEdit->setFont(font);

        verticalLayout->addWidget(lineEdit);

        BtnAdd = new QPushButton(sTICList);
        BtnAdd->setObjectName(QStringLiteral("BtnAdd"));
        BtnAdd->setMinimumSize(QSize(0, 40));
        BtnAdd->setFont(font);

        verticalLayout->addWidget(BtnAdd);


        retranslateUi(sTICList);

        QMetaObject::connectSlotsByName(sTICList);
    } // setupUi

    void retranslateUi(QWidget *sTICList)
    {
        sTICList->setWindowTitle(QApplication::translate("sTICList", "sTICList", nullptr));
        checkBox->setText(QString());
        label->setText(QApplication::translate("sTICList", "\350\264\250\351\207\217\346\225\260", nullptr));
        label_2->setText(QApplication::translate("sTICList", "\345\210\240\351\231\244", nullptr));
        BtnAdd->setText(QApplication::translate("sTICList", "Add", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sTICList: public Ui_sTICList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STICLIST_H
