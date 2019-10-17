#include "sTICList.h"
#include "ui_sTICList.h"
#include <QDebug>
#include <QStringList>


sTICList::sTICList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sTICList)
{
    ui->setupUi(this);
    ui->lineEdit->setProperty("special",true);
    selectTool = new ColorSelectTool();

    this->setStyleSheet("QListWidget{border: 1px solid #000000; border-radius: 2px;}");
    connect(ui->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(onClicked(QListWidgetItem*)));
}

sTICList::~sTICList()
{
    delete ui;
}

void sTICList::modifyList()
{
    QString strTemp,strParam="0.5/";
    if(ItemList.size() != 0){
        int nRow = 0;
        strParam += "0:"+ItemList[nRow].first->getLineEdit()+strTemp.sprintf(":%X:1:0",
                                    ItemList[nRow].first->getColor().rgba());
        for(++nRow; nRow < ui->listWidget->count(); ++nRow){
            strParam += "@0:"+ItemList[nRow].first->getLineEdit()+ strTemp.sprintf(":%X:1:0",
                                        ItemList[nRow].first->getColor().rgba());
        }
    }
    emit ChangedManager(strParam, true);
}

void sTICList::on_BtnAdd_clicked()
{
    if(ItemList.size() > 6)
        return;
    QString text = ui->lineEdit->text();
    if(text.isEmpty())
        return;
    ui->lineEdit->clear();
    ListItem* widget = new ListItem();
    widget->setLineEdit(text);
    QColor color = selectTool->getColor();
    widget->setColor(color);

    emit MassWidgetAddLine(text.toDouble(),color);

    QListWidgetItem *item = new QListWidgetItem();
    item->setFlags(item->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
    QSize size = item->sizeHint();
    item->setSizeHint(QSize(size.width(), 35));
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item,widget);
    QPair<ListItem*,QListWidgetItem*> temp;
    temp.first = widget;
    temp.second = item;
    ItemList.append(temp);

    connect(widget,SIGNAL(itemRemove(ListItem*)),this,SLOT(on_ItemRemove(ListItem*)));
    connect(widget,SIGNAL(itemChecked(ListItem*,bool)),this,SLOT(on_ItemChecked(ListItem*,bool)));

    modifyList();
}


void sTICList::on_ItemRemove(ListItem *item)
{
    for(QList<QPair<ListItem*,QListWidgetItem*>>::iterator it = ItemList.begin(); it != ItemList.end();it++){
        if((*it).first == item){
            ui->listWidget->removeItemWidget((*it).second);

            QString massNum = (*it).first->getLineEdit();
            emit itemRemove(massNum.toDouble());
            selectTool->reInitColor((*it).first->getColor());

            qDebug() << "删除质量数为：" << massNum;

            delete (*it).second;
            delete (*it).first;
            ItemList.removeOne((*it));
            break;
        }
    }
    modifyList();
}

void sTICList::on_ItemChecked(ListItem *item, bool state)
{
    for(QList<QPair<ListItem*,QListWidgetItem*>>::iterator it = ItemList.begin(); it != ItemList.end();it++){
        if((*it).first == item){

            QString massNum = (*it).first->getLineEdit();
            //emit itemChecked(massNum,state);
            emit HideXIC(0, massNum, state);
            qDebug() << "质量数为： " << massNum << "状态为：" << state;

            return;
        }
    }
}

void sTICList::on_checkBox_stateChanged(int arg1)
{
    if(ItemList.isEmpty())
        return;
    for(QList<QPair<ListItem*,QListWidgetItem*>>::iterator it = ItemList.begin(); it != ItemList.end();it++)
    {
        if(ui->checkBox->checkState()){
            (*it).first->setCheckBox(true);
        }else{
            (*it).first->setCheckBox(false);
        }
    }
}

void sTICList::onClicked(QListWidgetItem *index)
{
    for(QList<QPair<ListItem*,QListWidgetItem*>>::iterator it = ItemList.begin(); it != ItemList.end();it++)
    {
        if(index == (*it).second){
            if((*it).first->getCheckBoxState()){
                (*it).first->setCheckBox(false);
            }else{
                (*it).first->setCheckBox(true);
            }
        }
    }
}


