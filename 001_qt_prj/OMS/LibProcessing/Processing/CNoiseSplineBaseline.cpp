//#include "StdAfx.h"
#include "CNoiseSplineBaseline.h"
//#include <algorithm>
using namespace LCTR;
//CNoiseSplineBaseline::CNoiseSplineBaseline(void)
//{
    //mMathLCTR=nullptr;
//};


/// <summary>
/// Filter profile data.  Uses peak detection to calculate threshold.
/// </summary>
/// <param name="dAbsc"></param>
/// <param name="dOrd"></param>
/// <returns>Threshold array.</returns>
vector<double> CNoiseSplineBaseline::Baseline(vector<double>const& dAbsc, vector<double>const& dOrd, double Limit)
{
	vector<double>Output;
	vector<double> dpkAbsc, dpkOrd;
	PeakDetect(dAbsc, dOrd, dpkAbsc, dpkOrd);
	vector<double> dThreshold(FindThreshold(dpkAbsc, dpkOrd, dAbsc, dOrd, 0/*Interpolate for profile*/, Limit));
	int N = dAbsc.Length;
	Output.resize(N,0);
    if(dThreshold.size()!=0)
        InterpolateThreshold(dAbsc, dAbsc[0], dAbsc[dAbsc.Length - 1], Output,
            *min_element(dThreshold.begin(),dThreshold.end()), dpkAbsc, dThreshold);
	return Output;
}

/// <summary>
/// Filter profile data using just start, end and intervals for abscissa.
/// </summary>
/// <param name="dStartAbsc">Starting point for abscissa.</param>
/// <param name="dEndAbsc">Ending point for abscissa.</param>
/// <param name="dIntAbsc">Incremental interval of abscissa.</param>
/// <param name="dOrd">Array of ordinate values.</param>
/// <returns>Double array of filter ordinates.</returns>
vector<double> CNoiseSplineBaseline::Baseline(double dStartAbsc, double dEndAbsc, double dIntAbsc,vector<double>const& dOrd, 
	double Limit)
{
	vector<double> dpkAbsc, dpkOrd;
	PeakDetect(dStartAbsc, dEndAbsc, dIntAbsc, dOrd, dpkAbsc, dpkOrd);
	vector<double> dThreshold(FindThreshold(dpkAbsc, dpkOrd, dStartAbsc, dEndAbsc, dIntAbsc, dOrd,0, Limit));
	return dThreshold;
}

/// <summary>
/// Filter centroided data.
/// </summary>
/// <param name="dMass">Profile masses.</param>
/// <param name="dInts">Profile intensities.</param>
/// <param name="dCMass">Centroided masses.</param>
/// <param name="dCInts">Centroided intensities.</param>
/// <param name="dPMass">Peak masses. [out]</param>
/// <param name="dPInts">Peak intensities. [out]</param>
/// <param name="iStart">Peak start index within profile data. [out]</param>
/// <param name="iEnd">Peak end index within profile data. [out]</param>
/// <returns>Threshold values at centroided masses.</returns>
vector<double> CNoiseSplineBaseline::BaselineC(vector<double>const& dAbsc,vector<double>const& dOrd,vector<double>const& dCAbsc,
	vector<double>const& dCOrd,vector<int>const& iCStart,vector<int>const& iCEnd,
	vector<double>& dPAbsc,vector<double>& dPOrd,vector<int>& iStart,vector<int>& iEnd, double Limit)
{
	// Filter centroided data.
	vector<double> dThreshold(FindThreshold(dCAbsc, dCOrd, dAbsc, dOrd, 1/*Threshold for centroids*/, Limit));
	int iNumPeaks = 0;
	int iN = dCAbsc.Length;
    for (int i = 0; i < iN; ++i){// run through data and sift out signal from nosie.
        if (dCOrd[i] > dThreshold[i]){// IsSignal
			++iNumPeaks;
		}
	}
	dPAbsc.resize(iNumPeaks,0);
	dPOrd.resize(iNumPeaks,0);
	iStart.resize(iNumPeaks,0);
	iEnd.resize(iNumPeaks,0);
	int j = 0;
    for (int i = 0; i < iN; ++i){
        if (dCOrd[i] > dThreshold[i]){
			dPAbsc[j] = dCAbsc[i];
			dPOrd[j] = dCOrd[i];
			iStart[j] = iCStart[i];
			iEnd[j++] = iCEnd[i];
		}
	}
	return dThreshold;
}

