#include "cCommunicationCMD.h"
#include "sCommandUSB/cMidWareUSB.h"
#include <QDebug>
#include <QCoreApplication>
#include <QTime>

using namespace std;
#define REG_DAC_OFS	(0xffff >> 3)
#define CCS_SYS_FREQENCY_HZ	100000000
#define SDBG(msg) qDebug()<<msg
#define SDBG1(msg) qDebug()<<msg

CommunicationCMD::CommunicationCMD(QObject *parent):
    QObject(parent)
{
    mThreadDAQ.setUserFunction(daqThread);
    mThreadDAQ.setUserParam(this);
    if(m_DAQ_DATA.size()== 0)
        for(int i=0;i<3;i++){
            m_DAQ_DATA.append(&(p_DAQ_DATA[i]));
        }
}

CommunicationCMD::~CommunicationCMD(void)
{
    if(mThreadDAQ.isRunning()){
        mThreadDAQ.stop();
        mThreadDAQ.wait();
    }
}

const uint arruMsMethod[] = {0xfffff065,0x00000008,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x3a4f7191,
0x00000000,0x00000000,0x00000100,0x28f5bf90,0x00000000,0x00000030,0x003000c0,0x30100090,0x80008000,0x80008000,0x80008000,0x80008000,0x80008000,0x80008000,0x00000000,0x00000000,
0x00000001,0x00000000,0x00000100,0x28f5bf90,0x00000000,0x00000030,0x003000c0,0x30100090,0x80008000,0x80008000,0x80008000,0x80008000,0x80008000,0x80008000,0x00000000,0x00000000,
0x00000002,0x00000000,0x00000100,0x28f5bf90,0x00000000,0x00000030,0x003000c0,0x30100090,0x80008000,0x80008000,0x80008000,0x80008000,0x80008000,0x80008000,0x00000000,0x00000000,
0x00000003,0x00000000,0x00000100,0x28f5bf90,0x00000000,0x00000030,0x003000c0,0x30100090,0x80008000,0x80008000,0x80008000,0x80008000,0x80008000,0x80008000,0x00000000,0x00000000,
0x00000004,0x00000000,0x00000100,0x28f5bf90,0x00000000,0x00000030,0x003000c0,0x30100090,0x80008000,0x80008000,0x80008000,0x80008000,0x80008000,0x80008000,0x00000000,0x00000000,
0x00000005,0x00000000,0x00000100,0x28f5bf90,0x00000000,0x00000030,0x003000c0,0x30100090,0x80008000,0x80008000,0x80008000,0x80008000,0x80008000,0x80008000,0x00000000,0x00000000,
0x00000006,0x00000000,0x00000100,0x28f5bf90,0x00000000,0x00000030,0x003000c0,0x30100090,0x80008000,0x80008000,0x80008000,0x80008000,0x80008000,0x80008000,0x00000000,0x00000000,
0x00000007,0x00000000,0x00000100,0x28f5bf90,0x00000000,0x00000030,0x003000c0,0x30100090,0x80008000,0x80008000,0x80008000,0x80008000,0x80008000,0x80008000,0x00000000,0x00000000};


int CommunicationCMD::safeCCS()
{
    uint uRecvBytes= 0;
    QVector<UINT> cmdData, recvData(128);
    ParamCCS::CCS_Halt(cmdData);
    ParamCCS::printfMethod(cmdData,true);
    if(!mComm.writeForBack(cmdData.data(), cmdData.size() * 4, recvData.data(), 512, &uRecvBytes))
        return -1;
    SDBG("N_CommunicationCMD_CCS_Halt_R" << uRecvBytes);

    QVector<UINT> safeMethod(256);
    for(int i=0; i<256; i++)
        safeMethod[i]= arruMsMethod[i];
    ParamCCS::Checksum(safeMethod);
    if(!mComm.writeForBack(safeMethod.data(), safeMethod.size()* 4, recvData.data(), 512, &uRecvBytes, 500))
        return -2;
    SDBG("N_CommunicationCMD_CCS_Update_R" << uRecvBytes);

    ParamCCS::CCS_Start(cmdData);
    ParamCCS::printfMethod(cmdData,true);
    if(!mComm.writeForBack(cmdData.data(), cmdData.size() * 4, recvData.data(), 512, &uRecvBytes))
        return -3;
    SDBG("N_CommunicationCMD_CCS_Start_R" << uRecvBytes);
    QThread::msleep(100);

    ParamCCS::CCS_Halt(cmdData);
    ParamCCS::printfMethod(cmdData,true);
    if(!mComm.writeForBack(cmdData.data(), cmdData.size() * 4, recvData.data(), 512, &uRecvBytes))
        return -1;
    SDBG("N_CommunicationCMD_CCS_Halt_R" << uRecvBytes);
    return 0;
}

