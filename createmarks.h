#ifndef CREATEMARKS_H
#define CREATEMARKS_H

#include <QDialog>
#include <QString>
#include <QSql>
#include <QSqlRecord>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QDate>

namespace Ui {
class CreateMarks;
}

class CreateMarks : public QDialog
{
    Q_OBJECT

public:
    explicit CreateMarks(QWidget *parent = 0, QDate in_date = QDate::currentDate());
    ~CreateMarks();

private:
    Ui::CreateMarks *ui;
    QString mark = ""; //заметка из формы
    QDate date; //дата
    void accept(); //функция нажатия на ОК
signals:
    void create_marks(); //сигнал, отправляемый в MainWindow для обновления заметок
};

#endif // CREATEMARKS_H
