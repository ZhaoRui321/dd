#ifndef ALLSCAN_H
#define ALLSCAN_H

#include <QWidget>
#include <QPushButton>
#include "DoubleSlider.h"
#include "OneSlider.h"

namespace Ui {
class AllScan;
}

class AllScan : public QWidget
{
    Q_OBJECT

public:
    explicit AllScan(QWidget *parent = 0);
    ~AllScan();

    void bigMassModel();
    void smallMassModel();
    void normalModel();
    double getStartMass();
    double getEndMass();
    double getSpeed();

private slots:
    void on_bigModelBtn_clicked();

    void on_smallModelBtn_clicked();

    void on_userModelBtn_clicked();
    void on_minValueChanged(float);
    void on_MaxValueChanged(float);
    void onSpeedValueChange(float);

private:
    Ui::AllScan *ui;
    DoubleSlider *doubleSlider;
    OneSlider *oneSlider;
    QString style1;
    QString style2;
    int bigMethod[3] = {50,120,20};
    int smallMethod[3] = {10,80,30};
    int normalMethod[3] = {10,100,20};

    float startMass,endMass,speed;

protected:

    //void paintEvent(QPaintEvent*);
};

#endif // ALLSCAN_H
