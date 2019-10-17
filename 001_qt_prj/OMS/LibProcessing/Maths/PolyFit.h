#ifndef POLYFIT_H
#define POLYFIT_H
//#include<iostream>
#include<cmath>
#include<vector>
#include <QDebug>

class Polyfit
{
public:

    void Fit(std::vector<double>& x, std::vector<double>& y, std::vector<double>& c, int m, int n);

private:
    void f1(std::vector<double>& a, std::vector<double>& x, int m, int n);
    void f2(std::vector<double>& a, std::vector<double>& b, std::vector<double>& y, int m, int n);
    void DirectLU(std::vector<double>& a, std::vector<double>& x, int m, int n);
    void swap(double & a, double & b);
};

class Fit
{
public:
    //静态方法，传入当前值，期望值，coefF，和当前校准数量-1
    static bool Polynomial(std::vector<double>& x,
                    std::vector<double>& y,
                    std::vector<double>& c,
                    unsigned int order= 5){
            int size= x.size();
            c.clear();
            if((y.size()!= size)||(size<= order))
                return false;
            c.resize(order);
            Polyfit mPolyfit;
            mPolyfit.Fit(x, y, c, order, size);
            return true;
        }
};

#endif // POLYFIT_H
