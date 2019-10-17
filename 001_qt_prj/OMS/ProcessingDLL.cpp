#include "ProcessingDLL.h"
#include "ui_ProcessingDLL.h"
#include <QDebug>
#define SDBG(msg)


ProcessingDLL::ProcessingDLL(QWidget *parent):
    QWidget(parent),
    ui(new Ui::ProcessingDLL)
{
    ui->setupUi(this);
}

ProcessingDLL::~ProcessingDLL()
{
    delete ui;
}

void ProcessingDLL::updateMethod()
{
    if(mParamVersion!=mMethodParam.uVersion){
        int nsizeKey= mMapParam.Key.size();
        for(int countKey=0; countKey<nsizeKey; countKey++){
            switch(mMapParam.Key[countKey]){
            case FilterDataType::MovingAverage:{
                if(!mMapParam.Value.isEmpty())
                    delete (FilterMovingAverage*)mMapParam.Value[countKey];
                break;}
            case FilterDataType::SavGol:{
                if(!mMapParam.Value.isEmpty())
                    delete (FilterSavGol*)mMapParam.Value[countKey];
                break;}
            case FilterDataType::FrameAverage:{
                if(!mMapParam.Value.isEmpty())
                    delete (FilterFrameAverage*)mMapParam.Value[countKey];
                break;}
            case FilterDataType::GainOffset:{
                if(!mMapParam.Value.isEmpty())
                    delete (FilterGainOffset*)mMapParam.Value[countKey];
                break;}
            }
        }
        mMapParam.Key.clear();
        mMapParam.Value.clear();
        if(!(mMethodParam.ListParam.isEmpty())){
            foreach(auto strParam,mMethodParam.ListParam){
                QStringList listParam=strParam.split(',');
                if(listParam[0].compare("MovingAverage", Qt::CaseInsensitive) == 0){
                    if(listParam.size()<2)
                        continue;
                    if(listParam[1].isEmpty())
                        continue;
                    FilterMovingAverage* pFilterMovingAverage=new FilterMovingAverage;
                    pFilterMovingAverage->DataParam1=listParam[1].toDouble();
                    mMapParam.Key.append(MovingAverage);
                    mMapParam.Value.append(pFilterMovingAverage);
                }else if(listParam[0].compare("SavGolFilt", Qt::CaseInsensitive) == 0){
                    if(listParam.size()<3)
                        continue;
                    if(listParam[1].isEmpty()||listParam[2].isEmpty())
                        continue;
                    FilterSavGol* pFilterSavGol=new FilterSavGol;
                    pFilterSavGol->DataParam1=listParam[1].toDouble();
                    pFilterSavGol->DataParam2=listParam[2].toInt();
                    mMapParam.Key.append(SavGol);
                    mMapParam.Value.append(pFilterSavGol);
                }else if(listParam[0].compare("FrameAverage", Qt::CaseInsensitive) == 0){
                    if(listParam.size()<2)
                        continue;
                    if(listParam[1].isEmpty())
                        continue;
                    FilterFrameAverage* pFilterFrameAverage=new FilterFrameAverage;
                    pFilterFrameAverage->DataParam1=listParam[1].toDouble();
                    mMapParam.Key.append(FrameAverage);
                    mMapParam.Value.append(pFilterFrameAverage);
                }else if(listParam[0].compare("GainOffset", Qt::CaseInsensitive) == 0){
                    if(listParam.size()<3)
                        continue;
                    FilterGainOffset* pFilterGainOffset=new FilterGainOffset;
                    if(!listParam[1].isEmpty()){
                        pFilterGainOffset->DataParam1=listParam[1].toDouble();
                        pFilterGainOffset->bOffset=true;
                    }else
                        pFilterGainOffset->bOffset=false;
                    if(!listParam[2].isEmpty()){
                        pFilterGainOffset->DataParam2=listParam[2].toDouble();
                        pFilterGainOffset->bGain=true;
                    }else
                        pFilterGainOffset->bGain=false;
                    mMapParam.Key.append(GainOffset);
                    mMapParam.Value.append(pFilterGainOffset);
                }
            }
        }
        mParamVersion=mMethodParam.uVersion;
    }
}

