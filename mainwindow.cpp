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

void MainWindow::marks_select()
{
        marks_text = "";
        QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
        dbase.setDatabaseName("C:/qtprojects/curs/course_2016.git/mydatabase.sqlite");
        if (!dbase.open())
        {
                 qDebug() << "Ошибка открытия базы данных!";

        }
         QSqlQuery a_query;
         if (!a_query.exec("SELECT * FROM marks WHERE time = date('now')"))
         {
                 qDebug() << "Ошибка выполнения запроса SELECT";
         }
         QSqlRecord rec = a_query.record();
         while (a_query.next())
         {
             marks_text.append("\n\n");
             marks_text.append(a_query.value(rec.indexOf("text")).toString());
         }
        ui->marks_conteiner->setText(marks_text);
}

void MainWindow::send_form()
{
        QSqlQuery a_query;
        mark = ui->textEdit->toPlainText();
        form_date = ui->dateEdit->text();
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
        ui->form_save_lable->show();
        marks_select();
}


