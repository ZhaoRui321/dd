#ifndef SIM_H
#define SIM_H

#include <QWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QItemDelegate>
#include <QLineEdit>
#include <massinput.h>

namespace Ui {
class SIM;
}


class SIM : public QWidget
{
    Q_OBJECT

public:
    explicit SIM(QWidget *parent = 0);
    ~SIM();
    int getMassListCount() { return massCount; }
    QList<double> getMassList();

private:
    Ui::SIM *ui;
    QList<MassInput*> m_MassInputList;
    int widgetWidth;
    int widgetHeight;
    int borderWidth = 50;
    int widgetToWidget = 20;
    int massCount = 0;
    QList<double> m_MassNumList;

    void setPosition();

signals:

private slots:
    void on_addBtn_clicked();
    void on_deleteBtn_clicked();
};

#endif // SIM_H
