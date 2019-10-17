#pragma once
#include <QVector>
#include<vector>
/**
 * @brief ParamCCS
 * CCS,ASG,DAQ指令参数及数据生成
 */
typedef unsigned int UINT;


struct _FRAME_BUFF_CCS{
public:
    static QByteArray* resize(int nLength= 16 * 1024 * 1024){
        static _FRAME_BUFF_CCS insFRAME_BUFF_CCS;
        insFRAME_BUFF_CCS.mBuff.resize(nLength);
        return &(insFRAME_BUFF_CCS.mBuff);
    }
    static QByteArray* get(){
        static _FRAME_BUFF_CCS insFRAME_BUFF_CCS;
        return &(insFRAME_BUFF_CCS.mBuff);
    }
private:
    QByteArray mBuff;
    _FRAME_BUFF_CCS(){}
    virtual ~_FRAME_BUFF_CCS(){}
    _FRAME_BUFF_CCS(const _FRAME_BUFF_CCS&){}
    _FRAME_BUFF_CCS& operator=(const _FRAME_BUFF_CCS&){
        static _FRAME_BUFF_CCS insFRAME_BUFF_CCS;
        return insFRAME_BUFF_CCS;
    }
};
//ACQUISITION
//struct _DAQ_BUFF_ACQUIS{
//public:
//    static QList<std::vector<double>>* get(){
//        static _DAQ_BUFF_ACQUIS insDAQ_BUFF_ACQUIS;
//        return &(insDAQ_BUFF_ACQUIS.mBuff);
//    }
//private:
//    QList<std::vector<double>> mBuff;               //size-allPoint
//    _DAQ_BUFF_ACQUIS(){}
//    virtual ~_DAQ_BUFF_ACQUIS(){}
//    _DAQ_BUFF_ACQUIS(const _DAQ_BUFF_ACQUIS&){}
//    _DAQ_BUFF_ACQUIS& operator=(const _DAQ_BUFF_ACQUIS&){
//        static _DAQ_BUFF_ACQUIS ins_DAQ_BUFF_ACQUIS;
//        return ins_DAQ_BUFF_ACQUIS;
//    }
//};

struct _DAQ_X_ACQUIS{
//public:
//    static std::vector<double>* resize(int nLength){
//        static _DAQ_X_ACQUIS insDAQ_X_ACQUIS;
//        insDAQ_X_ACQUIS.mBuff.resize(nLength);
//        return &(insDAQ_X_ACQUIS.mBuff);
//    }
//    static std::vector<double>* get(){
//        static _DAQ_X_ACQUIS insDAQ_X_ACQUIS;
//        return &(insDAQ_X_ACQUIS.mBuff);
//    }
//private:
//    std::vector<double> mBuff;         //size-allPoint
//    _DAQ_X_ACQUIS(){}
//    virtual ~_DAQ_X_ACQUIS(){}
//    _DAQ_X_ACQUIS(const _DAQ_X_ACQUIS&){}
//    _DAQ_X_ACQUIS& operator=(const _DAQ_X_ACQUIS&){
//        static _DAQ_X_ACQUIS insDAQ_X_ACQUIS;
//        return insDAQ_X_ACQUIS;
//    }
public:
    static QList<std::vector<double>>* get(){
        static _DAQ_X_ACQUIS insDAQ_X_ACQUIS;
        return &(insDAQ_X_ACQUIS.mBuff);
    }
private:
    QList<std::vector<double>> mBuff;               //size-allPoint
    _DAQ_X_ACQUIS(){}
    virtual ~_DAQ_X_ACQUIS(){}
    _DAQ_X_ACQUIS(const _DAQ_X_ACQUIS&){}
    _DAQ_X_ACQUIS& operator=(const _DAQ_X_ACQUIS&){
        static _DAQ_X_ACQUIS ins_DAQ_X_ACQUIS;
        return ins_DAQ_X_ACQUIS;
    }
};

struct _DAQ_Y_ACQUIS{
public:
    static QList<std::vector<double>>* get(){
        static _DAQ_Y_ACQUIS insDAQ_Y_ACQUIS;
        return &(insDAQ_Y_ACQUIS.mBuff);
    }
private:
    QList<std::vector<double>> mBuff;               //size-allPoint
    _DAQ_Y_ACQUIS(){}
    virtual ~_DAQ_Y_ACQUIS(){}
    _DAQ_Y_ACQUIS(const _DAQ_Y_ACQUIS&){}
    _DAQ_Y_ACQUIS& operator=(const _DAQ_Y_ACQUIS&){
        static _DAQ_Y_ACQUIS ins_DAQ_Y_ACQUIS;
        return ins_DAQ_Y_ACQUIS;
    }
};

