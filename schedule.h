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
#include <QPixmap>

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
    Ui::schedule *ui;
    void select_sch(int day = 1); // достать пары из бд
};

#endif // SCHEDULE_H
