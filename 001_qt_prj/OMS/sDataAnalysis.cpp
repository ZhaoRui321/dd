#include "sDataAnalysis.h"
#include "ui_sDataAnalysis.h"
#include <QFileDialog>
#include <QByteArray>
#include <QTouchEvent>
#include "tool/Algorithm.h"

sDataAnalysis::sDataAnalysis(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sDataAnalysis)
{
    ui->setupUi(this);
    ui->groupBox->hide();
    ui->groupBox_2->hide();
    select = new ColorSelectTool();
    mChartMass = new sChartWidget(sChartWidget::_ENORMAL_CHART);
    ui->verticalLayout_3->addWidget(mChartMass);
    connect(mChartMass,SIGNAL(selected(const double)),this,SLOT(onSelectedMass(const double)));

    mChartTIC = new sChartWidget(sChartWidget::_TIC_CHART,false);
    ui->verticalLayout_2->addWidget(mChartTIC);
    connect(mChartTIC,SIGNAL(selected(const double)),this,SLOT(onSelectedTIC(const double)));
    
    //注册事件对象
    ui->widgetForTouch->grabGesture(Qt::PanGesture);
    ui->widgetForTouch->grabGesture(Qt::PinchGesture);

    ui->widgetForTouch->installEventFilter(this);
    ui->widgetForTouch->setAttribute(Qt::WA_AcceptTouchEvents);

    ui->delBtn->hide();
    ui->verticalWidget_2->hide();

    mDataProcess= sDataProcess::getDataProcess();

    mLoadDataFile= new cLoadDataFile();

    mAnalyzeThread= new SThread(this);
    mAnalyzeThread->setUserFunction(analyzeThread);
    mAnalyzeThread->setUserParam(this);

    QObject::connect(this,SIGNAL(sUpdateGraphMass()),this,SLOT(onUpdateGraphMass()),Qt::QueuedConnection);
    QObject::connect(this,SIGNAL(sUpdateGraphTIC()),this,SLOT(onUpdateGraphTIC()),Qt::QueuedConnection);
    connect(mChartMass,SIGNAL(lastFrame()),this,SLOT(on_UI_PB_LAST_clicked()));
    connect(mChartMass,SIGNAL(nextFrame()),this,SLOT(on_UI_PB_NEXT_clicked()));

    connect(this, SIGNAL(ChangedManager(QList<QPair<sChartWidget::XICInform*,myGroupBox*>>, bool )),
            mChartTIC,SLOT(on_ChangedManager(QList<QPair<sChartWidget::XICInform*,myGroupBox*>>, bool)));

    connect(this,SIGNAL(hideCurve(sChartWidget::XICInform*,bool)),mChartTIC,SLOT(onHideCurve(sChartWidget::XICInform*,bool)));
    connect(this,SIGNAL(deleteCurve(sChartWidget::XICInform*)),mChartTIC,SLOT(ondeleteCurve(sChartWidget::XICInform*)));
}

sDataAnalysis::~sDataAnalysis()
{
    if(mAnalyzeThread->isRunning()){
        mAnalyzeThread->stop();
        mAnalyzeThread->wait();
    }
    if(mAnalyzeThread)
        delete mAnalyzeThread;
    mAnalyzeThread=nullptr;
    if(mChartTIC)
        delete mChartTIC;
    mChartTIC=nullptr;
    if(mChartMass)
        delete mChartMass;
    mChartMass=nullptr;
    delete ui;
}

void sDataAnalysis::setDatapath(QString path)
{
    datapath = path;
}

bool sDataAnalysis::showDataTIC(QString fileName)
{
    if(fileName.isEmpty())
        return false;
    mFileNameTIC = fileName;
    if(mAnalyzeThread->isRunning())
        return false;
    m_TYPE_THREAD= _TYPE_TIC;
    mAnalyzeThread->start();
    return true;
}

bool sDataAnalysis::showDataMass(QString fileName, uint nFrame)
{
    if(fileName.isEmpty())
        return false;
    mFileNameMass= fileName;
    if(mAnalyzeThread->isRunning())
        return false;
    m_TYPE_THREAD= _TYPE_MASS;
    mFrame= nFrame;
    mAnalyzeThread->start();
    return true;
}

bool sDataAnalysis::showDataMass(QString fileName, uint nFrameB, uint nFrameE)
{
    if(fileName.isEmpty())
        return false;
    mFileNameMass= fileName;
    if(mAnalyzeThread->isRunning())
        return false;
    m_TYPE_THREAD= _TYPE_MASS_RANGE;
    mFrameRange.first=nFrameB;
    mFrameRange.second=nFrameE;
    //mFrame= nFrame;
    mAnalyzeThread->start();
    return true;
}

