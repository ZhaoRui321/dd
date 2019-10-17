#include "sSystem.h"
#include "ui_sSystem.h"
#include "tool/Algorithm.h"

sSystem::sSystem(_CONGIG_OMS::_CONGIG_METHOD* pCONGIG_METHOD,
                 _CONGIG_OMS::_CONGIG_ACQUISITION* pCONGIG_ACQUISITION,
                 _CONGIG_OMS::_CONGIG_ANALYSIS* pCONGIG_ANALYSIS,QScriptEngine* pScriptEngine,
                 QWidget *parent):
    mScriptEngine(pScriptEngine),
    QWidget(parent),
    ui(new Ui::sSystem),
    mParent(parent),
    mCONGIG_METHOD(pCONGIG_METHOD),
    mCONGIG_ACQUISITION(pCONGIG_ACQUISITION),
    mCONGIG_ANALYSIS(pCONGIG_ANALYSIS)
{
    ui->setupUi(this);
    ui->UI_PB_SHOW_SSC->hide();

    mAutoTuning=new sAutoTuning(&mDAQ_CONFIG, this);
    mManualTuning=new sManualTuning(&mDAQ_CONFIG, this);
    //mManualTuning->setFilePath(filePath);
    //ui->control->setFilePath(filePath);
    ui->control->setState(false);

    ui->stackedWidget->addWidget(mAutoTuning);
    connect(mAutoTuning,SIGNAL(ShowSystem()),this,SLOT(onShowSystem()));
    ui->stackedWidget->addWidget(mManualTuning);
    connect(mManualTuning,SIGNAL(ShowSystem()),this,SLOT(onShowSystem()));
    //setCurrentWindow(*(ui->UI_W_SYSTEM));
    mDataProcess= sDataProcess::getDataProcess();
    pControlSSC= new sControlSSC(this);
    ui->stackedWidget->addWidget(pControlSSC);

    btn_style[0] = "QPushButton{background-color:gray;color: white;border-top-left-radius: 25px;border-top-right-radius: 25px;}";
    btn_style[1] = "QPushButton{background-color: white;color: black;border-top-left-radius: 25px;border-top-right-radius: 25px;}";
    btn_style[2] = "QPushButton{color: black;}";
    btn_style[3] = "QPushButton{color: blue;}";

    ui->UI_PB_CONTROL->setStyleSheet(btn_style[1]);
    ui->UI_PB_AUTO->setStyleSheet(btn_style[0]);
    ui->UI_PB_MANUAL->setStyleSheet(btn_style[0]);

    connect(ui->control,SIGNAL(sendAllState(sControlSSC::_CMD_SSC_SET&)),pControlSSC,SLOT(onSendAllState(sControlSSC::_CMD_SSC_SET&)));

    pPwmCCS= new sPwmCCS(this);
    ui->UI_PB_SHOW_PWM->hide();
    ui->stackedWidget->addWidget(pPwmCCS);

    loadFile();
}

sSystem::~sSystem()
{
    delete ui;
}

void sSystem::onPolarity(bool state)
{
    if(state)
        ui->control->setPositive(1);
    else
        ui->control->setPositive(0);
}

void sSystem::setFilePath(QString path)
{
    filePath = path;
    mManualTuning->setFilePath(filePath);
    ui->control->setFilePath(filePath);
}

void sSystem::setControlState(bool state)
{
    if(!state)
        ui->control->setState(state);
    ui->control->setAllEnabled(state);
    ui->UI_PB_MANUAL->setDisabled(!state);
    ui->UI_PB_AUTO->setDisabled(!state);
}

void sSystem::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    QRect rect= ui->UI_PB_CONTROL->rect();
    QPoint p1 = QPoint(rect.left()+4,rect.bottom()+1);;
    QPoint p2 = QPoint(p1.x()+900,p1.y());
    p1 = ui->UI_PB_CONTROL->mapToParent(p1);
    p2 = ui->UI_PB_CONTROL->mapToParent(p2);
    p1 = ui->btnWidget->mapToParent(p1);
    p2 = ui->btnWidget->mapToParent(p2);
    QPen pen = QPen(QColor("white"));
    pen.setWidth(6);
    p.setPen(pen);
    p.drawLine(p1,p2);
}

void sSystem::setCurrentWindow(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
    switch (index) {
    case 0:
        ui->UI_PB_CONTROL->setStyleSheet(btn_style[1]);
        ui->UI_PB_AUTO->setStyleSheet(btn_style[0]);
        ui->UI_PB_MANUAL->setStyleSheet(btn_style[0]);
        break;
    case 1:
        ui->UI_PB_CONTROL->setStyleSheet(btn_style[0]);
        ui->UI_PB_AUTO->setStyleSheet(btn_style[1]);
        ui->UI_PB_MANUAL->setStyleSheet(btn_style[0]);
        break;
    case 2:
        ui->UI_PB_CONTROL->setStyleSheet(btn_style[0]);
        ui->UI_PB_AUTO->setStyleSheet(btn_style[0]);
        ui->UI_PB_MANUAL->setStyleSheet(btn_style[1]);
        emit tuningState();
        break;
    case 3:
        ui->UI_PB_CONTROL->setStyleSheet(btn_style[0]);
        ui->UI_PB_AUTO->setStyleSheet(btn_style[0]);
        ui->UI_PB_MANUAL->setStyleSheet(btn_style[0]);
    default:
        break;
    }
}

void sSystem::on_UI_PB_AUTO_clicked()
{
    setCurrentWindow(1);
}

