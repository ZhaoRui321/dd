#include "cParamCCS.h"
#include <QFile>
#include <QTextStream>
#include <string.h>
ParamCCS::ParamCCS()
{

}
void ParamCCS::printfMethod(const QByteArray &buffer, bool ifAppend, QString fileName)
{
#if 0
    const uint* puPkt,*puFrame,*puEnd;
    QFile file(fileName);
    if(ifAppend){
        if(!file.open(QFile::WriteOnly|QIODevice::Append))
            return;
    }else{
        if(!file.open(QFile::WriteOnly))
            return;
    }
    QTextStream txtOS(&file);
    char szFmt[20];
    puPkt = (const uint*)buffer.constData();
    puEnd = puPkt + buffer.size() / 4;
    auto fFormatHex = [&](const uint* puBegin, uint uSize){
       for(uint uIndex = 0; uIndex < uSize; uIndex++){
           sprintf(szFmt, "%08X\t", *(puBegin++));
           txtOS << szFmt;
           if((uIndex % 8) == 7)
               txtOS << "\n";
       }
    };
    txtOS << "CMD(MS Method)-" << (buffer.size() / 4 - 128) / 16  << ":\n";
    fFormatHex(puPkt, 128);
    puFrame = puPkt + 128;
    uint uFrameIndex = 0;
    while(puFrame < puEnd){
        txtOS << "Frame " << uFrameIndex++ << ":\n";
        fFormatHex(puFrame, 16);
        puFrame += 16;
    }
    file.close();
#endif
}

void ParamCCS::printfMethod(QVector<UINT>& buffer, bool ifAppend, QString fileName)
{
#if 0
    const uint* puPkt,*puFrame,*puEnd;
    QFile file(fileName);
    if(ifAppend){
        if(!file.open(QFile::WriteOnly|QIODevice::Append))
            return;
    }else{
        if(!file.open(QFile::WriteOnly))
            return;
    }
    QTextStream txtOS(&file);
    char szFmt[20];
    puPkt = (const uint*)buffer.data();
    //puEnd = puPkt + buffer.size / 4;
    puEnd = puPkt + buffer.size();
    auto fFormatHex = [&](const uint* puBegin, uint uSize){
        for(uint uIndex = 0; uIndex < uSize; uIndex++){
            sprintf(szFmt, "%08X\t", *(puBegin++));
            txtOS << szFmt;
            if((uIndex % 8) == 7)
                txtOS << "\n";
        }
    };
    txtOS << "CMD(MS Method)-" << (buffer.size() / 4 - 128) / 16  << ":\n";
    fFormatHex(puPkt, 128);
    puFrame = puPkt + 128;
    uint uFrameIndex = 0;
    while(puFrame < puEnd){
        txtOS << "Frame " << uFrameIndex++ << ":\n";
        fFormatHex(puFrame, 16);
        puFrame += 16;
    }
    file.close();
#endif
}
void ParamCCS::Checksum(QVector<UINT>& pBuffer)
{
    UINT lchksum= 0, nLength= pBuffer.size();
    for(UINT i=0;i<nLength;i++)
        if(i!=127)
            lchksum += pBuffer[i];
    pBuffer[127]=lchksum;
}


// 生成缓冲气体控制命令数据
int ParamCCS::bufferGasControlG(QVector<UINT>& pBuffer,bool bufferGasControl)
{
    pBuffer.resize(128);
    memset(pBuffer.data(), 0, pBuffer.size()* sizeof(UINT));
    pBuffer[0] = BUFFER_GAS_CTRL_ID;
    if(bufferGasControl)
        pBuffer[3] |= (uint)0x0000ffff;
    pBuffer[127] = pBuffer[0]+ pBuffer[3];
    return 0;
}

// 生成系统真空控制命令数据
int ParamCCS::pumpVentSystemG(QVector<UINT>& pBuffer, bool openPump)
{
    pBuffer.resize(128);
    memset(pBuffer.data(), 0, pBuffer.size()* sizeof(UINT));
    pBuffer[0] = PUMP_VENT_CTRL_ID;
    if(openPump)
        pBuffer[3] = 0xffffffff;
    pBuffer[127] = pBuffer[0]+ pBuffer[3];
    return 0;
}

// 生成全局高压系统及离子源使能命令数据
int ParamCCS::enableHV(QVector<UINT>& pBuffer, bool openGHV)
{
    pBuffer.resize(128);
    memset(pBuffer.data(), 0, pBuffer.size()* sizeof(UINT));
    pBuffer[0] = GHV_ENABLE_CTRL_ID;
    if(openGHV)
        pBuffer[3] = 0xffffffff;
    pBuffer[127] = pBuffer[0]+ pBuffer[3];
    return 0;
}

