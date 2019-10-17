#include "QSwitchButton.h"

#include <QPainter>
#include <QRectF>

QSwitchButton::QSwitchButton(QWidget *parent)
    : QLabel(parent), isSelected(true), buttonWidth(100), buttonHeight(40)
    , backgroundColorSelected(Qt::white), backgroundColorNotSelected("#E7E3E7")
    , sliderColorSelected("#63BAFF"), sliderColorNotSelected("#7B797B")
    , rectRound(30), isAntiAliasing(true), buttonStyle(Ellipse), isEnable(true)
    , strTextOn("开"),strTextOff("关")
{
    resize(buttonWidth, buttonHeight);
    setMouseTracking(true);
}

QSwitchButton::~QSwitchButton()
{

}

void QSwitchButton::SetButtonStyle(ButtonStyle button_style)
{
    buttonStyle = button_style;
    repaint();
}

void QSwitchButton::SetSize(int width, int height)
{
    buttonWidth = width;
    buttonHeight = height;

    resize(buttonWidth, buttonHeight);

    repaint();
}

void QSwitchButton::SetSize(const QSize& size)
{
    buttonWidth = size.width();
    buttonHeight = size.height();

    resize(buttonWidth, buttonHeight);

    repaint();
}

void QSwitchButton::SetBackgroundColor(const QColor& selected_color, const QColor& not_selected_color)
{
    backgroundColorSelected = selected_color;
    backgroundColorNotSelected = not_selected_color;

    repaint();
}

void QSwitchButton::SetSliderColor(const QColor& selected_color, const QColor& not_selected_color)
{
    sliderColorSelected = selected_color;
    sliderColorNotSelected = not_selected_color;

    repaint();
}

void QSwitchButton::SetRound(int round)
{
    rectRound = round;
    repaint();
}

void QSwitchButton::EnableAntiAliasing(bool enable)
{
    isAntiAliasing = enable;
    repaint();
}

bool QSwitchButton::IsAntiAliasing()
{
    return isAntiAliasing;
}

void QSwitchButton::SetSelected(bool is_selected)
{
    isSelected = is_selected;

    repaint();
}

bool QSwitchButton::IsSelected()
{
    return isSelected;
}

void QSwitchButton::SetEnabel(bool is_enable)
{
    isEnable = is_enable;

    repaint();
}

bool QSwitchButton::IsEnable()
{
    return isEnable;
}

void QSwitchButton::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    if (isAntiAliasing)
    {
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);
    }

    if (!isEnable)  //未启用
    {
        painter.setPen(QPen(QColor("#F4F4F4")));
        painter.setBrush(QBrush(QColor("#F4F4F4")));
        DrawBackRect(&painter, QRectF(0, 0, buttonWidth, buttonHeight));

        painter.setPen(QPen(QColor("#ADB2B5")));
        painter.setBrush(QBrush(QColor("#ADB2B5")));
        DrawSliderRect(&painter, QRectF(buttonWidth*2/3-2, 2.5, buttonWidth/3, buttonHeight-5));
    }
    else if (isSelected)
    {
        painter.setPen(QPen(backgroundColorSelected));
        painter.setBrush(QBrush(backgroundColorSelected));
        DrawBackRect(&painter, QRectF(0, 0, buttonWidth, buttonHeight));

        painter.setPen(QPen(sliderColorSelected));
        painter.setBrush(QBrush(sliderColorSelected));
        DrawSliderRect(&painter, QRectF(buttonWidth*2/3-2, 2.5, buttonWidth/3, buttonHeight-5));
    }
    else
    {
        painter.setPen(QPen(backgroundColorNotSelected));
        painter.setBrush(QBrush(backgroundColorNotSelected));
        DrawBackRect(&painter,QRectF(0, 0, buttonWidth, buttonHeight));

        painter.setPen(QPen(sliderColorNotSelected));
        painter.setBrush(QBrush(sliderColorNotSelected));
        DrawSliderRect(&painter,QRectF(2, 2.5, buttonWidth/3, buttonHeight-5));
    }

    return QLabel::paintEvent(event);
}

void QSwitchButton::mousePressEvent(QMouseEvent *event)
{
    if (isEnable)
    {
        isSelected = !isSelected;
        repaint();

        emit clicked();
        emit clicked(isSelected);
    }

    return QLabel::mousePressEvent(event);
}

void QSwitchButton::mouseMoveEvent(QMouseEvent *event)
{
    setCursor(Qt::PointingHandCursor);

    return QLabel::mouseMoveEvent(event);
}

void QSwitchButton::DrawBackRect(QPainter* painter, const QRectF& rect)
{
    switch (buttonStyle)
    {
    case Rectage:
        painter->drawRoundRect(rect, rectRound, rectRound);
        break;
    case Ellipse:
        painter->drawEllipse(0, 0, buttonHeight, buttonHeight);
        painter->drawEllipse(buttonWidth - buttonHeight, 0, buttonHeight, buttonHeight);
        painter->drawRect(buttonHeight/2, 0, buttonWidth-buttonHeight, buttonHeight);
        DrawText(painter);
        break;
    default:
        break;
    }
}

void QSwitchButton::DrawText(QPainter *painter)
{
    painter->save();
    QFont font("Microsoft YaHei", 12, 50, false);
    painter->setFont(font);
    int x,y;
    if(isSelected){
        strText = strTextOn;
        x = 0;
        y = 0;
        painter->setPen(QPen(sliderColorSelected));
        painter->setBrush(QBrush(sliderColorSelected));
    }else{
        strText = strTextOff;
        x = buttonWidth - buttonHeight;
        y = 0;
        painter->setPen(QPen(sliderColorNotSelected));
        painter->setBrush(QBrush(sliderColorNotSelected));
    }
    painter->drawText(x,y,buttonHeight,buttonHeight,Qt::AlignCenter,strText);
    painter->restore();
}

void QSwitchButton::DrawSliderRect(QPainter* painter, const QRectF& rect)
{
    switch (buttonStyle)
    {
    case Rectage:
        painter->drawRoundRect(rect, rectRound, rectRound);
        break;
    case Ellipse:
        painter->drawEllipse(rect);
        break;
    default:
        break;
    }
}
