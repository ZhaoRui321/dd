#include "sPwmCCS.h"
#include <QHBoxLayout>
#include <QComboBox>
#include <QContextMenuEvent>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QCoreApplication>
#include <QDebug>
#include <QSettings>
#include <QTime>

sPwmCCS::sPwmCCS(QWidget *parent): QWidget(parent)
{

    m_pwmTable = new QTableWidget(this);

    m_applyButton = new QPushButton(tr("Apply"), this);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_pwmTable);
    layout->addWidget(m_applyButton);
    connect(m_applyButton, SIGNAL(released()), SLOT(apply()));
    //connect(m_pwmTable,SIGNAL(cellChanged(int, int)),this, SLOT(saveParameter(int, int)));

    initPWMTable();
}

QString sPwmCCS::getName()
{
    QString name;
    for(int index=0; index<m_pwmTable->rowCount(); index++){
        if(m_pwmTable->item(index, 0)){
            if(index== m_pwmTable->rowCount()-1)
                name+= m_pwmTable->item(index, 0)->text();
            else
                name+= m_pwmTable->item(index, 0)->text()+ ";";
        }
    }
    return name;
}

void sPwmCCS::setName(QString name)
{
    QStringList names = name.split(';');
    int index = 0;
    foreach (const QString& name, names) {
        if(m_pwmTable->item(index, 0))
            m_pwmTable->item(index, 0)->setText(name);
        else
            m_pwmTable->setItem(index, 0, new QTableWidgetItem(name));
        ++index;
    }
}

void sPwmCCS::initPWMTable()
{
    QStringList headerTxt;
    headerTxt << tr("Name") << tr("Frequency(MHz)") << tr("Duty cycle(%)") << tr("Delay(%)") << tr("Reverse") << tr("Enable");
    m_pwmTable->setRowCount(8);
    m_pwmTable->setColumnCount(headerTxt.size());
    m_pwmTable->setHorizontalHeaderLabels(headerTxt);

    setName("PWM0;PWM1;PWM2;PWM3;PWM4;PWM5;PWM6;PWM7");

    uint period=1, hstart=0, hend=0;
    double fUnit = freuencyUnit();
    bool enable=true, reverse=false;
    QTableWidgetItem* twItem;
    auto fSetItem = [&](int row, int col, const QVariant& value){
        if((twItem = m_pwmTable->item(row, col)) == NULL) {
            twItem = new QTableWidgetItem();
            m_pwmTable->setItem(row, col, twItem);
        }
        twItem->setData(Qt::EditRole, value);
    };

    for(int index = 0; index < 8; index++){
        fSetItem(index, 1, sysFrequency() / (period * fUnit));
        fSetItem(index, 2, 50);//double(hend - hstart) * 100 / period);
        fSetItem(index, 3, 50);//double(hstart) * 100 / period);
        fSetItem(index, 4, reverse);
        fSetItem(index, 5, enable);
    }
}

double sPwmCCS::freuencyUnit()
{
    //    QString funit = sobject()->property("frequency_unit").toString();
    double fu = 1;
    //    if(funit.compare("GHz", Qt::CaseInsensitive) == 0)
    //        fu = 1000000000;
    //    else if(funit.compare("MHz", Qt::CaseInsensitive) == 0)
    fu = 1000000;
    //    else if(funit.compare("KHz", Qt::CaseInsensitive) == 0)
    //        fu = 1000;
    return fu;
}

//void sPwmCCS::propertyOfSObjectChanged(SObject *pObj, const QString &strPropName, const SObject::PropertyT &propChangedBy)
//{
//    QVariant varValue = pObj->property(strPropName.toUtf8().data());
//    QObject::blockSignals(true);
//    if(strPropName == "name"){
//        updateName(varValue.toString());
//    }else if(strPropName == "frequency_unit"){
//        m_pwmTable->horizontalHeaderItem(1)->setText(tr("Frequency(%1)")
//                                                     .arg(pObj->property("frequency_unit").toString()));
//        updatePWMTable();
//    }else if(strPropName == "parameter"){
//        disconnect(m_pwmTable,SIGNAL(cellChanged(int, int)),this, SLOT(saveParameter(int, int)));
//        setParameter(pObj->property("parameter").toString());
//        connect(m_pwmTable,SIGNAL(cellChanged(int, int)),this, SLOT(saveParameter(int, int)));
//    }
//        QObject::blockSignals(false);
//}

