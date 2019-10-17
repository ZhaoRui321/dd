template <typename T>
std::vector<T> cFrameAverage<T>::frameAverage(const std::vector<T>& pIn, uint uCount)
{
    if(!bLock){
        bLock=true;
        if(m_dataList.maxSize()!=uCount)
            m_dataList.setMaxSize(uCount);
        uint sizeBuff=pIn.size();
        //T* pIn2,*pOut2,*pTemp;
        uint uFrames;
        m_buffer[B_TEMP].resize(sizeBuff);
        if(m_buffer[B_SUM].size() != sizeBuff){
            m_dataList.release();
        }
        uFrames = m_dataList.size();
        if(uFrames == 0){
            m_buffer[B_SUM].resize(sizeBuff);
            memcpy(m_buffer[B_SUM].data(), pIn.data(), sizeof(T) * sizeBuff);
            memcpy(m_buffer[B_TEMP].data(), pIn.data(), sizeof(T) * sizeBuff);
        }else if(uFrames < m_dataList.maxSize()){
            uFrames++;
            for(uint uIndex = 0; uIndex < sizeBuff; uIndex++){
                m_buffer[B_SUM][uIndex] += pIn[uIndex];
                m_buffer[B_TEMP][uIndex] = m_buffer[B_SUM][uIndex] / uFrames;
            }
        }else{
            // SCList<std::vector<T> >::DataT *pLast;
            auto pLast = m_dataList.currentData()->next;
            for(uint uIndex = 0; uIndex < sizeBuff; uIndex++){
                m_buffer[B_SUM][uIndex] += pIn[uIndex] - pLast->data[uIndex] ;
                m_buffer[B_TEMP][uIndex] = m_buffer[B_SUM][uIndex] / uFrames;
            }
        }

        auto pData = m_dataList.toNext();
        pData->data.resize(sizeof(T) * sizeBuff);
        memcpy(pData->data.data(), pIn.data(), sizeof(T) * sizeBuff);
        bLock=false;
    }
    return m_buffer[B_TEMP];
}
