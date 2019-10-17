#include "sMyButton.h"

using namespace MyWidget;

sMyButton::sMyButton(QWidget *parent):
    QWidget(parent),
    mSize(0,0),
    m_TYPE_BUTTON(_TYPE_MENU)
{
    mFont.setFamily("Microsoft YaHei");
    mFont.setPointSize(9);
    setSize(QSize(56,64));
}

sMyButton::sMyButton(QPixmap pressPicture,
          QPixmap releasePicture,
          QWidget *parent):
    QWidget(parent),
    mSize(0,0),
    mPressPicture(pressPicture),
    mReleasePicture(releasePicture)
{
    mFont.setFamily("Microsoft YaHei");
    mFont.setPointSize(9);
    setSize(QSize(81,38));
}

sMyButton::sMyButton(QPixmap pressPicture,
                     //QSize pSize,
                     QFont pFont,
          QWidget *parent):
    QWidget(parent),
    //mSize(pSize),
    mPressPicture(pressPicture),
    mReleasePicture(pressPicture),
    m_TYPE_BUTTON(_TYPE_TITLE)
{
    mFont=pFont;
    setSize(pressPicture.size());
}

void sMyButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter pPaintBK(this);
    //pPaintBK.setPen(QPen(mColor,1,Qt::SolidLine));
    //pPaintBK.setBrush(QBrush(mColor,Qt::SolidPattern));
    //pPaintBK.drawRect(width()/2, 0, width(), height());
    if(m_TYPE_BUTTON == _TYPE_TAB){
        switch (m_STYLE_BUTTON) {
        case _STYLE_PRESS:
            pPaintBK.setPen(QPen(Qt::black,1,Qt::SolidLine));
            pPaintBK.drawLine(QPoint(0,0),QPoint(width()-1,0));
            pPaintBK.drawLine(QPoint(0,height()-1),QPoint(width()-1,height()-1));
            break;
        case _STYLE_MOVE:
            break;
        case _STYLE_RELEASE:
            break;
        default:
            break;
        }
        switch(m_TAB_STYLE){
        case _TAB_SHOW:
            mStylePic=mPressPicture;
            pPaintBK.setPen(QPen(Qt::black,1,Qt::SolidLine));
            pPaintBK.drawLine(QPoint(0,0),QPoint(width()-1,0));
            pPaintBK.drawLine(QPoint(0,height()-1),QPoint(width()-1,height()-1));
            break;
        case _TAB_HIDE:
            mStylePic=mPressPicture;
            break;
        case _TAB_ENABLE:
            mStylePic=mReleasePicture;
            break;
        default:break;
        }

        if((mSize.height()==0)||(mSize.width()==0)){
            mSize.setHeight(mStylePic.height());
            mSize.setWidth(mStylePic.width());
        }
        pPaintBK.drawPixmap(0,0,mSize.width(),mSize.height(),mStylePic);
        pPaintBK.setPen(QPen(Qt::black,4,Qt::SolidLine));
        pPaintBK.setFont(mFont);
        if(mText.size()>8)
            pPaintBK.drawText(rect(), Qt::TextWrapAnywhere, mText);
        else
            pPaintBK.drawText(rect(), Qt::AlignLeft|Qt::AlignVCenter, mText);
    }else if(m_TYPE_BUTTON == _TYPE_MENU){
        pPaintBK.setPen(QPen(QColor(218,200,37),1,Qt::SolidLine));
        pPaintBK.drawLine(QPoint(0,0),QPoint(0,height()));
        pPaintBK.setPen(QPen(QColor(228,218,208),1,Qt::SolidLine));
        pPaintBK.drawLine(QPoint(1,0),QPoint(1,height()));
        pPaintBK.setPen(QPen(QColor(218,200,37),4,Qt::SolidLine));
        pPaintBK.setFont(mFont);
        pPaintBK.drawText(rect(), Qt::TextWrapAnywhere|Qt::AlignCenter, mText);
    }else if(m_TYPE_BUTTON == _TYPE_TITLE){
        pPaintBK.drawPixmap(0,0,mSize.width(),mSize.height(),mPressPicture);
        pPaintBK.setPen(QPen(Qt::black,4,Qt::SolidLine));
        pPaintBK.setFont(mFont);

        QRectF tmpRect=rect();
        tmpRect.setRight(tmpRect.right()-200);
        pPaintBK.drawText(tmpRect, Qt::AlignCenter, mText);
    }
}
