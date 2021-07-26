#include "dohod.h"
#include "ui_dohod.h"

Dohod::Dohod(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dohod)
{
    ui->setupUi(this);
    ui->lineEditPrice->setValidator( new QIntValidator(0, 99999999, this) );
    ui->lineEditSebest->setValidator( new QIntValidator(0, 99999999, this) );
    ui->lineEditPeople->setValidator( new QIntValidator(0, 99, this) );
    Dohod::resize();
}


Dohod::~Dohod()
{

    delete ui;
}


void Dohod::resize()
{
    ui->tableWidget->setColumnWidth(0, ui->tableWidget->width()*0.15);
    ui->tableWidget->setColumnWidth(1, ui->tableWidget->width()*0.30);
    ui->tableWidget->setColumnWidth(2, ui->tableWidget->width()*0.12);
    ui->tableWidget->setColumnWidth(3, ui->tableWidget->width()*0.08);
    ui->tableWidget->setColumnWidth(4, ui->tableWidget->width()*0.07);
    ui->tableWidget->setColumnWidth(5, ui->tableWidget->width()*0.12);
    ui->tableWidget->setColumnWidth(6, ui->tableWidget->width()*0.16);
}


void Dohod::Init(Person* user)
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

    for(int i=0,max=User->Get_Dohod_Istochnik_Size();i<max;i++)
    {
        QString str;
        str=QString::fromStdString(User->Get_Dohod_Istochnik_Str(i));
        ui->comboBoxIstoch->addItem(str);
    }
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    Dohod::ViewElement(ui->dateStart->date(),ui->dateEnd->date());
}


void Dohod::ViewElement(const int &begin, const int &end)
{
    ui->tableWidget->setRowCount(0);
    for(int i=begin;i<=end;i++)
    {
        Person::DohodElement& temp = User->Get_Dohod_Element(i);
        QDate date;
        date.setDate(temp.date.year,temp.date.month,temp.date.day);
        QString Sdate = date.toString("dd.MM.yyyy");
        QString Name(temp.name.c_str());
        QString Sprice = QString::number(temp.price);
        QString Service(temp.service.c_str());
        QString Speople = QString::number(temp.people);
        QString Ssebest = QString::number(temp.sebest);
        QString Ist(temp.istochnik.c_str());

        int j = ui->tableWidget->rowCount();

        ui->tableWidget->insertRow(j);
        ui->tableWidget->setItem(j,0, new QTableWidgetItem(Sdate));
        ui->tableWidget->setItem(j,1, new QTableWidgetItem(Name));
        ui->tableWidget->setItem(j,2, new QTableWidgetItem(Sprice));
        ui->tableWidget->setItem(j,3, new QTableWidgetItem(Service));
        ui->tableWidget->setItem(j,4, new QTableWidgetItem(Speople));
        ui->tableWidget->setItem(j,5, new QTableWidgetItem(Ssebest));
        ui->tableWidget->setItem(j,6, new QTableWidgetItem(Ist));
    }
    if(begin==User->Get_Dohod_Size())
        startview = -1;
    else
        startview = begin;
}


void Dohod::ViewElement(const QDate &Start, const QDate &End)
{
    int begin = User->Get_Dohod_Element_Begin(Start.day(),Start.month(),Start.year());
    int end = User->Get_Dohod_Element_End(End.day(),End.month(),End.year());
    Dohod::ViewElement(begin,end);
}


void Dohod::closeEvent(QCloseEvent*)
{
    emit thirdWindow();
}


void Dohod::on_pushButtonViewAll_clicked()
{
    Dohod::ViewElement(0,User->Get_Dohod_Size()-1);
}


void Dohod::on_pushButtonErase_clicked()
{
    if(startview==-1)
        return;
    for (int row = 0; row < ui->tableWidget->model()->rowCount(ui->tableWidget->rootIndex()); ++row)
    {
        QModelIndex index = ui->tableWidget->model()->index(row,0, ui->tableWidget->rootIndex());
        if (ui->tableWidget->selectionModel()->isSelected(index))
            User->Dohod_Erase(startview+row);
    }
    Dohod::ViewElement(ui->dateStart->date(),ui->dateEnd->date());
}


void Dohod::on_pushButtonAdd_clicked()
{
    QDate date = ui->dateEdit->date();
    QString name = ui->lineEditName->text();
    int price = ui->lineEditPrice->text().toInt();
    QString service ="";
    if(ui->checkBoxM->isChecked())
        service+="М";
    if(ui->checkBoxP->isChecked())
        service+="П";
    if(ui->checkBoxR->isChecked())
        service+="Р";
    if(ui->checkBoxY->isChecked())
        service+="У";
    if(ui->checkBoxF->isChecked())
        service+="Ф";
    if(ui->checkBoxA->isChecked())
        service+="А";
    int people = ui->lineEditPeople->text().toInt();
    int sebest = ui->lineEditSebest->text().toInt();
    QString ist = ui->comboBoxIstoch->currentText();
    if(name != "" && price != 0)
    {
        Person::DohodElement temp;
        temp.date.day = date.day();
        temp.date.month = date.month();
        temp.date.year = date.year();
        temp.name = name.toStdString();
        temp.price = price;
        temp.service = service.toStdString();
        temp.people = people;
        temp.sebest = sebest;
        temp.istochnik = ist.toStdString();
        User->Set_Dohod(temp);
        ui->lineEditName->clear();
        ui->lineEditPrice->clear();
        ui->lineEditPeople->clear();
        ui->lineEditSebest->clear();
        Dohod::ViewElement(ui->dateStart->date(),ui->dateEnd->date());
    }
}


void Dohod::on_dateStart_userDateChanged(const QDate &date)
{
    Dohod::ViewElement(date,ui->dateEnd->date());
}


void Dohod::on_dateEnd_userDateChanged(const QDate &date)
{
    Dohod::ViewElement(ui->dateStart->date(),date);
}

