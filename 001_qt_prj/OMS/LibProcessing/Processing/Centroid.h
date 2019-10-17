#pragma once
#include "../Maths/cMathLCTR.h"
#include<vector>
#include "../Maths/structLCTR.h"
#include "../Maths/cMathLCTR.h"
#include "../Maths/MatrixNumeric.h"
#include "../MiscUtilities/RegistryHandler.h"
using namespace LCTR;
class CCentroid
{
public:
	CCentroid(void){}
private:
    cMathLCTR mMathLCTR;
	CMatrixNumeric mCurveFit;
	CRegistryHandler mRegistryHandler;
    std::vector<double>mTmpCX;
    std::vector<double>mTmpCY;
    std::vector<int>mTmpStart;
    std::vector<int>mTmpEnd;
    std::vector<double>mTmpCoord;
    std::vector<double>mArrdDiffs;

    std::vector<double>mCopydAbsc;
    std::vector<double>mCopydOrd;
    std::vector<double>mCopyTmpCoord;
    std::vector<double>mCopyTmpCY;

    std::vector<double>mCopyStart;
    std::vector<double>mCopyEnd;
public:
	/// <summary>
	/// Traditional way using local maxima as peaks
	/// </summary>
	/// <param name="dAbsc">x values</param>
	/// <param name="dOrd">y values</param>
	/// <param name="cAbsc">x values at centroids</param>
	/// <param name="cOrd">y values at centroids</param>
	/// <param name="iStart">start of centroids</param>
	/// <param name="iEnd">corresponding ends of centroids</param>
    double CentroidData(vector<double>const& dAbsc,vector<double>const& dOrd,vector<double>& cAbsc,
        vector<double>& cOrd,vector<int>& iStart,vector<int>& iEnd,int width){
            return CentroidDataA(dAbsc, dOrd,cAbsc,cOrd,iStart,iEnd,width);
        }
	/// <summary>
	/// Traditional way using local maxima as peaks but with start and stop rather than range for x axis
	/// </summary>
	/// <param name="dStartAbsc">start x real value</param>
	/// <param name="dEndAbsc">end x real value</param>
	/// <param name="dIncAbsc">x increments between start and end</param>
	/// <param name="dOrd">y values</param>
	/// <param name="cAbsc">x values at centroids</param>
	/// <param name="cOrd">y values at centroids</param>
	/// <param name="iStart">start of centroids</param>
	/// <param name="iEnd">corresponding ends of centroids</param>
	void CentroidData(double dStartAbsc, double dEndAbsc, double dIncAbsc,vector<double> dOrd,vector<double>& cAbsc,
        vector<double>& cOrd,vector<int>& iStart,vector<int>& iEnd,int width){
        vector<double> dAbsc = GetAbsc(dStartAbsc, dEndAbsc, dIncAbsc, dOrd.Length);
        double dTmp = CentroidDataA(dAbsc, dOrd, cAbsc, cOrd, iStart, iEnd,width);
        dTmp=dTmp;
    }
	/// <summary>
	/// Traditional way using local maxima as peaks but calc area as well with start and stop rather than range for x axis
	/// </summary>
	/// <param name="dStartAbsc">start x real value</param>
	/// <param name="dEndAbsc">end x real value</param>
	/// <param name="dIncAbsc">x increments between start and end</param>
	/// <param name="dOrd">y values</param>
	/// <param name="cAbsc">x values at centroids</param>
	/// <param name="cOrd">y values at centroids</param>
	/// <param name="iStart">start of centroids</param>
	/// <param name="iEnd">corresponding ends of centroids</param>
	/// <returns>Cumulative area of all defined centroids (between starts and ends)</returns>
	double CentroidDataA(double dStartAbsc, double dEndAbsc, double dIncAbsc,vector<double> dOrd,vector<double>& cAbsc,
        vector<double>& cOrd,vector<int>& iStart,vector<int>& iEnd,int width){
        vector<double> dAbsc = GetAbsc(dStartAbsc, dEndAbsc, dIncAbsc, dOrd.Length);
        double dArea = CentroidDataA(dAbsc, dOrd, cAbsc, cOrd, iStart, iEnd,width);
        return dArea;}
	/// <summary>
	/// Traditional way using local maxima as peaks but calc area as well
	/// </summary>
	/// <param name="dAbsc">x values</param>
	/// <param name="dOrd">y values</param>
	/// <param name="cAbsc">x values at centroids</param>
	/// <param name="cOrd">y values at centroids</param>
	/// <param name="iStart">start of centroids</param>
	/// <param name="iEnd">corresponding ends of centroids</param>
	/// <returns>Cumulative area of all defined centroids (between starts and ends)</returns>
    double CentroidDataA(vector<double>const& dAbsc,vector<double>const& dOrd,vector<double>& cAbsc,vector<double>& cOrd,
        vector<int>& iStart,vector<int>& iEnd,int width);
private: 
	/// <summary>
	/// Get array of values from start, stop values & increment
	/// </summary>
	/// <param name="dStartAbsc">Start x</param>
	/// <param name="dEndAbsc">Stop x</param>
	/// <param name="dIncAbsc">X Increment</param>
	/// <param name="iL">Length of array</param>
	/// <returns>x values in array</returns>
	vector<double> GetAbsc(double dStartAbsc, double dEndAbsc, double dIncAbsc, int iL);
    bool SetCentroidValues(double* tmpCX, double* tmpCY, int* tmpStart,int* tmpEnd,
        double& dDenominator,double& dNumerator,int& istart,int& iend,int& iV,double& dPeakInt,double& dPeakCoord,
                           double* tmpCoord,int& cIndex,int width);
    bool SetCentroidValues1(double* tmpCY,int& istart,int& iend,int& iV,double& dPeakInt,double& dPeakCoord,
                           double* tmpCoord,int& cIndex,int width);
    static void SetIndices(vector<double>const& dAbsc,vector<double>const& dOrd,
                                      int SearchIndex,  double const* arrdDiffs, int& istart,
               int& iend, int& iV, double& dPeakInt,double& dPeakCoord);
public:
	/// <summary>
	/// wrapper method - determines which method to use to get centroids
	/// </summary>
	/// <param name="dAbsc">x values</param>
	/// <param name="dOrdY">y values</param>
	/// <param name="darrBaseline">baseline signal</param>
	/// <param name="cAbsc">x values at centroid peaks</param>
	/// <param name="cOrd">y values at centroid peaks</param>
	/// <param name="iarrStart">peak starts</param>
	/// <param name="iarrEnd">corresponding peak stops</param>
	void /*null*/CentroidData(vector<double> dAbsc,vector<double> dOrdY,vector<double> darrBaseline,vector<double>& cAbsc,
		vector<double>& cOrd,vector<int>& iarrStart, vector<int>& iarrEnd);
	void CopyArrays(vector<double>& cAbsc, vector<double>& cOrd, vector<int>& iStart, vector<int>& iEnd,
		vector<double>& tmpCX,vector<double>& tmpCY, vector<int>& tmpStart, vector<int>& tmpEnd, int& cIndex);
	/// <summary>
	/// Gradient peak detection method, where signal's derivative used to detect peaks and calc FWHM
	/// Modified method based on that of T. C. O'Haver, 1995.  Version 2  Last revised Oct 27, 2006 (TOH method in MATLAB)
	/// </summary>
	/// <param name="dAbsc">x values</param>
	/// <param name="dOrdY">y values</param>
	/// <param name="cAbsc">x values at centroid peaks</param>
	/// <param name="cOrd">y values at centroid peaks</param>
	/// <param name="iarrStart">peak starts</param>
	/// <param name="iarrEnd">corresponding peak stops</param>
	void /*null*/CentroidDataGradient(vector<double> dAbsc,vector<double> dOrd,vector<double>& cAbsc,vector<double>& cOrd,
		vector<int>& iarrStart,
		vector<int>& iarrEnd);
    
private:
	/// <summary>
	/// Calc centroid from x, y data between x limits
	/// </summary>
	/// <param name="dAbsc">x values</param>
	/// <param name="dOrd">y values</param>
	/// <param name="iStart">start index</param>
	/// <param name="iStop">stop index</param>
	/// <returns></returns>
	double CalcCentroid(vector<double> dAbsc, vector<double> dOrd, int iStart, int iStop);
	/// <summary>
	/// Get points to fit curve to at apex of peak
	/// </summary>
	/// <param name="dAbsc">x values</param>
	/// <param name="dOrd">y values</param>
	/// <param name="iW">Peak width</param>
	/// <param name="iStart">Start index of peak</param>
	/// <param name="iStop">Stop index of peak</param>
	/// <param name="iApex">Index at apex of peak</param>
	/// <param name="bFlatTop">True if top of peak is malformed (flat-topped)</param>
	/// <param name="iFRStart">Start index of flat top region (if flat-topped)</param>
	/// <param name="iFlatRun">Length of flat top region (if flat-topped)</param>
	/// <param name="darrX">Curve fit x data</param>
	/// <param name="darrY">Curve fit y data</param>
	/// <returns>True if successful in gathering suitable points for curve fitting, false otherwise</returns>
    bool GetCurveFitData(vector<double> dAbsc, vector<double> dOrd, int iW, int iStart, int iStop, int iApex, bool bFlatTop,
		int iFRStart, int iFlatRun, vector<double>& darrX, vector<double>& darrY);
	/// <summary>
	/// Processed apex where shape is malformed as flat-topped region
	/// </summary>
	/// <param name="dAbsc">x values</param>
	/// <param name="dOrd">y values</param>
	/// <param name="iW">Peak width</param>
	/// <param name="iStart">Start index of peak</param>
	/// <param name="iStop">Stop index of peak</param>
	/// <param name="iApex">Index at apex of peak</param>
	/// <param name="iFRStart">Start index of flat top region (if flat-topped)</param>
	/// <param name="iFlatRun">Length of flat top region (if flat-topped)</param>
	/// <param name="darrX">Curve fit x data</param>
	/// <param name="darrY">Curve fit y data</param>
	/// <returns>True if successful in gathering suitable points for curve fitting, false otherwise</returns>
	bool ProcessFlatTopData(vector<double> dAbsc, vector<double> dOrd, int iW, int iStart, int iStop, int iApex, int iFRStart,
		int iFlatRun, vector<double>& darrX, vector<double>& darrY);
	/// <summary>
	/// Gathers data for curve fit
	/// </summary>
	/// <param name="dAbsc">x values</param>
	/// <param name="dOrd">y values</param>
	/// <param name="iW">Peak width</param>
	/// <param name="iStart">Start index of peak</param>
	/// <param name="iStop">Stop index of peak</param>
	/// <param name="iApex">Index at apex of peak</param>
	/// <param name="iFRStart">Start index of flat top region (if flat-topped)</param>
	/// <param name="iFlatRun">Length of flat top region (if flat-topped)</param>
	/// <param name="darrX">Curve fit x data</param>
	/// <param name="darrY">Curve fit y data</param>
    void ProcessStandardData(vector<double> dAbsc, vector<double> dOrd, int iW, int iStart, int iStop, int iApex, int iFRStart,
		int iFlatRun, vector<double>& darrX, vector<double>& darrY);
	/// <summary>
	/// Calcs differences between y values
	/// </summary>
	/// <param name="dOrd">y values</param>
	/// <returns>Differences</returns>
    vector<double> GetDiffs(vector<double> dOrd);
	/// <summary>
	/// First derivative of vector using 2-point central difference.
	/// Example: deriv([1 1 1 2 3 4]) yeilds [0 0 .5 1 1 1]
	/// T. C. O'Haver, 1988. original in MATLAB
	/// </summary>
	/// <param name="dOrd">y values</param>
	/// <returns>first derivative of y values</returns>
    vector<double> GetDeriv(vector<double> dOrd);
	/// <summary>
	/// fastsmooth(Y,w) smooths vector Y by triangular
	/// smooth of width = smoothwidth. Works well with signals up to 
	/// 100,000 points in length and smooth widths up to 1000 points. 
	/// Faster than tsmooth for smooth widths above 600 points.
	/// Example: fastsmooth([0 0 0 0 9 0 0 0 0],3) yields [0 0 1 2 3 2 1 0 0]
	/// T. C. O'Haver, 2006. original in MATLAB
	/// </summary>
	/// <param name="Y">y values</param>
	/// <param name="w">smoothing width applied to differential - the greater, the less sensitive is the peak detection</param>
	/// <returns></returns>
    vector<double> SmoothDifferential(vector<double> Y, int w);
	/// <summary>
	/// Finds percentage differences between adjacent y values
	/// </summary>
	/// <param name="dOrd">y values</param>
	/// <param name="arrdDiffs">Calculated perc differences</param>
    void FindPercDiffs(vector<double>const& dOrd, double* arrdDiffs);
public:
	/// <summary>
	/// threshold peak detection method where signal rises over/below threshold to dilineate peak
	/// </summary>
	/// <param name="dAbsc">x values</param>
	/// <param name="dOrdY">y values</param>
	/// <param name="darrBaseline">baseline signal</param>
	/// <param name="cAbsc">x values at centroid peaks</param>
	/// <param name="cOrd">y values at centroid peaks</param>
	/// <param name="iarrStart">peak starts</param>
	/// <param name="iarrEnd">corresponding peak stops</param>
    void /*null*/CentroidDataThreshold(vector<double> dAbsc, vector<double> dOrd, vector<double> darrBaseline,
		vector<double>& cAbsc,vector<double>& cOrd,vector<int>& iarrStart, vector<int>& iarrEnd);
	/// <summary>
	/// current - uses real X values & widths
	/// </summary>
	/// <param name="darrX">x values</param>
	/// <param name="CX">x values of centroids</param>
	/// <param name="CY">y values of centroids</param>
	/// <param name="Start">start indices of centroids</param>
	/// <param name="End">end indices of centroids</param>
	/// <param name="strUnits">units of x axis</param>
	/// <param name="FCX">x values of centroids that pass filter</param>
	/// <param name="FCY">y values of centroids that pass filter</param>
	/// <param name="FStart">start indices of centroids that pass filter</param>
	/// <param name="FEnd">end indices of centroids that pass filter</param>
    //void /*null*/FilterCentroids(vector<double> darrX, vector<double> CX, vector<double> CY, vector<int> Start, vector<int> End,
    //	string strUnits, vector<double>& FCX, vector<double>& FCY, vector<int>& FStart, vector<int>& FEnd){
    //    double XlimMin = darrX[0];double XlimMax = darrX[darrX.Length - 1];
    //    FilterCentroids(darrX, CX, CY, Start, End, XlimMin, XlimMax, strUnits,FCX,FCY,FStart,FEnd);}
	/// <summary>
	/// also current - uses real X values & widths but for limited X range
	/// </summary>
	/// <param name="darrX">x values</param>
	/// <param name="CX">x values of centroids</param>
	/// <param name="CY">y values of centroids</param>
	/// <param name="Start">start indices of centroids</param>
	/// <param name="End">end indices of centroids</param>
	/// <param name="XlimMin">real x min value</param>
	/// <param name="XlimMax">real x max value</param>
	/// <param name="strUnits">units of x axis</param>
	/// <param name="FCX">x values of centroids that pass filter</param>
	/// <param name="FCY">y values of centroids that pass filter</param>
	/// <param name="FStart">start indices of centroids that pass filter</param>
	/// <param name="FEnd">end indices of centroids that pass filter</param>
    //void /*null*/FilterCentroids(vector<double> darrX, vector<double> CX, vector<double> CY, vector<int> Start, vector<int> End,
    //	double XlimMin, double XlimMax,string strUnits,vector<double>& FCX, vector<double>& FCY, vector<int>& FStart,
    //	vector<int>& FEnd);
    
private:
	int /*null*/GetRegCentroidQuota();
    bool /*null*/GetRegCentroidApplyQuota();
	/// <summary>
	/// current filter criteria
	/// </summary>
	/// <param name="dInt">peak intensity</param>
	/// <param name="dStart">start x value (of centroid)</param>
	/// <param name="dStop">end x value (of centroid)</param>
	/// <param name="dHeightMin">Min allowable y value</param>
	/// <param name="dHeightMax">Max allowable y value</param>
	/// <param name="dWidthMin">Min allowable centroid width</param>
	/// <param name="dWidthMax">Max allowable centroid width</param>
	/// <returns></returns>
    bool CentroidPassFilter(double dInt, double dStart, double dStop, double dHeightMin, double dHeightMax,
		double dWidthMin,double dWidthMax);
    
public:
	/// <summary>
	/// old - does not use real X values, only integers when applying width filter
	/// </summary>
	/// <param name="CX">x values of centroids</param>
	/// <param name="CY">y values of centroids</param>
	/// <param name="Start">start indices of centroids</param>
	/// <param name="End">end indices of centroids</param>
	/// <param name="FCX">x values of centroids that pass filter</param>
	/// <param name="FCY">y values of centroids that pass filter</param>
	/// <param name="FStart">start indices of centroids that pass filter</param>
	/// <param name="FEnd">end indices of centroids that pass filter</param>
	void /*null*/FilterCentroids(vector<double> CX, vector<double> CY, vector<int> Start, vector<int> End, 
		vector<double>& FCX, vector<double>& FCY, vector<int>& FStart, vector<int>& FEnd);
	/// <summary>
	/// old - does not use real X values, only integers but for limited X range
	/// </summary>
	/// <param name="darrX">x values</param>
	/// <param name="CX">x values of centroids</param>
	/// <param name="CY">y values of centroids</param>
	/// <param name="Start">start indices of centroids</param>
	/// <param name="End">end indices of centroids</param>
	/// <param name="XlimMin">real x min value</param>
	/// <param name="XlimMax">real x max value</param>
	/// <param name="FCX">x values of centroids that pass filter</param>
	/// <param name="FCY">y values of centroids that pass filter</param>
	/// <param name="FStart">start indices of centroids that pass filter</param>
	/// <param name="FEnd">end indices of centroids that pass filter</param>
    void /*null*/FilterCentroids(vector<double> CX, vector<double> CY, vector<int> Start, vector<int> End, double XlimMin,
		double XlimMax,vector<double>& FCX, vector<double>& FCY, vector<int>& FStart, vector<int>& FEnd);
    
private:
    //double /*null*/GetRegCentroidWidth(string strUnits);
    //double /*null*/GetRegCentroidWidthMax(string strUnits);
    int /*null*/GetRegCentroidWidth();
    int /*null*/GetRegCentroidWidthMax();
    //string /*null*/GetCentroidMethod();
    bool /*null*/GetUseBaselineChoice();
    double /*null*/GetRegCentroidHeight();
    double /*null*/GetRegCentroidHeightMax();
    int /*null*/GetRegGradSmooth();
    double /*null*/GetUserThreshold();
};

//class CentroidPeak : IComparable
//{
//public:
//	double mdX, mdY;
//    int miStart, miEnd;
//	CentroidPeak(double dX, double dY, int iStart, int iEnd)
//        {
//            mdX = dX;
//            mdY = dY;
//            miStart = iStart;
//            miEnd = iEnd;
//        }
//	int CompareTo(object o)
//        {
//            CentroidPeak cp = (CentroidPeak)o;
//            return mdY.CompareTo(cp.mdY);
//        }
//	void UpdateArray(vector<double>& dX, vector<double>& dY, ref vector<int> iStart, vector<int>& iEnd, int iInd)
//        {
//            dX[iInd] = mdX;
//            dY[iInd] = mdY;
//            iStart[iInd] = miStart;
//            iEnd[iInd] = miEnd;
//        }
//}
