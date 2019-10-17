#include "sWidgetCalibration.h"
#include "ui_sWidgetCalibration.h"
#include <Maths/PolyFit.h>
#include <Maths/zxMath.h>
#include <QDebug>
//#include <gsl/include/gsl/gsl_poly.h>

sWidgetCalibration::sWidgetCalibration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sWidgetCalibration)
{
    ui->setupUi(this);
    uiExpect[0]=ui->UI_LE_EXPECT0;
    uiExpect[1]=ui->UI_LE_EXPECT1;
    uiExpect[2]=ui->UI_LE_EXPECT2;
    uiExpect[3]=ui->UI_LE_EXPECT3;
    uiExpect[4]=ui->UI_LE_EXPECT4;
    uiExpect[5]=ui->UI_LE_EXPECT5;
    uiCurrent[0]=ui->UI_LE_CURRENT0;
    uiCurrent[1]=ui->UI_LE_CURRENT1;
    uiCurrent[2]=ui->UI_LE_CURRENT2;
    uiCurrent[3]=ui->UI_LE_CURRENT3;
    uiCurrent[4]=ui->UI_LE_CURRENT4;
    uiCurrent[5]=ui->UI_LE_CURRENT5;
}

sWidgetCalibration::~sWidgetCalibration()
{
    delete ui;
}

void sWidgetCalibration::on_UI_PB_CALIBRAT_clicked()
{
    _CONGIG_OMS::_PARAM_FIT tempPARAM_FIT;
    QString MassExtension;
    getParam(tempPARAM_FIT, MassExtension, false);
    QString tempStr1, tempStr2;
    std::vector<double> expect;
    std::vector<double> current;
    for(int i=0; i<6; i++){
        tempStr1= uiExpect[i]->text();
        tempStr2= uiCurrent[i]->text();
        if((!tempStr1.isEmpty())&& (!tempStr2.isEmpty())){
            expect.push_back(tempStr1.toDouble());
            current.push_back(tempStr2.toDouble());
        }
    }
    int nPloy= ui->UI_LE_PLOY_D->text().toInt();
    if((current.size()>nPloy)&&current.size()==expect.size()){
        double out_chisq=0;
        zx::Math::fit::polyfit(current.data(), expect.data(), current.size(), nPloy,
                               mPARAM_FIT.coefF,out_chisq);
        zx::Math::fit::polyfit(expect.data(), current.data(), current.size(), nPloy,
                               mPARAM_FIT.coefB,out_chisq);
        //mPARAM_FIT.coefF[0]-= expect[2];
        //std::vector<double> roots;
        //zx::Math::roots::polyRoots(mPARAM_FIT.coefF.data(),mPARAM_FIT.coefF.size(),roots);
        //Fit::Polynomial(current, expect, mPARAM_FIT.coefF, current.size()-1);
        //Fit::Polynomial(expect, current, mPARAM_FIT.coefB, current.size()-1);
        emit Calibrat();
    }
}

void sWidgetCalibration::on_UI_CB_ENABLE_clicked()
{
//    _CONGIG_OMS::_PARAM_FIT tempPARAM_FIT;
//    getParam(tempPARAM_FIT, false);
    emit Calibrat();
}

void sWidgetCalibration::updateParam(_CONGIG_OMS::_PARAM_FIT &pPARAM_FIT, QString MassExtension)
{
    ui->UI_LE_MassExtension->setText(MassExtension);
    if((pPARAM_FIT.current.size()<6)||(pPARAM_FIT.expect.size()<6))
        return;
    if(pPARAM_FIT.enable)
        ui->UI_CB_ENABLE->setChecked(true);
    else
        ui->UI_CB_ENABLE->setChecked(false);
    for(int i=0; i< 6; i++){
        uiExpect[i]->setText(pPARAM_FIT.expect[i]);
        uiCurrent[i]->setText(pPARAM_FIT.current[i]);
    }
    int tempSize= pPARAM_FIT.coefF.size();
    mPARAM_FIT.coefF.resize(tempSize);
    for(int i=0; i<tempSize; i++)
        mPARAM_FIT.coefF[i]= pPARAM_FIT.coefF[i];
    tempSize= pPARAM_FIT.coefB.size();
        mPARAM_FIT.coefB.resize(tempSize);
        for(int i=0; i<tempSize; i++)
            mPARAM_FIT.coefB[i]= pPARAM_FIT.coefB[i];
}

void sWidgetCalibration::getParam(_CONGIG_OMS::_PARAM_FIT &pPARAM_FIT, QString& MassExtension, bool update)
{
    MassExtension= ui->UI_LE_MassExtension->text();
    if(ui->UI_CB_ENABLE->isChecked())
        pPARAM_FIT.enable= 1;
    else
        pPARAM_FIT.enable= 0;
    pPARAM_FIT.expect.resize(6);
    pPARAM_FIT.current.resize(6);
    for(int i=0; i< 6; i++){
        pPARAM_FIT.expect[i]= uiExpect[i]->text();
        pPARAM_FIT.current[i]= uiCurrent[i]->text();
    }
    if(update){
        int tempSize= mPARAM_FIT.coefF.size();
        pPARAM_FIT.coefF.resize(tempSize);
        for(int i=0; i<tempSize; i++)
            pPARAM_FIT.coefF[i]= mPARAM_FIT.coefF[i];
        tempSize= mPARAM_FIT.coefB.size();
        pPARAM_FIT.coefB.resize(tempSize);
        for(int i=0; i<tempSize; i++)
            pPARAM_FIT.coefB[i]= mPARAM_FIT.coefB[i];
    }
}

//void sWidgetCalibration::getAdjustFactor(_Adjust_Factor& pAdjust_Factor)
//{
//    pAdjust_Factor.d_Mass_Forward_Extension= ui->UI_LE_MassExtension->text().toDouble();
//}

