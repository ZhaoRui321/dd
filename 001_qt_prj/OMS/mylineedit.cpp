#include "myLineEdit.h"
#include <QDoubleValidator>

myLineEdit::myLineEdit(QWidget *parent)
    :QLineEdit(parent)
{
    range[0] = -99999;
    range[1] = 99999;
    this->setValidator(new QDoubleValidator(range[0],range[1],2,this));
}

void myLineEdit::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);
    this->selectAll();
    emit tipSend(range[0],range[1]);  
}

void myLineEdit::setRange(int min, int max)
{
    range[0] = min;
    range[1] = max;

    this->setValidator(new QIntValidator(min,max,this));
}

void myLineEdit::focusOutEvent(QFocusEvent *event)
{
    QLineEdit::focusOutEvent(event);
    if(this->text().isEmpty())
        this->setText("0");
}

