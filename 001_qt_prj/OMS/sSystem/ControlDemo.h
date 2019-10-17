#ifndef CONTROLDEMO_H
#define CONTROLDEMO_H

#include <QWidget>
#include <QPaintEvent>
namespace Ui {
class ControlDemo;
}

class ControlDemo : public QWidget
{
    Q_OBJECT

public:
    explicit ControlDemo(QWidget *parent = 0);
    ~ControlDemo();

    void setTitle(QString str);
    void setLineEdit(QString num);
    int getState();
    void setState(bool state);
    void setAllEnabled(bool state);
    QString getValue();
    void setDescription(QString str);
    void setEnabled(bool state);
    void setRangeInput(const double minvalue,const double maxvalue)
    {
        rangeInput[0] = minvalue;
        rangeInput[1] = maxvalue;
    }

signals:
    void stateChange();
    void controlChanged();

protected:
    void paintEvent(QPaintEvent* e);

private:
    Ui::ControlDemo *ui;
    double rangeInput[2] = {-999999,999999};


public slots:
    void on_clicked();
    void on_LineEditChanged(QString text);
};

#endif // CONTROLDEMO_H
