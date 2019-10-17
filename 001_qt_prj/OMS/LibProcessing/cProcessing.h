#ifndef CPROCESSING_H
#define CPROCESSING_H
#define QT_GICAP
#include "Processing/CSmoothingFilter.h"
#include "Processing/CSignalArea.h"
#include "Processing/CNoiseSplineBaseline.h"
#include "Processing/Centroid.h"
#include "Processing/CFWHM.h"
#ifdef QT_GICAP
#include <QByteArray>
#include <share/sdata.h>
#endif
class  SignalProcessing
{
public:
    SignalProcessing(void){}
    ~SignalProcessing(){}

private:
    HighFrequencyFilter mHighFrequencyFilter;
    MovingAverageFilter mMovingAverageFilterServices;
    WeightedMovingAverageFilter mWeightedMovingAverageFilterServices;
    SavitzkyGolayFilter mSGFilterServices;
public:
    vector<double> HighFrequencySmooth(vector<double> data,double baseLine,int nPointFilter){
        return mHighFrequencyFilter.Filter(data,baseLine,nPointFilter);}
    vector<double> MovingAverageSmooth(vector<double>& data, int width){
        return mMovingAverageFilterServices.Filter(data, width);}
    vector<double> WeightedMovingAverageSmooth(vector<double>& data, int width){
        return mWeightedMovingAverageFilterServices.Filter(data, width);}
    vector<double> SavGolFilt(vector<double>& Val, int K, int F){
        return mSGFilterServices.Filter(Val, K, F);}

private:
    CCentroid mCentroidServices;
public:
    double CentroidData(vector<double>const& arrAbsc, vector<double>const& arrOrd,
                      vector<double>& dAbsc,vector<double>& dOrd, vector<int>& iStart, vector<int>& iEnd,int width){
        if (*max_element(arrAbsc.begin(),arrAbsc.end()) > 0)
            return mCentroidServices.CentroidData(arrAbsc, arrOrd, dAbsc, dOrd, iStart, iEnd, width);
        return -1;
    }

    void CentroidData(double dStartAbsc, double dEndAbsc, double dIncAbsc,vector<double> dOrd,vector<double>& cAbsc,
                      vector<double>& cOrd, vector<int>& iStart, vector<int>& iEnd,int width){
        if (dStartAbsc < dEndAbsc)
            mCentroidServices.CentroidData(dStartAbsc, dEndAbsc, dIncAbsc, dOrd, cAbsc, cOrd, iStart, iEnd, width);}

    /*void CentroidDataThreshold(vector<double> dAbsc, vector<double> dOrd, vector<double> darrBaseline, vector<double>& cAbsc,
        vector<double>& cOrd, vector<int>& iarrStart, vector<int>& iarrEnd){
        if (*max_element(dAbsc.begin(),dAbsc.end())> 0)
            mCentroidServices.CentroidDataThreshold(dAbsc, dOrd, darrBaseline, cAbsc, cOrd, iarrStart, iarrEnd);}*/

    /*void CentroidData(vector<double> dAbsc, vector<double> dOrd, vector<double> darrBaseline, vector<double>& cAbsc,
        vector<double>& cOrd, vector<int>& iarrStart, vector<int>& iarrEnd){
        if (*max_element(dAbsc.begin(),dAbsc.end()) > 0)
            mCentroidServices.CentroidData(dAbsc, dOrd, darrBaseline, cAbsc, cOrd, iarrStart, iarrEnd);}*/

    double CentroidDataA(vector<double> arrAbsc, vector<double> arrOrd,
                         vector<double>& dAbsc, vector<double>& dOrd, vector<int>& iStart, vector<int>& iEnd,int width){
        double dOut =0;
        if (*max_element(arrAbsc.begin(),arrAbsc.end()) > 0)
            dOut = mCentroidServices.CentroidDataA(arrAbsc, arrOrd, dAbsc, dOrd, iStart, iEnd,width);
        return dOut;}

