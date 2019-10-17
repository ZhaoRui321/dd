#include "FileListWidget.h"

FileListWidget::FileListWidget(QString path, QListWidget *parent):
    datapath(path+ "/data"),
    QListWidget(parent)

{
    setAutoFillBackground(true);
    setFileNameList();
//    QString filename;
//    for(int i = 0 ;i < fileNameList.count(); i++){
//        filename = fileNameList.at(i);
//        setItemStyle(filename);
//    }
}

FileListWidget::~FileListWidget()
{

}

void FileListWidget::setDatapath(QString path)
{
    fileNameList.clear();
    this->clear();
    datapath = path + "/data";
    setFileNameList();
    this->addItems(fileNameList);
}


void FileListWidget::setItemStyle(QString name)
{
    QListWidgetItem* Item = new QListWidgetItem(this);
    Item->setSizeHint(QSize(90, 120));
    QWidget *pContainer = new QWidget(this);
    QVBoxLayout *hLayout = new QVBoxLayout(pContainer);
    QVBoxLayout *hLeftLayout = new QVBoxLayout(pContainer);
    //QHBoxLayout *hRightLeftLayout = new QHBoxLayout(pContainer);
    //QHBoxLayout *hRightRightLayout = new QHBoxLayout(pContainer);
    QVBoxLayout *hRightLayout = new QVBoxLayout(pContainer);

    QLabel *pCaseName = new QLabel(name);
    pCaseName->setAlignment(Qt::AlignCenter);
    //pCaseName->font()
    //添加三个按钮，实现运行、停止运行、删除功能

    //QPushButton *pRunButton = new QPushButton(pContainer);
    //pRunButton->setStyleSheet("pro_check");
    //pRunButton->setIconSize(QSize(30,120));
    //pRunButton->setText("预览");
    //pRunButton->pressed();
    //pRunButton->setStyleSheet("QPushButton{border-image:url(:/images/images/runbutton.png)}");
//    QPushButton *pStopButton = new QPushButton(pContainer);
//    pStopButton->setStyleSheet("QPushButton{border-image:url(:/images/images/stopbutton.png)}");
    QPushButton *pDelButton = new QPushButton(pContainer);
    pDelButton->setStyleSheet("delete");
    pDelButton->setText("删除");
    pDelButton->setIconSize(QSize(30,120));
    //pDelButton->setStyleSheet("QPushButton{border-image:url(:/images/images/delbutton.png)}");

    //将各个空间添加到水平布局器中
    hLeftLayout->addWidget(pCaseName);
    //hRightRightLayout->addStretch(1);
    //hRightRightLayout->addWidget(pRunButton);
//    hRightRightLayout->addStretch(1);
//    hRightRightLayout->addWidget(pStopButton);
    //hRightRightLayout->addStretch(1);
    hRightLayout->addWidget(pDelButton);
    //hRightRightLayout->addStretch(1);

    //设置布局器的比例
    //hRightLayout->addLayout(hRightLeftLayout);
    //hRightLayout->addLayout(hRightRightLayout);
    //hRightLayout->setStretchFactor(hRightLeftLayout, 1);
    //hRightLayout->setStretchFactor(hRightRightLayout, 1);
    hLayout->addLayout(hLeftLayout);
    hLayout->addLayout(hRightLayout);
    //hLayout->setStretchFactor(hLeftLayout, 1);
    //hLayout->setStretchFactor(hRightLayout, 1);
    //hLayout->setContentsMargins(5,2,5,2);
    pContainer->setLayout(hLayout);

    this->setItemWidget(Item, pContainer);

}

void FileListWidget::removeFile(int currentRow)
{
    QString fileName = fileNameList[currentRow];
    QString path = datapath + fileName;
    QFile::remove(path);
}
