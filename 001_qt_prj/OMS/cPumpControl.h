#ifndef cPumpControl_H
#define cPumpControl_H

#include <QByteArray>
#include <QString>
#include "cParamCCS.h"
#include <QDebug>

class cPumpControl
{
public:
    explicit cPumpControl(){}
    ~cPumpControl(){}
    struct _STATE_REQUEST:ParamCCS::_STATE_REQUEST_CCS{
        int rotatinSpeed=0;
        double driveCurrent=0;
    };

    static QByteArray createPumpOnCMD(){
        QByteArray tmpCMD= SynCommand(1, 10, 111111).toLatin1();
        qDebug() << "sendOn:";
        qDebug() << tmpCMD;
        return ParamCCS::uartCMDData(tmpCMD);
    }

    static QByteArray createPumpOffCMD(){
        QByteArray tmpCMD= SynCommand(1, 10, 0).toLatin1();
        qDebug() << "sendOff:";
        qDebug() << tmpCMD;
        return ParamCCS::uartCMDData(tmpCMD);
    }

    static QByteArray createPumpDriveCMD(){
        QByteArray tmpCMD= SynCommand(1, 310, 0).toLatin1();
        qDebug() << "send310:";
        qDebug() << tmpCMD;
        return ParamCCS::uartCMDData(tmpCMD);
    }

    static QByteArray createPumpSpeedCMD(){
        QByteArray tmpCMD= SynCommand(1, 309, 0).toLatin1();
        qDebug() << "send309:";
        qDebug() << tmpCMD;
        return ParamCCS::uartCMDData(tmpCMD);
    }

    static bool getDrive(const QByteArray& tmpR, _STATE_REQUEST& pSTATE_REQUEST);

    static bool getRotatinSpeed(const QByteArray& tmpR, _STATE_REQUEST& pSTATE_REQUEST);
private:
    static QString CHkSTR(QString sString);
    static QString SynCommand(int paddr,int PcommID, int Pdata);
    static QString SynCommand(int paddr,int PcommID, QString Pdata);
//    static QByteArray uartCMDData(QByteArray& baReq_s_comm);
//    static uint checkSum(uint* data, size_t size);
};

#endif // cPumpControl_H