    /*void FilterCentroids(vector<double> CX, vector<double> CY, vector<int> Start, vector<int> End,
        vector<double>& FCX, vector<double>& FCY, vector<int>& FStart, vector<int>& FEnd){
        mCentroidServices.FilterCentroids(CX, CY, Start, End, FCX, FCY, FStart, FEnd);}

    void FilterCentroids(vector<double> darrX, vector<double> CX, vector<double> CY, vector<int> Start, vector<int> End,
        string strUnits, vector<double>& FCX, vector<double>& FCY, vector<int>& FStart, vector<int>& FEnd){
        mCentroidServices.FilterCentroids(darrX, CX, CY, Start, End, strUnits, FCX, FCY, FStart, FEnd);}

    void FilterCentroids(vector<double> CX, vector<double> CY, vector<int> Start, vector<int> End, double XlimMin, double XlimMax,
        vector<double>& FCX, vector<double>& FCY, vector<int>& FStart, vector<int>& FEnd){
        mCentroidServices.FilterCentroids(CX, CY, Start, End, XlimMin, XlimMax, FCX, FCY, FStart, FEnd);}

    void FilterCentroids(vector<double> darrX, vector<double> CX, vector<double> CY, vector<int> Start, vector<int> End, double XlimMin,
        double XlimMax, string strUnits, vector<double>& FCX, vector<double>& FCY, vector<int>& FStart, vector<int>& FEnd){
        mCentroidServices.FilterCentroids(darrX, CX, CY, Start, End, XlimMin, XlimMax, strUnits, FCX, FCY, FStart, FEnd);}
*/

private:
    CNoiseSplineBaseline mNoiseSplineBaselineServices;
    //KratosBaselineCorrection mKratosServices;
public:
    vector<double> FilterData(vector<double>const& dAbsc, vector<double>const& dOrd, double Limit){
        return mNoiseSplineBaselineServices.Baseline(dAbsc, dOrd, Limit);}
    /*vector<double> BaselineCorrection(vector<double> rawData, int FilterWidth, vector<int> baselineFilters,vector<int> smoothFilters){
        return mKratosServices.BaselineCorrection(rawData, FilterWidth, baselineFilters, smoothFilters);}
    vector<double> BaselineCorrectionPlus(vector<double> rawData, int FilterWidth, vector<int> baselineFilters, vector<int> smoothFilters){
        return mKratosServices.BaselineCorrectionPlus(rawData, FilterWidth, baselineFilters, smoothFilters);}*/

private:
    CFWHM mFWHMServices;
public:
    vector<double> GetHHFW(vector<double>& dAbsc, vector<double>& dOrd, vector<int>& iStart, vector<int>& iEnd){
        return mFWHMServices.GetFWHM(dAbsc, dOrd, iStart, iEnd);}
    //	vector<double> GetMassResolution(vector<double> dAbsc,vector<double> dOrd,vector<double> dXC,vector<int> iStart,vector<int> iEnd){
    //		return mFWHMServices.GetMassResolution(dAbsc, dOrd, dXC, iStart, iEnd);}

private:
    CSignalArea mSignalAreaServices;
public:
    double SignalArea(vector<double>& dAbsc,vector<double>& dOrd){
        return mSignalAreaServices.SignalArea(dAbsc, dOrd);}
    vector<double> SignalArea(vector<double>& dAbsc,vector<double>& dOrd,vector<int>& Start,vector<int>& End){
        return mSignalAreaServices.SignalArea(dAbsc, dOrd, Start, End);}
    double SignalArea(vector<double>& dAbsc,vector<double>& dOrd, int istart, int iend){
        return mSignalAreaServices.SignalArea(dAbsc, dOrd, istart, iend);}
    double SignalArea(vector<double>& dAbsc,vector<double>& dOrd, double dstart, double dend){
        return mSignalAreaServices.SignalArea(dAbsc, dOrd, dstart, dend);}
    double SignalContourArea(vector<double>& dAbsc,vector<double>& dOrd){
        return mSignalAreaServices.SignalContourArea(dAbsc, dOrd);}

};
#ifdef QT_GICAP
//template <typename T>
//uint convert(const QByteArray& baFrom, std::vector<double>& vecTo){
//    T* pIndex,*pEnd;
//    uint uSize;
//    double* pBuffer;

//    pIndex = (T*)baFrom.data();
//    pEnd = (T*)(baFrom.data() + baFrom.size());
//    uSize = baFrom.size() / sizeof(T);
//    vecTo.resize(uSize);
//    pBuffer = vecTo.data();
//    while (pIndex < pEnd) {
//        *(pBuffer++) = *(pIndex++);
//    }
//    return uSize;
//}
//template <typename T>
//uint VECTtoQBYTEA(QByteArray& baFrom,const std::vector<T>& vecTo){
//    T* pIndex,*pEnd;
//    uint uSize;
//    T* pBuffer;

//    pIndex = (T*)vecTo.data();
//    pEnd = (T*)(vecTo.data() + vecTo.size());
//    uSize = vecTo.size() * sizeof(T);
//    baFrom.resize(uSize);
//    pBuffer = (T*)baFrom.data();
//    while (pIndex < pEnd) {
//        *(pBuffer++) = *(pIndex++);
//    }
//    return uSize;
//}
//template <typename XT, typename YT>
//static uint convert(srls::Data2DLineBaseT* pData2DLineBase,std::vector<double>& pData){
//    srls::Data2DLineT<XT, YT>* pData2DLine = reinterpret_cast<srls::Data2DLineT<XT, YT>*>(pData2DLineBase);
//    YT* pIndex,*pEnd;
//    double* pBuffer;

