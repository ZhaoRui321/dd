#include "sMethod.h"
#include "ui_sMethod.h"
#include <QDebug>
#include <QQuickWidget>
#include <QQuickView>
#include <QTimer>
#include <QDateTime>
#include <QLine>
#include <QPainter>
#include <QRect>
#include <QPoint>
#include "tool/Algorithm.h"

sMethod::sMethod(QScriptEngine* pScriptEngine, QWidget *parent) :
    mScriptEngine(pScriptEngine),
    QWidget(parent),
    ui(new Ui::sMethod)
{
    ui->setupUi(this);
    allScan = new AllScan();
    ui->switchBtn->SetTextOn("正");
    ui->switchBtn->SetTextOff("负");
    ui->switchBtn_AGC->SetTextOn("开");
    ui->switchBtn_AGC->SetTextOff("关");

    ui->switchBtn->SetSize(140,50);
    ui->switchBtn_AGC->SetSize(140,50);

    ui->stackedWidget->setCurrentIndex(0);
    mBufferCCS= _FRAME_BUFF_CCS::resize();
//    mScanFullScan.p_Segment= getSegmentParam();
//    mScanFullScan.p_Segment->sumEvent = 1;
//    mScanFullScan.p_Segment->minTime = 0;
//    memset(mScanFullScan.p_Segment->title,'\0',30);
//    strcpy(mScanFullScan.p_Segment->title,QString("LIT").toUtf8().data());

    btn_style[0] = "QPushButton{background-color:gray;color: white;border-top-left-radius: 25px;border-top-right-radius: 25px;}";
    btn_style[1] = "QPushButton{background-color: white;color: black;border-top-left-radius: 25px;border-top-right-radius: 25px;}";
    btn_style[2] = "QPushButton{color: black;}";
    btn_style[3] = "QPushButton{color: blue;}";


    ui->allSacnBtn->setStyleSheet(btn_style[1]);
    ui->simBtn->setStyleSheet(btn_style[0]);
    ui->msnBtn->setStyleSheet(btn_style[0]);

    connect(ui->switchBtn,SIGNAL(clicked(bool)),this,SLOT(onSwitchClicked(bool)));

//    QUrl source("../OMS/pathView/AllScanf.qml");
//    QQuickView *view = new QQuickView();
//    view->setSource(source);
//    QWidget *container = QWidget::createWindowContainer(view);
//    ui->stackedWidget->addWidget(container);

    //qDebug() << "宽为：" << ui->stackedWidget->widget(3)->width() << "高为：" << ui->stackedWidget->widget(3)->height();
}

sMethod::~sMethod()
{
    delete ui;
}

bool sMethod::getPolarity()
{
    return ui->switchBtn->IsSelected();
}

void sMethod::onSwitchClicked(bool state)
{
    emit polaritySwitched(state);
}

bool sMethod::getAGC()
{
    return ui->switchBtn_AGC->IsSelected();
}

void sMethod::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QRect rect= ui->allSacnBtn->rect();
    QPoint p1 = QPoint(rect.left()+4,rect.bottom()+1);;
    QPoint p2 = QPoint(p1.x()+900,p1.y());
    p1 = ui->allSacnBtn->mapToParent(p1);
    p2 = ui->allSacnBtn->mapToParent(p2);
    p1 = ui->btnWidget->mapToParent(p1);
    p2 = ui->btnWidget->mapToParent(p2);
    p1 = ui->widget->mapToParent(p1);
    p2 = ui->widget->mapToParent(p2);
    QPen pen = QPen(QColor("white"));
    pen.setWidth(6);
    p.setPen(pen);
    p.drawLine(p1,p2);

}

bool sMethod::startMethodScan()
{
    if(!loadFile())
        return false;

    return scan();
}

bool sMethod::scan(bool ifAGC)
{
    int LengthMS=0;
    methods[0] = allScan->getStartMass();
    methods[1] = allScan->getEndMass();
    methods[2] = allScan->getSpeed();
    QString tempStr;
    if(createMethodScan(LengthMS, tempStr, isFullScan)){
        if(LengthMS>0){
            if(ifAGC==false){
                emit StartScan(mBufferCCS->data(), LengthMS, tempStr, mSegment);
            }
            else
                emit StartAGC(mBufferCCS->data(), LengthMS);
            return true;
        }
    }
    return false;
}

bool sMethod::adjustParamAGC(double current)
{
    if(current < AGCMIN){
        if(mInjectionFullScan.d_Time >= MAX_HOLDTIME){
            return false;
        }else{
            mInjectionFullScan.d_Time *= 1.5;
        }
    }
    if(current > AGCMAX){
        if(mInjectionFullScan.d_Time <= MIN_HOLDTIME)
            return false;
        else
            mInjectionFullScan.d_Time *=0.75;
    }

    return true;
    /*
    if(!mScriptEngine)
        return false;
    QScriptValue jsValue = mScriptEngine->evaluate(tr("scaleRangeAGC(%1,%2,%3,%4)")
                                                   .arg(mScanFullScan.d_msStartOrig)
                                                   .arg(mScanFullScan.d_msEndOrig)
                                                   .arg(mScanFullScan.d_Scan_Speed)
                                                   .arg(mInjectionFullScan.d_Time));
    if(!mScriptEngine->hasUncaughtException()){
        if(jsValue.isNumber()){   //0.95
            double tempScaleRangeAGC= jsValue.toNumber();
            double scaleAGC= current / mThresholdAGC;
            if(scaleAGC< tempScaleRangeAGC){
                if(mInjectionFullScan.d_Time>= MAX_HOLDTIME)
                    return false;
                mInjectionFullScan.d_Time/= scaleAGC;
                if(mInjectionFullScan.d_Time>= MAX_HOLDTIME)
                    mInjectionFullScan.d_Time= MAX_HOLDTIME;
            }else if(scaleAGC> 1.0){
                if(mInjectionFullScan.d_Time<= MIN_HOLDTIME)
                    return false;
                mInjectionFullScan.d_Time/= scaleAGC;
                if(mInjectionFullScan.d_Time<= MIN_HOLDTIME)
                    mInjectionFullScan.d_Time= MIN_HOLDTIME;
            }
            qDebug()<<"N_sMethod_Injection_Time:"<<mInjectionFullScan.d_Time;
            return true;
        }else
            return false;
    }
    return false;*/
}

void sMethod::calibration(double& pValue)
{
    if(mCALIBRATE.enable==1){
        switch (mCALIBRATE.coefB.size()) {
        case 6:
            pValue= pow(pValue, 5) * mCALIBRATE.coefB[5]
                    + pow(pValue, 4) * mCALIBRATE.coefB[4]
                    + pow(pValue, 3) * mCALIBRATE.coefB[3]
                    + pow(pValue, 2) * mCALIBRATE.coefB[2]
                    + pValue * mCALIBRATE.coefB[1]
                    + mCALIBRATE.coefB[0]; break;
        case 5:
            pValue= pow(pValue, 4) * mCALIBRATE.coefB[4]
                    + pow(pValue, 3) * mCALIBRATE.coefB[3]
                    + pow(pValue, 2) * mCALIBRATE.coefB[2]
                    + pValue * mCALIBRATE.coefB[1]
                    + mCALIBRATE.coefB[0]; break;
        case 4:
            pValue= pow(pValue, 3) * mCALIBRATE.coefB[3]
                    + pow(pValue, 2) * mCALIBRATE.coefB[2]
                    + pValue * mCALIBRATE.coefB[1]
                    + mCALIBRATE.coefB[0]; break;
        case 3:
            pValue= pow(pValue, 2) * mCALIBRATE.coefB[2]
                    + pValue * mCALIBRATE.coefB[1]
                    + mCALIBRATE.coefB[0]; break;
        default: break;
        }
    }
}