int sDataAnalysis::analyzeThread(void *pParam, const bool &bRunning)
{
    sDataAnalysis* pDataAnalysis = (sDataAnalysis*)pParam;
    if(!pDataAnalysis)
        return -1;
    if(pDataAnalysis->currentType()== sDataAnalysis::_TYPE_TIC){
        pDataAnalysis->mGraphBuffMutexTIC.lock();
        if(pDataAnalysis->loadFileTIC(pDataAnalysis->currentFileTIC(),
                                   pDataAnalysis->mDataTIC_X, pDataAnalysis->mDataTIC_Y))
            emit pDataAnalysis->sUpdateGraphTIC();
        pDataAnalysis->mGraphBuffMutexTIC.unlock();
    }else if(pDataAnalysis->currentType()== sDataAnalysis::_TYPE_MASS){
        pDataAnalysis->mGraphBuffMutexMass.lock();
        if(pDataAnalysis->loadFileMass(pDataAnalysis->currentFileMass(), pDataAnalysis->currentFrame(),
                                       pDataAnalysis->mDataMass_X, pDataAnalysis->mDataMass_Y, pDataAnalysis->mStreamHead))
        {
            emit pDataAnalysis->sUpdateGraphMass();
        }else
            qDebug()<<"E_MemoryOverflow";

#if 0
        if(pDataAnalysis->loadFileMass(pDataAnalysis->currentFileMass(), pDataAnalysis->currentFrame(),
                                       pDataAnalysis->mDataMass_Y, pDataAnalysis->mStreamHead)){
            _StreamHead* pStreamHead= (_StreamHead*)(pDataAnalysis->mStreamHead.data());
            if(!pStreamHead)
                return false;
            cParamValue::_EventLIT* pEventLIT= (cParamValue::_EventLIT*)&(pStreamHead->segment.fisrtEvent);
            if(!pEventLIT)
                return false;

            uint lengthSrc= pDataAnalysis->mDataMass_Y.size();
            if(pDataAnalysis->mDataMass_X.size()!= lengthSrc){
                pDataAnalysis->mDataMass_X.resize(lengthSrc);
                double dbVal = pEventLIT->msStart;
                double dbStep = (pEventLIT->msEnd - dbVal) / (double)lengthSrc;
                for(uint nIndex = 0; nIndex < lengthSrc; nIndex++){
                    pDataAnalysis->mDataMass_X[nIndex] = dbVal;
                    dbVal += dbStep;
                }
            }
            if(pDataAnalysis->AnalyzeScan(pDataAnalysis->mDataMass_X, pDataAnalysis->mDataMass_Y,
                                          lengthSrc, 8, false)){
                //isRestart=false;
                emit pDataAnalysis->sUpdateGraphMass();
            }else
                qDebug()<<"E_MemoryOverflow";
        }
#endif
        pDataAnalysis->mGraphBuffMutexMass.unlock();
    }else if(pDataAnalysis->currentType()== sDataAnalysis::_TYPE_MASS_RANGE){
        pDataAnalysis->mGraphBuffMutexMass.lock();
        if(pDataAnalysis->loadFileMass(pDataAnalysis->currentFileMass(), pDataAnalysis->mFrameRange.first,
                                       pDataAnalysis->mFrameRange.second, pDataAnalysis->mDataMass_Y, pDataAnalysis->mStreamHead)){
            _StreamHead* pStreamHead= (_StreamHead*)(pDataAnalysis->mStreamHead.data());
            if(!pStreamHead)
                return false;
            cParamValue::_EventLIT* pEventLIT= (cParamValue::_EventLIT*)&(pStreamHead->segment.fisrtEvent);
            if(!pEventLIT)
                return false;

            uint lengthSrc= pDataAnalysis->mDataMass_Y.size();
            if(pDataAnalysis->mDataMass_X.size()!= lengthSrc){
                pDataAnalysis->mDataMass_X.resize(lengthSrc);
                double dbVal = pEventLIT->msStart;
                double dbStep = (pEventLIT->msEnd - dbVal) / (double)lengthSrc;
                for(uint nIndex = 0; nIndex < lengthSrc; nIndex++){
                    pDataAnalysis->mDataMass_X[nIndex] = dbVal;
                    dbVal += dbStep;
                }
            }
            if(pDataAnalysis->AnalyzeScan(pDataAnalysis->mDataMass_X, pDataAnalysis->mDataMass_Y,
                                          lengthSrc, 8, false)){
                //isRestart=false;

                emit pDataAnalysis->sUpdateGraphMass();
            }else
                qDebug()<<"E_MemoryOverflow";
        }
        pDataAnalysis->mGraphBuffMutexMass.unlock();
    }
    return 0;
}