struct _CHART_X_ACQUIS{
public:
    static QList<std::vector<double>>* get(){
        static _CHART_X_ACQUIS insCHART_X_ACQUIS;
        return &(insCHART_X_ACQUIS.mBuff);
    }
private:
    QList<std::vector<double>> mBuff;//std::vector<double> mBuff;         //size-allPoint
    _CHART_X_ACQUIS(){}
    virtual ~_CHART_X_ACQUIS(){}
    _CHART_X_ACQUIS(const _CHART_X_ACQUIS&){}
    _CHART_X_ACQUIS& operator=(const _CHART_X_ACQUIS&){
        static _CHART_X_ACQUIS insCHART_X_ACQUIS;
        return insCHART_X_ACQUIS;
    }
};

struct _BASELINE_OFFSET{
public:
    static QList<std::vector<double>>* get(){
        static _BASELINE_OFFSET insCHART_X_ACQUIS;
        return &(insCHART_X_ACQUIS.mBuff);
    }
private:
    QList<std::vector<double>> mBuff;//std::vector<double> mBuff;         //size-allPoint
    _BASELINE_OFFSET(){}
    virtual ~_BASELINE_OFFSET(){}
    _BASELINE_OFFSET(const _BASELINE_OFFSET&){}
    _BASELINE_OFFSET& operator=(const _BASELINE_OFFSET&){
        static _BASELINE_OFFSET insCHART_X_ACQUIS;
        return insCHART_X_ACQUIS;
    }
};

struct _CHART_Y_ACQUIS{
public:
    static QList<std::vector<double>>* get(){
        static _CHART_Y_ACQUIS insCHART_Y_ACQUIS;
        return &(insCHART_Y_ACQUIS.mBuff);
    }
private:
    QList<std::vector<double>> mBuff;         //size-allPoint
    _CHART_Y_ACQUIS(){}
    virtual ~_CHART_Y_ACQUIS(){}
    _CHART_Y_ACQUIS(const _CHART_Y_ACQUIS&){}
    _CHART_Y_ACQUIS& operator=(const _CHART_Y_ACQUIS&){
        static _CHART_Y_ACQUIS insCHART_Y_ACQUIS;
        return insCHART_Y_ACQUIS;
    }
};

struct _STRUCT_GRAPH{
public:
    std::vector<double> Absc;
    std::vector<double> Ord;
    QVector<QString> Marker;
    _STRUCT_GRAPH(int size=0){
        Absc.resize(size);
        Ord.resize(size);
        Marker.resize(size);
    }
};

struct _CHART_PEAK_ACQUIS{
public:
    static QList<_STRUCT_GRAPH>* get(){
        static _CHART_PEAK_ACQUIS insCHART_PEAK_ACQUIS;
        return &(insCHART_PEAK_ACQUIS.mBuff);
    }
private:
    QList<_STRUCT_GRAPH> mBuff;         //size-allPoint
    _CHART_PEAK_ACQUIS(){}
    virtual ~_CHART_PEAK_ACQUIS(){}
    _CHART_PEAK_ACQUIS(const _CHART_PEAK_ACQUIS&){}
    _CHART_PEAK_ACQUIS& operator=(const _CHART_PEAK_ACQUIS&){
        static _CHART_PEAK_ACQUIS insCHART_PEAK_ACQUIS;
        return insCHART_PEAK_ACQUIS;
    }
};

struct _PEAK_ABSC_ACQUIS{
public:
    static std::vector<double>* resize(int nLength){
        static _PEAK_ABSC_ACQUIS insPEAK_ABSC_ACQUIS;
        insPEAK_ABSC_ACQUIS.mBuff.resize(nLength);
        return &(insPEAK_ABSC_ACQUIS.mBuff);
    }
    static std::vector<double>* get(){
        static _PEAK_ABSC_ACQUIS insPEAK_ABSC_ACQUIS;
        return &(insPEAK_ABSC_ACQUIS.mBuff);
    }
private:
    std::vector<double> mBuff;         //size-nPeak
    _PEAK_ABSC_ACQUIS(){}
    virtual ~_PEAK_ABSC_ACQUIS(){}
    _PEAK_ABSC_ACQUIS(const _PEAK_ABSC_ACQUIS&){}
    _PEAK_ABSC_ACQUIS& operator=(const _PEAK_ABSC_ACQUIS&){
        static _PEAK_ABSC_ACQUIS insPEAK_ABSC_ACQUIS;
        return insPEAK_ABSC_ACQUIS;
    }
};

