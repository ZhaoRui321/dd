#include "cMidWareUSB.h"
#include <QVariant>
#include <QTime>
#include <QCoreApplication>
#include <QDebug>

#define debugN(msg)
#define debugE(msg) qDebug()<<msg
#define YEP_IN  0x86
#define YEP_OUT 0x02

MidWareUSB::MidWareUSB(QObject *parent):
    QObject(parent)
{
    m_context = NULL;
    m_device = NULL;
    libusb_init(&m_context);

    m_msThread.setUserFunction(controlThread);
    m_msThread.setUserParam(this);
    m_msThread.start();
}

	  
MidWareUSB::~MidWareUSB(void)
{
    if(m_msThread.isRunning()){
        m_msThread.stop();
        m_msThread.wait();
    }
    if(m_device)
        libusb_close(m_device);
    m_device= NULL;
    if(m_context)
        libusb_exit(m_context);
    m_context= NULL;
}

bool MidWareUSB::reConnect()
{
    debugE("W_MidWareUSB_reConnect");
    try{
        if(m_device)
            libusb_close(m_device);
        if(m_context)
            libusb_exit(m_context);
    }catch(...){}
    m_context = NULL;
    m_device = NULL;
    libusb_init(&m_context);
    //QThread::msleep(50);
    return open();
}

bool MidWareUSB::open(ushort pid, ushort vid)
{
    struct libusb_device **devs;
    struct libusb_device *dev;
    struct libusb_device_handle *handle = NULL;
    size_t i = 0;
    try{
        if (libusb_get_device_list(m_context, &devs)< 0){
            debugE("ERROR_MidWareUSB_cantOpen2");
            return false;
        }
    }catch(...){
        debugE("ERROR_MidWareUSB_cantOpen3");
        return false;
    }
    while ((dev = devs[i++]) != NULL) {
        QCoreApplication::processEvents();   //进入消息队列
        struct libusb_device_descriptor desc;
        if (libusb_get_device_descriptor(dev, &desc) < 0)
            continue;
        if (desc.idVendor == vid && desc.idProduct == pid) {
            try{
                if (libusb_open(dev, &handle) < 0)
                    continue;
            }catch(...){
                continue;}
            m_device = handle;
            try{
                if(libusb_claim_interface(handle,0) < 0){
                    m_device = NULL;
                    libusb_close(handle);
                    continue;
                }
            }catch(...){
                continue;}
            break;
        }
    }
    libusb_free_device_list(devs, 1);
    if(m_device == NULL){
        debugE("ERROR_MidWareUSB_cantOpen4");
        return false;
    }
    m_status = SCOMM_STATUS_OPENED;
    return true;
}

//************************************
// Method:    Close ,关闭通讯接口
// FullName:  MidWareUSB::Close
// Access:    virtual public
// Returns:   int ，返回状态
// Qualifier:
// Parameter: void
//************************************
void MidWareUSB::close(void)
{
    if(m_device == NULL)
        return;
    libusb_close(m_device);
    m_device = NULL;
    m_status &= ~SCOMM_STATUS_OPENED;
}

bool MidWareUSB::write(const void* lpBuffer,
                              unsigned int nNumberOfBytesToWrite,
                              unsigned int* lpNumberOfBytesWritten,
                              unsigned int nTimeOutMs)
{
    if(lpNumberOfBytesWritten && lpBuffer){
        *lpNumberOfBytesWritten = 0;
    }else{
        debugE("ERROR_MidWareUSB_write1");return false;
    }

    int dwByteWritten=0;
    if (status() != SCOMM_STATUS_OPENED){
        if(!reConnect()){
            debugE("ERROR_MidWareUSB_write2");return false;
        }
    }
    int nRes =-1;
    if(m_device){
        try{
            nRes = libusb_bulk_transfer(m_device, YEP_OUT, (uchar*)lpBuffer, (int)nNumberOfBytesToWrite, &dwByteWritten, nTimeOutMs);
        }catch(...){
            nRes =-1;
            debugE("ERROR_MidWareUSB_write3 ")<< ((uint*)lpBuffer)[0]<< " "<<((uint*)lpBuffer)[3];
        }
    }else{
        debugE("ERROR_MidWareUSB_write4")<< ((uint*)lpBuffer)[0]<< " "<<((uint*)lpBuffer)[3];
    }

    if(nRes == 0){
        *lpNumberOfBytesWritten = dwByteWritten;
        return true;
    }else{
        debugE("W_MidWareUSB_write9")<< ((uint*)lpBuffer)[0]<< " "<<((uint*)lpBuffer)[3];
        if(reConnect()){
            if(m_device){
                try{
                    nRes = libusb_bulk_transfer(m_device, YEP_OUT, (uchar*)lpBuffer, (int)nNumberOfBytesToWrite, &dwByteWritten, nTimeOutMs);
                }catch(...){
                    debugE("ERROR_MidWareUSB_write5")<< ((uint*)lpBuffer)[0]<< " "<<((uint*)lpBuffer)[3];return false;
                }
                if(nRes == 0){
                    *lpNumberOfBytesWritten = dwByteWritten;
                    return true;
                }else{
                    debugE("ERROR_MidWareUSB_write6")<< ((uint*)lpBuffer)[0]<< " "<<((uint*)lpBuffer)[3];return false;
                }
            }else{
                debugE("ERROR_MidWareUSB_write7")<< ((uint*)lpBuffer)[0]<< " "<<((uint*)lpBuffer)[3];return false;
            }
        }else{
            debugE("ERROR_MidWareUSB_write8")<< ((uint*)lpBuffer)[0]<< " "<<((uint*)lpBuffer)[3];return false;
        }
    }
    return false;
}

