#include "CSmoothingFilter.h"
#include <math.h>
//double HighFrequencyFilter::Filter(double )
//{
//
//}
void HighFrequencyFilter::FindPercDiffs(vector<double>const& dOrd, vector<double>& arrdDiffs)
{
	arrdDiffs.resize(dOrd.Length - 1,0);
	for (int i = 1; i < (int)(dOrd.Length); i++)
	{
		double dTmp;
        (void)dTmp;
		if (dOrd[i - 1] > 0)
			dTmp = dOrd[i - 1];
		else if (dOrd[i] > 0)
			dTmp = dOrd[i];
		else
		{
			arrdDiffs[i - 1] = 0;
			continue;
		}
		if(dOrd[i - 1]==0)
			arrdDiffs[i - 1]=0;//srls2015.1.8 xz
		else
			arrdDiffs[i - 1] = (dOrd[i] - dOrd[i - 1]) * 100 / dOrd[i - 1];
	}
}
//vector<int> HighFrequencyFilter::SetIndices(vector<double> arrdDiffs,int nPointFilter)
//{
//	double dTh = 0.1;
//	double dNTh = -dTh;
//	vector<int> ispeak(arrdDiffs.size(),0);
//	int npoint=(int)(arrdDiffs.Length)-nPointFilter+1;
//	for (int j=0;j<npoint;j++)
//	{
//		for (int i=j;i<nPointFilter;i++)
//		{
//			if (arrdDiffs[i]<dNTh)
//				ispeak[i]--;
//			else if (arrdDiffs[i]>dTh)
//				ispeak[i]++;
//		}
//	}
//	return ispeak;
//}
//void HighFrequencyFilter::SetIndices(vector<double>& dOrd, int SearchIndex, vector<double> ispeak, int& istart,
//	int& iend, int& iV, double& dPeakInt,double baseLine,int nPointFilter)
//{
//	int npoint=(int)(ispeak.Length)-1;
//	for (int i=1;i<npoint;i++)
//	{
//		if (ispeak[i]<nPointFilter&&ispeak[i]>-nPointFilter)
//		{
//			if ((ispeak[i-1]>=nPointFilter)&&(ispeak[i+1]!=-nPointFilter))
//			{
//			} 
//			else
//			{
//			}
//		}
//		else if (ispeak[i]<nPointFilter&&ispeak[i]>0)
//		{
//		}
//	}
//}
//void HighFrequencyFilter::SetIndices(vector<double>& dOrd, int SearchIndex, vector<double> arrdDiffs, int& istart,
//	int& iend, int& iV, double& dPeakInt,double baseLine,int nPointFilter)
//{
//	double dTh = 0.1; //of a 1% diff
//	double dNTh = -1 * dTh;
//	double dOrdN = dOrd[SearchIndex];
//	double dOrdmin1 = dOrd[SearchIndex - 1];
//	double dOrdplus1 = dOrd[SearchIndex + 1];
//	int aaaaaaa1=0;
//
//		for (int i=SearchIndex;i<nPointFilter;i++)
//		{
//			if (arrdDiffs[i]<dNTh)
//			{
//				aaaaaaa1--;
//			} 
//			else
//			{
//				aaaaaaa1++;
//			}
//		}
//
//	if (SearchIndex == 1 && arrdDiffs[SearchIndex - 1] > dTh && arrdDiffs[SearchIndex + 1] > 0)
//		istart = SearchIndex;
//
//	if ()
//	{
//	}
//	if (SearchIndex == 1 && arrdDiffs[SearchIndex - 1] > dTh && dOrdmin1 > 0)
//		istart = SearchIndex;
//	else if (abs(arrdDiffs[SearchIndex - 1]) < dTh && arrdDiffs[SearchIndex] > dTh)
//	{
//		istart = SearchIndex;
//		dPeakInt = 0;
//	}
//	else if (arrdDiffs[SearchIndex - 1] < dNTh && abs(arrdDiffs[SearchIndex]) < dTh && istart > -1)
//	{
//		iend = SearchIndex;
//	}
//	else if (arrdDiffs[SearchIndex - 1] > dTh && abs(arrdDiffs[SearchIndex]) < dTh)
//	{
//		if (iV > -1)
//		{
//			iV = -1;
//			istart = -1;
//			iend = -1;
//			dPeakInt = 0;
//		}
//	}
//	else if (arrdDiffs[SearchIndex - 1] < dNTh && arrdDiffs[SearchIndex] > dTh)
//	{
//		if (istart > -1)
//		{
//			if(SearchIndex-istart<nPointFilter)//2015.1.08 xz
//			{
//				for (int i=istart;i<=SearchIndex;i++)
//				{
//					dOrd[i]=baseLine;
//				}	
//			}
//			iend = SearchIndex;
//			iV = SearchIndex;
//		}
//		else
//		{
//			istart = SearchIndex;
//			iV = SearchIndex;
//			dPeakInt = 0;
//		}
//	}
//	else if (arrdDiffs[SearchIndex - 1] > dTh && arrdDiffs[SearchIndex] < dNTh)
//		dPeakInt = dOrdN;
//	else if (abs(arrdDiffs[SearchIndex - 1]) < dTh && arrdDiffs[SearchIndex] < dNTh)
//	{
//		if (istart > -1)
//		{
//			double dTmp = 0;
//			if (dOrdmin1 > dOrdN)
//				dTmp = dOrdmin1;
//			else
//				dTmp = dOrdN;
//			if(dTmp > dPeakInt)
//				dPeakInt = dTmp;
//		}
//	}
//}
bool HighFrequencyFilter::SetCentroidValues(int& istart, int& iend, int& iV)////,double& dPeakInt
{
	bool bI = false;
	if (iend > istart && istart > -1)
	{
		if (iV > -1)
		{
			istart = iV;
			bI = true;
			//dPeakInt = 0;
		}
		else
			istart = -1;
		iend = -1;
		iV = -1;
	}
	return bI;
}
vector<double> HighFrequencyFilter::Filter(vector<double>const& data,double baseLine,int nPointFilter)
{
	vector<double> dataOut(data.size(),baseLine);
	vector<double> arrdDiffs;
	FindPercDiffs(data,arrdDiffs);

	int istart = -1, iend = -1, iV = -1;
	int nlength=(int)(data.Length)-2;
	for(int SearchIndex = 1;SearchIndex < nlength;++SearchIndex)
	{
		SetIndices(dataOut,data, SearchIndex, arrdDiffs, istart,iend, iV, nPointFilter);//dPeakInt, bReset, 
		SetCentroidValues(istart,iend, iV);
	}
	return dataOut;
}

