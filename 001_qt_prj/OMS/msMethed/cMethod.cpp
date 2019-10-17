#include "cmethod.h"


CMethod::CMethod()
{

}
CMethod::~CMethod()
{
    if(m_Command_Struct.p_StageName!=nullptr)
        delete [] m_Command_Struct.p_StageName;
    if(m_Command_Struct.p_STAGE_PARAMETER!=nullptr)
        delete [] m_Command_Struct.p_STAGE_PARAMETER;
}

/************************************************************************************************/
/*            Name:                                                                             */
/*                                                                                              */
/*         Explain:                                                                             */
/*           InPut:                                                                             */
/*          OutPut:                                                                             */
/*    Modification:                                                                             */
/*            Time:                                                                             */
/************************************************************************************************/
bool CMethod::InitState(_Adjust_Factor* p_Adjust_Factor,QString Q_path,int NumStage)
{
#ifdef ENVIRONMENT_QT
    QString path;
    if(Q_path.isEmpty())
        path = DEFAULT_PTM_CONFIG_FILE;
    else
        path = Q_path;

    QSettings configIniRead(path, QSettings::IniFormat);
    m_Command_Struct.mMathMethod.L_HVHFV     = configIniRead.value("/Method/L_HVHFV", 100.0).toDouble();
    m_Command_Struct.mMathMethod.H_HVHFV     = configIniRead.value("/Method/H_HVHFV", 250.0).toDouble();

    m_Command_Struct.mMathMethod.Injection_q = configIniRead.value("/Method/Injection_q", 0.6).toDouble();
    m_Command_Struct.mMathMethod.Cooling_q   = configIniRead.value("/Method/Cooling_q", 0.6).toDouble();
    m_Command_Struct.mMathMethod.DAWI_q      = configIniRead.value("/Method/DAWI_q", 0.562).toDouble();
    m_Command_Struct.mMathMethod.IsoCooling_q= configIniRead.value("/Method/IsoCooling_q", 0.25).toDouble();
    m_Command_Struct.mMathMethod.Empty_q     = configIniRead.value("/Method/Empty_q", 4.0).toDouble();

    m_Command_Struct.mMathMethod.VHVPH       = configIniRead.value("/Method/VHVPH", 250.0).toDouble();
    m_Command_Struct.mMathMethod.VHVPL       = configIniRead.value("/Method/VHVPL", 100).toDouble();
    m_Command_Struct.mMathMethod.VHVNH       = configIniRead.value("/Method/VHVNH", -250.0).toDouble();
    m_Command_Struct.mMathMethod.VHVNL       = configIniRead.value("/Method/VHVNL", -100.0).toDouble();

    m_Command_Struct.mMathMethod.SwitchM     = configIniRead.value("/Method/SwitchM", 9999999.0).toDouble();
    m_Command_Struct.mMathMethod.cdRfield    = configIniRead.value("/Method/cdRfield", 0.004).toDouble();
    m_Command_Struct.mMathMethod.cdA2        = configIniRead.value("/Method/cdA2", 0.5).toDouble();

    for(int nIndex = 0; nIndex < 32; nIndex++){
        p_Adjust_Factor->dio[nIndex] = configIniRead.value("/DIO/DIO_"+ QString::number(nIndex), 0).toUInt();
    }
#endif
    m_Command_Struct.i_StageNum                     = 0;
    if(m_Command_Struct.p_StageName!=nullptr){
        delete [] m_Command_Struct.p_StageName;
        m_Command_Struct.p_StageName=nullptr;
    }
    m_Command_Struct.p_StageName                    = new int[NumStage];
    if(m_Command_Struct.p_STAGE_PARAMETER!=nullptr){
        delete m_Command_Struct.p_STAGE_PARAMETER;
        m_Command_Struct.p_STAGE_PARAMETER=nullptr;
    }
    m_Command_Struct.p_STAGE_PARAMETER              = new MSPointerT[NumStage];

    for(int i=0;i<12;i++){
        m_Command_Struct.DF_DAC_GAIN[i]   = p_Adjust_Factor->d_DACGain[i];
        m_Command_Struct.DF_DAC_OFFSET[i] = p_Adjust_Factor->d_DACOffset[i];
    }
    m_Command_Struct.DF_MASS_SCALE=p_Adjust_Factor->d_Mass_Scale_Factor;
    m_Command_Struct.DF_MASS_OFFSET=p_Adjust_Factor->d_Mass_Offset_Factor;
    m_Command_Struct.DF_MASS_FORWARD=p_Adjust_Factor->d_Mass_Forward_Extension;
    for(int nIndex = 0; nIndex < 32; nIndex++){
        m_Command_Struct.DF_MASS_DIO[nIndex]=p_Adjust_Factor->dio[nIndex];
    }
    m_Command_Struct.isTrigger=false;
    return true;
}
/************************************************************************************************/
/*            Name:                                                                             */
/*                                                                                              */
/*         Explain:                                                                             */
/*           InPut:                                                                             */
/*          OutPut:                                                                             */
/*    Modification:                                                                             */
/*            Time:                                                                             */
/************************************************************************************************/
int CMethod::CreateMethod(unsigned char* pBufferFreqTable,int* nMSCALEn,int* MSLength,int methodNO,int ID_DataPackage)                                   //命令包编号，默认为0
{
    Stage* pStage= nullptr;                                                     //阶段指针，用来实例化阶段
    int MethodState=Succeed;                                                    //状态码，用来返回频点表声称状态

    m_Command_Struct.pBufferFreqTable=(unsigned int*)pBufferFreqTable;                         //
    m_Command_Struct.Tpassed_us=0.0;                                            //
    m_Command_Struct.nMSstage=0;                                                // 质谱阶段
    m_Command_Struct.nCurrFF=0;                                                 // 频点帧个数
    m_Command_Struct.CurrLength=128;                                     // 开始长度设为头长度

    for(int i=0;i<m_Command_Struct.i_StageNum;i++){
        switch(*(m_Command_Struct.p_StageName+i)){
        case i_Injection:   pStage = (Stage*)new Injection;     break;      //
        case i_Cooling:     pStage = (Stage*)new Cooling;       break;      //
        case i_RExcitation: pStage = (Stage*)new RExcitation;   break;      //
        case i_IsoCooling:  pStage = (Stage*)new IsoCooling;    break;      //
        case i_DAWI:        pStage = (Stage*)new DAWI;          break;      //
        case i_BIsoScan:    pStage = (Stage*)new BIsoScan;      break;      //
        case i_FIsoScan:    pStage = (Stage*)new FIsoScan;      break;      //
        case i_Scan:        pStage = (Stage*)new Scan;          break;      //
        case i_Empty:       pStage = (Stage*)new Empty;         break;      //
        case i_ScanSpecial: pStage = (Stage*)new ScanSpecial;   break;
        default:            return Error_Struct;                            //
        }
        if(pStage!=nullptr){
            if(i == m_Command_Struct.i_StageNum-1)//last
                MethodState=pStage->CreatStage((int*)*(m_Command_Struct.p_STAGE_PARAMETER+i), &m_Command_Struct, true);
            else
                MethodState=pStage->CreatStage((int*)*(m_Command_Struct.p_STAGE_PARAMETER+i), &m_Command_Struct);
            delete pStage;
            pStage=nullptr;
            if(MethodState!=Succeed)
                return MethodState;                                             // 返回错误码
        }
        else
            return Error_Struct;
    }
    createHead(m_Command_Struct,methodNO,ID_DataPackage);
    //*nMSCALEn=MScaleNo;                                                       // 返回质量校正表的数目
    *MSLength=m_Command_Struct.CurrLength*4;                                      // 返回完整频点表命令的字节长度
    *nMSCALEn=1;                                                                // 质量矫正表现在只有一个，只允许存在一个SCan阶段，否则DAQ参数无法处理
    return MethodState;
}

int CMethod::createHead(_Command_Struct& pCommand_Struct,unsigned int methodNO,unsigned int DP_ID)
{
    memset(pCommand_Struct.pBufferFreqTable,0,512);
    pCommand_Struct.pBufferFreqTable[0]=0xFFFFF065;
    pCommand_Struct.pBufferFreqTable[1]=pCommand_Struct.nCurrFF;                                         // 更新命令包序号
    pCommand_Struct.pBufferFreqTable[2]= DP_ID;                                                           // 命令包编号，默认为0
    pCommand_Struct.pBufferFreqTable[3]= methodNO;                                                        // 更新方法序号
    //unsigned int lWordLength = m_Command_Struct.CurrLength >> 2;                // 重新计算并更新命令头校验码
    unsigned int lChksum = 0;
    for (int i=0;i<m_Command_Struct.CurrLength;i++){
        if (i!=127)
            lChksum += pCommand_Struct.pBufferFreqTable[i];
    }
    pCommand_Struct.pBufferFreqTable[127] = lChksum;
}

_METHOD_STATE Stage::fillForm(_Command_Struct* pCommand_Struct,unsigned int cycle,unsigned int FreqTune,
         unsigned int DIO,unsigned int paramDDS1,unsigned int paramDDS2,double* d_DAC)
{
    if(pCommand_Struct->CurrLength> MAX_MEMORY)
        return Error_MemOver;
    unsigned int* pTxBufD = pCommand_Struct->pBufferFreqTable+pCommand_Struct->CurrLength;
    memset(pTxBufD,0,FreqDataL_32* 4);
    pTxBufD[0] = pCommand_Struct->nCurrFF;                                                          // 设置频点帧号
    pTxBufD[1] = pCommand_Struct->nMSstage;                                                         // 设置Microsweep号
    pTxBufD[2] = cycle;                                                                             // 设置CF DDS Cycle
    pTxBufD[3] = FreqTune;                                                                           // 设置FreqTune Word
    pTxBufD[5] = DIO;                                                                                // 设置DIOx
    pTxBufD[6] = paramDDS1;                                                             // 设置Dipole 上升沿 DDS设置Dipole DDS Cycle Length                                                              //
    pTxBufD[7] = paramDDS2;                                                                // 设置HVHF 下降沿 DDS设置HVHF 上升沿 DDS设置Dipole 下降沿 DDS
    for(int i=0;i<6;i++)
        pTxBufD[i+8] = (unsigned int)(((d_DAC[i*2] -pCommand_Struct->DF_DAC_OFFSET[i*2])   // 设置偶数DAC值
                /pCommand_Struct->DF_DAC_GAIN[i*2] + 10.0)/20.0 * 65535)|
                ((unsigned int)(((d_DAC[i*2+1] -pCommand_Struct->DF_DAC_OFFSET[i*2+1])    // 设置奇数DAC值
                 /pCommand_Struct->DF_DAC_GAIN[i*2+1] + 10.0)/20.0 * 65535))<<16;
    pCommand_Struct->CurrLength+= FreqDataL_32;                                                  // 计算已使用长度
    pCommand_Struct->nCurrFF++;
    return Succeed;                                                             // 当前帧号
}
/************************************************************************************************/
/*            Name:                                                                             */
/*                                                                                              */
/*         Explain:                                                                             */
/*           InPut:                                                                             */
/*          OutPut:                                                                             */
/*    Modification:                                                                             */
/*            Time:                                                                             */
/************************************************************************************************/
//int Injection::CreatStage(int* p_StageParam,_Command_Struct* pCommand_Struct, bool isSpecial)
//{
//    _Injection_Param* p_Param=(_Injection_Param*)p_StageParam;
//    double Trap_q=pCommand_Struct->mMathMethod.Injection_q,T_Trap=0.0;
//    double M0=pCommand_Struct->mMathMethod.Truemz(p_Param->d_Mass_Start_Th,pCommand_Struct->DF_MASS_SCALE,pCommand_Struct->DF_MASS_OFFSET)-
//            pCommand_Struct->DF_MASS_FORWARD;
//    unsigned int DIO=0;
//    if (M0<pCommand_Struct->mMathMethod.SwitchM){
//        T_Trap=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.L_HVHFV,M0);
//        DIO=0x00000000;
//    }else{
//        T_Trap=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.H_HVHFV,M0);
//        DIO=0x00000060;
//    };
//    DIO |= 0x00000008;
//    DIO |=p_Param->ui_DIO;
//    unsigned int ncycle=(unsigned int)((p_Param->d_Time*1000.0) /T_Trap)*64;                        // 当前帧生存周期
//    if(ncycle>0xffffffff)
//        return Holdtime_Injection_Over;
//    unsigned int FreqTune=(unsigned int)(4294967296.0 / 6.250 / T_Trap);
//    if(FreqTune>2147473648)
//        return DDS_Injection_OverQuick;
//    if(!isSpecial){
//        if(ncycle<pCommand_Struct->mMathMethod.MinCycle)
//            return Holdtime_Injection_Short;
//        if(fillForm(pCommand_Struct,ncycle,FreqTune,DIO,p_Param->i_DDSDuration|p_Param->i_DDSADelay<<16,
//                 p_Param->i_DDSADuty|p_Param->i_DDSBDelay<<16|p_Param->i_DDSBDuty<<24,p_Param->d_DAC)!=Succeed)
//            return  Error_MemOver;
//        pCommand_Struct->Tpassed_us+= (double)ncycle * T_Trap/64000.0;                                 // 计算经过时间
//    }else{// 根据现有频点帧号，将Empty的总DDS周期分散到1至多个频点帧，使总频帧数为8N
//        int restFF=(((pCommand_Struct->nCurrFF+8)>>3)<<3)-pCommand_Struct->nCurrFF;
//        ncycle = ncycle-pCommand_Struct->mMathMethod.MinCycle*(restFF-1);                                                            //除了第一个，其他全为pCommand_Struct->mMathMethod.MinCycle
//        if(ncycle<pCommand_Struct->mMathMethod.MinCycle)
//            return Holdtime_Injection_Short;
//        for (int tmpFF=0;tmpFF<restFF;tmpFF++){
//            if(fillForm(pCommand_Struct,ncycle,FreqTune,DIO,p_Param->i_DDSDuration|p_Param->i_DDSADelay<<16,
//                     p_Param->i_DDSADuty|p_Param->i_DDSBDelay<<16|p_Param->i_DDSBDuty<<24,p_Param->d_DAC)!=Succeed)
//            return  Error_MemOver;
//            pCommand_Struct->Tpassed_us+= ((double)ncycle) * T_Trap/64000.0;                                 // 计算经过时间
//            ncycle= pCommand_Struct->mMathMethod.MinCycle;
//        }
//    }
//    pCommand_Struct->nMSstage++;                                           // 当前Micro sweep号
//    return Succeed;
//}


