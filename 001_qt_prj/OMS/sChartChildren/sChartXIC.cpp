#include "sChartXIC.h"
#include "ui_sChartXIC.h"
#include <QColorDialog>

sChartXIC::sChartXIC(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sChartXIC)
{
    ui->setupUi(this);
    mManagerXIC= new sManagerXIC(this);
    ui->verticalLayout_3->addWidget(mManagerXIC);
    mManagerXIC->hide();
    connect(mManagerXIC, SIGNAL(B_clicked(QListWidgetItem*, bool)), SLOT(on_Manager_clicked(QListWidgetItem*, bool )));
    mXIC="5/";
}

sChartXIC::~sChartXIC()
{
    delete ui;
}
/**
 * @brief sChartXIC::setParam
 * @param pXics
 */

bool sChartXIC::setParam(QString str)
{
    QStringList strList=str.split('/');
    if(strList.size()!= 2){
        ui->listWidget->clear();
        return false;
    }
    mXIC= str;
    double mXicOffset= strList[0].toDouble();
    if(mXicOffset< 0)
        return false;
    setParam(sChartXIC::_XIC_STEP, strList[0]);
    setParam(sChartXIC::_XIC_STRUCT, strList[1]);
    return true;
}

void sChartXIC::setParam(_XIC_PARAM name,QString str)
{
    if (name== _XIC_STEP) {
        ui->lineEdit->setText(str);
    }else if(name== _XIC_STRUCT){
        ui->listWidget->clear();
        QStringList strList= str.split("@");
        QStringList tmpList;
        foreach (auto tmpStr, strList) {
            tmpList= tmpStr.split(":");
            if(tmpList.size()!=5)
                continue;

            _TEMP_XIC tmpPARAM_XIC;
            tmpPARAM_XIC.nEvent   = tmpList[0].toInt();
            tmpPARAM_XIC.mass     = tmpList[1];
            tmpPARAM_XIC.color    = QColor(QRgb(tmpList[2].toUInt(NULL, 16)));
            tmpPARAM_XIC.Gain     = tmpList[3].toDouble();
            tmpPARAM_XIC.Offset   = tmpList[4].toDouble();

            QPixmap pix(50, 50);
            pix.fill(tmpPARAM_XIC.color);
            QListWidgetItem* pItem = new QListWidgetItem(QIcon(pix), QString("Event:%1,Mass:%2,Gain:%3,Offset:%4")
                                                         .arg(tmpPARAM_XIC.nEvent).arg(tmpPARAM_XIC.mass)
                                                         .arg(tmpPARAM_XIC.Gain).arg(tmpPARAM_XIC.Offset), ui->listWidget);
            pItem->setData(Qt::UserRole, tmpPARAM_XIC.nEvent);
            pItem->setData(Qt::UserRole + 1, tmpPARAM_XIC.mass.toDouble());
            pItem->setData(Qt::UserRole + 2, tmpPARAM_XIC.color.rgba());
            pItem->setData(Qt::UserRole + 3, tmpPARAM_XIC.Gain);
            pItem->setData(Qt::UserRole + 4, tmpPARAM_XIC.Offset);
            ui->listWidget->addItem(pItem);
        }
    }
}
/**
 * @brief sChartXIC::addXic
 * @param pManagerXIC
 */
void sChartXIC::addXic(sManagerXIC* pManagerXIC)
{
    if(pManagerXIC){
        QListWidgetItem* pItem = new QListWidgetItem(ui->listWidget);
        pItem->setData(sManagerXIC::_MANAGE_Type,    sManagerXIC::_MANAGE_ADD);
        pItem->setData(sManagerXIC::_MANAGE_Event,   0);
        pItem->setData(sManagerXIC::_MANAGE_Mass,    0);
        pItem->setData(sManagerXIC::_MANAGE_Color,   QColor(Qt::red).rgba());
        pItem->setData(sManagerXIC::_MANAGE_Gain,    1);
        pItem->setData(sManagerXIC::_MANAGE_Offset,  0);
        pManagerXIC->setXic(pItem);
    }
}
/**
 * @brief sChartXIC::ModifyXic
 * @param pManagerXIC
 */
