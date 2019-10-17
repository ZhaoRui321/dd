#include "ControlDemo.h"
#include "ui_ControlDemo.h"
#include <QPainter>

ControlDemo::ControlDemo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlDemo)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground);
    //this->setWindowFlags(Qt::FramelessWindowHint);
    ui->lineEdit->setStyleSheet("background-color: transparent;");
//                                "border-top: 2px solid white;"
//                                "border-bottom: 2px solid white;");

    ui->switchBtn->SetSize(220,80);
    setState(false);
    connect(ui->switchBtn,SIGNAL(clicked()),this,SLOT(on_clicked()));
    connect(ui->lineEdit,SIGNAL(textChanged(QString)),this,SLOT(on_LineEditChanged(QString)));


}

ControlDemo::~ControlDemo()
{
    delete ui;
}

void ControlDemo::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); //反锯齿
    //painter.setBrush(QBrush(Qt::white));
    painter.setPen(Qt::white);
    QRect rect = this->rect();
    rect.setWidth(rect.width()-1);
    rect.setHeight(rect.height()-1);
    painter.drawRoundedRect(rect,30,30);

    QWidget::paintEvent(e);
}

void ControlDemo::setTitle(QString str)
{
    ui->label->setText(str);
}

void ControlDemo::setDescription(QString str)
{
    ui->descriptLaber->setText(str);
}

void ControlDemo::setLineEdit(QString num)
{
    ui->lineEdit->setText(num);
}

void ControlDemo::on_clicked()
{
    emit stateChange();
}

int ControlDemo::getState()
{
    if(ui->switchBtn->IsSelected())
        return 1;
    else
        return 0;
}

void ControlDemo::setState(bool state)
{
    ui->switchBtn->SetSelected(state);
}

void ControlDemo::setEnabled(bool state)
{
    ui->switchBtn->SetEnabel(state);
}

void ControlDemo::on_LineEditChanged(QString text)
{
    if(text.toDouble() < rangeInput[0])
        ui->lineEdit->setText(QString::number(rangeInput[0]));
    if(text.toDouble() > rangeInput[1])
        ui->lineEdit->setText(QString::number(rangeInput[1]));

    ui->switchBtn->SetSelected(false);
}

QString ControlDemo::getValue()
{
    return ui->lineEdit->text();
}
