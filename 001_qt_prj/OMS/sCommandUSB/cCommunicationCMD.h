#pragma once
#include <QMutex>
#include <QVector>
#include <tool/ssafedata.h>
#include <tool/sthread.h>
#include "cParamCCS.h"
#include "cMidWareUSB.h"
/**
 * @brief The CommandUSB class
 * CCS,ASG,DAQ指令的具体实现，内含DAQ采集线程，getDataDAQ为数据提取接口
 */
//class cParamCCS;

class CommunicationCMD: public QObject
{
    Q_OBJECT
public:
    struct _DAQ_DATA{
        volatile uint nVersion= 0;
        QMutex qLock;
        QVector<uint> pBuff;
    }p_DAQ_DATA[3];
    CommunicationCMD(QObject *parent = 0);
    virtual ~CommunicationCMD(void);
    bool isThreadRun(){
        return mThreadDAQ.isRunning();
    }
    QList<_DAQ_DATA*>* getDataDAQ(){
        return &m_DAQ_DATA;
    }
    int safeCCS();
    int scanCCS(QByteArray& pArrayCCS);
    int scanCCS(char* pData, uint nLength);
    int stopCCS();
    int scanASG(QByteArray& pArrayASG);
    int scanASG(char* pData, uint nLength);
    int stopASG();

    int startDAQ(ParamCCS::_DAQ_CONFIG& p_DAQ_CONFIG);
    int stopDAQ();

    int startPWM(ParamCCS::PWM_GENETATE& pPWM_GENETATE);
    int sendCMD(const QByteArray& pArrayCMD, QByteArray& pArrayBack, uint sizeBack= 512);
    int sendCMD(const char* pW, const uint nW, char* const pR, const uint nR);
private:
    SThread mThreadDAQ; /**< TODO */
    ParamCCS::_DAQ_CONFIG m_DAQ_CONFIG;
    MidWareUSB mComm;
    int mCurrentBuff=0;
    volatile bool mSentDaqStop= false;
    QList<_DAQ_DATA*> m_DAQ_DATA;
    static int daqThread(void *pParam, const bool &bRunning);
    bool init_DAQ_DATA(int nSize=0){
        for(int i=0;i<3;i++){
            m_DAQ_DATA[i]->qLock.lock();
            if(nSize> 0){
                m_DAQ_DATA[i]->pBuff.reserve(nSize);//.shrink_to_fit();
                m_DAQ_DATA[i]->pBuff.resize(nSize);
            }
            m_DAQ_DATA[i]->nVersion= 1;
            m_DAQ_DATA[i]->qLock.unlock();
        }return true;
    }
    bool daqGetData(QVector<uint>& recvBuffer,uint* pLastPkt,QVector<uint>& frameBuff,
                    uint& uFrameCount,uint& uPacketCount,bool& isSameFrame,bool& isRightPacket,
                    int uValidSize,int uLastPktSize);
};

