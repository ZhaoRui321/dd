#include "sControlSSC.h"
#include "ui_sControlSSC.h"
#include <QSettings>
#include <Qdebug>

QString tempTitle_S[]={"TEM1_Set","TEM2_Set","TEM3_Set","TEM4_Set","TEM5_Set","TEM6_Set"};
QString PIDTitle_S[]={"PID1_Set","PID2_Set","PID3_Set","PID4_Set","PID5_Set","PID6_Set"};
QString dacTitle_S[]={"DAC1_Set","DAC2_Set","DAC3_Set","DAC4_Set","DAC5_Set","DAC6_Set","DAC7_Set","DAC8_Set"};

QString tempTitle_G[]={"TEM1_Get","TEM2_Get","TEM3_Get","TEM4_Get","TEM5_Get","TEM6_Get"};
QString dacTitle_G[]={"DAC1_Get","DAC2_Get","DAC3_Get","DAC4_Get","DAC5_Get","DAC6_Get","DAC7_Get","DAC8_Get",
                     "DAC9_Get","DAC10_Get","DAC11_Get","DAC12_Get","DAC13_Get","DAC14_Get","DAC15_Get","DAC16_Get"};

void sControlSSC::exportCmdTxt(const uint *cmd, uint size, const QString &fileName)
{
    FILE* pFile = fopen(fileName.toUtf8().data(), "a");
    char szFmt[20];
    const uint *pcIndex,*pcEnd;
    pcIndex = cmd;
    pcEnd = pcIndex + size;
    while(pcIndex < pcEnd){
        sprintf(szFmt, "%08X ", *pcIndex);
        fwrite(szFmt, 9, 1, pFile);
        ++pcIndex;
    }
    fwrite("\n",1,1,pFile);
    fclose(pFile);
}

sControlSSC::sControlSSC(QWidget *parent) :
    QWidget(parent),
    //m_engine(new QScriptEngine()),//m_engine(&mainWindow->project()->scriptEngine()),
    ui(new Ui::sControlSSC)
{
    ui->setupUi(this);
    initSObject(this);
    setSObject(this);
    //arrayReq.resize(SIZE_SSC_BUFF);
    //mBaReq_s_ccs.resize(SIZE_CCS_BUFF);
    initTable();
}

sControlSSC::~sControlSSC()
{
//    if ( m_timerID != -1 )
//        killTimer(m_timerID);
    delete ui;
}

void sControlSSC::initTable()
{
    QTableWidget* pQTableWidget[6]={ui->TABLE_CCS,ui->TABLE_TempGet,ui->TABLE_ADC1,ui->TABLE_ADC2,ui->TABLE_TempSet,ui->TABLE_DacSet};
    for(int i=0; i<6; i++){
        int nRow= pQTableWidget[i]->rowCount();
        int nColumn= pQTableWidget[i]->columnCount();
        QTableWidgetItem* pQTableWidgetItem= nullptr;
        for(int row=0; row< nRow; row++){
            for(int column= 0; column< nColumn; column++){
                pQTableWidgetItem= pQTableWidget[i]->item(row,column);
                if(row== 1){
                    if(!pQTableWidgetItem)
                        pQTableWidget[i]->setItem(row,column,new QTableWidgetItem("return "+
                                                                                  pQTableWidget[i]->horizontalHeaderItem(column)->text()+ ";"));
                    else
                        pQTableWidget[i]->item(row,column)->
                                setText("return "+ pQTableWidget[i]->horizontalHeaderItem(column)->text()+ ";");
                }else if(row== 3){
                    if(!pQTableWidgetItem)
                        pQTableWidget[i]->setItem(row,column,new QTableWidgetItem("0@0@0"));
                    else
                        pQTableWidget[i]->item(row,column)->setText("0@0@0");
                }else{
                    if(!pQTableWidgetItem)
                        pQTableWidget[i]->setItem(row,column,new QTableWidgetItem("0"));
                    else
                        pQTableWidget[i]->item(row,column)->setText("0");
                    if(!(row== 2 && (pQTableWidget[i]== ui->TABLE_TempSet|| pQTableWidget[i]== ui->TABLE_DacSet)))
                        pQTableWidget[i]->item(row,column)->setFlags(Qt::NoItemFlags);
                }
            }
        }
    }
    //QTableWidget* pQTableWidget1[4]={ui->TABLE_TempSet,ui->TABLE_DacSet};
}