bool ProcessingDLL::processData(std::vector<double>const& dataSrc, std::vector<double>& dataDest)
{
    int nSize = dataSrc.size();
    m_FilerData.bufy.resize(nSize);
    dataDest.resize(nSize);
    memcpy(m_FilerData.bufy.data(),dataSrc.data(),sizeof(double)*nSize);

    if(bFilterEnable){
        int nsizeKey=mMapParam.Key.size();
        for(int countKey=0;countKey<nsizeKey;countKey++){
            switch(mMapParam.Key[countKey]){
            case FilterDataType::MovingAverage:{
                SDBG("MovingAverage:" << mSrcBuf.size());
                if(!mMapParam.Value.isEmpty()){
                    FilterMovingAverage* pTemp=(FilterMovingAverage*)mMapParam.Value[countKey];
                    m_FilerData.bufy=mSignalProcessing.MovingAverageSmooth(
                                m_FilerData.bufy,(int)(pTemp->DataParam1));
                }
                break;}
            case FilterDataType::SavGol:{
                SDBG("SavGol:" << mSrcBuf.size());
                if(!mMapParam.Value.isEmpty()){
                    FilterSavGol* pTemp=(FilterSavGol*)mMapParam.Value[countKey];
                    m_FilerData.bufy=mSignalProcessing.SavGolFilt(
                                m_FilerData.bufy,int(pTemp->DataParam1),pTemp->DataParam2);
                }
                break;}
            case FilterDataType::FrameAverage:{
                SDBG("FrameAverage:" << mSrcBuf.size());
                if(!mMapParam.Value.isEmpty()){
                    FilterFrameAverage* pTemp=(FilterFrameAverage*)mMapParam.Value[countKey];
                    m_FilerData.bufy=pTemp->mFrameAverage.frameAverage(m_FilerData.bufy,(int)(pTemp->DataParam1));
                }
                break;}
            case FilterDataType::GainOffset:{
                SDBG("GainOffset:" << mSrcBuf.size());
                if(!mMapParam.Value.isEmpty()){
                    FilterGainOffset* pFilterGainOffset1=(FilterGainOffset*)(mMapParam.Value[countKey]);
                    if(pFilterGainOffset1->bGain&&pFilterGainOffset1->bOffset){
                        for(int ii=0;ii<nSize;ii++)
                            m_FilerData.bufy[ii]=pFilterGainOffset1->DataParam2*m_FilerData.bufy[ii]+pFilterGainOffset1->DataParam1;
                    }else if((!pFilterGainOffset1->bGain)&&pFilterGainOffset1->bOffset){
                        for(int ii=0;ii<nSize;ii++)
                            m_FilerData.bufy[ii]=m_FilerData.bufy[ii]+pFilterGainOffset1->DataParam1;
                    }else if(pFilterGainOffset1->bGain&&(!pFilterGainOffset1->bOffset)){
                        for(int ii=0;ii<nSize;ii++)
                            m_FilerData.bufy[ii]=pFilterGainOffset1->DataParam2*m_FilerData.bufy[ii];
                    }
                }
                break;}
            }
        }
        memcpy(dataDest.data(),m_FilerData.bufy.data(),sizeof(double)*nSize);
    }
    return true;
}

//void ProcessingDLL::setMethod(QString strSructMethod)
//{
//    if(!(strSructMethod.isEmpty())){
//        ui->tableWidget->clear();
//        QStringList listMethod= strSructMethod.split('+');
//        int nMaxRow=listMethod.size();
//        int nMaxColumn=0;
//        foreach(auto method1,listMethod){
//            QStringList templist=method1.split(',');
//            if(templist.size()>nMaxColumn)
//                nMaxColumn=templist.size();
//        }
//        ui->tableWidget->setRowCount(nMaxRow);
//        ui->tableWidget->setColumnCount(nMaxColumn);
//        for(int i=0;i<nMaxRow;i++)
//            for(int j=0;j<nMaxColumn;j++)
//                ui->tableWidget->setItem(i,j,new QTableWidgetItem(""));
//        int irow=0,jcolumn=0;
//        foreach(auto method1,listMethod){
//            QStringList templist=method1.split(',');
//            foreach(QString param1,templist){
//                ui->tableWidget->setItem(irow,jcolumn,new QTableWidgetItem(param1));
//                ui->tableWidget->item(irow,jcolumn)->setText(param1);
//                if(jcolumn==0)
//                    ui->tableWidget->item(irow,jcolumn)->setTextColor(255);
//                jcolumn++;
//            }
//            irow++;
//            jcolumn=0;
//        }
//        mMethodParam.ListParam=strSructMethod.split('+');
//    }else{
//        mMethodParam.ListParam.clear();
//    }
//    if(mMethodParam.uVersion >= 9999){
//        mMethodParam.uVersion=0;
//    }else{
//        mMethodParam.uVersion++;
//    }
//    ui->tableWidget->show();
//}

bool ProcessingDLL::setMethod(QString& strSructMethod)
{
    if(!(strSructMethod.isEmpty())){
        mMethodParam.ListParam=strSructMethod.split('+');
    }else{
        mMethodParam.ListParam.clear();
    }
    if(mMethodParam.uVersion >= 9999){
        mMethodParam.uVersion=0;
    }else{
        mMethodParam.uVersion++;
    }
    return true;
}

void ProcessingDLL::insertList(int columnCount,QString name)
{
    while(ui->tableWidget->columnCount()<columnCount){
        ui->tableWidget->insertColumn(ui->tableWidget->columnCount());
        for(int i=0;i<ui->tableWidget->rowCount();i++)
            ui->tableWidget->setItem(i,ui->tableWidget->columnCount()-1,new QTableWidgetItem(""));
    }
    int currentrow1=ui->tableWidget->currentRow();
    if(currentrow1==-1)
        currentrow1=ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(currentrow1);
    for(int i=0;i<ui->tableWidget->columnCount();i++)
        ui->tableWidget->setItem(currentrow1,i,new QTableWidgetItem(""));
    ui->tableWidget->item(currentrow1,0)->setText(name);

    if(name=="MovingAverage"){
        ui->tableWidget->item(currentrow1,1)->setText("9");
    }else if(name=="SavGolFilt"){//n,5;3,7;5,7;3,9;5,9;3,11;5,11
        ui->tableWidget->item(currentrow1,1)->setText("3");
        ui->tableWidget->item(currentrow1,2)->setText("7");
    }else if(name=="FrameAverage"){
        ui->tableWidget->item(currentrow1,1)->setText("9");
    }else if(name=="GainOffset"){
        ui->tableWidget->item(currentrow1,1)->setText("1");
        ui->tableWidget->item(currentrow1,1)->setText("0");
    }
}

