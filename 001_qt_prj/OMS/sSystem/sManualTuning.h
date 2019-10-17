#ifndef sManualTuning_H
#define sManualTuning_H

#include <QWidget>
#include <cParamCCS.h>
#include <sChartWidget.h>
#include <msMethed/cMethod.h>
#include <tool/sthread.h>
#include <QEvent>
#include <QObject>
#include "LibWidget/sFileDir.h"
#include "cConfigOMS.h"
#include "sWidgetCalibration.h"
#include "myLineEdit.h"
#include "./cDataProcess.h"

namespace Ui {
class sManualTuning;
}

class sManualTuning : public QWidget
{
    Q_OBJECT

public:
    struct _STRUCT_DATA{
        uint uEvtValidPoint=0,//uPrePoint+ uEventPoint+ uPostPoint
        uPrePoint=0,
        uEventPoint=0,//without pre post
        uPostPoint=0;
    };
    struct _STRUCT_CALIBRATE:public QMutex{
    public:
        _STRUCT_CALIBRATE():QMutex(){}
        bool changed= false;
        _CONGIG_OMS::_PARAM_FIT mPARAM_FIT;
    }mCALIBRATE;
    explicit sManualTuning(ParamCCS::_DAQ_CONFIG* pDAQ_CONFIG, QWidget *parent = 0);
    ~sManualTuning();
    bool loadFile(bool ifUpdateUI=false, QString qPath=nullptr);
    bool saveFile(QString qPath=nullptr);

    cParamValue::_Segment* getSegmentParam(QByteArray* pArray= nullptr){
        if(pArray)
            return (cParamValue::_Segment*)pArray->data();
        else
            return (cParamValue::_Segment*)mSegment.data();
    }
    QByteArray getSegment(){
        return mSegment;
    }
    bool dataDismantle(QByteArray& pByteArray);
    uint updateGraph(QByteArray& pByteArray, cParamValue::_Segment* pSegment,
                     QList<std::vector<double>>* pListX, QList<std::vector<double>>* pListY, QList<_STRUCT_DATA>& pSTRUCT_DATA, bool isRestart);
    void stop(){
        if(mAnalyzeThread->isRunning()){
            mAnalyzeThread->stop();
            mAnalyzeThread->wait();
        }
    }
    bool startDataAcquisiton(QByteArray& pSegment);
    void updateConfig();
    void changeCloseButton();

public:
    QByteArray mGraphBuffer;
    QMutex mGraphBuffMutex;
    QList<std::vector<double>>* mGraphBuffX;//std::vector<double>* mGraphBuff[2];         //size-allPoint
    QList<std::vector<double>>* mGraphBuffY;
    QList<_STRUCT_GRAPH>* mList_PEAK;
    QList<std::vector<double>>* mBaseLine = nullptr;              //size-allPoint
    cDataProcess* mDataProcess= nullptr;
    bool AnalyzeScan(double* pX, double* pY, _STRUCT_DATA& pSTRUCT_DATA,
                     int currentEvt, int countEvt, _STRUCT_PEAK& pSTRUCT_PEAK,uint uWidth);
    _CONGIG_OMS::_CONGIG_MANUAL_TUNING* getConfig(){
        return &mCONGIG_MANUAL_TUNING;
    }

    void setFilePath(QString path) { filePath = path; }

private slots:
    void on_UI_PB_TUNING_SCAN_clicked();
    void on_UI_PB_LOADFILE_clicked();
    void on_UI_PB_SAVEFILE_clicked();
    void on_UI_PB_OK_clicked();
    void on_UI_PB_CANCEL_clicked();
    void on_UI_PB_TARGET_clicked();
    void on_UI_PB_FULL_clicked();
    void on_UI_PB_TUNING_FIT_clicked();

    void on_UI_PB_BASELINE_clicked();

public slots:
    void onUpdateGraph(int);
    void onSelectFile(bool,QString);
    void onCalibrat();
    void onTipSend(int min,int max);

protected:
    SThread* mAnalyzeThread= nullptr;
    static int analyzeThread(void *pParam, const bool &bRunning);

private:
    Ui::sManualTuning *ui;
    QWidget* mParent=nullptr;
    sWidgetCalibration* mWidgetCalibration= nullptr;
    _CONGIG_OMS::_CONGIG_MANUAL_TUNING mCONGIG_MANUAL_TUNING;//changed in class sSystem
    sFileDir* mFileDir=nullptr;
    CMethod mMethod;
    QByteArray* mBufferCCS=nullptr;
    _Adjust_Factor mAdjustFactor;
    ParamCCS::_DAQ_CONFIG* mDAQ_CONFIG= nullptr;
    sChartWidget* mChartWidget;
    QList<QPair<sChartWidget*,_Scan_Param>> mChartTarget;
    _Injection_Param proInjectionFullScan;
    _Injection_Param mInjectionFullScan;
    _Cooling_Param mCoolingFullScan;
    QByteArray mSegment;
    _Scan_Param mScanFullScan;
    _Empty_Param mEmptyFullScan;

    QString temp_FAE;
    QString temp_OrificeBias;

    bool state = false;

    QString filePath;

    void memoryInit();
    bool getParam(_Injection_Param& pInjection_Param);
    bool getParam(_Cooling_Param& pCooling_Param);
    bool getParam(_Scan_Param& pScan_Param);
    bool getParam(_Empty_Param& pEmpty_Param);
    bool createMethodScan(int& LengthMS, bool isFullScan);
    void showWindow(QWidget* pWidget);

    inline void calibration(double* pFirst, double* pLast, double *bFirst, double dbVal, double dbStep);
    inline void calibration(double* pFirst, double* pLast, cParamValue::_EventLIT* pEventLIT, _STRUCT_DATA* tempSTRUCT_DATA);
    QString strCalibratP(_CONGIG_OMS::_PARAM_FIT& tempPARAM_FIT);
    void calibration(double& pValue);


signals:
    void ShowSystem();
    void StartScan(char* ,uint ,QByteArray&);
    void StopScan(void);
    void sUpdateGraph(int);
    void tipSend(QString str);
    void stopTuning();
};

#endif // sManualTuning_H