struct _PEAK_ORD_ACQUIS{
public:
    static std::vector<double>* resize(int nLength){
        static _PEAK_ORD_ACQUIS insPEAK_ORD_ACQUIS;
        insPEAK_ORD_ACQUIS.mBuff.resize(nLength);
        return &(insPEAK_ORD_ACQUIS.mBuff);
    }
    static std::vector<double>* get(){
        static _PEAK_ORD_ACQUIS insPEAK_ORD_ACQUIS;
        return &(insPEAK_ORD_ACQUIS.mBuff);
    }
private:
    std::vector<double> mBuff;         //size-nPeak
    _PEAK_ORD_ACQUIS(){}
    virtual ~_PEAK_ORD_ACQUIS(){}
    _PEAK_ORD_ACQUIS(const _PEAK_ORD_ACQUIS&){}
    _PEAK_ORD_ACQUIS& operator=(const _PEAK_ORD_ACQUIS&){
        static _PEAK_ORD_ACQUIS insPEAK_ORD_ACQUIS;
        return insPEAK_ORD_ACQUIS;
    }
};

struct _PEAK_START_ACQUIS{
public:
    static std::vector<int>* resize(int nLength){
        static _PEAK_START_ACQUIS insPEAK_START_ACQUIS;
        insPEAK_START_ACQUIS.mBuff.resize(nLength);
        return &(insPEAK_START_ACQUIS.mBuff);
    }
    static std::vector<int>* get(){
        static _PEAK_START_ACQUIS insPEAK_START_ACQUIS;
        return &(insPEAK_START_ACQUIS.mBuff);
    }
private:
    std::vector<int> mBuff;         //size-nPeak
    _PEAK_START_ACQUIS(){}
    virtual ~_PEAK_START_ACQUIS(){}
    _PEAK_START_ACQUIS(const _PEAK_START_ACQUIS&){}
    _PEAK_START_ACQUIS& operator=(const _PEAK_START_ACQUIS&){
        static _PEAK_START_ACQUIS insPEAK_START_ACQUIS;
        return insPEAK_START_ACQUIS;
    }
};

struct _PEAK_END_ACQUIS{
public:
    static std::vector<int>* resize(int nLength){
        static _PEAK_END_ACQUIS insPEAK_END_ACQUIS;
        insPEAK_END_ACQUIS.mBuff.resize(nLength);
        return &(insPEAK_END_ACQUIS.mBuff);
    }
    static std::vector<int>* get(){
        static _PEAK_END_ACQUIS insPEAK_END_ACQUIS;
        return &(insPEAK_END_ACQUIS.mBuff);
    }
private:
    std::vector<int> mBuff;         //size-nPeak
    _PEAK_END_ACQUIS(){}
    virtual ~_PEAK_END_ACQUIS(){}
    _PEAK_END_ACQUIS(const _PEAK_END_ACQUIS&){}
    _PEAK_END_ACQUIS& operator=(const _PEAK_END_ACQUIS&){
        static _PEAK_END_ACQUIS insPEAK_END_ACQUIS;
        return insPEAK_END_ACQUIS;
    }
};

struct _PEAK_MARK_ACQUIS{
public:
    static std::vector<int>* resize(int nLength){
        static _PEAK_MARK_ACQUIS insPEAK_MARK_ACQUIS;
        insPEAK_MARK_ACQUIS.mBuff.resize(nLength);
        return &(insPEAK_MARK_ACQUIS.mBuff);
    }
    static std::vector<int>* get(){
        static _PEAK_MARK_ACQUIS insPEAK_MARK_ACQUIS;
        return &(insPEAK_MARK_ACQUIS.mBuff);
    }
private:
    std::vector<int> mBuff;         //size-nPeak
    _PEAK_MARK_ACQUIS(){}
    virtual ~_PEAK_MARK_ACQUIS(){}
    _PEAK_MARK_ACQUIS(const _PEAK_MARK_ACQUIS&){}
    _PEAK_MARK_ACQUIS& operator=(const _PEAK_MARK_ACQUIS&){
        static _PEAK_MARK_ACQUIS insPEAK_MARK_ACQUIS;
        return insPEAK_MARK_ACQUIS;
    }
};

