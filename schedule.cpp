#include "schedule.h"
#include "ui_schedule.h"

schedule::schedule(QWidget *parent, int day) :
    QDialog(parent),
    ui(new Ui::schedule)
{
    ui->setupUi(this);
    _day = day;
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

void schedule::select_sch(int day)
{
    QString name[10];

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

    for (int i = 1; i <= 10; i++) //циклом присваиваем всем QLineEdit значения из базы
    {
        QLineEdit *edit = findChild<QLineEdit *>("Edit_" + QString::number(i));
        if (edit == nullptr) continue;  //если объект не найден
        edit->setText(name[i-1]);
    }

}
void schedule::update_sch(int day, int number, QString name)
{
    QSqlQuery a_query; // переменная для запроса
    int id = (day-1) * 10 + number; //вычисляем id записи
    qDebug() << id;
    QString str_update = "UPDATE schedule SET name = '%1' WHERE rowid = %2";
    QString str = str_update.arg(name)
            .arg(id);

    if (!a_query.exec(str))
    {
            qDebug() << "Ошибка выполнения запроса UPDATE";
    }
}
void schedule::accept()
{
    for (int i = 1; i <= 10; i++) //циклом заносим значения из всех QLineEdit в базу
    {
        qDebug() << _day
                 << i;
        QLineEdit *edit = findChild<QLineEdit *>("Edit_" + QString::number(i));
        if (edit == nullptr) continue;  //если объект не найден
        QString name = edit->text();
        name = name.simplified(); //убираем пробелы
        update_sch(_day,i,name);
    }

}
