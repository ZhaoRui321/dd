#ifndef CCONFIGOMS_H
#define CCONFIGOMS_H

#include <QVector>

struct _CONGIG_OMS
{
public:
    struct _CONGIG_METHOD{
        double MassExtension=5;
        QString LimitInjectTime;
        QString ScaleRangeAGC;
        QString FunctionAGC;
    };
    struct _CONGIG_ACQUISITION{
        double Period= 1000;
    };
    struct _CONGIG_ANALYSIS{

    };
    struct _CONGIG_SYSTEM{

    };
    struct _CONGIG_MANUAL_TUNING{
        double MassExtension=5;
        bool showFit= false;
    };
    struct _CONGIG_AUTO_TUNING{
        double MassExtension=5;
    };
    struct _PARAM_FIT{
        uint enable= 1;
        QVector<QString> expect;//std::vector<double> expect;
        QVector<QString> current;//std::vector<double> current;
        std::vector<double> coefF;   //前向传递系数
        std::vector<double> coefB;   //反向传递系数
    };
};

#endif // CCONFIGOMS_H