bool MidWareUSB::read(void* lpBuffer,
                            unsigned int nNumberOfBytesToRead,
                            unsigned int* lpNumberOfBytesRead,
                            unsigned int nTimeOutMs)
{
    int dwByteWritten=0;
    if(lpNumberOfBytesRead && lpBuffer){
        *lpNumberOfBytesRead = 0;
    }else{
        debugE("ERROR_MidWareUSB_read1");return false;
    }

    if (status() != SCOMM_STATUS_OPENED){
        if(!reConnect()){
            debugE("ERROR_MidWareUSB_read2");return false;
        }
    }

    int nRes =-1;
    if(m_device){
        try{
            nRes = libusb_bulk_transfer(m_device, YEP_IN, (uchar*)lpBuffer, (int)nNumberOfBytesToRead, &dwByteWritten, nTimeOutMs);
        }catch(...){
            nRes =-1;
            debugE("ERROR_MidWareUSB_read3");
        }
    }else{
        debugE("ERROR_MidWareUSB_read4");
    }

    if(nRes == 0){
        *lpNumberOfBytesRead = dwByteWritten;
        return true;
    }else{
        if(reConnect()){
            debugE("W_MidWareUSB_read9");
        //QThread::msleep(10);
            if(m_device){
                try{
                    nRes = libusb_bulk_transfer(m_device, YEP_IN, (uchar*)lpBuffer, (int)nNumberOfBytesToRead, &dwByteWritten, nTimeOutMs);
                }catch(...){
                    debugE("ERROR_MidWareUSB_read5");return false;
                }
                if(nRes == 0){
                    *lpNumberOfBytesRead = dwByteWritten;
                    return true;
                }else{
                    debugE("ERROR_MidWareUSB_read6");return false;
                }
            }else{
                debugE("ERROR_MidWareUSB_read7");return false;
            }
        }else{
            debugE("ERROR_MidWareUSB_read8");return false;
        }
    }
    return false;
}

//QVariantList MidWareUSB::ioControl(int dwIoControlCode, const QVariantList &data, unsigned int nOutBufferSize, unsigned int nTimeOutMs)
//{
//    unsigned int uRead;
//    QByteArray ba,ba2;
//    QVariantList vl;

//    srls::vl2ba(data,ba);
//    ba2.resize((int)nOutBufferSize);
//    ioControl(dwIoControlCode,ba.data(), (unsigned int)ba.size(), ba2.data(), nOutBufferSize,
//              &uRead, nTimeOutMs);
//    ba2.resize((int)uRead);
//    srls::ba2vl(ba2, vl);
//    return vl;
//}

