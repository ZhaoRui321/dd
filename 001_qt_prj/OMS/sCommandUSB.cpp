#include "sCommandUSB.h"
#include <QDebug>
#include <QDir>
#include <QTime>

CommandUSB::CommandUSB(QObject *parent):
    QObject(parent)
{
    mProcessThread.setUserParam(this);
    mProcessThread.setUserFunction(processDataThread);
}

CommandUSB::~CommandUSB()
{
    if(mProcessThread.isRunning()){
        mProcessThread.stop();
        mProcessThread.wait();
    }
}

QString CommandUSB::save2File(QString rFileName)
{
    QString trueFile;
#if 0
    if(mDataFile){
        if(mDataFile->isOpen())
            mDataFile->close();
        mDataFile=nullptr;
    }else{
        mDataFile= new QFile();
        QDateTime dt = QDateTime::currentDateTime();
        if(rFileName.isEmpty())
            trueFile=QString("./daq_%1.dat").arg(dt.toString("yyMMddhhmmss"));
        else
            trueFile= rFileName;
        mDataFile->setFileName(trueFile);
        mDataFile->open(QFile::WriteOnly);
        if(!mDataFile->isOpen()){
//            SFileHead fileHead;
//            fileHead.vid = 0x53524C53;
//            fileHead.pid = 0x00000005;
//            file.write((char*)&fileHead, sizeof(fileHead));

//            SDaqFileHead daqFileHead;
//            fileHead.paramSize = sizeof(daqFileHead);
//            daqFileHead.accumulate = uAccNumber;
//            daqFileHead.framePoint = uValidSize;//uValidEnd;
//            daqFileHead.dateTime = dt.toTime_t();
//            daqFileHead.frequency = 100.0 / pDaqPart->property("frqaq").toUInt();
//            daqFileHead.massStart = dbMassStart;
//            daqFileHead.massEnd = dbMassEnd;
//            file.write((char*)&daqFileHead, sizeof(daqFileHead));
            method2File(mDataFile);
        }
    }
#endif
    return trueFile;
}

int CommandUSB::method2File(QFile* pFile, QString rFileName)
{
    if(rFileName.isEmpty()){
        qDebug("E_CommandUSB_method2File_FileName");
        return -1;
    }
    if(pFile->isOpen()){
        QFile rfile(rFileName);
        rfile.open(QFile::ReadOnly);
        if(rfile.isOpen()){
            if(rfile.size()>0){
                QByteArray tempRead=rfile.readAll();
                pFile->write(tempRead.data(),tempRead.size());
            }
            rfile.close();
        }
        return 0;
    }
    return -2;
}

QString CommandUSB::createFileTIC(QString fileName)
{
    if(mDataFileTIC!=nullptr){
        try{
            mDataFileTIC->close();
            delete mDataFileTIC;
        }catch(...){}
        mDataFileTIC=nullptr;
    }
    if(fileName.isEmpty()){
        fileName= QDir::currentPath() + "\\data";
        QDir dir;
        if (!dir.exists(fileName))
            if(!dir.mkpath(fileName))
                return QString();
        fileName += "\\MASS_DATA_";// + QDateTime::currentDateTime().toString("yyMMddhhmmss");
        try{
            mDataFileTIC= new QFile(fileName + ".TIC");
            if(!mDataFileTIC->open(QIODevice::WriteOnly | QIODevice::Text))
                return QString();
            else
                mFileName=fileName.toUtf8();
        }catch(...){
            delete mDataFileTIC;
            return QString();
        }
//        if(mStreamTIC){
//            delete mStreamTIC;
//            mStreamTIC=nullptr;
//        }
//        mStreamTIC = new QTextStream(mDataFileTIC);
    }else{

    }
    return fileName;
}

QString CommandUSB::createFileMass(QString fileName)
{
    if(mDataFileMass!=nullptr){
        try{
            mDataFileMass->close();
            delete mDataFileMass;
        }catch(...){}
        mDataFileMass=nullptr;
    }
    if(fileName.isEmpty()){
        fileName= QDir::currentPath() + "\\data";
        QDir dir;
        if (!dir.exists(fileName))
            if(!dir.mkpath(fileName))
                return QString();
        fileName += "\\MASS_DATA_";// + QDateTime::currentDateTime().toString("yyMMddhhmmss");

    }else{

    }
    try{
        mDataFileMass= new QFile(fileName + ".TIC.dat");
        if(!mDataFileMass->open(QIODevice::WriteOnly | QIODevice::Truncate))
            return QString();
        else{
            if(!mFileHead.isEmpty()){//method2File(mDataFileMass);
                mDataFileMass->write(mFileHead.data(),mFileHead.length());
                mDataFileMass->flush();
            }
            mFileName=fileName.toUtf8();
        }
    }catch(...){
        delete mDataFileMass;
        return QString();
    }
    return fileName;
}

