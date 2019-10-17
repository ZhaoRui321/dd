#include "SIM.h"
#include "ui_SIM.h"
#include <QLabel>
#include <QDebug>
#include <QPainter>
#include <QRect>
#include <QDesktopWidget>

SIM::SIM(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SIM)
{
    ui->setupUi(this);
    QRect deskRect = QApplication::desktop()->availableGeometry();
    widgetHeight = (deskRect.height()-borderWidth*2-widgetToWidget*2-400)/3;
    widgetWidth = (deskRect.width()-borderWidth*2-widgetToWidget*2-600)/3;
    qDebug() << this->width() << this->height();

    ui->btnControl->resize(widgetWidth-2,widgetHeight-5);
    ui->btnControl->move(borderWidth,borderWidth);
}

SIM::~SIM()
{
    delete ui;
}

QList<double> SIM::getMassList()
{
    massCount = 0;
    m_MassNumList.clear();

    int count = m_MassInputList.count();
    for(int i = 0; i < count; i++){
        MassInput* temp = m_MassInputList.at(i);
        double massNum = temp->getMassNum();
        if(massNum != 0){
            m_MassNumList.append(massNum);
            massCount ++;
        }
    }
    return m_MassNumList;
}

void SIM::setPosition()
{
    int number = m_MassInputList.count()+1;
    int x = number / 3;
    int y = number % 3;

    int posx = borderWidth+(widgetWidth+widgetToWidget)*y;
    int posy = borderWidth+(widgetHeight+widgetToWidget)*x;

    MassInput* massInput = new MassInput(this);
    massInput->resize(widgetWidth,widgetHeight);
    massInput->move(posx,posy);
    massInput->show();

    m_MassInputList.append(massInput);
}


void SIM::on_addBtn_clicked()
{
    if(m_MassInputList.count()  == 8){
        return;
    }
    setPosition();
}

void SIM::on_deleteBtn_clicked()
{
    if(m_MassInputList.count() == 0){
        return;
    }
    MassInput* massInput = m_MassInputList.at(m_MassInputList.count()-1);
    m_MassInputList.removeAt(m_MassInputList.count()-1);
    delete(massInput);
}