void sControlSSC::initSObject(QObject *pObj)
{
    pObj->setProperty("connect", "false");           //state
    pObj->setProperty("Parameter","");
    pObj->setProperty("ADC0", "0");
    pObj->setProperty("ADC1", "0");
    pObj->setProperty("ADC2", "0");
    pObj->setProperty("ADC3", "0");
    pObj->setProperty("baudrate", "115200");
    pObj->setProperty("length(byte)", "64");

    for(int i=0;i<TEMP_WIDTH;i++)
        pObj->setProperty(tempTitle_S[i].toLocal8Bit(), "0");           //TEMP_SET
    for(int i=0;i<TEMP_WIDTH;i++)
        pObj->setProperty(PIDTitle_S[i].toLocal8Bit(), "0@0@0");           //PID
    for(int i=0;i<TEMP_WIDTH;i++)
        pObj->setProperty(tempTitle_G[i].toLocal8Bit(), "0");           //TEMP_GET

    for(int i=0;i<DAC_WIDTH_SET;i++)
        pObj->setProperty(dacTitle_S[i].toLocal8Bit(), "0");           //DAC_SET
    for(int i=0;i<DAC_WIDTH_GET;i++)
        pObj->setProperty(dacTitle_G[i].toLocal8Bit(), "0");           //DAC_GET

    for(int i=0;i<8;i++)
        pObj->setProperty(("IO"+QString::number(i)).toLocal8Bit(), "0");

//    pObj->setProperty("E_DYNODE","1");
//    pObj->setProperty("P_DYNODE","1");
//    pObj->setProperty("E_ESI","1");
//    pObj->setProperty("P_ESI","1");
//    pObj->setProperty("E_SEM","1");

    //addSpecialProperty(pObj, "DataOut", "", "mapping");  //out
    //addSpecialProperty(pObj, "DataIn", "", "mapping");  //in
}

void sControlSSC::setSObject(QObject *obj)
{
    //SWidget::setSObject(obj);
    setParameter(obj->property("parameter").toString());
    connect(ui->TABLE_CCS,SIGNAL(cellChanged(int, int)),this, SLOT(onCCSChanged(int, int)));
    connect(ui->TABLE_TempSet,SIGNAL(cellChanged(int, int)),this, SLOT(onTempSetChanged(int, int)));
    connect(ui->TABLE_DacSet,SIGNAL(cellChanged(int, int)),this, SLOT(onDacSetChanged(int, int)));
    connect(ui->TABLE_TempGet,SIGNAL(cellChanged(int, int)),this, SLOT(onTempGetChanged(int, int)));
    connect(ui->TABLE_ADC1,SIGNAL(cellChanged(int, int)),this, SLOT(onADC1Changed(int, int)));
    connect(ui->TABLE_ADC2,SIGNAL(cellChanged(int, int)),this, SLOT(onADC2Changed(int, int)));
//    if(m_timerID==-1)
//        m_timerID = startTimer(10);
}

//void sControlSSC::propertyOfSObjectChanged(SObject* pObj, const QString& strPropName, const SObject::PropertyT& propChangedBy)
//{
//    Q_UNUSED(propChangedBy)
//    //QVariant varValue = pObj->property(strPropName.toUtf8().data());
//    //QObject::blockSignals(true);
//    //QObject::blockSignals(false);
//}

bool sControlSSC::ParamDown(_CMD_SSC_SET &tempCMD_SSC_SET)
{
    mUART_SSC.baudrate= 115200;//sobject()->property("baudrate").toUInt();
    mUART_SSC.uartTxBytes= 64;//sobject()->property("length(byte)").toUInt();
    for(int i=0;i<TEMP_WIDTH;i++)
        tempCMD_SSC_SET.Value_TEMP[i]=sobject()->property(tempTitle_S[i].toLocal8Bit()).toInt();
    for(int i=0;i<TEMP_WIDTH;i++){
        QString strPID=sobject()->property(PIDTitle_S[i].toLocal8Bit()).toString();
        if(!strPID.isEmpty()){
            QStringList tmpList=strPID.split("@");
            if(tmpList.size()==3){
                tempCMD_SSC_SET.Value_PID[i*3]=tmpList[0].toInt();           //PID
                tempCMD_SSC_SET.Value_PID[i*3+1]=tmpList[1].toInt();
                tempCMD_SSC_SET.Value_PID[i*3+2]=tmpList[2].toInt();
            }
        }
    }
    for(int i=0;i<DAC_WIDTH_SET;i++)
        tempCMD_SSC_SET.Value_DAC[i]=sobject()->property(dacTitle_S[i].toLocal8Bit()).toDouble();
    for(int i=0;i<12;i++)
        tempCMD_SSC_SET.enableIO[i]= (quint16)(sobject()->property(("IO"+QString::number(i)).toLocal8Bit()).toInt());
//    tempCMD_SSC_SET.E_DYNODE=sobject()->property("E_DYNODE").toInt();
//    tempCMD_SSC_SET.P_DYNODE=sobject()->property("P_DYNODE").toInt();
//    tempCMD_SSC_SET.E_ESI=sobject()->property("E_ESI").toInt();
//    tempCMD_SSC_SET.P_ESI=sobject()->property("P_ESI").toInt();
//    tempCMD_SSC_SET.E_SEM=sobject()->property("E_SEM").toInt();
    return true;
}