bool MidWareUSB::writeForBack(const void *lpInBuffer,
                                 unsigned int nInBufferSize,
                                 void *lpOutBuffer,
                                 unsigned int nOutBufferSize,
                                 unsigned int *lpBytesReturned,
                                 unsigned int nTimeOutMs)
{
//    if(!mWR_Mutex.tryLock(nTimeOutMs)){
//        debugE("usb_writeForBack_mWR_Mutex");
//        return false;
//    }
    _COMMUNICATION_STRUCT tmp_COMMUNICATION_STRUCT;
    tmp_COMMUNICATION_STRUCT.pBufferW= lpInBuffer;
    tmp_COMMUNICATION_STRUCT.nBufferW= nInBufferSize;
    tmp_COMMUNICATION_STRUCT.pBufferR= lpOutBuffer;
    tmp_COMMUNICATION_STRUCT.nBufferR= nOutBufferSize;
    int req=pushBuff(&tmp_COMMUNICATION_STRUCT);
    if(req==0){
        int nCount=0;
        QTime tmEmptyPkt;
        tmEmptyPkt.start();
        do{
            QCoreApplication::processEvents();
            req=popBuff(&tmp_COMMUNICATION_STRUCT);   //检测读写是否正常完成
            if(req==0){
                *lpBytesReturned= nOutBufferSize;
                debugN("usb_writeForBack_ok");
                //mWR_Mutex.unlock();
                return true;
            }else if(req== -2){
                tmEmptyPkt.restart();
            }else if(req== -3){
                break;
            }
            debugN("usb_writeForBack_wrong");
            nCount++;
        }while((uint)tmEmptyPkt.elapsed()<nTimeOutMs || nCount<=3);

    }else if(-2== req)
        return false;
    debugE("usb_writeForBack_error"<<((uint*) lpInBuffer)[0]<<" "<<((uint*) lpInBuffer)[3]);
    //mWR_Mutex.unlock();
    return false;
}

int MidWareUSB::pushBuff(_COMMUNICATION_STRUCT* p_COMMUNICATION_STRUCT)
{
    if(p_COMMUNICATION_STRUCT){
        while(1){
            if(!mBufferrMutex.tryLock())
                QCoreApplication::processEvents();
            else
                break;
        }
        const uint* pTmp= (uint*)(p_COMMUNICATION_STRUCT->pBufferW);
        if((pTmp[0]== 0xFFFFF201) &&
                (pTmp[3]== 0x00000004)){   //DAQ Data Request
            if(mIsScan==false){
                mBufferrMutex.unlock();
                return -2;
            }
            if(pTmp[7]> 30 ){//20180503if(pTmp[7]<= 10 ){
                mBufferList.insert(0,p_COMMUNICATION_STRUCT);
            }else{
                //if(!mBufferList.append(p_COMMUNICATION_STRUCT))
                //    qDebug("usb_buff_push_full");
                mBufferList.append(p_COMMUNICATION_STRUCT);
            }
            //qDebug("usb_buff_IsR");
        }else if((pTmp[0]== 0xFFFFF201) &&
                 (pTmp[3]== 0x00000002)){     //DAQ Start
            mBufferList.append(p_COMMUNICATION_STRUCT);
            mIsScan=true;
            //qDebug("usb_buff_IsScan");
        }else if((pTmp[0]== 0xFFFFF201) &&
                 (pTmp[3]== 0x00000008)){     //DAQ Stop
            mBufferList.append(p_COMMUNICATION_STRUCT);
            mIsScan=false;
            //qDebug("usb_buff_IsStop");
        }else {
            mBufferList.append(p_COMMUNICATION_STRUCT);
        }
        mBufferrMutex.unlock();
        debugN("usb_buff_push_ok");
        return 0;
    }else
        qDebug("usb_buff_push_errorParam");
    return -1;
}

int MidWareUSB::clearBuff(_COMMUNICATION_STRUCT* p_COMMUNICATION_STRUCT)
{
    if(p_COMMUNICATION_STRUCT){
        while(1){
            try{
                if(!mBufferrMutex.tryLock())
                    QCoreApplication::processEvents();
                else
                    break;
            }catch(...){}
        }
        for(QList<_COMMUNICATION_STRUCT*>::iterator i=mBufferList.begin(); i!=mBufferList.end(); i++){
            if(*i == p_COMMUNICATION_STRUCT){
                mBufferList.removeOne(p_COMMUNICATION_STRUCT);
                mBufferrMutex.unlock();
                debugN("usb_buff_remove");
                return 0;
            }
        }
        mBufferrMutex.unlock();
    }
    return 0;
}

int MidWareUSB::popBuff(_COMMUNICATION_STRUCT* p_COMMUNICATION_STRUCT)
{
    if(p_COMMUNICATION_STRUCT){
        while(1){
            try{
                if(!mBufferrMutex.tryLock())
                    QCoreApplication::processEvents();
                else
                    break;
            }catch(...){}
        }
        for(QList<_COMMUNICATION_STRUCT*>::iterator i=mBufferList.begin(); i!=mBufferList.end(); i++){
            if(*i == p_COMMUNICATION_STRUCT){
                debugN("usb_buff_pop_waiting");
                mBufferrMutex.unlock();
                return -2;//ing
            }
        }
        mBufferrMutex.unlock();
    }else{
        qDebug("usb_buff_pop_errorParam");
        return -1;//errorParam
    }
    if(p_COMMUNICATION_STRUCT->isOK){
        debugN("usb_buff_pop_ok");
        return 0;//isOK
    }
    qDebug("usb_buff_pop_closed");
    return -3;//usb closed
}

