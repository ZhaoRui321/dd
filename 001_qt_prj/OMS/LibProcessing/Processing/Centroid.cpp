#include "Centroid.h"
#include <cmath>
#include <math.h>

const double RATIO_PEAK=0.6;
const double MIN_PEAK=-999999999;//DBL_MIN;

/// <summary>
/// Traditional way using local maxima as peaks
/// </summary>
/// <param name="dAbsc">x values</param>
/// <param name="dOrd">y values</param>
/// <param name="cAbsc">x values at centroids</param>
/// <param name="cOrd">y values at centroids</param>
/// <param name="iStart">start of centroids</param>
/// <param name="iEnd">corresponding ends of centroids</param>
//void CCentroid::CentroidData(vector<double> dAbsc, vector<double> dOrd, vector<double>& cAbsc,
//	vector<double>& cOrd, vector<int>& iStart, vector<int>& iEnd)
//{
//	double dTmp = CentroidDataA(dAbsc, dOrd, out cAbsc, out cOrd, out iStart, out iEnd);
//}

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
//void CCentroid::CentroidData(double dStartAbsc, double dEndAbsc, double dIncAbsc, vector<double> dOrd,
//	vector<double>& cAbsc,vector<double>& cOrd, vector<int>& iStart, vector<int>& iEnd)
//{
//	vector<double> dAbsc = GetAbsc(dStartAbsc, dEndAbsc, dIncAbsc, dOrd.Length);
//	double dTmp = CentroidDataA(dAbsc, dOrd, out cAbsc, out cOrd, out iStart, out iEnd);
//}

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
//double CCentroid::CentroidDataA(double dStartAbsc, double dEndAbsc, double dIncAbsc, vector<double> dOrd,
//	vector<double>& cAbsc,vector<double>& cOrd, vector<int>& iStart, vector<int>& iEnd)
//{
//	vector<double> dAbsc = GetAbsc(dStartAbsc, dEndAbsc, dIncAbsc, dOrd.Length);
//	double dArea = CentroidDataA(dAbsc, dOrd, out cAbsc, out cOrd, out iStart, out iEnd);
//	return dArea;
//}

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
double CCentroid::CentroidDataA(vector<double>const& dAbsc, vector<double>const& dOrd, vector<double>& cAbsc, vector<double>& cOrd,
    vector<int>& iStart,vector<int>& iEnd,int width)
{
    if(mTmpCX.size()!=dOrd.Length){
        try{
            mTmpCX.resize(dOrd.Length);
            mTmpCY.resize(dOrd.Length);
            mTmpStart.resize(dOrd.Length);
            mTmpEnd.resize(dOrd.Length);
            mTmpCoord.resize(dOrd.Length);
            mArrdDiffs.resize(dOrd.Length-1);
        }catch(...){return -1;}
    }
#if 1
    FindPercDiffs(dOrd,mArrdDiffs.data());
    double dDenominator = 0, dNumerator = 0;//, dArea = 0;
	int istart = -1, iend = -1, iV = -1;
    double dPeakInt = MIN_PEAK,dPeakCoord = 0;
	int cIndex = 0;
	int nlength=(int)(dOrd.Length)-2;
	for(int SearchIndex = 1;SearchIndex < nlength;++SearchIndex){
        SetIndices(dAbsc,dOrd, SearchIndex, mArrdDiffs.data(), istart,iend, iV, dPeakInt,dPeakCoord);//, bReset
        if (istart > -1){// && iend == -1)
            dNumerator += dAbsc[SearchIndex] * dOrd[SearchIndex];
            dDenominator += dOrd[SearchIndex];
        }
        bool bInitV = SetCentroidValues(mTmpCX.data(), mTmpCY.data(), mTmpStart.data(), mTmpEnd.data(), dDenominator, dNumerator, istart,
            iend, iV, dPeakInt,dPeakCoord, mTmpCoord.data(),cIndex,width);
        if (bInitV){ //reinit for \/ shape
            //dArea += (dAbsc[SearchIndex] - dAbsc[SearchIndex - 1]) * (dOrd[SearchIndex] + dOrd[SearchIndex - 1]) / 2;
            dNumerator += dAbsc[SearchIndex] * dOrd[SearchIndex];
            dDenominator += dOrd[SearchIndex];
        }
    }
#endif
#if 1//正反扫对比
    if(mCopydAbsc.size()!=dOrd.Length){
        try{
        mCopydAbsc.resize(dOrd.Length);
        mCopydOrd.resize(dOrd.Length);
        mCopyTmpCoord.resize(dOrd.Length);
        mCopyTmpCY.resize(dOrd.Length);
        }catch(...){return -1;}
    }
    int tempLength=dOrd.Length-1;
    for(int i=0;i<dOrd.Length;i++){
        mCopydOrd[i]=dOrd[tempLength-i];
        mCopydAbsc[i]=dAbsc[tempLength-i];
    }
    FindPercDiffs(mCopydOrd,mArrdDiffs.data());

    istart = -1; iend = -1; iV = -1;
    dPeakInt = MIN_PEAK;dPeakCoord = 0;
    int cIndex1 = 0;
    nlength=(int)(dOrd.Length)-2;

    for(int SearchIndex = 1;SearchIndex < nlength;++SearchIndex){
        SetIndices(mCopydAbsc,mCopydOrd, SearchIndex, mArrdDiffs.data(), istart,iend, iV, dPeakInt,dPeakCoord);
        SetCentroidValues1(mCopyTmpCY.data(),istart,iend, iV, dPeakInt,dPeakCoord, mCopyTmpCoord.data(),cIndex1,width);
    }
    bool peaktrue=false;
    nlength=0;
    for(int i=0;i<cIndex;i++){
        peaktrue=false;
        for(int j=0;j<cIndex1;j++){
            if(mTmpCY[i]==mCopyTmpCY[j]){
                if((mTmpCoord[i]>=mCopyTmpCoord[j]-(width*10))&&(mTmpCoord[i]<=mCopyTmpCoord[j]+(width*10))){
                    peaktrue=true;
                    nlength++;
                    break;
                }
            }
        }
        if(!peaktrue)
            mTmpCoord[i]=-1;
    }
    cAbsc.resize(nlength,0);
    cOrd.resize(nlength,0);
    iStart.resize(nlength,0);
    iEnd.resize(nlength,0);
    for(int i=0,k=0;i<cIndex;i++){
        if(mTmpCoord[i]!=-1){
            cAbsc[k]=mTmpCX[i];
            cOrd[k]=mTmpCY[i];
            iStart[k]=mTmpStart[i];
            iEnd[k]=mTmpEnd[i];
            k++;
        }
    }
#endif
    return 0;
    //return dArea;
}