void CommandUSB::saveDataTIC(QString data)
{
    try{
//        mStreamTIC<<data;
//        mStreamTIC->flush();
        mDataFileTIC->write(data.toUtf8());
        mDataFileTIC->flush();
    } catch(...) { }
}

bool CommandUSB::saveDataMass(QByteArray& pData)
{
    try{
        mDataFileMass->write(pData);
        mDataFileMass->flush();
    }catch(...){
        return false;
    }
    return true;
}

bool CommandUSB::saveDataMass(char* pData,qint64 nLength)
{
    try{
        mDataFileMass->write(pData,nLength);
        mDataFileMass->flush();
    }catch(...){
        return false;
    }
    return true;
}

void CommandUSB::closeFileTIC()
{
    if(mDataFileTIC){
        try{
            mDataFileTIC->close();
        }catch(...) { }
        delete mDataFileTIC;
        mDataFileTIC=nullptr;
    }
}

void CommandUSB::closeFileMass()
{
    if(mDataFileMass){
        try{
            mDataFileMass->close();
        }catch(...) { }
        delete mDataFileMass;
        mDataFileMass=nullptr;
    }
}

void CommandUSB::renameFile(QString fileName)
{
    if (!mFileName.isEmpty())
    {
        QString currentFileTIC=QString::fromUtf8(mFileName) + ".TIC";
        QString currentFileMass=QString::fromUtf8(mFileName) + ".TIC.dat";
        mFileName.clear();
        QFile tmpFileTIC(currentFileTIC);
        QFile tmpFileMass(currentFileMass);
        if(!tmpFileTIC.exists()){
            if(tmpFileMass.exists()){
                try{
                    tmpFileMass.remove();
                }catch(...){}
            }
            return;
        }
        if(!tmpFileMass.exists()){
            if(tmpFileTIC.exists()){
                try{
                    tmpFileTIC.remove();
                }catch(...){}
            }
            return;
        }
        if(fileName.isEmpty()){//delete file
            try{
                tmpFileTIC.remove();
            tmpFileMass.remove();
            }catch(...){}
        }else{
            //QByteArray tmpName(pName, lengthName);
            //QString newName(tmpName);
            try{
            tmpFileTIC.rename(fileName);
            tmpFileMass.rename(fileName+".dat");
            }catch(...){}
        }
    }
}

void CommandUSB::renameFile(char* pName,int lengthName)
{
    if (!mFileName.isEmpty())
    {
        QString currentFileTIC=QString::fromUtf8(mFileName) + ".TIC";
        QString currentFileMass=QString::fromUtf8(mFileName) + ".TIC.dat";
        mFileName.clear();
        QFile tmpFileTIC(currentFileTIC);
        QFile tmpFileMass(currentFileMass);
        if(!tmpFileTIC.exists()){
            if(tmpFileMass.exists()){
                try{
                    tmpFileMass.remove();
                }catch(...){}
            }
            return;
        }
        if(!tmpFileMass.exists()){
            if(tmpFileTIC.exists()){
                try{
                    tmpFileTIC.remove();
                }catch(...){}
            }
            return;
        }
        if(lengthName<=0){//delete file
            try{
                tmpFileTIC.remove();
            tmpFileMass.remove();
            }catch(...){}
        }else{
            QByteArray tmpName(pName, lengthName);
            QString newName(tmpName);
            try{
            tmpFileTIC.rename(newName);
            tmpFileMass.rename(newName+".dat");
            }catch(...){}
        }
    }
}