void sChartXIC::ModifyXic(sManagerXIC* pManagerXIC)
{
    if(pManagerXIC){
        QListWidgetItem* pItem = ui->listWidget->currentItem();
        if(pItem){
            pItem->setData(sManagerXIC::_MANAGE_Type,    sManagerXIC::_MANAGE_MODIFY);
            pManagerXIC->setXic(pItem);
        }
    }
    return;
}
/**
 * @brief sChartXIC::removeXic
 */
void sChartXIC::removeXic()
{
    QListWidgetItem* pItem = ui->listWidget->currentItem();
    if(pItem){
        ui->listWidget->removeItemWidget(pItem);
        delete pItem;
    }
}
/**
 * @brief sChartXIC::on_B_OK_clicked
 */
void sChartXIC::on_B_OK_clicked()
{
    QString strTemp,strParam=ui->lineEdit->text()+'/';
    if(ui->listWidget->count() != 0){
        int nRow = 0;
        QListWidgetItem* pItem = ui->listWidget->item(nRow++);
        strParam += strTemp.sprintf("%d:%f:%X:%f:%f",pItem->data(sManagerXIC::_MANAGE_Event).toInt(),
                         pItem->data(sManagerXIC::_MANAGE_Mass).toDouble(),
                         pItem->data(sManagerXIC::_MANAGE_Color).toUInt(),
                         pItem->data(sManagerXIC::_MANAGE_Gain).toDouble(),
                         pItem->data(sManagerXIC::_MANAGE_Offset).toDouble());
        for(; nRow < ui->listWidget->count(); nRow++){
            pItem = ui->listWidget->item(nRow);
            strParam += strTemp.sprintf("@%d:%f:%X:%f:%f",pItem->data(sManagerXIC::_MANAGE_Event).toInt(),
                                        pItem->data(sManagerXIC::_MANAGE_Mass).toDouble(),
                                        pItem->data(sManagerXIC::_MANAGE_Color).toUInt(),
                                        pItem->data(sManagerXIC::_MANAGE_Gain).toDouble(),
                                        pItem->data(sManagerXIC::_MANAGE_Offset).toDouble());
        }
    }
    mXIC= strParam;
    emit ChangedManager(strParam, true);
}

void sChartXIC::on_B_Cancel_clicked()
{
    setParam(mXIC);
    emit ChangedManager("", false);
}
/**
 * @brief sChartXIC::ParamShow
 * @param pItem
 */
void sChartXIC::ParamShow(QListWidgetItem* pItem)
{
    if(pItem){
        double dbMass = pItem->data(sManagerXIC::_MANAGE_Mass).toDouble(),
                dbGain= pItem->data(sManagerXIC::_MANAGE_Gain).toDouble(),
                dbOffset= pItem->data(sManagerXIC::_MANAGE_Offset).toDouble();
        int nEvent=pItem->data(sManagerXIC::_MANAGE_Event).toInt();
        QColor clr(pItem->data(sManagerXIC::_MANAGE_Color).toUInt());
        QPixmap pix(50, 50);
        pix.fill(clr);
        pItem->setIcon(QIcon(pix));
        pItem->setText(QString("Event:%1,Mass:%2,Gain:%3,Offset:%4")
                       .arg(nEvent).arg(dbMass).arg(dbGain).arg(dbOffset));
    }
}

void sChartXIC::on_B_Add_clicked()
{
    ui->widget_2->hide();
    addXic(mManagerXIC);
    mManagerXIC->show();
}

void sChartXIC::on_B_Modify_clicked()
{
    ui->widget_2->hide();
    ModifyXic(mManagerXIC);
    mManagerXIC->show();
}

void sChartXIC::on_B_Remove_clicked()
{
    removeXic();
}

void sChartXIC::on_Manager_clicked(QListWidgetItem* pQListWidgetItem, bool isChanged)
{
    if(isChanged){
        mManagerXIC->getXic(pQListWidgetItem);
        ParamShow(pQListWidgetItem);
    }else{
        if(pQListWidgetItem->data(sManagerXIC::_MANAGE_Type)==sManagerXIC::_MANAGE_ADD){
            ui->listWidget->removeItemWidget(pQListWidgetItem);
            delete pQListWidgetItem;
            pQListWidgetItem=NULL;
        }
    }
    ui->widget_2->show();
    mManagerXIC->hide();
}
