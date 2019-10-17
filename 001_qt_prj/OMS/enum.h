#ifndef ENUM_H
#define ENUM_H

enum MyEnum
{
    GRAP = 2,               //控件四周间隙，可更改;
    WIDTH = 350+2*GRAP,     //+2*GRAP不能更改，只能改前面的数字,如将400改为300或500，下同;
    HEIGHT = 230+2*GRAP,
};

#endif // ENUM_H
