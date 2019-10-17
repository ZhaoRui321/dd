#include "polyfit.h"
//#include <QDebug>

void Polyfit::Fit(std::vector<double>& x, std::vector<double>& y, std::vector<double>& c, int m, int n)
{
    std::vector<double> a(m*n);//double a[m][n];
    std::vector<double> b(n*(n+1));//double b[n][n + 1];
    f1(a, x, m, n);
    f2(a, b, y,m,n);
    DirectLU(b, c, m, n);
}

void Polyfit::f1(std::vector<double>& a, std::vector<double>& x,int m, int n)
{
    //int i, j, k;
    double temp;
    for (int i = 0; i<n; i++)
        for (int j = 0; j<m; j++){
            temp = 1;
            for (int k = 0; k<i; k++)
               temp *= x[j];// temp *= *(x+j);
            a[i*m + j]= temp;//*(a + i*m + j) = temp;
        }
}

void Polyfit::f2(std::vector<double>& a, std::vector<double>& b, std::vector<double>& y,int m,int n)
{
    //int i, j, k;
    double temp2;
    for (int i = 0; i<n; i++){
        for (int j = 0; j<n; j++){
            temp2 = 0;
            for (int k = 0; k<m; k++)
                temp2 += a[i*m + k]* a[j*m+ k];//temp2 += *(a + i*m + k)*(*(a + j*m+ k));
            b[i*(n + 1) + j]= temp2;//*(b + i*(n + 1) + j) = temp2;
        }
        temp2 = 0;
        for (int k = 0; k<m; k++){
            temp2 += y[k]* a[i*m + k];//temp2 += *(y+k) * (*(a + i*m + k));
            b[i*(n + 1) + n] = temp2;//*(b + i*(n + 1) + n) = temp2;
        }
    }
}

inline void Polyfit::swap(double &a, double &b)
{
    a = a + b;
    b = a - b;
    a = a - b;
}

void Polyfit::DirectLU(std::vector<double>& a, std::vector<double>& x,int m,int n)
{
    int i, r, k, j;
    std::vector<double> s(n);//double *s = new double[n];
    std::vector<double> t(n);//double *t = new double[n];
    double max;
    for (r = 0; r<n; r++){
        max = 0;
        j = r;
        for (i = r; i<n; i++) {//求是s[i]的绝对值,选主元
            s[i] = a[i*(n+1)+r];//s[i] = *(a+i*(n+1)+r);
            for (k = 0; k<r; k++)
                s[i] -= a[i*(n+1)+k] * a[k*(n+1)+r];//s[i] -= *(a+i*(n+1)+k) * *(a+k*(n+1)+r);
            s[i] = s[i]>0 ? s[i] : -s[i]; //s[i]取绝对值
            if (s[i]>max) {
                j = i;
                max = s[i];
            }
        }
        if (j != r){ //选出的主元所在行j若不是r,则对两行相应元素进行调换
            for (i = 0; i<n + 1; i++)
                swap(a[r*(n+1)+i],a[j*(n+1)+i]);//swap(*(a+r*(n+1)+i),*(a+j*(n+1)+i));
        }
        for (i = r; i<n + 1; i++) //记算第r行的元素
            for (k = 0; k<r; k++) {
                a[r*(n+1)+i] -= a[r*(n+1)+k] * a[k*(n+1)+i];//*(a+r*(n+1)+i) -= *(a+r*(n+1)+k) * *(a+k*(n+1)+i);
            }
        for (i = r + 1; i<n; i++){ //记算第r列的元素
            for (k = 0; k<r; k++)
                a[i*(n+1)+r] -= a[i*(n+1)+k] * a[k*(n+1)+r];//*(a+i*(n+1)+r) -= *(a+i*(n+1)+k) * *(a+k*(n+1)+r);
            a[i*(n+1)+r] /= a[r*(n+1)+r];//*(a+i*(n+1)+r) /= *(a+r*(n+1)+r);
        }
    }
    for (i = 0; i<n; i++)
        t[i] = a[i*(n+1)+n];//t[i] = *(a+i*(n+1)+n);
    for (i = n - 2; i >= 0; i--){//for (i = n - 1; i >= 0; i--){ //利用回代法求最终解
        for (r = n - 1; r>i; r--)
            t[i] -= a[i*(n+1)+r] * x[r];//t[i] -= *(a+i*(n+1)+r) * *(x+r);
        x[i] = t[i] / a[i*(n+1)+i];//*(x+i) = t[i] / *(a+i*(n+1)+i);
    }
}
