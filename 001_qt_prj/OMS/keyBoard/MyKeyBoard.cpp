#include "MyKeyBoard.h"
#include "ui_MyKeyBoard.h"
#include "qdebug.h"
#include <QDesktopWidget>
#include <QTimer>


MyKeyBoard* MyKeyBoard::_instance = 0;
MyKeyBoard::MyKeyBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyKeyBoard)
{
    ui->setupUi(this);
    this->InitForm();//初始化窗体数据
    this->InitProperty();//初始化属性
    this->ChangeStyle();//改变样式
    this->setStyleSheet("QPushButton{border:2px solid rgb(216,216,216);"
                        "background-color: rgb(216,216,216);border-radius: 10px;}");
//    QRect rect = QApplication::desktop()->rect();
//    this->resize(rect.width()-300,rect.height()/3);
}

MyKeyBoard::~MyKeyBoard()
{
    delete ui;
}

void MyKeyBoard::Init(QString style, int fontSize)
{
    this->currentStyle = style;
    this->currentFontSize = fontSize;
    this->ChangeStyle();

}


bool MyKeyBoard::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        if (currentEditType != "") {
//            if (obj != ui->btnClose) {
//                this->setVisible(true);
//            }
            btnPress = (QPushButton *)watched;
            if (checkPress()) {
                isPress = true;
                timerPress->start(500);
            }
        }
        return false;
    } else if (event->type() == QEvent::MouseButtonRelease) {
        btnPress = (QPushButton *)watched;
        if (checkPress()) {
            isPress = false;
            timerPress->stop();
        }
        return false;
    }
    return QWidget::eventFilter(watched, event);

}


void MyKeyBoard::focusChanged(QWidget *oldWidget, QWidget *nowWidget)
{
    //qDebug() << "oldWidget:" << oldWidget << " nowWidget:" << nowWidget;
    if (nowWidget != 0 && !this->isAncestorOf(nowWidget)) {
        //在Qt5和linux系统中(嵌入式linux除外),当输入法面板关闭时,焦点会变成无,然后焦点会再次移到焦点控件处
        //这样导致输入法面板的关闭按钮不起作用,关闭后马上有控件获取焦点又显示.
        //为此,增加判断,当焦点是从有对象转为无对象再转为有对象时不要显示.
        //这里又要多一个判断,万一首个窗体的第一个焦点就是落在可输入的对象中,则要过滤掉
#ifndef __arm__
        if (oldWidget == 0x0 && !isFirst) {
            return;
        }
#endif
        if(!nowWidget->property("number").toBool()){
            this->setVisible(false);
            return;
        }
        isFirst = false;
        if (nowWidget->inherits("QLineEdit")) {
            currentLineEdit = (QLineEdit *)nowWidget;
            currentEditType = "QLineEdit";
            this->setVisible(true);
        } else if (nowWidget->inherits("QTextEdit")) {
            currentTextEdit = (QTextEdit *)nowWidget;
            currentEditType = "QTextEdit";
            this->setVisible(true);
        } else if (nowWidget->inherits("QPlainTextEdit")) {
            currentPlain = (QPlainTextEdit *)nowWidget;
            currentEditType = "QPlainTextEdit";
            this->setVisible(true);
        } else if (nowWidget->inherits("QTextBrowser")) {
            currentBrowser = (QTextBrowser *)nowWidget;
            currentEditType = "QTextBrowser";
            this->setVisible(true);
        } else if (nowWidget->inherits("QComboBox")) {
            QComboBox *cbox = (QComboBox *)nowWidget;
            //只有当下拉选择框处于编辑模式才可以输入
            if (cbox->isEditable()) {
                currentLineEdit = cbox->lineEdit() ;
                currentEditType = "QLineEdit";
                this->setVisible(true);
            }
        } else if (nowWidget->inherits("QSpinBox") ||
                   nowWidget->inherits("QDoubleSpinBox") ||
                   nowWidget->inherits("QDateEdit") ||
                   nowWidget->inherits("QTimeEdit") ||
                   nowWidget->inherits("QDateTimeEdit")) {
            currentWidget = nowWidget;
            currentEditType = "QWidget";
            this->setVisible(true);
        } else {
            currentWidget = 0;
            currentLineEdit = 0;
            currentTextEdit = 0;
            currentPlain = 0;
            currentBrowser = 0;
            currentEditType = "";
            this->setVisible(false);
        }

        QDesktopWidget *pDesk = QApplication::desktop();
        int x = pDesk->screenGeometry(0).width() - this->width();
        int y = pDesk->screenGeometry(0).height() - this->height();
        this->setGeometry(x/2,y-100,this->width(),this->height());
    }

    Q_UNUSED(oldWidget);//未使用参数

}


