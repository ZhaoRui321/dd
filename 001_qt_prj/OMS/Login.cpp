#include "Login.h"
#include "ui_Login.h"
#include <QMessageBox>
#include <QDebug>
#include <QDesktopWidget>
#include <QPushButton>
#include <QPainter>
#include <QTimer>
#include <QList>
#include <QPen>
#include <QBrush>
#include <QRect>
#include <QDir>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    s = new sMainWindow();
    QDesktopWidget *pDesk = QApplication::desktop();
    int x = pDesk->screenGeometry(0).width() - ui->loginWidget->width();
    int y = pDesk->screenGeometry(0).height() - ui->loginWidget->height();
    ui->loginWidget->move(x/2,y/2);
    //lineEdit上半
    style[0] = "background-color: white; border-top-left-radius: 20px; border-top-right-radius: 20px;";
    //lineEdit下半
    style[1] = "background-color: white; border-bottom-left-radius: 20px; border-bottom-right-radius: 20px;";
    //按钮
    style[2] = "QPushButton{border-radius: 20px;background-color: white;font-size: 30px;} QPushButton:hover{color: blue;background-color: gray;font-size: 35px;}";
    //系统未开启
    style[3] = QString("QPushButton{border-radius: %1px;background-color: gray;font-size: 30px;}").arg(ui->btnSys->width()/2);
    //系统开启
    style[4] = QString("QPushButton{border-radius: %1px;background-color: red;font-size: 30px;}").arg(ui->btnSys->width()/2);

    ui->CountEdit->setStyleSheet(style[0]);
    ui->passWord->setStyleSheet(style[1]);
    ui->btnLogin->setStyleSheet(style[2]);
    ui->btnRes->setStyleSheet(style[2]);
    ui->btnSys->setStyleSheet(style[3]);
    ui->CountEdit->setProperty("number",true);
    ui->passWord->setProperty("number",true);
    ui->passWord->setEchoMode(QLineEdit::Password);
    ui->CountEdit->setPlaceholderText("账号");
    ui->passWord->setPlaceholderText("密码");

    currentTimer1 = new QTimer(this);
    currentTimer2 = new QTimer(this);
    connect(currentTimer2,SIGNAL(timeout()),this,SLOT(operateElecPump()));
    connect(currentTimer1,SIGNAL(timeout()),this,SLOT(operateMachPump()));

    //this->initSql();
    connect(this,SIGNAL(userInfo(QString)),s,SLOT(onUserInfo(QString)));
    connect(s,SIGNAL(showLogin()),this,SLOT(onShowLogin()));
    connect(s,SIGNAL(firstState(double)),this,SLOT(onFirstState(double)));
    connect(this,SIGNAL(sysInfo(bool)),s,SLOT(onSysInfo(bool)));
    //emit sysInfo(false);

}

Login::~Login()
{
    delete ui;
}

void Login::onFirstState(double current)
{
    if(current==0)
        return;
    if(current < LOW){
        machPumpIsopen = true;
        elecPumpIsopen = true;
        ui->btnSys->setText("关闭系统");
        emit sysInfo(true);
    }else if(current < HIGH){
        machPumpIsopen = true;
    }
}

void Login::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); //反锯齿
    QRect rect = ui->stateLightWidget->rect();
    QPoint pos = QPoint(rect.left(),rect.top());
    pos = ui->stateLightWidget->mapToGlobal(pos);
    QPoint pos1 = QPoint(pos.x()+rect.width()/4,pos.y()+rect.height()/2);
    QPoint pos2 = QPoint(pos.x()+rect.width()/2,pos.y()+rect.height()/2);
    QPoint pos3 = QPoint(pos.x()+rect.width()*3/4,pos.y()+rect.height()/2);

    QColor color1 = QColor(Qt::green);
    QColor color2 = QColor(Qt::red);
    QColor color3 = QColor(Qt::yellow);
    painter.setPen(Qt::transparent);
    int radius = 10;

    if(s->getVacuumNum()>6.5){
        painter.setBrush(color1);
        painter.drawEllipse(pos1,radius,radius);
        painter.setBrush(Qt::gray);
        painter.drawEllipse(pos2,radius,radius);
        painter.setBrush(Qt::gray);
        painter.drawEllipse(pos3,radius,radius);
    }else if(s->getVacuumNum() > 3.3){
        painter.setBrush(color1);
        painter.drawEllipse(pos1,radius,radius);
        painter.setBrush(color2);
        painter.drawEllipse(pos2,radius,radius);
        painter.setBrush(Qt::gray);
        painter.drawEllipse(pos3,radius,radius);
    }else if(s->getVacuumNum() > 2.5){
        painter.setBrush(color1);
        painter.drawEllipse(pos1,radius,radius);
        painter.setBrush(color2);
        painter.drawEllipse(pos2,radius,radius);
        painter.setBrush(color3);
        painter.drawEllipse(pos3,radius,radius);
    }else{
        painter.setBrush(Qt::gray);
        painter.drawEllipse(pos1,radius,radius);
        painter.drawEllipse(pos2,radius,radius);
        painter.drawEllipse(pos3,radius,radius);
    }
}


void Login::initSql()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("User");
    db.setUserName("root");
    db.setPassword("123456");
    if(db.open()){
        qDebug() << "connect successfully";
        //createTable();
        return;
    }else{
        qDebug() << "connect failed";
        return;
    }

}

void Login::createTable()
{
    query=new QSqlQuery;
    query->exec("create table user(name VARCHAR(30) PRIMARY KEY UNIQUE NOT NULL,password VARCHAR(30))");

    /*创建root用户*/
    query->exec("insert into user value('root', 'root')");

}

