#include "cLoadDataFile.h"
#include <QDir>
#include <math.h>

cLoadDataFile::cLoadDataFile()
{

}

bool cLoadDataFile::loadFileTIC(const char* pFilePath, const int lengthPath,
                                double** pDataTIC, long& lengthTIC,
                                double** pDataMass, long& lengthMass)
{
    //QByteArray tmpFilePath(pFilePath, lengthPath);
    QString filePath(QString::fromUtf8(QByteArray(pFilePath, lengthPath)));
    if(!filePath.isEmpty()){
        QFile tmpDataFileTIC(filePath);
        //long sizePoint= tmpDataFileTIC.size()/2;
        //mDataTIC_X.resize(sizePoint);
        //mDataTIC_Y.resize(sizePoint);
        try{
            if(!tmpDataFileTIC.open(QIODevice::ReadOnly | QIODevice::Text))
                return false;
            else{
                mDataTIC=tmpDataFileTIC.readAll();
                QList<QByteArray> tmpList=mDataTIC.split('\n');
                long listSize=tmpList.size();
                mDataTIC_X.resize(listSize);
                mDataTIC_Y.resize(listSize);
                QList<QByteArray> tmpList1;
                --listSize;
                for(int i=0;i<listSize;++i){
                    tmpList1= tmpList[i].split('\t');
                    mDataTIC_X[i]=tmpList1[0].toDouble();
                    mDataTIC_Y[i]=tmpList1[1].toDouble();
                }
            }
        }catch(...){
            return false;
        }
    }
}

bool cLoadDataFile::loadFileTIC(QString pFilePath,QVector<double>& pDataTIC_X,QVector<double>& pDataTIC_Y)
{
    if(!pFilePath.isEmpty()){
        QFile tmpDataFileTIC(pFilePath);
        try{
            if(!tmpDataFileTIC.open(QIODevice::ReadOnly | QIODevice::Text))
                return false;
            else{
                mDataTIC=tmpDataFileTIC.readAll();
                tmpDataFileTIC.close();
            }
        }catch(...){
            return false;
        }
        QList<QByteArray> tmpList=mDataTIC.split('\n');
        long listSize=tmpList.size();
        if(listSize<=0)
            return false;
        pDataTIC_X.resize(listSize);
        pDataTIC_Y.resize(listSize);
        QList<QByteArray> tmpList1;
        --listSize;
        for(int i=0;i<listSize;++i){
            tmpList1= tmpList[i].split('\t');
            pDataTIC_X[i]=tmpList1[0].toDouble();
            pDataTIC_Y[i]=tmpList1[1].toDouble();
        }
        return true;
    }
    return false;
}
bool cLoadDataFile::loadFileTIC(QString pFilePath,std::vector<double>& pDataTIC_X,std::vector<double>& pDataTIC_Y)
{
    if(!pFilePath.isEmpty()){
        QFile tmpDataFileTIC(pFilePath);
        try{
            if(!tmpDataFileTIC.open(QIODevice::ReadOnly | QIODevice::Text))
                return false;
            else{
                mDataTIC=tmpDataFileTIC.readAll();
                tmpDataFileTIC.close();
            }
        }catch(...){
            return false;
        }
        QList<QByteArray> tmpList=mDataTIC.split('\n');
        long listSize=tmpList.size()-1;//last is empty
        if(listSize<=0)
            return false;
        pDataTIC_X.resize(listSize);
        pDataTIC_Y.resize(listSize);
        QList<QByteArray> tmpList1;
        //--listSize;
        for(int i=0;i<listSize;++i){
            tmpList1= tmpList[i].split('\t');
            pDataTIC_X[i]=tmpList1[0].toDouble();
            pDataTIC_Y[i]=tmpList1[1].toDouble();
        }
        return true;
    }
    return false;
}

bool cLoadDataFile::loadFileMass(QString pFilePath, int index, QVector<double>& pData,QByteArray& pStreamHead)
{
    if(!pFilePath.isEmpty()){
        uint sizeHead=sizeof(_StreamHead);
        QFile tmpDataFileMass(pFilePath);
        //QByteArray tmpStreamHead(sizeHead);
        pStreamHead.resize(sizeHead);
        //_StreamHead* pStreamHead;
        try{
            if(!tmpDataFileMass.open(QIODevice::ReadOnly | QIODevice::Truncate))
                return false;
        }catch(...){
            return false;
        }
        try{
            if(sizeHead!= tmpDataFileMass.read(pStreamHead.data(), sizeHead)){
                tmpDataFileMass.close();
                return false;
            }else{
                _StreamHead* tmpStreamHead= (_StreamHead*)(pStreamHead.data());
                sizeHead= tmpStreamHead->length;
                pStreamHead.resize(sizeHead);
                tmpStreamHead= (_StreamHead*)(pStreamHead.data());
                tmpDataFileMass.seek(0);
                if(sizeHead!= tmpDataFileMass.read(pStreamHead.data(), sizeHead)){
                    tmpDataFileMass.close();
                    return false;
                }else{
                    sizeHead= tmpStreamHead->length;//debug
                }
            }
        }catch(...){
            return false;
        }
        uint sizeBody=sizeof(_StreamBody);
        QByteArray tmpStreamBody;
        tmpStreamBody.resize(sizeBody);
        qint64 sizeData=0;
        try{
            tmpDataFileMass.seek(sizeHead);
            if(sizeBody!= tmpDataFileMass.read(tmpStreamBody.data(),sizeBody)){
                tmpDataFileMass.close();
                return false;
            }else{
                _StreamBody* pStreamBody= reinterpret_cast<decltype(pStreamBody)>(tmpStreamBody.data());
                //_StreamBody* pStreamBody= (_StreamBody*)(tmpStreamBody.data());
                sizeData= pStreamBody->length- sizeBody;
            }
        }catch(...){
            tmpDataFileMass.close();
            return false;
        }
        if(sizeData>0){
            pData.resize(sizeData/sizeof(double)-1);//remove end point
            try{
//                tmpDataFileMass.seek(sizeHead+(sizeBody+sizeData)*index);
//                tmpDataFileMass.read(tmpStreamBody.data(),sizeBody);
//_StreamBody* pStreamBody= reinterpret_cast<decltype(pStreamBody)>(tmpStreamBody.data());
                tmpDataFileMass.seek(sizeHead+(sizeBody+sizeData)*index+ sizeBody);
                tmpDataFileMass.read((char*)(pData.data()),sizeData-sizeof(double));//remove end point
                //y值变号
                for(int i = 0; i< (sizeData-1)/sizeof(double) ;i++)
                    pData[i] = - pData[i];
            }catch(...){
                tmpDataFileMass.close();
                return false;
            }
        }
        try{
            tmpDataFileMass.close();
        }catch(...){
            return false;
        }
        return true;
    }
    return false;
}

