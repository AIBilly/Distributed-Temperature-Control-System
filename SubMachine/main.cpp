#include "mainwindow.h"
#include <QApplication>
#include "controll_client.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
