#include "sCommandUSB.h"
#include "sDataAcquisiton.h"
#include "ui_sDataAcquisiton.h"
#include <QLineEdit>
#include "tool/Algorithm.h"
#include <QSettings>

void sDataAcquisiton::memoryInit()
{
    mGraphBuffX= _CHART_X_ACQUIS::get();
    mGraphBuffY= _CHART_Y_ACQUIS::get();
    mList_PEAK= _CHART_PEAK_ACQUIS::get();
    mBaseLine = _BASELINE_OFFSET::get();
}

sDataAcquisiton::sDataAcquisiton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sDataAcquisiton)
{
    ui->setupUi(this);
    ui->UI_PB_PROCESS->setEnabled(false);//showWindow(ui->UI_W_ORIGINAL);
    mChartTIC = new sChartWidget(sChartWidget::_TIC_CHART);
    //connect(mChartTIC, SIGNAL(PlotChanged()),this, SLOT(on_PlotChanged()));
    //connect(mChartTIC, SIGNAL(ChangedXIC(QString)), this, SLOT(on_ChangedXIC(QString)));
//    connect(mChartTIC, SIGNAL(CommandSignal(QString ,sChartWidget* ,void* )),
//                                 this, SLOT(on_CommandSignal(QString ,sChartWidget* ,void* )));
    ui->UI_LAYOUT_TIC->addWidget(mChartTIC);

    resizeChart(1);
    memoryInit();
    mAnalyzeThread= new SThread(this);
    mAnalyzeThread->setUserFunction(analyzeThread);
    mAnalyzeThread->setUserParam(this);
    QObject::connect(this,SIGNAL(sUpdateGraph(int)),this,SLOT(onUpdateGraph(int)),Qt::QueuedConnection);
    QObject::connect(this,SIGNAL(sUpdateTIC(int)),this,SLOT(onUpdateTIC(int)),Qt::QueuedConnection);
    mDataProcess= sDataProcess::getDataProcess();

    connect(ui->TICList, SIGNAL(ChangedManager(QString, bool )),
            mChartTIC,SLOT(on_ChangedManager(QString, bool )));
    connect(ui->TICList, SIGNAL(HideXIC(uint32_t , QString , bool )),
            mChartTIC,SLOT(onHideXIC(uint32_t , QString , bool )));

    ui->RightWidget->hide();
    ui->rangeWidget_2->hide();

    mLoadDataFile= new cLoadDataFile();
}

sDataAcquisiton::~sDataAcquisiton()
{
    if(mAnalyzeThread){
        if(mAnalyzeThread->isRunning()){
            mAnalyzeThread->stop();
            mAnalyzeThread->wait();
        }
        delete mAnalyzeThread;
        mAnalyzeThread= nullptr;
    }
    if(mChartTIC){
        delete mChartTIC;
        mChartTIC=nullptr;
    }
    resizeChart(0);
    delete ui;
}

bool sDataAcquisiton::loadFile(bool ifUpdateUI, QString qPath)
{
    Q_UNUSED(ifUpdateUI)
    QString path;
    if(qPath.isEmpty())
        path = filePath +"/tuning.ini";
        //path = ".\tuning.ini";
    else
        path = qPath;
    QSettings configIniRead(path, QSettings::IniFormat);
    QString tmpStr = configIniRead.value("/FIT/PolyFit","").toString();
    QStringList tmpList= tmpStr.split("&");
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
    return true;
}

