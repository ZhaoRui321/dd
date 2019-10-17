#ifndef SDATAANALYSIS_H
#define SDATAANALYSIS_H
#include <QMainWindow>
#include <QMutex>
#include <tool/sthread.h>
#include "cLoadDataFile.h"
#include "sChartWidget.h"
#include "cDataProcess.h"
#include "FileListWidget.h"
#include "LibWidget/ListWidget/ColorSelectTool.h"
#include "LibProcessing/Processing/CSignalArea.h"
#include "myGroupBox.h"
#include "cconfigoms.h"

namespace Ui {
class sDataAnalysis;
}

class sDataAnalysis : public QMainWindow
{
    Q_OBJECT

public:
    enum _TYPE_THREAD{_TYPE_TIC, _TYPE_MASS, _TYPE_MASS_RANGE};
    explicit sDataAnalysis(QWidget *parent = 0);
    ~sDataAnalysis();

    void setDatapath(QString path);    
    void modifyList();

    void manageGroupBox();

    void createXICListItem(double mass);
    double caculMassNum(double x);
    double getMassNum(double x,std::vector<double> vx,std::vector<double> vy);
    double getMassNum(double x,std::vector<double> vx);

    int getRightValue(int min,int rel,int max)
    {
        rel = (rel < min) ? min : rel;
        return (rel > max) ? max : rel;
    }

    _CONGIG_OMS::_CONGIG_ANALYSIS* getConfig(){
        return &mCONGIG_ANALYSIS;
    }

    _TYPE_THREAD currentType(){
        return m_TYPE_THREAD;
    }
/** about tic*/
    std::vector<double> mDataTIC_X;
    std::vector<double> mDataTIC_Y;
    QString currentFileTIC(){
        return mFileNameTIC;
    }
    bool showDataTIC(QString fileName);
/** about mass*/
    std::vector<double> mDataMass_X;
    std::vector<double> mDataMass_Y;
    std::vector<double> mlistPeak_X;
    std::vector<double> mlistPeak_Y;
    QVector<QString> mPeakMarker;
    QByteArray mStreamHead;
    QString currentFileMass(){
        return mFileNameMass;
    }
    uint currentFrame(){
        return mFrame;
    }
    bool showDataMass(QString fileName, uint nFrame);
    QPair<uint, uint> mFrameRange;//_TYPE_MASS_RANGE
    bool showDataMass(QString fileName, uint nFrameB, uint nFrameE);
/** */

    bool loadFileTIC(QString pFilePath,QVector<double>& pDataTIC_X,QVector<double>& pDataTIC_Y){
        if(mLoadDataFile)
            return mLoadDataFile->loadFileTIC(pFilePath, pDataTIC_X, pDataTIC_Y);
        return false;
    }
    bool loadFileTIC(QString pFilePath,std::vector<double>& pDataTIC_X,std::vector<double>& pDataTIC_Y){
        if(mLoadDataFile)
            return mLoadDataFile->loadFileTIC(pFilePath, pDataTIC_X, pDataTIC_Y);
        return false;
    }
    bool loadFileMass(QString pFilePath,int index, QVector<double>& pData,QByteArray& pStreamHead){
        if(mLoadDataFile)
            return mLoadDataFile->loadFileMass(pFilePath, index, pData, pStreamHead);
        return false;
    }
    bool loadFileMass(QString pFilePath,int index, std::vector<double>& pData,QByteArray& pStreamHead){
        if(mLoadDataFile)
            return mLoadDataFile->loadFileMass(pFilePath, index, pData, pStreamHead);
        return false;
    }
    //棒图
    bool loadFileMass(QString pFilePath,int index, std::vector<double>& xData, std::vector<double>& yData, QByteArray& pStreamHead){
        if(mLoadDataFile)
            return mLoadDataFile->loadFileMass(pFilePath, index, xData, yData, pStreamHead);
        return false;
    }
    bool loadFileMass(QString pFilePath, int nFrameB, int nFrameE, std::vector<double>& pData,QByteArray& pStreamHead){
        if(mLoadDataFile)
            return mLoadDataFile->loadFileMass(pFilePath, nFrameB, nFrameE, pData, pStreamHead);
        return false;
    }
    bool loadFileMassInX(QString pFilePath, int indexX, std::vector<double>& pData,QByteArray& pStreamHead){
        if(mLoadDataFile)
            return mLoadDataFile->loadFileMassInX(pFilePath, indexX, pData, pStreamHead);
        return false;
    }
    //棒图
    bool loadFileMassInX(QString pFilePath, double mass, std::vector<double>& pData,QByteArray& pStreamHead){
        if(mLoadDataFile)
            return mLoadDataFile->loadFileMassInX(pFilePath, mass, pData, pStreamHead);
        return false;
    }
    bool loadFileMassInX(QString pFilePath, double mass, int indexX, std::vector<double>& pData,QByteArray& pStreamHead){
        if(mLoadDataFile)
            return mLoadDataFile->loadFileMassInX(pFilePath, mass, indexX, pData, pStreamHead);
        return false;
    }
    bool AnalyzeScan(std::vector<double>& pX, std::vector<double>& pY,
                     int uEvtValidPoint, uint uWidth, bool reStart);
/** dataAnalusis struct*/
//    std::vector<double> *mAbsc,*mOrd,           //size-nPeak
//        cAbsc1,cOrd1;                           //size-uWidth
//    std::vector<int> *mStart, *mEnd, *mMarker,  //size-nPeak
//        iStart1,iEnd1;                          //size-uWidth

