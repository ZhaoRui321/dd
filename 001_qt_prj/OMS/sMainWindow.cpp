#include "sMainWindow.h"
#include "ui_sMainWindow.h"
#include <QQuickView>
#include <QQuickWidget>
#include <qmessagebox.h>
#include "cPumpControl.h"
#include <QTimer>
#include <QDesktopWidget>
#include <QString>
#include <QFileDialog>
#include "sSystem/MyControl.h"


sMainWindow::sMainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sMainWindow)
{
    ui->setupUi(this);
    mMethod= new sMethod(&mScriptEngine, this);
    mSystem= new sSystem(mMethod->getConfig(), mDataAcquisiton.getConfig(), mDataAnalysis.getConfig(), &mScriptEngine, this);
    savefile = new SaveFile(this);
    ui->tipEdit->setPlaceholderText("提示信息...");
    ui->verticalLayout_3->addWidget(&mDataAcquisiton);
    ui->verticalLayout_3->addWidget(&mDataAnalysis);
    ui->verticalLayout_3->addWidget(mSystem);
    ui->verticalLayout_3->addWidget(mMethod);
    //ui->UI_LAYOUT_SYSSTATE->addWidget(&mSystemState);
    setCurrentWindow(*mMethod);
    ui->UI_PB_METHOD->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/R1-1.png);"));
    mCommandUSB= sCommandUSB::getCommandUSB();

    connect(savefile,SIGNAL(saveInfo(QString)),this,SLOT(onSaveInfo(QString)));
    connect(mMethod,SIGNAL(StartAGC(char* ,int)),this,SLOT(onStartAGC(char* ,int)));
    connect(mSystem->getManualTuningP(),SIGNAL(StartScan(char* ,uint ,QByteArray&)),this,SLOT(onStartScanManualTuning(char* ,uint ,QByteArray&)));
    connect(mSystem->getManualTuningP(),SIGNAL(StopScan()),this,SLOT(onStopScan()));
    connect(mMethod,SIGNAL(StartScan(char* ,int ,QString&,QByteArray&)),this,SLOT(onStartScanMethod(char* ,int ,QString&,QByteArray&)));
    connect(mSystem->getStateWidget(),SIGNAL(systemStateChange()),this,SLOT(onSystemStateChanged()));
    connect(mSystem->getManualTuningP(),SIGNAL(tipSend(QString)),this,SLOT(onTipSend(QString)));
    connect(mSystem,SIGNAL(tuningState()),this,SLOT(onTuningState()));
    connect(mSystem->getManualTuningP(),SIGNAL(stopTuning()),this,SLOT(onStopTuning()));
    connect(mCommandUSB,SIGNAL(currentFilePath(QString,QString,bool)),&mDataAnalysis,SLOT(onGetCurrentFilePath(QString,QString,bool)));
    connect(this,SIGNAL(showCurrentFile(bool)),mCommandUSB,SLOT(onShowCurrentFile(bool)));
    connect(mMethod,SIGNAL(polaritySwitched(bool)),this,SLOT(onPolaritySwitched(bool)));
    connect(&mDataAcquisiton, SIGNAL(sAGC(double)), this, SLOT(onAGC(double)));

    mScriptEngine.globalObject().setProperty("Method", mScriptEngine.newQObject(mMethod));
    mScriptEngine.globalObject().setProperty("Tuning", mScriptEngine.newQObject(mSystem->getManualTuningP()));

    QVector<UINT> tmpBuffer;
    ParamCCS::stateRequest(tmpBuffer);//状态查询指令
    QByteArray tmpStateRequestCMD(tmpBuffer.size()* sizeof(UINT),0);
    memcpy(tmpStateRequestCMD.data(), tmpBuffer.data(), tmpStateRequestCMD.size());

    mTimerStateID=startTimer(1000);

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);

    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("hh:mm:ss \nyyyy/M/d");
    ui->timer->setText(str);
    ui->heatBtn->setDisabled(true);
    ui->hightBtn->setDisabled(true);
    ui->tipEdit->setStyleSheet("text-indent: 5px;");
    ui->countLabel->setStyleSheet("color: rgb(216,216,216);");
    ui->stateTitle->setStyleSheet("border-bottom: 2px solid black;"
                                  "color: rgb(111,111,111);");
    ui->headBtn->installEventFilter(this);
    ui->countLabel->installEventFilter(this);
    ui->tipEdit->setText("双击右上角用户头像或ID切换用户...");

    ui->snapBtn->setVisible(false);

    port = new SerialPort();
    connect(port,SIGNAL(getData(QByteArray)),this,SLOT(onGetData(QByteArray)));
    connect(port,SIGNAL(loseSSC()),this,SLOT(onLoseSSC()));

    //initWidget();
}

