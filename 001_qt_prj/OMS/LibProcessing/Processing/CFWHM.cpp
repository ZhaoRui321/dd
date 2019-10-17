#include "CFWHM.h"

vector<double> CFWHM::GetFWHM(vector<double>& dAbsc, vector<double>& dOrd, vector<int>& iStart, vector<int>& iEnd)
{
    int N = iStart.Length;
    vector<double> dOutput(N);
    for (int i = 0; i < N; ++i)
    {
        double dDiff;
        int iIndX;
        if (GetFWHM(dAbsc, dOrd, iStart[i], iEnd[i], dDiff, iIndX))
            dOutput[i] = dDiff;
        else
            dOutput[i] = 0;
    }
    return dOutput;
}

bool CFWHM::GetFWHM(vector<double>& dAbsc, vector<double>& dOrd, int iStart, int iEnd, double& dFWHM, int& iXIndMaxY)
{
    int iCounter = iStart;
    int iStartCounter = iStart;
    int iEndLimit = iEnd;
    //double dIntStart = dOrd[iCounter];
    double dMaxInt = dOrd[iCounter];
    dFWHM = 0;
    iXIndMaxY = iCounter;

    while (iCounter < iEndLimit)
    {
        if (dOrd[iCounter] > dMaxInt)
        {
            dMaxInt = dOrd[iCounter];
            iXIndMaxY = iCounter;
        }
        // start from iStart[i] and wind up till peak pos
        ++iCounter;
    }

    double dHH = dOrd[iXIndMaxY] / 2; //(dOrd[iXIndMaxY] + dIntStart) / 2;
    if (dHH <= 0)
        return false;

    //double dX = dAbsc[iXIndMaxY];
    int iBackwards = iXIndMaxY;
    int iForwards = iXIndMaxY;
    while (iBackwards > iStartCounter && dOrd[iBackwards] > dHH)
        // from there, go backwards to find first HH point
        --iBackwards;

    if (OutsideRange(dOrd[iBackwards], dOrd[iBackwards + 1], dHH))
        return false;

    double dAbsc1 = mMathLCTR.LinIntYToX(dAbsc[iBackwards], dAbsc[iBackwards + 1],
            dOrd[iBackwards], dOrd[iBackwards + 1], dHH);

    while (iForwards <= iEndLimit && dOrd[iForwards] > dHH)
        // go forwards to find second HH point
        ++iForwards;

    if (OutsideRange(dOrd[iForwards - 1], dOrd[iForwards], dHH))
        return false;
    double dAbsc2 = mMathLCTR.LinIntYToX(dAbsc[iForwards - 1], dAbsc[iForwards],
            dOrd[iForwards - 1], dOrd[iForwards], dHH);

    dFWHM = dAbsc2 - dAbsc1;
    if (dFWHM > 0)
        return true;
    else
    {
        dFWHM = 0;
        return false;
    }
}

vector<double> CFWHM::GetMassResolution(vector<double>  dAbsc, vector<double>  dOrd, vector<double>  dXC, vector<int>  iStart, vector<int>  iEnd)
{
    int N = iStart.Length;
    vector<double> dOutput(N);
    for (int i = 0; i < N; ++i)
    {
        double dDiff;
        int iIndX;
        if (GetFWHM(dAbsc, dOrd, iStart[i], iEnd[i], dDiff, iIndX))
        {
            if (dDiff > 0 && iIndX > 0)
                dOutput[i] = dXC[i] / dDiff;
        }
        else
            dOutput[i] = 0;
    }
    return dOutput;
}

bool CFWHM::OutsideRange(double Y1, double Y2, double y)
{
    bool bOut = false;
    if (Y2 > Y1)
    {
        if (y > Y2 || y < Y1)
            bOut = true;
    }
    else
    {
        if (y < Y2 || y > Y1)
            bOut = true;
    }
    return bOut;
}
