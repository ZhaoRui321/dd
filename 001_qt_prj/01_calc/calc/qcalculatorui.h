#ifndef QCALCULATORUI_H
#define QCALCULATORUI_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class QCalculatorUI : public QWidget
{
private:
    QLineEdit* m_edit;
    QPushButton* mbtn[20];

    QCalculatorUI();
    bool construct();
public:
    static QCalculatorUI* NewInstance();
    void show();
    ~QCalculatorUI();
};

#endif // QCALCULATORUI_H
