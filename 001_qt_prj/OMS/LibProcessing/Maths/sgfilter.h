#ifndef SGFILTER_H
#define SGFILTER_H
#include <vector>
#include <cmath>

namespace sgfilter {

//! comfortable array of doubles
typedef std::vector<double> float_vect;

/*! \brief savitzky golay smoothing.
 *
 * This method means fitting a polynome of degree 'deg' to a sliding window
 * of width 2w+1 throughout the data.  The needed coefficients are
 * generated dynamically by doing a least squares fit on a "symmetric" unit
 * vector of size 2w+1, e.g. for w=2 b=(0,0,1,0,0). evaluating the polynome
 * yields the sg-coefficients.  at the border non symmectric vectors b are
 * used. */
float_vect smooth(const float_vect &v, const int w, const int deg);

// c-callable interface to for tcl plugin code
double *calc_smooth(const int ndat, double *input, const int window, const int order);

}

namespace filter {

template <typename T>
void average(const T *pIn, T *pOut, const unsigned int count, const unsigned int wndSize = 2)
{
    double dbSum = 0;
    unsigned int uHalfSize;
    T* pWndBegin,* pWndEnd, *pEnd,* pVal;

    if(count <= wndSize
            || wndSize < 2){
        memcpy(pOut, pIn, count * sizeof(T));
        return;
    }
    pWndBegin = (T*)pIn;
    pWndEnd = pWndBegin + wndSize - 1;
    pEnd = (T*)pIn + count;
    uHalfSize = wndSize / 2;
    pVal = pOut + uHalfSize;
    memcpy(pOut, pIn, uHalfSize * sizeof(T));
    memcpy(pOut + (count - uHalfSize), pIn + (count - uHalfSize), uHalfSize * sizeof(T));
    while(pWndBegin < pWndEnd)
        dbSum += *(pWndBegin++);
    pWndBegin = (T*)pIn;
    while((++pWndEnd) < pEnd){
        dbSum += *pWndEnd;
        *(pVal++) = dbSum / wndSize;
        dbSum -= *(pWndBegin++);
    }
}

}


namespace tool {

template <typename T1, typename T2>
double sn(const T1 *ss, const T2 *ns, const unsigned int size) {
    double sn = 0;
    const T1 *sitem, *send;
    const T2 *nitem;
    sitem = ss;
    send = ss + size;
    nitem = ns;
    do{
        //sn += std::fabs(*sitem / *nitem);
        sn += std::fabs((*sitem - *nitem) / *sitem);
        ++nitem;
    }while(++sitem < send);
    //return std::log10(sn / size);
    return sn / size;
}

}
#endif // SGFILTER_H
