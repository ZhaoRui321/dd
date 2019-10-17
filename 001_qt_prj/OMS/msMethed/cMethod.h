#pragma once
#include "MsParams.h"
#include "mathmethod.h"
#define ENVIRONMENT_QT
#ifdef ENVIRONMENT_QT
#include <QDir>
#include <QSettings>
#endif

#define MAX_MEMORY 16*1024*1024
#define FreqDataL_32 16
#define DF_DAC_GAIN        m_Adjust_Factor.d_DACGain
#define DF_DAC_OFFSET      m_Adjust_Factor.d_DACOffset
#define DF_MASS_SCALE      m_Adjust_Factor.d_Mass_Scale_Factor
#define DF_MASS_OFFSET     m_Adjust_Factor.d_Mass_Offset_Factor
#define DF_MASS_FORWARD    m_Adjust_Factor.d_Mass_Forward_Extension
#define DF_MASS_DIO        m_Adjust_Factor.dio
#define DEFAULT_PTM_CONFIG_FILE            "./PTMSCONFIG.ini"
/**
 * @brief
 *
 */
typedef void* MSPointerT;

/**
 * @brief
 *
 */
struct _Command_Struct
{
    int i_StageNum                          = 0;                //阶段数 /**< TODO */
    int* p_StageName                        = nullptr;          //极端名字 /**< TODO */
    MSPointerT* p_STAGE_PARAMETER                  = nullptr;          //阶段内容 /**< TODO */
    unsigned int* pBufferFreqTable         = nullptr;          //数据存储区 /**< TODO */
    unsigned int CurrLength=0;                                  //数据长度，uint /**< TODO */
    unsigned int nCurrFF;                                       //频点个数 /**< TODO */
    int nMSstage;                                               // /**< TODO */
    int num_MSScale;                                            //质量矫正表个数 /**< TODO */
    double Tpassed_us;                                          //时间长度 /**< TODO */
    int isTrigger=false;
    _Adjust_Factor m_Adjust_Factor;                             //矫正参数 /**< TODO */
    cMathMethod mMathMethod;
};

/**
 * @brief
 *
 */
class CMethod
{
private:
    _Command_Struct m_Command_Struct; /**< TODO */
public:
    /**
     * @brief
     *
     */
    CMethod();
    /**
     * @brief
     *
     */
    ~CMethod();
    /**
     * @brief
     *
     * @param p_Adjust_Factor
     * @param Q_path
     * @param NumStage
     * @return bool
     */
    bool InitState(_Adjust_Factor* p_Adjust_Factor,QString Q_path=nullptr,int NumStage=100);
    template <typename Stage_Param>
    /**
     * @brief
     *
     * @param p_Stage_Param
     * @return int
     */
    int AddStage(Stage_Param* p_Stage_Param){
        *(m_Command_Struct.p_STAGE_PARAMETER+m_Command_Struct.i_StageNum) = (MSPointerT)p_Stage_Param;
        *(m_Command_Struct.p_StageName+m_Command_Struct.i_StageNum)       = p_Stage_Param->i_Name;
        if(m_Command_Struct.i_StageNum<32)
            p_Stage_Param->ui_DIO=m_Command_Struct.m_Adjust_Factor.dio[m_Command_Struct.i_StageNum];
        m_Command_Struct.i_StageNum++;
        return m_Command_Struct.i_StageNum-1;}                  //返回所处阶段号
    /**
     * @brief
     *
     * @param pBufferFreqTable
     * @param nMSCALEn
     * @param MSLength
     * @param methodNO
     * @param ID_DataPackage
     * @return int
     */
    int CreateMethod(unsigned char* pBufferFreqTable,           //数据存储区
                     int* nMSCALEn=nullptr,            //返回质量校正表的数目
                     int* MSLength=nullptr,                    //返回实际表长
                     int methodNO=0,
                     int ID_DataPackage=0);              //命令包编号，默认为0
private:
    int createHead(_Command_Struct& pCommand_Struct,
                   unsigned int methodNO,
                   unsigned int DP_ID);
};
/**
 * @brief
 *
 */