void MyKeyBoard::btn_clicked()
{
    //如果当前焦点控件类型为空,则返回不需要继续处理
    if (currentEditType == "") {
        this->setVisible(false);
        return;
    }

    QPushButton *btn = (QPushButton *)sender();
    QString objectName = btn->objectName();
    if (objectName == "btnDelete") {
        deleteValue();
    } else if (objectName == "btnSpace") {
        insertValue(" ");
    } else {
        QString value = btn->text();
        insertValue(value);
    }

}

void MyKeyBoard::changeStyle(QString topColor, QString bottomColor,
                             QString borderColor, QString textColor)
{
    QStringList qss;
    qss.append(QString("QWidget#frmNum{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 %1,stop:1 %2);}")
               .arg(topColor).arg(bottomColor));
    qss.append("QPushButton{padding:5px;border-radius:3px;}");
    qss.append(QString("QPushButton:hover{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 %1,stop:1 %2);}")
               .arg(topColor).arg(bottomColor));
    qss.append(QString("QLabel,QPushButton{font-size:%1pt;color:%2;}")
               .arg(currentFontSize).arg(textColor));
    qss.append(QString("QPushButton#btnPre,QPushButton#btnNext,QPushButton#btnClose{padding:5px;}"));
    qss.append(QString("QPushButton{border:1px solid %1;border-radius: 10px;}")
               .arg(borderColor));
    qss.append(QString("QLineEdit{border:1px solid %1;border-radius:5px;padding:2px;background:none;selection-background-color:%2;selection-color:%3;}")
               .arg(borderColor).arg(bottomColor).arg(topColor));
    this->setStyleSheet(qss.join(""));

}

void MyKeyBoard::reClicked()
{
    if (isPress) {
        timerPress->setInterval(30);
        btnPress->click();
    }
}

bool MyKeyBoard::checkPress()
{
    bool num_ok = btnPress->property("btnNum").toBool();
    bool other_ok = btnPress->property("btnOther").toBool();
    bool alp_ok = btnPress->property("btnAlp").toBool();
    if (num_ok || other_ok || alp_ok) {
        return true;
    }
    return false;

}


void MyKeyBoard::InitForm()
{
    this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    isFirst = true;
    isPress = false;
    timerPress = new QTimer(this);
    connect(timerPress, SIGNAL(timeout()), this, SLOT(reClicked()));
    currentWidget = 0;

    //如果需要更改输入法面板的样式,改变currentStyle这个变量即可
    //blue--淡蓝色  dev--dev风格  black--黑色  brown--灰黑色  lightgray--浅灰色  darkgray--深灰色  gray--灰色  silvery--银色
    currentStyle = "";

    //输入法面板字体大小,如果需要更改面板字体大小,该这里即可
    currentFontSize = 100;

    QList<QPushButton *> btn = this->findChildren<QPushButton *>();
    foreach (QPushButton * b, btn) {
        connect(b, SIGNAL(clicked()), this, SLOT(btn_clicked()));
    }

    //绑定全局改变焦点信号槽
    connect(qApp, SIGNAL(focusChanged(QWidget *, QWidget *)),
            this, SLOT(focusChanged(QWidget *, QWidget *)));
    //绑定按键事件过滤器
    qApp->installEventFilter(this);

}


