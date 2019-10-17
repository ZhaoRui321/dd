#include "myGroupBox.h"
#include <QVBoxLayout>

myGroupBox::myGroupBox(QWidget *parent) : QGroupBox(parent)
{
    this->setCheckable(true);
    this->setChecked(true);
    myLabel = new QLabel();
    myPushButton = new QPushButton();
    myPushButton->setText("删除");
    QVBoxLayout* vbox = new QVBoxLayout();
    vbox->addWidget(myLabel);
    vbox->addWidget(myPushButton);
    this->setLayout(vbox);
    //connect(this,SIGNAL(clicked(bool)),this,SLOT(onClicked(bool)));
    connect(myPushButton,SIGNAL(clicked(bool)),this,SLOT(onBtnClicked(bool)));
}


void myGroupBox::setColor(QColor color)
{
    this->color = color;
    QString style = QString("QGroupBox{"
                            "border-width:1px;"
                            "border-style:solid;"
                            "border-color:%1}").arg(color.name());
    this->setStyleSheet(style);
}

void myGroupBox::setContainer(QString str)
{
    myLabel->setText(str);
}

void myGroupBox::setState(bool state)
{
    this->setChecked(state);
}

void myGroupBox::onBtnClicked(bool state)
{
    emit groupBoxRemoved(this);
    delete this;
}

void myGroupBox::onClicked(bool state)
{
    emit groupBoxClicked(this,state);
}

void myGroupBox::mousePressEvent(QMouseEvent *event)
{
    bool state = this->isChecked();
    setState(!state);
    emit groupBoxClicked(this,!state);
    //QGroupBox::mousePressEvent(event);
}