/*
bool sMethod::loadFile(bool ifUpdateUI, QString qPath)
{
    QString path;
    if(qPath.isEmpty())
        path = QCoreApplication::applicationDirPath()+"/tuning.ini";
        //path = ".\tuning.ini";
    else
        path = qPath;
    QSettings configIniRead(path, QSettings::IniFormat);
    //mDAQ_CONFIG->Frq_AQ= (uint)(100.0/configIniRead.value("/ConfigDAQ/Frequency",1).toDouble());
    //mDAQ_CONFIG->No_ACC= configIniRead.value("/ConfigDAQ/NoACC",4).toInt();

    mAdjustFactor.d_Mass_Scale_Factor=configIniRead.value("/AdjustLIT/MassScale",1).toDouble();
    mAdjustFactor.d_Mass_Offset_Factor=configIniRead.value("/AdjustLIT/MassOffset",0).toDouble();
    mAdjustFactor.d_Mass_Forward_Extension=configIniRead.value("/AdjustLIT/MassExtension",2).toDouble();
    QString tmpStr = configIniRead.value("/AdjustLIT/DACGain","1&1&1&1&1&1&1&1&1&1&1&1").toString();
    QStringList tmpList= tmpStr.split("&");
    if(tmpList.size()!=12)
        return false;
    for(int i=0; i<tmpList.size();i++){
        if(tmpList[i].isEmpty())
            return false;
        mAdjustFactor.d_DACGain[i]=tmpList[i].toDouble();
        if(mAdjustFactor.d_DACGain[i]-0.0000001<0&&
                mAdjustFactor.d_DACGain[i]+0.0000001>0)
            return false;
    }
    tmpStr = configIniRead.value("/AdjustLIT/DACOffset","0&0&0&0&0&0&0&0&0&0&0&0").toString();
    tmpList= tmpStr.split("&");
    if(tmpList.size()!=12)
        return false;
    for(int i=0; i<tmpList.size();i++){
        if(tmpList[i].isEmpty())
            return false;
        mAdjustFactor.d_DACOffset[i]=tmpList[i].toDouble();

    }
    mPARAM_SHARE.PhaseAC= configIniRead.value("/LIT/PhaseAC", "9.375").toString();
    mPARAM_SHARE.DutyCycleAC=configIniRead.value("/LIT/DutyCycleAC", "25").toString();
    mPARAM_SHARE.VoltageAC=configIniRead.value("/LIT/VoltageAC", "0").toString();
    mPARAM_SHARE.VoltageRF=configIniRead.value("/LIT/VoltageRF", "0").toString();

    mPARAM_SHARE.FrontCapOn=configIniRead.value("/LIT/FrontCapOn", "0").toString();
    mPARAM_SHARE.FrontCapOff=configIniRead.value("/LIT/FrontCapOff", "0").toString();
    mPARAM_SHARE.BackCap=configIniRead.value("/LIT/BackCap", "0").toString();
    mPARAM_SHARE.FeildVoltage=configIniRead.value("/LIT/FeildVoltage", "0").toString();

    mPARAM_SHARE.OffsetQArray=configIniRead.value("/LIT/OffsetQArray", "0").toString();
    mPARAM_SHARE.VoltQArray=configIniRead.value("/LIT/VoltQArray", "0").toString();
    mPARAM_SHARE.Dynode=configIniRead.value("/LIT/Dynode", "0").toString();
    mPARAM_SHARE.Multiplier=configIniRead.value("/LIT/Multiplier", "0").toString();

    tmpStr = configIniRead.value("/FullScanLIT/MethodArray", "Injection&Cooling&Scan&Empty").toString();
    //tmpStr = configIniRead.value("/Filter/FilterArray", "Injection&Cooling&Scan&Empty").toString();

    mInjectionFullScan.d_Time=              configIniRead.value("/FullScanInjection/Time", "100").toDouble();
    //mInjectionFullScan.d_Mass_Start_Th=		configIniRead.value("/FullScanInjection/MassStart", "40").toDouble();
    mInjectionFullScan.i_DDSDuration=       configIniRead.value("/FullScanInjection/DDSDuration", "64").toInt();
    mInjectionFullScan.i_DDSADelay=         configIniRead.value("/FullScanInjection/DDSADelay", "0").toInt();
    mInjectionFullScan.i_DDSADuty=          configIniRead.value("/FullScanInjection/DDSADuty", "0").toInt();
    mInjectionFullScan.i_DDSBDelay=         configIniRead.value("/FullScanInjection/DDSBDelay", "16").toInt();
    mInjectionFullScan.i_DDSBDuty=          configIniRead.value("/FullScanInjection/DDSBDuty", "48").toInt();

    mCoolingFullScan.d_Time=                configIniRead.value("/FullScanCooling/Time", "50").toDouble();
    //mCoolingFullScan.d_Mass_Start_Th=       configIniRead.value("/FullScanCooling/MassStart", "40").toDouble();
    mCoolingFullScan.i_DDSDuration=         configIniRead.value("/FullScanCooling/DDSDuration", "64").toInt();
    mCoolingFullScan.i_DDSADelay=           configIniRead.value("/FullScanCooling/DDSADelay", "0").toInt();
    mCoolingFullScan.i_DDSADuty=            configIniRead.value("/FullScanCooling/DDSADuty", "0").toInt();
    mCoolingFullScan.i_DDSBDelay=           configIniRead.value("/FullScanCooling/DDSBDelay", "16").toInt();
    mCoolingFullScan.i_DDSBDuty=            configIniRead.value("/FullScanCooling/DDSBDuty", "48").toInt();

    //mScanFullScan.d_Mass_Start_Th=          configIniRead.value("/FullScanScan/MassStart", "40").toDouble();
    //mScanFullScan.d_Mass_End_Th=            configIniRead.value("/FullScanScan/MassEnd", "300").toDouble();
    //mScanFullScan.d_Scan_Speed=             configIniRead.value("/FullScanScan/ScanSpeed", "1000.0").toDouble();
    mScanFullScan.d_Precursor_Mass=         configIniRead.value("/FullScanScan/PrecursorMass", "152").toDouble();
    mScanFullScan.d_Forward_Scan_Precursor_Offset=configIniRead.value("/FullScanScan/ForwardPrecursorOffset", "-0.2").toDouble();
    mScanFullScan.i_DDSDuration=            configIniRead.value("/FullScanScan/DDSDuration", "192").toInt();
    //mScanFullScan.i_DDSADelay=              configIniRead.value("/FullScanScan/DDSADelay", "5").toInt();
    //mScanFullScan.i_DDSADuty=               configIniRead.value("/FullScanScan/DDSADuty", "53").toInt();
    mScanFullScan.i_DDSBDelay=              configIniRead.value("/FullScanScan/DDSBDelay", "16").toInt();
    mScanFullScan.i_DDSBDuty=               configIniRead.value("/FullScanScan/DDSBDuty", "48").toInt();

    mEmptyFullScan.d_Time=                  configIniRead.value("/FullScanEmpty/Time", "50").toDouble();
    //mEmptyFullScan.d_Mass_Start_Th=         configIniRead.value("/FullScanEmpty/MassStart", "40").toDouble();
    //mEmptyFullScan.d_Mass_End_Th=           configIniRead.value("/FullScanEmpty/MassEnd", "300").toDouble();
    mEmptyFullScan.i_DDSDuration=           configIniRead.value("/FullScanEmpty/DDSDuration", "64").toInt();
    mEmptyFullScan.i_DDSADelay=             configIniRead.value("/FullScanEmpty/DDSADelay", "0").toInt();
    mEmptyFullScan.i_DDSADuty=              configIniRead.value("/FullScanEmpty/DDSADuty", "0").toInt();
    mEmptyFullScan.i_HVHF_DutyCycle_DDS=    configIniRead.value("/FullScanEmpty/HVHFDutyCycleDDS", "28").toInt();
    return true;
}
*/
// 2.19/4/13 号修改 为了适应多项式校准
bool sMethod::loadFile(bool ifUpdateUI, QString qPath)
{
    QString path;
    if(qPath.isEmpty())
        path = filePath + "/tuning.ini";
        //path = ".\tuning.ini";
    else
        path = qPath;
    QSettings configIniRead(path, QSettings::IniFormat);
    //mDAQ_CONFIG->Frq_AQ= (uint32_t32_t)(100.0/configIniRead.value("/ConfigDAQ/Frequency",1).toDouble());
    //mDAQ_CONFIG->No_ACC= configIniRead.value("/ConfigDAQ/NoACC",4).toInt();

    mAdjustFactor.d_Mass_Scale_Factor=configIniRead.value("/AdjustLIT/MassScale",1).toDouble();
    mAdjustFactor.d_Mass_Offset_Factor=configIniRead.value("/AdjustLIT/MassOffset",0).toDouble();
    mAdjustFactor.d_Mass_Forward_Extension=configIniRead.value("/AdjustLIT/MassExtension",2).toDouble();
    QString tmpStr = configIniRead.value("/AdjustLIT/DACGain","1&1&1&1&1&1&1&1&1&1&1&1").toString();
    QStringList tmpList= tmpStr.split("&");
    if(tmpList.size()!=12)
        return false;
    for(int i=0; i<tmpList.size();i++){
        if(tmpList[i].isEmpty())
            return false;
        mAdjustFactor.d_DACGain[i]=tmpList[i].toDouble();
        if(mAdjustFactor.d_DACGain[i]-0.0000001<0&&
                mAdjustFactor.d_DACGain[i]+0.0000001>0)
            return false;
    }
    tmpStr = configIniRead.value("/AdjustLIT/DACOffset","0&0&0&0&0&0&0&0&0&0&0&0").toString();
    tmpList= tmpStr.split("&");
    if(tmpList.size()!=12)
        return false;
    for(int i=0; i<tmpList.size();i++){
        if(tmpList[i].isEmpty())
            return false;
        mAdjustFactor.d_DACOffset[i]=tmpList[i].toDouble();
    }

    tmpStr = configIniRead.value("/FIT/PolyFit","").toString();
    tmpList= tmpStr.split("&");
    if(tmpList.size()== 5){
        mCALIBRATE.enable= tmpList[0].toUInt();
        QStringList tempCurrent= tmpList[1].split("@");
        QStringList tempExpect= tmpList[2].split("@");
        QStringList tempCF= tmpList[3].split("@");
        QStringList tempCB= tmpList[4].split("@");
        if((tempCurrent.size()==6)&& (tempExpect.size()==6)){
            mCALIBRATE.current.clear();
            mCALIBRATE.expect.clear();
            mCALIBRATE.coefF.clear();
            mCALIBRATE.coefB.clear();
            foreach (QString var, tempCurrent)
                mCALIBRATE.current.push_back(var);
            foreach (QString var, tempExpect)
                mCALIBRATE.expect.push_back(var);
            foreach (QString var, tempCF)
                mCALIBRATE.coefF.push_back(var.toDouble());
            foreach (QString var, tempCB)
                mCALIBRATE.coefB.push_back(var.toDouble());
        }
    }   
    Algorithm::getInstance()->setDataOffset(configIniRead.value("/ALgorithm/DataOffset",0.1).toDouble());
    Algorithm::getInstance()->setBaseLineOffset(configIniRead.value("/Algorithm/BaseLineOffset",0.005).toDouble());

    mPARAM_SHARE.PhaseAC= configIniRead.value("/LIT/PhaseAC", "9.375").toString();
    mPARAM_SHARE.DutyCycleAC=configIniRead.value("/LIT/DutyCycleAC", "25").toString();
    mPARAM_SHARE.VoltageAC=configIniRead.value("/LIT/VoltageAC", "0").toString();
    mPARAM_SHARE.VoltageRF=configIniRead.value("/LIT/VoltageRF", "0").toString();

    mPARAM_SHARE.FrontCapOn=configIniRead.value("/LIT/FrontCapOn", "0").toString();
    mPARAM_SHARE.FrontCapOff=configIniRead.value("/LIT/FrontCapOff", "0").toString();
    mPARAM_SHARE.BackCap=configIniRead.value("/LIT/BackCap", "0").toString();
    mPARAM_SHARE.FeildVoltage=configIniRead.value("/LIT/FeildVoltage", "0").toString();

    mPARAM_SHARE.OffsetQArray=configIniRead.value("/LIT/OffsetQArray", "0").toString();
    mPARAM_SHARE.VoltQArray=configIniRead.value("/LIT/VoltQArray", "0").toString();
    mPARAM_SHARE.Dynode=configIniRead.value("/LIT/Dynode", "0").toString();
    mPARAM_SHARE.Multiplier=configIniRead.value("/LIT/Multiplier", "0").toString();

    mPARAM_SHARE.FAE = configIniRead.value("/LIT/FAE", "0").toString();
    mPARAM_SHARE.OrificeBias = configIniRead.value("/LIT/OrificeBias", "0").toString();

    tmpStr = configIniRead.value("/FullScanLIT/MethodArray", "Injection&Cooling&Scan&Empty").toString();
    //tmpStr = configIniRead.value("/Filter/FilterArray", "Injection&Cooling&Scan&Empty").toString();

    mInjectionFullScan.d_Time=              configIniRead.value("/FullScanInjection/Time", "100").toDouble();
    //mInjectionFullScan.d_Mass_Start_Th=		configIniRead.value("/FullScanInjection/MassStart", "40").toDouble();
    mInjectionFullScan.i_DDSDuration=       configIniRead.value("/FullScanInjection/DDSDuration", "64").toInt();
    mInjectionFullScan.i_DDSADelay=         configIniRead.value("/FullScanInjection/DDSADelay", "0").toInt();
    mInjectionFullScan.i_DDSADuty=          configIniRead.value("/FullScanInjection/DDSADuty", "0").toInt();
    mInjectionFullScan.i_DDSBDelay=         configIniRead.value("/FullScanInjection/DDSBDelay", "16").toInt();
    mInjectionFullScan.i_DDSBDuty=          configIniRead.value("/FullScanInjection/DDSBDuty", "48").toInt();
    mInjectionFullScan.d_Qarray_RF_Step=    configIniRead.value("/FullScanInjection/d_Qarray_RF_Step", "10").toInt();
    mInjectionFullScan.d_Qarray_RF_FactorA= configIniRead.value("/FullScanInjection/d_Qarray_RF_FactorA", "0.167").toDouble();
    mInjectionFullScan.d_Qarray_RF_FactorB= configIniRead.value("/FullScanInjection/d_Qarray_RF_FactorB", "33.333").toDouble();
    mInjectionFullScan.VoltageRFOffset=     configIniRead.value("/FullScanInjection/VoltageRFOffset", "10").toDouble();

    mCoolingFullScan.d_Time=                configIniRead.value("/FullScanCooling/Time", "50").toDouble();
    //mCoolingFullScan.d_Mass_Start_Th=       configIniRead.value("/FullScanCooling/MassStart", "40").toDouble();
    mCoolingFullScan.i_DDSDuration=         configIniRead.value("/FullScanCooling/DDSDuration", "64").toInt();
    mCoolingFullScan.i_DDSADelay=           configIniRead.value("/FullScanCooling/DDSADelay", "0").toInt();
    mCoolingFullScan.i_DDSADuty=            configIniRead.value("/FullScanCooling/DDSADuty", "0").toInt();
    mCoolingFullScan.i_DDSBDelay=           configIniRead.value("/FullScanCooling/DDSBDelay", "16").toInt();
    mCoolingFullScan.i_DDSBDuty=            configIniRead.value("/FullScanCooling/DDSBDuty", "48").toInt();

    //mScanFullScan.d_Mass_Start_Th=          configIniRead.value("/FullScanScan/MassStart", "40").toDouble();
    //mScanFullScan.d_Mass_End_Th=            configIniRead.value("/FullScanScan/MassEnd", "300").toDouble();
    //mScanFullScan.d_Scan_Speed=             configIniRead.value("/FullScanScan/ScanSpeed", "1000.0").toDouble();
    mScanFullScan.d_Precursor_Mass=         configIniRead.value("/FullScanScan/PrecursorMass", "152").toDouble();
    mScanFullScan.d_Forward_Scan_Precursor_Offset=configIniRead.value("/FullScanScan/ForwardPrecursorOffset", "-0.2").toDouble();
    mScanFullScan.i_DDSDuration=            configIniRead.value("/FullScanScan/DDSDuration", "192").toInt();
    //mScanFullScan.i_DDSADelay=              configIniRead.value("/FullScanScan/DDSADelay", "5").toInt();
    //mScanFullScan.i_DDSADuty=               configIniRead.value("/FullScanScan/DDSADuty", "53").toInt();
    mScanFullScan.i_DDSBDelay=              configIniRead.value("/FullScanScan/DDSBDelay", "16").toInt();
    mScanFullScan.i_DDSBDuty=               configIniRead.value("/FullScanScan/DDSBDuty", "48").toInt();

    mEmptyFullScan.d_Time=                  configIniRead.value("/FullScanEmpty/Time", "50").toDouble();
    //mEmptyFullScan.d_Mass_Start_Th=         configIniRead.value("/FullScanEmpty/MassStart", "40").toDouble();
    //mEmptyFullScan.d_Mass_End_Th=           configIniRead.value("/FullScanEmpty/MassEnd", "300").toDouble();
    mEmptyFullScan.i_DDSDuration=           configIniRead.value("/FullScanEmpty/DDSDuration", "64").toInt();
    mEmptyFullScan.i_DDSADelay=             configIniRead.value("/FullScanEmpty/DDSADelay", "0").toInt();
    mEmptyFullScan.i_DDSADuty=              configIniRead.value("/FullScanEmpty/DDSADuty", "0").toInt();
    mEmptyFullScan.i_HVHF_DutyCycle_DDS=    configIniRead.value("/FullScanEmpty/HVHFDutyCycleDDS", "28").toInt();
    return true;
}

