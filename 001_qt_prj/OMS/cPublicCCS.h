#ifndef CTYPECCS_H
#define CTYPECCS_H
#include <QPluginLoader>

struct cTypeCCS
{
public:
    cTypeCCS(){}
};
struct cParamValue{
public:
    enum Type_Event{Type_Null, Type_LIT, Type_Profile, Type_Scan, Type_SIM, Type_Scan_RCT, Type_Static_RCT};
    enum Type_Segment{Type_Seg_Null, Type_LIT_TARGET, Type_LIT_FULL};
    struct _Event{
        Type_Event type = Type_Null;
        double holdTime = 0.0;//s阶段总时间，包含前后拓展
        double preReadyTime;//s
        double postReadyTime;//s
        double minTime;
        double msPrecursor;
        char title[30];
    };

    struct _Segment{
        Type_Segment    type= Type_Seg_Null;           //if Tuning
        unsigned int    sumEvent;
        char    title[30];      //SegTitle
        _Event   fisrtEvent;
    };

    struct _EventScan:public _Event{
        double msStart;
        double msEnd;
        double msStartOrig;
        double msEndOrig;
    };

    typedef _EventScan _EventProfile;

    typedef _EventScan _EventLIT;

    struct _EventSIM:public _Event{
        double mass[64];
    };

    cParamValue(){}
};

struct _StreamHead{
    enum Type_Param{Type_Null, Type_Tuning, Type_Acquisition};
    enum Type_Plot{sticks = 0,profile = 1};
    unsigned long length = 0;
    Type_Param typeParam = Type_Null;
    Type_Plot typePlot = sticks;
    unsigned long dateTime = 0;
    cParamValue::_Segment segment;
    _StreamHead(){}
};

struct _StreamBody{
    enum Type_Data{Type_Null};
    unsigned long length = 0;
    Type_Data typeParam = Type_Null;
    double currentTime=0;
    double currentAcc=0;
    unsigned long dateTime = 0;
    unsigned long dataFrame= 0;
    double y[0];
};

class Q_DECL_EXPORT sortGICAP{
public:
    sortGICAP(){}
    static void quickSort(double s[], int* pMarker, int left, int right);
    static void widthSort(double* cAbsc, int* pMarker, int nLength, int nWidth);
    static void DateSort(const std::vector<double>& pAbsc, const std::vector<double>& pOrd,
                                    const std::vector<int>& pStart, const std::vector<int>& pEnd, std::vector<double>& pAbsc1, std::vector<double>& pOrd1,
                                    std::vector<int>& pStart1, std::vector<int>& pEnd1, std::vector<int>& pMarker, uint uWidth);
};

class vectorOperate{
public:
    template <class T>
    static bool Resize(std::vector<T>& pT, uint n){
        if(n> pT.capacity()){
            pT.clear();
            pT.shrink_to_fit();
        }
        try{
            pT.resize(n);
        }catch(...){
            return false;
        }
        return true;
    }
    template <class T>
    static void Clear(std::vector<T>& pT){
        pT.clear();
        pT.shrink_to_fit();
    }
private:
    vectorOperate(){}
};
class QvectorOperate{
public:
    template <class T>
    static bool Resize(QVector<T>& pT, uint n){
        if(n> pT.capacity()){
            pT.clear();
            pT.shrink_to_fit();
        }
        try{
            pT.resize(n);
        }catch(...){
            return false;
        }
        return true;
    }
    template <class T>
    static void Clear(QVector<T>& pT){
        pT.clear();
        pT.shrink_to_fit();
    }
private:
    QvectorOperate(){}
};
#endif // CTYPECCS_H