bool sDataAnalysis::AnalyzeScan(std::vector<double>& pX, std::vector<double>& pY, int uEvtValidPoint, uint uWidth, bool reStart)
{
#if 0
    if(mMarker->size()!= uEvtValidPoint)
        mMarker->resize(uEvtValidPoint);
    for(uint ii=0;ii<uEvtValidPoint;ii++)
        (*mMarker)[ii]=ii;
    mDataProcess->getData(pY, pY, reStart);
    if(mDataProcess->CentroidData(pX,pY,*mAbsc,*mOrd,*mStart,*mEnd,uWidth)==-1)//找峰
        return false;
#endif
//    mBaseLine.resize(uEvtValidPoint);
//    std::copy(pY.begin(),pY.end(),mBaseLine.begin());
//    step.resize(mStart.size());
//    for(uint i=0;i<step.size();i++){
//        step[i]=(mBaseLine[iEnd[i]]-mBaseLine[iStart[i]])/(iEnd[i]-iStart[i]);
//        for(int j=0;j<iEnd[i]-iStart[i];j++)
//            mBaseLine[iStart[i]+j]=step[i]*j+mBaseLine[iStart[i]];
//    }
//    for(uint i=0;i<uEvtValidPoint;i++)
//        mBaseLine[i]=pY[i]-mBaseLine[i];
//    double dNumerator=0,dDenominator=0;
//    for(uint i=0;i<iStart.size();i++){
//        dNumerator=0;
//        dDenominator=0;
//        for(int j=iStart[i];j<=iEnd[i];j++){
//            dNumerator += mDataBuff[0][j] * mBaseLine[j];
//            dDenominator += mBaseLine[j];
//        }
//        if(dDenominator>0.0000001||dDenominator<-0.0000001)
//            *mAbsc[i] = dNumerator / dDenominator;
//    }
#if 0
    sortGICAP::DateSort(*mAbsc, *mOrd, *mStart, *mEnd, cAbsc1, cOrd1, iStart1, iEnd1, *mMarker, uWidth);
    cFWHM=mDataProcess->GetHHFW(pX,pY,iStart1,iEnd1);//计算半高峰宽
    strMarker.resize(uWidth);
    if(cFWHM.size()>=uWidth){
        for(uint jj=0;jj<uWidth;jj++)
            strMarker[jj]=QString::number(cFWHM[jj])+"\n"+QString::number(cAbsc1[jj])+","+QString::number(cOrd1[jj]);
    }
    mGraphBuffMutex.lock();
    if(mGraphBuff[0]->size()!= uEvtValidPoint){
        mGraphBuff[0]->resize(uEvtValidPoint);
        mGraphBuff[1]->resize(uEvtValidPoint);
    }
    mGraphMarker.resize(uWidth);
    mGraphAbsc.resize(uWidth);
    mGraphOrd.resize(uWidth);
    std::copy(pX.begin(),pX.end(),mGraphBuff[0]->begin());
    std::copy(pY.begin(),pY.end(),mGraphBuff[1]->begin());
    std::copy(cAbsc1.begin(),cAbsc1.end(),mGraphAbsc.begin());
    std::copy(cOrd1.begin(),cOrd1.end(),mGraphOrd.begin());
    std::copy(strMarker.begin(),strMarker.end(),mGraphMarker.begin());
    mGraphBuffMutex.unlock();
#else

#endif
    return true;
}

void sDataAnalysis::onUpdateGraphMass()
{
    if(mGraphBuffMutexMass.tryLock(50)){
        _StreamHead* pStreamHead= (_StreamHead*)(mStreamHead.data());
        if(!pStreamHead)
            return;
        cParamValue::_EventLIT* pEventLIT= (cParamValue::_EventLIT*)&(pStreamHead->segment.fisrtEvent);
        if(!pEventLIT)
            return ;
        if(mDataMass_X.size()<=0)
            return ;

        if(currentType()== sDataAnalysis::_TYPE_TIC){
            mGraphBuffMutexMass.unlock();
            return;
        }else if(currentType()== sDataAnalysis::_TYPE_MASS){
            ui->labelCurrentPage->setText("Frame:"+QString::number(mCurrentMass));//mChartMass->setStyleM(TVPlot::Lines, "Frame:"+QString::number(mCurrentMass),pEventLIT->msStart, pEventLIT->msEnd);
            if(pStreamHead->typePlot == _StreamHead::profile)
                mChartMass->setStyleM(TVPlot::Lines, "Frame:"+QString::number(mCurrentMass),pEventLIT->msStart, pEventLIT->msEnd);
            else if(pStreamHead->typePlot == _StreamHead::sticks)
                mChartMass->setStyleM(TVPlot::Sticks, "Frame:"+QString::number(mCurrentMass),pEventLIT->msStart, pEventLIT->msEnd);
        }else if(currentType()== sDataAnalysis::_TYPE_MASS_RANGE){
            ui->labelCurrentPage->setText("Frame:"+QString::number(mFrameRange.first)+"-"+QString::number(mFrameRange.second));//mChartMass->setStyleM(TVPlot::Lines, "Frame:"+QString::number(mFrameRange.first)+" - "+
                                  //QString::number(mFrameRange.second),pEventLIT->msStart, pEventLIT->msEnd);
        }
        //mChartMass->SetMarker(mGraphAbsc,mGraphOrd,mGraphMarker);
        if(pStreamHead->typePlot == _StreamHead::sticks){
            mlistPeak_X.clear();
            mlistPeak_Y.clear();
            int size = mDataMass_X.size();
            mlistPeak_X.resize(size);
            mlistPeak_Y.resize(size);
            for(int i = 0; i<size ; i++){
                mPeakMarker.append(QString::number(((int)(mDataMass_Y[i]*10))/(double)10));
                mlistPeak_X[i] = mDataMass_X[i];
                mlistPeak_Y[i] = mDataMass_Y[i];
            }
            mChartMass->setSamples(mlistPeak_X, mlistPeak_Y);
        }else if(pStreamHead->typePlot == _StreamHead::profile){
            mChartMass->setSamples(mDataMass_X, mDataMass_Y);
            //计算峰位
            QVector<double> pData;
            QVector<int> pMark;
            if(Algorithm::getInstance()->getResult(pData,mDataMass_Y,pMark) != 1){
                qDebug() << "无峰...";
            }
            int size = pMark.size();
            mlistPeak_X.clear();
            mlistPeak_Y.clear();
            mlistPeak_X.resize(size);
            mlistPeak_Y.resize(size);
            for(int i = 0; i<size ; i++){
                mlistPeak_X[i] = mDataMass_X[pMark[i]];
                mlistPeak_Y[i] = mDataMass_Y[pMark[i]];
                mPeakMarker.append(QString::number(((int)(mDataMass_Y[pMark[i]]*10))/(double)10));
            }
            mChartMass->SetMarker(mlistPeak_X, mlistPeak_Y, mPeakMarker);
        }
        mGraphBuffMutexMass.unlock();
    }
}