bool sMethod::createMethodFullScan(int& LengthMS)
{
    if(!loadFile())
        return false;
    if(!getParam(mInjectionFullScan)|| !getParam(mCoolingFullScan)|| !getParam(mScanFullScan)|| !getParam(mEmptyFullScan))
        return false;
    mMethod.InitState(&mAdjustFactor,QCoreApplication::applicationDirPath()+"/PTMSCONFIG.ini");
    mMethod.AddStage(&mInjectionFullScan);
    mMethod.AddStage(&mCoolingFullScan);
    mMethod.AddStage(&mScanFullScan);
    mMethod.AddStage(&mEmptyFullScan);

    int nRet,nMSCALEn,methodNO,ID_DataPackage;//MSLength,
    nMSCALEn = LengthMS = methodNO = ID_DataPackage = 0;
    nRet = mMethod.CreateMethod((uchar*)mBufferCCS->data(), &nMSCALEn, &LengthMS, methodNO, ID_DataPackage);

    if(nRet == 0)
        return true;
    return false;
}

bool sMethod::createMethodScan(int& LengthMS, bool isFullScan)
{
    if(!loadFile())
        return false;
    if(!getParam(mInjectionFullScan)|| !getParam(mCoolingFullScan)|| !getParam(mScanFullScan)|| !getParam(mEmptyFullScan))
        return false;
    mMethod.InitState(&mAdjustFactor,QCoreApplication::applicationDirPath()+"/PTMSCONFIG.ini");     //每次都需要初始化
    mMethod.AddStage(&mInjectionFullScan);     //一级扫描方法默认只有四个阶段，分别为injection,cooling,scan,empty
    mMethod.AddStage(&mCoolingFullScan);       //其中scan阶段最多只能有一个，empty阶段需为最后一个阶段

    if(isFullScan){//if(ui->UI_W_FULLSCAN->isHidden()){
        mSegment.resize(sizeof(cParamValue::_Segment) - sizeof(cParamValue::_Event)+sizeof(cParamValue::_EventLIT));
        mScanFullScan.pEvent= &(getSegmentParam()->fisrtEvent);
        mScanFullScan.pEvent->minTime = 0;
        getSegmentParam()->type= cParamValue::Type_LIT_FULL;
        getSegmentParam()->sumEvent = 1;
        memset(getSegmentParam()->title,'\0',30);
        strcpy(getSegmentParam()->title,QString("LIT").toUtf8().data());
        mMethod.AddStage(&mScanFullScan);
    }else{
        massNumList = ui->sim->getMassList();
        massNumCount = ui->sim->getMassListCount();

        if(massNumCount < 1)
            return false;
        mSegment.resize(sizeof(cParamValue::_Segment) - sizeof(cParamValue::_Event)
                        +sizeof(cParamValue::_EventLIT)* massNumCount);
        getSegmentParam()->type= cParamValue::Type_LIT_TARGET;
        getSegmentParam()->sumEvent = massNumCount;
        memset(getSegmentParam()->title,'\0',30);
        strcpy(getSegmentParam()->title,QString("LIT").toUtf8().data());

        for(int i=0; i< massNumCount; i++){
            _Scan_Param* temp_param = new _Scan_Param(mScanFullScan);
            temp_param->pEvent= (cParamValue::_EventLIT*)
                    (((char*)(&(getSegmentParam()->fisrtEvent)))+sizeof(cParamValue::_EventLIT)*i);
            temp_param->pEvent->minTime = 0;
            temp_param->d_Mass_Start_Th= massNumList.at(i) - getConfig()->MassExtension;
            temp_param->d_Mass_End_Th= massNumList.at(i) + getConfig()->MassExtension;
            for(int jj=0;jj<12;jj++)
                temp_param->d_DAC[jj]=i;
            mMethod.AddStage(temp_param);
        }
    }
    mMethod.AddStage(&mEmptyFullScan);         //按步骤调用InitState、AddState、CreateMethod，将得到板卡通讯数据

    int nRet,nMSCALEn,methodNO,ID_DataPackage;//MSLength,
    nMSCALEn = LengthMS = methodNO = ID_DataPackage = 0;
    nRet = mMethod.CreateMethod((uchar*)mBufferCCS->data(), &nMSCALEn, &LengthMS, methodNO, ID_DataPackage);
    mThresholdAGC= calcThresholdAGC(mScriptEngine, mInjectionFullScan, mScanFullScan);
    //MAX_HOLDTIME= limitInjectionTime(mScriptEngine, mInjectionFullScan);
    if(nRet == 0)
        return true;
    return false;
}