//参数列表： 阶段数据头指针，阶段数据尾指针
//计算第一个数据点和最后一个点的实际值
void sDataAcquisiton::calibration(double* pFirst, double* pLast, double* baseline, cParamValue::_EventLIT* pEventLIT, _STRUCT_DATA* tempSTRUCT_DATA)
{
    double tempStart= pEventLIT->msStart- pEventLIT->msPrecursor;
    double tempEnd=pEventLIT->msEnd+ pEventLIT->msPrecursor;
    double dbStep= (tempEnd - tempStart) / tempSTRUCT_DATA->uEvtValidPoint;
    //double* pIndex= pFirst;
    tempSTRUCT_DATA->uPrePoint= 0;
    tempSTRUCT_DATA->uPostPoint= tempSTRUCT_DATA->uEvtValidPoint;

    if(mCALIBRATE.enable==1){
        switch (mCALIBRATE.coefF.size()) {
        case 6:
            while(pFirst<= pLast){
                *pFirst= pow(tempStart, 5) * mCALIBRATE.coefF[5]
                        + pow(tempStart, 4) * mCALIBRATE.coefF[4]
                        + pow(tempStart, 3) * mCALIBRATE.coefF[3]
                        + pow(tempStart, 2) * mCALIBRATE.coefF[2]
                        + tempStart * mCALIBRATE.coefF[1]
                        + mCALIBRATE.coefF[0];
                if(*pFirst< pEventLIT->msStartOrig)
                    ++tempSTRUCT_DATA->uPrePoint;
                if(*pFirst< pEventLIT->msEndOrig)
                    --tempSTRUCT_DATA->uPostPoint;
                tempStart += dbStep;
                pFirst++;
            }break;
        case 5:
            while(pFirst<= pLast){
                *pFirst= pow(tempStart, 4) * mCALIBRATE.coefF[4]
                        + pow(tempStart, 3) * mCALIBRATE.coefF[3]
                        + pow(tempStart, 2) * mCALIBRATE.coefF[2]
                        + tempStart * mCALIBRATE.coefF[1]
                        + mCALIBRATE.coefF[0];
                if(*pFirst< pEventLIT->msStartOrig)
                    ++tempSTRUCT_DATA->uPrePoint;
                if(*pFirst< pEventLIT->msEndOrig)
                    --tempSTRUCT_DATA->uPostPoint;
                tempStart += dbStep;
                pFirst++;
            }break;
        case 4:
            while(pFirst<= pLast){

                *pFirst= pow(tempStart, 3) * mCALIBRATE.coefF[3]
                        + pow(tempStart, 2) * mCALIBRATE.coefF[2]
                        + tempStart * mCALIBRATE.coefF[1]
                        + mCALIBRATE.coefF[0];
                if(*pFirst< pEventLIT->msStartOrig)
                    ++tempSTRUCT_DATA->uPrePoint;
                if(*pFirst< pEventLIT->msEndOrig)
                    --tempSTRUCT_DATA->uPostPoint;
                tempStart += dbStep;
                pFirst++;
            }break;
        case 3:
            while(pFirst<= pLast){
                *pFirst= pow(tempStart, 2) * mCALIBRATE.coefF[2]
                        + tempStart * mCALIBRATE.coefF[1]
                        + mCALIBRATE.coefF[0];
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
            *baseline = 0.06/tempStart - 0.0002;
            if(*pFirst< pEventLIT->msStartOrig)
                ++tempSTRUCT_DATA->uPrePoint;
            if(*pFirst< pEventLIT->msEndOrig)
                --tempSTRUCT_DATA->uPostPoint;
            tempStart += dbStep;
            pFirst++;
            baseline++;
        }
    }
}

void sDataAcquisiton::calibration(double* pFirst, double* pLast, double dbVal, double dbStep)
{
    if(mCALIBRATE.enable==1){
        switch (mCALIBRATE.coefF.size()) {
        case 6:
            while(pFirst<= pLast){
                *pFirst= pow(dbVal, 5) * mCALIBRATE.coefF[5]
                        + pow(dbVal, 4) * mCALIBRATE.coefF[4]
                        + pow(dbVal, 3) * mCALIBRATE.coefF[3]
                        + pow(dbVal, 2) * mCALIBRATE.coefF[2]
                        + dbVal * mCALIBRATE.coefF[1]
                        + mCALIBRATE.coefF[0];
                dbVal += dbStep;
                pFirst++;
            }break;
        case 5:
            while(pFirst<= pLast){
                *pFirst= pow(dbVal, 4) * mCALIBRATE.coefF[4]
                        + pow(dbVal, 3) * mCALIBRATE.coefF[3]
                        + pow(dbVal, 2) * mCALIBRATE.coefF[2]
                        + dbVal * mCALIBRATE.coefF[1]
                        + mCALIBRATE.coefF[0];
                dbVal += dbStep;
                pFirst++;
            }break;
        case 4:
            while(pFirst<= pLast){
                *pFirst= pow(dbVal, 3) * mCALIBRATE.coefF[3]
                        + pow(dbVal, 2) * mCALIBRATE.coefF[2]
                        + dbVal * mCALIBRATE.coefF[1]
                        + mCALIBRATE.coefF[0];
                dbVal += dbStep;
                pFirst++;
            }break;
        case 3:
            while(pFirst<= pLast){
                *pFirst= pow(dbVal, 2) * mCALIBRATE.coefF[2]
                        + dbVal * mCALIBRATE.coefF[1]
                        + mCALIBRATE.coefF[0];
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
            dbVal += dbStep;
            pFirst++;
        }
    }
}

void sDataAcquisiton::resizeChart(int size)
{
    if(mMassChart.size()!= size){
        while(mMassChart.size()!=0){
            ui->UI_LAYOUT_PROCESS->removeWidget(mMassChart.last());
            delete mMassChart.last();
            mMassChart.removeLast();
        }
        for(int i=0; i<size; i++){
            sChartWidget* tempChart = new sChartWidget(sChartWidget::_NORMAL_CHART);
            ui->UI_LAYOUT_PROCESS->addWidget(tempChart);
            mMassChart.append(tempChart);
            connect(ui->btnSaveFrame,SIGNAL(clicked(bool)),tempChart,SLOT(exportPlot()));
            connect(ui->TICList, SIGNAL(MassWidgetAddLine(double,QColor)),
                    tempChart,SLOT(onMassWidgetAddLine(double,QColor)));
            connect(ui->TICList,SIGNAL(itemRemove(double)),tempChart,SLOT(onItemRemove(double)));
        }
    }
}

bool sDataAcquisiton::startDataAcquisiton(QByteArray& pSegment, QString fileHead, bool saveState)
{
    if(pSegment.isEmpty())
        return false;
    isSave = saveState;
    mSegment.resize(pSegment.size());
    memcpy(mSegment.data(), pSegment.data(), pSegment.size());
    mChartTIC->setFileHead(fileHead);
    cParamValue::_Segment* tempP = (cParamValue::_Segment*)pSegment.data();
    if(tempP->type==cParamValue::Type_LIT_TARGET){
        resizeChart(tempP->sumEvent);
        for(uint32_t i=0;i<tempP->sumEvent;++i){
            cParamValue::_EventLIT* pEvent= (cParamValue::_EventLIT*)
                    (((char*)(&(tempP->fisrtEvent)))+sizeof(cParamValue::_EventLIT)*i);
            if(!pEvent)
                return false;
            mMassChart[i]->setFileHead(fileHead);
            mMassChart[i]->setStyleM(TVPlot::Sticks, "",pEvent->msStartOrig, pEvent->msEndOrig);
            //mMassChart[i]->setStyleM(TVPlot::Sticks, "",pEvent->msStartOrig, pEvent->msEndOrig);
        }
        mAnalyzeThread->start();
        return true;
    }else if(tempP->type==cParamValue::Type_LIT_FULL){
        cParamValue::_EventLIT* pEvent= (cParamValue::_EventLIT*)&(tempP->fisrtEvent);
        if(pEvent){
            resizeChart(1);
            mMassChart[0]->setFileHead(fileHead);
            if(isProfile)
                mMassChart[0]->setStyleM(TVPlot::Lines, "",pEvent->msStartOrig, pEvent->msEndOrig);
            else
                mMassChart[0]->setStyleM(TVPlot::Sticks, "",pEvent->msStartOrig, pEvent->msEndOrig);
            //mMassChart[0]->setStyleM(TVPlot::Sticks, "",pEvent->msStartOrig, pEvent->msEndOrig);
            mAnalyzeThread->start();
            return true;
        }
    }
    return false;
}

//
bool sDataAcquisiton::dataDismantleTIC(QByteArray& pByteArray, double& xTIC, double& yTIC)
{
    if(pByteArray.size()< (int)sizeof(_StreamBody))
        return false;
    _StreamBody* pStreamBody = (_StreamBody*)(pByteArray.data());
    xTIC= pStreamBody->currentTime;
    yTIC= pStreamBody->currentAcc;
    //计算所有数据点个数
    uint32_t uAllPoint = (pByteArray.size() - sizeof(_StreamBody)) / sizeof(double);
    //记录整个包头指针
    double* pdbHead = (double*)(pByteArray.data());
    //记录数据头指针
    double* pdbOffset = (double*)(pByteArray.data() + sizeof(_StreamBody));
    QVector<double> tempV(uAllPoint);

    //将包头数据删除，只保留点数据
    for(uint32_t i=0; i<uAllPoint; i++){
        *pdbHead= *pdbOffset;
        tempV[i]=*pdbOffset;
        pdbHead++;
        pdbOffset++;
    }
    pByteArray.resize(uAllPoint*sizeof(double));
    return true;
}

//参数列表： 数据值，参数结构体，各阶段数据点x值的列表，各阶段数据点y值的列表，各阶段数据参数列表，判断值（未知）
//返回值： 数据点的总个数
uint32_t sDataAcquisiton::dataDismantleFirst(QByteArray& pByteArray, cParamValue::_Segment* pSegment,
                                QList<std::vector<double>>* pListX, QList<std::vector<double>>* pListY,
                                QList<_STRUCT_DATA>& pSTRUCT_DATA, bool restart)
{
    if(pByteArray.isEmpty()||(pSegment==nullptr)||(pListY==nullptr))
        return 0;
    cParamValue::_EventLIT* pEventLIT= (cParamValue::_EventLIT*)&(pSegment->fisrtEvent);
    if(pEventLIT==nullptr)
        return 0;
    double dbEvtTimeSum= 0;//pEventLIT->holdTime;
    //计算总时间
    for(uint32_t i=0;i<pSegment->sumEvent;i++)
        dbEvtTimeSum+= ((cParamValue::_EventLIT*)((int*)pEventLIT+ sizeof(cParamValue::_EventLIT)/sizeof(int)*i))->holdTime;
    if(dbEvtTimeSum< 0.0000001)
        return 0;

    //初始化X,Y
    if((uint32_t)(pListY->size())!= pSegment->sumEvent){
        mBaseLine->clear();
        pListY->clear();
        pListX->clear();
        for(uint32_t i=0;i<pSegment->sumEvent;i++){
            mBaseLine->append(std::vector<double>(0));
            pListY->append(std::vector<double>(0));
            pListX->append(std::vector<double>(0));
        }
    }

    if(restart){
        pSTRUCT_DATA.clear();
        for(uint32_t currentEvt=0;currentEvt<pSegment->sumEvent;currentEvt++){
            //_STRUCT_DATA tempSTRUCT_DATA;
            pSTRUCT_DATA.append(_STRUCT_DATA());
        }
    }
    //获取数据个数
    uint32_t uAllPoint = pByteArray.size() / sizeof(double);
    //获取数据头指针
    double* pdbOffset = (double*)(pByteArray.data());

    for(uint32_t currentEvt=0;currentEvt<pSegment->sumEvent;currentEvt++){
        pEventLIT=((cParamValue::_EventLIT*)((int*)&(pSegment->fisrtEvent)+ sizeof(cParamValue::_EventLIT)/sizeof(int)*currentEvt));
        _STRUCT_DATA* tempSTRUCT_DATA= &(pSTRUCT_DATA[currentEvt]);
        //tempSTRUCT_DATA->uPrePoint = (uint32_t)(pEventLIT->preReadyTime * uAllPoint /dbEvtTimeSum);
        //tempSTRUCT_DATA->uPostPoint = (uint32_t)(pEventLIT->postReadyTime * uAllPoint /dbEvtTimeSum);
        tempSTRUCT_DATA->uEvtValidPoint = (uint32_t)(pEventLIT->holdTime * uAllPoint / dbEvtTimeSum);
        //tempSTRUCT_DATA->uEventPoint= tempSTRUCT_DATA->uEvtValidPoint- tempSTRUCT_DATA->uPrePoint- tempSTRUCT_DATA->uPostPoint;

        //对Y初始化并对各个阶段数据长度初始化
        if((!vectorOperate::Resize((*pListY)[currentEvt],tempSTRUCT_DATA->uEvtValidPoint))
            ||(!vectorOperate::Resize((*pListX)[currentEvt],tempSTRUCT_DATA->uEvtValidPoint))
                ||(!vectorOperate::Resize((*mBaseLine)[currentEvt],tempSTRUCT_DATA->uEvtValidPoint)))
                return 0;

        if(restart){
            double* pFirst= (*pListX)[currentEvt].data();
            double* pLast= pFirst+ tempSTRUCT_DATA->uEvtValidPoint-1;
            double* mBaseLineFirst = (*mBaseLine)[currentEvt].data();
            //算出第一个点和最后一个点的实际值
            calibration(pFirst, pLast, mBaseLineFirst, pEventLIT, tempSTRUCT_DATA);
            tempSTRUCT_DATA->uEventPoint= tempSTRUCT_DATA->uEvtValidPoint- tempSTRUCT_DATA->uPrePoint- tempSTRUCT_DATA->uPostPoint;
            Baseline_Average = 0;
            for(int i = 0 ; i< mBaseLine->size() ;i++){
                double average = 0;
                for(int j = 0 ; j<(*mBaseLine)[i].size(); j++){
                    average = (*mBaseLine)[i][j]*j/(j+1) + average/(j+1);
                }
                Baseline_Average = average/(i+1) + Baseline_Average*i/(i+1);
            }
        }
        memcpy((*pListY)[currentEvt].data(), pdbOffset, tempSTRUCT_DATA->uEvtValidPoint* sizeof(double));
        //qDebug() << "错误数据：";
        for(int i = 0; i<tempSTRUCT_DATA->uEvtValidPoint; i++){
            //if((*pListY)[currentEvt][i] > 0 || (*pListY)[currentEvt][i] < -0.5)
                //qDebug() << "第" << i  << "点：" << (*pListY)[currentEvt][i];
            (*pListY)[currentEvt][i] = (*pListY)[currentEvt][i] + (*mBaseLine)[currentEvt][i];
        }

        if(!mDataProcess->getData((*pListY)[currentEvt],(*pListY)[currentEvt],restart))
            return 0;
        pdbOffset += tempSTRUCT_DATA->uEvtValidPoint;
    }
    return uAllPoint;
}

//对阶段数据列表中各阶段赋值
bool sDataAcquisiton::dataDismantleSecond(const QByteArray& pByteArray,QList<std::vector<double>>* pListY,
                                          const QList<_STRUCT_DATA>& pSTRUCT_DATA)
{
    if(pByteArray.isEmpty()||(pListY==nullptr)|| pSTRUCT_DATA.isEmpty())
        return false;
    double* pdbOffset = (double*)(pByteArray.data());
    for(int currentEvt=0; currentEvt< pSTRUCT_DATA.size(); currentEvt++){
        memcpy((*pListY)[currentEvt].data(), pdbOffset, pSTRUCT_DATA.at(currentEvt).uEvtValidPoint* sizeof(double));
        pdbOffset += pSTRUCT_DATA.at(currentEvt).uEvtValidPoint;
    }
    return true;
}

bool sDataAcquisiton::AnalyzeScan(double* pX, double* pY, _STRUCT_DATA& pSTRUCT_DATA,
                                int currentEvt, int countEvt, _STRUCT_PEAK& pSTRUCT_PEAK,uint32_t uWidth)
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
    pSTRUCT_PEAK.yXIC = 0;

    for(int i = 0; i< uWidth; i++){
        int peakPoint = pMark[i];
        tempSTRUCT_PEAK.Absc.push_back(tempX[peakPoint]);
        tempSTRUCT_PEAK.Ord.push_back(tempY[peakPoint]);
        strMarker.append(QString::number(tempX[peakPoint]));
        pSTRUCT_PEAK.yXIC += tempY[peakPoint];
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

bool sDataAcquisiton::AnalyzeXIC(double* pX, double* pY, _STRUCT_DATA& pSTRUCT_DATA,uint32_t currentEvt,uint32_t sizeTIC)
{
    mChartTIC->lockXIC();
    QMutableMapIterator<QString, sChartWidget::_GRAPH_XIC*> tempIter((*(mChartTIC->getXIC()))[currentEvt]);
    while (tempIter.hasNext()) {
        double tempY=0;
        double tempMass=tempIter.next().key().toDouble();
        sChartWidget::_GRAPH_XIC* pGRAPH_XIC=tempIter.value();
        uint32_t sizeY=pGRAPH_XIC->yListXIC.size();
        double tempFirstM= tempMass- pGRAPH_XIC->massRange;
        double tempLastM= tempMass+ pGRAPH_XIC->massRange;
        uint32_t sizeF= pSTRUCT_DATA.uPrePoint+pSTRUCT_DATA.uEventPoint;
        int countY=0;
        if((tempLastM < pX[pSTRUCT_DATA.uPrePoint])||
                (tempFirstM> pX[sizeF])){
            if(sizeY>0)
                vectorOperate::Clear(pGRAPH_XIC->yListXIC);
        }else{
            for(uint32_t i= pSTRUCT_DATA.uPrePoint; i< sizeF; ++i){
                if(pX[i]>tempLastM)
                    break;
                if((pX[i]> tempFirstM)&&(pX[i]< tempLastM)){
                    ++countY;
                    tempY=fabs(tempY/(countY)*(countY-1)+ fabs(pY[i])/(countY));
                }
            }
            if(sizeY==0){
                pGRAPH_XIC->yListXIC.resize(sizeTIC,tempY);
            }else{
                pGRAPH_XIC->yListXIC.resize(sizeTIC);
                if(sizeY > sizeTIC)//maximun size
                    pGRAPH_XIC->yListXIC.shrink_to_fit();
            }
            pGRAPH_XIC->yListXIC[sizeTIC-1]= tempY* pGRAPH_XIC->Gain+ pGRAPH_XIC->Offset;
        }

    }
    mChartTIC->unLockXIC();
    return true;
}

bool sDataAcquisiton::AnalyzeXIC(uint32_t currentEvt, uint32_t sizeTIC)
{
    mChartTIC->lockXIC();
    QMutableMapIterator<QString, sChartWidget::_GRAPH_XIC*> tempIter((*(mChartTIC->getXIC()))[currentEvt]);
    while (tempIter.hasNext()) {
        double tempY=0;
        double tempMass=tempIter.next().key().toDouble();
        sChartWidget::_GRAPH_XIC* pGRAPH_XIC=tempIter.value();
        uint32_t sizeY=pGRAPH_XIC->yListXIC.size();

        for(int i = 0; i < (*mList_PEAK)[0].Absc.size();i++){
            double dx = fabs(tempMass - (*mList_PEAK)[0].Absc[i]);
            if(dx < 1){
                tempY += (1-dx)*(*mList_PEAK)[0].Ord[i];
            }else{
                tempY += 0;
            }
        }

        if(sizeY==0){
            pGRAPH_XIC->yListXIC.resize(sizeTIC,tempY);
        }else{
            pGRAPH_XIC->yListXIC.resize(sizeTIC);
            if(sizeY > sizeTIC)//maximun size
                pGRAPH_XIC->yListXIC.shrink_to_fit();
        }
        pGRAPH_XIC->yListXIC[sizeTIC-1]= tempY* pGRAPH_XIC->Gain+ pGRAPH_XIC->Offset;
    }
    mChartTIC->unLockXIC();
    return true;
}

void sDataAcquisiton::setTICValue(QString value)
{
    ui->TIC_Value->setText(value);
}

int sDataAcquisiton::analyzeThread(void *pParam, const bool &bRunning)
{
    sDataAcquisiton* pDataAcquisiton = (sDataAcquisiton*)pParam;
    CommandUSB* pCommandUSB= sCommandUSB::getCommandUSB();
    if(pDataAcquisiton&& pCommandUSB){
        pDataAcquisiton->loadFile();
        bool isRestart=true;
        QList<std::vector<double>>* mThreadBuffY= _DAQ_Y_ACQUIS::get();
        QList<std::vector<double>>* mThreadBuffX= _DAQ_X_ACQUIS::get();
        _STRUCT_PEAK* pSTRUCT_PEAK=_PEAK_THREAD_ACQUIS::get();
        if(pDataAcquisiton->mBaseLine == nullptr)
            pDataAcquisiton->mBaseLine = new QList<std::vector<double>>();
        QByteArray mSegmentGraph(pDataAcquisiton->getSegment());
        cParamValue::_Segment* pSegmentLIT= pDataAcquisiton->getSegmentParam(&mSegmentGraph);
        pDataAcquisiton->initTIC();
        QList<_STRUCT_DATA> listSTRUCT_DATA;
        int countAverageAGC=0;
        double tempPeriod= pDataAcquisiton->getConfig()->Period;
        if(pDataAcquisiton->getIsSave()){
            pDataAcquisiton->getLoadDataFile()->createDataFile(pDataAcquisiton->getFileHead());
        }
        while(bRunning){
            //获取数据
            if(pCommandUSB->getDataDAQ(pDataAcquisiton->mGraphBuffer)!= -1 && !pDataAcquisiton->mGraphBuffer.isEmpty()){
                double xTIC,yTIC;
                //分析xTIC和yTIC
                if(!pDataAcquisiton->dataDismantleTIC(pDataAcquisiton->mGraphBuffer, xTIC, yTIC))
                    continue;
                //分析mass谱图
                if(pDataAcquisiton->dataDismantleFirst(pDataAcquisiton->mGraphBuffer, pSegmentLIT,
                                              mThreadBuffX, mThreadBuffY, listSTRUCT_DATA, isRestart)==0)//create original mThreadBuffX, mThreadBuffY
                    continue;
                double pTIC = yTIC-pDataAcquisiton->Baseline_Average;
                pDataAcquisiton->setTICValue(QString::number(pTIC));

                if(++countAverageAGC >= 5){
                    countAverageAGC=0;
                    emit pDataAcquisiton->sAGC(pTIC);
                }

                //确定几个分谱
                uint32_t countEvt= listSTRUCT_DATA.size();
                if(countEvt==0)
                    continue;

                for(uint32_t currentEvt=0;currentEvt<countEvt;currentEvt++){
                    _STRUCT_DATA* pSTRUCT_DATA= &(listSTRUCT_DATA[currentEvt]);
                    //分析扫描过程，确定峰位
                    if(!pDataAcquisiton->AnalyzeScan((*mThreadBuffX)[currentEvt].data(),
                                                     (*mThreadBuffY)[currentEvt].data(),
                                                   *pSTRUCT_DATA, currentEvt, countEvt, *pSTRUCT_PEAK, 8)){
                        qDebug()<<"E_MemoryOverflow";
                        return 0;
                    }
                }

                //获取新的TICy值
                yTIC = pSTRUCT_PEAK->yXIC;


                //如果时间大于1000秒,则丢弃前前一半数据，将后一半数据copy至前一半
                if(xTIC > tempPeriod){
                    tempPeriod += pDataAcquisiton->getConfig()->Period/2.5;
                    pDataAcquisiton->mSTRUCT_TIC.resizeFit();
                }
                pDataAcquisiton->mSTRUCT_TIC.append(xTIC,yTIC);
                if(pDataAcquisiton->getIsSave())
                    pDataAcquisiton->getLoadDataFile()->saveDataTIC(QString::number(xTIC) + "\t"+ QString::number(yTIC) + "\n");
                //获取当前TIC的尺寸
                uint32_t sizeTIC= pDataAcquisiton->mSTRUCT_TIC.size();

                for(uint32_t currentEvt=0;currentEvt<countEvt;currentEvt++){
                    if(pDataAcquisiton->isProfile == _StreamHead::sticks)
                        pDataAcquisiton->AnalyzeXIC(currentEvt,sizeTIC);
                    else if(pDataAcquisiton->isProfile == _StreamHead::profile)
                    {
                        _STRUCT_DATA* pSTRUCT_DATA= &(listSTRUCT_DATA[currentEvt]);
                        //获取对应质量数的XIC
                        pDataAcquisiton->AnalyzeXIC((*mThreadBuffX)[currentEvt].data(),
                                        (*mThreadBuffY)[currentEvt].data(),*pSTRUCT_DATA, currentEvt, sizeTIC);//create xic
                    }
                }

                emit pDataAcquisiton->sUpdateTIC(sizeTIC);//update tic/xic

                isRestart=false;
                emit pDataAcquisiton->sUpdateGraph(pSegmentLIT->sumEvent);
            }
            QThread::usleep(100);
        }      
        mThreadBuffX->clear();
        mThreadBuffY->clear();
        qDebug() << "N_DataAcquistion_AnalyzeThread_Over";
    }
    if(pDataAcquisiton->getIsSave()){
        pDataAcquisiton->getLoadDataFile()->closeFileTIC();
        pDataAcquisiton->getLoadDataFile()->closeFileMass();
    }
    return 0;
}

void sDataAcquisiton::onUpdateGraph(int type)
{
    if(mGraphBuffMutex.tryLock(50)){
        for(int i=0; i< type; i++){
            if(getIsSave()){
                if(isProfile == _StreamHead::sticks)
                    getLoadDataFile()->saveDataMass((*mList_PEAK)[i].Absc,(*mList_PEAK)[i].Ord);
                else if(isProfile == _StreamHead::profile)
                    getLoadDataFile()->saveDataMass((*mGraphBuffY)[i]);
            }
            mMassChart[i]->SetMarker((*mList_PEAK)[i].Absc,(*mList_PEAK)[i].Ord,(*mList_PEAK)[i].Marker);
            if(isProfile == _StreamHead::profile)
                mMassChart[i]->setSamples((*mGraphBuffX)[i], (*mGraphBuffY)[i]);
            else if(isProfile == _StreamHead::sticks){
                int size = (*mList_PEAK)[i].Absc.size();
                if(size != 0){
                    double temp = (*mList_PEAK)[i].Absc[size-1];
                    (*mList_PEAK)[i].Absc.push_back(temp-1);
                    (*mList_PEAK)[i].Ord.push_back(0);
                }
                mMassChart[i]->addBaseLine();
                mMassChart[i]->setSamples((*mList_PEAK)[i].Absc,(*mList_PEAK)[i].Ord);
            }
        }
        mGraphBuffMutex.unlock();
    }
}

void sDataAcquisiton::onUpdateTIC(int sizeTIC)
{
    if(mSTRUCT_TIC.tryLock(50)){
        if(mChartTIC)
            mChartTIC->setSamples(mSTRUCT_TIC.xTIC.data(), mSTRUCT_TIC.yTIC.data(), sizeTIC);
        mChartTIC->drawXIC(mSTRUCT_TIC.xTIC, sizeTIC);
        mSTRUCT_TIC.unlock();
    }
}

void sDataAcquisiton::on_UI_PB_PROCESS_clicked()
{
    ui->UI_PB_PROCESS->setEnabled(false);
            ui->UI_PB_ORIGINAL->setEnabled(true);
            ui->UI_PB_ORIGINAL->setFocus();
}

void sDataAcquisiton::on_UI_PB_ORIGINAL_clicked()
{
    ui->UI_PB_ORIGINAL->setEnabled(false);
            ui->UI_PB_PROCESS->setEnabled(true);
            ui->UI_PB_PROCESS->setFocus();
}

bool sDataAcquisiton::isOriginal(){
    return ui->UI_PB_PROCESS->isEnabled();
}

//void sDataAcquisiton::on_ChangedXIC(QString strPropXIC)
//{
////    if(!strPropXIC.isEmpty())
////        sobject()->setProperty("structXIC", strPropXIC);
//}

void sDataAcquisiton::setDatapath(QString path)
{
    filePath = path;
    mChartTIC->setDataPath(path);
}

void sDataAcquisiton::on_btnSlide_clicked()
{
    if(ui->RightWidget->isHidden())
    {
        if(isAdmin == false){
            ui->UI_PB_ORIGINAL->hide();
            ui->UI_PB_PROCESS->hide();
            ui->line->hide();
        }
        ui->RightWidget->show();
        ui->btnSlide->setStyleSheet(QStringLiteral("border-image: url(:/picture/Icon_Right.jpg);"));
    }else{
        ui->RightWidget->hide();
        ui->btnSlide->setStyleSheet(QStringLiteral("border-image: url(:/picture/Icon_Left.jpg);"));
    }
}


void sDataAcquisiton::on_btnRange_clicked()
{
    if(ui->rangeWidget_2->isHidden()){
        ui->rangeWidget_2->show();
    }else{
        ui->rangeWidget_2->hide();
        if(ui->UI_LE_X1->text().isEmpty() ||
           ui->UI_LE_X2->text().isEmpty() ||
           ui->UI_LE_X1->text() == "auto" ||
           ui->UI_LE_X2->text() == "auto")
        {
            ui->UI_LE_X1->setText("auto");
            ui->UI_LE_X2->setText("auto");
            mMassChart[0]->setScale(QwtPlot::xBottom, "auto");
        }else {
            QString rangeX = ui->UI_LE_X1->text() + "," + ui->UI_LE_X2->text();
            mMassChart[0]->setScale(QwtPlot::xBottom, rangeX);
        }

        if(ui->UI_LE_Y1->text().isEmpty() ||
           ui->UI_LE_Y2->text().isEmpty() ||
           ui->UI_LE_Y1->text() == "auto" ||
           ui->UI_LE_Y2->text() == "auto")
        {
            ui->UI_LE_Y1->setText("auto");
            ui->UI_LE_Y2->setText("auto");
            mMassChart[0]->setScale(QwtPlot::yLeft, "auto");
            return;
        }else {
            QString rangeY = ui->UI_LE_Y1->text() + "," + ui->UI_LE_Y2->text();
            mMassChart[0]->setScale(QwtPlot::yLeft, rangeY);
            return;
        }
    }
}
