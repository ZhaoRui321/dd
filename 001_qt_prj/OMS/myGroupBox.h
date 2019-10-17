#ifndef MYGROUPBOX_H
#define MYGROUPBOX_H

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>

class myGroupBox : public QGroupBox
{
    Q_OBJECT
public:
    explicit myGroupBox(QWidget *parent = nullptr);
    QColor getColor() {return color;}
    void setColor(QColor color);
    void setContainer(QString str);
    void setState(bool state);

signals:
    void groupBoxRemoved(myGroupBox*);
    void groupBoxClicked(myGroupBox*,bool);

private:
    QColor color;
    QLabel* myLabel;
    QPushButton* myPushButton;

protected:
    void mousePressEvent(QMouseEvent *event);

public slots:
    void onBtnClicked(bool state);
    void onClicked(bool);
};

#endif // MYGROUPBOX_H
