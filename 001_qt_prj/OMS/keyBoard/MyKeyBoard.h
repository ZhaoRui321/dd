#ifndef MYKEYBOARD_H
#define MYKEYBOARD_H

#include <QWidget>
#include <QPushButton>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QTextBrowser>
#include <QComboBox>
#include <QEvent>

namespace Ui {
class MyKeyBoard;
}

class MyKeyBoard : public QWidget
{
    Q_OBJECT

public:
    explicit MyKeyBoard(QWidget *parent = 0);
    ~MyKeyBoard();

    static MyKeyBoard* Instance(){
        if(!_instance){
            _instance = new MyKeyBoard();
        }
        return _instance;
    }

    //初始化面板状态,包括字体大小
    void Init(QString style, int fontSize);

protected:
    //事件过滤器
    bool eventFilter(QObject *watched, QEvent *event);

private slots:

    //焦点改变事件槽函数处理
    void focusChanged(QWidget *oldWidget, QWidget *nowWidget);
    //输入法面板按键处理
    void btn_clicked();
    //改变输入法面板样式
    void changeStyle(QString topColor, QString bottomColor,
                     QString borderColor, QString textColor);
    //定时器处理退格键
    void reClicked();

private:
    Ui::MyKeyBoard *ui;
    static MyKeyBoard* _instance;

    bool isPress;                   //是否长按退格键
    QPushButton *btnPress;          //长按按钮
    QTimer *timerPress;             //退格键定时器
    bool checkPress();              //校验当前长按的按钮

    bool isFirst;                   //是否首次加载
    void InitForm();                //初始化窗体数据
    void InitProperty();            //初始化属性
    void ChangeStyle();             //改变样式

    QWidget *currentWidget;         //当前焦点的对象
    QLineEdit *currentLineEdit;     //当前焦点的单行文本框
    QTextEdit *currentTextEdit;     //当前焦点的多行文本框
    QPlainTextEdit *currentPlain;   //当前焦点的富文本框
    QTextBrowser *currentBrowser;   //当前焦点的文本浏览框

    QString currentEditType;        //当前焦点控件的类型
    QString currentStyle;           //当前输入法面板样式
    int currentFontSize;            //当前输入法面板字体大小
    void insertValue(QString value);//插入值到当前焦点控件
    void deleteValue();             //删除当前焦点控件的一个字符
};

#endif // MYKEYBOARD_H
