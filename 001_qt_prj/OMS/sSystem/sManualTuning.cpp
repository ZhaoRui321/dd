#include "sManualTuning.h"
#include "ui_sManualTuning.h"
#include <QSettings>
#include <sCommandUSB.h>
#include <tool/Algorithm.h>

void sManualTuning::memoryInit()
{
    mBufferCCS= _FRAME_BUFF_CCS::resize();//mBufferCCS.resize(16 * 1024 * 1024);

    mGraphBuffX= _CHART_X_ACQUIS::get();
    mGraphBuffY= _CHART_Y_ACQUIS::get();

    mList_PEAK= _CHART_PEAK_ACQUIS::get();
}

sManualTuning::sManualTuning(ParamCCS::_DAQ_CONFIG* pDAQ_CONFIG, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sManualTuning),
    mParent(parent),
    mDAQ_CONFIG(pDAQ_CONFIG)
{
    ui->setupUi(this);
    mChartWidget = new sChartWidget(sChartWidget::_NORMAL_CHART);
    ui->UI_LAYOUT_CHART->addWidget(mChartWidget);
    for(int i=0; i<4;++i){
        QPair<sChartWidget*,_Scan_Param> tempPair;
        sChartWidget* tempChart = new sChartWidget(sChartWidget::_NORMAL_CHART);
        tempPair.first= tempChart;
        mChartTarget.append(tempPair);
        ui->UI_LAYOUT_TARGET->addWidget(tempChart,0,i);
    }

    mWidgetCalibration= new sWidgetCalibration();
    mWidgetCalibration->hide();
    ui->UI_LAYOUT_TUNING_METHOD->insertWidget(0, mWidgetCalibration);
    connect(mWidgetCalibration, SIGNAL(Calibrat()), this, SLOT(onCalibrat()));

    mFileDir=new sFileDir(this);
    connect(mFileDir,SIGNAL(selectFile(bool,QString)),this,SLOT(onSelectFile(bool,QString)));
    ui->UI_LAYOUT_FILE->insertWidget(0,mFileDir);
    showWindow(ui->UI_W_CHART);

    memoryInit();
    mAnalyzeThread= new SThread(this);
    mAnalyzeThread->setUserFunction(analyzeThread);
    mAnalyzeThread->setUserParam(this);
    QObject::connect(this,SIGNAL(sUpdateGraph(int)),this,SLOT(onUpdateGraph(int)),Qt::QueuedConnection);

    mDataProcess = sDataProcess::getDataProcess();

    //loadFile(true);

//    //引入时间
//    ui->UI_LE_TIME_I->setRange(0,1);
//    //冷却时间
//    ui->UI_LE_TIME_CO->setRange(0,1);
//    //清空时间
//    ui->UI_LE_TIME_E->setRange(0,2);
//    //质量扫速
//    ui->UI_LE_SPEED->setRange(0,3);
//    //ac相位
//    ui->UI_LE_PHASE_AC->setRange(0,4);
//    //ac占空比
//    ui->UI_LE_DUTYCYCLE_AC->setRange(0,5);
//    //ac幅值
//    ui->UI_LE_VOLT_AC->setRange(0,6);
//    //rf幅值
//    ui->UI_LE_VOLT_RF->setRange(0,7);
//    //前端盖开
//    ui->UI_LE_F_CAP_ON->setRange(0,8);
//    //前端盖闭
//    ui->UI_LE_F_CAP_OFF->setRange(0,9);
//    //后端盖
//    ui->UI_LE_B_CAP->setRange(0,10);
//    //场调节电极
//    ui->UI_LE_FEILD_VOLT->setRange(0,11);
//    //q-array偏置
//    ui->UI_LE_OFFSET_AQRRAY->setRange(0,12);
//    //q-array幅值
//    ui->UI_LE_VOLT_QARRAY->setRange(0,13);
//    //打拿极
//    ui->UI_LE_STARTMASS->setRange(0,14);
//    //倍增器
//    ui->UI_LE_ENDMASS->setRange(0,15);

    connect(ui->UI_LE_B_CAP,SIGNAL(tipSend(int,int)),this,SLOT(onTipSend(int,int)));
    connect(ui->UI_LE_DUTYCYCLE_AC,SIGNAL(tipSend(int,int)),this,SLOT(onTipSend(int,int)));
    connect(ui->UI_LE_STARTMASS,SIGNAL(tipSend(int,int)),this,SLOT(onTipSend(int,int)));
    connect(ui->UI_LE_FEILD_VOLT,SIGNAL(tipSend(int,int)),this,SLOT(onTipSend(int,int)));
    connect(ui->UI_LE_F_CAP_OFF,SIGNAL(tipSend(int,int)),this,SLOT(onTipSend(int,int)));
    connect(ui->UI_LE_F_CAP_ON,SIGNAL(tipSend(int,int)),this,SLOT(onTipSend(int,int)));
    connect(ui->UI_LE_ENDMASS,SIGNAL(tipSend(int,int)),this,SLOT(onTipSend(int,int)));
    connect(ui->UI_LE_OFFSET_AQRRAY,SIGNAL(tipSend(int,int)),this,SLOT(onTipSend(int,int)));
    connect(ui->UI_LE_PHASE_AC,SIGNAL(tipSend(int,int)),this,SLOT(onTipSend(int,int)));
    connect(ui->UI_LE_SPEED,SIGNAL(tipSend(int,int)),this,SLOT(onTipSend(int,int)));
    connect(ui->UI_LE_TIME_CO,SIGNAL(tipSend(int,int)),this,SLOT(onTipSend(int,int)));
    connect(ui->UI_LE_TIME_E,SIGNAL(tipSend(int,int)),this,SLOT(onTipSend(int,int)));
    connect(ui->UI_LE_TIME_I,SIGNAL(tipSend(int,int)),this,SLOT(onTipSend(int,int)));
    connect(ui->UI_LE_VOLT_AC,SIGNAL(tipSend(int,int)),this,SLOT(onTipSend(int,int)));
    connect(ui->UI_LE_VOLT_QARRAY,SIGNAL(tipSend(int,int)),this,SLOT(onTipSend(int,int)));
    connect(ui->UI_LE_VOLT_RF,SIGNAL(tipSend(int,int)),this,SLOT(onTipSend(int,int)));
}

sManualTuning::~sManualTuning()
{
    stop();
    delete ui;
}

int sManualTuning::analyzeThread(void *pParam, const bool &bRunning)
{
    sManualTuning* pManualTuning = (sManualTuning*)pParam;
    CommandUSB* pCommandUSB= sCommandUSB::getCommandUSB();
    if(pManualTuning&& pCommandUSB){
        bool isRestart=true;
        QList<std::vector<double>>* mThreadBuffY= _DAQ_Y_ACQUIS::get();
        QList<std::vector<double>>* mThreadBuffX= _DAQ_X_ACQUIS::get();
        _STRUCT_PEAK* pSTRUCT_PEAK=_PEAK_THREAD_ACQUIS::get();
        QList<_STRUCT_DATA> listSTRUCT_DATA;
        if(pManualTuning->mBaseLine == nullptr)
            pManualTuning->mBaseLine = new QList<std::vector<double>>();
        QByteArray mSegmentGraph(pManualTuning->getSegment());
        cParamValue::_Segment* pSegmentLIT= pManualTuning->getSegmentParam(&mSegmentGraph);
        while(bRunning){
            if(pCommandUSB->getDataDAQ(pManualTuning->mGraphBuffer)!= -1 && !pManualTuning->mGraphBuffer.isEmpty()){
                if(!pManualTuning->dataDismantle(pManualTuning->mGraphBuffer))
                    continue;

                if(pManualTuning->updateGraph(pManualTuning->mGraphBuffer, pSegmentLIT,
                                              mThreadBuffX, mThreadBuffY, listSTRUCT_DATA,isRestart)==0)
                    continue;
                uint countEvt= listSTRUCT_DATA.size();
                if(countEvt==0)
                    continue;
                for(uint currentEvt=0;currentEvt<countEvt;currentEvt++){
                    _STRUCT_DATA* pSTRUCT_DATA= &(listSTRUCT_DATA[currentEvt]);

                    if(!pManualTuning->AnalyzeScan((*mThreadBuffX)[currentEvt].data(),//(*(pManualTuning->mThreadBuffX)).data(),
                                                   (*mThreadBuffY)[currentEvt].data(),
                                                   *pSTRUCT_DATA, currentEvt, countEvt, *pSTRUCT_PEAK, 8)){
                        qDebug()<<"E_MemoryOverflow";
                        return 0;
                    }
                }
                isRestart=false;
                if(pSegmentLIT->type==cParamValue::Type_LIT_FULL)
                    emit pManualTuning->sUpdateGraph(-1);
                else
                    emit pManualTuning->sUpdateGraph(pSegmentLIT->sumEvent);
            }
            QThread::usleep(100);
        }
        mThreadBuffX->clear();
        mThreadBuffY->clear();
    }
    return 0;
}