bool sControlSSC::ParamUp()
{
    sobject()->QObject::setProperty("ADC0",QString::number(mSTATE_REQUEST_CCS.adcValue[0]));
    ui->TABLE_CCS->item(0,0)->setText(QString::number(mSTATE_REQUEST_CCS.adcValue[0]));
    sobject()->QObject::setProperty("ADC1",QString::number(mSTATE_REQUEST_CCS.adcValue[1]));
    ui->TABLE_CCS->item(0,1)->setText(QString::number(mSTATE_REQUEST_CCS.adcValue[1]));
    sobject()->QObject::setProperty("ADC2",QString::number(mSTATE_REQUEST_CCS.adcValue[0]));
    ui->TABLE_CCS->item(0,2)->setText(QString::number(mSTATE_REQUEST_CCS.adcValue[2]));
    sobject()->QObject::setProperty("ADC3",QString::number(mSTATE_REQUEST_CCS.adcValue[0]));
    ui->TABLE_CCS->item(0,3)->setText(QString::number(mSTATE_REQUEST_CCS.adcValue[3]));

    QString tmpStr;
    for(int i=0;i<TEMP_WIDTH;i++){
        if(i<4){
            tmpStr= QString::number(mCMD_SSC_REQ.Value_TEMP[i] * 0.0373 - 306.03);
        }else {
            tmpStr= QString::number(mCMD_SSC_REQ.Value_TEMP[i] * 0.2465 - 42.521);
        }
        sobject()->QObject::setProperty(tempTitle_G[i].toLocal8Bit(),tmpStr);
        ui->TABLE_TempGet->item(0,i)->setText(tmpStr);
    }
    for(int i=0;i<DAC_WIDTH_GET;i++){
        tmpStr= QString::number(mCMD_SSC_REQ.Value_DAC[i] * 0.00243861 - 9.98585727);
        sobject()->QObject::setProperty(dacTitle_G[i].toLocal8Bit(), tmpStr);
        int firstCount= ui->TABLE_ADC1->columnCount();

        if(i<firstCount){
            ui->TABLE_ADC1->item(0,i)->setText(tmpStr);

            QTableWidgetItem* pQTableRow0= ui->TABLE_ADC1->item(0,i);
            QTableWidgetItem* pQTableRow1= ui->TABLE_ADC1->item(1,i);
            QTableWidgetItem* pQTableRow2= ui->TABLE_ADC1->item(2,i);
            if(!pQTableRow1|| !pQTableRow0|| !pQTableRow2)
                return false;
        }else{
            QTableWidgetItem* pQTableRow0= ui->TABLE_ADC2->item(0,i-firstCount);
            QTableWidgetItem* pQTableRow1= ui->TABLE_ADC2->item(1,i-firstCount);
            QTableWidgetItem* pQTableRow2= ui->TABLE_ADC2->item(2,i-firstCount);
            if(!pQTableRow1|| !pQTableRow0|| !pQTableRow2)
                return false;
            pQTableRow0->setText(tmpStr);
        }
    }
    return true;
}