struct _BASELINE_Y_ACQUIS{
public:
    static std::vector<double>* resize(int nLength){
        static _BASELINE_Y_ACQUIS insBASELINE_Y_ACQUIS;
        insBASELINE_Y_ACQUIS.mBuff.resize(nLength);
        return &(insBASELINE_Y_ACQUIS.mBuff);
    }
    static std::vector<double>* get(){
        static _BASELINE_Y_ACQUIS insBASELINE_Y_ACQUIS;
        return &(insBASELINE_Y_ACQUIS.mBuff);
    }
private:
    std::vector<double> mBuff;              //size-allPoint
    _BASELINE_Y_ACQUIS(){}
    virtual ~_BASELINE_Y_ACQUIS(){}
    _BASELINE_Y_ACQUIS(const _BASELINE_Y_ACQUIS&){}
    _BASELINE_Y_ACQUIS& operator=(const _BASELINE_Y_ACQUIS&){
        static _BASELINE_Y_ACQUIS insBASELINE_Y_ACQUIS;
        return insBASELINE_Y_ACQUIS;
    }
};
struct _STRUCT_PEAK{
public:
    std::vector<double> Absc;
    std::vector<double> Ord;
    std::vector<int> Start;
    std::vector<int> End;
    double yXIC = 0.0;
    _STRUCT_PEAK(int size=0){
        Absc.resize(size);
        Ord.resize(size);
        Start.resize(size);
        End.resize(size);
    }
};

struct _PEAK_THREAD_ACQUIS{
public:
    static _STRUCT_PEAK* get(){
        static _PEAK_THREAD_ACQUIS insPEAK_THREAD_ACQUIS;
        return &(insPEAK_THREAD_ACQUIS.mBuff);
    }
private:
    _STRUCT_PEAK mBuff;         //size-nPeak
    _PEAK_THREAD_ACQUIS(){}
    virtual ~_PEAK_THREAD_ACQUIS(){}
    _PEAK_THREAD_ACQUIS(const _PEAK_THREAD_ACQUIS&){}
    _PEAK_THREAD_ACQUIS& operator=(const _PEAK_THREAD_ACQUIS&){
        static _PEAK_THREAD_ACQUIS insPEAK_THREAD_ACQUIS;
        return insPEAK_THREAD_ACQUIS;
    }
};

class ParamCCS
{
public:
    enum CCS_CMD_ID{
        STATE_REQ_ID			= 0xFFFFF001,
        SOFT_RST_ID				= 0xFFFFF002,
        VERSION_REQ_ID			= 0xFFFFF003,
        MS_METHOD_ID			=0xFFFFF065,
        MS_UPDATE_ID			=0xFFFFF066,
        MS_START_ID				=0xFFFFF067,
        MS_STOP_ID				=0xFFFFF068,
        BUFFER_GAS_CTRL_ID  = 0xFFFFF069,
        //BUFFER_GAS_EXT_ID	  = 0xFFFFF06A,
        PWM_GENERATE_ID	  = 0xFFFFF06B,
        PUMP_VENT_CTRL_ID   = 0xFFFFF0C9,
        GHV_ENABLE_CTRL_ID  = 0xFFFFF12D,
        TEMPERATURE_CTRL_ID = 0xFFFFF12E,
        TEMPERATURE_PID_ID  = 0xFFFFF130,
        HEATING_SWITCH_ID   = 0xFFFFF131,
        SAMPLE_GAS_CTRL_ID  = 0xFFFFF132,
        DAQ_COMMAND_ID			= 0xFFFFF201,
        ASG_COMMAND_ID			= 0xFFFFF301
    };
    enum DAQ_SUBCMD_ID{
        DAQ_CONFIG_ID			= 0x00000001,
        DAQ_START_ID			= 0x00000002,
        DAQ_DATAREQ_ID			= 0x00000004,
        DAQ_STOP_ID				= 0x00000008,
        ASG_POWERDOWN_ID		= 0x00000010
    };
    enum ASG_SUBCMD_ID{
        ASG_CONFIG_ID			= 0x00000001,
        ASG_SET_ID				= 0x00000002,
        ASG_UPDATE_ID			= 0x00000004,
        ASG_START_ID			= 0x00000008,
        ASG_HALT_ID				= 0x00000010,
        ASG_ADJUST_ID			= 0x00000020
    };
    struct _TEMPERATURE_PID{
        UINT p_PID;
        UINT i_PID;
        UINT d_PID;
    };
    struct _DAQ_CONFIG{
        UINT No_AQP;
        UINT Frq_AQ;
        UINT No_ACC;
    };
    struct CCS_SCAN{
        UINT triggerEXT=0,
        scanTimes=0;
    };
    struct DAC_STRUCT{
        unsigned int
            DAQ_Trigger;
        double Frequency,
            Value_DAC[12],
            HoldTime;//ms
    };
    struct PARAM_STRUCT{
        double Gain_DAC[12],
            Offset_DAC[12];
        std::vector<DAC_STRUCT> pDACStruct;
    };
    struct PWM_GENETATE{
        unsigned long lPWMCycle[8];
        unsigned long lPWMUp[8];
        unsigned long lPWMDown[8];
        unsigned long lPWMEnable;
    };
    struct FREQUENCY{
        double Freq_MHz[6];
        unsigned long Delay_ns[6];
        double Freq_Duty[6];
        unsigned long Freq_Enable[6];
        unsigned long PWM_CTRL[6];
    };
    struct DMSIT_DAC_STRUCT{
        double	HoldTime;
        unsigned long	MaskDAC[8];
        double DacValue[160];
        FREQUENCY Freq;
    };
    struct _ASG_STRUCT{
        UINT	MethodValue;
        std::vector<DMSIT_DAC_STRUCT> pStructDAC;
        double DacOffset[160],
            DacGain[160];
    };
//    struct SDACConfigPara{
//        unsigned long	Offset0;
//        unsigned long	Offset1;
//    };
    struct SDACAdjustPara{
        float	ParaA[160];
        float	ParaB[160];
    };