void sManualTuning::onUpdateGraph(int type)
{
    if(type==-1){
        if(mGraphBuffMutex.tryLock(50)){
            mChartWidget->SetMarker((*mList_PEAK)[0].Absc,(*mList_PEAK)[0].Ord,(*mList_PEAK)[0].Marker);
            mChartWidget->setSamples((*mGraphBuffX)[0], (*mGraphBuffY)[0]);
            mGraphBuffMutex.unlock();
        }
    }else{
        if(mChartTarget.size()!= type){
            qDebug()<<"E_sManualTuning_onUpdateGraph";
            return;
        }
        if(mGraphBuffMutex.tryLock(50)){
            for(int i=0; i< type; i++){
                mChartTarget[i].first->SetMarker((*mList_PEAK)[i].Absc,(*mList_PEAK)[i].Ord,(*mList_PEAK)[i].Marker);
                mChartTarget[i].first->setSamples((*mGraphBuffX)[i], (*mGraphBuffY)[i]);
            }
            mGraphBuffMutex.unlock();
        }
    }
}

bool sManualTuning::startDataAcquisiton(QByteArray& pSegment)
{
    if(pSegment.isEmpty())
        return false;
    cParamValue::_Segment* tempP = (cParamValue::_Segment*)pSegment.data();
    if(tempP->type==cParamValue::Type_LIT_TARGET){
        if(tempP->sumEvent > mChartTarget.size())
            return false;
        for(int i=0;i<tempP->sumEvent;++i){
            cParamValue::_EventLIT* pEvent= (cParamValue::_EventLIT*)
                    (((char*)(&(tempP->fisrtEvent)))+sizeof(cParamValue::_EventLIT)*i);
            if(!pEvent)
                return false;
            mChartTarget[i].first->setStyleM(TVPlot::Lines, "",pEvent->msStartOrig, pEvent->msEndOrig);
        }
        mAnalyzeThread->start();
        return true;
    }else if(tempP->type==cParamValue::Type_LIT_FULL){
        cParamValue::_EventLIT* pEvent= (cParamValue::_EventLIT*)&(tempP->fisrtEvent);
        if(pEvent){
            mChartWidget->setStyleM(TVPlot::Lines, "",pEvent->msStartOrig, pEvent->msEndOrig);
            mAnalyzeThread->start();
            return true;
        }
    }
    return false;
}

void sManualTuning::on_UI_PB_TUNING_SCAN_clicked()
{
    if(state){
        emit stopTuning();
        ui->UI_PB_TUNING_SCAN->setText("执行");
        state = false;
    }else{

        ui->UI_PB_TUNING_SCAN->setText("停止");
        int LengthMS=0;
        if(!saveFile())
            return;
        bool isFullScan= !ui->UI_W_CHART->isHidden();
        if(createMethodScan(LengthMS, isFullScan)){
            if(LengthMS>0){
                emit StartScan(mBufferCCS->data(), LengthMS, mSegment);
            }
        }
        state = true;
    }
}

bool sManualTuning::AnalyzeScan(double* pX, double* pY, _STRUCT_DATA& pSTRUCT_DATA,
                                int currentEvt, int countEvt, _STRUCT_PEAK& pSTRUCT_PEAK,uint uWidth)
{
    _STRUCT_PEAK tempSTRUCT_PEAK;
    vector<int> tmpMarker(pSTRUCT_DATA.uEventPoint);
    for(uint ii=0; ii<pSTRUCT_DATA.uEventPoint; ii++)
        tmpMarker[ii]=ii;
    QVector<double> tempX(pSTRUCT_DATA.uEventPoint);
    QVector<double> tempY(pSTRUCT_DATA.uEventPoint);
    QVector<double> pData;
    QVector<int> pMark;
    QVector<QString> strMarker;
    memcpy(tempX.data(), pX+pSTRUCT_DATA.uPrePoint, pSTRUCT_DATA.uEventPoint*sizeof(double));
    memcpy(tempY.data(), pY+pSTRUCT_DATA.uPrePoint, pSTRUCT_DATA.uEventPoint*sizeof(double));
    Algorithm* temp = Algorithm::getInstance();

    if(1){//Algorithm::getInstance()->getResult(pData,tempY,pMark) != 1){
        uWidth = 0;
    }
    uWidth = pMark.size();
    for(int i = 0; i< uWidth; i++){
        int peakPoint = pMark[i];
        tempSTRUCT_PEAK.Absc.push_back(tempX[peakPoint]);
        tempSTRUCT_PEAK.Ord.push_back(tempY[peakPoint]);
        strMarker.append(QString::number(tempX[peakPoint]));
    }

    mGraphBuffMutex.lock();
    while(mGraphBuffX->size()> countEvt){
        mGraphBuffX->removeLast();
        mGraphBuffY->removeLast();
        mList_PEAK->removeLast();
    }
    while(mGraphBuffX->size()< countEvt){
        mGraphBuffX->append(std::vector<double>(0));
        mGraphBuffY->append(std::vector<double>(0));
        mList_PEAK->append(_STRUCT_GRAPH(0));
    }
    if(!(vectorOperate::Resize((*mGraphBuffX)[currentEvt],pSTRUCT_DATA.uEventPoint)
         &&vectorOperate::Resize((*mGraphBuffY)[currentEvt],pSTRUCT_DATA.uEventPoint)))
        return false;

    if(!(vectorOperate::Resize((*mList_PEAK)[currentEvt].Absc, uWidth)
         &&vectorOperate::Resize((*mList_PEAK)[currentEvt].Ord, uWidth)))
        return false;
    std::copy(tempX.begin(),tempX.end(),(*mGraphBuffX)[currentEvt].begin());//std::copy(tempX.begin(),tempX.end(),mGraphBuff[0]->begin()+nOffsetBuff);
    std::copy(tempY.begin(),tempY.end(),(*mGraphBuffY)[currentEvt].begin());//std::copy(tempY.begin(),tempY.end(),mGraphBuff[1]->begin()+nOffsetBuff);

    if(uWidth>0){
        std::copy(tempSTRUCT_PEAK.Absc.begin(),tempSTRUCT_PEAK.Absc.end(),(*mList_PEAK)[currentEvt].Absc.begin());
        std::copy(tempSTRUCT_PEAK.Ord.begin(),tempSTRUCT_PEAK.Ord.end(),(*mList_PEAK)[currentEvt].Ord.begin());
        (*mList_PEAK)[currentEvt].Marker = strMarker;
    }
    mGraphBuffMutex.unlock();
    return true;
}

bool sManualTuning::dataDismantle(QByteArray& pByteArray)
{
    if(pByteArray.size() < (int)sizeof(_StreamBody))
        return false;
    uint uAllPoint = (pByteArray.size() - sizeof(_StreamBody)) / sizeof(double);
    double* pdbHead = (double*)(pByteArray.data());
    double* pdbOffset = (double*)(pByteArray.data() + sizeof(_StreamBody));
    for(int i=0; i<uAllPoint; i++){
        *pdbHead= *pdbOffset;
        pdbHead++;
        pdbOffset++;
    }
    pByteArray.resize(uAllPoint*sizeof(double));
    return true;
}