bool cLoadDataFile::loadFileMass(QString pFilePath, int index, std::vector<double>& pData,QByteArray& pStreamHead)
{
    if(!pFilePath.isEmpty()){
        uint sizeHead=sizeof(_StreamHead);
        QFile tmpDataFileMass(pFilePath);
        //QByteArray tmpStreamHead(sizeHead);
        pStreamHead.resize(sizeHead);
        //_StreamHead* pStreamHead;
        try{
            if(!tmpDataFileMass.open(QIODevice::ReadOnly | QIODevice::Truncate))
                return false;
        }catch(...){
            return false;
        }
        try{
            if(sizeHead!= tmpDataFileMass.read(pStreamHead.data(), sizeHead)){
                tmpDataFileMass.close();
                return false;
            }else{
                _StreamHead* tmpStreamHead= (_StreamHead*)(pStreamHead.data());
                sizeHead= tmpStreamHead->length;
                pStreamHead.resize(sizeHead);
                tmpStreamHead= (_StreamHead*)(pStreamHead.data());
                tmpDataFileMass.seek(0);
                if(sizeHead!= tmpDataFileMass.read(pStreamHead.data(), sizeHead)){
                    tmpDataFileMass.close();
                    return false;
                }else{
                    sizeHead= tmpStreamHead->length;//debug
                }
            }
        }catch(...){
            return false;
        }
        uint sizeBody=sizeof(_StreamBody);
        QByteArray tmpStreamBody;
        tmpStreamBody.resize(sizeBody);
        qint64 sizeData=0;
        try{
            tmpDataFileMass.seek(sizeHead);
            if(sizeBody!= tmpDataFileMass.read(tmpStreamBody.data(),sizeBody)){
                tmpDataFileMass.close();
                return false;
            }else{
                _StreamBody* pStreamBody= reinterpret_cast<decltype(pStreamBody)>(tmpStreamBody.data());
                //_StreamBody* pStreamBody= (_StreamBody*)(tmpStreamBody.data());
                sizeData= pStreamBody->length- sizeBody;
            }
        }catch(...){
            tmpDataFileMass.close();
            return false;
        }
        if(sizeData>0){
            pData.resize((sizeData-1)/sizeof(double));//remove end point
            try{
//                tmpDataFileMass.seek(sizeHead+(sizeBody+sizeData)*index);
//                tmpDataFileMass.read(tmpStreamBody.data(),sizeBody);
//_StreamBody* pStreamBody= reinterpret_cast<decltype(pStreamBody)>(tmpStreamBody.data());
                tmpDataFileMass.seek(sizeHead+(sizeBody+sizeData)*index+ sizeBody);
                tmpDataFileMass.read((char*)(pData.data()),sizeData-sizeof(double));//remove end point
                //y值变号
                for(int i = 0; i< (sizeData-1)/sizeof(double) ;i++)
                    pData[i] = - pData[i];

            }catch(...){
                tmpDataFileMass.close();
                return false;
            }
        }
        try{
            tmpDataFileMass.close();
        }catch(...){
            return false;
        }
        return true;
    }
    return false;
}

//棒图
bool cLoadDataFile::loadFileMass(QString pFilePath, int index, std::vector<double> &xData, std::vector<double> &yData, QByteArray &pStreamHead)
{
    if(!pFilePath.isEmpty()){
        uint sizeHead=sizeof(_StreamHead);
        QFile tmpDataFileMass(pFilePath);
        _StreamHead::Type_Plot plot;
        cParamValue::_EventLIT* pEventLIT;

        //QByteArray tmpStreamHead(sizeHead);
        pStreamHead.resize(sizeHead);
        //_StreamHead* pStreamHead;
        try{
            if(!tmpDataFileMass.open(QIODevice::ReadOnly | QIODevice::Truncate))
                return false;
        }catch(...){
            return false;
        }
        try{
            if(sizeHead!= tmpDataFileMass.read(pStreamHead.data(), sizeHead)){
                tmpDataFileMass.close();
                return false;
            }else{
                _StreamHead* tmpStreamHead= (_StreamHead*)(pStreamHead.data());
                sizeHead= tmpStreamHead->length;
                pStreamHead.resize(sizeHead);
                tmpStreamHead= (_StreamHead*)(pStreamHead.data());
                tmpDataFileMass.seek(0);
                if(sizeHead!= tmpDataFileMass.read(pStreamHead.data(), sizeHead)){
                    tmpDataFileMass.close();
                    return false;
                }else{
                    sizeHead= tmpStreamHead->length;//debug
                    plot = tmpStreamHead->typePlot;
                    pEventLIT = (cParamValue::_EventLIT*)&(tmpStreamHead->segment.fisrtEvent);
                    if(!pEventLIT)
                        return false;
                }
            }
        }catch(...){
            return false;
        }
        if(plot == _StreamHead::sticks){
            QByteArray dataByteAll;
            QByteArray dataByte;
            uint sizeData;
            try{
                tmpDataFileMass.seek(sizeHead);
                dataByteAll = tmpDataFileMass.readAll();
                tmpDataFileMass.close();
                QList<QByteArray> tmpData = dataByteAll.split('\n');
                dataByte = tmpData[index];
                QList<QByteArray> dataList = dataByte.split('\t');
                sizeData = dataList.size();
                xData.resize(sizeData);
                yData.resize(sizeData);
                for(int i = 0; i < sizeData-1 ;i++)
                {
                    QByteArray temp = dataList[i];
                    xData[i] = temp.split(',')[0].toDouble();
                    yData[i] = temp.split(',')[1].toDouble();
                }
            }catch(...){
                return false;
            }
            return true;
        }else if(plot== _StreamHead::profile){
            uint sizeBody=sizeof(_StreamBody);
            QByteArray tmpStreamBody;
            tmpStreamBody.resize(sizeBody);
            qint64 sizeData=0;
            try{
                tmpDataFileMass.seek(sizeHead);
                if(sizeBody!= tmpDataFileMass.read(tmpStreamBody.data(),sizeBody)){
                    tmpDataFileMass.close();
                    return false;
                }else{
                    _StreamBody* pStreamBody= reinterpret_cast<decltype(pStreamBody)>(tmpStreamBody.data());
                    //_StreamBody* pStreamBody= (_StreamBody*)(tmpStreamBody.data());
                    sizeData= pStreamBody->length- sizeBody;
                }
            }catch(...){
                tmpDataFileMass.close();
                return false;
            }
            if(sizeData>0){
                yData.resize((sizeData-1)/sizeof(double));//remove end point
                try{
                    tmpDataFileMass.seek(sizeHead+(sizeBody+sizeData)*index+ sizeBody);
                    tmpDataFileMass.read((char*)(yData.data()),sizeData-sizeof(double));//remove end point
                    //y值变号
                    for(int i = 0; i< (sizeData-1)/sizeof(double) ;i++)
                        yData[i] = -yData[i];

                }catch(...){
                    tmpDataFileMass.close();
                    return false;
                }
            }
            uint lengthSrc= yData.size();
            if(xData.size()!= lengthSrc){
                xData.resize(lengthSrc);
                double dbVal = pEventLIT->msStart;
                double dbStep = (pEventLIT->msEnd - dbVal) / (double)lengthSrc;
                for(uint nIndex = 0; nIndex < lengthSrc; nIndex++){
                    xData[nIndex] = dbVal;
                    dbVal += dbStep;
                }
            }
            try{
                tmpDataFileMass.close();
                return true;
            }catch(...){
                return false;
            }
        }
    }
    return false;
}