bool sMethod::createMethodScan(int& LengthMS, QString& fileHead, bool isFullScan)
{
    if(!loadFile())
        return false;
    if(!getParam(mInjectionFullScan)|| !getParam(mCoolingFullScan)|| !getParam(mScanFullScan)|| !getParam(mEmptyFullScan))
        return false;
    fileHead.clear();
    mMethod.InitState(&mAdjustFactor,QCoreApplication::applicationDirPath()+"/PTMSCONFIG.ini");     //每次都需要初始化
    fileHead+= adjust2string(mAdjustFactor);

    proInjectionFullScan = mInjectionFullScan;
    proInjectionFullScan.d_Time = 5;
    proInjectionFullScan.d_DAC[10] = mPARAM_SHARE.FrontCapOff.toDouble();
    mMethod.AddStage(&proInjectionFullScan);
    calibration(mInjectionFullScan.d_Mass_Start_Th);
    mMethod.AddStage(&mInjectionFullScan);     //一级扫描方法默认只有四个阶段，分别为injection,cooling,scan,empty
    fileHead+= method2string(mInjectionFullScan);

    calibration(mCoolingFullScan.d_Mass_Start_Th);
    mMethod.AddStage(&mCoolingFullScan);       //其中scan阶段最多只能有一个，empty阶段需为最后一个阶段
    fileHead+= method2string(mCoolingFullScan);

    if(isFullScan){//if(ui->UI_W_FULLSCAN->isHidden()){
        mSegment.resize(sizeof(cParamValue::_Segment) - sizeof(cParamValue::_Event)+sizeof(cParamValue::_EventLIT));
        mScanFullScan.pEvent= &(getSegmentParam()->fisrtEvent);
        mScanFullScan.pEvent->minTime = 0;
        getSegmentParam()->type= cParamValue::Type_LIT_FULL;
        getSegmentParam()->sumEvent = 1;
        memset(getSegmentParam()->title,'\0',30);
        strcpy(getSegmentParam()->title,QString("LIT").toUtf8().data());
        calibration(mScanFullScan.d_Mass_Start_Th);
        calibration(mScanFullScan.d_Mass_End_Th);
        mMethod.AddStage(&mScanFullScan);
        fileHead+= method2string(mScanFullScan);
    }/*else{
        if(mListScan.size()<1)
            return false;
        mSegment.resize(sizeof(cParamValue::_Segment) - sizeof(cParamValue::_Event)
                        +sizeof(cParamValue::_EventLIT)* mListScan.size());
        getSegmentParam()->type= cParamValue::Type_LIT_TARGET;
        getSegmentParam()->sumEvent = mListScan.size();
        memset(getSegmentParam()->title,'\0',30);
        strcpy(getSegmentParam()->title,QString("LIT").toUtf8().data());
        for(int i=0; i<mListScan.size(); i++){
            mListScan[i].second= mScanFullScan;
            mListScan[i].second.pEvent= (cParamValue::_EventLIT*)
                    (((char*)(&(getSegmentParam()->fisrtEvent)))+sizeof(cParamValue::_EventLIT)*i);
            mListScan[i].second.pEvent->minTime = 0;
            mListScan[i].second.d_Mass_Start_Th=mListScan[i].first->getMass().toDouble()- getConfig()->MassExtension;
            calibration(mListScan[i].second.d_Mass_Start_Th);
            mListScan[i].second.d_Mass_End_Th=mListScan[i].first->getMass().toDouble()+ getConfig()->MassExtension;
            calibration(mListScan[i].second.d_Mass_End_Th);
            for(int jj=0;jj<12;jj++)
                mListScan[i].second.d_DAC[jj]=i;
            mMethod.AddStage(&(mListScan[i].second));
        }
    }*/
    calibration(mEmptyFullScan.d_Mass_Start_Th);
    calibration(mEmptyFullScan.d_Mass_End_Th);
    mMethod.AddStage(&mEmptyFullScan);         //按步骤调用InitState、AddState、CreateMethod，将得到板卡通讯数据
    fileHead+= method2string(mEmptyFullScan);

    int nMSCALEn,methodNO,ID_DataPackage;//MSLength,
    nMSCALEn = LengthMS = methodNO = ID_DataPackage = 0;
    int nRet = mMethod.CreateMethod((uchar*)mBufferCCS->data(), &nMSCALEn, &LengthMS, methodNO, ID_DataPackage); //生成频点表
    mThresholdAGC= calcThresholdAGC(mScriptEngine, mInjectionFullScan, mScanFullScan);
    //MAX_HOLDTIME= limitInjectionTime(mScriptEngine, mInjectionFullScan);
    if(nRet == 0)
        return true;
    return false;
}