void ProcessingDLL::insertList(MyTableItem MyTableItem1,QString name){
    while(ui->tableWidget->columnCount()<MyTableItem1.size()){
        ui->tableWidget->insertColumn(ui->tableWidget->columnCount());
        for(int i=0;i<ui->tableWidget->rowCount();i++)
            ui->tableWidget->setItem(i,ui->tableWidget->columnCount()-1,new QTableWidgetItem(""));
    }
    int currentrow1=ui->tableWidget->currentRow();
    if(currentrow1==-1)
        currentrow1=ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(currentrow1);
    for(int i=0;i<ui->tableWidget->columnCount();i++){
        QTableWidgetItem* QTableWidgetItem1=new QTableWidgetItem();
        if(MyTableItem1[i]==ItemType_Check){
            QTableWidgetItem1->setCheckState(Qt::Checked);
            QTableWidgetItem1->setText("Auto");
        }
        ui->tableWidget->setItem(currentrow1,i,QTableWidgetItem1);
    }
    ui->tableWidget->item(currentrow1,0)->setText(name);
}

void ProcessingDLL::on_pushButton_3_clicked()
{
    int nMaxRow=ui->tableWidget->rowCount();
    int nMaxColumn=ui->tableWidget->columnCount();
    //QStringList listMethod;
    mMethodParam.ListParam.clear();
    for(int nrow=0;nrow<nMaxRow;nrow++){
        QString StringMethod;
        for(int ncolumn=0;ncolumn<nMaxColumn;ncolumn++){
            QString tempStr=ui->tableWidget->item(nrow,ncolumn)->text();
            if(StringMethod.isEmpty())
                StringMethod+=tempStr;
            else
                StringMethod+=","+tempStr;
        }
       // listMethod<<StringMethod;
        mMethodParam.ListParam<<StringMethod;
    }
    if(!mMethodParam.ListParam.isEmpty())
        //if(!listMethod.isEmpty())
        //mMethodStr= listMethod.join("+");
        mMethodStr= mMethodParam.ListParam.join("+");
    else
        mMethodStr.clear();
    if(ui->checkBox->isChecked())
        bFilterEnable= true;
    else
        bFilterEnable= false;

    if(mMethodParam.uVersion >= 9999){
        mMethodParam.uVersion=0;
    }else{
        mMethodParam.uVersion++;
    }
}

void ProcessingDLL::on_pushButton_2_clicked()
{
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
}

void ProcessingDLL::on_B_BaseLine_clicked()
{
    MyTableItem MyTableItem1(3);
    MyTableItem1[0]=ItemType_Edit;
    MyTableItem1[1]=ItemType_Check;
    MyTableItem1[2]=ItemType_Edit;
    insertList(MyTableItem1,"BaseLine");
}

//QApplication* a= nullptr;
//ProcessingDLL* w= nullptr;

////int main(int argc, char *argv[])
//extern "C" __declspec(dllexport)int main(int argc, char *argv[])
//{
//    a = new QApplication(argc, argv);
//    w = new ProcessingDLL();
//    w->hide();
//    return 0;
//    //return a.exec();
//}

//void createFilter(){
//    char* b="abc";
//    main(0, &b);
//}

//void deleteFilter(){
//    if(w){
//        delete w;
//        w= nullptr;
//    }
//    if(a){
//        a->exec();
//    }
//}

//void showFilter(bool showD)
//{
//    if(w){
//        if(showD)
//            w->show();
//        else
//            w->hide();
//    }
//}

//void setEnabledF(bool bEnable){
//    if(w)
//        w->setEnabledF(bEnable);
//}

//bool getEnabledF(){
//    if(w)
//        return w->getEnabledF();
//    else
//        return false;
//}

//char* getMethod(){
//    if(w){
//        QString tmpStr= w->getMethod();
//        if(!tmpStr.isEmpty()){
//            QByteArray ba = tmpStr.toLatin1();
//            char *str=ba.data();
//            return str;
//        }
//        return nullptr;
//    }
//    return nullptr;
//}

//bool getData(std::vector<double>const& dataSrc, std::vector<double>& dataDest,double xBegin,double xEnd){
//    if(w)
//    return w->getData(dataSrc,dataDest,xBegin,xEnd);
//}

//void setMethod(char* strSructMethod){
//    if(w){
//        if(strSructMethod){
//            w->setMethod(QString(QLatin1String(strSructMethod)));
//        }else{
//            w->setMethod("");
//        }
//    }
//}
