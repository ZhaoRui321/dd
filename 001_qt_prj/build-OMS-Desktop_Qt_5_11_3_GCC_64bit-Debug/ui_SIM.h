/********************************************************************************
** Form generated from reading UI file 'SIM.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIM_H
#define UI_SIM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SIM
{
public:
    QFrame *btnControl;
    QVBoxLayout *verticalLayout;
    QPushButton *addBtn;
    QPushButton *deleteBtn;

    void setupUi(QWidget *SIM)
    {
        if (SIM->objectName().isEmpty())
            SIM->setObjectName(QStringLiteral("SIM"));
        SIM->resize(1000, 650);
        SIM->setMinimumSize(QSize(0, 0));
        SIM->setMaximumSize(QSize(16777215, 950));
        SIM->setFocusPolicy(Qt::ClickFocus);
        btnControl = new QFrame(SIM);
        btnControl->setObjectName(QStringLiteral("btnControl"));
        btnControl->setGeometry(QRect(30, 150, 39, 118));
        btnControl->setStyleSheet(QLatin1String("border: 1px solid black;\n"
"border-radius: 30px;"));
        btnControl->setFrameShape(QFrame::StyledPanel);
        btnControl->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(btnControl);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        addBtn = new QPushButton(btnControl);
        addBtn->setObjectName(QStringLiteral("addBtn"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(addBtn->sizePolicy().hasHeightForWidth());
        addBtn->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(50);
        addBtn->setFont(font);
        addBtn->setStyleSheet(QStringLiteral("border: 0px;"));

        verticalLayout->addWidget(addBtn);

        deleteBtn = new QPushButton(btnControl);
        deleteBtn->setObjectName(QStringLiteral("deleteBtn"));
        sizePolicy.setHeightForWidth(deleteBtn->sizePolicy().hasHeightForWidth());
        deleteBtn->setSizePolicy(sizePolicy);
        deleteBtn->setFont(font);
        deleteBtn->setStyleSheet(QStringLiteral("border: 0;"));

        verticalLayout->addWidget(deleteBtn);


        retranslateUi(SIM);

        QMetaObject::connectSlotsByName(SIM);
    } // setupUi

    void retranslateUi(QWidget *SIM)
    {
        SIM->setWindowTitle(QApplication::translate("SIM", "Form", nullptr));
        addBtn->setText(QApplication::translate("SIM", "+", nullptr));
        deleteBtn->setText(QApplication::translate("SIM", "-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SIM: public Ui_SIM {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIM_H
