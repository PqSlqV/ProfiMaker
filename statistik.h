#ifndef STATISTIK_H
#define STATISTIK_H

#include <QWidget>
#include <QString>
#include "person.h"
#include <QTime>

namespace Ui {
class Statistik;
}

class Statistik : public QWidget
{
    Q_OBJECT
    Person* User=nullptr;

public:
    explicit Statistik(QWidget *parent = nullptr);
    ~Statistik();
    void Init(Person* user);
    void Update();
signals:
    void secondWindow();
private slots:
    void ViewElementStat(const int& begin,const int& end);
    void ViewElementStat(const QDate& Start,const QDate& End);
    void on_pushButtonStatAll_clicked();

    void on_dateSStart_userDateChanged(const QDate &date);

    void on_dateSEnd_userDateChanged(const QDate &date);

private:
    Ui::Statistik *ui;

    void closeEvent(QCloseEvent *event);
};

#endif // STATISTIK_H