// 生成离子源温度控制命令数据
int ParamCCS::tempControl(QVector<UINT>& pBuffer, uint temperature)
{
    pBuffer.resize(128);
    memset(pBuffer.data(), 0, pBuffer.size()* sizeof(UINT));
    pBuffer[0] = TEMPERATURE_CTRL_ID;
    pBuffer[3] = temperature& 0x0000ffff;
    pBuffer[127] = pBuffer[0]+ pBuffer[3];
    return 0;
}

// 生成离子源温度控制PID设置命令数据
int ParamCCS::tempPID(QVector<UINT>& pBuffer, _TEMPERATURE_PID& p_TEMPERATURE_PID)
{
    pBuffer.resize(128);
    memset(pBuffer.data(), 0, pBuffer.size()* sizeof(UINT));
    pBuffer[0] = TEMPERATURE_PID_ID;
    pBuffer[3] = p_TEMPERATURE_PID.p_PID;
    pBuffer[4] = p_TEMPERATURE_PID.i_PID;
    pBuffer[5] = p_TEMPERATURE_PID.d_PID;
    pBuffer[127] = pBuffer[0]+ pBuffer[3]+ pBuffer[4]+ pBuffer[5];
    return 0;
}

// 生成离子源加热开关命令数据
int ParamCCS::heatingSwitch(QVector<UINT>& pBuffer,uint heatingSwitch)
{
    pBuffer.resize(128);
    memset(pBuffer.data(), 0, pBuffer.size()* sizeof(UINT));
    pBuffer[0] = HEATING_SWITCH_ID;
    pBuffer[3] = heatingSwitch;
    pBuffer[127] = pBuffer[0]+ pBuffer[3];
    return 0;
}

// 生成样品气体流速控制命令数据
int ParamCCS::gasControl(QVector<UINT>& pBuffer, uint sampleGas)
{
    pBuffer.resize(128);
    memset(pBuffer.data(), 0, pBuffer.size()* sizeof(UINT));
    pBuffer[0] = SAMPLE_GAS_CTRL_ID;
    pBuffer[3] = sampleGas;
    pBuffer[127] = pBuffer[0]+ pBuffer[3];
    return 0;
}

int ParamCCS::restart(QVector<UINT>& pBuffer)
{
    pBuffer.resize(128);
    memset(pBuffer.data(), 0, pBuffer.size()* sizeof(UINT));
    pBuffer[0] = SOFT_RST_ID;
    pBuffer[127] = pBuffer[0];
    return 0;
}
/************************************************************************************************/
/*            Name:                                                                             */
/**/
/*         Explain:                                                                             */
/*           InPut:                                                                             */
/*          OutPut:                                                                             */
/*    Modification:                                                                             */
/*            Time:                                                                             */
/************************************************************************************************/
int ParamCCS::sysSoftReset(QVector<UINT>& pBuffer)
{
    pBuffer.resize(128);
    memset(pBuffer.data(), 0, pBuffer.size()* sizeof(UINT));
    pBuffer[0] = SOFT_RST_ID;
    pBuffer[127] = pBuffer[0];
    return 0;
}
/************************************************************************************************/
/*            Name:                                                                             */
/**/
/*         Explain:                                                                             */
/*           InPut:                                                                             */
/*          OutPut:                                                                             */
/*    Modification:                                                                             */
/*            Time:                                                                             */
/************************************************************************************************/
int ParamCCS::sysVersionRequest(QVector<UINT>& pBuffer)
{
    pBuffer.resize(128);
    memset(pBuffer.data(), 0, pBuffer.size()* sizeof(UINT));
    pBuffer[0] = VERSION_REQ_ID;
    pBuffer[127] = pBuffer[0];
    return 0;
}
int ParamCCS::stateRequest(QVector<UINT>& pBuffer)
{
    pBuffer.resize(128);
    memset(pBuffer.data(), 0, pBuffer.size()* sizeof(UINT));
    pBuffer[0] = STATE_REQ_ID;
    pBuffer[127] = pBuffer[0];
    return 0;
}

