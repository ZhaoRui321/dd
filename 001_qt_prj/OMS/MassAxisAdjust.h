#ifndef MASSAXISADJUST_H
#define MASSAXISADJUST_H

#include <QWidget>
#define Number 1e-13
#define CONFIGPATH "./PTMSCONFIG.ini"
#include <QSettings>

namespace Ui {
class MassAxisAdjust;
}

struct Mass_axis_factor{
    double factor[3] = {0.0, 1.0 , 0.0};
};

class MassAxisAdjust : public QWidget
{
    Q_OBJECT
public:
    explicit MassAxisAdjust(QWidget *parent = 0);
    ~MassAxisAdjust();
    void initFactor();
    void autoAdjust();
    bool adjustProcess(std::vector<double> &dataSrc,std::vector<double> &dataDest);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MassAxisAdjust *ui;
    Mass_axis_factor massAxis;
    std::vector<double> adjustValueX;
};

#endif // MASSAXISADJUST_H
