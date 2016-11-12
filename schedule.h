#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QDialog>

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
};

#endif // SCHEDULE_H
