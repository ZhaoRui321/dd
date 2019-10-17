#pragma once
#include "../Maths/cMathLCTR.h"
#include<vector>
#include "../Maths/structLCTR.h"
#include <algorithm>
using namespace std;

class CNoiseSplineBaseline
{
private: 
    cMathLCTR mMathLCTR;
public:
	CNoiseSplineBaseline(void){}
	~CNoiseSplineBaseline(){}
	vector<double> Baseline(vector<double>const& dAbsc, vector<double>const& dOrd, double Limit);

	vector<double> Baseline(double dStartAbsc, double dEndAbsc, double dIntAbsc, vector<double>const& dOrd, double Limit);

	vector<double> BaselineC(vector<double>const& dAbsc, vector<double>const& dOrd, vector<double>const& dCAbsc,
		vector<double>const& dCOrd, vector<int>const& iCStart,vector<int>const& iCEnd,vector<double>& dPAbsc,
		vector<double>& dPOrd,vector<int>& iStart,vector<int>& iEnd,double Limit);

	vector<double> BaselineC(double dStartAbsc, double dEndAbsc, double dIntAbsc,vector<double>const&dOrd,
		vector<double>const& dCAbsc,vector<double>const& dCOrd,vector<int>const& iCStart,vector<int>const& iCEnd,
		vector<double>& dPAbsc,vector<double>& dPOrd,vector<int>& iStart,vector<int>& iEnd, double Limit);

	vector<double> FindThreshold(vector<double>const& dCAbsc,vector<double>const& dCOrd,vector<double>const& dPAbsc,
		vector<double>const& dPOrd,int InterpolateFlag, double Lim);

	vector<double> FindThreshold(vector<double>const& dCAbsc,vector<double>const& dCOrd,double dStartAbsc,double dEndAbsc,
		double dIntAbsc,vector<double>const& dPOrd, int InterpolateFlag, double Lim);

	double CalculateMinimumThreshold(int Length1,vector<double>const& dInts, int iIdealSize, double Lim);

private: 
	static void CalculateVariableThreshold(double dStartAbsc, double dEndAbsc, double dIntAbsc,
		vector<double>const& arrOrd, double dSThresh, double dInc, double dWindow, vector<double>& dThreshAbsc,
		vector<double>& dThreshOrd);

	void CalculateVariableThreshold(vector<double>const& arrAbsc,vector<double>const& arrOrd, double dEndAbsc, double dSThresh,
		double dInc, double dWindow,vector<double>& dThreshAbsc,vector<double>& dThreshOrd);

	void InterpolateThreshold(vector<double>const& dAbsc, double dStartAbsc, double dEndAbsc,
		vector<double>& dthreshold, double dSThresh,vector<double>const& dThreshAbsc,vector<double>const& dThreshOrd);

	void InterpolateThreshold(double dStartAbsc, double dEndAbsc, double dIncAbsc,
		vector<double>& dthreshold, double dSThresh,vector<double>const& dThreshAbsc,vector<double>const& dThreshOrd);

	double InterpolateThresholdItem(double dStartAbsc, double dEndAbsc, double dSThresh,
		vector<double>const& dThreshAbsc,vector<double>const& dThreshOrd,int& j, double dItem);

	void PeakDetect(vector<double>const& dAbsc,vector<double>const& dOrd,vector<double>& dpkAbsc,vector<double>& dpkOrd);

	void PeakDetect(double dStartAbsc, double dEndAbsc, double dIntAbsc,vector<double>const& dOrd,
		vector<double>& dpkAbsc,vector<double>& dpkOrd);
};

