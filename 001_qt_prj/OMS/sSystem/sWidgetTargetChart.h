#ifndef SWIDGETTARGETCHART_H
#define SWIDGETTARGETCHART_H

#include <QWidget>
#include <sChartWidget.h>

namespace Ui {
class sWidgetTargetChart;
}

class sWidgetTargetChart : public QWidget
{
    Q_OBJECT

public:
    explicit sWidgetTargetChart(QWidget *parent = 0);
    ~sWidgetTargetChart();
    sChartWidget* getChart(){
        return mChartWidget;
    }
    QString getTargetMass();
private:
    Ui::sWidgetTargetChart *ui;
    sChartWidget* mChartWidget;
};

#endif // SWIDGETTARGETCHART_H