int CommunicationCMD::scanCCS(char* pData, uint nLength)
{
    uint uRecvBytes= 0;
    QVector<UINT> cmdData, recvData(128);
    ParamCCS::CCS_Halt(cmdData);
    ParamCCS::printfMethod(cmdData,true);
    if(!mComm.writeForBack(cmdData.data(), cmdData.size() * 4, recvData.data(), 512, &uRecvBytes))
        return -1;
    SDBG("N_CommunicationCMD_CCS_Halt_R" << uRecvBytes);

    //ParamCCS::printfMethod(pArrayCCS,true);
    //int sizeArray=pArrayCCS.size();
    if(!mComm.writeForBack(pData, nLength, recvData.data(), 512, &uRecvBytes, 5000))
        return -2;
    ParamCCS::printfMethod(recvData,true);
    SDBG("N_CommunicationCMD_CCS_Update_R" << uRecvBytes);

    ParamCCS::CCS_Start(cmdData);
    ParamCCS::printfMethod(cmdData,true);
    if(!mComm.writeForBack(cmdData.data(), cmdData.size() * 4, recvData.data(), 512, &uRecvBytes))
        return -3;
    SDBG("N_CommunicationCMD_CCS_Start_R" << uRecvBytes);
    QThread::msleep(100);
    return 0;
}
int CommunicationCMD::scanCCS(QByteArray& pArrayCCS)
{
    uint uRecvBytes= 0;
    QVector<UINT> cmdData, recvData(128);
    ParamCCS::CCS_Halt(cmdData);
    ParamCCS::printfMethod(cmdData,true);
    if(!mComm.writeForBack(cmdData.data(), cmdData.size() * 4, recvData.data(), 512, &uRecvBytes))
        return -1;
    SDBG("N_CommunicationCMD_CCS_Halt_R" << uRecvBytes);

    ParamCCS::printfMethod(pArrayCCS,true);
    //int sizeArray=pArrayCCS.size();
    if(!mComm.writeForBack(pArrayCCS.data(), pArrayCCS.size(), recvData.data(), 512, &uRecvBytes, 5000))
        return -2;
    ParamCCS::printfMethod(recvData,true);
    SDBG("N_CommunicationCMD_CCS_Update_R" << uRecvBytes);

    ParamCCS::CCS_Start(cmdData);
    ParamCCS::printfMethod(cmdData,true);
    if(!mComm.writeForBack(cmdData.data(), cmdData.size() * 4, recvData.data(), 512, &uRecvBytes))
        return -3;
    SDBG("N_CommunicationCMD_CCS_Start_R" << uRecvBytes);
    QThread::msleep(100);
    return 0;
}

int CommunicationCMD::stopCCS()
{
    uint uRecvBytes= 0;
    QVector<UINT> cmdData, recvData(128);
    ParamCCS::CCS_Halt(cmdData);
    ParamCCS::printfMethod(cmdData,true);
    if(!mComm.writeForBack(cmdData.data(), cmdData.size() * 4, recvData.data(), 512, &uRecvBytes))
        return -1;
    SDBG("N_CommunicationCMD_CCS_Halt_R" << uRecvBytes);
    return 0;
}

