#ifndef RASHOD_H
#define RASHOD_H

#include <QWidget>
#include <QString>
#include "person.h"
#include <QIntValidator>

namespace Ui {
class Rashod;
}

class Rashod : public QWidget
{
    Q_OBJECT
    int startview=0;
    Person* User=nullptr;
public:
    explicit Rashod(QWidget *parent = nullptr);
    ~Rashod();

    void Init( Person* user);

signals:
    void firstWindow();  // Сигнал для открытия

private slots:

    void on_pushButtonErase_clicked();

    void on_pushButtonAdd_clicked();

    void on_pushButtonViewAll_clicked();

    void on_dateStart_userDateChanged(const QDate &date);

    void on_dateEnd_userDateChanged(const QDate &date);

private:
    Ui::Rashod *ui;
    void ViewElement(const int& begin,const int& end);
    void ViewElement(const QDate& Start,const QDate& End);
    void closeEvent(QCloseEvent *event);
};

#endif // RASHOD_H
