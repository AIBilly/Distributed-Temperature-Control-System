#include "sign_up.h"
#include "ui_sign_up.h"

sign_up::sign_up(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sign_up)
{
    ui->setupUi(this);
    ui->username->setText("admin");
    ui->password1->setEchoMode(QLineEdit::Password);
    ui->password2->setEchoMode(QLineEdit::Password);
    ui->password1->setFocus();
}

sign_up::~sign_up()
{
    delete ui;
}

void sign_up::on_ok_clicked()
{
    if(ui->username->text()=="\0")
    {
        QMessageBox::critical(this, "critical", "Please input the username!", QMessageBox::Yes | QMessageBox::No);
        ui->password1->clear();
        ui->password2->clear();
        ui->username->setFocus();
    }
    else
    {
        if(ui->password1->text()=="\0")
        {
           QMessageBox::critical(this, "critical", "Please input the password!", QMessageBox::Yes | QMessageBox::No);
           ui->password1->clear();
           ui->password2->clear();
           ui->username->setFocus();
        }
        else
        {
            if(ui->password2->text()=="\0")
            {
                QMessageBox::critical(this, "critical", "Please input the password again!", QMessageBox::Yes | QMessageBox::No);
                ui->password1->clear();
                ui->password2->clear();
                ui->username->setFocus();
            }
            else
            {
                if(ui->password1->text()!=ui->password2->text())
                {
                    QMessageBox::critical(this, "critical", "The two passwords you have input is not the same,please input again!!", QMessageBox::Yes | QMessageBox::No);
                    ui->password1->clear();
                    ui->password2->clear();
                    ui->username->setFocus();
                }
                else
                {

                }
            }
        }
    }
}