uint sManualTuning::updateGraph(QByteArray& pByteArray, cParamValue::_Segment* pSegment,
                                QList<std::vector<double>>* pListX, QList<std::vector<double>>* pListY,
                                QList<_STRUCT_DATA>& pSTRUCT_DATA,bool isRestart)
{
    if(pByteArray.isEmpty()||(pSegment==nullptr)||(pListY==nullptr))
        return 0;
    cParamValue::_EventLIT* pEventLIT= (cParamValue::_EventLIT*)&(pSegment->fisrtEvent);
    if(pEventLIT==nullptr)
        return 0;
    double dbEvtTimeSum= 0;//pEventLIT->holdTime;
    for(int i=0;i<pSegment->sumEvent;i++)
        dbEvtTimeSum+= ((cParamValue::_EventLIT*)((int*)pEventLIT+ sizeof(cParamValue::_EventLIT)/sizeof(int)*i))->holdTime;
    if(dbEvtTimeSum< 0.0000001)
        return 0;

    if(pListY->size()!=pSegment->sumEvent){
        mBaseLine->clear();
        pListY->clear();
        pListX->clear();
        for(uint i=0;i<pSegment->sumEvent;i++){
            mBaseLine->append(std::vector<double>(0));
            pListY->append(std::vector<double>(0));
            pListX->append(std::vector<double>(0));
        }
    }

    if(isRestart){
        pSTRUCT_DATA.clear();
        for(int currentEvt = 0; currentEvt<pSegment->sumEvent;currentEvt++){
            pSTRUCT_DATA.append(_STRUCT_DATA());
        }
    }

    double dbEvtTime;
    uint uAllPoint = pByteArray.size() / sizeof(double);
    double* pdbOffset = (double*)(pByteArray.data());
    for(uint currentEvt=0;currentEvt<pSegment->sumEvent;currentEvt++){
        pEventLIT=((cParamValue::_EventLIT*)((int*)&(pSegment->fisrtEvent)+ sizeof(cParamValue::_EventLIT)/sizeof(int)*currentEvt));
        _STRUCT_DATA* tempSTRUCT_DATA = &(pSTRUCT_DATA[currentEvt]);
        tempSTRUCT_DATA->uPrePoint = (uint)(pEventLIT->preReadyTime * uAllPoint /dbEvtTimeSum);
        tempSTRUCT_DATA->uPostPoint = (uint)(pEventLIT->postReadyTime * uAllPoint /dbEvtTimeSum);
        dbEvtTime=pEventLIT->holdTime;
        tempSTRUCT_DATA->uEvtValidPoint = (uint)(dbEvtTime * uAllPoint / dbEvtTimeSum);
        tempSTRUCT_DATA->uEventPoint= tempSTRUCT_DATA->uEvtValidPoint- tempSTRUCT_DATA->uPrePoint- tempSTRUCT_DATA->uPostPoint;

        if((!vectorOperate::Resize((*pListY)[currentEvt],tempSTRUCT_DATA->uEvtValidPoint))
            ||(!vectorOperate::Resize((*pListX)[currentEvt],tempSTRUCT_DATA->uEvtValidPoint))
                ||(!vectorOperate::Resize((*mBaseLine)[currentEvt],tempSTRUCT_DATA->uEvtValidPoint)))
                return 0;
        memcpy((*pListY)[currentEvt].data(), pdbOffset, tempSTRUCT_DATA->uEvtValidPoint* sizeof(double));

        if(isRestart){
            double* pFirst= (*pListX)[currentEvt].data();
            double* pLast= pFirst+ tempSTRUCT_DATA->uEvtValidPoint-1;
            double tempStart= pEventLIT->msStart- pEventLIT->msPrecursor,
                    tempEnd=pEventLIT->msEnd+ pEventLIT->msPrecursor;
            double* mBaseLineFirst = (*mBaseLine)[currentEvt].data();


            if(mCALIBRATE.changed){
                calibration(pFirst, pLast, mBaseLineFirst, tempStart, (tempEnd - tempStart) / tempSTRUCT_DATA->uEvtValidPoint);
            }else{
                if((tempStart- *pFirst> 1e-6)|| (tempStart- *pFirst< -1e-6)
                        ||(tempEnd- *pLast> 1e-6)|| (tempEnd- *pLast< -1e-6)){
                    calibration(pFirst, pLast, mBaseLineFirst, tempStart, (tempEnd - tempStart) / tempSTRUCT_DATA->uEvtValidPoint);

                }
            }
        }
        //qDebug() << "总点数:" << tempSTRUCT_DATA->uEvtValidPoint;
        for(int i = 0 ; i<tempSTRUCT_DATA->uEvtValidPoint; i++){
//            if((*pListY)[currentEvt][i] >0 || (*pListY)[currentEvt][i] < -0.5)
//                qDebug() << "第"  << i << "点:" << (*pListY)[currentEvt][i];
            (*pListY)[currentEvt][i] = (*pListY)[currentEvt][i] + (*mBaseLine)[currentEvt][i];
        }

        if(!mDataProcess->getData((*pListY)[currentEvt],(*pListY)[currentEvt],isRestart))
            return 0;
        pdbOffset += tempSTRUCT_DATA->uEvtValidPoint;
    }
    return uAllPoint;
}