vector<double> CNoiseSplineBaseline::BaselineC(double dStartAbsc,double dEndAbsc,double dIntAbsc,vector<double>const& dOrd,
	vector<double>const& dCAbsc,vector<double>const& dCOrd,vector<int>const& iCStart,vector<int>const& iCEnd,
	vector<double>& dPAbsc,vector<double>& dPOrd,vector<int>& iStart,vector<int>& iEnd, double Limit)
{
	// Filter centroided data.
	vector<double> dThreshold(FindThreshold(dCAbsc, dCOrd, dStartAbsc, dEndAbsc, dIntAbsc, dOrd, 1, Limit));
	int iNumPeaks = 0;
    for (int i = 0; i < (int)dCAbsc.Length; ++i){// run through data and sift out signal from nosie.
        if (dCOrd[i] > dThreshold[i]){// IsSignal
			++iNumPeaks;
		}
	}
	dPAbsc.resize(iNumPeaks,0);
	dPOrd.resize(iNumPeaks,0);
	iStart.resize(iNumPeaks,0);
	iEnd.resize(iNumPeaks,0);
	int j = 0;
    for (int i = 0; i < (int)dCAbsc.Length; ++i){
        if (dCOrd[i] > dThreshold[i]){
			dPAbsc[j] = dCAbsc[i];
			dPOrd[j] = dCOrd[i];
			iStart[j] = iCStart[i];
			iEnd[j++] = iCEnd[i];
		}
	}
	return dThreshold;
}

//#pragma region Threshold

/// <summary>
/// Calculate threshold.
/// </summary>
/// <param name="dCMass">Double array of centroided masses.</param>
/// <param name="dCInts">Double array of centroided intensities.</param>
/// <param name="dPMass">Double array of profile masses.</param>
/// <param name="dPInts">Double array of profile intensities.</param>
/// <param name="InterpolateFlag">0: Interpolate for centroids, 1: interpolate for profile.</param>
/// <returns>Returns values of threshold interpolated at the same points as the centroided peaks.</returns>
vector<double> CNoiseSplineBaseline::FindThreshold(vector<double>const& dCAbsc,vector<double>const& dCOrd,vector<double>const& dPAbsc,
	vector<double>const& dPOrd, int InterpolateFlag, double Lim)
{
	double dStartAbsc = dPAbsc[0];
	double dEndAbsc = dPAbsc[dPAbsc.Length - 1];
	vector<double> dthreshold(dCAbsc.Length);
	double dsThresh = 0;
	int iNC = dCAbsc.Length;
	const int iIdealSize = 500;
    if ((!dCAbsc.empty()) && iNC > 0) {// precaution//change strategy depending on how complicated the data is
		if (iNC < 100)
			dsThresh = *max_element(dCOrd.begin(),dCOrd.end()) * 0.01;
		else
			dsThresh = CalculateMinimumThreshold(iNC, dCOrd, iIdealSize, Lim);
		double dInc = (dEndAbsc - dStartAbsc) / (iIdealSize - 1);
		double dWindow = dStartAbsc + dInc;
		vector<double> dThreshAbsc(iIdealSize - 1,0);
		vector<double> dThreshOrd(iIdealSize - 1,0);
		CalculateVariableThreshold(dPAbsc, dPOrd, dEndAbsc, dsThresh, dInc, dWindow, dThreshAbsc, dThreshOrd);
        switch (InterpolateFlag){
		case 0:
			InterpolateThreshold(dCAbsc, dStartAbsc, dEndAbsc,dthreshold,
				dsThresh, dThreshAbsc, dThreshOrd);
			break;
		case 1:
			InterpolateThreshold(dPAbsc, dStartAbsc, dEndAbsc,dthreshold,
				dsThresh, dThreshAbsc, dThreshOrd);
			break;
		}
	}
	return dthreshold;
}

vector<double> CNoiseSplineBaseline::FindThreshold(vector<double>const& dCAbsc,vector<double>const& dCOrd, double dStartAbsc,
	double dEndAbsc, double dIntAbsc,vector<double>const& dPOrd, int InterpolateFlag, double Lim)
{
	int iNC = dCOrd.Length;
	double dsThresh = 0;
	vector<double> dthreshold;
	const int iIdealSize = 500;
    if (!dCOrd.empty() && iNC > 0) {// precaution//change strategy depending on how complicated the data is
        if (iNC < 100){
			dsThresh = *max_element(dCOrd.begin(),dCOrd.end()) * 0.01;
        }else{
			dsThresh = CalculateMinimumThreshold(iNC, dCOrd, iIdealSize, Lim);
		}
		double dInc = (dEndAbsc - dStartAbsc) / (iIdealSize - 1);
		double dWindow = dStartAbsc + dInc;
		vector<double> dThreshAbsc(iIdealSize - 1,0);
		vector<double> dThreshOrd(iIdealSize - 1,0);
		CalculateVariableThreshold(dStartAbsc, dEndAbsc, dIntAbsc, dPOrd, dsThresh, dInc, dWindow,
			dThreshAbsc, dThreshOrd);
        switch (InterpolateFlag){
		case 0:
			dthreshold.resize(iNC);
			InterpolateThreshold(dCAbsc, dStartAbsc, dEndAbsc, dthreshold,
				dsThresh, dThreshAbsc, dThreshOrd);
			break;
		case 1:
			dthreshold.resize(dPOrd.Length);
			InterpolateThreshold(dStartAbsc, dEndAbsc, dIntAbsc, dthreshold,
				dsThresh, dThreshAbsc, dThreshOrd);
			break;
		}
	}
	return dthreshold;
}