/// <summary>
/// Get array of values from start, stop values & increment
/// </summary>
/// <param name="dStartAbsc">Start x</param>
/// <param name="dEndAbsc">Stop x</param>
/// <param name="dIncAbsc">X Increment</param>
/// <param name="iL">Length of array</param>
/// <returns>x values in array</returns>
vector<double> CCentroid::GetAbsc(double dStartAbsc, double dEndAbsc, double dIncAbsc, int iL)
{
//	int iInd = (int)((dEndAbsc - dStartAbsc) / dIncAbsc);
    (void)dEndAbsc;
	vector<double> dAbsc(iL,0);
	double dAbscTmp = dStartAbsc;
	for (int i = 0; i < iL; i++)
	{
		dAbsc[i] = dAbscTmp;
		dAbscTmp += dIncAbsc;
	}
	return dAbsc;
}
bool CCentroid::SetCentroidValues1(double* tmpCY,int& istart, int& iend, int& iV, double& dPeakInt, double& dPeakCoord,
                                   double* tmpCoord,int& cIndex,int width)
{
    bool bI = false;
    if (iend > istart && istart > -1){
        if(iend-istart>=width){
            tmpCY[cIndex] = dPeakInt;
            tmpCoord[cIndex]=dPeakCoord;
            ++cIndex;
        }
        if (iV > -1){
            istart = iV;
            bI = true;
            dPeakInt = MIN_PEAK;
        }
        else
            istart = -1;
        iend = -1;
        iV = -1;
    }
    return bI;
}
bool CCentroid::SetCentroidValues(double* tmpCX, double* tmpCY, int* tmpStart,int* tmpEnd,
                                  double& dDenominator,double& dNumerator, int& istart, int& iend, int& iV, double& dPeakInt,
                                  double& dPeakCoord,double* tmpCoord,int& cIndex,int width)
{
	bool bI = false;
	if (iend > istart && istart > -1){
        if(iend-istart>=width){
            tmpCX[cIndex] = dNumerator / dDenominator;
            tmpCY[cIndex] = dPeakInt;
            tmpStart[cIndex] = istart;
            tmpEnd[cIndex] = iend;
            tmpCoord[cIndex]=dPeakCoord;
            ++cIndex;
        }
		if (iV > -1){
			istart = iV;
			bI = true;
            dPeakInt = MIN_PEAK;
		}
		else
			istart = -1;
		iend = -1;
		iV = -1;
		dNumerator = 0;
		dDenominator = 0;
	}
	return bI;
}

void CCentroid::SetIndices(vector<double>const& dAbsc,vector<double>const& dOrd,
                           int SearchIndex, double const* arrdDiffs, int& istart,
                           int& iend, int& iV, double& dPeakInt,double& dPeakCoord)
{
    double dTh = 0.000001; //of a 1% diff
	double dNTh = -1 * dTh;
	double dOrdN = dOrd[SearchIndex];
	double dOrdmin1 = dOrd[SearchIndex - 1];
    if (arrdDiffs[SearchIndex - 1] > dNTh && arrdDiffs[SearchIndex - 1] < dTh){//__
        if(arrdDiffs[SearchIndex] > dTh){/* __/ */
            if (istart > -1){
                if (dOrdmin1 > dOrdN){
                    if(dOrdmin1 > dPeakInt){//取最高点
                        dPeakInt = dOrdmin1;
                        dPeakCoord=dAbsc[SearchIndex - 1];
                    }
                }else{
                    if(dOrdN > dPeakInt){//取最高点
                        dPeakInt = dOrdN;
                        dPeakCoord=dAbsc[SearchIndex];
                    }
                }
            }else{
                istart = SearchIndex;
                dPeakInt =MIN_PEAK;
            }
        }else{
            if (istart > -1){
                if (dOrdmin1 > dOrdN){
                    if(dOrdmin1 > dPeakInt){//取最高点
                        dPeakInt = dOrdmin1;
                        dPeakCoord=dAbsc[SearchIndex - 1];
                    }
                }else{
                    if(dOrdN > dPeakInt){//取最高点
                        dPeakInt = dOrdN;
                        dPeakCoord=dAbsc[SearchIndex];
                    }
                }
            }
        }
		return;
    }else if (arrdDiffs[SearchIndex - 1] > dTh){//  /
        if (SearchIndex == 1 ){//最开始&&dOrdmin1 > 0
            istart = SearchIndex;
            dPeakInt =MIN_PEAK;
            return;
        }else if(istart>-1){
            if (dOrdmin1 > dOrdN){
                if(dOrdmin1 > dPeakInt){//取最高点
                    dPeakInt = dOrdmin1;
                    dPeakCoord=dAbsc[SearchIndex - 1];
                }
            }else{
                if(dOrdN > dPeakInt){//取最高点
                    dPeakInt = dOrdN;
                    dPeakCoord=dAbsc[SearchIndex];
                }
            }
        }
		return;
    }else if (arrdDiffs[SearchIndex - 1] < dNTh){/*  \ */
        if (arrdDiffs[SearchIndex]>dNTh && arrdDiffs[SearchIndex] < dTh){/* \__*/
            if (istart > -1){
                if((dPeakInt-dOrdN)/(dPeakInt-dOrd[istart])>RATIO_PEAK)
                    iV = iend = SearchIndex;
            }else
                iend = -1;
        }else if (arrdDiffs[SearchIndex] > dTh){ /* \/ */
            if (istart > -1){
                if((dPeakInt-dOrdN)/(dPeakInt-dOrd[istart])>RATIO_PEAK)
                    iV = iend = SearchIndex;
            }else{
                istart = SearchIndex;
                dPeakInt =MIN_PEAK;
                iend = -1;
            }
        }
		return;
	}
}

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
//void CCentroid::CentroidData(vector<double> dAbsc, vector<double> dOrdY, vector<double> darrBaseline,
//	vector<double>& cAbsc, vector<double>& cOrd, vector<int>& iarrStart, vector<int>& iarrEnd)
//{
	/*vector<double> dOrd(dOrdY.Length,0);
	for(int i = 0; i < dOrdY.Length; i++)
	{
		if(dOrdY[i] < 0)
            dOrd[i] = 0;
        else
            dOrd[i] = dOrdY[i];
    }
	string strMethod = GetCentroidMethod();
	switch (strMethod)
	{
		case(Constants.CENTROID_TYPE_THRESH_25):
		case (Constants.CENTROID_TYPE_THRESH_FULL):
			CentroidDataThreshold(dAbsc, dOrd, darrBaseline, out cAbsc, out cOrd, out iarrStart, out iarrEnd);break;
		case (Constants.CENTROID_TYPE_GRAD_25):
		case (Constants.CENTROID_TYPE_GRAD_FULL):
			CentroidDataGradient(dAbsc, dOrd, out cAbsc, out cOrd, out iarrStart, out iarrEnd);break;
		case (Constants.CENTROID_TYPE_STD):
			CentroidData(dAbsc, dOrd, out cAbsc, out cOrd, out iarrStart, out iarrEnd);break;
		default:
			CentroidData(dAbsc, dOrd, out cAbsc, out cOrd, out iarrStart, out iarrEnd);break;
	}*/
