#ifndef PROCESSINGDLL_H
#define PROCESSINGDLL_H

#include <QTableWidgetItem>
#include "cProcessing.h"
#include <Algorithm/FrameAverage.h>
#include "sProcessManager.h"

namespace Ui {
    class ProcessingDLL;
}
enum MyTableItemType{
    ItemType_Edit=0,
    ItemType_Check=1,
};
struct FilerDataT{
    uint localVersion = 0;
    double defaultXBegin = 0;
    double defaultXEnd = 1;
    std::vector<double> bufx;
    std::vector<double> bufy;
};
typedef QVector<int> MyTableItem;

class ProcessingDLL:public QWidget
{
    Q_OBJECT
public:
    ProcessingDLL(QWidget *parent = 0);
    ~ProcessingDLL();
    void setEnabledF(bool bEnable =true){
        bFilterEnable= bEnable;
    }
    bool getEnabledF(){
        return bFilterEnable;
    }
    QString getMethod(){
        return mMethodStr;
    }
    bool getData(std::vector<double>const& dataSrc, std::vector<double>& dataDest){
        updateMethod();
        return processData(dataSrc,dataDest);
    }
    //void setMethod(QString strSructMethod);
    bool setMethod(QString& strSructMethod);
private:
    Ui::ProcessingDLL *ui;
    bool bFilterEnable=true;
    QString mMethodStr;
    uint mParamVersion = 0;
    SignalProcessing mSignalProcessing;
    FilerDataT m_FilerData;
    MapParam mMapParam;
    MethodParam mMethodParam;
    void updateMethod();
    bool processData(std::vector<double>const& dataSrc, std::vector<double>& dataDest);
    void insertList(int columnCount,QString name);
    void insertList(MyTableItem MyTableItem1,QString name);
private slots:
    void on_pushButton_clicked(){
        insertList(2,"MovingAverage");}
    void on_pushButton_4_clicked(){
        insertList(3,"SavGolFilt");}
    void on_B_FrameAverage_clicked(){
        insertList(2,"FrameAverage");}
    void on_pushButton_2_clicked();
    void on_B_Backward_clicked(){
        insertList(3,"GainOffset");}
    void on_pushButton_3_clicked();
    void on_B_BaseLine_clicked();
};


//extern "C" {
//    PROCESSINGDLLSHARED_EXPORT void createFilter();
//    PROCESSINGDLLSHARED_EXPORT void deleteFilter();
//    PROCESSINGDLLSHARED_EXPORT void showFilter(bool showD);
//    PROCESSINGDLLSHARED_EXPORT void setEnabledF(bool bEnable);
//    PROCESSINGDLLSHARED_EXPORT bool getEnabledF();
//    PROCESSINGDLLSHARED_EXPORT char* getMethod();
//    PROCESSINGDLLSHARED_EXPORT bool getData(std::vector<double>const& dataSrc,
//                                            std::vector<double>& dataDest,double xBegin,double xEnd);
//    PROCESSINGDLLSHARED_EXPORT void setMethod(char* strSructMethod);
//}
#endif // PROCESSINGDLL_H
