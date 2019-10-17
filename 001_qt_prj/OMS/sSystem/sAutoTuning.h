#ifndef SAUTOTUNING_H
#define SAUTOTUNING_H

#include <QWidget>
#include <cParamCCS.h>
#include <sChartWidget.h>
#include <msMethed/cMethod.h>
#include <tool/sthread.h>
#include "cDataProcess.h"
#include "cConfigOMS.h"

namespace Ui {
class sAutoTuning;
}

class sAutoTuning : public QWidget
{
    Q_OBJECT

public:
    explicit sAutoTuning(ParamCCS::_DAQ_CONFIG* pDAQ_CONFIG, QWidget *parent = 0);
    ~sAutoTuning();
    _CONGIG_OMS::_CONGIG_AUTO_TUNING* getConfig(){
        return &mCONGIG_AUTO_TUNING;
    }
private:
    Ui::sAutoTuning *ui;
    QWidget* mParent=nullptr;
    _CONGIG_OMS::_CONGIG_AUTO_TUNING mCONGIG_AUTO_TUNING;
    ParamCCS::_DAQ_CONFIG* mDAQ_CONFIG= nullptr;
signals:
    void ShowSystem();
};

#endif // SAUTOTUNING_H
