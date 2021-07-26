#ifndef DOHOD_H
#define DOHOD_H

#include <QWidget>
#include "person.h"
#include <QString>
#include <QIntValidator>

namespace Ui {
class Dohod;
}

class Dohod : public QWidget
{
    Q_OBJECT
    Person* User=nullptr;
    int startview=0;

public:
    explicit Dohod(QWidget *parent = nullptr);
    ~Dohod();

    void Init( Person* user);
signals:
    void thirdWindow();
private slots:
    void on_pushButtonViewAll_clicked();

    void on_pushButtonErase_clicked();

    void on_pushButtonAdd_clicked();

    void on_dateStart_userDateChanged(const QDate &date);

    void on_dateEnd_userDateChanged(const QDate &date);

private:
    Ui::Dohod *ui;
    void ViewElement(const int& begin,const int& end);
    void ViewElement(const QDate& Start,const QDate& End);
    void closeEvent(QCloseEvent *event);
    void resize();
};

#endif // DOHOD_H
