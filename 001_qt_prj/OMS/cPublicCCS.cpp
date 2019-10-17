#include "cPublicCCS.h"

void sortGICAP::quickSort(double s[], int* pMarker, int left,//数组下标
                 int right)//数组下标，为长度-1

{
    if (left < right){
        int low = left, high = right;
        double key = s[left];
        int keyMarker=pMarker[left];
        while (low < high){
            while(low < high && s[high] - key >= 0.0000001) // 从右向左找第一个小于key的数
                high--;
            if(low < high){
                pMarker[low] = pMarker[high];
                s[low++] = s[high];
            }
            while(low < high && s[low] < key) // 从左向右找第一个大于等于key的数
                low++;
            if(low < high){
                pMarker[high] = pMarker[low];
                s[high--] = s[low];
            }
        }
        s[low] = key;
        pMarker[low]=keyMarker;
        sortGICAP::quickSort(s, pMarker,left, low - 1); // 递归调用
        sortGICAP::quickSort(s, pMarker,low + 1, right);
    }
}
void sortGICAP::widthSort(double* cAbsc,/*y值数组*/
                              int* pMarker,/**/
                              int nLength,
                              int nWidth)//只排序前nWidth个最大值
{
    if(nLength==nWidth)
        return;
    int countAbsc=0;
    double temp1=0;
    int left1=0,right1=nLength-1,left2=nLength-1;
    while(left1<nWidth){
        for(int i=left1;i<nLength;i++){
            if(cAbsc[left1]<cAbsc[i]){
                countAbsc++;
                if(countAbsc>=nWidth-left1){
                    temp1=cAbsc[right1];
                    cAbsc[right1]=cAbsc[left1];
                    cAbsc[left1]=temp1;
                    temp1=pMarker[right1];
                    pMarker[right1]=pMarker[left1];
                    pMarker[left1]=temp1;
                    right1--;
                    break;
                }
            }
        }
        countAbsc=0;
        if(left2!=right1)
            left2=right1;
        else left1++;
    }
}

void sortGICAP::DateSort(const std::vector<double>& pAbsc, const std::vector<double>& pOrd,
                         const std::vector<int>& pStart, const std::vector<int>& pEnd, std::vector<double>& pAbsc1, std::vector<double>& pOrd1,
                         std::vector<int>& pStart1, std::vector<int>& pEnd1, std::vector<int>& pMarker, uint uWidth)
{
    uint nLength=pOrd.size();
    vectorOperate::Resize(pOrd1, nLength);//pOrd1.resize(nLength);
    std::copy(pOrd.begin(),pOrd.end(),pOrd1.begin());
    if(nLength<uWidth)
        uWidth=nLength;
    sortGICAP::widthSort(&(pOrd1[0]),&(pMarker[0]),nLength,uWidth);
    sortGICAP::quickSort(&(pOrd1[0]),&(pMarker[0]),0,uWidth-1);
    vectorOperate::Resize(pAbsc1, uWidth);//pAbsc1.resize(uWidth);
    vectorOperate::Resize(pOrd1, uWidth);//pOrd1.resize(uWidth);
    vectorOperate::Resize(pStart1, uWidth);//pStart1.resize(uWidth);
    vectorOperate::Resize(pEnd1, uWidth);//pEnd1.resize(uWidth);
    for(uint j=0;j<uWidth;j++){
        pAbsc1[j]=pAbsc[pMarker[j]];
        pOrd1[j]=pOrd[pMarker[j]];
        pStart1[j]=pStart[pMarker[j]];
        pEnd1[j]=pEnd[pMarker[j]];
    }
}
