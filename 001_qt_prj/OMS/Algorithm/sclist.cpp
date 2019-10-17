#include "sclist.h"

template <typename T>
SCList<T>::SCList(uint maxSize):
    m_maxSize(maxSize)
{
}

template <typename T>
SCList<T>::~SCList()
{
    release();
}

template <typename T>
typename SCList<T>::DataT* SCList<T>::pushNext(const T& data)
{
    DataT* pNew;
    if(m_size < m_maxSize){
        pNew = new DataT;
        if(m_current == NULL){
            m_current == pNew;
            pNew->next = pNew;
            pNew->front = pNew;
        }else{
            pNew->next = m_current->next;
            pNew->front = m_current;
            m_current->next->front = pNew;
            m_current->next = pNew;
        }
        m_size++;
    }else{
        pNew = m_current->next;
    }
    pNew->data = data;
    m_current = pNew;
    return pNew;
}

template <typename T>
typename SCList<T>::DataT* SCList<T>::pushFront(const T &data)
{
    DataT* pNew;
    if(m_size < m_maxSize){
        pNew = new DataT;
        if(m_current == NULL){
            m_current == pNew;
            pNew->next = pNew;
            pNew->front = pNew;
        }else{
            pNew->next = m_current;
            pNew->front = m_current->front;
            m_current->front->next = pNew;
            m_current->front = pNew;
        }
        m_size++;
    }else{
        pNew = m_current->front;
    }
    pNew->data = data;
    m_current = pNew;
    return pNew;
}

template <typename T>
uint SCList<T>::size()
{
    return m_size;
}
template <typename T>
uint SCList<T>::maxSize() const
{
    return m_maxSize;
}

template <typename T>
void SCList<T>::setMaxSize(const uint &maxSize)
{
    if(m_maxSize < maxSize)
        release();
    m_maxSize = maxSize;
}

template <typename T>
typename SCList<T>::DataT *SCList<T>::currentData()
{
    return m_current;
}

template <typename T>
void SCList<T>::release()
{
    if(m_current != NULL){
        DataT* pCUr,*pNext;
        pCUr = m_current;
        m_current->front->next =  NULL;
        do{
            pNext = pCUr->next;
            delete pCUr;
            pCUr = pNext;
        }while(pCUr != NULL);
        m_current = NULL;
        m_size = 0;
    }
}


template <typename T>
typename SCList<T>::DataT *SCList<T>::toNext()
{
    DataT* pNew;
    if(m_size < m_maxSize){
        pNew = new DataT;
        if(m_current == NULL){
            m_current = pNew;
            pNew->next = pNew;
            pNew->front = pNew;
        }else{
            pNew->next = m_current->next;
            pNew->front = m_current;
            m_current->next->front = pNew;
            m_current->next = pNew;
        }
        m_size++;
    }else{
        pNew = m_current->next;
    }
    m_current = pNew;
    return pNew;
}
