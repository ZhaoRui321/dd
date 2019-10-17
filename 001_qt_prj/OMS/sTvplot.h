#pragma once
#include <qwt_plot.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_panner.h>
#include <qwt_panner.h>
#include <QGestureEvent>
#include <QMutex>

class Histogram;
class TVPlot: public QwtPlot
{
    Q_OBJECT

public:
    enum MPlotStyle
    {
        /*!
           Don't draw a curve. Note: This doesn't affect the symbols.
        */
        NoCurve = -1,

        /*!
           Connect the points with straight lines. The lines might
           be interpolated depending on the 'Fitted' attribute. Curve
           fitting can be configured using setCurveFitter().
        */
        Lines,

        /*!
           Draw vertical or horizontal sticks ( depending on the
           orientation() ) from a baseline which is defined by setBaseline().
        */
        Sticks,

        /*!
           Connect the points with a step function. The step function
           is drawn from the left to the right or vice versa,
           depending on the QwtPlotCurve::Inverted attribute.
        */
        Steps,

        /*!
           Draw dots at the locations of the data points. Note:
           This is different from a dotted line (see setPen()), and faster
           as a curve in QwtPlotCurve::NoStyle style and a symbol
           painting a point.
        */
        Dots,

        /*!
           Styles >= QwtPlotCurve::UserCurve are reserved for derived
           classes of QwtPlotCurve that overload drawCurve() with
           additional application specific curve types.
        */
        Histograms,
        UserCurve = 100
    };
    TVPlot( QWidget * = NULL , MPlotStyle type=Lines);
    ~TVPlot();
    void setStyle(MPlotStyle type){
        if(pQwtPlotCurve!=nullptr){
            pQwtPlotCurve->setStyle((QwtPlotCurve::CurveStyle)type);
            if(type == Sticks)
                pQwtPlotCurve->setBaseline(0);
            mStyle=(int)type;
        }
    }
    void SetMarker(std::vector<double>const& ValuesX,std::vector<double>& ValuesY,QVector<QString>& Marker);
    void SetMarker(std::vector<double>const& ValuesX,std::vector<double>& ValuesY,std::vector<double>& Marker);
    //replot();
public Q_SLOTS:
    void setMode( int );
    void exportPlot();
    void populate(std::vector<double>const& ValuesX,std::vector<double>& ValuesY);
    void populate( const double *xData, const double *yData, int size ){
        //min = axisScaleDiv(QwtPlot::xBottom).lowerBound();
        //max = axisScaleDiv(QwtPlot::xBottom).upperBound();
        pQwtPlotCurve->setSamples(xData, yData, size);
        replot();
    }
    void setSamples( const double *xData, const double *yData, int size ){
        //min = axisScaleDiv(QwtPlot::xBottom).lowerBound();
        //max = axisScaleDiv(QwtPlot::xBottom).upperBound();
        pQwtPlotCurve->setSamples(xData, yData, size);
    }
    void setZoomBase(bool setBase);
    void setXRange(double xmin, double xmax){
        min = xmin;
        max = xmax;
    }

private:
    int mStyle;
    QList<QwtPlotMarker*> pMarker;
    QwtPlotCurve* pQwtPlotCurve=nullptr;
    Histogram* phistogram=nullptr;
    QwtPlotZoomer* m_zoomer=nullptr;
    QwtPlotPanner* m_panner = nullptr;
    //std::vector<double> tmpValuesY;
    //std::vector<double> tmpValuesX;
    //std::vector<int> marker;

    qreal lastScale;
    qreal totalScale = 1;
    double min = 0;
    double max = 0;

    bool gestureEvent(QGestureEvent *event);
    void panTriggered(QPanGesture* pan);
    void pinchTriggered(QPinchGesture*);
    void scaleFactorChange(double zb, bool isX, bool isY);

protected:
    bool event(QEvent *e);

};

