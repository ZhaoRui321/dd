#ifndef SDATAACQUISITON_H
#define SDATAACQUISITON_H

#include "sChartWidget.h"
#include <QWidget>
#include <tool/sthread.h>
#include <cParamCCS.h>
#include "cDataProcess.h"
#include "cPublicCCS.h"
#include "cConfigOMS.h"
#include "cLoadDataFile.h"

namespace Ui {
class sDataAcquisiton;
}

class sDataAcquisiton : public QWidget
{
    Q_OBJECT

public:
    struct _STRUCT_DATA{
        uint32_t uEvtValidPoint=0,//uPrePoint+ uEventPoint+ uPostPoint
        uPrePoint=0,
        uEventPoint=0,//without pre post
        uPostPoint=0;
    };
    struct _STRUCT_TIC:public QMutex{
    public:
        _STRUCT_TIC():QMutex(){}
        std::vector<double> xTIC;
        std::vector<double> yTIC;
        void clear(){
            lock();
            xTIC.clear();
            yTIC.clear();
            unlock();
        }
        void append(double x, double y){
            lock();
            xTIC.push_back(x);
            yTIC.push_back(y);
            unlock();
        }
        uint32_t size(){
            return xTIC.size();
        }
        void resizeFit(){
            lock();

            xTIC.erase(xTIC.begin(),xTIC.begin()+xTIC.size()/2);
            yTIC.erase(yTIC.begin(),yTIC.begin()+yTIC.size()/2);

            xTIC.shrink_to_fit();
            yTIC.shrink_to_fit();
//            xTIC.clear();
//            yTIC.clear();
            unlock();
        }
    }mSTRUCT_TIC;

    explicit sDataAcquisiton(QWidget *parent = 0);
    ~sDataAcquisiton();
    uint32_t dataDismantleFirst(QByteArray& pByteArray, cParamValue::_Segment* pSegment,
                     QList<std::vector<double>>* pListX, QList<std::vector<double>>* pListY, QList<_STRUCT_DATA>& pSTRUCT_DATA, bool restart=false);
    bool dataDismantleSecond(const QByteArray& pByteArray,QList<std::vector<double>>* pListY,
                                              const QList<_STRUCT_DATA>& pSTRUCT_DATA);

    void setTICValue(QString value);

    cParamValue::_Segment* getSegmentParam(QByteArray* pArray= nullptr){
        if(pArray)
            return (cParamValue::_Segment*)pArray->data();
        else
            return (cParamValue::_Segment*)mSegment.data();
    }
    QByteArray getSegment(){
        return mSegment;
    }
    bool dataDismantleTIC(QByteArray& pByteArray, double& xTIC, double& yTIC);
    bool loadFile(bool ifUpdateUI=false, QString qPath=nullptr);
    void setDatapath(QString path);
    void SetIsAdmin(bool state)
    {
        isAdmin = state;
    }

    void setIsProfile(const _StreamHead::Type_Plot state){
        isProfile = state;
    }

public:
    QByteArray mGraphBuffer;
    QList<std::vector<double>>* mGraphBuffX;//std::vector<double>* mGraphBuff[2];         //size-allPoint
    QList<std::vector<double>>* mGraphBuffY;
    QList<_STRUCT_GRAPH>* mList_PEAK;
    QList<std::vector<double>>* mBaseLine = nullptr;
    double Baseline_Average = 0;
    //vector<double> mBaseLine;              //size-allPoint

    _CONGIG_OMS::_CONGIG_ACQUISITION* getConfig(){
        return &mCONGIG_ACQUISITION;
    }

    cDataProcess* mDataProcess= nullptr;
    QByteArray mSegment;
    void initTIC(){
        mSTRUCT_TIC.clear();
        mChartTIC->clearBuffXIC();
    }
    bool AnalyzeScan(double* pX, double* pY, _STRUCT_DATA& pSTRUCT_DATA,
                     int currentEvt, int countEvt, _STRUCT_PEAK& pSTRUCT_PEAK,uint32_t uWidth);
    bool AnalyzeXIC(double* pX, double* pY, _STRUCT_DATA& pSTRUCT_DATA,uint32_t currentEvt,uint32_t sizeTIC);
    bool AnalyzeXIC(uint32_t currentEvt, uint32_t sizeTIC);

    bool startDataAcquisiton(QByteArray&, QString fileHead, bool saveState);
    void stop(){
        if(mAnalyzeThread->isRunning()){
            mAnalyzeThread->stop();
            mAnalyzeThread->wait();
        }
    }
    void resizeChart(int size);
    bool isOriginal();
    inline void calibration(double* pFirst, double* pLast, double dbVal, double dbStep);
    inline void calibration(double* pFirst, double* pLast, double *baseline, cParamValue::_EventLIT* pEventLIT, _STRUCT_DATA* tempSTRUCT_DATA);

    void setFileHead(char* pHead, uint lengthHead){
        mFileHead.resize(lengthHead);
        memcpy(mFileHead.data(), pHead, lengthHead);
    }

    bool getIsSave() { return isSave;}
    cLoadDataFile* getLoadDataFile() { return mLoadDataFile; }
    QByteArray getFileHead() { return mFileHead; }

    void renameFile(char* pName,int lengthName)
    {
        if(mLoadDataFile)
            mLoadDataFile->renameFile(pName,lengthName);
    }
    void renameFile(QString fileName)
    {
        if(mLoadDataFile)
            mLoadDataFile->renameFile(fileName);
    }

protected:
    SThread* mAnalyzeThread= nullptr;
    static int analyzeThread(void *pParam, const bool &bRunning);

private:
    Ui::sDataAcquisiton *ui;
    sChartWidget* mChartTIC=nullptr;
    QList<sChartWidget*> mMassChart;//
    QMutex mGraphBuffMutex;
    _CONGIG_OMS::_CONGIG_ACQUISITION mCONGIG_ACQUISITION;
    //std::vector<double> mXicX;
    void memoryInit();
    _CONGIG_OMS::_PARAM_FIT mCALIBRATE;
    QString filePath;
    bool isAdmin = false;
    cLoadDataFile* mLoadDataFile=nullptr;
    QByteArray mFileHead;
    bool isSave = false;
    _StreamHead::Type_Plot isProfile = _StreamHead::sticks;

signals:
    void sUpdateGraph(int);
    void sUpdateTIC(int);
    //void sUpdateXIC();
    void sAGC(double);

public slots:
    void onUpdateGraph(int);
    void onUpdateTIC(int sizeTIC);

private slots:
    void on_UI_PB_ORIGINAL_clicked();
    //void on_ChangedXIC(QString strPropXIC);
    void on_UI_PB_PROCESS_clicked();
    void on_btnSlide_clicked();
    void on_btnRange_clicked();
};

#endif // SDATAACQUISITON_H
