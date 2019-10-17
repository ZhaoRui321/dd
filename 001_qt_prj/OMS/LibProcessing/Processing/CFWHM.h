#pragma once
#include "../Maths/cMathLCTR.h"
#include<vector>
#include "../Maths/structLCTR.h"
using namespace LCTR;
class CFWHM
{
public:
    CFWHM(void){}
    // <summary>
    // Gets full width (x) at half maximum (y) (FWHM) of peaks defined by start-end limits
    // </summary>
    // <param name="dAbsc">x values</param>
    // <param name="dOrd">y values</param>
    // <param name="iStart">start indices of target peaks</param>
    // <param name="iEnd">end indices of target peaks</param>
    // <returns>set of FWHMs, 1 for each start-end pair</returns>
    vector<double> GetFWHM(vector<double>& dAbsc, vector<double>& dOrd, vector<int>& iStart, vector<int>& iEnd);

private:
    cMathLCTR mMathLCTR;
    /// <summary>
    /// Calcs FWHM for 1 start-end pair
    /// </summary>
    /// <param name="dAbsc">x values</param>
    /// <param name="dOrd">y values</param>
    /// <param name="iStart">start index of target peak</param>
    /// <param name="iEnd">end index of target peak</param>
    /// <param name="dFWHM">value of FWHM</param>
    /// <param name="iXIndMaxY">index at apex of peak</param>
    /// <returns>boolean if calc of FWHM is successful or not</returns>
    bool GetFWHM(vector<double>& dAbsc, vector<double>& dOrd, int iStart, int iEnd, double& dFWHM, int& iXIndMaxY);
public:
    /// <summary>
    /// Calcs Peak (e.g. Mass) Resolution of peaks defined by start-end limits
    /// </summary>
    /// <param name="dAbsc">x values</param>
    /// <param name="dOrd">y values</param>
    /// <param name="iStart">start indices of target peaks</param>
    /// <param name="iEnd">end indices of target peaks</param>
    /// <returns>set of peak resolutions, 1 for each start-end pair</returns>
    vector<double> GetMassResolution(vector<double>  dAbsc, vector<double>  dOrd, vector<double>  dXC, vector<int>  iStart, vector<int>  iEnd);
private:
    /// <summary>
    /// Checks interpolation between values is feasible
    /// </summary>
    /// <param name="Y1">1st y  value</param>
    /// <param name="Y2">2nd y value</param>
    /// <param name="y">target y value</param>
    /// <returns>x interpolated at target y value</returns>
    bool OutsideRange(double Y1, double Y2, double y);
};