void HighFrequencyFilter::SetIndices(vector<double>& outFilter,vector<double>const& dOrd, int SearchIndex, vector<double>const& arrdDiffs, int& istart,
	int& iend, int& iV, int nPointFilter)//double& dPeakInt,bool& bReset,
{
	double dTh = 0.1; //of a 1% diff
	double dNTh = -1 * dTh;
//	double dOrdN = dOrd[SearchIndex];
	double dOrdmin1 = dOrd[SearchIndex - 1];
//	double dOrdplus1 = dOrd[SearchIndex + 1];
	if (arrdDiffs[SearchIndex - 1] > dNTh && arrdDiffs[SearchIndex - 1] < dTh)
	{
		if(arrdDiffs[SearchIndex] > dTh)
			istart = SearchIndex;
		return;
	}
	else if (arrdDiffs[SearchIndex - 1] > dTh)
	{
		if (SearchIndex == 1 &&dOrdmin1 > 0)
			istart = SearchIndex; 
		else if (arrdDiffs[SearchIndex]>dNTh && arrdDiffs[SearchIndex] < dTh)
		{
			if (iV > -1)
			{
				iV = -1;
				istart = -1;
				iend = -1;
			}
		}
		return;
	}
	else if (arrdDiffs[SearchIndex - 1] < dNTh)
	{
		if (arrdDiffs[SearchIndex]>dNTh && arrdDiffs[SearchIndex] < dTh && istart > -1)
		{
			if(SearchIndex-istart>=nPointFilter)
			{
				iend = SearchIndex;
				for (int i=istart;i<=iend;i++)
					outFilter[i]=dOrd[i];
			}
		} 
		else if (arrdDiffs[SearchIndex] > dTh)
		{
			if (istart > -1)
			{
				if(SearchIndex-istart>=nPointFilter)
				{
					iend = SearchIndex;
					iV = SearchIndex;
					for (int i=istart;i<=iend;i++)
						outFilter[i]=dOrd[i];
				}
			}
			else
			{
				istart = SearchIndex;
				iV = SearchIndex;
			}
		}
		return;
	}
}
vector<double> MovingAverageFilter::Filter(vector<double>& data,int width)//
{
    int dataSize = data.size();
    if(mbuffer.size()!=dataSize){
        mbuffer.resize(dataSize,0);
        mTempBuff.resize(dataSize,0);
    }
    //vector<double> s(dataSize,0);
    //double* s2 = new double[dataSize];
    int i;
    double count = 0;
    double r = 0;
    int midPt = width / 2;

    // only odd widths allowed (not 1)
    if (((width % 2) == 0) || (width <= 1) || (width >= dataSize)){
        memcpy(mbuffer.data(),data.data(),dataSize*sizeof(double));
        return mbuffer;
    }

    // square the data to improve resolution
    for (i = 0; i < dataSize; i++){
        if (data[i] > 0)
            mTempBuff[i] = data[i] * data[i];
        else
            mTempBuff[i] = -1 * data[i] * data[i];
    }

    for (i = 0; i < dataSize; i++){
        if (i < midPt || i > dataSize - midPt - 1)
        {
            // can't apply box, too close to left end or right end
            // just pass back unaveraged point
            if (mTempBuff[i] > 0)
                mbuffer[i] = sqrt(mTempBuff[i]);
            else
                mbuffer[i] = -1 * (sqrt(-1 * mTempBuff[i]));
        }else{
            // scan the box (the midpoint of which is the point to average)
            // Highest weight is assigned to that one, decreasing in size
            // the futher away we get from it)
            count = 0;
            r = 0;
            for (int j = -midPt; j <= midPt; j++){
                r += mTempBuff[i + j];
                count++;
            }

            // square root the result (the original input data was
            // artificially squared)
            if (r > 0)
                mbuffer[i] = sqrt(r / count);
            else
                mbuffer[i] = -1 * (sqrt(-1 * r / count));
        }
    }
    //delete [] s2;
    //s2=nullptr;
    return mbuffer;

}
vector<double> WeightedMovingAverageFilter::Filter(vector<double>& data,int width)
{
    int dataSize = data.size();
    vector<double> s(dataSize,0);
    double* s2 = new double[dataSize];
	int i;
	double count = 0;
	double r = 0;
	int midPt = width / 2;
	double weight = 1;

	// only odd widths allowed (not 1)
    if (((width % 2) == 0) || (width <= 1) || (width >= dataSize)){
        memcpy(s.data(),data.data(),dataSize*sizeof(double));
        return s;
    }

	// square the data to improve resolution
    for (i = 0; i < dataSize; i++){
		if (data[i] > 0)
			s2[i] = data[i] * data[i];
		else
			s2[i] = -1 * data[i] * data[i];
	}

    for (i = 0; i < dataSize; i++){
        if (i < midPt || i > dataSize - midPt - 1){
			// can't apply box, too close to left end or right end
			// just pass back unaveraged point
			if (s2[i] > 0)
				s[i] = sqrt(s2[i]);
			else
				s[i] = -1 * (sqrt(-1 * s2[i]));
        }else{
			// scan the box (the midpoint of which is the point to average)
			// Highest weight is assigned to that one, decreasing in size
			// the futher away we get from it)
			count = 0;
			r = 0;
			weight = 1;

            for (int j = -midPt; j <= midPt; j++){
				r += weight * s2[i + j];
				count += weight;
				if (j < 0)
					weight *= 2;
				else
					weight /= 2;
			}
			// square root the result (the original input data was
			// artificially squared)
			if (r > 0)
				s[i] = sqrt(r / count);
			else
				s[i] = -1 * (sqrt(-1 * r / count));
		}
	}
	return s;

}
vector<double> SavitzkyGolayFilter::Filter(vector<double>& Val,int K, int F)
{
    //vector<double> Output;
	if (nullptr == mSGFilter)
		mSGFilter = new SGF(K, F);
	else
		mSGFilter->SetParams(K, F);
	int rem;
	int N = Val.size();
    if (mSGFilter->SanityCheck()){
		Output.resize(N,0);
        for (int i = 0; i < N; ++i){
			// Slide window across signal
            Window.resize (F,0);
			int Z = MyMath::DivRem(F, 2, rem);
            if (i < Z){
				// Window fallen off the front. Pad with zeros.
				int k = 0;
                for (int j = i - Z; j <= i + Z; ++j){
					if (j < 0)
						Window[k++] = 0;
					else
						Window[k++] = Val[j];
				}
            }else if (i + Z >= N){
				// Window fallen off the back. Pad with zeros.
				int k = 0;
                for (int j = i - Z; j <= i + Z; ++j){
					if (j < N)
						Window[k++] = Val[j];
					else
						Window[k++] = 0;
				}
            }else{
				int k = 0;
				for (int j = i - Z; j <= i + Z; ++j)
					Window[k++] = Val[j];
			}
			Output[i] = mSGFilter->Filter(Window);
		}
    }else
        memcpy(Output.data(),Val.data(),N*sizeof(double));
	return Output;
}
SGF::SGF(){
	mK=0;
	mF=0;
	NFIVE=35;
	NSEVEN[0]=21;
	NSEVEN[1]
	=NNINE[0]=231;
	NNINE[1]
	=NELEVEN[0]
	=NELEVEN[1]=429;

	int iFIVE[5]		={ -3, 12, 17, 12, -3 };
	int iSEVEN[2][7]	= { { -2, 3, 6, 7, 6, 3, -2 }, { 5, -30, 75, 131, 75, -30, 5 } };
	int iNINE[2][9]	= { { -21, 14, 39, 54, 59, 54, 39, 14, -21 }, { 15, -55, 30, 135, 179, 135, 30, -55, 15 } };
	int iELEVEN[2][11]	= { { -36, 9, 44, 69, 84, 89, 84, 69, 44, 9, -36 }, { 48, -45, -10, 60, 120, 143, 120, 60, -10, -45, 18 } };
	for(int i=0;i<5;i++)						FIVE[i]=iFIVE[i];
	for(int j=0;j<2;j++) for (int i=0;i<7;i++)	SEVEN[j][i]=iSEVEN[j][i];
	for(int j=0;j<2;j++) for (int i=0;i<9;i++)	NINE[j][i]=iNINE[j][i];
	for(int j=0;j<2;j++) for (int i=0;i<11;i++) ELEVEN[j][i]=iELEVEN[j][i];
}
SGF::SGF(int K, int F)
{
    mK=K;
    mF=F;
    NFIVE=35;
    NSEVEN[0]=21;
    NSEVEN[1]
    =NNINE[0]=231;
    NNINE[1]
    =NELEVEN[0]
    =NELEVEN[1]=429;

    int iFIVE[5]		={ -3, 12, 17, 12, -3 };
    int iSEVEN[2][7]	= { { -2, 3, 6, 7, 6, 3, -2 }, { 5, -30, 75, 131, 75, -30, 5 } };
    int iNINE[2][9]	= { { -21, 14, 39, 54, 59, 54, 39, 14, -21 }, { 15, -55, 30, 135, 179, 135, 30, -55, 15 } };
    int iELEVEN[2][11]	= { { -36, 9, 44, 69, 84, 89, 84, 69, 44, 9, -36 }, { 48, -45, -10, 60, 120, 143, 120, 60, -10, -45, 18 } };
    for(int i=0;i<5;i++)						FIVE[i]=iFIVE[i];
    for(int j=0;j<2;j++) for (int i=0;i<7;i++)	SEVEN[j][i]=iSEVEN[j][i];
    for(int j=0;j<2;j++) for (int i=0;i<9;i++)	NINE[j][i]=iNINE[j][i];
    for(int j=0;j<2;j++) for (int i=0;i<11;i++) ELEVEN[j][i]=iELEVEN[j][i];
}

