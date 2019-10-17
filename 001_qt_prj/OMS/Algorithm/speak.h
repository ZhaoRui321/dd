#ifndef SPEAK_H
#define SPEAK_H
#include <qglobal.h>
#include <map>

template <typename T>
/**
 * @brief
 *
 */
class SPeak
{
public:
    /**
     * @brief
     *
     */
    struct PeakT{
        double area; /**< TODO */
        uint max; /**< TODO */
        uint start; /**< TODO */
        uint end; /**< TODO */
    };
    /**
     * @brief
     *
     */
    enum StateT{S_IDLE, S_START, S_END};
    /**
     * @brief
     *
     */
    SPeak();
    /**
     * @brief
     *
     * @param data
     * @param count
     * @param baseLine
     * @return std::map<uint, PeakT>
     */
    std::map<uint,PeakT> peak(const T* data, uint count, T& baseLine);
    /**
     * @brief
     *
     * @return double
     */
    double thresholdAngle() const;
    /**
     * @brief
     *
     * @param thresholdAngle
     */
    void setThresholdAngle(double thresholdAngle);

    /**
     * @brief
     *
     * @return uint
     */
    uint wndSize() const;
    /**
     * @brief
     *
     * @param wndSize
     */
    void setWndSize(const uint &wndSize);

private:
    double m_thresholdAngle = 45; /**< TODO */
    uint m_wndSize = 10; /**< TODO */
};

#include "speak.cpp"
#endif // SPEAK_H