//}

void CCentroid::CopyArrays(vector<double>& cAbsc, vector<double>& cOrd, vector<int>& iStart, vector<int>& iEnd,
	vector<double>& tmpCX,vector<double>& tmpCY, vector<int>& tmpStart, vector<int>& tmpEnd, int& cIndex)
{
	if (cIndex > 0)
	{
		--cIndex;
        mMathLCTR.CopyArrays(tmpCX,	cAbsc,	0, cIndex);
        mMathLCTR.CopyArrays(tmpCY,	cOrd,	0, cIndex);
        mMathLCTR.CopyArrays(tmpStart,	iStart, 0, cIndex);
        mMathLCTR.CopyArrays(tmpEnd,	iEnd,	0, cIndex);
	}
}

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
//void CCentroid::CentroidDataGradient(vector<double> dAbsc, vector<double> dOrd, vector<double>& cAbsc,
//	vector<double>& cOrd, vector<int>& iarrStart, vector<int>& iarrEnd)
//{
	/*double dHeightMin = GetRegCentroidHeight();
	double dHeightMax = GetRegCentroidHeightMax();
	double dWidthMin = 0; 
	double dWidthMax = double.MaxValue;

	int iSW = GetRegGradSmooth(); ;
	if (iSW < 1)
		iSW = 5;

	cAbsc = null;
	cOrd = null;
	iarrStart = null;
	iarrEnd = null;
	vector<double> tmpCX(dOrd.Length,0);
	vector<double> tmpCY(dOrd.Length,0);
	vector<double> tmpFWHM(dOrd.Length,0);
	vector<int> tmpStart(dOrd.Length,0);
	vector<int> tmpEnd(dOrd.Length,0);
	int cIndex = 0;
	vector<double> darrRawDiffs = GetDiffs(dOrd); 
	vector<double> darrDiffs = GetDeriv(dOrd);
	vector<double> darrSDiffs = SmoothDifferential(darrDiffs, iSW);
	vector<double> darrSDiffs2 = GetDiffs(darrSDiffs);

	for (int j = 0; j < darrSDiffs.Length - 2; j++)
	{
		if ((darrSDiffs[j] >= 0 && darrSDiffs[j + 1] < 0) || (darrSDiffs[j] > 0 && darrSDiffs[j + 1] <= 0)) //zero crossing detected == apex
		{
			int iApex = -1;
			int iStart = -1;
			int iStop = -1;
			bool bFlatTop = false;
			int iFlatRun = 1;
			int iFRStart = 0;

			int iPrevEnd = 0;
			if(cIndex > 0)
				iPrevEnd = tmpEnd[cIndex];

			int iStApex = max(0, j - 2);
			int iEApex = min(darrSDiffs.Length, j + 2);    //smoothed 0-crossing not exact position of apex

			if (dOrd[j] > dOrd[j + 1])
				iApex = j;
			else
				iApex = j + 1;

			for (int i = iApex; i > 1; i--)
			{
				if ((darrSDiffs2[i - 1] >= 0 && darrSDiffs2[i] < 0) || (darrSDiffs2[i - 1] > 0 && darrSDiffs2[i] <= 0))
				{
					iStart = i - 1;
					break;
				}
			}
			for (int i = iApex; i < darrSDiffs2.Length - 2; i++)
			{
				if ((darrSDiffs2[i + 1] >= 0 && darrSDiffs2[i] < 0) || (darrSDiffs2[i + 1] > 0 && darrSDiffs2[i] <= 0))
				{
					iStop = i + 2;
					break;
				}
			}

			if (iApex <= 0 || iStart < 0 || iStop <= 0)
				continue;
			double dLower = dOrd[iApex] * (1 - 0.0015);
			double dUpper = dOrd[iApex] * (1 + 0.0015);
			for (int a = iApex + 1; a <= iStop; a++)
			{
				if (dOrd[a] >= dLower && dOrd[a] <= dUpper)
				{
					bFlatTop = true;
					iFlatRun++;
				}
				else
					break;
			}

			for (int a = iApex - 1; a >= iStart; a--)
			{
				if (dOrd[a] >= dLower && dOrd[a] <= dUpper)
				{
					iFRStart = a;
					bFlatTop = true;
					iFlatRun++;
				}
				else
					break;
			}


			if ((iApex >= iStop) || (iApex <= iStart))
				continue;
			double dHH = dOrd[iApex] / 2;
			double dSmall = 0.000001;
			int iInit = -1, iDimin = -1;   //very limits of peak
			int iMaxLimit = iStop + (iStop - iStart) * 2;
			for (int i = iStart; i > 1; i--)
			{
				if ((darrSDiffs[i - 1] <= 0 && darrSDiffs[i] > 0) || (darrSDiffs[i - 1] < 0 && darrSDiffs[i] >= 0))
				{//find u-shaped dip at peak boundary
					iInit = i;
					break;
				}
				else if (darrSDiffs2[i - 1] >= -1 * dSmall && darrSDiffs2[i - 1] <= dSmall && darrSDiffs2[i] >= -1 * dSmall && darrSDiffs2[i] <= dSmall)
				{//flatlines
					iInit = i;
					break;
				}
				else if (dOrd[i-1] == 0 && dOrd[i] == 0)
				{
					iInit = i;
					break;
				}
				if (i <= iPrevEnd)
				{   //ensure it doesn't encroach on prev peak
					iInit = i;
					break;
				}

			}
			for (int i = iStop; i < darrSDiffs2.Length - 2; i++)
			{
				if ((darrSDiffs[i] <= 0 && darrSDiffs[i + 1] > 0) || (darrSDiffs[i] < 0 && darrSDiffs[i + 1] >= 0))
				{//find u-shaped dip at peak boundary
					iDimin = i;
					break;
				}
				else if (darrSDiffs2[i] >= -1 * dSmall && darrSDiffs2[i] <= dSmall && darrSDiffs2[i + 1] >= -1 * dSmall && darrSDiffs2[i + 1] <= dSmall)
				{//flatlines
					iDimin = i;
					break;
				}
				else if(dOrd[i] == 0 && dOrd[i+1] == 0)
				{
					iDimin = i;
					break;
				}
				if(i > iMaxLimit)
				{//ensure it doesn't wander too far
                            //iDimin = i;
					break;
				}
			}
			if ((iInit < 0) || (iInit > iStart) || ((iStart - iInit) / (iStop - iStart)) > 1.5)
				iInit = iStart;
			if ((iDimin < 0) || (iDimin < iStop) || ((iDimin - iStop) / (iStop - iStart)) > 1.5)
				iDimin = iStop;
			int iWidth = iStop - iStart;
			int iLLim = max(0,iInit-iWidth);
			int iULim = iDimin + iWidth;
			if (dOrd[iInit] > dHH)  //ensure that we can calc FWHM from start of peak - if not, extend boundary if poss
			{
				for(int i = iInit; i > 0; i--)
				{
					if(i < iLLim)
						break;
					if (dOrd[i] < dHH)
					{
						iInit = i;
						break;
					}
				}
			}
			if (dOrd[iDimin] > dHH) //ensure that we can calc FWHM from end of peak - if not, extend boundary if poss
			{
				for(int i = iDimin; i < dOrd.Length; i++)
				{
					if (i > iULim)
						break;
					if (dOrd[i] < dHH)
					{
						iDimin = i;
						break;
					}
				}
			}
                    //check width, etc?
			if (CentroidPassFilter(dOrd[iApex], dAbsc[iStart], dAbsc[iStop], dHeightMin, dHeightMax, dWidthMin, dWidthMax)) //Filter(dOrd[iApex], dAbsc[iStart], dAbsc[iStop]))
			{
				vector<double> darrX = null;
				vector<double> darrY = null;
				int iW = iStop - iStart + 1;
				if (iW >= 3)    //cannot be a real peak if <3 data pts wide
				{
					double dXPos;
					double dYPos;
					double dFWHM;
					double dRes;

					if (GetCurveFitData(dAbsc, dOrd, iW, iStart, iStop, iApex, bFlatTop, iFRStart, iFlatRun, darrX, darrY) && mCurveFit != null)
					{
                        if (mMathLCTR != null)
						{
                            double dStdev = mMathLCTR.PopSTD(darrX);
							double dMean = darrX.Average();
							vector<double> darrLnY(darrY.Length];
							vector<double> darrNormX(darrY.Length];
							for (int m = 0; m < darrY.Length; m++)
							{
								if (dStdev != 0)
									darrNormX[m] = (darrX[m] - dMean) / dStdev;
								else
									darrNormX[m] = 0;
								darrLnY[m] = log(darrY[m]);
							}

							int nPolyOrder = 2;

							double[,] dZ = new double[darrY.Length, nPolyOrder + 1];

							for (int i = 0; i < darrY.Length; i++)
							{
								dZ[i, 0] = 1.0;
								dZ[i, 1] = darrNormX[i];
								dZ[i, 2] = darrNormX[i] * darrNormX[i];
							}

                                    //curve fit
							vector<double> dCoeffs;
							try
							{
								dCoeffs = mCurveFit.Regress(dZ, darrLnY);
							}
							catch (ArithmeticException)
							{
								continue;
							}

							double c1 = dCoeffs[0];
							double c2 = dCoeffs[1];
							double c3 = dCoeffs[2];

							double dRSquare = mCurveFit.GetRSquareValue(darrNormX, darrLnY, dCoeffs);
                                    
							if (dRSquare > 0.85)    //curve fit is reasonable
							{
								if (c3 == 0)
									continue;
								dXPos = -((dStdev * c2 / (2 * c3)) - dMean);
								if (dXPos < darrX[0] || dXPos > darrX[darrX.Length-1])
								{
									dXPos = CalcCentroid(dAbsc, dOrd, iStart, iStop);
									if (dXPos <= 0)
										continue;
									dYPos = dOrd[iApex];
									dFWHM = -1;
								}
								if (double.IsNaN(dXPos))    //mainly caused by small mis-shapen peaks
									continue;
								dYPos = dOrd[iApex];
								dFWHM = dStdev * 2.35703 / (sqrt(2) * sqrt(-1 * c3));
								if (double.IsNaN(dFWHM))
									dFWHM = 0;
								dRes = dXPos / dFWHM;
							}
							else
							{   //curve fit is too poor to use so calc centroid using data pts directly
								dXPos = CalcCentroid(dAbsc, dOrd, iStart, iStop);
								if (dXPos <= 0)
									continue;
								dYPos = dOrd[iApex];
								dFWHM = -1;
							}
						}
						else
							continue;
					}
					else
					{   //cannot curve fit - peak is too oddly shaped so calc centroid using data pts directly
						dXPos = CalcCentroid(dAbsc, dOrd, iStart,iStop);
						if (dXPos <= 0)
							continue;
						dYPos = dOrd[iApex];
						dFWHM = -1;
					}

					tmpCX[cIndex] = dXPos;
					tmpCY[cIndex] = dYPos;
					tmpStart[cIndex] = iInit;
					tmpEnd[cIndex] = iDimin;
					tmpFWHM[cIndex] = dFWHM;
					++cIndex;
				}
			}//end filter
		}
	}
	CopyArrays(cAbsc, cOrd, iarrStart, iarrEnd, tmpCX, tmpCY, tmpStart, tmpEnd, cIndex);*/
