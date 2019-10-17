#include "SerialPort.h"
#include <QDebug>

SerialPort::SerialPort(QObject *parent)
    : QObject(parent)
{
    serial = new QSerialPort();
    initPort();
    timer = new QTimer(this);
    timer->start(5000);

    connect(timer,SIGNAL(timeout()),this,SLOT(onTimeout()));
    connect(serial,SIGNAL(readyRead()),this,SLOT(onReadReady()));
    connect(serial,SIGNAL(errorOccurred(QSerialPort::SerialPortError)),this,SLOT(onErrorOccurred(QSerialPort::SerialPortError)));
}

SerialPort::~SerialPort()
{
    delete serial;
    delete serialInfo;
    delete timer;
}

void SerialPort::initPort()
{
    QString portName = "";
    if(serial->isOpen())
        return;
    else
        flag = false;

    foreach (QSerialPortInfo info, QSerialPortInfo::availablePorts())
    {
        serialInfo = nullptr;
        //qDebug() << info.description();
        if(info.description() == tr("Silicon Labs CP210x USB to UART Bridge"))//tr("USB Serial Port"))//
        {
            serialInfo = new QSerialPortInfo();
            serialInfo = &info;
            portName = serialInfo->portName();
        }
    }

    if(!portName.isEmpty())
    {
        if(flag)
            return;
        serial->setBaudRate(115200);
        serial->setPortName(portName);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);
        if(serial->open(QIODevice::ReadWrite)){
            qDebug() << "connect successful.................................................................";
            flag = true;
        }else{
            serial->close();
            flag = false;
        }
    }
    else
    {
       if(flag)
           qDebug() << "connect failed.....................................................................";
       flag = false;
       serial->close();
    }
}

void SerialPort::writeData(const QByteArray byte)
{
//    qDebug() << "send: ";
//    qDebug() << byte ;
    if(serial->isOpen())
        serial->write(byte);
    else{
        if(serial->open(QIODevice::ReadWrite))
            serial->write(byte);
        else
            ;
           // qDebug() << "serial port is close....";
    }
}

void SerialPort::onTimeout()
{
    initPort();
}

void SerialPort::onReadReady()
{
    QByteArray buf;
    buf = serial->readAll();
//    qDebug() << "accept: ";
//    qDebug() << buf;
    if(!buf.isEmpty())
    {
        getData(buf);
    }
    buf.clear();
}

void SerialPort::onErrorOccurred(QSerialPort::SerialPortError error)
{
    if(error == QSerialPort::DeviceNotFoundError)
        emit loseSSC();
}
