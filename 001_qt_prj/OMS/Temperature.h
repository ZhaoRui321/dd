#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <QWidget>

namespace Ui {
class Temperature;
}

class Temperature : public QWidget
{
    Q_OBJECT

public:
    explicit Temperature(QWidget *parent = 0);
    ~Temperature();

private:
    Ui::Temperature *ui;
    QString SliderStyle;
};

#endif // TEMPERATURE_H