//}

/// <summary>
/// Calc centroid from x, y data between x limits
/// </summary>
/// <param name="dAbsc">x values</param>
/// <param name="dOrd">y values</param>
/// <param name="iStart">start index</param>
/// <param name="iStop">stop index</param>
/// <returns></returns>
double CCentroid::CalcCentroid(vector<double> dAbsc, vector<double> dOrd, int iStart, int iStop)
{
	double dXPos = -1;
	double dNumerator = 0;
	double dDenominator = 0;
	for (int i = iStart; i <= iStop; i++)
	{
		dNumerator += dAbsc[i] * dOrd[i];
		dDenominator += dOrd[i];
	}
	if (dDenominator > 0)
		dXPos = dNumerator / dDenominator;
	return dXPos;
}

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
bool CCentroid::GetCurveFitData(vector<double> dAbsc, vector<double> dOrd, int iW, int iStart, int iStop, int iApex, bool bFlatTop, int iFRStart, int iFlatRun, vector<double>& darrX, vector<double>& darrY)
{
	bool bOK = false;
	if (bFlatTop)
		bOK = ProcessFlatTopData(dAbsc, dOrd, iW, iStart, iStop, iApex, iFRStart, iFlatRun, darrX, darrY);
	else
	{
		ProcessStandardData(dAbsc, dOrd, iW, iStart, iStop, iApex, iFRStart, iFlatRun, darrX, darrY);
		bOK = true;
	}
	return bOK;
}

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
bool CCentroid::ProcessFlatTopData(vector<double> dAbsc, vector<double> dOrd, int iW, int iStart, int iStop, int iApex, int iFRStart, int iFlatRun, vector<double>& darrX, vector<double>& darrY)
{
    (void)iApex;
	bool bOK = false;
	int iDiff = iW - iFlatRun;
	int iBegin = iStart;
	int iEnd = iStop;
	int iCt = 0;

	if (iDiff > 2)
	{
		if (iW >= 7)
		{
			int iLeft = iFRStart - iStart;
			int iRight = iStop - (iFRStart + iFlatRun - 1);
			int iVal = min(iLeft, iRight);
			if (iVal > 0)
			{
				iBegin = iFRStart - iVal;
				iEnd = iFRStart + iFlatRun - 1 + iVal;
			}
		}

		darrX.resize(iEnd - iBegin + 1,0);
		darrY.resize(iEnd - iBegin + 1,0);

		for (int z = iBegin; z <= iEnd; z++, iCt++)
		{
			darrX[iCt] = dAbsc[z];
			darrY[iCt] = dOrd[z];
		}
		bOK = true;
	}
	return bOK;
}

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
void CCentroid::ProcessStandardData(vector<double> dAbsc, vector<double> dOrd, int iW, int iStart, int iStop, int iApex, int iFRStart, int iFlatRun, vector<double>& darrX, vector<double>& darrY)
{
    (void)iStart;(void)iStop;(void)iFRStart;(void)iFlatRun;
	int iWindow = -1;
	int iCt = 0;
	switch (iW)
	{
		case(3):
		case(4):
			iWindow = 3;
			break;
		case(5):
		case(6):
			iWindow = 5;
			break;
		default:
			iWindow = 7;
			break;
	}
	int iShoulder = iWindow / 2;
	darrX.resize(2 * iShoulder + 1,0);
	darrY.resize(2 * iShoulder + 1,0);

	for (int z = max(0, iApex - iShoulder); z <= iApex + iShoulder; z++, iCt++)
	{
		darrX[iCt] = dAbsc[z];
		darrY[iCt] = dOrd[z];
	}
}