bool cLoadDataFile::loadFileMass(QString pFilePath, int nFrameB, int nFrameE, std::vector<double>& pData,QByteArray& pStreamHead)
{
    if(!pFilePath.isEmpty()){
        uint sizeHead=sizeof(_StreamHead);
        QFile tmpDataFileMass(pFilePath);
        //QByteArray tmpStreamHead(sizeHead);
        pStreamHead.resize(sizeHead);
        //_StreamHead* pStreamHead;
        try{
            if(!tmpDataFileMass.open(QIODevice::ReadOnly | QIODevice::Truncate))
                return false;
        }catch(...){
            return false;
        }
        //向pStreamHead中写入数据头
        try{
            if(sizeHead!= tmpDataFileMass.read(pStreamHead.data(), sizeHead)){
                tmpDataFileMass.close();
                return false;
            }else{
                _StreamHead* tmpStreamHead= (_StreamHead*)(pStreamHead.data());
                sizeHead= tmpStreamHead->length;
                pStreamHead.resize(sizeHead);
                tmpStreamHead= (_StreamHead*)(pStreamHead.data());
                tmpDataFileMass.seek(0);
                if(sizeHead!= tmpDataFileMass.read(pStreamHead.data(), sizeHead)){
                    tmpDataFileMass.close();
                    return false;
                }else{
                    sizeHead= tmpStreamHead->length;//debug
                }
            }
        }catch(...){
            return false;
        }
        uint sizeBody=sizeof(_StreamBody);
        QByteArray tmpStreamBody;
        tmpStreamBody.resize(sizeBody);
        qint64 sizeData=0;
        //向tempStreamBody中写入主体数据
        try{
            tmpDataFileMass.seek(sizeHead);
            if(sizeBody!= tmpDataFileMass.read(tmpStreamBody.data(),sizeBody)){
                tmpDataFileMass.close();
                return false;
            }else{
                _StreamBody* pStreamBody= reinterpret_cast<decltype(pStreamBody)>(tmpStreamBody.data());
                //_StreamBody* pStreamBody= (_StreamBody*)(tmpStreamBody.data());
                sizeData= pStreamBody->length- sizeBody;
            }
        }catch(...){
            tmpDataFileMass.close();
            return false;
        }
        if(sizeData>0){
            //将二进制数据转换,传给pData
            int sizeDataD=sizeData/sizeof(double)-1;//remove end point
            pData.resize(sizeDataD,0);
            try{
//                tmpDataFileMass.seek(sizeHead+(sizeBody+sizeData)*index);
//                tmpDataFileMass.read(tmpStreamBody.data(),sizeBody);
//_StreamBody* pStreamBody= reinterpret_cast<decltype(pStreamBody)>(tmpStreamBody.data());
                //tmpDataFileMass.seek(sizeHead+(sizeBody+sizeData)*nFrameB+ sizeBody);
                std::vector<double> tempData(sizeDataD);
                int tmpACC = 0;
                for(;nFrameB<nFrameE;++nFrameB){
                    tmpDataFileMass.seek(sizeHead+(sizeBody+sizeData)*nFrameB+ sizeBody);
                    tmpDataFileMass.read((char*)(tempData.data()),sizeData-sizeof(double));//remove end point
                    ++tmpACC;
                    for(int i=0;i<sizeDataD;i++){
                        pData[i]= (double)(tmpACC-1) / (double)(tmpACC) * pData[i]+ tempData[i]/ (tmpACC);
                    }
                }

            }catch(...){
                tmpDataFileMass.close();
                return false;
            }
        }
        try{
            tmpDataFileMass.close();
        }catch(...){
            return false;
        }
        return true;
    }
    return false;
}

