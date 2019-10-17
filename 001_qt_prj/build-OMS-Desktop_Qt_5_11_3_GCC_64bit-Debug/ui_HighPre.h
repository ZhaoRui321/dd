/********************************************************************************
** Form generated from reading UI file 'HighPre.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HIGHPRE_H
#define UI_HIGHPRE_H

#include <QSwitchButton.h>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HighPre
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QSwitchButton *allControl;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QSwitchButton *iconSource;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QSwitchButton *dynode;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QSwitchButton *increase;

    void setupUi(QWidget *HighPre)
    {
        if (HighPre->objectName().isEmpty())
            HighPre->setObjectName(QStringLiteral("HighPre"));
        HighPre->resize(200, 300);
        verticalLayout = new QVBoxLayout(HighPre);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(HighPre);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(0, 40));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        line = new QFrame(HighPre);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(HighPre);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setMinimumSize(QSize(60, 0));
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_2);

        allControl = new QSwitchButton(HighPre);
        allControl->setObjectName(QStringLiteral("allControl"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(allControl->sizePolicy().hasHeightForWidth());
        allControl->setSizePolicy(sizePolicy2);
        allControl->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(allControl);


        verticalLayout->addLayout(horizontalLayout);

        line_2 = new QFrame(HighPre);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_4 = new QLabel(HighPre);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);
        label_4->setMinimumSize(QSize(60, 0));
        label_4->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_4);

        iconSource = new QSwitchButton(HighPre);
        iconSource->setObjectName(QStringLiteral("iconSource"));
        sizePolicy2.setHeightForWidth(iconSource->sizePolicy().hasHeightForWidth());
        iconSource->setSizePolicy(sizePolicy2);
        iconSource->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(iconSource);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_5 = new QLabel(HighPre);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);
        label_5->setMinimumSize(QSize(60, 0));
        label_5->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_5);

        dynode = new QSwitchButton(HighPre);
        dynode->setObjectName(QStringLiteral("dynode"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(dynode->sizePolicy().hasHeightForWidth());
        dynode->setSizePolicy(sizePolicy3);
        dynode->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(dynode);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_6 = new QLabel(HighPre);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);
        label_6->setMinimumSize(QSize(60, 0));
        label_6->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_6);

        increase = new QSwitchButton(HighPre);
        increase->setObjectName(QStringLiteral("increase"));
        sizePolicy2.setHeightForWidth(increase->sizePolicy().hasHeightForWidth());
        increase->setSizePolicy(sizePolicy2);
        increase->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(increase);


        verticalLayout->addLayout(horizontalLayout_4);


        retranslateUi(HighPre);

        QMetaObject::connectSlotsByName(HighPre);
    } // setupUi

    void retranslateUi(QWidget *HighPre)
    {
        HighPre->setWindowTitle(QApplication::translate("HighPre", "Form", nullptr));
        label->setText(QApplication::translate("HighPre", "\345\274\200\345\220\257/\345\205\263\351\227\255", nullptr));
        label_2->setText(QApplication::translate("HighPre", "\345\205\250  \351\203\250", nullptr));
        allControl->setText(QString());
        label_4->setText(QApplication::translate("HighPre", "\347\246\273\345\255\220\346\272\220", nullptr));
        iconSource->setText(QString());
        label_5->setText(QApplication::translate("HighPre", "\346\211\223\346\213\277\346\236\201", nullptr));
        dynode->setText(QString());
        label_6->setText(QApplication::translate("HighPre", "\345\200\215\345\242\236\345\231\250", nullptr));
        increase->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class HighPre: public Ui_HighPre {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HIGHPRE_H
