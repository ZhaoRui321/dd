#ifndef SMYBUTTON_H
#define SMYBUTTON_H

#include <QLabel>
#include <QPainter>
#include <QPushButton>

enum _TAB_STYLE{_TAB_SHOW,_TAB_HIDE,_TAB_ENABLE};
namespace MyWidget
{
class sMyButton:public QWidget
{
    Q_OBJECT
public:
    enum _TYPE_BUTTON{_TYPE_TAB,_TYPE_MENU,_TYPE_TITLE};
    enum _STYLE_BUTTON{_STYLE_PRESS,_STYLE_MOVE,_STYLE_RELEASE};
    explicit sMyButton(QWidget *parent = 0);
    explicit sMyButton(QPixmap pressPicture,
              QPixmap releasePicture,
              QWidget *parent = 0);
    explicit sMyButton(QPixmap pressPicture,
              //QSize pSize,
              QFont pFont,
              QWidget *parent = 0);
    void setPressPicture(QPixmap pic){
        mPressPicture = pic;
    }
    void setReleasePicture(QPixmap pic){
        mReleasePicture = pic;
    }
    void setColor(QColor &pQColor){
        mColor = pQColor;
        update();
    }
    void setFont(QFont &pFont){
        mFont = pFont;
        update();
    }
    QColor getColor(){
        return mColor;
    }
    void setText(QString text){
        mText=text;
        update();
    }
    QString getText(){
        return mText;
    }
    void setSize(QSize iconSize){
        mSize=iconSize;
        //setMaximumSize(iconSize);
        setFixedSize(iconSize);
        update();
    }
    void setStyle(_TAB_STYLE TAB_STYLE1){
        m_TAB_STYLE = TAB_STYLE1;
        update();
    }
    _TAB_STYLE getStyle(){
        return m_TAB_STYLE;
    }

    void mousePressEvent (QMouseEvent *event){
        Q_UNUSED(event)
        m_STYLE_BUTTON=_STYLE_PRESS;
        update();
        emit ButtonClicked();//(void*)this
    }
    void mouseMoveEvent(QMouseEvent *event){
        Q_UNUSED(event)
        m_STYLE_BUTTON=_STYLE_MOVE;
        update();
    }
    void mouseReleaseEvent (QMouseEvent *event){
        Q_UNUSED(event)
        m_STYLE_BUTTON=_STYLE_RELEASE;
        update();

    }
signals:
    void ButtonClicked();
private:
    //QPainter* pPaintBK;
    _TYPE_BUTTON m_TYPE_BUTTON = _TYPE_TAB;
    QFont mFont;
    QColor mFontColor = Qt::black;
    QColor mColor = Qt::red;
    QString mText;
    QPixmap mPressPicture;
    QPixmap mReleasePicture;
    QPixmap mStylePic;
    QSize mSize;
    _TAB_STYLE m_TAB_STYLE = _TAB_SHOW;
    _STYLE_BUTTON m_STYLE_BUTTON=_STYLE_RELEASE;
    //QLabel mQLabel;
    void paintEvent(QPaintEvent *);
};
}


#endif // SMYBUTTON_H