void sSystem::on_UI_PB_MANUAL_clicked()
{
    setCurrentWindow(2);
}

void sSystem::onShowSystem()
{
    //setCurrentWindow(*(ui->UI_W_SYSTEM));
}

void sSystem::on_UI_PB_QUIT_clicked()
{
    emit tuningState();
    if(mParent)
        mParent->close();
}

bool sSystem::loadFile(bool ifUpdateUI, QString qPath)
{
    mCONGIG_MANUAL_TUNING= mManualTuning->getConfig();
    mCONGIG_AUTO_TUNING= mAutoTuning->getConfig();
    if(!(mCONGIG_METHOD|| mCONGIG_ACQUISITION|| mCONGIG_ANALYSIS|| mCONGIG_MANUAL_TUNING||mCONGIG_AUTO_TUNING))
        return false;
    QString path;
    if(qPath.isEmpty())
        path = QCoreApplication::applicationDirPath()+"/system.ini";
    else
        path = qPath;
    QSettings configIniRead(path, QSettings::IniFormat);
    mDAQ_CONFIG.No_ACC = configIniRead.value("/ConfigDAQ/ACC",4).toDouble();
    mDAQ_CONFIG.Frq_AQ= (uint32_t)(100.0/configIniRead.value("/ConfigDAQ/Frequency",1).toDouble());
    Algorithm::getInstance()->setAcc(mDAQ_CONFIG.No_ACC);
    Algorithm::getInstance()->setFreq(configIniRead.value("/ConfigDAQ/Frequency",1).toDouble());

    QString tmpMethod= configIniRead.value("/Processing/Method","").toString();//"FrameAverage&10+GainOffset&0&1";
    if(mDataProcess)
        mDataProcess->setMethod(tmpMethod);

    mCONGIG_METHOD->LimitInjectTime= configIniRead.value("/Method/LimitInjectionTime","function limitInjectionTime(massStart){return 200;}//ms").toString();//"FrameAverage&10+GainOffset&0&1";
    mScriptEngine->evaluate(mCONGIG_METHOD->LimitInjectTime);
    if(mScriptEngine->hasUncaughtException())
        qDebug()<<"E_sSystem_Method/LimitInjectTime";

    mCONGIG_METHOD->ScaleRangeAGC= configIniRead.value("/Method/ScaleRangeAGC","function scaleRangeAGC(massStart, massEnd, scanSpeed, injectionTime){return 0.95;}").toString();//"FrameAverage&10+GainOffset&0&1";
    mScriptEngine->evaluate(mCONGIG_METHOD->ScaleRangeAGC);
    if(mScriptEngine->hasUncaughtException())
        qDebug()<<"E_sSystem_Method/ScaleRangeAGC";

    mCONGIG_METHOD->FunctionAGC= configIniRead.value("/Method/FunctionAGC","function thresholdAGC(massStart, massEnd, scanSpeed, injectionTime){return 0;}").toString();//"FrameAverage&10+GainOffset&0&1";
    mScriptEngine->evaluate(mCONGIG_METHOD->FunctionAGC);
    if(mScriptEngine->hasUncaughtException())
        qDebug()<<"E_sSystem_Method/FunctionAGC";

    mCONGIG_METHOD->MassExtension
            =mCONGIG_MANUAL_TUNING->MassExtension
            =mCONGIG_AUTO_TUNING->MassExtension= configIniRead.value("/TargetScan/MassExtension",5).toDouble();

    tmpMethod= configIniRead.value("/ManualTuning/ShowFIT","").toString();
    if(tmpMethod.compare("true")==0)
        mCONGIG_MANUAL_TUNING->showFit=true;
    else
        mCONGIG_MANUAL_TUNING->showFit=false;

    mCONGIG_ACQUISITION->Period=configIniRead.value("/TIC/Period",1000).toDouble();

    if(pPwmCCS){
        tmpMethod= configIniRead.value("/System/ShowPWM","").toString();
        if(tmpMethod.compare("true")==0)
            ui->UI_PB_SHOW_PWM->show();
        tmpMethod= configIniRead.value("/System/NamePWM","").toString();
        if(!tmpMethod.isEmpty())
            pPwmCCS->setName(tmpMethod);
        tmpMethod= configIniRead.value("/System/ParameterPWM","").toString();
        if(!tmpMethod.isEmpty())
            pPwmCCS->setParameter(tmpMethod);
    }

    tmpMethod= configIniRead.value("/System/ShowSSC","").toString();
    if(tmpMethod.compare("true")==0)
        ui->UI_PB_SHOW_SSC->show();

    tmpMethod= configIniRead.value("/System/ParameterSSC","").toString();
    if(tmpMethod.isEmpty())
        return false;
    if(pControlSSC){
        if(!pControlSSC->setParameter(tmpMethod))
            return false;
    }else
        return false;
    mManualTuning->updateConfig(); 

    return true;
}

void sSystem::on_pushButton_clicked()
{
    mMassAxis = new MassAxisAdjust();
    mMassAxis->show();
}

void sSystem::on_UI_PB_CONTROL_clicked()
{
    setCurrentWindow(0);
}

MyControl* sSystem::getStateWidget()
{
    return ui->control;
}

void sSystem::on_UI_PB_SHOW_SSC_clicked()
{
    setCurrentWindow(3);
}

void sSystem::on_UI_PB_SHOW_PWM_clicked()
{
    setCurrentWindow(4);
}
