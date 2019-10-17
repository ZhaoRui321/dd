/********************************************************************************
** Form generated from reading UI file 'sDataAcquisiton.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SDATAACQUISITON_H
#define UI_SDATAACQUISITON_H

#include <LibWidget/ListWidget/sTICList.h>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sDataAcquisiton
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QWidget *UI_W_TIC;
    QVBoxLayout *UI_LAYOUT_TIC;
    QWidget *UI_W_PROCESS;
    QHBoxLayout *UI_LAYOUT_PROCESS;
    QPushButton *btnSlide;
    QWidget *RightWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *TIC_Value;
    sTICList *TICList;
    QFrame *line;
    QPushButton *UI_PB_ORIGINAL;
    QPushButton *UI_PB_PROCESS;
    QFrame *line_2;
    QWidget *rangeWidget_2;
    QVBoxLayout *rangeWidget;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *UI_LE_X1;
    QLineEdit *UI_LE_X2;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *UI_LE_Y1;
    QLineEdit *UI_LE_Y2;
    QPushButton *btnRange;
    QPushButton *btnSaveFrame;
    QWidget *widget;

    void setupUi(QWidget *sDataAcquisiton)
    {
        if (sDataAcquisiton->objectName().isEmpty())
            sDataAcquisiton->setObjectName(QStringLiteral("sDataAcquisiton"));
        sDataAcquisiton->resize(1140, 693);
        horizontalLayout = new QHBoxLayout(sDataAcquisiton);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, 0, -1);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        UI_W_TIC = new QWidget(sDataAcquisiton);
        UI_W_TIC->setObjectName(QStringLiteral("UI_W_TIC"));
        UI_W_TIC->setMaximumSize(QSize(16777215, 16777215));
        UI_LAYOUT_TIC = new QVBoxLayout(UI_W_TIC);
        UI_LAYOUT_TIC->setObjectName(QStringLiteral("UI_LAYOUT_TIC"));

        verticalLayout->addWidget(UI_W_TIC);

        UI_W_PROCESS = new QWidget(sDataAcquisiton);
        UI_W_PROCESS->setObjectName(QStringLiteral("UI_W_PROCESS"));
        UI_LAYOUT_PROCESS = new QHBoxLayout(UI_W_PROCESS);
        UI_LAYOUT_PROCESS->setObjectName(QStringLiteral("UI_LAYOUT_PROCESS"));

        verticalLayout->addWidget(UI_W_PROCESS);


        horizontalLayout->addLayout(verticalLayout);

        btnSlide = new QPushButton(sDataAcquisiton);
        btnSlide->setObjectName(QStringLiteral("btnSlide"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnSlide->sizePolicy().hasHeightForWidth());
        btnSlide->setSizePolicy(sizePolicy);
        btnSlide->setMinimumSize(QSize(50, 0));
        btnSlide->setMaximumSize(QSize(16777215, 16777215));
        btnSlide->setStyleSheet(QStringLiteral("border-image: url(:/picture/Icon_Left.jpg);"));

        horizontalLayout->addWidget(btnSlide);

        RightWidget = new QWidget(sDataAcquisiton);
        RightWidget->setObjectName(QStringLiteral("RightWidget"));
        RightWidget->setMaximumSize(QSize(400, 16777215));
        verticalLayout_2 = new QVBoxLayout(RightWidget);
        verticalLayout_2->setSpacing(20);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 20);
        TIC_Value = new QLabel(RightWidget);
        TIC_Value->setObjectName(QStringLiteral("TIC_Value"));

        verticalLayout_2->addWidget(TIC_Value);

        TICList = new sTICList(RightWidget);
        TICList->setObjectName(QStringLiteral("TICList"));

        verticalLayout_2->addWidget(TICList);

        line = new QFrame(RightWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        UI_PB_ORIGINAL = new QPushButton(RightWidget);
        UI_PB_ORIGINAL->setObjectName(QStringLiteral("UI_PB_ORIGINAL"));
        UI_PB_ORIGINAL->setMinimumSize(QSize(0, 40));
        QFont font;
        font.setPointSize(12);
        UI_PB_ORIGINAL->setFont(font);

        verticalLayout_2->addWidget(UI_PB_ORIGINAL);

        UI_PB_PROCESS = new QPushButton(RightWidget);
        UI_PB_PROCESS->setObjectName(QStringLiteral("UI_PB_PROCESS"));
        UI_PB_PROCESS->setMinimumSize(QSize(0, 40));
        UI_PB_PROCESS->setFont(font);

        verticalLayout_2->addWidget(UI_PB_PROCESS);

        line_2 = new QFrame(RightWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);

        rangeWidget_2 = new QWidget(RightWidget);
        rangeWidget_2->setObjectName(QStringLiteral("rangeWidget_2"));
        rangeWidget = new QVBoxLayout(rangeWidget_2);
        rangeWidget->setSpacing(6);
        rangeWidget->setObjectName(QStringLiteral("rangeWidget"));
        rangeWidget->setContentsMargins(-1, 10, -1, 10);
        label = new QLabel(rangeWidget_2);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        rangeWidget->addWidget(label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        UI_LE_X1 = new QLineEdit(rangeWidget_2);
        UI_LE_X1->setObjectName(QStringLiteral("UI_LE_X1"));
        UI_LE_X1->setMinimumSize(QSize(0, 60));
        QFont font1;
        font1.setPointSize(15);
        UI_LE_X1->setFont(font1);
        UI_LE_X1->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(UI_LE_X1);

        UI_LE_X2 = new QLineEdit(rangeWidget_2);
        UI_LE_X2->setObjectName(QStringLiteral("UI_LE_X2"));
        UI_LE_X2->setMinimumSize(QSize(0, 60));
        UI_LE_X2->setFont(font1);
        UI_LE_X2->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(UI_LE_X2);


        rangeWidget->addLayout(horizontalLayout_2);

        label_2 = new QLabel(rangeWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);

        rangeWidget->addWidget(label_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        UI_LE_Y1 = new QLineEdit(rangeWidget_2);
        UI_LE_Y1->setObjectName(QStringLiteral("UI_LE_Y1"));
        UI_LE_Y1->setMinimumSize(QSize(0, 60));
        UI_LE_Y1->setFont(font1);
        UI_LE_Y1->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(UI_LE_Y1);

        UI_LE_Y2 = new QLineEdit(rangeWidget_2);
        UI_LE_Y2->setObjectName(QStringLiteral("UI_LE_Y2"));
        UI_LE_Y2->setMinimumSize(QSize(0, 60));
        UI_LE_Y2->setFont(font1);
        UI_LE_Y2->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(UI_LE_Y2);


        rangeWidget->addLayout(horizontalLayout_3);


        verticalLayout_2->addWidget(rangeWidget_2);

        btnRange = new QPushButton(RightWidget);
        btnRange->setObjectName(QStringLiteral("btnRange"));
        btnRange->setMinimumSize(QSize(0, 40));
        btnRange->setFont(font);

        verticalLayout_2->addWidget(btnRange);

        btnSaveFrame = new QPushButton(RightWidget);
        btnSaveFrame->setObjectName(QStringLiteral("btnSaveFrame"));
        btnSaveFrame->setMinimumSize(QSize(0, 40));
        btnSaveFrame->setFont(font);

        verticalLayout_2->addWidget(btnSaveFrame);

        widget = new QWidget(RightWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(400, 400));
        widget->setMaximumSize(QSize(400, 400));

        verticalLayout_2->addWidget(widget);


        horizontalLayout->addWidget(RightWidget);


        retranslateUi(sDataAcquisiton);

        QMetaObject::connectSlotsByName(sDataAcquisiton);
    } // setupUi

    void retranslateUi(QWidget *sDataAcquisiton)
    {
        sDataAcquisiton->setWindowTitle(QApplication::translate("sDataAcquisiton", "Form", nullptr));
        btnSlide->setText(QString());
        TIC_Value->setText(QString());
        UI_PB_ORIGINAL->setText(QApplication::translate("sDataAcquisiton", "\345\216\237\345\247\213\350\260\261", nullptr));
        UI_PB_PROCESS->setText(QApplication::translate("sDataAcquisiton", "\345\271\263\346\273\221\350\260\261", nullptr));
        label->setText(QApplication::translate("sDataAcquisiton", "X\345\235\220\346\240\207\350\214\203\345\233\264", nullptr));
        UI_LE_X1->setText(QApplication::translate("sDataAcquisiton", "auto", nullptr));
        UI_LE_X2->setText(QApplication::translate("sDataAcquisiton", "auto", nullptr));
        label_2->setText(QApplication::translate("sDataAcquisiton", "Y\345\235\220\346\240\207\350\214\203\345\233\264", nullptr));
        UI_LE_Y1->setText(QApplication::translate("sDataAcquisiton", "auto", nullptr));
        UI_LE_Y2->setText(QApplication::translate("sDataAcquisiton", "auto", nullptr));
        btnRange->setText(QApplication::translate("sDataAcquisiton", "\346\230\276\347\244\272\350\214\203\345\233\264", nullptr));
        btnSaveFrame->setText(QApplication::translate("sDataAcquisiton", "\350\260\261\345\233\276\346\210\252\345\233\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sDataAcquisiton: public Ui_sDataAcquisiton {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SDATAACQUISITON_H
