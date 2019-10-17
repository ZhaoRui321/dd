#include "qcalculatorui.h"

QCalculatorUI::QCalculatorUI() : QWidget(NULL,Qt::WindowCloseButtonHint)
{

}
bool QCalculatorUI::construct()
{
    bool ret = true;
    const char* btnText[20]={
        "7" ,"8" ,"9" ,"+" ,"(" ,
        "4" ,"5" ,"6" ,"-" ,")" ,
        "1" ,"2" ,"3" ,"*" ,"<-" ,
        "0" ,"." ,"=" ,"/" ,"C"
    };
    m_edit = new QLineEdit(this);

    if(m_edit != NULL)
    {
        m_edit->move(10,10);
        m_edit->resize(240,30);
        m_edit->setReadOnly(true);
    }
    else
    {
        ret = false;
    }

    for(int i= 0;i<4 && ret;i++)
    {
            for(int j=0;j<5 && ret;j++)
        {
            mbtn[i*5+j] = new QPushButton(this);
            if(mbtn[i*5+j] != NULL){
            mbtn[i*5+j]->resize(40,40);
            mbtn[i*5+j]->move(10+(10+40)*j,50+(10+40)*i);
            mbtn[i*5+j]->setText(btnText[i*5+j]);
            }
            else {
                ret = false;
            }
        }
    }

    return ret;
}
QCalculatorUI* QCalculatorUI::NewInstance()
{
    QCalculatorUI* ret = new QCalculatorUI();
    if(ret ==NULL || !ret->construct())
    {
        delete  ret;
        ret =NULL;
    }
    return  ret;
}
 void QCalculatorUI::show()
 {
     QWidget::show();
     this->setFixedSize(this->width(),this->height());
 }
QCalculatorUI::~QCalculatorUI()
{
    delete  m_edit;
    for(int i = 0; i<20 ;i++){
    delete  mbtn[i];
    }
}
