/********************************************************************************
** Form generated from reading UI file 'SaveFile.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVEFILE_H
#define UI_SAVEFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SaveFile
{
public:
    QWidget *saveWidget;
    QGridLayout *gridLayout;
    QLineEdit *fileNameEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnSave;
    QPushButton *btnCancel;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *SaveFile)
    {
        if (SaveFile->objectName().isEmpty())
            SaveFile->setObjectName(QStringLiteral("SaveFile"));
        SaveFile->resize(728, 785);
        SaveFile->setFocusPolicy(Qt::ClickFocus);
        saveWidget = new QWidget(SaveFile);
        saveWidget->setObjectName(QStringLiteral("saveWidget"));
        saveWidget->setGeometry(QRect(10, 10, 661, 471));
        gridLayout = new QGridLayout(saveWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        fileNameEdit = new QLineEdit(saveWidget);
        fileNameEdit->setObjectName(QStringLiteral("fileNameEdit"));
        fileNameEdit->setMinimumSize(QSize(800, 150));
        fileNameEdit->setMaximumSize(QSize(800, 150));
        QFont font;
        font.setPointSize(50);
        fileNameEdit->setFont(font);
        fileNameEdit->setFrame(false);

        gridLayout->addWidget(fileNameEdit, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnSave = new QPushButton(saveWidget);
        btnSave->setObjectName(QStringLiteral("btnSave"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnSave->sizePolicy().hasHeightForWidth());
        btnSave->setSizePolicy(sizePolicy);
        btnSave->setMinimumSize(QSize(300, 100));
        btnSave->setMaximumSize(QSize(16777215, 40));
        QFont font1;
        font1.setPointSize(30);
        btnSave->setFont(font1);

        horizontalLayout->addWidget(btnSave);

        btnCancel = new QPushButton(saveWidget);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        sizePolicy.setHeightForWidth(btnCancel->sizePolicy().hasHeightForWidth());
        btnCancel->setSizePolicy(sizePolicy);
        btnCancel->setMinimumSize(QSize(300, 100));
        btnCancel->setMaximumSize(QSize(16777215, 40));
        btnCancel->setFont(font1);

        horizontalLayout->addWidget(btnCancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(SaveFile);

        QMetaObject::connectSlotsByName(SaveFile);
    } // setupUi

    void retranslateUi(QWidget *SaveFile)
    {
        SaveFile->setWindowTitle(QApplication::translate("SaveFile", "Form", nullptr));
        btnSave->setText(QApplication::translate("SaveFile", "\344\277\235\345\255\230", nullptr));
        btnCancel->setText(QApplication::translate("SaveFile", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SaveFile: public Ui_SaveFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVEFILE_H
