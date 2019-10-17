#include "Temperature.h"
#include "ui_Temperature.h"
#include <QColor>

Temperature::Temperature(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Temperature)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    SliderStyle = "  \
    QSlider\
    {\
        background-color: white;\
        min-width:5px;\
        max-width:5px;\
        border:15px solid white;\
    }\
     QSlider::add-page:vertical\
     {     \
        background-color: rgb(87, 97, 106);\
        width:8px;\
     }\
     QSlider::sub-page:vertical \
    {\
        background-color: #FFFF00;\
        width:8px;\
     }\
    QSlider::groove:vertical \
    {\
        background:transparent;\
        width:10px;\
    }\
    QSlider::handle:vertical \
    {\
        height: 20px;\
        width:20px;\
        border-image: url(:/picture/handle.jpg);\
        margin: -0 -4px; \
     }";
    ui->verticalSlider->setStyleSheet(SliderStyle);
    //ui->switchBtn->SetSliderColor(QColor("#FFFF00"),QColor("#7B797B"));
}

Temperature::~Temperature()
{
    delete ui;
}
