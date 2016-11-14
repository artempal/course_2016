#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "schedule.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    marks_select();
    schedule_show();

    ui->form_save_lable->hide();
    ui->dateEdit->setDate(current_date);

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(send_form()));

    connect(ui->sch_1,SIGNAL(clicked()),this,SLOT(open_sch()));
    connect(ui->sch_2,SIGNAL(clicked()),this,SLOT(open_sch()));
    connect(ui->sch_3,SIGNAL(clicked()),this,SLOT(open_sch()));
    connect(ui->sch_4,SIGNAL(clicked()),this,SLOT(open_sch()));
    connect(ui->sch_5,SIGNAL(clicked()),this,SLOT(open_sch()));
    connect(ui->sch_6,SIGNAL(clicked()),this,SLOT(open_sch()));

    QPixmap myPixmap("C:/qtprojects/curs/course_2016.git/tem2.jpg"); //фотография
    ui->photo->setPixmap(myPixmap);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::db_connect()
{
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName("C:/qtprojects/curs/course_2016.git/mydatabase.sqlite");
    if (!dbase.open())
    {
             qDebug() << "Ошибка открытия базы данных!";

    }
    else
    {
        _db_connect = 1; //если база данных успешно подключена, то меняем параметр на 1
    }
}

void MainWindow::marks_select()
{
     if(!_db_connect)db_connect(); //проверка подключения к базе
     marks_text = ""; // обнуляем переменную

     QSqlQuery a_query; // переменная для запроса

     if (!a_query.exec("SELECT * FROM marks WHERE time = date('now')"))
     {
             qDebug() << "Ошибка выполнения запроса SELECT";
     }


     QSqlRecord res = a_query.record(); //результат запроса

     while (a_query.next())
     {
         marks_text.append("\n\n"); //отступ от заметок
         marks_text.append(a_query.value(res.indexOf("text")).toString());
     }

     if(marks_text == "") marks_text = "Заметок на сегодня нет!";

     ui->marks_conteiner->setText(marks_text);
}

void MainWindow::send_form()
{
    mark = ui->textEdit->toPlainText();
    mark = mark.simplified(); //убираем лишние пробелы из строки

    form_date = ui->dateEdit->text();

    if(mark == "")
    {
        ui->form_save_lable->setText("Введите текст заметки");
        ui->form_save_lable->show();
        return;
    }

    if(!_db_connect)db_connect(); //проверка подключения к базе

    QSqlQuery a_query;

    QString str_insert = "INSERT INTO marks(text,time) "
                "VALUES ('%1', '%2');";
    QString str = str_insert.arg(mark)
            .arg(form_date);

    bool b = a_query.exec(str);

    if (!b)
    {
        qDebug() << "Ошибка выполнения запроса INSERT";
    }

    ui->textEdit->clear();
    ui->dateEdit->setDate(current_date);
    ui->form_save_lable->setText("Заметка сохранена!");
    ui->form_save_lable->show();
    marks_select();
}
void MainWindow::open_sch()
{
    QObject* obj = QObject::sender(); //объект, который запустил слот

    QString obj_name = obj->objectName(); // имя объекта

    int day;

    if(obj_name == "sch_1") day = 1;
    else if(obj_name == "sch_2") day = 2;
    else if(obj_name == "sch_3") day = 3;
    else if(obj_name == "sch_4") day = 4;
    else if(obj_name == "sch_5") day = 5;
    else if(obj_name == "sch_6") day = 6;

    schedule sch(this,day);
    sch.exec();
}
void MainWindow::schedule_show()
{
    int start_week = 35;
    int week = current_date.weekNumber();
    int cur_week = week - start_week + 1;

    qDebug() << cur_week;
}
