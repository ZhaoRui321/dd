#include "sChartWidget.h"
#include <QGridLayout>
#include <QTimerEvent>
#include <qwt_plot_renderer.h>
//#include <sobject.h>
//#include <sproject.h>
#include <QMenuBar>
#include <qwt_plot_grid.h>
#include <QSettings>
#include <QFileDialog>
#include <QGestureEvent>
#include <qwt_picker_machine.h>
#include <LibWidget/sinputdialog.h>

using namespace MyWidget;
sChartWidget::sChartWidget(_STYLE_CHART _STYLE_CHART1, bool state, QWidget *parent):
    m_STYLE_CHART(_STYLE_CHART1),
    QWidget(parent)
{
    setAutoFillBackground(true);
    mPublicProperty.insert("Title","");
    mPublicProperty.insert("RangeX","auto");
    mPublicProperty.insert("RangeY","auto");

    mPlotProp.insert("RangeX","auto");
    mPlotProp.insert("RangeY","auto");

    QVBoxLayout* pLayout = new QVBoxLayout(this);
    pLayout->setContentsMargins(0,0,0,5);
    pLayout->setSpacing(0);
    QHBoxLayout* pTitleLayout = new QHBoxLayout;
    pTitleLayout->setContentsMargins(0,0,0,2);
    pTitleLayout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Expanding,QSizePolicy::Expanding));
    QHBoxLayout* pTitleChild = new QHBoxLayout;
    pTitleChild->setContentsMargins(0,0,0,0);
    pTitleChild->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Expanding,QSizePolicy::Expanding));
    pStackedLayout = new QStackedLayout();
    QHBoxLayout* pCentralLayout = new QHBoxLayout;
    pCentralLayout->addLayout(pStackedLayout);
    pLayout->addLayout(pTitleLayout,0);
    pLayout->addLayout(pCentralLayout,1);//pLayout->addLayout(pStackedLayout,1);
    pLayout->setStretch(1,1);
    setLayout(pLayout);

    dataPath = QDir::currentPath();

    mChartXIC = new sChartXIC();                        //构造XIC编辑控件

    connect(mChartXIC, SIGNAL(ChangedManager(QString, bool )),
            this,SLOT(on_ChangedManager(QString, bool )));

    m_Histogram_plot = new TVPlot(this);                //构造谱图控件
    m_Histogram_plot->setProperty("__uid", "ins");
    m_Histogram_plot->setAxisScaleDraw(QwtPlot::yLeft, new DistroScaleDraw());
    m_Histogram_plot->setAxisAutoScale(QwtPlot::yLeft, true);
    m_Histogram_plot->setAxisScaleDraw(QwtPlot::xBottom, new DistroScaleDraw());
    m_Histogram_plot->setAxisAutoScale(QwtPlot::xBottom, true);
    m_Histogram_plot->setCanvasBackground(QBrush(QColor(255,255,255)));

    m_Histogram_plot->canvas()->installEventFilter(this);
//    (m_Histogram_plot->axisWidget(QwtPlot::yLeft))->installEventFilter(this);
//    (m_Histogram_plot->axisWidget(QwtPlot::xBottom))->installEventFilter(this);

    mPicker = new QwtPlotPicker(m_Histogram_plot->canvas());//mPicker = new  DistroQwtPicker(m_Histogram_plot->canvas());
    mPicker->setStateMachine(new QwtPickerClickPointMachine);
    connect(mPicker,SIGNAL(selected(const QPointF &)),this,SLOT(onSelected(const QPointF &)));

    QwtPlotGrid *grid = new QwtPlotGrid;                //网格
    grid->setMajorPen(QPen(Qt::gray, 0, Qt::DotLine));  //大格子
    grid->attach(m_Histogram_plot);

    QFont mfont;
    mfont.setPointSize(24);
    mfont.setFamily("Microsoft YaHei");
    if(m_STYLE_CHART==_TUNING_CHART){
        pTitle= new sMyButton(this);
    }else{
        pTitle= new sMyButton(QPixmap(":/picture/title.png"),mfont,this);
    }
    pTitle->setMinimumWidth(150);
    pTitle->hide();
    connect(pTitle,SIGNAL(ButtonClicked()),this,SLOT(onTitleClicked()));
    pTitle->setLayout(pTitleChild);
    pTitleLayout->addWidget(pTitle);
    pProp = new sMyButton(QPixmap(":/picture/Widget_menu.png"),mfont,pTitle);
    pProp->hide();
    connect(pProp,SIGNAL(ButtonClicked()),this,SLOT(setPlot()));
    pSave = new sMyButton(QPixmap(":/picture/Widget_save.png"),mfont,pTitle);
    pSave->hide();
    connect(pSave,SIGNAL(ButtonClicked()),this,SLOT(exportPlot()));
