#include "sSystemState.h"
#include "ui_sSystemState.h"
#include "cPumpControl.h"

sSystemState::sSystemState(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sSystemState)
{
    ui->setupUi(this);
}

sSystemState::~sSystemState()
{
    delete ui;
}

void sSystemState::showDrive(QByteArray& pArray)
{
    uint* pStateRequest= (uint*)(pArray.data());
    if ((*pStateRequest==0xfffff001)&&(*(pStateRequest+1)==0x00000000)){
        //State_Show=_T("板卡工作正常\r\n");
        switch(*(pStateRequest+2)&0x0000ffff){
        case 0x00000000:
            ui->label_6->setText("正在扫描");
            ui->label_8->setText("采谱停止");
            break;
        case 0x00000001:
            ui->label_6->setText("扫描停止");
            ui->label_8->setText("采谱停止");
            break;
        case 0x00000002:
            ui->label_6->setText("正在扫描");
            ui->label_8->setText("正在采谱");
            break;
        case 0x00000003:
            ui->label_6->setText("扫描停止");
            ui->label_8->setText("正在采谱");
            break;
        }
    }
    cPumpControl::_STATE_REQUEST tmpSTATE_REQUEST;
    if(cPumpControl::getDrive(pArray, tmpSTATE_REQUEST)){
        ui->L_AD0->setText(QString::number(pow(10, -tmpSTATE_REQUEST.adcValue[0]- 3.5)));
        ui->L_AD1->setText(QString::number(-tmpSTATE_REQUEST.adcValue[1]));
        ui->L_AD2->setText(QString::number(-tmpSTATE_REQUEST.adcValue[2]));
        ui->L_AD3->setText(QString::number(pow(10, -tmpSTATE_REQUEST.adcValue[3]- 3.5)));
        ui->label_3->setText(QString::number(tmpSTATE_REQUEST.driveCurrent));
    }
}

void sSystemState::showRotatinSpeed(QByteArray& pArray)
{
    cPumpControl::_STATE_REQUEST tmpSTATE_REQUEST;
    if(cPumpControl::getRotatinSpeed(pArray, tmpSTATE_REQUEST)){
        ui->L_AD0->setText(QString::number(pow(10, -tmpSTATE_REQUEST.adcValue[0]- 3.5)));
        ui->L_AD1->setText(QString::number(-tmpSTATE_REQUEST.adcValue[1]));
        ui->L_AD2->setText(QString::number(-tmpSTATE_REQUEST.adcValue[2]));
        ui->L_AD3->setText(QString::number(pow(10, -tmpSTATE_REQUEST.adcValue[3]- 3.5)));
        ui->label_4->setText(QString::number(tmpSTATE_REQUEST.rotatinSpeed));
    }
}
