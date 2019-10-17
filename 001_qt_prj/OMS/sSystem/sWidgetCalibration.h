#ifndef SWIDGETCALIBRATION_H
#define SWIDGETCALIBRATION_H

#include <QLineEdit>
#include <QWidget>
#include <cConfigOMS.h>

#include <msMethed/MsParams.h>

namespace Ui {
class sWidgetCalibration;
}

class sWidgetCalibration : public QWidget
{
    Q_OBJECT

public:
    _CONGIG_OMS::_PARAM_FIT mPARAM_FIT;
    explicit sWidgetCalibration(QWidget *parent = 0);
    ~sWidgetCalibration();
    void updateParam(_CONGIG_OMS::_PARAM_FIT &pPARAM_FIT, QString MassExtension);
    void getParam(_CONGIG_OMS::_PARAM_FIT &pPARAM_FIT, QString& MassExtension, bool update= true);
    //void getAdjustFactor(_Adjust_Factor& pAdjust_Factor);
private slots:
    void on_UI_PB_CALIBRAT_clicked();
    void on_UI_CB_ENABLE_clicked();

private:
    Ui::sWidgetCalibration *ui;
    QLineEdit* uiExpect[6];
    QLineEdit* uiCurrent[6];

signals:
    void Calibrat();
};

#endif // SWIDGETCALIBRATION_H
