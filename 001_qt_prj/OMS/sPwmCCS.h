#ifndef sPwmCCS_H
#define sPwmCCS_H
//#include <ui/swidget.h>
#include "cParamCCS.h"
#include <QPushButton>
#include <QTableWidget>

/**
 * @brief The sPwmCCS class
 * 输出频率最大为50M方波
 */

class sPwmCCS : public QWidget
{
    Q_OBJECT
    QTableWidget* m_pwmTable = NULL;
    QPushButton* m_applyButton = NULL;
public:
    sPwmCCS(QWidget *parent);
    QString getName();
    void setName(QString name);

    double freuencyUnit();
    uint sysFrequency(){
        return 100000000;
    }
    QString getParameter();
    bool setParameter(QString parameter);
    bool createPWM(ParamCCS::PWM_GENETATE& pPWM_GENETATE);
    QByteArray createPWM();
    //void propertyOfSObjectChanged(SObject* pObj, const QString& strPropName, const SObject::PropertyT& propChangedBy) override;
    //static QString keyString();
    //static void initSObject(SObject *pObj);
public slots:
    //void setting(bool);
    void apply();
    //void saveParameter(int, int);
//protected:
//    void contextMenuEvent(QContextMenuEvent * event);
private:
    void initPWMTable();

    QByteArray tmpW, tmpR;
    volatile bool isOver= true;
};

#endif // sPwmCCS_H
