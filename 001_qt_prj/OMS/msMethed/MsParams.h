#pragma once
#include <cPublicCCS.h>

/**
 * @brief
 *
 */
enum _METHOD_STATE:const int{
    Succeed=0,
    Error_Struct=1,                                    //creatmethod  pStage!=nullptr
    Error_MemOver,
    DDS_Injection_OverQuick,
    Holdtime_Injection_Short,
    Holdtime_Injection_Over,

    DDS_Cooling_OverQuick,
    Holdtime_Cooling_Short,
    Holdtime_Cooling_Over,

    DDS_RExcitation_OverQuick,
    Holdtime_RExcitation_Short,
    Holdtime_RExcitation_Over,

    DDS_IsoCooling_OverQuick,
    Holdtime_IsoCooling_Short,
    Holdtime_IsoCooling_Over,

    DDS_DAWI_OverQuick,
    Holdtime_DAWI_Short,
    Holdtime_DAWI_Over,

    DDS_BIsoScan_OverQuick,
    Holdtime_BIsoScan_Short,
    Holdtime_BIsoScan_Over,

    DDS_FIsoScan_OverQuick,
    Holdtime_FIsoScan_Short,
    Holdtime_FIsoScan_Over,

    DDS_Scan_OverQuick,
    Holdtime_Scan_Short,
    Holdtime_Scan_Over,

    DDS_Empty_OverQuick,
    Holdtime_Empty_Short,
    Holdtime_Empty_Over,

    DDS_i_Custom_OverQuick,
    Holdtime_i_Custom_Short,
    Holdtime_i_Custom_Over,

    DDS_IB_OverQuick,
    Holdtime_IB_Short,
    Holdtime_IB_Over
};

/**
 * @brief
 *
 */
enum _STAGE_NAME:const int
{
    i_Null=0,
    i_Injection   = 1,
    i_Cooling     = 2,
    i_RExcitation = 3,
    i_IsoCooling  = 4,
    i_DAWI        = 5,
    i_BIsoScan    = 6,
    i_FIsoScan    = 7,
    i_Scan        = 8,
    i_Empty       = 9,
    i_Custom      = 10,
    i_IB          = 11,
    i_ScanSpecial = 12
};

/**
 * @brief
 *
 */
struct _Adjust_Factor
{
    //double          DAQFREQP=1.0;				//1: Sample rate: 1MS/s, 2: Sample rate: 2MS/s, 4: Sample rate: 4MS/s /**< TODO */
    double          d_DACGain[12]={1.0,10.0,10.0,10.0,10.0,10.0,1.0,-300.0,-1000.0,1.0,1.0,1.0}; /**< TODO */
    double          d_DACOffset[12]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}; /**< TODO */
    double          d_Mass_Scale_Factor=1;             //Mass_Scale_Factor=1; /**< TODO */
    double          d_Mass_Offset_Factor=0;            //Mass_Offset_Factor=0; /**< TODO */
    double          d_Mass_Forward_Extension=2;        //Mass_Forward_Extension=2; /**< TODO */
    unsigned int    dio[32]; /**< TODO */
};

/**
 * @brief
 *
 */
struct _MASS_SCALE_TABLE
{
    long            StartDAQpoint; /**< TODO */
    long            EndDAQpoint; /**< TODO */
    double          StartMass; /**< TODO */
    double          StopMass; /**< TODO */
    double          NonlinearParam1; /**< TODO */
    double          NonlinearParam2; /**< TODO */
    double          NonlinearParam3; /**< TODO */
};
/**
 * @brief
 *
 */
struct _LIT_PARAM{
    int       i_Name=i_Null;
};

struct _Injection_Param:_LIT_PARAM{
    _Injection_Param(){i_Name=i_Injection;}//int       i_Name=i_Injection; /**< TODO */
    double          d_Time=100;                        //ms /**< TODO */

    double          d_Mass_Start_Th= 100;                //Th; /**< TODO */
    double          d_Mass_End_Th  = 1000;
    double          d_msStartOrig = 100;
    double          d_msEndOrig = 1000;

    unsigned int    d_Qarray_RF_Step = 10;
    double          d_Qarray_RF_FactorA = 0.167;
    double          d_Qarray_RF_FactorB = 33.333;
    double          VoltageRFOffset = 10;