bool sControlSSC::updateSwitch(QString name, QString value)
{
    if(!sobject()->property(name.toLocal8Bit()).isNull()){
        if(name.contains("IO",Qt::CaseSensitive)){
            if(name== "IO0"){
                if(value=="1"){
                    ui->UI_PB_IO0->setText("Off");
                }else if(value=="0"){
                    ui->UI_PB_IO0->setText("On");
                }else
                    return false;
            }else if(name== "IO1"){
                if(value=="1"){
                    ui->UI_PB_IO1->setText("Off");
                }else if(value=="0"){
                    ui->UI_PB_IO1->setText("On");
                }else
                    return false;
            }else if(name== "IO2"){
                if(value=="1"){
                    ui->UI_PB_IO2->setText("Off");
                }else if(value=="0"){
                    ui->UI_PB_IO2->setText("On");
                }else
                    return false;
            }else if(name== "IO3"){
                if(value=="1"){
                    ui->UI_PB_IO3->setText("Off");
                }else if(value=="0"){
                    ui->UI_PB_IO3->setText("On");
                }else
                    return false;
            }else if(name== "IO4"){
                if(value=="1"){
                    ui->UI_PB_IO4->setText("Off");
                }else if(value=="0"){
                    ui->UI_PB_IO4->setText("On");
                }else
                    return false;
            }else if(name== "IO5"){
                if(value=="1"){
                    ui->UI_PB_IO5->setText("Off");
                }else if(value=="0"){
                    ui->UI_PB_IO5->setText("On");
                }else
                    return false;
            }else if(name== "IO6"){
                if(value=="1"){
                    ui->UI_PB_IO6->setText("Off");
                }else if(value=="0"){
                    ui->UI_PB_IO6->setText("On");
                }else
                    return false;
            }else if(name== "IO7"){
                if(value=="1"){
                    ui->UI_PB_IO7->setText("Off");
                }else if(value=="0"){
                    ui->UI_PB_IO7->setText("On");
                }else
                    return false;
            }else
                return false;
        }
        sobject()->setProperty(name.toLocal8Bit(),value);
    }
}

QByteArray sControlSSC::createSSC_CMD(){
    QByteArray tmpCMD(SIZE_SSC_BUFF, 0);
    quint16* pCommand=(quint16*)tmpCMD.data();
    pCommand[0]=0xf301;
    pCommand[1]=0x0002;
    pCommand[31]=0x0A0D;
    return ParamCCS::uartCMDData(tmpCMD, 115200u);
}

void sControlSSC::showSSC(QByteArray& pArray)
{
    if(pArray.size()<512)
        return;
    uint* pCMD32=(uint*)(pArray.data());
    mSTATE_REQUEST_CCS.adcValue[0]= ((double)(pCMD32[3] & 0x0000ffff)) * 20.0 / 65535 - 10;
    mSTATE_REQUEST_CCS.adcValue[1]= ((double)((pCMD32[3]>>16) & 0x0000ffff)) * 20.0 / 65535 - 10;
    mSTATE_REQUEST_CCS.adcValue[2]= ((double)(pCMD32[4] & 0x0000ffff)) * 20.0 / 65535 - 10;
    mSTATE_REQUEST_CCS.adcValue[3]= ((double)((pCMD32[4]>>16) & 0x0000ffff)) * 20.0 / 65535 - 10;

    if((pCMD32[125]&0xff)==64){
        QByteArray arrayReq(SIZE_SSC_BUFF, 0);
        //arrayReq.resize(SIZE_SSC_BUFF);
        for(int i=0;i<64;i++)
            arrayReq.data()[i]=pCMD32[i+5]&0xff;
        quint16* pCommand=(quint16*)arrayReq.data();
        if(pCommand[0]==0xf301){
            for(int i=0;i<TEMP_WIDTH;i++)
                mCMD_SSC_REQ.Value_TEMP[i] = pCommand[i+2];           //DAC_SET
            for(int i=0;i<DAC_WIDTH_GET;i++)
                mCMD_SSC_REQ.Value_DAC[i] = pCommand[i+8];           //DAC_GET
        }
        ParamUp();
        qDebug()<<"N_ControlSSC_RRcommand_R:"<<(pCMD32[125]&0xff);
        return;
    }else{
        //ParamUp();
        qDebug()<<"W_ControlSSC_RRcommand_R:"<<(pCMD32[125]&0xff);
        return;
    }
}

QByteArray sControlSSC::createRequest(){
    QByteArray tmpCMD(SIZE_SSC_BUFF, 0);
    quint16* pCommand=(quint16*)tmpCMD.data();
    pCommand[0]=0xf301;
    pCommand[1]=0x0002;
    pCommand[31]=0x0A0D;
    return tmpCMD;//ParamCCS::uartCMDData(tmpCMD, 115200u);
}

QByteArray sControlSSC::createElecPumpOff()
{
    QByteArray tmpCMD(SIZE_SSC_BUFF, 0);
    quint16* pCommand=(quint16*)tmpCMD.data();
    pCommand[0]=0xf301;
    pCommand[1]=0x0004;
    pCommand[31]=0x0A0D;
    return tmpCMD;//ParamCCS::uartCMDData(tmpCMD, 115200u);
}

