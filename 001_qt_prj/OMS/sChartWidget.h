#ifndef SCHARTWIDGET_H
#define SCHARTWIDGET_H
#include <qwt_legend.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_zoomer.h>
#include <QGestureEvent>
#include <QMutex>
#include <QColor>
#include <QLabel>
#include <QPushButton>
#include <QStackedLayout>
#include <qwt_scale_draw.h>
#include <LibWidget/sMyButton.h>
#include <LibWidget/ListWidget/sTICList.h>
#include "sTvplot.h"
#include "myGroupBox.h"
//#include "CPublic.h"
//#include "cProcessing.h"
//#include "sInputdialog.h"
#include "sChartChildren/sChartXIC.h"
#include "LibWidget/sFileWidget.h"

#define SMS_CHANNEL_COUNT 64
//struct ObjectPropT{
//    QObject* obj = NULL;
//    QString name;
//};

//struct SignalProp{
//    ObjectPropT signal;
//    TVPlot* cuver = NULL;
//    uint32_t localVersion = 0;
//    double defaultxStart = 0;
//    double defaultxEnd = 1;

//    std::vector<double> bufx;
//    std::vector<double> bufy;
//    std::vector<double> cAbsc;
//    std::vector<double> cOrd;
//    std::vector<int> iStart;
//    std::vector<int> iEnd;
//    std::vector<double> cFWHM;
//    std::vector<double> cArea;
//};

/**
 * @brief The DistroScaleDraw class
 * 用来设置谱图控件颜色的类
 */
class DistroScaleDraw:public QwtScaleDraw
{
public:
    DistroScaleDraw():QwtScaleDraw(),mColor(QColor(0,0,0)){}
    QColor mColor;
    void setColor(QColor pColor){
        mColor= pColor;
    }
    virtual QwtText label(double value) const{
        QwtText text(QString::number(value));
        text.setColor(mColor);
        return text;
    }
};

class DistroQwtLegend:public QwtLegend
{
public:
    DistroQwtLegend( QWidget *parent = NULL ):QwtLegend(parent){}
    QString mColor= "color:#E4DAD0;";
    void setColor(QString pColor){
        mColor= pColor;
        contentsWidget()->setStyleSheet(mColor);
    }
};

/**
 * @brief The sChartWidget class
 * 通用谱图控件类
 */
class sChartWidget:public QWidget
{
    Q_OBJECT
public:

    //XIC显示结构体
    struct XICInform{
        double mass;    //质量数
        int beginTime;  //起始时间
        int endTime;    //终止时间
        double massArea;  //峰面积
        double massRange = 0.0;
        std::vector<double> yListXIC;
        double Gain=1;
        double Offset=0;
        QColor color;
    };

    enum _STYLE_CHART{_NORMAL_CHART,_TIC_CHART,_TUNING_CHART,_ENORMAL_CHART};
    struct _GRAPH_XIC:sChartXIC::_PARAM_XIC{//:PEAK_VALUE{
    public:
        double massRange=0.5;
        std::vector<double> yListXIC;
        QwtPlotCurve* curve=nullptr; /**< TODO */
        _GRAPH_XIC(){}
        ~_GRAPH_XIC(){
            if(curve){//curve-> detach();
                delete curve;
                curve=nullptr;
            }
        }
    };
    explicit sChartWidget(_STYLE_CHART _STYLE_CHART1,bool state = true, QWidget *parent = 0);
    ~sChartWidget();


    //QMap<QString, SignalProp>& signals_Centroid();
    QMap<QString,QString> mPublicProperty;
    QMap<QString,QString> mPlotProp;
    void propertyChanged(QString QString1);
    QString GetClassProp();
    bool isShow(){
        return bShow;
    }
    void setBackgroundColor(QColor pQColor){
        mQColor=pQColor;
        QPalette palette;
        palette.setColor(QPalette::Background, mQColor);//QColor(148,163,220));
        this->setPalette(palette);
    }
    QColor getColor(){
        return mQColor;
    }
    void setStyleM(TVPlot::MPlotStyle type, QString title, double xStart,double xEnd);
    void setTitle(QString title){
        mPublicProperty["Title"]=title;
        pTitle->setText(title);
    }
    QString getTitle(){
        QString tmpStr=pTitle->getText();
        QStringList tmpList=tmpStr.split("  ");
        if(tmpList.size()<2)
            return tmpStr;
        else
            return tmpList[0]+"\n"+tmpList[1];
    }

