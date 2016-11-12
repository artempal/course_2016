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
}

schedule::~schedule()
{
    delete ui;
}