    unsigned int    i_DDSDuration=64;                  //DDS; /**< TODO */
    unsigned int    i_DDSADelay=0;                     //DDS; /**< TODO */
    unsigned int    i_DDSADuty=0;                      //DDS; /**< TODO */
    unsigned int    i_DDSBDelay=16;                    //DDS; /**< TODO */
    unsigned int    i_DDSBDuty=48;                     //DDS; /**< TODO */
    unsigned int    ui_DIO=0; /**< TODO */
    double          d_DAC[12]; /**< TODO */
};
/**
 * @brief
 *
 */
struct _Cooling_Param:_LIT_PARAM{
    _Cooling_Param(){i_Name=i_Cooling;}//int       i_Name=i_Cooling; /**< TODO */
    double          d_Time=50;                         //ms  Cooling_Time=50;ms /**< TODO */

    double          d_Mass_Start_Th=100;                //Th  Mass_Start_Th=40; /**< TODO */
    double          d_msStartOrig = 100;

    unsigned int    i_DDSDuration=64;                  //DDS  TuneParam[0].Dipole_Duration_DDS=64; /**< TODO */
    unsigned int    i_DDSADelay=0;                     //DDS; /**< TODO */
    unsigned int    i_DDSADuty=0;                      //DDS; /**< TODO */
    unsigned int    i_DDSBDelay=16;                    //DDS; /**< TODO */
    unsigned int    i_DDSBDuty=48;                     //DDS; /**< TODO */
    unsigned int    ui_DIO=0; /**< TODO */
    double          d_DAC[12]; /**< TODO */
};
/**
 * @brief
 *
 */
struct _RExcitation_Param:_LIT_PARAM{
    _RExcitation_Param(){i_Name=i_RExcitation;}//int       i_Name=i_RExcitation; /**< TODO */
    double          d_Time=100;                        //ms  TandemParam[0].Fragmentation_Time=100;  ms /**< TODO */

    double          d_Mass_Start_Th=40;                //Th  Mass_Start_Th=40; /**< TODO */
    double          d_msStartOrig = 100;

    double          d_Precursor_Mass=152;              //Th  TandemParam[0].Precursor_Mass /**< TODO */
    double          d_msPrecursorOrig=152;
    double          d_Excitation_Frequency_Offset=1; /**< TODO */

    unsigned int    i_DDSDuration=192;                 //DDS; /**< TODO */
    unsigned int    i_DDSADelay=37;                    //DDS; /**< TODO */
    unsigned int    i_DDSADuty=85;                     //DDS; /**< TODO */
    unsigned int    i_DDSBDelay=16;                    //DDS; /**< TODO */
    unsigned int    i_DDSBDuty=48;                     //DDS; /**< TODO */
    unsigned int    ui_DIO=0; /**< TODO */
    double          d_DAC[12]; /**< TODO */
};
/**
 * @brief
 *
 */
struct _IsoCooling_Param:_LIT_PARAM{
    _IsoCooling_Param(){i_Name=i_IsoCooling;}//int       i_Name=i_IsoCooling; /**< TODO */
    double          d_Time=50;                         //ms  TandemParam[0].Fragment_Cooling_Time=50; ms /**< TODO */

    double          d_Mass_Start_Th=40;                //Th  Mass_Start_Th=40; /**< TODO */
    double          d_msStartOrig = 100;

    double          d_Precursor_Mass=152;              //Th  TandemParam[0].Precursor_Mass /**< TODO */
    double          d_msPrecursorOrig=152;

    unsigned int    i_DDSDuration=64;                  //DDS; /**< TODO */
    unsigned int    i_DDSADelay=0;                     //DDS; /**< TODO */
    unsigned int    i_DDSADuty=0;                      //DDS; /**< TODO */
    unsigned int    i_DDSBDelay=16;                    //DDS; /**< TODO */
    unsigned int    i_DDSBDuty=48;                     //DDS; /**< TODO */
    unsigned int    ui_DIO=0; /**< TODO */
    double          d_DAC[12]; /**< TODO */
};
/**
 * @brief
 *
 */
struct _DAWI_Param:_LIT_PARAM{
    _DAWI_Param(){i_Name=i_DAWI;}//int       i_Name=i_DAWI; /**< TODO */
    double          d_Time=50;                         //ms  TandemParam[1].Fragment_Cooling_Time=50; ms /**< TODO */

    double          d_Mass_Start_Th=40;                //Th  Mass_Start_Th=40; /**< TODO */
    double          d_msStartOrig = 100;

    double          d_Precursor_Mass=152;              //Th  TandemParam[1].Precursor_Mass=152 /**< TODO */
    double          d_msPrecursorOrig=152;