bool sManualTuning::loadFile(bool ifUpdateUI, QString qPath)
{
    QString path;
    if(qPath.isEmpty())
        path = filePath+"/tuning.ini";
        //path = ".\tuning.ini";
    else
        path = qPath;
    QSettings configIniRead(path, QSettings::IniFormat);
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

    if(ifUpdateUI){
        tmpStr = configIniRead.value("/FIT/PolyFit","").toString();
        tmpList= tmpStr.split("&");
        tmpStr = configIniRead.value("/AdjustLIT/MassExtension","2").toString();
        mAdjustFactor.d_Mass_Forward_Extension= tmpStr.toDouble();
        if(tmpList.size()== 5){
            mCALIBRATE.mPARAM_FIT.enable= tmpList[0].toUInt();
            QStringList tempCurrent= tmpList[1].split("@");
            QStringList tempExpect= tmpList[2].split("@");
            QStringList tempCF= tmpList[3].split("@");
            QStringList tempCB= tmpList[4].split("@");
            if((tempCurrent.size()==6)&& (tempExpect.size()==6)){
                mCALIBRATE.lock();
                mCALIBRATE.mPARAM_FIT.current.clear();
                mCALIBRATE.mPARAM_FIT.expect.clear();
                mCALIBRATE.mPARAM_FIT.coefF.clear();
                mCALIBRATE.mPARAM_FIT.coefB.clear();
                foreach (QString var, tempCurrent)
                    mCALIBRATE.mPARAM_FIT.current.push_back(var);
                foreach (QString var, tempExpect)
                    mCALIBRATE.mPARAM_FIT.expect.push_back(var);
                foreach (QString var, tempCF)
                    mCALIBRATE.mPARAM_FIT.coefF.push_back(var.toDouble());
                foreach (QString var, tempCB)
                    mCALIBRATE.mPARAM_FIT.coefB.push_back(var.toDouble());
                mWidgetCalibration->updateParam(mCALIBRATE.mPARAM_FIT,tmpStr);
                mCALIBRATE.unlock();
            }
            qDebug() << mCALIBRATE.mPARAM_FIT.coefF[5];
            qDebug() << mCALIBRATE.mPARAM_FIT.coefF[4];
            qDebug() << mCALIBRATE.mPARAM_FIT.coefF[3];
            qDebug() << mCALIBRATE.mPARAM_FIT.coefF[2];
            qDebug() << mCALIBRATE.mPARAM_FIT.coefF[1];
            qDebug() << mCALIBRATE.mPARAM_FIT.coefF[0];
            qDebug() << "---------------------------- ";
            for(int i = 0 ; i < 6 ; i++){
                double temp = mCALIBRATE.mPARAM_FIT.current.at(i).toDouble();
                double res1 = pow(temp, 5) * mCALIBRATE.mPARAM_FIT.coefF[5]
                        + pow(temp, 4) * mCALIBRATE.mPARAM_FIT.coefF[4]
                        + pow(temp, 3) * mCALIBRATE.mPARAM_FIT.coefF[3]
                        + pow(temp, 2) * mCALIBRATE.mPARAM_FIT.coefF[2]
                        + temp * mCALIBRATE.mPARAM_FIT.coefF[1]
                        + mCALIBRATE.mPARAM_FIT.coefF[0];
                qDebug() << res1;
            }
            qDebug() << "---------------------------- ";

        }

        tmpStr = configIniRead.value("/ManualTuning/MassTarget", "50&100&150&200").toString();
        tmpList= tmpStr.split("&");
        if(tmpList.size()== 4){
            ui->UI_LE_MASS0->setText(tmpList[0]);
            ui->UI_LE_MASS1->setText(tmpList[1]);
            ui->UI_LE_MASS2->setText(tmpList[2]);
            ui->UI_LE_MASS3->setText(tmpList[3]);
        }
        Algorithm::getInstance()->setDataOffset(configIniRead.value("/ALgorithm/DataOffset",0.1).toDouble());
        Algorithm::getInstance()->setBaseLineOffset(configIniRead.value("/Algorithm/BaseLineOffset",0.005).toDouble());

        ui->UI_LE_TIME_I->setText(configIniRead.value("/FullScanInjection/Time", "100").toString());
        ui->UI_LE_TIME_CO->setText(configIniRead.value("/FullScanCooling/Time", "50").toString());
        ui->UI_LE_TIME_E->setText(configIniRead.value("/FullScanEmpty/Time", "50").toString());
        ui->UI_LE_SPEED->setText(configIniRead.value("/FullScanScan/ScanSpeed", "1000").toString());

        ui->UI_LE_PHASE_AC->setText(configIniRead.value("/LIT/PhaseAC", "0").toString());
        ui->UI_LE_DUTYCYCLE_AC->setText(configIniRead.value("/LIT/DutyCycleAC", "0").toString());
        ui->UI_LE_VOLT_AC->setText(configIniRead.value("/LIT/VoltageAC", "0").toString());
        ui->UI_LE_VOLT_RF->setText(configIniRead.value("/LIT/VoltageRF", "0").toString());

        ui->UI_LE_F_CAP_ON->setText(configIniRead.value("/LIT/FrontCapOn", "0").toString());
        ui->UI_LE_F_CAP_OFF->setText(configIniRead.value("/LIT/FrontCapOff", "0").toString());
        ui->UI_LE_B_CAP->setText(configIniRead.value("/LIT/BackCap", "0").toString());
        ui->UI_LE_FEILD_VOLT->setText(configIniRead.value("/LIT/FeildVoltage", "0").toString());

        ui->UI_LE_OFFSET_AQRRAY->setText(configIniRead.value("/LIT/OffsetQArray", "0").toString());
        ui->UI_LE_VOLT_QARRAY->setText(configIniRead.value("/LIT/VoltQArray", "0").toString());
        temp_FAE = configIniRead.value("/LIT/FAE", "0").toString();
        temp_OrificeBias = configIniRead.value("/LIT/OrificeBias", "0").toString();
        ui->UI_LE_STARTMASS->setText(configIniRead.value("/FullScanScan/MassStart", "100").toString());
        ui->UI_LE_ENDMASS->setText(configIniRead.value("/FullScanScan/MassEnd", "1000").toString());
    }
    tmpStr = configIniRead.value("/FullScanLIT/MethodArray", "Injection&Cooling&Scan&Empty").toString();
    //tmpStr = configIniRead.value("/Filter/FilterArray", "Injection&Cooling&Scan&Empty").toString();

    //mInjectionFullScan.d_Time=              configIniRead.value("/FullScanInjection/Time", "100").toDouble();
    mInjectionFullScan.d_Mass_Start_Th=		configIniRead.value("/FullScanScan/MassStart", "100").toDouble();
    mInjectionFullScan.d_msStartOrig = mInjectionFullScan.d_Mass_Start_Th;
    mInjectionFullScan.d_Mass_End_Th = configIniRead.value("/FullScanScan/MassEnd", "100").toDouble();
    mInjectionFullScan.d_msEndOrig = mInjectionFullScan.d_Mass_End_Th;
    mInjectionFullScan.i_DDSDuration=       configIniRead.value("/FullScanInjection/DDSDuration", "64").toInt();
    mInjectionFullScan.i_DDSADelay=         configIniRead.value("/FullScanInjection/DDSADelay", "0").toInt();
    mInjectionFullScan.i_DDSADuty=          configIniRead.value("/FullScanInjection/DDSADuty", "0").toInt();
    mInjectionFullScan.i_DDSBDelay=         configIniRead.value("/FullScanInjection/DDSBDelay", "16").toInt();
    mInjectionFullScan.i_DDSBDuty=          configIniRead.value("/FullScanInjection/DDSBDuty", "48").toInt();
    mInjectionFullScan.d_Qarray_RF_Step=    configIniRead.value("/FullScanInjection/d_Qarray_RF_Step", "10").toInt();
    mInjectionFullScan.d_Qarray_RF_FactorA= configIniRead.value("/FullScanInjection/d_Qarray_RF_FactorA", "0.167").toDouble();
    mInjectionFullScan.d_Qarray_RF_FactorB= configIniRead.value("/FullScanInjection/d_Qarray_RF_FactorB", "33.333").toDouble();
    mInjectionFullScan.VoltageRFOffset=     configIniRead.value("/FullScanInjection/VoltageRFOffset", "10").toDouble();

    //mCoolingFullScan.d_Time=                configIniRead.value("/FullScanCooling/Time", "50").toDouble();
    mCoolingFullScan.d_Mass_Start_Th=       configIniRead.value("/FullScanCooling/MassStart", "40").toDouble();
    mCoolingFullScan.d_msStartOrig = mCoolingFullScan.d_Mass_Start_Th;
    mCoolingFullScan.i_DDSDuration=         configIniRead.value("/FullScanCooling/DDSDuration", "64").toInt();
    mCoolingFullScan.i_DDSADelay=           configIniRead.value("/FullScanCooling/DDSADelay", "0").toInt();
    mCoolingFullScan.i_DDSADuty=            configIniRead.value("/FullScanCooling/DDSADuty", "0").toInt();
    mCoolingFullScan.i_DDSBDelay=           configIniRead.value("/FullScanCooling/DDSBDelay", "16").toInt();
    mCoolingFullScan.i_DDSBDuty=            configIniRead.value("/FullScanCooling/DDSBDuty", "48").toInt();

    mScanFullScan.d_Mass_Start_Th=          configIniRead.value("/FullScanScan/MassStart", "40").toDouble();
    mScanFullScan.d_msStartOrig = mInjectionFullScan.d_Mass_Start_Th;
    mScanFullScan.d_Mass_End_Th=            configIniRead.value("/FullScanScan/MassEnd", "300").toDouble();
    mScanFullScan.d_msEndOrig = mInjectionFullScan.d_Mass_End_Th;
    //mScanFullScan.d_Scan_Speed=             configIniRead.value("/FullScanScan/ScanSpeed", "1000.0").toDouble();
    mScanFullScan.d_Precursor_Mass=         configIniRead.value("/FullScanScan/PrecursorMass", "152").toDouble();
    mScanFullScan.d_Forward_Scan_Precursor_Offset=configIniRead.value("/FullScanScan/ForwardPrecursorOffset", "-0.2").toDouble();
    mScanFullScan.i_DDSDuration=            configIniRead.value("/FullScanScan/DDSDuration", "192").toInt();
    //mScanFullScan.i_DDSADelay=              configIniRead.value("/FullScanScan/DDSADelay", "5").toInt();
    //mScanFullScan.i_DDSADuty=               configIniRead.value("/FullScanScan/DDSADuty", "53").toInt();
    mScanFullScan.i_DDSBDelay=              configIniRead.value("/FullScanScan/DDSBDelay", "16").toInt();
    mScanFullScan.i_DDSBDuty=               configIniRead.value("/FullScanScan/DDSBDuty", "48").toInt();

    //mEmptyFullScan.d_Time=                  configIniRead.value("/FullScanEmpty/Time", "50").toDouble();
    mEmptyFullScan.d_Mass_Start_Th=         configIniRead.value("/FullScanEmpty/MassStart", "40").toDouble();
    mEmptyFullScan.d_msStartOrig = mInjectionFullScan.d_Mass_Start_Th;
    mEmptyFullScan.d_Mass_End_Th=           configIniRead.value("/FullScanEmpty/MassEnd", "300").toDouble();
    mEmptyFullScan.d_msEndOrig = mInjectionFullScan.d_Mass_End_Th;
    mEmptyFullScan.i_DDSDuration=           configIniRead.value("/FullScanEmpty/DDSDuration", "64").toInt();
    mEmptyFullScan.i_DDSADelay=             configIniRead.value("/FullScanEmpty/DDSADelay", "0").toInt();
    mEmptyFullScan.i_DDSADuty=              configIniRead.value("/FullScanEmpty/DDSADuty", "0").toInt();
    mEmptyFullScan.i_HVHF_DutyCycle_DDS=    configIniRead.value("/FullScanEmpty/HVHFDutyCycleDDS", "28").toInt();
}

