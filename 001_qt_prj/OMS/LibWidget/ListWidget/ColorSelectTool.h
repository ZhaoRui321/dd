#ifndef COLORSELECTTOOL_H
#define COLORSELECTTOOL_H
#include <QColor>

class ColorSelectTool
{
public:
    ColorSelectTool();

    QColor getColor();

    void reInitColor(QColor color);

private:
    QList<QPair<QColor,bool>> colorList;
};

#endif // COLORSELECTTOOL_H
