#ifndef FILECONTENT_H
#define FILECONTENT_H

#include <QObject>
#include <QFile>
#include <QTextStream>

class FileContent : public QObject
{
    Q_OBJECT
public:
    //Q_PROPERTY(QString content READ getContent)
    Q_PROPERTY(QString filename READ getFileName WRITE setFileName)
    Q_PROPERTY(QString datapath READ getDataPath WRITE setDataPath)
    Q_PROPERTY(QStringList fileNames READ getFIleNames)
    Q_INVOKABLE bool resetfilename(QString mfilename);
    Q_INVOKABLE QString getContent();
    Q_INVOKABLE bool writeContent(const QString &data);
    Q_INVOKABLE QString getFileName();
    Q_INVOKABLE QString getDataPath();
    Q_INVOKABLE bool deleteContent(const QString &filename);
    Q_INVOKABLE QStringList getFileNames();
    Q_INVOKABLE int getFileCount();
    Q_INVOKABLE QString fileN(int);
    Q_INVOKABLE int dataN(int i);
    Q_INVOKABLE bool justFile();
    //Q_INVOKABLE QString loadFileContent();
    FileContent(QObject *parent = 0);
    ~FileContent();

private:
    QFile   *file;
    QString content;
    QString datapath;
    QString filename;
    QStringList fileNames;

public slots:
    void setDataPath(const QString &datapath);
    bool setFileName(const QString& filename);
    void clearContent();
};

#endif // FILECONTENT_H
