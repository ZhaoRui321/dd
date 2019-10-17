#include "CSignalArea.h"
#include <cmath>
#include <algorithm>
#include <numeric>
using namespace LCTR;
//#pragma region Signal Area

/// <summary>
/// Sums entire signal using trapezium rule
/// </summary>
/// <param name="dAbsc">x values</param>
/// <param name="dOrd">y values</param>
/// <returns>Area under signal</returns>
double CSignalArea::SignalArea(vector<double>& dAbsc, vector<double>& dOrd)
{
	double dArea = 0;
	int N = dAbsc.Length;
	for (int i = 1; i < N; ++i)
	{
		dArea += (dAbsc[i] - dAbsc[i - 1]) * (dOrd[i] + dOrd[i - 1]) / 2;
	}
	return dArea;
}

/// <summary>
/// Sums the triangle areas immediately below signal level
/// perp heights of trapezia defined by difference of adjacent y values
/// </summary>
/// <param name="dAbsc">x values</param>
/// <param name="dOrd">y values</param>
/// <returns>Area of triangles immediately below signal</returns>
double CSignalArea::SignalContourArea(vector<double>& dAbsc, vector<double>& dOrd)
{
	double dArea = 0;
	int N = dAbsc.Length;
	for (int i = 1; i < N; ++i)
	{
		dArea += (dAbsc[i] - dAbsc[i - 1]) * abs(dOrd[i] - dOrd[i - 1]) / 2;
	}
	return dArea;
}

/// <summary>
/// Sums entire signal using trapezium rule using x increments as perp height
/// </summary>
/// <param name="dAbscInc">x increment</param>
/// <param name="dOrd">y values</param>
/// <returns>Area under signal</returns>
double CSignalArea::SignalArea(double dAbscInc, vector<double>& dOrd)
{
	double dArea = 0;
	int N = dOrd.Length;
	for (int i = 1; i < N; ++i)
	{
		dArea += dAbscInc * (dOrd[i] + dOrd[i - 1]) / 2;
	}
	return dArea;
}

/// <summary>
/// Sums signal using trapezium rule between a set of index limits
/// </summary>
/// <param name="dAbsc">x values</param>
/// <param name="dOrd">y values</param>
/// <param name="start">start index for calc area</param>
/// <param name="end">end index for calc area</param>
/// <returns>Area under signal</returns>
double CSignalArea::SignalArea(vector<double>& dAbsc, vector<double>& dOrd, int start, int end)
{
	double dArea = 0;
	int N = end - start + 1;
	for (int i = 1; i < N; ++i)
	{
		dArea += (dAbsc[start + i] - dAbsc[start + i - 1]) * (dOrd[start + i] + dOrd[start + i - 1]) / 2;
	}
	return dArea;
}

/// <summary>
/// Sums signal using trapezium rule between real x value limits
/// </summary>
/// <param name="dAbsc">x values</param>
/// <param name="dOrd">y values</param>
/// <param name="Start">start indices for calc area</param>
/// <param name="End">end indices for calc area</param>
/// <returns>Areas under signal bewteen start-end groups</returns>
vector<double> CSignalArea::SignalArea(vector<double>& dAbsc, vector<double>& dOrd, vector<int>& Start, vector<int>& End)
{
	int N = Start.Length;
	vector<double> dArea(N,0);
	for (int i = 0; i < N; ++i)
	{
		dArea[i] = SignalArea(dAbsc, dOrd, Start[i], End[i]);
	}
	return dArea;
}

/// <summary>
/// sums signal using trapezium rule between real x value limits
/// </summary>
/// <param name="dAbsc">x values</param>
/// <param name="dOrd">y values</param>
/// <param name="start">real starting value</param>
/// <param name="end">real stopping x value</param>
/// <returns>Area under signal</returns>
double CSignalArea::SignalArea(vector<double>& dAbsc, vector<double>& dOrd, double start, double end)
{
	double dArea = 0;
	for (int i = 1; i < (int)dAbsc.Length; ++i)
	{
		if (dAbsc[i]-start >=0.00001  && dAbsc[i]-end <=0.00001 )
		{
			dArea += (dAbsc[i] - dAbsc[i - 1]) * (dOrd[i] + dOrd[i - 1]) / 2;
		}
	}
	return dArea;
}

/// <summary>
/// Finds max signal in y values
/// </summary>
/// <param name="dOrd">y values</param>
/// <returns>Area under signal</returns>
double CSignalArea::MaxSignal(vector<double>& dOrd)
{
	if (!dOrd.empty())
	{
		return *max_element(dOrd.begin(),dOrd.end());
	}
	return 0;
}

/// <summary>
/// Calcs average signal of y values
/// </summary>
/// <param name="dOrd">y values</param>
/// <returns>Area under signal</returns>
double CSignalArea::AverageSignal(vector<double>& dOrd)
{
	if ((!dOrd.empty()) && (dOrd.Length > 0))
	{
		return accumulate(dOrd.begin() , dOrd.end() ,0) / dOrd.Length;
		
	}
	return 0;
}

/// <summary>
/// Calcs total signal from y values
/// </summary>
/// <param name="dOrd">y values</param>
/// <returns>Area under signal</returns>
double CSignalArea::TotalSignal(vector<double>& dOrd)
{
	if (!dOrd.empty())
	{
		return accumulate(dOrd.begin() , dOrd.end() ,0);
	}
	return 0;
}
//#pragma endregion
