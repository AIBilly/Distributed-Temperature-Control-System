#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = new Controll_client();
    connect(client,SIGNAL(mesArrive()),this,SLOT(refresh_state()));
    connect(client,SIGNAL(linkChanged(QString)),this,SLOT(refresh_link_state(QString)));

    one_sec = new QTimer();
    one_sec->setInterval(1000);
    connect(one_sec,SIGNAL(timeout()),this,SLOT(send_mes()));

    this->setWindowTitle("Room No."+QString::number(client->getRoomNum()));
    ui->tem_adj->setValue(client->getGoalTemp());
    ui->wind_speed_adj->setValue(client->getWindSpeed()-1);
    ui->cur_tem->setText(QString("%1").arg(client->getTemRoom()));
    ui->link_state->setText("disconnected");
    ui->mode->setText("Unknown");
    ui->schedule_state->setText("Unknown");

    int power=client->getState();
    if(power==2)
    {
        ui->tem_adj->setDisabled(1);
        ui->wind_speed_adj->setDisabled(1);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refresh_state(void)
{
    ui->cur_tem->setText(QString("%1").arg(client->getTemRoom()));
    int mode=client->getModel();
    if(mode==1)
        ui->mode->setText("Cooling");
    else
        ui->mode->setText("Heating");
    int s_state=client->getState();
    if(s_state==1)
        ui->schedule_state->setText("Running");
    else if(s_state==3)
        ui->schedule_state->setText("Waiting");
    else
        ui->schedule_state->setText("Unknown");
}

void MainWindow::refresh_link_state(QString state)
{
    ui->link_state->setText(state);
}

void MainWindow::on_tem_adj_valueChanged(const QString &arg1)
{
    if(!one_sec->isActive())
        one_sec->start();
}

void MainWindow::on_wind_speed_adj_valueChanged(int value)
{
    if(!one_sec->isActive())
        one_sec->start();
}

void MainWindow::send_mes(void)
{
    one_sec->stop();
    //send message
    QString content = "4 "+ QString::number(client->getRoomNum()) + " " + QString("%1").arg(client->getTemRoom())
            + " " + QString::number(ui->tem_adj->value())+ " " + QString::number(ui->wind_speed_adj->value()+1);
    client->send(content);
}

void MainWindow::on_power_clicked()
{
    int power = client->getState();
    if(power==2)
    {
        client->setState(stay);
        ui->tem_adj->setEnabled(1);
        ui->wind_speed_adj->setEnabled(1);
        QString content = "1 "+ QString::number(client->getRoomNum()) + " " + QString("%1").arg(client->getTemRoom())
                + " " + QString("%1").arg(client->getGoalTemp())+ " " + QString::number(client->getWindSpeed());
        client->send(content);
    }
    else
    {
        client->setState(off);
        ui->tem_adj->setDisabled(1);
        ui->wind_speed_adj->setDisabled(1);
        QString content = "2 "+ QString::number(client->getRoomNum()) + " " + QString("%1").arg(client->getTemRoom())
                + " " + QString("%1").arg(client->getGoalTemp())+ " " + QString::number(client->getWindSpeed());
        client->send(content);
    }
}