void sMainWindow::initWidget()
{
    ui->heatBtn->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/DL-OFF.png);"));
    ui->hightBtn->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/HV-OFF.png);"));
    ui->vacuumBtn->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/V-OFF.png);"));
    ui->UI_PB_STOP->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/START-0.png);"));
    ui->UI_PB_STOP->setDisabled(true);
}

sMainWindow::~sMainWindow()
{
    if(mTimerStateID!=-1){
        killTimer(mTimerStateID);
        mTimerStateID=-1;
    }
    delete ui;
}

void sMainWindow::onAGC(double currentTIC)
{
    if(mMethod->getAGC()){
        if(mCommandUSB->isRunningDAQ()){
            if(mMethod->adjustParamAGC(currentTIC))
                //mMethod->scan(true);
                return;
        }
    }
}

void sMainWindow::onGetData(QByteArray arrayReq)
{
    quint16* pCommand=(quint16*)arrayReq.data();
    if(pCommand[0]==0xf301 && pCommand[1] == 0x0002){
        for(int i=0;i<TEMP_WIDTH;i++)
            mCMD_SSC_REQ.Value_TEMP[i] = pCommand[i+2];           //DAC_SET
        for(int i=0;i<DAC_WIDTH_GET;i++)
            mCMD_SSC_REQ.Value_DAC[i] = pCommand[i+8];           //DAC_GET
        mCMD_SSC_REQ.pump_speed = pCommand[25]%256*1000 + pCommand[25]/256*100 + pCommand[26]%256*10 + pCommand[26]/256;
        mCMD_SSC_REQ.pump_current = pCommand[28]%256*10000 + pCommand[28]/256*1000 + pCommand[29]%256*100 + pCommand[29]/256*10;

        if(mCMD_SSC_REQ.pump_current == 2833050 && mCMD_SSC_REQ.pump_speed == 0){
            ui->PumpState->setText("分子泵状态:断电");
        }else if(mCMD_SSC_REQ.pump_current == 0){
            ui->PumpState->setText("分子泵状态:关闭");
        }else if(mCMD_SSC_REQ.pump_current != 0){
            ui->PumpState->setText("分子泵电流:"+QString::number(mCMD_SSC_REQ.pump_current));
        }else if(mCMD_SSC_REQ.pump_speed != 0){
            ui->PumpState->setText("分子泵转速:" + QString::number(mCMD_SSC_REQ.pump_speed));
        }

        double temp = mCMD_SSC_REQ.Value_DAC[1]*0.00243861 - 9.98585727;
        vacuumNum = (int)(temp*100.0)/100.0;

        if(isFirst){
            if(vacuumNum < LOW){
                ui->vacuumBtn->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/V-ON.png);"));
                mSystem->getStateWidget()->initState(MyControl::STATE_OPENALL);
            }else if(vacuumNum < HIGH){
                ui->vacuumBtn->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/V-OFF.png);"));
                mSystem->getStateWidget()->initState(MyControl::STATE_ONLYMACH);
            }else{
                ui->vacuumBtn->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/V-OFF.png);"));
                mSystem->getStateWidget()->initState(MyControl::STATE_CLOSE);
            }
            isFirst = false;
            emit firstState(vacuumNum);
        }

        if(vacuumNum > LOW)
            closeSystem();

        if(vacuumNum < LOW)
            ui->vacuumBtn->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/V-ON.png);"));

        if(vacuumNum == 0)
            ui->GUIState->setText("板卡异常");
        else
            ui->GUIState->setText(QString("规读数为: %1").arg(vacuumNum));
    }
}