//    pScreenShot = new sMyButton(QPixmap(":/picture/Widget_screenShot.png"),mfont,pTitle);
//    pScreenShot->hide();
//    connect(pScreenShot,SIGNAL(ButtonClicked()),this,SLOT(exportPlot()));
    if(m_STYLE_CHART==_TIC_CHART && state){//如果构造为TIC组件，则增加XIC编辑按键、右标
        //m_legend = new DistroQwtLegend(this);
        //m_Histogram_plot->insertLegend(m_legend, QwtPlot::RightLegend);
        m_Histogram_plot->setContentsMargins(0,0,9,0);
//        mTICList= new sTICList(this);
//        pCentralLayout->addWidget(mTICList);
//        connect(mTICList, SIGNAL(ChangedManager(QString, bool )),
//                this,SLOT(on_ChangedManager(QString, bool )));
//        connect(mTICList, SIGNAL(HideXIC(uint32_t , QString , bool )),
//                this,SLOT(onHideXIC(uint32_t , QString , bool )));
        pEditXIC = new sMyButton(QPixmap(":/picture/Widget_xic.png"),mfont,pTitle);
        pEditXIC->hide();
        connect(pEditXIC,SIGNAL(ButtonClicked()),this,SLOT(on_ShowManager()));
        pTitleChild->addWidget(pEditXIC);
    }
    pTitleChild->addWidget(pProp);
    pTitleChild->addWidget(pSave);
//    pTitleChild->addWidget(pScreenShot);

    pStackedLayout->addWidget(m_Histogram_plot);
    pStackedLayout->addWidget(mChartXIC);
    pStackedLayout->addWidget(&mFileWidget);
    connect(&mFileWidget,SIGNAL(selectFile(bool,QString)),this,SLOT(onSelectFile(bool,QString)));
    grabGesture(Qt::PinchGesture);
}


sChartWidget::~sChartWidget()
{
    lockXIC();
    QMutableMapIterator< uint32_t, QMap<QString, _GRAPH_XIC*> > tempIter(mXIC);
    while (tempIter.hasNext()) {
        QMutableMapIterator<QString, sChartWidget::_GRAPH_XIC*> tempIter1(tempIter.next().value());
        while (tempIter1.hasNext())
            delete tempIter1.next().value();
    }
    unLockXIC();
    if(m_Histogram_plot!=NULL)
        delete m_Histogram_plot;
    m_Histogram_plot=NULL;
}

void sChartWidget::onTitleClicked()
{
    if(isTitleClicked){
        if(pProp)       pProp->hide();
        //if(pEditXIC)    pEditXIC->hide();
        if(pSave)       pSave->hide();
//        if(pScreenShot) pScreenShot->hide();
    }else{
        if(pProp)       pProp->show();
        //if(pEditXIC)    pEditXIC->show();
        if(pSave)       pSave->show();
//        if(pScreenShot) pScreenShot->show();
    }
    isTitleClicked=!isTitleClicked;
}
void sChartWidget::saveToFile(QString pathName)
{
    QwtPlotRenderer renderer;
    renderer.renderDocument(m_Histogram_plot, pathName+".jpg",QSizeF( 300, 200 ));
    QFile file(pathName+".txt");
    if(file.open(QFile::WriteOnly|QIODevice::Text)){
        mutex.lock();
        uint32_t buffSize=mValuesX.size();
        if((buffSize>0)&&(buffSize==mValuesY.size())){
            QTextStream stream(&file);
            stream << mFileHead<< "\n";
            stream << "_X\t_Y\n";
            for(uint32_t i=0;i<buffSize;i++)
                stream << QString::number(mValuesX.at(i)) << "\t"<< QString::number(mValuesY.at(i)) << "\n";
        }
        mutex.unlock();
//        mutex_XIC.lock();
//        if((buffSize>0)&&(m_xics.size()>0)){
//            for(auto iterXic = m_xics.begin();
//                iterXic != m_xics.end(); iterXic++){
//                if(iterXic->data.size()<=0)
//                    continue;
//                QTextStream stream(&file);
//                stream << "data_XIC\nEvent:"
//                       <<iterXic.value().nEvent<<"\nGain:"
//                      <<iterXic.value().Gain<<"\nOffset:"
//                     <<iterXic.value().Offset<<"\nmass:"
//                       //<<iterXic.value().color.toRgb()
//                    <<iterXic.value().mass<<"\n";
//                for(int i=0;i<buffSize;i++)
//                    stream << QString::number(iterXic->data.at(i)) << "\n";
//            }
//        }
//        mutex_XIC.unlock();
        file.close();
    }
}