class Stage
{
public:
    /**
     * @brief
     *
     */
    Stage(){}
    /**
     * @brief
     *
     */
    virtual ~Stage(){}
    /**
     * @brief
     *
     * @param p_StageParam
     * @param pCommand_Struct
     * @return int
     */
    virtual int CreatStage(int* p_StageParam,_Command_Struct* pCommand_Struct, bool isSpecial= false)=0;
    _METHOD_STATE fillForm(_Command_Struct* pCommand_Struct,
                  unsigned int cycle,
                  unsigned int FreqTune,
                  unsigned int DIO,
                  unsigned int paramDDS1,
                  unsigned int paramDDS2,
                  double* d_DAC);
};
/**
 * @brief
 *
 */
class Injection:Stage
{
    public:
    /**
     * @brief
     *
     * @param p_StageParam
     * @param pCommand_Struct
     * @return int
     */
    int CreatStage(int* p_StageParam,_Command_Struct* pCommand_Struct, bool isSpecial=false);
};
/**
 * @brief
 *
 */
class Cooling:Stage
{
    public:
    /**
     * @brief
     *
     * @param p_StageParam
     * @param pCommand_Struct
     * @return int
     */
    int CreatStage(int* p_StageParam,_Command_Struct* pCommand_Struct, bool isSpecial=false);
};
/**
 * @brief
 *
 */
class RExcitation:Stage
{
    public:
    /**
     * @brief
     *
     * @param p_StageParam
     * @param pCommand_Struct
     * @return int
     */
    int CreatStage(int* p_StageParam,_Command_Struct* pCommand_Struct, bool isSpecial=false);
};
/**
 * @brief
 *
 */
class IsoCooling:Stage
{
    public:
    /**
     * @brief
     *
     * @param p_StageParam
     * @param pCommand_Struct
     * @return int
     */
    int CreatStage(int* p_StageParam,_Command_Struct* pCommand_Struct, bool isSpecial=false);
};
/**
 * @brief
 *
 */
class DAWI:Stage
{
    public:
    /**
     * @brief
     *
     * @param p_StageParam
     * @param pCommand_Struct
     * @return int
     */
    int CreatStage(int* p_StageParam,_Command_Struct* pCommand_Struct, bool isSpecial=false);
};
/**
 * @brief
 *
 */
class BIsoScan:Stage
{
    /**
     * @brief
     *
     * @param p_StageParam
     * @param pCommand_Struct
     * @return int
     */
    int CreatStage(int* p_StageParam,_Command_Struct* pCommand_Struct, bool isSpecial=false);
};
/**
 * @brief
 *
 */
class FIsoScan:Stage
{
    public:
    /**
     * @brief
     *
     * @param p_StageParam
     * @param pCommand_Struct
     * @return int
     */
    int CreatStage(int* p_StageParam,_Command_Struct* pCommand_Struct, bool isSpecial=false);
};
/**
 * @brief
 *
 */
class Scan:Stage
{
    public:
    /**
     * @brief
     *
     * @param p_StageParam
     * @param pCommand_Struct
     * @return int
     */
    int CreatStage(int* p_StageParam,_Command_Struct* pCommand_Struct, bool isSpecial=false);
};
/**
 * @brief
 *
 */
class ScanSpecial:Stage
{
    public:
    /**
     * @brief
     *
     * @param p_StageParam
     * @param pCommand_Struct
     * @return int
     */
    int CreatStage(int* p_StageParam,_Command_Struct* pCommand_Struct, bool isSpecial=false);
};
/**
 * @brief
 *
 */
class Empty:Stage
{
    public:
    /**
     * @brief
     *
     * @param p_StageParam
     * @param pCommand_Struct
     * @return int
     */
    int CreatStage(int* p_StageParam,_Command_Struct* pCommand_Struct, bool isSpecial=false);
};
/*class Custom:Stage
{
    public:
    int CreatStage(int* p_StageParam,_Command_Struct* pCommand_Struct);
};*/
