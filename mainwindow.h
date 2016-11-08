#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDate>
#include <QSql>
#include <QSqlRecord>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QString>

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
    QString marks_text = ""; //вывод заметок
    QString mark = ""; //заметка из формы
    QDate current_date = QDate::currentDate(); //текущяя дата
    QString form_date; //дата из формы
    void marks_select(); //функция выборки заметок
private slots:
    void send_form();
};

#endif // MAINWINDOW_H
