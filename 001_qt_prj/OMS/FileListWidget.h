#ifndef FILELISTWIDGET_H
#define FILELISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QString>
#include <QVBoxLayout>
#include <QDir>
#include <QLabel>
#include <QPushButton>
#include <QEvent>
#include <QDebug>

class FileListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit FileListWidget(QString path,QListWidget *parent = 0);
    ~FileListWidget();
    void setFileNameList(){
        fileNameList.clear();
        this->clear();
        QDir dir(datapath);
        QStringList fileType;
        fileType << "*.TIC";
        fileNameList = dir.entryList(fileType,QDir::Files | QDir::Readable, QDir::Name);
        this->addItems(fileNameList);
    }
    void setDatapath(QString path);

    QString getDatapath(){
        return datapath;
    }

    void removeFile(int currentRow);

private:
    QVBoxLayout* layout = new QVBoxLayout;
    QStringList readDate;
    QStringList dateList;
    QStringList fileNameList;
    QString datapath;

    void setItemStyle(QString name);


};

#endif // FILELISTWIDGET_H
