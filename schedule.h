#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QDialog>
#include <QString>
#include <QSql>
#include <QSqlRecord>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QDebug>

namespace Ui {
class schedule;
}

class schedule : public QDialog
{
    Q_OBJECT

public:
    explicit schedule(QWidget *parent = 0, int day = 1);
    ~schedule();

private:
    int _day; //выбранный день
    QString _name[10]; //массив с парами
    Ui::schedule *ui;
    void select_sch(int day = 1); // достать пары из бд
    void update_sch(int day, int number, QString name); //обновление расписанаия в базе
    void accept(); //функция нажатия на ОК
signals:
    void sch_update(); //сигнал, отправляемый в MainWindow для обновления расписания
};

#endif // SCHEDULE_H