bool sManualTuning::saveFile(QString qPath)
{
    QString path;
    if(qPath.isEmpty())
        path = filePath+"/tuning.ini";
    else
        path = qPath;

    QSettings configIniWrite(path, QSettings::IniFormat);

    configIniWrite.setValue("/AdjustLIT/MassScale",QString::number(mAdjustFactor.d_Mass_Scale_Factor));
    configIniWrite.setValue("/AdjustLIT/MassOffset",QString::number(mAdjustFactor.d_Mass_Offset_Factor));
    configIniWrite.setValue("/AdjustLIT/MassExtension",QString::number(mAdjustFactor.d_Mass_Forward_Extension));
    QString tempStr1= QString::null,tempStr2= QString::null;
    for(int i=0; i<12; i++){
        if(i==11){
            tempStr1+= QString::number(mAdjustFactor.d_DACGain[i]);
            tempStr2+= QString::number(mAdjustFactor.d_DACOffset[i]);
        }else{
            tempStr1+= QString::number(mAdjustFactor.d_DACGain[i])+"&";
            tempStr2+= QString::number(mAdjustFactor.d_DACOffset[i])+"&";
        }
    }
    configIniWrite.setValue("/AdjustLIT/DACGain",tempStr1);
    configIniWrite.setValue("/AdjustLIT/DACOffset",tempStr2);

//    _CONGIG_OMS::_PARAM_FIT tempPARAM_FIT;
//    mWidgetCalibration->getParam(tempPARAM_FIT);
    configIniWrite.setValue("/ManualTuning/MassTarget", ui->UI_LE_MASS0->text()+'&'
                            +ui->UI_LE_MASS1->text()+'&'
                            +ui->UI_LE_MASS2->text()+'&'
                            +ui->UI_LE_MASS3->text());

    configIniWrite.setValue("/FIT/PolyFit", strCalibratP(mCALIBRATE.mPARAM_FIT));

    configIniWrite.setValue("/FullScanInjection/Time",ui->UI_LE_TIME_I->text());
    configIniWrite.setValue("/FullScanCooling/Time",ui->UI_LE_TIME_CO->text());
    configIniWrite.setValue("/FullScanEmpty/Time",ui->UI_LE_TIME_E->text());
    configIniWrite.setValue("/FullScanScan/ScanSpeed",ui->UI_LE_SPEED->text());

    configIniWrite.setValue("/LIT/PhaseAC",ui->UI_LE_PHASE_AC->text());
    configIniWrite.setValue("/LIT/DutyCycleAC",ui->UI_LE_DUTYCYCLE_AC->text());
    configIniWrite.setValue("/LIT/VoltageAC",ui->UI_LE_VOLT_AC->text());
    configIniWrite.setValue("/LIT/VoltageRF",ui->UI_LE_VOLT_RF->text());

    configIniWrite.setValue("/LIT/FrontCapOn",ui->UI_LE_F_CAP_ON->text());
    configIniWrite.setValue("/LIT/FrontCapOff",ui->UI_LE_F_CAP_OFF->text());
    configIniWrite.setValue("/LIT/BackCap",ui->UI_LE_B_CAP->text());
    configIniWrite.setValue("/LIT/FeildVoltage",ui->UI_LE_FEILD_VOLT->text());

    configIniWrite.setValue("/LIT/OffsetQArray",ui->UI_LE_OFFSET_AQRRAY->text());
    configIniWrite.setValue("/LIT/VoltQArray",ui->UI_LE_VOLT_QARRAY->text());
    configIniWrite.setValue("/FullScanScan/MassStart",ui->UI_LE_STARTMASS->text());
    configIniWrite.setValue("/FullScanScan/MassEnd",ui->UI_LE_ENDMASS->text());
    configIniWrite.setValue("/LIT/FAE",temp_FAE);
    configIniWrite.setValue("/LIT/OrificeBias",temp_OrificeBias);

    configIniWrite.setValue("/FullScanLIT/MethodArray", "Injection&Cooling&Scan&Empty");

    //mInjectionFullScan.d_Time=              configIniRead.value("/FullScanInjection/Time", "100").toDouble();
    configIniWrite.setValue("/FullScanInjection/MassStart",QString::number(mInjectionFullScan.d_msStartOrig));
    configIniWrite.setValue("/FullScanInjection/MassEnd",QString::number(mInjectionFullScan.d_msEndOrig));
    configIniWrite.setValue("/FullScanInjection/DDSDuration",QString::number(mInjectionFullScan.i_DDSDuration));
    configIniWrite.setValue("/FullScanInjection/DDSADelay",QString::number(mInjectionFullScan.i_DDSADelay));
    configIniWrite.setValue("/FullScanInjection/DDSADuty",QString::number(mInjectionFullScan.i_DDSADuty));
    configIniWrite.setValue("/FullScanInjection/DDSBDelay",QString::number(mInjectionFullScan.i_DDSBDelay));
    configIniWrite.setValue("/FullScanInjection/DDSBDuty",QString::number(mInjectionFullScan.i_DDSBDuty));

    //mCoolingFullScan.d_Time=                configIniRead.value("/FullScanCooling/Time", "50").toDouble();
    configIniWrite.setValue("/FullScanCooling/MassStart",QString::number(mCoolingFullScan.d_msStartOrig));
    configIniWrite.setValue("/FullScanCooling/DDSDuration",QString::number(mCoolingFullScan.i_DDSDuration));
    configIniWrite.setValue("/FullScanCooling/DDSADelay",QString::number(mCoolingFullScan.i_DDSADelay));
    configIniWrite.setValue("/FullScanCooling/DDSADuty",QString::number(mCoolingFullScan.i_DDSADuty));
    configIniWrite.setValue("/FullScanCooling/DDSBDelay",QString::number(mCoolingFullScan.i_DDSBDelay));
    configIniWrite.setValue("/FullScanCooling/DDSBDuty",QString::number(mCoolingFullScan.i_DDSBDuty));

    configIniWrite.setValue("/FullScanScan/MassStart",QString::number(mScanFullScan.d_msStartOrig));
    configIniWrite.setValue("/FullScanScan/MassEnd",QString::number(mScanFullScan.d_msEndOrig));
    //mScanFullScan.d_Scan_Speed=             configIniRead.value("/FullScanScan/ScanSpeed", "1000.0").toDouble();
    configIniWrite.setValue("/FullScanScan/PrecursorMass",QString::number(mScanFullScan.d_Precursor_Mass));
    configIniWrite.setValue("/FullScanScan/ForwardPrecursorOffset",QString::number(mScanFullScan.d_Forward_Scan_Precursor_Offset));
    configIniWrite.setValue("/FullScanScan/DDSDuration",QString::number(mScanFullScan.i_DDSDuration));
    //mScanFullScan.i_DDSADelay=              configIniRead.value("/FullScanScan/DDSADelay", "5").toInt();
    //mScanFullScan.i_DDSADuty=               configIniRead.value("/FullScanScan/DDSADuty", "53").toInt();
    configIniWrite.setValue("/FullScanScan/DDSBDelay",QString::number(mScanFullScan.i_DDSBDelay));
    configIniWrite.setValue("/FullScanScan/DDSBDuty",QString::number(mScanFullScan.i_DDSBDuty));

    //mEmptyFullScan.d_Time=                  configIniRead.value("/FullScanEmpty/Time", "50").toDouble();
    configIniWrite.setValue("/FullScanEmpty/MassStart",QString::number(mEmptyFullScan.d_msStartOrig));
    configIniWrite.setValue("/FullScanEmpty/MassEnd",QString::number(mEmptyFullScan.d_msEndOrig));
    configIniWrite.setValue("/FullScanEmpty/DDSDuration",QString::number(mEmptyFullScan.i_DDSDuration));
    configIniWrite.setValue("/FullScanEmpty/DDSADelay",QString::number(mEmptyFullScan.i_DDSADelay));
    configIniWrite.setValue("/FullScanEmpty/DDSADuty",QString::number(mEmptyFullScan.i_DDSADuty));
    configIniWrite.setValue("/FullScanEmpty/HVHFDutyCycleDDS",QString::number(mEmptyFullScan.i_HVHF_DutyCycle_DDS));
    return true;
}

bool sManualTuning::createMethodScan(int& LengthMS, bool isFullScan)
{
    if(!loadFile())
        return false;
    if(!getParam(mInjectionFullScan)|| !getParam(mCoolingFullScan)|| !getParam(mScanFullScan)|| !getParam(mEmptyFullScan))
        return false;
    mMethod.InitState(&mAdjustFactor,QCoreApplication::applicationDirPath()+"/PTMSCONFIG.ini");     //每次都需要初始化 
    proInjectionFullScan = mInjectionFullScan;
    proInjectionFullScan.d_Time = 5;
    proInjectionFullScan.d_DAC[10] = ui->UI_LE_F_CAP_OFF->text().toDouble();
    mMethod.AddStage(&proInjectionFullScan);
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
        calibration(mScanFullScan.d_Mass_Start_Th);
        calibration(mScanFullScan.d_Mass_End_Th);
        mMethod.AddStage(&mScanFullScan);          //此处演示的为一个最基本的一级扫描方法
    }else{
        if(mChartTarget.size()<1)
            return false;
        mSegment.resize(sizeof(cParamValue::_Segment) - sizeof(cParamValue::_Event)
                        +sizeof(cParamValue::_EventLIT)*mChartTarget.size());
        getSegmentParam()->type= cParamValue::Type_LIT_TARGET;
        getSegmentParam()->sumEvent = mChartTarget.size();
        memset(getSegmentParam()->title,'\0',30);
        strcpy(getSegmentParam()->title,QString("LIT").toUtf8().data());

        for(int i=0; i<mChartTarget.size(); i++){
            mChartTarget[i].second= mScanFullScan;
            mChartTarget[i].second.pEvent= (cParamValue::_EventLIT*)
                    (((char*)(&(getSegmentParam()->fisrtEvent)))+sizeof(cParamValue::_EventLIT)*i);
            mChartTarget[i].second.pEvent->minTime = 0;
            double tempMass= 0;
            switch (i) {
            case 0:
                tempMass= ui->UI_LE_MASS0->text().toDouble();
                for(int j=0;j<12;j++)
                    mChartTarget[i].second.d_DAC[j]=1;
                break;
            case 1:
                tempMass= ui->UI_LE_MASS1->text().toDouble();
                for(int j=0;j<12;j++)
                    mChartTarget[i].second.d_DAC[j]=2;
                break;
            case 2:
                tempMass= ui->UI_LE_MASS2->text().toDouble();
                for(int j=0;j<12;j++)
                    mChartTarget[i].second.d_DAC[j]=3;
                break;
            case 3:
                tempMass= ui->UI_LE_MASS3->text().toDouble();
                for(int j=0;j<12;j++)
                    mChartTarget[i].second.d_DAC[j]=4;
                break;
            default: break;
            }
            mChartTarget[i].second.d_Mass_Start_Th= tempMass- getConfig()->MassExtension;
            mChartTarget[i].second.d_msStartOrig = mChartTarget[i].second.d_Mass_Start_Th;
            calibration(mChartTarget[i].second.d_Mass_Start_Th);
            if(mChartTarget[i].second.d_Mass_Start_Th<20)
                return false;
            mChartTarget[i].second.d_Mass_End_Th= tempMass+ getConfig()->MassExtension;
            mChartTarget[i].second.d_msEndOrig = mChartTarget[i].second.d_Mass_End_Th;
            calibration(mChartTarget[i].second.d_Mass_End_Th);
            mMethod.AddStage(&(mChartTarget[i].second));
        }
    }
    mMethod.AddStage(&mEmptyFullScan);         //按步骤调用InitState、AddState、CreateMethod，将得到板卡通讯数据

    int nRet,nMSCALEn,methodNO,ID_DataPackage;//MSLength,
    nMSCALEn = LengthMS = methodNO = ID_DataPackage = 0;
    nRet = mMethod.CreateMethod((uchar*)mBufferCCS->data(), &nMSCALEn, &LengthMS, methodNO, ID_DataPackage);

    if(nRet == 0)
        return true;
    return false;
}

