#include "staff_manage.h"
#include "ui_staff_manage.h"

Staff_manage::Staff_manage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Staff_manage)
{
    ui->setupUi(this);
}

Staff_manage::~Staff_manage()
{
    delete ui;
}