int CommunicationCMD::scanASG(QByteArray& pArrayASG)
{
    uint uRecvBytes= 0;
    QVector<UINT> cmdData, recvData(128);
    ParamCCS::ASG_Config(cmdData);
    ParamCCS::printfMethod(cmdData,true);
    if(!mComm.writeForBack(cmdData.data(), cmdData.size() * 4, recvData.data(), 512, &uRecvBytes))
        return -1;
    SDBG("N_CommunicationCMD_ASG_Config_R" << uRecvBytes);

    ParamCCS::ASG_Adjust(cmdData);
    ParamCCS::printfMethod(cmdData,true);
    if(!mComm.writeForBack(cmdData.data(), cmdData.size() * 4, recvData.data(), 512, &uRecvBytes))
        return -2;
    SDBG("N_CommunicationCMD_ASG_Adjust_R" << uRecvBytes);

    ParamCCS::printfMethod(pArrayASG,true);
    if(!mComm.writeForBack(pArrayASG.data(), pArrayASG.size(), recvData.data(), 512, &uRecvBytes))
        return -3;
    SDBG("N_CommunicationCMD_ASG_Update_R" << uRecvBytes);

    ParamCCS::ASG_Stop(cmdData);
    ParamCCS::printfMethod(cmdData,true);
    if(!mComm.writeForBack(cmdData.data(), cmdData.size() * 4, recvData.data(), 512, &uRecvBytes))
        return -4;
    SDBG("N_CommunicationCMD_ASG_Stop_R" << uRecvBytes);

    ParamCCS::ASG_Start(cmdData);
    ParamCCS::printfMethod(cmdData,true);
    if(!mComm.writeForBack(cmdData.data(), cmdData.size() * 4, recvData.data(), 512, &uRecvBytes))
        return -5;
    SDBG("N_CommunicationCMD_ASG_Start_R" << uRecvBytes);
    return 0;
}

int CommunicationCMD::scanASG(char* pData, uint nLength)
{
    uint uRecvBytes= 0;
    QVector<UINT> cmdData, recvData(128);
    ParamCCS::ASG_Config(cmdData);
    ParamCCS::printfMethod(cmdData,true);
    if(!mComm.writeForBack(cmdData.data(), cmdData.size() * 4, recvData.data(), 512, &uRecvBytes))
        return -1;
    SDBG("N_CommunicationCMD_ASG_Config_R" << uRecvBytes);

    ParamCCS::ASG_Adjust(cmdData);
    ParamCCS::printfMethod(cmdData,true);
    if(!mComm.writeForBack(cmdData.data(), cmdData.size() * 4, recvData.data(), 512, &uRecvBytes))
        return -2;
    SDBG("N_CommunicationCMD_ASG_Adjust_R" << uRecvBytes);

    //ParamCCS::printfMethod(pArrayASG,true);
    if(!mComm.writeForBack(pData, nLength, recvData.data(), 512, &uRecvBytes))
        return -3;
    SDBG("N_CommunicationCMD_ASG_Update_R" << uRecvBytes);

    ParamCCS::ASG_Stop(cmdData);
    ParamCCS::printfMethod(cmdData,true);
    if(!mComm.writeForBack(cmdData.data(), cmdData.size() * 4, recvData.data(), 512, &uRecvBytes))
        return -4;
    SDBG("N_CommunicationCMD_ASG_Stop_R" << uRecvBytes);

    ParamCCS::ASG_Start(cmdData);
    ParamCCS::printfMethod(cmdData,true);
    if(!mComm.writeForBack(cmdData.data(), cmdData.size() * 4, recvData.data(), 512, &uRecvBytes))
        return -5;
    SDBG("N_CommunicationCMD_ASG_Start_R" << uRecvBytes);
    return 0;
}

int CommunicationCMD::stopASG()
{
    uint uRecvBytes= 0;
    QVector<UINT> cmdData, recvData(128);
    ParamCCS::ASG_Stop(cmdData);
    ParamCCS::printfMethod(cmdData,true);
    if(!mComm.writeForBack(cmdData.data(), cmdData.size() * 4, recvData.data(), 512, &uRecvBytes))
        return -1;
    qDebug()<<"N_CommunicationCMD_ASG_Stop_R" << uRecvBytes;
    return 0;
}

