#include "speak.h"
#include <math.h>

template <typename T>
SPeak<T>::SPeak()
{
}

template <typename T>
std::map<uint, typename SPeak<T>::PeakT> SPeak<T>::peak(const T *data, uint count, T& baseLine)
{
    std::map<uint, SPeak<T>::PeakT> peaks;
    SPeak<T>::PeakT pk;
    StateT state = S_IDLE;
    T tMax, tMin, tPeakMax;
    double dbDifference,dbThreshold,dbStartVal;
    uint uHalfSize,uWndSize = m_wndSize;
    T* pWndBegin,* pWndEnd, *pEnd,* pVal;

    if(count <= uWndSize
            || uWndSize < 2){
        return peaks;
    }
    tMax = tMin = data[0];
    pWndBegin = (T*)data;
    pWndEnd = pWndBegin + uWndSize - 1;
    pEnd = (T*)data + count;
    while(pWndBegin < pEnd){
        if(*pWndBegin < tMin)
            tMin = *pWndBegin;
        if(*pWndBegin > tMax)
            tMax = *pWndBegin;
        pWndBegin++;
    }
    baseLine = tMin;
    dbThreshold = uWndSize * tan(m_thresholdAngle * M_PI/ 180);
    pWndBegin = (T*)data;
    uHalfSize = uWndSize / 2;
    pVal = (T*)data + uHalfSize;
    while((++pWndEnd) < pEnd){
        dbDifference = *pWndEnd - *pWndBegin;
        if(dbDifference > dbThreshold){
            if(state == S_END){
                pk.end = pVal - data;
                pk.area -= (pk.end - pk.start) * tMin;
                peaks[pk.start] = pk;
                state = S_IDLE;
            }
            if(state == S_IDLE){
                pk.start = pVal - data;
                pk.max = pk.start;
                pk.area = 0;
                tPeakMax = *pVal;
                dbStartVal = *pVal;
                state = S_START;
            }
        }else if(dbDifference < -dbThreshold){
            if(state == S_START){
                state = S_END;
            }
        }else if(state == S_END
                 && (*pVal - dbStartVal) < dbThreshold){
            pk.end = pVal - data;
            pk.area -= (pk.end - pk.start) * tMin;
            peaks[pk.start] = pk;
            state = S_IDLE;
        }
        if(state == S_START
                || state == S_END){
            pk.area += *pVal;
            if(tPeakMax < *pVal){
                tPeakMax = *pVal;
                pk.max = pVal - data;
            }
        }

        pVal++;
        pWndBegin++;
    }
    if(state == S_END){
        pk.end = pVal - data;
        peaks[pk.start] = pk;
    }
    return peaks;
}

template <typename T>
double SPeak<T>::thresholdAngle() const
{
    return m_thresholdAngle;
}

template <typename T>
void SPeak<T>::setThresholdAngle(double thresholdAngle)
{
    m_thresholdAngle = thresholdAngle;
}

template <typename T>
uint SPeak<T>::wndSize() const
{
    return m_wndSize;
}

template <typename T>
void SPeak<T>::setWndSize(const uint &wndSize)
{
    m_wndSize = wndSize;
}