double CNoiseSplineBaseline::CalculateMinimumThreshold(int Length1,vector<double>const& dInts, int iIdealSize, double Lim)
{
	double dSThresh = Lim;
    if (Length1 < 100){
		dSThresh =*max_element(dInts.begin(),dInts.end())* 0.01;
    }else{
		vector<double> u;
		vector<int> n;
        mMathLCTR.Unique(dInts, u, n);
		int numLimit = Length1 / 10;
        if (*max_element(n.begin(),n.end()) > (numLimit)){
            for (int i = 0; i < (int)n.Length; ++i){
                if (n[i] > numLimit){
                    dSThresh =Mymax(dSThresh, u[i]);
				}
			}
        }else{
			double one = 1;
			double hundred = 100;
            double dPrc =Mymax((one - (double)iIdealSize / (double)Length1) * hundred, 0);
            dSThresh = mMathLCTR.Prctile(dInts, dPrc);
		}
	}
	return dSThresh;
}

//#pragma region Calculate Variable Threshold
void CNoiseSplineBaseline::CalculateVariableThreshold(double dStartAbsc, double dEndAbsc, double dIntAbsc,
	vector<double>const& arrOrd, double dSThresh, double dInc, double dWindow,vector<double>& dThreshAbsc,
	vector<double>& dThreshOrd)
{
	int iIndex = 0, iLastIndex = 0, k = 0, iN = arrOrd.Length;
    while (dWindow <= dEndAbsc){
		bool bStop = false;
        while (!bStop && iIndex < iN){
			if (min(dStartAbsc + iIndex * dIntAbsc, dEndAbsc) > dWindow)
				bStop = true;
			++iIndex;
		}
		double dMeanOrd = 0, dMeanAbsc = 0;
		int iCountElements = 1;
        for (int i = iLastIndex; i < iIndex; ++i){
			dMeanOrd += arrOrd[i];
			dMeanAbsc += min(dStartAbsc + i * dIntAbsc, dEndAbsc);
			++iCountElements;
		}
		dMeanOrd /= (iCountElements);
		dMeanOrd = max(dMeanOrd, dSThresh);
		dMeanAbsc /= (iCountElements);
		dThreshOrd[k] = dMeanOrd;
		dThreshAbsc[k++] = dMeanAbsc;
		iLastIndex = iIndex;
		dWindow += dInc;
	}
}

void CNoiseSplineBaseline::CalculateVariableThreshold(vector<double>const& arrAbsc,vector<double>const& arrOrd, double dEndAbsc,
	double dSThresh,double dInc, double dWindow,vector<double>& dThreshAbsc,vector<double>& dThreshOrd)
{
	int iIndex = 0, iLastIndex = 0, k = 0;
    while (dWindow <= dEndAbsc){
		bool bStop = false;
        while (!bStop && iIndex < (int)arrAbsc.Length){
            if (arrAbsc[iIndex] > dWindow){
				bStop = true;
			}
			++iIndex;
		}
		double dMeanOrd = 0, dMeanAbsc = 0;
		int iCountElements = 1;
        for (int i = iLastIndex; i < iIndex; ++i){
			dMeanOrd += arrOrd[i];
			dMeanAbsc += arrAbsc[i];
			++iCountElements;
		}
		dMeanOrd /= (iCountElements);
		dMeanOrd = max(dMeanOrd, dSThresh);
		dMeanAbsc /= (iCountElements);
		dThreshOrd[k] = dMeanOrd;
		dThreshAbsc[k++] = dMeanAbsc;
		iLastIndex = iIndex;
		dWindow += dInc;
	}
}
//#pragma endregion

//#pragma endregion

//#pragma region Interpolate Threshold

