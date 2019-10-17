#include "sTvplot.h"
#include <qwt_plot_layout.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_renderer.h>
#include <qwt_legend.h>
#include <qwt_legend_label.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_histogram.h>
#include <qwt_column_symbol.h>
#include <qwt_series_data.h>
#include <qpen.h>
#include <stdlib.h>
#include <cPublicCCS.h>

class Histogram: public QwtPlotHistogram
{
public:
    Histogram( const QString &, const QColor & );
    void setColor( const QColor & );
    void setValues( uint numValues, const double * );
    void setValues( std::vector<double>const& ValuesX,std::vector<double>& ValuesY );
};

Histogram::Histogram( const QString &title, const QColor &symbolColor ):
    QwtPlotHistogram( title )
{
    setStyle( static_cast<QwtPlotHistogram::HistogramStyle>(QwtPlotHistogram::Outline) );
    setColor( symbolColor );
}

void Histogram::setColor( const QColor &color )
{
    QColor c = color;
    //c.setAlpha( 180 );//透明
    setBrush( QBrush( c ) );
}

void Histogram::setValues( uint numValues, const double *values )
{
    QVector<QwtIntervalSample> samples( numValues );
    for ( uint i = 0; i < numValues; i++ ){
        QwtInterval interval( double( i ),i+0.000001  );// i+ 5.0
        interval.setBorderFlags( QwtInterval::ExcludeMaximum);
        samples[i] = QwtIntervalSample(values[i], interval  );
    }
    setSamples(new QwtIntervalSeriesData( samples ));
}

void Histogram::setValues( std::vector<double>const& ValuesX,std::vector<double>& ValuesY )
{
    uint numValues=ValuesX.size();
    QVector<QwtIntervalSample> samples( numValues );
    for ( uint i = 0; i < numValues; i++ ){
        QwtInterval interval( ValuesX[i],ValuesX[i]+0.000001  );// i+ 5.0
        interval.setBorderFlags( QwtInterval::ExcludeMaximum);
        samples[i] = QwtIntervalSample(ValuesY[i], interval  );
    }
    setSamples(new QwtIntervalSeriesData( samples ));
}

TVPlot::TVPlot( QWidget *parent, MPlotStyle type):
    QwtPlot( parent ),
    //pMarker(nullptr),
    phistogram(nullptr)
{
    plotLayout()->setAlignCanvasToScales( true );
    QwtPlotGrid *grid = new QwtPlotGrid;
    grid->enableX( false );
    grid->enableY( true );
    grid->enableXMin( false );
    grid->enableYMin( false );
    grid->setMajorPen( Qt::black, 0, Qt::DotLine );
    grid->attach( this );
    if(type==Histograms){
        phistogram=new Histogram( "Histogram", Qt::red );
        phistogram->attach( this );
    }
    else{
        pQwtPlotCurve = new QwtPlotCurve("TIC");
        pQwtPlotCurve->attach(this);
        pQwtPlotCurve->setStyle((QwtPlotCurve::CurveStyle)type);
    }
    mStyle=type;
//    m_zoomer = new QwtPlotZoomer( this->canvas() );
//    m_zoomer->setTrackerMode( QwtPlotPicker::AlwaysOn );
//    m_zoomer->setRubberBandPen( QColor( Qt::red ) );
//    m_zoomer->setTrackerPen( QColor( Qt::red ) );

    m_panner = new QwtPlotPanner(this->canvas());
    m_panner->setOrientations(Qt::Horizontal);

    //grabGesture(Qt::PanGesture);
    grabGesture(Qt::PinchGesture);

    replot(); // creating the legend items
    setAutoReplot( true );
}

TVPlot::~TVPlot()
{
    qDeleteAll(pMarker);
    pMarker.clear();
    if(pQwtPlotCurve!=nullptr)
        delete pQwtPlotCurve;
    if(phistogram!=nullptr)
        delete phistogram;
    if(m_zoomer!=nullptr)
        delete m_zoomer;
}