int CommandUSB::processDataThread(void *pParam, const bool &bRunning)
{
    qDebug("N_CommandUSB_processDataThread_start");
    CommandUSB* pCmd = (CommandUSB*)pParam;
    if(!pCmd)
        return -1;

#if 0
    bool bSaveFile= false;
    if(pCmd->isSaveFile()){
        bSaveFile= pCmd->createDataFile();
    }
#endif

    int uAccNumber = (int)pCmd->m_DAQ_CONFIG.No_ACC;//pDaqPart->property("noacc").toInt();
    int nPointNumber= (int)pCmd->m_DAQ_CONFIG.No_AQP;   //总数据点数
    if(uAccNumber <= 0){
        qDebug("E_CommandUSB_processDataThread_ACC");return -1;
    }
    qint64 uValidSize = (nPointNumber + uAccNumber - 1) / uAccNumber;
    if(uValidSize<= 0){
        qDebug("E_CommandUSB_processDataThread_ZeroPoint");return -1;
    }
    qint64 uLastPktSize= uValidSize % 120;	//每帧的最后一个包中有效数据个数
    if (uLastPktSize==0)
        uLastPktSize=120;
    double dbRawScale = 2 * 4.197 / (uAccNumber * uint(0xffff));
    //pDaqPart->propertyInfo()["sampled_data"].version = 0;
    //pDaqPart->propertyInfo()["average_data"].version = 0;
    uint tmpVersion=1;
    QByteArray sampledData;
    QList<CommunicationCMD::_DAQ_DATA*>* pDataDAQ= pCmd->mCommunicationCMD.getDataDAQ();
    if(!pDataDAQ)
        return -2;
    int nsize= pDataDAQ->size();
    qDebug()<<"N_CommandUSB_tryToGetBuffer&Version "<<tmpVersion;
    _StreamBody* p_StreamBody= nullptr;
    double* pdbVal =nullptr;

    QTime currentT;
    currentT.start();
    double tmpTimeS=0;
    double elapsedTime=0;
    double elapsedRange=10000;
    int elapsedNum=0;
    //currentT.elapsed() / 1000.0
    double sumY = 0;
    bool isNewData=false;
    while(bRunning && pCmd->mCommunicationCMD.isThreadRun()){
        for(int i=0;i<nsize;i++){
            isNewData=false;
            if(!pDataDAQ->at(i)){
                QThread::msleep(1);
                continue;
            }
            pDataDAQ->at(i)->qLock.lock();
            if((pDataDAQ->at(i)->nVersion> tmpVersion)
                    || (pDataDAQ->at(i)->nVersion==0)){
                //qDebug()<<"Command_Thread-Version:"<<pCmd->m_DAQ_DATA.at(i)->nVersion<<" "<<tmpVersion;

                elapsedTime= ((double)currentT.elapsed())/1000.0;
                if(elapsedTime-elapsedRange>1e-6){
                    ++elapsedNum;
                    currentT.restart();
                }

                if(pDataDAQ->at(i)->pBuff.isEmpty()){
                    pDataDAQ->at(i)->qLock.unlock();
                    continue;
                }
                if(pDataDAQ->at(i)->pBuff.size() != uValidSize){
                    qDebug("W_CommandUSB_processDataThread_nFrame");
                    pDataDAQ->at(i)->qLock.unlock();
                    continue;
                }
                sampledData.resize(sizeof(_StreamBody) + uValidSize * sizeof(double));
                //currentT= QDateTime::currentDateTime();
                QDateTime tempDateTime=QDateTime::currentDateTime();
                p_StreamBody = reinterpret_cast<decltype(p_StreamBody)>(sampledData.data());
                p_StreamBody->typeParam = _StreamBody::Type_Null;
                p_StreamBody->length = sampledData.size();

                p_StreamBody->dateTime= tempDateTime.toTime_t()*1000+ tempDateTime.time().msec();
                p_StreamBody->dataFrame= pDataDAQ->at(i)->nVersion;

                pdbVal = &p_StreamBody->y[0];
                for(int uIndex = 0; uIndex < uValidSize; uIndex++){
                    pdbVal[uIndex] =(((pDataDAQ->at(i)->pBuff[uIndex] & 0x03ffffff))* dbRawScale - 4.197);
                    sumY = ((double)uIndex / (double)(uIndex + 1) * sumY + pdbVal[uIndex] / (uIndex + 1));
                }

                tmpTimeS=currentT.elapsed() / 1000.0+ elapsedRange* (double)elapsedNum;
                //tmpTimeS=(double)currentT.elapsed()/1000.0+ (double)(elapsedRange)/1000.0* (double)(elapsedNum);
                p_StreamBody->currentTime= tmpTimeS;
                p_StreamBody->currentAcc= fabs(sumY);

                pCmd->setDataDAQ(sampledData);
                tmpVersion = pDataDAQ->at(i)->nVersion;
                isNewData=true;
            }
            pDataDAQ->at(i)->qLock.unlock();
#if 0
            if(bSaveFile&& isNewData){
                pCmd->saveDataTIC(QString::number(tmpTimeS) + "\t"+ QString::number(sumY) + "\n");//
                pCmd->saveDataMass(sampledData);

                QVector<double> tmpD(sampledData.size()/sizeof(double));
                memcpy(tmpD.data(),sampledData.data(),sampledData.size());
                int idebug=0;
                idebug++;

            }
#endif
            QThread::msleep(1);
        }
    }
    pCmd->clearBuff();
#if 0
    if(bSaveFile){
        pCmd->closeFileTIC();
        pCmd->closeFileMass();
    }
#endif
    qDebug("N_CommandUSB_processDataThread_Over");
    return 0;
}
void CommandUSB::setDataDAQ(QByteArray& srcData)
{
    mSampledData.qLock.lock();
    mSampledData.pBuff.resize(srcData.size());
    memcpy(mSampledData.pBuff.data(), srcData.data(), srcData.size());
    mSampledData.nVersion++;
    if(mSampledData.nVersion>40000)
        mSampledData.nVersion=1;
    mSampledData.qLock.unlock();
}

