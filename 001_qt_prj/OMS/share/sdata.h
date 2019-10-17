#ifndef SDATA_H
#define SDATA_H
#include <typeinfo>

namespace srls {

/**
 * @brief
 *
 */
enum ValueTypeT{VT_UNKNOWN,VT_U8,VT_S8,VT_U16,VT_S16,VT_U32,VT_S32,VT_U64,VT_S64,VT_BIT,VT_BOOL,VT_FLOAT,VT_DOUBLE};
/**
 * @brief
 *
 */
enum DataTypeT{DT_UNKNOWN, DT_2D_LINE, DT_POINTS};

/**
 * @brief
 *
 */
struct DataT{
    int type; /**< TODO */
    /**
     * @brief
     *
     * @param nType
     */
    DataT(int nType = DT_UNKNOWN): type(nType){}
};

/**
 * @brief
 *
 */
struct Data2DLineBaseT : public DataT
{
    ValueTypeT xVType; /**< TODO */
    ValueTypeT yVType; /**< TODO */
    unsigned int yLength; /**< TODO */

    /**
     * @brief
     *
     */
    Data2DLineBaseT(): DataT(DT_2D_LINE){}
};

template <typename XT, typename YT = XT>
/**
 * @brief
 *
 */
struct Data2DLineT : public Data2DLineBaseT
{
    XT xBegin; /**< TODO */
    XT xEnd; /**< TODO */
    YT y[0]; /**< TODO */

    /**
     * @brief
     *
     */
    Data2DLineT(){
        if(typeid(XT) == typeid(unsigned char))
            xVType = VT_U8;
        else if(typeid(XT) == typeid(char))
            xVType = VT_S8;
        else if(typeid(XT) == typeid(unsigned short))
            xVType = VT_U16;
        else if(typeid(XT) == typeid(short))
            xVType = VT_S16;
        else if(typeid(XT) == typeid(unsigned int))
            xVType = VT_U32;
        else if(typeid(XT) == typeid(int))
            xVType = VT_S32;
        else if(typeid(XT) == typeid(unsigned long long))
            xVType = VT_U64;
        else if(typeid(XT) == typeid(long long))
            xVType = VT_S64;
        else if(typeid(XT) == typeid(bool))
            xVType = VT_BOOL;
        else if(typeid(XT) == typeid(float))
            xVType = VT_FLOAT;
        else if(typeid(XT) == typeid(double))
            xVType = VT_DOUBLE;
        else
            xVType = VT_UNKNOWN;

        if(typeid(YT) == typeid(unsigned char))
            yVType = VT_U8;
        else if(typeid(YT) == typeid(char))
            yVType = VT_S8;
        else if(typeid(YT) == typeid(unsigned short))
            yVType = VT_U16;
        else if(typeid(YT) == typeid(short))
            yVType = VT_S16;
        else if(typeid(YT) == typeid(unsigned int))
            yVType = VT_U32;
        else if(typeid(YT) == typeid(int))
            yVType = VT_S32;
        else if(typeid(YT) == typeid(unsigned long long))
            yVType = VT_U64;
        else if(typeid(YT) == typeid(long long))
            yVType = VT_S64;
        else if(typeid(YT) == typeid(bool))
            yVType = VT_BOOL;
        else if(typeid(YT) == typeid(float))
            yVType = VT_FLOAT;
        else if(typeid(YT) == typeid(double))
            yVType = VT_DOUBLE;
        else
            yVType = VT_UNKNOWN;
    }
};

}
#endif // SDATA_H
