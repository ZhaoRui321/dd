#include "DoubleSlider.h"

static double n_startMass = 0;
static double n_endMass = 0;

DoubleSlider::DoubleSlider(int handleNum, int min, int max, int step, QWidget* parent)
    : QWidget(parent)
    , m_min(min)
    , m_max(max)
    , m_singleStep(step)
    , m_minValue(min)
    , m_maxValue(max)
    , m_state(None)
    , handleNum(handleNum)
    , readOnly(false)
{
    setFixedHeight(100);
    setFocusPolicy(Qt::StrongFocus);
    n_startMass = m_minValue;
    n_endMass = m_maxValue;
}

void DoubleSlider::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    paintValueLabel(&painter);
}

void DoubleSlider::paintColoredRect(QRect rect, QColor color ,QPainter* painter)
{
    painter->fillRect(rect,QBrush(color));
}

void DoubleSlider::paintValueLabel(QPainter* painter)
{
    painter->setBrush(Qt::NoBrush);
    painter->setPen(Qt::black);
    painter->setFont(QFont("Arial",24));

    QString minValueString = QString::number(m_minValue*m_singleStep);
    QString maxValueString = QString::number(m_maxValue*m_singleStep);
    n_startMass = minValueString.toDouble();
    n_endMass = maxValueString.toDouble();

    QFontMetrics metrics = painter->fontMetrics();
    int mintextWidth = metrics.width(minValueString);
    int maxtextWidth = metrics.width(maxValueString);
    int textHeight = metrics.height();

    //---- paint text
    painter->drawText(QRectF(2,4,mintextWidth,textHeight),minValueString);
    if(handleNum == 2)
    painter->drawText(QRectF(width() - maxtextWidth -2, 4, maxtextWidth,textHeight), maxValueString);


    //----- paint label
    painter->setFont(QFont("Arial",24));
    metrics = painter->fontMetrics();
    int labelWidth = metrics.width(m_label);
    int labelHeight = metrics.height();

    QRectF textRect = QRectF((width()/2 - labelWidth/2), 0,labelWidth,labelHeight);

    painter->drawText(textRect,m_label);


    int minPos = ( m_minValue - m_min ) * width() / (m_max - m_min);
    int maxPos = (m_maxValue - m_min ) * width() /  (m_max - m_min);

    if(minPos <= 20){
        minPos = 20;
    }else if(minPos >= width() - 40){
        minPos = width() - 40;
    }else{}
    if(handleNum == 2){
        if(maxPos <= 20){
            maxPos = 20;
        }else if(maxPos >= width() -40){
            maxPos = width() - 40;
        }else{}
    }else{
        if(maxPos <= 20){
            maxPos = 20;
        }else if(maxPos >= width()){
            maxPos = width();
        }else{}
    }


    //----- paint groove
    grooveRect = QRect(20,70,width(),20);
    paintColoredRect(grooveRect,Qt::white,painter);
    paintColoredRect(QRect(minPos + 4,70,maxPos - minPos,20),Qt::green,painter);
    grooveMinRect = QRect(4,70,minPos-4,20);
    grooveMaxRect = QRect(maxPos,70,width() - maxPos,20);


    //----- handle

    minHandleRegion = QRect(minPos ,60,40,60);
    if(handleNum == 2)
        maxHandleRegion = QRect(maxPos ,60,40,60);

    //-----paint Handle
    QColor minColor  = (m_state == MinHandle) ? Qt::lightGray : Qt::white;
    QColor maxColor  = (m_state == MaxHandle) ? Qt::lightGray : Qt::white;
    paintColoredRect(minHandleRegion,minColor,painter);
    if(handleNum == 2){
        paintColoredRect(maxHandleRegion,maxColor,painter);
    }

}

inline int getValidValue(int val, int min, int max)
{
    int tmp = std::max(val, min);
    return std::min(tmp, max);
}

double DoubleSlider::startMass() const
{
    return n_startMass;
}

double DoubleSlider::endMass() const
{
    return n_endMass;
}

void DoubleSlider::setRange(int min, int max)
{
    m_min = min;
    m_max = max;

    if(minValue() < m_min)
        setMinValue(m_min);

    if(maxValue() > m_max){
        setMaxValue(m_max);
    }
}

void DoubleSlider::setSingleStep(int step)
{
    m_singleStep = step;
}

int DoubleSlider::minValue() const
{
    return m_minValue;
}
void DoubleSlider::setMinValue(int val)
{
    if(fabs( m_minValue - val ) > 0.0001 ){
        m_minValue = val;
        emit minValueChanged(val);
        update();
    }
}

int DoubleSlider::maxValue() const
{
    return m_maxValue;
}
void DoubleSlider::setMaxValue(int val)
{
    if(handleNum == 2)
        if(fabs(m_maxValue - val) > 0.0001){
            m_maxValue = val;
            emit maxValueChanged(val);
            update();
        }
}

void DoubleSlider::setLabel(const QString& label)
{
   m_label = label;
   update();
}

void DoubleSlider::leaveEvent(QEvent* event)
{
    QWidget::leaveEvent(event);
    m_state = None;
    update();
}

int DoubleSlider::minRange() const
{
    return m_min;
}
int DoubleSlider::maxRange() const
{
    return m_max;
}


void DoubleSlider::mousePressEvent(QMouseEvent* event)
{
    if(minHandleRegion.contains(event->pos()) ){
        m_state = MinHandle;
    }else if(handleNum == 2){
        if(maxHandleRegion.contains(event->pos()))
            m_state = MaxHandle;
    }else{
        m_state = None;
    }

    if(fabs(minValue() - maxValue()) < 0.001){
        if(fabs(minValue() - m_min) < 0.001){
            m_state = MaxHandle;
        }else if(fabs(minValue() - m_max) < 0.001){
            m_state = MinHandle;
        }else{}
    }

    update();
}

void DoubleSlider::mouseMoveEvent(QMouseEvent* event)
{
    if(readOnly == true)
       update();
    else{
    if(event->buttons() & Qt::LeftButton){
        int move = event->x() * (m_max - m_min) * 1.0/ width() + m_min;

        switch(m_state){
            case MinHandle:{
                int val = getValidValue( move, m_min,maxValue());
                setMinValue(val);
                break;
            }

            case MaxHandle:{
                    int val = getValidValue(move, minValue(), m_max);
                    setMaxValue(val);
                    break;
            }
            case None:default: break;
        }
    }
    update();
    }
}


void DoubleSlider::keyPressEvent(QKeyEvent *event)
{
    QWidget::keyPressEvent(event);

    if(event->key() == Qt::Key_Left){
        if(m_state == MinHandle){
            int val = getValidValue(minValue()- m_singleStep, m_min ,maxValue());
            setMinValue(val);
        }else if(m_state == MaxHandle) {
            int val = getValidValue(maxValue()- m_singleStep, minValue() ,m_max);
            setMaxValue(val);
        }else{}
    }else if(event->key() == Qt::Key_Right){
        if(m_state == MinHandle){
            int val = getValidValue(minValue() + m_singleStep, m_min ,maxValue());
            setMinValue(val);
        }else if(m_state == MaxHandle) {
            int val = getValidValue(maxValue() + m_singleStep, minValue() ,m_max);
            setMaxValue(val);
        }else{}
    }

    update();

}
