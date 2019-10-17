#pragma once
#include "sclist.h"
#include <list>
#include <vector>
template <typename T>
class cFrameAverage
{
private:
    enum BufferT{B_TEMP, B_SUM, B_LENGTH};
    SCList<std::vector<T> > m_dataList; /**< TODO */
    std::vector<T> m_buffer[B_LENGTH]; /**< TODO */
    volatile bool bLock=false;
public:
    cFrameAverage(){}
    void ClearCounts(){
        if(!bLock){
            bLock=true;
            m_dataList.release();
            bLock=false;
        }
    }
    std::vector<T> frameAverage(const std::vector<T>& pIn, uint uCount);
};

#include "FrameAverage.cpp"

