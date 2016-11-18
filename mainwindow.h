#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QSql>
#include <QSqlRecord>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QString>
#include <QPixmap>
#include <QDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    bool _db_connect = 0;
    Ui::MainWindow *ui;
    QString marks_text; //вывод заметок
    QString sch_text; //вывод расписания
    QString mark = ""; //заметка из формы
    const int start_week = 35; //неделя начала занятий
    QDate current_date = QDate::currentDate(); //текущяя дата
    int week = current_date.weekNumber(); //номер недели
    int day_week = current_date.dayOfWeek(); //номер дня недели (1-7)
    int cur_week = week - start_week + 1; //неделя в расписании МИРЭА
    QString form_date; //дата из формы
    void db_connect(); // функция подключения к базе
    void marks_select(); //функция выборки заметок
    void schedule_show(); //функция показа расписания
    void sch_select(int day_week, int week); //выборка расписания из базы
private slots:
    void send_form();
    void open_sch();
};

#endif // MAINWINDOW_H
