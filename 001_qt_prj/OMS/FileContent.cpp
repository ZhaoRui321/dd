#include "filecontent.h"
#include <QDebug>
#include <QFileInfo>
#include <QTextCodec>
#include <QDir>
#include <QFile>
#include <QFileDialog>

FileContent::FileContent(QObject *parent)
{

}

FileContent::~FileContent() {
    delete file;
}

QString FileContent::getFileName() {
    return this->filename;
}

QString FileContent::getDataPath()
{
    return this->datapath;
}

bool FileContent::setFileName(const QString &filename) {
    if(this->filename != NULL)
        this->filename.clear();
    if(filename.isEmpty())
        return 0;

    this->filename = filename;
   file = new QFile(this->datapath+filename);
   return 1;
}

void FileContent::setDataPath(const QString &datapath)
{
    this->datapath = datapath;
}

QString FileContent::getContent() {
    if(filename.isEmpty())
        return content;
    if( content.length() == 0){
        file->open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(file);
        content = in.readAll();
        if( content.length() == 0) {
            qDebug() << "[Warning] FileContent: file " << this->datapath+this->filename << "is empty" << endl;
        }
    }
    file->close();
    return content;
}

bool FileContent::writeContent(const QString &data)
{
    qDebug() << "writing.....";
    if (filename.isEmpty())
        return false;
    QFile file(datapath+filename);
    QFileInfo fileInfo(file.fileName());
    qDebug() << "file path: " << fileInfo.absoluteFilePath();
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text | QFile::Truncate))    //只读并且数据清除chong重写
        return false;
    QTextStream out(&file);
    out << data;
    file.close();
    return true;
}

bool FileContent::deleteContent(const QString &filename)
{
    qDebug() << "delete....";
    if(filename.isEmpty())
        return false;
    QString str = datapath+filename;
//    //QString str = QFileDialog::getOpenFileName(this,"chance","/","All file(*.*)");
    qDebug() << str;
    QFile file(str);
    if(file.exists()){
        if(file.remove())
            qDebug()<< "成功删除";
        qDebug() << "存在";
        return 1;
        }
    else{
        qDebug() << "不存在";
        return 0;
    }
//    if(QFile::remove(str))
//        return true;
//    else
//        return false;
}

QStringList FileContent::getFileNames()
{
    QDir dir(datapath);
    QStringList fileType;
    //nameFilers << "*.set" << "*.setting";
    fileNames = dir.entryList(fileType,QDir::Files | QDir::Readable, QDir::Name);
    return fileNames;
}

int FileContent::getFileCount()
{
    return fileNames.size();
}

QString FileContent::fileN(int i)
{
    return fileNames[i];
}

int FileContent::dataN(int i)
{
    QStringList datalist = getContent().split("\n");
    return datalist[i].toInt();
}

bool FileContent::justFile()
{
    if(fileNames.isEmpty())
        return 0;
    else
        return 1;
}




//QString FileContent::loadFileContent()
//{
//    QStringList files = getFIleNames();
//    for(QList<QString>::iterator it = files.begin() ; it != files.end(); it++){
//        filename = *it;
//        QStringList set = getContent();
//        res.insertMulti(filename,set);
//    }
//    return res;
//}

void FileContent::clearContent() {
    content.clear();
}


bool FileContent::resetfilename(QString mfilename) {
    bool res = QFile::rename(this->datapath+filename,this->datapath+mfilename);
    filename = mfilename;
    if(res)
    qDebug() << "修改文件名成功.....";
    return res;
}