/// <summary>
/// Calcs differences between y values
/// </summary>
/// <param name="dOrd">y values</param>
/// <returns>Differences</returns>
vector<double> CCentroid::GetDiffs(vector<double> dOrd)
{
    vector<double> darrDiffs(dOrd.Length-1,0);
    for (int i = 1; i < (int)(dOrd.Length); i++)
        darrDiffs[i - 1] = dOrd[i] - dOrd[i - 1];
    return darrDiffs;
}

/// <summary>
/// First derivative of vector using 2-point central difference.
/// Example: deriv([1 1 1 2 3 4]) yeilds [0 0 .5 1 1 1]
/// T. C. O'Haver, 1988. original in MATLAB
/// </summary>
/// <param name="dOrd">y values</param>
/// <returns>first derivative of y values</returns>
vector<double> CCentroid::GetDeriv(vector<double> dOrd)
{ 
    int n = dOrd.Length;
    vector<double> deriv(n,0);
    deriv[0]=dOrd[1]-dOrd[0];
    deriv[n-1]=dOrd[n-1]-dOrd[n-2];
    for (int j = 1; j < n-1; j++)
      deriv[j]=(dOrd[j+1]-dOrd[j-1]) / 2;
    return deriv;
}

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
vector<double> CCentroid::SmoothDifferential(vector<double> Y, int w)
{
    vector<double> s(Y.Length,0);
    if (w <= 1)
    {
		for (int i = 0; i < (int)(Y.Length); i++)
			s[i] = Y[i];
        return s;
    }
    vector<double> SmoothY(s.Length,0);
    double SumPoints = 0;
    for (int i = 0; i < w; i++)
        SumPoints += Y[i];
    int halfw = (int)(((double)w / 2) + 0.5);

    for (int k = 0; k < (int)(Y.Length) - w; k++)
    {
        s[k + halfw - 1] = SumPoints;
        SumPoints = SumPoints - Y[k];
        SumPoints = SumPoints + Y[k + w];
    }
    for (int j = 0; j < (int)(s.Length); j++)
        s[j] /= w;
    SumPoints = 0;
    for (int l = 0; l < w; l++)
        SumPoints += s[l];
    for (int m = 0; m < (int)(s.Length) - w; m++)
    {
        SmoothY[m + halfw - 1] = SumPoints;
        SumPoints = SumPoints - s[m];
        SumPoints = SumPoints + s[m + w];
    }
    for (int n = 0; n < (int)(SmoothY.Length); n++)
        SmoothY[n] /= w;
    return SmoothY;
}

