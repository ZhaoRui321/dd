#include "cDataProcess.h"

//cDataProcess* cDataProcess::getDataProcess()
//{
//    static cDataProcess insDataProcess;
//    return &insDataProcess;
//}

void cDataProcess::updateMethod()
{
    if(mParamVersion!=mMethodParam.uVersion){
        int nsizeKey= mMapParam.Key.size();
        for(int countKey=0; countKey<nsizeKey; countKey++){
            switch(mMapParam.Key[countKey]){
            case FilterDataType::MovingAverage:{
                if(!mMapParam.Value.isEmpty())
                    delete (FilterMovingAverage*)mMapParam.Value[countKey];
                break;}
            case FilterDataType::SavGol:{
                if(!mMapParam.Value.isEmpty())
                    delete (FilterSavGol*)mMapParam.Value[countKey];
                break;}
            case FilterDataType::FrameAverage:{
                if(!mMapParam.Value.isEmpty())
                    delete (FilterFrameAverage*)mMapParam.Value[countKey];
                break;}
            case FilterDataType::GainOffset:{
                if(!mMapParam.Value.isEmpty())
                    delete (FilterGainOffset*)mMapParam.Value[countKey];
                break;}
            }
        }
        mMapParam.Key.clear();
        mMapParam.Value.clear();
        if(!(mMethodParam.ListParam.isEmpty())){
            foreach(auto strParam,mMethodParam.ListParam){
                QStringList listParam=strParam.split('&');
                if(listParam[0].compare("MovingAverage", Qt::CaseInsensitive) == 0){
                    if(listParam.size()<2)
                        continue;
                    if(listParam[1].isEmpty())
                        continue;
                    FilterMovingAverage* pFilterMovingAverage=new FilterMovingAverage;
                    pFilterMovingAverage->DataParam1=listParam[1].toDouble();
                    mMapParam.Key.append(MovingAverage);
                    mMapParam.Value.append(pFilterMovingAverage);
                }else if(listParam[0].compare("SavGolFilt", Qt::CaseInsensitive) == 0){
                    if(listParam.size()<3)
                        continue;
                    if(listParam[1].isEmpty()||listParam[2].isEmpty())
                        continue;
                    FilterSavGol* pFilterSavGol=new FilterSavGol;
                    pFilterSavGol->DataParam1=listParam[1].toDouble();
                    pFilterSavGol->DataParam2=listParam[2].toInt();
                    mMapParam.Key.append(SavGol);
                    mMapParam.Value.append(pFilterSavGol);
                }else if(listParam[0].compare("FrameAverage", Qt::CaseInsensitive) == 0){
                    if(listParam.size()<2)
                        continue;
                    if(listParam[1].isEmpty())
                        continue;
                    FilterFrameAverage* pFilterFrameAverage=new FilterFrameAverage;
                    pFilterFrameAverage->DataParam1=listParam[1].toDouble();
                    mMapParam.Key.append(FrameAverage);
                    mMapParam.Value.append(pFilterFrameAverage);
                }else if(listParam[0].compare("GainOffset", Qt::CaseInsensitive) == 0){
                    if(listParam.size()<3)
                        continue;
                    FilterGainOffset* pFilterGainOffset=new FilterGainOffset;
                    if(!listParam[1].isEmpty()){
                        pFilterGainOffset->DataParam1=listParam[1].toDouble();
                        pFilterGainOffset->bOffset=true;
                    }else
                        pFilterGainOffset->bOffset=false;
                    if(!listParam[2].isEmpty()){
                        pFilterGainOffset->DataParam2=listParam[2].toDouble();
                        pFilterGainOffset->bGain=true;
                    }else
                        pFilterGainOffset->bGain=false;
                    mMapParam.Key.append(GainOffset);
                    mMapParam.Value.append(pFilterGainOffset);
                }
            }
        }
        mParamVersion=mMethodParam.uVersion;
    }
}