bool sManualTuning::getParam(_Injection_Param& pInjection_Param)
{
    pInjection_Param.d_Time= ui->UI_LE_TIME_I->text().toDouble();
    pInjection_Param.d_Mass_Start_Th = ui->UI_LE_STARTMASS->text().toDouble();
    pInjection_Param.d_Mass_End_Th = ui->UI_LE_ENDMASS->text().toDouble();
    pInjection_Param.d_msStartOrig = pInjection_Param.d_Mass_Start_Th;
    pInjection_Param.d_msEndOrig = pInjection_Param.d_Mass_End_Th;

    //if(pInjection_Param.d_Time<0.000004)
    //    return false;

    pInjection_Param.d_DAC[11]=temp_OrificeBias.toDouble();//
    pInjection_Param.d_DAC[8]=0;//
    pInjection_Param.d_DAC[10]=ui->UI_LE_F_CAP_ON->text().toDouble();
    pInjection_Param.d_DAC[9]=ui->UI_LE_B_CAP->text().toDouble();
    pInjection_Param.d_DAC[7]=0;
    pInjection_Param.d_DAC[4]=0;
    pInjection_Param.d_DAC[6]= ui->UI_LE_VOLT_RF->text().toDouble()-mInjectionFullScan.VoltageRFOffset;
    pInjection_Param.d_DAC[5]= ui->UI_LE_VOLT_RF->text().toDouble()+mInjectionFullScan.VoltageRFOffset;//8
    pInjection_Param.d_DAC[3]=ui->UI_LE_VOLT_QARRAY->text().toDouble();
    pInjection_Param.d_DAC[0]= 0;//ui->UI_LE_VOLT_AC->text().toDouble();//VoltageAC
    pInjection_Param.d_DAC[2]= 0;//ui->UI_LE_VOLT_RF->text().toDouble();
    pInjection_Param.d_DAC[1]=ui->UI_LE_OFFSET_AQRRAY->text().toDouble();
    return true;
}

bool sManualTuning::getParam(_Cooling_Param& pCooling_Param)
{
    pCooling_Param.d_Time= ui->UI_LE_TIME_CO->text().toDouble();
    pCooling_Param.d_Mass_Start_Th = ui->UI_LE_STARTMASS->text().toDouble();
    pCooling_Param.d_msStartOrig = pCooling_Param.d_Mass_Start_Th;
    //if(pCooling_Param.d_Time<0.000004)
    //    return false;

    pCooling_Param.d_DAC[11]=temp_OrificeBias.toDouble();//
    pCooling_Param.d_DAC[8]=0;//
    pCooling_Param.d_DAC[10]=ui->UI_LE_F_CAP_OFF->text().toDouble();
    pCooling_Param.d_DAC[9]=ui->UI_LE_B_CAP->text().toDouble();
    pCooling_Param.d_DAC[7]=0;
    pCooling_Param.d_DAC[4]=0;
    pCooling_Param.d_DAC[6]= ui->UI_LE_VOLT_RF->text().toDouble();
    pCooling_Param.d_DAC[5]= ui->UI_LE_VOLT_RF->text().toDouble();//8
    pCooling_Param.d_DAC[3]=ui->UI_LE_VOLT_QARRAY->text().toDouble();
    pCooling_Param.d_DAC[0]= 0;//ui->UI_LE_VOLT_AC->text().toDouble();//VoltageAC
    pCooling_Param.d_DAC[2]= 0;//ui->UI_LE_VOLT_RF->text().toDouble();
    pCooling_Param.d_DAC[1]=ui->UI_LE_OFFSET_AQRRAY->text().toDouble();
    return true;
}

bool sManualTuning::getParam(_Scan_Param& pScan_Param)
{
    pScan_Param.d_Mass_Start_Th = ui->UI_LE_STARTMASS->text().toDouble();
    pScan_Param.d_Mass_End_Th = ui->UI_LE_ENDMASS->text().toDouble();
    pScan_Param.d_msStartOrig = pScan_Param.d_Mass_Start_Th;
    pScan_Param.d_msEndOrig = pScan_Param.d_Mass_End_Th;
    pScan_Param.d_Scan_Speed=ui->UI_LE_SPEED->text().toDouble();
    Algorithm::getInstance()->setSpeed(pScan_Param.d_Scan_Speed);
    double tmpPhase=ui->UI_LE_PHASE_AC->text().toDouble();
    double tmpPercentage= ui->UI_LE_DUTYCYCLE_AC->text().toDouble();
    pScan_Param.i_DDSADelay=(uint)(((double)pScan_Param.i_DDSDuration)* tmpPhase/ 360.0);
    pScan_Param.i_DDSADuty=(uint)(((double)pScan_Param.i_DDSDuration)* tmpPercentage/ 100.0)
            + pScan_Param.i_DDSADelay;

    pScan_Param.d_DAC[11]=temp_OrificeBias.toDouble();//
    pScan_Param.d_DAC[8]=0;//
    pScan_Param.d_DAC[10]=ui->UI_LE_F_CAP_OFF->text().toDouble();
    pScan_Param.d_DAC[9]=ui->UI_LE_B_CAP->text().toDouble();
    pScan_Param.d_DAC[7]=temp_FAE.toDouble();
    pScan_Param.d_DAC[4]=0;
    pScan_Param.d_DAC[6]= ui->UI_LE_VOLT_RF->text().toDouble();
    pScan_Param.d_DAC[5]= ui->UI_LE_VOLT_RF->text().toDouble();//8
    pScan_Param.d_DAC[3]=ui->UI_LE_VOLT_QARRAY->text().toDouble();
    pScan_Param.d_DAC[0]= ui->UI_LE_VOLT_AC->text().toDouble();//VoltageAC
    pScan_Param.d_DAC[2]= 0;//ui->UI_LE_VOLT_RF->text().toDouble();
    pScan_Param.d_DAC[1]=ui->UI_LE_OFFSET_AQRRAY->text().toDouble();
    return true;
}

bool sManualTuning::getParam(_Empty_Param& pEmpty_Param)
{
    pEmpty_Param.d_Time= ui->UI_LE_TIME_E->text().toDouble();
    pEmpty_Param.d_Mass_Start_Th = ui->UI_LE_STARTMASS->text().toDouble();
    pEmpty_Param.d_Mass_End_Th = ui->UI_LE_ENDMASS->text().toDouble();
    pEmpty_Param.d_msStartOrig = pEmpty_Param.d_Mass_Start_Th;
    pEmpty_Param.d_msEndOrig = pEmpty_Param.d_Mass_End_Th;
    //if(pEmpty_Param.d_Time<0.000004)
    //    return false;

    pEmpty_Param.d_DAC[11]=temp_OrificeBias.toDouble();//
    pEmpty_Param.d_DAC[8]=0;//
    pEmpty_Param.d_DAC[10]=ui->UI_LE_F_CAP_OFF->text().toDouble();
    pEmpty_Param.d_DAC[9]=ui->UI_LE_B_CAP->text().toDouble();
    pEmpty_Param.d_DAC[7]=0;
    pEmpty_Param.d_DAC[4]=0;
    pEmpty_Param.d_DAC[6]= ui->UI_LE_VOLT_RF->text().toDouble();
    pEmpty_Param.d_DAC[5]= ui->UI_LE_VOLT_RF->text().toDouble();//8
    pEmpty_Param.d_DAC[3]=ui->UI_LE_VOLT_QARRAY->text().toDouble();
    pEmpty_Param.d_DAC[0]= 0;//ui->UI_LE_VOLT_AC->text().toDouble();//VoltageAC
    pEmpty_Param.d_DAC[2]= 0;//ui->UI_LE_VOLT_RF->text().toDouble();
    pEmpty_Param.d_DAC[1]=ui->UI_LE_OFFSET_AQRRAY->text().toDouble();
    return true;
}

