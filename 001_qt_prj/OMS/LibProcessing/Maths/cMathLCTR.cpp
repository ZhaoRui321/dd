#include "cMathLCTR.h"
#include <math.h>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include "structLCTR.h"
using namespace LCTR;

double cMathLCTR::Prctile(vector<double> data, double prc)
{
	int n = (int)MyMath::Round(((data.size() - 1) / 100) * prc + 0.5,2);
	vector<double> dSortedData;
	vector<int> iNumRept;
	Unique(data, dSortedData, iNumRept);
	vector<double> tempdata(data.size(),0);
	int k = 0;
    for (int i = 0; i < (int)dSortedData.Length; ++i){
        for (int j = 0; j < iNumRept[i]; ++j){
			tempdata[k++] = dSortedData[i];
		}
	}
	return tempdata[n];
}

//#pragma region Linear Intertoplation

/// <summary>
/// Linear interpolation given (x1, y1), (x2, y2) and x.
/// </summary>
/// <param name="dX1"></param>
/// <param name="dX2"></param>
/// <param name="dY1"></param>
/// <param name="dY2"></param>
/// <param name="dX"></param>
/// <returns>Interpolated y value at x.</returns>
double cMathLCTR::LinIntXToY(double dX1, double dX2, double dY1, double dY2, double dX)
{
	if (dX1 == dX2)
		return dY1;
	else
		return dY1 + ((dY2 - dY1) / (dX2 - dX1) * (dX - dX1));
}

double cMathLCTR::LinIntYToX(double dX1, double dX2, double dY1, double dY2, double dY)
{
	if (dY1 == dY2)
		return dX1;
	else
		return dX1 + ((dY - dY1) * (dX2 - dX1) / (dY2 - dY1));    //(dY2 - dY1) / (dX2 - dX1) * (dX - dX1);
}
/// <summary>
/// Given an array of x, y points fit a linear line to it and calculate a/b constants
//  of the line where y = ax + b
/// </summary>
/// <param name="x">x coordinates</param>
/// <param name="y">y coordinqates</param>
/// <param name="n">n number of points</param>
/// <param name="gradient">gradient, gradient of line</param>
/// <param name="intersect">intersect, intersect</param>
void cMathLCTR::LinLeastSq(vector<double> x,vector<double> y, int n, double& gradient, double& intersect)
{
	double sum_x = 0;
	double sum_y = 0;
	double sum_xx = 0;
	double sum_xy = 0;
	double xx = 0;
	double xy = 0;

    for (int i = 0; i < n; i++){
		sum_x = sum_x + x[i];
		sum_y = sum_y + y[i];
		xx = x[i] * x[i];
		sum_xx = sum_xx + xx;
		xy = x[i] * y[i];
		sum_xy = sum_xy + xy;
	}

	gradient = (-sum_x * sum_y + n * sum_xy) / (n * sum_xx - sum_x * sum_x);
	intersect = (-sum_x * sum_xy + sum_xx * sum_y) / (n * sum_xx - sum_x * sum_x);

}

//#pragma endregion