//QString sPwmCCS::keyString()
//{
//    return SWidget::key("ccs_pwm");
//}

//void sPwmCCS::initSObject(SObject *pObj)
//{
//    pObj->setProperty("name", "PWM0;PWM1;PWM2;PWM3;PWM4;PWM5;PWM6;PWM7");
//    pObj->setProperty("frequency_unit", "Hz");
//    pObj->setProperty("parameter", "");
//    addSpecialProperty(pObj, "DataOut", "", "mapping");  //out
//    addSpecialProperty(pObj, "DataIn", "", "mapping");  //in
//}

//void sPwmCCS::setting(bool)
//{
//    int index;
//    QDialog setDlg(this);
//    QComboBox* funitBox = new QComboBox(&setDlg);
//    QLineEdit* edits[8];
//    QPushButton* button[2];
//    QStringList names = sobject()->property("name").toString().split(';');
//    QFormLayout* layout = new QFormLayout(&setDlg);
//    const char* pins[] = {"J5.5", "J5.9", "J5.11", "J5.10", "J5.8", "J5.6", "J5.4", "J5.13*"};
//    funitBox->addItems(QStringList() << "Hz" << "KHz" << "MHz" << "GHz");
//    funitBox->setCurrentText(sobject()->property("frequency_unit").toString());
//    layout->addRow(tr("Frequency unit"), funitBox);
//    for(index = 0; index < 8; index++){
//        edits[index] = new QLineEdit(names.at(index));
//        layout->addRow(tr("PWM%1(%2)").arg(index).arg(pins[index]), edits[index]);
//    }
//    button[0] = new QPushButton(tr("OK"), &setDlg);
//    button[1] = new QPushButton(tr("Cancel"), &setDlg);
//    connect(button[0], SIGNAL(released()), &setDlg, SLOT(accept()));
//    connect(button[1], SIGNAL(released()), &setDlg, SLOT(close()));
//    layout->addRow(button[0], button[1]);
//    if(setDlg.exec() != QDialog::Accepted)
//        return;
//    names.clear();
//    for(index = 0; index < 8; index++){
//        names.append(edits[index]->text());
//    }
//    sobject()->setProperty("name", names.join(';'));
//    QString funit = funitBox->currentText();
//    if(funit.compare(sobject()->property("frequency_unit").toString(), Qt::CaseInsensitive) != 0)
//        sobject()->setProperty("frequency_unit", funit);
//}

//void sPwmCCS::saveParameter(int row, int column)
//{
//    sobject()->QObject::setProperty("parameter", getParameter());
//}

QString sPwmCCS::getParameter()
{
    QString forBack;
    for(int index = 0; index < 8; index++){
        for(int nColumn= 1; nColumn< 6;nColumn++){
            if(m_pwmTable->item(index, nColumn) == NULL)
                m_pwmTable->setItem(index, nColumn, new QTableWidgetItem());
            if(nColumn== 5)
                forBack += m_pwmTable->item(index, nColumn)->text()+";";
            else
                forBack += m_pwmTable->item(index, nColumn)->text()+",";
        }
    }
    return forBack;
}

bool sPwmCCS::setParameter(QString parameter)
{
    QStringList tmpList=  parameter.split(";");
    if(tmpList.size()< 8)
        return false;
    int row= 0;
    foreach (QString tmpString, tmpList) {
        QStringList commaList = tmpString.split(",");
        if(commaList.size()!= 5)
            return false;
        int column= 1;
        foreach (QString commaString, commaList){
            m_pwmTable->item(row, column++)->setText(commaString);
        }
        row++;
    }
    return true;
}

