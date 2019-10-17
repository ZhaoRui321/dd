#pragma once
#include<vector>
#include "../Maths/structLCTR.h"
using namespace std;
class CSignalArea
{
public:
	CSignalArea(void){};
	~CSignalArea(){};
    double SignalArea(vector<double>& dAbsc,vector<double>& dOrd);
    double SignalContourArea(vector<double>& dAbsc,vector<double>& dOrd);
    double SignalArea(double dAbscInc, vector<double>& dOrd);
    static double SignalArea(vector<double>& dAbsc, vector<double>& dOrd, int start, int end);
    vector<double> SignalArea(vector<double>& dAbsc, vector<double>& dOrd, vector<int>& Start, vector<int>& End);
    double SignalArea(vector<double>& dAbsc, vector<double>& dOrd, double start, double end);
    double MaxSignal(vector<double>& dOrd);
    double AverageSignal(vector<double>& dOrd);
    double TotalSignal(vector<double>& dOrd);
};

