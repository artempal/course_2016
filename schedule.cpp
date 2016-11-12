#include "schedule.h"
#include "ui_schedule.h"

schedule::schedule(QWidget *parent, int day) :
    QDialog(parent),
    ui(new Ui::schedule)
{
    ui->setupUi(this);
    switch(day)
    {
    case 1:
        ui->day_name->setText("Понедельник");
        break;
    case 2:
        ui->day_name->setText("Вторник");
        break;
    case 3:
        ui->day_name->setText("Среда");
        break;
    case 4:
        ui->day_name->setText("Четверг");
        break;
    case 5:
        ui->day_name->setText("Пятница");
        break;
    case 6:
        ui->day_name->setText("Суббота");
        break;

    }
    select_sch(day);
}

schedule::~schedule()
{
    delete ui;
}

void schedule::db_connect()
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
void schedule::select_sch(int day)
{
    QString name[10];
    if(!_db_connect)db_connect(); //проверка подключения к базе

    QSqlQuery a_query; // переменная для запроса

    QString str_select = "SELECT * FROM schedule WHERE day = %1";
    QString str = str_select.arg(day);


    if (!a_query.exec(str))
    {
            qDebug() << "Ошибка выполнения запроса SELECT";
    }


    QSqlRecord res = a_query.record(); //результат запроса
    int i =0;
    while (a_query.next())
    {
       name[i] = a_query.value(res.indexOf("name")).toString();
       i++;
    }


    ui->Edit_1->setText(name[0]);
    ui->Edit_2->setText(name[1]);
    ui->Edit_3->setText(name[2]);
    ui->Edit_4->setText(name[3]);
    ui->Edit_5->setText(name[4]);
    ui->Edit_6->setText(name[5]);
    ui->Edit_7->setText(name[6]);
    ui->Edit_8->setText(name[7]);
    ui->Edit_9->setText(name[8]);
    ui->Edit_10->setText(name[9]);

}