void sChartWidget::exportPlot()
{
    QString pathName= dataPath+"/data";
    if(mFileWidget.getFrameCount()== 1)
        saveToFile(pathName+"/tmpfile");
    pStackedLayout->setCurrentIndex(2);

    QDateTime dateTime = QDateTime::currentDateTime();
    QLocale locale = QLocale::English;
    QString strFormat = "H.m.s-a-yyyy.MMMM.dd";
    mFileWidget.creatNewFile(pathName, locale.toString(dateTime, strFormat));
}

void sChartWidget::onSelectFile(bool selected,QString fileName)
{
    pStackedLayout->setCurrentIndex(0);
    QString pathName = dataPath+"/data/";
    if(selected){
        if(mFileWidget.getFrameCount()== 1){
            QFile::rename(pathName+ "tmpfile.jpg",pathName+fileName+".jpg");
            QFile::rename(pathName+ "tmpfile.txt",pathName+fileName+".txt");
            mCountSave=0;
        }else{
            QFile::remove(pathName+ "tmpfile.jpg");
            QFile::remove(pathName+ "tmpfile.txt");
            mCurrentFile= pathName+fileName;
            mCountSave= mFileWidget.getFrameCount();
        }
    }else{
        if(mFileWidget.getFrameCount()== 1){
            QFile::remove(pathName+ "tmpfile.jpg");
            QFile::remove(pathName+ "tmpfile.txt");
        }
        mCountSave=0;
    }
}

void sChartWidget::setPlot()
{
    QStringList lstName, lstValue, lstButton;
    {
        lstName << "RangeX"<<"RangeY";
        lstValue << mPlotProp["RangeX"]
                 << mPlotProp["RangeY"];
        lstButton << "OK" << "Cancel";
        SInputDialog dlgSet(lstName, lstValue, lstButton, this);
        dlgSet.setWindowTitle("Setting plot");
        if(dlgSet.execEx() == "OK"){
            QString strRange = dlgSet.parameter("RangeX");
            if(!strRange.isEmpty()){
                mPlotProp["RangeX"]=strRange;
                setScale(QwtPlot::xBottom, mPlotProp["RangeX"]);
            }
            strRange = dlgSet.parameter("RangeY");
            if(!strRange.isEmpty()){
                mPlotProp["RangeY"]=strRange;
                if(strRange.compare("auto", Qt::CaseInsensitive) == 0){
                    setScale(QwtPlot::yLeft, mPlotProp["RangeY"]);
                }else{
                    QStringList lstRange = strRange.split(',');
                    if(lstRange.size() >= 2)
                        m_Histogram_plot->setAxisScale(QwtPlot::yLeft, lstRange[0].toDouble(),
                                lstRange[1].toDouble());
                    m_Histogram_plot->setZoomBase(true);
                }

            }
        }
    }
}

//QMap<QString, SignalProp>& sChartWidget::signals_Centroid()
//{
//    return m_signals_Centroid;
//}

void sChartWidget::setStyleM(TVPlot::MPlotStyle type, QString title, double xStart,double xEnd)
{
    m_Histogram_plot->setStyle(type);
    if(m_STYLE_CHART!=_TUNING_CHART){
        if(mPublicProperty["Title"] != title)
            setTitle(title);
    }
    if(m_STYLE_CHART == _NORMAL_CHART){
        startMass = xStart;
        endMass = xEnd;
    }

    QString strRange= QString::number(xStart)+","+QString::number(xEnd);
    if(mPublicProperty["RangeX"]!= strRange){
        mPublicProperty["RangeX"]=strRange;
        if(mPlotProp["RangeX"] == "auto" ||
                mPlotProp["RangeX"].isEmpty()){
            setScale(QwtPlot::xBottom, strRange);
        }else {
            setScale(QwtPlot::xBottom, mPlotProp["RangeX"]);
        }
    }
    mCurrentStartX=xStart;
    mCurrentEndX=xEnd;
    m_Histogram_plot->setXRange(xStart,xEnd);

}