//    //sig.xBegin = (double)pData2DLine->xBegin;
//    //sig.xEnd = (double)pData2DLine->xEnd;
//    pIndex = &pData2DLine->y[0];
//    pEnd = &pData2DLine->y[0] + pData2DLine->yLength;
//    pData.resize(pData2DLine->yLength);//double
//    pBuffer = pData.data();
//    while (pIndex < pEnd) {
//        *(pBuffer++) = *(pIndex++);
//    }
//    return pData2DLine->yLength;
//}

//template <typename T>
//static bool analyseSignal(srls::Data2DLineBaseT* pData2DLine,std::vector<double>& pData){
//    if(pData2DLine->yVType == srls::VT_DOUBLE){
//        convert<T, double>(pData2DLine, pData);
//    }else if(pData2DLine->yVType == srls::VT_FLOAT){
//        convert<T, float>(pData2DLine, pData);
//    }else if(pData2DLine->yVType == srls::VT_S32){
//        convert<T, int>(pData2DLine, pData);
//    }else if(pData2DLine->yVType == srls::VT_U32){
//        convert<T, uint>(pData2DLine, pData);
//    }else if(pData2DLine->yVType == srls::VT_S16){
//        convert<T, short>(pData2DLine, pData);
//    }else if(pData2DLine->yVType == srls::VT_U16){
//        convert<T, ushort>(pData2DLine, pData);
//    }else if(pData2DLine->yVType == srls::VT_S8){
//        convert<T, char>(pData2DLine, pData);
//    }else if(pData2DLine->yVType == srls::VT_U8){
//        convert<T, uchar>(pData2DLine, pData);
//    }else if(pData2DLine->yVType == srls::VT_BOOL){
//        convert<T, bool>(pData2DLine, pData);
//    }else
//        return false;
//    return true;
//}
//static bool DDT2VECT(QByteArray& baFrom,std::vector<double>& pData,double& xbegin,double& xend){
//    srls::Data2DLineT<double>* pData2DLine;
//    pData2DLine = reinterpret_cast<decltype(pData2DLine)>(  baFrom.data());
//    if(baFrom.size() < (int)sizeof(*pData2DLine)
//            || pData2DLine->type != srls::DT_2D_LINE)
//      return false;
//    xbegin=(double)pData2DLine->xBegin;
//    xend = (double)pData2DLine->xEnd;
//    if(pData2DLine->xVType == srls::VT_DOUBLE){
//        analyseSignal<double>(pData2DLine, pData);
//    }else if(pData2DLine->xVType == srls::VT_FLOAT){
//        analyseSignal<float>(pData2DLine, pData);
//    }else if(pData2DLine->xVType == srls::VT_S32){
//        analyseSignal<int>(pData2DLine, pData);
//    }else if(pData2DLine->xVType == srls::VT_U32){
//        analyseSignal<uint>(pData2DLine, pData);
//    }else if(pData2DLine->xVType == srls::VT_S16){
//        analyseSignal<short>(pData2DLine, pData);
//    }else if(pData2DLine->xVType == srls::VT_U16){
//        analyseSignal<ushort>(pData2DLine, pData);
//    }else if(pData2DLine->xVType == srls::VT_S8){
//        analyseSignal<char>(pData2DLine, pData);
//    }else if(pData2DLine->xVType == srls::VT_U8){
//        analyseSignal<uchar>(pData2DLine, pData);
//    }else if(pData2DLine->xVType == srls::VT_BOOL){
//        analyseSignal<bool>(pData2DLine, pData);
//    }
//    return true;
//}
//static void VECT2DDT(QByteArray& baFrom,const std::vector<double>& pData,const double& xbegin,const double& xend)
//{
//    srls::Data2DLineT<double>* pData2DLine;
//    baFrom.resize(sizeof(*pData2DLine) + pData.size() * sizeof(double));
//    pData2DLine = reinterpret_cast<decltype(pData2DLine)>(baFrom.data());

//    pData2DLine->type = srls::DT_2D_LINE;
//    pData2DLine->xVType = srls::VT_DOUBLE;
//    pData2DLine->xBegin = xbegin;
//    pData2DLine->xEnd = xend;
//    pData2DLine->yVType = srls::VT_DOUBLE;
//    pData2DLine->yLength = pData.size();

//    double* pIndex= (double*)(pData.data());
//    double* pEnd= (double*)(pData.data() + pData.size());;
//    double* pBuffer = &pData2DLine->y[0];

//    while (pIndex < pEnd) {
//        *(pBuffer++) = *(pIndex++);
//    }

//}
//struct ObjectPropT{
//    SObject* obj = NULL;
//    QString name;
//};
#endif
#endif // CPROCESSING_H