//#pragma region Hist
/// <summary>
/// Calculate histogram.  Same as [H, B] = HIST(X, N) in Matlab.
/// </summary>
/// <param name="data">Double array of data.</param>
/// <param name="iNumBins">Number of bins to use.</param>
/// <param name="iHist">Frequency of items in each bin. [out]</param>
/// <param name="dBins">Top end of each bin. [out]</param>
void cMathLCTR::Hist(vector<double> data, int iNumBins,vector<int>& iHist, vector<double>& dBins)
{
	//Array.Sort(data);
	sort(data.begin(),data.end());
	iHist.resize(iNumBins,0);
	dBins.resize(iNumBins,0);
	vector<double> dEdges(iNumBins,0);

	double dEdgesInc = (data[data.Length - 1] - data[0]) / iNumBins;
	double dInc = dEdgesInc / 2;
	double dbin = dInc;
	double dedge = dEdgesInc;
	int iIndex = 0;
    while (dbin < data[data.size() - 1] && iIndex < iNumBins){
		dBins[iIndex] = dbin;
		dbin += dEdgesInc;  //for midpoint of each bin
        if (iIndex == iNumBins){
			dedge = data[data.size() - 1];
		}
		dEdges[iIndex++] = dedge;
		dedge += dEdgesInc;
	}
	//ArrayList arrData = new ArrayList(data);
	vector<double> arrData(data);
	for (int i = 0; i < (int)dEdges.size(); ++i){
        for (int j = 0; j < (int)arrData.size(); ++j){
            if (i == 0 && (double)arrData[j] < dEdges[i]){
				++iHist[i];
				//arrData.RemoveAt(j);
				arrData.erase(arrData.begin()+j);
			}
            else if (i > 0 && (double)arrData[j] >= dEdges[i - 1] && (double)arrData[j] < dEdges[i]){
				++iHist[i];
				//arrData.RemoveAt(j);
				arrData.erase(arrData.begin()+j);
			}
		}
	}
}

/// <summary>
/// Lazy version of Hist.  Frequencies are counted only for exact matches with the bins.
/// </summary>
/// <param name="data">Input double array.</param>
/// <param name="bins">Exact bin values.</param>
/// <returns>Frequency of exact match of data to bins.</returns>
vector<int> cMathLCTR::Hist(vector<double> data, vector<double> bins)
{
	// cheating slightly because building historgram for exact matches only.
	vector<int> iOut(bins.size(),0);
	/*foreach (double dItem in data)
	{
	bool bFound = false;
	for (int i = 0; i < bins.size() && !bFound; ++i)
	{
	if (dItem == bins[i])
	{
	bFound = true;
	++iOut[i];
	}
	}
	}*/
    for (int j=0;j<(int)data.size();j++){
		bool bFound = false;
        for (int i = 0; i < (int)bins.size() && !bFound; ++i){
            if (data[j] == bins[i]){
				bFound = true;
				++iOut[i];
			}
		}
	}
	return iOut;
}

//#pragma endregion

//#pragma region Unique
/// <summary>
/// Extract only unqiue items from an array.  
/// </summary>
/// <param name="data"></param>
/// <returns>Output array is sorted in ascending order.</returns>
vector<double> cMathLCTR::Unique(vector<double> data)
{
	sort(data.begin(),data.end());
	vector<double> df(data.size()-1);
	int iCounter = 1;
    for (int i = 0; i < (int)data.size() - 1; ++i){
		double d = data[i + 1] - data[i];
        if (d != 0){
			++iCounter;
		}
		df[i] = d;
	}
	vector<double> dOutput(iCounter,0);
	dOutput[0] = data[0];
	iCounter = 1;
    for (int i = 0; i < (int)df.size(); ++i){
        if (df[i] != 0){
			dOutput[iCounter++] = data[i + 1];
		}
	}
	return dOutput;
}

/// <summary>
/// Sorts and makes unique the input array.  Also counts how many times each unique item was repeated.
/// </summary>
/// <param name="data">Input array.</param>
/// <param name="dOutput">Sorted unique array.</param>
/// <param name="iNumRept">Number of repetitions per unique item.</param>
void cMathLCTR::Unique(vector<double> data, vector<double>& dOutput, vector<int>& iNumRept)
{
	sort(data.begin(),data.end());
	vector<double> df(data.size()-1,0);
	int iCounter = 1;
    for (int i = 0; i < (int)data.size() - 1; ++i){
		double d = data[i + 1] - data[i];
        if (d != 0){
			++iCounter;
		}
		df[i] = d;
	}
	dOutput.resize(iCounter,0);
	iNumRept.resize(iCounter,0);
	int iRept = 1;
	dOutput[0] = data[0];
	iCounter = 1;
    for (int i = 0; i < (int)df.size(); ++i){
        if (df[i] == 0){
			++iRept;
		}
        else{
			iNumRept[iCounter - 1] = iRept;
			dOutput[iCounter++] = data[i + 1];
			iRept = 1;
		}
	}
	iRept = 1;
    for (int i = df.size() - 1; df[i] == 0 && i > -1; --i){
		++iRept;
	}
	iNumRept[iNumRept.size() - 1] = iRept;
}
//#pragma endregion

