#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <QWidget>

namespace Ui {
class SaveFile;
}

class SaveFile : public QWidget
{
    Q_OBJECT

public:
    explicit SaveFile(QWidget *parent = 0);
    ~SaveFile();

private slots:
    void on_btnCancel_clicked();

    void on_btnSave_clicked();

private:
    Ui::SaveFile *ui;
    QString style1;    //点击
    QString style2;    //未点击

signals:
    void saveInfo(QString text);
};

#endif // SAVEFILE_H
