#include "massinput.h"
#include "ui_massinput.h"
#include <QPainter>

MassInput::MassInput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MassInput)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint);
}

MassInput::~MassInput()
{
    delete ui;
}

double MassInput::getMassNum()
{
    if(ui->lineEdit->text().isEmpty())
        return 0;
    double num = ui->lineEdit->text().toDouble();
    return num;

}


void MassInput::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); //反锯齿
    painter.setBrush(QBrush(Qt::white));
    painter.setPen(Qt::transparent);
    QRect rect = this->rect();
    rect.setWidth(rect.width()-1);
    rect.setHeight(rect.height()-1);
    painter.drawRoundedRect(rect,30,30);

    QWidget::paintEvent(e);

}

void MassInput::mousePressEvent(QMouseEvent* e)
{
    if(this->rect().contains(e->pos())){
        ui->lineEdit->setFocus(Qt::MouseFocusReason);
        ui->lineEdit->selectAll();
    }
}
