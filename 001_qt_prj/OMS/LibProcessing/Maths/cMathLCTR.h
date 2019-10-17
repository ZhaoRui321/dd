#pragma once
#define QT_GICAP
#include<vector>
#include "structLCTR.h"
using namespace std;

class cMathLCTR
{
public:
    cMathLCTR(void){}
	double Prctile(vector<double> data, double prc);
	double LinIntXToY(double dX1, double dX2, double dY1, double dY2, double dX);
	double LinIntYToX(double dX1, double dX2, double dY1, double dY2, double dY);
	void LinLeastSq(vector<double> x,vector<double> y, int n, double& gradient, double& intersect);
	void Hist(vector<double> data, int iNumBins,vector<int>& iHist, vector<double>& dBins);
	vector<int> Hist(vector<double> data, vector<double> bins);
	vector<double> Unique(vector<double> data);
	void Unique(vector<double> data, vector<double>& dOutput, vector<int>& iNumRept);
	double STD(vector<double> Val);
	double PopSTD(vector<double> Val);
	double STD(vector<double> Val, int N);
	double STD(vector<double> Val, double& M);
	double STD(vector<double> Val, int N, double& M);
	double RMS(vector<double> Val);
	vector<double> APlusB(vector<double> A, vector<double> B);
	vector<double> AMinusB(vector<double> A, vector<double> B);
	vector<double> AMinusBAllPlus(vector<double> A, vector<double> B);
    void FactorArray(vector<double> A, double F, bool bMulitply);
    bool CopyArrays(vector<double>& From, vector<double>& To, int iStart, int iEnd);
    bool CopyArrays(vector<int> From, vector<int>& To, int iStart, int iEnd);

    static double average(int n,double *x);
    static double spfh(int n,double *x);
    static double shpf(int n,double *x);
    static double dcj(int n,double *x,double *y);
    static double djc(int n,double *x,double *y);
    static double he(int n,double *x);
    static double xsa(int n,double *x,double *y);
    static double xsb(int n,double *x,double *y,double a);
};
template <class T>
class QuickSort
{
private:
    T tmp;
    void swap(T *a, T *b);
    int partition(vector<T>& Arrays, int nChoose);

public:
    QuickSort(vector<T>& Arrays, int nChoose);
};
