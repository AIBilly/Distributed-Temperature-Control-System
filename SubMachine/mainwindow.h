#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "controll_client.h"
#include <QString>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void refresh_state(void);
    void refresh_link_state(QString state);

    void on_tem_adj_valueChanged(const QString &arg1);

    void send_mes(void);

    void on_wind_speed_adj_valueChanged(int value);

    void on_power_clicked();

private:
    Controll_client *client;
    Ui::MainWindow *ui;
    QTimer* one_sec;
};

#endif // MAINWINDOW_H