QByteArray sControlSSC::createElecPumpOn()
{
    QByteArray tmpCMD(SIZE_SSC_BUFF, 0);
    quint16* pCommand=(quint16*)tmpCMD.data();
    pCommand[0]=0xf301;
    pCommand[1]=0x0003;
    pCommand[31]=0x0A0D;
    return tmpCMD;//ParamCCS::uartCMDData(tmpCMD, 115200u);
}

QByteArray sControlSSC::createConfig()
{
    _CMD_SSC_SET tempCMD_SSC_SET;
    ParamDown(tempCMD_SSC_SET);
    QByteArray arrayReq(SIZE_SSC_BUFF, 0);
    //memset(arrayReq.data(),0,SIZE_SSC_BUFF);
    quint16* pCommand=(quint16*)arrayReq.data();
    pCommand[0]=0xf301;
    pCommand[1]=0x0001;
    for(int i=0;i<TEMP_WIDTH;i++){
        if(i<4){
            //pCommand[2+i] = 0x0000;
            pCommand[2+i]=((quint16)(tempCMD_SSC_SET.Value_TEMP[i] * 26.80965 + 8204.558
                                     ))&0xffff;
        }else{
            pCommand[2+i]=((quint16)(tempCMD_SSC_SET.Value_TEMP[i]* 4.056795 + 172.499
                                     ))&0xffff;
        }
    }
    for(int i=0;i<TEMP_WIDTH;i++){
        arrayReq.data()[16+i*3]=tempCMD_SSC_SET.Value_PID[i*3];
        arrayReq.data()[17+i*3]=tempCMD_SSC_SET.Value_PID[i*3+1];
        arrayReq.data()[18+i*3]=tempCMD_SSC_SET.Value_PID[i*3+2];
    }
    for(int i=0;i<DAC_WIDTH_SET;i++){
        quint16 tmpV=((quint16)(tempCMD_SSC_SET.Value_DAC[i] * 3276.2467 + 32768.28))&0xffff;
        pCommand[17+i]=tmpV;
    }
    for(int i=0;i<6;i++)
        pCommand[25+i]=(tempCMD_SSC_SET.enableIO[i*2]&0x00ff)+((tempCMD_SSC_SET.enableIO[i*2+1]&0x00ff)<<8);
//    pCommand[25]=(tempCMD_SSC_SET.E_DYNODE&0x00ff)+((tempCMD_SSC_SET.P_DYNODE&0x00ff)<<8);
//    pCommand[26]=(tempCMD_SSC_SET.E_ESI&0x00ff)+((tempCMD_SSC_SET.P_ESI&0x00ff)<<8);
//    pCommand[27]=tempCMD_SSC_SET.E_SEM&0x00ff;

    pCommand[31]=0x0A0D;
    //QByteArray tmpW= ParamCCS::uartCMDData(arrayReq, 115200u);
#ifdef DEBUG_TXT
        exportCmdTxt((uint*) tmpW.data(), tmpW.size()/sizeof(uint), "c:\\SysRequest.txt");
#endif
    return arrayReq;
}

//bool sControlSSC::analysisConfig(QByteArray tmpR)
//{
//    if(tmpR.isEmpty() || tmpR.size()<512){
//        return false;
//    }
//    uint* pCMD32=(uint*)(mBaReq_r_ccs.data());
//    if((pCMD32[125]&0xff)>=64)
//        return true;
//    return false;
//}

QString sControlSSC::getParameter(QTableWidget* pQTableWidget)
{
    if(!pQTableWidget)
        return QString();
    QString forBack;
    QTableWidgetItem* pQTableWidgetItem= NULL;
    int nRowTempSet= pQTableWidget->rowCount();
    int nColumnTempSet= pQTableWidget->columnCount();
    for(int i= 0; i< nRowTempSet; i++){
        for(int j= 0; j< nColumnTempSet; j++){
            pQTableWidgetItem= pQTableWidget->item(i,j);
            if(pQTableWidgetItem!= NULL){
                if(j== nColumnTempSet- 1)
                    forBack+= pQTableWidgetItem->text();
                else
                    forBack+= pQTableWidgetItem->text()+ ",";
            }else{
                if(j== nColumnTempSet- 1)
                    forBack+= "0";
                else
                    forBack+= "0,";
            }
        }
        //if(i!= nRowTempSet- 1)
            forBack+= "$";
    }
    return forBack;
}