void cDataProcess::setMethod(QString& strSructMethod)
{
    if(!(strSructMethod.isEmpty())){
        mMethodParam.ListParam=strSructMethod.split('+');
    }else{
        mMethodParam.ListParam.clear();
    }
    if(mMethodParam.uVersion >= 9999){
        mMethodParam.uVersion=0;
    }else{
        mMethodParam.uVersion++;
    }
}



bool cDataProcess::processData(std::vector<double>const& dataSrc, bool reStart)
{
    int nSize = dataSrc.size();
    mDataTmp.resize(nSize);
    memcpy(mDataTmp.data(),dataSrc.data(),sizeof(double)*nSize);

    int nsizeKey=mMapParam.Key.size();
    for(int countKey=0;countKey<nsizeKey;countKey++){
        switch(mMapParam.Key[countKey]){
        case FilterDataType::MovingAverage:{
            if(!mMapParam.Value.isEmpty()){
                FilterMovingAverage* pTemp=(FilterMovingAverage*)mMapParam.Value[countKey];
                mDataTmp=MovingAverageSmooth(
                            mDataTmp,(int)(pTemp->DataParam1));
            }
            break;}
        case FilterDataType::SavGol:{
            if(!mMapParam.Value.isEmpty()){
                FilterSavGol* pTemp=(FilterSavGol*)mMapParam.Value[countKey];
                mDataTmp=SavGolFilt(
                            mDataTmp,int(pTemp->DataParam1),pTemp->DataParam2);
            }
            break;}
        case FilterDataType::FrameAverage:{
            if(!mMapParam.Value.isEmpty()){
                FilterFrameAverage* pTemp=(FilterFrameAverage*)mMapParam.Value[countKey];
                if(reStart){
                    pTemp->mFrameAverage.ClearCounts();
                    mDataTmp=pTemp->mFrameAverage.frameAverage(mDataTmp,(int)(pTemp->DataParam1));
                }else
                    mDataTmp=pTemp->mFrameAverage.frameAverage(mDataTmp,(int)(pTemp->DataParam1));
            }
            break;}
        case FilterDataType::GainOffset:{
            if(!mMapParam.Value.isEmpty()){
                FilterGainOffset* pFilterGainOffset1=(FilterGainOffset*)(mMapParam.Value[countKey]);
                if(pFilterGainOffset1->bGain&&pFilterGainOffset1->bOffset){
                    for(int ii=0;ii<nSize;ii++)
                        mDataTmp[ii]=pFilterGainOffset1->DataParam2* mDataTmp[ii]+pFilterGainOffset1->DataParam1;
                }else if((!pFilterGainOffset1->bGain)&&pFilterGainOffset1->bOffset){
                    for(int ii=0;ii<nSize;ii++)
                        mDataTmp[ii]= mDataTmp[ii]+pFilterGainOffset1->DataParam1;
                }else if(pFilterGainOffset1->bGain&&(!pFilterGainOffset1->bOffset)){
                    for(int ii=0;ii<nSize;ii++)
                        mDataTmp[ii]=pFilterGainOffset1->DataParam2* mDataTmp[ii];
                }
            }
            break;}
        }
    }
    return true;
}