int Injection::CreatStage(int* p_StageParam,_Command_Struct* pCommand_Struct, bool isSpecial)
{
    _Injection_Param* p_Param=(_Injection_Param*)p_StageParam;
    double Trap_q=pCommand_Struct->mMathMethod.Injection_q,T_Trap=0.0;
    double M0=pCommand_Struct->mMathMethod.Truemz(p_Param->d_Mass_Start_Th,pCommand_Struct->DF_MASS_SCALE,pCommand_Struct->DF_MASS_OFFSET)-
            pCommand_Struct->DF_MASS_FORWARD;
    unsigned int DIO=0;
    if (M0<pCommand_Struct->mMathMethod.SwitchM){
        T_Trap=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.L_HVHFV,M0);
        DIO=0x00000000;
    }else{
        T_Trap=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.H_HVHFV,M0);
        DIO=0x00000060;
    };
    DIO |= 0x00000008;
    DIO |=p_Param->ui_DIO;
    unsigned int ncycle=(unsigned int)((p_Param->d_Time*1000.0) /T_Trap)*64;                        // 当前帧生存周期
    if(ncycle>0xffffffff)
        return Holdtime_Injection_Over;
    double start_AC = p_Param->d_Mass_Start_Th*p_Param->d_Qarray_RF_FactorA + p_Param->d_Qarray_RF_FactorB;
    double end_AC = p_Param->d_Mass_End_Th*p_Param->d_Qarray_RF_FactorA + p_Param->d_Qarray_RF_FactorB;
    unsigned int number_step = (end_AC - start_AC)/p_Param->d_Qarray_RF_Step + 1;
    unsigned int min_ncycle_step = ncycle / number_step + 1;
    unsigned int FreqTune=(unsigned int)(4294967296.0 / 6.250 / T_Trap);
    if(FreqTune>2147473648)
        return DDS_Injection_OverQuick;
    if(!isSpecial){
        if(p_Param->d_DAC[3] != 0){
            //d_DAC[3]如果不为0，则Q-array幅值固定值扫描
            if(ncycle<pCommand_Struct->mMathMethod.MinCycle)
                return Holdtime_Injection_Short;
            if(fillForm(pCommand_Struct,ncycle,FreqTune,DIO,p_Param->i_DDSDuration|p_Param->i_DDSADelay<<16,
                        p_Param->i_DDSADuty|p_Param->i_DDSBDelay<<16|p_Param->i_DDSBDuty<<24,p_Param->d_DAC)!=Succeed)
                return  Error_MemOver;
        }else{
            //Q-array 幅值扫描，曲线方程：0.167*MASS + 33.33    步长为10
            for(p_Param->d_DAC[3] = start_AC;p_Param->d_DAC[3] <= end_AC;p_Param->d_DAC[3]+=p_Param->d_Qarray_RF_Step){
                if(min_ncycle_step<pCommand_Struct->mMathMethod.MinCycle)
                    return Holdtime_Injection_Short;
                if(fillForm(pCommand_Struct,min_ncycle_step,FreqTune,DIO,p_Param->i_DDSDuration|p_Param->i_DDSADelay<<16,
                            p_Param->i_DDSADuty|p_Param->i_DDSBDelay<<16|p_Param->i_DDSBDuty<<24,p_Param->d_DAC)!=Succeed)
                    return  Error_MemOver;
            }
        }
        pCommand_Struct->Tpassed_us+= (double)ncycle * T_Trap/64000.0;                                 // 计算经过时间
    }else{// 根据现有频点帧号，将Empty的总DDS周期分散到1至多个频点帧，使总频帧数为8N
        int restFF=(((pCommand_Struct->nCurrFF+8)>>3)<<3)-pCommand_Struct->nCurrFF;
        ncycle = ncycle-pCommand_Struct->mMathMethod.MinCycle*(restFF-1);                                                            //除了第一个，其他全为pCommand_Struct->mMathMethod.MinCycle
        if(ncycle<pCommand_Struct->mMathMethod.MinCycle)
            return Holdtime_Injection_Short;
        for (int tmpFF=0;tmpFF<restFF;tmpFF++){
            if(fillForm(pCommand_Struct,ncycle,FreqTune,DIO,p_Param->i_DDSDuration|p_Param->i_DDSADelay<<16,
                     p_Param->i_DDSADuty|p_Param->i_DDSBDelay<<16|p_Param->i_DDSBDuty<<24,p_Param->d_DAC)!=Succeed)
            return  Error_MemOver;
            pCommand_Struct->Tpassed_us+= ((double)ncycle) * T_Trap/64000.0;                                 // 计算经过时间
            ncycle= pCommand_Struct->mMathMethod.MinCycle;
        }
    }
    pCommand_Struct->nMSstage++;                                           // 当前Micro sweep号
    return Succeed;
}
/************************************************************************************************/
/*            Name:                                                                             */
/*                                                                                              */
/*         Explain:                                                                             */
/*           InPut:                                                                             */
/*          OutPut:                                                                             */
/*    Modification:                                                                             */
/*            Time:                                                                             */
/************************************************************************************************/
int Cooling::CreatStage(int* p_StageParam,_Command_Struct* pCommand_Struct, bool isSpecial)
{
    _Cooling_Param* p_Param=(_Cooling_Param*)p_StageParam;                  // 类型转换
    double Trap_q=pCommand_Struct->mMathMethod.Cooling_q,T_Trap=0.0;
    double M0=pCommand_Struct->mMathMethod.Truemz(p_Param->d_Mass_Start_Th,pCommand_Struct->DF_MASS_SCALE,pCommand_Struct->DF_MASS_OFFSET)
            -pCommand_Struct->DF_MASS_FORWARD;
    unsigned int DIO;
    if (M0<pCommand_Struct->mMathMethod.SwitchM){
        T_Trap=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.L_HVHFV,M0);
        DIO=0x00000000;
    }else{
        T_Trap=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.H_HVHFV,M0);
        DIO=0x00000060;                                                     // 需重新设定
    };
    DIO |=p_Param->ui_DIO;
    unsigned int FreqTune=(unsigned int)(4294967296.0 / 6.250 / T_Trap);
    if(FreqTune>2147473648)
        return DDS_Cooling_OverQuick;
    unsigned int ncycle=(unsigned int)((p_Param->d_Time*1000.0) /T_Trap)*64;                    // 当前帧生存周期
    if(ncycle>0xffffffff)
        return Holdtime_Cooling_Over;
    if(!isSpecial){
        if(ncycle<pCommand_Struct->mMathMethod.MinCycle)
            return Holdtime_Cooling_Short;
        if(fillForm(pCommand_Struct,ncycle,FreqTune,DIO,p_Param->i_DDSDuration|p_Param->i_DDSADelay<<16,
                 p_Param->i_DDSADuty|p_Param->i_DDSBDelay<<16|p_Param->i_DDSBDuty<<24,p_Param->d_DAC)!=Succeed)
            return  Error_MemOver;
        pCommand_Struct->Tpassed_us+= (double)ncycle * T_Trap/64000.0;                 // 计算经过时间
    }else{// 根据现有频点帧号，将Empty的总DDS周期分散到1至多个频点帧，使总频帧数为8N
        int restFF=(((pCommand_Struct->nCurrFF+8)>>3)<<3)-pCommand_Struct->nCurrFF;
        ncycle = ncycle-pCommand_Struct->mMathMethod.MinCycle*(restFF-1);                                                            //除了第一个，其他全为pCommand_Struct->mMathMethod.MinCycle
        if(ncycle<pCommand_Struct->mMathMethod.MinCycle)
            return Holdtime_Cooling_Short;
        for (int tmpFF=0;tmpFF<restFF;tmpFF++){
            if(fillForm(pCommand_Struct,ncycle,FreqTune,DIO,p_Param->i_DDSDuration|p_Param->i_DDSADelay<<16,
                     p_Param->i_DDSADuty|p_Param->i_DDSBDelay<<16|p_Param->i_DDSBDuty<<24,p_Param->d_DAC)!=Succeed)
                return  Error_MemOver;
            pCommand_Struct->Tpassed_us+= ((double)ncycle) * T_Trap/64000.0;                                 // 计算经过时间
            ncycle= pCommand_Struct->mMathMethod.MinCycle;
        }
    }
    pCommand_Struct->nMSstage++;                                           // 当前Micro sweep号
    return Succeed;
}
/************************************************************************************************/
/*            Name:                                                                             */
/*                                                                                              */
/*         Explain:                                                                             */
/*           InPut:                                                                             */
/*          OutPut:                                                                             */
/*    Modification:                                                                             */
/*            Time:                                                                             */
/************************************************************************************************/
int RExcitation::CreatStage(int* p_StageParam,_Command_Struct* pCommand_Struct, bool isSpecial)
{
    _RExcitation_Param* p_Param=(_RExcitation_Param*)p_StageParam;          //类型转换
    double Trap_q=pCommand_Struct->mMathMethod.ddstoq(p_Param->i_DDSDuration),T_Trap=0.0;
    Trap_q=Trap_q*p_Param->d_Excitation_Frequency_Offset;//LitCoeffParam.Excitation_Frequency_Offset;
    double M0=pCommand_Struct->mMathMethod.Truemz(p_Param->d_Precursor_Mass,pCommand_Struct->DF_MASS_SCALE,pCommand_Struct->DF_MASS_OFFSET);//TandemParam[0].Precursor_Mass
    double M00=pCommand_Struct->mMathMethod.Truemz(p_Param->d_Mass_Start_Th,pCommand_Struct->DF_MASS_SCALE,pCommand_Struct->DF_MASS_OFFSET)
            -pCommand_Struct->DF_MASS_FORWARD;
    unsigned int DIO;
    if (M00<pCommand_Struct->mMathMethod.SwitchM){
        T_Trap=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.L_HVHFV,M0);
        DIO=0x00000000;
    }else{
        T_Trap=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.H_HVHFV,M0);
        DIO=0x00000060;
    };
    DIO |=p_Param->ui_DIO;
    unsigned int FreqTune=(unsigned int)(4294967296.0 / 6.250 / T_Trap);
    if(FreqTune>2147473648)
        return DDS_RExcitation_OverQuick;
    unsigned int ncycle=(unsigned int)((p_Param->d_Time*1000.0) /T_Trap)*64;                    // 当前帧生存周期TandemParam[0].Fragmentation_Time
    if(ncycle>0xffffffff)
        return Holdtime_RExcitation_Over;
    if(!isSpecial){
        if(ncycle<pCommand_Struct->mMathMethod.MinCycle)
            return Holdtime_RExcitation_Short;
        if(fillForm(pCommand_Struct,ncycle,FreqTune,DIO,p_Param->i_DDSDuration|p_Param->i_DDSADelay<<16,
                 p_Param->i_DDSADuty|p_Param->i_DDSBDelay<<16|p_Param->i_DDSBDuty<<24,p_Param->d_DAC)!=Succeed)
            return  Error_MemOver;
        pCommand_Struct->Tpassed_us+= (double)ncycle * T_Trap/64000.0;                 // 计算经过时间
    }else{// 根据现有频点帧号，将Empty的总DDS周期分散到1至多个频点帧，使总频帧数为8N
        int restFF=(((pCommand_Struct->nCurrFF+8)>>3)<<3)-pCommand_Struct->nCurrFF;
        ncycle = ncycle-pCommand_Struct->mMathMethod.MinCycle*(restFF-1);                                                            //除了第一个，其他全为pCommand_Struct->mMathMethod.MinCycle
        if(ncycle<pCommand_Struct->mMathMethod.MinCycle)
            return Holdtime_RExcitation_Short;
        for (int tmpFF=0;tmpFF<restFF;tmpFF++){
            if(fillForm(pCommand_Struct,ncycle,FreqTune,DIO,p_Param->i_DDSDuration|p_Param->i_DDSADelay<<16,
                     p_Param->i_DDSADuty|p_Param->i_DDSBDelay<<16|p_Param->i_DDSBDuty<<24,p_Param->d_DAC)!=Succeed)
                return  Error_MemOver;
            pCommand_Struct->Tpassed_us+= ((double)ncycle) * T_Trap/64000.0;                                 // 计算经过时间
            ncycle= pCommand_Struct->mMathMethod.MinCycle;
        }
    }
    pCommand_Struct->nMSstage++;                                           // 当前Micro sweep号
    return Succeed;
}
/************************************************************************************************/
/*            Name:                                                                             */
/*                                                                                              */
/*         Explain:                                                                             */
/*           InPut:                                                                             */
/*          OutPut:                                                                             */
/*    Modification:                                                                             */
/*            Time:                                                                             */
/************************************************************************************************/
int IsoCooling::CreatStage(int* p_StageParam,_Command_Struct* pCommand_Struct, bool isSpecial)
{
    _IsoCooling_Param* p_Param=(_IsoCooling_Param*)p_StageParam;            //类型转换
    double Trap_q=pCommand_Struct->mMathMethod.IsoCooling_q,T_Trap=0.0;
    double M0=pCommand_Struct->mMathMethod.Truemz(p_Param->d_Precursor_Mass,pCommand_Struct->DF_MASS_SCALE,pCommand_Struct->DF_MASS_OFFSET);//TandemParam[0].Precursor_Mass
    double M00=pCommand_Struct->mMathMethod.Truemz(p_Param->d_Mass_Start_Th,pCommand_Struct->DF_MASS_SCALE,pCommand_Struct->DF_MASS_OFFSET)-
           pCommand_Struct->DF_MASS_FORWARD;//Mass_Forward_Extension;
    unsigned int DIO;
    if (M00<pCommand_Struct->mMathMethod.SwitchM){
        T_Trap=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.L_HVHFV,M0);
        DIO=0x00000000;
    }else{
        T_Trap=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.H_HVHFV,M0);
        DIO=0x00000060;
    };
    DIO |=p_Param->ui_DIO;
    unsigned int FreqTune=(unsigned int)(4294967296.0 / 6.250 / T_Trap);
    if(FreqTune>2147473648)
        return DDS_IsoCooling_OverQuick;
    unsigned int ncycle=(unsigned int)((p_Param->d_Time*1000.0) /T_Trap)*64;                    // 当前帧生存周期TandemParam[0].Fragmentation_Time
    if(ncycle>0xffffffff)
        return Holdtime_IsoCooling_Over;
    if(!isSpecial){
        if(ncycle<pCommand_Struct->mMathMethod.MinCycle)
            return Holdtime_IsoCooling_Short;
        if(fillForm(pCommand_Struct,ncycle,FreqTune,DIO,p_Param->i_DDSDuration|p_Param->i_DDSADelay<<16,
                 p_Param->i_DDSADuty|p_Param->i_DDSBDelay<<16|p_Param->i_DDSBDuty<<24,p_Param->d_DAC)!=Succeed)
            return  Error_MemOver;
        pCommand_Struct->Tpassed_us+= ((double)ncycle) * T_Trap/64000.0;                 // 计算经过时间
    }else{// 根据现有频点帧号，将Empty的总DDS周期分散到1至多个频点帧，使总频帧数为8N
        int restFF=(((pCommand_Struct->nCurrFF+8)>>3)<<3)-pCommand_Struct->nCurrFF;
        ncycle = ncycle-pCommand_Struct->mMathMethod.MinCycle*(restFF-1);                                                            //除了第一个，其他全为pCommand_Struct->mMathMethod.MinCycle
        if(ncycle<pCommand_Struct->mMathMethod.MinCycle)
            return Holdtime_IsoCooling_Short;
        for (int tmpFF=0;tmpFF<restFF;tmpFF++){
            if(fillForm(pCommand_Struct,ncycle,FreqTune,DIO,p_Param->i_DDSDuration|p_Param->i_DDSADelay<<16,
                     p_Param->i_DDSADuty|p_Param->i_DDSBDelay<<16|p_Param->i_DDSBDuty<<24,p_Param->d_DAC)!=Succeed)
                return  Error_MemOver;
            pCommand_Struct->Tpassed_us+= ((double)ncycle) * T_Trap/64000.0;                                 // 计算经过时间
            ncycle= pCommand_Struct->mMathMethod.MinCycle;
        }
    }
    pCommand_Struct->nMSstage++;                                           // 当前Micro sweep号
    return Succeed;
}
/************************************************************************************************/
/*            Name:                                                                             */
/*                                                                                              */
/*         Explain:                                                                             */
/*           InPut:                                                                             */
/*          OutPut:                                                                             */
/*    Modification:                                                                             */
/*            Time:                                                                             */
/************************************************************************************************/
int DAWI::CreatStage(int* p_StageParam,_Command_Struct* pCommand_Struct, bool isSpecial)
{
    _DAWI_Param* p_Param=(_DAWI_Param*)p_StageParam;                  //类型转换
    double Trap_q=pCommand_Struct->mMathMethod.DAWI_q,T_Trap=0.0;
    double M0=pCommand_Struct->mMathMethod.Truemz(p_Param->d_Precursor_Mass,pCommand_Struct->DF_MASS_SCALE,pCommand_Struct->DF_MASS_OFFSET);
    double M00=pCommand_Struct->mMathMethod.Truemz(p_Param->d_Mass_Start_Th,pCommand_Struct->DF_MASS_SCALE,pCommand_Struct->DF_MASS_OFFSET)-
            pCommand_Struct->DF_MASS_FORWARD;
    unsigned int DIO;
    if (M00<pCommand_Struct->mMathMethod.SwitchM){
        T_Trap=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.L_HVHFV,M0);
        DIO=0x00000000;
    }else{
        T_Trap=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.H_HVHFV,M0);
        DIO=0x00000060;                                                     // 需重新设定
    };
    DIO |=p_Param->ui_DIO;
    unsigned int FreqTune=(unsigned int)(4294967296.0 / 6.250 / T_Trap);
    if(FreqTune>2147473648)
        return DDS_DAWI_OverQuick;
    unsigned int ncycle=(unsigned int)((p_Param->d_Time*1000.0) /T_Trap)*64;                    // 当前帧生存周期
    if(ncycle>0xffffffff)
        return Holdtime_DAWI_Over;
    if(!isSpecial){
        if(ncycle<pCommand_Struct->mMathMethod.MinCycle)
            return Holdtime_DAWI_Short;
        if(fillForm(pCommand_Struct,ncycle,FreqTune,DIO,p_Param->i_DDSDuration|p_Param->i_DDSADelay<<16,
                 p_Param->i_DDSADuty|p_Param->i_DDSBDelay<<16|p_Param->i_DDSBDuty<<24,p_Param->d_DAC)!=Succeed)
            return  Error_MemOver;
        pCommand_Struct->Tpassed_us+= ((double)ncycle) * T_Trap/64000.0;                 // 计算经过时间
    }else{// 根据现有频点帧号，将Empty的总DDS周期分散到1至多个频点帧，使总频帧数为8N
        int restFF=(((pCommand_Struct->nCurrFF+8)>>3)<<3)-pCommand_Struct->nCurrFF;
        ncycle = ncycle-pCommand_Struct->mMathMethod.MinCycle*(restFF-1);                                                            //除了第一个，其他全为pCommand_Struct->mMathMethod.MinCycle
        if(ncycle<pCommand_Struct->mMathMethod.MinCycle)
            return Holdtime_DAWI_Short;
        for (int tmpFF=0;tmpFF<restFF;tmpFF++){
            if(fillForm(pCommand_Struct,ncycle,FreqTune,DIO,p_Param->i_DDSDuration|p_Param->i_DDSADelay<<16,
                     p_Param->i_DDSADuty|p_Param->i_DDSBDelay<<16|p_Param->i_DDSBDuty<<24,p_Param->d_DAC)!=Succeed)
                    return  Error_MemOver;
            pCommand_Struct->Tpassed_us+= ((double)ncycle) * T_Trap/64000.0;                                 // 计算经过时间
            ncycle= pCommand_Struct->mMathMethod.MinCycle;
        }
    }
    pCommand_Struct->nMSstage++;                                           // 当前Micro sweep号
    return Succeed;
}
/************************************************************************************************/
/*            Name:                                                                             */
/*                                                                                              */
/*         Explain:                                                                             */
/*           InPut:                                                                             */
/*          OutPut:                                                                             */
/*    Modification:                                                                             */
/*            Time:                                                                             */
/************************************************************************************************/
int BIsoScan::CreatStage(int* p_StageParam,_Command_Struct* pCommand_Struct, bool isSpecial)
{
    _BIsoScan_Param* p_Param=(_BIsoScan_Param*)p_StageParam;                  //类型转换
    double Trap_q=pCommand_Struct->mMathMethod.ddstoq(p_Param->i_DDSDuration),T_Trap0=0.0,T_Trap1=0,Tstep=0;
    double M0=pCommand_Struct->mMathMethod.Truemz(p_Param->d_Precursor_Mass*1.1,pCommand_Struct->DF_MASS_SCALE,pCommand_Struct->DF_MASS_OFFSET)+
                     p_Param->d_Reverse_Scan_Precursor_Offset;
    double M1=pCommand_Struct->mMathMethod.Truemz(p_Param->d_Precursor_Mass,pCommand_Struct->DF_MASS_SCALE,pCommand_Struct->DF_MASS_OFFSET)+
                     p_Param->d_Reverse_Scan_Precursor_Offset;
    double M00=pCommand_Struct->mMathMethod.Truemz(p_Param->d_Mass_Start_Th,pCommand_Struct->DF_MASS_SCALE,pCommand_Struct->DF_MASS_OFFSET)-
                      pCommand_Struct->DF_MASS_FORWARD;
    unsigned int ncycle=24,FreqTune=0,DIO=0;
    if (M00<pCommand_Struct->mMathMethod.SwitchM) {
        T_Trap0=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.L_HVHFV,M0);
        T_Trap1=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.L_HVHFV,M1);
        Tstep=-pCommand_Struct->mMathMethod.calc_Tstep_ps(p_Param->d_ReverseSpeed*pCommand_Struct->DF_MASS_SCALE,Trap_q,pCommand_Struct->mMathMethod.cdA2,ncycle,pCommand_Struct->mMathMethod.L_HVHFV)*1E-6;
        DIO=0x00000000;
    }else{
        T_Trap0=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.H_HVHFV,M0);
        T_Trap1=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.H_HVHFV,M1);
        Tstep=-pCommand_Struct->mMathMethod.calc_Tstep_ps(p_Param->d_ReverseSpeed*pCommand_Struct->DF_MASS_SCALE,Trap_q,pCommand_Struct->mMathMethod.cdA2,ncycle,pCommand_Struct->mMathMethod.H_HVHFV)*1E-6;
        DIO=0x00000060;
    };
    DIO |=p_Param->ui_DIO;
    ncycle=ncycle*64;                                                        // 当前帧生存周期
    //double dTriggerWidth=0.0;
    double T_Trap=((Tstep<0)?T_Trap0:T_Trap1);
    for(;((Tstep<0)?(T_Trap>T_Trap1):(T_Trap<T_Trap0));T_Trap+=Tstep){
        FreqTune=(unsigned int)(4294967296.0 / 6.250 / T_Trap);
        if(FreqTune>2147473648)
            return DDS_BIsoScan_OverQuick;
        if(fillForm(pCommand_Struct,ncycle,FreqTune,DIO,p_Param->i_DDSDuration|p_Param->i_DDSADelay<<16,
                 p_Param->i_DDSADuty|p_Param->i_DDSBDelay<<16|p_Param->i_DDSBDuty<<24,p_Param->d_DAC)!=Succeed)
            return  Error_MemOver;
        pCommand_Struct->Tpassed_us+= ((double)ncycle) * T_Trap/64000.0;                 // 计算经过时间
    }
    if(isSpecial){
        int restFF=(((pCommand_Struct->nCurrFF+8)>>3)<<3)-pCommand_Struct->nCurrFF;
        for(int i=0;i<restFF;i++,T_Trap+=Tstep){
            FreqTune=(unsigned int)(4294967296.0 / 6.250 / T_Trap);
            if(FreqTune>2147473648)
                return DDS_Scan_OverQuick;
            if(fillForm(pCommand_Struct,ncycle,FreqTune,DIO,p_Param->i_DDSDuration|p_Param->i_DDSADelay<<16,
                     p_Param->i_DDSADuty|p_Param->i_DDSBDelay<<16|p_Param->i_DDSBDuty<<24,p_Param->d_DAC)!=Succeed)
                return  Error_MemOver;
            //dTriggerWidth+=((double)ncycle) * T_Trap/64000.0;                                 // 计算经过时间
            //if (dTriggerWidth>=0.1) {DIO=DION;}; //强制控制trigger为100us //怀疑Trigger脉宽不够，可注释掉使trigger on扩展到整个扫描阶段
            pCommand_Struct->Tpassed_us+= ((double)ncycle) * T_Trap/64000.0;                 // 计算经过时间
        }
    }
    pCommand_Struct->nMSstage++;                                           // 当前Micro sweep号
    return Succeed;
}
/************************************************************************************************/
/*            Name:                                                                             */
/*                                                                                              */
/*         Explain:                                                                             */
/*           InPut:                                                                             */
/*          OutPut:                                                                             */
/*    Modification:                                                                             */
/*            Time:                                                                             */
/************************************************************************************************/
int FIsoScan::CreatStage(int* p_StageParam,_Command_Struct* pCommand_Struct, bool isSpecial)
{
    _FIsoScan_Param* p_Param=(_FIsoScan_Param*)p_StageParam;                  //类型转换
    double Trap_q=pCommand_Struct->mMathMethod.ddstoq(p_Param->i_DDSDuration),T_Trap0=0.0,T_Trap1=0.0,Tstep=0.0;
    double M0=pCommand_Struct->mMathMethod.Truemz(p_Param->d_Precursor_Mass*0.8,pCommand_Struct->DF_MASS_SCALE,pCommand_Struct->DF_MASS_OFFSET)+
                     p_Param->d_Forward_Scan_Precursor_Offset;
    double M1=pCommand_Struct->mMathMethod.Truemz(p_Param->d_Precursor_Mass,pCommand_Struct->DF_MASS_SCALE,pCommand_Struct->DF_MASS_OFFSET)+
                     p_Param->d_Forward_Scan_Precursor_Offset;
    unsigned int ncycle=24,DIO=0,FreqTune=0;
    if (M0<pCommand_Struct->mMathMethod.SwitchM){
        T_Trap0=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.L_HVHFV,M0);
        T_Trap1=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.L_HVHFV,M1);
        Tstep=pCommand_Struct->mMathMethod.calc_Tstep_ps(p_Param->d_ForwardSpeed*pCommand_Struct->DF_MASS_SCALE,Trap_q,pCommand_Struct->mMathMethod.cdA2,ncycle,pCommand_Struct->mMathMethod.L_HVHFV)*1E-6;
        DIO=0x00000000;
    }else{
        T_Trap0=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.H_HVHFV,M0);
        T_Trap1=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.H_HVHFV,M1);
        Tstep=pCommand_Struct->mMathMethod.calc_Tstep_ps(p_Param->d_ForwardSpeed*pCommand_Struct->DF_MASS_SCALE,Trap_q,pCommand_Struct->mMathMethod.cdA2,ncycle,pCommand_Struct->mMathMethod.H_HVHFV)*1E-6;
        DIO=0x00000060;
    };
    DIO |=p_Param->ui_DIO;
    //double dTriggerWidth=0.0;
    ncycle=ncycle*64;                                                        // 当前帧生存周期
    double T_Trap=T_Trap0;
    for(;T_Trap<T_Trap1;T_Trap+=Tstep){
        FreqTune=(unsigned int)(4294967296.0 / 6.250 / T_Trap);
        if(FreqTune>2147473648)
            return DDS_FIsoScan_OverQuick;
        if(fillForm(pCommand_Struct,ncycle,FreqTune,DIO,p_Param->i_DDSDuration|p_Param->i_DDSADelay<<16,
                 p_Param->i_DDSADuty|p_Param->i_DDSBDelay<<16|p_Param->i_DDSBDuty<<24,p_Param->d_DAC)!=Succeed)
            return  Error_MemOver;
        pCommand_Struct->Tpassed_us+= ((double)ncycle) * T_Trap/64000.0;                 // 计算经过时间
    }
    if(isSpecial){
        int restFF=(((pCommand_Struct->nCurrFF+8)>>3)<<3)-pCommand_Struct->nCurrFF;
        for(int i=0;i<restFF;i++,T_Trap+=Tstep){
            FreqTune=(unsigned int)(4294967296.0 / 6.250 / T_Trap);
            if(FreqTune>2147473648)
                return DDS_Scan_OverQuick;
            if(fillForm(pCommand_Struct,ncycle,FreqTune,DIO,p_Param->i_DDSDuration|p_Param->i_DDSADelay<<16,
                     p_Param->i_DDSADuty|p_Param->i_DDSBDelay<<16|p_Param->i_DDSBDuty<<24,p_Param->d_DAC)!=Succeed)
                    return  Error_MemOver;
            //dTriggerWidth+=((double)ncycle) * T_Trap/64000.0;                                 // 计算经过时间
            //if (dTriggerWidth>=0.1) {DIO=DION;}; //强制控制trigger为100us //怀疑Trigger脉宽不够，可注释掉使trigger on扩展到整个扫描阶段
            pCommand_Struct->Tpassed_us+= ((double)ncycle) * T_Trap/64000.0;                 // 计算经过时间
        }
    }
    pCommand_Struct->nMSstage++;
    return Succeed;
}
/************************************************************************************************/
/*            Name:                                                                             */
/*                                                                                              */
/*         Explain:                                                                             */
/*           InPut:                                                                             */
/*          OutPut:                                                                             */
/*    Modification:                                                                             */
/*            Time:                                                                             */
/************************************************************************************************/
int Scan::CreatStage(int* p_StageParam,_Command_Struct* pCommand_Struct, bool isSpecial)
{
    _Scan_Param* p_Param=(_Scan_Param*)p_StageParam;                  //类型转换
    double Trap_q=pCommand_Struct->mMathMethod.ddstoq(p_Param->i_DDSDuration);
    double M0=pCommand_Struct->mMathMethod.Truemz(p_Param->d_Mass_Start_Th,pCommand_Struct->DF_MASS_SCALE,pCommand_Struct->DF_MASS_OFFSET)-
                     pCommand_Struct->DF_MASS_FORWARD;//d_Mass_Start_Th=40,DF_MASS_FORWARD=2,M0=38
    double M1=pCommand_Struct->mMathMethod.Truemz(p_Param->d_Mass_End_Th,pCommand_Struct->DF_MASS_SCALE,pCommand_Struct->DF_MASS_OFFSET)+
                     pCommand_Struct->DF_MASS_FORWARD;//d_Mass_End_Th=100,M1=102
    double M00=pCommand_Struct->mMathMethod.Truemz(p_Param->d_Mass_Start_Th,pCommand_Struct->DF_MASS_SCALE,pCommand_Struct->DF_MASS_OFFSET);//M00=40
    double M10=pCommand_Struct->mMathMethod.Truemz(p_Param->d_Mass_End_Th,pCommand_Struct->DF_MASS_SCALE,pCommand_Struct->DF_MASS_OFFSET);//M10=100
    double T_Trap0=0,T_Trap1=0;
    unsigned int ncycle=24,FreqTune=0,DIO=0,DION=0;
    double Tstep=0.0,dTriggerWidth=0.0;
    if (M0<pCommand_Struct->mMathMethod.SwitchM){
        T_Trap0=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.L_HVHFV,M0);
        T_Trap1=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.L_HVHFV,M1);
        Tstep=(p_Param->d_Scan_Speed>0)?
              (pCommand_Struct->mMathMethod.calc_Tstep_ps(p_Param->d_Scan_Speed*pCommand_Struct->DF_MASS_SCALE,Trap_q,pCommand_Struct->mMathMethod.cdA2,ncycle,pCommand_Struct->mMathMethod.L_HVHFV)*1E-6):
              (-pCommand_Struct->mMathMethod.calc_Tstep_ps(-p_Param->d_Scan_Speed*pCommand_Struct->DF_MASS_SCALE,Trap_q,pCommand_Struct->mMathMethod.cdA2,ncycle,pCommand_Struct->mMathMethod.L_HVHFV)*1E-6);
        DION=0x00ff0000;
    }else{
        T_Trap0=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.H_HVHFV,M0);
        T_Trap1=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.H_HVHFV,M1);
        Tstep=(p_Param->d_Scan_Speed>0)?
              (pCommand_Struct->mMathMethod.calc_Tstep_ps(p_Param->d_Scan_Speed*pCommand_Struct->DF_MASS_SCALE,Trap_q,pCommand_Struct->mMathMethod.cdA2,ncycle,pCommand_Struct->mMathMethod.H_HVHFV)*1E-6):
              (-pCommand_Struct->mMathMethod.calc_Tstep_ps(-p_Param->d_Scan_Speed*pCommand_Struct->DF_MASS_SCALE,Trap_q,pCommand_Struct->mMathMethod.cdA2,ncycle,pCommand_Struct->mMathMethod.H_HVHFV)*1E-6);
        DION=0x00ff0060;
    };