QString sControlSSC::getParameter()
{
    QString tmpStr,forBack;
    QTableWidget* pQTableWidget[6]= {ui->TABLE_CCS,ui->TABLE_TempSet,ui->TABLE_DacSet,ui->TABLE_TempGet,ui->TABLE_ADC1,ui->TABLE_ADC2};
    for(int i=0; i<6;i++){
        tmpStr= getParameter(pQTableWidget[i]);
        if(tmpStr.isEmpty())
            return QString();
        else
            forBack+= tmpStr;
    }
    return forBack;
}

bool sControlSSC::setParameter(QString parameter)
{
    QTableWidget* pQTableWidget[6]= {ui->TABLE_CCS,ui->TABLE_TempSet,ui->TABLE_DacSet,ui->TABLE_TempGet,ui->TABLE_ADC1,ui->TABLE_ADC2};
    QStringList tmpList=  parameter.split("$");
    int sizeList= tmpList.size();
    int currentList=0;
    QTableWidgetItem* tmpQTableWidgetItem= nullptr;
    for(int nWidget= 0; nWidget<6; nWidget++){
        int rowCount= pQTableWidget[nWidget]->rowCount();
        for(int nRow=0; nRow< rowCount; nRow++){
            if(currentList< sizeList){
                QString tmpString= tmpList.at(currentList);
                currentList++;
                QStringList commaList = tmpString.split(",");
                int column= 0;
                foreach (QString commaString, commaList){
                    tmpQTableWidgetItem= pQTableWidget[nWidget]->item(nRow, column);
                    if(tmpQTableWidgetItem)
                        tmpQTableWidgetItem->setText(commaString);
                    else
                        pQTableWidget[nWidget]->setItem(nRow, column,new QTableWidgetItem(commaString));
                    column++;
                }
            }else
                return false;
        }
    }
    return true;
}

void sControlSSC::on_B_Update_clicked()
{
    QString strParam= getParameter();
    if(strParam.isEmpty())
        return;
    QString path= QCoreApplication::applicationDirPath()+"/system.ini";
    QSettings configIniWrite(path, QSettings::IniFormat);
    configIniWrite.setValue("/System/ParameterSSC", strParam);
}

QString sControlSSC::useScript(QString valueStr, QString scriptStr, QString value)
{
    if(valueStr.isEmpty()|| scriptStr.isEmpty())
        return QString();
    QString tmpScript= "function f"+valueStr+"("+ valueStr+"){"+scriptStr+"}";
//    QScriptValue jsValue = m_engine->evaluate(tmpScript);
//    if(!m_engine->hasUncaughtException()){
//        jsValue = m_engine->evaluate("f"+valueStr+"("+ value+ ")");
//        if(!m_engine->hasUncaughtException())
//            return jsValue.toString();
//        else
//            return QString();
//    }else
//        return QString();
}

void sControlSSC::onCCSChanged(int row, int column)
{
//    if(m_engine){
//        if(row==0||row== 1){
//            QTableWidgetItem* pQTableRow0= ui->TABLE_CCS->item(0,column);
//            QTableWidgetItem* pQTableRow1= ui->TABLE_CCS->item(1,column);
//            QTableWidgetItem* pQTableRow2= ui->TABLE_CCS->item(2,column);
//            if(!pQTableRow1|| !pQTableRow0|| !pQTableRow2)
//                return;
//            pQTableRow2->setText(useScript(ui->TABLE_CCS->horizontalHeaderItem(column)->text(),
//                                  pQTableRow1->text(), pQTableRow0->text()));
////            QString tmpStr= getParameter();
////            if(tmpStr.isEmpty())
////                return;
////            sobject()->QObject::setProperty("Parameter", tmpStr);
//        }
//    }
}

