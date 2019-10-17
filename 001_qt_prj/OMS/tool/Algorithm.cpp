#include "Algorithm.h"
#include <cmath>
#include <QVector>
#include <QTimer>

class Algorithm::PrivateData
{
public:
    PrivateData(){
        dataList.clear();
    }

    struct dataCut{
        QVector<double> data;
        QVector<double> dataD;
        int length;
        int startPoint;

        QVector<int> maxPoint;
        void init(int point){
            data.clear();
            dataD.clear();
            length = 1;
            startPoint = point;
            maxPoint.clear();
        }
    };

    QList<dataCut> dataList;
    double FWHM = 0.4;
    int width = 2;
    int freq = 2000000;
    int speed = 1500;
    int acc = 16;  
    double baseLineOffset = 0.0005;
    double dataOffset = 0.1;
};

Algorithm* Algorithm::algo = new Algorithm();

Algorithm::Algorithm(QObject *parent) : QObject(parent)
{
    d_data = new PrivateData();
}

Algorithm* Algorithm::getInstance()
{
    return algo;
}

void Algorithm::setFWHM(const double FWHM)
{
    d_data->FWHM = FWHM;
}

void Algorithm::setAcc(const int acc)
{
    d_data->acc = acc;
}

void Algorithm::setSpeed(const int speed)
{
    d_data->speed = speed;
}

void Algorithm::setWidth(const int width)
{
    d_data->width = width;
}

void Algorithm::setFreq(const double freq)
{
    d_data->freq = (int)(freq*1000000);
}

void Algorithm::setBaseLineOffset(const double offset)
{
    d_data->baseLineOffset = offset;
}

void Algorithm::setDataOffset(const double offset)
{
    d_data->dataOffset = offset;
}

double Algorithm::getBaseLineOffset()
{
    return d_data->baseLineOffset;
}

double Algorithm::getDataOffset()
{
    return d_data->dataOffset;
}

int Algorithm::getAcc()
{
    return d_data->acc;
}

int Algorithm::getSpeed()
{
    return d_data->speed;
}

double Algorithm::getFWHM()
{
    return d_data->FWHM;
}

int Algorithm::getWidth()
{
    return d_data->width;
}

int Algorithm::getFreq()
{
    return d_data->freq;
}

double Algorithm::sum()
{
    double sum=0;
    int m = (int)(d_data->freq/(d_data->speed*d_data->acc));
    int w = d_data->width*m + 1;
    double fwhm = d_data->FWHM*m;

    for(int index = 0; index< w ; index++){
        double temp = 2.4/pow(fwhm,4)*(2.4*pow(index-m,2)-pow(fwhm,2))*exp(-1.2*pow((index-m)/fwhm,2));
        sum += temp;
    }
    return sum;
}

QVector<double> Algorithm::createCj()
{
    int m = d_data->freq/(d_data->speed*d_data->acc);
    double fwhm = d_data->FWHM*m;
    int width = d_data->width*m + 1;
    QVector<double> CjList;
    CjList.resize(width);
    double sum0 = sum();

    for(int index = 0;index < width; index++){
        double temp = -2.4/pow(fwhm,4)*(2.4*pow(index-m,2)-pow(fwhm,2))*exp(-1.2*pow((index-m)/fwhm,2)) + sum0/width;
        CjList[index] = temp;
    }
    return CjList;
}

QVector<double> Algorithm::createCj2(QVector<double> data)
{
    QVector<double> templist;
    int size = data.size();
    templist.resize(size);

    for(int index = 0; index < size; index++)
    {
        templist[index] = pow(data[index],2);
    }

    return templist;
}

void Algorithm::createDataCut(QVector<double> data)
{
    d_data->dataList.clear();

    int size = data.size();
    bool state = false;
    PrivateData::dataCut temp;

    for(int i = 0; i< size; i++){
        if(data[i] > d_data->baseLineOffset && state == false){
            temp.init(i);
            state = true;
            temp.data.append(data[i]);
        }else if(data[i] > d_data->baseLineOffset && state == true){
            temp.data.append(data[i]);
            temp.length++;
        }else if(data[i] < d_data->baseLineOffset && state == true){
            if(temp.length > (int)(d_data->freq/(d_data->speed*d_data->acc))){
                d_data->dataList.append(temp);
            }
            state = false;
        }

    }
}