double sMethod::calcThresholdAGC(QScriptEngine* pScriptEngine,
                                 _Injection_Param& pInjectionFullScan, _Scan_Param& pScanFullScan)
{
    if(!pScriptEngine)
        return 99999.99999;
    QScriptValue jsValue = pScriptEngine->evaluate(tr("thresholdAGC(%1,%2,%3,%4)")
                            .arg(pScanFullScan.d_msStartOrig)
                            .arg(pScanFullScan.d_msEndOrig)
                            .arg(pScanFullScan.d_Scan_Speed)
                            .arg(pInjectionFullScan.d_Time));
    if(!pScriptEngine->hasUncaughtException()){
        if(jsValue.isNumber()){
            return jsValue.toNumber();
        }else
            return 99999.99999;
    }
    return 99999.99999;
}
double sMethod::limitInjectionTime(QScriptEngine* pScriptEngine, _Injection_Param& pInjectionFullScan)
{
    if(!pScriptEngine)
        return 200.0;
    QScriptValue jsValue = pScriptEngine->evaluate(tr("limitInjectionTime(%1)")
                            .arg(pInjectionFullScan.d_msStartOrig));
    if(!pScriptEngine->hasUncaughtException()){
        if(jsValue.isNumber()){
            return jsValue.toNumber();
        }else
            return 200.0;
    }
    return 200.0;
}


bool sMethod::getParam(_Injection_Param& pInjection_Param)
{
    pInjection_Param.d_Mass_Start_Th= methods[0];//ui->UI_LE_LOWMASS->text().toDouble();
    pInjection_Param.d_Mass_End_Th = methods[1];
    pInjection_Param.d_msStartOrig = methods[0];
    pInjection_Param.d_msEndOrig = methods[1];
#if 0
    for(int i=0;i<12;i++){
        pInjection_Param.d_DAC[i]=0;
    }
#else
    pInjection_Param.d_DAC[11]=mPARAM_SHARE.OrificeBias.toDouble();//
    pInjection_Param.d_DAC[8]=0;//
    pInjection_Param.d_DAC[10]=mPARAM_SHARE.FrontCapOn.toDouble();
    pInjection_Param.d_DAC[9]=mPARAM_SHARE.BackCap.toDouble();
    pInjection_Param.d_DAC[7]=0;
    pInjection_Param.d_DAC[4]=0;
    pInjection_Param.d_DAC[6]= mPARAM_SHARE.VoltageRF.toDouble()-mInjectionFullScan.VoltageRFOffset;
    pInjection_Param.d_DAC[5]= mPARAM_SHARE.VoltageRF.toDouble()+mInjectionFullScan.VoltageRFOffset;//8
    pInjection_Param.d_DAC[3]=mPARAM_SHARE.VoltQArray.toDouble();
    pInjection_Param.d_DAC[0]= 0;//mPARAM_SHARE.VoltageAC.toDouble();//VoltageAC
    pInjection_Param.d_DAC[2]= 0;//mPARAM_SHARE.VoltageRF.toDouble();
    pInjection_Param.d_DAC[1]= mPARAM_SHARE.OffsetQArray.toDouble();
#endif
    return true;
}

bool sMethod::getParam(_Cooling_Param& pCooling_Param)
{
    mCoolingFullScan.d_Mass_Start_Th= methods[0];//ui->UI_LE_LOWMASS->text().toDouble();
    mCoolingFullScan.d_msStartOrig = methods[0];
#if 0
    for(int i=0;i<12;i++){
        pCooling_Param.d_DAC[i]=1;
    }
#else
    pCooling_Param.d_DAC[11]=mPARAM_SHARE.OrificeBias.toDouble();//
    pCooling_Param.d_DAC[8]=0;//
    pCooling_Param.d_DAC[10]= mPARAM_SHARE.FrontCapOff.toDouble();
    pCooling_Param.d_DAC[9]= mPARAM_SHARE.BackCap.toDouble();
    pCooling_Param.d_DAC[7]=0;
    pCooling_Param.d_DAC[4]=0;
    pCooling_Param.d_DAC[6]= mPARAM_SHARE.VoltageRF.toDouble(); //正值
    pCooling_Param.d_DAC[5]= mPARAM_SHARE.VoltageRF.toDouble(); //负值
    pCooling_Param.d_DAC[3]= mPARAM_SHARE.VoltQArray.toDouble();
    pCooling_Param.d_DAC[0]= 0;//mPARAM_SHARE.VoltageAC.toDouble();//VoltageAC
    pCooling_Param.d_DAC[2]= 0;//mPARAM_SHARE.VoltageRF.toDouble();       //5.21  端口失效
    pCooling_Param.d_DAC[1]= mPARAM_SHARE.OffsetQArray.toDouble();
#endif
    return true;
}

bool sMethod::getParam(_Scan_Param& pScan_Param)
{
//    pScan_Param.d_Mass_Start_Th= ui->UI_LE_LOWMASS->text().toDouble();
//    pScan_Param.d_Mass_End_Th= ui->UI_LE_HIGHMASS->text().toDouble();
//    pScan_Param.d_Scan_Speed= ui->UI_LE_SPEED->text().toDouble();
    pScan_Param.d_Mass_Start_Th= methods[0];
    pScan_Param.d_msStartOrig = methods[0];
    pScan_Param.d_Mass_End_Th= methods[1];
    pScan_Param.d_msEndOrig = methods[1];
    pScan_Param.d_Scan_Speed= methods[2];
    Algorithm::getInstance()->setSpeed((int)pScan_Param.d_Scan_Speed);
    double tmpPhase=mPARAM_SHARE.PhaseAC.toDouble();
    double tmpPercentage= mPARAM_SHARE.DutyCycleAC.toDouble();
    pScan_Param.i_DDSADelay=(uint)(((double)pScan_Param.i_DDSDuration)* tmpPhase/ 360.0);
    pScan_Param.i_DDSADuty=(uint)(((double)pScan_Param.i_DDSDuration)* tmpPercentage/ 100.0)
            + pScan_Param.i_DDSADelay;
#if 0
    for(int i=0;i<12;i++){
        pScan_Param.d_DAC[i]=2;
    }
#else
    pScan_Param.d_DAC[11]=mPARAM_SHARE.OrificeBias.toDouble();//
    pScan_Param.d_DAC[8]=0;//
    pScan_Param.d_DAC[10]= mPARAM_SHARE.FrontCapOff.toDouble();
    pScan_Param.d_DAC[9]= mPARAM_SHARE.BackCap.toDouble();
    pScan_Param.d_DAC[7]=mPARAM_SHARE.FAE.toDouble();
    pScan_Param.d_DAC[4]=0;
    pScan_Param.d_DAC[6]= mPARAM_SHARE.VoltageRF.toDouble();
    pScan_Param.d_DAC[5]= mPARAM_SHARE.VoltageRF.toDouble();//8
    pScan_Param.d_DAC[3]= mPARAM_SHARE.VoltQArray.toDouble();
    pScan_Param.d_DAC[0]= mPARAM_SHARE.VoltageAC.toDouble();//VoltageAC
    pScan_Param.d_DAC[2]= 0;//mPARAM_SHARE.VoltageRF.toDouble();
    pScan_Param.d_DAC[1]= mPARAM_SHARE.OffsetQArray.toDouble();
#endif
    return true;
}

bool sMethod::getParam(_Empty_Param& pEmpty_Param)
{
    mEmptyFullScan.d_Mass_Start_Th=methods[0];//ui->UI_LE_LOWMASS->text().toDouble();
    mEmptyFullScan.d_Mass_End_Th=methods[1];//ui->UI_LE_HIGHMASS->text().toDouble();
    mEmptyFullScan.d_msStartOrig = methods[0];
    mEmptyFullScan.d_msEndOrig = methods[1];
#if 0
    for(int i=0;i<12;i++){
        pEmpty_Param.d_DAC[i]=3;
    }
#else
    pEmpty_Param.d_DAC[11]=mPARAM_SHARE.OrificeBias.toDouble();//
    pEmpty_Param.d_DAC[8]=0;//
    pEmpty_Param.d_DAC[10]= mPARAM_SHARE.FrontCapOff.toDouble();
    pEmpty_Param.d_DAC[9]= mPARAM_SHARE.BackCap.toDouble();
    pEmpty_Param.d_DAC[7]=0;
    pEmpty_Param.d_DAC[4]=0;
    pEmpty_Param.d_DAC[6]= mPARAM_SHARE.VoltageRF.toDouble();
    pEmpty_Param.d_DAC[5]= mPARAM_SHARE.VoltageRF.toDouble();//8
    pEmpty_Param.d_DAC[3]= mPARAM_SHARE.VoltQArray.toDouble();
    pEmpty_Param.d_DAC[0]= 0;//mPARAM_SHARE.VoltageAC.toDouble();//VoltageAC
    pEmpty_Param.d_DAC[2]= 0;//mPARAM_SHARE.VoltageRF.toDouble();
    pEmpty_Param.d_DAC[1]= mPARAM_SHARE.OffsetQArray.toDouble();
#endif
    return true;
}

