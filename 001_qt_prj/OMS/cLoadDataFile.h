#ifndef CLOADDATAFILE_H
#define CLOADDATAFILE_H
#include <QFile>
#include <QString>
#include <QVector>
#include "cPublicCCS.h"
#include <QObject>

class cLoadDataFile
{
public:
    cLoadDataFile();
    bool loadFileTIC(const char* pFilePath, const int lengthPath,
                                    double** pDataTIC, long& lengthTIC,
                                    double** pDataMass, long& lengthMass);
    bool loadFileTIC(QString pFilePath, QVector<double> &pDataTIC_X, QVector<double> &pDataTIC_Y);
    bool loadFileTIC(QString pFilePath, std::vector<double> &pDataTIC_X, std::vector<double> &pDataTIC_Y);
    bool loadFileMass(QString pFilePath,int index, QVector<double>& pData,QByteArray& pStreamHead);
    bool loadFileMass(QString pFilePath, int index, std::vector<double>& pData,QByteArray& pStreamHead);
    //棒图
    bool loadFileMass(QString pFilePath, int index, std::vector<double>& xData, std::vector<double>& yData, QByteArray& pStreamHead);
    bool loadFileMass(QString pFilePath, int nFrameB, int nFrameE, std::vector<double>& pData,QByteArray& pStreamHead);
    bool loadFileMassInX(QString pFilePath, int indexX, std::vector<double>& pData, QByteArray& pStreamHead);
    //棒图TIC
    bool loadFileMassInX(QString pFilePath, double mass, std::vector<double>& pData, QByteArray& pStreamHead);
    bool loadFileMassInX(QString pFilePath, double mass, int indexX, std::vector<double>& pData, QByteArray& pStreamHead);

    //写入文件夹
    bool createDataFile(QByteArray tempHead){
        mFileHead = tempHead;
        QString fileName=createFileTIC();
        if(!fileName.isEmpty())
            if(!createFileMass(fileName).isEmpty())
                return true;
        return false;
    }

    void saveDataTIC(QString data);
    bool saveDataMass(QByteArray& pData);
    bool saveDataMass(char* pData,qint64 nLength);
    bool saveDataMass(std::vector<double> xData, std::vector<double> yData);
    bool saveDataMass(std::vector<double> yData);
    void closeFileTIC();
    void closeFileMass();

    void renameFile(char* pName,int lengthName);
    void renameFile(QString fileName);

private: 
    QFile* mDataFileMass= nullptr;
    QFile* mDataFileTIC= nullptr;

    QByteArray mFileName;
    QByteArray mFileHead;

    QByteArray mDataTIC;
    QVector<double> mDataTIC_X;
    QVector<double> mDataTIC_Y;
    //QByteArray mDataMass;

    QString createFileTIC(QString fileName= QString());
    QString createFileMass(QString fileName= QString());
};

#endif // CLOADDATAFILE_H
