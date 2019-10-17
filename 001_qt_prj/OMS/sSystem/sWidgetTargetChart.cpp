#include "sWidgetTargetChart.h"
#include "ui_sWidgetTargetChart.h"

sWidgetTargetChart::sWidgetTargetChart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sWidgetTargetChart)
{
    ui->setupUi(this);
    mChartWidget = new sChartWidget(sChartWidget::_NORMAL_CHART);
    ui->UI_LAYOUT_CHART->addWidget(mChartWidget);
}

sWidgetTargetChart::~sWidgetTargetChart()
{
    delete ui;
}

QString sWidgetTargetChart::getTargetMass(){
    return ui->UI_LE_MASS->text();
}
