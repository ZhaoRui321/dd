#ifndef SSYSTEM_H
#define SSYSTEM_H

#include <QWidget>
#include <QPaintEvent>
#include <QScriptEngine>
#include "sSystem/sAutoTuning.h"
#include "sSystem/sManualTuning.h"
#include "MassAxisAdjust.h"
#include <QCoreApplication>
#include "sControlSSC.h"
#include "sSystem/MyControl.h"
#include "sPwmCCS.h"

namespace Ui {
class sSystem;
}

class sSystem : public QWidget
{
    Q_OBJECT

public:
    explicit sSystem(_CONGIG_OMS::_CONGIG_METHOD* pCONGIG_METHOD,
    _CONGIG_OMS::_CONGIG_ACQUISITION* pCONGIG_ACQUISITION,
    _CONGIG_OMS::_CONGIG_ANALYSIS* pCONGIG_ANALYSIS,QScriptEngine* pScriptEngine,
    QWidget *parent = 0);
    ~sSystem();
    void setCurrentWindow(int index);
    sAutoTuning* getAutoTuningP(){
        return mAutoTuning;
    }
    sManualTuning* getManualTuningP(){
        return mManualTuning;
    }
    ParamCCS::_DAQ_CONFIG* getConfigDAQ(){
        return &mDAQ_CONFIG;
    }

    sPwmCCS* getPWMWidgeht() { return pPwmCCS; }

    MyControl *getStateWidget();

    void setFilePath(QString path);

    void setControlState(bool state);

    void showSSC(QByteArray& pArray){
        if(pControlSSC)
            pControlSSC->showSSC(pArray);
    }

    QByteArray createConfig(){
        if(pControlSSC)
            return pControlSSC->createConfig();
        return QByteArray();
    }

    QByteArray createRequest(){
        if(pControlSSC)
            return pControlSSC->createRequest();
        return QByteArray();
    }

    QByteArray createElecPumpOn(){
        if(pControlSSC)
            return pControlSSC->createElecPumpOn();
        return QByteArray();
    }

    QByteArray createElecPumpOff(){
        if(pControlSSC)
            return pControlSSC->createElecPumpOff();
        return QByteArray();
    }

    void onPolarity(bool state);

private slots:
    void on_UI_PB_AUTO_clicked();
    void on_UI_PB_MANUAL_clicked();
    void onShowSystem();
    void on_UI_PB_QUIT_clicked();

    void on_pushButton_clicked();

    void on_UI_PB_CONTROL_clicked();

    void on_UI_PB_SHOW_SSC_clicked();

    void on_UI_PB_SHOW_PWM_clicked();

private:
    Ui::sSystem *ui;
    QWidget* mParent=nullptr;

    _CONGIG_OMS::_CONGIG_SYSTEM mCONGIG_SYSTEM;
    _CONGIG_OMS::_CONGIG_METHOD* mCONGIG_METHOD= nullptr;
    _CONGIG_OMS::_CONGIG_ACQUISITION* mCONGIG_ACQUISITION= nullptr;
    _CONGIG_OMS::_CONGIG_ANALYSIS* mCONGIG_ANALYSIS= nullptr;
    _CONGIG_OMS::_CONGIG_MANUAL_TUNING* mCONGIG_MANUAL_TUNING= nullptr;
    _CONGIG_OMS::_CONGIG_AUTO_TUNING* mCONGIG_AUTO_TUNING= nullptr;

    cDataProcess* mDataProcess= nullptr;
    sAutoTuning* mAutoTuning=nullptr;
    sManualTuning* mManualTuning=nullptr;
    ParamCCS::_DAQ_CONFIG mDAQ_CONFIG;
    sControlSSC* pControlSSC= nullptr;
    bool loadFile(bool ifUpdateUI=false, QString qPath=nullptr);
    MassAxisAdjust* mMassAxis = nullptr;
    sPwmCCS* pPwmCCS=nullptr;
    QScriptEngine* mScriptEngine;

    QString btn_style[4];
    QString filePath;

protected:
    void paintEvent(QPaintEvent* e);
signals:
    void tuningState();
};

#endif // SSYSTEM_H