//获得某个质量数的XIC图像
bool cLoadDataFile::loadFileMassInX(QString pFilePath, int indexX, std::vector<double> &pData, QByteArray &pStreamHead)
{
    if(!pFilePath.isEmpty()){
        uint sizeHead=sizeof(_StreamHead);
        QFile tmpDataFileMass(pFilePath);
        //QByteArray tmpStreamHead(sizeHead);
        pStreamHead.resize(sizeHead);
        //_StreamHead* pStreamHead;
        try{
            if(!tmpDataFileMass.open(QIODevice::ReadOnly | QIODevice::Truncate))
                return false;
        }catch(...){
            return false;
        }
        //向pStreamHead中写入数据头
        try{
            if(sizeHead!= tmpDataFileMass.read(pStreamHead.data(), sizeHead)){
                tmpDataFileMass.close();
                return false;
            }else{
                _StreamHead* tmpStreamHead= (_StreamHead*)(pStreamHead.data());
                sizeHead= tmpStreamHead->length;
                pStreamHead.resize(sizeHead);
                tmpStreamHead= (_StreamHead*)(pStreamHead.data());
                tmpDataFileMass.seek(0);
                if(sizeHead!= tmpDataFileMass.read(pStreamHead.data(), sizeHead)){
                    tmpDataFileMass.close();
                    return false;
                }else{
                    sizeHead= tmpStreamHead->length;//debug
                }
            }
        }catch(...){
            return false;
        }
        uint sizeBody=sizeof(_StreamBody);
        QByteArray tmpStreamBody;
        tmpStreamBody.resize(sizeBody);
        qint64 sizeData=0;
        //向tempStreamBody中写入主体数据
        try{
            tmpDataFileMass.seek(sizeHead);
            if(sizeBody!= tmpDataFileMass.read(tmpStreamBody.data(),sizeBody)){
                tmpDataFileMass.close();
                return false;
            }else{
                _StreamBody* pStreamBody= reinterpret_cast<decltype(pStreamBody)>(tmpStreamBody.data());
                //_StreamBody* pStreamBody= (_StreamBody*)(tmpStreamBody.data());
                sizeData= pStreamBody->length- sizeBody;
            }
        }catch(...){
            tmpDataFileMass.close();
            return false;
        }
        if(sizeData>0){
            //将二进制数据转换,传给pData
            int frameCount = (tmpDataFileMass.size()-sizeHead)/(sizeBody+sizeData);
            int sizeDataD=sizeData/sizeof(double)-1;//remove end point
            pData.resize(sizeDataD,0);
            try{
//                tmpDataFileMass.seek(sizeHead+(sizeBody+sizeData)*index);
//                tmpDataFileMass.read(tmpStreamBody.data(),sizeBody);
//_StreamBody* pStreamBody= reinterpret_cast<decltype(pStreamBody)>(tmpStreamBody.data());
                //tmpDataFileMass.seek(sizeHead+(sizeBody+sizeData)*nFrameB+ sizeBody);
                std::vector<double> tempData(sizeDataD);
                int tmpACC = 0;
                for(int i = 0;i < frameCount; i++){
                    tmpDataFileMass.seek(sizeHead+(sizeBody+sizeData)*i+ sizeBody);
                    tmpDataFileMass.read((char*)(tempData.data()),sizeData-sizeof(double));//remove end point
                    ++tmpACC;
                    int range = 30;    //TIC质量数范围
                    for(int j = indexX-range; j <= indexX+range; j++)
                    {
                        pData[i] += (-tempData[j]);
                    }
//                    for(int i=0;i<sizeDataD;i++)
//                        pData[i]= (double)(tmpACC-1) / (double)(tmpACC) * pData[i]+ tempData[i]/ (tmpACC);
                }

            }catch(...){
                tmpDataFileMass.close();
                return false;
            }
        }
        try{
            tmpDataFileMass.close();
        }catch(...){
            return false;
        }
        return true;
    }
    return false;
}

bool cLoadDataFile::loadFileMassInX(QString pFilePath, double mass, std::vector<double> &pData, QByteArray &pStreamHead)
{
    if(!pFilePath.isEmpty()){
        uint sizeHead=sizeof(_StreamHead);
        QFile tmpDataFileMass(pFilePath);
        //QByteArray tmpStreamHead(sizeHead);
        pStreamHead.resize(sizeHead);
        //_StreamHead* pStreamHead;
        try{
            if(!tmpDataFileMass.open(QIODevice::ReadOnly | QIODevice::Truncate))
                return false;
        }catch(...){
            return false;
        }
        try{
            if(sizeHead!= tmpDataFileMass.read(pStreamHead.data(), sizeHead)){
                tmpDataFileMass.close();
                return false;
            }else{
                _StreamHead* tmpStreamHead= (_StreamHead*)(pStreamHead.data());
                sizeHead= tmpStreamHead->length;
                pStreamHead.resize(sizeHead);
                tmpStreamHead= (_StreamHead*)(pStreamHead.data());
                tmpDataFileMass.seek(0);
                if(sizeHead!= tmpDataFileMass.read(pStreamHead.data(), sizeHead)){
                    tmpDataFileMass.close();
                    return false;
                }else{
                    sizeHead= tmpStreamHead->length;//debug
                }
            }
        }catch(...){
            return false;
        }
        QByteArray dataByteAll;
        QByteArray dataByte;
        uint sizeDataall;
        uint sizeData;
        try{
            tmpDataFileMass.seek(sizeHead);
            dataByteAll = tmpDataFileMass.readAll();
            tmpDataFileMass.close();
            QList<QByteArray> tmpData = dataByteAll.split('\n');
            sizeDataall = tmpData.size();
            pData.resize(sizeDataall);
            for(int i = 0; i<sizeDataall-1;i++){
                dataByte = tmpData[i];
                QList<QByteArray> dataList = dataByte.split('\t');
                sizeData = dataList.size();
                for(int j = 0; j < sizeData-1 ;j++)
                {
                    QByteArray temp = dataList[j];
                    double tempMass = temp.split(',')[0].toDouble();
                    double tempHigh = temp.split(',')[1].toDouble();
                    double dx = fabs(tempMass-mass);
                    if(dx < 1)
                        pData[i] += (1-dx)*tempHigh;
                    else
                        pData[i] += 0.0;
                }
            }
        }catch(...){
            return false;
        }
        return true;

    }
    return false;
}

