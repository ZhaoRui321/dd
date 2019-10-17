
#include <QApplication>
#include "qcalculatorui.h"

int main(int argc, char *argv[])
{
    int ret = -1;
    QApplication a(argc, argv);
    QCalculatorUI* cal = QCalculatorUI::NewInstance();
    if(cal != NULL){
        cal->show();
        ret =  a.exec();
        delete cal;
    }
    return ret;
}
