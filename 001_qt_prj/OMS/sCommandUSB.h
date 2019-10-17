#pragma once
#include "sCommandUSB/cCommunicationCMD.h"
#include "cPublicCCS.h"
#include <QTextStream>
/**
 * @brief The CommandUSB class
 * CCS,ASG,DAQ指令的封装，内含DAQ数据处理线程，getDataDAQ为数据提取接口
 */


class CommandUSB: public QObject
{
    Q_OBJECT
public:
    struct SFileHead{
        uint vid = 0; /**< TODO */
        uint pid = 0; /**< TODO */
        uint paramSize = 0; /**< TODO */
    };
    struct SDaqFileHead{
        uint accumulate; /**< TODO */
        uint framePoint; /**< TODO */
        double frequency; /**< TODO */
        double dateTime; /**< TODO */
        double massStart; /**< TODO */
        double massEnd; /**< TODO */
    };
    struct _DAQ_DATA{
        volatile uint nVersion= 0;
        QMutex qLock;
        QVector<double> pBuff;
    };
    CommandUSB(QObject *parent = 0);
    ~CommandUSB();
    void clearBuff(){
        mSampledData.qLock.lock();
        mSampledData.pBuff.clear();
        mSampledData.nVersion++;
        if(mSampledData.nVersion>40000)
            mSampledData.nVersion=1;
        mSampledData.qLock.unlock();
    }
    inline void setDataDAQ(QByteArray& srcData);
    int getDataDAQ(_DAQ_DATA* p_DAQ_DATA, bool always = false);
    int getDataDAQ(QByteArray& srcData, bool always = false);
    int getDataDAQ(std::vector<double>& srcData, bool always = false);
    int getDataDAQ(char** srcData, uint& nLength, bool always){
        int fReturn=getDataDAQ(mDaqData, always);
        *srcData= mDaqData.data();
        nLength= mDaqData.size()/sizeof(double);
        return fReturn;
    }
    void zeroVersion(){
        mSampledData.qLock.lock();
        mSampledData.nVersion= 0;
        mSampledData.qLock.unlock();
    }
#if 1
    void setFileHead(char* pHead, uint lengthHead){
        mFileHead.resize(lengthHead);
        memcpy(mFileHead.data(), pHead, lengthHead);
    }
    void setFileHeadFromFile(char* pHead, uint lengthHead){}
    bool createDataFile(){
        QString fileName=createFileTIC();
        if(!fileName.isEmpty())
            if(!createFileMass(fileName).isEmpty())
                return true;
        return false;
    }
    inline void saveDataTIC(QString data);
    bool saveDataMass(QByteArray& pData);
    inline bool saveDataMass(char* pData,qint64 nLength);
    void closeFileTIC();
    void closeFileMass();
    QByteArray getFileName(){
        return mFileName;
    }
    void getFileName(char** pName, int& lengthName){
        if(!mFileName.isEmpty()){
            //QByteArray tmpName= mFileName.toUtf8();
            *pName= mFileName.data();
            lengthName= mFileName.size();
        }else
            lengthName=0;
    }
    void renameFile(char* pName,int lengthName);
    void renameFile(QString fileName);
#endif
private:
    SThread mProcessThread;
    CommunicationCMD mCommunicationCMD;
    //QFile* mDataFile= nullptr;
#if 1
    QFile* mDataFileMass= nullptr;
    QFile* mDataFileTIC= nullptr;
    QTextStream* mStreamTIC= nullptr;
#endif
    QString save2File(QString rFileName="");
    int method2File(QFile* pFile, QString rFileName= "./tempMethodParam.dat");
    uint mVersionGet=1;
    _DAQ_DATA mSampledData;
    ParamCCS::_DAQ_CONFIG m_DAQ_CONFIG;
    static int processDataThread(void *pParam, const bool &bRunning);
    QByteArray mDaqData;
#if 1
    QByteArray mFileName;
    QByteArray mFileHead;
    QString createFileTIC(QString fileName= QString());//QString::null );20190305zhouxu
    QString createFileMass(QString fileName= QString());//QString::null );20190305zhouxu
    bool mSaveFile=false;
#endif
public:
    bool isRunningDAQ(){
        mProcessThread.isRunning();
    }

    bool isSaveFile(){
        return mSaveFile;
    }
    int safeCCS(){
        return mCommunicationCMD.safeCCS();
    }

    int scanCCS(char* pData, uint nLength){
        return mCommunicationCMD.scanCCS(pData, nLength);
    }
    int scanCCS(QByteArray pArrayCCS){
        return mCommunicationCMD.scanCCS(pArrayCCS);
    }
    int stopCCS(){
        return mCommunicationCMD.stopCCS();
    }
    int scanASG(char* pData, uint nLength){
        return mCommunicationCMD.scanASG(pData, nLength);
    }
    int scanASG(QByteArray pArrayASG){
        return mCommunicationCMD.scanASG(pArrayASG);
    }
    int stopASG(){
        return mCommunicationCMD.stopASG();
    }

    int startDAQ(ParamCCS::_DAQ_CONFIG& p_DAQ_CONFIG, bool saveFile=false){
        if(!mProcessThread.isRunning()){
            zeroVersion();
            memcpy(&m_DAQ_CONFIG, &p_DAQ_CONFIG, sizeof(ParamCCS::_DAQ_CONFIG));
            mSaveFile= saveFile;
            if(mCommunicationCMD.startDAQ(m_DAQ_CONFIG)== 0){
                mProcessThread.start();
                return 0;
            }
        }
        return -1;
    }

    int stopDAQ(){
        //mSaveFile= false;
        if(mProcessThread.isRunning()){
            mProcessThread.stop();
            mProcessThread.wait();
        }
        if(mCommunicationCMD.stopDAQ()== 0)
            return 0;
        else
            return -1;
    }

    int startPWM(ParamCCS::PWM_GENETATE pPWM_GENETATE){
        return mCommunicationCMD.startPWM(pPWM_GENETATE);
    }
    int sendCMD(const char* pW, const uint nW, char* const pR, const uint nR){
        return mCommunicationCMD.sendCMD(pW, nW, pR, nR);
    }
    int sendCMD(const QByteArray& pArrayCMD, QByteArray& pArrayBack, uint sizeBack= 512){
        return mCommunicationCMD.sendCMD(pArrayCMD, pArrayBack, sizeBack);
    }

signals:
    void currentFilePath(QString TICFile,QString MassFile,bool state);

public slots:
    void onShowCurrentFile(bool state);
};

class sCommandUSB{
public:
    static CommandUSB* getCommandUSB(){
        static sCommandUSB insmCommandUSB;
        return &(insmCommandUSB.mCommandUSB);
    }
private:
    CommandUSB mCommandUSB;
    sCommandUSB(){}
    virtual ~sCommandUSB(){}
    sCommandUSB(const sCommandUSB&){}
    sCommandUSB& operator=(const sCommandUSB&){
        static sCommandUSB insCommandUSB;
        return insCommandUSB;
    }
};