int MidWareUSB::controlThread(void *pParam, const bool &bRunning)
{
    MidWareUSB* pCommunication = (MidWareUSB*)pParam;
    QTime tmEmptyPkt;
    tmEmptyPkt.start();
    if(pCommunication){
        _COMMUNICATION_STRUCT* tmp_COMMUNICATION_STRUCT= nullptr;
        uint ulLength=0,wLength=0,rLength=0;
        bool bError=false;
        uint* pTmp=nullptr;
        while(bRunning){
            pCommunication->mBufferrMutex.lock();
            if(!pCommunication->mBufferList.isEmpty()){
                tmp_COMMUNICATION_STRUCT= pCommunication->mBufferList.first();
                pCommunication->mBufferList.removeFirst();
                debugN("usb_thread_removeFirst");
                if(tmp_COMMUNICATION_STRUCT){
                    ulLength= wLength= rLength=0;
                    bError=false;
                    tmEmptyPkt.restart();
                    do{
                        if(tmp_COMMUNICATION_STRUCT->pBufferW == nullptr || tmp_COMMUNICATION_STRUCT->nBufferW == 0){
                            qDebug("usb_write_emptyBufferW");
                            bError=true;
                            break;
                        }

                        pTmp= (uint*)(tmp_COMMUNICATION_STRUCT->pBufferW);
                        if((pTmp[0]== 0xFFFFF201) &&
                                (pTmp[3]== 0x00000004)){    //DAQ Data Request
                            if(pCommunication->mIsScan==false){
                                bError=true;
                                tmp_COMMUNICATION_STRUCT->isOK=true;
                                break;
                            }
                        }
                        try{
                            if(!pCommunication->write(tmp_COMMUNICATION_STRUCT->pBufferW+wLength, tmp_COMMUNICATION_STRUCT->nBufferW-wLength,
                                                      &wLength,(tmp_COMMUNICATION_STRUCT->nBufferW-wLength)/5000+500)){//(tmp_COMMUNICATION_STRUCT->nBufferW-wLength)/5000+200)){
                                qDebug("usb_write_disconnect");
                                bError=true;
                                break;
                            }
                        }catch(...){
                            qDebug("usb_write_disconnect");
                            bError=true;
                            break;
                        }
                        if((uint)tmEmptyPkt.elapsed() > ((tmp_COMMUNICATION_STRUCT->nBufferW/5000)+500)*5){//((tmp_COMMUNICATION_STRUCT->nBufferW/5000)+200)*5){
                            qDebug("usb_write_overtime");
                            bError=true;
                            break;
                        }
                    }while(ulLength+ wLength <tmp_COMMUNICATION_STRUCT->nBufferW);
                    if(!bError){
                        ulLength = 0;
                        bError=false;
                        tmEmptyPkt.restart();
                        do{
                            try{
                                if(!pCommunication->read(tmp_COMMUNICATION_STRUCT->pBufferR,tmp_COMMUNICATION_STRUCT->nBufferR-rLength,
                                                         &rLength,(tmp_COMMUNICATION_STRUCT->nBufferR-rLength)/5000+1000)){//tmp_COMMUNICATION_STRUCT->overTimeR)){//(tmp_COMMUNICATION_STRUCT->nBufferR-rLength)/5000+200)){
                                    qDebug("usb_read_disconnect");
                                    bError=true;
                                    break;
                                }
                            }catch(...){
                                qDebug("usb_read_disconnect");
                                bError=true;
                                break;
                            }
                            if((uint)tmEmptyPkt.elapsed() > ((tmp_COMMUNICATION_STRUCT->nBufferR/5000)+1000)*5){//((tmp_COMMUNICATION_STRUCT->overTimeR){//tmp_COMMUNICATION_STRUCT->nBufferR/5000)+200)*5){
                                qDebug("usb_read_overtime");
                                bError=true;
                                break;
                            }
                        }while(ulLength+ rLength<tmp_COMMUNICATION_STRUCT->nBufferR);
                        if(!bError)
                            tmp_COMMUNICATION_STRUCT->isOK=true;
                    }
                }
                pCommunication->mBufferrMutex.unlock();
            }else{
                pCommunication->mBufferrMutex.unlock();
                QThread::usleep(100);
            }
        }
    }
    return true;
}

		