void sControlSSC::onTempSetChanged(int row, int column)
{
//    if(m_engine){
//        QTableWidgetItem* pQTableRow0= ui->TABLE_TempSet->item(0,column);
//        QTableWidgetItem* pQTableRow1= ui->TABLE_TempSet->item(1,column);
//        QTableWidgetItem* pQTableRow2= ui->TABLE_TempSet->item(2,column);
//        QTableWidgetItem* pQTableRow3= ui->TABLE_TempSet->item(3,column);
//        if(!pQTableRow1|| !pQTableRow0|| !pQTableRow2|| !pQTableRow3)
//            return;
//        if(row== 1|| row== 2){
//            QString tmpStr= useScript(ui->TABLE_TempSet->horizontalHeaderItem(column)->text(),
//                                      pQTableRow1->text(), pQTableRow2->text());
//            pQTableRow0->setText(tmpStr);
//            sobject()->setProperty(tempTitle_S[column].toLocal8Bit(), tmpStr);           //TEMP_SET
////            tmpStr= getParameter();
////            if(tmpStr.isEmpty())
////                return;
////            sobject()->QObject::setProperty("Parameter", tmpStr);
//        }else if(row== 3){
//            if(pQTableRow3->text().isEmpty())
//                sobject()->setProperty(PIDTitle_S[column].toLocal8Bit(), "0@0@0");           //PID
//            else
//                sobject()->setProperty(PIDTitle_S[column].toLocal8Bit(), pQTableRow3->text());           //PID
////            QString tmpStr= getParameter();
////            if(tmpStr.isEmpty())
////                return;
////            sobject()->QObject::setProperty("Parameter", tmpStr);
//        }
//    }
}

void sControlSSC::onDacSetChanged(int row, int column)
{
//    if(m_engine){
//        if(row== 1|| row== 2){
//            QTableWidgetItem* pQTableRow0= ui->TABLE_DacSet->item(0,column);
//            QTableWidgetItem* pQTableRow1= ui->TABLE_DacSet->item(1,column);
//            QTableWidgetItem* pQTableRow2= ui->TABLE_DacSet->item(2,column);
//            if(!pQTableRow1|| !pQTableRow0|| !pQTableRow2)
//                return;
//            QString tmpStr= useScript(ui->TABLE_DacSet->horizontalHeaderItem(column)->text(),
//                                      pQTableRow1->text(), pQTableRow2->text());
//            pQTableRow0->setText(tmpStr);
//            sobject()->setProperty(dacTitle_S[column].toLocal8Bit(), tmpStr);           //DAC_SET
////            tmpStr= getParameter();
////            if(tmpStr.isEmpty())
////                return;
////            sobject()->QObject::setProperty("Parameter", tmpStr);
//        }
//    }
}

void sControlSSC::onTempGetChanged(int row, int column)
{
//    if(m_engine){
//        if(row==0||row== 1){//
//            QTableWidgetItem* pQTableRow0= ui->TABLE_TempGet->item(0,column);
//            QTableWidgetItem* pQTableRow1= ui->TABLE_TempGet->item(1,column);
//            QTableWidgetItem* pQTableRow2= ui->TABLE_TempGet->item(2,column);
//            if(!pQTableRow1|| !pQTableRow0|| !pQTableRow2)
//                return;
//            pQTableRow2->setText(useScript(ui->TABLE_TempGet->horizontalHeaderItem(column)->text(),
//                                  pQTableRow1->text(), pQTableRow0->text()));
////            QString tmpStr= getParameter();
////            if(tmpStr.isEmpty())
////                return;
////            sobject()->QObject::setProperty("Parameter", tmpStr);
//        }
//    }
}

void sControlSSC::onADC1Changed(int row, int column)
{
//    if(m_engine){
//        if(row==0||row== 1){//
//            QTableWidgetItem* pQTableRow0= ui->TABLE_ADC1->item(0,column);
//            QTableWidgetItem* pQTableRow1= ui->TABLE_ADC1->item(1,column);
//            QTableWidgetItem* pQTableRow2= ui->TABLE_ADC1->item(2,column);
//            if(!pQTableRow1|| !pQTableRow0|| !pQTableRow2)
//                return;
//            pQTableRow2->setText(useScript(ui->TABLE_ADC1->horizontalHeaderItem(column)->text(),
//                                  pQTableRow1->text(), pQTableRow0->text()));
////            QString tmpStr= getParameter();
////            if(tmpStr.isEmpty())
////                return;
////            sobject()->QObject::setProperty("Parameter", tmpStr);
//        }
//    }
}

void sControlSSC::onADC2Changed(int row, int column)
{
//    if(m_engine){
//        if(row==0||row== 1){//
//            QTableWidgetItem* pQTableRow0= ui->TABLE_ADC2->item(0,column);
//            QTableWidgetItem* pQTableRow1= ui->TABLE_ADC2->item(1,column);
//            QTableWidgetItem* pQTableRow2= ui->TABLE_ADC2->item(2,column);
//            if(!pQTableRow1|| !pQTableRow0|| !pQTableRow2)
//                return;
//            pQTableRow2->setText(useScript(ui->TABLE_ADC2->horizontalHeaderItem(column)->text(),
//                                  pQTableRow1->text(), pQTableRow0->text()));
////            QString tmpStr= getParameter();
////            if(tmpStr.isEmpty())
////                return;
////            sobject()->QObject::setProperty("Parameter", tmpStr);
//        }
//    }
}

