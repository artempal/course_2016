#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    marks_select();
    ui->form_save_lable->hide();
    ui->dateEdit->setDate(current_date);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(send_form()));
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