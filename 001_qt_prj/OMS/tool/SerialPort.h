#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QtSerialPort\qserialport.h>
#include <QtSerialPort\qserialportinfo.h>
#include <QTimer>
#include <QMutex>

class SerialPort : public QObject
{
    Q_OBJECT
public:
    explicit SerialPort(QObject *parent = nullptr);
    ~SerialPort();

    void writeData(const QByteArray byte);
    void initPort();

private:
    QSerialPort* serial;
    QSerialPortInfo* serialInfo;
    QTimer* timer;
    bool flag = false;

signals:
    void getData(QByteArray byte);

    void loseSSC();

public slots:
    void onReadReady();
    void onTimeout();
    void onErrorOccurred(QSerialPort::SerialPortError error);
};

#endif // SERIALPORT_H