bool SGF::SanityCheck()
{
	bool bIsSane = false;
	int rem;
	MyMath::DivRem(mF, 2, rem);
	if (mF > 4 && mF < 12 && rem == 1 && mF > mK && mK > 1 && mK < 6)
		bIsSane = true;
	return bIsSane;
}

double SGF::Filter(vector<double>& Val)
{
	double Output = 0;
	int Vsize=Val.size();
    switch (mF){
	case 5:
		for (int i = 0; i < Vsize; ++i)
			Output += Val[i] * FIVE[i];
		Output /= NFIVE;
		break;
	case 7:
		switch (mK)
		{
		case 2:
		case 3:
            Output = FilterLoop(Val, Output, (int*)SEVEN, NSEVEN, 0);
			break;
		case 4:
		case 5:
            Output = FilterLoop(Val, Output, (int*)SEVEN, NSEVEN, 1);
			break;
		}
		break;
	case 9:
		switch (mK)
		{
		case 2:
		case 3:
            Output = FilterLoop(Val, Output, (int*)NINE, NNINE, 0);
			break;
		case 4:
		case 5:
            Output = FilterLoop(Val, Output, (int*)NINE, NNINE, 1);
			break;
		}
		break;
	case 11:
		switch (mK)
		{
		case 2:
		case 3:
            Output = FilterLoop(Val, Output, (int*)ELEVEN, NELEVEN, 0);
			break;
		case 4:
		case 5:
            Output = FilterLoop(Val, Output, (int*)ELEVEN, NELEVEN, 1);
			break;
		}
		break;
	}
	return Output;

}
/**
double FilterLoop(double[] Val, double Output, int[,] Table, int[] NTable, int Index)
{
    for (int i = 0; i < Val.Length; ++i)
    {
        int temp = Table[Index, i];
        Output += Val[i] * Table[Index, i];
    }
    Output /= NTable[Index];
    return Output;
}
*/
double SGF::FilterLoop(vector<double>& Val, double Output, int* Table, int* NTable, int Index)
{
	int Vsize=Val.size();
	for (int i = 0; i < Vsize; ++i)
        Output += Val[i] * *(Table+Index*Vsize+i);
	Output /= NTable[Index];
	return Output;
}