void sMainWindow::closeSystem()
{
    ui->vacuumBtn->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/V-OFF.png);"));
    ui->UI_PB_STOP->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/START-0.png);"));
    ui->UI_PB_STOP->setDisabled(true);
    if(mSystem->getStateWidget()->getHState()){
        mSystem->getStateWidget()->setState(false);
        mSystem->getStateWidget()->setAllEnabled(false);
    }
    if(state_running)
        stopAcquisiton();
}

void sMainWindow::onPolaritySwitched(bool state)
{
    if(state)
    {
        mSystem->getStateWidget()->setPositive(1);
    }
    else
    {
        mSystem->getStateWidget()->setPositive(0);
    }
}

void sMainWindow::timerUpdate()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("hh:mm:ss \nyyyy/M/d");
    ui->timer->setText(str);
}

void sMainWindow::timerEvent(QTimerEvent *evt)
{
    if(evt->timerId() == mTimerStateID){
        if(mSerialPortCMD.isEmpty())
            port->writeData(mSystem->createRequest());
        else{
            port->writeData(mSerialPortCMD.first());
            mSerialPortCMD.pop_front();
        }
    }

}

void sMainWindow::showDrive(QByteArray temp)
{
    uint* pStateRequest= (uint*)(temp.data());
    if ((*pStateRequest==0xfffff001)&&(*(pStateRequest+1)==0x00000000)){
        cPumpControl::_STATE_REQUEST tmpSTATE_REQUEST;
        if(cPumpControl::getDrive(temp, tmpSTATE_REQUEST)){
           ui->PumpState->setText(QString("分子泵电流： %1").arg(tmpSTATE_REQUEST.driveCurrent));
        }
    }else if((*pStateRequest==0xfffff133)){
        return;
    }else{
        ui->PumpState->setText("板卡异常");
    }


}

void sMainWindow::setCurrentWindow(QWidget& pWidget)
{
    mDataAcquisiton.hide();
    mDataAnalysis.hide();
    mSystem->hide();
    mMethod->hide();
    ui->UI_PB_METHOD->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/R1-0.png);"));
    ui->UI_PB_ACQUISITION->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/R2-0.png);"));
    ui->UI_PB_ANALYSIS->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/R3-0.png);"));
    ui->UI_PB_SYSTEM->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/R4-0.png);"));
    pWidget.show();
}


void sMainWindow::on_UI_PB_METHOD_clicked()
{
    if(!state_running && vacuumNum < 3.3 && vacuumNum != 0)
        outTuningState();
    setCurrentWindow(*mMethod);
    ui->snapBtn->setVisible(false);
    ui->UI_PB_METHOD->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/R1-1.png);"));
    ui->heatBtn->setDisabled(true);
    ui->hightBtn->setDisabled(true);
    ui->tipEdit->setText("双击右上角用户头像或ID切换用户...");
}

void sMainWindow::on_UI_PB_ACQUISITION_clicked()
{     
    if(!state_running && vacuumNum < 3.3 && vacuumNum != 0)
        outTuningState();
    if(state_running)
        ui->snapBtn->setVisible(true);
    setCurrentWindow(mDataAcquisiton);
    ui->UI_PB_ACQUISITION->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/R2-1.png);"));
    ui->heatBtn->setDisabled(true);
    ui->hightBtn->setDisabled(true);
    ui->tipEdit->clear();
}