    std::vector<double> cFWHM;                  //size-uWidth
    QVector<QString> strMarker;                 //size-uWidth

    std::vector<double> mBaseLine;              //size-allPoint
    cDataProcess* mDataProcess= nullptr;

protected:
    SThread* mAnalyzeThread= nullptr;
    static int analyzeThread(void *pParam, const bool &bRunning);

    QString mFileNameTIC;
    QString mFileNameMass;
    //bool mIsTIC=true;
    _TYPE_THREAD m_TYPE_THREAD=_TYPE_TIC;
    uint mFrame=0;

    QMutex mGraphBuffMutexMass;
    QMutex mGraphBuffMutexTIC;
    
    bool eventFilter(QObject *watched, QEvent *event);
    
private:
    Ui::sDataAnalysis *ui;
    cLoadDataFile* mLoadDataFile=nullptr;
    sChartWidget* mChartMass;
    sChartWidget* mChartTIC;
    FileListWidget* fileListWidget;
    ColorSelectTool* select;
    _CONGIG_OMS::_CONGIG_ANALYSIS mCONGIG_ANALYSIS;

    QList<QPair<sChartWidget::XICInform*,myGroupBox*>> XICInformList;

    QString datapath;
    bool isOriginal;
    bool hasLine;

    int touchPointX;

    int mCurrentMass=-1;
    //int mCountLine=0;
    //int mCountLineMass=0;
    //double mCurrentX=0.0;
    void panTriggered(QPanGesture*);
    void pinchTriggered(QPinchGesture*);
    bool gestureEvent(QGestureEvent*);
    void changeLinePos(int move);
    void changeLinePos(int movex, int movey);
    bool isEdit = false;

    QPair<sChartWidget::XICInform*,myGroupBox*> getCurrentCurve();
    void updateTIC(QPair<sChartWidget::XICInform*,myGroupBox*> tempTIC);

signals:
    void sUpdateGraphMass();
    void sUpdateGraphTIC();
    void ChangedManager(QList<QPair<sChartWidget::XICInform*,myGroupBox*>>, bool);
    void hideCurve(sChartWidget::XICInform*,bool);
    void deleteCurve(sChartWidget::XICInform*);

public slots:
    void onUpdateGraphMass();
    void onUpdateGraphTIC();
    void onSelectedTIC(const double);
    void onSelectedMass(const double);
    void onCurrentItemChanged(QListWidgetItem*,QListWidgetItem*);
    void onListDoubleClicked(QModelIndex);
    void onDelClicked();

    void onGetCurrentFilePath(QString TICFile, QString MassFile, bool state);

    void onGroupBoxClicked(myGroupBox*,bool);
    void onGroupBoxRemoved(myGroupBox*);

private slots:
    void on_UI_PB_LOAD_clicked();
    void on_UI_PB_NEXT_clicked();
    void on_UI_PB_LAST_clicked();
    void on_UI_PB_TIC_CHOOSE_clicked();
    void on_UI_PB_ACCTIC_clicked();
    void on_UI_PB_MASS_CHOOSE_clicked();
    void on_UI_PB_CALCULATE_clicked();
    void on_UI_PB_TIC_CLEAR_clicked();
    void on_UI_PB_MASS_CLEAR_clicked();
    void on_pushButton_clicked();
    void on_BtnAdd_clicked();
    void on_BtnChange_clicked();
    void on_btn_saveFrame_clicked();
};

#endif // SDATAANALYSIS_H