/*******************************************************************************************/
/*函数名称: MS_Start                                                                       */
/*函数功能：将传入的数组填入MS_Start控制命令                                               */
/*函数参数：pBuffer传入数组的指针，nLength传入数组的长度								   */
/*修改时间：2012.10.16.17：58                                                              */
/*函数说明: 参数nLength暂时无用                                                            */
/*******************************************************************************************/
int ParamCCS::CCS_Start(QVector<UINT>& pBuffer, CCS_SCAN& pCCS_SCAN)
{
    pBuffer.resize(128);
    memset(pBuffer.data(), 0, pBuffer.size()* sizeof(UINT));
    pBuffer[0] = MS_START_ID;
    pBuffer[3] = pCCS_SCAN.triggerEXT;
    pBuffer[16]= pCCS_SCAN.scanTimes;
    pBuffer[127] = pBuffer[0]+ pBuffer[3]+ pBuffer[16];
    return 0;
}

int ParamCCS::CCS_Start(QVector<UINT>& pBuffer)
{
    pBuffer.resize(128);
    memset(pBuffer.data(), 0, pBuffer.size()* sizeof(UINT));
    pBuffer[0] = MS_START_ID;
    pBuffer[127] = pBuffer[0];
    return 0;
}
/*******************************************************************************************/
/*函数名称: MS_Halt                                                                        */
/*函数功能：将传入的数组填入MS_Halt控制命令                                                */
/*函数参数：pBuffer传入数组的指针，nLength传入数组的长度                          */
/*修改时间：2012.10.16.17：58                                                              */
/*函数说明: 参数nLength暂时无用                                                            */
/*******************************************************************************************/
int ParamCCS::CCS_Halt(QVector<UINT>& pBuffer)
{
    pBuffer.resize(128);
    memset(pBuffer.data(), 0, pBuffer.size()* sizeof(UINT));
    pBuffer[0] = MS_STOP_ID;
    pBuffer[127] = pBuffer[0];
    return 0;
}

int ParamCCS::DAQ_Config(QVector<UINT>& pBuffer,const _DAQ_CONFIG &p_DAQ_CONFIG)
{
    pBuffer.resize(128);
    memset(pBuffer.data(), 0, pBuffer.size()* sizeof(UINT));
    pBuffer[0] = DAQ_COMMAND_ID;
    pBuffer[3] = DAQ_CONFIG_ID;
    pBuffer[4] = (UINT)(p_DAQ_CONFIG.No_AQP);
    pBuffer[5] = (UINT)(p_DAQ_CONFIG.Frq_AQ);
    pBuffer[6] = (UINT)(p_DAQ_CONFIG.No_ACC);
    pBuffer[127] = pBuffer[0] + pBuffer[3] + pBuffer[4] + pBuffer[5] + pBuffer[6];
    return 0;
}

int ParamCCS::DAQ_Start(QVector<UINT>& pBuffer)
{
    pBuffer.resize(128);
    memset(pBuffer.data(), 0, pBuffer.size()* sizeof(UINT));
    pBuffer[0] = DAQ_COMMAND_ID;
    pBuffer[3] = DAQ_START_ID;
    pBuffer[127] = pBuffer[0] + pBuffer[3];
    return 0;
}

int  ParamCCS::DAQ_Stop(QVector<UINT>& pBuffer)
{
    pBuffer.resize(128);
    memset(pBuffer.data(), 0, pBuffer.size()* sizeof(UINT));
    pBuffer[0] = DAQ_COMMAND_ID;
    pBuffer[3] = DAQ_STOP_ID;
    pBuffer[127] = pBuffer[0] + pBuffer[3];
    return 0;
}

int ParamCCS::DAQ_Request(UINT* pBuffer, UINT uNoDataReq)
{
    //pBuffer.resize(128);
    memset(pBuffer, 0, 512);
    pBuffer[0] = DAQ_COMMAND_ID;
    pBuffer[3] = DAQ_DATAREQ_ID;
    pBuffer[7] = uNoDataReq;
    pBuffer[127] = pBuffer[0] + pBuffer[3] + pBuffer[7];
    return 0;
}

int ParamCCS::DAQ_Request(QVector<UINT>& pBuffer, UINT uNoDataReq)
{
    pBuffer.resize(128);
    memset(pBuffer.data(), 0, pBuffer.size()* sizeof(UINT));
    pBuffer[0] = DAQ_COMMAND_ID;
    pBuffer[3] = DAQ_DATAREQ_ID;
    pBuffer[7] = uNoDataReq;
    pBuffer[127] = pBuffer[0] + pBuffer[3] + pBuffer[7];
    return 0;
}