void sMainWindow::on_UI_PB_ANALYSIS_clicked()
{
    if(!state_running && vacuumNum < 3.3 && vacuumNum != 0)
        outTuningState();
    setCurrentWindow(mDataAnalysis);
    ui->snapBtn->setVisible(false);
    ui->heatBtn->setDisabled(true);
    ui->hightBtn->setDisabled(true);
    ui->UI_PB_ANALYSIS->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/R3-1.png);"));
    ui->tipEdit->clear();
}

void sMainWindow::on_UI_PB_SYSTEM_clicked()
{
    //outTuningState();
    setCurrentWindow(*mSystem);
    ui->snapBtn->setVisible(false);
    ui->UI_PB_SYSTEM->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/R4-1.png);"));
    initWidgetPos();
    ui->tipEdit->setText("提示： 电压单位为：V，温度单位为：℃...");
    mSystem->getManualTuningP()->loadFile(true);
    mSystem->setCurrentWindow(0);
}

void sMainWindow::closeEvent ( QCloseEvent * e )
{
    if( QMessageBox::question(this,
                             tr("Quit"),
                             tr("Are you sure to quit this application?"),
                              QMessageBox::Yes, QMessageBox::No )
                   == QMessageBox::Yes){
        stopAcquisiton();
        e->accept();
    }else
      e->ignore();
}

void sMainWindow::onStopTuning()
{
    stopAcquisiton();
}

void sMainWindow::stopAcquisiton()
{
    mSystem->getManualTuningP()->stop();
    mSystem->getManualTuningP()->changeCloseButton();
    mDataAcquisiton.stop();
    mCommandUSB->stopDAQ();
    mCommandUSB->stopCCS();

}

bool sMainWindow::startAcquisiton(char* pData,uint32_t nLength, QByteArray& pSegment, QString* fileHead, bool saveFile)
{
    if((uint32_t)(pSegment.size())< sizeof(cParamValue::_Segment))
        return false;
    if(nLength>512){
        QByteArray tempHead;
        tempHead.resize(sizeof(_StreamHead) - sizeof(cParamValue::_Segment));
        tempHead+= pSegment;
        if(fileHead)
            tempHead+= (*fileHead).toUtf8();
        _StreamHead* p_StreamHead =(_StreamHead*)(tempHead.data());
        p_StreamHead->dateTime = QDateTime::currentDateTime().toTime_t();
        p_StreamHead->length = tempHead.size();
        p_StreamHead->typeParam = _StreamHead::Type_Acquisition;
        QSettings configIniRead(filePath+"/tuning.ini", QSettings::IniFormat);
        p_StreamHead->typePlot = (_StreamHead::Type_Plot)configIniRead.value("/SYS/IsProfile",0).toInt();

        mDataAcquisiton.setIsProfile(p_StreamHead->typePlot);
        mDataAcquisiton.setFileHead(tempHead.data(), tempHead.size());
        mCommandUSB->setFileHead(tempHead.data(), tempHead.size());//mCommandUSB->setFileHead(pSegment.data(), pSegment.size());
        mCommandUSB->scanCCS(pData, nLength);
        ParamCCS::_DAQ_CONFIG* tmpDAQ_CONFIG= mSystem->getConfigDAQ();
        if(tmpDAQ_CONFIG==nullptr)
            return false;

        double tmpEventTime=0;
        cParamValue::_Segment* tempSegment=(cParamValue::_Segment*)(pSegment.data());
        for(uint32_t i=0;i<tempSegment->sumEvent;i++){
            cParamValue::_Event* pEvent=((cParamValue::_Event*)((int*)&(tempSegment->fisrtEvent)+ sizeof(cParamValue::_EventLIT)/sizeof(int)*i));
            if(pEvent==nullptr)
                return false;
            tmpEventTime+= pEvent->holdTime;
        }
//        cParamValue::_Event* pEvent= &(((cParamValue::_Segment*) (pSegment.data()))->fisrtEvent);
//        if(pEvent==nullptr)
//            return false;
//        double tmpEventTime= pEvent->holdTime;
//        if(tmpEventTime- 10.0>= 1e-8)
//            tmpDAQ_CONFIG->No_ACC= 1<<6;
//        else if(tmpEventTime- 5.0>= 1e-8)
//            tmpDAQ_CONFIG->No_ACC= 1<<5;
//        else if(tmpEventTime- 2.5>= 1e-8)
//            tmpDAQ_CONFIG->No_ACC= 1<<4;
//        else if(tmpEventTime- 1.25>= 1e-8)
//            tmpDAQ_CONFIG->No_ACC= 1<<3;
//        else if(tmpEventTime- 0.625>= 1e-8)
//            tmpDAQ_CONFIG->No_ACC= 1<<2;
//        else
//            tmpDAQ_CONFIG->No_ACC= 1<<1;
//        tmpDAQ_CONFIG->No_ACC=4;
//        tmpDAQ_CONFIG->Frq_AQ = 100;// 100 的分频   50-2M 100-1M 25-4M（最大）
        tmpDAQ_CONFIG->No_AQP= ((uint32_t)(100000000.0/(double)tmpDAQ_CONFIG->Frq_AQ*
                                      tmpEventTime));//+tmpDAQ_CONFIG->No_ACC-1)/tmpDAQ_CONFIG->No_ACC;
        //上限100-2000  /100   2M  32
        mCommandUSB->startDAQ(*(mSystem->getConfigDAQ()), saveFile);
        return true;
    }
    return false;
}

