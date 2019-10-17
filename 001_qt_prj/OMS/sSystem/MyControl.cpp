#include "MyControl.h"
#include "ui_MyControl.h"
#include <QSettings>


MyControl::MyControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyControl)
{
    ui->setupUi(this);
    initWidget();
    connect(ui->dynodeWidget,SIGNAL(stateChange()),this,SLOT(onStateChange()));
    connect(ui->iconWidget,SIGNAL(stateChange()),this,SLOT(onStateChange()));
    connect(ui->increaseWidget,SIGNAL(stateChange()),this,SLOT(onStateChange()));
    connect(ui->tempterature,SIGNAL(stateChange()),this,SLOT(onStateChange()));

    connect(ui->dynodeWidget,SIGNAL(controlChanged()),this,SLOT(onControlChanged()));
    connect(ui->iconWidget,SIGNAL(controlChanged()),this,SLOT(onControlChanged()));
    connect(ui->increaseWidget,SIGNAL(controlChanged()),this,SLOT(onControlChanged()));
    connect(ui->tempterature,SIGNAL(controlChanged()),this,SLOT(onControlChanged()));

    qRegisterMetaType<sControlSSC::_CMD_SSC_SET>("sControlSSC::_CMD_SSC_SET");
    setAllEnabled(false);
}

MyControl::~MyControl()
{
    delete ui;
}


void MyControl::setState(bool state)
{
    if(state)
    {
        isMachPump = 1;
        isFpump = 1;
    }
    ui->dynodeWidget->setState(state);
    ui->iconWidget->setState(state);
    ui->increaseWidget->setState(state);
    ui->tempterature->setState(state);
    ui->ZSQWidgeht->setState(state);
    ui->DFWidget->setState(state);
    emit systemStateChange();
}

void MyControl::setAllEnabled(bool state)
{
    ui->dynodeWidget->setEnabled(state);
    ui->iconWidget->setEnabled(state);
    ui->increaseWidget->setEnabled(state);
    ui->tempterature->setEnabled(state);
    ui->ZSQWidgeht->setEnabled(state);
    ui->DFWidget->setEnabled(state);
}

void MyControl::initWidget()
{
    QString path;
    if(filePath.isEmpty())
        path = QApplication::applicationDirPath() + "/tuning.ini";
    else
        path = filePath + "/tuning.ini";

    QSettings configIniRead(path, QSettings::IniFormat);

    ui->iconWidget->setTitle("离子源");
    ui->iconWidget->setDescription("KV");
    ui->iconWidget->setLineEdit(configIniRead.value("/SYS/Icon", "0").toString());
    ui->dynodeWidget->setTitle("打拿极");
    ui->dynodeWidget->setDescription("KV");
    ui->dynodeWidget->setLineEdit(configIniRead.value("/SYS/Dynode", "0").toString());
    ui->increaseWidget->setTitle("倍增器");
    ui->increaseWidget->setDescription("KV");
    ui->increaseWidget->setLineEdit(configIniRead.value("/SYS/Increase", "0").toString());
    ui->tempterature->setTitle("DL加热");
    ui->tempterature->setDescription("℃");
    ui->tempterature->setLineEdit(configIniRead.value("/SYS/Temperature", "0").toString());
    ui->tempterature->setRangeInput(0.0,7.0);
    ui->DFWidget->setTitle("辉光放电");
    ui->DFWidget->setLineEdit("0");
    ui->ZSQWidgeht->setTitle("注射器");
    ui->ZSQWidgeht->setDescription("ul/min");
    ui->ZSQWidgeht->setLineEdit("0");
}

void MyControl::onStateChange()
{
    if(ui->increaseWidget->getState() == 1){
        isHVHF = 1;
    }else{
        isHVHF = 0;
    }
    //和ssc控制界面通讯，更新数据
    getAllState();
    emit sendAllState(temp_CMD_SSC);

    //和主界面通讯，下发指令
    emit systemStateChange();
}

bool MyControl::getHState()
{
    if(ui->iconWidget->getState() || ui->increaseWidget->getState() || ui->dynodeWidget->getState())
        return true;
    else
        return false;
}

bool MyControl::getTState()
{
    return ui->tempterature->getState();
}


void MyControl::onControlChanged()
{
    QString path;
    if(filePath.isEmpty())
        path = QApplication::applicationDirPath() + "/tuning.ini";
    else
        path = filePath + "/tuning.ini";

    QSettings configIniWrite(path, QSettings::IniFormat);

    configIniWrite.setValue("/SYS/Icon",ui->iconWidget->getValue());
    configIniWrite.setValue("/SYS/Dynode",ui->dynodeWidget->getValue());
    configIniWrite.setValue("/SYS/Increase",ui->increaseWidget->getValue());
    configIniWrite.setValue("/SYS/Tempterature",ui->tempterature->getValue());

    getAllState();
    emit sendAllState(temp_CMD_SSC);

    emit systemStateChange();
}