QString sChartWidget::GetClassProp(){
    return mPublicProperty["Title"]+"/"
            +mPlotProp["RangeX"]+"/"
            +mPlotProp["RangeY"];
}
void sChartWidget::propertyChanged(QString QString1)//const QString& strPropName, const QString& varValue)
{
//    QStringList QStringList1 = QString1.split('/');
//    if(QStringList1.size()!=3)
//        return;
//    if((QStringList1[0]!=mPublicProperty["TopTitle"])&&(!QStringList1[0].isEmpty())){
//        mPublicProperty["TopTitle"]=QStringList1[0];
//        setTitle(QStringList1[0]);
//    }
//    if((QStringList1[1]!=mPublicProperty["RangeX"])&&(!QStringList1[1].isEmpty())){
//        mPublicProperty["RangeX"]=QStringList1[1];
//        setScale(QwtPlot::xBottom, QStringList1[1]);
//    }
//    if((QStringList1[2]!=mPublicProperty["RangeY"])&&(!QStringList1[2].isEmpty())){
//        mPublicProperty["RangeY"]=QStringList1[2];
//        setScale(QwtPlot::yLeft, QStringList1[2]);
//    }
}

void sChartWidget::setScale(QwtPlot::Axis axic1, QString strScale)
{
    if(m_Histogram_plot!= NULL && !strScale.isEmpty()){
        if(strScale.compare("auto", Qt::CaseInsensitive) == 0){
            m_Histogram_plot->setAxisAutoScale(axic1, true);
        }else{
            QStringList lstRange = strScale.split(',');
            if(lstRange.size() >= 2){
                m_Histogram_plot->setAxisScale(axic1, lstRange[0].toDouble(),
                        lstRange[1].toDouble());
                //m_Histogram_plot->setZoomBase(true);
            }
        }
    }
}

void sChartWidget::setSamples(std::vector<double> &ValuesX,
                                  std::vector<double>& ValuesY)
{
    if(ValuesX.size() < 1)
    {
        ValuesX.push_back(mCurrentStartX);
        ValuesY.push_back(0);
        ValuesX.push_back(mCurrentEndX);
        ValuesY.push_back(0);
    }
    m_Histogram_plot->populate(ValuesX,ValuesY);
    if(mutex.tryLock()){
        mValuesX.resize(ValuesX.size());
        mValuesY.resize(ValuesY.size());
        memcpy(&(mValuesX.at(0)),&(ValuesX.at(0)),ValuesX.size()*sizeof(double));
        memcpy(&(mValuesY.at(0)),&(ValuesY.at(0)),ValuesY.size()*sizeof(double));
        mutex.unlock();
    }
//    if(mPublicProperty["RangeY"].compare("auto", Qt::CaseInsensitive) == 0)
//        m_Histogram_plot->setAxisAutoScale(QwtPlot::yLeft, true);
}
void sChartWidget::setSamples( const double *xData, const double *yData, int size, bool save)
{
    if(save){
        m_Histogram_plot->populate(xData, yData, size);
        if(mutex.tryLock()){
            mValuesX.resize(size);
            mValuesY.resize(size);
            memcpy(&(mValuesX.at(0)),xData,size*sizeof(double));
            memcpy(&(mValuesY.at(0)),yData,size*sizeof(double));
            mutex.unlock();
        }
    }else{
        m_Histogram_plot->setSamples(xData, yData, size);
    }

}
void sChartWidget::ShowPlot()
{
//    if(bShow){
//        m_Histogram_plot->hide();
//        pButton->setIcon(QIcon(":/Histogram/picture/u=1839574454,1247872404&fm=23&gp=1.jpg"));
//              pButton->setIconSize(QSize(50, 50));
//              bShow=false;
//    }else{
//        m_Histogram_plot->show();
//        pButton->setIcon(QIcon(":/Histogram/picture/u=1839574454,1247872404&fm=23&gp=0.jpg"));
//              pButton->setIconSize(QSize(50, 50));
//              bShow=true;
//    }
}

