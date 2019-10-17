#ifndef SCLIST_H
#define SCLIST_H
#include <qglobal.h>

template <typename T>
/**
 * @brief
 *
 */
class SCList
{
public:
    /**
     * @brief
     *
     */
    struct DataT{
        T data; /**< TODO */
        DataT* next; /**< TODO */
        DataT* front; /**< TODO */
        /**
         * @brief
         *
         */
        DataT(){
           next = NULL;
           front = NULL;
        }
    };

    /**
     * @brief
     *
     * @param maxSize
     */
    SCList(uint maxSize = 1);
    /**
     * @brief
     *
     */
    ~SCList();
    /**
     * @brief
     *
     * @param data
     * @return DataT
     */
    DataT* pushNext(const T& data);
    /**
     * @brief
     *
     * @param data
     * @return DataT
     */
    DataT* pushFront(const T& data);
    /**
     * @brief
     *
     * @return DataT
     */
    DataT* toNext();
    /**
     * @brief
     *
     * @return uint
     */
    uint size();
    /**
     * @brief
     *
     * @return uint
     */
    uint maxSize() const;
    /**
     * @brief
     *
     * @param maxSize
     */
    void setMaxSize(const uint &maxSize);
    /**
     * @brief
     *
     * @return DataT
     */
    DataT* currentData();
    /**
     * @brief
     *
     */
    void release();
private:

    DataT* m_current = NULL; /**< TODO */
    uint m_size = 0; /**< TODO */
    uint m_maxSize; /**< TODO */
};

#include "sclist.cpp"
#endif // SCLIST_H
