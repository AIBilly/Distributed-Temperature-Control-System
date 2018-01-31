#include "logindlg.h"
#include "ui_logindlg.h"
#include "sign_up.h"
#include "staff_controler.h"

extern staff_controler sc;
extern int systemstate;

loginDlg::loginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDlg)
{
    ui->setupUi(this);
    ui->pwdlineEdit->setEchoMode(QLineEdit::Password);
    ui->userlineEdit->setFocus();
}

loginDlg::~loginDlg()
{
    delete ui;
}

void loginDlg::on_login_clicked()
{
    if(ui->userlineEdit->text()=="\0" || ui->pwdlineEdit->text()=="\0")
    {
        QMessageBox::warning(this, "Warning", "username or password not be input!", QMessageBox::Yes | QMessageBox::No);
        ui->userlineEdit->clear();
        ui->pwdlineEdit->clear();
        ui->userlineEdit->setFocus();
    }
    else
    {
        //if((sc.login(ui->userlineEdit->text(),ui->pwdlineEdit->text(),systemstate))==1)
        //{
            systemstate = 1;
            accept();
        //}
        //else
        //{
        //    QMessageBox::critical(this, "critical", "user name or password error!", QMessageBox::Yes | QMessageBox::No);
        //    ui->userlineEdit->clear();
        //    ui->pwdlineEdit->clear();
        //    ui->userlineEdit->setFocus();
        //}
    }
}