void sChartWidget::pinchTriggered(QPinchGesture *gesture)
{
    QPinchGesture::ChangeFlags changeFlags = gesture->changeFlags();
    //isFirstCenter=true;
    //canvasW=0;
    //tmpStartX=0;
    //tmpEndX=0;
    if (changeFlags & QPinchGesture::CenterPointChanged) {
        if(isFirstCenter){
            isFirstCenter=false;
            if(mLastEndX==0){
                mLastStartX=0;
                mLastEndX=mValuesX.size()-1;
            }
            mScale=1;
            QPoint startValue=gesture->property("lastCenterPoint").toPoint();
            canvasW=(double)(m_Histogram_plot->canvas()->width());
            mCenterX=(int)(double(startValue.x())*double(mLastEndX-mLastStartX)
                           /canvasW+mLastStartX);
        }
    }
    if (changeFlags & QPinchGesture::ScaleFactorChanged) {
        qreal lastValue=gesture->property("lastScaleFactor").toReal();
        if(lastValue>0 || lastValue<0){
            mScale*=lastValue;
            QPoint startValue=gesture->property("lastCenterPoint").toPoint();
            double dcanvasX=double(startValue.x())/mScale;
            tmpStartX=mCenterX-double(mLastEndX-mLastStartX)*dcanvasX/canvasW;
            tmpEndX=tmpStartX+double(mLastEndX-mLastStartX)/mScale;
            if(tmpStartX<0)
                tmpStartX=0;
            if(tmpEndX>mValuesY.size()-1)
                tmpEndX=mValuesY.size()-1;
            m_Histogram_plot->setAxisScale(QwtPlot::xBottom, mValuesX[tmpStartX],
                                           mValuesX[tmpEndX]);
        }
    }
    if (gesture->state() == Qt::GestureFinished) {
        mLastStartX=tmpStartX;
        mLastEndX=tmpEndX;
        isFirstCenter=true;
        bMouseM=false;
    }
}

bool sChartWidget::gestureEvent(QGestureEvent *event)
{
    if (QGesture *pinch = event->gesture(Qt::PinchGesture))
        pinchTriggered(static_cast<QPinchGesture *>(pinch));
    return true;
}

//bool sChartWidget::event(QEvent *event)
//{
//    if (event->type() == QEvent::Gesture)
//        return gestureEvent(static_cast<QGestureEvent*>(event));
//    return QWidget::event(event);
//}

bool sChartWidget::xPanTriggered(QPanGesture *gesture)
{
    QPointF point = gesture->delta();
    qreal dx = point.x();
    const QwtScaleDiv scaleDiv = m_Histogram_plot->axisScaleDiv(QwtPlot::xBottom);
    double begin = scaleDiv.lowerBound();
    double end = scaleDiv.upperBound();

}

bool sChartWidget::yPanTriggered(QPanGesture *gesture)
{

}

bool sChartWidget::xPinchTriggered(QPinchGesture *gesture)
{

}

bool sChartWidget::yPinchTriggered(QPinchGesture *gesture)
{

}