int CommunicationCMD::startPWM(ParamCCS::PWM_GENETATE& pPWM_GENETATE)
{
    uint uRecvBytes= 0;
    QVector<UINT> cmdData, recvData(128);
    ParamCCS::generaterPWM(cmdData, pPWM_GENETATE);
    ParamCCS::printfMethod(cmdData,true);
    if(!mComm.writeForBack(cmdData.data(), cmdData.size() * 4, recvData.data(), 512, &uRecvBytes))
        return -1;
    SDBG("N_CommunicationCMD_generaterPWM_R" << uRecvBytes);
    return 0;
}

int CommunicationCMD::startDAQ(ParamCCS::_DAQ_CONFIG& p_DAQ_CONFIG)
{
    if(mThreadDAQ.isRunning()){
        SDBG("E_startDAQ_isRunning");
        return -1;
    }
    memcpy(&m_DAQ_CONFIG, &p_DAQ_CONFIG, sizeof(ParamCCS::_DAQ_CONFIG));
    uint uRecvBytes= 0;
    QVector<UINT> cmdData, recvData(128);
    ParamCCS::DAQ_Config(cmdData, m_DAQ_CONFIG);
    ParamCCS::printfMethod(cmdData,true);
    if(!mComm.writeForBack(cmdData.data(), cmdData.size() * 4, recvData.data(), 512, &uRecvBytes))
        return -2;
    SDBG("N_CommunicationCMD_DAQ_Config_R" << uRecvBytes);

    ParamCCS::DAQ_Start(cmdData);
    ParamCCS::printfMethod(cmdData,true);
    if(!mComm.writeForBack(cmdData.data(), cmdData.size() * 4, recvData.data(), 512, &uRecvBytes))
        return -3;
    SDBG("N_CommunicationCMD_DAQ_Start_R" << uRecvBytes);

    for(int i=0;i<3;i++){
        m_DAQ_DATA[i]->qLock.lock();
        m_DAQ_DATA[i]->nVersion= 1;
        m_DAQ_DATA[i]->qLock.unlock();
    }
    mSentDaqStop= false;
    mThreadDAQ.start();
    return 0;
}

int CommunicationCMD::stopDAQ()
{
    int backM= 0;
    uint uRecvBytes= 0;
    QVector<UINT> cmdData, recvData(128);
    ParamCCS::DAQ_Stop(cmdData);
    ParamCCS::printfMethod(cmdData,true);
    for(int i=0;i<3;i++){
        if(!mComm.writeForBack(cmdData.data(), cmdData.size() * 4, recvData.data(), 512, &uRecvBytes)){
            backM= -1;
            SDBG("E_CommunicationCMD_DAQ_Stop_R" << uRecvBytes);
        }else{
            backM= 0;
            break;
        }
    }
    mSentDaqStop= true;
    if(backM== 0)
        SDBG("N_CommunicationCMD_DAQ_Stop_R" << uRecvBytes);
    if(mThreadDAQ.isRunning()){
        mThreadDAQ.stop();
        mThreadDAQ.wait();
    }
    return 0;
}

