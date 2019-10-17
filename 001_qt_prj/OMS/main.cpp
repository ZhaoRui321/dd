//#include "mainwindow.h"
#include "sMainWindow.h"
#include <QApplication>
#include <QQmlEngine>
//#include "FileContent.h"
#include "frmnum.h"
#include "keyBoard/MyKeyBoard.h"
#include "Login.h"
#include "HighPre.h"
#include "Temperature.h"
#include "SaveFile.h"

int main(int argc, char *argv[])
{
    //qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QApplication a(argc, argv);
    //qmlRegisterType<FileContent>("test.filecontent", 1, 0, "FileContentItem");

    qApp->setFont(QFont("Microsoft YaHei", 10));
    frmNum::Instance()->Init("brown",20);//set brown--灰黑色
    MyKeyBoard::Instance()->Init("Black",40);
    //MainWindow w;
    //w.show();
    //sMainWindow w;
    Login w;
    w.showFullScreen();
    //HighPre w;
//    Temperature w;
//    SaveFile w;
//    w.show();

    return a.exec();
}
