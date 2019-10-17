#ifndef DOUBLESLIDER_H
#define DOUBLESLIDER_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class DoubleSlider : public QWidget
{
    Q_OBJECT
public:
    DoubleSlider(int handleNum,int min,int max,int step,QWidget* parent = 0);
    void setRange(int min, int max);
    void setSingleStep(int step);

    enum State{ MinHandle,MaxHandle,None};

    int minValue() const;
    int maxValue() const;

    int minRange() const;
    int maxRange() const;

    double startMass() const;
    double endMass() const;

public slots:
    void setLabel(const QString& label);
    void setMaxValue(int val);
    void setMinValue(int val);
    void setReadOnly(bool state) { readOnly = state; }

signals:
    void minValueChanged(int);
    void maxValueChanged(int);

private:
    int m_min;
    int m_max;
    int m_singleStep;

    int m_minValue;
    int m_maxValue;

    QRect minHandleRegion;
    QRect maxHandleRegion;
    QRect grooveRect;
    QRect grooveMinRect;
    QRect grooveMaxRect;

    State m_state;

    QString m_label;

    int handleNum;
    bool readOnly;


protected:
    void paintEvent(QPaintEvent* event);
    void paintColoredRect(QRect rect, QColor color, QPainter* painter);
    void paintValueLabel(QPainter* painter);

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

    void keyPressEvent(QKeyEvent *event);
    void leaveEvent(QEvent* event);



};

#endif // DOUBLESLIDER_H