void sMainWindow::onStartScanManualTuning(char* pData,uint nLength, QByteArray& pSegment)
{
    stopAcquisiton();
    if(startAcquisiton(pData, nLength ,pSegment)){
        mSystem->getManualTuningP()->startDataAcquisiton(pSegment);
        //mSystem->onPolarity(mMethod->getPolarity());
        //ui->UI_PB_STOP->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/STOP.png);"));
    }
}

//2019/4/13 适应校对
void sMainWindow::onStartScanMethod(char* pData,int nLength, QString& fileHead, QByteArray& pSegment)
{
    QByteArray tmpR(512,0);
//    if(mCommandUSB->sendCMD(mSystem->getPWMWidgeht()->createPWM(),tmpR) != 0)
//        return;

    stopAcquisiton();
    if(startAcquisiton(pData, nLength, pSegment, &fileHead, false)){//if(startAcquisiton(pData, nLength ,pSegment,fileHead, true)){
        if(mDataAcquisiton.startDataAcquisiton(pSegment, fileHead ,true)){
            setCurrentWindow(mDataAcquisiton);
            //mSystem->onPolarity(mMethod->getPolarity());
            //ui->snapBtn->setVisible(true);
            state_running = true;
            ui->heatBtn->setDisabled(true);
            ui->hightBtn->setDisabled(true);
            ui->UI_PB_ACQUISITION->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/R2-1.png);"));
            ui->UI_PB_STOP->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/STOP.png);"));
        }
    }
}


void sMainWindow::on_UI_PB_STOP_clicked()
{
    if(state_running){
        ui->snapBtn->setVisible(false);
        stopAcquisiton();
        savefile->showFullScreen();
        ui->UI_PB_STOP->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/START.png);"));
        state_running = false;
    }else{ 
        if(mMethod->startMethodScan()){
        }
    }

}

void sMainWindow::onUserInfo(QString name)
{
    ui->countLabel->setText(name);
    filePath = QCoreApplication::applicationDirPath() + "/" + name;
    mMethod->setFilePath(filePath);
    mSystem->setFilePath(filePath);
    mDataAnalysis.setDatapath(filePath);
    mDataAcquisiton.setDatapath(filePath);
    if(name == "admin")
        mDataAcquisiton.SetIsAdmin(true);
}