bool sPwmCCS::createPWM(ParamCCS::PWM_GENETATE& pPWM_GENETATE)
{
    QTableWidgetItem* twItem;
    auto fGetItem = [&](int row, int col) -> QVariant{
        if((twItem = m_pwmTable->item(row, col)) == NULL)
            return 0;
        return twItem->data(Qt::EditRole);
    };
    //ParamCCS::PWM_GENETATE tmpPWM_GENETATE;
    pPWM_GENETATE.lPWMEnable=0x07;//0xff;
    double frequency, dutyCycle, delay, funit;
    for(int index = 0; index < 8; index++){
        frequency = fGetItem(index, 1).toDouble();
        dutyCycle = fGetItem(index, 2).toDouble();
        delay = fGetItem(index, 3).toDouble();
        funit = freuencyUnit();
        //sysFreq = sysFrequency();
        pPWM_GENETATE.lPWMCycle[index] = uint(sysFrequency() / (frequency * funit));//period
        pPWM_GENETATE.lPWMUp[index] = uint(delay * pPWM_GENETATE.lPWMCycle[index] / 100);//hstart
        pPWM_GENETATE.lPWMDown[index] = pPWM_GENETATE.lPWMUp[index]
                + uint(dutyCycle * pPWM_GENETATE.lPWMCycle[index] / 100);//hend
    }
    return true;
}

QByteArray sPwmCCS::createPWM()
{
    QByteArray tmpCMD;
    int index;
    QTableWidgetItem* twItem;
    auto fGetItem = [&](int row, int col) -> QVariant{
        if((twItem = m_pwmTable->item(row, col)) == NULL)
            return 0;
        return twItem->data(Qt::EditRole);
    };
    ParamCCS::PWM_GENETATE tmpPWM_GENETATE;
    tmpPWM_GENETATE.lPWMEnable=0x07;//0xff;
    double frequency, dutyCycle, delay, funit;
    for(index = 0; index < 8; index++){
        frequency = fGetItem(index, 1).toDouble();
        dutyCycle = fGetItem(index, 2).toDouble();
        delay = fGetItem(index, 3).toDouble();
        funit = freuencyUnit();
        //sysFreq = sysFrequency();
        tmpPWM_GENETATE.lPWMCycle[index] = uint(sysFrequency() / (frequency * funit));//period
        tmpPWM_GENETATE.lPWMUp[index] = uint(delay * tmpPWM_GENETATE.lPWMCycle[index] / 100);//hstart
        tmpPWM_GENETATE.lPWMDown[index] = tmpPWM_GENETATE.lPWMUp[index]
                + uint(dutyCycle * tmpPWM_GENETATE.lPWMCycle[index] / 100);//hend
    }
    QVector<UINT> tmpBuffer;
    ParamCCS::generaterPWM(tmpBuffer,tmpPWM_GENETATE);
    if(tmpBuffer.size()>0){
        tmpCMD.resize(tmpBuffer.size()* sizeof(UINT));
        int size = tmpCMD.size();
        memcpy(tmpCMD.data(), tmpBuffer.data(), tmpCMD.size());
    }
    return tmpCMD;
}

void sPwmCCS::apply()
{
    if(isOver){
        isOver=false;
        QString path= QCoreApplication::applicationDirPath()+"/system.ini";
        QSettings configIniWrite(path, QSettings::IniFormat);

        QString strParam= getParameter();
        if(!strParam.isEmpty())
            configIniWrite.setValue("/System/ParameterPWM", strParam);

        strParam= getName();
        if(!strParam.isEmpty())
            configIniWrite.setValue("/System/NamePWM", strParam);
        tmpW= createPWM();
        if(tmpW.size()>0){
//            if(writeForBack(tmpW, "DataOut", tmpR, "DataIn")== 0){
//                qDebug()<<"N_CCSPWMWidget_apply";
//            }else{
//                qDebug()<<"E_CCSPWMWidget_apply";
//            }
        }
        isOver=true;
    }
}

//void sPwmCCS::contextMenuEvent(QContextMenuEvent *event)
//{
//    QMenu menu(this);
//    menu.addAction(tr("Settings"), this, SLOT(setting(bool)));
//    menu.exec(event->globalPos());
//}