void sDataAnalysis::onUpdateGraphTIC()
{
    if(mGraphBuffMutexTIC.tryLock(50)){
        int sizeTIC_X=mDataTIC_X.size();
        if(sizeTIC_X<=0)
            return ;
        mChartTIC->setStyleM(TVPlot::Lines, "",mDataTIC_X[0], mDataTIC_X[sizeTIC_X-1]);
        //mChartMass->SetMarker(mGraphAbsc,mGraphOrd,mGraphMarker);
        mChartTIC->setSamples(mDataTIC_X.data(), mDataTIC_Y.data(), mDataTIC_Y.size());
        mGraphBuffMutexTIC.unlock();
    }
}

void sDataAnalysis::on_UI_PB_LOAD_clicked()
{
//    QString fileName = QFileDialog::getOpenFileName(this,
//                                                     tr("Open File"),
//                                                     QDir::currentPath() + "\\data",
//                                                     "TIC Files(*.TIC)",
//                                                     0);
//    if (!fileName.isNull())
//        showDataTIC(fileName);
    if(ui->verticalWidget_2->isHidden())
        ui->verticalWidget_2->show();
    else
        ui->verticalWidget_2->hide();
}
void sDataAnalysis::onSelectedTIC(const double x)
{
    if(mFileNameTIC.isEmpty())
        return;

    double tempX = x;
    if(tempX <= mDataTIC_X[0])
        tempX = mDataTIC_X[0]+0.0000002;
    if(tempX >= mDataTIC_X[mDataTIC_X.size()-1])
        tempX = mDataTIC_X[mDataTIC_X.size()-1]-0.0000002;

    //double x=polygon.x();
    if(ui->UI_PB_TIC_CHOOSE->text()=="Disable"){
        if(mChartTIC->getLineMark().size()>1)
            return;
        mChartTIC->addLine(tempX);
    }else{
        if(mGraphBuffMutexTIC.tryLock(50)){
            int sizeTIC_X=mDataTIC_X.size()-1;
            for(int i=0;i<sizeTIC_X;++i){
                if((tempX-mDataTIC_X[i]>=0.0000001)&& (mDataTIC_X[i+1]-tempX>=0.0000001)){
                    if(mCurrentMass!= i){
                        mCurrentMass= i;
                        mChartTIC->clearLine();
                        mChartTIC->addLine(tempX);
                        showDataMass(currentFileTIC()+".dat",i);
                    }
                    mGraphBuffMutexTIC.unlock();
                    return;
                }
            }
            mGraphBuffMutexTIC.unlock();
        }
    }
}

void sDataAnalysis::on_UI_PB_NEXT_clicked()
{
    if(mGraphBuffMutexTIC.tryLock(50)){
        int sizeTIC_X=mDataTIC_X.size();
        if(sizeTIC_X>0){
            if(mCurrentMass+1 <sizeTIC_X){
                if(!showDataMass(currentFileTIC()+".dat",++mCurrentMass)){
                    --mCurrentMass;
                    qDebug()<<currentFileTIC()+".dat";
                }
            }
        }
        mGraphBuffMutexTIC.unlock();
    }
}

void sDataAnalysis::on_UI_PB_LAST_clicked()
{
    if(mGraphBuffMutexTIC.tryLock(50)){
        int sizeTIC_X=mDataTIC_X.size();
        if(sizeTIC_X>0){
            if(mCurrentMass-1 >=0){
                if(!showDataMass(currentFileTIC()+".dat",--mCurrentMass))
                    ++mCurrentMass;
            }
        }
        mGraphBuffMutexTIC.unlock();
    }
}

void sDataAnalysis::on_UI_PB_TIC_CHOOSE_clicked()
{
    if(ui->UI_PB_TIC_CHOOSE->text()=="Enable"){
        ui->UI_PB_TIC_CHOOSE->setText("Disable");
        ui->UI_PB_ACCTIC->setEnabled(true);
    }else{
        ui->UI_PB_TIC_CHOOSE->setText("Enable");
        ui->UI_PB_ACCTIC->setEnabled(false);
        mChartTIC->clearLine();
    }
}

void sDataAnalysis::on_UI_PB_ACCTIC_clicked()
{
    QList<double> tempList =mChartTIC->getLineMark();
    if(tempList.size()!=2)
        return;
    if(mGraphBuffMutexTIC.tryLock(50)){
        if(tempList[0]< tempList[1])
            showDataMass(currentFileTIC()+".dat", tempList[0], tempList[1]);
        else
            showDataMass(currentFileTIC()+".dat", tempList[1], tempList[0]);
        mGraphBuffMutexTIC.unlock();
    }
}

void sDataAnalysis::on_UI_PB_TIC_CLEAR_clicked()
{
    mChartTIC->clearLine();
}