void MyKeyBoard::InitProperty()
{
    ui->btn0->setProperty("btnNum", true);
    ui->btn1->setProperty("btnNum", true);
    ui->btn2->setProperty("btnNum", true);
    ui->btn3->setProperty("btnNum", true);
    ui->btn4->setProperty("btnNum", true);
    ui->btn5->setProperty("btnNum", true);
    ui->btn6->setProperty("btnNum", true);
    ui->btn7->setProperty("btnNum", true);
    ui->btn8->setProperty("btnNum", true);
    ui->btn9->setProperty("btnNum", true);

    ui->btnQ->setProperty("btnAlp",true);
    ui->btnW->setProperty("btnAlp",true);
    ui->btnE->setProperty("btnAlp",true);
    ui->btnR->setProperty("btnAlp",true);
    ui->btnT->setProperty("btnAlp",true);
    ui->btnY->setProperty("btnAlp",true);
    ui->btnU->setProperty("btnAlp",true);
    ui->btnI->setProperty("btnAlp",true);
    ui->btnO->setProperty("btnAlp",true);
    ui->btnP->setProperty("btnAlp",true);
    ui->btnA->setProperty("btnAlp",true);
    ui->btnS->setProperty("btnAlp",true);
    ui->btnD->setProperty("btnAlp",true);
    ui->btnF->setProperty("btnAlp",true);
    ui->btnG->setProperty("btnAlp",true);
    ui->btnH->setProperty("btnAlp",true);
    ui->btnJ->setProperty("btnAlp",true);
    ui->btnK->setProperty("btnAlp",true);
    ui->btnL->setProperty("btnAlp",true);
    ui->btnZ->setProperty("btnAlp",true);
    ui->btnX->setProperty("btnAlp",true);
    ui->btnC->setProperty("btnAlp",true);
    ui->btnV->setProperty("btnAlp",true);
    ui->btnB->setProperty("btnAlp",true);
    ui->btnN->setProperty("btnAlp",true);
    ui->btnM->setProperty("btnAlp",true);

    ui->btnCut->setProperty("btnOther",true);
    ui->btnDot->setProperty("btnOther", true);
    ui->btnSpace->setProperty("btnOther", true);
    ui->btnDelete->setProperty("btnOther",true);
}


void MyKeyBoard::ChangeStyle()
{
    if (currentStyle == "blue") {
        changeStyle("#DEF0FE", "#C0DEF6", "#C0DCF2", "#386487");
    } else if (currentStyle == "dev") {
        changeStyle("#C0D3EB", "#BCCFE7", "#B4C2D7", "#324C6C");
    } else if (currentStyle == "gray") {
        changeStyle("#E4E4E4", "#A2A2A2", "#A9A9A9", "#000000");
    } else if (currentStyle == "lightgray") {
        changeStyle("#EEEEEE", "#E5E5E5", "#D4D0C8", "#6F6F6F");
    } else if (currentStyle == "darkgray") {
        changeStyle("#D8D9DE", "#C8C8D0", "#A9ACB5", "#5D5C6C");
    } else if (currentStyle == "black") {
        changeStyle("#4D4D4D", "#292929", "#D9D9D9", "#CACAD0");
    } else if (currentStyle == "brown") {
        changeStyle("#667481", "#566373", "#C2CCD8", "#E7ECF0");
    } else if (currentStyle == "silvery") {
        changeStyle("#E1E4E6", "#CCD3D9", "#B2B6B9", "#000000");
    }

}

void MyKeyBoard::insertValue(QString value)
{
    if (currentEditType == "QLineEdit") {
        currentLineEdit->insert(value);
    } else if (currentEditType == "QTextEdit") {
        currentTextEdit->insertPlainText(value);
    } else if (currentEditType == "QPlainTextEdit") {
        currentPlain->insertPlainText(value);
    } else if (currentEditType == "QTextBrowser") {
        currentBrowser->insertPlainText(value);
    } else if (currentEditType == "QWidget") {
        QKeyEvent keyPress(QEvent::KeyPress, 0, Qt::NoModifier, QString(value));
        QApplication::sendEvent(currentWidget, &keyPress);
    }
}

void MyKeyBoard::deleteValue()
{
    if (currentEditType == "QLineEdit") {
        currentLineEdit->backspace();
    } else if (currentEditType == "QTextEdit") {
        //获取当前QTextEdit光标,如果光标有选中,则移除选中字符,否则删除光标前一个字符
        QTextCursor cursor = currentTextEdit->textCursor();
        if(cursor.hasSelection()) {
            cursor.removeSelectedText();
        } else {
            cursor.deletePreviousChar();
        }
    } else if (currentEditType == "QPlainTextEdit") {
        //获取当前QTextEdit光标,如果光标有选中,则移除选中字符,否则删除光标前一个字符
        QTextCursor cursor = currentPlain->textCursor();
        if(cursor.hasSelection()) {
            cursor.removeSelectedText();
        } else {
            cursor.deletePreviousChar();
        }
    } else if (currentEditType == "QTextBrowser") {
        //获取当前QTextEdit光标,如果光标有选中,则移除选中字符,否则删除光标前一个字符
        QTextCursor cursor = currentBrowser->textCursor();
        if(cursor.hasSelection()) {
            cursor.removeSelectedText();
        } else {
            cursor.deletePreviousChar();
        }
    } else if (currentEditType == "QWidget") {
        QKeyEvent keyPress(QEvent::KeyPress, Qt::Key_Delete, Qt::NoModifier, QString());
        QApplication::sendEvent(currentWidget, &keyPress);
    }

}