bool cLoadDataFile::loadFileMassInX(QString pFilePath, double mass, int indexX, std::vector<double> &pData, QByteArray &pStreamHead)
{
    if(!pFilePath.isEmpty()){
        uint sizeHead=sizeof(_StreamHead);
        _StreamHead::Type_Plot plot;
        QFile tmpDataFileMass(pFilePath);
        cParamValue::_EventLIT* pEventLIT;
        //QByteArray tmpStreamHead(sizeHead);
        pStreamHead.resize(sizeHead);
        //_StreamHead* pStreamHead;
        try{
            if(!tmpDataFileMass.open(QIODevice::ReadOnly | QIODevice::Truncate))
                return false;
        }catch(...){
            return false;
        }
        try{
            if(sizeHead!= tmpDataFileMass.read(pStreamHead.data(), sizeHead)){
                tmpDataFileMass.close();
                return false;
            }else{
                _StreamHead* tmpStreamHead= (_StreamHead*)(pStreamHead.data());
                sizeHead= tmpStreamHead->length;
                pStreamHead.resize(sizeHead);
                tmpStreamHead= (_StreamHead*)(pStreamHead.data());
                tmpDataFileMass.seek(0);
                if(sizeHead!= tmpDataFileMass.read(pStreamHead.data(), sizeHead)){
                    tmpDataFileMass.close();
                    return false;
                }else{
                    sizeHead= tmpStreamHead->length;//debug
                    plot = tmpStreamHead->typePlot;
                    pEventLIT = (cParamValue::_EventLIT*)&(tmpStreamHead->segment.fisrtEvent);
                    if(!pEventLIT)
                        return false;
                }
            }
        }catch(...){
            return false;
        }
        if(plot == _StreamHead::sticks){
            QByteArray dataByteAll;
            QByteArray dataByte;
            uint sizeDataall;
            uint sizeData;
            try{
                tmpDataFileMass.seek(sizeHead);
                dataByteAll = tmpDataFileMass.readAll();
                tmpDataFileMass.close();
                QList<QByteArray> tmpData = dataByteAll.split('\n');
                sizeDataall = tmpData.size();
                pData.resize(sizeDataall);
                for(int i = 0; i<sizeDataall-1;i++){
                    dataByte = tmpData[i];
                    QList<QByteArray> dataList = dataByte.split('\t');
                    sizeData = dataList.size();
                    for(int j = 0; j < sizeData-1 ;j++)
                    {
                        QByteArray temp = dataList[j];
                        double tempMass = temp.split(',')[0].toDouble();
                        double tempHigh = temp.split(',')[1].toDouble();
                        double dx = fabs(tempMass-mass);
                        if(dx < 1)
                            pData[i] += (1-dx)*tempHigh;
                        else
                            pData[i] += 0.0;
                    }
                }
            }catch(...){
                return false;
            }
            return true;
        }else if(plot == _StreamHead::profile){
            uint sizeBody=sizeof(_StreamBody);
            QByteArray tmpStreamBody;
            tmpStreamBody.resize(sizeBody);
            qint64 sizeData=0;
            double dx = pEventLIT->msEnd-pEventLIT->msStart;
            //向tempStreamBody中写入主体数据
            try{
                tmpDataFileMass.seek(sizeHead);
                if(sizeBody!= tmpDataFileMass.read(tmpStreamBody.data(),sizeBody)){
                    tmpDataFileMass.close();
                    return false;
                }else{
                    _StreamBody* pStreamBody= reinterpret_cast<decltype(pStreamBody)>(tmpStreamBody.data());
                    //_StreamBody* pStreamBody= (_StreamBody*)(tmpStreamBody.data());
                    sizeData= pStreamBody->length- sizeBody;
                }
            }catch(...){
                tmpDataFileMass.close();
                return false;
            }
            if(sizeData>0){
                //将二进制数据转换,传给pData
                int frameCount = (tmpDataFileMass.size()-sizeHead)/(sizeBody+sizeData);
                int sizeDataD=sizeData/sizeof(double)-1;//remove end point
                pData.resize(sizeDataD,0);
                try{
                    std::vector<double> tempData(sizeDataD);
                    int tmpACC = 0;
                    for(int i = 0;i < frameCount; i++){
                        tmpDataFileMass.seek(sizeHead+(sizeBody+sizeData)*i+ sizeBody);
                        tmpDataFileMass.read((char*)(tempData.data()),sizeData-sizeof(double));//remove end point
                        ++tmpACC;
                        int range = (int)sizeDataD/dx/2;    //单位质量范围
                        for(int j = indexX-range; j <= indexX+range; j++)
                        {
                            pData[i] += fabs(tempData[j]);
                        }
                    }

                }catch(...){
                    tmpDataFileMass.close();
                    return false;
                }
            }
            try{
                tmpDataFileMass.close();
            }catch(...){
                return false;
            }
            return true;
        }
    }
    return false;
}

QString cLoadDataFile::createFileTIC(QString fileName)
{
    if(mDataFileTIC!=nullptr){
        try{
            mDataFileTIC->close();
            delete mDataFileTIC;
        }catch(...){}
        mDataFileTIC=nullptr;
    }
    if(fileName.isEmpty()){
        fileName= QDir::currentPath() + "\\data";
        QDir dir;
        if (!dir.exists(fileName))
            if(!dir.mkpath(fileName))
                return QString();
        fileName += "\\MASS_DATA_";// + QDateTime::currentDateTime().toString("yyMMddhhmmss");
        try{
            mDataFileTIC= new QFile(fileName + ".TIC");
            if(!(mDataFileTIC->open(QIODevice::WriteOnly | QIODevice::Text)))
                return QString();
            else
                mFileName=fileName.toUtf8();
        }catch(...){
            delete mDataFileTIC;
            return QString();
        }
//        if(mStreamTIC){
//            delete mStreamTIC;
//            mStreamTIC=nullptr;
//        }
//        mStreamTIC = new QTextStream(mDataFileTIC);
    }else{

    }
    return fileName;
}

QString cLoadDataFile::createFileMass(QString fileName)
{
    if(mDataFileMass!=nullptr){
        try{
            mDataFileMass->close();
            delete mDataFileMass;
        }catch(...){}
        mDataFileMass=nullptr;
    }
    if(fileName.isEmpty()){
        fileName= QDir::currentPath() + "\\data";
        QDir dir;
        if (!dir.exists(fileName))
            if(!dir.mkpath(fileName))
                return QString();
        fileName += "\\TEMP_DATA";// + QDateTime::currentDateTime().toString("yyMMddhhmmss");

    }else{

    }
    try{
        mDataFileMass= new QFile(fileName + ".TIC.dat");
        if(!(mDataFileMass->open(QIODevice::WriteOnly | QIODevice::Truncate)))
            return QString();
        else{
            if(!mFileHead.isEmpty()){//method2File(mDataFileMass);
                mDataFileMass->write(mFileHead.data(),mFileHead.length());
                mDataFileMass->flush();
            }
            mFileName=fileName.toUtf8();
        }
    }catch(...){
        delete mDataFileMass;
        return QString();
    }
    return fileName;
}

void cLoadDataFile::saveDataTIC(QString data)
{
    try{
//        mStreamTIC<<data;
//        mStreamTIC->flush();
        if(mDataFileTIC){
            mDataFileTIC->write(data.toUtf8());
            bool result = mDataFileTIC->flush();
        }
    } catch(...) { }
}