bool Login::logUser(QString name, QString password)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("User");
    if(!db.open()){
        qDebug() << "open failed" << db.lastError().text();
        return false;
    }
    QString str=QString("select * from user where name= '%1' and password= '%2'").arg(name).arg(password);
    query = new QSqlQuery;
    query->exec(str);
    query->last();

    int record=query->at()+1;
    qDebug() << record << query->at();
    db.close();
    if(record == -1)
        return false;
    return true;

}

bool Login::signUp(QString name, QString password)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("User");
    if(!db.open()){
        qDebug() << "open failed"<< db.lastError().text();
        return false;
    }
    QString str=QString("select * from user where name='%1'").arg(name);
    query=new QSqlQuery;
    query->exec(str);
    query->last();

    int record=query->at()+1;
    if(record != -1)
        return false;

    str=QString("insert into user values('%1','%2')").arg(name).arg(password);
    bool ret = query->exec(str);
    if(!ret)
        qDebug() << db.lastError().text();
    db.close();

    return ret;


}

bool Login::createUserData(QString name)
{
    QString path = QCoreApplication::applicationDirPath() + "/" + name;
    QDir dir;
    if(!dir.exists(path)){
        bool res = dir.mkpath(path);
        //qDebug() << "------" << res << "--------";
    }

    QString ini = QCoreApplication::applicationDirPath() + "/tuning.ini";
    if(!QFile::exists(ini)){
        qDebug() << "--------" << "配置文件丢失" << "--------";
        return false;
    }

    QString iniNew = path + "/tuning.ini";
    QString dataNew = path + "/data";
    if(!dir.exists(dataNew)){
        bool res = dir.mkpath(dataNew);
        //qDebug() << "------" << res << "--------";
    }

    if(!QFile::copy(ini,iniNew)){
        return false;
    }

    return true;

}

bool Login::checkUserData(QString name)
{
    QString path = QCoreApplication::applicationDirPath() + "/" + name;

    QString ini = path + "/tuning.ini";
    QString dataPath = path + "/data";
    QDir dir;

    if(!QFile::exists(path) || !QFile::exists(ini) || !dir.exists(dataPath)){
        createUserData(name);
        return false;
    }

    return true;

}

void Login::on_btnLogin_clicked()
{
    QString name = ui->CountEdit->text();
    QString password = ui->passWord->text();

    if(name.isEmpty() || password.isEmpty()){
        qDebug() << "账号密码不能为空";
        return;
    }

    bool ret = logUser(name,password);
    if(ret){
        qDebug() << "login successsfully";
        //QMessageBox::information(this,"","login successfully");
        ui->CountEdit->clear();
        ui->passWord->clear();
        checkUserData(name);

        s->showFullScreen();
        this->hide();

        emit userInfo(name);

    }else{
        qDebug() << "login failed";
        QMessageBox::warning(this,"","login failed!");
        ui->CountEdit->clear();
        ui->passWord->clear();
    }

}

void Login::on_btnRes_clicked()
{
    QString name = ui->CountEdit->text();
    QString password = ui->passWord->text();

    if(name.isEmpty() || password.isEmpty()){
        qDebug() << "账号密码不能为空";
        return;
    }

    bool ret = signUp(name,password);
    if(ret){
        qDebug() << "register successsfully";
        bool res = createUserData(name);
        if(!res)
            qDebug() << "创建个人文件夹失败....";
        ui->CountEdit->clear();
        ui->passWord->clear();
    }else{
        qDebug() << "register failed";
        ui->CountEdit->clear();
        ui->passWord->clear();
    }
}

void Login::on_btnSys_clicked()
{
    update();
    if(ui->btnSys->text() == "开启系统" || ui->btnSys->text() == "关闭中"){
        if(!machPumpIsopen){
            s->getSystemWidget()->getStateWidget()->setMachPump(true);
            machPumpIsopen = true;
        }
        ui->btnSys->setText("开启中");
        ui->btnSys->setStyleSheet(style[3]);
        currentTimer2->start(1000);
        if(currentTimer1->isActive())
            currentTimer1->stop();
    }else{
        //emit sysInfo(false);
        if(elecPumpIsopen){
            s->elecPumpCCSCMD(false);
            s->getSystemWidget()->getStateWidget()->setFPump(false);
            elecPumpIsopen = false;
        }
        ui->btnSys->setText("关闭中");
        ui->btnSys->setStyleSheet(style[4]);
        currentTimer1->start(1000);
        if(currentTimer2->isActive())
            currentTimer2->stop();
    }
}

void Login::onShowLogin()
{
    qDebug() << "切换页面";
    this->showFullScreen();
    s->hide();
}


void Login::operateMachPump()
{
    if(s->getVacuumNum() > 6.5){
        if(machPumpIsopen){
            s->getSystemWidget()->getStateWidget()->setMachPump(false);
            machPumpIsopen = false;
        }
        ui->btnSys->setText("开启系统");
        machPumpIsopen = false;
        elecPumpIsopen = false;
        currentTimer1->stop();
        update();
    }else if(s->getVacuumNum() > 5){
        if(machPumpIsopen){
            s->getSystemWidget()->getStateWidget()->setMachPump(false);
            machPumpIsopen = false;
            update();
        }
    }

}

void Login::operateElecPump()
{
    if(s->getVacuumNum() < 3.3){
        if(!elecPumpIsopen){
            s->elecPumpCCSCMD(true);
            elecPumpIsopen = true;
        }
        ui->btnSys->setText("关闭系统");
        currentTimer2->stop();
        emit sysInfo(true);
        update();
    }else if(s->getVacuumNum() < 6.5){
        if(!elecPumpIsopen){
            s->elecPumpCCSCMD(true);
            elecPumpIsopen = true;
            update();
        }
    }
}
