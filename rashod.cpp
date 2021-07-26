#include "rashod.h"
#include "ui_rashod.h"

Rashod::Rashod(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Rashod)
{
    ui->setupUi(this);
    ui->lineEditPrice->setValidator( new QIntValidator(0, 99999999, this) );
    ui->tableWidget->setColumnWidth(0, ui->tableWidget->width()*0.15);
    ui->tableWidget->setColumnWidth(1, ui->tableWidget->width()*0.38);
    ui->tableWidget->setColumnWidth(2, ui->tableWidget->width()*0.15);
    ui->tableWidget->setColumnWidth(3, ui->tableWidget->width()*0.17);
    ui->tableWidget->setColumnWidth(4, ui->tableWidget->width()*0.15);
}


Rashod::~Rashod()
{

    delete ui;
}


void Rashod::closeEvent(QCloseEvent *)
{
    emit firstWindow();
}


void Rashod::ViewElement(const int& begin,const int& end)
{
    ui->tableWidget->setRowCount(0);
    for(int i=begin;i<=end;i++)
    {
        Person::Element& temp = User->Get_Rashod_Element(i);
        QDate date;
        date.setDate(temp.date.year,temp.date.month,temp.date.day);
        QString Sdate = date.toString("dd.MM.yyyy");
        QString Sprice = QString::number(temp.price);
        QString Name(temp.name.c_str());
        QString Cat(temp.category.c_str());
        QString Ist(temp.istochnik.c_str());

        int j = ui->tableWidget->rowCount();

        ui->tableWidget->insertRow(j);
        ui->tableWidget->setItem(j,0, new QTableWidgetItem(Sdate));
        ui->tableWidget->setItem(j,1, new QTableWidgetItem(Name));
        ui->tableWidget->setItem(j,2, new QTableWidgetItem(Sprice));
        ui->tableWidget->setItem(j,3, new QTableWidgetItem(Cat));
        ui->tableWidget->setItem(j,4, new QTableWidgetItem(Ist));
    }
    if(begin==User->Get_Rashod_Size())
        startview = -1;
    else
        startview = begin;
}


void Rashod::ViewElement(const QDate &Start, const QDate &End)
{
    int begin = User->Get_Rashod_Element_Begin(Start.day(),Start.month(),Start.year());
    int end = User->Get_Rashod_Element_End(End.day(),End.month(),End.year());
    Rashod::ViewElement(begin,end);
}


void Rashod::Init( Person* user)
{
    User = user;
    QDate date = QDate::currentDate();
    ui->dateEdit->setDate(date);
    ui->dateEnd->setDate(date);
    if(date.month()>1)
        date.setDate(date.year(),date.month()-1,date.day());
    else
        date.setDate(date.year()-1,12,date.day());
    ui->dateStart->setDate(date);
    for(int i=0,max=User->Get_Rashod_Category_Size();i<max;i++)
    {
        QString str;
        str=QString::fromStdString(User->Get_Rashod_Category_Str(i));
        ui->comboBoxCateg->addItem(str);
    }
    for(int i=0,max=User->Get_Rashod_Istochnik_Size();i<max;i++)
    {
        QString str;
        str=QString::fromStdString(User->Get_Rashod_Istochnik_Str(i));
        ui->comboBoxIstoch->addItem(str);
    }
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    Rashod::ViewElement(ui->dateStart->date(),ui->dateEnd->date());
}


void Rashod::on_pushButtonErase_clicked()
{
    if(startview==-1)
        return;
    for (int row = 0; row < ui->tableWidget->model()->rowCount(ui->tableWidget->rootIndex()); ++row)
    {
        QModelIndex index = ui->tableWidget->model()->index(row,0, ui->tableWidget->rootIndex());
        if (ui->tableWidget->selectionModel()->isSelected(index))
            User->Rashod_Erase(startview+row);
    }
    Rashod::ViewElement(ui->dateStart->date(),ui->dateEnd->date());
}


void Rashod::on_pushButtonAdd_clicked()
{
    QDate date = ui->dateEdit->date();
    QString name = ui->lineEditName->text();
    int price = ui->lineEditPrice->text().toInt();
    QString cat = ui->comboBoxCateg->currentText();
    QString ist = ui->comboBoxIstoch->currentText();
    if(name != "" && price != 0)
    {
        Person::Element temp;
        temp.date.day = date.day();
        temp.date.month = date.month();
        temp.date.year = date.year();
        temp.name = name.toStdString();
        temp.price = price;
        temp.category = cat.toStdString();
        temp.istochnik = ist.toStdString();
        User->Set_Rashod(temp);
        ui->lineEditName->clear();
        ui->lineEditPrice->clear();
    }
    Rashod::ViewElement(ui->dateStart->date(),ui->dateEnd->date());
}


void Rashod::on_pushButtonViewAll_clicked()
{
    Rashod::ViewElement(0,User->Get_Rashod_Size()-1);
}


void Rashod::on_dateStart_userDateChanged(const QDate &date)
{
    Rashod::ViewElement(date, ui->dateEnd->date());
}


void Rashod::on_dateEnd_userDateChanged(const QDate &date)
{
    Rashod::ViewElement(ui->dateStart->date(), date);
}