bool sChartWidget::eventFilter(QObject *obj, QEvent *ev)
{
#if 0
    if(ev->type() == QEvent::Gesture){
        QGestureEvent* event = static_cast<QGestureEvent*>(ev);
        if(QGesture *pinch = event->gesture(Qt::PinchGesture)){
            if(obj == m_Histogram_plot->canvas()){
                //x轴缩放
            }else if(obj == (QWidget*)(m_Histogram_plot->axisWidget(QwtPlot::yLeft))){
                //y轴缩放
            }else if(obj == (QWidget*)(m_Histogram_plot->axisWidget(QwtPlot::xBottom))){
                //备用
            }
        }else if(QGesture *pan = event->gesture(Qt::PanGesture)){
            if(obj == m_Histogram_plot->canvas()){
                //x轴移动
            }else if(obj == (QWidget*)(m_Histogram_plot->axisWidget(QwtPlot::yLeft))){
                //y轴缩放
            }else if(obj == (QWidget*)(m_Histogram_plot->axisWidget(QwtPlot::xBottom))){
                //备用
            }
        }
    }
#endif

    Q_UNUSED(obj)
    if (ev->type() == QEvent::MouseButtonDblClick)
        return true;
    if (ev->type() == QEvent::MouseButtonPress ||
            ev->type() == QEvent::MouseButtonRelease ){//||ev->type() == QEvent::MouseButtonDblClick
        QMouseEvent *mouseev = static_cast<QMouseEvent *>(ev);
        if(mouseev->button() == Qt::LeftButton) {
            if(m_bGesture){
                if(ev->type() == QEvent::MouseButtonPress){
                    mStartPos=mouseev->pos();
                    bMouseM=true;
                }else if(ev->type() == QEvent::MouseButtonRelease){
                    if(bMouseM){
                        int distance = (mouseev->pos() - mStartPos).manhattanLength();
                        if (distance >= 50){//QApplication::startDragDistance()
                            qDebug("Eat Left button!");
                        }
                    }
                }
                return true;
            }else{
                if(ev->type() == QEvent::MouseButtonPress){
                    mStartPos=mouseev->pos();
                    //bPickerM=false;
                }else if(ev->type() == QEvent::MouseButtonRelease){
                    //if(!bMouseM){
                    int distance = (mouseev->pos() - mStartPos).manhattanLength();
                    if (distance < 5){//QApplication::startDragDistance()
                        emit selected(mCurrentX);//bPickerM=true;
                    }
                    //else
                        //                            bPickerM=false;
                        //}
                }
                return false;//false控制鼠标启用
            }
        }else if(mouseev->button() == Qt::RightButton){
#if 1
            if(m_Histogram_plot!=NULL){
                if(mPlotProp["RangeX"] == "auto" ||
                        mPlotProp["RangeX"].isEmpty())
                    setScale(QwtPlot::xBottom, mPublicProperty["RangeX"]);
                else
                    setScale(QwtPlot::xBottom, mPlotProp["RangeX"]);
                setScale(QwtPlot::yLeft, mPlotProp["RangeY"]);
                mScale=1;
            }
            return true;
#else
            return false;
#endif
        }else
            return false;
    }
    return false;
}

void sChartWidget::onSelected(const QPointF &polygon)
{
    mCurrentX= polygon.x();
}

void sChartWidget::addBaseLine(double y, QColor color)
{
    QwtPlotMarker *my = new QwtPlotMarker();
    my->setLineStyle(QwtPlotMarker::HLine);
    my->setLinePen(QPen(color,1, Qt::SolidLine));
    my->setYValue(y);
    my->attach(m_Histogram_plot);
    m_Histogram_plot->replot();
}

void sChartWidget::addLine(double x,QColor color)
{
    QwtPlotMarker *mX = new QwtPlotMarker();
    //mX->setLabel(QString::fromLatin1(""));
    //mX->setLabelAlignment(Qt::AlignLeft, Qt::AlignBottom);
    //mX->setLabelOrientation(Qt::Vertical);
    mX->setLineStyle(QwtPlotMarker::VLine);
    mX->setLinePen(QPen(color, 1, Qt::DashDotDotLine));
    mX->setXValue(x);
    mX->attach(m_Histogram_plot);
    mLineMark.append(mX);
    m_Histogram_plot->replot();
}

void sChartWidget::clearLine(){
    foreach (auto var, mLineMark) {
        if(var){
            delete var;
            var=nullptr;
        }
    }
    mLineMark.clear();
    m_Histogram_plot->replot();
}

void sChartWidget::clearLine(double x){
    foreach (auto var, mLineMark) {
        if((var->xValue()-x)<0.00001 && (x-var->xValue()<0.00001)){
            delete var;
            var=nullptr;
        }
    }
    //mLineMark.clear();
    m_Histogram_plot->replot();
}

QList<double> sChartWidget::getLineMark()
{
    QList<double> tempList;
    foreach (auto var, mLineMark) {
        if(var)
            tempList.append(var->xValue());
        else
            tempList.clear();
    }
    return tempList;
}