void sMethod::on_allSacnBtn_clicked()
{
   ui->stackedWidget->setCurrentIndex(0);
   ui->allSacnBtn->setStyleSheet(btn_style[1]);
   ui->simBtn->setStyleSheet(btn_style[0]);
   ui->msnBtn->setStyleSheet(btn_style[0]);
   isFullScan = true;
}

void sMethod::on_simBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->allSacnBtn->setStyleSheet(btn_style[0]);
    ui->simBtn->setStyleSheet(btn_style[1]);
    ui->msnBtn->setStyleSheet(btn_style[0]);
    isFullScan = false;
}

void sMethod::on_msnBtn_clicked()
{
//    ui->stackedWidget->setCurrentIndex(3);
//    ui->allSacnBtn->setStyleSheet(btn_style[0]);
//    ui->simBtn->setStyleSheet(btn_style[0]);
//    ui->msnBtn->setStyleSheet(btn_style[1]);
}

QString sMethod::adjust2string(_Adjust_Factor& pAdjust_Factor)
{
    return QString("AdjustFactor\nMassScaleFactor=%1\tMassOffsetFactor=%2\tMassForwardExtension=%3\t"
                   "DAC0Gain=%4\tDAC1Gain=%5\tDAC2Gain=%6\tDAC3Gain=%7\tDAC4Gain=%8\tDAC5Gain=%9\t"
                   "DAC6Gain=%10\tDAC7Gain=%11\tDAC8Gain=%12\tDAC9Gain=%13\tDAC10Gain=%14\tDAC11Gain=%15\t"
                   "DAC0Offset=%16\tDAC1Offset=%17\tDAC2Offset=%18\tDAC3Offset=%19\tDAC4Offset=%20\tDAC5Offset=%21\t"
                   "DAC6Offset=%22\tDAC7Offset=%23\tDAC8Offset=%24\tDAC9Offset=%25\tDAC10Offset=%26\tDAC11Offset=%27\n")
            .arg(pAdjust_Factor.d_Mass_Scale_Factor).arg(pAdjust_Factor.d_Mass_Offset_Factor).arg(pAdjust_Factor.d_Mass_Forward_Extension)
            .arg(pAdjust_Factor.d_DACGain[0]).arg(pAdjust_Factor.d_DACGain[1]).arg(pAdjust_Factor.d_DACGain[2])
            .arg(pAdjust_Factor.d_DACGain[3]).arg(pAdjust_Factor.d_DACGain[4]).arg(pAdjust_Factor.d_DACGain[5])
            .arg(pAdjust_Factor.d_DACGain[6]).arg(pAdjust_Factor.d_DACGain[7]).arg(pAdjust_Factor.d_DACGain[8])
            .arg(pAdjust_Factor.d_DACGain[9]).arg(pAdjust_Factor.d_DACGain[10]).arg(pAdjust_Factor.d_DACGain[11])
            .arg(pAdjust_Factor.d_DACOffset[0]).arg(pAdjust_Factor.d_DACOffset[1]).arg(pAdjust_Factor.d_DACOffset[2])
            .arg(pAdjust_Factor.d_DACOffset[3]).arg(pAdjust_Factor.d_DACOffset[4]).arg(pAdjust_Factor.d_DACOffset[5])
            .arg(pAdjust_Factor.d_DACOffset[6]).arg(pAdjust_Factor.d_DACOffset[7]).arg(pAdjust_Factor.d_DACOffset[8])
            .arg(pAdjust_Factor.d_DACOffset[9]).arg(pAdjust_Factor.d_DACOffset[10]).arg(pAdjust_Factor.d_DACOffset[11]);
}

