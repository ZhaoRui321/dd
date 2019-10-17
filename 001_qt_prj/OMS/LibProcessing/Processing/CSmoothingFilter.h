#pragma once
#include<stdio.h>
#include<vector>
#include<cstring>
#include "../Maths/structLCTR.h"

using namespace std;
//using namespace SignalProcessingPublic;
class HighFrequencyFilter
{
public:
	vector<double> Filter(vector<double>const& data,double baseLine,int nPointFilter);
private:
	void FindPercDiffs(vector<double>const& dOrd, vector<double>& arrdDiffs);
	void SetIndices(vector<double>& outFilter,vector<double>const& dOrd, int SearchIndex, vector<double>const& arrdDiffs, int& istart,
		int& iend, int& iV, int nPointFilter);//,double& dPeakInt,bool& bReset
	bool SetCentroidValues(int& istart, int& iend, int& iV);//,double& dPeakInt
};

class MovingAverageFilter
{
private:
    vector<double> mbuffer;
    vector<double> mTempBuff;
public:
    vector<double> Filter(vector<double>& data, int width);//
};
class WeightedMovingAverageFilter
{
public:
    vector<double> Filter(vector<double>& data, int width);
};
class SGF
{
private:
	int FIVE[5],
		NFIVE,
		SEVEN[2][7],
		NSEVEN[2],
		NINE[2][9],
		NNINE[2],
		ELEVEN[2][11],
		NELEVEN[2],
		mK,
		mF;
public:
	SGF();
    SGF(int K, int F);
	void SetParams(int K, int F){mK = K;mF = F;};
	bool SanityCheck();
    double Filter(vector<double>& Val);

private:
    double FilterLoop(vector<double>& Val, double Output, int* Table, int* NTable, int Index);
};
class SavitzkyGolayFilter
{
private:
	SGF* mSGFilter;
    vector<double> Window;
    vector<double> Output;
public:
	SavitzkyGolayFilter(){mSGFilter=nullptr;};
    vector<double> Filter(vector<double>& Val,int K, int F);
};
