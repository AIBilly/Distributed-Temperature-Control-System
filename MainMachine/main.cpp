#include "mainwindow.h"
#include "staff_controler.h"
#include "logindlg.h"
#include <QApplication>

staff_controler sc;

int systemstate = -1;

int main(int argc, char *argv[])
{
    int currentExitCode = 0;
    QApplication a(argc, argv);

    do
    {
        loginDlg login;
        if(login.exec()==QDialog::Accepted)
        {
            MainWindow w;
            w.show();
            currentExitCode = a.exec();
        }
        else return 0;
    }while(currentExitCode == EXIT_CODE_REBOOT);

    return 0;
}