void sDataAnalysis::onSelectedMass(const double x)
{
    if(mFileNameMass.isEmpty())
        return;

    double realX;
//    if(ui->UI_PB_MASS_CHOOSE->text()=="Disable")
//        mChartMass->addLine(x);
    if(ui->BtnAdd->text() == "选择峰位"){
        //计算出峰位对应质量数
        realX = caculMassNum(x);
        createXICListItem(realX);
    }
    if(ui->BtnAdd->text() == "确定"){
        select->reInitColor(XICInformList.last().first->color);
        XICInformList.removeLast();
        realX = caculMassNum(x);
        createXICListItem(realX);
        mChartTIC->update();
    }
}


void sDataAnalysis::createXICListItem(double mass)
{
    //新建XICInform
    sChartWidget::XICInform* tempXIC = new sChartWidget::XICInform();
    tempXIC->mass = mass;
    tempXIC->color = select->getColor();
    tempXIC->beginTime = (mCurrentMass-5<0)? 0 : (mCurrentMass-5);;
    tempXIC->endTime = (mCurrentMass+5>mDataTIC_X.size()-1)? (mDataTIC_X.size()-1) : (mCurrentMass+5);
    //根据质量轴算出XIC谱图
    int indexX = 0;
    int size = mDataMass_X.size()-1;
    for(int i = 0;i<size;i++){
        if(fabs(mDataMass_X[i]-mass)<0.01){
            indexX = i;
            break;
        }
    }
    if(!loadFileMassInX(currentFileMass(),mass,indexX,tempXIC->yListXIC,mStreamHead)){
        qDebug() << "加载失败--------------------------------";
        return;
    }

    tempXIC->yListXIC = mDataProcess->MovingAverageSmooth(tempXIC->yListXIC,tempXIC->yListXIC.size()/200*2+1);//tempXIC->yListXIC.size()/100+1);

    //计算XIC峰面积
    tempXIC->massArea = CSignalArea::SignalArea(mDataTIC_X,tempXIC->yListXIC,tempXIC->beginTime,tempXIC->endTime);

    mChartTIC->clearLine();
    mChartTIC->addLine(mDataTIC_X[tempXIC->beginTime],tempXIC->color);
    mChartTIC->addLine(mDataTIC_X[tempXIC->endTime],tempXIC->color);
    mChartMass->clearLine();
    mChartMass->addLine(mass,tempXIC->color);

    myGroupBox* tempGroupBox = new myGroupBox();
    tempGroupBox->setTitle(QString::number(mass));
    tempGroupBox->setContainer(QString::number(tempXIC->massArea));
    tempGroupBox->setColor(tempXIC->color);
    connect(tempGroupBox,SIGNAL(groupBoxClicked(myGroupBox*,bool)),this,SLOT(onGroupBoxClicked(myGroupBox*,bool)));
    connect(tempGroupBox,SIGNAL(groupBoxRemoved(myGroupBox*)),this,SLOT(onGroupBoxRemoved(myGroupBox*)));

    QPair<sChartWidget::XICInform*,myGroupBox*> tempPair;
    tempPair.first = tempXIC;
    tempPair.second = tempGroupBox;

    XICInformList.append(tempPair);
    ui->BtnAdd->setText("确定");
}

double sDataAnalysis::caculMassNum(double x)
{
//    std::vector<double> tempDataMass_X;
//    std::vector<double> tempDataMass_Y;
//    int minFrame,maxFrame;
//    minFrame = (mCurrentMass-5<0)? 0 : (mCurrentMass-5);
//    maxFrame = (mCurrentMass+5>mDataTIC_X.size()-1)? (mDataTIC_X.size()-1) : (mCurrentMass+5);

//    if(loadFileMass(currentFileMass(), minFrame, maxFrame, tempDataMass_Y,mStreamHead)){
//        _StreamHead* pStreamHead= (_StreamHead*)(mStreamHead.data());
//        if(!pStreamHead)
//            return false;
//        cParamValue::_EventLIT* pEventLIT= (cParamValue::_EventLIT*)&(pStreamHead->segment.fisrtEvent);
//        if(!pEventLIT)
//            return false;

//        uint lengthSrc= tempDataMass_Y.size();
//        if(tempDataMass_X.size()!= lengthSrc){
//            tempDataMass_X.resize(lengthSrc);
//            double dbVal = pEventLIT->msStart;
//            double dbStep = (pEventLIT->msEnd - dbVal) / (double)lengthSrc;
//            for(uint nIndex = 0; nIndex < lengthSrc; nIndex++){
//                tempDataMass_X[nIndex] = dbVal;
//                dbVal += dbStep;
//            }
//        }
//    }else{
//        return 0;
//    }

    //峰位计算
    return getMassNum(x,mlistPeak_X);
    //return getMassNum(x,mDataMass_X,mDataMass_Y);
}

double sDataAnalysis::getMassNum(double x, std::vector<double> vx, std::vector<double> vy)
{
    for(int i = 0;i<=vx.size()-1;i++) {
        if((x-vx[i]<0.01)&&(vx[i]-x<0.01)){
            if(vy[i]<vy[i+1]){
                //最高点在右侧
                while(vy[i]<vy[i+1]&&i<vx.size()){
                    i++;
                }
                return vx[i];
            }else
            {
                //最高点在左侧
                while(vy[i-1]>vy[i]&&i>0){
                    i--;
                }
                return vx[i];
            }
        }
    }
}