#if 0
    double tM0=pCommand_Struct->Tpassed_us+(M00-M0)/p_Param->d_Scan_Speed*//40-38
        pCommand_Struct->DF_MASS_SCALE*1e6*((p_Param->d_Scan_Speed>0)?1.0:-1.0);
    double tM1=pCommand_Struct->Tpassed_us+(M10-M0)/p_Param->d_Scan_Speed*//100-38
            pCommand_Struct->DF_MASS_SCALE*1e6*((p_Param->d_Scan_Speed>0)?1.0:-1.0);
    if(p_Param->d_Scan_Speed>0){
        p_Param->m_sMassScaleTable.StartMass=(double)(p_Param->d_Mass_Start_Th);
        p_Param->m_sMassScaleTable.StopMass =(double)(p_Param->d_Mass_End_Th);
    }else{
        p_Param->m_sMassScaleTable.StartMass=(double)(p_Param->d_Mass_End_Th);
        p_Param->m_sMassScaleTable.StopMass =(double)(p_Param->d_Mass_Start_Th);
    }
    p_Param->m_sMassScaleTable.StartDAQpoint=(long)((tM0-(pCommand_Struct->Tpassed_us))*pCommand_Struct->m_Adjust_Factor.DAQFREQP);
    p_Param->m_sMassScaleTable.EndDAQpoint=(long)((tM1-(pCommand_Struct->Tpassed_us))*pCommand_Struct->m_Adjust_Factor.DAQFREQP);
