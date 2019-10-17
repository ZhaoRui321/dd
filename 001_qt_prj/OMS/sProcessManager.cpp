#include "sProcessManager.h"

sProcessManager::sProcessManager()
{

}

sProcessManager::~sProcessManager()
{

}

void sProcessManager::setMethod(const QString& strSructMethod,MethodParam& mMethodParam)
{
    if(!(strSructMethod.isEmpty()))
        mMethodParam.ListParam=strSructMethod.split('+');
    else
        mMethodParam.ListParam.clear();
    if(mMethodParam.uVersion==9999)
        mMethodParam.uVersion=0;
    else
        mMethodParam.uVersion++;
}

MethodParam sProcessManager::setMethod(const QString& strSructMethod)
{
    MethodParam mMethodParam;
    if(!(strSructMethod.isEmpty()))
        mMethodParam.ListParam=strSructMethod.split('+');
    else
        mMethodParam.ListParam.clear();
    if(mMethodParam.uVersion==9999)
        mMethodParam.uVersion=0;
    else
        mMethodParam.uVersion++;
    return mMethodParam;
}

void sProcessManager::setParam(const MethodParam& mMethodParam,MapFilterData& mFilterData)
{
    static uint uParamVersion = 0;
    int nsizeKey=0;
    nsizeKey=mFilterData.Key.size();
    if(uParamVersion!=mMethodParam.uVersion){
        for(int countKey=0;countKey<nsizeKey;countKey++){
            switch(mFilterData.Key[countKey]){
            case FilterDataType::MovingAverage:{
                if(!mFilterData.Value.isEmpty())
                    delete (FilterMovingAverage*)mFilterData.Value[countKey];
                break;}
            case FilterDataType::SavGol:{
                if(!mFilterData.Value.isEmpty())
                    delete (FilterSavGol*)mFilterData.Value[countKey];
                break;}
            case FilterDataType::FrameAverage:{
                if(!mFilterData.Value.isEmpty())
                    delete (FilterFrameAverage*)mFilterData.Value[countKey];
                break;}
            case FilterDataType::GainOffset:{
                if(!mFilterData.Value.isEmpty())
                    delete (FilterGainOffset*)mFilterData.Value[countKey];
                break;}
            }
        }
        //}
        mFilterData.Key.clear();
        mFilterData.Value.clear();
        if(!(mMethodParam.ListParam.isEmpty())){
            foreach(auto strParam,mMethodParam.ListParam){
                QStringList listParam=strParam.split(',');
                if(listParam[0].compare("MovingAverage", Qt::CaseInsensitive) == 0){
                    if(listParam.size()<2)
                        continue;
                    if(listParam[1].isEmpty())
                        continue;
                    FilterMovingAverage* pFilterMovingAverage=new FilterMovingAverage;
                    pFilterMovingAverage->DataParam1=listParam[1].toDouble();
                    mFilterData.Key.append(MovingAverage);
                    mFilterData.Value.append(pFilterMovingAverage);
                }else if(listParam[0].compare("SavGolFilt", Qt::CaseInsensitive) == 0){
                    if(listParam.size()<3)
                        continue;
                    if(listParam[1].isEmpty()||listParam[2].isEmpty())
                        continue;
                    FilterSavGol* pFilterSavGol=new FilterSavGol;
                    pFilterSavGol->DataParam1=listParam[1].toDouble();
                    pFilterSavGol->DataParam2=listParam[2].toInt();
                    mFilterData.Key.append(SavGol);
                    mFilterData.Value.append(pFilterSavGol);
                }else if(listParam[0].compare("FrameAverage", Qt::CaseInsensitive) == 0){
                    if(listParam.size()<2)
                        continue;
                    if(listParam[1].isEmpty())
                        continue;
                    FilterFrameAverage* pFilterFrameAverage=new FilterFrameAverage;
                    pFilterFrameAverage->DataParam1=listParam[1].toDouble();
                    mFilterData.Key.append(FrameAverage);
                    mFilterData.Value.append(pFilterFrameAverage);
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
                    mFilterData.Key.append(GainOffset);
                    mFilterData.Value.append(pFilterGainOffset);
                }
            }
        }
        uParamVersion=mMethodParam.uVersion;
    }
}
