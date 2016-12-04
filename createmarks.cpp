#include "createmarks.h"
#include "ui_createmarks.h"

CreateMarks::CreateMarks(QWidget *parent, QDate in_date) :
    QDialog(parent),
    ui(new Ui::CreateMarks)
{
    ui->setupUi(this);
    date = in_date; //получаем дату из главного окна
    QString date_to_string = date.toString("dd.MM.yyyy");
    QString h1 = "Создание заметки на " + date_to_string;
    ui->h1_label->setText(h1);
    ui->form_label->hide();
}

CreateMarks::~CreateMarks()
{
    delete ui;
}

void CreateMarks::accept()
{
    QWidget::close();
    mark = ui->textEdit->toPlainText();
    mark = mark.simplified(); //убираем лишние пробелы из строки


    if(mark == "")
    {
        ui->form_label->setText("Введите текст заметки");
        ui->form_label->show();
        return;
    }


    QSqlQuery a_query;

    QString str_insert = "INSERT INTO marks(text,time) "
                "VALUES ('%1', '%2');";
    QString str = str_insert.arg(mark)
            .arg(date.toString("yyyy-MM-dd"));

    bool b = a_query.exec(str);

    if (!b)
    {
        qDebug() << "Ошибка выполнения запроса INSERT marks";
    }

    emit create_marks();
}