void Algorithm::createDataCut(std::vector<double> data)
{
    d_data->dataList.clear();

    int size = data.size();
    bool state = false;
    PrivateData::dataCut temp;

    for(int i = 0; i< size; i++){
        if(data[i] > d_data->baseLineOffset && state == false){
            temp.init(i);
            state = true;
            temp.data.append(data[i]);
        }else if(data[i] > d_data->baseLineOffset && state == true){
            temp.data.append(data[i]);
            temp.length++;
        }else if(data[i] < d_data->baseLineOffset && state == true){
            if(temp.length > (int)(d_data->freq/(d_data->speed*d_data->acc))){
                d_data->dataList.append(temp);
            }
            state = false;
        }

    }
}

void Algorithm::process()
{
    int m = (int)(d_data->freq/(d_data->speed*d_data->acc));
    int w = d_data->width*m;
    QVector<double> CjList = createCj();
    QVector<double> Cj2List = createCj2(CjList);

    int size = d_data->dataList.size();

    for(int index = 0; index < size; index++){
        QVector<double> data = d_data->dataList[index].data;
        int dataSize = data.size();
        d_data->dataList[index].dataD.resize(dataSize-1);
        QVector<double> temp1(dataSize);
        QVector<double> temp2(dataSize);

        QVector<double> preData(w/2,0);
        QVector<double> lastData(w/2,0);
        QVector<double> newData = preData+data+lastData;

        for(int i = 0; i < dataSize;i++){
            for(int j = 0; j< w+1; j++){
                temp1[i] += CjList[j]*newData[j+i];
                temp2[i] += Cj2List[j]*newData[j+i];
                d_data->dataList[index].data[i] = temp1[i]/pow(temp2[i],0.5);
                if(i != 0)
                    d_data->dataList[index].dataD[i-1] = d_data->dataList[index].data[i]-d_data->dataList[index].data[i-1];
            }
        }

        for(int i = 0; i< dataSize-2; i++){
            if(d_data->dataList[index].dataD[i+1]*d_data->dataList[index].dataD[i] < 0){
                if(d_data->dataList[index].dataD[i]>0){
                    if(d_data->dataList[index].data[i]>d_data->dataOffset)
                    d_data->dataList[index].maxPoint.append(i+d_data->dataList[index].startPoint);
                }
            }
        }
    }
}


int Algorithm::getResult(QVector<double> &pData, QVector<double> &oData, QVector<int>& pMask)
{
    int size = oData.size();

    if(size == 0)
        return -1;        //输入为空

    createDataCut(oData);
    if(d_data->dataList.isEmpty())
        return 0;         //无数据

    process();
    pData.resize(size);

    for(int i = 0; i<d_data->dataList.size();i++){
        for(int j = 0;j < d_data->dataList[i].length;j++){
            pData[d_data->dataList[i].startPoint+j] = d_data->dataList[i].data[j];
        }
        pMask.append(d_data->dataList[i].maxPoint);
    }

    return 1;
}

int Algorithm::getResult(QVector<double> &pData, std::vector<double> &oData, QVector<int> &pMask)
{
    int size = oData.size();

    if(size == 0)
        return -1;        //输入为空

    createDataCut(oData);
    if(d_data->dataList.isEmpty())
        return 0;         //无数据

    process();
    pData.resize(size);

    for(int i = 0; i<d_data->dataList.size();i++){
        for(int j = 0;j < d_data->dataList[i].length;j++){
            pData[d_data->dataList[i].startPoint+j] = d_data->dataList[i].data[j];
        }
        pMask.append(d_data->dataList[i].maxPoint);
    }

    return 1;
}
