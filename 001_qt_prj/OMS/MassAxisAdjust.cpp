#include "MassAxisAdjust.h"
#include "ui_MassAxisAdjust.h"
#include <QDebug>

MassAxisAdjust::MassAxisAdjust(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MassAxisAdjust)
{
    ui->setupUi(this);
    initFactor();
}

MassAxisAdjust::~MassAxisAdjust()
{
    delete ui;
}

void MassAxisAdjust::initFactor()
{
    QString path = QCoreApplication::applicationDirPath()+CONFIGPATH;
    //qDebug() << path;
    QSettings configIniRead(path, QSettings::IniFormat);
    massAxis.factor[0] = configIniRead.value("/MassAxis/Factor1", 0.0).toDouble();
    massAxis.factor[1] = configIniRead.value("/MassAxis/Factor2", 1.0).toDouble();
    massAxis.factor[2] = configIniRead.value("/MassAxis/Factor3", 0.0).toDouble();
    qDebug() << "a: "<< massAxis.factor[0] <<"b: "<< massAxis.factor[1] <<"c:"<< massAxis.factor[2];
}

void MassAxisAdjust::autoAdjust()
{
    float x[5],y[5];
    int i = 0;
    if(!ui->source1->text().toDouble())
        x[0] = ui->source1->text().toDouble();
    else
        x[0] = 0;
    if(ui->source2->text().toDouble())
        x[1] = ui->source2->text().toDouble();
    else
        x[1] = 0;
    if(ui->source3->text().toDouble())
        x[2] = ui->source3->text().toDouble();
    else
        x[2] = 0;
    if(ui->source4->text().toDouble())
        x[3] = ui->source4->text().toDouble();
    else
        x[3] = 0;
    if(ui->source5->text().toDouble())
        x[4] = ui->source5->text().toDouble();
    else
        x[4] = 0;

    if(ui->target1->text().toDouble())
        y[0] = ui->target1->text().toDouble();
    else
        y[0] = 0;
    if(ui->target2->text().toDouble())
        y[1] = ui->target2->text().toDouble();
    else
        y[1] = 0;
    if(ui->target3->text().toDouble())
        y[2] = ui->target3->text().toDouble();
    else
        y[2] = 0;
    if(ui->target4->text().toDouble())
        y[3] = ui->target4->text().toDouble();
    else
        y[3] = 0;
    if(ui->target5->text().toDouble())
        y[4] = ui->target5->text().toDouble();
    else
        y[4] = 0;

    for(i = 0;i<5;i++){
        qDebug() << x[i];
        qDebug() << y[i];
    }
    double a,b,c,m1,m2,m3,z1,z2,z3;
    a=b=c=0;
    double sumx=0,sumx2=0,sumx3=0,sumx4=0,sumy=0,sumxy=0,sumx2y=0;
    for(int i=0;i<5;i++){sumx+=x[i];sumy+=y[i];
        sumx2+=pow (x[i],2);
        sumxy+=x[i]*y[i];
        sumx3+=pow(x[i],3);
        sumx2y+=pow(x[i],2)*y[i];
        sumx4+=pow(x[i],4);
    }do{
        m1=a;
        a=(sumx2y-sumx3*b-sumx2*c)/sumx4;
        z1=(a-m1)*(a-m1);
        m2=b;
        b=(sumxy-sumx*c-sumx3*a)/sumx2;
        z2=(b-m2)*(b-m2);
        m3=c;
        c=(sumy-sumx2*a-sumx*b)/42; z3=(c-m3)*(c-m3);
    }
    while((z1>Number)||(z2>Number)||(z3>Number));
    massAxis.factor[0] = a;
    massAxis.factor[1] = b;
    massAxis.factor[2] = c;

    printf("a=%9.6f,\nb=%9.6f,\nc=%9.6f\n",a,b,c);
    qDebug("拟合方程为   y=%9.6fx*x+%9.6fx+%9.6f",a,b,c);
    QString path = QCoreApplication::applicationDirPath()+CONFIGPATH;

    QSettings configIniWrite(path, QSettings::IniFormat);
    configIniWrite.setValue("/MassAxis/Factor1",QString::number(a));
    configIniWrite.setValue("/MassAxis/Factor2",QString::number(b));
    configIniWrite.setValue("/MassAxis/Factor3",QString::number(c));
}

bool MassAxisAdjust::adjustProcess(std::vector<double> &dataSrc,std::vector<double> &dataDest)
{
    adjustValueX.resize(dataSrc.size());
    for(int i = 0;i<dataSrc.size();i++){
        adjustValueX.at(i) = massAxis.factor[0]*dataSrc.at(i)*dataSrc.at(i) + massAxis.factor[1]*dataSrc.at(i) + massAxis.factor[2];
    }
    memcpy(dataDest.data(),adjustValueX.data(),dataSrc.size()*sizeof(double));
    return 1;

}

void MassAxisAdjust::on_pushButton_clicked()
{
    autoAdjust();
    this->close();
}

void MassAxisAdjust::on_pushButton_2_clicked()
{
    this->close();
}
