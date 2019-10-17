#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QWidget>
#include <QLineEdit>
#include <QEvent>

class myLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit myLineEdit(QWidget *parent = nullptr);

    ~myLineEdit() { }

    void setRange(int min,int max);
    int* getRange() { return range;}

signals:
    void tipSend(int min,int max);

public slots:


protected:
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);

private:
    int range[2];
};

#endif // MYLINEEDIT_H
