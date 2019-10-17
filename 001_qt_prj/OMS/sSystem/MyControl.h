#ifndef MYCONTROL_H
#define MYCONTROL_H

#include <QWidget>
#include "sControlSSC.h"
#include <QTimer>

namespace Ui {
class MyControl;
}

class MyControl : public QWidget
{
    Q_OBJECT

public:

    enum STATE_VACUUM{STATE_OPENALL,STATE_ONLYMACH,STATE_CLOSE};
    explicit MyControl(QWidget *parent = 0);
    ~MyControl();
    void setState(bool state);
    void setAllEnabled(bool state);
    void initWidget();
    void setFilePath(QString path) { filePath = path; }
    bool getHState();
    void getAllState();
    void setPositive(int state);
    void setMachPump(bool state);
    void setFPump(bool state);
    void setGain(bool state);
    void setMinMachPump(bool state);
    bool getTState();
    void initState(STATE_VACUUM state);

private:
    Ui::MyControl *ui;
    QString style;

    QString filePath;

    sControlSSC::_CMD_SSC_SET temp_CMD_SSC;

    int isPositive = 1;
    int isMachPump = 0;  //机械泵使能信号
    int isFpump = 0;  //分子泵使能开关
    int isGain = 1;   //增益器切换开关
    int isMinMachPump = 0;   //小机械泵使能开关
    int isHVHF = 0;     //HVHF使能开关
    QTimer timer;

signals:
    void systemStateChange();
    void sendAllState(sControlSSC::_CMD_SSC_SET&);

public slots:
    void onStateChange();
    void onControlChanged();
    void onTimeOut();
};

#endif // MYCONTROL_H
