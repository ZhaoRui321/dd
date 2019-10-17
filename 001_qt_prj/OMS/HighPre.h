#ifndef HIGHPRE_H
#define HIGHPRE_H

#include <QWidget>

namespace Ui {
class HighPre;
}

class HighPre : public QWidget
{
    Q_OBJECT

public:
    explicit HighPre(QWidget *parent = 0);
    ~HighPre();

private:
    Ui::HighPre *ui;

public slots:

    void on_allControl_clicked(bool is_selected);
    void on_iconSource_clicked(bool is_selected);
    void on_dynode_clicked(bool is_selected);
    void on_increase_clicked(bool is_selected);

};

#endif // HIGHPRE_H