int ParamCCS::DAQ_Powerdown(QVector<UINT>& pBuffer)
{
    pBuffer.resize(128);
    memset(pBuffer.data(), 0, pBuffer.size()* sizeof(UINT));
    pBuffer[0] = DAQ_COMMAND_ID;
    pBuffer[3] = ASG_POWERDOWN_ID;
    pBuffer[127] = pBuffer[0] + pBuffer[3];
    return 0;
}


int ParamCCS::generaterPWM(QVector<UINT>& pBuffer,PWM_GENETATE& pPWM_GENETATE)
{
    pBuffer.resize(128);
    memset(pBuffer.data(), 0, pBuffer.size()* sizeof(UINT));
    pBuffer[0] = PWM_GENERATE_ID;
    for(int i=0;i<8;i++){
        pBuffer[i*3+2]=pPWM_GENETATE.lPWMCycle[i];
        pBuffer[i*3+3]=pPWM_GENETATE.lPWMUp[i];
        pBuffer[i*3+4]=pPWM_GENETATE.lPWMDown[i];
    }
    pBuffer[26]=pPWM_GENETATE.lPWMEnable;
    Checksum(pBuffer);
    return 0;
}

int ParamCCS::ASG_Config(QVector<UINT>& pBuffer)//,SDACConfigPara *pDacConfigP)
{
    pBuffer.resize(128);
    memset(pBuffer.data(), 0, pBuffer.size()* sizeof(UINT));
    pBuffer[0] = ASG_COMMAND_ID;
    pBuffer[3] = ASG_CONFIG_ID;
    //pBuffer[4]=((pDacConfigP->Offset1)&0xFFFF)<<16 | (pDacConfigP->Offset0&0xFFFF);
    pBuffer[4]=(0xffff >> 3)<<16 | 0xffff >> 3;
    pBuffer[127]=pBuffer[0]+pBuffer[3]+pBuffer[4];
    return 0;
}

int ParamCCS::ASG_Adjust(QVector<UINT>& pBuffer,SDACAdjustPara *pDacAdjustP)
{
    uint gain[160],offset[160];
    if(pDacAdjustP){
        for(int i=0;i<160;i++){
            gain[i]= (uint)pDacAdjustP->ParaA[i];
            offset[i]= (uint)pDacAdjustP->ParaB[i];
        }
    }else{
        for(int i=0;i<160;i++){
            gain[i]= 0x4000;
            offset[i]= 0x0000;
        }
    }
    pBuffer.resize(1536);
    memset(pBuffer.data(), 0, pBuffer.size()* sizeof(UINT));
    //Step0 Data Frame Generate(A parameter Generate)
    UINT* pTxBufD=pBuffer.data()+128;
    pTxBufD[0]=0x00000001;
    for(int i=0;i<80;i++)
        pTxBufD[11+i]=(gain[i*2+1]<<16) | gain[i*2];
    //Step1 Data Frame Generate(D parameter Generate)
    pTxBufD=pBuffer.data()+256;
    pTxBufD[0]=0x00000002;
    for(int i=0;i<80;i++)
        pTxBufD[11+i]=(offset[i*2+1]<<16) | offset[i*2];
    //Command Head Package Generate
    pBuffer[0]=ASG_COMMAND_ID;
    pBuffer[1]=0x00000002;
    pBuffer[3]=ASG_ADJUST_ID;
    Checksum(pBuffer);
    return 0;
}

//int ParamCCS::FreqControl(FREQUENCY *pFREQUENCY,UINT* pBuffer)
//{
//    pBuffer.resize(128);
//    memset(pBuffer.data(), 0, pBuffer.size()* sizeof(UINT));
//    UINT PWMEnable1=0;
//    UINT PWM_CTRL1=0;
//    for (int i=0;i<8;i++){
//        pBuffer[92+i*3]=(unsigned long)(pFREQUENCY->Freq_MHz[i]);//ecl_rf  frequency
//        pBuffer[93+i*3]=pBuffer[92+i*3]/2;
//        pBuffer[94+i*3]=pBuffer[92+i*3];

//        PWMEnable1|=pFREQUENCY->Freq_Enable[i]<<i;
//        PWM_CTRL1|=pFREQUENCY->PWM_CTRL[i]<<i;
//    }
//    pBuffer[116]=PWMEnable1;
//    pBuffer[117]=PWM_CTRL1;
//    return 0;
//}

