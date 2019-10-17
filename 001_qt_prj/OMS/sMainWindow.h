#ifndef SMAINWINDOW_H
#define SMAINWINDOW_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include "sCommandUSB.h"
#include "sDataAcquisiton.h"
#include "sDataAnalysis.h"
#include "sSystem.h"
#include "sMethod.h"
#include "sSystemState.h"
#include "Temperature.h"
#include "HighPre.h"
#include "SaveFile.h"
#include "tool/SerialPort.h"
#include <QScriptEngine>


#define HIGH 6.5
#define MID 6.0
#define LOW 3.3

namespace Ui {
class sMainWindow;
}

class sMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit sMainWindow(QWidget *parent = 0);
    ~sMainWindow();
    void setCurrentWindow(QWidget& pWidget);
    sSystem* getSystemWidget() { return mSystem; }

    struct _CMD_SSC_REQ{
        int Value_TEMP[TEMP_WIDTH];
        int Value_DAC[DAC_WIDTH_GET];
        int pump_speed;
        int pump_current;
    }mCMD_SSC_REQ;

    double getVacuumNum() { return vacuumNum; }
    void elecPumpCCSCMD(bool state);

private slots:
    void on_UI_PB_METHOD_clicked();
    void on_UI_PB_ACQUISITION_clicked();
    void on_UI_PB_ANALYSIS_clicked();
    void on_UI_PB_SYSTEM_clicked();
    void closeEvent ( QCloseEvent * e );
    void onStartScanManualTuning(char* ,uint , QByteArray& );
    //void onStartScanMethod(char* ,uint , QByteArray&,QString);
    void onStartScanMethod(char* ,int , QString&, QByteArray&);
    void on_UI_PB_STOP_clicked();
    void onUserInfo(QString name);
    void timerUpdate();

    void onSaveInfo(QString text);

    void onSystemStateChanged();
    void onSysInfo(bool state);
    void onTipSend(QString str);
    void onTuningState();
    void onStopTuning();

    void on_snapBtn_clicked();
    void onStopScan()
    {
        stopAcquisiton();
    }

    void onPolaritySwitched(bool);

    void onStartAGC(char* pData,int nLength){
        mCommandUSB->scanCCS(pData, nLength);
    }
    void onAGC(double );
    void onGetData(QByteArray);
    void onLoseSSC();

private:
    Ui::sMainWindow *ui;
    QScriptEngine mScriptEngine;
    CommandUSB* mCommandUSB;
    Temperature* temp;
    SaveFile* savefile;
    HighPre* highPre;
    sDataAcquisiton mDataAcquisiton;
    sDataAnalysis mDataAnalysis;
    sSystem* mSystem;
    sMethod* mMethod;
    sSystemState mSystemState;
    QByteArray mGraphBuffer;
    QString filePath;
    SerialPort* port = nullptr;
    int mCurrentCMD= 0;
    double vacuumNum = 0;
    bool isFirst = true;

    bool bSwitch = true;
    bool bControlCMD = true;
    bool pumpEnable = false;

    void closeSystem();

    QList<QByteArray> mSerialPortCMD;
    int mTimerStateID = -1;
    void timerEvent(QTimerEvent *evt);
    void stopAcquisiton();
    //bool startAcquisiton(char* pData,uint nLength, QByteArray& pSegment, bool saveFile=false);
    bool startAcquisiton(char* pData,uint32_t nLength, QByteArray& pSegment, QString* fileHead= nullptr, bool saveFile=false);
    bool state_running = false;
    void initWidgetPos();
    void initWidget();
    void outTuningState();
    void showDrive(QByteArray temp);
protected:
    void paintEvent(QPaintEvent* e);
    bool eventFilter(QObject *watched, QEvent *event);

signals:
    void showLogin();
    void showCurrentFile(bool state);
    void firstState(double);
};

#endif // SMAINWINDOW_H