    unsigned int    i_DDSDuration=64;                  //DDS; /**< TODO */
    unsigned int    i_DDSADelay=0;                     //DDS; /**< TODO */
    unsigned int    i_DDSADuty=0;                      //DDS; /**< TODO */
    unsigned int    i_DDSBDelay=18;                    //DDS  32-(TuneParam[1].HVHF_DutyCycle_DDS(28)>>1); /**< TODO */
    unsigned int    i_DDSBDuty=46;                     //DDS  32-(TuneParam[1].HVHF_DutyCycle_DDS(28)>>1)+TuneParam[1].HVHF_DutyCycle_DDS(28); /**< TODO */
    unsigned int    ui_DIO=0; /**< TODO */
    double          d_DAC[12]; /**< TODO */
};
/**
 * @brief
 *
 */
struct _BIsoScan_Param:_LIT_PARAM{
    _BIsoScan_Param(){i_Name=i_BIsoScan;}//int       i_Name=i_BIsoScan; /**< TODO */
    double          d_ReverseSpeed=1000.0;              //ms /**< TODO */

    double          d_Mass_Start_Th=100;                //Th  Mass_Start_Th=40; /**< TODO */
    double          d_msStartOrig = 100;

    double          d_Precursor_Mass=152;              //Th  TandemParam[1].Precursor_Mass=152 /**< TODO */
    double          d_msPrecursorOrig=152;
    double          d_Reverse_Scan_Precursor_Offset=0.4;//Th  THReverse_Scan_Precursor_Offset=0.4; /**< TODO */

    unsigned int    i_DDSDuration=192;                 //DDS  TuneParam[0].Dipole_Duration_DDS=192; /**< TODO */
    unsigned int    i_DDSADelay=5;                     //DDS  TuneParam[0].Dipole_Delay_DDS=5; /**< TODO */
    unsigned int    i_DDSADuty=53;                     //DDS  TuneParam[0].Dipole_Duty_DDS+TuneParam[0].Dipole_Delay_DDS=48+5; /**< TODO */
    unsigned int    i_DDSBDelay=16;                    //DDS  16 /**< TODO */
    unsigned int    i_DDSBDuty=48;                     //DDS  48 /**< TODO */
    unsigned int    ui_DIO=0; /**< TODO */
    double          d_DAC[12]; /**< TODO */
};
/**
 * @brief
 *
 */
struct _FIsoScan_Param:_LIT_PARAM{
    _FIsoScan_Param(){i_Name=i_FIsoScan;}//int       i_Name=i_FIsoScan; /**< TODO */
    double          d_ForwardSpeed=1000.0;             //ms  ForwardSpeed=1000.0; /**< TODO */

    double          d_Mass_Start_Th=40;                //Th  Mass_Start_Th=40; /**< TODO */
    double          d_msStartOrig = 100;

    double          d_Precursor_Mass=152;              //Th  TandemParam[1].Precursor_Mass=152 /**< TODO */
    double          d_msPrecursorOrig=152;
    double          d_Forward_Scan_Precursor_Offset=-0.2;//Th  Forward_Scan_Precursor_Offset=-0.2; /**< TODO */

    unsigned int    i_DDSDuration=192;                 //DDS  TuneParam[0].Dipole_Duration_DDS=192; /**< TODO */
    unsigned int    i_DDSADelay=5;                     //DDS  TuneParam[0].Dipole_Delay_DDS=5; /**< TODO */
    unsigned int    i_DDSADuty=53;                     //DDS  TuneParam[0].Dipole_Duty_DDS+TuneParam[0].Dipole_Delay_DDS=48+5; /**< TODO */
    unsigned int    i_DDSBDelay=16;                    //DDS  16 /**< TODO */
    unsigned int    i_DDSBDuty=48;                     //DDS  48 /**< TODO */
    unsigned int    ui_DIO=0; /**< TODO */
    double          d_DAC[12]; /**< TODO */
};
/**
 * @brief
 *
 */
struct _Scan_Param:_LIT_PARAM{
    _Scan_Param(){i_Name=i_Scan;}//int       i_Name=i_Scan; /**< TODO */
    double          d_Scan_Speed=1000.0;              //ms  Scan_Speed=10000; /**< TODO */

    double          d_Mass_Start_Th=40;                //Th  Mass_Start_Th=40; /**< TODO */
    double          d_Mass_End_Th=300;                 //Th  Mass_End_Th=300; /**< TODO */
    double          d_msStartOrig = 100;
    double          d_msEndOrig = 1000;