void TVPlot::populate(std::vector<double>const& ValuesX,std::vector<double>& ValuesY)
{
//    int njuneValues=ValuesX.size();

//    if(njuneValues<1){
//        return;
//    }

    if(mStyle==Lines&&pQwtPlotCurve!=nullptr){
        pQwtPlotCurve->setSamples(ValuesX.data(), ValuesY.data(),ValuesX.size());
    }else if(mStyle==Sticks||mStyle==Histograms){
        if(mStyle==Sticks)
            pQwtPlotCurve->setSamples(ValuesX.data(), ValuesY.data(),ValuesX.size());
        else
            phistogram->setValues(ValuesX, ValuesY);
#if 0
        tmpValuesY.resize(ValuesY.size());
        tmpValuesX.resize(ValuesX.size());
        memcpy(&tmpValuesY[0], &ValuesY[0], ValuesY.size() * sizeof(double));
        memcpy(&tmpValuesX[0], &ValuesX[0], ValuesX.size() * sizeof(double));
        marker.resize(ValuesY.size());
        for(int i=0;i<njuneValues;i++)
            marker[i]=i;
        int nMarkers=20;
        if(njuneValues>nMarkers){
            sortGICAP::widthSort(&(tmpValuesY[0]),&(marker[0]),njuneValues,nMarkers);
            for(int i=0;i<nMarkers;i++)
                tmpValuesX[i]=ValuesX[marker[i]];
        }else
            nMarkers= njuneValues;

        if(pMarker.size()!=nMarkers){
            while(pMarker.size()< nMarkers){
                pMarker.append(new QwtPlotMarker());
            }
            while(pMarker.size()> nMarkers){
                delete pMarker.last();
                pMarker.removeLast();
            }
        }
        for(int i=0;i<nMarkers;i++){
            pMarker[i]->setLabel(QString::number(tmpValuesX[i]));
            pMarker[i]->setLabelAlignment(Qt::AlignTop);//Qt::AlignLeft |
            pMarker[i]->setLineStyle(QwtPlotMarker::NoLine);
            pMarker[i]->setXValue(tmpValuesX[i]);
            pMarker[i]->setYValue(tmpValuesY[i]);
            pMarker[i]->attach(this);
        }
#endif
    }
    replot();
}

void TVPlot::SetMarker(std::vector<double>const& ValuesX,std::vector<double>& ValuesY,QVector<QString>& Marker)
{
    if(ValuesX.size()!=ValuesY.size()||
            ValuesY.size()!=Marker.size()||
            ValuesX.size()!=Marker.size())
        return;
    int nMarkers=Marker.size();
    if(pMarker.size()!=nMarkers){
        while(pMarker.size()< nMarkers){
            pMarker.append(new QwtPlotMarker());
        }
        while(pMarker.size()> nMarkers){
            delete pMarker.last();
            pMarker.removeLast();
        }
    }
    for(int i=0;i<nMarkers;i++){
        pMarker[i]->setLabel(Marker[i]);
        pMarker[i]->setLabelAlignment(Qt::AlignTop);//Qt::AlignLeft |
        pMarker[i]->setLineStyle(QwtPlotMarker::NoLine);
        pMarker[i]->setXValue(ValuesX[i]);
        pMarker[i]->setYValue(ValuesY[i]);
        pMarker[i]->attach(this);
    }
    replot();
}

void TVPlot::SetMarker(std::vector<double>const& ValuesX,std::vector<double>& ValuesY,std::vector<double>& Marker)
{
    if(ValuesX.size()!=ValuesY.size()||
            ValuesY.size()!=Marker.size()||
            ValuesX.size()!=Marker.size())
        return;
    int nMarkers=Marker.size();
    if(pMarker.size()!=nMarkers){
        while(pMarker.size()< nMarkers){
            pMarker.append(new QwtPlotMarker());
        }
        while(pMarker.size()> nMarkers){
            delete pMarker.last();
            pMarker.removeLast();
        }
    }
    for(int i=0;i<nMarkers;i++){
        if(Marker[i]<0.00001)
            continue;
        pMarker[i]->setLabel(QString::number(Marker[i]));
        pMarker[i]->setLabelAlignment(Qt::AlignTop);//Qt::AlignLeft |
        pMarker[i]->setLineStyle(QwtPlotMarker::NoLine);
        pMarker[i]->setXValue(ValuesX[i]);
        pMarker[i]->setYValue(ValuesY[i]);
        pMarker[i]->attach(this);
    }
    replot();
}

void TVPlot::exportPlot()
{
    QwtPlotRenderer renderer;
    renderer.exportTo( this, "tvplot.pdf" );
}

void TVPlot::setMode( int mode )
{
    QwtPlotItemList items = itemList( QwtPlotItem::Rtti_PlotHistogram );
    for ( int i = 0; i < items.size(); i++ ){
        QwtPlotHistogram *phistogram = static_cast<QwtPlotHistogram *>( items[i] );
        if ( mode < 3 ){
            phistogram->setStyle( static_cast<QwtPlotHistogram::HistogramStyle>( mode ) );
            phistogram->setSymbol( NULL );
        }else{
            phistogram->setStyle( QwtPlotHistogram::Columns );
            QwtColumnSymbol *symbol = new QwtColumnSymbol( QwtColumnSymbol::Box );
            symbol->setFrameStyle( QwtColumnSymbol::Raised );
            symbol->setLineWidth( 2 );
            symbol->setPalette( QPalette( phistogram->brush().color() ) );
            phistogram->setSymbol( symbol );
        }
    }
}