bool cLoadDataFile::saveDataMass(QByteArray& pData)
{
    try{
        mDataFileMass->write(pData);
        mDataFileMass->flush();
    }catch(...){
        return false;
    }
    return true;
}

bool cLoadDataFile::saveDataMass(char* pData,qint64 nLength)
{
    try{
        if(mDataFileMass){
            mDataFileMass->write(pData,nLength);
            mDataFileMass->flush();
        }
    }catch(...){
        return false;
    }
    return true;
}

bool cLoadDataFile::saveDataMass(std::vector<double> xData, std::vector<double> yData)
{
    QString dataMass;
    int size = xData.size() < yData.size() ? xData.size() : yData.size();

    try{

        for(int i = 0 ;i < size; i++)
        {
            QString temp = QString::number(xData[i]) + "," + QString::number(yData[i]) + "\t";
            dataMass += temp;
        }
        dataMass += "\n";

        if(mDataFileMass){
            mDataFileMass->write(dataMass.toUtf8());
            mDataFileMass->flush();
        }
    }catch(...){
        return false;
    }
    return true;
}

bool cLoadDataFile::saveDataMass(std::vector<double> yData)
{
    QByteArray sampleData;
    int size = yData.size();
    sampleData.resize(sizeof(_StreamBody)+size*sizeof(double));
    _StreamBody* p_streamBody = reinterpret_cast<decltype(p_streamBody)>(sampleData.data());
    p_streamBody->typeParam = _StreamBody::Type_Null;
    p_streamBody->length = sampleData.size();
    double* pdbval = &p_streamBody->y[0];
    for(int i = 0; i< size; i++){
        pdbval[i] = yData[i];
    }

    try{
        if(mDataFileMass){
            mDataFileMass->write(sampleData);
            mDataFileMass->flush();
        }
    }catch(...){
        return false;
    }
    return true;
}

void cLoadDataFile::closeFileMass()
{
    if(mDataFileMass){
        try{
            mDataFileMass->close();
        }catch(...) { }
        delete mDataFileMass;
        mDataFileMass=nullptr;
    }

}

void cLoadDataFile::closeFileTIC()
{
    if(mDataFileTIC){
        try{
            mDataFileTIC->close();
        }catch(...) { }
        delete mDataFileTIC;
        mDataFileTIC=nullptr;
    }
}



void cLoadDataFile::renameFile(QString fileName)
{
    if (!mFileName.isEmpty())
    {
        QString currentFileTIC=QString::fromUtf8(mFileName) + ".TIC";
        QString currentFileMass=QString::fromUtf8(mFileName) + ".TIC.dat";
        mFileName.clear();
        QFile tmpFileTIC(currentFileTIC);
        QFile tmpFileMass(currentFileMass);
        if(!tmpFileTIC.exists()){
            if(tmpFileMass.exists()){
                try{
                    tmpFileMass.remove();
                }catch(...){}
            }
            return;
        }
        if(!tmpFileMass.exists()){
            if(tmpFileTIC.exists()){
                try{
                    tmpFileTIC.remove();
                }catch(...){}
            }
            return;
        }
        if(fileName.isEmpty()){//delete file
            try{
                tmpFileTIC.remove();
            tmpFileMass.remove();
            }catch(...){}
        }else{
            //QByteArray tmpName(pName, lengthName);
            //QString newName(tmpName);
            try{
            tmpFileTIC.rename(fileName);
            tmpFileMass.rename(fileName+".dat");
            }catch(...){}
        }
    }
}

void cLoadDataFile::renameFile(char* pName,int lengthName)
{
    if (!mFileName.isEmpty())
    {
        QString currentFileTIC=QString::fromUtf8(mFileName) + ".TIC";
        QString currentFileMass=QString::fromUtf8(mFileName) + ".TIC.dat";
        mFileName.clear();
        QFile tmpFileTIC(currentFileTIC);
        QFile tmpFileMass(currentFileMass);
        if(!tmpFileTIC.exists()){
            if(tmpFileMass.exists()){
                try{
                    tmpFileMass.remove();
                }catch(...){}
            }
            return;
        }
        if(!tmpFileMass.exists()){
            if(tmpFileTIC.exists()){
                try{
                    tmpFileTIC.remove();
                }catch(...){}
            }
            return;
        }
        if(lengthName<=0){//delete file
            try{
                tmpFileTIC.remove();
            tmpFileMass.remove();
            }catch(...){}
        }else{
            QByteArray tmpName(pName, lengthName);
            QString newName(tmpName);
            try{
            tmpFileTIC.rename(newName);
            tmpFileMass.rename(newName+".dat");
            }catch(...){}
        }
    }
}



/**
std::vector<char> baEvtParam;
        baEvtParam.resize(sizeof(cParamValue::_EventLIT));//_EventScan _EventProfile
        cParamValue::_EventLIT* p_EventLIT = (cParamValue::_EventLIT*)(baEvtParam.data());
        memset(p_EventLIT->title,'\0',30);
        strcpy(p_EventLIT->title, "Scan");
        p_EventLIT->type = cParamValue::Type_LIT;

        std::vector<char> graphParam;
        graphParam.resize(sizeof(_StreamHead) - sizeof(cParamValue::_Event));
        graphParam.insert(graphParam.end(),baEvtParam.begin(),baEvtParam.end());//graphParam.append(baEvtParam);

        _StreamHead* p_StreamHead =(_StreamHead*)(graphParam.data());
        p_StreamHead->dateTime= 0;//QDateTime::currentDateTime().toTime_t();//////////////////////////////////
        p_StreamHead->length= graphParam.size();
        p_StreamHead->typeParam = _StreamHead::Type_Acquisition;
        p_StreamHead->segment.sumEvent = 1;
        p_StreamHead->segment.minTime = 0;
        memset(p_StreamHead->segment.title,'\0',30);
        strcpy(p_StreamHead->segment.title, "LIT");

        p_StreamHead->segment.postReadyTime= p_StreamHead->segment.preReadyTime= 0;
        //cParamValue::_EventLIT* p_EventLIT= (cParamValue::_EventLIT*)(&(p_StreamHead->segment.fisrtEvent));
        p_EventLIT->holdTime= mTimeAcquisition;
        p_EventLIT->msStart= 0;
        p_EventLIT->msEnd= mTimeAcquisition;
  */