#endif

//    p_Param->p_Segment->postReadyTime= p_Param->p_Segment->preReadyTime= (M00-M0)/p_Param->d_Scan_Speed*//40-38
//            pCommand_Struct->DF_MASS_SCALE*((p_Param->d_Scan_Speed>0)?1.0:-1.0);
    cParamValue::_EventLIT* p_EventLIT= (cParamValue::_EventLIT*)p_Param->pEvent;
    //cParamValue::_EventLIT* p_EventLIT= (cParamValue::_EventLIT*)&(p_Param->p_Segment->fisrtEvent);
    p_EventLIT->postReadyTime= p_EventLIT->preReadyTime= (M00-M0)/p_Param->d_Scan_Speed*//40-38
        pCommand_Struct->DF_MASS_SCALE*((p_Param->d_Scan_Speed>0)?1.0:-1.0);
    p_EventLIT->holdTime= (M1- M0)/p_Param->d_Scan_Speed*//102-38
            pCommand_Struct->DF_MASS_SCALE*((p_Param->d_Scan_Speed>0)?1.0:-1.0);
    p_EventLIT->msStart= p_Param->d_Mass_Start_Th;
    p_EventLIT->msEnd= p_Param->d_Mass_End_Th;
    p_EventLIT->msStartOrig = p_Param->d_msStartOrig;
    p_EventLIT->msEndOrig = p_Param->d_msEndOrig;
    p_EventLIT->msPrecursor= pCommand_Struct->DF_MASS_FORWARD;

    ncycle = pCommand_Struct->mMathMethod.MinCycle;                                                        // 当前帧生存周期
    //if(_Command_Struct.isTrigger){
        DIO=DION;
    //}else{
    //    DIO=DION|0x00000001;
    //}
    DIO |=p_Param->ui_DIO;
    double T_Trap=((Tstep>0)?(T_Trap0):(T_Trap1));
    for(;((Tstep>0)?(T_Trap<T_Trap1):(T_Trap>T_Trap0));T_Trap+=Tstep){
        FreqTune=(unsigned int)(4294967296.0 / 6.250 / T_Trap);
        if(FreqTune>2147473648)
            return DDS_Scan_OverQuick;
        if(pCommand_Struct->isTrigger)
            DIO=DION;
        else
            DIO=DION|0x00000001;
        if(fillForm(pCommand_Struct,ncycle,FreqTune,DIO,p_Param->i_DDSDuration|p_Param->i_DDSADelay<<16,
                 p_Param->i_DDSADuty|p_Param->i_DDSBDelay<<16|p_Param->i_DDSBDuty<<24,p_Param->d_DAC)!=Succeed)
                return  Error_MemOver;
        dTriggerWidth+=((double)ncycle) * T_Trap/64000.0;                                 // 计算经过时间
        pCommand_Struct->isTrigger=true;
        //if (dTriggerWidth>=0.1) {DIO=DION;}; //强制控制trigger为100us //怀疑Trigger脉宽不够，可注释掉使trigger on扩展到整个扫描阶段
        pCommand_Struct->Tpassed_us+= ((double)ncycle) * T_Trap/64000.0;                 // 计算经过时间
    }
    if(isSpecial){
        int restFF=(((pCommand_Struct->nCurrFF+8)>>3)<<3)-pCommand_Struct->nCurrFF;
        for(int i=0;i<restFF;i++,T_Trap+=Tstep){
            FreqTune=(unsigned int)(4294967296.0 / 6.250 / T_Trap);
            if(FreqTune>2147473648)
                return DDS_Scan_OverQuick;
            if(pCommand_Struct->isTrigger)
                DIO=DION;
            else
                DIO=DION|0x00000001;
            if(fillForm(pCommand_Struct,ncycle,FreqTune,DIO,p_Param->i_DDSDuration|p_Param->i_DDSADelay<<16,
                     p_Param->i_DDSADuty|p_Param->i_DDSBDelay<<16|p_Param->i_DDSBDuty<<24,p_Param->d_DAC)!=Succeed)
                    return  Error_MemOver;
            dTriggerWidth+=((double)ncycle) * T_Trap/64000.0;                                 // 计算经过时间
            pCommand_Struct->isTrigger=true;//if (dTriggerWidth>=0.1) {DIO=DION;}; //强制控制trigger为100us //怀疑Trigger脉宽不够，可注释掉使trigger on扩展到整个扫描阶段
            pCommand_Struct->Tpassed_us+= ((double)ncycle) * T_Trap/64000.0;                 // 计算经过时间
        }
    }
    pCommand_Struct->nMSstage++;
    pCommand_Struct->num_MSScale++;
    return Succeed;
}
/************************************************************************************************/
/*            Name:                                                                             */
/*                                                                                              */
/*         Explain:                                                                             */
/*           InPut:                                                                             */
/*          OutPut:                                                                             */
/*    Modification:                                                                             */
/*            Time:                                                                             */
/************************************************************************************************/
int ScanSpecial::CreatStage(int* p_StageParam,_Command_Struct* pCommand_Struct, bool isSpecial)
{
    _Scan_Param* p_Param=(_Scan_Param*)p_StageParam;                  //类型转换
    double Trap_q=pCommand_Struct->mMathMethod.ddstoq(p_Param->i_DDSDuration);
    double M0=pCommand_Struct->mMathMethod.Truemz(p_Param->d_Mass_Start_Th,pCommand_Struct->DF_MASS_SCALE,pCommand_Struct->DF_MASS_OFFSET)-
                     pCommand_Struct->DF_MASS_FORWARD;
    double M1=pCommand_Struct->mMathMethod.Truemz(p_Param->d_Mass_End_Th,pCommand_Struct->DF_MASS_SCALE,pCommand_Struct->DF_MASS_OFFSET)+
                     pCommand_Struct->DF_MASS_FORWARD;
    double M00=pCommand_Struct->mMathMethod.Truemz(p_Param->d_Mass_Start_Th,pCommand_Struct->DF_MASS_SCALE,pCommand_Struct->DF_MASS_OFFSET);
    double M10=pCommand_Struct->mMathMethod.Truemz(p_Param->d_Mass_End_Th,pCommand_Struct->DF_MASS_SCALE,pCommand_Struct->DF_MASS_OFFSET);
    double T_Trap0=0,T_Trap1=0;
    unsigned int ncycle=24,FreqTune=0,DIO=0,DION=0;
    double Tstep=0.0,dTriggerWidth=0.0;
    if (M0<pCommand_Struct->mMathMethod.SwitchM){
        T_Trap0=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.L_HVHFV,M0);
        T_Trap1=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.L_HVHFV,M1);
        Tstep=(p_Param->d_Scan_Speed>0)?
              (pCommand_Struct->mMathMethod.calc_Tstep_ps(p_Param->d_Scan_Speed*pCommand_Struct->DF_MASS_SCALE,Trap_q,pCommand_Struct->mMathMethod.cdA2,ncycle,pCommand_Struct->mMathMethod.L_HVHFV)*1E-6):
              (-pCommand_Struct->mMathMethod.calc_Tstep_ps(-p_Param->d_Scan_Speed*pCommand_Struct->DF_MASS_SCALE,Trap_q,pCommand_Struct->mMathMethod.cdA2,ncycle,pCommand_Struct->mMathMethod.L_HVHFV)*1E-6);
        DION=0x00ff0000;
    }else{
        T_Trap0=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.H_HVHFV,M0);
        T_Trap1=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.H_HVHFV,M1);
        Tstep=(p_Param->d_Scan_Speed>0)?
              (pCommand_Struct->mMathMethod.calc_Tstep_ps(p_Param->d_Scan_Speed*pCommand_Struct->DF_MASS_SCALE,Trap_q,pCommand_Struct->mMathMethod.cdA2,ncycle,pCommand_Struct->mMathMethod.H_HVHFV)*1E-6):
              (-pCommand_Struct->mMathMethod.calc_Tstep_ps(-p_Param->d_Scan_Speed*pCommand_Struct->DF_MASS_SCALE,Trap_q,pCommand_Struct->mMathMethod.cdA2,ncycle,pCommand_Struct->mMathMethod.H_HVHFV)*1E-6);
        DION=0x00ff0060;
    };
