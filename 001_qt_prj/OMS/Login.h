#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLineEdit>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QtSql/QSqlError>
#include <sMainWindow.h>
#include <QPaintEvent>
#include <QTimer>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    bool createUserData(QString name);
    bool checkUserData(QString name);

private:
    Ui::Login *ui;
    QSqlQuery* query;
    sMainWindow *s;
    QString style[5];

    QTimer* currentTimer1;
    QTimer* currentTimer2;

    bool machPumpIsopen = false;
    bool elecPumpIsopen = false;



protected:
    void initSql();
    void createTable();
    bool logUser(QString name,QString password);
    bool signUp(QString name,QString password);
    void paintEvent(QPaintEvent* e);

private slots:
    void on_btnLogin_clicked();
    void on_btnRes_clicked();
    void on_btnSys_clicked();
    void onShowLogin();
    void operateMachPump();
    void operateElecPump();
    void onFirstState(double current);

signals:
    void userInfo(QString name);
    void sysInfo(bool state);
};

#endif // LOGIN_H