/// <summary>
/// Finds percentage differences between adjacent y values
/// </summary>
/// <param name="dOrd">y values</param>
/// <param name="arrdDiffs">Calculated perc differences</param>
void CCentroid::FindPercDiffs(vector<double>const& dOrd, double* arrdDiffs)
{
    int nlength=(int)(dOrd.Length);
    for (int i = 1; i < nlength; i++){
        if(dOrd[i - 1]>1e-8||dOrd[i - 1]<-(1e-8))
                    arrdDiffs[i - 1] = (dOrd[i] - dOrd[i - 1]) * 100 / fabs(dOrd[i - 1]);
        else
             arrdDiffs[i - 1]=0;
    }
}

//void CCentroid::FindPercDiffsR(vector<double>const& dOrd, double* arrdDiffs)
//{
//    int nlength=(int)(dOrd.Length);
//    for (int i = nlength- 1; i >=0; i--){
//        if(dOrd[i - 1]>1e-8||dOrd[i - 1]<-(1e-8))
//            arrdDiffs[i - 1] = (dOrd[i] - dOrd[i - 1]) * 100 / fabs(dOrd[i - 1]);
//        else
//            arrdDiffs[i - 1]=0;
//    }
//}
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
//void CCentroid::CentroidDataThreshold(vector<double> dAbsc, vector<double> dOrd, vector<double> darrBaseline,
//	vector<double>& cAbsc, vector<double>& cOrd, vector<int>& iarrStart, vector<int>& iarrEnd)
//{
	/*double dFactor = 1.025;
	cAbsc = null;
	cOrd = null;
	iarrStart = null;
	iarrEnd = null;
	vector<double> tmpCX(dOrd.Length,0);
	vector<double> tmpCY(dOrd.Length,0);
	vector<int> tmpStart(dOrd.Length,0);
	vector<int> tmpEnd(dOrd.Length,0);
	int cIndex = 0;

	double dDenominator = 0, dNumerator = 0;
	bool bUseBaseline = GetUseBaselineChoice();
	double dUThresh = GetUserThreshold();

	int istart = -1, iend = -1;

	double dPeakInt = 0;
	int iPeakInt = 0;
	vector<double> darrBl(dAbsc.Length];
	bool bInPeak = false;
	for (int i = 0; i < dAbsc.Length; i++)
	{
	if (bUseBaseline && darrBaseline != null)
	darrBl[i] = max(0.0001, darrBaseline[i]) * dFactor;
	else
	darrBl[i] = dUThresh;
	}
	for (int i = 0; i < dOrd.Length; i++)
	{
	if ((dOrd[i] >= darrBl[i]) && (darrBl[i] > 0) && (!bInPeak))
	{
	istart = i;
	bInPeak = true;
	dDenominator = 0; dNumerator = 0; dPeakInt = 0; iPeakInt = 0;
	}
	else if (dOrd[i] <= darrBl[i] && (bInPeak))
	{
	iend = i;
	bInPeak = false;

	tmpCX[cIndex] = dNumerator / dDenominator;
	tmpCY[cIndex] = dPeakInt;
	tmpStart[cIndex] = istart;
	tmpEnd[cIndex] = iend;
	++cIndex;
	}

	if (bInPeak)
	{
	if (dOrd[i] > dPeakInt)
	{
	dPeakInt = dOrd[i];
	iPeakInt = i;
	}
	dNumerator += dAbsc[i] * dOrd[i];
	dDenominator += dOrd[i];
	}
	}
	CopyArrays(cAbsc, cOrd, iarrStart, iarrEnd, tmpCX, tmpCY, tmpStart, tmpEnd, cIndex);*/
//}


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
//void CCentroid::FilterCentroids(vector<double> darrX, vector<double> CX, vector<double> CY, vector<int> Start,
//	vector<int> End,string strUnits, vector<double>& FCX, vector<double>& FCY, vector<int>& FStart, vector<int>& FEnd)
//{
//    double XlimMin = darrX[0];
//    double XlimMax = darrX[darrX.Length - 1];
//    FilterCentroids(darrX, CX, CY, Start, End, XlimMin, XlimMax, strUnits, out FCX, out FCY, out FStart, out FEnd);
//}

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
/*void CCentroid::FilterCentroids(vector<double> darrX, vector<double> CX, vector<double> CY, vector<int> Start,
    vector<int> End, double XlimMin, double XlimMax, string strUnits,vector<double>& FCX, vector<double>& FCY,
    vector<int>& FStart, vector<int>& FEnd)
{
    double Height = GetRegCentroidHeight();
    double HeightMax = GetRegCentroidHeightMax();
    double Width = GetRegCentroidWidth(strUnits);
    double WidthMax = GetRegCentroidWidthMax(strUnits);
    bool bQuota= GetRegCentroidApplyQuota();
    int iQuota = GetRegCentroidQuota();

    int iCounter = 0;
    int N = CX.Length;
    vector<double> tmpFCX(N,0);
    vector<double> tmpFCY(N,0);
    vector<int> tmpFStart(N,0);
    vector<int> tmpFEnd(N,0);

    FCX = null;
    FCY = null;
    FStart = null;
    FEnd = null;
    List<CentroidPeak> list = new List<CentroidPeak>();

    for (int i = 0; i < N; ++i)
    {
        double dStart = darrX[Start[i]];
        double dStop  = darrX[End[i]];
        double dWidth = dStop - dStart;
        if (CentroidPassFilter(CY[i], darrX[Start[i]], darrX[End[i]], Height, HeightMax, Width, WidthMax))
        {
            if (CX[i] >= XlimMin && CX[i] <= XlimMax)
			{
				CentroidPeak cp = new CentroidPeak(CX[i], CY[i], Start[i], End[i]);
				list.Add(cp);
			}
		}
	}
	iCounter = list.Count;

	if (iCounter > 0)
	{
		if (bQuota)
		{
			iCounter = min(iCounter, iQuota);
			list.Sort();
			list.Reverse();
		}

		FCX.resize(iCounter,0);
		FCY.resize(iCounter,0);
		FStart.resize(iCounter,0);
		FEnd.resize(iCounter,0);
		for(int ind=0; ind<iCounter; ind++)
			list[ind].UpdateArray(FCX, FCY, FStart, FEnd, ind);
    }
}*/

