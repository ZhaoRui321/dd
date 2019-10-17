#include "ColorSelectTool.h"

ColorSelectTool::ColorSelectTool()
{
    QList<QColor> list;
    list << QColor("#FF8C00") << QColor("#FF0000") << QColor("#00FF7F")
         << QColor("#1E90FF") << QColor("#0000CD") << QColor("#483D8B")
         << QColor("#8B008B") << QColor("#DC143C");

    for(int i = 0; i < list.size(); i++ ){
        QPair<QColor,bool> temp;
        temp.first = list[i];
        temp.second = false;
        colorList.append(temp);
    }

}

QColor ColorSelectTool::getColor()
{
    for(QList<QPair<QColor,bool>>::iterator it = colorList.begin();it != colorList.end() ; it++){
        if((*it).second == false){
            (*it).second = true;
            return (*it).first;
        }
    }
}

void ColorSelectTool::reInitColor(QColor color)
{
    for(QList<QPair<QColor,bool>>::iterator it = colorList.begin();it != colorList.end() ; it++){
        if((*it).first == color){
            (*it).second = false;
        }
    }
}
