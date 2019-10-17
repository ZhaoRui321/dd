#include "SaveFile.h"
#include "ui_SaveFile.h"
#include <QDesktopWidget>

SaveFile::SaveFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SaveFile)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    QDesktopWidget *pDesk = QApplication::desktop();
    int x = pDesk->width() - ui->saveWidget->width();
    int y = pDesk->height() - ui->saveWidget->height();
    ui->saveWidget->move(x/2,y/3);
    ui->fileNameEdit->setProperty("number",true);
    ui->fileNameEdit->setPlaceholderText("FileName");
    ui->fileNameEdit->setStyleSheet("background-color: white; border-radius: 10px;");
    //未点击
    style1 = "QPushButton{border-radius: 60px;background-color: gray;font-size: 40px;";
    //点击
    style2 = "QPushButton{border-radius: 10px;background-color: white;font-size: 35px;} QPushButton:hover{color: blue;background-color: gray;font-size: 35px;}";

    ui->btnSave->setStyleSheet(style2);
    ui->btnCancel->setStyleSheet(style2);
}

SaveFile::~SaveFile()
{
    delete ui;
}

void SaveFile::on_btnCancel_clicked()
{
    ui->fileNameEdit->clear();
    ui->btnCancel->setStyleSheet(style1);
    this->hide();
}

void SaveFile::on_btnSave_clicked()
{
    emit saveInfo(ui->fileNameEdit->text());
    ui->fileNameEdit->clear();
    ui->btnSave->setStyleSheet(style1);
    this->hide();
}