//OpenFileDialog openNew = new OpenFileDialog();
//            openNew.Title = "打开文件";
//            openNew.Filter = "MS文件|*.TIC|所有文件|*.*|文本文件|*.txt";
//            openNew.InitialDirectory = @"C:\";
//            if (openNew.ShowDialog() == DialogResult.OK)
//            {
//                mAnalysisXIC.clearList();
//                for (int iSeries = 1; iSeries < axTChart5.SeriesCount; )
//                    axTChart5.RemoveSeries(iSeries);
//                mAnalysisFile = null;
//                List<string> lineList2 = new List<string>();
//                try
//                {
//                    StreamReader sr = new StreamReader(openNew.FileName);
//                    while (!sr.EndOfStream)
//                        lineList2.Add(sr.ReadLine());
//                    sr.Close();
//                }
//                catch { };
//                Application.DoEvents();
//                List<double> tmpTIC_Y = new List<double>();
//                AnalysisTIC.Clear();// List<double> tmpTIC_X = new List<double>();

//                double tmpStep = 500.0 / (double)lineList2.Count;
//                if (lineList2.Count > 0)
//                {
//                    for (int i = 0; i < lineList2.Count; i++)
//                    {
//                        string[] split = Regex.Split(lineList2[i].ToString(), "\t");
//                        if (split.Length == 2)
//                        {
//                            tmpTIC_Y.Add(double.Parse(split[1]));
//                            AnalysisTIC.Add(double.Parse(split[0]));//tmpTIC_X.Add(double.Parse(split[0]));
//                        }
//                    }
//                    mAnalysisFile = openNew.FileName;
//                    string filename = openNew.FileName.Substring(openNew.FileName.LastIndexOf('\\') + 1);
//                    axTChart5.Series(0).AddArray(AnalysisTIC.Count, tmpTIC_Y.ToArray(), AnalysisTIC.ToArray());//axTChart5.Series(0).AddArray(tmpTIC_X.Count, tmpTIC_Y.ToArray(), tmpTIC_X.ToArray());
//                    axTChart5.Header.Text.Clear();
//                    axTChart5.Header.Text.Add(filename);
//                    mFileIndex = 0;
//                    mFilePointCount = tmpTIC_Y.Count;
//                    UpdateMassFile(mAnalysisFile, mFileIndex);
//                }
//            }


//                private void UpdateMassFile(string fileName,int valueIndex)
//                        {
//                            if (fileName != null)
//                            {
//                                FileStream tmpFileStream;
//                                int tmpSizeDouble = sizeof(double);
//                                try { tmpFileStream = new FileStream(fileName + ".dat", FileMode.Open); } catch { return; }

//                                byte[] tmpData = new byte[tmpSizeDouble];
//                                try { tmpFileStream.Read(tmpData, 0, tmpData.Length); } catch { return; }
//                                double tmpStartMass = BitConverter.ToDouble(tmpData, 0);

//                                try { tmpFileStream.Read(tmpData, 0, tmpData.Length); } catch { return; }
//                                double tmpStopMass = BitConverter.ToDouble(tmpData, 0);

//                                tmpData = null;
//                                tmpData = new byte[sizeof(long)];
//                                try { tmpFileStream.Read(tmpData, 0, tmpData.Length); } catch { return; }
//                                long tmpStartDAQpoint = BitConverter.ToInt64(tmpData, 0);

//                                try { tmpFileStream.Read(tmpData, 0, tmpData.Length); } catch { return; }
//                                long tmpAllPoint = BitConverter.ToInt64(tmpData, 0);

//                                try { tmpFileStream.Read(tmpData, 0, tmpData.Length); } catch { return; }
//                                long tmpEndDAQpoint = BitConverter.ToInt64(tmpData, 0);
//                                if (tmpAllPoint <= 0)
//                                    return;

//                                long tmpSeek = (long)(tmpSizeDouble * 2 + sizeof(long) * 3);
//                                try
//                                { tmpFileStream.Seek(tmpSeek + (long)(valueIndex * tmpSizeDouble) * tmpAllPoint, SeekOrigin.Begin); }
//                                catch { return; }

//                                tmpData = null;
//                                tmpData = new byte[tmpSizeDouble * tmpAllPoint];
//                                try { tmpFileStream.Read(tmpData, 0, tmpData.Length); } catch { return; }

//                                try { tmpFileStream.Close(); } catch { return; }

