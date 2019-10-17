#ifndef SMETHOD_H
#define SMETHOD_H

#include "cParamCCS.h"

#include <QWidget>
#include <msMethed/cMethod.h>
#include <tool/sthread.h>
#include <QScriptEngine>
#include "AllScan.h"
#include "QSwitchButton.h"
#include "cConfigOMS.h"
#define MIN_HOLDTIME ((double)0.01)//ms
#define MAX_HOLDTIME ((double)500.0)//ms
#define AGCMIN 0.0
#define AGCMAX 0.023

namespace Ui {
class sMethod;
}

class sMethod : public QWidget
{
    Q_OBJECT

public:
    explicit sMethod(QScriptEngine* pScriptEngine, QWidget *parent = 0);
    ~sMethod();
    double mThresholdAGC=99999.99999;
    bool loadFile(bool ifUpdateUI=false, QString qPath=nullptr);
    _CONGIG_OMS::_CONGIG_METHOD* getConfig(){
        return &mCONGIG_METHOD;
    }
    bool getPolarity();
    void setPolarity(bool);
    void setFilePath(QString path) { filePath = path; }

    bool scan(bool ifAGC=false);
    bool getAGC();
    bool adjustParamAGC(double current);
    bool startMethodScan();

private slots:
    void on_allSacnBtn_clicked();
    void on_simBtn_clicked();
    void on_msnBtn_clicked();
    void onSwitchClicked(bool);

protected:
    SThread* mAnalyzeThread= nullptr;
    static int analyzeThread(void *pParam, const bool &bRunning);

    void paintEvent(QPaintEvent*);

private:

    struct _PARAM_SHARE{
        QString PhaseAC= 0;
        QString DutyCycleAC= 0;
        QString VoltageAC= 0;
        QString VoltageRF= 0;

        QString FrontCapOn= 0;
        QString FrontCapOff= 0;
        QString BackCap= 0;
        QString FeildVoltage= 0;

        QString OffsetQArray= 0;
        QString VoltQArray= 0;
        QString Dynode= 0;
        QString Multiplier= 0;
        QString FAE = 0;
        QString OrificeBias = 0;
    };

    QString currentname;
    double methods[3];
    Ui::sMethod *ui;
    _CONGIG_OMS::_CONGIG_METHOD mCONGIG_METHOD;
    AllScan* allScan;
    QWidget* mParent=nullptr;
    _PARAM_SHARE mPARAM_SHARE;
    CMethod mMethod;
    //QVector<uint>* mBufferCCS=nullptr;
    QByteArray* mBufferCCS=nullptr;
    _Adjust_Factor mAdjustFactor;
    ParamCCS::_DAQ_CONFIG* mDAQ_CONFIG= nullptr;

    _Injection_Param mInjectionFullScan;
    _Injection_Param proInjectionFullScan;
    _Cooling_Param mCoolingFullScan;
    QByteArray mSegment;
    _Scan_Param mScanFullScan;
    _Empty_Param mEmptyFullScan;
    //QList<QPair<sTargetMass*,_Scan_Param>> mListScan;
    QString btn_style[4];
    QString filePath;

    bool isFullScan = true;
    QList<double> massNumList;
    int massNumCount = 0;
    QScriptEngine* mScriptEngine;

    cParamValue::_Segment* getSegmentParam(){
        return (cParamValue::_Segment*)mSegment.data();
    }
    bool getParam(_Injection_Param& pInjection_Param);
    bool getParam(_Cooling_Param& pCooling_Param);
    bool getParam(_Scan_Param& pScan_Param);
    bool getParam(_Empty_Param& pEmpty_Param);

    bool createMethodFullScan(int& LengthMS);
    bool createMethodScan(int& LengthMS, bool isFullScan);
    bool createMethodScan(int& LengthMS, QString& fileHead, bool isFullScan);

    QString adjust2string(_Adjust_Factor& pAdjust_Factor);
    QString method2string(_LIT_PARAM& pLIT_PARAM);
    _CONGIG_OMS::_PARAM_FIT mCALIBRATE;

    void calibration(double& pValue );
    double calcThresholdAGC(QScriptEngine* pScriptEngine,
                                   _Injection_Param& pInjectionFullScan,
                                   _Scan_Param& pScanFullScan);
    double limitInjectionTime(QScriptEngine* pScriptEngine, _Injection_Param& pInjectionFullScan);

signals:
    void StartScan(char* ,int ,QString&,QByteArray&);
    void polaritySwitched(bool state);
    void StartAGC(char* ,int );
};

#endif // SMETHOD_H
