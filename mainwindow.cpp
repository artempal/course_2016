#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "schedule.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db_connect();
    res_date = date();
    marks_select();
    if (!res_date) schedule_show(); //если каникулы или сессия не выводим расписание

    h1_generator();

    ui->form_save_lable->hide();
    ui->dateEdit->setDate(current_date);

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(send_form()));
    connect(ui->save_btn,SIGNAL(clicked()),this,SLOT(send_study_day()));

    for (int i = 1; i <= 6; i++) //назначаем одинаковые сигналы всем кнопкам
    {
        QPushButton *butt = findChild<QPushButton *>("sch_" + QString::number(i));
        if (butt == nullptr) continue;  //если объект не найден
        connect(butt,SIGNAL(clicked()),this,SLOT(open_sch()));
    }

    QPixmap myPixmap(":img/tem2.jpg"); //фотография
    ui->photo->setPixmap(myPixmap);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //убираем горизонтальую прокурутку
    ui->scrollArea->setBackgroundRole(QPalette::Light); //задаем белый цвет
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
}

void MainWindow::marks_select()
{
     marks_text = ""; // обнуляем переменную

     QSqlQuery a_query; // переменная для запроса

     if (!a_query.exec("SELECT * FROM marks WHERE time = date('now')"))
     {
             qDebug() << "Ошибка выполнения запроса SELECT marks";
     }


     QSqlRecord res = a_query.record(); //результат запроса

     while (a_query.next())
     {
         marks_text.append(a_query.value(res.indexOf("text")).toString());
         marks_text.append("\n\n"); //отступ от заметок
     }

     //if(marks_text == "") marks_text = "Заметок на сегодня нет!";

     ui->marks_conteiner->setText(marks_text);
}

void MainWindow::sch_select(int day_week, int week)
{
     if(day_week == 7)
     {
         sch_text = "Ура! Cегодня пар нет!";
         return;
     }
     int type_week = 1;
     if(week % 2 == 0) type_week = 2;
     sch_text = ""; // обнуляем переменную

     QSqlQuery a_query; // переменная для запроса
     QString str_select; //текст запроса

     if(type_week == 2) str_select = "SELECT * FROM schedule WHERE day = %1 LIMIT 5";
     if(type_week == 1) str_select = "SELECT * FROM schedule WHERE day = %1 LIMIT 5,5";
     QString str = str_select.arg(day_week);


     if (!a_query.exec(str))
     {
             qDebug() << "Ошибка выполнения запроса SELECT schedule";
     }


     QSqlRecord res = a_query.record(); //результат запроса
    int i = 1; //счетчик пар
     while (a_query.next())
     {
         sch_text.append(QString::number(i));
         sch_text.append(". ");
         QString para = a_query.value(res.indexOf("name")).toString();
         if(para == "") sch_text.append("-"); else sch_text.append(para);
         sch_text.append("\n\n");
         i++;
     }
     if(sch_text == "") sch_text = "Ура! Cегодня пар нет!";
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


    QSqlQuery a_query;

    QString str_insert = "INSERT INTO marks(text,time) "
                "VALUES ('%1', '%2');";
    QString str = str_insert.arg(mark)
            .arg(form_date);

    bool b = a_query.exec(str);

    if (!b)
    {
        qDebug() << "Ошибка выполнения запроса INSERT marks";
    }

    ui->textEdit->clear();
    ui->dateEdit->setDate(current_date);
    ui->form_save_lable->setText("Заметка сохранена!");
    ui->form_save_lable->show();
    marks_select();
}
void MainWindow::open_sch()
{
    QObject* obj = QObject::sender(); //объект, который запустил слот

    QString obj_name = obj->objectName(); // имя объекта

    int day;

    if(obj_name == "sch_1") day = 1;
    else if(obj_name == "sch_2") day = 2;
    else if(obj_name == "sch_3") day = 3;
    else if(obj_name == "sch_4") day = 4;
    else if(obj_name == "sch_5") day = 5;
    else if(obj_name == "sch_6") day = 6;

    schedule sch(this,day);
    sch.setWindowFlags (sch.windowFlags() & ~Qt::WindowContextHelpButtonHint); //убираем знак вопроса из заголовка окна
    connect(&sch,&schedule::sch_update,this,&MainWindow::schedule_show); //коннектор обновления расписания в главном окне
    sch.exec();
}
void MainWindow::schedule_show()
{
    sch_select(day_week,cur_week); //выборка расписания на текущий день из таблицы
    ui->sch_output->setText(sch_text); //вывод в lable в главное окно
}

bool MainWindow::date()
{
    QSqlQuery a_query; // переменная для запроса

    if (!a_query.exec("SELECT week FROM study_day LIMIT 4"))
    {
            qDebug() << "Ошибка выполнения запроса SELECT week";
    }

    QSqlRecord res = a_query.record(); //результат запроса

    int i=0;
    while (a_query.next())
    {
       study_day[i] = a_query.value(res.indexOf("week")).toInt();
       i++;
    }
    if(week >= study_day[0] && week <= study_day[1]) cur_week = week-study_day[0] + 1; //входит ли текущая неделя в диапазон семестра
    else if(week >= study_day[2] && week <= study_day[3]) cur_week = week-study_day[2] + 1;
    else return 1; //значит каникулы или сессия

    ui->spin_1->setValue(study_day[0]); //заполним поля для настройки начала и конца семестра
    ui->spin_2->setValue(study_day[1]);
    ui->spin_3->setValue(study_day[2]);
    ui->spin_4->setValue(study_day[3]);

    return 0;
}
void MainWindow::update_week(int rowid, int value)
{
    QSqlQuery a_query;

    QString str_insert = "UPDATE study_day SET week=%1 WHERE rowid=%2";
    QString str = str_insert.arg(value)
            .arg(rowid);

    bool b = a_query.exec(str); //делаем запрос обновления

    if (!b)
    {
        qDebug() << "Ошибка выполнения запроса UPDATE week";
    }
}

void MainWindow::send_study_day()
{
    int new_study_day;

    for (int i = 1; i <= 4; i++) //ищем все измененные значения недель и заносим в базу
    {
        QSpinBox *box = findChild<QSpinBox *>("spin_" + QString::number(i));
        if (box == nullptr) continue;  //если объект не найден
        new_study_day = box->value();
        if(new_study_day!=study_day[i-1]) update_week(i,new_study_day); //если значение поля было изменено - меняем значение в базе
    }
    date(); //проверим неделю
    h1_generator(); //заново генерируем заголовок
    if(!res_date) schedule_show(); //если не каникулы и не сессия выводим расписание
    QMessageBox::information(this,"Успешно","Настройки сохранены!");

}
void MainWindow::h1_generator()
{
    QString name_day[] = {"понедельник", "вторник", "среда", "четверг", "пятница", "суббота", "воскресение"};
    QString h1_text = "Сегодня";

    h1_text.append(", ");
    h1_text.append(current_date.toString("d MMM yyyy"));
    h1_text.append(", ");
    h1_text.append(name_day[day_week-1]);

    if(!res_date)
    {
        h1_text.append(", идет ");
        h1_text.append(QString::number(cur_week));
        h1_text.append("-ая неделя учебы");
    }

    ui->h1_main->setText(h1_text);
}
