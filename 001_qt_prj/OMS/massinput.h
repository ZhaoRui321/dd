#ifndef MASSINPUT_H
#define MASSINPUT_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class MassInput;
}

class MassInput : public QWidget
{
    Q_OBJECT

public:
    explicit MassInput(QWidget *parent = 0);
    ~MassInput();
    double getMassNum();

private:
    Ui::MassInput *ui;

protected:
    void paintEvent(QPaintEvent* e);
    void mousePressEvent(QMouseEvent* e);
};

#endif // MASSINPUT_H
