#ifndef SPROCESSMANAGER_H
#define SPROCESSMANAGER_H
#include <QStringList>
#include <qvector.h>
#include <Algorithm/FrameAverage.h>

struct FilterDataBase{
    double DataParam1;
 };
struct MapParam{
    QVector<uint> Key;
    QVector<FilterDataBase*> Value;
};
enum FilterDataType{
    MovingAverage=0,
    SavGol=1,
    FrameAverage=2,
    GainOffset//BackOffset=3//Baseline
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
class sProcessManager
{
public:
    sProcessManager();
    ~sProcessManager();
    static void setMethod(const QString& strSructMethod,MethodParam& mMethodParam);
    static MethodParam setMethod(const QString& strSructMethod);
    static void setParam(const MethodParam& mMethodParam,MapParam& mFilterData);
//private:
    //MapFilterData mFilterData;

};

#endif // SPROCESSMANAGER_H
