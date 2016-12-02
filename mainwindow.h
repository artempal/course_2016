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
#include <QDir>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QUrl>

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
    Ui::MainWindow *ui;
    bool res_date; //переменная результата работы функции date
    QString marks_text; //вывод заметок
    QString sch_text; //вывод расписания
    QString mark = ""; //заметка из формы
    QString db_path = QDir::currentPath() + "/mydatabase.sqlite"; //адрес базы данных
    QDate current_date = QDate::currentDate(); //текущяя дата
    int week; //номер недели
    //int week = 7;
    int day_week; //номер дня недели (1-7)
    int cur_week; //неделя в расписании МИРЭА
    int year; //текущий год
    int study_day[4]; //срок семестра
    QString form_date; //дата из формы
    QNetworkAccessManager *networkManager; //менеджер для работы с сетью для прогноза погоды
    void db_connect(); // функция подключения к базе
    void marks_select(); //функция выборки заметок
    void schedule_show(); //функция показа расписания
    void sch_select(int day_week, int week); //выборка расписания из базы
    bool date(); //определяет текущую недулю в расписании МИРЭА
    void update_week(int rowid, int value); // обновление недель начала учебы
    void h1_generator(); //генератор заголовка главного окна
private slots:
    void send_form(); //отправка заметки
    void open_sch(); //открытие расписания
    void send_study_day(); //редактирование недель учебы
    void update_calendar(QDate); //смена даты при нажатии на календаре
    void weather_result(QNetworkReply *reply); //получение ответа сервера погоды

};

#endif // MAINWINDOW_H