bool CommunicationCMD::daqGetData(QVector<uint>& recvBuffer,uint* pLastPkt,QVector<uint>& frameBuff,
                               uint& uFrameCount,uint& uPacketCount,bool& isSameFrame,bool& isRightPacket,
                               int uValidSize,int uLastPktSize)
{
    for(uint* pIndexPkt = recvBuffer.data(); pIndexPkt <= pLastPkt; pIndexPkt += 128){//,uPacketCount++
        if(pIndexPkt[5] == 0x00010001){// if there is not more package, this process is ended.
            SDBG1("N_CommunicationCMD_daqGetData_lastPackage");
            return false;//goto OUT;
        }

        if(pIndexPkt[4]== 1){//first packet
            uPacketCount= pIndexPkt[4];
            uFrameCount= pIndexPkt[3];
            isSameFrame= true;
            isRightPacket=true;
        }else
            uPacketCount++;

        if(pIndexPkt[5] & 0x1){//last packet
            if(uFrameCount!= pIndexPkt[3]){//errorFrame
                SDBG1("W_CommunicationCMD_daqGetData_errorFrame");
                isSameFrame= false;break;
            }
            if(uPacketCount!= pIndexPkt[4]){//errorPacket
                SDBG1("W_CommunicationCMD_daqGetData_errorPacket");
                isRightPacket= false;break;
            }
            if(((pIndexPkt[4] - 1) * 120 + (uint)uLastPktSize) != (uint)uValidSize){
                SDBG1("W_CommunicationCMD_daqGetData_errorPacket");
                isSameFrame= false;break;
            }
            if(isSameFrame && isRightPacket){
                memcpy(frameBuff.data() + (pIndexPkt[4] - 1) * 120, pIndexPkt + 7, uLastPktSize * 4);
                bool isGotBuff= false;
                for(int i=0;i<3;i++){
                    mCurrentBuff== 2? mCurrentBuff=0:mCurrentBuff++;
                    if(m_DAQ_DATA[mCurrentBuff]->qLock.tryLock()){
                        m_DAQ_DATA[mCurrentBuff]->pBuff.resize(frameBuff.size());
                        memcpy(m_DAQ_DATA[mCurrentBuff]->pBuff.data(), frameBuff.data(), frameBuff.size()*sizeof(uint));
                        m_DAQ_DATA[mCurrentBuff]->nVersion= uFrameCount;//可能导致第一帧无法记录
                        m_DAQ_DATA[mCurrentBuff]->qLock.unlock();
                        //SDBG1("DAQ_add-Frame:")<<mCurrentBuff<<"-Version:"<<uFrameCount;
                        isGotBuff=true;
                        break;
                    }
                }
                if(!isGotBuff){
                    SDBG1("W_CommunicationCMD_daqGetData_errorGetBuffer");
                    return false;//goto OUT;
                }
            }else
                SDBG1("W_CommunicationCMD_daqGetData_lostFrame");
        }else{
            if(uFrameCount!= pIndexPkt[3]){//errorFrame
                SDBG1("W_CommunicationCMD_daqGetData_errorFrame");
                isSameFrame= false;break;
            }
            if(uPacketCount!= pIndexPkt[4]){//errorPacket
                SDBG1("W_CommunicationCMD_daqGetData_errorPacket");
                isRightPacket= false;break;
            }
            if(pIndexPkt[4]*120 > (uint)uValidSize){//somethingError
                isSameFrame= false;break;
            }
            memcpy(frameBuff.data() + (pIndexPkt[4] - 1) * 120, pIndexPkt + 7, 120 * 4);
        }
    }
    return true;
}