double sDataAnalysis::getMassNum(double x, std::vector<double> vx)
{
    if(vx.size() == 0)
        return x;
    double dx = fabs(vx[0]-x);
    double realX = vx[0];
    for(int i = 1 ; i< vx.size(); i++)
    {
        if(fabs(vx[i]-x) < dx){
            dx = fabs(vx[i]-x);
            realX = vx[i];
        }
    }
    return realX;
}

void sDataAnalysis::on_UI_PB_MASS_CHOOSE_clicked()
{
    if(ui->UI_PB_MASS_CHOOSE->text()=="Enable"){
        ui->UI_PB_MASS_CHOOSE->setText("Disable");
        ui->UI_PB_CALCULATE->setEnabled(true);
    }else{
        ui->UI_PB_MASS_CHOOSE->setText("Enable");
        ui->UI_PB_CALCULATE->setEnabled(false);
        mChartMass->clearLine();
    }
}

void sDataAnalysis::on_UI_PB_CALCULATE_clicked()
{
    QList<double> listMark= mChartMass->getLineMark();
    if(listMark.size()<2)
        return;
    if(!mGraphBuffMutexMass.tryLock(50))
        return;
    int tmpCount = mDataMass_X.size()-1;
    if (tmpCount < 1)
        return;
    qSort(listMark.begin(), listMark.end());
    int tmpPeak = listMark.size() >> 1 << 1;
    std::vector<int> tempStart, tempEnd;
    std::vector<double> tempFWHM, tempArea;
    for (int i = 0; i < tmpPeak; i += 2){
        if ((listMark[i] < mDataMass_X[tmpCount]) && (listMark[i] > mDataMass_X[0])
                && (listMark[i + 1] < mDataMass_X[tmpCount]) && (listMark[i + 1] > mDataMass_X[0])){
            bool tmpFirst = false;
            for (int tmpImdex = 0; tmpImdex < tmpCount; ++tmpImdex){
                if (!tmpFirst){
                    if ((listMark[i] - mDataMass_X[tmpImdex] >= 1e-8) && (listMark[i] - mDataMass_X[tmpImdex+1] <= 1e-8)){
                        tempStart.push_back(tmpImdex);
                        tmpFirst = true;
                    }
                }else{
                    if ((listMark[i + 1] - mDataMass_X[tmpImdex] >= -1e-8) && (listMark[i + 1] - mDataMass_X[tmpImdex+1] <= 1e-8)){
                        tempEnd.push_back(tmpImdex);
                        break;
                    }
                }
            }
        }
    }
    if (tempStart.size() == tempEnd.size()){
        tempFWHM = mDataProcess->GetHHFW(mDataMass_X, mDataMass_Y, tempStart, tempEnd);
        int sizeFWHM=tempFWHM.size();
        if (sizeFWHM> 0){
            tempArea= mDataProcess->SignalArea(mDataMass_X, mDataMass_Y, tempStart, tempEnd);
            if(tempArea.size()!= sizeFWHM)
                return;
            std::vector<double> tempX(sizeFWHM), tempY(sizeFWHM);
            QVector<QString> tempStrMark(sizeFWHM);
            for (int i = 0; i < sizeFWHM; ++i){
                int tmpIndexC = (tempEnd[i] - tempStart[i]) / 2 + tempStart[i];
                tempX[i]= mDataMass_X[tmpIndexC];
                tempY[i]= mDataMass_Y[tmpIndexC];
                tempStrMark[i]= "半高峰宽：" + QString::number(tempFWHM[i]) + "\r\n峰面积："+ QString::number(tempArea[i]);
            }
            mChartMass->SetMarker(tempX, tempY, tempStrMark);
        }
    }
    mGraphBuffMutexMass.unlock();
}

void sDataAnalysis::on_UI_PB_MASS_CLEAR_clicked()
{
    mChartMass->clearLine();
}

void sDataAnalysis::onCurrentItemChanged(QListWidgetItem *newItem, QListWidgetItem *proItem)
{
    if(XICInformList.size() != 0){
        XICInformList.clear();
        mChartTIC->clearMycurve();
    }
    QString dataPath = fileListWidget->getDatapath();
    QString fileName = dataPath + "/" + newItem->text();
    qDebug() << fileName << "-------------------------";
    if (!fileName.isNull())
        showDataTIC(fileName);
    QFileInfo info(fileName);
    QString fileInfo = info.created().toString("yyyy-MM-dd hh:mm:ss");
    ui->labelFileName->setText(newItem->text());
    ui->labelFileTime->setText(fileInfo);   
}


void sDataAnalysis::on_pushButton_clicked()
{
    if(ui->verticalWidget_2->isHidden()){
        fileListWidget = new FileListWidget(datapath);
        ui->verticalLayout_6->addWidget(fileListWidget);
        connect(fileListWidget,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,SLOT(onCurrentItemChanged(QListWidgetItem*,QListWidgetItem*)));
        connect(fileListWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(onListDoubleClicked(QModelIndex)));
        ui->verticalWidget_2->show();
        ui->delBtn->hide();
        ui->pushButton->setStyleSheet(QStringLiteral("border-image: url(:/picture/Icon_Right.jpg);"));
    }
    else{
        ui->verticalLayout_6->removeWidget(fileListWidget);
        delete fileListWidget;
        ui->delBtn->hide();
        ui->verticalWidget_2->hide();
        ui->pushButton->setStyleSheet(QStringLiteral("border-image: url(:/picture/Icon_Left.jpg);"));
    }
}

