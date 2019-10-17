#include "sAutoTuning.h"
#include "ui_sAutoTuning.h"

sAutoTuning::sAutoTuning(ParamCCS::_DAQ_CONFIG* pDAQ_CONFIG, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sAutoTuning),
    mParent(parent),
    mDAQ_CONFIG(pDAQ_CONFIG)
{
    ui->setupUi(this);
}

sAutoTuning::~sAutoTuning()
{
    delete ui;
}

//void sAutoTuning::on_UI_PB_TUNING_RETURN_clicked()
//{
//    emit ShowSystem();
//}