void sChartWidget::updateXIC(QString XicString)
{
    mutex_XIC.lock();
    QMap<uint32_t, QMap<QString, sChartXIC::_PARAM_XIC>> xics;
    QStringList lstStr = XicString.split('/');
    if(lstStr.size()<2){
        mutex_XIC.unlock();
        return;
    }
    double massRange= lstStr[0].toDouble();
    QStringList lstCurves = lstStr[1].split('@');
    foreach (QString strCurve, lstCurves) {
        QStringList lstCurveInfo = strCurve.split(':');
        if(lstCurveInfo.size() < 5)
            continue;
        uint32_t tempEvent= lstCurveInfo[0].toInt();
        if(xics.find(tempEvent)==xics.end())
            xics[tempEvent]= QMap<QString, sChartXIC::_PARAM_XIC>();
        QString tempMass= lstCurveInfo[1];
        xics[tempEvent][tempMass].color    = QColor(QRgb(lstCurveInfo[2].toUInt(NULL, 16)));
        xics[tempEvent][tempMass].Gain     = lstCurveInfo[3].toDouble();
        xics[tempEvent][tempMass].Offset   = lstCurveInfo[4].toDouble();
    }
    //清空
    foreach (auto tmpKey, mXIC.keys()) {
        auto iterXic = xics.find(tmpKey);
        if(iterXic == xics.end()){
            if(mXIC[tmpKey].size()>0){
                foreach (auto tmpKey1, mXIC[tmpKey].keys()){
                    delete mXIC[tmpKey][tmpKey1];
                    mXIC[tmpKey][tmpKey1]= nullptr;
                    mXIC[tmpKey].remove(tmpKey1);
                }
                mXIC[tmpKey].clear();
            }
            mXIC.remove(tmpKey);
        }else{
            foreach (auto tmpKey1, mXIC[tmpKey].keys()){
                auto iterXic1 = xics[tmpKey].find(tmpKey1);
                if(iterXic1 == xics[tmpKey].end()){
                    delete mXIC[tmpKey][tmpKey1];
                    mXIC[tmpKey][tmpKey1]= nullptr;
                    mXIC[tmpKey].remove(tmpKey1);
                }
            }
        }
    }
    //重建
    foreach (uint32_t tmpKey, xics.keys()) {
        auto iterXic = mXIC.find(tmpKey);
        if(iterXic == mXIC.end()){
            mXIC[tmpKey]= QMap<QString, _GRAPH_XIC*>();
            foreach (auto tmpKey1, xics[tmpKey].keys()){
                mXIC[tmpKey][tmpKey1]= new _GRAPH_XIC();
                auto pDest= mXIC[tmpKey][tmpKey1];
                auto& pSrc= xics[tmpKey][tmpKey1];
                pDest->massRange= massRange;
                pDest->color= pSrc.color;
                pDest->Gain= pSrc.Gain;
                pDest->Offset= pSrc.Offset;
                pDest->curve = new QwtPlotCurve(QString("E%1Mass%2").arg(tmpKey).arg(tmpKey1));
                pDest->curve->setPen(pSrc.color);
                if(m_Histogram_plot)
                    pDest->curve->attach(m_Histogram_plot);
            }
        }else{
            foreach (auto tmpKey1, xics[tmpKey].keys()){
                auto iterXic1= mXIC[tmpKey].find(tmpKey1);
                if(iterXic1 == mXIC[tmpKey].end()){
                    mXIC[tmpKey][tmpKey1]= new _GRAPH_XIC();
                    auto pDest= mXIC[tmpKey][tmpKey1];
                    auto& pSrc= xics[tmpKey][tmpKey1];
                    pDest->massRange= massRange;
                    pDest->color= pSrc.color;
                    pDest->Gain= pSrc.Gain;
                    pDest->Offset= pSrc.Offset;
                    pDest->curve = new QwtPlotCurve(QString("E%1Mass%2").arg(tmpKey).arg(tmpKey1));
                    pDest->curve->setPen(pSrc.color);
                    if(m_Histogram_plot)
                        pDest->curve->attach(m_Histogram_plot);
                }else{
                    auto pDest= mXIC[tmpKey][tmpKey1];
                    auto& pSrc= xics[tmpKey][tmpKey1];
                    if(pDest->color!= pSrc.color)
                        pDest->curve->setPen(pSrc.color);
                    pDest->massRange= massRange;
                    pDest->color= pSrc.color;
                    pDest->Gain= pSrc.Gain;
                    pDest->Offset= pSrc.Offset;
                }
            }
        }
    }
    mutex_XIC.unlock();
}

