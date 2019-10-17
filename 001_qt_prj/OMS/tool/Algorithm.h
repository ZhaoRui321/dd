#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <QObject>

class Algorithm : public QObject
{
    Q_OBJECT
public:
    static Algorithm* getInstance();

    void setSpeed(const int speed);
    void setAcc(const int acc);
    void setFWHM(const double FWHM);
    void setWidth(const int width);
    void setFreq(const double freq);
    void setBaseLineOffset(const double offset);
    void setDataOffset(const double offset);
    int getSpeed();
    int getAcc();
    double getFWHM();
    int getWidth();
    int getFreq();
    double getBaseLineOffset();
    double getDataOffset();

    double sum();
    QVector<double> createCj();
    QVector<double> createCj2(QVector<double> data);

    void createDataCut(QVector<double> data);
    void createDataCut(std::vector<double> data);
    void process();

    int getResult(QVector<double>& pData , QVector<double>& oData, QVector<int> &pMask);
    int getResult(QVector<double> &pData , std::vector<double> &oData, QVector<int> &pMask);
private:
    class PrivateData;
    PrivateData* d_data;
    
    explicit Algorithm(QObject *parent = nullptr);
    static Algorithm* algo;

signals:

public slots:
};

#endif // ALGORITHM_H
