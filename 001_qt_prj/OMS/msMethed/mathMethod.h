#pragma once
#include "math.h"

//unsigned int MinCycle=24*64; /**< TODO */
//double L_HVHFV=100.0; /**< TODO */
//double H_HVHFV=250.0; /**< TODO */

//double Injection_q=0.6; /**< TODO */
//double Cooling_q=0.6; /**< TODO */
//double DAWI_q=0.562; /**< TODO */
//double IsoCooling_q=0.25; /**< TODO */
//double Empty_q=4; /**< TODO */

//double VHVPH= 250.0,VHVPL= 100.0; /**< TODO */
//double VHVNH=-250.0,VHVNL=-100.0; /**< TODO */

//double SwitchM=159.0; /**< TODO */

//const double cdThomson=		1.0/6.0221367E+26/1.60217733E-19;	//unit:kg/Coulomb /**< TODO */
//double cdRfield=0.005;		//unit: meter /**< TODO */
//double cdA2=0.97013;			//a.u. /**< TODO */
//const double cdPI=3.14159265358979323846; /**< TODO */

///**
// * @brief
// *
// * @param T_us
// * @param param_A2
// * @param V_volts
// * @param M_Thomson
// * @return double
// */
//double calc_q(double T_us,double param_A2,double V_volts, double M_Thomson)
//{
//    return (T_us*T_us*1.0E-12*param_A2 * V_volts/(cdPI*cdPI)/(cdRfield*cdRfield)/M_Thomson/cdThomson);
//}

///**
// * @brief
// *
// * @param param_q
// * @param param_A2
// * @param V_volts
// * @param M_Thomson
// * @return double
// */
//double calc_T(double param_q,double param_A2,double V_volts, double M_Thomson)
//{
//    return sqrt(param_q*(cdPI*cdPI)*(cdRfield*cdRfield)*M_Thomson*cdThomson/(param_A2 * V_volts))*1.0E+6;
//}

///**
// * @brief
// *
// * @param param_q
// * @param T_us
// * @param param_A2
// * @param V_volts
// * @return double
// */
//double calc_M(double param_q,double T_us,double param_A2,double V_volts)
//{
//    return (T_us*T_us*1.0E-12*param_A2 * V_volts/(cdPI*cdPI)/(cdRfield*cdRfield)/param_q/cdThomson);
//}

///**
// * @brief
// *
// * @param param_q
// * @param param_A2
// * @param Tstep_ps
// * @param N_wf
// * @param V_volts
// * @return double
// */
//double calc_scan_speed(double param_q,double param_A2,double Tstep_ps, int N_wf, double V_volts)
//{
//    return (param_A2*Tstep_ps*2E-12/N_wf*V_volts/(cdPI*cdPI)/(cdRfield*cdRfield)/param_q/cdThomson);
//}

///**
// * @brief
// *
// * @param scan_speed_Th_per_second
// * @param param_q
// * @param param_A2
// * @param N_wf
// * @param V_volts
// * @return double
// */
//double calc_Tstep_ps(double scan_speed_Th_per_second,double param_q,double param_A2, int N_wf, double V_volts)
//{
//    return scan_speed_Th_per_second/(param_A2*2E-12/N_wf*V_volts/(cdPI*cdPI)/(cdRfield*cdRfield)/param_q/cdThomson);
//}

///**
// * @brief
// *
// * @param mz
// * @param d_Mass_Scale_Factor
// * @param d_Mass_Offset_Factor
// * @return double
// */
//double Truemz(double mz,double d_Mass_Scale_Factor,double d_Mass_Offset_Factor)
//{
//   //return (mz*InputDialog.m_sFreqTable.LitCoeffParam.Mass_Scale_Factor + InputDialog.m_sFreqTable.LitCoeffParam.Mass_Offset_Factor);
//   return (mz*d_Mass_Scale_Factor + d_Mass_Offset_Factor);
//}