void sChartWidget::updateXIC(QList<QPair<sChartWidget::XICInform *, myGroupBox *> > XICList)
{
   mutex_MyCurve.lock();

   foreach (auto XIC, myCurve) {
       XIC.second->hide();
       delete XIC.second;
   }
   myCurve.clear();

   foreach (auto XICIndex, XICList) {
       XICInform* tempXIC = XICIndex.first;
       QwtPlotCurve* curve = new QwtPlotCurve(QString("Mass:%1").arg(QString::number(tempXIC->mass)));
       curve->setPen(XICIndex.first->color);
       QPair<XICInform*,QwtPlotCurve*> tempPair;
       tempPair.first = tempXIC;
       tempPair.second = curve;
       myCurve.append(tempPair);
       if(m_Histogram_plot)
           curve->attach(m_Histogram_plot);
   }
   mutex_MyCurve.unlock();
}


void sChartWidget::onHideXIC(uint32_t msXIC, QString XicString, bool show)
{
    mutex_XIC.lock();
    _GRAPH_XIC* tempGRAPH_XIC= mXIC[msXIC][XicString];//->curve;
    if(tempGRAPH_XIC){
        if(tempGRAPH_XIC->curve){
            if(show)
                tempGRAPH_XIC->curve->show();
            else
                tempGRAPH_XIC->curve->hide();
        }
    }
    mutex_XIC.unlock();
}

bool sChartWidget::drawXIC(std::vector<double>& pX, uint32_t sizeTIC, int timeout)
{
    if(sizeTIC>0)
    if(tryLockXIC(timeout)){
        QMutableMapIterator< uint32_t, QMap<QString, _GRAPH_XIC*> > tempIter(mXIC);
        while (tempIter.hasNext()) {
            QMutableMapIterator<QString, sChartWidget::_GRAPH_XIC*> tempIter1(tempIter.next().value());
            while (tempIter1.hasNext()) {
                sChartWidget::_GRAPH_XIC* pGRAPH_XIC= tempIter1.next().value();
                if(pGRAPH_XIC->curve){
                    if(pGRAPH_XIC->yListXIC.size()== sizeTIC)
                        pGRAPH_XIC->curve->setSamples(pX.data(), pGRAPH_XIC->yListXIC.data(), sizeTIC);
                }
            }
        }
        unLockXIC();
        return true;
    }
    return false;
}

bool sChartWidget::drawXIC(std::vector<double>& pX)
{
    //mutex_MyCurve.lock();
    if(myCurve.isEmpty() || pX.size() == 0)
    {
        return false;
    }

    foreach (auto XIC, myCurve) {
        if(XIC.second){
            XIC.second->setSamples(pX.data(),XIC.first->yListXIC.data(),pX.size());
        }else{
            return false;
        }
    }
    //mutex_MyCurve.unlock();
    return true;
}

void sChartWidget::clearBuffXIC()
{
    lockXIC();
    QMutableMapIterator< uint32_t, QMap<QString, _GRAPH_XIC*> > tempIter(mXIC);
    while (tempIter.hasNext()) {
        QMutableMapIterator<QString, sChartWidget::_GRAPH_XIC*> tempIter1(tempIter.next().value());
        while (tempIter1.hasNext()) {
            sChartWidget::_GRAPH_XIC* pGRAPH_XIC= tempIter1.next().value();
            pGRAPH_XIC->yListXIC.clear();

        }
    }
    unLockXIC();
}

void sChartWidget::onMassWidgetAddLine(double mass, QColor color)
{
    addLine(mass,color);
}

void sChartWidget::onItemRemove(double mass)
{
    clearLine(mass);
}

void sChartWidget::onHideCurve(sChartWidget::XICInform *XICinform,bool state)
{
    foreach (auto XIC, myCurve) {
        if(XIC.first == XICinform)
        {
            if(state == false)
                XIC.second->hide();
            else
                XIC.second->show();
        }
    }
}

void sChartWidget::ondeleteCurve(sChartWidget::XICInform *XICinform)
{
    foreach (auto XIC, myCurve) {
        if(XIC.first == XICinform)
        {
            XIC.second->hide();
            delete XIC.second;
            myCurve.removeOne(XIC);
        }
    }
}

void sChartWidget::clearMycurve()
{
    foreach (auto XIC, myCurve) {
        delete XIC.first;
        delete XIC.second;
    }
    myCurve.clear();
}