#if 0
    double tM0=pCommand_Struct->Tpassed_us+(M00-M0)/p_Param->d_Scan_Speed*
        pCommand_Struct->DF_MASS_SCALE*1e6*((p_Param->d_Scan_Speed>0)?1.0:-1.0);
    double tM1=pCommand_Struct->Tpassed_us+(M10-M0)/p_Param->d_Scan_Speed*
            pCommand_Struct->DF_MASS_SCALE*1e6*((p_Param->d_Scan_Speed>0)?1.0:-1.0);
    if(p_Param->d_Scan_Speed>0){
        p_Param->m_sMassScaleTable.StartMass=(double)(p_Param->d_Mass_Start_Th);
        p_Param->m_sMassScaleTable.StopMass =(double)(p_Param->d_Mass_End_Th);
    }else{
        p_Param->m_sMassScaleTable.StartMass=(double)(p_Param->d_Mass_End_Th);
        p_Param->m_sMassScaleTable.StopMass =(double)(p_Param->d_Mass_Start_Th);
    }
    p_Param->m_sMassScaleTable.StartDAQpoint=(long)((tM0-(pCommand_Struct->Tpassed_us))*pCommand_Struct->m_Adjust_Factor.DAQFREQP);
    p_Param->m_sMassScaleTable.EndDAQpoint=(long)((tM1-(pCommand_Struct->Tpassed_us))*pCommand_Struct->m_Adjust_Factor.DAQFREQP);
