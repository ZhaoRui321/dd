#include "AllScan.h"
#include "ui_AllScan.h"
#include "DoubleSlider.h"
#include <QPen>
#include <QPainter>
#include <QDebug>

AllScan::AllScan(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AllScan)
{
    ui->setupUi(this);
    doubleSlider = new DoubleSlider(2,0,150,10);
    ui->doubleSliderLayout->addWidget(doubleSlider);
    oneSlider = new OneSlider(1,0,50,100);
    ui->oneSliderLayout->addWidget(oneSlider);

//    doubleSlider->setRange(0,150);
//    oneSlider->setRange(0,50);
//    oneSlider->setHandleNum(1);
//    oneSlider->setSingleStep(100);
    //未选中状态
    style1 = "QPushButton{background-color:gray;\
            color: white;   border-radius: 10px;\
            border-style: inset; font-size: 30px;}"
          "QPushButton:pressed{background-color:rgb(85, 170, 255);\
                           border-style: inset; }";

    //选中状态
    style2 = "QPushButton{background-color:white;font-size: 40px;\
                                   color: black;   border-radius: 10px;\
                                   border-style: outset;}"
                                 "QPushButton:pressed{background-color:rgb(85, 170, 255);\
                                                  border-style: inset; }";

    ui->bigModelBtn->setStyleSheet(style1);
    ui->smallModelBtn->setStyleSheet(style1);
    ui->userModelBtn->setStyleSheet(style2);
    normalModel();

    connect(doubleSlider,SIGNAL(minValueChanged(float)),this,SLOT(on_minValueChanged(float)));
    connect(doubleSlider,SIGNAL(maxValueChanged(float)),this,SLOT(on_MaxValueChanged(float)));
    connect(oneSlider,SIGNAL(minValueChanged(float)),this,SLOT(onSpeedValueChange(float)));

}

AllScan::~AllScan()
{
    delete ui;
}

//void AllScan::paintEvent(QPaintEvent *)
//{
//    QPainter p(this);
//    QPen pen = QPen("white");
//    pen.setWidth(6);
//    QPoint pos = ui->btnWidget->pos();
//    QPoint p1 = QPoint(pos.x(),pos.y()+400);
//    QPoint p2 = QPoint(p1.x()+ui->btnWidget->width(),p1.y());
//    p.setPen(pen);
//    p.drawLine(p1,p2);
//}

void AllScan::on_minValueChanged(float num)
{
    startMass = num;
    qDebug() << "******************" << startMass;
}

void AllScan::on_MaxValueChanged(float num)
{
    endMass = num;
    qDebug() << "******************" << endMass;
}
void AllScan::onSpeedValueChange(float num)
{
    speed = num;
    qDebug() << "******************" << speed;
}

double AllScan::getStartMass()
{
    return doubleSlider->startMass();
}

double AllScan::getEndMass()
{
    return doubleSlider->endMass();
}

double AllScan::getSpeed()
{
    return oneSlider->startMass();
}

void AllScan::bigMassModel()
{
    doubleSlider->setMinValue(bigMethod[0]);
    doubleSlider->setMaxValue(bigMethod[1]);
    oneSlider->setMaxValue(bigMethod[2]);
}

void AllScan::smallMassModel()
{
    doubleSlider->setMinValue(smallMethod[0]);
    doubleSlider->setMaxValue(smallMethod[1]);
    oneSlider->setMaxValue(smallMethod[2]);
}

void AllScan::normalModel()
{
    doubleSlider->setMinValue(normalMethod[0]);
    doubleSlider->setMaxValue(normalMethod[1]);
    oneSlider->setMaxValue(normalMethod[2]);
}



void AllScan::on_bigModelBtn_clicked()
{
    ui->bigModelBtn->setStyleSheet(style2);
    ui->smallModelBtn->setStyleSheet(style1);
    ui->userModelBtn->setStyleSheet(style1);
    doubleSlider->setReadOnly(false);
    oneSlider->setReadOnly(false);
    bigMassModel();
    doubleSlider->setReadOnly(true);
    oneSlider->setReadOnly(true);
}

void AllScan::on_smallModelBtn_clicked()
{
    ui->bigModelBtn->setStyleSheet(style1);
    ui->smallModelBtn->setStyleSheet(style2);
    ui->userModelBtn->setStyleSheet(style1);
    doubleSlider->setReadOnly(false);
    oneSlider->setReadOnly(false);
    smallMassModel();
    doubleSlider->setReadOnly(true);
    oneSlider->setReadOnly(true);
}

void AllScan::on_userModelBtn_clicked()
{
    doubleSlider->setReadOnly(false);
    oneSlider->setReadOnly(false);
    normalModel();
    ui->bigModelBtn->setStyleSheet(style1);
    ui->smallModelBtn->setStyleSheet(style1);
    ui->userModelBtn->setStyleSheet(style2);
}
