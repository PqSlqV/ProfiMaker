#include "mainwindow.h"
#include "ui_mainwindow.h"

Person User;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Инициализируем второе окно
    _rashod = new Rashod();
    _rashod->Init(&User);
    _dohod = new Dohod();
    _dohod->Init(&User);
    _static = new Statistik();
    _static->Init(&User);
    _staticdohod = new StatistikDohod();
    _staticdohod->Init(&User);
    // подключаем к слоту запуска главного окна по кнопке во втором окне
    connect(_rashod, &Rashod::firstWindow, this, &MainWindow::show);
    connect(_static, &Statistik::secondWindow, this, &MainWindow::show);
    connect(_dohod, &Dohod::thirdWindow, this, &MainWindow::show);
    connect(_staticdohod, &StatistikDohod::fourthWindow, this, &MainWindow::show);

    QString Str = QString::fromStdString (User.Get_Name());
    Str="Добро пожаловать, "+Str+"!";
    ui->label->setText(Str);
}

MainWindow::~MainWindow()
{
    delete _rashod;
    delete _dohod;
    delete _static;
    delete _staticdohod;
    delete ui;
}

//расходы
void MainWindow::on_pushButton_clicked()
{
    _rashod->show();
    this->close();
}

//статистика расходы
void MainWindow::on_pushButton_2_clicked()
{
    _static->Update();
    _static->show();
    this->close();
}

//доходы
void MainWindow::on_pushButton_3_clicked()
{
    _dohod->show();
    this->close();
}

//статистика доходы
void MainWindow::on_pushButton_4_clicked()
{
    _staticdohod->Re_Init();
    _staticdohod->show();
    this->close();
}