void sDataAnalysis::onListDoubleClicked(QModelIndex qmi)
{
    ui->delBtn->show();
    connect(ui->delBtn,SIGNAL(clicked()),this,SLOT(onDelClicked()));
}

void sDataAnalysis::onDelClicked()
{
    //删除文件
    fileListWidget->removeFile(fileListWidget->currentRow());
    fileListWidget->takeItem(fileListWidget->currentRow());    
    ui->delBtn->hide();
}

void sDataAnalysis::onGetCurrentFilePath(QString TICFile, QString MassFile,bool state)
{
    if(TICFile.isEmpty() || MassFile.isEmpty())
        return;
    showDataTIC(TICFile);
    mFileNameMass = MassFile;
    isOriginal = state;
}




void sDataAnalysis::on_BtnAdd_clicked()
{
    if(mFileNameMass.isEmpty())
        return;
    if(ui->BtnAdd->text() == "添加通道")
    //高亮表示可以选择质量数
        ui->BtnAdd->setText("选择峰位");

    if(ui->BtnAdd->text() == "确定"){
        ui->BtnAdd->setText("添加通道");
        isEdit = true;
        modifyList();
        mChartTIC->drawXIC(mDataTIC_X);
        manageGroupBox();
    }
}

void sDataAnalysis::manageGroupBox()
{
    foreach (auto XIC, XICInformList) {
        if(XIC == XICInformList.last())
            break;
        XIC.second->setState(false);
        emit hideCurve(XIC.first,false);
    }
    ui->HLayout_XICList->addWidget(XICInformList.last().second);
}

void sDataAnalysis::modifyList()
{
    emit ChangedManager(XICInformList, true);
}

void sDataAnalysis::onGroupBoxClicked(myGroupBox *groupBox, bool state)
{
    mChartMass->clearLine();
    mChartTIC->clearLine();
    foreach (auto XIC, XICInformList) {
        if(groupBox == XIC.second){
            if(state)
            {
                isEdit = true;
                mChartMass->addLine(XIC.first->mass,XIC.first->color);
                mChartTIC->addLine(mDataTIC_X[XIC.first->beginTime],XIC.first->color);
                mChartTIC->addLine(mDataTIC_X[XIC.first->endTime],XIC.first->color);
            }
            emit hideCurve(XIC.first,state);
        }else{
            XIC.second->setState(false);
            emit hideCurve(XIC.first,false);
        }
    }

}

void sDataAnalysis::onGroupBoxRemoved(myGroupBox *groupBox)
{
    isEdit = false;
    foreach (auto XIC, XICInformList) {
        if(groupBox == XIC.second){
            select->reInitColor(groupBox->getColor());
            emit deleteCurve(XIC.first);
            XICInformList.removeOne(XIC);
        }
    }

}

bool sDataAnalysis::eventFilter(QObject *watched, QEvent *event)
{
    if(isEdit == false || XICInformList.isEmpty())
        return QWidget::eventFilter(watched,event);

    if(watched == (QObject*)ui->widgetForTouch)
    {
//        if(event->type() == QEvent::Gesture)
//        {
//            return gestureEvent(static_cast<QGestureEvent*>(event));
//        }

//        if(event->type() == QEvent::TouchBegin)
//        {
//            QTouchEvent* e = static_cast<QTouchEvent*> (event);
//            QTouchEvent::TouchPoint p = e->touchPoints().at(0);
//            switch (e->touchPointStates()) {
//            case Qt::TouchPointPressed:
//            {
//                int x = p.pos().x();
//                //                if(x <= ui->widgetForTouch->width()/2)
//                //                    currentLine = leftLine;
//                //                if(x > ui->widgetForTouch->width()/2)
//                //                    currentLine = rightLine;
//            }
//                break;
//            case Qt::TouchPointMoved:
//            {
//                int move = p.lastPos().x()-p.startPos().x();
//                changeLinePos(move);
//            }
//                break;
//            default:
//                break;
//            }
//        }

        if(event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent* e = static_cast<QMouseEvent*> (event);
            touchPointX = e->pos().x();
            ui->labelMin->setText(QString::number(touchPointX));
        }

        if(event->type() == QEvent::MouseMove)
        {
            if(touchPointX == -1)
                return QWidget::eventFilter(watched,event);
            QMouseEvent* e = static_cast<QMouseEvent*> (event);
            int move = e->pos().x() - touchPointX;
            ui->labelMax->setText(QString::number(e->pos().x()));
            touchPointX = e->pos().x();
            ui->labelMin->setText(QString::number(touchPointX));
            changeLinePos(move);
        }

    }else
    {
        touchPointX = -1;
    }
    update();
    return QWidget::eventFilter(watched,event);
}