int ParamCCS::ASG_Update(QVector<UINT>& pBuffer, _ASG_STRUCT& p_ASG_STRUCT)
{
    int nSize= p_ASG_STRUCT.pStructDAC.size();
    if(nSize<1)
        return -1;
    int nLength=128+ 128* nSize;
    pBuffer.resize(nLength);
    memset(pBuffer.data(), 0, pBuffer.size()* sizeof(UINT));

    UINT DacValue[160];
    pBuffer[0]=ASG_COMMAND_ID;
    pBuffer[1]=nSize;
    pBuffer[2]=0;//p_ASG_STRUCT.MethodValue;
    pBuffer[3]=ASG_SET_ID;
    for(int i=0;i<nSize;i++){
        UINT* pTxBufD= pBuffer.data()+(i+1)*128;
        pTxBufD[0]= 1;
        pTxBufD[1]= i+1;
        if(p_ASG_STRUCT.pStructDAC[i].HoldTime<0.0)
            continue;
        pTxBufD[2]= 1000;//(UINT)(p_ASG_STRUCT.pStructDAC[i].HoldTime);
        for(int j=3;j<11;j++)
            pTxBufD[j]= p_ASG_STRUCT.pStructDAC[i].MaskDAC[j-3];
        memset(DacValue, 0, 160* sizeof(UINT));
        for (int j=0;j<160;j++)
            DacValue[j]=(UINT)((p_ASG_STRUCT.pStructDAC[i].DacValue[j] + 10) * 0xffff / 20);
        for(int n=0;n<80;n++)
            pTxBufD[11+n]=(DacValue[n*2+1]<<16) | (DacValue[n*2]&0x0000FFFF);
        if(i<10 && i>0)
            pTxBufD[91]=0xffffffff;
        else
            pTxBufD[91]=0xffff0000;
        //FreqControl(&(p_ASG_STRUCT.pStructDAC[i].Freq),pTxBufD);如加入则错误
    }
    Checksum(pBuffer);
    return 0;
}

int ParamCCS::ASG_Start(QVector<UINT>& pBuffer,_ASG_STRUCT& p_ASG_STRUCT){
    pBuffer.resize(128);
    memset(pBuffer.data(), 0, pBuffer.size()* sizeof(UINT));
    pBuffer[0]=ASG_COMMAND_ID;
    pBuffer[2]=p_ASG_STRUCT.MethodValue;
    pBuffer[3]=ASG_START_ID;
    pBuffer[127]=pBuffer[0]+pBuffer[2]+pBuffer[3];
    return 0;
}

int ParamCCS::ASG_Start(QVector<UINT>& pBuffer){//,DMSIT_STRUCT& p_ASG_STRUCT
    pBuffer.resize(128);
    memset(pBuffer.data(), 0, pBuffer.size()* sizeof(UINT));
    pBuffer[0]=ASG_COMMAND_ID;
    pBuffer[2]=0;//p_ASG_STRUCT.MethodValue;
    pBuffer[3]=ASG_START_ID;
    pBuffer[127]=pBuffer[0]+pBuffer[2]+pBuffer[3];
    return 0;
}

int ParamCCS::ASG_Stop(QVector<UINT>& pBuffer)
{
    pBuffer.resize(128);
    memset(pBuffer.data(), 0, pBuffer.size()* sizeof(UINT));
    pBuffer[0]=ASG_COMMAND_ID;
    pBuffer[3]=ASG_HALT_ID;
    pBuffer[127]=pBuffer[0]+ pBuffer[3];
    return 0;
}


QByteArray ParamCCS::uartCMDData(QByteArray& baReq_s_comm, UINT baudrate)
{
    QByteArray mBaReq_s_ccs(512, 0);
    //mBaReq_s_ccs.resize(512);
    //memset(mBaReq_s_ccs.data(),0,512);
    uint* cmdData = (uint*)(mBaReq_s_ccs.data());
    const uint maxLen = 120;
    uint uartTxBytes = baReq_s_comm.size();
    if (uartTxBytes > maxLen)
        uartTxBytes = maxLen;
    cmdData[0] = 0xFFFFF133;
    cmdData[1] = ((100000000u / baudrate) << 16) | uartTxBytes;//cmdData[1] = ((100000000u / 9600u) << 16) | uartTxBytes;
    for (uint idx = 0; idx < uartTxBytes; ++idx)
        cmdData[2 + idx] = (baReq_s_comm.data()[idx])&0xff;
    cmdData[127] = checkSum(cmdData, 127);
    return mBaReq_s_ccs;
}

uint ParamCCS::checkSum(uint* data, size_t size)
{
    uint* pEnd = data + size;
    uint* pOffset = data;
    uint uSum = 0;
    while(pOffset < pEnd){
        uSum += *pOffset;
        pOffset++;
    }
    return uSum;
}