#endif
    //    p_Param->p_Segment->postReadyTime= p_Param->p_Segment->preReadyTime= (M00-M0)/p_Param->d_Scan_Speed*//40-38
    //            pCommand_Struct->DF_MASS_SCALE*((p_Param->d_Scan_Speed>0)?1.0:-1.0);
        cParamValue::_EventLIT* p_EventLIT= (cParamValue::_EventLIT*)p_Param->pEvent;
        //cParamValue::_EventLIT* p_EventLIT= (cParamValue::_EventLIT*)&(p_Param->p_Segment->fisrtEvent);
        p_EventLIT->postReadyTime= p_EventLIT->preReadyTime= (M00-M0)/p_Param->d_Scan_Speed*//40-38
            pCommand_Struct->DF_MASS_SCALE*((p_Param->d_Scan_Speed>0)?1.0:-1.0);
    p_EventLIT->holdTime= (M1- M0)/p_Param->d_Scan_Speed*//102-38
            pCommand_Struct->DF_MASS_SCALE*((p_Param->d_Scan_Speed>0)?1.0:-1.0);
    p_EventLIT->msStart= p_Param->d_Mass_Start_Th;
    p_EventLIT->msEnd= p_Param->d_Mass_End_Th;
    p_EventLIT->msPrecursor= pCommand_Struct->DF_MASS_FORWARD;

    ncycle = pCommand_Struct->mMathMethod.MinCycle;                                                        // 当前帧生存周期
    DIO=DION|0x00000001;
    DIO |=p_Param->ui_DIO;
    double T_Trap=((Tstep>0)?(T_Trap0):(T_Trap1));
    for(; ((Tstep>0)?(T_Trap<T_Trap1):(T_Trap>T_Trap0)); T_Trap+=Tstep){
        FreqTune=(unsigned int)(4294967296.0 / 6.250 / T_Trap);
        if(FreqTune>2147473648)
            return DDS_Scan_OverQuick;
        if(fillForm(pCommand_Struct,ncycle,FreqTune,DIO,p_Param->i_DDSDuration|p_Param->i_DDSADelay<<16,
                 p_Param->i_DDSADuty|p_Param->i_DDSBDelay<<16|p_Param->i_DDSBDuty<<24,p_Param->d_DAC)!=Succeed)
                return  Error_MemOver;
        dTriggerWidth+=((double)ncycle) * T_Trap/64000.0;                                 // 计算经过时间
        if (dTriggerWidth>=0.1) {DIO=DION;}; //强制控制trigger为100us //怀疑Trigger脉宽不够，可注释掉使trigger on扩展到整个扫描阶段
        pCommand_Struct->Tpassed_us+= ((double)ncycle) * T_Trap/64000.0;                 // 计算经过时间
    }
    if(isSpecial){
        int restFF=(((pCommand_Struct->nCurrFF+8)>>3)<<3)-pCommand_Struct->nCurrFF;
        for(int i=0;i<restFF;i++,T_Trap+=Tstep){
            FreqTune=(unsigned int)(4294967296.0 / 6.250 / T_Trap);
            if(FreqTune>2147473648)
                return DDS_Scan_OverQuick;
            if(fillForm(pCommand_Struct,ncycle,FreqTune,DIO,p_Param->i_DDSDuration|p_Param->i_DDSADelay<<16,
                     p_Param->i_DDSADuty|p_Param->i_DDSBDelay<<16|p_Param->i_DDSBDuty<<24,p_Param->d_DAC)!=Succeed)
                    return  Error_MemOver;
            dTriggerWidth+=((double)ncycle) * T_Trap/64000.0;                                 // 计算经过时间
            if (dTriggerWidth>=0.1) {DIO=DION;}; //强制控制trigger为100us //怀疑Trigger脉宽不够，可注释掉使trigger on扩展到整个扫描阶段
            pCommand_Struct->Tpassed_us+= ((double)ncycle) * T_Trap/64000.0;                 // 计算经过时间
        }
    }
    pCommand_Struct->nMSstage++;
    pCommand_Struct->num_MSScale++;
    return Succeed;
}
/************************************************************************************************/
/*            Name:                                                                             */
/*                                                                                              */
/*         Explain:                                                                             */
/*           InPut:                                                                             */
/*          OutPut:                                                                             */
/*    Modification:                                                                             */
/*            Time:                                                                             */
/************************************************************************************************/
int Empty::CreatStage(int* p_StageParam,_Command_Struct* pCommand_Struct, bool isSpecial)
{
    _Empty_Param* p_Param=(_Empty_Param*)p_StageParam;                  //类型转换
    const double Trap_q=pCommand_Struct->mMathMethod.Empty_q;//4;
    double M0=pCommand_Struct->mMathMethod.Truemz(p_Param->d_Mass_End_Th,pCommand_Struct->DF_MASS_SCALE,pCommand_Struct->DF_MASS_OFFSET)+
            pCommand_Struct->DF_MASS_FORWARD;
    double M00=pCommand_Struct->mMathMethod.Truemz(p_Param->d_Mass_Start_Th,pCommand_Struct->DF_MASS_SCALE,pCommand_Struct->DF_MASS_OFFSET)-
            pCommand_Struct->DF_MASS_FORWARD;
    double T_Trap;                                                          // 频率
    unsigned int DIO;
    if (M00<pCommand_Struct->mMathMethod.SwitchM) {
        T_Trap=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.L_HVHFV,M0);
        DIO=0x00000000;
    }else{
        T_Trap=pCommand_Struct->mMathMethod.calc_T(Trap_q,pCommand_Struct->mMathMethod.cdA2,pCommand_Struct->mMathMethod.H_HVHFV,M0);
        DIO=0x00000060;
    };
    DIO |=p_Param->ui_DIO;
    unsigned int i_DDSBDelay=32-(int)(p_Param->i_HVHF_DutyCycle_DDS/2);
    unsigned int i_DDSBDuty=32-(int)(p_Param->i_HVHF_DutyCycle_DDS/2)+p_Param->i_HVHF_DutyCycle_DDS;
    unsigned int ncycle=(unsigned int)((p_Param->d_Time*1000.0) /T_Trap)*64;                    // 当前帧生存周期
    if(ncycle>0xffffffff)
        return Holdtime_Empty_Over;
    unsigned int FreqTune=(unsigned int)(4294967296.0 / 6.250 / T_Trap);
    if(FreqTune>2147473648)
        return DDS_Empty_OverQuick;
    if(!isSpecial){
        if(ncycle<pCommand_Struct->mMathMethod.MinCycle)
            return Holdtime_Empty_Short;
        if(fillForm(pCommand_Struct,ncycle,FreqTune,DIO,p_Param->i_DDSDuration|p_Param->i_DDSADelay<<16,
                 p_Param->i_DDSADuty|i_DDSBDelay<<16|i_DDSBDuty<<24,p_Param->d_DAC)!=Succeed)
                return  Error_MemOver;
        pCommand_Struct->Tpassed_us+= ((double)ncycle) * T_Trap/64000.0;                               // 计算经过时间
    }else{// 根据现有频点帧号，将Empty的总DDS周期分散到1至多个频点帧，使总频帧数为8N
        int restFF=(((pCommand_Struct->nCurrFF+8)>>3)<<3)-pCommand_Struct->nCurrFF;
        ncycle=ncycle-1536*(restFF-1);//24*64
        if(ncycle<pCommand_Struct->mMathMethod.MinCycle)
            return Holdtime_Empty_Short;
        for (int emptyFF=0;emptyFF<restFF;emptyFF++){
            if(fillForm(pCommand_Struct,ncycle,FreqTune,DIO,p_Param->i_DDSDuration|p_Param->i_DDSADelay<<16,
                     p_Param->i_DDSADuty|i_DDSBDelay<<16|i_DDSBDuty<<24,p_Param->d_DAC)!=Succeed)
                    return  Error_MemOver;
            pCommand_Struct->Tpassed_us+= ((double)ncycle) * T_Trap/64000.0;                 // 计算经过时间
            ncycle = pCommand_Struct->mMathMethod.MinCycle;
        }
    }
    pCommand_Struct->nMSstage++;                                           // 当前Micro sweep号
    return Succeed;
}


//double fCallUserCode(int dacIndex,double mass,double detectorVol = 0,double ifVol = 0,
//                     double dlVol = 0,double qDCVol = 0,double qRFVol = 0,int segIndex = 1,int evtIndex = 1){
//    double val = 0;
//    if(m_isValidJs){
//        QScriptValue jsValue = js.evaluate(tr("dacValue(%1,%2,%3,%4,%5,%6,%7,%8,%9)")
//                                           .arg(dacIndex)
//                                           .arg(mass)
//                                           .arg(detectorVol)
//                                           .arg(ifVol)
//                                           .arg(dlVol)
//                                           .arg(qDCVol)
//                                           .arg(qRFVol)
//                                           .arg(segIndex)
//                                           .arg(evtIndex));
//        if(!js.hasUncaughtException())
//            val = jsValue.toNumber();
//        if(val > 10)
//            val = 10;
//        else if(val < -10)
//            val = -10;
//    }
//    return val;
//}

//int ScanSpecial::CreatStage(int* p_StageParam,_Command_Struct* pCommand_Struct, bool isSpecial)
//{
//    _ScanQ_Param* p_Param=(_ScanQ_Param*)p_StageParam;                  //类型转换


//    if(pEvt->EventTime <= (PreReadyTime + PostReadyTime + SPARAM_MIN_FRAME_TIME_SEC))
//        pEvt->EventTime = PreReadyTime + PostReadyTime + SPARAM_MIN_FRAME_TIME_SEC;
//    {
//        if(pEvt->msStart > pEvt->msEnd)
//            pEvt->msEnd = pEvt->msStart;//不支持反扫
//        if(pEvt->microScan < SPARAM_MIN_MASS_MICRO_SCAN)
//            pEvt->microScan = SPARAM_MIN_MASS_MICRO_SCAN;

//        nEvtFrameCount = uint((pEvt->msEnd - pEvt->msStart) / pEvt->microScan + 0.5) + 1;
//        nFrameCount = nEvtFrameCount + 2;
//        if((nFrameCount % 8) != 0)
//            nFrameCount += 8 - nFrameCount % 8;
//        baEvtMsMethodBuffer.resize(nFrameCount * 16 * sizeof(uint));
//        memset(baEvtMsMethodBuffer.data(), 0, baEvtMsMethodBuffer.size());
//        baEvtParam.resize(sizeof(ScanEvent));
//        pScanEvtParam = (ScanEvent*)baEvtParam.data();
//        memset(pScanEvtParam->title,'\0',30);
//        tmpstr=pEvt->title.toLocal8Bit();
//        memcpy(pScanEvtParam->title,tmpstr.data(),tmpstr.size());
//        pScanEvtParam->type = 1;
//        pScanEvtParam->msStart = pEvt->msStart;
//        pScanEvtParam->msEnd = pEvt->msEnd;
//        pScanEvtParam->time = pEvt->EventTime;
//        dbTimeSum += pEvt->EventTime;

//        // pre-ready frame
//        nFrameNumber++;

//        // event frame
//        dbEvtTimeStep = (pEvt->EventTime - PreReadyTime - PostReadyTime) / nEvtFrameCount;
//        nFrameKeepPeriod = uint(dbEvtTimeStep * pTreeCMS.nDDSFrequncyHz);
//        puFrameBuffer = (uint*)baEvtMsMethodBuffer.data() + 16;

//        QString srtCodeTmp(strCode);
//        if(pEvt->TypeDL!="Default")
//        srtCodeTmp=ChangeParam(srtCodeTmp,"_G_DLBias",QString::number(pEvt->ValueDL));
//        if(pEvt->TypeDC!="Default")
//            srtCodeTmp=ChangeParam(srtCodeTmp,"_G_QABias",QString::number(pEvt->ValueDC));
//        if(pEvt->TypeDC!="Tuning")
//            srtCodeTmp=ChangeParam(srtCodeTmp,"_G_MIGBias",QString::number(pEvt->ValueMIG));
//        if(pEvt->TypeOrifice!="Tuning")
//            srtCodeTmp=ChangeParam(srtCodeTmp,"_G_ORBias",QString::number(pEvt->ValueOrifice));
//        if(pEvt->TypePRE!="Tuning")
//            srtCodeTmp=ChangeParam(srtCodeTmp,"_G_PreBias",QString::number(pEvt->ValuePRE));
//        if(pEvt->TypeQMF!="Tuning")
//            srtCodeTmp=ChangeParam(srtCodeTmp,"_G_QMFBias",QString::number(pEvt->ValueQMF));
//        js.evaluate(srtCodeTmp);