void sManualTuning::on_UI_PB_LOADFILE_clicked()
{
    if(!mFileDir)
        return;
    mFileDir->showFileList(4, mFileDir->getFileNames(filePath));//QCoreApplication::applicationDirPath()+"/tuningDir"));
    ui->E_FILENAME->hide();
    ui->UI_PB_OK->setText("打开");
    showWindow(ui->UI_W_FILE);
}

void sManualTuning::on_UI_PB_SAVEFILE_clicked()
{
    if(!mFileDir)
        return;
    mFileDir->showFileList(4, mFileDir->getFileNames(filePath));//QCoreApplication::applicationDirPath()+"/tuningDir"));
    ui->E_FILENAME->show();
    QString strFormat = "H.m.s-a-yyyy.MMMM.dd";
    QDateTime dateTime = QDateTime::currentDateTime();
    QLocale locale = QLocale::English;
    strFormat= locale.toString(dateTime, strFormat)+".tuning";
    ui->E_FILENAME->setText(strFormat);
    ui->UI_PB_OK->setText("保存");
    showWindow(ui->UI_W_FILE);
}

void sManualTuning::on_UI_PB_OK_clicked()
{
    if(ui->E_FILENAME->isHidden()){
        if(!ui->E_FILENAME->text().isEmpty())
            loadFile(true, filePath + "/" +ui->E_FILENAME->text()+".tuning");
    }else{
        if(!ui->E_FILENAME->text().isEmpty())
            saveFile(filePath + "/" + ui->E_FILENAME->text());
    }

    if(ui->UI_PB_FULL->isEnabled()){
        showWindow(ui->UI_W_CHART);
    }else{
        showWindow(ui->UI_W_TARGET_CHART);
    }
}

void sManualTuning::on_UI_PB_CANCEL_clicked()
{
    if(ui->UI_PB_FULL->isEnabled()){
        showWindow(ui->UI_W_CHART);
    }else{
        showWindow(ui->UI_W_TARGET_CHART);
    }
}

void sManualTuning::onSelectFile(bool isCurrent,QString strFile)
{
    if(!strFile.isEmpty()){
        ui->E_FILENAME->setText(strFile);
    }
}

void sManualTuning::on_UI_PB_TARGET_clicked()
{
    showWindow(ui->UI_W_TARGET_CHART);
}

void sManualTuning::on_UI_PB_FULL_clicked()
{
    showWindow(ui->UI_W_CHART);
}

void sManualTuning::showWindow(QWidget* pWidget)
{
    if(!pWidget)
        return;
    ui->UI_W_FILE->hide();
    ui->UI_W_CHART->hide();
    ui->UI_W_TARGET_CHART->hide();
    if(ui->UI_W_CHART== pWidget){
        ui->UI_PB_FULL->setEnabled(false);
        ui->UI_PB_TARGET->setEnabled(true);
        ui->UI_PB_TARGET->setFocus();
    }else if(ui->UI_W_TARGET_CHART== pWidget){
        ui->UI_PB_TARGET->setEnabled(false);
        ui->UI_PB_FULL->setEnabled(true);
        ui->UI_PB_FULL->setFocus();
    }
    pWidget->show();
}

void sManualTuning::on_UI_PB_TUNING_FIT_clicked()
{
    if(mWidgetCalibration->isHidden())
        mWidgetCalibration->show();
    else
        mWidgetCalibration->hide();
}

void sManualTuning::calibration(double* pFirst, double* pLast, cParamValue::_EventLIT* pEventLIT, _STRUCT_DATA* tempSTRUCT_DATA)
{
    double tempStart= pEventLIT->msStart- pEventLIT->msPrecursor;
    double tempEnd=pEventLIT->msEnd+ pEventLIT->msPrecursor;
    double dbStep= (tempEnd - tempStart) / tempSTRUCT_DATA->uEvtValidPoint;
    //double* pIndex= pFirst;
    tempSTRUCT_DATA->uPrePoint= 0;
    tempSTRUCT_DATA->uPostPoint= tempSTRUCT_DATA->uEvtValidPoint;
    mCALIBRATE.lock();
    if(mCALIBRATE.mPARAM_FIT.enable==1){
        switch (mCALIBRATE.mPARAM_FIT.coefF.size()) {
        case 6:
            while(pFirst<= pLast){
                *pFirst= pow(tempStart, 5) * mCALIBRATE.mPARAM_FIT.coefF[5]
                        + pow(tempStart, 4) * mCALIBRATE.mPARAM_FIT.coefF[4]
                        + pow(tempStart, 3) * mCALIBRATE.mPARAM_FIT.coefF[3]
                        + pow(tempStart, 2) * mCALIBRATE.mPARAM_FIT.coefF[2]
                        + tempStart * mCALIBRATE.mPARAM_FIT.coefF[1]
                        + mCALIBRATE.mPARAM_FIT.coefF[0];
                if(*pFirst< pEventLIT->msStartOrig)
                    ++tempSTRUCT_DATA->uPrePoint;
                if(*pFirst< pEventLIT->msEndOrig)
                    --tempSTRUCT_DATA->uPostPoint;
                tempStart += dbStep;
                pFirst++;
            }break;
        case 5:
            while(pFirst<= pLast){
                *pFirst= pow(tempStart, 4) * mCALIBRATE.mPARAM_FIT.coefF[4]
                        + pow(tempStart, 3) * mCALIBRATE.mPARAM_FIT.coefF[3]
                        + pow(tempStart, 2) * mCALIBRATE.mPARAM_FIT.coefF[2]
                        + tempStart * mCALIBRATE.mPARAM_FIT.coefF[1]
                        + mCALIBRATE.mPARAM_FIT.coefF[0];
                if(*pFirst< pEventLIT->msStartOrig)
                    ++tempSTRUCT_DATA->uPrePoint;
                if(*pFirst< pEventLIT->msEndOrig)
                    --tempSTRUCT_DATA->uPostPoint;
                tempStart += dbStep;
                pFirst++;
            }break;
        case 4:
            while(pFirst<= pLast){

                *pFirst= pow(tempStart, 3) * mCALIBRATE.mPARAM_FIT.coefF[3]
                        + pow(tempStart, 2) * mCALIBRATE.mPARAM_FIT.coefF[2]
                        + tempStart * mCALIBRATE.mPARAM_FIT.coefF[1]
                        + mCALIBRATE.mPARAM_FIT.coefF[0];
                if(*pFirst< pEventLIT->msStartOrig)
                    ++tempSTRUCT_DATA->uPrePoint;
                if(*pFirst< pEventLIT->msEndOrig)
                    --tempSTRUCT_DATA->uPostPoint;
                tempStart += dbStep;
                pFirst++;
            }break;
        case 3:
            while(pFirst<= pLast){
                *pFirst= pow(tempStart, 2) * mCALIBRATE.mPARAM_FIT.coefF[2]
                        + tempStart * mCALIBRATE.mPARAM_FIT.coefF[1]
                        + mCALIBRATE.mPARAM_FIT.coefF[0];
                if(*pFirst< pEventLIT->msStartOrig)
                    ++tempSTRUCT_DATA->uPrePoint;
                if(*pFirst< pEventLIT->msEndOrig)
                    --tempSTRUCT_DATA->uPostPoint;
                tempStart += dbStep;
                pFirst++;
            }break;
        default:
            while(pFirst<= pLast){
                *pFirst= tempStart;
                if(*pFirst< pEventLIT->msStartOrig)
                    ++tempSTRUCT_DATA->uPrePoint;
                if(*pFirst< pEventLIT->msEndOrig)
                    --tempSTRUCT_DATA->uPostPoint;
                tempStart += dbStep;
                pFirst++;
            }
            break;
        }
    }else{
        while(pFirst<= pLast){
            *pFirst= tempStart;
            if(*pFirst< pEventLIT->msStartOrig)
                ++tempSTRUCT_DATA->uPrePoint;
            if(*pFirst< pEventLIT->msEndOrig)
                --tempSTRUCT_DATA->uPostPoint;
            tempStart += dbStep;
            pFirst++;
        }
    }
    mCALIBRATE.changed=false;
    mCALIBRATE.unlock();
}