///**
// * @brief
// *
// * @param n_DDS
// * @return double
// */
//double ddstoq(int n_DDS)
//{
//    double B4;
//    B4= 2.0/((double)(n_DDS)/64.0);
//    return (0.0231426*B4*B4*B4*B4*B4*B4 - 0.001847385*B4*B4*B4*B4*B4 + 0.002884489*B4*B4*B4*B4 - 0.413975*B4*B4*B4 - 0.0003623956*B4*B4 + 1.102711*B4 - 0.00000249799);
//}

///**
// * @brief
// *
// * @param HLSET
// * @return double
// */
//double VHVP(bool HLSET)
//{
//    return (HLSET?VHVPH:VHVPL);
//}

///**
// * @brief
// *
// * @param HLSET
// * @return double
// */
//double VHVN(bool HLSET)
//{
//    return (HLSET?VHVNH:VHVNL);
//}

struct cMathMethod
{
public:
    //cMathMethod(){}
    //~cMathMethod(){}
    unsigned int MinCycle=24*64; /**< TODO */
    double L_HVHFV=100.0; /**< TODO */
    double H_HVHFV=250.0; /**< TODO */

    double Injection_q=0.6; /**< TODO */
    double Cooling_q=0.6; /**< TODO */
    double DAWI_q=0.562; /**< TODO */
    double IsoCooling_q=0.25; /**< TODO */
    double Empty_q=4; /**< TODO */

    double VHVPH= 250.0,VHVPL= 100.0; /**< TODO */
    double VHVNH=-250.0,VHVNL=-100.0; /**< TODO */

    double SwitchM=159.0; /**< TODO */

    const double cdThomson=		1.0/6.0221367E+26/1.60217733E-19;	//unit:kg/Coulomb /**< TODO */
    double cdRfield=0.005;		//unit: meter /**< TODO */
    double cdA2=0.97013;			//a.u. /**< TODO */
    const double cdPI=3.14159265358979323846; /**< TODO */
    inline double calc_q(double T_us,double param_A2,double V_volts, double M_Thomson){
        return (T_us*T_us*1.0E-12*param_A2 * V_volts/(cdPI*cdPI)/(cdRfield*cdRfield)/M_Thomson/cdThomson);
    }
    inline double calc_T(double param_q,double param_A2,double V_volts, double M_Thomson){
        return sqrt(param_q*(cdPI*cdPI)*(cdRfield*cdRfield)*M_Thomson*cdThomson/(param_A2 * V_volts))*1.0E+6;
    }
    inline double calc_M(double param_q,double T_us,double param_A2,double V_volts){
        return (T_us*T_us*1.0E-12*param_A2 * V_volts/(cdPI*cdPI)/(cdRfield*cdRfield)/param_q/cdThomson);
    }
    inline double calc_scan_speed(double param_q,double param_A2,double Tstep_ps, int N_wf, double V_volts){
        return (param_A2*Tstep_ps*2E-12/N_wf*V_volts/(cdPI*cdPI)/(cdRfield*cdRfield)/param_q/cdThomson);
    }
    inline double calc_Tstep_ps(double scan_speed_Th_per_second,double param_q,double param_A2, int N_wf, double V_volts){
        return scan_speed_Th_per_second/(param_A2*2E-12/N_wf*V_volts/(cdPI*cdPI)/(cdRfield*cdRfield)/param_q/cdThomson);
    }
    inline double Truemz(double mz,double d_Mass_Scale_Factor,double d_Mass_Offset_Factor){
       return (mz*d_Mass_Scale_Factor + d_Mass_Offset_Factor);
    }
    inline double ddstoq(int n_DDS){
        double B4= 2.0/((double)(n_DDS)/64.0);
        return (0.0231426*B4*B4*B4*B4*B4*B4 - 0.001847385*B4*B4*B4*B4*B4 + 0.002884489*B4*B4*B4*B4 - 0.413975*B4*B4*B4 - 0.0003623956*B4*B4 + 1.102711*B4 - 0.00000249799);
    }
    inline double VHVP(bool HLSET){
        return (HLSET?VHVPH:VHVPL);
    }
    inline double VHVN(bool HLSET){
        return (HLSET?VHVNH:VHVNL);
    }
};