void TVPlot::setZoomBase(bool setBase)
{
    m_zoomer->setZoomBase(setBase);
}

bool TVPlot::event(QEvent *event)
{
    if (event->type() == QEvent::Gesture && min!= max){
        return gestureEvent(static_cast<QGestureEvent*>(event));
    }
    return QwtPlot::event(event);
}

bool TVPlot::gestureEvent(QGestureEvent *event)
{
    if(QGesture *pan = event->gesture(Qt::PanGesture))
        panTriggered(static_cast<QPanGesture *>(pan));
    if (QGesture *pinch = event->gesture(Qt::PinchGesture))
        pinchTriggered(static_cast<QPinchGesture *>(pinch));
    return true;
}

void TVPlot::panTriggered(QPanGesture *pan)
{

    QPointF point = pan->lastOffset();
    const QwtScaleDiv scaleDiv = this->axisScaleDiv(QwtPlot::xBottom);
    double begin = scaleDiv.lowerBound();
    double end = scaleDiv.lowerBound() + scaleDiv.range();
    double dx = scaleDiv.range()*point.x()/this->width()/10;
    begin = begin-dx;
    end = end-dx;
    if(begin <= min){
        this->setAxisScale( QwtPlot::xBottom, min, min+scaleDiv.range() );
        return;
    }
    if(end >= max){
        this->setAxisScale( QwtPlot::xBottom, max-scaleDiv.range(), max);
        return;
    }

    this->setAxisScale( QwtPlot::xBottom, begin-dx, end-dx );
}

void TVPlot::pinchTriggered(QPinchGesture *gesture)
{
    //m_zoomer->setEnabled(false);
    m_panner->setEnabled(false);

    QPinchGesture::ChangeFlags changeFlags = gesture->changeFlags();

    if (changeFlags & QPinchGesture::ScaleFactorChanged) {
        //如果是两指放缩比例改变，则放缩
        lastScale = gesture->lastScaleFactor();

        QPoint centerPoint = this->mapFromGlobal(gesture->lastCenterPoint().toPoint());
        double dx = centerPoint.x() - (this->width()-centerPoint.x())? centerPoint.x() : (this->width()-centerPoint.x());
        double dy = centerPoint.y() - (this->height()-centerPoint.y())? centerPoint.y() : (this->height()-centerPoint.y());
        if(dx < dy){
            double zb = 1- (double)centerPoint.y()/(double)this->height();
            scaleFactorChange(zb,false,true);
        }else{
            double zb = (double)centerPoint.x()/(double)this->width();
            scaleFactorChange(zb,true,false);
        }
    }

    if (gesture->state() == Qt::GestureFinished) {
        totalScale *= lastScale;
    }
    replot();
    update();

    m_panner->setEnabled(true);
    //m_zoomer->setEnabled(true);
}

void TVPlot::scaleFactorChange(double zb, bool isX, bool isY)
{
    bool doReplot = false;

    const bool autoReplot = this->autoReplot();
    setAutoReplot( false );

    if(isX){
        const QwtScaleDiv scaleDiv = this->axisScaleDiv(QwtPlot::xBottom);
        double begin = scaleDiv.lowerBound();
        double end = scaleDiv.lowerBound() + scaleDiv.range();
        const double center = scaleDiv.lowerBound() + scaleDiv.range()*zb;

        double d1 = (center-begin)/lastScale;
        double d2 = (end-center)/lastScale;

        begin = (center-d1)>min ? (center-d1):min;
        end = (center+d2)<max ? (center+d2):max;

        this->setAxisScale( QwtPlot::xBottom, begin, end );
        doReplot = true;
    }
    if(isY){
        const QwtScaleDiv scaleDiv = this->axisScaleDiv(QwtPlot::yLeft);
        double begin = scaleDiv.lowerBound();
        double end = scaleDiv.lowerBound() + scaleDiv.range();
        const double center = scaleDiv.lowerBound() + scaleDiv.range()*zb;

        double d1 = (center-begin)/lastScale;
        double d2 = (end-center)/lastScale;
        this->setAxisScale( QwtPlot::yLeft, center-d1, center+d2 );
        doReplot = true;
    }

    setAutoReplot(autoReplot);
    if(doReplot)
        replot();
}