void MyControl::getAllState()
{
    if(0 == ui->tempterature->getState())
        temp_CMD_SSC.Value_TEMP[0] == 0;
    else
        temp_CMD_SSC.Value_TEMP[0] = ui->tempterature->getValue().toInt();

    temp_CMD_SSC.Value_DAC[1] = ui->dynodeWidget->getValue().toDouble()*1000/1000;
    temp_CMD_SSC.Value_DAC[3] = ui->increaseWidget->getValue().toDouble()*1000/400;
    temp_CMD_SSC.Value_DAC[5] = ui->iconWidget->getValue().toDouble()*1000/500;

    temp_CMD_SSC.enableIO[1] = !isPositive;
    temp_CMD_SSC.enableIO[0] = ui->dynodeWidget->getState();
    temp_CMD_SSC.enableIO[3] = isPositive;
    temp_CMD_SSC.enableIO[2] = ui->iconWidget->getState();
    temp_CMD_SSC.enableIO[5] = isMachPump;
    temp_CMD_SSC.enableIO[4] = ui->increaseWidget->getState();
    temp_CMD_SSC.enableIO[7] = isGain;
    temp_CMD_SSC.enableIO[6] = isFpump;
    double temp = ui->tempterature->getValue().toDouble();
    if(ui->tempterature->getState())
        temp_CMD_SSC.enableIO[8] = (temp>7.0)?7.0:temp;
    else
        temp_CMD_SSC.enableIO[8] = 0;
    temp_CMD_SSC.enableIO[9] = isMinMachPump;
    temp_CMD_SSC.enableIO[10] = isHVHF;
    temp_CMD_SSC.enableIO[11] = 0;
}

void MyControl::initState(STATE_VACUUM state)
{
    switch (state) {
    case STATE_OPENALL:
        isMinMachPump = 1;
        isMachPump = 1;
        isFpump = 1;
        break;
    case STATE_ONLYMACH:
        isMinMachPump = 1;
        isMachPump = 1;
        isFpump = 0;
        break;
    case STATE_CLOSE:
        isMinMachPump = 0;
        isMachPump = 0;
        isFpump = 0;
        break;
    default:
        break;
    }
}

void MyControl::setMachPump(bool state)
{
    if(state)
    {
        isMinMachPump = 1;
        getAllState();
        emit sendAllState(temp_CMD_SSC);
        timer.start(5000);
        connect(&timer,SIGNAL(timeout()),this,SLOT(onTimeOut()));
    }
    else
    {
//        if(isFpump == 1)
//            return;
        isMachPump = 0;
        isMinMachPump = 0;
        isFpump = 0;
        ui->dynodeWidget->setState(false);
        ui->iconWidget->setState(false);
        ui->increaseWidget->setState(false);
        getAllState();
        emit sendAllState(temp_CMD_SSC);
    }

    emit systemStateChange();
}

void MyControl::onTimeOut()
{
    if(isMinMachPump == 1){
        isMachPump = 1;
        isFpump = 1;
        getAllState();
        emit sendAllState(temp_CMD_SSC);
        emit systemStateChange();
    }
}

void MyControl::setMinMachPump(bool state)
{
    if(state){
        isMinMachPump = 1;
        getAllState();
        emit sendAllState(temp_CMD_SSC);
        emit systemStateChange();
    }else{
        isMinMachPump = 0;
    }
}


void MyControl::setPositive(int state)
{
    isPositive = state;
    getAllState();
    emit sendAllState(temp_CMD_SSC);
    emit systemStateChange();
}

void MyControl::setFPump(bool state)
{
    if(state)
    {
        if(isMachPump == 1)
            isFpump = 1;
        getAllState();
        emit sendAllState(temp_CMD_SSC);
    }
    else
    {
        isFpump = 0;
        ui->dynodeWidget->setState(false);
        ui->iconWidget->setState(false);
        ui->increaseWidget->setState(false);
        getAllState();
        emit sendAllState(temp_CMD_SSC);
    }

    emit systemStateChange();
}

void MyControl::setGain(bool state)
{
    if(state)
    {
        isGain = 1;
        getAllState();
        emit sendAllState(temp_CMD_SSC);
    }
    else
    {
        isGain = 0;
        getAllState();
        emit sendAllState(temp_CMD_SSC);
    }

    emit systemStateChange();
}
