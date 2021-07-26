#ifndef STATISTIKDOHOD_H
#define STATISTIKDOHOD_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "person.h"

namespace Ui {
class StatistikDohod;
}

class StatistikDohod : public QWidget
{
    Q_OBJECT
    Person* User=nullptr;
    QGraphicsScene *scene;
    QGraphicsScene *scene2;
    vector<pair<pair<int,int>,int>> Dohod;
    float Scale = 0.1;

public:
    explicit StatistikDohod(QWidget *parent = nullptr);
    ~StatistikDohod();

    void Init(Person* user);
    void Re_Init();
signals:
    void fourthWindow();
private slots:
    void on_ScaleSlider_sliderMoved(int position);

    void on_dateStart_userDateChanged(const QDate &date);

    void on_dateEnd_userDateChanged(const QDate &date);

private:
    Ui::StatistikDohod *ui;
    void closeEvent(QCloseEvent *event);
    void Update(const int& yearstart,const int& yearend);
};

#endif // STATISTIKDOHOD_H
