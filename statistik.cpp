#include "statistik.h"
#include "ui_statistik.h"

Statistik::Statistik(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Statistik)
{
    ui->setupUi(this);
    ui->tableWidgetStat->verticalHeader()->setVisible(false);
    ui->tableWidgetStat->setSelectionBehavior(QAbstractItemView::SelectRows);
}


Statistik::~Statistik()
{
    delete ui;
}


void Statistik::Init(Person* user)
{
    User = user;
    QDate date = QDate::currentDate();
    ui->dateSEnd->setDate(date);
    if(date.month()>1)
        date.setDate(date.year(),date.month()-1,date.day());
    else
        date.setDate(date.year()-1,12,date.day());
    ui->dateSStart->setDate(date);


    Statistik::ViewElementStat(ui->dateSStart->date(),ui->dateSEnd->date());
}


void Statistik::Update()
{
    Statistik::ViewElementStat(ui->dateSStart->date(),ui->dateSEnd->date());
}


void Statistik::ViewElementStat(const int &begin, const int &end)
{
    User->Rashod_Statistic(begin,end);
    ui->tableWidgetStat->setRowCount(0);
    for (int i=0,cat=User->Get_Rashod_Category_Size(); i<cat; i++)
    {
        ui->tableWidgetStat->insertRow(i);
        for (int j=0,ist=User->Get_Rashod_Istochnik_Size(); j<ist; j++)
        {
            Person::Price& temp = User->Get_Rashod_Statistic_Element(i + j * cat);
            QString Cat(temp.cat.c_str());
            QString Sprice = QString::number(temp.price);
            QString Sproc = QString::number(temp.proc)+"%";

            ui->tableWidgetStat->setItem(i,0+3*j, new QTableWidgetItem(Cat));
            ui->tableWidgetStat->setItem(i,1+3*j, new QTableWidgetItem(Sprice));
            ui->tableWidgetStat->setItem(i,2+3*j, new QTableWidgetItem(Sproc));
        }
    }
    Person::Price& temp = User->Get_Rashod_Statistic_Element(User->Get_Rashod_Category_Size() * User->Get_Rashod_Istochnik_Size());
    QString name1(temp.ist.c_str());
    ui->label_Name1->setText(name1);
    QString sum1 = QString::number(temp.sum);
    ui->label_Sum1->setText(sum1);
    temp = User->Get_Rashod_Statistic_Element(User->Get_Rashod_Category_Size() * User->Get_Rashod_Istochnik_Size()+1);
    QString name2(temp.ist.c_str());
    ui->label_Name2->setText(name2);
    QString sum2 = QString::number(temp.sum);
    ui->label_Sum2->setText(sum2);
    temp = User->Get_Rashod_Statistic_Element(User->Get_Rashod_Category_Size() * User->Get_Rashod_Istochnik_Size()+2);
    QString sum = QString::number(temp.sum);
    ui->label_Sum->setText(sum);
}


void Statistik::ViewElementStat(const QDate &Start, const QDate &End)
{
    Statistik::ViewElementStat(User->Get_Rashod_Element_Begin(Start.day(),Start.month(),Start.year()),User->Get_Rashod_Element_End(End.day(),End.month(),End.year()));
}


void Statistik::closeEvent(QCloseEvent *)
{
    emit secondWindow();
}


void Statistik::on_pushButtonStatAll_clicked()
{
    Statistik::ViewElementStat(0,User->Get_Rashod_Size()-1);
}


void Statistik::on_dateSStart_userDateChanged(const QDate &date)
{
    Statistik::ViewElementStat(date,ui->dateSEnd->date());
}


void Statistik::on_dateSEnd_userDateChanged(const QDate &date)
{
    Statistik::ViewElementStat(ui->dateSStart->date(),date);
}