void sControlSSC::on_UI_PB_IO0_clicked()
{
    if(ui->UI_PB_IO0->text()=="On"){
        sobject()->setProperty("IO0", "1");
        ui->UI_PB_IO0->setText("Off");
    }else{
        sobject()->setProperty("IO0", "0");
        ui->UI_PB_IO0->setText("On");
    }
}

void sControlSSC::on_UI_PB_IO1_clicked()
{
    if(ui->UI_PB_IO1->text()=="On"){
        sobject()->setProperty("IO1", "1");
        ui->UI_PB_IO1->setText("Off");
    }else{
        sobject()->setProperty("IO1", "0");
        ui->UI_PB_IO1->setText("On");
    }
}

void sControlSSC::on_UI_PB_IO2_clicked()
{
    if(ui->UI_PB_IO2->text()=="On"){
        sobject()->setProperty("IO2", "1");
        ui->UI_PB_IO2->setText("Off");
    }else{
        sobject()->setProperty("IO2", "0");
        ui->UI_PB_IO2->setText("On");
    }
}

void sControlSSC::on_UI_PB_IO3_clicked()
{
    if(ui->UI_PB_IO3->text()=="On"){
        sobject()->setProperty("IO3", "1");
        ui->UI_PB_IO3->setText("Off");
    }else{
        sobject()->setProperty("IO3", "0");
        ui->UI_PB_IO3->setText("On");
    }
}

void sControlSSC::on_UI_PB_IO4_clicked()
{
    if(ui->UI_PB_IO4->text()=="On"){
        sobject()->setProperty("IO4", "1");
        ui->UI_PB_IO4->setText("Off");
    }else{
        sobject()->setProperty("IO4", "0");
        ui->UI_PB_IO4->setText("On");
    }
}

void sControlSSC::on_UI_PB_IO5_clicked()
{
    if(ui->UI_PB_IO5->text()=="On"){
        sobject()->setProperty("IO5", "1");
        ui->UI_PB_IO5->setText("Off");
    }else{
        sobject()->setProperty("IO5", "0");
        ui->UI_PB_IO5->setText("On");
    }
}

void sControlSSC::on_UI_PB_IO6_clicked()
{
    if(ui->UI_PB_IO6->text()=="On"){
        sobject()->setProperty("IO6", "1");
        ui->UI_PB_IO6->setText("Off");
    }else{
        sobject()->setProperty("IO6", "0");
        ui->UI_PB_IO6->setText("On");
    }
}

void sControlSSC::on_UI_PB_IO7_clicked()
{
    if(ui->UI_PB_IO7->text()=="On"){
        sobject()->setProperty("IO7", "1");
        ui->UI_PB_IO7->setText("Off");
    }else{
        sobject()->setProperty("IO7", "0");
        ui->UI_PB_IO7->setText("On");
    }
}


void sControlSSC::onSendAllState(sControlSSC::_CMD_SSC_SET& tempCMD_SSC_SET)
{
    //设定属性值
    for(int i=0;i<TEMP_WIDTH;i++)
        sobject()->setProperty(tempTitle_S[i].toLocal8Bit(),QString::number(tempCMD_SSC_SET.Value_TEMP[i]));
    for(int i=0;i<TEMP_WIDTH;i++){
        QString strPID = QString("%1@%2@%3")
                .arg(tempCMD_SSC_SET.Value_PID[i*3])
                .arg(tempCMD_SSC_SET.Value_PID[i*3+1])
                .arg(tempCMD_SSC_SET.Value_PID[i*3+2]);
        sobject()->setProperty(PIDTitle_S[i].toLocal8Bit(),strPID);
    }
    for(int i=0;i<DAC_WIDTH_SET;i++)
        sobject()->setProperty(dacTitle_S[i].toLocal8Bit(),QString::number(tempCMD_SSC_SET.Value_DAC[i]));
    for(int i=0;i<12;i++)
        sobject()->setProperty(("IO"+QString::number(i)).toLocal8Bit(),QString::number(tempCMD_SSC_SET.enableIO[i]));

}
