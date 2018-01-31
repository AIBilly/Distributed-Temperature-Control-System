#ifndef STAFF_MANAGE_H
#define STAFF_MANAGE_H

#include <QDialog>

namespace Ui {
class Staff_manage;
}

class Staff_manage : public QDialog
{
    Q_OBJECT

public:
    explicit Staff_manage(QWidget *parent = 0);
    ~Staff_manage();

private:
    Ui::Staff_manage *ui;
};

#endif // STAFF_MANAGE_H