    double          d_Precursor_Mass=152;              //Th  TandemParam[1].Precursor_Mass=152 /**< TODO */
    double          d_msPrecursorOrig=152;
    double          d_Forward_Scan_Precursor_Offset=-0.2;//Th  Forward_Scan_Precursor_Offset=-0.2; /**< TODO */

    unsigned int    i_DDSDuration=192;                 //DDS  TuneParam[0].Dipole_Duration_DDS=192; /**< TODO */
    unsigned int    i_DDSADelay=5;                     //DDS  TuneParam[0].Dipole_Delay_DDS=5; /**< TODO */
    unsigned int    i_DDSADuty=53;                     //DDS  TuneParam[0].Dipole_Duty_DDS+TuneParam[0].Dipole_Delay_DDS=48+5; /**< TODO */
    unsigned int    i_DDSBDelay=16;                    //DDS  16 /**< TODO */
    unsigned int    i_DDSBDuty=48;                     //DDS  48 /**< TODO */
    unsigned int    ui_DIO=0; /**< TODO */
    double          d_DAC[12]; /**< TODO */

    //_MASS_SCALE_TABLE m_sMassScaleTable; /**< TODO */
    cParamValue::_Event* pEvent;//cParamValue::_Segment* p_Segment;
};
/**
 * @brief
 *
 */
struct _Empty_Param:_LIT_PARAM{
    _Empty_Param(){i_Name=i_Empty;}//int       i_Name=i_Empty; /**< TODO */
    double          d_Time=50;                         //ms  Empty_Time=50; /**< TODO */

    double          d_Mass_Start_Th=40;                //Th  Mass_Start_Th=40; /**< TODO */
    double          d_Mass_End_Th=300;                 //Th  Mass_End_Th=300; /**< TODO */
    double          d_msStartOrig = 100;
    double          d_msEndOrig = 1000;

    unsigned int    i_DDSDuration=64;                  //DDS  TuneParam[0].Dipole_Duration_DDS=64; /**< TODO */
    unsigned int    i_DDSADelay=0;                     //DDS  0; /**< TODO */
    unsigned int    i_DDSADuty=0;                      //DDS  0; /**< TODO */
    int             i_HVHF_DutyCycle_DDS=28;           //DDS  HVHF_DutyCycle_DDS=28; /**< TODO */
    unsigned int    ui_DIO=0; /**< TODO */
    double          d_DAC[12]; /**< TODO */
};
/**
 * @brief
 *
 */
struct _ScanQ_Param:_LIT_PARAM{
    _ScanQ_Param(){i_Name=i_Empty;}//int       i_Name=i_Empty; /**< TODO */
    double          d_Time=50;                         //ms  Empty_Time=50; /**< TODO */

    double          d_Mass_Start_Th=100;                //Th  Mass_Start_Th=40; /**< TODO */
    double          d_Mass_End_Th=1000;                 //Th  Mass_End_Th=300; /**< TODO */
    double          d_msStartOrig = 100;
    double          d_msEndOrig = 1000;

    unsigned int    i_DDSDuration=64;                  //DDS  TuneParam[0].Dipole_Duration_DDS=64; /**< TODO */
    unsigned int    i_DDSADelay=0;                     //DDS  0; /**< TODO */
    unsigned int    i_DDSADuty=0;                      //DDS  0; /**< TODO */
    int             i_HVHF_DutyCycle_DDS=28;           //DDS  HVHF_DutyCycle_DDS=28; /**< TODO */
    unsigned int    ui_DIO=0; /**< TODO */
    double          d_DAC[12]; /**< TODO */
};
/**
 * @brief
 *
 */
struct _Custom_Param:_LIT_PARAM{
    _Custom_Param(){i_Name=i_Custom;}//int             i_Name=i_Custom; /**< TODO */

};

/**
 * @brief
 *
 * @param d_value
 * @return unsigned long
 */
inline unsigned long DoubleToUnsignedlong(double d_value)
{
    if(d_value<0.0)
        return 0;
    else
       return ((unsigned long)d_value);
}

/**
 * @brief
 *
 * @param a
 * @param b
 * @param num_int
 */
inline void UINT2CHAR(unsigned int *a,unsigned char *b,int num_int)//128
{
    for(int i=0;i<num_int;i++){
        *(b+(i<<2))=(unsigned char)(*(a+i))&0xFF;
        *(b+(i<<2)+1)=(unsigned char)((*(a+i))>>8)&0xFF;
        *(b+(i<<2)+2)=(unsigned char)((*(a+i))>>16)&0xFF;
        *(b+(i<<2)+3)=(unsigned char)((*(a+i))>>24)&0xFF;
    }
}

