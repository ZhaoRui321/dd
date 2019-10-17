#pragma once
//#include <tool/sglobal.h>
#include <tool/sthread.h>
#include <QList>
#include <QMutex>
#include <QVariant>
#include <libusb-1.0/libusb.h>

#define SCOMM_STATUS_OPENED 1
/**
 * @brief The MidWareUSB class
 * USB驱动的封装类，内含通讯数据池线程，writeForBack为USB读写接口
 */
class MidWareUSB: public QObject
{
    Q_OBJECT
public:
    struct _COMMUNICATION_STRUCT{
        const void * pBufferW=nullptr;
        uint nBufferW=0;
        //uint overTimeW=0;
        void * pBufferR=nullptr;
        uint nBufferR=0;
        //uint overTimeR=0;
        volatile bool isOK=false;
    };
    volatile bool mIsScan=false;
    MidWareUSB(QObject *parent = 0);
    ~MidWareUSB(void);
    bool writeForBack(const void* lpInBuffer,
                      unsigned int nInBufferSize,
                      void* lpOutBuffer,
                      unsigned int nOutBufferSize,
                      unsigned int* lpBytesReturned = NULL,
                      unsigned int nTimeOutMs = 500);
    int getListSize(){
        return mBufferList.size();
    }

protected:
    QList<_COMMUNICATION_STRUCT*> mBufferList;
    SThread m_msThread;
    QMutex mBufferrMutex;
    QMutex mWR_Mutex;
    QThread mBufferrQThread;
    int pushBuff(_COMMUNICATION_STRUCT* p_COMMUNICATION_STRUCT);//, int overTime
    int popBuff(_COMMUNICATION_STRUCT* p_COMMUNICATION_STRUCT);//, int overTime
    int clearBuff(_COMMUNICATION_STRUCT* p_COMMUNICATION_STRUCT);
    static int controlThread(void *pParam, const bool &bRunning);
    bool reConnect();
    bool open(ushort pid= 4098, ushort vid= 1351);
    void close(void);
    bool write(const void* lpBuffer,
               unsigned int nNumberOfBytesToWrite,
               unsigned int* lpNumberOfBytesWritten = NULL,
               unsigned int nTimeOutMs = ~0);
    bool read(void* lpBuffer,
              unsigned int nNumberOfBytesToRead,
              unsigned int* lpNumberOfBytesRead = NULL,
              unsigned int nTimeOutMs = ~0);
private:
    int m_status = 0; /**< The status for this communication module */
    libusb_context* m_context; /**< TODO */
    libusb_device_handle* m_device; /**< TODO */
    int status(void){
        return m_status;
    }

//    void setStatus(int nStatus){
//        m_status = nStatus;
//    }
    //    QVariantList ioControl(
    //            int dwIoControlCode,
    //            const QVariantList &data,
    //            unsigned int nOutBufferSize,
    //            unsigned int nTimeOutMs);
};