int CommandUSB::getDataDAQ(_DAQ_DATA* p_DAQ_DATA, bool always)
{
    mSampledData.qLock.lock();
    int nSize= mSampledData.pBuff.size();
    if(always){
        if (nSize!=0){
            if (p_DAQ_DATA->pBuff.size()!= nSize){
                p_DAQ_DATA->pBuff.resize(nSize);
            }
            memcpy(p_DAQ_DATA->pBuff.data(), mSampledData.pBuff.data(), nSize);
            mSampledData.qLock.unlock();
            return 0;
        }
    }else{
        if(p_DAQ_DATA->nVersion!=mSampledData.nVersion){
            p_DAQ_DATA->nVersion=mSampledData.nVersion;
            if (nSize!=0){
                if (p_DAQ_DATA->pBuff.size()!= nSize){
                    p_DAQ_DATA->pBuff.resize(nSize);
                }
                memcpy(p_DAQ_DATA->pBuff.data(), mSampledData.pBuff.data(), nSize);
                mSampledData.qLock.unlock();
                return 0;
            }
        }
    }
    mSampledData.qLock.unlock();
    return -1;
}

int CommandUSB::getDataDAQ(QByteArray& srcData, bool always)
{
    mSampledData.qLock.lock();
    int nSize= mSampledData.pBuff.size();
    if(always){
        if (nSize!=0){
            if (srcData.size()!= nSize)
                srcData.resize(nSize);
            memcpy(srcData.data(), mSampledData.pBuff.data(), nSize);
            mSampledData.qLock.unlock();
            return mSampledData.nVersion;
        }else
            srcData.clear();
        mSampledData.qLock.unlock();
        return mSampledData.nVersion;
    }else{
        if(mVersionGet!=mSampledData.nVersion){
            mVersionGet=mSampledData.nVersion;
            if (nSize!=0){
                if (srcData.size()!= nSize)
                    srcData.resize(nSize);
                memcpy(srcData.data(), mSampledData.pBuff.data(), nSize);
            }else
                srcData.clear();
            mSampledData.qLock.unlock();
            return mSampledData.nVersion;
        }
    }
    mSampledData.qLock.unlock();
    return -1;
}

int CommandUSB::getDataDAQ(std::vector<double>& srcData, bool always)
{
    mSampledData.qLock.lock();
    uint nSize= mSampledData.pBuff.size();
    if(always){
        if (nSize!=0){
            if (srcData.size()!= nSize){
                srcData.resize(nSize);
            }
            memcpy(srcData.data(), mSampledData.pBuff.data(), nSize*sizeof(double));
//            mSampledData.qLock.unlock();
//            return mSampledData.nVersion;
        }else
            srcData.clear();
        mSampledData.qLock.unlock();
        return mSampledData.nVersion;
    }else{
        if(mVersionGet!=mSampledData.nVersion){
            mVersionGet=mSampledData.nVersion;
            if (nSize!=0){
                if (srcData.size()!= nSize){
                    srcData.resize(nSize);
                }
                memcpy(srcData.data(), mSampledData.pBuff.data(), nSize*sizeof(double));
            }else
                srcData.clear();
            mSampledData.qLock.unlock();
            return mSampledData.nVersion;
        }
    }
    mSampledData.qLock.unlock();
    return -1;
}

void CommandUSB::onShowCurrentFile(bool state)
{
    if(mProcessThread.isRunning()){
        QString fileTIC = QDir::currentPath() + "\\TEMP_DATA.TIC";     //mDataFileTIC->fileName();
        QString fileMass = fileTIC+".dat";                        //mDataFileMass->fileName();
        if(!fileTIC.isEmpty()&&!fileMass.isEmpty())
            emit currentFilePath(fileTIC,fileMass,state);
    }
}