int CCentroid::GetRegCentroidQuota()
{
    int iQuota = 1;
   /* object regVal = mRegistryHandler.GetValue(Constants.SIGNALPROCESSING_KEY, Constants.CENTROID_QUOTA_KEY);
    if (null != regVal)
        iQuota = (int)regVal;
    else
        iQuota = Constants.CENTROID_QUOTA;*/
    return iQuota;
}

bool CCentroid::GetRegCentroidApplyQuota()
{
    bool bApplyQuota = false;
   /* object regVal = mRegistryHandler.GetValue(Constants.SIGNALPROCESSING_KEY, Constants.CENTROID_APPLY_QUOTA_KEY);
    if (null != regVal)
        bApplyQuota = bool.Parse((string)regVal);
    else
        bApplyQuota = Constants.CENTROID_APPLY_QUOTA;*/
    return bApplyQuota;
}

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
bool CCentroid::CentroidPassFilter(double dInt, double dStart, double dStop, double dHeightMin, double dHeightMax, double dWidthMin, double dWidthMax)
{
    bool bOK = false;
    double dW = dStop - dStart;

    if ((dInt >= dHeightMin) && (dInt <= dHeightMax) && (dW >= dWidthMin) && (dW <= dWidthMax))
    {
        bOK = true;
    }
    return bOK;
}

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
//void CCentroid::FilterCentroids(vector<double> CX, vector<double> CY, vector<int> Start, vector<int> End,
 //   vector<double>& FCX, vector<double>& FCY, vector<int>& FStart, vector<int>& FEnd)
//{
    /*double Height = GetRegCentroidHeight();
    double HeightMax = GetRegCentroidHeightMax();
    int Width = GetRegCentroidWidth();
    int WidthMax = GetRegCentroidWidthMax();

    int iCounter = 0;
    int N = CX.Length;
    vector<double> tmpFCX(N,0);
    vector<double> tmpFCY(N,0);
    vector<int> tmpFStart(N,0);
    vector<int> tmpFEnd(N,0);

    FCX = null;
    FCY = null;
    FStart = null;
    FEnd = null;

    for (int i = 0; i < N; ++i)
    {
        if (CY[i] >= Height && CY[i] <= HeightMax && (End[i] - Start[i] + 1) >= Width && (End[i] - Start[i] + 1) <= WidthMax)
        {
			tmpFCX[iCounter] = CX[i];
			tmpFCY[iCounter] = CY[i];
			tmpFStart[iCounter] = Start[i];
			tmpFEnd[iCounter++] = End[i];
		}
	}

	if (iCounter > 0)
	{
		FCX.resize(iCounter,0);
        FCY.resize(iCounter,0);
        FStart.resize(iCounter,0);
        FEnd.resize(iCounter,0);
        --iCounter;
        mMathLCTR.CopyArrays(tmpFCX, out FCX, 0, iCounter);
        mMathLCTR.CopyArrays(tmpFCY, out FCY, 0, iCounter);
        mMathLCTR.CopyArrays(tmpFStart, out FStart, 0, iCounter);
        mMathLCTR.CopyArrays(tmpFEnd, out FEnd, 0, iCounter);
    }*/
//}

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
//void CCentroid::FilterCentroids(vector<double> CX, vector<double> CY, vector<int> Start, vector<int> End,
//	double XlimMin, double XlimMax,vector<double>& FCX, vector<double>& FCY, vector<int>& FStart, vector<int>& FEnd)
//{
    /*double Height    = GetRegCentroidHeight();
    double HeightMax = GetRegCentroidHeightMax();
    int Width        = GetRegCentroidWidth();
    int WidthMax     = GetRegCentroidWidthMax();

    int iCounter = 0;
    int N = CX.Length;
    vector<double> tmpFCX(N,0);
    vector<double> tmpFCY(N,0);
    vector<int> tmpFStart(N,0);
    vector<int> tmpFEnd(N,0);

    FCX = null;
    FCY = null;
    FStart = null;
    FEnd = null;

    for (int i = 0; i < N; ++i)
    {
        if (CY[i] >= Height && CY[i] <= HeightMax && (End[i] - Start[i] + 1) >= Width &&  (End[i] - Start[i] + 1) <= WidthMax)
        {
			if (CX[i] >= XlimMin && CX[i] <= XlimMax)
			{
				tmpFCX[iCounter] = CX[i];
				tmpFCY[iCounter] = CY[i];
				tmpFStart[iCounter] = Start[i];
				tmpFEnd[iCounter++] = End[i];
			}
		}
	}
	if (iCounter > 0)
    { 

        FCX.resize(iCounter,0);
        FCY.resize(iCounter,0);
        FStart.resize(iCounter,0);
        FEnd.resize(iCounter,0);
        --iCounter;
        mMathLCTR.CopyArrays(tmpFCX, out FCX, 0, iCounter);
        mMathLCTR.CopyArrays(tmpFCY, out FCY, 0, iCounter);
        mMathLCTR.CopyArrays(tmpFStart, out FStart, 0, iCounter);
        mMathLCTR.CopyArrays(tmpFEnd, out FEnd, 0, iCounter);
    }*/
//}

