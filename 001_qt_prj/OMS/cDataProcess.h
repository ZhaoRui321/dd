#ifndef CDATAPROCESS_H
#define CDATAPROCESS_H
#include <Algorithm/FrameAverage.h>
#include <QStringList>
#include <QVector>
#include <cProcessing.h>

class cDataProcess: public SignalProcessing {
public:
    enum FilterDataType{
        MovingAverage=0,
        SavGol=1,
        FrameAverage=2,
        GainOffset//BackOffset=3//Baseline
    };
    struct FilterDataBase{
        double DataParam1;
     };
    struct MapParam{
        QVector<uint> Key;
        QVector<FilterDataBase*> Value;
    };
    struct FilterMovingAverage:FilterDataBase{};
    struct FilterGainOffset:FilterDataBase{
        bool bOffset=false;
        //bool Backward=false;
        bool bGain=false;
        double DataParam2=1;
    };
    struct FilterFrameAverage:FilterDataBase{
        cFrameAverage<double> mFrameAverage;
    };
    struct FilterSavGol:FilterDataBase{
        int DataParam2;
    };
    struct FilterBaseLine:FilterDataBase{
        int DataParam2;
    };
    struct MethodParam{
        uint uVersion=0;
        QStringList ListParam;
    };

public:
    cDataProcess(){}
    virtual ~cDataProcess(){}
private :
    uint mParamVersion = 0;
    MethodParam mMethodParam;
    MapParam mMapParam;
    std::vector<double> mDataTmp;
    void updateMethod();
    bool processData(std::vector<double>const& dataSrc, bool reStart= false);
    bool processData(std::vector<double>const& dataSrc, std::vector<double>& dataDest, bool reStart= false);

    bool processData(double* dataSrc, int nSize, bool reStart= false);
    bool processData(double* dataSrc, double* dataDest, int nSize, bool reStart= false);
public:
    bool getData(double* dataSrc, int sizeData, bool reStart= false){
        updateMethod();
        return processData(dataSrc, sizeData, reStart);
    }
    bool getData(double* dataSrc, double* dataDest, int sizeData, bool reStart= false){
        updateMethod();
        return processData(dataSrc, dataDest, sizeData, reStart);
    }
    bool getData(std::vector<double>const& dataSrc, std::vector<double>& dataDest, bool reStart= false){
        updateMethod();
        return processData(dataSrc, dataDest, reStart);
    }
    void setMethod(QString& strSructMethod);

    void sortVector(std::vector<double> &xData, std::vector<double> &yData);
};

class sDataProcess{
public:
    static cDataProcess* getDataProcess(){
        static sDataProcess insDataProcess;
        return &(insDataProcess.mDataProcess);
    }
private:
    cDataProcess mDataProcess;
    sDataProcess(){}
    virtual ~sDataProcess(){}
    sDataProcess(const sDataProcess&){}
    sDataProcess& operator=(const sDataProcess&){
        static sDataProcess insDataProcess;
        return insDataProcess;
    }
};

class sDataProcessAnalysis{
public:
    static cDataProcess* getDataProcess(){
        static sDataProcessAnalysis insDataProcessAnalysis;
        return &(insDataProcessAnalysis.mDataProcess);
    }
private:
    cDataProcess mDataProcess;
    sDataProcessAnalysis(){}
    virtual ~sDataProcessAnalysis(){}
    sDataProcessAnalysis(const sDataProcessAnalysis&){}
    sDataProcessAnalysis& operator=(const sDataProcessAnalysis&){
        static sDataProcessAnalysis insDataProcessAnalysis;
        return insDataProcessAnalysis;
    }
};
#endif // CDATAPROCESS_H