//                                double tmpStepX = (tmpStopMass - tmpStartMass) /
//                                        (double)(tmpEndDAQpoint - tmpStartDAQpoint);
//                                object[] tmpArrayX = new object[tmpAllPoint];
//                                object[] tmpArrayY = new object[tmpAllPoint];
//                                double[] tmpArrayDoubleX = new double[tmpAllPoint];
//                                double[] tmpArrayDoubleY = new double[tmpAllPoint];
//                                //if(testExport_Y.Length!= tmpAllPoint)
//                                //{
//                                //    testExport_Y = null;
//                                //    testExport_Y= new double[tmpAllPoint];
//                                //}
//                                int i = 0;
//                                if (mCalibration.isEnable())
//                                {
//                                    if (mCalibration.isChanged)
//                                    {
//                                        mCalibration.isChanged = false;
//                                        string tmpStr = cIniHelper.Ini_Read("Polynomial", "pointNum", mCalibration.getFilePath());
//                                        if (tmpStr != "")
//                                        {
//                                            int tmpPointNum = Convert.ToInt32(tmpStr);
//                                            mPolynomial = new double[tmpPointNum];
//                                            for (i = 0; i < tmpPointNum; i++)
//                                                mPolynomial[i] = Convert.ToDouble(cIniHelper.Ini_Read("Polynomial", "Coefficient" + i.ToString(), mCalibration.getFilePath()));
//                                        }
//                                    }
//                                    switch (mPolynomial.Length)
//                                    {
//                                        case 5:
//                                            for (i = 0; i < tmpAllPoint; i++)
//                                            {
//                                                tmpArrayDoubleY[i] = BitConverter.ToDouble(tmpData, tmpSizeDouble * i);
//                                                tmpArrayDoubleX[i] = tmpStartMass + i * tmpStepX;
//                                                tmpArrayX[i] = (object)(tmpArrayDoubleX[i] * tmpArrayDoubleX[i] * tmpArrayDoubleX[i] * tmpArrayDoubleX[i] * mPolynomial[4]
//                                                + tmpArrayDoubleX[i] * tmpArrayDoubleX[i] * tmpArrayDoubleX[i] * mPolynomial[3]
//                                                + tmpArrayDoubleX[i] * tmpArrayDoubleX[i] * mPolynomial[2]
//                                                + tmpArrayDoubleX[i] * mPolynomial[1]
//                                                + mPolynomial[0]);
//                                            }
//                                            break;
//                                        case 4:
//                                            for (i = 0; i < tmpAllPoint; i++)
//                                            {
//                                                tmpArrayDoubleY[i] = BitConverter.ToDouble(tmpData, tmpSizeDouble * i);
//                                                tmpArrayDoubleX[i] = tmpStartMass + i * tmpStepX;
//                                                tmpArrayX[i] = (object)(tmpArrayDoubleX[i] * tmpArrayDoubleX[i] * tmpArrayDoubleX[i] * mPolynomial[3]
//                                                + tmpArrayDoubleX[i] * tmpArrayDoubleX[i] * mPolynomial[2]
//                                                + tmpArrayDoubleX[i] * mPolynomial[1]
//                                                + mPolynomial[0]);
//                                            }
//                                            break;
//                                        case 3:
//                                            for (i = 0; i < tmpAllPoint; i++)
//                                            {
//                                                tmpArrayDoubleY[i] = BitConverter.ToDouble(tmpData, tmpSizeDouble * i);
//                                                tmpArrayDoubleX[i] = tmpStartMass + i * tmpStepX;
//                                                tmpArrayX[i] = (object)(tmpArrayDoubleX[i] * tmpArrayDoubleX[i] * mPolynomial[2]
//                                                + tmpArrayDoubleX[i] * mPolynomial[1]
//                                                + mPolynomial[0]);
//                                            }
//                                            break;
//                                        default:
//                                            for (i = 0; i < tmpAllPoint; ++i)
//                                            {
//                                                tmpArrayDoubleY[i] = BitConverter.ToDouble(tmpData, tmpSizeDouble * i);
//                                                tmpArrayDoubleX[i] = tmpStartMass + i * tmpStepX;
//                                                tmpArrayX[i] = (object)(tmpArrayDoubleX[i]);
//                                            }
//                                            break;
//                                    }
//                                }
//                                else
//                                {
//                                    for (i = 0; i < tmpAllPoint; i++)
//                                    {
//                                        tmpArrayDoubleY[i] = BitConverter.ToDouble(tmpData, tmpSizeDouble * i);
//                                        tmpArrayDoubleX[i] = tmpStartMass + i * tmpStepX;
//                                        tmpArrayX[i] = (object)tmpArrayDoubleX[i];
//                                    }
//                                    //if (checkBox2.Checked)
//                                    //{
//                                    //    for (i = 0; i < tmpAllPoint; i++)
//                                    //    {
//                                    //        tmpArrayDoubleY[i] = BitConverter.ToDouble(tmpData, tmpSizeDouble * i);
//                                    //        tmpArrayDoubleX[i] = tmpStartMass + i * tmpStepX;
//                                    //        testExport_Y[i] = (testExport_Y[i] * mCountFrame + tmpArrayDoubleY[i]) / (mCountFrame + 1);
//                                    //        tmpArrayDoubleY[i] = testExport_Y[i];

//                                    //        tmpArrayX[i] = (object)tmpArrayDoubleX[i];
//                                    //    }
//                                    //    ++mCountFrame;
//                                    //}
//                                    //else
//                                    //{
//                                    //    for (i = 0; i < tmpAllPoint; i++)
//                                    //    {
//                                    //        tmpArrayDoubleY[i] = BitConverter.ToDouble(tmpData, tmpSizeDouble * i);
//                                    //        tmpArrayDoubleX[i] = tmpStartMass + i * tmpStepX;
//                                    //        tmpArrayX[i] = (object)tmpArrayDoubleX[i];
//                                    //    }
//                                    //    mCountFrame = 0;
//                                    //}
//                                }

//                                if (mCalibration.isEnableBaseline())
//                                {
//                                    double[] tmpBaseline = mNoiseSplineBaseline.Baseline(tmpArrayDoubleX, tmpArrayDoubleY, mCalibration.getLimit());
//                                    //double[] tmpBaseline = new double[tmpArrayDoubleY.Length];
//                                    //baseLine(ref tmpArrayDoubleY[0], ref tmpBaseline[0], tmpArrayDoubleY.Length);
//                                    if (tmpBaseline != null && (tmpBaseline.Length == tmpArrayDoubleY.Length))
//                                    {
//                                        double tmpAverage = MathNet.Numerics.Statistics.Statistics.Mean(tmpBaseline);
//                                        for (i = 0; i < tmpAllPoint; ++i)
//                                            tmpArrayY[i] = (object)(tmpArrayDoubleY[i] - tmpAverage);
//                                    }
//                                    else
//                                    {
//                                        for (i = 0; i < tmpAllPoint; ++i)
//                                            tmpArrayY[i] = (object)(tmpArrayDoubleY[i]);
//                                    }
//                                }
//                                else
//                                {
//                                    for (i = 0; i < tmpAllPoint; ++i)
//                                        tmpArrayY[i] = (object)(tmpArrayDoubleY[i]);
//                                }

//                                if (mutexAnalysisMass.WaitOne(10))
//                                {
//                                    if (mAnalysisMassX.Length!= tmpAllPoint)
//                                    {
//                                        mAnalysisMassX = null;
//                                        mAnalysisMassY = null;
//                                        mAnalysisMassX = new double[tmpAllPoint];
//                                        mAnalysisMassY = new double[tmpAllPoint];
//                                    }
//                                    for (i = 0; i < tmpAllPoint; ++i)
//                                    {
//                                        mAnalysisMassX[i] = (double)tmpArrayX[i];
//                                        mAnalysisMassY[i] = (double)tmpArrayY[i];
//                                    }
//                                    mutexAnalysisMass.ReleaseMutex();
//                                }
//                                axTChart4.Series(1).Clear();
//                                axTChart4.Series(0).AddArray((int)tmpAllPoint, tmpArrayY, tmpArrayX);
//                                axTChart4.Header.Text.Clear();
//                                axTChart4.Header.Text.Add("Mass Spectra No. " + (mFileIndex + 1).ToString());
//                            }
//                        }