/*double CCentroid::GetRegCentroidWidth(string strUnits)
{
    double dWidth = 0;
    object regVal = null;
    switch (strUnits)
    {
        case (Constants.CENTROID_WIDTH_UNITS_MS):
            regVal = mRegistryHandler.GetValue(Constants.SIGNALPROCESSING_KEY, Constants.CENTROID_WIDTH_MS_KEY);
            if (null != regVal)
                dWidth = Convert.ToDouble((string)regVal);
            else
                dWidth = Constants.CENTROID_WIDTH_MS;
            break;
        case (Constants.CENTROID_WIDTH_UNITS_TH):
            regVal = mRegistryHandler.GetValue(Constants.SIGNALPROCESSING_KEY, Constants.CENTROID_WIDTH_TH_KEY);
			if (null != regVal)
				dWidth = Convert.ToDouble((string)regVal);
			else
				dWidth = Constants.CENTROID_WIDTH_TH;
			break;
		case (Constants.CENTROID_WIDTH_UNITS_VO):
			regVal = mRegistryHandler.GetValue(Constants.SIGNALPROCESSING_KEY, Constants.CENTROID_WIDTH_VO_KEY);
			if (null != regVal)
				dWidth = Convert.ToDouble((string)regVal);
			else
				dWidth = Constants.CENTROID_WIDTH_VO;
			break;
    }
	return dWidth;
}
*/
/*double CCentroid::GetRegCentroidWidthMax(string strUnits)
{
    double dWidth = 0;
    object regVal = null;
    switch (strUnits)
    {
        case (Constants.CENTROID_WIDTH_UNITS_MS):
            regVal = mRegistryHandler.GetValue(Constants.SIGNALPROCESSING_KEY, Constants.CENTROID_WIDTHMAX_MS_KEY);
			if (null != regVal)
				dWidth = Convert.ToDouble((string)regVal);
			else
				dWidth = Constants.CENTROID_WIDTHMAX_MS;
			break;
		case (Constants.CENTROID_WIDTH_UNITS_TH):
			regVal = mRegistryHandler.GetValue(Constants.SIGNALPROCESSING_KEY, Constants.CENTROID_WIDTHMAX_TH_KEY);
			if (null != regVal)
				dWidth = Convert.ToDouble((string)regVal);
			else
				dWidth = Constants.CENTROID_WIDTHMAX_TH;
			break;
        case (Constants.CENTROID_WIDTH_UNITS_VO):
            regVal = mRegistryHandler.GetValue(Constants.SIGNALPROCESSING_KEY, Constants.CENTROID_WIDTHMAX_VO_KEY);
			if (null != regVal)
				dWidth = Convert.ToDouble((string)regVal);
			else
				dWidth = Constants.CENTROID_WIDTHMAX_VO;
			break;
    }
    return dWidth;
}
*/
int CCentroid::GetRegCentroidWidth()
{
    int Width = 0;
   /* object regVal = mRegistryHandler.GetValue(Constants.SIGNALPROCESSING_KEY, Constants.CENTROID_WIDTH_KEY);
    if (null != regVal)
        Width = Convert.ToInt32((string)regVal);
    else
        Width = Constants.CENTROID_WIDTH;*/
    return Width;
}

int CCentroid::GetRegCentroidWidthMax()
{
    int Width = 0;
	/* object regVal = mRegistryHandler.GetValue(Constants.SIGNALPROCESSING_KEY, Constants.CENTROID_WIDTHMAX_KEY);
	if (null != regVal)
	Width = Convert.ToInt32((string)regVal);
	else
	Width = Constants.CENTROID_WIDTHMAX;*/
    return Width;
}

/*string CCentroid::GetCentroidMethod()
{
    string strMethod;
    object regVal = mRegistryHandler.GetValue(Constants.SIGNALPROCESSING_KEY, Constants.CENTROID_METHOD_KEY);
	if (null != regVal)
	strMethod = (string)regVal;
	else
    strMethod = Constants.CENTROID_TYPE_THRESH_25;
    return strMethod;
}*/

bool CCentroid::GetUseBaselineChoice()
{
    bool bUseBl=false;
	/*object regVal = mRegistryHandler.GetValue(Constants.SIGNALPROCESSING_KEY, Constants.CENTROID_USEBTHRESH_KEY);
	if (null != regVal)
	bUseBl = bool.Parse((string)regVal);
	else
	bUseBl = true;*/
    return bUseBl;
}

double CCentroid::GetRegCentroidHeight()
{
    double Height = 0;
	/*object regVal = mRegistryHandler.GetValue(Constants.SIGNALPROCESSING_KEY, Constants.CENTROID_HEIGHT_KEY);
	if (null != regVal)
	Height = Convert.ToDouble((string)regVal);
	else
	Height = Constants.CENTROID_HEIGHT;*/
    return Height;
}

double CCentroid::GetRegCentroidHeightMax()
{
    double Height = 0;
	/*object regVal = mRegistryHandler.GetValue(Constants.SIGNALPROCESSING_KEY, Constants.CENTROID_HEIGHTMAX_KEY);
	if (null != regVal)
	Height = Convert.ToDouble((string)regVal);
	else
	Height = Constants.CENTROID_HEIGHTMAX;*/
    return Height;
}

int CCentroid::GetRegGradSmooth()
{
    int dVal=0;
	/*object regVal = mRegistryHandler.GetValue(Constants.SIGNALPROCESSING_KEY, Constants.CENTROID_GRADSMOOTH_KEY);
	if (null != regVal)
	dVal = (int)regVal;
	else
	dVal = Constants.CENTROID_GRADSMOOTH;*/
    return dVal;
}

double CCentroid::GetUserThreshold()
{
    double dVal=0;
    /*object regVal = mRegistryHandler.GetValue(Constants.SIGNALPROCESSING_KEY, Constants.CENTROID_THRESH_KEY);
    if (null != regVal)
    {
        if (!double.TryParse((string)regVal, out dVal))
            dVal = Constants.CENTROID_USER_THRESHOLD;
    }
    else
        dVal = Constants.CENTROID_USER_THRESHOLD;*/
    return dVal;
}


//
//    public class CentroidPeak : IComparable
//    {
//        double mdX, mdY;
//        int miStart, miEnd;
//
//        public CentroidPeak(double dX, double dY, int iStart, int iEnd)
//        {
//            mdX = dX;
//            mdY = dY;
//            miStart = iStart;
//            miEnd = iEnd;
//        }
//
//        public int CompareTo(object o)
//        {
//            CentroidPeak cp = (CentroidPeak)o;
//            return mdY.CompareTo(cp.mdY);
//        }
//
//        public void UpdateArray(vector<double>& dX, vector<double>& dY, vector<int>& iStart, vector<int>& iEnd, int iInd)
//        {
//            dX[iInd] = mdX;
//            dY[iInd] = mdY;
//            iStart[iInd] = miStart;
//            iEnd[iInd] = miEnd;
//        }
//
//    }
//}