void CNoiseSplineBaseline::InterpolateThreshold(vector<double>const& dAbsc, double dStartAbsc, double dEndAbsc,
	vector<double>& dthreshold, double dSThresh,vector<double>const& dThreshAbsc,vector<double>const& dThreshOrd)
{
	int j = 1;
    for (int x = 0; x < (int)dAbsc.Length - 1; ++x){
		double dItem = dAbsc[x];
		dthreshold[x] = InterpolateThresholdItem(dStartAbsc, dEndAbsc, dSThresh, dThreshAbsc,
			dThreshOrd, j, dItem);
	}
	dthreshold[dthreshold.Length - 1] = dSThresh;
}

void CNoiseSplineBaseline::InterpolateThreshold(double dStartAbsc, double dEndAbsc, double dIncAbsc,
	vector<double>& dthreshold, double dSThresh,vector<double>const& dThreshAbsc,vector<double>const& dThreshOrd)
{
	int j = 0, iCount = dthreshold.Length;
    for (int x = 0; x < iCount - 1; ++x){
		double dItem = min(dStartAbsc + x * dIncAbsc, dEndAbsc);
		dthreshold[x] = InterpolateThresholdItem(dStartAbsc, dEndAbsc, dSThresh, dThreshAbsc,
			dThreshOrd, j, dItem);
	}
	dthreshold[dthreshold.Length - 1] = dSThresh;
}

double CNoiseSplineBaseline::InterpolateThresholdItem(double dStartAbsc, double dEndAbsc, double dSThresh,
	vector<double>const& dThreshAbsc,vector<double>const& dThreshOrd,int& j, double dItem)
{
	double dthreshitem = dSThresh;
	bool bFoundItem = false;
    while (!bFoundItem && j < (int)dThreshAbsc.Length){
        if (dItem < dThreshAbsc[0]){
            // Interpolate between dThreshMass[0] and dStartMass
            dthreshitem = mMathLCTR.LinIntXToY(dStartAbsc, dThreshAbsc[0], dSThresh, dThreshOrd[0], dItem);
			bFoundItem = true;
        }else if (dItem > dThreshAbsc[dThreshAbsc.Length - 1]){
			// Interpolate between dThreshMass[end] and dEndMass
            dthreshitem = mMathLCTR.LinIntXToY(dThreshAbsc[j], dEndAbsc, dThreshOrd[j], dSThresh, dItem);
			bFoundItem = true;
        }else if (dThreshAbsc[j] >= dItem && dThreshAbsc[j - 1] <= dItem){
			// Normal
            dthreshitem = mMathLCTR.LinIntXToY(dThreshAbsc[j - 1], dThreshAbsc[j], dThreshOrd[j - 1], dThreshOrd[j], dItem);
			bFoundItem = true;
		}
        else{
			++j;
		}
	}
	return dthreshitem;
}

//#pragma endregion

//#pragma region Peak Detect
void CNoiseSplineBaseline::PeakDetect(vector<double>const& dAbsc,vector<double>const& dOrd,vector<double>& dpkAbsc,vector<double>& dpkOrd)
{
	int iCounter = 0;
	int iN = dAbsc.Length;
    for (int i = 1; i < iN - 2; ++i){
        if (dOrd[i - 1] < dOrd[i] && dOrd[i] > dOrd[i + 1]){
			++iCounter;
		}
	}
	dpkAbsc.resize(iCounter,0);
	dpkOrd.resize(iCounter,0);
	iCounter = 0;
    for (int i = 1; i < iN - 2; ++i){
        if (dOrd[i - 1] < dOrd[i] && dOrd[i] > dOrd[i + 1]){
			dpkAbsc[iCounter] = dAbsc[i];
			dpkOrd[iCounter++] = dOrd[i];
		}
	}
}

void CNoiseSplineBaseline::PeakDetect(double dStartAbsc, double dEndAbsc, double dIntAbsc,vector<double>const& dOrd,
	vector<double>& dpkAbsc,vector<double>& dpkOrd)
{
	int iCounter = 0, iN = dOrd.Length;
    for (int i = 1; i < iN - 2; ++i){
        if (dOrd[i - 1] < dOrd[i] && dOrd[i] > dOrd[i + 1]){
			++iCounter;
		}
	}
	dpkAbsc.resize(iCounter,0);
	dpkOrd.resize(iCounter,0);
	int j = 0;
    for (int i = 1; i < iN - 2; ++i){
        if (dOrd[i - 1] < dOrd[i] && dOrd[i] > dOrd[i + 1]){
			dpkAbsc[j] = min(dStartAbsc + i * dIntAbsc, dEndAbsc);
			dpkOrd[j++] = dOrd[i];
		}
	}
}
//#pragma endregion