//        for(nEvtFrameIndex = 0; nEvtFrameIndex < nEvtFrameCount; nEvtFrameIndex++, puFrameBuffer += 16){
//            puFrameBuffer[0] = nFrameNumber++;  // Frame number
//            puFrameBuffer[1] = nEvtIndex;       // Micro sweep
//            puFrameBuffer[2] = nFrameKeepPeriod;// Frame cycle
//            puFrameBuffer[3] = pTreeCMS.nDDSFwt;         // DDS's FWT parameter
//            puFrameBuffer[5] = 0x00ff0000;      // DAQ's triger
//            puFrameBuffer[6] = (pTreeCMS.uDipoleHStart << 16) | pTreeCMS.uDipolePeriod;
//            puFrameBuffer[7] = (pTreeCMS.uHvhfHEnd << 24) | (pTreeCMS.uHvhfHStart << 16) | pTreeCMS.uDipoleHEnd;
//            // DACs
//            puDacBuffer = puFrameBuffer + 8;
//            for(nDacIndex = 0; nDacIndex < 12; nDacIndex += 2){
//                dbDacAValue = fCallUserCode(nDacIndex,
//                            pScanEvtParam->msStart+ nEvtFrameIndex * pEvt->microScan,
//                            dbDetectorVol,dbIfVol,dbDlVol,dbQDcVol,
//                            dbQRfVol,nSegIndex,nEvtIndex);
//                dbDacBValue = fCallUserCode(nDacIndex + 1,
//                            pScanEvtParam->msStart + nEvtFrameIndex * pEvt->microScan,
//                            dbDetectorVol,dbIfVol,dbDlVol,dbQDcVol,
//                            dbQRfVol,nSegIndex,nEvtIndex);
//                puDacBuffer[nDacIndex >> 1] = ((uint((dbDacAValue + 10) * 0xffff / 20) & 0xffff) )
//                        | ((uint((dbDacBValue + 10) * 0xffff / 20) & 0xffff)<< 16);
//            }
//            //test
//#ifdef QT_DEBUG
//            puDacBuffer[5] = (puDacBuffer[5] & 0x0000ffff) | (((19661 + nEvtFrameIndex * 26214 / nEvtFrameCount) & 0xffff) << 16);
//#endif
//        }


//    ncycle = pCommand_Struct->mMathMethod.MinCycle;                                                        // 当前帧生存周期
//    DIO=DION|0x00000001;
//    DIO |=p_Param->ui_DIO;
//    double T_Trap=((Tstep>0)?(T_Trap0):(T_Trap1));
//    for(; ((Tstep>0)?(T_Trap<T_Trap1):(T_Trap>T_Trap0)); T_Trap+=Tstep){
//        FreqTune=(unsigned int)(4294967296.0 / 6.250 / T_Trap);
//        if(FreqTune>2147473648)
//            return DDS_Scan_OverQuick;
//        fillForm(pCommand_Struct,ncycle,FreqTune,DIO,p_Param->i_DDSDuration|p_Param->i_DDSADelay<<16,
//                 p_Param->i_DDSADuty|p_Param->i_DDSBDelay<<16|p_Param->i_DDSBDuty<<24,p_Param->d_DAC);
//        dTriggerWidth+=((double)ncycle) * T_Trap/64000.0;                                 // 计算经过时间
//        if (dTriggerWidth>=0.1) {DIO=DION;}; //强制控制trigger为100us //怀疑Trigger脉宽不够，可注释掉使trigger on扩展到整个扫描阶段
//        pCommand_Struct->Tpassed_us+= ((double)ncycle) * T_Trap/64000.0;                 // 计算经过时间
//    }
//    if(isSpecial){
//        int restFF=(((pCommand_Struct->nCurrFF+8)>>3)<<3)-pCommand_Struct->nCurrFF;
//        for(int i=0;i<restFF;i++,T_Trap+=Tstep){
//            FreqTune=(unsigned int)(4294967296.0 / 6.250 / T_Trap);
//            if(FreqTune>2147473648)
//                return DDS_Scan_OverQuick;
//            fillForm(pCommand_Struct,ncycle,FreqTune,DIO,p_Param->i_DDSDuration|p_Param->i_DDSADelay<<16,
//                     p_Param->i_DDSADuty|p_Param->i_DDSBDelay<<16|p_Param->i_DDSBDuty<<24,p_Param->d_DAC);
//            dTriggerWidth+=((double)ncycle) * T_Trap/64000.0;                                 // 计算经过时间
//            if (dTriggerWidth>=0.1) {DIO=DION;}; //强制控制trigger为100us //怀疑Trigger脉宽不够，可注释掉使trigger on扩展到整个扫描阶段
//            pCommand_Struct->Tpassed_us+= ((double)ncycle) * T_Trap/64000.0;                 // 计算经过时间
//        }
//    }
//    pCommand_Struct->nMSstage++;
//    pCommand_Struct->num_MSScale++;
//    return Succeed;
//}


//void smswidget1::CreatMethod(TreeCMS &pTreeCMS)
//{
//    uint nSegIndex,nEvtIndex,nEvtFrameCount,nEvtFrameIndex,nFrameKeepPeriod,nFrameCount,
//            nFrameNumber, nDacIndex;
//    uint *puFrameBuffer,*puDacBuffer;
//    QByteArray baMsMethodBuffer,baEvtMsMethodBuffer,baExportParam, baEvtParam;
//    double dbEvtTimeStep,dbDacAValue,dbDacBValue, dbDetectorVol,
//            dbIfVol, dbDlVol, dbQDcVol, dbQRfVol, dbTimeSum;
//    bool bSetupDaqTrigger;
//    EventParam* pEvtParam;
//    ScanEvent* pScanEvtParam;
//    SIMEvent* pSimEvtParam;
//    QFile rfile("./ms_formula.js");
//    if(!rfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
//        qDebug()<<"Can't open the file! ./ms_formula.js"<<endl;
//        rfile.close();
//        return;
//    }
//    QScriptEngine js;
//    QString strCode = rfile.readAll();
//    rfile.close();
//    if(!strCode.isEmpty()){
//        js.evaluate(strCode);
//        if(js.hasUncaughtException())
//            return;
//    }else{
//        qDebug()<<"empty! ./ms_formula.js"<<endl;
//        return;
//    }

//    nSegIndex = 1;
//    QList<ParamEvent*>& lstEvt = pTreeCMS.pEvent;
//    nEvtIndex = 1;
//    nFrameNumber = 1;
//    baMsMethodBuffer.resize(512);
//    puFrameBuffer = (uint*)baMsMethodBuffer.data();
//    memset(puFrameBuffer, 0, 512);
//    puFrameBuffer[0] = 0xfffff065;
//    bSetupDaqTrigger = false;
//    baExportParam.resize(sizeof(EventParam) - sizeof(Event));
//    pEvtParam = (EventParam*)baExportParam.data();
//    pEvtParam->eventNumber = lstEvt.size();
//    pEvtParam->type= pTreeCMS.type;//1 tuning
//    pEvtParam->minTime = SPARAM_MIN_FRAME_TIME_SEC;
//    pEvtParam->preReadyTime = PreReadyTime;
//    pEvtParam->postReadyTime = PostReadyTime;

//    QByteArray tmpstr=pTreeCMS.pSegment->title.toLocal8Bit();
//    strcpy(pEvtParam->title,tmpstr.data());
//    dbTimeSum = 0;
//    foreach (ParamEvent* pEvt, lstEvt) {
//        if(pEvt->EventTime <= (PreReadyTime + PostReadyTime + SPARAM_MIN_FRAME_TIME_SEC))
//            pEvt->EventTime = PreReadyTime + PostReadyTime + SPARAM_MIN_FRAME_TIME_SEC;
//        if(pEvt->type == "Scan"
//                || pEvt->type == "Profile" ){
//            if(pEvt->msStart > pEvt->msEnd)
//                pEvt->msEnd = pEvt->msStart;//不支持反扫
//            if(pEvt->microScan < SPARAM_MIN_MASS_MICRO_SCAN)
//                pEvt->microScan = SPARAM_MIN_MASS_MICRO_SCAN;

//            nEvtFrameCount = uint((pEvt->msEnd - pEvt->msStart) / pEvt->microScan + 0.5) + 1;
//            nFrameCount = nEvtFrameCount + 2;
//            if((nFrameCount % 8) != 0)
//                nFrameCount += 8 - nFrameCount % 8;
//            baEvtMsMethodBuffer.resize(nFrameCount * 16 * sizeof(uint));
//            memset(baEvtMsMethodBuffer.data(), 0, baEvtMsMethodBuffer.size());
//            baEvtParam.resize(sizeof(ScanEvent));
//            pScanEvtParam = (ScanEvent*)baEvtParam.data();
//            memset(pScanEvtParam->title,'\0',30);
//            tmpstr=pEvt->title.toLocal8Bit();
//            memcpy(pScanEvtParam->title,tmpstr.data(),tmpstr.size());
//            pScanEvtParam->type = 1;
//            pScanEvtParam->msStart = pEvt->msStart;
//            pScanEvtParam->msEnd = pEvt->msEnd;
//            pScanEvtParam->time = pEvt->EventTime;
//            dbTimeSum += pEvt->EventTime;

//            // pre-ready frame
//            nFrameNumber++;

//            // event frame
//            dbEvtTimeStep = (pEvt->EventTime - PreReadyTime - PostReadyTime) / nEvtFrameCount;
//            nFrameKeepPeriod = uint(dbEvtTimeStep * pTreeCMS.nDDSFrequncyHz);
//            puFrameBuffer = (uint*)baEvtMsMethodBuffer.data() + 16;

//            QString srtCodeTmp(strCode);
//            if(pEvt->TypeDL!="Default")
//            srtCodeTmp=ChangeParam(srtCodeTmp,"_G_DLBias",QString::number(pEvt->ValueDL));
//            if(pEvt->TypeDC!="Default")
//                srtCodeTmp=ChangeParam(srtCodeTmp,"_G_QABias",QString::number(pEvt->ValueDC));
//            if(pEvt->TypeDC!="Tuning")
//                srtCodeTmp=ChangeParam(srtCodeTmp,"_G_MIGBias",QString::number(pEvt->ValueMIG));
//            if(pEvt->TypeOrifice!="Tuning")
//                srtCodeTmp=ChangeParam(srtCodeTmp,"_G_ORBias",QString::number(pEvt->ValueOrifice));
//            if(pEvt->TypePRE!="Tuning")
//                srtCodeTmp=ChangeParam(srtCodeTmp,"_G_PreBias",QString::number(pEvt->ValuePRE));
//            if(pEvt->TypeQMF!="Tuning")
//                srtCodeTmp=ChangeParam(srtCodeTmp,"_G_QMFBias",QString::number(pEvt->ValueQMF));
//            js.evaluate(srtCodeTmp);