    void setSamples(std::vector<double>& ValuesX,std::vector<double>& ValuesY);
    void setSamples( const double *xData, const double *yData, int size, bool save= true);
    void SetMarker(std::vector<double>const& ValuesX,std::vector<double>& ValuesY,QVector<QString>& Marker){
        m_Histogram_plot->SetMarker(ValuesX,ValuesY,Marker);
    }
    void SetMarker(std::vector<double>const& ValuesX,std::vector<double>& ValuesY,std::vector<double>& Marker){
        m_Histogram_plot->SetMarker(ValuesX,ValuesY,Marker);
    }
    //void setTitle(QString title);
    void setScale(QwtPlot::Axis axic1, QString ScaleBottom);
    void setZoomBase(bool setBase){
        m_Histogram_plot->setZoomBase(setBase);
    }
    void updateXIC(QString XicString);
    void updateXIC(QList<QPair<sChartWidget::XICInform*,myGroupBox*>> XICList);
    QMap<uint32_t, QMap<QString, _GRAPH_XIC*>>* getXIC(){
        return &mXIC;
    }
    void clearBuffXIC();
    bool drawXIC(std::vector<double>& pX, uint32_t sizeTIC, int timeout= 50);
    bool drawXIC(std::vector<double>& pX);
    void lockXIC(){
        return mutex_XIC.lock();
    }
    bool tryLockXIC(int timeout = 0){
        return mutex_XIC.tryLock(timeout);
    }
    void unLockXIC(){
        return mutex_XIC.unlock();
    }
    QwtPicker *getPicker(){//DistroQwtPicker *getPicker(){
        return mPicker;
    }
    void addBaseLine(double y = 0,QColor color= Qt::black);
    void addLine(double x,QColor color = Qt::black);
    void removeLine(){
        if(mLineMark.size()>0){
            if(mLineMark.last()){
                delete mLineMark.last();
                mLineMark.last()=nullptr;
            }
            mLineMark.removeLast();
        }
        m_Histogram_plot->replot();
    }
    void clearMycurve();

    void clearLine();
    void clearLine(double mass);
    QList<double> getLineMark();

    void copy2BuffXIC(const std::vector<double>& ValuesX, const std::vector<double>& ValuesY){
        mValuesX.resize(ValuesX.size());
        mValuesY.resize(ValuesY.size());
        memcpy(&(mValuesX.at(0)),&(ValuesX.at(0)),ValuesX.size()*sizeof(double));
        memcpy(&(mValuesY.at(0)),&(ValuesY.at(0)),ValuesY.size()*sizeof(double));
    }

    void setFileHead(QByteArray& fileHead){
        mFileHead= QString::fromUtf8(fileHead);
    }
    void setFileHead(QString& fileHead){
        mFileHead= fileHead;
    }
    uint32_t mCountSave=0;
    QString mCurrentFile;
    void saveToFile(QString pathName);

    void setDataPath(QString path)
    {
        dataPath = path;
    }


public slots:
    void onTitleClicked();
    void exportPlot();
    void onSelectFile(bool,QString);
    void setPlot();
    void ShowPlot();
    void on_ShowManager(){
        pStackedLayout->setCurrentIndex(1);
    }
    void on_hide(){
        this->hide();
        emit CommandSignal("hide",this ,(void*)0 );
    }
    void onSelected(const QPointF& );
    void on_ChangedManager(QString strProp, bool bModify){
        if(mChartXIC){
            pStackedLayout->setCurrentIndex(0);
            if(bModify)
                updateXIC(strProp);
        }
    }