void sManualTuning::calibration(double* pFirst, double* pLast, double* bFirst, double dbVal, double dbStep)
{
    mCALIBRATE.lock();
    if(mCALIBRATE.mPARAM_FIT.enable==1){
        switch (mCALIBRATE.mPARAM_FIT.coefF.size()) {
        case 5:
            while(pFirst<= pLast){
                *pFirst= pow(dbVal, 4) * mCALIBRATE.mPARAM_FIT.coefF[4]
                        + pow(dbVal, 3) * mCALIBRATE.mPARAM_FIT.coefF[3]
                        + pow(dbVal, 2) * mCALIBRATE.mPARAM_FIT.coefF[2]
                        + dbVal * mCALIBRATE.mPARAM_FIT.coefF[1]
                        + mCALIBRATE.mPARAM_FIT.coefF[0];
                dbVal += dbStep;
                pFirst++;
            }break;
        case 4:
            while(pFirst<= pLast){
                *pFirst= pow(dbVal, 3) * mCALIBRATE.mPARAM_FIT.coefF[3]
                        + pow(dbVal, 2) * mCALIBRATE.mPARAM_FIT.coefF[2]
                        + dbVal * mCALIBRATE.mPARAM_FIT.coefF[1]
                        + mCALIBRATE.mPARAM_FIT.coefF[0];
                dbVal += dbStep;
                pFirst++;
            }break;
        case 3:
            while(pFirst<= pLast){
                *pFirst= pow(dbVal, 2) * mCALIBRATE.mPARAM_FIT.coefF[2]
                        + dbVal * mCALIBRATE.mPARAM_FIT.coefF[1]
                        + mCALIBRATE.mPARAM_FIT.coefF[0];
                dbVal += dbStep;
                pFirst++;
            }break;
        default:
            while(pFirst<= pLast){
                *pFirst= dbVal;
                dbVal += dbStep;
                pFirst++;
            }
            break;
        }
    }else{
        while(pFirst<= pLast){
            *pFirst= dbVal;
            *bFirst = 0.06/dbVal - 0.0002;
            dbVal += dbStep;
            bFirst++;
            pFirst++;
        }
    }
    mCALIBRATE.changed=false;
    mCALIBRATE.unlock();
}

QString sManualTuning::strCalibratP(_CONGIG_OMS::_PARAM_FIT& tempPARAM_FIT)
{
    QString tmpStr= QString::number(tempPARAM_FIT.enable)+'&';
    uint tempSize= tempPARAM_FIT.current.size();
    for(int i=0; i< tempSize; i++){
        tmpStr+= tempPARAM_FIT.current[i];
        if(i== tempSize-1)
            tmpStr+='&';
        else
            tmpStr+='@';
    }
    tempSize= tempPARAM_FIT.expect.size();
    for(int i=0; i< tempSize; i++){
        tmpStr+= tempPARAM_FIT.expect[i];
        if(i== tempSize-1)
            tmpStr+='&';
        else
            tmpStr+='@';
    }
    tempSize= tempPARAM_FIT.coefF.size();
    for(int i=0; i< tempSize; i++){
        tmpStr+= QString::number(tempPARAM_FIT.coefF[i]);
        if(i== tempSize-1)
            tmpStr+='&';
        else
            tmpStr+='@';
    }
    tempSize= tempPARAM_FIT.coefB.size();
    for(int i=0; i< tempSize; i++){
        tmpStr+= QString::number(tempPARAM_FIT.coefB[i]);
        if(i== tempSize-1)
            break;
        else
            tmpStr+='@';
    }
    return tmpStr;
}

//收到信号，则保存修正后的信息，并写回配置文件当中
/*
void sManualTuning::onCalibrat()
{


    QString path= filePath+"/tuning.ini";
    QSettings configIniWrite(path, QSettings::IniFormat);
    QString strTemp;
    mCALIBRATE.lock();
    mCALIBRATE.mPARAM_FIT.current.clear();
    mCALIBRATE.mPARAM_FIT.expect.clear();
    mCALIBRATE.mPARAM_FIT.coefF.clear();
    mCALIBRATE.mPARAM_FIT.coefB.clear();
    mWidgetCalibration->getParam(mCALIBRATE.mPARAM_FIT,);
    strTemp= strCalibratP(mCALIBRATE.mPARAM_FIT);
    mCALIBRATE.changed= true;
    mCALIBRATE.unlock();
    configIniWrite.setValue("/FIT/PolyFit", strTemp);
}
*/

void sManualTuning::onCalibrat()
{
    emit StopScan();
    QString path= filePath + "/tuning.ini";
    QSettings configIniWrite(path, QSettings::IniFormat);
    QString strTemp;
    mCALIBRATE.lock();
    mCALIBRATE.mPARAM_FIT.current.clear();
    mCALIBRATE.mPARAM_FIT.expect.clear();
    mCALIBRATE.mPARAM_FIT.coefF.clear();
    mCALIBRATE.mPARAM_FIT.coefB.clear();
    QString MassExtension;
    mWidgetCalibration->getParam(mCALIBRATE.mPARAM_FIT, MassExtension);
    mAdjustFactor.d_Mass_Forward_Extension= MassExtension.toDouble();
    configIniWrite.setValue("/AdjustLIT/MassExtension", MassExtension);
    strTemp= strCalibratP(mCALIBRATE.mPARAM_FIT);
    mCALIBRATE.changed= true;
    mCALIBRATE.unlock();
    configIniWrite.setValue("/FIT/PolyFit", strTemp);
}


void sManualTuning::updateConfig(){
    if(mCONGIG_MANUAL_TUNING.showFit)
        ui->UI_PB_TUNING_FIT->show();
    else
        ui->UI_PB_TUNING_FIT->hide();
}

void sManualTuning::onTipSend(int min, int max)
{
    QString str = QString("推荐范围为: %1~%2").arg(min).arg(max);
    emit tipSend(str);
}

void sManualTuning::calibration(double& pValue)
{
    mCALIBRATE.lock();
    if(mCALIBRATE.mPARAM_FIT.enable==1){
        switch (mCALIBRATE.mPARAM_FIT.coefB.size()) {
        case 6:
            pValue= pow(pValue, 5) * mCALIBRATE.mPARAM_FIT.coefB[5]
                    + pow(pValue, 4) * mCALIBRATE.mPARAM_FIT.coefB[4]
                    + pow(pValue, 3) * mCALIBRATE.mPARAM_FIT.coefB[3]
                    + pow(pValue, 2) * mCALIBRATE.mPARAM_FIT.coefB[2]
                    + pValue * mCALIBRATE.mPARAM_FIT.coefB[1]
                    + mCALIBRATE.mPARAM_FIT.coefB[0]; break;
        case 5:
            pValue= pow(pValue, 4) * mCALIBRATE.mPARAM_FIT.coefB[4]
                    + pow(pValue, 3) * mCALIBRATE.mPARAM_FIT.coefB[3]
                    + pow(pValue, 2) * mCALIBRATE.mPARAM_FIT.coefB[2]
                    + pValue * mCALIBRATE.mPARAM_FIT.coefB[1]
                    + mCALIBRATE.mPARAM_FIT.coefB[0]; break;
        case 4:
            pValue= pow(pValue, 3) * mCALIBRATE.mPARAM_FIT.coefB[3]
                    + pow(pValue, 2) * mCALIBRATE.mPARAM_FIT.coefB[2]
                    + pValue * mCALIBRATE.mPARAM_FIT.coefB[1]
                    + mCALIBRATE.mPARAM_FIT.coefB[0]; break;
        case 3:
            pValue= pow(pValue, 2) * mCALIBRATE.mPARAM_FIT.coefB[2]
                    + pValue * mCALIBRATE.mPARAM_FIT.coefB[1]
                    + mCALIBRATE.mPARAM_FIT.coefB[0]; break;
        default: break;
        }
    }
    mCALIBRATE.unlock();
}

void sManualTuning::changeCloseButton()
{
    if(state){
        ui->UI_PB_TUNING_SCAN->setText("执行");
        state = false;
    }
}

void sManualTuning::on_UI_PB_BASELINE_clicked()
{
    int size = mGraphBuffY->size();
    if(0 == size)
        return;
    double offset = 0;
    for(int i=0; i<size; i++){
        std::vector<double> temp = (*mGraphBuffY)[i];

        if(temp.size() == 0)
            continue;
        for(int j = 0; j< temp.size();j++){
            offset = (double)(offset*j)/(double)(j+1) + temp[i]/(double)(j+1);
        }
    }
    if(offset == 0)
        return;
    offset = -offset;
    QString path = QCoreApplication::applicationDirPath()+"/system.ini";
    QSettings configIniRead(path, QSettings::IniFormat);
    QString tmpMethod= configIniRead.value("/Processing/Method","").toString();
    QStringList tempData = tmpMethod.split('+');
    QString method;
    for(int i = 0; i<tempData.size(); i++){
        QString meth = tempData[i];
        if(meth.split('&')[0] == "GainOffset"){
            QString oldnum = meth.split('&')[1];
            double old = oldnum.toDouble();
            meth = meth.split('&')[2];
            meth = "GainOffset&" + QString::number(offset+old) + "&" + meth;
        }else{
            meth += "+";
        }

        method += meth;
    }
    mDataProcess->setMethod(method);
    configIniRead.setValue("/Processing/Method",method);
}