bool cDataProcess::processData(std::vector<double>const& dataSrc, std::vector<double>& dataDest, bool reStart)
{
    int nSize = dataSrc.size();
    mDataTmp.resize(nSize);
    memcpy(mDataTmp.data(),dataSrc.data(),sizeof(double)*nSize);

    int nsizeKey=mMapParam.Key.size();
    for(int countKey=0;countKey<nsizeKey;countKey++){
        switch(mMapParam.Key[countKey]){
        case FilterDataType::MovingAverage:{
            if(!mMapParam.Value.isEmpty()){
                FilterMovingAverage* pTemp=(FilterMovingAverage*)mMapParam.Value[countKey];
                mDataTmp=MovingAverageSmooth(
                            mDataTmp,(int)(pTemp->DataParam1));
            }
            break;}
        case FilterDataType::SavGol:{
            if(!mMapParam.Value.isEmpty()){
                FilterSavGol* pTemp=(FilterSavGol*)mMapParam.Value[countKey];
                mDataTmp=SavGolFilt(
                            mDataTmp,int(pTemp->DataParam1),pTemp->DataParam2);
            }
            break;}
        case FilterDataType::FrameAverage:{
            if(!mMapParam.Value.isEmpty()){
                FilterFrameAverage* pTemp=(FilterFrameAverage*)mMapParam.Value[countKey];
                if(reStart){
                    pTemp->mFrameAverage.ClearCounts();
                    mDataTmp=pTemp->mFrameAverage.frameAverage(mDataTmp,(int)(pTemp->DataParam1));
                }else
                    mDataTmp=pTemp->mFrameAverage.frameAverage(mDataTmp,(int)(pTemp->DataParam1));
            }
            break;}
        case FilterDataType::GainOffset:{
            if(!mMapParam.Value.isEmpty()){
                FilterGainOffset* pFilterGainOffset1=(FilterGainOffset*)(mMapParam.Value[countKey]);
                if(pFilterGainOffset1->bGain&&pFilterGainOffset1->bOffset){
                    for(int ii=0;ii<nSize;ii++)
                        mDataTmp[ii]=pFilterGainOffset1->DataParam2* mDataTmp[ii]+pFilterGainOffset1->DataParam1;
                }else if((!pFilterGainOffset1->bGain)&&pFilterGainOffset1->bOffset){
                    for(int ii=0;ii<nSize;ii++)
                        mDataTmp[ii]= mDataTmp[ii]+pFilterGainOffset1->DataParam1;
                }else if(pFilterGainOffset1->bGain&&(!pFilterGainOffset1->bOffset)){
                    for(int ii=0;ii<nSize;ii++)
                        mDataTmp[ii]=pFilterGainOffset1->DataParam2* mDataTmp[ii];
                }
            }
            break;}
        }
    }
    dataDest.resize(nSize);
    memcpy(dataDest.data(),mDataTmp.data(),sizeof(double)*nSize);
    return true;
}

bool cDataProcess::processData(double* dataSrc, int nSize, bool reStart)
{
    mDataTmp.resize(nSize);
    memcpy(mDataTmp.data(), dataSrc, sizeof(double)*nSize);
    int nsizeKey=mMapParam.Key.size();
    for(int countKey=0;countKey<nsizeKey;countKey++){
        switch(3){     // mMapParam.Key[countKey]){
        case FilterDataType::MovingAverage:{
            if(!mMapParam.Value.isEmpty()){
                FilterMovingAverage* pTemp=(FilterMovingAverage*)mMapParam.Value[countKey];
                mDataTmp=MovingAverageSmooth(
                            mDataTmp,(int)(pTemp->DataParam1));
            }
            break;}
        case FilterDataType::SavGol:{
            if(!mMapParam.Value.isEmpty()){
                FilterSavGol* pTemp=(FilterSavGol*)mMapParam.Value[countKey];
                mDataTmp=SavGolFilt(
                            mDataTmp,int(pTemp->DataParam1),pTemp->DataParam2);
            }
            break;}
        case FilterDataType::FrameAverage:{
            if(!mMapParam.Value.isEmpty()){
                FilterFrameAverage* pTemp=(FilterFrameAverage*)mMapParam.Value[countKey];
                if(reStart){
                    pTemp->mFrameAverage.ClearCounts();
                    mDataTmp=pTemp->mFrameAverage.frameAverage(mDataTmp,(int)(pTemp->DataParam1));
                }else
                    mDataTmp=pTemp->mFrameAverage.frameAverage(mDataTmp,(int)(pTemp->DataParam1));
            }
            break;}
        case FilterDataType::GainOffset:{
            if(!mMapParam.Value.isEmpty()){
                FilterGainOffset* pFilterGainOffset1=(FilterGainOffset*)(mMapParam.Value[countKey]);
                if(pFilterGainOffset1->bGain&&pFilterGainOffset1->bOffset){
                    for(int ii=0;ii<nSize;ii++)
                        mDataTmp[ii]=pFilterGainOffset1->DataParam2* mDataTmp[ii]+pFilterGainOffset1->DataParam1;
                }else if((!pFilterGainOffset1->bGain)&&pFilterGainOffset1->bOffset){
                    for(int ii=0;ii<nSize;ii++)
                        mDataTmp[ii]= mDataTmp[ii]+pFilterGainOffset1->DataParam1;
                }else if(pFilterGainOffset1->bGain&&(!pFilterGainOffset1->bOffset)){
                    for(int ii=0;ii<nSize;ii++)
                        mDataTmp[ii]=pFilterGainOffset1->DataParam2* mDataTmp[ii];
                }
            }
            break;}
        }
    }
    memcpy(dataSrc,mDataTmp.data(),sizeof(double)*nSize);
    return true;
}