//#pragma region Stats

double cMathLCTR::STD(vector<double> Val)
{
	double M = accumulate(Val.begin(),Val.end(),0)/Val.size();
	int N = Val.size();
	double STD = 0;
	for (int i=0;i<N;i++)
		STD += (M - Val[i]) * (M - Val[i]);
	STD /= (N - 1);
	return sqrt(STD);
}

double cMathLCTR::PopSTD(vector<double> Val)
{
	double M = accumulate(Val.begin(),Val.end(),0)/Val.size();
	int N = Val.size();
	double STD = 0;
	for (int i=0;i<N;i++)
		STD += (M - Val[i]) * (M - Val[i]);
	STD /= N;
	return sqrt(STD);
}

double cMathLCTR::STD(vector<double> Val, int N)
{
	double M = 0;
    for (int i = 0; i < N; i++){
		M += Val[i];
	}
	M /= N;
	double STD = 0;
    for (int i = 0; i < N; i++){
		STD += (M - Val[i]) * (M - Val[i]);
	}
	STD /= (N - 1);
	return sqrt(STD);
}

double cMathLCTR::STD(vector<double> Val, double& M)
{
	M = accumulate(Val.begin(),Val.end(),0)/Val.size();
	int N = Val.size();
	double STD = 0;
	for (int i=0;i<N;i++)
		STD += (M - Val[i]) * (M - Val[i]);
	STD /= (N - 1);
	return sqrt(STD);
}

double cMathLCTR::STD(vector<double> Val, int N, double& M)
{
	M = 0;
    for (int i = 0; i < N; i++){
		M += Val[i];
	}
	M /= N;
	double STD = 0;
    for(int i = 0; i < N; i++){
		STD += (M - Val[i]) * (M - Val[i]);
	}
	STD /= (N - 1);
	return sqrt(STD);
}

double cMathLCTR::RMS(vector<double> Val)
{
	double M = 0;
	int N = Val.size();
    for (int i = 0; i < N; i++){
		M += Val[i] * Val[i];
	}
	M /= N;
	return sqrt(M);
}

//#pragma endregion

vector<double> cMathLCTR::APlusB(vector<double> A, vector<double> B)
{
	vector<double> returnval((int)A.size(),0);
    if (A.size() == B.size()){
        for (int i = 0; i < (int)A.size(); ++i){
			returnval[i] = A[i] + B[i];
		}
	}
	return returnval;
}

vector<double> cMathLCTR::AMinusB(vector<double> A, vector<double> B)
{
	vector<double> returnval((int)A.size(),0);
    if (A.size() == B.size()){
        for (int i = 0; i <(int)A.size(); ++i){
			returnval[i] = A[i] - B[i];
		}
	}
	return returnval;
}

vector<double> cMathLCTR::AMinusBAllPlus(vector<double> A, vector<double> B)
{
	vector<double> returnval(A.size(),0);
    if (A.size() == B.size()){
        for (int i = 0; i < (int)A.size(); ++i){
			returnval[i] = A[i] - B[i];
            if (returnval[i] < 0){
				returnval[i] = 0;
			}
		}
	}
	return returnval;
}

void cMathLCTR::FactorArray(vector<double> A, double F, bool bMulitply)
{
    if ((F == 0) && (!bMulitply)){   //cannot divide by 0
		return;
	}
	for (int i = 0; i < (int)A.Length; i++){
		if (bMulitply)
			A[i] *= F;
		else
			A[i] /= F;
	}

}

/// <summary>
/// Copy whole or part of one array to another.  Set START and END to -1 to copy the whole array.
/// </summary>
/// <param name="From">Array to copy from.</param>
/// <param name="To">Array to copy to. Function will NEW it.</param>
/// <param name="iStart">Starting index (inclusive).</param>
/// <param name="iEnd">Ending index (inclusive).</param>

