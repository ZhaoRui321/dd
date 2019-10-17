#ifndef sControlSSC_H
#define sControlSSC_H
#include <QGridLayout>
//#include <ui/swidget.h>
//#include <QScriptEngine>
#include <QTableWidgetItem>
#include <QWidget>
#include "cParamCCS.h"
//#define DEBUG_TXT

#define TEMP_WIDTH 6
#define DAC_WIDTH_SET 8
#define DAC_WIDTH_GET 16

#define SIZE_CCS_BUFF 512
#define SIZE_SSC_BUFF 64
namespace Ui {
class sControlSSC;
}

class sControlSSC:public QWidget
{
    Q_OBJECT
public:
    struct _UART_SSC{
        uint baudrate;
        uint uartTxBytes;
    }mUART_SSC;

    struct _CMD_SSC_SET{
        int Value_TEMP[TEMP_WIDTH] = {0};
        unsigned char Value_PID[18] = {0};
        double Value_DAC[DAC_WIDTH_SET] = {0.0};
        quint16 enableIO[12]={0,0,0,0,0,0,0,0,0,0,0,0};
        //DYNODE极性，DYNODE使能开关，ESI极性，ESI使能开关，机械泵使能，SEM,gain,分子泵,温度,HVHF使能，小机械泵使能
    };

    struct _CMD_SSC_REQ{
        int Value_TEMP[TEMP_WIDTH];
        int Value_DAC[DAC_WIDTH_GET];
    }mCMD_SSC_REQ;

    ParamCCS::_STATE_REQUEST_CCS mSTATE_REQUEST_CCS;
    explicit sControlSSC(QWidget *parent = 0);
    ~sControlSSC();
    QByteArray createConfig();
    QByteArray createRequest();
    QByteArray createElecPumpOn();
    QByteArray createElecPumpOff();
    QString getParameter();
    bool setParameter(QString parameter);
    static QByteArray createSSC_CMD();
    void showSSC(QByteArray& pArray);
    bool updateSwitch(QString name, QString value);

private slots:
    void on_B_Update_clicked();
    void onTempSetChanged(int row, int column);
    void onCCSChanged(int row, int column);
    void onDacSetChanged(int row, int column);
    void onTempGetChanged(int row, int column);
    void onADC1Changed(int row, int column);
    void onADC2Changed(int row, int column);
    void on_UI_PB_IO0_clicked();
    void on_UI_PB_IO1_clicked();
    void on_UI_PB_IO2_clicked();
    void on_UI_PB_IO3_clicked();
    void on_UI_PB_IO4_clicked();
    void on_UI_PB_IO5_clicked();
    void on_UI_PB_IO6_clicked();
    void on_UI_PB_IO7_clicked();
    void onSendAllState(sControlSSC::_CMD_SSC_SET& contain);

private:
    Ui::sControlSSC *ui;
    QObject* sobject(){return this;}
    //QScriptEngine* m_engine=nullptr;

    void exportCmdTxt(const uint *cmd, uint size, const QString &fileName);
    //bool analysisConfig(QByteArray tmpR);
    QString useScript(QString valueStr,QString scriptStr, QString value);
    QString getParameter(QTableWidget* pQTableWidget);
    void initTable();
    static void initSObject(QObject *pObj);
    void setSObject(QObject* obj);
    bool ParamDown(_CMD_SSC_SET &tempCMD_SSC_SET);
    bool ParamUp();

};

#endif // sControlSSC_H
