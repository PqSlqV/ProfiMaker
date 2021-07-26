#include "statistikdohod.h"
#include "ui_statistikdohod.h"

StatistikDohod::StatistikDohod(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatistikDohod)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(ui->graphicsView);
    scene2 = new QGraphicsScene(ui->graphicsView_2);
}


StatistikDohod::~StatistikDohod()
{
    delete scene;
    delete scene2;
    delete ui;
}


void StatistikDohod::Init(Person* user)
{
    User = user;
    Re_Init();
    QDate date = QDate::currentDate();
    ui->dateEnd->setDate(date);
    date.setDate(date.year()-1,date.month(),date.day());
    ui->dateStart->setDate(date);
}

void StatistikDohod::Re_Init()
{
    Dohod.clear();
    int maxprice = 0;
    Dohod = User->Get_Dohod_Statistik(maxprice);
    double width,height,x,y;
    ui->graphicsView->sceneRect().getRect(&x,&y,&width,&height);
    Scale = (height - 30) / maxprice;
    Update(ui->dateStart->date().year(),ui->dateEnd->date().year());
}


void StatistikDohod::Update(const int& yearstart,const int& yearend)
{
    scene->clear();
    scene2->clear();
    int Color[12] {Qt::red,Qt::blue,Qt::yellow,Qt::green,Qt::cyan,Qt::magenta,Qt::darkRed,Qt::darkBlue,Qt::darkYellow, Qt::darkGreen,Qt::darkCyan, Qt::darkMagenta};
    QPen pen(Qt::gray);
    double width,height,x,y;
    ui->graphicsView->sceneRect().getRect(&x,&y,&width,&height);
    width = (width+20) / 12;
    for(int i=0, Wx = 20;i<12;i++,Wx +=width)
        scene->addLine(Wx,height,Wx,height - 10,pen);
    float startX = 0.0f,startY = 0.0f;
    int ind = 0;
    float sum = 0.0f;
    bool first = true;
    for(int i=0,size = Dohod.size();i<=size;i++)
    {
        if(i==size)
        {
            if(!first)
            {
                QString stemp = QString::number(int(sum*10.0f)/10.0f);
                QGraphicsTextItem* temp = new QGraphicsTextItem(stemp);
                temp->setPos(60,20*ind);
                scene2->addItem(temp);
            }
            break;
        }
        if(Dohod[i].first.second<yearstart)
            continue;
        if(Dohod[i].first.second>yearend)
        {
            QString stemp = QString::number(int(sum*10.0f)/10.0f);
            QGraphicsTextItem* temp = new QGraphicsTextItem(stemp);
            temp->setPos(60,20*ind);
            scene2->addItem(temp);
            break;
        }
        if(Dohod[i].first.first == 0)
        {
            startX = 20;
            startY = height - 10 - Dohod[i].second * Scale;
            if(!first)
            {
                QString stemp = QString::number(int(sum*10.0f)/10.0f);
                QGraphicsTextItem* temp = new QGraphicsTextItem(stemp);
                temp->setPos(60,20*ind);
                scene2->addItem(temp);
                sum = 0.0f;
                ind++;
                if(ind>11)
                    ind = 0;
            }
            scene2->addLine(5,12+20*ind,15,12+20*ind,QPen(Qt::GlobalColor(Color[ind]),1.5));
            QString stemp = QString::number(Dohod[i].first.second);
            QGraphicsTextItem* temp = new QGraphicsTextItem(stemp);
            temp->setPos(20,20*ind);
            scene2->addItem(temp);
            first=false;
        }
        else
        {
            float NewX =  startX + width;
            float NewY = height - 10 - Dohod[i].second * Scale ;
            scene->addLine(startX, startY,NewX,NewY ,QPen(Qt::GlobalColor(Color[ind]),1.5));
            startX = NewX;
            startY = NewY;
        }
        float val = float(Dohod[i].second)/1000;
        sum+=val;
        if(val!= 0.0f)
        {
            QString stemp = QString::number(int(val*10.0f)/10.0f);
            QGraphicsTextItem* temp = new QGraphicsTextItem(stemp);
            temp->setPos(startX-20,startY-20);
            scene->addItem(temp);
        }
    }
    ui->graphicsView->setScene(scene);
    ui->graphicsView_2->setScene(scene2);
}


void StatistikDohod::closeEvent(QCloseEvent*)
{
    scene->clear();
    scene2->clear();
    emit fourthWindow();
}


void StatistikDohod::on_ScaleSlider_sliderMoved(int position)
{
    scene->clear();
    static float scale = Scale;
    Scale = scale + 0.01f * position;
    Update(ui->dateStart->date().year(),ui->dateEnd->date().year());
}


void StatistikDohod::on_dateStart_userDateChanged(const QDate &date)
{
    Update(date.year(),ui->dateEnd->date().year());
}


void StatistikDohod::on_dateEnd_userDateChanged(const QDate &date)
{
    Update(ui->dateStart->date().year(),date.year());
}