void sMainWindow::initWidgetPos()
{
    highPre = new HighPre(this);
    QRect rect = ui->hightBtn->rect();
    QPoint pos = QPoint(rect.left(), rect.bottom());
    pos = ui->hightBtn->mapToGlobal(pos);
    highPre->setGeometry(pos.x()-highPre->width()-25,pos.y()-highPre->height(),highPre->width(),highPre->height());

    temp = new Temperature(this);
    rect = ui->heatBtn->rect();
    pos = QPoint(rect.left(), rect.top());
    pos = ui->heatBtn->mapToGlobal(pos);
    temp->setGeometry(pos.x()-temp->width()-25,pos.y(),temp->width(),temp->height());

    highPre->setVisible(false);
    temp->setVisible(false);
    ui->heatBtn->setDisabled(false);
    ui->hightBtn->setDisabled(false);

}



void sMainWindow::onSaveInfo(QString text)
{
    QString str = "保存成功！路径为：" + filePath + "/data/" + text;
    QString path = filePath + "/data/" + text + ".TIC";
    qDebug() << path << "----------";
    mDataAcquisiton.renameFile(path);
    ui->tipEdit->setText(str);
}

void sMainWindow::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
}


void sMainWindow::onSystemStateChanged()
{
    MyControl* temp = mSystem->getStateWidget();
    if(temp->getHState())
        ui->hightBtn->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/HV-ON.png);"));
    else
        ui->hightBtn->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/HV-OFF.png);"));

    if(!temp->getTState())
        ui->heatBtn->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/DL-OFF.png);"));
    else
        ui->heatBtn->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/DL-ON.png);"));

    QByteArray tempArray = mSystem->createConfig();
    mSerialPortCMD.append(tempArray);
}


bool sMainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(qobject_cast<QPushButton*>(watched) == ui->headBtn
            && event->type() == QEvent::MouseButtonDblClick){
        qDebug() << "触发成功";
        emit showLogin();
        return true;
    }else if(qobject_cast<QLabel*>(watched) == ui->countLabel
             && event->type() == QEvent::MouseButtonDblClick){
        emit showLogin();
        return true;
    }
    return QWidget::eventFilter(watched,event);
}

void sMainWindow::elecPumpCCSCMD(bool state)
{
    if(state)
    {
        //开启分子泵使能
        mSerialPortCMD.append(mSystem->createElecPumpOn());
    }else{
        //关闭分子泵使能
        mSerialPortCMD.append(mSystem->createElecPumpOff());
    }
}

void sMainWindow::onSysInfo(bool state)
{

    if(state){
        ui->vacuumBtn->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/V-ON.png);"));
        ui->UI_PB_STOP->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/START.png);"));
        ui->UI_PB_STOP->setDisabled(false);
    }else{
        //改变显示状态
        ui->heatBtn->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/DL-OFF.png);"));
        ui->hightBtn->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/HV-OFF.png);"));
        ui->vacuumBtn->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/V-OFF.png);"));
        ui->UI_PB_STOP->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/START-0.png);"));
        ui->UI_PB_STOP->setDisabled(true);
    }
    mSystem->setControlState(state);
}

void sMainWindow::onTipSend(QString str)
{
    ui->tipEdit->setText(str);
}

void sMainWindow::onTuningState()
{
    stopAcquisiton();
    ui->UI_PB_STOP->setDisabled(true);
    ui->UI_PB_STOP->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/START-0.png);"));
    state_running = false;
}

void sMainWindow::outTuningState()
{
    stopAcquisiton();
    ui->UI_PB_STOP->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/START.png);"));
    ui->UI_PB_STOP->setDisabled(false);
    ui->snapBtn->setVisible(false);
    state_running = false;
}

void sMainWindow::on_snapBtn_clicked()
{
    ui->snapBtn->setVisible(false);
    setCurrentWindow(mDataAnalysis);
    ui->UI_PB_ANALYSIS->setStyleSheet(QStringLiteral("border-image: url(:/picture/icons/R3-1.png);"));
    emit showCurrentFile(mDataAcquisiton.isOriginal());
}

void sMainWindow::onLoseSSC()
{
    ui->GUIState->setText("板卡断开");
    ui->PumpState->setText("板卡断开");
    vacuumNum = 0;
    mCMD_SSC_REQ.pump_current = 0;

    mSystem->getStateWidget()->setState(false);
}