    void on_ChangedManager(QList<QPair<sChartWidget::XICInform*,myGroupBox*>> XICList,bool bModify)
    {
        if(mChartXIC){
            pStackedLayout->setCurrentIndex(0);
            if(bModify)
                updateXIC(XICList);
        }
    }

    void onHideXIC(uint32_t msXIC, QString XicString, bool show);//signal from class sTICList, show or hide one of line XIC
    //质量选择提示线
    void onMassWidgetAddLine(double mass,QColor color);
    void onItemRemove(double mass);

    void onHideCurve(sChartWidget::XICInform*, bool state);
    void ondeleteCurve(sChartWidget::XICInform*);

private:
    enum _NAME_BUTTON{_PROP_BUTTON = 0, _EXPORT_BUTTON, _XIC_BUTTON, _CLOSE_BUTTON, NUM_BUTTON};
    _STYLE_CHART m_STYLE_CHART= _NORMAL_CHART;
    QStackedLayout* pStackedLayout  = nullptr;//谱图控件与XIC编辑控件布局//同层
    //SignalProcessing mSignalProcessing;       //数据处理类
    TVPlot* m_Histogram_plot        = nullptr;//谱图控件
    //QwtLegend* m_legend             = nullptr;//谱图控件右标，TIC组件专用
    DistroQwtLegend* m_legend             = nullptr;//谱图控件右标，TIC组件专用
    sChartXIC* mChartXIC            = nullptr;//XIC编辑控件

    QwtPlotPicker *mPicker=nullptr;//DistroQwtPicker *mPicker=nullptr;

    bool isTitleClicked             = false;  //用来判断Title控件是否点击，显/隐其他按键
    MyWidget::sMyButton* pTitle     = nullptr;//Title控件
    MyWidget::sMyButton* pProp      = nullptr;//属性按键
    MyWidget::sMyButton* pEditXIC   = nullptr;//XIC编辑按键
    MyWidget::sMyButton* pSave      = nullptr;//谱图数据保存按键
    //    MyWidget::sMyButton* pScreenShot= nullptr;//谱图图像存储按键

    QList<QwtPlotMarker*> mLineMark;//QList<QPair<QwtPlotMarker*, QwtPlotMarker*>> mLineMark;

    QMutex mutex;//current data locker
    QMutex mutex_XIC;
    QMutex mutex_MyCurve;
    bool bShow=true;
    QColor mQColor=QColor(148,163,220);
    std::vector<double> mValuesX;//current data for save
    std::vector<double> mValuesY;//current data for save
    //QMap<QString, _GRAPH_XIC> m_xics;
    QMap<uint32_t, QMap<QString, _GRAPH_XIC*>> mXIC;
    QList<QPair<XICInform*,QwtPlotCurve*>> myCurve;

    sFileWidget mFileWidget;

    QString mFileHead;
    double mCurrentX=0.0;

    //sTICList* mTICList;
private://触摸屏
    bool m_bGesture=false;
    bool bMouseM=false;
    bool operateLock = true;

    QPoint mStartPos;
    int mRectW=0;
    double mCurrentStartX=0,
    mCurrentEndX=0;
    int mCenterX=0;
    int mLastStartX=0;
    int mLastEndX=0;
    qreal mScale=1;
    qreal mAngle=0;

    bool isFirstCenter=true;
    double canvasW=0;
    int tmpStartX=0;
    int tmpEndX=0;
    double startMass;
    double endMass;

    QString dataPath;

    void pinchTriggered(QPinchGesture *gesture);
    bool gestureEvent(QGestureEvent *event);

    bool xPinchTriggered(QPinchGesture *gesture);
    bool yPinchTriggered(QPinchGesture *gesture);
    bool xPanTriggered(QPanGesture* gesture);
    bool yPanTriggered(QPanGesture* gesture);

protected:
    //QMap<QString, SignalProp> m_signals_Centroid;
    //bool event(QEvent *event);
    bool eventFilter(QObject *obj, QEvent *ev);
signals:
    void ChangedXIC(QString);
    void CommandSignal(QString ,sChartWidget* ,void* );
    void selected( const double);
};

#endif // SCHARTWIDGET_H
