#ifndef SSYSTEMSTATE_H
#define SSYSTEMSTATE_H

#include <QWidget>

namespace Ui {
class sSystemState;
}

class sSystemState : public QWidget
{
    Q_OBJECT

public:
    explicit sSystemState(QWidget *parent = 0);
    ~sSystemState();
    void showDrive(QByteArray& pArray);
    void showRotatinSpeed(QByteArray& pArray);
private:
    Ui::sSystemState *ui;
};

#endif // SSYSTEMSTATE_H