int CommunicationCMD::daqThread(void *pParam, const bool &bRunning)
{
    qDebug("N_CommunicationCMD_daqThread_start");
    CommunicationCMD* pCmd = (CommunicationCMD*)pParam;
    if(!pCmd)
        return -1;
    int uAccNumber = (int)pCmd->m_DAQ_CONFIG.No_ACC;// pObj->property("noacc").toInt();
    int nPointNumber= (int)pCmd->m_DAQ_CONFIG.No_AQP;
    if(uAccNumber <= 0){
        qDebug("E_CommunicationCMD_daqThread_ACC");return -1;
    }
    int uValidSize = (nPointNumber + uAccNumber - 1) / uAccNumber;
    if(uValidSize<= 0){
        qDebug("E_CommunicationCMD_daqThread_ZeroPoint");return -1;
    }

    uint uLastPktSize= uValidSize % 120;	//每帧的最后一个包中有效数据个数
    if (uLastPktSize==0)
        uLastPktSize=120;

    pCmd->init_DAQ_DATA((uValidSize+119)*128/120);//初始化缓存池QList<_DAQ_DATA*>
    QVector<uint> frameBuff(uValidSize,0),//一帧数据
            arrCmd,//DAQ_Request指令缓存
            recvBuffer;//DAQ_Request回包缓存
    //uint* arrCmd= new uint[128];
    ParamCCS::DAQ_Request(arrCmd, 1);//生成DAQ_Request指令

    //bool bSentDaqStop= false;
    uint uFrameCount = 1;
    uint uPacketCount = 1;
    bool isSameFrame=true;
    bool isRightPacket=true;

    uint uRecvBytes =0;
    uint uLeftBytes =512;
    uint* pLastPkt = nullptr;
    QTime tmEmptyPkt;
    tmEmptyPkt.start();
    while(bRunning){//forever{
        uRecvBytes =0;
        recvBuffer.resize(arrCmd[7] * 128);
        uLeftBytes = arrCmd[7] * 512;
        if(pCmd->mSentDaqStop)
            break;
        if(!pCmd->mComm.writeForBack(arrCmd.data(), 512, recvBuffer.data(), uLeftBytes, &uRecvBytes, arrCmd[7]*500*2)){
            if(!pCmd->mSentDaqStop)
            {
                SDBG1("E_CommunicationCMD_daqThread_OVERTIME");
                break;
            }
            while(!pCmd->mSentDaqStop){
                uLeftBytes= 512;
                ParamCCS::DAQ_Request(arrCmd, 1);//生成DAQ_Request指令
                if(pCmd->mComm.writeForBack(arrCmd.data(), 512, recvBuffer.data(), uLeftBytes, &uRecvBytes, arrCmd[7]*500))
                    break;
                QThread::msleep(1);
            }
        }
        if(pCmd->mSentDaqStop)
            break;
        if(uRecvBytes!= uLeftBytes){
            SDBG1("E_CommunicationCMD_daqThread_uRecvBytes:" << uRecvBytes<< " uLeftBytes:"<<uLeftBytes);break;
        }
        pLastPkt = &(recvBuffer[uRecvBytes / 4 - 128]);// offset to last package
        if(pLastPkt[2] & 0x00010000){
            if(tmEmptyPkt.elapsed()>500 && pCmd->mSentDaqStop){
                SDBG1("E_CommunicationCMD_daqThread_StopOvertime");break;
            }
            QThread::usleep(1);
        }else{
            if(!pCmd->daqGetData(recvBuffer, pLastPkt, frameBuff, uFrameCount, uPacketCount,
                           isSameFrame, isRightPacket, uValidSize, uLastPktSize))
                break;
        }
        if(pLastPkt[6] > 1){//FPGA中剩余包数
            arrCmd[7] = (pLastPkt[6] > 500) ? 500 : (pLastPkt[6] - 1);
        }else{
            arrCmd[7] = 1;
        }
        ParamCCS::DAQ_Request(arrCmd, arrCmd[7]);//生成DAQ_Request指令
    }
    SDBG1("N_CommunicationCMD_daqThread_Over");
    if(pCmd->mComm.getListSize()==0)
        return 0;
}

int CommunicationCMD::sendCMD(const QByteArray& pArrayCMD, QByteArray& pArrayBack, uint sizeBack)
{
    uint uRecvBytes=0;
    if(!mComm.writeForBack(pArrayCMD.data(), pArrayCMD.size(), pArrayBack.data(), sizeBack, &uRecvBytes)){
        SDBG("E_CommunicationCMD_sendCMD_R" << uRecvBytes << ((uint*)pArrayCMD.data())[0] << ((uint*)pArrayCMD.data())[3]);
        return -1;
    }
    return 0;
}

int CommunicationCMD::sendCMD(const char* pW, const uint nW, char* const pR, const uint nR)
{
    uint uRecvBytes=0;
    if(!mComm.writeForBack(pW, nW, pR, nR, &uRecvBytes)){
        SDBG("E_CommunicationCMD_sendCMD_R" << uRecvBytes << ((uint*)pW)[0] << ((uint*)pW)[3]);
        return -1;
    }
    return 0;
}