bool sDataAnalysis::gestureEvent(QGestureEvent *event)
{
    if(QGesture* pan = event->gesture(Qt::PanGesture))
        panTriggered(static_cast<QPanGesture*>(pan));
    if(QGesture* pinch = event->gesture(Qt::PinchGesture))
        pinchTriggered(static_cast<QPinchGesture*>(pinch));
    return true;
}

void sDataAnalysis::panTriggered(QPanGesture *pan)
{
    QPointF point = pan->lastOffset();

    changeLinePos(point.x(),point.x());
}

void sDataAnalysis::pinchTriggered(QPinchGesture *pinch)
{
    QPinchGesture::ChangeFlags changeFlags = pinch->changeFlags();

    if (changeFlags & QPinchGesture::ScaleFactorChanged) {
        //如果是两指放缩比例改变，则放缩
        double lastScale = pinch->lastScaleFactor();
        int move = lastScale*this->width();
        changeLinePos(-move,move);
    }

    if (pinch->state() == Qt::GestureFinished) {

    }
    update();
}

void sDataAnalysis::changeLinePos(int move)
{
    QPair<sChartWidget::XICInform*,myGroupBox*> tempXIC = getCurrentCurve();
    if(touchPointX > ui->widgetForTouch->pos().x() && touchPointX < ui->widgetForTouch->pos().x()+ui->widgetForTouch->width()/2)
    {
        int tempValue1 = move*mDataTIC_X[mDataTIC_X.size()-1]/ui->widgetForTouch->width() + tempXIC.first->beginTime;
        tempXIC.first->beginTime = getRightValue(1,tempValue1,tempXIC.first->endTime-1);
        //ui->labelMin->setText(QString::number(mDataTIC_X[tempXIC.first->beginTime]));
        updateTIC(tempXIC);
    }else if(touchPointX < ui->widgetForTouch->pos().x()+ui->widgetForTouch->width())
    {
        int tempValue2 = move*mDataTIC_X[mDataTIC_X.size()-1]/ui->widgetForTouch->width() + tempXIC.first->endTime;
        tempXIC.first->endTime = getRightValue(tempXIC.first->beginTime+1,tempValue2,mDataTIC_X.size()-1);
        ui->labelMax->setText(QString::number(mDataTIC_X[tempXIC.first->endTime]));
        updateTIC(tempXIC);
    }
}

void sDataAnalysis::changeLinePos(int movex, int movey)
{
    QPair<sChartWidget::XICInform*,myGroupBox*> tempXIC = getCurrentCurve();

    int tempValue1 = movex*mDataTIC_X[mDataTIC_X.size()-1]/ui->widgetForTouch->width() + tempXIC.first->beginTime;
    tempXIC.first->beginTime = getRightValue(1,tempValue1,tempXIC.first->endTime-1);
    //ui->labelMin->setText(QString::number(mDataTIC_X[tempXIC.first->beginTime]));

    int tempValue2 = movey*mDataTIC_X[mDataTIC_X.size()-1]/ui->widgetForTouch->width() + tempXIC.first->endTime;
    tempXIC.first->endTime = getRightValue(tempXIC.first->beginTime+1,tempValue2,mDataTIC_X.size()-1);
    ui->labelMax->setText(QString::number(mDataTIC_X[tempXIC.first->endTime]));
    updateTIC(tempXIC);

}

QPair<sChartWidget::XICInform *, myGroupBox *> sDataAnalysis::getCurrentCurve()
{
    foreach (auto XIC, XICInformList) {
        if(XIC.second->isChecked())
            return XIC;
    }
}

void sDataAnalysis::updateTIC(QPair<sChartWidget::XICInform *, myGroupBox *> tempTIC)
{
    //画线
    mChartTIC->clearLine();
    mChartTIC->addLine(mDataTIC_X[tempTIC.first->beginTime],tempTIC.first->color);
    mChartTIC->addLine(mDataTIC_X[tempTIC.first->endTime],tempTIC.first->color);
    //计算峰面积
    tempTIC.first->massArea = CSignalArea::SignalArea(mDataTIC_X,tempTIC.first->yListXIC,tempTIC.first->beginTime,tempTIC.first->endTime);
    //修改groupBox
    tempTIC.second->setContainer(QString::number(tempTIC.first->massArea));
}


void sDataAnalysis::on_BtnChange_clicked()
{
    mChartMass->clearLine();
    mChartTIC->clearLine();
    foreach (auto XIC, XICInformList) {
        XIC.second->setState(false);
        mChartMass->addLine(XIC.first->mass,XIC.first->color);
        emit hideCurve(XIC.first,true);
    }
    isEdit = false;
}

void sDataAnalysis::on_btn_saveFrame_clicked()
{
    if(mFileNameMass.isEmpty())
        return;
    QString fileName = fileListWidget->getDatapath()+"/"+ui->labelFileName->text()+QString::number(currentFrame())+".txt";
    QFile *file = new QFile();
    if(file->exists(fileName))
        return;
    file->setFileName(fileName);
    if(!file->open(QIODevice::WriteOnly|QIODevice::Text))
        return;
    QString pData;
    int size = mDataMass_X.size();
    for(int i = 0; i<size; i++){
        QString temp = QString::number(mDataMass_X[i]) + "\t" + QString::number(mDataMass_Y[i]) + "\n";
        pData += temp;
    }

    file->write(pData.toUtf8());
    file->flush();
    file->close();
}