//            for(nEvtFrameIndex = 0; nEvtFrameIndex < nEvtFrameCount; nEvtFrameIndex++, puFrameBuffer += 16){
//                puFrameBuffer[0] = nFrameNumber++;  // Frame number
//                puFrameBuffer[1] = nEvtIndex;       // Micro sweep
//                puFrameBuffer[2] = nFrameKeepPeriod;// Frame cycle
//                puFrameBuffer[3] = pTreeCMS.nDDSFwt;         // DDS's FWT parameter
//                puFrameBuffer[5] = 0x00ff0000;      // DAQ's triger
//                puFrameBuffer[6] = (pTreeCMS.uDipoleHStart << 16) | pTreeCMS.uDipolePeriod;
//                puFrameBuffer[7] = (pTreeCMS.uHvhfHEnd << 24) | (pTreeCMS.uHvhfHStart << 16) | pTreeCMS.uDipoleHEnd;
//                // DACs
//                puDacBuffer = puFrameBuffer + 8;
//                for(nDacIndex = 0; nDacIndex < 12; nDacIndex += 2){
//                    dbDacAValue = fCallUserCode(nDacIndex,
//                                pScanEvtParam->msStart+ nEvtFrameIndex * pEvt->microScan,
//                                dbDetectorVol,dbIfVol,dbDlVol,dbQDcVol,
//                                dbQRfVol,nSegIndex,nEvtIndex);
//                    dbDacBValue = fCallUserCode(nDacIndex + 1,
//                                pScanEvtParam->msStart + nEvtFrameIndex * pEvt->microScan,
//                                dbDetectorVol,dbIfVol,dbDlVol,dbQDcVol,
//                                dbQRfVol,nSegIndex,nEvtIndex);
//                    puDacBuffer[nDacIndex >> 1] = ((uint((dbDacAValue + 10) * 0xffff / 20) & 0xffff) )
//                            | ((uint((dbDacBValue + 10) * 0xffff / 20) & 0xffff)<< 16);
//                }
//                //test
//#ifdef QT_DEBUG
//                puDacBuffer[5] = (puDacBuffer[5] & 0x0000ffff) | (((19661 + nEvtFrameIndex * 26214 / nEvtFrameCount) & 0xffff) << 16);
//#endif
//            }
//        }else if(pEvt->type == "SIM"){
//            QList<uint> lstValidChannel;
//            uint nChannelIndex;
//            double dbSIMMass,dbMass,dbMaxMass;
//            baEvtParam.resize(sizeof(SIMEvent));
//            pSimEvtParam = (SIMEvent*)baEvtParam.data();
//            memset(pSimEvtParam->title,'\0',30);
//            tmpstr=pEvt->title.toLocal8Bit();
//            memcpy(pSimEvtParam->title,tmpstr.data(),tmpstr.size());
//            pSimEvtParam->type = 2;
//            pSimEvtParam->time = pEvt->EventTime;

//            dbMaxMass = std::numeric_limits<double>::min();
//            for(nChannelIndex = 0; nChannelIndex < SMS_CHANNEL_COUNT; nChannelIndex++){
//                if((dbMass = pEvt->ChannelMass[nChannelIndex].toDouble()) > 0.0001){
//                    lstValidChannel.append(nChannelIndex);
//                    if(dbMaxMass < dbMass)
//                        dbMaxMass = dbMass;
//                }
//                pSimEvtParam->mass[nChannelIndex] = dbMass;
//            }
//            nEvtFrameCount = lstValidChannel.size();
//            if(nEvtFrameCount == 0)
//                continue;
//            nFrameCount = nEvtFrameCount + 2;
//            if((nFrameCount % 8) != 0)
//                nFrameCount += 8 - nFrameCount % 8;
//            baEvtMsMethodBuffer.resize(nFrameCount * 16 * sizeof(uint));
//            memset(baEvtMsMethodBuffer.data(), 0, baEvtMsMethodBuffer.size());

//            // pre-ready frame
//            nFrameNumber++;
//            // event frame
//            pEvt->EventTime -= PreReadyTime + PostReadyTime;
//            if(pEvt->EventTime < ((PreReadyTime * 2 + SPARAM_MIN_FRAME_TIME_SEC) * nEvtFrameCount))
//                dbEvtTimeStep = PreReadyTime * 2 + SPARAM_MIN_FRAME_TIME_SEC;
//            else
//                dbEvtTimeStep = pEvt->EventTime  / nEvtFrameCount;
//            pEvt->EventTime = PreReadyTime + PostReadyTime + dbEvtTimeStep * nEvtFrameCount;
//            dbTimeSum += pEvt->EventTime;
//            nFrameKeepPeriod = uint(dbEvtTimeStep * pTreeCMS.nDDSFrequncyHz);
//            puFrameBuffer = (uint*)baEvtMsMethodBuffer.data() + 16;
//            for(nEvtFrameIndex = 0; nEvtFrameIndex < nEvtFrameCount; nEvtFrameIndex++, puFrameBuffer += 16){
//                puFrameBuffer[0] = nFrameNumber++;  // Frame number
//                puFrameBuffer[1] = nEvtIndex;       // Micro sweep
//                puFrameBuffer[2] = nFrameKeepPeriod;// Frame cycle
//                puFrameBuffer[3] = pTreeCMS.nDDSFwt;         // DDS's FWT parameter
//                puFrameBuffer[5] = 0x00ff0000;      // DAQ's triger
//                puFrameBuffer[6] = (pTreeCMS.uDipoleHStart << 16) | pTreeCMS.uDipolePeriod;
//                puFrameBuffer[7] = (pTreeCMS.uHvhfHEnd << 24) | (pTreeCMS.uHvhfHStart << 16) | pTreeCMS.uDipoleHEnd;

//                nChannelIndex = lstValidChannel.at(nEvtFrameIndex);
//                dbSIMMass = pEvt->ChannelMass[nChannelIndex].toDouble();

//                QString srtCodeTmp(strCode);
//                if(pEvt->TypeDL!="Default")
//                    srtCodeTmp=ChangeParam(srtCodeTmp,"_G_DLBias",pEvt->ChannelDL[nChannelIndex]);
//                if(pEvt->TypeDC!="Default")
//                    srtCodeTmp=ChangeParam(srtCodeTmp,"_G_QABias",pEvt->ChannelDC[nChannelIndex]);
//                if(pEvt->TypeDC!="Tuning")
//                    srtCodeTmp=ChangeParam(srtCodeTmp,"_G_MIGBias",QString::number(pEvt->ValueMIG));
//                if(pEvt->TypeOrifice!="Tuning")
//                    srtCodeTmp=ChangeParam(srtCodeTmp,"_G_ORBias",QString::number(pEvt->ValueOrifice));
//                if(pEvt->TypePRE!="Tuning")
//                    srtCodeTmp=ChangeParam(srtCodeTmp,"_G_PreBias",QString::number(pEvt->ValuePRE));
//                if(pEvt->TypeQMF!="Tuning")
//                    srtCodeTmp=ChangeParam(srtCodeTmp,"_G_QMFBias",QString::number(pEvt->ValueQMF));
//                js.evaluate(srtCodeTmp);

//                // DACs
//                puDacBuffer = puFrameBuffer + 8;
//                for(nDacIndex = 0; nDacIndex < 12; nDacIndex += 2){
//                    dbDacAValue = fCallUserCode(nDacIndex,dbSIMMass,dbDetectorVol,dbIfVol,
//                                                dbDlVol,dbQDcVol,dbQRfVol,nSegIndex,nEvtIndex);
//                    dbDacBValue = fCallUserCode(nDacIndex + 1,dbSIMMass,dbDetectorVol,dbIfVol,
//                                                dbDlVol,dbQDcVol,dbQRfVol,nSegIndex,nEvtIndex);
//                    puDacBuffer[nDacIndex >> 1] = ((uint((dbDacAValue + 10) * 0xffff / 20) & 0xffff) )
//                            | ((uint((dbDacBValue + 10) * 0xffff / 20) & 0xffff)<< 16);
//                }
//#ifdef QT_DEBUG
//                //test
//                puDacBuffer[5] = (puDacBuffer[5] & 0x0000ffff) | ((uint(19661 + dbSIMMass * 26214 / dbMaxMass) & 0xffff) << 16);
//#endif
//            }
//        }
//        // pre-ready frame
//        puFrameBuffer = (uint*)baEvtMsMethodBuffer.data();
//        memcpy(puFrameBuffer, puFrameBuffer + 16, 16 * 4);
//        puFrameBuffer[0]--;
//        puFrameBuffer[2] = uint(PreReadyTime * pTreeCMS.nDDSFrequncyHz);
//        if(!bSetupDaqTrigger){
//            puFrameBuffer[5] = 0x00ff00ff;      // DAQ's trigger
//            bSetupDaqTrigger = true;
//        }
//        // post-ready frame
//        puFrameBuffer = (uint*)baEvtMsMethodBuffer.data() + (nEvtFrameCount + 1) * 16;
//        nFrameKeepPeriod = uint(PostReadyTime * pTreeCMS.nDDSFrequncyHz / (nFrameCount - nEvtFrameCount - 1));
//        for(nEvtFrameIndex = nEvtFrameCount + 1; nEvtFrameIndex < nFrameCount; nEvtFrameIndex++, puFrameBuffer += 16){
//            memcpy(puFrameBuffer, baEvtMsMethodBuffer.data()+nEvtFrameCount*64, 64);
//            puFrameBuffer[0] = nFrameNumber++;  // Frame number
//            puFrameBuffer[2] = nFrameKeepPeriod;// Frame cycle
//            puFrameBuffer[5] = 0x00ff0000;
//        }
//        baExportParam.append(baEvtParam);
//        baMsMethodBuffer.append(baEvtMsMethodBuffer);
//        nEvtIndex++;
//    }

//    puFrameBuffer = (uint*)baMsMethodBuffer.data();
//    puFrameBuffer[1] = (baMsMethodBuffer.size() - 512) / 64;
//    puFrameBuffer[127] = puFrameBuffer[0] + puFrameBuffer[1];
//    SObject* pMsObj = sobject()->findChild<SObject*>("ms");
//if(mTreeCMS.type){
//    SObject* pObjs = sobject()->findChild<SObject*>("ms_tuning");
//    if(pObjs)
//        pObjs->setProperty("ms_method", baMsMethodBuffer);//需要新加此属性/////////////
//}else{
//    pMsObj->QObject::setProperty("events_time", dbTimeSum);
//    SObject* pSeg = pMsObj->findChild<SObject*>("segment1");
//    if(pSeg)
//        pSeg->setProperty("ms_method", baMsMethodBuffer);
//}
//    printfMsMethod(baMsMethodBuffer);
//    baMsMethodBuffer.clear();
//    nSegIndex++;
//    pMsObj->setProperty("event_param", baExportParam);

//    int sizeExportParam=baExportParam.size();
//    QFile file("./tempMethodParam.dat");
//    file.open(QFile::WriteOnly);
//    if(file.isOpen()){
//        if(file.size()!=0)
//            file.resize(0);
//        file.write((char*)(&sizeExportParam),sizeof(sizeExportParam));
//        if(sizeExportParam>0)
//            file.write(baExportParam.data(), baExportParam.size());
//        file.close();
//    }

//    if(m_isValidJs){
//        SCommand* pComd;
//        SObject* pObj;
//        auto comms = mainWindow()->project()->communications();
//        foreach (SCommunication* comm, comms) {
//            if((pComd = comm->command()) != NULL && pComd->name() == "dmsit"){
//                pObj = pComd->sobject()->findChild<SObject*>("asg");
//                if(pObj != NULL && (pObj = pObj->findChild<SObject*>("dac")) != NULL){
//                    uint uAsgBoradIndex, uAsgDacIndex, uAsgDacOffset;
//                    double dbAsgDacVal;
//                    char szPropName[2][20];
//                    QScriptValue jsValue;
//                    for(uAsgBoradIndex = 0; uAsgBoradIndex < 4; uAsgBoradIndex++){
//                        sprintf(&szPropName[0][0], "value_%c", char('A' + uAsgBoradIndex));
//                        strcat(&szPropName[0][0], "%u");
//                        uAsgDacOffset = uAsgBoradIndex * 100;
//                        for(uAsgDacIndex = 0; uAsgDacIndex < 40; uAsgDacIndex++){
//                            jsValue = js.evaluate(tr("asgDacValue(%1)").arg(uAsgDacOffset + uAsgDacIndex));
//                            if(!js.hasUncaughtException())
//                                dbAsgDacVal = jsValue.toNumber();
//                            else
//                                dbAsgDacVal = 0;
//                            sprintf(&szPropName[1][0], &szPropName[0][0], uAsgDacIndex);
//                            pObj->setProperty(&szPropName[1][0], dbAsgDacVal);
//                        }
//                    }
//                }
//            }
//        }
//    }
//}
