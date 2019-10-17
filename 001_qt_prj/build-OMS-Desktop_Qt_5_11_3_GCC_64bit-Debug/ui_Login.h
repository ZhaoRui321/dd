/********************************************************************************
** Form generated from reading UI file 'Login.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QWidget *loginWidget;
    QVBoxLayout *hor;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_2;
    QWidget *inputWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *CountEdit;
    QFrame *line;
    QLineEdit *passWord;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btnLogin;
    QPushButton *btnRes;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnSys;
    QWidget *stateLightWidget;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QStringLiteral("Login"));
        Login->resize(874, 772);
        Login->setFocusPolicy(Qt::ClickFocus);
        loginWidget = new QWidget(Login);
        loginWidget->setObjectName(QStringLiteral("loginWidget"));
        loginWidget->setGeometry(QRect(180, 20, 551, 741));
        hor = new QVBoxLayout(loginWidget);
        hor->setObjectName(QStringLiteral("hor"));
        label_3 = new QLabel(loginWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        hor->addWidget(label_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        inputWidget = new QWidget(loginWidget);
        inputWidget->setObjectName(QStringLiteral("inputWidget"));
        verticalLayout = new QVBoxLayout(inputWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(10, 10, 10, 10);
        CountEdit = new QLineEdit(inputWidget);
        CountEdit->setObjectName(QStringLiteral("CountEdit"));
        CountEdit->setMinimumSize(QSize(500, 100));
        QFont font;
        font.setPointSize(15);
        CountEdit->setFont(font);
        CountEdit->setFocusPolicy(Qt::StrongFocus);
        CountEdit->setFrame(false);

        verticalLayout->addWidget(CountEdit);

        line = new QFrame(inputWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setLineWidth(1);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        passWord = new QLineEdit(inputWidget);
        passWord->setObjectName(QStringLiteral("passWord"));
        passWord->setMinimumSize(QSize(500, 100));
        passWord->setFont(font);
        passWord->setFocusPolicy(Qt::StrongFocus);
        passWord->setFrame(false);

        verticalLayout->addWidget(passWord);


        verticalLayout_2->addWidget(inputWidget);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(12, -1, 12, -1);
        btnLogin = new QPushButton(loginWidget);
        btnLogin->setObjectName(QStringLiteral("btnLogin"));
        btnLogin->setMinimumSize(QSize(0, 80));

        horizontalLayout_4->addWidget(btnLogin);

        btnRes = new QPushButton(loginWidget);
        btnRes->setObjectName(QStringLiteral("btnRes"));
        btnRes->setMinimumSize(QSize(0, 80));

        horizontalLayout_4->addWidget(btnRes);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, 200, -1, -1);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        btnSys = new QPushButton(loginWidget);
        btnSys->setObjectName(QStringLiteral("btnSys"));
        btnSys->setMinimumSize(QSize(150, 150));
        btnSys->setMaximumSize(QSize(150, 150));

        horizontalLayout_5->addWidget(btnSys);

        stateLightWidget = new QWidget(loginWidget);
        stateLightWidget->setObjectName(QStringLiteral("stateLightWidget"));
        stateLightWidget->setMinimumSize(QSize(175, 0));

        horizontalLayout_5->addWidget(stateLightWidget);


        verticalLayout_2->addLayout(horizontalLayout_5);


        horizontalLayout->addLayout(verticalLayout_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        hor->addLayout(horizontalLayout);


        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "Form", nullptr));
        label_3->setText(QApplication::translate("Login", "OMS", nullptr));
        btnLogin->setText(QApplication::translate("Login", "\347\231\273\351\231\206", nullptr));
        btnRes->setText(QApplication::translate("Login", "\346\263\250\345\206\214", nullptr));
        btnSys->setText(QApplication::translate("Login", "\345\274\200\345\220\257\347\263\273\347\273\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
