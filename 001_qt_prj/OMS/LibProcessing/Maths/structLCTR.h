#pragma once
#include <stdio.h>
#include <float.h>
#include <math.h>

namespace LCTR
{
#define Length size()
}

#define QT

#ifndef QT
#define zend_isinf(a)   ((_fpclass(a) == _FPCLASS_PINF) || (_fpclass(a) == _FPCLASS_NINF))
#define zend_isnan(x)   _isnan(x)
#endif


#define Mymax(a,b)    (((a) > (b)) ? (a) : (b))
#define Mymin(a,b)    (((a) < (b)) ? (a) : (b))

namespace SignalProcessingPublic
{

}
class MyMath
{
public:
	static int DivRem(int a, int b, int& result){
		int output;
		output=a/b;
		result=a%b;
		return output;
	};

	static double Round(double val, int places) {
		double t;
		double f = pow(10.0, (double) places);
		double x = val * f;
#ifndef QT
		if (zend_isinf(x) || zend_isnan(x)) {
			return val;
		}
#endif
		if (x >= 0.0) {
			t = ceil(x);
			if ((t - x) > 0.50000000001) {
				t -= 1.0;
			}
		} else {
			t = ceil(-x);
			if ((t + x) > 0.50000000001) {
				t -= 1.0;
			}
			t = -t; 
		}
        if(f!=0.0)
            x = t / f;
#ifndef QT
		return !zend_isnan(x) ? x : t;
#endif
        return x;
	}


};