    struct _STATE_REQUEST_CCS{
        double adcValue[4]={0,0,0,0};
    };

    ParamCCS();
    static void printfMethod(const QByteArray &buffer, bool ifAppend, QString fileName= "./MSMethod.txt");
    static void printfMethod(QVector<UINT>& buffer, bool ifAppend, QString fileName= "./command.txt");
    static void Checksum(QVector<UINT>& pBuffer);
    static uint checkSum(uint* data, size_t size);

    static int bufferGasControlG(QVector<UINT>& pBuffer,bool bufferGasControl);
    static int pumpVentSystemG(QVector<UINT>& pBuffer, bool openPump);// 生成系统真空控制命令数据
    static int enableHV(QVector<UINT>& pBuffer, bool openGHV);// 生成全局高压系统及离子源使能命令数据
    static int tempControl(QVector<UINT>& pBuffer, uint temperature);// 生成离子源温度控制命令数据
    static int tempPID(QVector<UINT>& pBuffer, _TEMPERATURE_PID& p_TEMPERATURE_PID);// 生成离子源温度控制PID设置命令数据
    static int heatingSwitch(QVector<UINT>& pBuffer, uint heatingSwitch);// 生成离子源加热开关命令数据
    static int gasControl(QVector<UINT>& pBuffer, uint sampleGas);// 生成样品气体流速控制命令数据
    static int restart(QVector<UINT>& pBuffer);
    static int sysSoftReset(QVector<UINT>& pBuffer);
    static int sysVersionRequest(QVector<UINT>& pBuffer);
    static int generaterPWM(QVector<UINT>& pBuffer,PWM_GENETATE& pPWM_GENETATE);
    static int stateRequest(QVector<UINT>& pBuffer);

    static int CCS_Start(QVector<UINT>& pBuffer, CCS_SCAN& pCCS_SCAN);
    static int CCS_Start(QVector<UINT>& pBuffer);
    static int CCS_Halt(QVector<UINT>& pBuffer);
    static int CCS_Update(UINT* pBuffer,UINT* nBuffer,double dSingleFreq,PARAM_STRUCT* pPARAM_STRUCT);

    static int DAQ_Config(QVector<UINT>& pBuffer,const _DAQ_CONFIG &p_DAQ_CONFIG);
    static int DAQ_Request(UINT* pBuffer, UINT uNoDataReq);
    static int DAQ_Request(QVector<UINT>& pBuffer, UINT uNoDataReq);
    static int DAQ_Start(QVector<UINT>& pBuffer);
    static int DAQ_Stop(QVector<UINT>& pBuffer);
    static int DAQ_Powerdown(QVector<UINT>& pBuffer);

    static int ASG_Config(QVector<UINT>& pBuffer);//,SDACConfigPara *pDacConfigP);
    static int ASG_Adjust(QVector<UINT>& pBuffer,SDACAdjustPara *pDacAdjustP=nullptr);
    static int ASG_Update(QVector<UINT>& pBuffer,_ASG_STRUCT& p_ASG_STRUCT);
    static int ASG_Start(QVector<UINT>& pBuffer,_ASG_STRUCT& p_ASG_STRUCT);
    static int ASG_Start(QVector<UINT>& pBuffer);
    static int ASG_Stop(QVector<UINT>& pBuffer);

    static QByteArray uartCMDData(QByteArray& baReq_s_comm, UINT baudrate= 9600u);
};