QString sMethod::method2string(_LIT_PARAM& pLIT_PARAM)
{
    switch(pLIT_PARAM.i_Name){
    case i_Injection:{
        _Injection_Param* pInjection_Param= (_Injection_Param*)(&pLIT_PARAM);
        return QString("Injection\nTime=%1\tMassStart=%2\tMassStartOrig=%3\t"
                       "DDSDuration=%4\tDDSADelay=%5\tDDSADuty=%6\tDDSBDelay=%7\tDDSBDuty=%8\t"
                       "DAC0=%9\tDAC1=%10\tDAC2=%11\tDAC3=%12\tDAC4=%13\tDAC5=%14\t"
                       "DAC6=%15\tDAC7=%16\tDAC8=%17\tDAC9=%18\tDAC10=%19\tDAC11=%20\tDIO=%21\n")
                .arg(pInjection_Param->d_Time).arg(pInjection_Param->d_Mass_Start_Th).arg(pInjection_Param->d_msStartOrig)
                .arg(pInjection_Param->i_DDSDuration).arg(pInjection_Param->i_DDSADelay).arg(pInjection_Param->i_DDSADuty)
                .arg(pInjection_Param->i_DDSBDelay).arg(pInjection_Param->i_DDSBDuty).arg(pInjection_Param->d_DAC[0])
                .arg(pInjection_Param->d_DAC[1]).arg(pInjection_Param->d_DAC[2]).arg(pInjection_Param->d_DAC[3])
                .arg(pInjection_Param->d_DAC[4]).arg(pInjection_Param->d_DAC[5]).arg(pInjection_Param->d_DAC[6])
                .arg(pInjection_Param->d_DAC[7]).arg(pInjection_Param->d_DAC[8]).arg(pInjection_Param->d_DAC[9])
                .arg(pInjection_Param->d_DAC[10]).arg(pInjection_Param->d_DAC[11]).arg(pInjection_Param->ui_DIO);
        break;}
    case i_Cooling:{
        _Cooling_Param* pCooling_Param= (_Cooling_Param*)(&pLIT_PARAM);
        return QString("Cooling\nTime=%1\tMassStart=%2\tMassStartOrig=%3\t"
                       "DDSDuration=%4\tDDSADelay=%5\tDDSADuty=%6\tDDSBDelay=%7\tDDSBDuty=%8\t"
                       "DAC0=%9\tDAC1=%10\tDAC2=%11\tDAC3=%12\tDAC4=%13\tDAC5=%14\t"
                       "DAC6=%15\tDAC7=%16\tDAC8=%17\tDAC9=%18\tDAC10=%19\tDAC11=%20\tDIO=%21\n")
                .arg(pCooling_Param->d_Time).arg(pCooling_Param->d_Mass_Start_Th).arg(pCooling_Param->d_msStartOrig)
                .arg(pCooling_Param->i_DDSDuration).arg(pCooling_Param->i_DDSADelay).arg(pCooling_Param->i_DDSADuty)
                .arg(pCooling_Param->i_DDSBDelay).arg(pCooling_Param->i_DDSBDuty).arg(pCooling_Param->d_DAC[0])
                .arg(pCooling_Param->d_DAC[1]).arg(pCooling_Param->d_DAC[2]).arg(pCooling_Param->d_DAC[3])
                .arg(pCooling_Param->d_DAC[4]).arg(pCooling_Param->d_DAC[5]).arg(pCooling_Param->d_DAC[6])
                .arg(pCooling_Param->d_DAC[7]).arg(pCooling_Param->d_DAC[8]).arg(pCooling_Param->d_DAC[9])
                .arg(pCooling_Param->d_DAC[10]).arg(pCooling_Param->d_DAC[11]).arg(pCooling_Param->ui_DIO);
        break;}
    case i_RExcitation:{
        _RExcitation_Param* pRExcitation_Param= (_RExcitation_Param*)(&pLIT_PARAM);
        return QString("RExcitation\nTime=%1\tMassStart=%2\tMassStartOrig=%3\t"
                       "DDSDuration=%4\tDDSADelay=%5\tDDSADuty=%6\tDDSBDelay=%7\tDDSBDuty=%8\t"
                       "DAC0=%9\tDAC1=%10\tDAC2=%11\tDAC3=%12\tDAC4=%13\tDAC5=%14\t"
                       "DAC6=%15\tDAC7=%16\tDAC8=%17\tDAC9=%18\tDAC10=%19\tDAC11=%20\tDIO=%21\t"
                       "PrecursorMass=%22\tPrecursorOrig=%23\tExcitationFrequencyOffset%24\n")
                .arg(pRExcitation_Param->d_Time).arg(pRExcitation_Param->d_Mass_Start_Th).arg(pRExcitation_Param->d_msStartOrig)
                .arg(pRExcitation_Param->i_DDSDuration).arg(pRExcitation_Param->i_DDSADelay).arg(pRExcitation_Param->i_DDSADuty)
                .arg(pRExcitation_Param->i_DDSBDelay).arg(pRExcitation_Param->i_DDSBDuty).arg(pRExcitation_Param->d_DAC[0])
                .arg(pRExcitation_Param->d_DAC[1]).arg(pRExcitation_Param->d_DAC[2]).arg(pRExcitation_Param->d_DAC[3])
                .arg(pRExcitation_Param->d_DAC[4]).arg(pRExcitation_Param->d_DAC[5]).arg(pRExcitation_Param->d_DAC[6])
                .arg(pRExcitation_Param->d_DAC[7]).arg(pRExcitation_Param->d_DAC[8]).arg(pRExcitation_Param->d_DAC[9])
                .arg(pRExcitation_Param->d_DAC[10]).arg(pRExcitation_Param->d_DAC[11]).arg(pRExcitation_Param->ui_DIO)
                .arg(pRExcitation_Param->d_Precursor_Mass).arg(pRExcitation_Param->d_msPrecursorOrig).arg(pRExcitation_Param->d_Excitation_Frequency_Offset);
        break;}
    case i_IsoCooling:{
        _IsoCooling_Param* pIsoCooling_Param= (_IsoCooling_Param*)(&pLIT_PARAM);
        return QString("IsoCooling\nTime=%1\tMassStart=%2\tMassStartOrig=%3\t"
                       "DDSDuration=%4\tDDSADelay=%5\tDDSADuty=%6\tDDSBDelay=%7\tDDSBDuty=%8\t"
                       "DAC0=%9\tDAC1=%10\tDAC2=%11\tDAC3=%12\tDAC4=%13\tDAC5=%14\t"
                       "DAC6=%15\tDAC7=%16\tDAC8=%17\tDAC9=%18\tDAC10=%19\tDAC11=%20\tDIO=%21\t"
                       "PrecursorMass=%22\tPrecursorOrig=%23\n")
                .arg(pIsoCooling_Param->d_Time).arg(pIsoCooling_Param->d_Mass_Start_Th).arg(pIsoCooling_Param->d_msStartOrig)
                .arg(pIsoCooling_Param->i_DDSDuration).arg(pIsoCooling_Param->i_DDSADelay).arg(pIsoCooling_Param->i_DDSADuty)
                .arg(pIsoCooling_Param->i_DDSBDelay).arg(pIsoCooling_Param->i_DDSBDuty).arg(pIsoCooling_Param->d_DAC[0])
                .arg(pIsoCooling_Param->d_DAC[1]).arg(pIsoCooling_Param->d_DAC[2]).arg(pIsoCooling_Param->d_DAC[3])
                .arg(pIsoCooling_Param->d_DAC[4]).arg(pIsoCooling_Param->d_DAC[5]).arg(pIsoCooling_Param->d_DAC[6])
                .arg(pIsoCooling_Param->d_DAC[7]).arg(pIsoCooling_Param->d_DAC[8]).arg(pIsoCooling_Param->d_DAC[9])
                .arg(pIsoCooling_Param->d_DAC[10]).arg(pIsoCooling_Param->d_DAC[11]).arg(pIsoCooling_Param->ui_DIO)
                .arg(pIsoCooling_Param->d_Precursor_Mass).arg(pIsoCooling_Param->d_msPrecursorOrig);
        break;}
    case i_DAWI:{
        _DAWI_Param* pDAWI_Param= (_DAWI_Param*)(&pLIT_PARAM);
        return QString("DAWI\nTime=%1\tMassStart=%2\tMassStartOrig=%3\t"
                       "DDSDuration=%4\tDDSADelay=%5\tDDSADuty=%6\tDDSBDelay=%7\tDDSBDuty=%8\t"
                       "DAC0=%9\tDAC1=%10\tDAC2=%11\tDAC3=%12\tDAC4=%13\tDAC5=%14\t"
                       "DAC6=%15\tDAC7=%16\tDAC8=%17\tDAC9=%18\tDAC10=%19\tDAC11=%20\tDIO=%21\t"
                       "PrecursorMass=%22\tPrecursorOrig=%23\n")
                .arg(pDAWI_Param->d_Time).arg(pDAWI_Param->d_Mass_Start_Th).arg(pDAWI_Param->d_msStartOrig)
                .arg(pDAWI_Param->i_DDSDuration).arg(pDAWI_Param->i_DDSADelay).arg(pDAWI_Param->i_DDSADuty)
                .arg(pDAWI_Param->i_DDSBDelay).arg(pDAWI_Param->i_DDSBDuty).arg(pDAWI_Param->d_DAC[0])
                .arg(pDAWI_Param->d_DAC[1]).arg(pDAWI_Param->d_DAC[2]).arg(pDAWI_Param->d_DAC[3])
                .arg(pDAWI_Param->d_DAC[4]).arg(pDAWI_Param->d_DAC[5]).arg(pDAWI_Param->d_DAC[6])
                .arg(pDAWI_Param->d_DAC[7]).arg(pDAWI_Param->d_DAC[8]).arg(pDAWI_Param->d_DAC[9])
                .arg(pDAWI_Param->d_DAC[10]).arg(pDAWI_Param->d_DAC[11]).arg(pDAWI_Param->ui_DIO)
                .arg(pDAWI_Param->d_Precursor_Mass).arg(pDAWI_Param->d_msPrecursorOrig);
        break;}
    case i_BIsoScan:{
        _BIsoScan_Param* pBIsoScan_Param= (_BIsoScan_Param*)(&pLIT_PARAM);
        return QString("BIsoScan\nReverseSpeed=%1\tMassStart=%2\tMassStartOrig=%3\t"
                       "DDSDuration=%4\tDDSADelay=%5\tDDSADuty=%6\tDDSBDelay=%7\tDDSBDuty=%8\t"
                       "DAC0=%9\tDAC1=%10\tDAC2=%11\tDAC3=%12\tDAC4=%13\tDAC5=%14\t"
                       "DAC6=%15\tDAC7=%16\tDAC8=%17\tDAC9=%18\tDAC10=%19\tDAC11=%20\tDIO=%21\t"
                       "PrecursorMass=%22\tPrecursorOrig=%23\tReverseScanPrecursorOffset=%24\n")
                .arg(pBIsoScan_Param->d_ReverseSpeed).arg(pBIsoScan_Param->d_Mass_Start_Th).arg(pBIsoScan_Param->d_msStartOrig)
                .arg(pBIsoScan_Param->i_DDSDuration).arg(pBIsoScan_Param->i_DDSADelay).arg(pBIsoScan_Param->i_DDSADuty)
                .arg(pBIsoScan_Param->i_DDSBDelay).arg(pBIsoScan_Param->i_DDSBDuty).arg(pBIsoScan_Param->d_DAC[0])
                .arg(pBIsoScan_Param->d_DAC[1]).arg(pBIsoScan_Param->d_DAC[2]).arg(pBIsoScan_Param->d_DAC[3])
                .arg(pBIsoScan_Param->d_DAC[4]).arg(pBIsoScan_Param->d_DAC[5]).arg(pBIsoScan_Param->d_DAC[6])
                .arg(pBIsoScan_Param->d_DAC[7]).arg(pBIsoScan_Param->d_DAC[8]).arg(pBIsoScan_Param->d_DAC[9])
                .arg(pBIsoScan_Param->d_DAC[10]).arg(pBIsoScan_Param->d_DAC[11]).arg(pBIsoScan_Param->ui_DIO)
                .arg(pBIsoScan_Param->d_Precursor_Mass).arg(pBIsoScan_Param->d_msPrecursorOrig).arg(pBIsoScan_Param->d_Reverse_Scan_Precursor_Offset);
        break;}
    case i_FIsoScan:{
        _FIsoScan_Param* pFIsoScan_Param= (_FIsoScan_Param*)(&pLIT_PARAM);
        return QString("FIsoScan\nForwardSpeed=%1\tMassStart=%2\tMassStartOrig=%3\t"
                       "DDSDuration=%4\tDDSADelay=%5\tDDSADuty=%6\tDDSBDelay=%7\tDDSBDuty=%8\t"
                       "DAC0=%9\tDAC1=%10\tDAC2=%11\tDAC3=%12\tDAC4=%13\tDAC5=%14\t"
                       "DAC6=%15\tDAC7=%16\tDAC8=%17\tDAC9=%18\tDAC10=%19\tDAC11=%20\tDIO=%21\t"
                       "PrecursorMass=%22\tPrecursorOrig=%23\tForwardScanPrecursorOffset=%24\n")
                .arg(pFIsoScan_Param->d_ForwardSpeed).arg(pFIsoScan_Param->d_Mass_Start_Th).arg(pFIsoScan_Param->d_msStartOrig)
                .arg(pFIsoScan_Param->i_DDSDuration).arg(pFIsoScan_Param->i_DDSADelay).arg(pFIsoScan_Param->i_DDSADuty)
                .arg(pFIsoScan_Param->i_DDSBDelay).arg(pFIsoScan_Param->i_DDSBDuty).arg(pFIsoScan_Param->d_DAC[0])
                .arg(pFIsoScan_Param->d_DAC[1]).arg(pFIsoScan_Param->d_DAC[2]).arg(pFIsoScan_Param->d_DAC[3])
                .arg(pFIsoScan_Param->d_DAC[4]).arg(pFIsoScan_Param->d_DAC[5]).arg(pFIsoScan_Param->d_DAC[6])
                .arg(pFIsoScan_Param->d_DAC[7]).arg(pFIsoScan_Param->d_DAC[8]).arg(pFIsoScan_Param->d_DAC[9])
                .arg(pFIsoScan_Param->d_DAC[10]).arg(pFIsoScan_Param->d_DAC[11]).arg(pFIsoScan_Param->ui_DIO)
                .arg(pFIsoScan_Param->d_Precursor_Mass).arg(pFIsoScan_Param->d_msPrecursorOrig).arg(pFIsoScan_Param->d_Forward_Scan_Precursor_Offset);
        break;}
    case i_Scan:{
        _Scan_Param* pScan_Param= (_Scan_Param*)(&pLIT_PARAM);
        return QString("Scan\nScanSpeed=%1\tMassStart=%2\tMassStartOrig=%3\t"
                       "DDSDuration=%4\tDDSADelay=%5\tDDSADuty=%6\tDDSBDelay=%7\tDDSBDuty=%8\t"
                       "DAC0=%9\tDAC1=%10\tDAC2=%11\tDAC3=%12\tDAC4=%13\tDAC5=%14\t"
                       "DAC6=%15\tDAC7=%16\tDAC8=%17\tDAC9=%18\tDAC10=%19\tDAC11=%20\tDIO=%21\t"
                       "PrecursorMass=%22\tPrecursorOrig=%23\tForwardScanPrecursorOffset=%24\t"
                       "MassEnd=%25\tMassEnOrig=%26\n")
                .arg(pScan_Param->d_Scan_Speed).arg(pScan_Param->d_Mass_Start_Th).arg(pScan_Param->d_msStartOrig)
                .arg(pScan_Param->i_DDSDuration).arg(pScan_Param->i_DDSADelay).arg(pScan_Param->i_DDSADuty)
                .arg(pScan_Param->i_DDSBDelay).arg(pScan_Param->i_DDSBDuty).arg(pScan_Param->d_DAC[0])
                .arg(pScan_Param->d_DAC[1]).arg(pScan_Param->d_DAC[2]).arg(pScan_Param->d_DAC[3])
                .arg(pScan_Param->d_DAC[4]).arg(pScan_Param->d_DAC[5]).arg(pScan_Param->d_DAC[6])
                .arg(pScan_Param->d_DAC[7]).arg(pScan_Param->d_DAC[8]).arg(pScan_Param->d_DAC[9])
                .arg(pScan_Param->d_DAC[10]).arg(pScan_Param->d_DAC[11]).arg(pScan_Param->ui_DIO)
                .arg(pScan_Param->d_Precursor_Mass).arg(pScan_Param->d_msPrecursorOrig).arg(pScan_Param->d_Forward_Scan_Precursor_Offset)
                .arg(pScan_Param->d_Mass_End_Th).arg(pScan_Param->d_msEndOrig);
        break;}
    case i_Empty:{
        _Empty_Param* pEmpty_Param= (_Empty_Param*)(&pLIT_PARAM);
        return QString("Empty\nTime=%1\tMassStart=%2\tMassStartOrig=%3\t\MassEnd=%4\tMassEndOrig=%5\t"
                       "DDSDuration=%6\tDDSADelay=%7\tDDSADuty=%8\tHVHFDutyCycleDDS=%9\t"
                       "DAC0=%10\tDAC1=%11\tDAC2=%12\tDAC3=%13\tDAC4=%14\tDAC5=%15\t"
                       "DAC6=%16\tDAC7=%17\tDAC8=%18\tDAC9=%19\tDAC10=%20\tDAC11=%21\tDIO=%22\n")
                .arg(pEmpty_Param->d_Time).arg(pEmpty_Param->d_Mass_Start_Th).arg(pEmpty_Param->d_msStartOrig)
                .arg(pEmpty_Param->d_Mass_End_Th).arg(pEmpty_Param->d_msEndOrig)
                .arg(pEmpty_Param->i_DDSDuration).arg(pEmpty_Param->i_DDSADelay).arg(pEmpty_Param->i_DDSADuty)
                .arg(pEmpty_Param->i_HVHF_DutyCycle_DDS).arg(pEmpty_Param->d_DAC[0])
                .arg(pEmpty_Param->d_DAC[1]).arg(pEmpty_Param->d_DAC[2]).arg(pEmpty_Param->d_DAC[3])
                .arg(pEmpty_Param->d_DAC[4]).arg(pEmpty_Param->d_DAC[5]).arg(pEmpty_Param->d_DAC[6])
                .arg(pEmpty_Param->d_DAC[7]).arg(pEmpty_Param->d_DAC[8]).arg(pEmpty_Param->d_DAC[9])
                .arg(pEmpty_Param->d_DAC[10]).arg(pEmpty_Param->d_DAC[11]).arg(pEmpty_Param->ui_DIO);
        break;}
    case i_ScanSpecial:{
        _Scan_Param* pScanSpecial_Param= (_Scan_Param*)(&pLIT_PARAM);
        return QString("ScanSpecial\nScanSpeed=%1\tMassStart=%2\tMassStartOrig=%3\t"
                       "DDSDuration=%4\tDDSADelay=%5\tDDSADuty=%6\tDDSBDelay=%7\tDDSBDuty=%8\t"
                       "DAC0=%9\tDAC1=%10\tDAC2=%11\tDAC3=%12\tDAC4=%13\tDAC5=%14\t"
                       "DAC6=%15\tDAC7=%16\tDAC8=%17\tDAC9=%18\tDAC10=%19\tDAC11=%20\tDIO=%21\t"
                       "PrecursorMass=%22\tPrecursorOrig=%23\tForwardScanPrecursorOffset=%24\t"
                       "MassEnd=%25\tMassEnOrig=%26\n")
                .arg(pScanSpecial_Param->d_Scan_Speed).arg(pScanSpecial_Param->d_Mass_Start_Th).arg(pScanSpecial_Param->d_msStartOrig)
                .arg(pScanSpecial_Param->i_DDSDuration).arg(pScanSpecial_Param->i_DDSADelay).arg(pScanSpecial_Param->i_DDSADuty)
                .arg(pScanSpecial_Param->i_DDSBDelay).arg(pScanSpecial_Param->i_DDSBDuty).arg(pScanSpecial_Param->d_DAC[0])
                .arg(pScanSpecial_Param->d_DAC[1]).arg(pScanSpecial_Param->d_DAC[2]).arg(pScanSpecial_Param->d_DAC[3])
                .arg(pScanSpecial_Param->d_DAC[4]).arg(pScanSpecial_Param->d_DAC[5]).arg(pScanSpecial_Param->d_DAC[6])
                .arg(pScanSpecial_Param->d_DAC[7]).arg(pScanSpecial_Param->d_DAC[8]).arg(pScanSpecial_Param->d_DAC[9])
                .arg(pScanSpecial_Param->d_DAC[10]).arg(pScanSpecial_Param->d_DAC[11]).arg(pScanSpecial_Param->ui_DIO)
                .arg(pScanSpecial_Param->d_Precursor_Mass).arg(pScanSpecial_Param->d_msPrecursorOrig).arg(pScanSpecial_Param->d_Forward_Scan_Precursor_Offset)
                .arg(pScanSpecial_Param->d_Mass_End_Th).arg(pScanSpecial_Param->d_msEndOrig);
        break;}
        default:            return QString();                            //
    }
}