bool cDataProcess::processData(double* dataSrc, double* dataDest, int nSize, bool reStart)
{
    mDataTmp.resize(nSize);
    memcpy(mDataTmp.data(), dataSrc, sizeof(double)*nSize);
    int nsizeKey=mMapParam.Key.size();
    for(int countKey=0;countKey<nsizeKey;countKey++){
        switch(mMapParam.Key[countKey]){
        case FilterDataType::MovingAverage:{
            if(!mMapParam.Value.isEmpty()){
                FilterMovingAverage* pTemp=(FilterMovingAverage*)mMapParam.Value[countKey];
                mDataTmp=MovingAverageSmooth(
                            mDataTmp,(int)(pTemp->DataParam1));
            }
            break;}
        case FilterDataType::SavGol:{
            if(!mMapParam.Value.isEmpty()){
                FilterSavGol* pTemp=(FilterSavGol*)mMapParam.Value[countKey];
                mDataTmp=SavGolFilt(
                            mDataTmp,int(pTemp->DataParam1),pTemp->DataParam2);
            }
            break;}
        case FilterDataType::FrameAverage:{
            if(!mMapParam.Value.isEmpty()){
                FilterFrameAverage* pTemp=(FilterFrameAverage*)mMapParam.Value[countKey];
                if(reStart){
                    pTemp->mFrameAverage.ClearCounts();
                    mDataTmp=pTemp->mFrameAverage.frameAverage(mDataTmp,(int)(pTemp->DataParam1));
                }else
                    mDataTmp=pTemp->mFrameAverage.frameAverage(mDataTmp,(int)(pTemp->DataParam1));
            }
            break;}
        case FilterDataType::GainOffset:{
            if(!mMapParam.Value.isEmpty()){
                FilterGainOffset* pFilterGainOffset1=(FilterGainOffset*)(mMapParam.Value[countKey]);
                if(pFilterGainOffset1->bGain&&pFilterGainOffset1->bOffset){
                    for(int ii=0;ii<nSize;ii++)
                        mDataTmp[ii]=pFilterGainOffset1->DataParam2* mDataTmp[ii]+pFilterGainOffset1->DataParam1;
                }else if((!pFilterGainOffset1->bGain)&&pFilterGainOffset1->bOffset){
                    for(int ii=0;ii<nSize;ii++)
                        mDataTmp[ii]= mDataTmp[ii]+pFilterGainOffset1->DataParam1;
                }else if(pFilterGainOffset1->bGain&&(!pFilterGainOffset1->bOffset)){
                    for(int ii=0;ii<nSize;ii++)
                        mDataTmp[ii]=pFilterGainOffset1->DataParam2* mDataTmp[ii];
                }
            }
            break;}
        }
    }
    //dataDest.resize(nSize);
    memcpy(dataDest,mDataTmp.data(),sizeof(double)*nSize);
    return true;
}

void cDataProcess::sortVector(std::vector<double>& xData, std::vector<double>& yData)
{
    int size = xData.size();
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size -1 -i; j++)
        {
            if(xData[j] < xData[j+1]){
                double temp = xData[j+1];
                xData[j+1] = xData[j];
                xData[j] = temp;

                temp = yData[j+1];
                yData[j+1] = yData[j];
                yData[j] = temp;
            }
        }
}