bool cMathLCTR::CopyArrays(vector<double>& From, vector<double>& To, int iStart, int iEnd)
{
    bool bReturn = false;
    To.clear();
    if (-1 == iStart && -1 == iEnd){
        To.resize(From.size(),0);
        iStart = 0;
        iEnd = From.size() - 1;
    }else if (iEnd >= iStart){
        To.resize(iEnd - iStart + 1,0);
    }
    if (!To.empty()&&!From.empty()){
       memcpy(&(To[0]),&(From[iStart]),(iEnd-iStart+1)*sizeof(double));
        bReturn = true;
    }
    return bReturn;
}

bool cMathLCTR::CopyArrays(vector<int> From, vector<int>& To, int iStart, int iEnd)
{
    bool bReturn = false;
    To.clear();
    if (-1 == iStart && -1 == iEnd){
        To.resize(From.size(),0);
        iStart = 0;
        iEnd = From.size() - 1;
    }else if (iEnd >= iStart){
        To.resize(iEnd - iStart + 1,0);
    }
    if (!To.empty()){
        memcpy(&(To[0]),&(From[iStart]),(iEnd-iStart+1)*sizeof(int));
        bReturn = true;
    }
    return bReturn;
}

template <class T>QuickSort<T> ::QuickSort(vector<T>& Arrays, int nChoose)
{
    if(!Arrays.empty())
        int privotLoc = partition(Arrays, nChoose);
}
template <class T>void QuickSort<T> ::swap(T *a, T *b)
{
    tmp = *a;
    *a = *b;
    *b = tmp;
}
template <class T>int QuickSort<T> ::partition(vector<T>& Arrays, int nChoose)
{
    T privotKey = Arrays[nChoose];
    T low=0,high=Arrays.size()-1;
    int nsize=Arrays.size();
    while(low < high){
        while(low < high  && Arrays[high] >= privotKey) --high;
        swap(&Arrays[low], &Arrays[high]);
        while(low < high  && Arrays[low] <= privotKey ) ++low;
        swap(&Arrays[low], &Arrays[high]);
    }
    return low;
}
double cMathLCTR:: average(int n,double *x)
{
    double av=0.0;
    for (int i=0;i<n;i++)
        av+=*(x+i);
    av=av/n;
    return av;
}


double cMathLCTR:: spfh(int n,double *x)
{
    double a=0.0;
    for (int i=0;i<n;i++)
        a+=(*(x+i))*(*(x+i));
    return a;
}


double cMathLCTR:: shpf(int n,double *x)
{
    double a=0.0,b;
    for (int i=0;i<n;i++)
        a=a+*(x+i);
    b=a*a/n;
    return b;
}

double cMathLCTR:: dcj(int n,double *x,double *y)
{
    double a=0.0;
    for (int i=0;i<n;i++)
        a+=(*(x+i))*(*(y+i));
    return a;
}

double cMathLCTR:: djc(int n,double *x,double *y)
{
    double a=0.0,b=0.0;
    for(int i=0;i<n;i++)
    {
        a=a+*(x+i);
        b=b+*(y+i);
    }
    a=a*b/n;
    return a;
}

double cMathLCTR:: he(int n,double *y)
{
    double a=0.0;
    for(int i=0;i<n;i++)
        a=a+*(y+i);
    return a;
}

double cMathLCTR:: xsa(int n,double *x,double *y)
{
    double a,b,c,d,e;
    a=spfh(n,x);
    b=shpf(n,x);
    c=dcj(n,x,y);
    d=djc(n,x,y);
    if(a-b==0)
        return 0;
    e=(c-d)/(a-b);
    return e;
}

double cMathLCTR:: xsb(int n,double *x,double *y,double a)
{
    double b,c,d;
    b=he(n,y);
    c=he(n,x);
    if(n==0)
        return 0;
    d=(b-a*c)/n;
    return d;
}
